#ifndef ACTIONSANDRULES_H
#define ACTIONSANDRULES_H
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ActionsAndRules.h - Added Customized rules for Pass 1 & Pass 2.											  // 																					   
//	ver 1.2																									  //	
//																											  //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #1 - CodeMetricsAnalyzer, Spring 2011								  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//  ActionsAndRules.h - declares new parsing rules and actions     //
//  ver 1.1                                                        //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Dell Precision T7400, Vista Ultimate SP1        //
//  Application:   Prototype for CSE687 Pr1, Sp09                  //
//  Author:        Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================
  This module defines several action classes.  Its classes provide 
  specialized services needed for specific applications.  The modules
  Parser, SemiExpression, and Tokenizer, are intended to be reusable
  without change.  This module provides a place to put extensions of
  these facilities and is not expected to be reusable.
  

  Public Interface:
  =================
  Toker t(someFile);              // create tokenizer instance
  SemiExp se(&t);                 // create a SemiExp attached to tokenizer
  Parser parser(se);              // now we have a parser
  Rule1 r1;                       // create instance of a derived Rule class
  Action1 a1;                     // create a derived action
  r1.addAction(&a1);              // register action with the rule
  parser.addRule(&r1);            // register rule with parser
  while(se.getSemiExp())          // get semi-expression
  parser.parse();               //   and parse it

  Build Process:
  ==============
  Required files
    - Parser.h, Parser.cpp, ActionsAndRules.h, ActionsAndRules.cpp,
      SemiExpression.h, SemiExpression.cpp, tokenizer.h, tokenizer.cpp
	  ScopeStack.h, DataStore.h, PackageHolder.h, ScopeStack.cpp
	  DataStore.cpp, PackageHolder.cpp 
  Build commands (either one)
    - devenv CodeMetricsAnalyzer.sln /rebuild debug

  Maintenance History:
  ====================
  ver 1.2 : 25 Feb 11
  - Add Custom Rules & Actions for Pass 1 & Pass 2.
  ver 1.1 : 17 Jan 09
  - changed to accept a pointer to interfaced ITokCollection instead
    of a SemiExpression
  ver 1.0 : 12 Jan 06
  - first release

*/
//
#include <queue>
#include <string>
#include "Parser.h"
#include "ITokCollection.h"
#include "ScopeStack.h"
#include "DataStore.h"
#include "PackageHolder.h"

///////////////////////////////////////////////////////////////
// Class with Static Method to calculate number of lines.
// Shared by all the classes for rules.
class NumberOfLines{

public : 

	static int getLineNumber(ITokCollection*,int, int);

};



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////// Rules & Action for CodeMetricsAnalyzer //////////////////////
/////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// rule to check for new line.
class NewLine : public IRule
{
public:	
  bool doTest(ITokCollection* );
};

///////////////////////////////////////////////////////////////
// action to increment the line number
class IncrementLineNumber : public IAction
{

int* pNumberOfLines;

public:
  
  IncrementLineNumber(int& );

  void doAction(ITokCollection* );

};

///////////////////////////////////////////////////////////////
// rule to detect scope start : {
class CheckBraceScope : public IRule
{
public:

  bool doTest(ITokCollection* );

};

///////////////////////////////////////////////////////////////
// action to be taken when scope starts : {
class DetectedBraceScope : public IAction
{

int* pNumberOfLines;

public:

   DetectedBraceScope(int& noOfLines);

  void doAction(ITokCollection* );

};

///////////////////////////////////////////////////////////////
// rule to detect Control Count for analyzis
class CheckControlCount : public IRule
{
public:
  bool isSpecialKeyWord(const std::string& );

  bool doTest(ITokCollection* );
};

///////////////////////////////////////////////////////////////
// action to handle the control count.
class ControlCountDetected : public IAction
{

int* pNumberOfLines;

public:

   ControlCountDetected(int& );

    bool isSpecialKeyWord(const std::string& );

   void doAction(ITokCollection* );

};

///////////////////////////////////////////////////////////////
// rule to detect function for analysis
class CheckFunction : public IRule
{
public:
  
	bool isSpecialKeyWord(const std::string& );

  bool doTest(ITokCollection* );

};

///////////////////////////////////////////////////////////////
// action to be taken when a function is detected.
class FunctionDetected : public IAction
{

int* pNumberOfLines;

  bool isOperator(const std::string& );

public:

   FunctionDetected(int& );

   void doAction(ITokCollection* );

};

///////////////////////////////////////////////////////////////
// rule to detect control statement for analyzis
class CheckControl : public IRule
{
public:
  bool isControlKeyWord(const std::string& );

  bool doTest(ITokCollection* );
};

///////////////////////////////////////////////////////////////
// action when Control is detected.
class ControlDetected : public IAction
{

std::vector<std::string>* pForBuffer;

int* pNumberOfLines;

public:

