#include "stdafx.h"
#include "Global.h"
#include "SRSender.h"


SRSender::SRSender():nextseqnum(0), waitingState(false), N(4), base(0), size(8)
{
}


SRSender::~SRSender()
{
}
//�����ȷ����������������
bool SRSender::getWaitingState() {
	if ((this->nextseqnum - this->base + this->size) % this->size == this->N)
		this->waitingState = true;
	else
		this->waitingState = false;
	return waitingState;
}

void SRSender::print_window() {
	std::cout << "����������ݣ�\n";
	for (vector<Packet>::iterator iter = sndpkt.begin(); iter != sndpkt.end(); iter++)
	{
		pUtils->printPacket("�������ݣ�", (*iter));
	}
	std::cout << "\n";
}

bool SRSender::send(Message &message) {
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
	if(this->base==this->nextseqnum)
		pns->startTimer(SENDER, Configuration::TIME_OUT, this->base);//�������ͷ���һ��packet�Ķ�ʱ��
	pns->sendToNetworkLayer(RECEIVER, packet);								//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�

	sndpkt.push_back(packet);
	this->nextseqnum = (this->nextseqnum + 1) % this->size;
	print_window();
	return true;
}

bool  SRSender::between(int acknum)
{
	if (this->base <= this->nextseqnum)
		return acknum >= this->base && acknum < this->nextseqnum;
	else
		return acknum >= this->base || acknum < this->nextseqnum;
}

void SRSender::receive(Packet &ackPkt) {
	cout << endl << endl;
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	cout << "sender::base::" << this->base << endl;
	cout << "sender::receive::" << ackPkt.acknum << endl;
	cout << "checkSum::" << checkSum << endl;
	cout << "checkSum::" << ackPkt.checksum << endl;
	//���У�����ȷ������ȷ�����=���ͷ��ѷ��Ͳ��ȴ�ȷ�ϵ����ݰ����
	if (checkSum == ackPkt.checksum) 
	{	
		
		if (between(ackPkt.acknum))
		{
			pns->stopTimer(SENDER, this->base);
			vector< Packet>::iterator iter = sndpkt.begin();
			for (; iter != sndpkt.end(); iter++)
			{
				if ((*iter).seqnum == ackPkt.acknum)
				{
					sndpkt.erase(iter);
					break;
				}
			}
			if (this->base == ackPkt.acknum)
			{
				pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);


				this->base = (this->base + 1) % this->size;

				if (!acklist.empty())
				{
					vector< Packet>::iterator iter = acklist.begin();
					cout << "iter->second.acknum::" << (*iter).acknum << endl;
					cout << "sender::base::" << this->base << endl;
					if ((*iter).acknum == this->base)
					{
						cout << "ȷ��֮ǰ��һЩ����" << endl;
						while (iter != acklist.end())
						{
							if ((*iter).acknum != this->base)
							{
								cout << "֮������ݲ�����������֮���ٴ���" << endl;
								break;
							}

							pUtils->printPacket("���ͷ�ͬʱȷ��", (*iter));
							this->base = (this->base + 1) % this->size;
							iter++;

						}
						if (iter != acklist.begin())
							acklist.erase(acklist.begin(), iter);
					}

				}	
			}
			else
			{
				pUtils->printPacket("���ͷ���ȷ�յ�ȷ�ϲ����뻺����", ackPkt);
				vector< Packet>::iterator iter = find(acklist.begin(),acklist.end(),ackPkt);
				if (iter == acklist.end())
					acklist.push_back(ackPkt);
			}

			if (this->base != this->nextseqnum)
				pns->startTimer(SENDER, Configuration::TIME_OUT, this->base);
		}
		else
			pUtils->printPacket("��ack�ѱ����ܹ���", ackPkt);

	}
	else
		pUtils->printPacket("���ͷ�û����ȷ�յ����շ���ACK����,����У�����", ackPkt);
	print_window();
}

void SRSender::timeoutHandler(int seqNum) {
	//Ψһһ����ʱ��,���迼��seqNum
	cout << endl << endl;
	cout << "timeout::" << seqNum << endl;

	vector< Packet >::iterator iter;
	for (iter = sndpkt.begin(); iter != sndpkt.end(); iter++)
	{
		if (iter->seqnum == seqNum)
		{
			pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط����䳬ʱ�ı���", (*iter));
			pns->stopTimer(SENDER, seqNum);										//���ȹرն�ʱ��
			pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);			//�����������ͷ���ʱ��
			pns->sendToNetworkLayer(RECEIVER, (*iter));			//���·������ݰ�
		}
	}
	print_window();
}