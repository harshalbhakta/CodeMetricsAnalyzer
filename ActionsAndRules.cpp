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
//  ActionsAndRules.cpp - implements new parsing rules and actions //
//  ver 1.1                                                        //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Dell Precision T7400, Vista Ultimate SP1        //
//  Application:   Prototype for CSE687 Pr1, Sp09                  //
//  Author:        Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////

#include "ActionsAndRules.h"

///////////////////////////////////////////////////////////////
// Class with Static Method to calculate number of lines.

	int NumberOfLines::getLineNumber(ITokCollection* pTc,int currIndex, int prevLineNumber)
	{
	
	  int tempNewLine = 0;

	  ITokCollection& tc = *pTc;
	  for ( int i = 0 ; i < currIndex ; i++ )
	  {
				if ( tc[i] == "\n" )
					tempNewLine++;

				if ( tc[i].find_first_of("//") == 0 || tc[i].find_first_of("/*") == 0 )
				{ // if semi is comment, check for multiple new line.
					for ( int k = 0 ; k < (int)tc[i].length() ; k++)
					{
						if ( tc[i][k] == '\n')
							tempNewLine++;
					}
				} 
	  }
	  return tempNewLine + prevLineNumber;
	
	}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////// Rules & Action for CodeMetricsAnalyzer //////////////////////
/////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// rule to count line number
  bool NewLine::doTest(ITokCollection* pTc)
  {
			doActions(pTc);
			return true;  
  }


///////////////////////////////////////////////////////////////
// action to increment the line number

///////////////////////////////////////////////////////////////
// Constructor to get previous number of lines
IncrementLineNumber::IncrementLineNumber(int& noOfLines) : pNumberOfLines(&noOfLines)
{ }

///////////////////////////////////////////////////////////////
// Function to increment number of lines by detecting new-line.
 void IncrementLineNumber::doAction(ITokCollection* pTc)
{
ITokCollection& tc = *pTc;

if ( *pNumberOfLines == 0 && tc.length() != 0 )
{ *pNumberOfLines = 1; }

for ( int i = 0 ; i < tc.length() ; i++ )
{
		if ( tc[i] == "\n" )
			*pNumberOfLines = *pNumberOfLines + 1;

		int z = tc[i].find("/*");

		if ( tc[i].find_first_of("//") == 0 || tc[i].find_first_of("/*") == 0 )
		{   // if semi is comment, look for multiple new line.
			for ( int k = 0 ; k < (int)tc[i].length() ; k++)
			{
				if ( tc[i][k] == '\n')
					*pNumberOfLines = *pNumberOfLines + 1;
			}

		} 
}

DataStore::setCurrent_File_Size(*pNumberOfLines);

}

///////////////////////////////////////////////////////////////
// rule to detect class,enum , struct, namespace for analyzis
bool CheckBraceScope::doTest(ITokCollection* pTc)
{

ITokCollection& tc = *pTc;

if(tc[tc.length()-1] == "{" && tc.length() > 1 && tc[tc.length()-2] != ")" )
{
	if ( tc.find("class") < tc.length() || tc.find("struct") < tc.length() || tc.find("enum") < tc.length() || tc.find("namespace") < tc.length() )
	{
			doActions(pTc);
			return true;
	}
}
return false;
}

///////////////////////////////////////////////////////////////
// action to detect Class, enum , struct , namespace

///////////////////////////////////////////////////////////////
// Constructor to get previous number of lines
DetectedBraceScope::DetectedBraceScope(int& noOfLines) : pNumberOfLines(&noOfLines)
{ }

///////////////////////////////////////////////////////////////
// ACtion to add class,enum,struct,namespace to stack.
void DetectedBraceScope::doAction(ITokCollection* pTc)
{
ITokCollection& tc = *pTc;

int len = tc.length()-1;

std::string type = "";

std::string classPart = "";

if ( tc.find("class") < tc.length() )
	{ len = tc.find("class") ; type = "CLASS" ; }
else if ( tc.find("enum") < tc.length() )
	{ len = tc.find("enum") ; type = "ENUM" ; }
else if ( tc.find("struct") < tc.length() )
	{ len = tc.find("struct") ; type = "STRUCT" ;}
else if ( tc.find("namespace") < tc.length() )
	{ len = tc.find("namespace") ; type = "NAMESPACE" ;}

classPart.append(tc[len+1]);

StackOperation::push(type,classPart,NumberOfLines::getLineNumber(pTc,tc.length()-1,*pNumberOfLines));
}

///////////////////////////////////////////////////////////////
// rule to detect function for analyzis

///////////////////////////////////////////////////////////////
// Function to check it a word is a special keyword.
bool CheckControlCount::isSpecialKeyWord(const std::string& tok)
{
const static std::string keys[]
    = { "for", "while", "switch", "if", "else" };
for(int i=0; i<5; ++i)
    if(tok == keys[i])
    return true;
return false;
}

///////////////////////////////////////////////////////////////
// Check if a control keyword exists in the semi.
bool CheckControlCount::doTest(ITokCollection* pTc)
{
ITokCollection& tc = *pTc;

for ( int i = 0 ; i < tc.length() - 1 ; i++ )
{
	if(isSpecialKeyWord(tc[i]))
	{
		doActions(pTc);
		return true;
	}
}
  
return false;
}

