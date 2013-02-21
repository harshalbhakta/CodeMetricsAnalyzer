#ifndef CUSTOMNAVIGATE_H
#define CUSTOMNAVIGATE_H
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CustomNavigate.h (ver 1.0)  -  Module to parse the directory and fetch files based on cmd arguments		  // 																					   
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

  This module takes the Directory Path,File Pattern and recurse flag as input. Based on the input arguments 
  provided, this module traveses through the Directory Structure recursively or non - recursively. Files are 
  picked up from the directories while traversing based on the file patter taken as input.

  Public Interface:
  =================
  
  CustomNavigate cn;	// Create Object

  std::vector<std::string>listFiles = cn.getFiles(tempDirs,tempPattern,recurse); // Call Function to fetch files.
	
  cn.printFileInfo();	// Print the list of valid files.

  Build Process:
  ==============
  Required files
    - WinTools.h,wintools.cpp, fileInfo.h, fileInfo.cpp
	- StringConversions.h,StringConversions.cpp,Nav.h,Nav.cpp,CustomNavigate.cpp
  Build commands
    - devenv CodeMetricsAnalyzer.sln /rebuild debug

  Maintenance History:
  ====================
  ver 1.0 : 25 Feb 11
  - changed SemiExp::getSemiExp() to SemiExp::get()
*/


#include <string>
#include <windows.h>
#include "StringConversion.h"
#include <vector>

namespace Win32Tools
{
  class CustomNavigate {

  public : 

	  std::vector<std::string> getFiles(std::string,std::vector<std::string>,bool);

	  void printFileInfo();

  private : 

	  bool validateDirectory(std::string);

	  void Walk(std::string,std::vector<std::string>,bool);

	  void addFile(std::string,std::string);

	  std::vector<std::string> files;

	  std::vector<std::string> invalidDirectoryPath;

	  std::vector<std::string> ignoredFiles;

  };

}

#endif