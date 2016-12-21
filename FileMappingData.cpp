

#include "FileMappingData.h"

bool CFileMappingData::CreateFileMap( double ratio )
{
	m_filesize = m_filesize*ratio;
	__int64 qwFileSize = m_filesize;
	//创建文件对象
	hfile = CreateFile(m_filename.c_str(), GENERIC_READ | GENERIC_WRITE, 
		FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hfile == INVALID_HANDLE_VALUE)
	{
		return false;	
	}

	// 创建文件映射对象
	m_maphandle = CreateFileMapping(hfile, NULL, PAGE_READWRITE, (long)(qwFileSize>>32), (long)(qwFileSize&0xFFFFFFFF), m_filename.c_str());
	if (m_maphandle == NULL)
	{
		CloseHandle(hfile);
		int nErrorNo = GetLastError();
		return false;			
	}

	// 关闭文件对象
	//CloseHandle(hFile);

	return true;
}

CFileMappingData::CFileMappingData( const char* filename,__int64 filesize )
{
	m_filename = filename;
	m_filesize =  filesize;
	m_maphandle =  NULL;
	m_buf =  NULL;
	hfile =  NULL;
}


CFileMappingData::~CFileMappingData()
{
	if(m_maphandle )
	{
		CloseHandle(m_maphandle);
	}
	m_maphandle = NULL;
	if(hfile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hfile);
	}
	hfile = NULL;
}

__int64 CFileMappingData::GetFileSize()
{
	return m_filesize;
}

HANDLE CFileMappingData::GetHandle()
{
	return m_maphandle;
}

bool CFileMappingData::OpenFileMap()
{
	m_maphandle = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,m_filename.c_str());
	if(m_maphandle == NULL)
	{
		return false;
	}
	return true;

}

int CFileMappingData::GetAllocGranularity() const
{
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	return info.dwAllocationGranularity;
}

//
//bool CFileMappingData::CreateMapViewBuf()
//{
//	m_buf = (LPTSTR) MapViewOfFile(m_filehandle,   // handle to map object
//		FILE_MAP_ALL_ACCESS, // read/write permission
//		0,
//		(long)(m_filesize&0xFFFFFFFF),
//		NULL);
//}

