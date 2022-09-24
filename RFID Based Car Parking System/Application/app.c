#include "app.h"

bool IsItPM(char hour_)
{
	if(hour_ & (AMPM))
	return 1;
	else
	return 0;
}

void app(void){
	char buffer[20], RFID[15], R_array[15];
	char* IDs[5];
	
	USART_Init(9600);			/* initialize USART with 9600 baud rate */
	I2C_Init();										/* Initialize I2C */
	lcdinit();										/* Initialize LCD16x2 */

	memset(RFID,0,15);
	memset(R_array,0,15);
	int mt;

	//Write valid IDs for authorized persons
	IDs[0]="4ADG532WE15D";
	IDs[1]="ER5A3Q21W53Q";
	IDs[2]="2SQ53AS4FR5H";
	IDs[3]="45HG6WD56Q54";
	IDs[4]="F8E4G84465DS";

    while(1)
    {
		
		RTC_Read_Clock(0);							// Read the clock with second address i.e location is 0
		if (hour & TimeFormat12)	
		{
			sprintf(buffer, "%02x:%02x:%02x  ", (hour & 0b00011111), minute, second);
			if(IsItPM(hour))
			strcat(buffer, "PM");
			else
			strcat(buffer, "AM");
		}
		else
		{
			sprintf(buffer, "%02x:%02x:%02x  ", (hour & 0b00011111), minute, second);
		}
		
		lcd_clear();
		lcd_print_xy(0,0,"Insert your Card");
	
		//Receive ID from RFID
		for(int x=0; x<12 ; x++)
		{
			RFID[x] = USART_RxChar();
		}
		
		mt = -1;
		for(int x=0 ; x<5 ; x++){

			if(strcmp(RFID, IDs[x])==0){ //Compare is Matched
				mt = 3*x;
				break;
			}
		}
		
		
		lcd_clear();
		if(mt != -1){ //ID is Listed and Authorized
			int S,M,H,T,D,Pay_D,Pay_C;
			
			i_sec = (second >> 4 & 7) * 10 + (second & 0x0F); //Convert RTC output format from [Binary Coded Decimal] to [Decimal]
			i_min = (minute >> 4)     * 10 + (minute & 0x0F);
			i_hr = ((hour & 0b00011111) >> 4)     * 10 + ((hour & 0b00011111) & 0x0F);
			i_total = i_sec + 60*i_min + 3600*i_hr;
			
			H = eeprom_read_byte ((const uint8_t*)mt);
			M = eeprom_read_byte ((const uint8_t*)mt+1);
			S = eeprom_read_byte ((const uint8_t*)mt+2);
			
			if(H==0xff || M==0xff || S==0xff){ //Not accessed before
				lcd_print_xy(0,0,"Matched");
				
				eeprom_write_block(&i_hr,mt,sizeof(char));
				eeprom_write_block(&i_min,mt+1,sizeof(char));
				eeprom_write_block(&i_sec,mt+2,sizeof(char));
				
				sprintf(buffer, "%02u:%02u:%02u", i_hr, i_min, i_sec);
				lcd_print_xy(1,0,buffer);
				_delay_ms(2000);
			}
			else{ //Accessed before
				lcd_print_xy(0,0,"Accessed before");
				
				H = eeprom_read_byte ((const uint8_t*)mt);
				M = eeprom_read_byte ((const uint8_t*)mt+1);
				S = eeprom_read_byte ((const uint8_t*)mt+2);
				T = S + 60*M + 3600*H;
				
				D = i_total - T;
				H = D / 3600;
				D %= 3600;
				M = D / 60;
				D %= 60;
				S = D;
				
				Pay_D = H*60 + M;
				Pay_C = 1.67*S;
				
				sprintf(buffer, "TC %02u:%02u:%02u", H, M, S);
				lcd_print_xy(1,0,buffer);
				_delay_ms(2000);
				lcd_clear();
				
				lcd_print_xy(0,0,"Payment:");
				sprintf(buffer, "$%02u.%02u", Pay_D, Pay_C);
				lcd_print_xy(1,0,buffer);
				_delay_ms(2000);
			
				H = 0xFF;
				M = 0xFF;
				S = 0xFF;
				//Reset time for this ID for the next fresh Access
				eeprom_write_block((void*)&H,mt,sizeof(char));
				eeprom_write_block((void*)&M,mt+1,sizeof(char));
				eeprom_write_block((void*)&S,mt+2,sizeof(char));
			}
		}
		else{
			lcd_print_xy(0,0,"Not Matched");
			_delay_ms(2000);
		}
	}	
}