/*
컴퓨터 네트워크 21812248 이창협
Soc6_1 Client
*/
#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#define MAX_BUF 1024

/* Server로부터 무언가 오기를 기다리는 함수 */
DWORD WINAPI thread_for_display(LPVOID pParam) {
	SOCKET s = (SOCKET)pParam; // 빨간 소켓의 이름을 전달 받는다 (해당 Client 전용으로 만든 Server의 소켓을 전달 받는다.)

	char chRxBuf[MAX_BUF] = { 0 };
	while (1) {
		int iLength = recv(s, chRxBuf, MAX_BUF - 1, 0);
		/* recv() error 확인, error가 발생했다면 정상적으로 종료 시킨다. */
		if (iLength == SOCKET_ERROR) {
			printf("Error in recv(), Error code: %d\n", WSAGetLastError());
			closesocket(s);
			WSACleanup();
			return -1;
		}
		/* error가 발생하지 않았다면 전달받은 메시지를 출력한다. */
		printf("수신 : %s\n", chRxBuf);
		chRxBuf[iLength] = NULL;


	}
	closesocket(s);
	return 0;
}

int main(void) {
	WSADATA wsa; // window가 나한테 알려주고 싶을 때 사용하는 빈 그릇인 wsa 데이터 타입의 구조체 선언

// Windows에서 소켓 라이브러리를 사용할려면  WSAStartup()과 WSACleanup()을 호출해주어야한다.

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) // paramater = > Winsock 2.2 버전 사용, window가 나한테 알려주는 정보를 wsa에 써줄 것이다.
											   // Startup 함수 실행했을 때 값이 0이 아니면 오류가 뜬 것이다.
	{
		printf("Error in starting up Winsock \n");
		return -1;
	}
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0); // TCP 타입으로 SOCKET만든다.
	// socket이 제대로 생성됐는지 확인
	if (s == INVALID_SOCKET) {
		printf(" Error in socket(), Error code: %d\n", WSAGetLastError());
		WSACleanup();;
		return -1;
	}

	SOCKADDR_IN serverAddress; // IP주소와 PORT 번호 세팅하기 위한 변수 
	ZeroMemory(&serverAddress, sizeof(serverAddress)); // 지정한 메모리 영역을 0 으로 초기화 해주는 함수, sin_zero 를 0으로 줘야하기때문에 미리 모두 0으로 초기화 해준다.
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080); // sin_port 는 Big endian으로 변환 해야함
	inet_pton(AF_INET, "165.229.229.248", &(serverAddress.sin_addr.s_addr)); // inet_pton() => ip 주소를 2진수로 변환 해주는 함수 이자 Big endian으로 자동 변환

	int cerror = connect(s, (SOCKADDR*)&serverAddress, sizeof(serverAddress));
	/* connect() error 확인, error가 발생했다면 정상적으로 종료 시킨다. */
	if (cerror == SOCKET_ERROR) {
		printf("Error in connect(), Error code: %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	CreateThread(NULL, 0, thread_for_display, (LPVOID)s, 0, NULL);

	while (1) {
		char chTxBuf[MAX_BUF] = { 0 };
		/* 키보드로부터 메세지 입력받는 함수*/
		if (gets_s(chTxBuf, MAX_BUF - 1) != NULL) {
			int aLength = send(s, chTxBuf, strlen(chTxBuf), 0);
			/* send() error 확인, error가 발생했다면 정상적으로 종료 시킨다. */
			if (aLength == SOCKET_ERROR) {
				printf("Error in send(), Error code: %d\n", WSAGetLastError());
				closesocket(s);
				WSACleanup();
				return -1;
			}
			/* error가 발생하지 않았다면 전송할 메시지를 출력한다. */
			printf("송신 : %s\n", chTxBuf);
		}
		else {
			break;
		}
	}

	closesocket(s);

	WSACleanup();

	return 0;
}