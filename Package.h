#ifndef PACKAGE_H
#define PACKAGE_H
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Package.h (ver 1.0)  -  Class to hold information about each package ( .h + .cpp ) file.					  // 																					   
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

  This module defines a Package class that will hold the information related to each package.

  Part 1 ) Function
  Part 2 ) Variable 
  Part 3 ) Control

  This module will basically hold the information related to the above mentioned parts. The 
  statistics related to the analysis of the header and the source files will be stored in
  the sub modules. 

  Function : Holds information related to the functions detected.

			 Function Name - no_of_lines - cyclo_complexity - scope - from_line - to_line;

  Variable : Holds information related to the variables detected.

			 Variable Name - fromFile - fromLine - toFile - toLine - loc_reference - ref_density

  Control  : Holds informaiton related to the controls detected.

			 Control Name - breadthControlSpan - scope - from_line - to_line

  Public Interface:
  =================
  
  Package pk;

  Function fk;

  fk.setFunctionName("Test");
  fk.setNoOfLines(12);
  fk.setDepthOfNesting(20);
  fk.setCycloComplexity(15);

  Variable vb;

  vb.setVariableName("LocOfReference");
  vb.setLocReference(20);
  vb.setRefDensity(5);

  Control ct;

  ct.setControlName("For");

  pk.addFunction(fk);
  pk.addControl(ct);
  pk.addVariable(vb);

  Build Process:
  ==============
  Required files
    - Package.cpp
  Build commands
    - devenv CodeMetricsAnalyzer.sln /rebuild debug

  Maintenance History:
  ====================
  ver 1.0 : 25 Feb 11
  
*/

#include <string>
#include <vector>

///////////////////////////////////////////////////////////////
// Class to hold information relate the function.
class Function
{

public : 

std::string getFunctionName();
void setFunctionName(std::string);

int getNoOfLines();
void setNoOfLines(int);

int getCycloComplexity();
void setCycloComplexity(int);

std::string getScope();
void setScope(std::string);

int getFromLine();
void setFromLine(int);

int getToLine();
void setToLine(int );

Function();

private :

std::string name;
int no_of_lines;
int cyclo_complexity;
std::string scope;
int from_line;
int to_line;

};

inline Function::Function() : name("XXXXX"),no_of_lines(0),cyclo_complexity(0),scope("XXXXX"),from_line(0),to_line(0) {}

inline std::string Function::getFunctionName() { return name; }
inline void Function::setFunctionName(std::string nm) { name = nm; }

inline int Function::getNoOfLines() { return no_of_lines; }
inline void Function::setNoOfLines(int lines) { no_of_lines = lines; }

inline int Function::getCycloComplexity() { return cyclo_complexity; }
inline void Function::setCycloComplexity(int cyclo) { cyclo_complexity = cyclo; }

inline std::string Function::getScope() { return scope; }
inline void Function::setScope(std::string sc) { scope = sc; }

inline int Function::getFromLine() { return from_line; }
inline void Function::setFromLine(int frm) { from_line = frm; }

inline int Function::getToLine() { return to_line; }
inline void Function::setToLine(int tl) { to_line = tl; }

///////////////////////////////////////////////////////////////
// Class to hold information related to variables.
class Variable
{

public : 

std::string getVariableName();
void setVariableName(std::string);

std::string getFromFileName();
void setFromFileName(std::string);

int getFromFileLine();
void setFromFileLine(int);

std::string getToFileName();
void setToFileName(std::string);

int getToFileLine();
void setToFileLine(int);

int getLocReference();
void setLocReference(int);

int getRefDensity();
void setRefDensity(int);

Variable();

private :

std::string name;
std::string fromFile;
int fromLine;
std::string toFile;
int toLine;
int loc_reference;
int ref_density;

};

inline Variable::Variable() : name("XXXXX"),fromFile("XXXXX"),fromLine(0),toFile("XXXXX"),toLine(0),loc_reference(0),ref_density(0)
{}

inline std::string Variable::getVariableName() { return name; }
inline void Variable::setVariableName(std::string nm) { name = nm; }

inline std::string Variable::getFromFileName() { return fromFile; }
inline void Variable::setFromFileName(std::string ff) { fromFile = ff; }

inline int Variable::getFromFileLine() { return fromLine; }
inline void Variable::setFromFileLine(int fl) { fromLine = fl; }

inline std::string Variable::getToFileName() { return toFile; }
inline void Variable::setToFileName(std::string tf) { toFile = tf; }

inline int Variable::getToFileLine() { return toLine; }
inline void Variable::setToFileLine(int tl) { toLine = tl; }

inline int Variable::getLocReference() { return loc_reference; }
inline void Variable::setLocReference(int loc) { loc_reference = loc; }

inline int Variable::getRefDensity() { return ref_density; }
inline void Variable::setRefDensity(int density) { ref_density = density; }

///////////////////////////////////////////////////////////////
// Class to hold information related to Control.
class Control
{

public :

std::string getControlName();
void setControlName(std::string);

int getBreadthControlSpan();
void setBreadthControlSpan(int);

std::string getScope();
void setScope(std::string);

int getFromLine();
void setFromLine(int);

int getToLine();
void setToLine(int );

Control();

private :

std::string name; 
int breadthControlSpan;
std::string scope;
int from_line;
int to_line;

};

inline Control::Control() : name("XXXXX"),breadthControlSpan(0),scope("XXXXX"),from_line(0),to_line(0) {}

inline std::string Control::getControlName() { return name; }
inline void Control::setControlName(std::string nm) { name = nm; } 

inline int Control::getBreadthControlSpan() { return breadthControlSpan; } 
inline void Control::setBreadthControlSpan(int bcs) { breadthControlSpan = bcs; }

inline std::string Control::getScope() { return scope; }
inline void Control::setScope(std::string sc) { scope = sc; }

inline int Control::getFromLine() { return from_line; }
inline void Control::setFromLine(int frm) { from_line = frm; }

inline int Control::getToLine() { return to_line; }
inline void Control::setToLine(int tl) { to_line = tl; }

///////////////////////////////////////////////////////////////
// Class to hold information related to function,variables & controls.
// A list will be maintined.
class Package
{

public :

	void addControl(Control);
	void addFunction(Function);
	void addVariable(std::string,std::string, std::string ,int,std::string,int,int);

	int getDepthOfNesting();
	void setDepthOfNesting(int);

	std::string getSourceFile();
	void setSourceFile(std::string);

	std::string getHeaderFile();
	void setHeaderFile(std::string);

	
	std::vector<Variable> getVariableListPrint();
	std::vector<Function> getFunctionList();
	std::vector<Control> getControlList();

private : 

std::vector<Variable>* getVariableList();

std::vector<Variable> VariableList;
std::vector<Function> FunctionList;
std::vector<Control> ControlList;

int number_of_identifiers;
int depth_of_nesting;

std::string header_file;
std::string source_file;

};

inline std::vector<Variable>* Package::getVariableList() { return &VariableList; }
inline std::vector<Variable> Package::getVariableListPrint() { return VariableList; }
inline std::vector<Function> Package::getFunctionList() { return FunctionList; }
inline std::vector<Control> Package::getControlList() { return ControlList; }

inline int Package::getDepthOfNesting() { return depth_of_nesting; }
inline void Package::setDepthOfNesting(int depth) { depth_of_nesting = depth; }

inline std::string Package::getSourceFile(){ return source_file; }
inline void Package::setSourceFile(std::string src) { source_file = src ;} 

inline std::string Package::getHeaderFile(){ return header_file; }
inline void Package::setHeaderFile(std::string hd){ header_file = hd; }

#endif