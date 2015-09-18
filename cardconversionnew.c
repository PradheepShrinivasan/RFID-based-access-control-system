/* Main Code*/

/*User defined and inbuilt header files*/
#include"stdio.h"
#include"string.h"
#include"stdlib.h"
#include"main.h"
#include"port.h"
#include"timeout.h"
#include"timeout.c"
#include "reg52.h"  		
#include "24xx512.h"
#include "ds1307.h"
#include"convdatetime.c"
#include"lcdrivernew.c"

/* Function prototype declaration*/

void ser_init(unsigned int);	
void truncate(unsigned char*,unsigned char*);
void readlong(unsigned int);
void writelong(unsigned int);
unsigned char getdata(void);
void tagwrite(void);
void stackupd(void);
void datecmp(void);
void updateprom(void);
void patterncheck(void);
void timeupdate(void);
void database(void);
void datasetup(unsigned int);
void readbase(void);
char tagsearch(void);
void buzzeron(void);

/* union,to convert long var to char and integer and vice-versa,used in storage of card no. in EEPROM*/
union longchar 
{
	unsigned long longe;
	unsigned int inte[2];
	unsigned char ch[4];
}valuel;

/* to convert int to char*/
union intchars 
{
	unsigned int inte;
	unsigned char ch[2];
}values;

/* to convert int to char*/
union intcharc 
{
	unsigned int inte;
	unsigned char ch[2];
}valuec;

/*Global Variables*/
unsigned int addr,addrw,addrs,addrsw;
unsigned int addrsp;
unsigned char idata c[12],temp[10],val,prev[12];

void main(void)
{
	unsigned char idata value,tag,pag;
	ser_init(9600); /* initialize serial comn. with 9600 baud*/
	//printf("hello");
	initlcd();/* lcd initialization*/
	DS1307_settime(0x09,0x20,0x00);		/* Set Time (hh:mm:ss) */
	DS1307_setdate(0x23,0x06,0x07);  	/* Set Date (dd/mm/yy) */
	addr=2005;addrw=2005,addrs=1005;
	database(); /* to create a database of the tags in the EEPROM*/
	select=1;
	//printf("addrssw=%d\n",addrsw);
	valuel.longe=0x00000000;
	printf("RFID");
	while(1)
	{ 
		// to display the welcome message on the lcd  
		general(); 
		// to get the serial data, either tag value or commands  
		value=getdata();
		// to switch on the buzzer for 500ms 
		buzzeron();
		cleardisp();
		delay_500micros();
		
		setcursor(1,3);
		if (value==0)
		{
			tag=tagsearch(); /* to search the tag(as val=0),within the database  */
			if(tag=='0')
				continue;

			delay_5ms();
			buzzeron();
			
			pag=enterpassword(addrsp); /* to check if the entered password matches with that of the corresponding tag in the database(160)!  */
			if(pag=='0')
				continue;
			
			cleardisp();
			delay_500micros();
			setcursor(1,3);

			write("Entering Tag");
			ES=0;
			tagwrite();
			setcursor(1,2);
			ES=1;
			
			valuel.longe=0x00000000;
		}
		else if (value==1)
		{
			if (strcmp(c,"rea")==0) /* read!, the command for displaying the tags entered hitherto*/
			{
				printf("Stored Tags\n");
				updateprom();
			}
			else if(strcmp(c,"read")==0) /* readd!,the command for displaying the tags in the database */
			{
				printf("Database\n");
				readbase();
			}
			else if(strcmp(c,"end")==0) /* to return the mux. control to RFID chip  */
			{
				select=1;
			}
		} 
	}
	while(1);
}

/* to switch on the buzzer momentarily on tag read*/
void buzzeron(void) 
{
	unsigned char i;
	buzzer=0;
	
	for(i=0;i<10;i++)
		delay_50ms();

	buzzer=1;
}

/* to read a data(series of 4 bytes) from the address addr in the EEPROM */
void readlong(unsigned int addr)
{
    valuel.longe=0x00000000;

    valuel.ch[0]=EEPROM_get(addr);//  Getting the higer order
	delay_500micros();
    
    valuel.ch[1]=EEPROM_get(addr+1); // lower 
    delay_500micros();
    
    valuel.ch[2]=EEPROM_get(addr+2); // lower 
    delay_500micros();
    
    valuel.ch[3]=EEPROM_get(addr+3); // lower 
	delay_500micros();
}

/* to write a data(series of 4 bytes) to the address addr in the EEPROM */
void writelong(unsigned int addr)
{
    
    EEPROM_set(addr,valuel.ch[0]);// Storing the higer order
	delay_500micros();

    
    EEPROM_set(addr+1,valuel.ch[1]); // lower 
    delay_500micros();
    
    
    EEPROM_set(addr+2,valuel.ch[2]); // lower 
    delay_500micros();
    
    
    EEPROM_set(addr+3,valuel.ch[3]); // lower 
	delay_500micros();    
}

