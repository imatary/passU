#ifndef __PACKET_H__
#define __PACKET_H__

typedef struct packet{ // Ű���� Ű ���� ������ �ִ� ��Ŷ(UDP)
   unsigned int sendDev:4;			// ������ ��ġ
   unsigned int recvDev:4;			// �޴� ��ġ
   unsigned int inputDev:1;			// �Է� ��ġ ���� 0: Ű����, 1: ���콺
   unsigned int relativeField:1;	// ��밪 ����
   unsigned int pad:22;				// ����
} PACKET;

typedef struct keypacket{ // Ű���� Ű ���� ������ �ִ� ��Ŷ(UDP)
   unsigned int sendDev:4;			// ������ ��ġ
   unsigned int recvDev:4;			// �޴� ��ġ
   unsigned int inputDev:1;			// �Է� ��ġ ���� 0: Ű����, 1: ���콺
   unsigned int relativeField:1;	// ��밪 ����
   unsigned int keyCode:14;			// Ű�ڵ�
   unsigned int pad:8;				// ����
} KPACKET;
 
typedef struct mousepacket{ // ���콺 ��ġ ������ ������ �ִ� ��Ŷ(UDP)
   unsigned int sendDev:4;			// ������ ��ġ
   unsigned int recvDev:4;			// �޴� ��ġ
   unsigned int inputDev:1;			// �Է� ��ġ ���� 0: Ű����, 1: ���콺
   unsigned int relativeField:1;	// ��밪 ����
   unsigned int xCoord:7;			// x ��ǥ
   unsigned int yCoord:7;			// y ��ǥ
   unsigned int wheel:1;			// �� On/Off
   unsigned int rightmouse:1;		// ������ ���콺 On/Off
   unsigned int leftmouse:1;		// ���� ���콺 On/Off
   unsigned int pad:4;
} MPACKET;


typedef struct clientpacket{ // �� ó�� Connect �� �� Ŭ���̾�Ʈ�� �������� ������ ��Ŷ
	unsigned int ip:17;
	
	/* �� �߰��� �� ������ ����3 */

} CPACKET;

typedef struct serverpacket{ // �� ó�� Connect �� �� ������ Ŭ���̾�Ʈ���� ������ ��Ŷ
	unsigned int position:4;

	/* �� �߰��� �� ������ ����3 */

} SPACKET;

#endif