#ifndef __I2C_GUARD__
#define __I2C_GUARD__

#include <stdbool.h>

#define i2c_hold() while (PIR1bits.SSPIF == 0); PIR1bits.SSPIF == 0;

void i2c_init(void);
void i2c_start(void);
void i2c_rep_start(void);
void i2c_stop(void);
bool i2c_wait_ack(void);
bool i2c_write(unsigned char slave, unsigned char addr, unsigned char val);
bool i2c_read(unsigned char slave, unsigned char addr, unsigned char *val);

#endif

