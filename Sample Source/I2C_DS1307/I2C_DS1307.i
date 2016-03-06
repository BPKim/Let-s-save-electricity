
#pragma used+
sfrb PINF=0;
sfrb PINE=1;
sfrb DDRE=2;
sfrb PORTE=3;
sfrb ADCL=4;
sfrb ADCH=5;
sfrw ADCW=4;      
sfrb ADCSRA=6;
sfrb ADMUX=7;
sfrb ACSR=8;
sfrb UBRR0L=9;
sfrb UCSR0B=0xa;
sfrb UCSR0A=0xb;
sfrb UDR0=0xc;
sfrb SPCR=0xd;
sfrb SPSR=0xe;
sfrb SPDR=0xf;
sfrb PIND=0x10;
sfrb DDRD=0x11;
sfrb PORTD=0x12;
sfrb PINC=0x13;
sfrb DDRC=0x14;
sfrb PORTC=0x15;
sfrb PINB=0x16;
sfrb DDRB=0x17;
sfrb PORTB=0x18;
sfrb PINA=0x19;
sfrb DDRA=0x1a;
sfrb PORTA=0x1b;
sfrb EECR=0x1c;
sfrb EEDR=0x1d;
sfrb EEARL=0x1e;
sfrb EEARH=0x1f;
sfrw EEAR=0x1e;   
sfrb SFIOR=0x20;
sfrb WDTCR=0x21;
sfrb OCDR=0x22;
sfrb OCR2=0x23;
sfrb TCNT2=0x24;
sfrb TCCR2=0x25;
sfrb ICR1L=0x26;
sfrb ICR1H=0x27;
sfrw ICR1=0x26;   
sfrb OCR1BL=0x28;
sfrb OCR1BH=0x29;
sfrw OCR1B=0x28;  
sfrb OCR1AL=0x2a;
sfrb OCR1AH=0x2b;
sfrw OCR1A=0x2a;  
sfrb TCNT1L=0x2c;
sfrb TCNT1H=0x2d;
sfrw TCNT1=0x2c;  
sfrb TCCR1B=0x2e;
sfrb TCCR1A=0x2f;
sfrb ASSR=0x30;
sfrb OCR0=0x31;
sfrb TCNT0=0x32;
sfrb TCCR0=0x33;
sfrb MCUCSR=0x34;
sfrb MCUCR=0x35;
sfrb TIFR=0x36;
sfrb TIMSK=0x37;
sfrb EIFR=0x38;
sfrb EIMSK=0x39;
sfrb EICRB=0x3a;
sfrb RAMPZ=0x3b;
sfrb XDIV=0x3c;
sfrb SPL=0x3d;
sfrb SPH=0x3e;
sfrb SREG=0x3f;
#pragma used-

#asm
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x20
	.EQU __sm_mask=0x1C
	.EQU __sm_powerdown=0x10
	.EQU __sm_powersave=0x18
	.EQU __sm_standby=0x14
	.EQU __sm_ext_standby=0x1C
	.EQU __sm_adc_noise_red=0x08
	.SET power_ctrl_reg=mcucr
	#endif
#endasm

char data[4]={0};

typedef char *va_list;

#pragma used+

char getchar(void);
void putchar(char c);
void puts(char *str);
void putsf(char flash *str);

char *gets(char *str,unsigned int len);

void printf(char flash *fmtstr,...);
void sprintf(char *str, char flash *fmtstr,...);
void snprintf(char *str, unsigned int size, char flash *fmtstr,...);
void vprintf (char flash * fmtstr, va_list argptr);
void vsprintf (char *str, char flash * fmtstr, va_list argptr);
void vsnprintf (char *str, unsigned int size, char flash * fmtstr, va_list argptr);
signed char scanf(char flash *fmtstr,...);
signed char sscanf(char *str, char flash *fmtstr,...);

#pragma used-

#pragma library stdio.lib

#pragma used+

void delay_us(unsigned int n);
void delay_ms(unsigned int n);

#pragma used-

void EEPROM_write(char WordAdress,char data)
{
(*(unsigned char *) 0x74) = (1<<7)|(1<<5)|(1<<2);

while (!((*(unsigned char *) 0x74) & (1<<7)));    

(*(unsigned char *) 0x73) = 0xd0;

(*(unsigned char *) 0x74) = (1<<7) |(1<<2);
while (!((*(unsigned char *) 0x74) & (1<<7)));

(*(unsigned char *) 0x73) = WordAdress;
(*(unsigned char *) 0x74) = (1<<7) |(1<<2);

while (!((*(unsigned char *) 0x74) & (1<<7)));

(*(unsigned char *) 0x73) = data;
(*(unsigned char *) 0x74) = (1<<7) |(1<<2); 

while (!((*(unsigned char *) 0x74) & (1<<7)));

(*(unsigned char *) 0x74) = (1<<7)|(1<<2)|(1<<4);

}
char EEPROM_read(char high)
{
char data=0;
(*(unsigned char *) 0x74) = (1<<7)|(1<<5)|(1<<2);

while (!((*(unsigned char *) 0x74) & (1<<7)));

(*(unsigned char *) 0x73) = 0xd0;
(*(unsigned char *) 0x74) = (1<<7) |(1<<2);

while (!((*(unsigned char *) 0x74) & (1<<7)));

(*(unsigned char *) 0x73) = high;
(*(unsigned char *) 0x74) = (1<<7) |(1<<2);

while (!((*(unsigned char *) 0x74) & (1<<7)));

(*(unsigned char *) 0x74) = (1<<7)|(1<<5)|(1<<2);

while (!((*(unsigned char *) 0x74) & (1<<7)));

(*(unsigned char *) 0x73) = 0xd1;
(*(unsigned char *) 0x74) = (1<<7) |(1<<2);

while (!((*(unsigned char *) 0x74) & (1<<7)));

(*(unsigned char *) 0x74) = (1<<7) |(1<<2);
while (!((*(unsigned char *) 0x74) & (1<<7)));

data=(*(unsigned char *) 0x73);
(*(unsigned char *) 0x74) = (1<<7)|(1<<2)|(1<<4);

return data;     
}

void main(void)
{

DDRD=0XFF;

UCSR0A=0x00;
UCSR0B=0x08;
(*(unsigned char *) 0x95)=0x06;
(*(unsigned char *) 0x90)=0x00;
UBRR0L=0x67;

(*(unsigned char *) 0x70) = (16000000 -(16*100000 ))/(4*2*100000 ) ;
(*(unsigned char *) 0x71)=0;
(*(unsigned char *) 0x74)=0X04;
EEPROM_write(00,0); 
EEPROM_write(01,0x03);  
EEPROM_write(02,6);   
EEPROM_write(07,0x03);    

while (1)
{ 
static unsigned char data,data1,data2=0;
static unsigned char h,m,s=0;

data=EEPROM_read(0);
data1=(data&0x0f);  
data2=(data&0x70);  
data2=(data2>>4)*10;

s=(data2+data1);

data=EEPROM_read(1);
data1=(data&0x0f);  
data2=(data&0x70);  
data2=(data2>>4)*10;
m=(data2+data1);   

data=EEPROM_read(2);
data1=(data&0x0f);  
data2=(data&0x30);  
data2=(data2>>4)*10;
h=(data2+data1);

printf("hour: %d minute: %d second: %d\r\n",h,m,s);  

}
}
