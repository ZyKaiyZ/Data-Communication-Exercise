#include <stdio.h>    
#include <winsock2.h>
#include<WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[]) {
	//初始化WSA windows自帶的socket
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0) {
		return 0;
	}

	//創建服務端套接字
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET) {
		printf("socket error !");
		return 0;
	}

	//服務端需要綁定ip和端口
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY; //監聽任意的地址
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR) { //將服務端套接字與上面的ip和端口綁定 
		printf("bind error !");
	}

	//開始監聽
	if (listen(slisten, 5) == SOCKET_ERROR) {  //用listen（） 監聽前面綁定好的slisten套接字
		printf("listen error !");
		return 0;
	}

	//循環接受數據
	SOCKET sClient;  //創建連接的套接字
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr); //用於接受客戶端地址
	char revData[255]; //存儲接受的數據
	while (1) {
		printf("等待連接...\n");
		sClient = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen); //和客戶端 connect（）對應
		if (sClient == INVALID_SOCKET) {
			printf("accept error !");
			continue;
		}
		char sendBuf[20] = { '\0' };
		printf("接受到一個連接：%s \r\n", inet_ntop(AF_INET, (void*)&remoteAddr.sin_addr, sendBuf, 16));

		//數據接收
		int ret = recv(sClient, revData, 255, 0);
		if (ret > 0) {
			revData[ret] = 0x00;
			printf(revData);
			printf("\n\n");
		}

		//發送數據給客戶端
		const char* sendData = "你好，TCP客戶端！ \n";
		send(sClient, sendData, strlen(sendData), 0);
		closesocket(sClient);  //關閉已接通的套接字
	}

	closesocket(slisten); //關閉監聽的套接字
	WSACleanup();
	return 0;
}
