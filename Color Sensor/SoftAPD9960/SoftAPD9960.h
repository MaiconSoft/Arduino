#ifndef _SOfT_APDS9960__
#define _SOfT_APDS9960__

// #define USE_DEFAULT_I2C_PINS // remova esse comentário para usar os pinos padrões de I2C

#include <SoftWire.h>
extern SoftWire Wire2 = SoftWire();


#define APDS9960_ADDRESS (0x39)
#define APDS9960_ENABLE 0x80
#define APDS9960_STATUS 0x93
#define APDS9960_CDATAL 0x94
#define APDS9960_RDATAL 0x96
#define APDS9960_GDATAL 0x98
#define APDS9960_BDATAL 0x9A
#define APDS9960_CDATAH 0x95
#define APDS9960_ID  0x92
#define APDS9960_ATIME          0x81
#define DEFAULT_ATIME           219     // 103ms


typedef struct
{
    uint16_t red;
    uint16_t green;
    uint16_t blue;
    uint16_t light;
} rgb_t;


struct enable {

    // power on
    uint8_t PON : 1;

    // ALS enable
    uint8_t AEN : 1;

    // Proximity detect enable
    uint8_t PEN : 1;

    // wait timer enable
    uint8_t WEN : 1;

    // ALS interrupt enable
    uint8_t AIEN : 1;

    // proximity interrupt enable
    uint8_t PIEN : 1;

    // gesture enable
    uint8_t GEN : 1;

    uint8_t get() {
        return (GEN << 6) | (PIEN << 5) | (AIEN << 4) | (WEN << 3) | (PEN << 2) |
               (AEN << 1) | PON;
    };
};

struct enable _enable;


struct status {
    /* ALS Valid. Indicates that an ALS cycle has completed since AEN was
    asserted or since a read from any of the ALS/Color data registers.
    */
    uint8_t AVALID : 1;

    /* Proximity Valid. Indicates that a proximity cycle has completed since PEN
    was asserted or since PDATA was last read. A read of PDATA automatically
    clears PVALID.
    */
    uint8_t PVALID : 1;

    /* Gesture Interrupt. GINT is asserted when GFVLV becomes greater than
    GFIFOTH or if GVALID has become asserted when GMODE transitioned to zero.
    The bit is reset when FIFO is completely emptied (read).
    */
    uint8_t GINT : 1;

    // ALS Interrupt. This bit triggers an interrupt if AIEN in ENABLE is set.
    uint8_t AINT : 1;

    // Proximity Interrupt. This bit triggers an interrupt if PIEN in ENABLE is
    // set.
    uint8_t PINT : 1;

    /* Indicates that an analog saturation event occurred during a previous
    proximity or gesture cycle. Once set, this bit remains set until cleared by
    clear proximity interrupt special function command (0xE5 PICLEAR) or by
    disabling Prox (PEN=0). This bit triggers an interrupt if PSIEN is set.
    */
    uint8_t PGSAT : 1;

    /* Clear Photodiode Saturation. When asserted, the analog sensor was at the
    upper end of its dynamic range. The bit can be de-asserted by sending a
    Clear channel interrupt command (0xE6 CICLEAR) or by disabling the ADC
    (AEN=0). This bit triggers an interrupt if CPSIEN is set.
    */
    uint8_t CPSAT : 1;

    void set(uint8_t data) {
        AVALID = data & 0x01;
        PVALID = (data >> 1) & 0x01;
        GINT = (data >> 2) & 0x01;
        AINT = (data >> 4) & 0x01;
        PINT = (data >> 5) & 0x01;
        PGSAT = (data >> 6) & 0x01;
        CPSAT = (data >> 7) & 0x01;
    }
};
status _status;


class SoftAPD9960
{
public:
    SoftAPD9960() {};
    ~SoftAPD9960() {};
    bool begin()
    {
        Wire2.begin();

        /* Make sure we're actually connected */
        uint8_t x = read8(APDS9960_ID);
        if (x != 0xAB) {
            return false;
        }

        enable(false);
        delay(10);
        enable(true);
        delay(10);
        write8(APDS9960_ATIME, DEFAULT_ATIME);
        return true;
    }

    bool enableColor(boolean en) {
        _enable.AEN = en;
        write8(APDS9960_ENABLE, _enable.get());
        return true;
    }

    bool colorDataReady() {
        _status.set(read8(APDS9960_STATUS));
        return _status.AVALID;
    }

    void getColorData(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c)
    {
        *c = read16R(APDS9960_CDATAL);
        *r = read16R(APDS9960_RDATAL);
        *g = read16R(APDS9960_GDATAL);
        *b = read16R(APDS9960_BDATAL);
    }

    void getColor(rgb_t *value)
    {

        wait();
        (*value).light =  read16R(APDS9960_CDATAL);
        (*value).red = read16R(APDS9960_RDATAL);
        (*value).green = read16R(APDS9960_GDATAL);
        (*value).blue = read16R(APDS9960_BDATAL);
    }

    void wait()
    {
        while (!colorDataReady())
        {
            delay(1);
        }
    }
private:
    void write(uint8_t reg, uint8_t *buf, uint8_t num)
    {
        Wire2.beginTransmission((uint8_t)APDS9960_ADDRESS);
        Wire2.write((uint8_t)reg);
        Wire2.write((uint8_t *)buf, num);
        Wire2.endTransmission();
    }


    uint8_t read(uint8_t reg, uint8_t *buf, uint8_t num)
    {
        uint8_t pos = 0;
        bool eof = false;

// on arduino we need to read in 32 byte chunks
        while (pos < num && !eof) {

            uint8_t read_now = min(32, num - pos);
            Wire2.beginTransmission((uint8_t)APDS9960_ADDRESS);
            Wire2.write((uint8_t)reg + pos);
            Wire2.endTransmission();

            Wire2.requestFrom((uint8_t)APDS9960_ADDRESS, read_now);

            for (int i = 0; i < read_now; i++) {
                if (!Wire2.available()) {
                    eof = true;
                    break;
                }
                buf[pos] = Wire2.read();
                pos++;
            }
        }
        return pos;
    }


    uint8_t read8(byte reg) {
        uint8_t ret;
        read(reg, &ret, 1);
        return ret;
    }


    void write8(byte reg, byte value) {
        write(reg, &value, 1);
    }


    uint16_t read16R(uint8_t reg) {
        uint8_t ret[2];
        read(reg, ret, 2);
        return (ret[1] << 8) | ret[0];
    }






    void enable(boolean en)
    {
        _enable.PON = en;
        write8(APDS9960_ENABLE, _enable.get());
    }
};

#endif