///////////////////////////////////////////////////////////////
// action to increment the line number

///////////////////////////////////////////////////////////////
// Constructor to get previous number of lines
ControlCountDetected::ControlCountDetected(int& noOfLines) : pNumberOfLines(&noOfLines)
{ }

///////////////////////////////////////////////////////////////
// Function to check it a word is a special keyword.
bool ControlCountDetected::isSpecialKeyWord(const std::string& tok)
{
const static std::string keys[]
    = { "for", "while", "switch", "if", "else" };
for(int i=0; i<5; ++i)
    if(tok == keys[i])
    return true;
return false;
}

///////////////////////////////////////////////////////////////
// Function to increment cyclo count when control detected.
void ControlCountDetected::doAction(ITokCollection* pTc)
{

ITokCollection& tc = *pTc;
	
for ( int i = 0 ; i < tc.length() - 1 ; i++ )
{
	if(isSpecialKeyWord(tc[i]))
	{
		if ( i == 0 )
		{
			DataStore::Increment_Cyclo();
		}
		else if ( tc[i-1] != "else" )
		  	DataStore::Increment_Cyclo();
	}
}

}

///////////////////////////////////////////////////////////////
// rule to detect function for analyzis

///////////////////////////////////////////////////////////////
// Function to check it a word is a special keyword.
  bool CheckFunction::isSpecialKeyWord(const std::string& tok)
  {
    const static std::string keys[]
      = { "for", "while", "switch", "if", "catch" , "each" };
    for(int i=0; i<6; ++i)
      if(tok == keys[i])
        return true;
    return false;
  }

///////////////////////////////////////////////////////////////
// Function to check if a semi has function statement
  bool CheckFunction::doTest(ITokCollection* pTc)
  {
    ITokCollection& tc = *pTc;
    if(tc[tc.length()-1] == "{")
    {
      int len = tc.find("(");
	  if ( len > 0 )
	  {
		if(len < tc.length() && !isSpecialKeyWord(tc[len-1]))
		{
		 doActions(pTc);
			return true;
		}	
	  }
    }
    return false;
  }


///////////////////////////////////////////////////////////////
// action to increment the line number

  ///////////////////////////////////////////////////////////////
// Function to check it a word is a special operator.
bool FunctionDetected::isOperator(const std::string& tok)
{
const static std::string keys[] = { "+","-","*","/","%","^","&","|","~","!","=","<",">","(" ,")","[","]","new","delete" };

for(int i=0; i<19; ++i)
    if(tok == keys[i])
    return true;
return false;
}

///////////////////////////////////////////////////////////////
// Constructor to get previous line count.
FunctionDetected::FunctionDetected(int& noOfLines) : pNumberOfLines(&noOfLines)
{ }

///////////////////////////////////////////////////////////////
// Function Detected. Etract name and Add to Stack.
void FunctionDetected::doAction(ITokCollection* pTc)
{
ITokCollection& tc = *pTc;

int len = tc.find("(");
	
int operator_keyword = tc.find("operator");

std::string detectedFunctionName = "";

std::string functionSignature = "";

for ( int j = len ; j < tc.length() - 1 ; j++)
{ 
	if ( tc[j] != "\n")
	{ functionSignature = functionSignature + tc[j] ; }
}

if ( isOperator(tc[len-1]) && operator_keyword < tc.length()-1 )
{	// extract fully qualified name.
	for ( int i = operator_keyword; i < len ; i++)
		detectedFunctionName = detectedFunctionName + tc[i];

		if ( (  ( (operator_keyword-1) >= 0 && tc[operator_keyword-1] == "::") || ( (operator_keyword-1) >= 0 && tc[operator_keyword-1]== "::~" ) ||  ( (operator_keyword-1) >= 0 && tc[operator_keyword-1] == "~") ) && ( (operator_keyword-1) >= 0 && (tc[operator_keyword-1] != "\n") ) )
			detectedFunctionName = tc[operator_keyword-2] + tc[operator_keyword-1] + detectedFunctionName; 
}
else if ( len > 2 )
{	// check if destructor symbol or scope resolution operator exist.
	    detectedFunctionName = tc[len-1];

	if ( (tc[len-2] == "::" || tc[len-2] == "::~" || tc[len-2] == "~") && (tc[len-3] != "\n") )
		detectedFunctionName = tc[len-3] + tc[len-2] + detectedFunctionName; 
}

detectedFunctionName = detectedFunctionName + functionSignature;

StackOperation::push("FUNCTION",detectedFunctionName,NumberOfLines::getLineNumber(pTc,len,*pNumberOfLines));
}


///////////////////////////////////////////////////////////////
// rule to detect control statement for analyzis

///////////////////////////////////////////////////////////////
// Function to check it a word is a special keyword.
  bool CheckControl::isControlKeyWord(const std::string& tok)
  {
    const static std::string keys[]
      = { "for", "while", "switch", "if", "do", "else" , "try", "catch" ,"for each" };
    for(int i=0; i<8; ++i)
      if(tok == keys[i])
        return true;
    return false;
  }

