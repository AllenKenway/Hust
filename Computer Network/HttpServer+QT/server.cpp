#include "server.h"
#include "winsockenv.h"
#include <algorithm>
#include <QString>
#include "httpserver.h"
#include "ui_httpserver.h"


Server::Server(void)
{
    this->recvBuf = new char[Config::BUFFERLENGTH]; //��ʼ�����ܻ�����
    memset(this->recvBuf, '\0', Config::BUFFERLENGTH);

    this->rcvedMessages = new list<string>();
    this->sessions = new list<SOCKET>();
    this->closedSessions = new list<SOCKET>();
}
Server::~Server(void)
{
    //�ͷŽ��ܻ�����
    if (this->recvBuf != NULL) {
        delete this->recvBuf;
        this->recvBuf = NULL;
    }


    //�ر�server socket
    if (this->srvSocket != NULL) {
        closesocket(this->srvSocket);
        this->srvSocket = NULL;
    }

    //�ر����лỰsocket���ͷŻỰ����
    if (this->sessions != NULL) {
        for (list<SOCKET>::iterator itor = this->sessions->begin(); itor != this->sessions->end(); itor++)
            closesocket(*itor); //�رջỰ
        delete this->sessions;  //�ͷŶ���
        this->sessions = NULL;
    }
    //�ͷ�ʧЧ�Ự����
    if (this->closedSessions != NULL) {
        for (list<SOCKET>::iterator itor = this->closedSessions->begin(); itor != this->closedSessions->end(); itor++)
            closesocket(*itor); //�رջỰ
        delete this->closedSessions;//�ͷŶ���
        this->closedSessions = NULL;
    }

    //�ͷŽ�����Ϣ����
    if (this->rcvedMessages != NULL) {
        this->rcvedMessages->clear(); //�����Ϣ�����е���Ϣ
        delete this->rcvedMessages;	// �ͷ���Ϣ����
        this->rcvedMessages = NULL;
    }


    WSACleanup(); //����winsock ���л���
}

//��ʼ��Winsock
int Server::WinsockStartup() {
    if (WinsockEnv::Startup() == -1) return -1;	//��ʼ��Winsock
    return 0;
}

//��ʼ��Server����������sockect���󶨵�IP��PORT
int Server::ServerStartup(int PORT,string SERVERADDRESS) {
    //���� TCP socket
    int id;
    this->srvSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->srvSocket == INVALID_SOCKET) {
        qDebug() << "Server socket creare error ! [WSAGetLastError :" << id << "]";
        WSACleanup();
        return -1;
    }
   qDebug()<< "Server socket create ok!\n";

    //���÷�����IP��ַ�Ͷ˿ں�
    this->srvAddr.sin_family = AF_INET;
    this->srvAddr.sin_port = htons(u_short(PORT));
    this->srvAddr.sin_addr.S_un.S_addr = inet_addr(SERVERADDRESS.c_str()); //��������һ������IP��ַ�ķ���

    //�� socket to Server's IP and port
    int rtn = ::bind(this->srvSocket, (LPSOCKADDR)&(this->srvAddr), sizeof(this->srvAddr));
    if (rtn == SOCKET_ERROR) {
        qDebug()<< "Server socket bind error! [WSAGetLastError :" << id << "]";
        closesocket(this->srvSocket);
        WSACleanup();
        return -1;
    }
    qDebug() << "Server socket bind ok!\n";
    return 0;
}

//��ʼ����,�ȴ��ͻ�����������
int Server::ListenStartup() {
    int rtn = listen(this->srvSocket, Config::MAXCONNECTION);
    if (rtn == SOCKET_ERROR) {
        qDebug("Server socket listen error ! ");
        closesocket(this->srvSocket);
        WSACleanup();
        return -1;
    }
    qDebug("Server socket listen ok!\n");
    return 0;
}

//���յ��Ŀͻ�����Ϣ���浽��Ϣ����
void Server::AddRecvMessage(string str) {
    if (!str.empty())
        this->rcvedMessages->insert(this->rcvedMessages->end(), str);

}

//���µĻỰSOCKET�������
void Server::AddSession(SOCKET session) {
    if (session != INVALID_SOCKET) {
        this->sessions->insert(this->sessions->end(), session);
    }
}

//��ʧЧ�ĻỰSOCKET�������
void Server::AddClosedSession(SOCKET session) {
    if (session != INVALID_SOCKET) {
        this->closedSessions->insert(this->closedSessions->end(), session);
    }
}

