#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "FileMappingData.h"
#include "Package.h"



class CDataManger
{
public:
	CDataManger(const char* filename);
	~CDataManger();
	char* AppendData(char* ptr, void* data, size_t length);
	char* GetData(char* ptr, void* data, size_t size);
	char* AppendData(CPackage* pkg);
	char* GetData(CPackage* pkg);
private:
	CFileMappingData* m_filemap;
	 
	char* m_fileaddr;
};
#endif