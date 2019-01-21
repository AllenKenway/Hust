#include "stdafx.h"
#include "Global.h"
#include "TCPSender.h"


TCPSender::TCPSender() :nextseqnum(0), waitingState(false), N(4), base(0), size(8)
{
	acknums = 0;
}


TCPSender::~TCPSender()
{
}

void TCPSender::print_window() {
	std::cout << "����������ݣ�\n";
	for (vector<Packet>::iterator iter = sndpkt.begin(); iter != sndpkt.end(); iter++)
	{
		pUtils->printPacket("��������", (*iter));
	}
	std::cout << "\n";
}

bool  TCPSender::between(int acknum)
{
	if (this->base <= this->nextseqnum)
		return acknum >= this->base && acknum < this->nextseqnum;
	else
		return acknum >= this->base || acknum < this->nextseqnum;
}

//�����ȷ����������������
bool TCPSender::getWaitingState() {
	if ((this->nextseqnum - this->base + this->size) % this->size == this->N)
		this->waitingState = true;
	else
		this->waitingState = false;
	return waitingState;
}
bool TCPSender::send(Message &message) {
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
		pns->startTimer(SENDER, Configuration::TIME_OUT, 0);//�������ͷ���һ��packet�Ķ�ʱ��
	pns->sendToNetworkLayer(RECEIVER, packet);								//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�

	sndpkt.push_back(packet);
	this->nextseqnum = (this->nextseqnum + 1) % this->size;

	print_window();
	return true;
}

void TCPSender::receive(Packet &ackPkt) {
	cout << endl << endl;
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//���У�����ȷ������ȷ�����=���ͷ��ѷ��Ͳ��ȴ�ȷ�ϵ����ݰ����
	if (checkSum == ackPkt.checksum) {
		cout << "sender::receive::" << ackPkt.acknum << endl;
		

		if (between((ackPkt.acknum - 1 + this->size) % this->size))
		{
			pUtils->printPacket("���ͷ���ȷ�յ�����", ackPkt);
			pns->stopTimer(SENDER, 0);
			this->base = ackPkt.acknum;
			if (!sndpkt.empty())
			{
				vector<Packet>::iterator iter = sndpkt.begin();
				for (; iter != sndpkt.end(); iter++)
				{
					if ((*iter).seqnum == (ackPkt.acknum - 1 + this->size) % this->size)
   					{
						iter++;
						break;
					}
				}
				sndpkt.erase(sndpkt.begin(), iter);
			}
			acknums = 1;

			if(this->base!=this->nextseqnum)
				pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
		}
		else//�����ش�����
		{
			acknums++;
			cout << "��������ACK::" << acknums << endl;
			if (acknums == 3)
			{
				vector<Packet>::iterator iter = sndpkt.begin();
				pUtils->printPacket("�����ش�����δȷ�ϵ�����", (*iter));
				pns->stopTimer(SENDER, 0);
				pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
				pns->sendToNetworkLayer(RECEIVER, (*iter));			//���·������ݰ�	
				acknums = 0;
			}
		}
	}
	else
		pUtils->printPacket("���ͷ�û����ȷ�յ����շ���ACK����,����У�����", ackPkt);
	print_window();
}

void TCPSender::timeoutHandler(int seqNum) {
	//Ψһһ����ʱ��,���迼��seqNum
	acknums = 0;
	cout << endl << endl;
	cout << "timeout::" << seqNum << endl;
	vector<Packet>::iterator iter = sndpkt.begin();
	pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ش�����δȷ�ϵ�����", (*iter));
	pns->stopTimer(SENDER, 0);
	pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
	pns->sendToNetworkLayer(RECEIVER, (*iter));			//���·������ݰ�	

	print_window();
}