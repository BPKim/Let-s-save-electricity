/*
Project : LED, ����ġ, ���� ����� �׽�Ʈ 
Version : ATmega128-C V01
Date    : 2011-07-28
Author  : Kyung Nam Lee
Company : LKEMBEDDED 
*/
#include <mega128.h>
void main(void)
{
PORTG=0x00;
DDRG=0x13; //����� �ʱ�ȭ 
while (1)
      {
        if((PING&0X04)==0)
         PORTG=0X01;    
        else if((PING&0X08)==0)
         PORTG=0X02;
        else PORTG=0XF3;   

      }
}
