#ifndef __DS1307_H__
#define __DS1307_H__


#define DS1307_ID 0xD0	

#define SEC   0x00
#define	MIN   0x01	
#define HOUR  0x02
#define DATE  0x04
#define MONTH 0x05
#define YEAR  0x06

unsigned char DS1307_get(unsigned char addr)
{
	unsigned char ret;	

	I2C_start();            /* Start i2c bus */

	I2C_write(DS1307_ID);   /* Connect to DS1307 */
	I2C_write(addr);		/* Request RAM address on DS1307 */
	
	I2C_start();			/* Start i2c bus */

	I2C_write(DS1307_ID+1);	/* Connect to DS1307 for Read */
	ret = I2C_read();		/* Receive data */
	
	I2C_stop();				/* Stop i2c bus */
  // printf("%02x ",ret);
   return ret;			
}

void DS1307_settime(unsigned char hh, unsigned char mm, unsigned char ss)
{
	I2C_start(); 

	I2C_write(DS1307_ID);	/* connect to DS1307 */ 
	I2C_write(0x00);       /* Request RAM address at 00H */ 
	I2C_write(ss);			/* Write sec on RAM address 00H */
	I2C_write(mm);			/* Write min on RAM address 01H */
	I2C_write(hh);			/* Write hour on RAM address 02H */

	I2C_stop();           	/* Stop i2c bus */
}

void DS1307_setdate(unsigned char dd, unsigned char mm, unsigned char yy)
{
 	I2C_start();	

	I2C_write(DS1307_ID);	/* connect to DS1307 */
	I2C_write(0x04);		/* Request RAM address at 04H */ 

	I2C_write(dd);			/* Write date on RAM address 04H */
	I2C_write(mm);			/* Write month on RAM address 05H */
	I2C_write(yy);			/* Write year on RAM address 06H */
   
	I2C_stop();				/* Stop i2c bus */
}

#endif