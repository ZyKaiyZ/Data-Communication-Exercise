#include <stdio.h>
#include <winsock2.h>
#include<WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main(int argc, char* argv[]) {
	WORD socketVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(socketVersion, &wsaData) != 0) {
		return 0;
	}
	SOCKET sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	/*sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");*/
	inet_pton(AF_INET, "127.0.0.1", (void*)&sin.sin_addr.S_un.S_addr);

	int len = sizeof(sin);

	const char* sendData[3] = { "來自客戶端的數據包_0.\n" ,"來自客戶端的數據包_1.\n" ,"來自客戶端的數據包_2.\n" };
	for (int i = 0;i < 3;i++) {
		printf("send\n");
		sendto(sclient, sendData[i], strlen(sendData[i]), 0, (sockaddr*)&sin, len);

		char recvData[255];
		int ret = recvfrom(sclient, recvData, 255, 0, (sockaddr*)&sin, &len);
		if (ret > 0) {
			recvData[ret] = 0x00;
			printf(recvData);
			printf("\n");
		}
	}
	closesocket(sclient);
	WSACleanup();
	return 0;
}