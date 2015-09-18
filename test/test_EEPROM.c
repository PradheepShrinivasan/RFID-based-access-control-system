#include<stdio.h>
#include<stdlib.h>
#include<main.h>
#include<timeout.h>
#include"timeout.c"
#include <reg52.h>  		
#include "24xx512.h"
#include "ds1307.h"

void date2prom(unsigned int);	
void ser_init(void);
void readprom(unsigned int);
void time2prom(unsigned int);	

#define SEC   0x00
#define	MIN   0x01	
#define HOUR  0x02
#define DATE  0x04
#define MONTH 0x05
#define YEAR  0x06

union intchar 
{
	unsigned int inte;
	unsigned char ch[2];
}value;

unsigned char pt[5];   

void init()
{
    unsigned char inner, outer;

    for (outer = 0x00; outer < 0x10; outer++) 
    	for (inner = 0x00; inner < 0xFF; inner++);
    
	ser_init();

	for (inner = 0; inner < 10; inner++) 
		delay_5ms();
}

void convertdate(unsigned char value,unsigned char i)
{
	unsigned char buf = 0;	

	if(i!=4)
	{
		buf = value & 0xF0;		/* Filter for high byte */
		buf = (buf>>4)|(0x30);	/* Convert  to ascii code */
		pt[i] = buf;
		i++;
	}

	buf = value & 0x0F;			/* Filter for low byte */
	buf = buf | 0x30;       	/* Convert to ascii code */
	pt[i]=buf;
}	

void converttime(unsigned char value,unsigned char i)
{
	unsigned char buf = 0;	


	buf = value & 0xF0;		/* Filter for high byte */
	buf = (buf>>4)|(0x30);		/* Convert  to ascii code */
	pt[i] = buf;

	i++;
	if(i != 5)
	{
		buf = value & 0x0F;		/* Filter for low byte */
		buf = buf | 0x30;       	/* Convert to ascii code */
		pt[i]=buf;
	}
}	

/************************************************************************************************************/

void date2prom(unsigned int addr)			
{
	unsigned char tchar=0x00;
    
	tchar=DS1307_get(DATE);                //receiving date,month and year
	convertdate(tchar,0);
	tchar=DS1307_get(MONTH);
	convertdate(tchar,2);
	tchar=DS1307_get(YEAR);
    convertdate(tchar,4);      
    value.inte=0x0000;   
      
   	value.inte=atoi(pt);                     //converting it into a integer from a string  
    
    EEPROM_set(addr,value.ch[0]);               //writing the higer order to the memory
    delay_500micros();
    EEPROM_set(addr+1,value.ch[1]);               //writing the lower order to the memory
    delay_500micros();
}

/*****************************************************************************************************************************/

void time2prom(unsigned int addr)			//same work as above the problem is in the reconstruction
{
    unsigned char tchar=0x00;
	
	tchar=DS1307_get(HOUR);                //receiving date,month and year
	converttime(tchar,0);
	tchar=DS1307_get(MIN);
	converttime(tchar,2);
	tchar=DS1307_get(SEC);
    converttime(tchar,4);      
    value.inte=0x0000;           
   	value.inte=atoi(pt);                     //converting it into a integer from a string  

    EEPROM_set(addr,value.ch[0]);               //writing the higer order to the memory
    delay_500micros();
    EEPROM_set(addr+1,value.ch[1]);               //writing the lower order to the memory
    delay_500micros();
}

/************************************************************************************************************/

void main(void)
{
	unsigned int val,i;
	init();  
	DS1307_settime(0x18,0x49,0x46);		/* Set Time (hh:mm:ss) */
	DS1307_setdate(0x02,0x01,0x07);  	/* Set Date (dd/mm/yy) */

	while(1)
	{
		date2prom(0x0010);
		delay_50ms();
		readprom(0x0010);
		printf("\ndate =%05d",value.inte);

		value.inte=0x0000;

		time2prom(0x0012);
		delay_50ms();
		readprom(0x0012);
		printf("\ntime =%05d",value.inte);
		
		for(i=0;i<20;i++)
			delay_50ms();
	}
	while(1);
}

/*************************************************************************************************************/

void ser_init(void)
{
    SCON  = 0x50;		        /* SCON: mode 1, 8-bit UART, enable rcvr      */
    TMOD |= 0x20;               /* TMOD: timer 1, mode 2, 8-bit reload        */
    TH1   = 253;                /* TH1:  reload value for 9600 baud @ 11.0592MHz   */
    TR1   = 1;                  /* TR1:  timer 1 run                          */
    TI    = 1;    
}

/*************************************************************************************************************/
void readprom(unsigned int addr)    //the reconstruction is done here
{   
    value.inte=0x0000;
    value.ch[0]=EEPROM_get(addr);//getting the higer order
	delay_50micros();
    value.ch[1]=EEPROM_get(addr+1); // lower 
}

/***************************************************************************************************************/