///////////////////////////////////////////////////////////////
// Function to check if a control exists.
  bool CheckControl::doTest(ITokCollection* pTc)
  {
    ITokCollection& tc = *pTc;
    if(tc[tc.length()-1] == "{" || tc[tc.length()-1] == ";")
    {

	  for ( int i = 0 ; i < tc.length() ; i++)
	  {
		  if( isControlKeyWord(tc[i]) )
			{
				doActions(pTc);
				return true;
			}
	  }
    }

    return false;
  }


///////////////////////////////////////////////////////////////
// action when Control is detected.

	bool ControlDetected::isControlKeyWord(const std::string& tok)
{
const static std::string keys[]
    = { "for", "while", "switch", "if", "do", "else" , "try", "catch" };
for(int i=0; i<8; ++i)
    if(tok == keys[i])
    return true;
return false;
}

///////////////////////////////////////////////////////////////
// Constructor to get previous number of lines.
ControlDetected::ControlDetected(std::vector<std::string>& forBuff,int& noOfLines) : pForBuffer(&forBuff),pNumberOfLines(&noOfLines)
{ }

// Actions combined for all control statments for handling : while ( true ) if ( true ) while ( true ) {

///////////////////////////////////////////////////////////////
// Function to handle a semi when control is detected.
void ControlDetected::doAction(ITokCollection* pTc)
{
ITokCollection& tc = *pTc;

for ( int i = 0 ; i < tc.length(); i++)
{ 
		if ( tc[i] ==  "for" && tc[i+1] != "each")
			handleFor(pTc,i);
		if ( tc[i] ==  "while")
			handleWhile(pTc,i);
		if ( tc[i] ==  "if" && i != 0 && tc[i-1] != "else")
			handleIf(pTc,i);
		if ( tc[i] ==  "else")
			handleElse(pTc,i);
		if ( tc[i] ==  "do")
			handleDo(pTc,i);
		if ( tc[i] ==  "switch")
			handleSwitch(pTc,i);
		if ( tc[i] == "for" && tc[i+1] == "each" )
			handleForEach(pTc,i+1);
		CheckTryCatch(tc[i],pTc,i);
}
}

void ControlDetected::CheckTryCatch(std::string tok,ITokCollection* pTc,int loc)
{
		if ( tok == "try")
			handleTry(pTc,loc);
		if ( tok == "catch")
			handleCatch(pTc,loc);
}

///////////////////////////////////////////////////////////////
// Function to handle "for" loop.
void ControlDetected::handleFor(ITokCollection* pTc,int loc)
{
	ITokCollection& tc = *pTc;
		
	std::string forPart = "";

	for ( int i = loc; i < tc.length(); i++)
	{	 forPart += tc[i] ;	}

	pForBuffer->clear();// Clear buffer when for starts.

	pForBuffer->push_back(forPart);// Add starting part to buffer.
}

///////////////////////////////////////////////////////////////
// Function to handle "while" loop.
void ControlDetected::handleWhile(ITokCollection* pTc,int loc)
{
	ITokCollection& tc = *pTc;
		
	std::string whilePart = "";

	int braceCount = 0;

	// Build while loop statement. while ( ... )
	for ( int i = loc; i < tc.length(); i++)
	{	 
			if ( tc[i] == "(" )
				braceCount++;
			else if ( tc[i] == ")")
				braceCount--;

			whilePart = whilePart + tc[i].c_str();		 

			if (braceCount == 0 && tc[i] != "while" )
				break;
	}

	if  (!(tc[tc.length()-1] == ";")) 
	{
		StackOperation::push("CONTROL",whilePart,NumberOfLines::getLineNumber(pTc,loc,*pNumberOfLines));
	}
}

///////////////////////////////////////////////////////////////
// Function to handle "switch" statement
void ControlDetected::handleSwitch(ITokCollection* pTc,int loc)
{
	ITokCollection& tc = *pTc;
		
	std::string switchPart = "";

	int braceCount = 0;

	// Buile switch statement : switch (..)
	for ( int i = loc; i < tc.length(); i++)
	{	 
			if ( tc[i] == "(" )
				braceCount++;
			else if ( tc[i] == ")")
				braceCount--;

			switchPart = switchPart + tc[i].c_str();		 

			if (braceCount == 0 && tc[i] != "switch" )
				break;
	}

StackOperation::push("CONTROL",switchPart,NumberOfLines::getLineNumber(pTc,loc,*pNumberOfLines));
	  
}

///////////////////////////////////////////////////////////////
// Function to handle try block
void ControlDetected::handleTry(ITokCollection* pTc,int loc)
{
	ITokCollection& tc = *pTc;

StackOperation::push("TRY-CATCH","try",NumberOfLines::getLineNumber(pTc,loc,*pNumberOfLines));

}

///////////////////////////////////////////////////////////////
// Function to handle catch block.
void ControlDetected::handleCatch(ITokCollection* pTc,int loc)
{
	ITokCollection& tc = *pTc;
		
	std::string catchPart = "";

	int braceCount = 0;

	// Build catch statement. catch (..)
	for ( int i = loc; i < tc.length(); i++)
	{	 
			if ( tc[i] == "(" )
				braceCount++;
			else if ( tc[i] == ")")
				braceCount--;

			catchPart = catchPart + tc[i].c_str();		 

			if (braceCount == 0 && tc[i] != "catch" )
				break;
	}

StackOperation::push("TRY-CATCH",catchPart,NumberOfLines::getLineNumber(pTc,loc,*pNumberOfLines));

}

