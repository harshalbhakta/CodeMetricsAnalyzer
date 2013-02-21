////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CmdLineArgs.cpp (ver 1.0)  -  Store and Validate Command Line Arguments.									  // 																					   
//		 																									  //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #1 - CodeMetricsAnalyzer, Spring 2011								  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "CmdLineArgs.h"
#include "CustomNavigate.h"

///////////////////////////////////////////////////////////////
//  CmdLineArgs - Constructor
CmdLineArgs::CmdLineArgs()
	: recurse(false),pathSpec("."),filePattern(1,"*.cpp")
{}

///////////////////////////////////////////////////////////////
//  Validate the Command line arguments.
bool CmdLineArgs::ValidateAndStoreArgs(int argc,char* argv[])
{
	try 
	{
		if ( argc < 4 ) { return false; }

		std::string recurseOption = argv[1];

		if ( recurseOption == "-r" ) 
			{ recurse = true; }
		else if ( recurseOption == "-nr") 
			{ recurse = false;}
		else 
			{ return false; }

		pathSpec = argv[2];

		filePattern.clear();

		for(int i = 3; i < argc;i++)
		{ filePattern.push_back(argv[i]); }

		fetchFiles();

		return true;
	}
	catch (std::exception ex)
	{
		std::cout<<std::endl<<"Error Processing Arguments : "<<ex.what();
		return false;
	}
}

///////////////////////////////////////////////////////////////
//  Return recurse flag.
bool CmdLineArgs::isRecurse()
{ return recurse; }

///////////////////////////////////////////////////////////////
//  Return File Pattern.
std::vector<std::string> CmdLineArgs::getFilePattern()
{ return filePattern; }

///////////////////////////////////////////////////////////////
//  Return Path Specs.
std::string CmdLineArgs::getPathSpecs()
{ return pathSpec;}

///////////////////////////////////////////////////////////////
//  Return Vector of String.
std::vector<std::string> CmdLineArgs::getFiles()
{
	return files;
}

///////////////////////////////////////////////////////////////
//  Fetch Files based on the arguments entered.
void CmdLineArgs::fetchFiles()
{
		CustomNavigate cn;

		files = cn.getFiles(pathSpec,filePattern,recurse);
}

///////////////////////////////////////////////////////////////
//  Print the valid files fetched.
void CmdLineArgs::printValidFiles()
{
	std::cout << "\n\n  Valid Files \n "<< std::string(22,'=') << std::endl;

	for each ( std::string file in files )
	{ std::cout<<std::endl<<" "<<file; }
}

///////////////////////////////////////////////////////////////
//  Print the manual when invalid arguments are entered.
void CmdLineArgs::printManual()
{

		std::cout<<std::endl<<"--------------------------------------------------------";
		std::cout<<std::endl<<"--------------------------------------------------------";
		std::cout<<std::endl<<"---   Usage : cma -r|-nr DirPath pat1 pat2 patN      ---";
		std::cout<<std::endl<<"---      -r : Recursively fetch files.		     ---";
		std::cout<<std::endl<<"---     -nr : Non Recursively fetch files.           ---";
		std::cout<<std::endl<<"--- DirPath : Base Dir. Relative or Absolute Path    ---";
		std::cout<<std::endl<<"---    pat1 : File Filter Pattern 1. (Eg. *.cpp *.h) ---";
		std::cout<<std::endl<<"---    pat2 : File Filter Pattern 2. (Eg. *.cpp *.h) ---";
		std::cout<<std::endl<<"---	    : (Atleast One File Pattern Required.)   ---";
		std::cout<<std::endl<<"---    patN : File Filter Pattern N. (Eg. *.cpp *.h) ---";
		std::cout<<std::endl<<"--------------------------------------------------------";
		std::cout<<std::endl<<"--------------------------------------------------------";
		std::cout<<std::endl;

}


///////////////////////////////////////////////////////////////
//  Test Stub.
#ifdef TEST_CMDLINEARDS
int main(int argc, char* argv[])
{
	std::cout << "\n  Testing CmdLineArgs class\n "
            << std::string(22,'=');

	CmdLineArgs cla;

	if ( cla.ValidateAndStoreArgs(argc,argv) ) 
	{

		std::cout << "\n  Argument Status \n "
            << std::string(22,'=');

		std::cout<<std::endl<<" Arguments Entered are valid." ;

		std::cout<<std::endl<<" Rescurse Option = "<<( cla.isRecurse() == 0 ? "False" : "True ");

		std::cout<<std::endl<<" Directory = "<<cla.getPathSpecs();

		std::vector<std::string> filePattern(cla.getFilePattern());

		std::cout<<std::endl<<" File Pattern = ";

		for ( int i = 0 ; i < (int)filePattern.size() ; i++ )
		{
			std::cout<<" "<<filePattern[i]<<" ";
		}

		cla.printValidFiles();

	}
	else 
	{
		std::cout<<std::endl<<" Invalid Arguments." ;
	}

	std::getchar();

}

#endif