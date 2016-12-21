#ifndef PACKAGE_H
#define PACKAGE_H

#include <cstdlib>
#include <cstring>

const long long  MAXFILE_SIZE = 1024*100;
const long long MAXPACKAGE_SIZE = 1024;

struct SFieldHeader
{
	char Package_Type;
	char Package_ID;
	int Package_Length;
};

typedef struct SBaseFiledSet
{
	SFieldHeader header;
}S_field;

class CPackage
{


public:
	CPackage();

	int PushBackBuf(void* data,int size);
	int PopFrontBuf(void* data, int size);
	int PopFrontFieldSet(SBaseFiledSet* set);
	int PushBackFieldSet(SBaseFiledSet* set);
	void* GetPtr() const ;
	int GetSize() const;
private:

	char  buf[MAXPACKAGE_SIZE];
	char* begin;
	char* end;
	char* curpos;
};


#endif