///////////////////////////////////////////////////////////////
// Function to handle If 
void ControlDetected::handleIf(ITokCollection* pTc,int loc)
{
	ITokCollection& tc = *pTc;
		
	std::string ifPart = "";

	int braceCount = 0;

	// Build if statement if (..)
	for ( int i = loc; i < tc.length(); i++)
	{	 
			if ( tc[i] == "(" )
				braceCount++;
			else if ( tc[i] == ")")
				braceCount--;

			ifPart = ifPart + tc[i].c_str();		 

			if (braceCount == 0 && tc[i] != "if" )
				break;
	}

	StackOperation::push("CONTROL",ifPart,NumberOfLines::getLineNumber(pTc,loc,*pNumberOfLines));

}

///////////////////////////////////////////////////////////////
// Function to handle For Each
void ControlDetected::handleForEach(ITokCollection* pTc,int loc)
{
	ITokCollection& tc = *pTc;
		
	std::string forEachPart = "";

	int braceCount = 0;

	// build For Each (..)
	for ( int i = loc; i < tc.length(); i++)
	{	 
			if ( tc[i] == "(" )
				braceCount++;
			else if ( tc[i] == ")")
				braceCount--;

			forEachPart = forEachPart + tc[i].c_str();		 

			if (braceCount == 0 && tc[i] != "each" )
				break;
	}

	StackOperation::push("CONTROL","for " + forEachPart,NumberOfLines::getLineNumber(pTc,loc,*pNumberOfLines));

}

///////////////////////////////////////////////////////////////
// Function to handle Else
void ControlDetected::handleElse(ITokCollection* pTc,int loc)
{
	
	ITokCollection& tc = *pTc;
		
	StackOperation::push("CONTROL","else",NumberOfLines::getLineNumber(pTc,loc,*pNumberOfLines));

}

///////////////////////////////////////////////////////////////
// Function to handle Do 
void ControlDetected::handleDo(ITokCollection* pTc,int loc)
{
	ITokCollection& tc = *pTc;

	StackOperation::push("CONTROL","do",NumberOfLines::getLineNumber(pTc,loc,*pNumberOfLines));
}

///////////////////////////////////////////////////////////////
// rule to build up for loop

///////////////////////////////////////////////////////////////
// Constructor to get previous number of line.
CheckBuildFor::CheckBuildFor(std::vector<std::string>& forBuff) : pForBuffer(&forBuff)
{ }

///////////////////////////////////////////////////////////////
// Function to build for loop when buffer is not empty.
bool CheckBuildFor::doTest(ITokCollection* pTc)
{
ITokCollection& tc = *pTc;

if ( pForBuffer->size() != 0 )
{	
	doActions(pTc);
		return true;
}
return false;
}

///////////////////////////////////////////////////////////////
// Constructor to get previous line number
DoBuildFor::DoBuildFor(std::vector<std::string>& forBuff,int& noOfLines)  : pForBuffer(&forBuff),pNumberOfLines(&noOfLines)
{ }

///////////////////////////////////////////////////////////////
// Function to build For statement using Buffer.
void DoBuildFor::doAction(ITokCollection* pTc)
{
	ITokCollection& tc = *pTc;

	std::string forPart = "";

	if ( pForBuffer->size() == 1 )
	{ // Add second part to buffer.
		for ( int i = 0 ; i < tc.length() ; i++ )
			forPart = forPart + tc[i].c_str();
		pForBuffer->push_back(forPart);
	}
	else if ( pForBuffer->size() == 2 )
	{ // Build For using all 3 parts. ( 1 detected + 2 buffer )
		for ( int i = 0 ; i < (int)pForBuffer->size() ; i++ )
		{  forPart = forPart + pForBuffer->at(i);  }

		int braceCount = 0;
		for ( int j = 0 ; j < tc.length() ; j++ )
		{ 
			if ( tc[j] == "(" )
				braceCount++;
			else if ( tc[j] == ")")
				braceCount--;

			forPart = forPart + tc[j].c_str();		 

			if (braceCount < 0)
				break;
		}

		pForBuffer->clear(); // clear when for is complete.

		StackOperation::push("CONTROL",forPart,(NumberOfLines::getLineNumber(pTc,tc.length()-1,*pNumberOfLines))-1);
	}
}


///////////////////////////////////////////////////////////////
// Function to check if scope starts.
bool ScopeStart::doTest(ITokCollection* pTc)
{
ITokCollection& tc = *pTc;

if ( tc.length() > 0 )
{	
	if ( tc[tc.length() - 1] == "{" ) 
	{	
		doActions(pTc);
			return true;
	}
}
return false;
}


///////////////////////////////////////////////////////////////
// constructor to get previous number of line
doScopeStart::doScopeStart(int& noOfLines)  : pNumberOfLines(&noOfLines)
{}

