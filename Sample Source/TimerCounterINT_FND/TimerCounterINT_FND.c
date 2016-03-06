/*
Project : 타이머 카운터 인터럽트 이용한 다이나믹 디스플레이 제어 (FND) 
Version : ATmega128-C V01
Date    : 2011-07-28
Author  : Kyung Nam Lee
Company : LKEMBEDDED 
*/

#include <mega128.h>
#include <delay.h>


#define fnd1 0
#define fnd2 1
#define fnd1_on (0<<fnd1)
#define fnd2_on (0<<fnd2)

#define fnd1_off (1<<fnd1)
#define fnd2_off (1<<fnd2)
char Number[11]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X27,0X7F,0X6F};  //0~9 배열선언  FND2
unsigned int cnt=0;
// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)  //1ms Tick Time
{
 static int i=0;
 i++;
 if(i==250)
 {
    cnt++;
    i=0;
    if(cnt==99)   
    {
        cnt=0;
        }
    }
 TCNT0+=0X06;
}

void FndDisplay(unsigned char data)
{
    int i,j=0;
    i=(data%100)/10;
    j=(data%10);

    PORTB=(fnd1_on|fnd2_off);
    PORTA=Number[i];         
    delay_ms(5);
    PORTB=(fnd1_off|fnd2_on);
    PORTA=Number[j];
    delay_ms(5);

}
void main(void)
{

DDRA=0XFF; //PORTA 출력으로 설정 
DDRB=0XFF; //PORTB 출력으로 설정 

TCCR0=0x04;//64Prescalel, Overflow Interrupt 
TCNT0=0x06;// Timer Count initialization

TIMSK=0x01;// Timer(s)/Counter(s) Interrupt(s) initialization
#asm("sei")// Global enable interrupts

while (1)
      {               
      FndDisplay(cnt); //타이머 카운터 인터럽트를 이용하여 250ms마다 FND 숫자값은 증가한다.
      }
}
