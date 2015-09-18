#include<main.h> 
#include<stdlib.h>
#include<stdio.h>
#include<timeout.h>
#include<timeout.c>		
#include"ds1307.h"
#include<serial.h>	

#define SEC   0x00
#define	MIN   0x01	
#define HOUR  0x02
#define DAY   0x03
#define DATE  0x04
#define MONTH 0x05
#define YEAR  0x06
void send_dt(tByte);
unsigned char STRBUF[3];
	
void PowerOn()
{
    unsigned char inner, outer;

    for (outer = 0x00; outer < 0x10; outer++) 
    {
        for (inner = 0x00; inner < 0xFF; inner++);
    }
    
    ser_init();
    
    for (inner = 0; inner < 10; inner++) 
    	delay_50ms();
}

void send2lcd(unsigned char value)
{
	unsigned char buf = 0;	
	
	buf = value & 0xF0;		/* Filter for high byte */
	buf = (buf>>4)|(0x30);		/* Convert  to ascii code */

	printf("%c",buf);			/* Show on LCD */

	buf = value & 0x0F;		/* Filter for low byte */
	buf = buf | 0x30;       	/* Convert to ascii code */

	printf("%c",buf);			/* Show on LCD */
}	

void main(void)			
{
	unsigned char sec, min, hour, date, month, year;
	unsigned int k;
	PowerOn();  
	
    printf("Date:");	
	printf("Time:");	
	
	DS1307_settime(0x23,0x59,0x00);		/* Set Time (hh:mm:ss) */
	DS1307_setdate(0x31,0x12,0x06);  	/* Set Date (dd/mm/yy) */
	
	while(1) 
	{
		/* Get Date & Time */
		sec   = DS1307_get(SEC);	
		min   = DS1307_get(MIN);	
		hour  = DS1307_get(HOUR);
		date  = DS1307_get(DATE);
		month = DS1307_get(MONTH);
		year  = DS1307_get(YEAR);
         sec=0x59;
		/* Show Date in format dd/mm/yr */
			/* Set LCD cursor at (1,6) */
		//printf("%x",date);

          btoi(sec);
        printf("%d",sec);

	    send2lcd(date);		/* Show date on LCD */
	
		printf("/");		
		//	printf("%x",month);
		send2lcd(month);	/* Show month on LCD */
		
		printf("/20");	
			//printf("%x",year);
		send2lcd(year);		/* Show year on LCD */
        printf("\n");
		/* Show Time in format hr:min:sec */	
			
	    send2lcd(hour);		/* Show hour on LCD */
		//	printf("%x",hour);	
		printf(":");   
		   	
		send2lcd(min);		/* Show min on LCD */
	    //printf("%x",min);	
		printf(":");		
		//printf("%x",sec);
		send2lcd(sec);		/* Show sec on LCD */

		for(k=0;k<100;k++)
		 delay_50ms();
	}	   
}


unsigned int btoi (unsigned char bcd) 
{               // change bcd to hex(int)
    STRBUF[0] = ((bcd & 0xf0) >> 4) | 0x30;           // to string first
    STRBUF[1] = (bcd & 0x0f) | 0x30;
    STRBUF[2] = 0;
    return (atoi (STRBUF));                           // string to int
}