///////////////////////////////////////////////////////////////
// Function to add scope start to stack.
void doScopeStart::doAction(ITokCollection* pTc)
{
ITokCollection& tc = *pTc;

std::pair<std::string, ScopeElement> item;
	
item.first = "SCOPE-START";
item.second.name = "{";
item.second.lineNumber = NumberOfLines::getLineNumber(pTc,tc.length() - 1,*pNumberOfLines);

ScopeStack<std::string,ScopeElement>::push(item);

}

///////////////////////////////////////////////////////////////
// Constructor to get previous line number.
  EndInSemiColon::EndInSemiColon(std::vector<std::string>& forBuff) : pForBuffer(&forBuff)
  { }

 ///////////////////////////////////////////////////////////////
// Function to check if a semi ends in semi colon
bool EndInSemiColon::doTest(ITokCollection* pTc)
{
ITokCollection& tc = *pTc;

if ( ScopeStack<std::string,ScopeElement>::size() != 0 )
{
	ScopeStack<std::string,ScopeElement>::iterator it = ScopeStack<std::string,ScopeElement>::end();

	--it;

	if ( tc[tc.length() - 1] == ";" && it->first != "SCOPE-START" && pForBuffer->size() == 0 )
	{	// Ignore ; statements if top of stack is {
		doActions(pTc);
		return true;
	}
}
	return false;
}

///////////////////////////////////////////////////////////////
// Contructor to get previous number of lines.
doEndInSemiColon::doEndInSemiColon(int& NoOfLines) : pNumberOfLines(&NoOfLines)
{ }

///////////////////////////////////////////////////////////////
// Pop element if semi-colon statement ends scope.
void doEndInSemiColon::doAction(ITokCollection* pTc)
{
ITokCollection& tc = *pTc;

// Ignore if : For Buffer not empty.
StackOperation::pop_from_stack((NumberOfLines::getLineNumber(pTc,tc.length()-1,*pNumberOfLines))+1);	
}

///////////////////////////////////////////////////////////////
// Function to check if semi ends in }
  bool EndInBrace::doTest(ITokCollection* pTc)
  {
    ITokCollection& tc = *pTc;

	if ( ScopeStack<std::string,ScopeElement>::size() != 0 )
	{
		if ( tc[tc.length() - 1] == "}" )
		{
			doActions(pTc);
			return true;
		}
	}
		return false;
  }

 ///////////////////////////////////////////////////////////////
// Constructor to get previous line number.
  doEndInBrace::doEndInBrace(int& NoOfLines) : pNumberOfLines(&NoOfLines)
  { }

///////////////////////////////////////////////////////////////
// Function to pop element as scope ends.
  void doEndInBrace::doAction(ITokCollection* pTc)
  {
	
	 ITokCollection& tc = *pTc;

	 StackOperation::pop_from_stack((NumberOfLines::getLineNumber(pTc,tc.length()-1,*pNumberOfLines)) + 1);	
	
  }


///////////////////////////////////////////////////////////////
// Function to detect object declaration
  bool DetectObjectDeclaration::doTest(ITokCollection* pTc)
  {
    ITokCollection& tc = *pTc;

	if ( ScopeStack<std::string,ScopeElement>::size() != 0 )
	{
		if ( tc[tc.length() - 1] == ";" )
		{
			doActions(pTc);
			return true;
		}
	}
		return false;
  }

///////////////////////////////////////////////////////////////
// extract object declaration from semi ending in ;
// http://www.ecs.syr.edu/faculty/fawcett/handouts/CSE687/code/Project1HelpSp11/DetectingDeclarations.doc
std::vector<std::string> doDetectObjectDeclaration::removeAssignment(std::vector<std::string> semi)
{
	std::vector<std::string>::iterator iter = std::find(semi.begin(),semi.end(),"=");

	if ( iter != semi.end() )
	{	
			std::vector<std::string>::iterator iter_end = semi.end();

			semi.erase(iter,iter_end);
	}

	return semi;
}

///////////////////////////////////////////////////////////////////
// Remove qualifiers from the semi to detect object declaration
std::vector<std::string> doDetectObjectDeclaration::removeQualifiers(std::vector<std::string> semi)
{
	std::vector<std::string>::iterator iter = semi.begin() ;

	const static std::string keys[]
      = { "short" , "long" , "const" , "register" , "static"  , "unsigned" , "extern"   , "\n"     ,
		  "*"     , "&"    , "["     , "]"        , "private" , ":"        , "volatile" , "return" , 
		  "true"  , "false", " " };	
	  
		for(int i=0; i<19; ++i)
		{
		  
		  iter = find(semi.begin(), semi.end(), keys[i]);

		  while ( iter != semi.end() )
		  {
			 semi.erase(iter);

			 iter = find(semi.begin(), semi.end(), keys[i]);
		  }

		}
	return semi;
}

///////////////////////////////////////////////////////////////
// Constructor to get previous number of lines.
  doDetectObjectDeclaration::doDetectObjectDeclaration(int& NoOfLines) : pNumberOfLines(&NoOfLines)
  { }

