#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

int main(void) {
	WSADATA wsa; // window가 나한테 알려주고 싶을 때 사용하는 빈 그릇인 wsa 데이터 타입의 구조체 선언

	// Windows에서 소켓 라이브러리를 사용할려면  WSAStartup()과 WSACleanup()을 호출해주어야한다.

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) // paramater = > Winsock 2.2 버전 사용, window가 나한테 알려주는 정보를 wsa에 써줄 것이다.
											   // Startup 함수 실행했을 때 값이 0이 아니면 오류가 뜬 것이다.
	{
		printf("Error in starting up Winsock \n");
		return -1;
	}
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0); // socket을 만드는 함수
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
	myAddress.sin_port = htons(50000); // sin_port 는 Big endian으로 변환 해야함
	inet_pton(AF_INET, "172.20.10.11", &(myAddress.sin_addr.s_addr)); // inet_pton() => ip 주소를 2진수로 변환 해주는 함수 이자 Big endian으로 자동 변환
	// 함수에 이름 붙이는 함수 bind(), error 처리, ip주소 및 port번호 등 bind() 함수가 정상적으로 됐는지 확인한다.
	if (bind(s, (SOCKADDR*)&myAddress, sizeof(myAddress)) == SOCKET_ERROR) {
		printf("Error in bind(), Error code: %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	closesocket(s);

	WSACleanup();

	return 0;
}