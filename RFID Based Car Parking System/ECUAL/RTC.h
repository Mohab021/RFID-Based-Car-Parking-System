#ifndef RTC_H_
#define RTC_H_

#include <time.h>
#include "../MCAL/I2C/I2C.h"

#define Device_Write_address	0xD0				/* Define RTC DS1307 slave address for write operation */
#define Device_Read_address		0xD1				/* Make LSB bit high of slave address for read operation */
#define TimeFormat12			0x40				/* Define 12 hour format */
#define AMPM					0x20
#define hour_12_AM				0x40
#define hour_12_PM				0x60
#define hour_24					0x00

int second, minute, hour, day, date, month, year;

#endif /* RTC_H_ */