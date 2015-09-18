#ifndef __PORT_H__
#define __PORT_H__

//for  i2c subroutine
sbit SDA=P3^4;		/* Set P2.0 = SDA */
sbit SCL=P3^3; 		/* Set P2.1 = SCL */

//for lcd
#define dataport P2

sbit EN = P0^7;//0x97;
sbit RW = P0^6;//0x96;
sbit RS = P0^5;//0x95;

//for keyboard
sbit R1 = P1^0;   
sbit R2 = P1^1;   
sbit R3 = P1^2;
//sbit R4 = P2^3;
sbit C2 = P1^3;
sbit C1 = P1^4;
sbit C3 = P1^5;
sbit C4 = P1^6;

//for buzzer
sbit buzzer=P3^2;

//for mux
sbit select=P3^6;

#endif