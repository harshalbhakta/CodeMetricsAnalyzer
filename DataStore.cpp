////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DataStore.cpp (ver 1.0)  -  Hold all the Static Data required to be stored for analysis.					  // 																					   
//		 																									  //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #1 - CodeMetricsAnalyzer, Spring 2011								  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include "DataStore.h"
#include <iomanip>

///////////////////////////////////////////////////////////////
//  Initialize Static Data
std::string DataStore::currentPackageName = "" ;

std::string DataStore::currentFileName = "" ;

int DataStore::curr_function_cyclo = 0;

int DataStore::depth_scope_nesting = 0;

int DataStore::current_file_size = 0;

DataStore::mode DataStore::parse_mode = FIRST_PASS;

std::vector<std::pair<std::string,std::string>> DataStore::namespaceList;

std::vector<std::pair<std::string,int>> DataStore::fileSizeList;

std::map<std::string,TypeItem> DataStore::TypeTable;

///////////////////////////////////////////////////////////////
//  Set Parse Mode.
void DataStore::setParseMode(DataStore::mode currMode)
{
	parse_mode = currMode;
}

///////////////////////////////////////////////////////////////
//  Get Parse Mode.
DataStore::mode DataStore::getParseMode()
{
	return parse_mode;
}

///////////////////////////////////////////////////////////////
//  Set Current Package Name
void DataStore::setcurrentPackageName(std::string currPkgName)
{
	currentPackageName = currPkgName;
}

///////////////////////////////////////////////////////////////
//  Get Current Package Name
std::string DataStore::getcurrentPackageName()
{
	return currentPackageName;
}

///////////////////////////////////////////////////////////////
//  Set Current File Name 
void DataStore::setcurrentFileName(std::string FileName)
{
	currentFileName = FileName;
}

///////////////////////////////////////////////////////////////
//  Get Current File Name
std::string DataStore::getcurrentFileName()
{
	return currentFileName;
}

///////////////////////////////////////////////////////////////
//  Set Current Cyclomatic Complexity
void DataStore::setCurr_function_cyclo(int cyclo)
{
	curr_function_cyclo = cyclo;
}

///////////////////////////////////////////////////////////////
//  Get Current Cyclomatic Complexity.
int DataStore::getCurr_function_cyclo()
{
	return curr_function_cyclo;
}

///////////////////////////////////////////////////////////////
//  Set Depth Scope Nesting
void DataStore::setDepth_scope_nesting(int depth)
{
	depth_scope_nesting = depth;
}

///////////////////////////////////////////////////////////////
//  Get Depth Scope Nesting
int DataStore::getDepth_scope_nesting()
{
	return depth_scope_nesting;
}

///////////////////////////////////////////////////////////////
//  Set Current File Size.
void DataStore::setCurrent_File_Size(int size)
{ current_file_size = size;
}

//////////////////////////////////////////////////////////////
//  Set Current File Size
int DataStore::getCurrent_File_Size()
{ return current_file_size; }

///////////////////////////////////////////////////////////////
//  Inrement Cyclomatic Complexity
void DataStore::Increment_Cyclo()
{
	curr_function_cyclo++;
}

///////////////////////////////////////////////////////////////
//  Insert Namespace when "using" detected.
void DataStore::InsertNamespace(std::string fileName,std::string Namespace)
{
	std::pair<std::string,std::string> temp;

	temp.first = fileName;
	temp.second = Namespace;

	namespaceList.push_back(temp);
}

///////////////////////////////////////////////////////////////
//  Insert the size of the file.
void DataStore::InsertFileSize(std::string fileName,int size)
{
	std::pair<std::string,int> temp;

	temp.first = fileName;
	temp.second = size;

	fileSizeList.push_back(temp);
}

///////////////////////////////////////////////////////////////
//  Get size of a file by name.
int DataStore::GetFileSize(std::string fileName)
{
	int size = 0;

	for ( int i = 0 ; i < (int)fileSizeList.size() ; i++ )
	{
		if ( fileSizeList[i].first == fileName )
		{ size = fileSizeList[i].second; break; }
	}

	return size;
}