///////////////////////////////////////////////////////////////
// Action to be taken when object declaration detected.
  void doDetectObjectDeclaration::doAction(ITokCollection* pTc)
  {
	 ITokCollection& tc = *pTc;

	 std::vector<std::string> semi ;

	 for ( int i = 0; i < tc.length() - 1 ; i++ )
	 { semi.push_back(tc[i]); }

	 semi = removeAssignment(semi);

	 semi = removeQualifiers(semi);

	if ( semi.size() == 2 )
		{  // Example : int temp;
		TypeItem ti; 
		ti.setFileName(DataStore::getcurrentFileName()); 
		ti.setpackageName(DataStore::getcurrentPackageName()) ;
		ti.setLineNumber(NumberOfLines::getLineNumber(pTc,tc.find("("),*pNumberOfLines));
		DataStore::addTypeToTypeTable(DataStore::getcurrentPackageName()+"::"+StackOperation::getCurrentScope()+"::"+semi[1],ti);
	}
	 else if ( semi.size() > 1 && semi[semi.size()-2].at(semi[semi.size()-2].length()-1) == '>')
		{ // Example : std::vector<std::string> temp;
		TypeItem ti; 
		ti.setFileName(DataStore::getcurrentFileName()); 
		ti.setpackageName(DataStore::getcurrentPackageName()) ;
		ti.setLineNumber(NumberOfLines::getLineNumber(pTc,tc.find("("),*pNumberOfLines));
		DataStore::addTypeToTypeTable(DataStore::getcurrentPackageName()+"::"+StackOperation::getCurrentScope()+"::"+semi[semi.size()-1],ti);
	}

  }

///////////////////////////////////////////////////////////////
// Check if a special keyword exist
  bool CheckFunctionArgument::isSpecialKeyWord(const std::string& tok)
  {
    const static std::string keys[]
      = { "for", "while", "switch", "if", "catch" };
    for(int i=0; i<5; ++i)
      if(tok == keys[i])
        return true;
    return false;
  }

/////////////////////////////////////////////////////////////////////
// Cehck if a function statement for detecting argument declaration.
  bool CheckFunctionArgument::doTest(ITokCollection* pTc)
  {
    ITokCollection& tc = *pTc;
    if(tc[tc.length()-1] == "{")
    {
      int len = tc.find("(");
	  if ( len > 0 )
	  {
		if(len < tc.length() && !isSpecialKeyWord(tc[len-1]))
		{
		    doActions(pTc);
			return true;
		}	
	  }
    }
    return false;
  }

///////////////////////////////////////////////////////////////
// Remove assignement and eveything to right.
std::vector<std::string> DoCheckFunctionArgument::removeAssignment(std::vector<std::string> semi)
{
	std::vector<std::string>::iterator iter = std::find(semi.begin(),semi.end(),"=");

	if ( iter != semi.end() )
	{	
			std::vector<std::string>::iterator iter_end = semi.end();

			semi.erase(iter,iter_end);
	}

	return semi;
}

///////////////////////////////////////////////////////////////
// Remove special keywords.
std::vector<std::string> DoCheckFunctionArgument::removeQualifiers(std::vector<std::string> semi)
{
	std::vector<std::string>::iterator iter = semi.begin() ;

	const static std::string keys[]
      = { "short" , "long" , "const" , "register" , "static"  , "unsigned" , "extern"   , "\n"     ,
		  "*"     , "&"    , "["     , "]"        , "private" , ":"        , "volatile" , "return" , 
		  "true"  , "false" };	
	  
		for(int i=0; i<18; ++i)
		{
		  
		  iter = find(semi.begin(), semi.end(), keys[i]);

		  while ( iter != semi.end() )
		  {
			 semi.erase(iter);

			 iter = find(semi.begin(), semi.end(), keys[i]);
		  }

		}
	return semi;
}


///////////////////////////////////////////////////////////////
// Constructor to get previous number of lines
   DoCheckFunctionArgument::DoCheckFunctionArgument(int& noOfLines) : pNumberOfLines(&noOfLines)
	{ }

 ///////////////////////////////////////////////////////////////
// Extract object declaration from function argument list.
   void DoCheckFunctionArgument::doAction(ITokCollection* pTc)
   {
	ITokCollection& tc = *pTc;

	int len = tc.find("(") + 1;

	std::string functionSignature = "";

	std::vector<std::string> semi;

	while ( len < tc.length() - 1 )
	{
		semi.clear();

		while ( len < tc.length() - 1 && tc[len] != "," && tc[len] != ")" )
		{
			semi.push_back(tc[len]);
			len++;
		}

		semi = removeAssignment(semi);

		semi = removeQualifiers(semi);

		if ( semi.size() == 2 )
			{ // Example : int temp;
		TypeItem ti; 
		ti.setFileName(DataStore::getcurrentFileName()); 
		ti.setpackageName(DataStore::getcurrentPackageName()) ;
		ti.setLineNumber(NumberOfLines::getLineNumber(pTc,tc.find("("),*pNumberOfLines));
		DataStore::addTypeToTypeTable(DataStore::getcurrentPackageName()+"::"+StackOperation::getCurrentScope()+"::"+semi[1],ti);
		}
		else if ( semi.size() > 1 && semi[semi.size()-2].at(semi[semi.size()-2].length()-1) == '>')
			{ // Example : std::vector<std::string> temp;
		TypeItem ti; 
		ti.setFileName(DataStore::getcurrentFileName()); 
		ti.setpackageName(DataStore::getcurrentPackageName()) ;
		ti.setLineNumber(NumberOfLines::getLineNumber(pTc,tc.find("("),*pNumberOfLines));
		DataStore::addTypeToTypeTable(DataStore::getcurrentPackageName()+"::"+StackOperation::getCurrentScope()+"::"+semi[semi.size()-1],ti);
		}

		if ( tc[len] == ")")
			break;
		len++;
	}

  }

