#ifndef DOWNLOAD_MODULE_H
#define DOWNLOAD_MODULE_H
#include <string>
#include "curl/curl.h"
using namespace std;

class DownLoadModule
{
public:
	DownLoadModule();
	virtual ~DownLoadModule();
	static void Init();
	static void Cleanup();

public:
	static size_t DownLoadPackage(void *ptr, size_t size, size_t nmemb,
			void *userdata);
private:
	long GetLocalFileLenth(const string& strFileName);
public:
	/*
	 * param1 string �����ļ���url��ַ��
	 * param2 string ���ص���·��  ע��Ҫ��/��β
	 * param3 string ���غ���ļ���
	 * return 0 ���سɹ�/-1�����ʼ��ʧ��/����Ϊcurl���ش�����
	 * */
	int DownLoad(std::string strUrl, std::string strStoragePath,
			std::string strFileName);
private:
	CURL *m_pCurl;
};

#endif
