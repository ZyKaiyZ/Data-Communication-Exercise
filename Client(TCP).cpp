//#include<WINSOCK2.H>
//#include<STDIO.H>
//#include<iostream>
//#include<cstring>
//#include <string>
//#include<WS2tcpip.h>
//using namespace std;
//#pragma comment(lib, "ws2_32.lib")
//int main()
//{
//	//初始化WSA windows自帶的socket
//	WORD sockVersion = MAKEWORD(2, 2);
//	WSADATA data;
//	if (WSAStartup(sockVersion, &data) != 0)
//	{
//		return 0;
//	}
//	
//	//創建客戶端套接字
//	while (true)
//	{
//	    SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //客戶端套接字
//		if (sclient == INVALID_SOCKET)
//		{
//			printf("invalid socket!");
//			return 0;
//		}
//	
//		sockaddr_in serAddr;
//        serAddr.sin_family = AF_INET;
//		serAddr.sin_port = htons(8888);
//		inet_pton(AF_INET, "192.168.0.159", (void*)&serAddr.sin_addr.S_un.S_addr);
//		if (connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR) //與指定IP地址和端口的服務端連接
//		{
//			printf("connect error !");
//			closesocket(sclient);
//			return 0;
//		}
//		
//		printf("輸入你想傳輸的英文： \n");
//		string data;
//		cin >> data;
//	    const char* sendData2;
//		sendData2 = data.c_str(); //string轉const char*
//		send(sclient, sendData2, strlen(sendData2), 0);
//		
//			
//		char recData[255];
//		int ret = recv(sclient, recData, 255, 0);
//		if (ret > 0)
//		{
//		    recData[ret] = 0x00;
//			printf(recData);
//			printf("\n");
//		}
//		closesocket(sclient);
//	}
//	WSACleanup();
//	return 0;
//}
