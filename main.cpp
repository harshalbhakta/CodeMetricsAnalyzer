////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// main.cpp (ver 1.0)  -  Source File to test CodeMetricsAnalyzer - Provider of function main()				  // 																					   
//		 																									  //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #1 - CodeMetricsAnalyzer, Spring 2011								  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Module Operations:
* ==================
* - main() : CodeMetricsAnalyzer Application start point.
* - Uses 'CmdLineArgs' to check and store command line arguments. 
* - Calls Executive to Analyze files
* - Calls Show to display results.
* Build Process:
* ==============
* devenv CodeMetricsAnalyzer.sln /rebuild debug
* 
* Requirement Files:
* ==================
* CmdLineArgs.h
* CmdLineArgs.cpp
* 
* Maintenance History:
* ====================
* ver 1.0 : 15 Feb 2011
* - Initial Release
*/

#include "CmdLineArgs.h"
#include "Executive.h"
#include "Show.h"

int main(int argc,char* argv[])
{
	try 
	{
		CmdLineArgs cla;

		Show::printHeader();

		if(cla.ValidateAndStoreArgs(argc,argv))
		{
		std::vector<std::string> ptrFiles = cla.getFiles();

		Executive ex(ptrFiles);

		ex.AnalyzeFiles();

		Show::printOverAllSummary();

		}
		else
		{
			cla.printManual();
		}
	}
	catch ( std::exception ex)
	{ std::cout<<"Application ended in error : "<<ex.what(); }
}
