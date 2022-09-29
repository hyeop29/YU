/* 
컴퓨터 네트워크 21812248 이창협
Soc4_1 Client
*/
#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#define MAX_BUF 1024

int main(void) {
	WSADATA wsa; // window가 나한테 알려주고 싶을 때 사용하는 빈 그릇인 wsa 데이터 타입의 구조체 선언

	// Windows에서 소켓 라이브러리를 사용할려면  WSAStartup()과 WSACleanup()을 호출해주어야한다.

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) // paramater = > Winsock 2.2 버전 사용, window가 나한테 알려주는 정보를 wsa에 써줄 것이다.
											   // Startup 함수 실행했을 때 값이 0이 아니면 오류가 뜬 것이다.
	{
		printf("Error in starting up Winsock \n");
		return -1;
	}
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0); // UDP 타입으로 SOCKET만든다.
	// socket이 제대로 생성됐는지 확인
	if (s == INVALID_SOCKET) {
		printf(" Error in socket(), Error code: %d\n", WSAGetLastError());
		WSACleanup();;
		return -1;
	}

	SOCKADDR_IN serverAddress; // IP주소와 PORT 번호 세팅하기 위한 변수 
	ZeroMemory(&serverAddress, sizeof(serverAddress)); // 지정한 메모리 영역을 0 으로 초기화 해주는 함수, sin_zero 를 0으로 줘야하기때문에 미리 모두 0으로 초기화 해준다.
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(50000); // sin_port 는 Big endian으로 변환 해야함
	inet_pton(AF_INET, "165.229.244.254", &(serverAddress.sin_addr.s_addr)); // inet_pton() => ip 주소를 2진수로 변환 해주는 함수 이자 Big endian으로 자동 변환
														
	char chTxBuf[MAX_BUF] = "Hello, UDP Time server!"; // 전송할 메시지
	int iLength = sendto(s, chTxBuf, strlen(chTxBuf), 0, (SOCKADDR*)&serverAddress, sizeof(serverAddress));
	
	/* sendto() error 확인, error가 발생했다면 정상적으로 종료 시킨다. */
	if (iLength == SOCKET_ERROR) {
		printf("Error in sendto(), Error code: %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}
	
	/* error가 발생하지 않았다면 전송할 메시지를 출력한다. */
	printf("송신 : %s\n", chTxBuf);

	SOCKADDR_IN clientAddress; // 다시 send to 할 수 도 있으니 client의 정보를 받기 위해 선언
	int iAddressLength = sizeof(clientAddress);
	char chRxBuf[MAX_BUF] = { 0 };
	int aLength = recvfrom(s, chRxBuf, MAX_BUF, 0, (SOCKADDR*)&clientAddress, &iAddressLength); // packet이 올 때까지 기다린다
	
	/* recvfrom() error 확인, error가 발생했다면 정상적으로 종료 시킨다. */
	if (aLength == SOCKET_ERROR) {
		printf("Error in recvfrom(), Error code: %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}
	/* error가 발생하지 않았다면 전달받은 메시지를 출력한다. */
	printf("수신 : %s\n", chRxBuf);

	closesocket(s);

	WSACleanup();

	return 0;
}