#ifndef _DS1307_GUARD__
#define _DS1307_GUARD__

#include <stdint.h>
#include <stdbool.h>

uint8_t read_seconds(void);
uint8_t read_minutes(void);
uint8_t read_hour(void);

bool write_seconds(uint8_t seconds);
bool write_minutes(uint8_t minutes);
bool write_hour(uint8_t hour);

#endif