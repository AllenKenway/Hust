#pragma once
#include <iostream>
#include <string>
#include "Server.h"
#include "WinsockEnv.h"
#include "Config.h"
#include <winsock2.h>
#include <algorithm>
#include <vector>
#include <fstream>
#pragma comment(lib, "Ws2_32.lib")

#pragma warning(disable:4996)


//��
#include<mutex>
#include<condition_variable>

std::condition_variable cond;
std::mutex print_mutex;
int flag = 0;

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
	if (WinsockEnv::Startup(this->threadid) == -1) return -1;	//��ʼ��Winsock
	return 0;
}

//��ʼ��Server����������sockect���󶨵�IP��PORT
int Server::ServerStartup(int PORT,string SERVERADDRESS) {
	//���� TCP socket
	int id;
	this->srvSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->srvSocket == INVALID_SOCKET) {
		id = WSAGetLastError();
		printf("[Thread_id��%d][WSAGetLastError :%d]erver socket creare error ! ", this->threadid,id);
		WSACleanup();
		return -1;
	}
	printf("[Thread_id��%d]Server socket create ok!\n",this->threadid);

	//���÷�����IP��ַ�Ͷ˿ں�
	this->srvAddr.sin_family = AF_INET;
	this->srvAddr.sin_port = htons(PORT);
	this->srvAddr.sin_addr.S_un.S_addr = inet_addr(SERVERADDRESS.c_str()); //��������һ������IP��ַ�ķ���

	//�� socket to Server's IP and port
	int rtn = ::bind(this->srvSocket, (LPSOCKADDR)&(this->srvAddr), sizeof(this->srvAddr));
	if (rtn == SOCKET_ERROR) {
		id = WSAGetLastError();
		printf("[Thread_id��%d][WSAGetLastError :%d]Server socket bind error ! ", this->threadid, id);
		closesocket(this->srvSocket);
		WSACleanup();
		return -1;
	}
	printf("[Thread_id��%d]Server socket bind ok!\n", this->threadid);
	return 0;
}

//��ʼ����,�ȴ��ͻ�����������
int Server::ListenStartup() {
	int rtn = listen(this->srvSocket, Config::MAXCONNECTION);
	if (rtn == SOCKET_ERROR) {
		int id = WSAGetLastError();
		printf("[Thread_id��%d][WSAGetLastError :%d]erver socket listen error ! ", this->threadid, id);
		closesocket(this->srvSocket);
		WSACleanup();
		return -1;
	}
	printf("[Thread_id��%d]Server socket listen ok!\n", this->threadid);
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
int Server::recvMessage(SOCKET socket,string PATH) {
	sockaddr_in clientAddr = GetClientAddress(socket);

	int receivedBytes = recv(socket, this->recvBuf, Config::BUFFERLENGTH, 0);
	if (receivedBytes == SOCKET_ERROR || receivedBytes == 0) {//�������ݴ��󣬰Ѳ�������ĻỰsocekt����sessionsClosed����
		this->AddClosedSession(socket);
		int id = WSAGetLastError();
		printf("[Thread_id��%d][WSAGetLastError:%d]%s:%d to %s:%d : failed to receive data.\n",
			this->threadid, id, inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), inet_ntoa(this->srvAddr.sin_addr), ntohs(this->srvAddr.sin_port));

	}
	else {
		recvBuf[receivedBytes] = '\0';
		printf("[Thread_id��%d]\n%s:%d to %s:%d : %s\n",this->threadid,inet_ntoa(clientAddr.sin_addr), 
			ntohs(clientAddr.sin_port), inet_ntoa(this->srvAddr.sin_addr), ntohs(this->srvAddr.sin_port),recvBuf);


		string remsg = "";
		string head = "";
		if (Config::recvBuf_remsg(recvBuf, head, remsg, PATH) == -1) //����HTTP�����Ĳ������Ӧ����
		{
			printf("[Thread_id��%d]%s:%d has closed!\n", this->threadid, inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
			return -1;
		}


		printf("[Thread_id��%d]\n%s:%d to %s:%d : %s\n", this->threadid,inet_ntoa(this->srvAddr.sin_addr), 
			ntohs(this->srvAddr.sin_port), inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), head.c_str());

		if (remsg != "")
			this->AddRecvMessage(remsg); //���յ�����Ϣ���뵽��Ϣ����
		memset(this->recvBuf, '\0', Config::BUFFERLENGTH);//������ܻ�����
	}
	return 0;
}

