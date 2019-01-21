#include "Config.h"
#include <string.h>
#include <vector>
#include <fstream>
#include<ctime>

#include<iostream>
using namespace std;


Config::Config(void)
{
}

Config::~Config(void)
{
}
const int Config::PORT = 80;						//�������˿�5050
const string Config::SERVERADDRESS = "127.0.0.1";	//������IP��ַ
const string Config::PATH = "C:\\Users\\LXR\\Desktop\\";
const int Config::MAXCONNECTION = 50;				//���������50
const int Config::BUFFERLENGTH = 1024;				//��������С256�ֽ�
const u_long Config::BLOCKMODE = 1;					//SOCKETΪ������ģʽ
vector<string> Config::split(const string& str, const string& delim) {
	vector<string> res;
	if ("" == str) return res;
	//�Ƚ�Ҫ�и���ַ�����string����ת��Ϊchar*����
	char * strs = new char[str.length() + 1]; //��Ҫ����
	strcpy(strs, str.c_str());

	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char *p = strtok(strs, d);
	while (p) {
		string s = p; //�ָ�õ����ַ���ת��Ϊstring����
		res.push_back(s); //����������
		p = strtok(NULL, d);
	}

	return res;
}
int Config::recvBuf_remsg(string http,string &head,string &msg,string path)	
{
	if (http.find("HTTP") == string::npos)
		return 0;
	vector<string> request = split(http, "\r\n");
	vector<string> shead = split(request[0], " ");

	string filename = shead[1].substr(1);
	string httplevel = shead[2];
	if (filename == "close")
		return -1;
	vector<string> filetypes = split(filename, ".");
	string filetype;
	for (vector<string>::iterator itor = filetypes.begin(); itor != filetypes.end(); itor++)
		filetype = *itor;

	filename = path + filename;

	ifstream content_file(filename);
	if (!content_file.is_open()) {
		head += httplevel + " 404 Not Found\r\n";
		string length = "0";
		head += "Content-Length:" + length + "\r\n\r\n";
		msg += head;
		msg += "Error��File not found.";
		return 0;
	}
	head += httplevel + " 200 OK\r\n";

	streampos file_size = content_file.tellg();
	content_file.seekg(0, ios::end);
	file_size = content_file.tellg() - file_size;
	content_file.seekg(0, ios::beg);

	string content = "";
	content.resize(file_size, 0);
	content_file.read((char *)content.c_str(), file_size);
	content_file.close();

	string length = to_string(content.size());
	//head += "Content-Type: " + filetype + "\r\n";
	head += "Content-Length :" + length + "\r\n\r\n";	//��ͨ�����������߷������Ѵ������

	msg += head;
	msg += content;
	return 0;
}