#include <pic16f887.h>

#include "i2c.h"

void i2c_init(void) {
    TRISC |= 0b00011000; //RC3 & RC4 (SLCL & SDA) as inputs
    SSPSTAT = 0x80; // Disable slew rate control
    SSPCON = 0x28; // Enable MSSP as I2C Master
    SSPADD = 19; // 100k Hz for I2C @ FOSC = 8M Hz
}

void i2c_start(void) {
    SSPCON2bits.SEN = 1;
    i2c_hold();
    return;
}

void i2c_rep_start(void) {
    SSPCON2bits.RSEN = 1;
    i2c_hold();
    return;
}

void i2c_stop(void) {
    SSPCON2bits.PEN = 1;
    i2c_hold();
    return;
}

bool i2c_wait_ack(void) {
    i2c_hold();
    return SSPCON2bits.ACKSTAT;
}

bool i2c_write(unsigned char slave, unsigned char addr, unsigned char val) {
    i2c_start();
    SSPBUF = (slave & 0xFE);
    if (i2c_wait_ack() == true) {
        return false; // No ACK from slave. Abort
    }
    SSPBUF = addr;
    if (i2c_wait_ack() == true) {
        return false;
    }
    SSPBUF = val;
    if (i2c_wait_ack() == true) {
        return false;
    }
    i2c_stop();
    
    return true;
}

bool i2c_read(unsigned char slave, unsigned char addr, unsigned char *val) {
    i2c_start();
    SSPBUF = (slave & 0xFE);
    if (i2c_wait_ack() == true) {
        return false;
    }
    SSPBUF = addr;
    if (i2c_wait_ack() == true) {
        return false;
    }
    SSPBUF = (slave | 0x01);
    if (i2c_wait_ack() == true) {
        return false;
    }
    SSPCON2bits.RCEN = 1;
    i2c_hold();
    *val = SSPBUF;
    SSPCON2bits.ACKEN = 1;
    i2c_hold();
    i2c_stop();
    
    return true;
}