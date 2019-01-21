#pragma once
#include "config.h"
#include <winsock2.h>
#include <list>
#include <string>
#include <map>
#include <vector>
#include <thread>
#include <fstream>
#include "ui_httpserver.h"
using namespace std;

//������
class Server
{
//    Q_OBJECT
//signals:
//    void send2ui(string msg);
public:
    sockaddr_in srvAddr;		//��������IP��ַ
    SOCKET srvSocket;			//������socket
private:

    char* recvBuf;				//���ܻ�����
    fd_set rfds;				//���ڼ��socket�Ƿ������ݵ����ĵ��ļ�������������socket������ģʽ�µȴ������¼�֪ͨ�������ݵ�����
    fd_set wfds;				//���ڼ��socket�Ƿ���Է��͵��ļ�������������socket������ģʽ�µȴ������¼�֪ͨ�����Է������ݣ�

    list<SOCKET> *sessions;							//��ǰ�ĻỰsocket����
    list<SOCKET> *closedSessions;					//������ʧЧ�ĻỰsocket����
    list<string> *rcvedMessages;					//�ѽ��յ��Ŀͻ�����Ϣ����
    int numOfSocketSignaled;						//�ɶ���д������������socket����
protected:

    virtual void AddRecvMessage(string str);								//���յ��Ŀͻ�����Ϣ���浽��Ϣ����
    virtual void AddSession(SOCKET session);								//���µĻỰsocket�������
    virtual void AddClosedSession(SOCKET session);							//��ʧЧ�ĻỰsocket�������
    virtual void RemoveClosedSession(SOCKET closedSession);					//��ʧЧ��SOCKET�ӻỰsocket����ɾ��
    virtual void RemoveClosedSession();										//��ʧЧ��SOCKET�ӻỰsocket����ɾ��
    virtual void ForwardMessage();											//�������ͻ�ת����Ϣ
    virtual void recvMessage(SOCKET s, string path);										//��SOCKET s������Ϣ
    virtual void sendMessage(SOCKET s, string msg);							//��SOCKET s������Ϣ
    virtual sockaddr_in  GetClientAddress(SOCKET s);								//�õ��ͻ���IP��ַ
    virtual void  ReceieveMessageFromClients(string path);								//���ܿͻ��˷�������Ϣ
    virtual int AcceptRequestionFromClient();								//�ȴ��ͻ�����������
public:
    std::thread::id threadid;//�߳�id
    Server(void);
    virtual ~Server(void);
    virtual int WinsockStartup();		//��ʼ��Winsock
    virtual int ServerStartup(int port,string ip);		//��ʼ��Server����������SOCKET���󶨵�IP��PORT
    virtual int ListenStartup();		//��ʼ�����ͻ�������
    virtual int Loop(string path);					//ѭ��ִ��"�ȴ��ͻ�������"->���������ͻ�ת����Ϣ��->"�ȴ��ͻ�����Ϣ"
};
