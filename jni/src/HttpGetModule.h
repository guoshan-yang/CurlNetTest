#ifndef HTTP_POST_MODULE_H
#define	HTTP_POST_MODULE_H

#include <string>
#include "curl/curl.h"
#include <iostream>
using namespace std;
typedef size_t (*WriteFunc)(char *ptr, size_t size, size_t nmemb,
		void *userdata);
/*
 * ����http����
 * ʹ�ÿ�Դcurl�������Ӧ��ʵ��
 * ����ģʽ
 * */
class HttpPostModule
{
public:
	HttpPostModule();
	virtual ~HttpPostModule();

	static void Init();
	static void Cleanup();
public:
	//���ó�ʱ
	bool SetTimeOut(unsigned short usSecond);

	//���� �����url
	bool SetURL(const string& strURL);
	//����httpͷ
	bool SetHttpHead(const string& strHttpHead);
	//���÷������ݻص�����
	bool SetWriteFunction(WriteFunc pFunc);
	//����http����
	int SendPostRequest(void);

private:
	CURL* m_pCurl;
public:

};
//NetModule end
#endif
