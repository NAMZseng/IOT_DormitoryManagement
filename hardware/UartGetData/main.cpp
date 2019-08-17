#include <windows.h>
#include <string>
#include <string.h>
#include <iostream>
using namespace std;
HANDLE hCom;
int main()
{
	int i;
	unsigned char str[5];
	hCom = CreateFile(TEXT("COM2"),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	if (hCom == (HANDLE)-1)
	{
		printf("��COMʧ��\n");
		return FALSE;
	}
	else
	{
		printf("��COM�ɹ�\n");
	}
	SetupComm(hCom, 1024, 1024);
	COMMTIMEOUTS TimeOuts;

	TimeOuts.ReadIntervalTimeout = 1000;
	TimeOuts.ReadTotalTimeoutMultiplier = 5000;
	TimeOuts.ReadTotalTimeoutConstant = 5000;

	TimeOuts.WriteTotalTimeoutMultiplier = 5000;
	TimeOuts.WriteTotalTimeoutConstant = 2000;
	SetCommTimeouts(hCom, &TimeOuts);
	DCB dcb;
	GetCommState(hCom, &dcb);
	dcb.BaudRate = 4800; 
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONE5STOPBITS;

	SetCommState(hCom, &dcb);
	DWORD wCount = 4; //��ȡ���ֽ��� 
	BOOL bReadStat;

	while (1)
	{
		PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
		bReadStat = ReadFile(hCom, str, 4, &wCount, NULL);
		if (!bReadStat)
		{
			printf("��ȡ����ʧ��!");
			return FALSE;
		}
		else
		{ 
			str[4] = '\0';
			//for (i = 0; str[i] != '\0'; i++) {
				//printf("%02x ", str[i]);
			//}
			int flag = (int)str[0];
			cout << flag << endl;
			if (flag > 200) { //���� 
				printf("1607094217") ;
			}
			else //�׿� 
			{
				printf("1607094216") ;
			}
		}
		printf("\n");
		Sleep(500);
	}
}
