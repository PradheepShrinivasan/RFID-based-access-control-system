#ifndef __24C512_H__
#define __24C512_H__

#include "i2c.h" /* Need i2c bus */

#define EEPROMS_ID 0xA0	/* Microchip 24xx512 */

unsigned char EEPROM_get(unsigned int addr)
{
	unsigned char dat;	

	I2C_start();            /* Start i2c bus */

	I2C_write(EEPROMS_ID);   /* Connect to EEPROM */
	I2C_write(addr&0xF0);	 /* Request RAM address (Hight byte) */
	I2C_write(addr&0x0F);	 /* Request RAM address (Low byte) */
	
	I2C_start();			/* Start i2c bus */

	I2C_write(EEPROMS_ID+1);/* Connect to EEPROM for Read */
	dat = I2C_read();		/* Receive data */

	I2C_noack();
	
	I2C_stop();	
	/* Stop i2c bus */
     return dat;			
}

void EEPROM_pagew(unsigned int addr,unsigned int number,unsigned char *data1)
{
 	int i;
	I2C_start(); 

	I2C_write(EEPROMS_ID);   /* Connect to EEPROM */
	I2C_write(addr&0xF0);	 /* Request RAM address (Hight byte) */
	I2C_write(addr&0x0F);	 /* Request RAM address (Low byte) */

	for(i=0;i<number;i++,data1++)
    	I2C_write(*data1);

	I2C_stop();           	/* Stop i2c bus */
}

void EEPROM_set(unsigned int addr, unsigned char val)
{
	I2C_start(); 

	I2C_write(EEPROMS_ID);   /* Connect to EEPROM */
	I2C_write(addr&0xF0);	 /* Request RAM address (Hight byte) */
	I2C_write(addr&0x0F);	 /* Request RAM address (Low byte) */

	I2C_write(val);			/* Write sec on RAM specified address */

	I2C_stop();           	/* Stop i2c bus */
}

void EEPROM_pager(unsigned int addr,unsigned int number,unsigned char *data1)  
/* this is to read eeprom in the page mode valid upto 32 bytes */
{
 	int i;
	I2C_start(); 
    I2C_write(EEPROMS_ID);
	
	I2C_write(addr&0xF0);	 /* Request RAM address (Hight byte) */
	I2C_write(addr&0x0F);	 /* Request RAM address (Low byte) */

	I2C_start();
    I2C_write(EEPROMS_ID+1);   /* Connect to EEPROM */

	for(i=0;i<number;i++,data1++)
	{
    	*data1=I2C_read();
		if (i!=(number-1))
	 		I2C_ack();
	}
    
    I2C_noack();
	I2C_stop();           	/* Stop i2c bus */
}

#endif
