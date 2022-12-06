#include <stdio.h>    
#include <winsock2.h>
#include<WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[]) {
	//��l��WSA windows�۱a��socket
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0) {
		return 0;
	}

	//�ЫتA�ȺݮM���r
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET) {
		printf("socket error !");
		return 0;
	}

	//�A�Ⱥݻݭn�j�wip�M�ݤf
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY; //��ť���N���a�}
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR) { //�N�A�ȺݮM���r�P�W����ip�M�ݤf�j�w 
		printf("bind error !");
	}

	//�}�l��ť
	if (listen(slisten, 5) == SOCKET_ERROR) {  //��listen�]�^ ��ť�e���j�w�n��slisten�M���r
		printf("listen error !");
		return 0;
	}

	//�`�������ƾ�
	SOCKET sClient;  //�Ыسs�����M���r
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr); //�Ω󱵨��Ȥ�ݦa�}
	char revData[255]; //�s�x�������ƾ�
	while (1) {
		printf("���ݳs��...\n");
		sClient = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen); //�M�Ȥ�� connect�]�^����
		if (sClient == INVALID_SOCKET) {
			printf("accept error !");
			continue;
		}
		char sendBuf[20] = { '\0' };
		printf("������@�ӳs���G%s \r\n", inet_ntop(AF_INET, (void*)&remoteAddr.sin_addr, sendBuf, 16));

		//�ƾڱ���
		int ret = recv(sClient, revData, 255, 0);
		if (ret > 0) {
			revData[ret] = 0x00;
			printf(revData);
			printf("\n\n");
		}

		//�o�e�ƾڵ��Ȥ��
		const char* sendData = "�A�n�ATCP�Ȥ�ݡI \n";
		send(sClient, sendData, strlen(sendData), 0);
		closesocket(sClient);  //�����w���q���M���r
	}

	closesocket(slisten); //������ť���M���r
	WSACleanup();
	return 0;
}