//��SOCKET s������Ϣ
void Server::sendMessage(SOCKET socket, string msg) {
	int rtn = send(socket, msg.c_str(), msg.length(), 0);
	if (rtn == SOCKET_ERROR) {//�������ݴ��󣬰Ѳ�������ĻỰsocekt����sessionsClosed����
		int id = WSAGetLastError();
		sockaddr_in clientAddr = GetClientAddress(socket);
		printf("[Thread_id��%d][WSAGetLastError:%d]Send to client failed.%s:%d  leave.\n", this->threadid, id,
			inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

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
	int id;

	//���srvSocket�Ƿ��յ��û���������
	if (this->numOfSocketSignaled > 0) {
		if (FD_ISSET(this->srvSocket, &rfds)) {  //�пͻ�����������
			this->numOfSocketSignaled--;

			//�����Ựsocket
			SOCKET newSession = accept(this->srvSocket, (LPSOCKADDR)&(clientAddr), &nAddrLen);
			if (newSession == INVALID_SOCKET) {
				id = WSAGetLastError();
				printf("[Thread_id��%d][WSAGetLastError:%d]Server accept connection request error!\n", this->threadid, id);
				return -1;
			}
			id = WSAGetLastError();
			printf("[Thread_id��%d]New client connection request arrived and new session created\n", this->threadid);

			//���µĻỰsocket��Ϊ������ģʽ��
			if (ioctlsocket(newSession, FIONBIO, &blockMode) == SOCKET_ERROR) {
				id = WSAGetLastError();
				printf("[Thread_id��%d][WSAGetLastError:%d]ioctlsocket() for new session failed with error!\n", this->threadid, id);
				return -1;
			}

			//���µ�session����Ự����
			this->AddSession(newSession);

			sockaddr_in clientAddr;
			int nameLen, rtn;
			nameLen = sizeof(clientAddr);
			rtn = getpeername(newSession, (LPSOCKADDR)&clientAddr, &nameLen);
			printf("[Thread_id��%d]%s:%d connect to %s:%d : %s !\n", this->threadid, inet_ntoa(clientAddr.sin_addr),
				ntohs(clientAddr.sin_port), inet_ntoa(this->srvAddr.sin_addr), ntohs(this->srvAddr.sin_port), recvBuf);
		}
	}
	return 0;
}

int Server::ReceieveMessageFromClients(string PATH) {
	if (this->numOfSocketSignaled > 0) {
		//�����Ự�б��е�����socket������Ƿ������ݵ���
		for (list<SOCKET>::iterator itor = this->sessions->begin(); itor != this->sessions->end(); itor++) {
			if (FD_ISSET(*itor, &rfds)) {  //ĳ�Ựsocket�����ݵ���
				//��������
				if (this->recvMessage(*itor, PATH) == -1)
					return -1;
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
	//return NULL;
}

//���ܿͻ��˷�������������ݲ�ת��
int Server::Loop(string PATH) {
	u_long blockMode = Config::BLOCKMODE;//��srvSock��Ϊ������ģʽ�Լ����ͻ���������
	int rtn;

	if ((rtn = ioctlsocket(this->srvSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO��������ֹ�׽ӿ�s�ķ�����ģʽ��
		printf("[Thread_id��%d]ioctlsocket() failed with error!\n",this->threadid);
		return -1;
	}
	printf("[Thread_id��%d]ioctlsocket() for server socket ok!Waiting for client connection and data\n", this->threadid);

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
		if ((this->numOfSocketSignaled = select(0, &this->rfds, &this->wfds, NULL, NULL)) == SOCKET_ERROR) { 
			//select���������пɶ����д��socket��������������rtn��.���һ�������趨�ȴ�ʱ�䣬��ΪNULL��Ϊ����ģʽ
			printf("[Thread_id��%d]select() failed with error!\n", this->threadid);
			return -1;
		}


		//���������е������ζ�����û������������������û����ݵ��������лỰsocket���Է�������

		//���ȼ���Ƿ��пͻ��������ӵ���
		if (this->AcceptRequestionFromClient() != 0) return -1;

		//Ȼ����ͻ��˷�������
		this->ForwardMessage();

		//�����ܿͻ��˷���������
		if (this->ReceieveMessageFromClients(PATH) == -1)
			return -1;
	}

	return 0;
}