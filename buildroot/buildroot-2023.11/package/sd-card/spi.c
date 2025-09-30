#include "spi.h"

static int sd_spi_transfer(struct spi_device *spi, const void *tx, void *rx, size_t len){
  struct spi_transfer xfer= {
    .tx_buf=tx,
    .rx_buf=rx,
    .len=len,
  };
  struct spi_message msg;
  spi_message_init(&msg);
  spi_message_add_tail(&xfer,&msg);
  return spi_sync (spi, &msg);
}

static void sd_dumb_clk(struct spi_device * spi){
  u8 one=0xFF;
  int i;
  for (i=0;i<10;i++){
    sd_spi_transfer(spi, &one, NULL, 1);
  }
}

int sd_send(struct sd_spi * dev, u8 cmd, u32 data, u8 * response){
  u8 buf[6];
  u8 resp=0xFF;
  buf[0]=0x40 | cmd;
  buf[1]= (data >> 24) & 0xFF;
  buf[2]= (data >> 16) & 0xFF;
  buf[3]= (data >> 8) & 0xFF;
  buf[4]= (data >> 0) & 0xFF;
  buf[5]= 0xFF;
  if (cmd == CMD0){
    buf[5]=0x95;
  }
  else if (cmd == CMD8){
    buf[5]=0x87;
  }
  sd_spi_transfer(dev->spi, buf, NULL, 6);
  int i;
  for (i=0; i<10; i++){
    sd_spi_transfer(dev->spi, NULL, &resp, 1);
    if (!(resp & 0x80)){
      break;
    }
  }
  if (response){
    *response = resp;
  }
  return 0;
}

int sd_init(struct sd_spi * dev){
  struct spi_device *spi = dev->spi;
  u8 response;
  int timeout=1000;
  spi->max_speed_hz=400000;
  spi_setup(spi);
  sd_dumb_clk(spi);
  sd_send(dev, CMD0, 0, &response);
  if(response !=0x01){
    return -EIO;
  }
  sd_send(dev, CMD8, 0x1AA, &response);
  if (response & 0x04){
    return -EIO;
  }
  else if (response == 0x01){
    u8 r7_buf[4];
    sd_spi_transfer(spi, NULL, r7_buf,4);
  }
  int i;
  for (i=0;i<timeout;i++){
    sd_send(dev, CMD55, 0, &response);
    sd_send(dev, ACMD41, 0x40000000, &response);
    if(response == 0x00){
      break;
    }
    msleep(1);
  }
  if (i==1000){
    return -ETIMEDOUT;
  }
  spi->max_speed_hz=2500000;
  spi_setup(spi);
  dev->ready =true;
  return 0;
}

static int sd_spi_probe(struct spi_device * spi)
{
  struct sd_spi *sd_dev;
  int ret;
  sd_dev=kmalloc(sizeof(*sd_dev), GFP_KERNEL);
  if(!sd_dev){
    return -ENOMEM;
  }
  sd_dev->spi=spi;
  sd_dev->ready=0;
  spi_set_drvdata(spi, sd_dev);
  spi->mode = SPI_MODE_0;
  spi->bits_per_word = 8;
  ret = spi_setup(spi);
  if(ret){
    kfree(sd_dev);
    return ret;
  }
  ret=sd_init(sd_dev);
  if(ret){
    kfree(sd_dev);
    return ret;
  }
  return 0;
}

static int sd_spi_remove(struct spi_device * spi){
  struct sd_spi *sd_dev = spi_get_drvdata(spi);
  if(sd_dev){
    sd_dev->ready = 0;
    kfree(sd_dev);
  }
  return 0;
}

// Device tree matching
static const struct of_device_id sd_spi_of_match[] = {
    { .compatible = "sd,spi-card" },
    { }
};
MODULE_DEVICE_TABLE(of, sd_spi_of_match);
// SPI device ID table
static const struct spi_device_id sd_spi_id[] = {
    { "sd-spi", 0 },
    { }
};
MODULE_DEVICE_TABLE(spi, sd_spi_id);
// SPI driver structure
static struct spi_driver sd_spi_driver = {
    .driver = {
        .name = "sd-spi",
        .of_match_table = sd_spi_of_match,
    },
    .id_table = sd_spi_id,
    .probe = sd_spi_probe,
    .remove = sd_spi_remove,
};
// Module initialization
static int __init sd_spi_module_init(void)
{
    printk(KERN_INFO "SD SPI driver loading\n");
    return spi_register_driver(&sd_spi_driver);
}
// Module cleanup
static void __exit sd_spi_module_exit(void)
{
    spi_unregister_driver(&sd_spi_driver);
    printk(KERN_INFO "SD SPI driver unloaded\n");
}


module_init(sd_spi_module_init);
module_exit(sd_spi_module_exit);
MODULE_DESCRIPTION("SD Card SPI Driver");
MODULE_AUTHOR("ijking");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