///////////////////////////////////////////////////////////////
// rule to add namespace
  bool DetectNamespace::doTest(ITokCollection* pTc)
  {
    ITokCollection& tc = *pTc;

		int usingLoc = tc.find("using");
		int namespaceLoc = tc.find("namespace");

		if ( usingLoc < tc.length() - 1 && namespaceLoc != tc.length() - 1 )
		{
			doActions(pTc);
			return true;
		}

		return false;
  }

///////////////////////////////////////////////////////////////
// Constructor to get previous line number
  doDetectNamespace::doDetectNamespace(int& NoOfLines) : pNumberOfLines(&NoOfLines)
  { }

///////////////////////////////////////////////////////////////
// Add Namespace to namespace list.
  void doDetectNamespace::doAction(ITokCollection* pTc)
  {
	
	 ITokCollection& tc = *pTc;

	 std::string nameSpace = "";

	 for ( int i = tc.find("namespace") + 1 ; i < tc.length() - 1 ; i++ )
	 { 
		 if ( tc[i] != " " && tc[i] != "\n" )
			 nameSpace = nameSpace + tc[i];
	 }
	
	 DataStore::InsertNamespace(DataStore::getcurrentFileName(),nameSpace);

  }

///////////////////////////////////////////////////////////////
// rule to check Locality of Refrence : PASS 2
// Check for all tokens in all semi.
  bool CheckTokenLocality::doTest(ITokCollection* pTc)
  {
			doActions(pTc);
			return true;
  }

///////////////////////////////////////////////////////////////
// Constructor to get previous line number
  doCheckTokenLocality::doCheckTokenLocality(int& NoOfLines) : pNumberOfLines(&NoOfLines)
  { }

 ///////////////////////////////////////////////////////////////
// Fucntion to compare token to TypeTable entries. ( Header File )
// Only check TypeTable entry in Header File
  void doCheckTokenLocality::headerFileDetection(ITokCollection* pTc)
  {
	  ITokCollection& tc = *pTc;

	  std::string token = "";

	  std::string functionToken = "";

	  for ( int i = 0 ; i < (int)tc.length() ; i++ )
	  {
		  
		  token = DataStore::getcurrentPackageName()+"::"+StackOperation::getCurrentScope() + "::" + tc[i];

		  functionToken = DataStore::getcurrentPackageName()+"::"+StackOperation::getCurrentScope().substr(0,StackOperation::getCurrentScope().find_last_of("::")+ 1) + tc[i];

		  if ( DataStore::findKeyInTypeTable(token) ) // Fully Qualified name
		  {  
			      TypeItem ti = DataStore::getTypeItemFromTypeTable(token);
				 
				  PackageHolder::addUpdateVariableToPackage(DataStore::getcurrentPackageName(),token, DataStore::getcurrentFileName() ,ti.getLineNumber(),DataStore::getcurrentFileName(),NumberOfLines::getLineNumber(pTc,i,*pNumberOfLines),NumberOfLines::getLineNumber(pTc,i,*pNumberOfLines) - ti.getLineNumber());
				  break;
		  }
		  else if (DataStore::findKeyInTypeTable(functionToken) ) // ignore function in scope.
		  {  
				 TypeItem ti = DataStore::getTypeItemFromTypeTable(functionToken);

				  PackageHolder::addUpdateVariableToPackage(DataStore::getcurrentPackageName(),functionToken, DataStore::getcurrentFileName() ,ti.getLineNumber(),DataStore::getcurrentFileName(),NumberOfLines::getLineNumber(pTc,i,*pNumberOfLines),NumberOfLines::getLineNumber(pTc,i,*pNumberOfLines) - ti.getLineNumber());
				  break;
		  }

	  }
  }

  std::vector<std::string> doCheckTokenLocality::GetAllPossibleScope(std::string scope)
  {

	std::vector<std::string> possibleScope;

	std::string temp = scope;

	std::string part = "";

	int count = 0;

	possibleScope.push_back(scope);

	try 
	{
		while ( temp.find("::") != -1 )
		{
			count++;

			if ( count == 1)
				part = part + temp.substr(0,temp.find("::"));
			else 
				part = part + "::" + temp.substr(0,temp.find("::"));

			temp = temp.substr(temp.find("::") + 2); 

			possibleScope.push_back(part);
		}

	}
	catch(std::exception ex)
	{ // Ignore Namespaces if a invalid entry exsists.// Return Name Space vector.
	}

	return possibleScope;

  }

  ///////////////////////////////////////////////////////////////
