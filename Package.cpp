#include "Package.h"

CPackage::CPackage()
{
	//Header.Package_Type = type;
	//Header.Package_ID = id;
	//Header.Package_Length = size;

	begin  =  buf;
	end = &(buf[MAXPACKAGE_SIZE]);
	curpos = begin;

}

int CPackage::PushBackBuf(void* data,int size )
{
	if(curpos+size < end)
	{
		memcpy(curpos,data,size);
		curpos = curpos + size;
		return size;
	}
	return 0;
}

int CPackage::GetSize() const
{
	return curpos - begin;
}

void* CPackage::GetPtr() const
{
	return begin;
}

int CPackage::PopFrontBuf( void* data, int size )
{
	if(begin+size < end)
	{
		memcpy(data,begin,size);
		begin =  begin+ sizeof(SFieldHeader);
		return size;
	}
	return 0;
}

int CPackage::PopFrontFieldSet( SBaseFiledSet* set )
{
	return PopFrontBuf(&(set->header),sizeof(SFieldHeader));
	//return 0;
}

int CPackage::PushBackFieldSet( SBaseFiledSet* set )
{
	return PushBackBuf(&(set->header),sizeof(SFieldHeader));
}