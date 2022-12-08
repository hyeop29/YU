/*
��ǻ�� ��Ʈ��ũ 21812248 ��â��
Soc6_1 Client
*/
#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#define MAX_BUF 1024

/* Server�κ��� ���� ���⸦ ��ٸ��� �Լ� */
DWORD WINAPI thread_for_display(LPVOID pParam) {
	SOCKET s = (SOCKET)pParam; // ���� ������ �̸��� ���� �޴´� (�ش� Client �������� ���� Server�� ������ ���� �޴´�.)

	char chRxBuf[MAX_BUF] = { 0 };
	while (1) {
		int iLength = recv(s, chRxBuf, MAX_BUF - 1, 0);
		/* recv() error Ȯ��, error�� �߻��ߴٸ� ���������� ���� ��Ų��. */
		if (iLength == SOCKET_ERROR) {
			printf("Error in recv(), Error code: %d\n", WSAGetLastError());
			closesocket(s);
			WSACleanup();
			return -1;
		}
		/* error�� �߻����� �ʾҴٸ� ���޹��� �޽����� ����Ѵ�. */
		printf("���� : %s\n", chRxBuf);
		chRxBuf[iLength] = NULL;


	}
	closesocket(s);
	return 0;
}

int main(void) {
	WSADATA wsa; // window�� ������ �˷��ְ� ���� �� ����ϴ� �� �׸��� wsa ������ Ÿ���� ����ü ����

// Windows���� ���� ���̺귯���� ����ҷ���  WSAStartup()�� WSACleanup()�� ȣ�����־���Ѵ�.

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) // paramater = > Winsock 2.2 ���� ���, window�� ������ �˷��ִ� ������ wsa�� ���� ���̴�.
											   // Startup �Լ� �������� �� ���� 0�� �ƴϸ� ������ �� ���̴�.
	{
		printf("Error in starting up Winsock \n");
		return -1;
	}
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0); // TCP Ÿ������ SOCKET�����.
	// socket�� ����� �����ƴ��� Ȯ��
	if (s == INVALID_SOCKET) {
		printf(" Error in socket(), Error code: %d\n", WSAGetLastError());
		WSACleanup();;
		return -1;
	}

	SOCKADDR_IN serverAddress; // IP�ּҿ� PORT ��ȣ �����ϱ� ���� ���� 
	ZeroMemory(&serverAddress, sizeof(serverAddress)); // ������ �޸� ������ 0 ���� �ʱ�ȭ ���ִ� �Լ�, sin_zero �� 0���� ����ϱ⶧���� �̸� ��� 0���� �ʱ�ȭ ���ش�.
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080); // sin_port �� Big endian���� ��ȯ �ؾ���
	inet_pton(AF_INET, "165.229.229.248", &(serverAddress.sin_addr.s_addr)); // inet_pton() => ip �ּҸ� 2������ ��ȯ ���ִ� �Լ� ���� Big endian���� �ڵ� ��ȯ

	int cerror = connect(s, (SOCKADDR*)&serverAddress, sizeof(serverAddress));
	/* connect() error Ȯ��, error�� �߻��ߴٸ� ���������� ���� ��Ų��. */
	if (cerror == SOCKET_ERROR) {
		printf("Error in connect(), Error code: %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	CreateThread(NULL, 0, thread_for_display, (LPVOID)s, 0, NULL);

	while (1) {
		char chTxBuf[MAX_BUF] = { 0 };
		/* Ű����κ��� �޼��� �Է¹޴� �Լ�*/
		if (gets_s(chTxBuf, MAX_BUF - 1) != NULL) {
			int aLength = send(s, chTxBuf, strlen(chTxBuf), 0);
			/* send() error Ȯ��, error�� �߻��ߴٸ� ���������� ���� ��Ų��. */
			if (aLength == SOCKET_ERROR) {
				printf("Error in send(), Error code: %d\n", WSAGetLastError());
				closesocket(s);
				WSACleanup();
				return -1;
			}
			/* error�� �߻����� �ʾҴٸ� ������ �޽����� ����Ѵ�. */
			printf("�۽� : %s\n", chTxBuf);
		}
		else {
			break;
		}
	}

	closesocket(s);

	WSACleanup();

	return 0;
}