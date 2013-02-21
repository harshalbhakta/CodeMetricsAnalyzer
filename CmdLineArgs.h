#ifndef CMDLINEARGS_H
#define CMDLINEARGS_H
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CmdLineArgs.h (ver 1.0)  -  Store and Validate Command Line Arguments.									  // 																					   
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

  This module defines a CmdLineArgs class. Its instance will be used to handle
  command line arguments. We need minimum 3 command line arguments. 

  Exactly Once : argv[1] : Recurse Option : -r Or -nr
  Exactly Once : argv[2] : File Pattern   : *.* ( Selection criteria to choose file )
  Atleast Once : argv[3] : Path Spces	   : ..\Parser ( Folder Location )
				 argv[.] : .............. : ( Folder Location )
				 argv[.] : .............. : ( Folder Location )
				 argv[.] : .............. : ( Folder Location )
				 argv[N] : .............. : ( Folder Location )

				 argv[3] To argv[N] = Folder Path Specifications.

  If initial -r/-nr option is ommited, we return error message.

  If number of command line arguments is < 3, we return error message.

  Public Interface:
  =================
  
  CmdLineArgs cla;	// Create Object

  if ( cla.ValidateAndStoreArgs(argc,argv) ) //  Validate and Analyze Arguments

  cla.getFiles();	// Get vector of files to analyze.

  Build Process:
  ==============
  Required files
    - WinTools.h,wintools.cpp, fileInfo.h, fileInfo.cpp
	- StringConversions.h,StringConversions.cpp,Nav.h,Nav.cpp
  Build commands
    - devenv CodeMetricsAnalyzer.sln /rebuild debug

  Maintenance History:
  ====================
  ver 1.0 : 25 Feb 11
  - changed SemiExp::getSemiExp() to SemiExp::get()
*/
#include <string>
#include <iostream>
#include <vector>
#include "WinTools.h"

using namespace Win32Tools;

class CmdLineArgs{

public :

	CmdLineArgs();

	bool ValidateAndStoreArgs(int argc,char* argv[]);

	void printValidFiles();

	void printManual();

	std::vector<std::string> getFiles();

	bool isRecurse();

	std::vector<std::string> getFilePattern();

	std::string getPathSpecs();

private : 

	bool recurse;
	std::string pathSpec;
	std::vector<std::string> filePattern;
	std::vector<std::string> files;

	void fetchFiles();

};

#endif