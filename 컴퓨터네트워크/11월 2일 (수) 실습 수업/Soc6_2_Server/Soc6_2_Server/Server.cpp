/*
컴퓨터 네트워크 21812248 이창협
Soc6_2 Server
*/
#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#define MAX_BUF 1024
#define MAX_CLIENT 1024

/* main 함수 적절히 실행될 함수 정의, 파라메타는 하나 밖에 못 준다. */
/* => 데이터의 덩어리를 전달, 데이터의 덩어리를 가르키는 곳(포인터)를 전달 */
/* Return 값은 DWORD (DoubleWorld) windows.h 를 필요로 한다. */
/* WINAPI는 Return 값이 절대 아니다. */
SOCKET client[MAX_CLIENT]; // 소켓디스티러를 담을 수 있는 전역변수, 배열

DWORD WINAPI thread_for_client(LPVOID pParam) {
	int idx = (int)pParam;
	SOCKET t = client[idx]; // 빨간 소켓의 이름을 받는다.

	char chRxBuf[MAX_BUF] = { 0 };
	while (1) {
		int iLength = recv(t, chRxBuf, MAX_BUF-1, 0);
		/* recv() error 확인, error가 발생했다면 정상적으로 종료 시킨다. */
		if (iLength == SOCKET_ERROR) {
			printf("Error in recv(), Error code: %d\n", WSAGetLastError());
			closesocket(t);
			WSACleanup();
			return -1;
		}
		printf("수신 : %s\n", chRxBuf);

		chRxBuf[iLength] = NULL;

		for (int i = 0; i < MAX_CLIENT; i++) {
			if ((client[i] != 0) && (client[i] != t)) {
				int aLength = send(client[i], chRxBuf, strlen(chRxBuf), 0);
				/* send() error 확인, error가 발생했다면 정상적으로 종료 시킨다.*/
				if (aLength == SOCKET_ERROR) {
					printf("Error in send(), Error code: %d\n", WSAGetLastError());
					closesocket(t);
					WSACleanup();
					return -1;
				}
				printf("송신 : %s\n", chRxBuf);
			}
		}
		
	}
	client[idx] = 0;
	closesocket(t);
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

	/* 통신 시작하기전 이름 붙이기 */
	SOCKADDR_IN myAddress; // IP주소와 PORT 번호 세팅하기 위한 변수 
	ZeroMemory(&myAddress, sizeof(myAddress)); // 지정한 메모리 영역을 0 으로 초기화 해주는 함수, sin_zero 를 0으로 줘야하기때문에 미리 모두 0으로 초기화 해준다.
	myAddress.sin_family = AF_INET;
	myAddress.sin_port = htons(8080); // sin_port 는 Big endian으로 변환 해야함
	myAddress.sin_addr.s_addr = INADDR_ANY; // 스스로 ip주소를 잡아준다.

	// 함수에 이름 붙이는 함수 bind(), error 처리, ip주소 및 port번호 등 bind() 함수가 정상적으로 됐는지 확인한다.
	if (bind(s, (SOCKADDR*)&myAddress, sizeof(myAddress)) == SOCKET_ERROR) {
		printf("Error in bind(), Error code: %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	// listen () 함수가 정상적으로 됐는지 확인한다.
	// listen 함수 => 노란색 소켓에게 대기실 만들어주세요. 즉 서버에 버퍼를 만들어달라고 요청한다.
	// 서버의 노란색 소켓과 소켓의 버퍼 크기를 전달해준다.
	if (listen(s, 5) == SOCKET_ERROR) {
		printf("Error in listen(), Error code: %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	/* 프로그램이 영원히 종료되지 않고 다음 클라이언트를 기다리기위해 while문 사용 */
	while (1) {
		SOCKADDR_IN clientAddress; // 다시 send to 할 수 도 있으니 client의 정보를 받기 위해 선언
		int iAddressLength = sizeof(clientAddress);

		SOCKET t = accept(s, (SOCKADDR*)&clientAddress, &iAddressLength);
		// accept 함수 부르는 순간 서버는 클라이언트가 접속을 요청해 올 때까지 대기한다.
		// 요청이 오면 짝을 지어주면서 풀려난다. 내부적으로 만든 빨간 소켓의 이름을 리턴해준다.
		// 노란색 소켓과 연결 요청을 해온 클라이언트의 이름을 전달한다.
		// socket이 제대로 생성됐는지 확인
		if (t == INVALID_SOCKET) {
			printf(" Error in accept(), Error code: %d\n", WSAGetLastError());
			WSACleanup();;
			return -1;
		}

		int idx = -1;
		/* 전역변수 배열에 빈자리 찾는다. */
		for (int i = 0; i < MAX_CLIENT; i++) {
			if (client[i] == 0) {
				idx = i;
				break;
			}
		}
		/* 전역변수 배열에 빈자리에 넣어준다. */
		if (idx >= 0) {
			client[idx] = t;
			CreateThread(NULL, 0, thread_for_client, (LPVOID)idx, 0, NULL);
		}

	}
	closesocket(s);

	WSACleanup();

	return 0;
}