//��ʧЧ��SOCKET�ӻỰSOCKET����ɾ��
void Server::RemoveClosedSession(SOCKET closedSession) {
    if (closedSession != INVALID_SOCKET) {
        list<SOCKET>::iterator itor = find(this->sessions->begin(), this->sessions->end(), closedSession);
        if (itor != this->sessions->end())
            this->sessions->erase(itor);
    }
}

//��ʧЧ��SOCKET�ӻỰSOCKET����ɾ��
void Server::RemoveClosedSession() {
    for (list<SOCKET>::iterator itor = this->closedSessions->begin(); itor != this->closedSessions->end(); itor++) {
        this->RemoveClosedSession(*itor);
    }
}

//��SOCKET s������Ϣ
void Server::recvMessage(SOCKET socket,string PATH) {
    sockaddr_in clientAddr = GetClientAddress(socket);

    int receivedBytes = recv(socket, this->recvBuf, Config::BUFFERLENGTH, 0);
    if (receivedBytes == SOCKET_ERROR || receivedBytes == 0) {//�������ݴ��󣬰Ѳ�������ĻỰsocekt����sessionsClosed����
        this->AddClosedSession(socket);
        qDebug() <<inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << " to "
            << inet_ntoa(this->srvAddr.sin_addr) << ":" << ntohs(this->srvAddr.sin_port) << ": failed to receive data." << endl;
    }
    else {
        recvBuf[receivedBytes] = '\0';
        recvBuf[receivedBytes] = '\0';

        qDebug() << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << " to " <<
            inet_ntoa(this->srvAddr.sin_addr) << ":" << ntohs(this->srvAddr.sin_port)<< recvBuf << endl;
        string remsg = "", head = "";
        Config::recvBuf_remsg(recvBuf, head, remsg,PATH); //����HTTP�����Ĳ������Ӧ����


        qDebug() << inet_ntoa(this->srvAddr.sin_addr) << ":" << ntohs(this->srvAddr.sin_port) <<
            " to " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << ":" << head.c_str() << endl;
        if (remsg != "")
            this->AddRecvMessage(remsg); //���յ�����Ϣ���뵽��Ϣ����
        memset(this->recvBuf, '\0', Config::BUFFERLENGTH);//������ܻ�����
    }
}

//��SOCKET s������Ϣ
void Server::sendMessage(SOCKET socket, string msg) {
    int rtn = send(socket, msg.c_str(), msg.size(), 0);
    if (rtn == SOCKET_ERROR) {//�������ݴ��󣬰Ѳ�������ĻỰsocekt����sessionsClosed����

        sockaddr_in clientAddr = GetClientAddress(socket);
        int id = WSAGetLastError();
        qDebug() << "[WSAGetLastError:" << id << "]"<< "Send to client failed."
            << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << " leave." << endl;
        this->AddClosedSession(socket);
    }
}

//�������ͻ�ת����Ϣ
void Server::ForwardMessage()
{
    if (this->numOfSocketSignaled > 0)
    {
        if (!this->rcvedMessages->empty())
        {//�����Ϣ���в�Ϊ��
            for (list<string>::iterator msgItor = this->rcvedMessages->begin(); msgItor != this->rcvedMessages->end(); msgItor++)
            {//����Ϣ�����е�ÿһ����Ϣ
                for (list<SOCKET>::iterator sockItor = this->sessions->begin(); sockItor != this->sessions->end(); sockItor++)
                {//�ԻỰsocket�����е�ÿ��socket
                    if (FD_ISSET(*sockItor, &this->wfds)) {
                        this->sendMessage(*sockItor, *msgItor);
                    }
                }
            }
        }
        this->rcvedMessages->clear(); //�������ͻ�ת����Ϣ�������Ϣ����
    }
}


