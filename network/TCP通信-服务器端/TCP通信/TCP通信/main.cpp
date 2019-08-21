/*�����
**SocketService.cpp
**2019/8/21
**Author:�����󣨸ģ�
**ע������ע�ؽ���ѧϰ����������Ըô���ĸ�ʽ
*/

#include<WINSOCK2.h>//windows socket��ͷ�ļ� ϵͳ�Դ�
#include<iostream>//�������֪����Ҳû�취
using namespace std;//��仰��Ҳ�����ΰ�

#pragma comment(lib,"ws2_32.lib")//������API������ʱ�򣬾�Ҫ������������ws2_32.lib��(�������Լ�ȥ��̬����ws2_32.dll)

int main()
{
	WSADATA wsaData;//�����洢�� WSAStartup �������ú󷵻ص�����
	WSAStartup(0x0202, &wsaData);
	/*
	��Ҫ�ԣ�WSAStartup������Windows Sockets�е�һ��ʹ�õĺ������ɹ����ú���ܽ�һ��ʹ��Windows Sockets API����
	���ã�ָ��Windows Sockets API�İ汾�ż�����ض�Windows Socketsʵ�ֵ�ϸ��
	�÷���ǰ����һ��WORD��˫�ֽڣ�����ֵ��ָ����Ӧ�ó�����Ҫʹ�õ�Winsock�淶����߰汾��
		�����WSADATA���ݽṹ��ָ�룬��������Windows Socketsʵ�ֵ�ϸ�ڡ�
	*/

	//1���׽��֣�SOCKET����ķ���)�Ĵ����͹ر�
	SOCKET listenSocket; //�����׽���
	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//�����׽���
	/*
	���ã������׽���ʱ����С������Ϊ����������ʶ��
	�÷���AF��ʾADDRESS FAMILY ��ַ�壬SOCK_STREAM��ʾ�ܱ�֤������ȷ���͵��Է���SOCKET��IPPROTO_TCP��ʾTCPЭ��
	���䣺����ʹ��socket�������׽���ʱ��Ӧ�õ���closesocket���������ر�(int closesocket(SOCKET s);  )
	*/

	//2�����׽��ֵ�ָ����IP��ַ�Ͷ˿ں�
	SOCKADDR_IN local;
	//���ڽ���listenSocket�ı��ع���sockaddr_in�ṹ
	local.sin_family = AF_INET;
	//��socket�����е�af�����ĺ�����ͬ������
	local.sin_port = htons(8888);
	//����˿ںŵ���0��ִ��ʱϵͳ���Զ�����Ψһ�Ķ˿ںţ���ֵ��1024��5000֮�䡣
	local.sin_addr.s_addr = htonl(INADDR_ANY);//�����ַ����INADDR_ANY�����Զ�ʹ�õ�ǰ�������õ�����IP��ַ��
	/*Ҳ������local.S_un.S_addr.s_addr = htonl(INADDR_ANY)��(��Ϊwinsock2.h�ж�����#define s_addr  S_un.S_addr)
	sin_port�ֶκ�sin_addr�ֶηֱ�ָ���׽�����Ҫ�󶨵Ķ˿ںź�IP��ַ�������������ֶε����ݵ��ֽ�˳������������ֽ�˳��
	����Ϊ�����ֽ�˳���Intel CPU���ֽ�˳��պ��෴�����Ա�������ʹ��htons��������ת����*/
	bind(listenSocket, (struct sockaddr *) &local, sizeof(local));
	/*
	���ã�bind��������û�н������ӵ��׽����ϣ����������ǰ��������ӵĻ��������ӵ��׽��֡�
		�׽��ֱ�socket���������Ժ󣬴�����ָ���ĵ�ַ�����������δ�����ġ�
		bind����ͨ������һ���������Ƶ�δ������socket��������socket�ı��ع�����
	�÷���1.SOCKET 2.SOCKADDR_IN	 3.SOCKADDR_IN�ĳ���
	*/

	//3�������׽��ֽ������״̬	
	listen(listenSocket, 1);
	cout << "����������\n";
	/*
	���ã������׽��ֽ������״̬��
	�÷����׽��֣����������������ֵ���δ����������������
	���ԣ�����ִ�гɹ����׽���s�����˱���ģʽ�����������ӻᱻ֪ͨҪ�ŶӵȺ���ܴ���
		��ͬһʱ�䴦������������ķ�����ͨ��ʹ��listen����
		���һ���������󵽴�����Ŷ��������ͻ��˽����յ�WSAECONNREFUSED����
	*/

	//4��������������
	SOCKET clientSocket;//�����˾Ϳ�����
	SOCKADDR_IN client;//�����˾Ϳ�����
	int addrSize = sizeof(SOCKADDR_IN);
	clientSocket = accept(listenSocket, (struct sockaddr *) &client, &addrSize);
	/*
	���ã�ȡ��δ���������еĵ�һ�����ӣ�Ȼ��Ϊ������Ӵ����µ��׽��֣�������
	���ԣ�����Ĭ�Ϲ���������ģʽ�£����û��δ��������Ӵ��ڣ��ͻ�ȴ���ȥ��ֱ���������ӷ��������д���
	�÷���addrlen��������ָ��addr��ָ�ռ�Ĵ�С��Ҳ���ڷ��ص�ַ��ʵ�ʳ��ȡ������NULL����û�й���Զ�̵�ַ����Ϣ����
	*/
	cout << "Accepted client:%s:%d\n"//����������Ϣ
		<< inet_ntoa(client.sin_addr)//inet_ntoa��һ��ʮ���������ֽ���ת��Ϊ���ʮ����IP��ʽ���ַ�����
		<< ntohs(client.sin_port);  //ntohs��һ��16λ���������ֽ�˳��ת��Ϊ�����ֽ�˳��

//5.��ͻ���ͨ��
	int const CLIENT_MSG_SIZE = 128;//���ջ���������
	char cacheMSG[CLIENT_MSG_SIZE]; //���ջ������Ļ���ַ
	while (TRUE) {
		int size = recv(clientSocket, cacheMSG, CLIENT_MSG_SIZE, 0);
		/*
		���ã�recv()�ӽ��ջ������������ݡ��ɹ�ʱ�����ؿ������ֽ�����ʧ�ܷ���-1��
		�÷���ǰ�������������Ĳ������塣���һ������Ϊ0�����壺Ĭ������ͨ��������ģʽ
		���ԣ�����ģʽ�£�recv������������������������һ���ֽڣ�û������ʱ��������״̬��
			�������������������أ��������򷵻ؿ��������ݴ�С�����򷵻ش���-1��
		*/
		cacheMSG[size] = '\0'; //�㶮��   
		cout << "Received:" << cacheMSG << endl;
	}

	//6.������β
	closesocket(listenSocket);
	closesocket(clientSocket);
	WSACleanup();
	return 0;
}
