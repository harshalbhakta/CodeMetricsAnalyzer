#ifndef EXECUTIVE_H
#define EXECUTIVE_H
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Executive.h (ver 1.0)  -  Executive Module that Starts the Analysis & Prints Summay output.	     		  // 																					   
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

  This module acts as the executive controller. It fetches the list of the files from 
  the CmdLineAgrs. It further used the ConfigureParser module to parse the files.
  Once the files are parsed, Executive controller uses the Display module to display summary 
  of the analysis.

  Works with CmdLineArgs, ConfigureParser & Display module for analysis.

  Public Interface:
  =================
  
  Executive ex(std::vector<std::string>); 

  ex.AnalyzeFiles();

  Build Process:
  ==============
  Required files
    - WinTools.h,DataStore.h,Tokenizer.h,SemiExpression.h,
	  Parser.h,ActionsAndRules.h,ConfigureParser.h,
	  Executive.h,DataStore.h, Show.h
  Build commands
    - devenv Project1HelpS06.sln

  Maintenance History:
  ====================
  ver 1.0 : 25 Feb 11
  - first release
*/
#include <string>
#include <iostream>
#include <vector>
#include "WinTools.h"
#include "DataStore.h"

using namespace Win32Tools;

class Executive{

public :

	Executive(std::vector<std::string>);

	void FirstPass();

	void SecondPass();

	void AnalyzeFiles();

	std::string ExtractPackageNamePassTwo(std::string);

	std::string ExtractPackageNamePassOne(std::string);

private : 

	void SecondPassParse(std::string);

	std::vector<std::string> ptrFiles;

};

#endif