#ifndef HTTP_POST_MODULE_H
#define	HTTP_POST_MODULE_H

#include <string>
#include "curl/curl.h"
#include <iostream>
using namespace std;
typedef size_t (*WriteFunc)(char *ptr, size_t size, size_t nmemb,
		void *userdata);
/*
 * 发送http请求
 * 使用开源curl库进行相应的实现
 * 单例模式
 * */
class HttpPostModule
{
public:
	HttpPostModule();
	virtual ~HttpPostModule();

	static void Init();
	static void Cleanup();
public:
	//设置超时
	bool SetTimeOut(unsigned short usSecond);

	//设置 请求的url
	bool SetURL(const string& strURL);
	//设置http头
	bool SetHttpHead(const string& strHttpHead);
	//设置返回数据回调函数
	bool SetWriteFunction(WriteFunc pFunc);
	//发送http请求
	int SendPostRequest(void);

private:
	CURL* m_pCurl;
public:

};
//NetModule end
#endif
