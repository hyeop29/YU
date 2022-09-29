/*
��ǻ�� ��Ʈ��ũ 21812248 ��â��
Soc4_1 Server
*/
#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#define MAX_BUF 1024

int main(void) {
	WSADATA wsa; // window�� ������ �˷��ְ� ���� �� ����ϴ� �� �׸��� wsa ������ Ÿ���� ����ü ����

	// Windows���� ���� ���̺귯���� ����ҷ���  WSAStartup()�� WSACleanup()�� ȣ�����־���Ѵ�.

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) // paramater = > Winsock 2.2 ���� ���, window�� ������ �˷��ִ� ������ wsa�� ���� ���̴�.
											   // Startup �Լ� �������� �� ���� 0�� �ƴϸ� ������ �� ���̴�.
	{
		printf("Error in starting up Winsock \n");
		return -1;
	}
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0); // UDP Ÿ������ SOCKET�����.
	// socket�� ����� �����ƴ��� Ȯ��
	if (s == INVALID_SOCKET) {
		printf(" Error in socket(), Error code: %d\n", WSAGetLastError());
		WSACleanup();;
		return -1;
	}

	/* ��� �����ϱ��� �̸� ���̱� */
	SOCKADDR_IN myAddress; // IP�ּҿ� PORT ��ȣ �����ϱ� ���� ���� 
	ZeroMemory(&myAddress, sizeof(myAddress)); // ������ �޸� ������ 0 ���� �ʱ�ȭ ���ִ� �Լ�, sin_zero �� 0���� ����ϱ⶧���� �̸� ��� 0���� �ʱ�ȭ ���ش�.
	myAddress.sin_family = AF_INET;
	myAddress.sin_port = htons(50000); // sin_port �� Big endian���� ��ȯ �ؾ���
	inet_pton(AF_INET, "165.229.244.254", &(myAddress.sin_addr.s_addr)); // inet_pton() => ip �ּҸ� 2������ ��ȯ ���ִ� �Լ� ���� Big endian���� �ڵ� ��ȯ
	
	// �Լ��� �̸� ���̴� �Լ� bind(), error ó��, ip�ּ� �� port��ȣ �� bind() �Լ��� ���������� �ƴ��� Ȯ���Ѵ�.
	if (bind(s, (SOCKADDR*)&myAddress, sizeof(myAddress)) == SOCKET_ERROR) {
		printf("Error in bind(), Error code: %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}
	
	/* ���α׷��� ������ ������� �ʰ� ���� Ŭ���̾�Ʈ�� ��ٸ������� while�� ��� */
	while (1) {
		SOCKADDR_IN clientAddress; // �ٽ� send to �� �� �� ������ client�� ������ �ޱ� ���� ����
		int iAddressLength = sizeof(clientAddress);
		char chRxBuf[MAX_BUF] = { 0 };
		int iLength = recvfrom(s, chRxBuf, MAX_BUF, 0, (SOCKADDR*)&clientAddress, &iAddressLength); // packet�� �� ������ ��ٸ���.
		
		/* recvfrom() error Ȯ��, error�� �߻��ߴٸ� ���������� ���� ��Ų��. */
		if (iLength == SOCKET_ERROR) {
			printf("Error in recvfrom(), Error code: %d\n", WSAGetLastError());
			closesocket(s);
			WSACleanup();
			return -1;
		}

		/* error�� �߻����� �ʾҴٸ� ���޹��� �޽����� ����Ѵ�. */
		printf("���� : %s\n", chRxBuf);

		char chTxBuf[MAX_BUF] = "Hi, Client. Current time is ...";  // ������ �޽���
		int aLength = sendto(s, chTxBuf, strlen(chTxBuf), 0, (SOCKADDR*)&clientAddress, sizeof(clientAddress));
		
		/* sendto() error Ȯ��, error�� �߻��ߴٸ� ���������� ���� ��Ų��. */
		if (aLength == SOCKET_ERROR) {
			printf("Error in sendto(), Error code: %d\n", WSAGetLastError());
			closesocket(s);
			WSACleanup();
			return -1;
		}
		/* error�� �߻����� �ʾҴٸ� ������ �޽����� ����Ѵ�. */
		printf("�۽� : %s\n", chTxBuf);
	}
	closesocket(s);
	
	WSACleanup();

	return 0;
}