#ifndef FILEMAPPINGDATA_H 
#define FILEMAPPINGDATA_H

#include <string>
#include <cstring>
#include <windows.h>

class CFileMappingData
{
public:
	CFileMappingData(const char* filename,__int64 filesize);
	~CFileMappingData();
	bool CreateFileMap(double ratio);
	bool OpenFileMap();
	HANDLE GetHandle();
	__int64 GetFileSize();
	int GetAllocGranularity() const ;

	//bool CreateMapViewBuf();
private:
	HANDLE m_maphandle;
	
	__int64 m_filesize;
	std::string m_filename;
	char* m_buf;

	HANDLE hfile;
};
#endif