# pico-htu21dfDriv
HTU21D-F library for pico-sdk \
Based on [Adafruit_HTU21DF_Library](https://github.com/adafruit/Adafruit_HTU21DF_Library)

## Usage
Add the _pico-htu21dfDriv_ subdirectory to the CMakeLists.txt of your project and include the library in _target_link_libraries_.
### Initializing the sensor
Before reading the sensor, it must be initialized with _HTU21DF_init_.
###
By default, the library uses pins 4 (SDA) and 5 (SCL). `HTU21DF_setI2C(i2c_inst_t *i, uint16_t sda, uint16_t scl, uint8_t addr);` can be used to select the I2C peripheral, pins and sensor adress.
### Reading the sensor
`HTU21DF_readTemperature()` returns the temperature in °C as _float_.\
`HTU21DF_readHumidity()` returns the relative humidity in percents, as _float_.