#ifndef STOP_WAIT_RDT_SENDER_H
#define STOP_WAIT_RDT_SENDER_H
#include "RdtSender.h"
#include <vector>
#include <map>
class TCPSender :public RdtSender
{
private:
	int nextseqnum;	// ��һ��������� 
	bool waitingState;				// �Ƿ��ڵȴ�Ack��״̬
	//Packet packetWaitingAck;		
	int base;
	const int N;
	const int size;
	vector<Packet> sndpkt;   //�ѷ��Ͳ��ȴ�Ack�����ݰ�
	
	int acknums;
public:

	bool getWaitingState();
	bool send(Message &message);						//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	void receive(Packet &ackPkt);						//����ȷ��Ack������NetworkServiceSimulator����	
	void timeoutHandler(int seqNum);					//Timeout handler������NetworkServiceSimulator����

public:
	TCPSender();
	virtual ~TCPSender();
	bool between(int);
	void print_window();
};

#endif