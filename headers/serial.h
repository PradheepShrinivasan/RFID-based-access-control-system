#ifndef __SERIAL_H__
#define __SERIAL_H__

void ser_init(unsigned int baudrate)
{
	SCON = 0x50;          
	PCON &= 0x7F;         
	TMOD &= 0xCF;        
	TMOD |= 0x20;         /* Set M1 for 8-bit autoreload timer */
	TH1 =(unsigned char) (256 - (OSC_FREQ/ (2*16L * 12L * baudrate)));
	TR1 = 1;              /* Start timer 1 */
	TI = 1;               /* Set TI to indicate ready to xmit */
}      


#endif