//void DataStore::addTypeVectorToTypeTable(std::string key,std::vector<TypeItem> vecItem)
//{
//	if ( DataStore::TypeTable.find(key) == DataStore::TypeTable.end() )
//	{
//		DataStore::TypeTable[key] = vecItem;
//	}
//}

//std::vector<TypeItem>* DataStore::getTypeVector(std::string key)
//{
//	return &DataStore::TypeTable[key];
//}


///////////////////////////////////////////////////////////////
//  Add Type to the Table
void DataStore::addTypeToTypeTable(std::string key,TypeItem ti)
{
 	if ( DataStore::TypeTable.find(key) == DataStore::TypeTable.end() )
	{
		DataStore::TypeTable[key] = ti;
	}
}

///////////////////////////////////////////////////////////////
//  Check if a key exists in the TypeTable.
bool DataStore::findKeyInTypeTable(std::string key)
{
	std::map<std::string,TypeItem>::iterator it ;

	it = TypeTable.find(key);

	if ( it != TypeTable.end() )
		return true;

	return false;
}

///////////////////////////////////////////////////////////////
//  Get TypeItem using key ( Fully Qualified Type Name )
TypeItem DataStore::getTypeItemFromTypeTable(std::string key)
{
	return TypeTable[key];
}

void DataStore::printDetectedTypes(std::string package)
{
	/*	std::vector<TypeItem>* tiPtr = DataStore::getTypeVector(package);

		std::cout<<"\n\n  "<<package<<"\n";

		std::cout<<"  "<<std::string(49,'-')<<"\n";

		std::cout<<"\n\n  "<<std::setw(5)<<"filename"<<" "<<"line #"<<" "<<"  type"<<"\n";

		std::cout<<"  "<<std::string(49,'-')<<"\n";

		for ( int i = 0 ; i < (int)((*tiPtr).size()) ; i++)
		{
			std::cout<<"  "<<std::setw(5)<<(*tiPtr)[i].getFileName()<<" "<<std::setw(5)<<(*tiPtr)[i].getLineNumber()<<" "<<(*tiPtr)[i].getFullyQualifiedName()<<"\n";
		}*/
}

///////////////////////////////////////////////////////////////
//  Test Function to display namespace associated to a file.
void DataStore::printNamespace(std::string file)
{
		std::cout<<"\n\n  "<<file<<"\n";

		std::cout<<"  "<<std::string(49,'-')<<"\n";

		std::cout<<"\n\n  "<<std::setw(5)<<"filename"<<"		"<<"namespace"<<"\n";

		std::cout<<"  "<<std::string(49,'-')<<"\n";

		for ( int i = 0 ; i < (int)namespaceList.size() ; i++)
		{
			if ( namespaceList[i].first == file )
				std::cout<<"  "<<std::setw(5)<<file<<"		"<<std::setw(5)<<namespaceList[i].second<<"\n";
		}
}

///////////////////////////////////////////////////////////////
//  Get Name space list for a file.
std::vector<std::string> DataStore::GetNamespace(std::string fileName)
{
	std::vector<std::string> temp;

	for ( int i = 0 ; i < (int)namespaceList.size() ; i++)
	{
		if ( namespaceList[i].first == fileName )
		{ temp.push_back(namespaceList[i].second);}
	}

	return temp;
}

///////////////////////////////////////////////////////////////
//  Test Stub
#ifdef TEST_DATABASE
int main ( int argc, char* argv[])
{
	std::cout<<"Testing Storage";

	DataStore::setcurrentPackageName("testing.cpp");

	std::cout<<DataStore::getcurrentPackageName();

	TypeItem ti;

	ti.setFileName("test.cpp");
	ti.setLineNumber(12);
	ti.setpackageName("test_package");
	
	DataStore::addTypeToTypeTable("variable",ti);

	bool find = DataStore::findKeyInTypeTable("varialbe");

	std::cout<<"\nVariable found or not : "<<find;

	DataStore::setParseMode(DataStore::FIRST_PASS);

	std::cout<<DataStore::getParseMode();

	DataStore::InsertFileSize("test",12);

	std::vector<std::string> test = DataStore::GetNamespace("test");

	std::cout<<test[0];

	std::getchar();
}
#endif