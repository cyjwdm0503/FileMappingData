
#include "DataManager.h"
#include "FileMappingData.h"
#include <exception>



CDataManger::CDataManger( const char* filename )
{

	m_filemap  = new CFileMappingData(filename,MAXFILE_SIZE);
	if(m_filemap->CreateFileMap(1.0) == false)
	{
		throw std::exception("CreateFileMap Failded");
	}
	HANDLE file_handle =  m_filemap->GetHandle(); 
	
	//³õÊ¼Î»ÖÃÎª0
	m_fileaddr = (char*)MapViewOfFile(file_handle,FILE_MAP_ALL_ACCESS,0,0,MAXFILE_SIZE);

}

char* CDataManger::AppendData( char* ptr, void* data, size_t length )
{
	if(ptr == NULL)
	{
		//strncpy(m_fileaddr,(char*)data,length);
		memcpy(m_fileaddr,data,length);
		FlushViewOfFile(m_fileaddr,length);
		m_fileaddr = m_fileaddr+length;
	}
	else
	{
		//strncpy(ptr,(char*)data,length);
		memcpy(ptr,data,length);
		FlushViewOfFile(ptr,length);
		m_fileaddr =  ptr+length;
	}

	return m_fileaddr;;
}

char* CDataManger::GetData( char* ptr, void* data, size_t size )
{
	if(ptr == NULL)
	{
		;//memcpy()
	}
	else
	{
		memcpy(data,ptr,size);
	}
	return NULL;
}

char* CDataManger::AppendData( CPackage* pkg )
{
	return AppendData(NULL,pkg->GetPtr(),pkg->GetSize());
}

CDataManger::~CDataManger()
{
	if(m_filemap != NULL)
	{
		delete m_filemap;
		m_filemap =  NULL;
	}
	if(m_fileaddr != NULL)
	{
		UnmapViewOfFile(m_fileaddr);
		m_fileaddr = NULL;
	}
}
