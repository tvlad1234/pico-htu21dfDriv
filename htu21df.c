#include "htu21df.h"
#include "hardware/i2c.h"

/** Read temperature register. */
#define HTU21DF_READTEMP (0xE3)

/** Read humidity register. */
#define HTU21DF_READHUM (0xE5)

/** Write register command. */
#define HTU21DF_WRITEREG (0xE6)

/** Read register command. */
#define HTU21DF_READREG (0xE7)

/** Reset command. */
#define HTU21DF_RESET (0xFE)

static uint8_t HTU21DF_ADDR = DEFAULT_HTU21DF_ADDR;
i2c_inst_t *htu21_i2c = i2c_default;
uint16_t htu21_sda = PICO_DEFAULT_I2C_SDA_PIN;
uint16_t htu21_scl = PICO_DEFAULT_I2C_SCL_PIN;

void HTU21DF_setI2C(i2c_inst_t *i, uint16_t sda, uint16_t scl, uint8_t addr)
{
    htu21_i2c = i;
    htu21_sda = sda;
    htu21_scl = scl;
    HTU21DF_ADDR = addr;
}

uint8_t htuRead8(uint8_t a)
{
    uint8_t r;
    i2c_write_blocking(htu21_i2c, HTU21DF_ADDR, &a, 1, true);
    i2c_read_blocking(htu21_i2c, HTU21DF_ADDR, &r, 1, false);
    return r;
}

void htuRead24(uint8_t a, uint8_t buf[])
{
    i2c_write_blocking(htu21_i2c, HTU21DF_ADDR, &a, 1, true);
    sleep_ms(50);
    i2c_read_blocking(htu21_i2c, HTU21DF_ADDR, buf, 3, false);
}

uint8_t HTU21DF_init()
{

    i2c_init(htu21_i2c, 400 * 1000);
    gpio_set_function(htu21_sda, GPIO_FUNC_I2C);
    gpio_set_function(htu21_scl, GPIO_FUNC_I2C);
    gpio_pull_up(htu21_sda);
    gpio_pull_up(htu21_scl);

    if (htuRead8(HTU21DF_READREG) != 0x2)
        return 0;

    return 1;
}

float HTU21DF_readTemperature(void)
{

    uint8_t buf[3];
    htuRead24(HTU21DF_READTEMP, buf);
    uint16_t t = buf[0];
    t <<= 8;
    t |= buf[1] & 0b11111100;

    // 3rd byte is the CRC

    float temp = t;
    temp *= 175.72f;
    temp /= 65536.0f;
    temp -= 46.85f;
    return temp;
}

float HTU21DF_readHumidity(void)
{
    uint8_t buf[3];
    htuRead24(HTU21DF_READHUM, buf);

    uint16_t h = buf[0];
    h <<= 8;
    h |= buf[1] & 0b11111100;

    // 3rd byte is the CRC

    float hum = h;
    hum *= 125.0f;
    hum /= 65536.0f;
    hum -= 6.0f;
    return hum;
}