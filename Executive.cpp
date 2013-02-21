////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Executive.cpp (ver 1.0)  -  Executive Module that Starts the Analysis & Prints Summay output.	     		  // 																					   
//		 																									  //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #1 - CodeMetricsAnalyzer, Spring 2011								  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Executive.h"
#include "Tokenizer.h"
#include "SemiExpression.h"
#include "Parser.h"
#include "ActionsAndRules.h"
#include "ConfigureParser.h"
#include "Executive.h"
#include "DataStore.h"
#include "Show.h"

/////////////////////////////////////////////////////////////////////////////////////
//  Constructor - Uses a vector of file names ( .h & .cpp files )
Executive::Executive(std::vector<std::string> ptrFileArg) : ptrFiles(ptrFileArg) 
{ }

/////////////////////////////////////////////////////////////////////////////////////
//  Function to perform First Pass. Type Table Created.
void Executive::FirstPass()
{
	for each ( std::string file in (ptrFiles) )
	{
	try
    {
		if ( file.length() < 4 || (( file.substr(file.length() - 4 ) != ".cpp" && file.substr(file.length() - 2 ) != ".h" )) ) 
		{ continue; } // Invalid File Format.

    ConfigParseToAnalyze configure; Parser* pParser = configure.Build();
   
	DataStore::setDepth_scope_nesting(0); DataStore::setCurrent_File_Size(0);

	std::string currentPackage = ExtractPackageNamePassOne(file);

	DataStore::setcurrentPackageName(currentPackage); DataStore::setcurrentFileName(file.substr(file.find_last_of("\\") + 1));

	while ( ScopeStack<std::string,ScopeElement>::size() > 0 )
	{ ScopeStack<std::string,ScopeElement>::pop(); } // Clear Stack Before Starting.

      if(pParser)
      {
        if(!configure.Attach(file))
		{ std::cout << "\n  could not open file " << file << std::endl; continue; }
      }
      else
	  { std::cout << "\n\n  Parser not built\n\n"; }

      while(pParser->next()) // now that parser is built, use it
        pParser->parse();
 
	if ( ScopeStack<std::string,ScopeElement>::size() != 0 )
	{ std::cout<<"\n\n Error Processing Package : "<<currentPackage<<" Error Code : 00000"; }
	else 
	{   PackageHolder::setDepthOfNesting(currentPackage,DataStore::getDepth_scope_nesting());
	DataStore::InsertFileSize(DataStore::getcurrentFileName(),DataStore::getCurrent_File_Size()); }
    }
    catch(std::exception& ex)
	{ std::cout << "\n\n Error Processing Package : "<<DataStore::getcurrentPackageName()<<" Error Code : 00001 - "<<DataStore::getCurrent_File_Size()<<ex.what()<<"\n\n"; }	}
}