// Fucntion to compare token to TypeTable entries. ( Source File )
// check TypeTable entry in Header File & Source file ( with namespace )
  void doCheckTokenLocality::sourceFileDetection(ITokCollection* pTc)
  {
	   ITokCollection& tc = *pTc; std::string token = "";

	  std::vector<std::string> scopeList = GetAllPossibleScope(StackOperation::getCurrentScope()); // Generate Multiple Scopes. Ex. Namespace1::Namespace2::test -> Namespace1 , Namespace1::Namespace2 ,  Namespace1::Namespace2::test

	  for ( int i = 0 ; i < tc.length() ; i++ )
	  {
		  for ( int j = 0 ; j < (int)scopeList.size() ; j++)
		  {

			 token = scopeList[j] + "::" + tc[i];

		     if ( DataStore::findKeyInTypeTable(DataStore::getcurrentPackageName()+"::"+token) ) // Fully qualified name
			  {

				  token = DataStore::getcurrentPackageName()+"::"+token;

				   TypeItem ti = DataStore::getTypeItemFromTypeTable(token);

				  if ( ti.getFileName() == DataStore::getcurrentFileName() )
				  { PackageHolder::addUpdateVariableToPackage(DataStore::getcurrentPackageName(),token, DataStore::getcurrentFileName() ,ti.getLineNumber(),DataStore::getcurrentFileName(),NumberOfLines::getLineNumber(pTc,i,*pNumberOfLines),NumberOfLines::getLineNumber(pTc,i,*pNumberOfLines) - (ti.getLineNumber())); }
				  else 
				  { PackageHolder::addUpdateVariableToPackage(DataStore::getcurrentPackageName(),token, ti.getFileName() ,ti.getLineNumber(),DataStore::getcurrentFileName(),NumberOfLines::getLineNumber(pTc,i,*pNumberOfLines), DataStore::GetFileSize(ti.getFileName())  - ti.getLineNumber() +  NumberOfLines::getLineNumber(pTc,i,*pNumberOfLines) ); }
				  break;
			  }
			  else // Check if entry belongs to a namespace.
			  {
				  checkNameSpaceList(token,pTc,i);
			  }
		  }
	  }

  }

 //////////////////////////////////////////////////////////////////
// Fucntion to compare token to TypeTable entries using namespace.
// Append namespace to the token and function token to compare.
  void doCheckTokenLocality::checkNameSpaceList(std::string token,ITokCollection* pTc,int tok)
  {
	std::vector<std::string> namespaceList = DataStore::GetNamespace(DataStore::getcurrentFileName());
 
	for ( int k = 0 ; k < (int)namespaceList.size() ; k++ )
		{		
			std::string local_token = DataStore::getcurrentPackageName()+"::"+namespaceList[k] + "::" + token;

			if ( DataStore::findKeyInTypeTable(local_token) ) // namespace :: token
			{
					TypeItem ti_token = DataStore::getTypeItemFromTypeTable(local_token);

					if ( ti_token.getFileName() == DataStore::getcurrentFileName() )
					{ PackageHolder::addUpdateVariableToPackage(DataStore::getcurrentPackageName(),local_token, DataStore::getcurrentFileName() ,ti_token.getLineNumber(),DataStore::getcurrentFileName(),NumberOfLines::getLineNumber(pTc,tok,*pNumberOfLines),NumberOfLines::getLineNumber(pTc,tok,*pNumberOfLines) - (ti_token.getLineNumber())); }
					else
					{ PackageHolder::addUpdateVariableToPackage(DataStore::getcurrentPackageName(),local_token, ti_token.getFileName() ,ti_token.getLineNumber(),DataStore::getcurrentFileName(),NumberOfLines::getLineNumber(pTc,tok,*pNumberOfLines), DataStore::GetFileSize(ti_token.getFileName())  - ti_token.getLineNumber() +  NumberOfLines::getLineNumber(pTc,tok,*pNumberOfLines) ); }
					break;
			}
		}
  
}

///////////////////////////////////////////////////////////////
// Fucntion to check locality of reference
  void doCheckTokenLocality::doAction(ITokCollection* pTc)
  {
	 ITokCollection& tc = *pTc;	 

	 if ( DataStore::getcurrentFileName().substr(DataStore::getcurrentFileName().length() - 2 ) == ".h" )
	 { headerFileDetection(pTc); }
	 else if ( DataStore::getcurrentFileName().substr(DataStore::getcurrentFileName().length() - 4 ) == ".cpp" )
	 { sourceFileDetection(pTc); }
	
  }

#ifdef TEST_ACTIONSANDRULES

#include <iostream>
#include "ActionsAndRules.h"
#include "Tokenizer.h"
#include "SemiExpression.h"

int main(int argc, char* argv[])
{
  std::cout << "\n  Testing ActionsAndRules class\n "
            << std::string(30,'=') << std::endl;

  try
  {
    
	  CheckBraceScope br;
	  DetectedBraceScope dr;
	  br.addAction(&dr);

    Toker toker("../ActionsAndRules.h");
    SemiExp se(&toker);
    Parser parser(&se);
    parser.addRule(&br);
    
    while(se.get())
      parser.parse();
    size_t len = resultsQ.size();
    for(size_t i=0; i<len; ++i)
    {
      std::cout << "\n  " << resultsQ.front().c_str();
      resultsQ.pop();
    }
    std::cout << "\n\n";
  }
  catch(std::exception& ex)
  {
    std::cout << "\n\n  " << ex.what() << "\n\n";
  }
}
#endif
