/*****************************************************
This program was produced by the
CodeWizardAVR V2.03.4 Standard
Automatic Program Generator
?Copyright 1998-2008 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : AVR���ߺ���� ������ Ȯ�庸�� ���� �ϱ� 
Date    : 2011-09-01
Author  : �̰泲
Company : LK EMBEDDED
Comments: 

��� AVR���ߺ��带 �̿��Ͽ� ������ Ȯ�庸�� ���� 10P �÷� ���̺��� �Ʒ��� ���� �������ּ���!

AVR ���ߺ���: PORTA 10PIN �ڽ�Ŀ���� <-------------> ������ Ȯ�庸��: PORT 10PIN �ڽ�Ŀ����PORT

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

DDRA=0xFF; // PORTA�� �����Ʈ�� ���� 
PORTA=0xFF; // ��� ��Ʈ �ʱ�ȭ

while (1)
      {
        PORTA=0XFE; //   ������1 ON 
        delay_ms(500);  // 500ms delay
        PORTA=0XFD; //   ������2 ON 
        delay_ms(500);  // 500ms delay
        PORTA=0XFB; //   ������3 ON 
        delay_ms(500);   // 500ms delay
        PORTA=0XF7; //   ������4 ON 
        delay_ms(500);  // 500ms delay    
      }
}
