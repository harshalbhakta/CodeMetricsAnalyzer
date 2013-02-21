#ifndef PACKAGEHOLDER_H
#define PACKAGEHOLDER_H
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PackageHolder.h (ver 1.0)  -  Class holder to hold multiple packages and perform add/update operations.    // 																					   
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

  This module holds a "map" that has the PackageName as the key and Package Object as the item.

  This module supports inserting & updating the package information.

  "map" used here will be static and will be shared by the Parser and Display module.

  For the parse phase, as the files will be parsed and analysed, relavent information will be stored in the "map.
  This information will be used by the display module to generate meaningful information.

  Public Interface:
  =================
  
  	 - addPackage(std::string,Package); // Add Package using Pacakge Name as key.

	 - getPackage(std::string);	// Get Package for use based on Package Name.

	 - getFilePackages();	// Get File Packages. Pair of ( .h & .cpp file name )
	 
	 - getFunctionList(std::string );	// Get List of Function Objects in a package.

	 - getPackageToPrint(std::string);	// Get List of Packages to Print.

	 - getControlList(std::string );	// Get List of Controls to print.

	 - addFunctionToPackage(std::string,Function);	// Add Function Object to list.

	 - addControlToPackage(std::string,Control);	// Add Control Object to list.

	 - addUpdateVariableToPackage(std::string,std::string, std::string,int,std::string,int,int);	// Add / Udate Variable Package.

	 - getDepthOfNesting(std::string);	// Get Depth of Nesting for a package.

	 - setDepthOfNesting(std::string,int);	// Set the Depth of Nesting for a package.

  Build Process:
  ==============
  Required files
    - Package.h, Package.cpp, PacakgeHandler.cpp
  Build commands
    - devenv CodeMetricsAnalyzer.sln /rebuild debug

  Maintenance History:
  ====================
  ver 1.0 : 25 Feb 11
  
*/

#include "Package.h"
#include <map>
#include <set>

class PackageHolder{

public :

	 static void addPackage(std::string,Package);

	 static std::vector<std::pair<std::string,std::string>> getFilePackages();
	 
	 static std::vector<Function> getFunctionList(std::string );

	 static Package PackageHolder::getPackageToPrint(std::string);

	 static std::set<std::string> PackageHolder::getPackageList();

	 static std::vector<Control> getControlList(std::string );

	 static void addFunctionToPackage(std::string,Function);

	 static void addControlToPackage(std::string,Control);

	 static void addUpdateVariableToPackage(std::string,std::string, std::string,int,std::string,int,int);

	 static int getDepthOfNesting(std::string);

	 static void setDepthOfNesting(std::string,int);

	 static void printPackage(std::string);

	 static void printFunctions(std::string);

	 static void printControls(std::string);

	 static void printVariables(std::string);

	 static void printSummary(std::string);

private :

	 static Package* getPackage(std::string);

	 static std::map<std::string,Package> PackageRepository;	 
};

#endif