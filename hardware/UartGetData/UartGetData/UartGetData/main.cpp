#include <stdio.h>
#include <string.h>
#include <string>
#include <windows.h>
#pragma warning(disable:4996)
using namespace std;

unsigned char str[5];
char no[22];
HANDLE hCom;

int main()
{
	hCom = CreateFile(TEXT("COM1"),      //�༭�򿪵Ĵ���
		GENERIC_READ | GENERIC_WRITE,    //�����д
		0,                               //��ռ��ʽ
		NULL,
		OPEN_EXISTING,                   //�򿪶����Ǵ���
		0,                               //ͬ����ʽ
		NULL);
	if (hCom == (HANDLE)-1) {
		printf("��COMʧ��\n");
		return FALSE;
	} else {
		printf("��COM�ɹ�\n");
	}
	SetupComm(hCom, 1024, 1024);          //���뻺�����������������С����1024
	COMMTIMEOUTS TimeOuts;
	//�趨����ʱ
	TimeOuts.ReadIntervalTimeout = 1000;
	TimeOuts.ReadTotalTimeoutMultiplier = 5000;
	TimeOuts.ReadTotalTimeoutConstant = 5000;
	//�趨д��ʱ
	TimeOuts.WriteTotalTimeoutMultiplier = 5000;
	TimeOuts.WriteTotalTimeoutConstant = 2000;
	SetCommTimeouts(hCom, &TimeOuts);
	DCB dcb;
	GetCommState(hCom, &dcb);
	dcb.BaudRate = 4800;                   //����������Ϊ4800
	dcb.ByteSize = 8;                      //ÿ�ֽ�8λ
	dcb.Parity = NOPARITY;                 //����żУ��λ
	dcb.StopBits = ONE5STOPBITS;           //1��ֹͣλ
	SetCommState(hCom, &dcb);
	DWORD wCount = 4;                      //��ȡ���ֽ��� 
	BOOL bReadStat;

	while (1)
	{
		PurgeComm(hCom, PURGE_TXCLEAR |    //��ջ�����
						PURGE_RXCLEAR);
		bReadStat = ReadFile(hCom, str, 4, &wCount, NULL);
		if (!bReadStat) {
			printf("��ȡ����ʧ��!");
			return FALSE;
		} else {
			//���ݴ���
			str[4] = '\0';
			int tar = (int)str[0];         //���ŵ���λλ���λ
			bool flag = true;              //��ֹ������
			if (tar == 144 || tar == 16) {
				strcpy(no, "1607094270");  //A card
			}
			else if (tar == 17 || tar == 49) {
				strcpy(no, "1607094271");  //B card
			}
			else if (tar == 135 || tar == 199) {
				strcpy(no, "1607094272");  //C card
			}
			else if (tar == 233) {
				strcpy(no, "1607094273");  //D card
			}
			else {
				flag = false;              //δ��⵽����
			}

			if (flag) {
				printf("�Ѽ�⵽ѧ��ѧ�ţ�%s, ״̬��%d", no, tar);
			}
			else {
				printf("error������ʧ�������·��ÿ�Ƭ");
			}
		}
		printf("\n");
		Sleep(500);
	}
}
