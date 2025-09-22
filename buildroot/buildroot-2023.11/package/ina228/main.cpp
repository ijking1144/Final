#include "i2c.hpp"
#include <stdio.h>

int main() {
    INA228 sensor;
    
    if (sensor.ina228_init() == 0) {
        printf("INA228 initialized successfully!\n");
        
        if (sensor.collect() == 0) {
            printf("Measurements collected successfully!\n");
        } else {
            printf("Failed to collect measurements\n");
        }
    } else {
        printf("Failed to initialize INA228\n");
    }
    
    return 0;
}
