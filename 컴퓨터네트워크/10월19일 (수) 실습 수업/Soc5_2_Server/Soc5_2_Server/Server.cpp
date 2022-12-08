/*
��ǻ�� ��Ʈ��ũ 21812248 ��â��
Soc5_2 Server
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
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0); // TCP Ÿ������ SOCKET�����.
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
	myAddress.sin_addr.s_addr = INADDR_ANY; // ������ ip�ּҸ� ����ش�.

	// �Լ��� �̸� ���̴� �Լ� bind(), error ó��, ip�ּ� �� port��ȣ �� bind() �Լ��� ���������� �ƴ��� Ȯ���Ѵ�.
	if (bind(s, (SOCKADDR*)&myAddress, sizeof(myAddress)) == SOCKET_ERROR) {
		printf("Error in bind(), Error code: %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	// listen () �Լ��� ���������� �ƴ��� Ȯ���Ѵ�.
	// listen �Լ� => ����� ���Ͽ��� ���� ������ּ���. �� ������ ���۸� �����޶�� ��û�Ѵ�.
	// ������ ����� ���ϰ� ������ ���� ũ�⸦ �������ش�.
	if (listen(s, 5) == SOCKET_ERROR) {
		printf("Error in listen(), Error code: %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	/* ���α׷��� ������ ������� �ʰ� ���� Ŭ���̾�Ʈ�� ��ٸ������� while�� ��� */
	while (1) {
		SOCKADDR_IN clientAddress; // �ٽ� send to �� �� �� ������ client�� ������ �ޱ� ���� ����
		int iAddressLength = sizeof(clientAddress);

		SOCKET t = accept(s, (SOCKADDR*)&clientAddress, &iAddressLength);
		// accept �Լ� �θ��� ���� ������ Ŭ���̾�Ʈ�� ������ ��û�� �� ������ ����Ѵ�.
		// ��û�� ���� ¦�� �����ָ鼭 Ǯ������. ���������� ���� ���� ������ �̸��� �������ش�.
		// ����� ���ϰ� ���� ��û�� �ؿ� Ŭ���̾�Ʈ�� �̸��� �����Ѵ�.
		// socket�� ����� �����ƴ��� Ȯ��
		if (t == INVALID_SOCKET) {
			printf(" Error in socket(), Error code: %d\n", WSAGetLastError());
			WSACleanup();;
			return -1;
		}

		char chRxBuf[MAX_BUF] = { 0 };
		int iLength = recv(t, chRxBuf, MAX_BUF, 0); // packet�� �� ������ ��ٸ���.

		/* recv() error Ȯ��, error�� �߻��ߴٸ� ���������� ���� ��Ų��. */
		if (iLength == SOCKET_ERROR) {
			printf("Error in recv(), Error code: %d\n", WSAGetLastError());
			closesocket(t);
			WSACleanup();
			return -1;
		}

		/* error�� �߻����� �ʾҴٸ� ���޹��� �޽����� ����Ѵ�. */
		printf("���� : %s\n", chRxBuf);

		char chTxBuf[MAX_BUF] = "Hi, TCP Client(21812248 LCH) . Current time is ...";  // ������ �޽���
		int aLength = send(t, chTxBuf, strlen(chTxBuf), 0);

		/* send() error Ȯ��, error�� �߻��ߴٸ� ���������� ���� ��Ų��. */
		if (aLength == SOCKET_ERROR) {
			printf("Error in send(), Error code: %d\n", WSAGetLastError());
			closesocket(t);
			WSACleanup();
			return -1;
		}
		/* error�� �߻����� �ʾҴٸ� ������ �޽����� ����Ѵ�. */
		printf("�۽� : %s\n", chTxBuf);

		closesocket(t);
	}
	closesocket(s);

	WSACleanup();

	return 0;
}