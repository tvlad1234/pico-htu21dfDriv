#ifndef _HTU21DF_H
#define _HTU21DF_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define DEFAULT_HTU21DF_ADDR 0x40

void HTU21DF_setI2C(i2c_inst_t *i, uint16_t sda, uint16_t scl, uint8_t addr);
uint8_t HTU21DF_init();

// Sensor read functions
float HTU21DF_readTemperature(void);
float HTU21DF_readHumidity(void);

#endif