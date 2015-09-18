#include <reg52.h>
#include <string.h>
#include "kybrd.c"

void sendcmd(unsigned char);
void cleardisp(void);
void setcursor(unsigned char,unsigned char);
void writechar(const char character);
void general(void);
unsigned char lcdpass(void);
void delay(unsigned char);
void writedata(unsigned int ) ;
unsigned int paswck(unsigned int,unsigned int);
unsigned int data1;
char enterpassword(unsigned int);
unsigned char bytrev(unsigned char data1);

unsigned char bytrev(unsigned char data1)
{
    unsigned char ret=0,i;
    for(i=0;i<8;i++)
    {
        ret|=(data1>>i)&0x01;
        if(i!=7)
            ret=ret<<1;
    }    
    return ret;
}

union intcharp 
{
    unsigned int inte;
    unsigned char ch[2];
}valuep;


void delaylcd(void)//for 39us internal
{
    unsigned char i;
	for(i=0;i<30;i++);
}

void initlcd(void)
{
	RW=0;//RW line is always zero, always write

	//2lines, 5x8 dots
	sendcmd(0x3c);	 
	
	//display on, cursor off, blink off
	sendcmd(0x0c);
	
	cleardisp();

	//entry mode=increment, shift off;
	sendcmd(0x06);
	delay(2);

	setcursor(1,1);
	delay(10);

}


void cleardisp(void)
{
	sendcmd(0x01);
	delay(2);//2ms delay
}

void sendcmd(unsigned char cmd)//internal
{
	EN=1;
	RS=0;
	dataport=bytrev(cmd);
	EN=0;
    delaylcd();
	EN=1;
}

void write(const char *string)
{
   	unsigned char i,len=strlen(string);
	for(i=0;i<len;i++)
	   writechar(*(string+i));
}

void writechar(const char character)
{
	EN=1;
	RS=1;

	dataport=bytrev(character);

	EN=0;
    delaylcd();

	EN=1;
}

void setcursor(unsigned char line, unsigned char position)
{
    position--;
	if(line==1)
	{
		//temp= 128 & position;
		sendcmd(128 | position);
	}
	else if(line==2)
	{
		sendcmd(128 | (position+0x40));
	}
    else if(line==3)
	{
		sendcmd(128 | (position+0x14));
	}
	else if(line==4)
	{
		sendcmd(128 | (position+0x54));
	}
	else{}

}

void cursor_on(void)
{
	sendcmd(0x0F);
}

void cursor_off(void)
{
	sendcmd(0x0C);
}

void delay(unsigned char delay)
{
    unsigned char i,j;
    for (i=1;i<delay;i++)
        for(j=0;j<255;j++);
}
char enterpassword(unsigned int addrsp)
{
  unsigned char idata  i=0,a,arr[5];
   bit  flag=0,psokf=0,exitf=0;
  initlcd();
  general();
  delay(255);
  arr[i]=lcdpass();
  writedata(i);
  i++;
  while(1)
 {
  a=READ_SWITCHES();
  if(a=='b')        //ok is pressed
  {
  arr[i]='\0';
    if(i>4)
    {
    cleardisp();
	delay_500micros();
    setcursor(1,3);
    write("Access Denied");
	for(i=0;i<4;i++)
	 delay_50ms();
     i=0;
   cleardisp();
   delay_500micros();
   setcursor(1,1);
   write("To Exit Press");
   setcursor(2,5);
   write("Cancel");
   flag=1;
   continue;
	}
  data1=atoi(arr);
  if(paswck(data1,addrsp)==1)
  {
  cleardisp();
  delay_500micros();
  setcursor(1,4);
  write("ACCESS GRANTED");
  for(i=0;i<30;i++)
   delay_50ms();
  general();
  i=0;
  return '1';
  }
  else
  {
  cleardisp();
  delay_500micros();
   setcursor(1,3);
   write("Access Denied");
   for(i=0;i<4;i++)
   delay_50ms();
   i=0;
   cleardisp();
   delay_500micros();
   setcursor(1,1);
   write("To Exit Press");
   setcursor(2,5);
   write("Cancel");
   flag=1;
   continue;
   }
}
  else if(a=='z')  //cancel is pressed
  {
   if(flag==1&&i==0)
   { 
   cleardisp();
  delay_500micros();
  setcursor(1,1);
   write("Exited");
   delay_50ms();
   exitf=1;
   return '0';
   }
   i=0;
   flag=0;
   arr[i]=lcdpass();
   i++;
   writedata(i);
  }
  else if(a!='a')  //some other key is pressed
  {
  flag=0;
  arr[i]=a;
  writedata(i);
  i++;
   }
 }
//while(1); */
}
void general(void)
{
  cleardisp();
  delay_500micros();
  setcursor(1,7);
  write("RFID BASED");
  setcursor(2,3);
  write("ACCESS CONTROL");
}

unsigned char lcdpass(void)
{
unsigned char a;
  cleardisp();
  delay_500micros();
  setcursor(1,1);
write(" Enter Password");
setcursor(2,2);
write("OK");
setcursor(2,10);
write("CANCEL");
do
a=READ_SWITCHES();
while(a=='a');
return a;
}

void writedata(unsigned int i) 
{
 unsigned  char k;
  cleardisp();
  delay_500micros();
  setcursor(1,1);
  for(k=0;k<i+1;k++)
  writechar('*');
  delay_500micros();
  setcursor(2,2);
  write("OK");
  setcursor(2,10);
  write("CANCEL");
  setcursor(1,2);
}
unsigned int paswck(unsigned int data1,unsigned int addrsp)
{
    delay_500micros();
    if(data1 == 222) {
        return 1;
    }
    else if(data1 == 444)
    {
        select=0;
        return 1;
    }

    return 0;
}
