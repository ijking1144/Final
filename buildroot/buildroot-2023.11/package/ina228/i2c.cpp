#include <i2c.hpp>

INA228::INA228(const char* i2c_dev): 
  fd(-1) 
  {}

int INA228::read_register(uint8_t reg, uint16_t &data){
  if(fd==-1){
    return -1;
  }
  if (write(fd, &reg, 1) != 1) {
    return -1;
  }
  uint8_t buffer[2];
  if (read(fd, buffer, 2) != 2){
    return -1;
  }
  data = (buffer[0] << 8) | buffer[1];
  return 0;
}

int INA228::ina228_init(){
  int error=0;
  uint16_t id;
  fd = open("/dev/i2c-1", O_RDWR);
  if(fd==-1){
    error=-1;
    return error;
  }
  error=ioctl(fd, I2C_SLAVE, INA228_SLAVE_ADDR);
  if (error<0){
    close(fd);
    return error;
  }
  if ((read_register(INA228_MANUFACTURER_ID, id) < 0) || (id!=INA228_MFG_ID_TI)){
    close(fd);
    error=-1;
    return error;
  }
  return error;
}

int INA228::collect(){
  bool success=true;
  if (fd == -1){
    success=false;
    return -1;
  }
  if (success && (read_register(INA228_REG_VSBUS, voltage))==0){
    printf("Voltage= %u\n",voltage);
  }
  else{
    success = false;
    return -1;
  }
  if (success && (read_register(INA228_REG_CURRENT, current))==0){
    printf("Current= %u\n",current);
  }
  else{
    success = false;
    return -1;
  }
  return 0;
}

INA228::~INA228(){
  if (fd!=-1){
    close(fd);
  }
}

