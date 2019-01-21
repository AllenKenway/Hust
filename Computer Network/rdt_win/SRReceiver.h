#ifndef STOP_WAIT_RDT_RECEIVER_H
#define STOP_WAIT_RDT_RECEIVER_H
#include "RdtReceiver.h"
#include <vector>
class SRReceiver :public RdtReceiver
{
private:
	int base;				   // �ڴ��յ�����һ���������
	int expectSequenceNumberRcvd;	
	Packet AckPkt;				//�ϴη��͵�ȷ�ϱ���

	const int N;
	const int size;	  
	vector<Packet> buff;


public:
	SRReceiver();
	virtual ~SRReceiver();

public:

	void receive(Packet &packet);	//���ձ��ģ�����NetworkService����
	bool between(int acknum);
};

#endif

