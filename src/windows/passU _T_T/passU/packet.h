#ifndef __PACKET_H__
#define __PACKET_H__

#pragma pack(1)
/*
#define STATUS_EMPTY	0
#define STATUS_PC		1
#define STATUS_MOBILE	2
*/

typedef struct packet{
	int msgType; // msgType : 1
	int sendDev; // id
	int recvDev; // first
	int deviceType;
	int relativeField;
	int updownFlag;
	int keyCode;
	int pad1;
	int pad2;
	int pad3;
	int pad4;
} PACKET;
typedef struct keypacket{ // Ű���� Ű ���� ������ �ִ� ��Ŷ(TCP)
	int msgType; // msgType : 1
	int sendDev; // id
	int recvDev; // first
	int deviceType;
	int relativeField;
	int updownFlag;
	int keyCode;
	int pad1;
	int pad2;
	int pad3;
	int pad4;
} KPACKET;

typedef struct mousepacket{ // ���콺 ��ġ ������ ������ �ִ� ��Ŷ(TCP)
	int msgType; // msgType : 2
	int sendDev;
	int recvDev;
	int deviceType;
	int relativeField;
	int updownFlag; // 0 : up, 1 : down
	int leftRight; // 0 : left , 1 : right
	int wheelFlag; // 0 : wheel off, 1 : wheel on 2 : wheel move
	int xCoord;
	int yCoord;
} MPACKET;

typedef struct c_packet{ // Ŭ���̾�Ʈ���� �� ��Ŷ
	int msgType; // msgType : 3
	int c_id; // Ŭ���̾�Ʈ ID
	int pad3; // � device����. Computer : 1 // Android : 2
	int hello; // Hello ��Ŷ
	int bye; // bye ��Ŷ
	int ipFirst;
	int ipSecond;
	int ipThird;
	int ipForth;
} CPACKET;

typedef struct dataPacket{ // ������ ���� �� �� ��Ŷ
	int msgType; // msgtype : 4
	int len; // data length
	unsigned char data[1024]; // data
} DPACKET;

#endif 