/////////////////////////////////////////////////////////////////////////////////////
//  Function to perform Second Pass on a package. Variable detecting matched against Type Table.
//  Package Analyzed and results displayed on screen.
void Executive::SecondPass()
{
	std::vector<std::pair<std::string,std::string>> filePackages = PackageHolder::getFilePackages();

	for each ( std::pair<std::string,std::string> package in (filePackages) )
	{
		try
		{

		std::string file = "";
	
		for ( int i = 0 ; i < 2 ; i++ )
		{
			if ( i == 0 )
				file = package.first; // Header File.
			else 
				file = package.second; // Source File.

			if ( file.length() < 4 || (( file.substr(file.length() - 4 ) != ".cpp" && file.substr(file.length() - 2 ) != ".h" )) ) 
				continue; // Invalid File Format.

			std::string currentPackage = ExtractPackageNamePassTwo(file);

			DataStore::setcurrentPackageName(currentPackage); DataStore::setcurrentFileName(file.substr(file.find_last_of("\\") + 1));

			while ( ScopeStack<std::string,ScopeElement>::size() > 0 )
 			{ ScopeStack<std::string,ScopeElement>::pop(); }

			SecondPassParse(file);
		}

		if ( ScopeStack<std::string,ScopeElement>::size() != 0 )
		{ std::cout<<"\n\n Error Processing Package : "<<DataStore::getcurrentPackageName()<<" Error Code : 00000"; }
		else 
		{  	Show::printNormal(DataStore::getcurrentPackageName()); 	
		    //Show::printVerbose(DataStore::getcurrentPackageName()); 
		}
		}
		catch ( std::exception ex )
		{ std::cout<<"\n\n Error Processing Package : "<<DataStore::getcurrentPackageName()<<" Error Code : 00001 -"<<DataStore::getCurrent_File_Size()<<ex.what()<<"\n\n"; }
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
//  Function to extract package name from the filename. ( Parser -> parser.h / parser.cpp )
std::string Executive::ExtractPackageNamePassTwo(std::string file)
{
	std::string currentPackage = file.substr(file.find_last_of("\\") + 1);

	if ( currentPackage.substr(currentPackage.length() - 2 ) == ".h" ) 
	{ currentPackage = currentPackage.substr(0,currentPackage.length()-2); }
	else if ( currentPackage.substr(currentPackage.length() - 4 ) == ".cpp" ) 
	{ currentPackage = currentPackage.substr(0,currentPackage.length()-4); }

	return currentPackage;
}

/////////////////////////////////////////////////////////////////////////////////////
//  Function to extract package Name and add initial package to Repository.
std::string Executive::ExtractPackageNamePassOne(std::string file)
{
	std::string currentPackage = file.substr(file.find_last_of("\\") + 1);

	if ( currentPackage.substr(currentPackage.length() - 2 ) == ".h" ) 
	{ 
	  currentPackage = currentPackage.substr(0,currentPackage.length()-2); 
	  Package pk; 
	  pk.setHeaderFile(file);
	  pk.setSourceFile("");// Add initial package with Source File Blank.
	  PackageHolder::addPackage(currentPackage,pk);  
	}
	else if ( currentPackage.substr(currentPackage.length() - 4 ) == ".cpp" ) 
	{ 
		currentPackage = currentPackage.substr(0,currentPackage.length()-4); 
		Package pk; 
		pk.setSourceFile(file);
		pk.setHeaderFile("");// Add initial package with Header File Blank.
		PackageHolder::addPackage(currentPackage,pk);
	}

	return currentPackage;
}

///////////////////////////////////////////////////////////////////////////////////////////
//  Function to perform Second Parse. Called once for each file. ( .h - .cpp seperately.)
void Executive::SecondPassParse(std::string file)
{
	ConfigParsePassTwo configure;
    Parser* pParser = configure.Build();
    try
    {
      if(pParser)
      {
        if(!configure.Attach(file))
        {
          std::cout << "\n  could not open file " << file << std::endl;
          return;
        }
      }
      else
      {
        std::cout << "\n\n  Parser not built\n\n";
		return;
      }
      
	  // now that parser is built, use it
      while(pParser->next())
        pParser->parse();
     
	   }
    catch(std::exception& ex)
    {
      { std::cout<<"\n\n Error Processing Package : "<<DataStore::getcurrentPackageName()<<" Error Code : 00001 -"<<DataStore::getCurrent_File_Size()<<ex.what()<<"\n\n"; }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
//  Controller function to perform 2 pass parsing.
void Executive::AnalyzeFiles()
{
	FirstPass();

	DataStore::setParseMode(DataStore::SECOND_PASS); // Change mode to ignore 1st Pass Operations not required in 2nd pass.

	SecondPass();
}

/////////////////////////////////////////////////////////////////////////////////////
//  Test Stub
#ifdef TEST_EXECUTIVE

void main ( int argc , char *argv[] )
{
	std::vector<std::string> files;

	files.push_back("..\\Parser.cpp");
	files.push_back("..\\Tokenizer.cpp");

	std::vector<std::string> ptrFiles = files;

	Executive ex(ptrFiles); 

	ex.AnalyzeFiles();

	std::getchar();
}

#endif