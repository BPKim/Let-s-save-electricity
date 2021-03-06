/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Professional
Automatic Program Generator
?Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 2011-07-29
Author  : NeVaDa
Company : 
Comments: 


Chip type               : ATmega128
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 1024
*****************************************************/

#include <mega128.h>

#define MAINCLK     16000000 //메인 크리스탈 클럭   
#define TWI_CLK      100000 //100khz   
  
#define TWBR_SET    (MAINCLK-(16*TWI_CLK))/(4*2*TWI_CLK) //자동으로 TWBR을 구하기 위한공식   

char data[4]={0};

// Standard Input/Output functions
#include <stdio.h>
#include <delay.h>
#define TWIE    0
#define TWEN    2
#define TWWC    3
#define TWSTO   4
#define TWSTA   5
#define TWEA    6
#define TWINT   7


void EEPROM_write(char WordAdress,char data)
{
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    /*
    Send START condition
    */
    while (!(TWCR & (1<<TWINT)));    
    /* Wait for TWINT flag set. This indicates that the
    START condition has been transmitted 
    */           
    TWDR = 0xd0;
    /*Load 0xa0 into TWDR Register.Clear TWINT bit in 
    TWCR to start transmission of address
    */ 
    TWCR = (1<<TWINT) |(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    /* Wait for TWINT flag set. This indicates that the
    0xa0 has been transmitted, and
    ACK/NACK has been received.
    */
    TWDR = WordAdress;
    TWCR = (1<<TWINT) |(1<<TWEN);

    /*
    Load low into TWDR Register. Clear TWINT
    bit in TWCR to start transmission of data 
    */ 
    while (!(TWCR & (1<<TWINT)));
    /*
    Wait for TWINT flag set. This indicates that the
    low has been transmitted, and ACK/NACK
    has been received.
    */    
    TWDR = data;
    TWCR = (1<<TWINT) |(1<<TWEN); 
    /*
    Load low into TWDR Register. Clear TWINT
    bit in TWCR to start transmission of data 
    */      
    while (!(TWCR & (1<<TWINT)));
    /*
    Wait for TWINT flag set. This indicates that the
    low has been transmitted, and ACK/NACK
    has been received.
    */
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
    /*
    Transmit STOP condition
    */
}
char EEPROM_read(char high)
{
    char data=0;
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    /*
    Send START condition
    */
    while (!(TWCR & (1<<TWINT)));
    /*
    Wait for TWINT flag set. This indicates that the
    low has been transmitted, and ACK/NACK
    has been received.
    */
    TWDR = 0xd0;
    TWCR = (1<<TWINT) |(1<<TWEN);
    /*
    Load 0xa0 into TWDR Register. Clear TWINT
    bit in TWCR to start transmission of data 
    */    
    while (!(TWCR & (1<<TWINT)));
    /*
    Wait for TWINT flag set. This indicates that the
    low has been transmitted, and ACK/NACK
    has been received.
    */
    TWDR = high;
    TWCR = (1<<TWINT) |(1<<TWEN);
    /*
    Load high into TWDR Register. Clear TWINT
    bit in TWCR to start transmission of data 
    */    
    while (!(TWCR & (1<<TWINT)));
    /*
    Wait for TWINT flag set. This indicates that the
    low has been transmitted, and ACK/NACK
    has been received.
    */      
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    /*
    Send RESTART condition
    */
    while (!(TWCR & (1<<TWINT)));
    /*
    Wait for TWINT flag set. This indicates that the
    low has been transmitted, and ACK/NACK
    has been received.
    */    
    TWDR = 0xd1;
    TWCR = (1<<TWINT) |(1<<TWEN);
    /*
    Load 0xa0|1 into TWDR Register. Clear TWINT
    bit in TWCR to start transmission of data 
    */    
    while (!(TWCR & (1<<TWINT)));
    /*
    Wait for TWINT flag set. This indicates that the
    low has been transmitted, and ACK/NACK
    has been received.
    */    
    TWCR = (1<<TWINT) |(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    /*
    Wait for TWINT flag set. This indicates that the
    low has been transmitted, and ACK/NACK
    has been received.
    */
    data=TWDR;
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
    /*
    Load TWDR into data. Clear TWINT
    bit in TWCR to start transmission of data 
    */    
return data;     
}

void main(void)
{

DDRD=0XFF;

// USART0 initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART0 Receiver: Off
// USART0 Transmitter: On
// USART0 Mode: Asynchronous
// USART0 Baud Rate: 9600
UCSR0A=0x00;
UCSR0B=0x08;
UCSR0C=0x06;
UBRR0H=0x00;
UBRR0L=0x67;



// TWI initialization
// TWI disabled
//TWBR = TWBR_SET;// 105  100kHz   

TWBR = TWBR_SET;// 15  100kHz   
TWSR=0;
TWCR=0X04;
EEPROM_write(00,0); //second  
EEPROM_write(01,0x03);  //minutes
EEPROM_write(02,6);   //hour
EEPROM_write(07,0x03);    //control

while (1)
      { 
       static unsigned char data,data1,data2=0;
       static unsigned char h,m,s=0;
       
      // Place your code here   
     // printf("%d \t %d \t %d \t %d \r\n",data[0],data[1],data[2],data[3]);
       data=EEPROM_read(0);
       data1=(data&0x0f);  // 1의 자리 초 
       data2=(data&0x70);  // 10의 자리 초 
      data2=(data2>>4)*10;
       
       s=(data2+data1);
     
       data=EEPROM_read(1);
       data1=(data&0x0f);  // 1의 자리 초 
       data2=(data&0x70);  // 10의 자리 초 
       data2=(data2>>4)*10;
       m=(data2+data1);   
       
       data=EEPROM_read(2);
       data1=(data&0x0f);  // 1의 자리 초 
       data2=(data&0x30);  // 10의 자리 초 
       data2=(data2>>4)*10;
       h=(data2+data1);
       
      printf("hour: %d minute: %d second: %d\r\n",h,m,s);  
     //  printf("%d\r\n",data);  
      }
}
