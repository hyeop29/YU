/* socket ���̺귯�� �⺻ ���̺귯���� �ƴ϶� ��Ŀ�� �ٿ����� �ʴ´�
   => ��Ŀ���� socket ���̺귯�� �Լ��� �����ش޶�� �ؾ��Ѵ�.
   socket ���̺귯�� �Լ��� ����ϴ� ���α׷��� © �� ..!
   �Ӽ� - ��Ŀ  - ws2_32.lib �߰� �� �� or  #pragma comment(lib, "ws2_32.lib");
*/
#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

int main(void) {
	WSADATA wsa; // window�� ������ �˷��ְ� ���� �� ����ϴ� �� �׸��� wsa ������ Ÿ���� ����ü ����

	// Windows���� ���� ���̺귯���� ����ҷ���  WSAStartup()�� WSACleanup()�� ȣ�����־���Ѵ�.

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) // paramater = > Winsock 2.2 ���� ���, window�� ������ �˷��ִ� ������ wsa�� ���� ���̴�.
											   // Startup �Լ� �������� �� ���� 0�� �ƴϸ� ������ �� ���̴�.
	{
		printf("Error in starting up Winsock \n");
		return -1;
	}
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0); // socket�� ����� �Լ�

	/* ��� �����ϱ��� �̸� ���̱� */
	SOCKADDR_IN myAddress; // IP�ּҿ� PORT ��ȣ �����ϱ� ���� ���� 
	ZeroMemory(&myAddress, sizeof(myAddress)); // ������ �޸� ������ 0 ���� �ʱ�ȭ ���ִ� �Լ�, sin_zero �� 0���� ����ϱ⶧���� �̸� ��� 0���� �ʱ�ȭ ���ش�.
	myAddress.sin_family = AF_INET;
	myAddress.sin_port = 50000; // port ��ȣ
	inet_pton(AF_INET, "172.20.10.11", &(myAddress.sin_addr.s_addr)); // inet_pton() => ip �ּҸ� 2������ ��ȯ ���ִ� �Լ�
	bind(s, (SOCKADDR*)&myAddress, sizeof(myAddress)); // �Լ��� �̸� ���̴� �Լ� bind()

	closesocket(s);

	WSACleanup();

	return 0;
}