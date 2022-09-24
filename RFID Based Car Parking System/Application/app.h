#ifndef APP_H_
#define APP_H_

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <avr/eeprom.h>			/* Include AVR EEPROM header file */
#include "../ECUAL/RTC.h"
#include "../MCAL/I2C/I2C.h"
#include "../MCAL/LCD/LCD.h"
#include "../MCAL/USART/USART.h"

int i_sec, i_min, i_hr, i_total;

bool IsItPM(char hour_);
void app(void);

#endif /* APP_H_ */