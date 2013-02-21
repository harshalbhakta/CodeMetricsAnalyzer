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
//  ConfigureParser.cpp - builds and configures parsers            //
//  ver 1.1                                                        //
//                                                                 //
//  Lanaguage:     Visual C++ 2005                                 //
//  Platform:      Dell Dimension 9150, Windows XP SP2             //
//  Application:   Prototype for CSE687 Pr1, Sp06                  //
//  Author:        Jim Fawcett, CST 2-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////

#include "Parser.h"
#include "SemiExpression.h"
#include "Tokenizer.h"
#include "ActionsAndRules.h"
#include "ConfigureParser.h"
#include "ScopeStack.h"

///////////////////////////////////////////////////////////////////
///////////////////// Code Metrics Analyzer ///////////////////////
///////////////////////////////////////////////////////////////////

///////////////////// PASS - 1 ///////////////////////

//----< constructor initializes pointers to all parts >--------------

ConfigParseToAnalyze::ConfigParseToAnalyze() 
  : pToker(0), pSemi(0), pParser(0), NumberOfLines(0),forBuffer(0),
  pNewLine(0), pIncrementLineNumber(0), pCheckControlCount(0), pControlCountDetected(0),
  pCheckBraceScope(0), pDetectedBraceScope(0), pCheckFunction(0), pFunctionDetected(0),
  pCheckControl(0), pControlDetected(0), pCheckBuildFor(0), pDoBuildFor(0), pScopeStart(0),
  pDoScopeStart(0), pEndInSemiColon(0), pDoEndInSemiColon(0), pEndInBrace(0), pDoEndInBrace(0),
  pDetectObjectDeclaration(0), pdoDetectObjectDeclaration(0), pDetectNamespace(0), 
  pdoDetectNamespace(0), pCheckFunctionArgument(0), pDoCheckFunctionArgument(0){}

//----< destructor releases all parts >------------------------------

ConfigParseToAnalyze::~ConfigParseToAnalyze()
{
  // when Builder goes out of scope, everything must be deallocated
  delete NumberOfLines;
  delete forBuffer;
  delete pNewLine;
  delete pIncrementLineNumber;
  delete pCheckControlCount;
  delete pControlCountDetected;
  delete pCheckBraceScope;
  delete pDetectedBraceScope;
  delete pCheckFunction;
  delete pFunctionDetected;
  delete pCheckControl;
  delete pControlDetected;
  delete pCheckBuildFor;
  delete pDoBuildFor;
  delete pScopeStart;
  delete pDoScopeStart;
  delete pEndInSemiColon;
  delete pDoEndInSemiColon;
  delete pEndInBrace;
  delete pDoEndInBrace;
  delete pDetectObjectDeclaration;
  delete pdoDetectObjectDeclaration;
  delete pDetectNamespace;
  delete pdoDetectNamespace;
  delete pCheckFunctionArgument;
  delete pDoCheckFunctionArgument;
  delete pParser;
  delete pToker;
  delete pSemi;
}
//----< attach toker to a file stream or stringstream >------------

bool ConfigParseToAnalyze::Attach(const std::string& name, bool isFile)
{
  if(pToker == 0)
    return false;

  NumberOfLines = 0;

  return pToker->attach(name, isFile);
}
//
//----< Here's where alll the parts get assembled >----------------

