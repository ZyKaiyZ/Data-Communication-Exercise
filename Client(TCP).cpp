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
//	//��l��WSA windows�۱a��socket
//	WORD sockVersion = MAKEWORD(2, 2);
//	WSADATA data;
//	if (WSAStartup(sockVersion, &data) != 0)
//	{
//		return 0;
//	}
//	
//	//�ЫثȤ�ݮM���r
//	while (true)
//	{
//	    SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //�Ȥ�ݮM���r
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
//		if (connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR) //�P���wIP�a�}�M�ݤf���A�Ⱥݳs��
//		{
//			printf("connect error !");
//			closesocket(sclient);
//			return 0;
//		}
//		
//		printf("��J�A�Q�ǿ骺�^��G \n");
//		string data;
//		cin >> data;
//	    const char* sendData2;
//		sendData2 = data.c_str(); //string��const char*
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