int Server::AcceptRequestionFromClient() {
    sockaddr_in clientAddr;		//�ͻ���IP��ַ
    int nAddrLen = sizeof(clientAddr);
    u_long blockMode = Config::BLOCKMODE;//��session socket��Ϊ������ģʽ�Լ����ͻ���������

    //���srvSocket�Ƿ��յ��û���������
    if (this->numOfSocketSignaled > 0) {
        if (FD_ISSET(this->srvSocket, &rfds)) {  //�пͻ�����������
            this->numOfSocketSignaled--;

            //�����Ựsocket
            SOCKET newSession = accept(this->srvSocket, (LPSOCKADDR)&(clientAddr), &nAddrLen);
            if (newSession == INVALID_SOCKET) {
                qDebug() << "Server accept connection request error!\n";
                return -1;
            }
            qDebug() << "New client connection request arrived and new session created\n";

                        //���µĻỰsocket��Ϊ������ģʽ��
            if (ioctlsocket(newSession, FIONBIO, &blockMode) == SOCKET_ERROR) {
                qDebug() << "ioctlsocket() for new session failed with error!\n";
                return -1;
            }

            //���µ�session����Ự����
            this->AddSession(newSession);

            sockaddr_in clientAddr;
            int nameLen, rtn;
            nameLen = sizeof(clientAddr);
            rtn = getpeername(newSession, (LPSOCKADDR)&clientAddr, &nameLen);

            qDebug() << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << " connect to "
                << inet_ntoa(this->srvAddr.sin_addr) << ":" << ntohs(this->srvAddr.sin_port) << "!" << endl;
        }
    }
    return 0;
}

void Server::ReceieveMessageFromClients(string PATH) {
    if (this->numOfSocketSignaled > 0) {
        //�����Ự�б��е�����socket������Ƿ������ݵ���
        for (list<SOCKET>::iterator itor = this->sessions->begin(); itor != this->sessions->end(); itor++) {
            if (FD_ISSET(*itor, &rfds)) {  //ĳ�Ựsocket�����ݵ���
                //��������
                this->recvMessage(*itor,PATH);
            }
        }//end for
    }
}

//�õ��ͻ���IP��ַ
sockaddr_in  Server::GetClientAddress(SOCKET s) {
    sockaddr_in clientAddr;
    int nameLen, rtn;

    nameLen = sizeof(clientAddr);
    rtn = getpeername(s, (LPSOCKADDR)&clientAddr, &nameLen);
    if (rtn != SOCKET_ERROR) {
        return clientAddr;
    }
}

//���ܿͻ��˷�������������ݲ�ת��
int Server::Loop(string PATH) {
    u_long blockMode = Config::BLOCKMODE;//��srvSock��Ϊ������ģʽ�Լ����ͻ���������
    int rtn;

    if ((rtn = ioctlsocket(this->srvSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO��������ֹ�׽ӿ�s�ķ�����ģʽ��
        int id = WSAGetLastError();
        qDebug() << "[WSAGetLastError:" << id << "]" << "ioctlsocket() failed with error!\n";
        return -1;
    }
    qDebug() << "ioctlsocket() for server socket ok!Waiting for client connection and data\n";
    while (true) { //�ȴ��ͻ�����������
        //���ȴӻỰSOCKET������ɾ�����Ѿ��رյĻỰsocket
        this->RemoveClosedSession();

        //Prepare the read and write socket sets for network I/O notification.
        FD_ZERO(&this->rfds);
        FD_ZERO(&this->wfds);

        //��srvSocket���뵽rfds���ȴ��û���������
        FD_SET(this->srvSocket, &this->rfds);

        //�ѵ�ǰ�ĻỰsocket���뵽rfds,�ȴ��û����ݵĵ���;�ӵ�wfds���ȴ�socket�ɷ�������
        for (list<SOCKET>::iterator itor = this->sessions->begin(); itor != this->sessions->end(); itor++) {
            FD_SET(*itor, &rfds);
            FD_SET(*itor, &wfds);
        }

        //�ȴ��û�����������û����ݵ�����Ựsocke�ɷ�������
        if ((this->numOfSocketSignaled = select(0, &this->rfds, &this->wfds, NULL, NULL)) == SOCKET_ERROR) { //select���������пɶ����д��socket��������������rtn��.���һ�������趨�ȴ�ʱ�䣬��ΪNULL��Ϊ����ģʽ
            int id = WSAGetLastError();
            qDebug() << "[WSAGetLastError:" << id << "]" << "select() failed with error!\n";
            return -1;
        }


        //���������е������ζ�����û������������������û����ݵ��������лỰsocket���Է�������

        //���ȼ���Ƿ��пͻ��������ӵ���
        if (this->AcceptRequestionFromClient() != 0) return -1;

        //Ȼ����ͻ��˷�������
        this->ForwardMessage();

        //�����ܿͻ��˷���������
        this->ReceieveMessageFromClients(PATH);
    }

    return 0;
}
