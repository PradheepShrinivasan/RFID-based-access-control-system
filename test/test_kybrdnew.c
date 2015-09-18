/*
	Test code for the matrix keyboard
*/

#include<stdio.h>
#include<stdlib.h>
#include<main.h>
#include<timeout.h>
#include"timeout.c"

sbit R1 = P1^0;   
sbit R2 = P1^1;   
sbit R3 = P1^2;

sbit C2 = P1^3;
sbit C1 = P1^4;
sbit C3 = P1^5;
sbit C4 = P1^6;

void ser_init(unsigned int);
unsigned char READ_SWITCHES (void);

//=========================================================================================================
unsigned char READ_SWITCHES (void)				// initialize the port for inputs
{
	P1=0xFF;			
	// P2.0 to p2.3 are outpot; and P2.4 to P2.7 are inputs
	// the keybad is connected to port 2		

	R3=1;
	R2=1;	
	R1=0;			

	// key 1 is presed
	if (C1 == 0) 		
	{
		//debounce
		delay_50ms();			
	    delay_50ms();	
		
		//wait until release the key
		while (C1 == 0);		
		return 'b';			
	}

	//key 2 is pressed
	if (C2 == 0) 		
	{
		//debounce
		delay_50ms();				
	    delay_50ms();	

	    //wait until release the key
		while (C2==0);		

		return '9';
	}
	//key 3 is pressed
	if (C3 == 0) 		
	{
		delay_50ms();				
	    delay_50ms();	
	    
	 	while (C3==0);

		return '0';
	}

	//key 4 is pressed
	if (C4 == 0)		
	{
		delay_50ms();				
		delay_50ms();	
		while (C4==0);

		return 'z';
	}

	R3=1;
	R1=1;
	R2=0;				

	if (C1 == 0)		
	{
		delay_50ms();				
		delay_50ms();	
		
		while (C1==0);		

		return '5';
	}
	if (C2 == 0) 
	{
		delay_50ms();
		delay_50ms();	
		
		while (C2 == 0);		

		return '6';
	}	
	if (C3 == 0)
	{
		delay_50ms();
		delay_50ms();	
		
		while (C3 == 0);		

		return '7';
	}
	if (C4 == 0) 
	{
		delay_50ms();
		delay_50ms();	
		
		while (C4==0);		

		return '8';
	}

	//test row 3
	R1=1;
	R2=1;
	R3=0;				

	if (C1 == 0)
	{
		delay_50ms();
		delay_50ms();	
		
		while (C1==0);		

		return '1';
	}
	if (C2 == 0)
	{
		delay_50ms();
		delay_50ms();	

		while (C2==0);		
		return '2';
	}
	if (C3 == 0)
	{
		delay_50ms();
		delay_50ms();	

		while (C3==0);		
		return '3';
	}
	if (C4 == 0)
	{
		delay_50ms();
		delay_50ms();	
		
		while (C4==0);		

		return '4';
	}
	return 'a';					// Means no key has been pressed
}


void main()
{
	char a, i=0, arr[10];
	int data1;

	ser_init(9600);
	printf("crossed ser_init");

	while(1)
	{
		a = READ_SWITCHES();
		if(a != 'a')
		{
			printf("%c",a);
		}
	}
}

void ser_init(unsigned int baudrate)
{
	baudrate=1;
	SCON = 0x50;          
	PCON &= 0x7F;         
	TMOD &= 0xCF;        
	TMOD |= 0x20;         /* Set M1 for 8-bit autoreload timer */
	TH1 =253;              //(unsigned char) (256 - (OSC_FREQ/ (2*16L * 12L * baudrate)));
	TR1 = 1;              /* Start timer 1 */
	TI = 1;               /* Set TI to indicate ready to xmit */
}   