Parser* ConfigParseToAnalyze::Build()
{
  try
  { // configure to detect and act on semi
    pToker = new Toker; pToker->returnComments();
    pSemi = new SemiExp(pToker); pSemi->makeCommentSemiExp();
    pParser = new Parser(pSemi);
	NumberOfLines = new int(0); forBuffer = new std::vector<std::string>();

	pCheckBuildFor = new CheckBuildFor(*forBuffer); pDoBuildFor = new DoBuildFor(*forBuffer,*NumberOfLines);
	pCheckBuildFor->addAction(pDoBuildFor); pParser->addRule(pCheckBuildFor);

	pCheckControlCount = new CheckControlCount; pControlCountDetected = new ControlCountDetected(*NumberOfLines);
	pCheckControlCount->addAction(pControlCountDetected); pParser->addRule(pCheckControlCount);

	pCheckBraceScope = new CheckBraceScope; pDetectedBraceScope = new DetectedBraceScope(*NumberOfLines);
	pCheckBraceScope->addAction(pDetectedBraceScope); pParser->addRule(pCheckBraceScope);

	pCheckFunction = new CheckFunction; pFunctionDetected = new FunctionDetected(*NumberOfLines);
	pCheckFunction->addAction(pFunctionDetected); pParser->addRule(pCheckFunction);

	pCheckControl = new CheckControl; pControlDetected = new ControlDetected(*forBuffer,*NumberOfLines);
	pCheckControl->addAction(pControlDetected); pParser->addRule(pCheckControl);

	pScopeStart = new ScopeStart; pDoScopeStart = new doScopeStart(*NumberOfLines);
	pScopeStart->addAction(pDoScopeStart); pParser->addRule(pScopeStart);

	pEndInSemiColon = new EndInSemiColon(*forBuffer); pDoEndInSemiColon = new doEndInSemiColon(*NumberOfLines);
	pEndInSemiColon->addAction(pDoEndInSemiColon); pParser->addRule(pEndInSemiColon);

	pEndInBrace = new EndInBrace; pDoEndInBrace = new doEndInBrace(*NumberOfLines);
	pEndInBrace->addAction(pDoEndInBrace); pParser->addRule(pEndInBrace);

	pDetectObjectDeclaration = new DetectObjectDeclaration; pdoDetectObjectDeclaration = new doDetectObjectDeclaration(*NumberOfLines);
	pDetectObjectDeclaration->addAction(pdoDetectObjectDeclaration); pParser->addRule(pDetectObjectDeclaration);

	pCheckFunctionArgument = new CheckFunctionArgument; pDoCheckFunctionArgument = new DoCheckFunctionArgument(*NumberOfLines);
	pCheckFunctionArgument->addAction(pDoCheckFunctionArgument); pParser->addRule(pCheckFunctionArgument);

	pDetectNamespace = new DetectNamespace; pdoDetectNamespace = new doDetectNamespace(*NumberOfLines);
	pDetectNamespace->addAction(pdoDetectNamespace); pParser->addRule(pDetectNamespace);

	pNewLine = new NewLine; pIncrementLineNumber = new IncrementLineNumber(*NumberOfLines);
	pNewLine->addAction(pIncrementLineNumber); pParser->addRule(pNewLine);
    return pParser;
  }
  catch(std::exception& ex)
  { std::cout << "\n\n  " << ex.what() << "\n\n"; return 0; }
}



	///////////////////// PASS - 2 ///////////////////////

//----< constructor initializes pointers to all parts >--------------

ConfigParsePassTwo::ConfigParsePassTwo() 
  : pToker(0), pSemi(0), pParser(0), NumberOfLines(0),forBuffer(0),
  pNewLine(0), pIncrementLineNumber(0), pCheckControlCount(0), pControlCountDetected(0),
  pCheckBraceScope(0), pDetectedBraceScope(0), pCheckFunction(0), pFunctionDetected(0),
  pCheckControl(0), pControlDetected(0), pCheckBuildFor(0), pDoBuildFor(0), pScopeStart(0),
  pDoScopeStart(0), pEndInSemiColon(0), pDoEndInSemiColon(0), pEndInBrace(0), pDoEndInBrace(0),
  pCheckTokenLocality(0), pdoCheckTokenLocality(0) {}

//----< destructor releases all parts >------------------------------

ConfigParsePassTwo::~ConfigParsePassTwo()
{
  // when Builder goes out of scope, everything must be deallocated
  delete NumberOfLines;
  delete forBuffer;
  delete pNewLine;
  delete pIncrementLineNumber;
  delete pCheckControlCount;
  delete pControlCountDetected;
  delete pCheckBraceScope;
  delete pDetectedBraceScope;
  delete pCheckFunction;
  delete pFunctionDetected;
  delete pCheckControl;
  delete pControlDetected;
  delete pCheckBuildFor;
  delete pDoBuildFor;
  delete pScopeStart;
  delete pDoScopeStart;
  delete pEndInSemiColon;
  delete pDoEndInSemiColon;
  delete pEndInBrace;
  delete pDoEndInBrace;
  delete pCheckTokenLocality;
  delete pdoCheckTokenLocality;
  delete pParser;
  delete pToker;
  delete pSemi;
}
//----< attach toker to a file stream or stringstream >------------

bool ConfigParsePassTwo::Attach(const std::string& name, bool isFile)
{
  if(pToker == 0)
    return false;

  NumberOfLines = 0;

  return pToker->attach(name, isFile);
}
//
//----< Here's where alll the parts get assembled >----------------

