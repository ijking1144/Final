#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spi/spi.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/of.h>


//https://chlazza.nfshost.com/sdcardinfo.html
#define CMD0    0
#define CMD8    8 
#define CMD55   55  
#define ACMD41  41  

struct sd_spi{
  struct spi_device * spi;
  bool ready;
  u8 * tx_buffer;
  u8 * rx_buffer;
};

int sd_send(struct sd_spi * dev, u8 cmd, u32 data, u8 * response);
int sd_init(struct sd_spi * dev);
