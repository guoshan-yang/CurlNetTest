#include <sys/stat.h>
#include <unistd.h>
#include "DownloadModule.h"


DownLoadModule::DownLoadModule() :
		m_pCurl(NULL)
{
	m_pCurl = curl_easy_init();
}
DownLoadModule::~DownLoadModule()
{
	curl_easy_cleanup(m_pCurl);
	m_pCurl = NULL;
}
void DownLoadModule::Init()
{
	curl_global_init(CURL_GLOBAL_ALL);

}
void DownLoadModule::Cleanup()
{
	curl_global_cleanup();

}

size_t DownLoadModule::DownLoadPackage(void *ptr, size_t size, size_t nmemb,
		void *userdata)
{
	FILE *fp = (FILE*) userdata;
	size_t written = fwrite(ptr, size, nmemb, fp);
	return written;
}

long DownLoadModule::GetLocalFileLenth(const string& strFileName)
{
	unsigned long filesize = 0;
	struct stat statbuff;
	if (stat(strFileName.c_str(), &statbuff) < 0)
	{
		return filesize;
	}
	else
	{
		filesize = statbuff.st_size;
	}
	return filesize;

}
int DownLoadModule::DownLoad(std::string strUrl, std::string strStoragePath,
		std::string strFileName)
{
	Init();
	// Create a file to save package.
	if (0 != access(strStoragePath.c_str(), F_OK))
		mkdir(strStoragePath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	;
	const string outFileName = strStoragePath + "/" + strFileName;
	//================¶ÏµãÐøÔØ===================
	long localLen = GetLocalFileLenth(outFileName.c_str());
	FILE *fp = fopen(outFileName.c_str(), "a+b");
	if (!fp)
	{
		return -1;
	}
	fseek(fp, 0, SEEK_END);

	// Download pacakge
	CURLcode res;
	curl_easy_setopt(m_pCurl, CURLOPT_URL, strUrl.c_str());
	curl_easy_setopt(m_pCurl, CURLOPT_WRITEFUNCTION, DownLoadPackage);
	curl_easy_setopt(m_pCurl, CURLOPT_WRITEDATA, fp);
	curl_easy_setopt(m_pCurl, CURLOPT_NOPROGRESS, true);
	//curl_easy_setopt(m_pCurl, CURLOPT_TIMEOUT, 30);
	curl_easy_setopt(m_pCurl, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(m_pCurl, CURLOPT_HEADER, 0L);
	curl_easy_setopt(m_pCurl, CURLOPT_NOBODY, 0L);
	curl_easy_setopt(m_pCurl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(m_pCurl, CURLOPT_RESUME_FROM, localLen);

	res = curl_easy_perform(m_pCurl);
	Cleanup();

	if (res != 0)
	{
		fclose(fp);
		return res;
	}
	fclose(fp);
	return 0;
}

