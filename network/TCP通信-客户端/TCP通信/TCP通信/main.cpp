/*�ͻ���
**SocketClient.cpp
**2019/8/21
**Author:�����󣨸ģ�
**ע������ע�ؽ���ѧϰ����������Ըô���ĸ�ʽ
*/
#include <WINSOCK2.H>   
#include<iostream>
using namespace std;

#pragma comment(lib, "ws2_32.lib")      

int main()
{
	WSADATA wsaData;
	WSAStartup(0x0202, &wsaData);//����Windows Sockets API֧Ԯ
	SOCKET clientSocket;//��������ʼ���׽���
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN server;//����������ַ��Ϣ
	server.sin_family = PF_INET;
	server.sin_port = htons(8888);
	server.sin_addr.s_addr = inet_addr("192.168.31.29");
	//����һ��������Ĵ��룬����϶��Ϳ��ö��ˡ��������ͻ�ͷ�ٿ����ɡ�

	//���ӷ�����   
	connect(clientSocket, (struct sockaddr *) &server, sizeof(server));
	/*
	����:���Ӻ������clientSocket��ʹ���������
	�÷�:Ҫ��¼���׽��֣�������Զ�̵�ַ��Ϣ��server����ַ��С��
	P.S�������������recv()������ͬ��
	*/

	//������Ϣ
	while (TRUE) {
		char Msg[128];//���巢�ͻ�����
		cout << "Send:"; cin >> Msg;//����Ҫ���͵��ֽ�
		send(clientSocket, Msg, strlen(Msg), 0);
		/*
		���ã�snd()�ӷ��ͻ������������ݡ�
		�÷���ǰ�������������Ĳ������塣���һ������Ϊ0�����壺Ĭ������ͨ��������ģʽ
		*/
	}

	//�����ͻ���;      
	closesocket(clientSocket);
	WSACleanup();
	return 0;
}
