typedef struct keypacket{ // Ű���� Ű ���� ������ �ִ� ��Ŷ(UDP)
	unsigned int sendDev:4;
	unsigned int recvDev:4;
	unsigned int inputDev:1;
	unsigned int relativeField:1;
	unsigned int keyCode:14;
} KPACKET;

typedef struct mousepacket{ // ���콺 ��ġ ������ ������ �ִ� ��Ŷ(UDP)
	unsigned int sendDev:4;
	unsigned int recvDev:4;
	unsigned int inputDev:1;
	unsigned int relativeField:1;
	unsigned int xCoord:7;
	unsigned int yCoord:7;
} MPACKET;

typedef struct clientpacket{ // �� ó�� Connect �� �� Ŭ���̾�Ʈ�� �������� ������ ��Ŷ
	unsigned int ip:17;
	
	/* �� �߰��� �� ������ ����3 */

} CPACKET;

typedef struct serverpacket{ // �� ó�� Connect �� �� ������ Ŭ���̾�Ʈ���� ������ ��Ŷ
	unsigned int position:4;

	/* �� �߰��� �� ������ ����3 */

} SPACKET;