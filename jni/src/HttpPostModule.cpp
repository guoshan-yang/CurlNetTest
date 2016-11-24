#include "HttpPostModule.h"

HttpPostModule::HttpPostModule() :
		m_pCurl(NULL)
{
	m_pCurl = curl_easy_init();
	curl_easy_setopt(m_pCurl, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(m_pCurl, CURLOPT_POST, 1L);
}
HttpPostModule::~HttpPostModule()
{
	curl_easy_cleanup(m_pCurl);
	m_pCurl = NULL;
}
void HttpPostModule::Init()
{
	curl_global_init(CURL_GLOBAL_ALL);

}
void HttpPostModule::Cleanup()
{
	curl_global_cleanup();

}
bool HttpPostModule::SetTimeOut(unsigned short usSecond)
{
	if (m_pCurl == NULL)
		return false;
	int nRet = curl_easy_setopt(m_pCurl, CURLOPT_TIMEOUT, usSecond);
	if (nRet == CURLE_OK)
		return true;
	else
	{
		cout << "SetTimeOut ERROR code =" << nRet << endl;
		return false;
	}
}
bool HttpPostModule::SetURL(const string& strURL)
{
	if (m_pCurl == NULL)
		return false;
	int nRet = curl_easy_setopt(m_pCurl, CURLOPT_URL, strURL.c_str());
	if (nRet == CURLE_OK)
		return true;
	else
	{
		cout << "SetURL ERROR code =" << nRet << endl;
		return false;
	}
}
bool HttpPostModule::SetHttpHead(const string& strHttpHead)
{
	if (m_pCurl == NULL)
		return false;
	curl_slist *plist = curl_slist_append(NULL, strHttpHead.c_str());
	int nRet = curl_easy_setopt(m_pCurl, CURLOPT_HTTPHEADER, plist);
	if (nRet == CURLE_OK)
		return true;
	else
	{
		cout << "SetHttpHead ERROR code =" << nRet << endl;
		return false;
	}
}
bool HttpPostModule::SetWriteFunction(WriteFunc pFunc)
{
	if (m_pCurl == NULL)
		return false;
	curl_easy_setopt(m_pCurl, CURLOPT_WRITEDATA, NULL);
	int nRet = curl_easy_setopt(m_pCurl, CURLOPT_WRITEFUNCTION, pFunc);
	if (nRet == CURLE_OK)
		return true;
	else
	{
		cout << "SetCallbackFunc ERROR code =" << nRet << endl;
		return false;
	}
}

int HttpPostModule::SendPostRequest(void)
{
	if (m_pCurl == NULL)
		return -1;
	int nRet = curl_easy_perform(m_pCurl);
	if (nRet == CURLE_OK)
		return 0;
	else
	{
		return nRet;
	}
}
