#ifndef SHOW_H
#define SHOW_H
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Show.h (ver 1.0)  -  Module to display analysis results.													  // 																					   
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

  This module is responsible for displaying the results for the analysis.

  Public Interface:
  =================
  
  printFunctions(Package) -> Print statistics related to functions.

  printControls(Package) -> Print statistics related to Controls.

  printVariables(Package) -> Print statistics related to Variables.

  printSummary(Package) -> Print summary statistics.

  Build Process:
  ==============
  Required files
    - PackageHolder.h , Package.h , PackageHolder.cpp , Package.cpp
  Build commands
    - devenv CodeMetricsAnalyzer.sln /rebuild debug

  Maintenance History:
  ====================
  ver 1.0 : 25 Feb 11
 
*/

#include <string>
#include <vector>
#include "PackageHolder.h"
#include "Package.h"

class Show
{

public : 

	static void printNormal(std::string);

	static void printVerbose(std::string);

	static void printHeader();

	static void printOverAllSummary();

private :

	static int CalculateNumberOfIdentifiers(Package);

	static void printFunctions(Package);

	static void printControls(Package);

	static void printVariables(Package);

	static void printSummary(Package);

	static void printVerboseFunctions(Package);

	static void printVerboseControls(Package);

	static void printVerboseVariables(Package);

	static void printOverAllStatistics(std::vector<Function>,std::vector<Control>,std::vector<Variable>);

	static void Show::getExceededFunction(Package,std::vector<Function>&,int&,int&);
	
	static void getExceededControl(Package,std::vector<Control>&,int&);

	static void getExceededVariable(Package,std::vector<Variable>&,int&,int&);

};

#endif