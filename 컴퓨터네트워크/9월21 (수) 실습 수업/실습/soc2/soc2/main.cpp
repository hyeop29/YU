/* socket 라이브러리 기본 라이브러리가 아니라서 링커가 붙여주지 않는다
   => 링커한테 socket 라이브러리 함수도 결합해달라고 해야한다.
   socket 라이브러리 함수를 사용하는 프로그램을 짤 때 ..!
   속성 - 링커  - ws2_32.lib 추가 할 것 or  #pragma comment(lib, "ws2_32.lib");
*/
#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

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

	/* 통신 시작하기전 이름 붙이기 */
	SOCKADDR_IN myAddress; // IP주소와 PORT 번호 세팅하기 위한 변수 
	ZeroMemory(&myAddress, sizeof(myAddress)); // 지정한 메모리 영역을 0 으로 초기화 해주는 함수, sin_zero 를 0으로 줘야하기때문에 미리 모두 0으로 초기화 해준다.
	myAddress.sin_family = AF_INET;
	myAddress.sin_port = 50000; // port 번호
	inet_pton(AF_INET, "172.20.10.11", &(myAddress.sin_addr.s_addr)); // inet_pton() => ip 주소를 2진수로 변환 해주는 함수
	bind(s, (SOCKADDR*)&myAddress, sizeof(myAddress)); // 함수에 이름 붙이는 함수 bind()

	closesocket(s);

	WSACleanup();

	return 0;
}