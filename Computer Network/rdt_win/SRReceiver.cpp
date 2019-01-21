#include "stdafx.h"
#include "Global.h"
#include "SRReceiver.h"


SRReceiver::SRReceiver():size(8),N(4),base(0)
{
	AckPkt.acknum = -1; //��ʼ״̬�£��ϴη��͵�ȷ�ϰ���ȷ�����Ϊ-1��ʹ�õ���һ�����ܵ����ݰ�����ʱ��ȷ�ϱ��ĵ�ȷ�Ϻ�Ϊ-1
	AckPkt.checksum = 0;
	AckPkt.seqnum = -1;	//���Ը��ֶ�
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
		AckPkt.payload[i] = '.';
	}
	AckPkt.checksum = pUtils->calculateCheckSum(AckPkt);
}


SRReceiver::~SRReceiver()
{
}

bool SRReceiver::between(int acknum)
{
	int nextseqnum = (this->base + 4) % this->size;
	if (this->base <= nextseqnum)
		return acknum >= this->base && acknum < nextseqnum;
	else
		return acknum >= this->base || acknum < nextseqnum;
}

void SRReceiver::receive(Packet &packet) {
	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(packet);
	cout << endl << endl;
	cout << "receiver::base::" << this->base << endl;
	cout << "receiver::packet.seqnum::" << packet.seqnum << endl;
	cout << "checkSum::" << checkSum << endl;
	cout << "checkSum::" << packet.checksum << endl;
	//���У�����ȷ��ͬʱ�յ����ĵ���ŵ��ڽ��շ��ڴ��յ��ı������һ��
	if (checkSum == packet.checksum)
	{
		if (this->base != packet.seqnum)
		{
			if (between(packet.seqnum))
			{
				pUtils->printPacket("���շ���ȷ�յ����ͷ��ı���,�����뻺����", packet);
				vector< Packet >::iterator iter;
				iter = find(buff.begin(), buff.end(), packet);
				if (iter == buff.end())
					buff.push_back(packet);
			}
			else
				pUtils->printPacket("�ð����ѽ��ܹ�", packet);
			AckPkt.acknum = packet.seqnum; //ȷ����ŵ����յ��ı������
			AckPkt.seqnum = 0;
			AckPkt.checksum = 0;
			AckPkt.checksum = pUtils->calculateCheckSum(AckPkt);
			pUtils->printPacket("���շ�����ȷ�ϱ���", AckPkt);
			pns->sendToNetworkLayer(SENDER, AckPkt);	//����ģ�����绷����sendToNetworkLayer��ͨ������㷢��ȷ�ϱ��ĵ��Է�
		}
		else
		{
			pUtils->printPacket("���շ���ȷ�յ����ͷ��ı���", packet);


			//ȡ��Message�����ϵݽ���Ӧ�ò�
			Message msg;
			memcpy(msg.data, packet.payload, sizeof(packet.payload));
			pns->delivertoAppLayer(RECEIVER, msg);
			this->base = (this->base + 1) % this->size;

			if (!buff.empty())
			{
				vector< Packet >::iterator iter = buff.begin();
				cout << "iter->second.seqnum::" << (*iter).seqnum << endl;
				cout << "receiver::base::" << this->base << endl;
				if ((*iter).seqnum == this->base)
				{
					cout << "���ϴ���֮ǰ��һЩ����" << endl;
					while (iter != buff.end())
					{
						
						if ((*iter).seqnum != this->base)
						{
							cout << "֮������ݲ�����������֮���ٴ���" << endl;
							break;
						}
							
						//ȡ��Message�����ϵݽ���Ӧ�ò�
						Message msg;
						memcpy(msg.data, (*iter).payload, sizeof((*iter).payload));
						pns->delivertoAppLayer(RECEIVER, msg);
						this->base = (this->base + 1) % this->size;

						iter++;

					}
					buff.erase(buff.begin(), iter);
				}

			}


			AckPkt.acknum = packet.seqnum; //ȷ����ŵ����յ��ı������
			AckPkt.seqnum = 0;
			AckPkt.checksum = 0;
			AckPkt.checksum = pUtils->calculateCheckSum(AckPkt);
			pUtils->printPacket("���շ�����ȷ�ϱ���", AckPkt);
			pns->sendToNetworkLayer(SENDER, AckPkt);	//����ģ�����绷����sendToNetworkLayer��ͨ������㷢��ȷ�ϱ��ĵ��Է�

		}

	}
	else {
		if (checkSum != packet.checksum) {
			pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı���,����У�����", packet);
		}
		else {
			pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı���,������Ų���", packet);
		}
	}

}
