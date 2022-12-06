#include <stdio.h>
#include <winsock2.h>
#include<WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[]) {
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &wsaData) != 0) {
		return 0;
	}

	SOCKET serSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (serSocket == INVALID_SOCKET) {
		printf("socket error !");
		return 0;
	}

	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);
	serAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(serSocket, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR) {
		printf("bind error !");
		closesocket(serSocket);
		return 0;
	}

	sockaddr_in remoteAddr;
	int nAddrLen = sizeof(remoteAddr);
	printf("���ݳs�u...\n");
	char recvData[255];
	int ret[3];
	for (int i = 0;i < 3;i++) {
		ret[i] = recvfrom(serSocket, recvData, 255, 0, (sockaddr*)&remoteAddr, &nAddrLen);
		if (ret[i] > 0) {
			recvData[ret[i]] = 0x00;
			char sendBuf[20] = { '\0' };
			if (i == 0) {
				printf("������@�ӳs���G%s \r\n", inet_ntop(AF_INET, (void*)&remoteAddr.sin_addr, sendBuf, 16));
			}
			printf(recvData);
			printf("\n");

			system("pause");
			const char* sendData = "ack\n";
			printf("return ack\n");
			sendto(serSocket, sendData, strlen(sendData), 0, (sockaddr*)&remoteAddr, nAddrLen);
		}
	}
	closesocket(serSocket);
	WSACleanup();
	return 0;
}