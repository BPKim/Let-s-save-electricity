/*****************************************************
This program was produced by the
CodeWizardAVR V2.03.4 Standard
Automatic Program Generator
?Copyright 1998-2008 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : AVR개발보드로 릴레이 확장보드 제어 하기 
Date    : 2011-09-01
Author  : 이경남
Company : LK EMBEDDED
Comments: 

당사 AVR개발보드를 이용하여 릴레이 확장보드 사용시 10P 플랫 케이블을 아래와 같이 연결해주세요!

AVR 개발보드: PORTA 10PIN 박스커넥터 <-------------> 릴레이 확장보드: PORT 10PIN 박스커넥터PORT

Chip type           : ATmega128
Program type        : Application
Clock frequency     : 16.000000 MHz
Memory model        : Small
External RAM size   : 0
Data Stack size     : 1024
*****************************************************/

#include <mega128.h>
#include <delay.h>
void main(void)
{

DDRA=0xFF; // PORTA를 출력포트로 설정 
PORTA=0xFF; // 출력 포트 초기화

while (1)
      {
        PORTA=0XFE; //   릴레이1 ON 
        delay_ms(500);  // 500ms delay
        PORTA=0XFD; //   릴레이2 ON 
        delay_ms(500);  // 500ms delay
        PORTA=0XFB; //   릴레이3 ON 
        delay_ms(500);   // 500ms delay
        PORTA=0XF7; //   릴레이4 ON 
        delay_ms(500);  // 500ms delay    
      }
}
