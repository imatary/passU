#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include "packet.h"
#pragma comment(lib, "ws2_32.lib")

#define BUFSIZE 512

void err_msg(const char *msg, bool option){
	LPVOID lpMsgBuf;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER|
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);


	if(option){
		MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
		LocalFree(lpMsgBuf);
		exit(-1);
	} else{
		printf("[%s] %s", msg, lpMsgBuf);
		LocalFree(lpMsgBuf);
	}
}

int main(void){

	int retval = 0;
	char serverIP[25];
	int serverPort = 0;
	KPACKET kp;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;


	// socket(UDP)
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if( sock == INVALID_SOCKET) err_msg("socket()", TRUE);

	// ip �ּ� �Է¹ޱ�
	printf("Server IP �ּ� : ");
	scanf("%s\n", serverIP);

	// ���� �ּ� ����ü �ʱ�ȭ

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9501);
	serveraddr.sin_addr.s_addr = inet_addr(serverIP); // ���� IP �ּ�a

	//connect()
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if( retval == SOCKET_ERROR ) err_msg("connect()", TRUE);

	// ������ ��ſ� ����� ����
	SOCKADDR_IN peeraddr;
	int addrlen;
	char buf[BUFSIZE + 1];
	char msg[BUFSIZE + 1];
	int len;


	ZeroMemory(buf, sizeof(buf));




	// Ŭ���̾�Ʈ�� ������ ���

	while(1){

		// ���� ������ �Է�
		printf("\n[���� ������] ");
		if(fgets(msg, BUFSIZE + 1 , stdin) == NULL)
			break;

		// \n ���� ����
		len = strlen(msg);
		if(msg[len - 1] == '\n')
			msg[len - 1] = '\0';
		if(strlen(msg) == 0)
			break;
		kp.inputDev = 0;
		kp.keyCode = 1231;
		kp.recvDev = 5;
		kp.sendDev = 1;
		kp.relativeField = 0;

		strcpy(buf, (char *)&kp);

		// ������ ������
		retval = sendto(sock, buf, strlen(buf), 0, (sockaddr *)&serveraddr, sizeof(serveraddr));
		if(retval == SOCKET_ERROR){
			err_msg("sendto() error!", false);
			continue;
		}

		// ������ �ޱ�
		addrlen = sizeof(peeraddr);
		retval = recvfrom(sock, buf, BUFSIZE, 0, (sockaddr *)&peeraddr, &addrlen);

		if(retval == SOCKET_ERROR){
			err_msg("recvfrom()", FALSE);
			continue;
		}

		// �۽��� IP üũ
		if(memcmp(&peeraddr, &serveraddr, sizeof(peeraddr))){
			printf("[����] �߸��� �������Դϴ�!\n");
			continue;
		}

		kp = *(KPACKET *)buf;

		//���� ������ ���
		buf[retval] = '\0';
		printf("[UDP Ŭ���̾�Ʈ] %d ����Ʈ�� �޾ҽ��ϴ�. \n", retval);
		printf("%d, %d, %d, %d, %d\n", kp.inputDev, kp.keyCode, kp.recvDev, kp.relativeField, kp.sendDev);

		//printf("[���� ������] %s\n", buf);


	}

	closesocket(sock);

	WSACleanup();

	return 0;

}






