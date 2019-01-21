#pragma once
#include <string>
#include <vector>
#include <winsock2.h>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <thread>
#include <list>
using namespace std;

//����������Ϣ
class Config
{
public:
    static const int MAXCONNECTION;		//���������
    static const int BUFFERLENGTH;		//��������С
    static const string SERVERADDRESS;  //��������ַ
    static const int PORT;				//�������˿�
    static const string PATH;
    static const u_long BLOCKMODE;			//SOCKET����ģʽ
    static vector<string> split(const string& str, const string& delim);
    static void recvBuf_remsg(string http, string &head, string &msg, string path);
private:
    Config(void);
    ~Config(void);
};
