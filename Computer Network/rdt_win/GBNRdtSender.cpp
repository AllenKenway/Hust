#include "stdafx.h"
#include "Global.h"
#include "GBNRdtSender.h"



GBNRdtSender::GBNRdtSender() :nextseqnum(0), waitingState(false),N(4),base(0),size(8)
{
}


GBNRdtSender::~GBNRdtSender()
{
}


void GBNRdtSender::print_window() {
	std::cout << "����������ݣ�\n";
	for (vector<Packet>::iterator iter = sndpkt.begin(); iter != sndpkt.end(); iter++)
	{
		pUtils->printPacket("�������ݣ�", (*iter));
	}
	std::cout << "\n";
}
bool  GBNRdtSender::between(int acknum)
{
	if (this->base <= this->nextseqnum)
		return acknum >= this->base && acknum < this->nextseqnum;
	else
		return acknum >= this->base || acknum < this->nextseqnum;
}

//�����ȷ����������������
bool GBNRdtSender::getWaitingState() {
	if ((this->nextseqnum - this->base + this->size) % this->size == this->N)
		this->waitingState = true;
	else
		this->waitingState = false;
	return waitingState;
}

bool GBNRdtSender::send(Message &message) {
	if (this->getWaitingState()) { //���ͷ����ڵȴ�ȷ��״̬
		return false;
	}
	cout << endl << endl;
	Packet packet;
	packet.acknum = -1;//���Ը��ֶ�
	packet.seqnum = this->nextseqnum;
	packet.checksum = 0;
	memcpy(packet.payload, message.data, sizeof(message.data));
	packet.checksum = pUtils->calculateCheckSum(packet);

	pUtils->printPacket("���ͷ����ͱ���", packet);
	if (this->base == this->nextseqnum)
		pns->startTimer(SENDER, Configuration::TIME_OUT, this->base);//�������ͷ���һ��packet�Ķ�ʱ��
	pns->sendToNetworkLayer(RECEIVER, packet);								//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�

	sndpkt.push_back(packet);
	this->nextseqnum = (this->nextseqnum + 1) % this->size;
	print_window();
	return true;
}

void GBNRdtSender::receive(Packet &ackPkt) {
	cout << endl << endl;
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//���У�����ȷ������ȷ�����=���ͷ��ѷ��Ͳ��ȴ�ȷ�ϵ����ݰ����
	if (checkSum == ackPkt.checksum) {
		cout << "sender::receive::" << ackPkt.acknum << endl;
		pns->stopTimer(SENDER,this->base);

		
		if (between(ackPkt.acknum))
		{
			pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
			this->base = (ackPkt.acknum + 1) % this->size;
			if (!sndpkt.empty())
			{
				vector<Packet>::iterator iter = sndpkt.begin();
				for (; iter != sndpkt.end(); iter++)
				{
					if ((*iter).seqnum == ackPkt.acknum)
					{
						iter++;
						break;
					}
				}
				sndpkt.erase(sndpkt.begin(), iter);
			}
		}
		else
			cout << "��ack�ѱ����ܹ���" << endl;

		if (this->base != this->nextseqnum)
			pns->startTimer(SENDER, Configuration::TIME_OUT, this->base);
	}
	print_window();
}

void GBNRdtSender::timeoutHandler(int seqNum) {
	//Ψһһ����ʱ��,���迼��seqNum
	cout << endl << endl;
	cout << "timeout::" << seqNum << endl;
	if (this->base != this->nextseqnum)
	{
		pns->stopTimer(SENDER, this->base);
		pns->startTimer(SENDER, Configuration::TIME_OUT, this->base);
		if(!sndpkt.empty())	
			for (vector< Packet >::iterator iter = sndpkt.begin(); iter != sndpkt.end(); iter++)
			{
				pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط�δ���ͳɹ��ı���", (*iter));
				pns->sendToNetworkLayer(RECEIVER, (*iter));			//���·������ݰ�	
			}
	}
	print_window();
}
