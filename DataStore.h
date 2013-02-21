#ifndef DATASTORE_H
#define DATASTORE_H
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DataStore.h (ver 1.0)  -  Hold all the Static Data required to be stored for analysis.					  // 																					   
//		 																									  //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #1 - CodeMetricsAnalyzer, Spring 2011								  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================

  This module will define and declare all the static data structure that will be required for analysis.

  TypeTable : Key   - Fully Qualified Name.
  TypeTable : Value - TypeItem [ fileName - package name - lineNumber ] 

  parse_mode : FIRST_PASS  : Pass 1 -> Functionality to add to TypeTable Enabled in ActionsAndRules.cpp
  parse_mode : SECOND_PASS : Pass 2 -> Functionality to add to TypeTable Disabled in ActionsAndRules.cpp

  currentPackageName : Hold the package name of the current package being analyzed.
	
  currentFileName : Hold the file name of the file being analyzed.

  curr_function_cyclo : Keep track of Cyclomatic Complexity for current control block.

  depth_scope_nesting : Keep track of Depth Scope Nesting for current file.

  current_file_size : Keep track of number of lines parsed. Finally gives line count for file.

  namespaceList : List of all the files and namespaces used in the file.

  fileSizeList : List of all the files along with the size of each file.

  Public Interface:
  =================
  
  Get - Set methods for all static data.

  DataStore::addTypeToTypeTable("variable",ti);

  bool find = DataStore::findKeyInTypeTable("varialbe");



  Build Process:
  ==============
  Required files
    - DataStore.cpp
  Build commands
    - devenv CodeMetricsAnalyzer.sln /rebuild debug

  Maintenance History:
  ====================
  ver 1.0 : 25 Feb 11
 
*/
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>

class TypeItem{
	std::string fileName;
	std::string packageName;
	int lineNumber;

public : 

	void setFileName(std::string);
	std::string getFileName();

	void setpackageName(std::string);
	std::string getpackageName();

	void setLineNumber(int);
	int getLineNumber();
};

inline void TypeItem::setFileName(std::string fn){ fileName = fn; }
inline std::string TypeItem::getFileName(){ return fileName; }

inline void TypeItem::setpackageName(std::string fq){ packageName = fq; }
inline std::string TypeItem::getpackageName(){ return packageName; }

inline void TypeItem::setLineNumber(int ln){ lineNumber = ln; }
inline int TypeItem::getLineNumber(){ return lineNumber; }

class DataStore {

public:

	enum mode { FIRST_PASS,SECOND_PASS } ;

	static bool findKeyInTypeTable(std::string);

	static TypeItem getTypeItemFromTypeTable(std::string);

	static void setcurrentPackageName(std::string);
	static std::string getcurrentPackageName();

	static void setcurrentFileName(std::string);
	static std::string getcurrentFileName();

	static void setCurr_function_cyclo(int);
	static int getCurr_function_cyclo();
	static void Increment_Cyclo();

	static void setDepth_scope_nesting(int);
	static int getDepth_scope_nesting();

	static void setCurrent_File_Size(int);
	static int getCurrent_File_Size();

	static void setParseMode(DataStore::mode);
	static mode DataStore::getParseMode();
	
	static void InsertNamespace(std::string,std::string);
	static std::vector<std::string> GetNamespace(std::string);

	static void InsertFileSize(std::string,int);
	static int GetFileSize(std::string);

	static void addTypeToTypeTable(std::string,TypeItem);

	static void printDetectedTypes(std::string);

	static void DataStore::printNamespace(std::string);

private:	

	static mode parse_mode;

	static std::string currentPackageName;
	
	static std::string currentFileName;

	static int curr_function_cyclo;

	static int depth_scope_nesting;

	static int current_file_size;

	static std::vector<std::pair<std::string,std::string>> namespaceList;

	static std::vector<std::pair<std::string,int>> fileSizeList;

	static std::map<std::string,TypeItem> TypeTable;	 
};

#endif