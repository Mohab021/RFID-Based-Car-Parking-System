# RFID Based Car Parking System
RFID based Car Parking System is a simple project that offers an efficient car parking management system with the help of RFID Technology.

## System Description
The principle of operation of the project lies in functioning of RFID, RTC and EEPROM.  
Every authorized user has a specific RFID Card and the card details are pre-programmed in the microcontroller.  
When the RFID card is swiped against the RFID Reader, it can be read and transmitted to the microcontroller via serial communication protocol.  
The microcontroller then checks for the received card details with already stored details and checks for authenticity of the card.  
If the card is existing in the database, the microcontroller will check for the current time in the RTC module and stores the in time details of the particular card in the EEPROM.  
The communication between the microcontroller and RTC module is using I2C protocol.  
If the card is swiped again, the in time details from the EEPROM and out time details from the RTC are taken and the fare is calculated as per the tariffs.

## Component List
- ATmega32
- RFID Reader (EM-18)
- DS 1307 RTC Module
- Internal EEPROM
- LCD 16×2 (LM016L)

## Getting Started
### Executing program
Run the program simulated using Proteus 8.13.

## Screenshots
![Image_01](assets/scr01.png?raw=true)
![Image_02](assets/scr02.png?raw=true)

## Authors
@[Mohab021](https://github.com/Mohab021)  
@[Electronic Wings](http://www.electronicwings.com)  
@[Electronics Hub](http://www.electronicshub.org)

## Version History
- 0.1
  - Initial Release
