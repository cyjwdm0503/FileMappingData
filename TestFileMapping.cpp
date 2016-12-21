#include "FileMappingData.h"
#include "Mutex.h"
#include <iostream>

#include "DataManager.h"


void testpackage()
{
	CPackage package;
	S_field field,rt;
	field.header.Package_ID = 'a';
	field.header.Package_Type = 'b';
	field.header.Package_Length = 10;
	package.PushBackFieldSet(&field);
	//package.GetFieldSet(&rt);
	CDataManger manager("text.txt");
	manager.AppendData(&package);

}

int main(int,char**)
{
	testpackage();
	int x = 136;
	int y = 64;
	std::cout<<x/y<<std::endl; 
	return 0;
}