	 bool isControlKeyWord(const std::string& );

  ControlDetected(std::vector<std::string>& ,int& );

  void CheckTryCatch(std::string,ITokCollection*,int);

  // Actions combined for all control statments for handling : while ( true ) if ( true ) while ( true ) {
  void doAction(ITokCollection*);

  void handleFor(ITokCollection* ,int );

  void handleWhile(ITokCollection* ,int );

  void handleSwitch(ITokCollection* ,int );

  void handleTry(ITokCollection* ,int );

  void handleCatch(ITokCollection* ,int );

  void handleIf(ITokCollection* ,int );

  void handleForEach(ITokCollection* ,int );

  void handleElse(ITokCollection* ,int );

  void handleDo(ITokCollection* ,int );

};

///////////////////////////////////////////////////////////////
// rule to build up for loop
class CheckBuildFor : public IRule
{

std::vector<std::string>* pForBuffer;

public:

  CheckBuildFor(std::vector<std::string>& );

  bool doTest(ITokCollection* );

};

///////////////////////////////////////////////////////////////
// action to Build For
class DoBuildFor : public IAction
{

std::vector<std::string>* pForBuffer;

int* pNumberOfLines;

public:

  DoBuildFor(std::vector<std::string>&,int&);

  void doAction(ITokCollection*);

};

///////////////////////////////////////////////////////////////
// rule to detect {
class ScopeStart : public IRule
{
public:

  bool doTest(ITokCollection*);

};

///////////////////////////////////////////////////////////////
// action when a new scope starts
class doScopeStart : public IAction
{

int* pNumberOfLines;

public:

  doScopeStart(int& );

  void doAction(ITokCollection*);

};

///////////////////////////////////////////////////////////////
// rule to detect if the semi ends in ";"
class EndInSemiColon : public IRule
{

std::vector<std::string> *pForBuffer;

public:

  EndInSemiColon(std::vector<std::string>& );

  bool doTest(ITokCollection*);

};

///////////////////////////////////////////////////////////////
// action for semi ending in ;
class doEndInSemiColon : public IAction
{

int *pNumberOfLines;

public:

  doEndInSemiColon(int&);

  void doAction(ITokCollection*);

};

///////////////////////////////////////////////////////////////
// rule to detect if the semi ends in "}"
class EndInBrace : public IRule
{
public:

  bool doTest(ITokCollection*);

};

///////////////////////////////////////////////////////////////
// action for semi ending in }
class doEndInBrace : public IAction
{

int *pNumberOfLines;

public:

  doEndInBrace(int&);

  void doAction(ITokCollection*);

};

///////////////////////////////////////////////////////////////
// rule to detect object declaration.
class DetectObjectDeclaration : public IRule
{
public:

  bool doTest(ITokCollection*);

};

///////////////////////////////////////////////////////////////
// action to handle object declaration
class doDetectObjectDeclaration : public IAction
{

int *pNumberOfLines;

std::vector<std::string> removeAssignment(std::vector<std::string>);

std::vector<std::string> removeQualifiers(std::vector<std::string>);

public:

  doDetectObjectDeclaration(int&);

  void doAction(ITokCollection*);

};

///////////////////////////////////////////////////////////////
// rule to detect declaration in function argument
class CheckFunctionArgument : public IRule
{
public:
  bool isSpecialKeyWord(const std::string&);

  bool doTest(ITokCollection*);

};

///////////////////////////////////////////////////////////////
// action to handle declaration in function argument.
class DoCheckFunctionArgument : public IAction
{

int* pNumberOfLines;

std::vector<std::string> removeAssignment(std::vector<std::string>);

std::vector<std::string> removeQualifiers(std::vector<std::string>);

public:

   DoCheckFunctionArgument(int&);

   void doAction(ITokCollection*);

};

///////////////////////////////////////////////////////////////
// rule to detect namespace
class DetectNamespace : public IRule
{
public:

  bool doTest(ITokCollection*);

};

///////////////////////////////////////////////////////////////
// action to add namespace related to a file
class doDetectNamespace : public IAction
{

int *pNumberOfLines;

public:

  doDetectNamespace(int&);

  void doAction(ITokCollection*);

};

///////////////////////////////////////////////////////////////
// rule to check Locality of Refrence : PASS 2
class CheckTokenLocality : public IRule
{
public:

  bool doTest(ITokCollection*);

};

///////////////////////////////////////////////////////////////
// action to Set Locality of Reference & Density : PASS 2
class doCheckTokenLocality : public IAction
{

int *pNumberOfLines;

public:

  doCheckTokenLocality(int&);

  void headerFileDetection(ITokCollection*);

  void sourceFileDetection(ITokCollection*);

  void checkNameSpaceList(std::string,ITokCollection*,int);

  void doAction(ITokCollection*);

  std::vector<std::string> GetAllPossibleScope(std::string);
 
};

#endif
