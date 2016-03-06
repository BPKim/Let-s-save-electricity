/*
Project : RS232 송신 테스트 
Version : ATmega128-C V01
Date    : 2011-07-28
Author  : Kyung Nam Lee
Company : LKEMBEDDED 
*/
#include <mega128.h>
// Standard Input/Output functions
#include <stdio.h>

void main(void)
{

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
while (1)
      {
        printf("LK-ATmega128-C RS232 Com Test\r\n");

      }
}
