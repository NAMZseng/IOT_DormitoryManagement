#include<reg52.h>
#include<main.h>
#include<mfrc522.h>

unsigned char UID[5], Temp[4];

void feeb() { //Ѱ���ɹ���Ӧ����
	ff=0;
	delay_10ms(1);
	ff=1;
	delay_10ms(1);
}

void Auto_Reader(void){
	int tar;
  while(1){
    if(PcdRequest(0x52,Temp)==MI_OK){  //Ѱ�����ɹ���Temp����Ϊ������
      if(PcdAnticoll(UID)==MI_OK){	  //����ͻ��UID��������Ϊ�����к�
				CALL_isr_UART();			  //�������жϽ�UID����ǰ�ĸ��ֽ��ϴ������ڵ�������
				feeb();                 //���÷�������ʾ 
      }
    } 
		else ff = 0;//Ѱ��ʧ��
  } 
}

void InitializeSystem(){
	SCON=0X50;			//����Ϊ������ʽ1
	TMOD=0X21;			//���ü�����������ʽ2
	PCON=0X80;			//�����ʼӱ�
	TH1=0XF3;		    //��������ʼֵ���ã�ע�Ⲩ������4800��
	TL1=0XF3;
	REN = 1;
	ES=1;						//�򿪽����ж�
	EA=1;						//�����ж�
	TR1=1;		
	ff = 0;
	PcdReset();
	PcdAntennaOff(); 
	PcdAntennaOn();  
	M500PcdConfigISOType( 'A' );
}

void delay_ms(int ms)
{
	int i, j;
	for (i = ms; i > 0; i--)
		for (j = 110; j > 0; j--);
}

void show_led()
{
	int i;
	led = 0;
	for (i = 0; i < 3; i++) {
		delay_ms(200);
		led = ~led;
	}
}

void isr_UART(void) interrupt 4 using 1{
  unsigned char i;
	if(RI)
   {
		 show_led();
		 led = 1;
     RI = 0;	//�����жϱ�־�����Լ��������Ҫ�ֶ����
   }
	if(TI){
		TI=0;
		for(i=0;i<4;i++){
			SBUF=UID[i];
			while(!TI);
			TI=0;			
		}
		REN=1;
	}
}

void main( ){   
  InitializeSystem( );
	Auto_Reader();
}