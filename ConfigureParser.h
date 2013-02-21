#ifndef CONFIGUREPARSER_H
#define CONFIGUREPARSER_H
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ConfigureParser.h - Added ConfigParsePassTwo for second pass.											  // 																					   
//	ver 1.2             Added More Rules & Actions.															  //	
//																											  //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #1 - CodeMetricsAnalyzer, Spring 2011								  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//  ConfigureParser.h - builds and configures parsers              //
//  ver 1.1                                                        //
//                                                                 //
//  Lanaguage:     Visual C++ 2005                                 //
//  Platform:      Dell Dimension 9150, Windows XP SP2             //
//  Application:   Prototype for CSE687 Pr1, Sp06                  //
//  Author:        Jim Fawcett, CST 2-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================
  This module builds and configures parsers.  It builds the parser
  parts and configures them with application specific rules and actions.
  It currently defines two builders, one for the first pass and other
  for the second pass.
  

  Public Interface:
  =================
  ConfigParseToAnalyze conConfig;
  conConfig.Build();
  conConfig.Attach(someFileName);

  ConfigParsePassTwo conConfig;
  conConfig.Build();
  conConfig.Attach(someFileName);

  Build Process:
  ==============
  Required files
    - ConfigureParser.h, ConfigureParser.cpp, Parser.h, Parser.cpp,
      ActionsAndRules.h, ActionsAndRules.cpp,
      SemiExpression.h, SemiExpression.cpp, tokenizer.h, tokenizer.cpp
  Build commands (either one)
    - devenv CodeMetricsAnalyzer.sln /rebuild debug

  Maintenance History:
  ====================
  ver 1.2 : 25 Feb 11
  - Customized to include ConfigParseToAnalyze & ConfigParsePassTwo
  ver 1.1 : 01 Feb 06
  - cosmetic changes to ConfigureParser.cpp
  ver 1.0 : 12 Jan 06
  - first release

*/

//
#include "Parser.h"
#include "SemiExpression.h"
#include "Tokenizer.h"
#include "ActionsAndRules.h"

///////////////////////////////////////////////////////////////
// build parser that analyzes C++ Files. ( 1st Pass )

class ConfigParseToAnalyze : IBuilder
{
public:
  ConfigParseToAnalyze();
  ~ConfigParseToAnalyze();
  bool Attach(const std::string& name, bool isFile=true);
  Parser* Build();

private:
  // Builder must hold onto all the pieces

  Toker* pToker;
  SemiExp* pSemi;
  Parser* pParser;

  int* NumberOfLines;
  std::vector<std::string>* forBuffer;

  // and the the Rules and Actions as well

  NewLine* pNewLine;
  IncrementLineNumber* pIncrementLineNumber;

  CheckControlCount* pCheckControlCount;
  ControlCountDetected* pControlCountDetected;

  CheckBraceScope* pCheckBraceScope;
  DetectedBraceScope* pDetectedBraceScope;

  CheckFunction* pCheckFunction;
  FunctionDetected* pFunctionDetected;

  CheckControl* pCheckControl;
  ControlDetected* pControlDetected;

  CheckBuildFor* pCheckBuildFor;
  DoBuildFor* pDoBuildFor;

  ScopeStart* pScopeStart;
  doScopeStart* pDoScopeStart;

  EndInSemiColon* pEndInSemiColon;
  doEndInSemiColon* pDoEndInSemiColon;

  EndInBrace* pEndInBrace;
  doEndInBrace* pDoEndInBrace;

  DetectObjectDeclaration* pDetectObjectDeclaration;
  doDetectObjectDeclaration* pdoDetectObjectDeclaration;

  DetectNamespace* pDetectNamespace;
  doDetectNamespace* pdoDetectNamespace;

  CheckFunctionArgument* pCheckFunctionArgument;
  DoCheckFunctionArgument* pDoCheckFunctionArgument;

  // prohibit copies and assignments

  ConfigParseToAnalyze(const ConfigParseToAnalyze&);
  ConfigParseToAnalyze& operator=(const ConfigParseToAnalyze&);
};

///////////////////////////////////////////////////////////////
// build parser that analyzes C++ Files. ( 2nd Pass )

class ConfigParsePassTwo : IBuilder
{
public:
  ConfigParsePassTwo();
  ~ConfigParsePassTwo();
  bool Attach(const std::string& name, bool isFile=true);
  Parser* Build();

private:
  // Builder must hold onto all the pieces

  Toker* pToker;
  SemiExp* pSemi;
  Parser* pParser;

  int* NumberOfLines;
  std::vector<std::string>* forBuffer;

  // and the the Rules and Actions as well

  NewLine* pNewLine;
  IncrementLineNumber* pIncrementLineNumber;

  CheckControlCount* pCheckControlCount;
  ControlCountDetected* pControlCountDetected;

  CheckBraceScope* pCheckBraceScope;
  DetectedBraceScope* pDetectedBraceScope;

  CheckFunction* pCheckFunction;
  FunctionDetected* pFunctionDetected;

  CheckControl* pCheckControl;
  ControlDetected* pControlDetected;

  CheckBuildFor* pCheckBuildFor;
  DoBuildFor* pDoBuildFor;

  ScopeStart* pScopeStart;
  doScopeStart* pDoScopeStart;

  EndInSemiColon* pEndInSemiColon;
  doEndInSemiColon* pDoEndInSemiColon;

  EndInBrace* pEndInBrace;
  doEndInBrace* pDoEndInBrace;

  CheckTokenLocality* pCheckTokenLocality;
  doCheckTokenLocality* pdoCheckTokenLocality;

  // prohibit copies and assignments

  ConfigParsePassTwo(const ConfigParseToAnalyze&);
  ConfigParsePassTwo& operator=(const ConfigParseToAnalyze&);
};

#endif
