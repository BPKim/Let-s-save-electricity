#include<avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define	STX 0X02
#define	ETX 0X03
#define BAUD_115200 8

typedef unsigned char uint8_t;

#define MAX_BUFF_SIZE 28
unsigned char _buf[MAX_BUFF_SIZE];
unsigned int Buffer = 0XFF;

int buf_len = 0;
uint8_t com_size = 0; 
uint8_t sint_flag = 0;

#define f(x) (1<<x)


void delay_us(unsigned char time_us) 
{ register unsigned char i;
 
  for(i = 0; i < time_us; i++)
    { asm volatile(" PUSH  R0 ");
      asm volatile(" POP   R0 ");
      asm volatile(" PUSH  R0 ");
      asm volatile(" POP   R0 ");                           
    }
}
 
void delay_ms(unsigned int time_ms) 
{ register unsigned int i;
 
  for(i = 0; i < time_ms; i++)
    { delay_us(250);
      delay_us(250);
      delay_us(250);     
   	  delay_us(250);  
    }
}
void tx0_char(unsigned char txChar)
{
	while(!(UCSR0A & (1<<UDRE)));
 	UDR0 = txChar;
}

void tx0_str(unsigned char *txStr, int len)
{
	int i;
	for(i = 0;i< len; i++)
	{
		tx0_char(txStr[i]);
 	}
}

void tx1_char(unsigned char txChar)
{
	while(!(UCSR0A & (1<<UDRE)));
 	UDR1 = txChar;
}

void tx1_str(unsigned char *txStr, int len)
{
	int i;
	for(i = 0;i< len; i++)
	{
		tx1_char(txStr[i]);
 	}
}

unsigned char RX0_char(void)
{
  while((UCSR0A & 0x80)== 0x00); //data received??
  return UDR0;
}

int main()
{
	unsigned int State;
 	cli();  
	
 	UBRR0H = (unsigned char) (BAUD_115200 >>8) ;
 	UBRR0L = (unsigned char) BAUD_115200;
 	UCSR0A = 0X00;
 	UCSR0B = (1<< TXEN0)| (1<< RXEN0)|(1<< RXCIE0); 
 	UCSR0C = (1<< UCSZ01) | (1<< UCSZ00) | (0<<USBS0); // 마지막꺼만 나중에주의


	UBRR1H = (unsigned char) (BAUD_115200 >>8) ;
 	UBRR1L = (unsigned char) BAUD_115200;
 	UCSR1A = 0X00;
 	UCSR1B = (1<< TXEN0)| (1<< RXEN0)|(1<< RXCIE0); 
 	UCSR1C = (1<< UCSZ01) | (1<< UCSZ00) | (0<<USBS0); // 마지막꺼만 나중에주의
 	sei();

 	DDRA=0xFF; // PORTA를 출력포트로 설정 
 	PORTA=0xFF; // 출력 포트 초기화
	
	//Printf("Heo_wooyun test");
	
	
 	while(1)
	{ 
		delay_ms(1000);
		State=((~PORTA) & 0x07);
		tx1_char(State+'0');
	}
}


SIGNAL(SIG_USART1_RECV)
{
	unsigned char _usart_rcv = 0;
			
	_usart_rcv = UDR1;
	
	//tx1_char(_usart_rcv);
	
	if(_usart_rcv == '2')
	{
		Buffer &= 0xFE;
	}
	
	if(_usart_rcv == '1')
	{
		Buffer |= 0x01;
	}

	
	if(_usart_rcv == '4')
	{
		Buffer &= 0xFD;
	}

	if(_usart_rcv == '3')
	{
		Buffer |= 0x02;
	}



	if(_usart_rcv == '6')
	{
		Buffer &= 0xFB;
	}

	if(_usart_rcv == '5')
	{
		Buffer |= 0x04;
	}

	PORTA = Buffer;
	//sei();
}
