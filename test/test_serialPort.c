
#include<main.h>
#include<stdio.h>

sbit select=P3^6;

unsigned char txover,rxover;


void ser_init(unsigned int baudrate)
{
 	SCON  = 0x50;		        /* SCON: mode 1, 8-bit UART, enable rcvr      */
    TMOD |= 0x20;               /* TMOD: timer 1, mode 2, 8-bit reload        */
    TH1   = 253;                /* TH1:  reload value for 1200 baud @ 16MHz   */
    TR1   = 1;                  /* TR1:  timer 1 run                          */
    TI    = 1;
}

void main()
{
	unsigned char c;
	char s[14];

	ser_init(9600);
	printf("HI");

	while(1)
	{
		scanf("%s",s);
		printf("%s",*s);
	}

}