/* to truncate the value received from the RFID chip,to about 8 characters  */
void truncate(unsigned char *c,unsigned char *temp)
{

	unsigned char *te;
	unsigned char i;
	te=temp;

	for(i=0,c=c+2; i<8 ; i++, temp++, c++)
	{
		*temp = *c;
	}
	temp[i+1]='\0';

}

/* to get serial data  */
unsigned char getdata()
{
	unsigned char i;
	strcpy(c,NULL);
	for(i=0;i<12;i++)
	{
		c[i]=_getkey();
		printf("%c",c[i]);
		if (c[i]=='!')
		{ 
			val=1;
			printf("\n");
			break;
		}
		val=0;
	}

	c[i-1]='\0';
	truncate(c,temp);

	//printf("c=%s",temp);
	valuel.longe=strtoul(temp,NULL,16);
	//printf("val conv%ld",valuel.longe);
	return val;
}

/* to enter details abt. the tag into EEPROM(tag value,date,time)  */
void tagwrite(void)
{
    
    writelong(addr);
    addr+=4;
	
    date2prom(addr);
	addr+=2;

	time2prom(addr);
	addr+=2;
    addrw=addr;
    //printf("\nafter longe=%ld",valuel.longe);
}

/* to display the tags entered so far */
void updateprom(void)
{
	unsigned char i;
	for(i=0, addr=2005; addr<addrw; i++)
	{
		delay_500micros();
		readlong(addr);

		addr+=4;
		printf("tag=%ld\n",valuel.longe);

		patterncheck();

		timeupdate();
	}
}

/* check the memory pattern(not yet implemented) */
void patterncheck(void)
{
	delay_500micros();
	valuec.ch[0]=EEPROM_get(addr);   // addr+2

	delay_500micros();
	valuec.ch[1]=EEPROM_get(addr+1);  // addr+3

	delay_500micros();
	printf("date=%05d\n",valuec.inte);

	addr+=2;                         // addr+=4
}

/* used to check if same day or next day(not yet implemented) */
void timeupdate(void)
{
	delay_500micros();
	valuec.ch[0]=EEPROM_get(addr);

	delay_500micros();
	valuec.ch[1]=EEPROM_get(addr+1);

	delay_500micros();
	printf("time=%05d\n",valuec.inte);

	addr+=2;
}

/* initialize serial comn.  */
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

/* creates a database of valid tags*/
void database(void)
{
	delay_500micros();
	valuel.longe=4003170;

	datasetup(addrs);
	addrs+=6;
	valuel.longe=4003481;

	datasetup(addrs);
	addrs+=6;
	valuel.longe=4003483;

	datasetup(addrs);
	addrs+=6;
	valuel.longe=4002742;

	datasetup(addrs);
	addrs+=6;
	valuel.longe=4002766;

	datasetup(addrs);
	addrs+=6;

	addrsw=addrs;
} 

/* helps to create database in the function above  */

void datasetup(unsigned int addrs)
{
	delay_500micros();
	EEPROM_set(addrs,valuel.ch[0]);

	delay_500micros();
	EEPROM_set(addrs+1,valuel.ch[1]);

	delay_500micros();
	EEPROM_set(addrs+2,valuel.ch[2]);

	delay_500micros();
	EEPROM_set(addrs+3,valuel.ch[3]);

	delay_500micros();
	valuel.longe=0x00000000;
}

/* display database of tags */

void readbase(void)
{
	unsigned int i;
	for(i=0,addrs=1005;addrs<addrsw;i++)
	{
		delay_500micros();
		readlong(addrs);
		addrs+=6;
		printf("tag=%ld\n",valuel.longe);
	}
}

/* to search if the received tag value is within the database */ 

char tagsearch(void)
{
	//valuel.longe has the long value of the Tag currently read
	unsigned int i,addrs,addrsp;
	char tag;
	delay_500micros();
	for(addrs=1005;addrs<addrsw;addrs+=6)
	{
		if (valuel.ch[0]==EEPROM_get(addrs))
		{
			delay_500micros();
			if (valuel.ch[1]==EEPROM_get(addrs+1))
			{
				delay_500micros();
				if (valuel.ch[2]==EEPROM_get(addrs+2))
				{
					delay_500micros();
					if (valuel.ch[3]==EEPROM_get(addrs+3))
					{ 
						cleardisp();
						delay_500micros();
						setcursor(1,3);

						//printf("User Found");
						write("User Found");
						addrsp=addrs+4;
						tag='1';
						break;
					}
				}
			}
		}
	}
	if(addrs>=addrsw)
	{
		cleardisp();
		delay_500micros();
		setcursor(1,3);

		tag='0';
		write("User Not found");

		for(i=0;i<20;i++)
			delay_50ms();
	}
	return tag;
}

/* Tag ID's

4003170
4003481
4003483
4002742
4002766
denied-4002784

*/

