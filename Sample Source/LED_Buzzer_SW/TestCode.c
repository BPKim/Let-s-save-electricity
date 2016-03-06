/*
Project : LED, 스위치, 부저 입출력 테스트 
Version : ATmega128-C V01
Date    : 2011-07-28
Author  : Kyung Nam Lee
Company : LKEMBEDDED 
*/
#include <mega128.h>
void main(void)
{
PORTG=0x00;
DDRG=0x13; //입출력 초기화 
while (1)
      {
        if((PING&0X04)==0)
         PORTG=0X01;    
        else if((PING&0X08)==0)
         PORTG=0X02;
        else PORTG=0XF3;   

      }
}
