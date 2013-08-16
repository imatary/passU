#ifndef __PACKET_H__
#define __PACKET_H__

typedef struct keypacket{ // Ű���� Ű ���� ������ �ִ� ��Ŷ(UDP)
   int sendDev:32;			// ������ ����̽� ��ġ
   int recvDev:32;			// �޴� ����̽� ��ġ
   int deviceType:8;		// 0: Ű���� 1: ���콺
   int relativeField:8;		// ó�� ������ ��ȣ ����
   int updownFlag:8;		// �� 1 �ٿ� 0
   int keyCode:32;			// Ű �ڵ�
   int pad1:32;
   int pad2:32;
   int pad3:6;
} KPACKET;
 
typedef struct mousepacket{ // ���콺 ��ġ ������ ������ �ִ� ��Ŷ(UDP)
   int sendDev:32;			// ������ ����̽� ��ġ
   int recvDev:32;			// �޴� ����̽� ��ġ
   int deviceType:8;		// 0: Ű���� 1: ���콺
   int relativeField:8;		// ó�� ������ ��ȣ ����
   int updownFlag:8;		// �� 1 �ٿ� 0
   int wheelFlag:8;			// �� ����
   int xCoord:32;			// x ��ġ
   int yCoord:32;			// y ��ġ
   int pad:32;
} MPACKET;

#endif	/* ifndef __PACKET_H__ */