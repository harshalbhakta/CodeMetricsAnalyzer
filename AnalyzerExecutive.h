#ifndef ANALYZEREXECUTIVE_H
#define ANALYZEREXECUTIVE_H
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
  Toker t;                                  // create tokenizer instance
  SemiExp se(&t);                           // create instance and attach
  if(se.get())                              // collect a semiExpression
    std::cout << se.showSemiExp().c_str();  // show it
  int n = se.length();                      // number of tokens in se
  std::string tok = se[2] = "a change";     // indexed read and write
  if(se.find("aTok") < se.length())         // search for a token
    std::cout << "found aTok";  
  se.clear();                               // remove all tokens

  Build Process:
  ==============
  Required files
    - SemiExpression.h, SemiExpression.cpp, Tokenizer.h, Tokenizer.cpp
  Build commands (either one)
    - devenv Project1HelpS06.sln
    - cl /EHsc /DTEST_SEMIEXPRESSION SemiExpression.cpp Tokenizer.cpp \
         /link setargv.obj

  Maintenance History:
  ====================
  ver 1.3 : 17 Jan 09
  - changed SemiExp::getSemiExp() to SemiExp::get()
  - changed SemiExp::showSemiExp() to SemiExp::show()
  - added scope walker to test stub
  ver 1.2 : 10 Feb 06
  - fixed bug in SemiExp::getSemiExp() that caused failure to return
    last group of tokens as a semi-expression if the last character
    in source is not a newline.
  ver 1.1 : 01 Feb 06
  - added an option to return comments as semi-expressions
  - added test, isComment(const std::string& tok)
  ver 1.0 : 12 Jan 06
  - first release
*/
#include <string>
#include <vector>

class AnalyzerExecutive{

public :

private :


};

#endif


