//���߳��������
#pragma once
#include "Server.h"
#include "Config.h"
#include <thread>
#include <vector>
#include <iostream>
using namespace std;
void run(int port,string ip,string path)
{
	Server srv;
	srv.threadid = this_thread::get_id();
	if (srv.WinsockStartup() == -1) return;
	if (srv.ServerStartup(port, ip) == -1) return;
	if (srv.ListenStartup() == -1) return;
	if (srv.Loop(path) == -1) return;
	return;
}
int main() {
	bool firsttime = 0;
	int op;
	while (1)
	{
		if (firsttime != 0)
		{
			cout << "Continue or quit(0)?" << endl;
			cin >> op;
			if (op == 0)break;
		}
		firsttime = 1;

		string ip;		 //���ip
		int port[50];  //��Ŷ˿�
		string portlist; //����˿�
		string path;  //��Ŀ¼
		int n;	   //�˿ڸ���

		cout << "If you enter 0, the default setting is used��" << endl;
		cout << "ip="; cin >> ip;  getchar();
		if (ip == "0")ip = Config::SERVERADDRESS;

		cout << "port="; getline(cin, portlist);
		vector<string> ports = Config::split(portlist, " ");
		if (ports.size() == 0 || portlist == "0")
		{
			port[0] = Config::PORT;
			n = 1;
		}
		else
		{
			for (int i = 0; i < ports.size(); i++)
			{
				port[i] = stoi(ports[i]);
			}
			n = ports.size();
		}

		cout << "path="; cin >> path;
		if (path == "0")path = Config::PATH;



		std::thread threads[50]; // ����洢�̵߳�����
		int thread_num = 0;	  //��ǰ�߳�����
		for (int i = 0; i < n; i++)
		{
			threads[i] = std::thread(run, port[i], ip, path);
			thread_num++;
		}
		for (int i = 0; i < thread_num; i++)
			threads[i].join();

		// �ͷ��׽���
		WSACleanup();
	}

	return 0;
}
