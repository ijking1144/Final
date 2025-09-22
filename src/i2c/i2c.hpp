#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

#define INA228_REG_CONFIG                    (0x00)
#define INA228_REG_ADCCONFIG                 (0x01)
#define INA228_REG_SHUNTCAL                  (0x02)
#define INA228_REG_SHUNTTEMPCO               (0x03)
#define INA228_REG_VSHUNT                    (0x04)
#define INA228_REG_VSBUS                     (0x05)
#define INA228_REG_DIETEMP                   (0x06)
#define INA228_REG_CURRENT                   (0x07)
#define INA228_REG_POWER                     (0x08)
#define INA228_REG_ENERGY                    (0x09)
#define INA228_REG_CHARGE                    (0x0a)
#define INA228_REG_DIAG_ALRT                 (0x0b)
#define INA228_REG_SOVL                      (0x0c)
#define INA228_REG_SUVL                      (0x0d)
#define INA228_REG_BOVL                      (0x0e)
#define INA228_REG_BUVL                      (0x0f)
#define INA228_REG_TEMP_LIMIT                (0x10)
#define INA228_REG_TPWR_LIMIT                (0x11)
#define INA228_MANUFACTURER_ID               (0x3e)
#define INA228_DEVICE_ID                     (0x3f)
#define INA228_MFG_ID_TI                     (0x5449)
#define INA228_MFG_DIE                       (0x228) 
#define INA228_SLAVE_ADDR                    (0x40)
class INA228
{
public:
    INA228(const char* i2c_dev = "/dev/i2c-1");
    ~INA228();
    int read_register(uint8_t reg, uint16_t &data);
    int collect();
    int ina228_init();
    uint16_t voltage{0};
    uint16_t current{0};

private:
    int fd;
};

