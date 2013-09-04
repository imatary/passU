#ifndef __PACKET_H__
#define __PACKET_H__

#pragma pack(1)
/*
#define STATUS_EMPTY	0
#define STATUS_PC		1
#define STATUS_MOBILE	2
*/

typedef struct packet{
	int msgType:32; // msgType : 1
	int sendDev:32; // id
	int recvDev:32; // first
	int deviceType:8;
	int relativeField:8;
	int updownFlag:8;
	int keyCode:32;
	int pad1:8;
	int pad2:32;
	int pad3:32;
	int pad4:32;
} PACKET;
typedef struct keypacket{ // Ű���� Ű ���� ������ �ִ� ��Ŷ(TCP)
	int msgType:32; // msgType : 1
	int sendDev:32; // id
	int recvDev:32; // first
	int deviceType:8;
	int relativeField:8;
	int updownFlag:8;
	int keyCode:32;
	int pad1:8;
	int pad2:32;
	int pad3:32;
	int pad4:32;
} KPACKET;

typedef struct mousepacket{ // ���콺 ��ġ ������ ������ �ִ� ��Ŷ(TCP)
	int msgType:32; // msgType : 2
	int sendDev:32;
	int recvDev:32;
	int deviceType:8;
	int relativeField:8;
	int updownFlag:8; // 0 : up, 1 : down
	int leftRight:8; // 0 : left , 1 : right
	int wheelFlag:32; // 0 : wheel off, 1 : wheel on 2 : wheel move
	int xCoord:32;
	int yCoord:32;
	int pad:32;
} MPACKET;

typedef struct c_packet{ // Ŭ���̾�Ʈ���� �� ��Ŷ
	int msgType:32; // msgType : 3
	int c_id:32; // Ŭ���̾�Ʈ ID
	int pad3:32; // � device����. Computer : 1 // Android : 2
	int hello:8; // Hello ��Ŷ
	int bye:8; // bye ��Ŷ
	int pad4:8;
	int pad5:8;
	int pad6:32;
	int pad7:32;
	int pad8:32;
	int pad9:32;
} CPACKET;

typedef struct dataPacket{ // ������ ���� �� �� ��Ŷ
	int msgType:32; // msgtype : 4
	int len:32; // data length
	unsigned char data[1024]; // data
} DPACKET;

#endif 