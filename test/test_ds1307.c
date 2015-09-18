#include<main.h>
#include<timeout.h>
#include<timeout.c>
#include<serial.h>
#include <intrins.h>
#include <math.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<i2c.h>

unsigned char    HEXBUF[3];            // hex buffer
unsigned char    TIMBUF[8];            // ss,mm,hh,ww,dd,mm,yy,cc 


void rtset (void) 
{                    // set RTC status bit 
    TIMBUF[0] = TIMBUF[0] & 0x7f;      // clear CH (clock halt) 
    TIMBUF[2] = TIMBUF[2] & 0xbf;      // set 24 hour 
    TIMBUF[7] = TIMBUF[7] & 0xec;      // b7=out b4=sqwe b1,b0=rs 
}

// ds1307 rtc write 
bit rtwr (void) 
{                     
    unsigned char i;                   // return 0=ok 1=error 
    bit err;
    I2C_start();
    err = I2C_write(0xd0);             // address & r/w bit 
    if (!err) 
    {
        err = I2C_write(0x00);         // start register addr=0 
        if (!err) 	
        {
            for (i=0;i<=7;i++) 
            {
                err = I2C_write(TIMBUF[i]);
                if (err) 
                    break;
            }
        }
    }
    I2C_stop();
    return (err);
}

// ds1307 rtc read 
bit rtrd (void) 
{   
    unsigned char i;                        // return 0=ok 1=error 
    bit err;
    I2C_start();
    err = I2C_write(0xd0);                  // address & r/w bit 
    if (!err) 
	{
	    printf("in rtrd");
        err = I2C_write(0x00);              // start register addr=0 
        if (!err) 
        {
            printf("in rtrd");
            I2C_stop();
            I2C_delay();
            I2C_start();

            err = I2C_write(0xd1);          // address & r/w bit 
            if (!err) 	
            {
                printf("in rtrd");
                for (i=0;i<=6;i++) 
                {
                    TIMBUF[i] = I2C_read();
                } 
                TIMBUF[7] = I2C_readn();    // last byte 
            }
        }
    }
    I2C_stop();
    return (err);
}

void main (void) 
{         
    unsigned char x;  
    unsigned int i,ip; 
    bit err;
    ser_init();
    printf("varapokuthu");

    x = 0xff;
    err = rtrd ();        // display hh.mm.ss

    if (TIMBUF[0]!=x)    // check second change 
    {
        printf("%c",TIMBUF[0]);
        x = TIMBUF[0];
    }

    TIMBUF[0] = TIMBUF[0] & 0x7F;	// enable oscillator (bit 7=0)
    TIMBUF[1] = 0x59;	// minute = 59
    TIMBUF[2] = 0x05;	// hour = 05 ,24-hour mode(bit 6=0)
    TIMBUF[3] = 0x01;	// Day = 1 or sunday
    TIMBUF[4] = 0x30;	// Date = 30
    TIMBUF[5] = 0x08;	// month = August
    TIMBUF[6] = 0x05;	// year = 05 or 2005

    rtset ();
    rtwr ();

    ip=0;         
    while(ip<4)
    {
        ip++;
        rtrd();        
        putchar(0x0C);      // clear Hyper terminal
        printf("Day  : %c\r\n",TIMBUF[3]);
        printf("Time : %c:%c:%c\r\n",TIMBUF[2],TIMBUF[1],TIMBUF[0]);
        printf("Data : %c-%c-%c",TIMBUF[4],TIMBUF[5],TIMBUF[6]);
        for(i=0;i<10;i++)
            delay_50ms();    // delay about 1 second
    }
    while(1);
}