Parser* ConfigParsePassTwo::Build()
{
  try
  {
    // configure to detect and act on pass two

    pToker = new Toker; pToker->returnComments();
    pSemi = new SemiExp(pToker); pSemi->makeCommentSemiExp();
    pParser = new Parser(pSemi);
	NumberOfLines = new int(0); forBuffer = new std::vector<std::string>();

	// configure to add and actio to the rules.

	pCheckBuildFor = new CheckBuildFor(*forBuffer); pDoBuildFor = new DoBuildFor(*forBuffer,*NumberOfLines);
	pCheckBuildFor->addAction(pDoBuildFor); pParser->addRule(pCheckBuildFor);

	pCheckControlCount = new CheckControlCount; pControlCountDetected = new ControlCountDetected(*NumberOfLines);
	pCheckControlCount->addAction(pControlCountDetected); pParser->addRule(pCheckControlCount);

	pCheckBraceScope = new CheckBraceScope; pDetectedBraceScope = new DetectedBraceScope(*NumberOfLines);
	pCheckBraceScope->addAction(pDetectedBraceScope); pParser->addRule(pCheckBraceScope);

	pCheckFunction = new CheckFunction; pFunctionDetected = new FunctionDetected(*NumberOfLines);
	pCheckFunction->addAction(pFunctionDetected); pParser->addRule(pCheckFunction);

	pCheckControl = new CheckControl; pControlDetected = new ControlDetected(*forBuffer,*NumberOfLines);
	pCheckControl->addAction(pControlDetected); pParser->addRule(pCheckControl);

	pScopeStart = new ScopeStart; pDoScopeStart = new doScopeStart(*NumberOfLines);
	pScopeStart->addAction(pDoScopeStart); pParser->addRule(pScopeStart);
 
	pEndInSemiColon = new EndInSemiColon(*forBuffer); pDoEndInSemiColon = new doEndInSemiColon(*NumberOfLines);
	pEndInSemiColon->addAction(pDoEndInSemiColon); pParser->addRule(pEndInSemiColon);

	pEndInBrace = new EndInBrace; pDoEndInBrace = new doEndInBrace(*NumberOfLines);
	pEndInBrace->addAction(pDoEndInBrace); pParser->addRule(pEndInBrace);

	pCheckTokenLocality = new CheckTokenLocality; pdoCheckTokenLocality = new doCheckTokenLocality(*NumberOfLines);
	pCheckTokenLocality->addAction(pdoCheckTokenLocality); pParser->addRule(pCheckTokenLocality);

	pNewLine = new NewLine; pIncrementLineNumber = new IncrementLineNumber(*NumberOfLines);
	pNewLine->addAction(pIncrementLineNumber); pParser->addRule(pNewLine);

    return pParser;
  }
  catch(std::exception& ex)
  { std::cout << "\n\n  " << ex.what() << "\n\n"; return 0; }
}

#ifdef TEST_ANALYZER_PARSER

#include <queue>
#include <string>

int main(int argc, char* argv[])
{
  std::cout << "\n  Testing ConfigureAnalyzer module\n "
            << std::string(32,'=') << std::endl;

  // collecting tokens from files, named on the command line

  if(argc < 2)
  {
    std::cout 
      << "\n  please enter name of file to process on command line\n\n";
    return 1;
  }

  for(int i=1; i<argc; ++i)
  {
    std::cout << "\n  Processing file " << argv[i];
    std::cout << "\n  " << std::string(16 + strlen(argv[i]),'-');

    ConfigParseToAnalyze configure;
    Parser* pParser = configure.Build();
    try
    {
      if(pParser)
      {
        if(!configure.Attach(argv[i]))
        {
          std::cout << "\n  could not open file " << argv[i] << std::endl;
          continue;
        }
      }
      else
      {
        std::cout << "\n\n  Parser not built\n\n";
        return 1;
      }
      // now that parser is built, use it

	  std::cout << "\n\n  Parser Parsing File\n\n";

      while(pParser->next())
        pParser->parse();
      std::cout << "\n\n";

	  std::cout << "\n\n  Parsing Complete\n\n";

	  showStack<std::string, ScopeElement>(false);

    }
    catch(std::exception& ex)
    {
      std::cout << "\n\n    " << ex.what() << "\n\n";
    }


//
    std::cout << "\n\n";
  }
  std::getchar();
}

#endif
