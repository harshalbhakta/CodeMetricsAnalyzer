////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ScopeStack.h (ver 3.0)  -  Added the ScopeElement Struct for holing 2 values.							  // 																					   
//		 																									  //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #1 - CodeMetricsAnalyzer, Spring 2011								  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ScopeStack.cpp - implements template stack holding items with two values  //
//                                                                           //
// version 2.0 - fixed bug in pop() method found by Drumil Bhattad           //
//                                                                           //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2011                 //
///////////////////////////////////////////////////////////////////////////////

#include "DataStore.h"
#include "PackageHolder.h"
#include "ScopeStack.h"

///////////////////////////////////////////////////////////////
// Class with Static Method to pop element from stack.

///////////////////////////////////////////////////////////////
// Function to update Depth of Scope Nesting.
void StackOperation::UpdateDepthScopeNesting()
	{
		int len = ScopeStack<std::string,ScopeElement>::size();
		
		int count = 0;

		ScopeStack<std::string,ScopeElement>::iterator it;

		if ( len > 0 )
		{
			it = ScopeStack<std::string,ScopeElement>::end();

			it--;

			while ( it != ScopeStack<std::string,ScopeElement>::begin() )
			{
				if ( it->first == "CONTROL" || it->first == "FUNCTION" || it->first == "CLASS" || it->first == "NAMESPACE" )
				{ count++; }

				it--;
			} // count all the elements in stack that define depth of scope.

			if ( it->first == "CONTROL" || it->first == "FUNCTION" || it->first == "CLASS" || it->first == "NAMESPACE" )
				{ count++; }
		}

		if ( count > DataStore::getDepth_scope_nesting())
			DataStore::setDepth_scope_nesting(count);
	}

///////////////////////////////////////////////////////////////
// Add Funtion to Reporitory : PackageHolder
void StackOperation::addFunctionToReporitory(std::string name,int noOfLine,int cyclo,std::string scp,int fromLine, int CurrLine )
	{ 
		Function fn;

		fn.setFunctionName(name);
		fn.setNoOfLines(noOfLine);
		fn.setCycloComplexity(cyclo);
		fn.setScope(scp);
		fn.setFromLine(fromLine);
		fn.setToLine(CurrLine);

		PackageHolder::addFunctionToPackage(DataStore::getcurrentPackageName(),fn);
	}

///////////////////////////////////////////////////////////////
// Add Control to Repository : PackageHolder
void StackOperation::addControlToReporitory(std::string name,int BreadthControl,std::string scp,int fromLine, int CurrLine )
	{ 
		Control ct;

		ct.setControlName(name);
		ct.setBreadthControlSpan(BreadthControl);
		ct.setScope(scp);
		ct.setFromLine(fromLine);		
		ct.setToLine(CurrLine);
		
		PackageHolder::addControlToPackage(DataStore::getcurrentPackageName(),ct);

		std::string s;

	}

//////////////////////////////////////////////////////////////////////////////////
// Pop element from stack. Add appropriately to Function list and Control list
void StackOperation::pop_from_stack(int currLineNo)
	{
		std::pair<std::string, ScopeElement> item;

		if (ScopeStack<std::string,ScopeElement>::size() > 0)
		{
			item =  ScopeStack<std::string,ScopeElement>::pop();
		
			if ( item.first == "SCOPE-START" )
			{ recursive_pop(currLineNo); } // Recursive pop when Open Scope is popped.
			else
			{
				if ( item.first == "FUNCTION" && ( DataStore::getParseMode() == DataStore::FIRST_PASS ) )
				{ addFunctionToReporitory(item.second.name, currLineNo - item.second.lineNumber,DataStore::getCurr_function_cyclo() + 1,getCurrentScope(),currLineNo,item.second.lineNumber); }
				else if ( DataStore::getParseMode() == DataStore::FIRST_PASS && item.first == "CONTROL" )
				{ addControlToReporitory(item.second.name,currLineNo-item.second.lineNumber,getCurrentScope(),item.second.lineNumber,currLineNo); }

				recursive_pop(currLineNo); // After pop, initiate recuresive pop.
			}	
		}
	}

///////////////////////////////////////////////////////////////
// Function that recursively calls itself for pop.
void StackOperation::recursive_pop(int currLineNo)
	{
		std::pair<std::string, ScopeElement> item;
	
		if (ScopeStack<std::string,ScopeElement>::size() > 0)
		{
			item =  ScopeStack<std::string,ScopeElement>::pop();
		
			if ( item.first == "SCOPE-START" )
			{ ScopeStack<std::string,ScopeElement>::push(item);  }
			else
			{
				if ( item.first == "FUNCTION" && ( DataStore::getParseMode() == DataStore::FIRST_PASS ) )
				{ addFunctionToReporitory(item.second.name, currLineNo - item.second.lineNumber,DataStore::getCurr_function_cyclo() + 1,getCurrentScope(),currLineNo,item.second.lineNumber); }
				else if ( DataStore::getParseMode() == DataStore::FIRST_PASS && item.first == "CONTROL" )
				{ addControlToReporitory(item.second.name,currLineNo-item.second.lineNumber,getCurrentScope(),item.second.lineNumber,currLineNo); }

				recursive_pop(currLineNo);
			}
			
		}
	
	}

///////////////////////////////////////////////////////////////
// Function to push element on stack.
void StackOperation::push(std::string first,std::string name,int lineNumber)
	{
		if ( first == "FUNCTION" && ( DataStore::getParseMode() == DataStore::FIRST_PASS ) )
		{ 	
			DataStore::setCurr_function_cyclo(0);
		}

		std::pair<std::string, ScopeElement> item;
	
		item.first = first;
		item.second.name = name;
		item.second.lineNumber = lineNumber;

		ScopeStack<std::string,ScopeElement>::push(item);

		if ( DataStore::getParseMode() == DataStore::FIRST_PASS )
			UpdateDepthScopeNesting(); // On push, calculate new depth of scope.
	}

///////////////////////////////////////////////////////////////
// Function to get current scope from stack.
std::string StackOperation::getCurrentScope()
	{ 
		int len = ScopeStack<std::string,ScopeElement>::size();
		
		int count = 0;

		std::string scope = "";

		ScopeStack<std::string,ScopeElement>::iterator it;

		if ( len > 0 )
		{
			it = ScopeStack<std::string,ScopeElement>::end();
			it--;
			while ( it != ScopeStack<std::string,ScopeElement>::begin() )
			{
				if ( it->first == "CONTROL" || it->first == "FUNCTION" || it->first == "CLASS" || it->first == "NAMESPACE" )
				{ 
					if ( scope == "" )
						scope.insert(0,it->second.name); 
					else 
						scope.insert(0,it->second.name + "::"); 
				} it--;
			}
			if ( it->first == "CONTROL" || it->first == "FUNCTION" || it->first == "CLASS" || it->first == "NAMESPACE" )
				{ 
					if ( scope == "" )
						scope.insert(0,it->second.name); 
					else 
						scope.insert(0,it->second.name + "::");  
				}
		}
		return scope;
	}

//----< test stub >------------------------------------------------------

#ifdef TEST_SCOPESTACK

#include "ScopeStack.h"
#include <string>
#include <iostream>

typedef ScopeStack<std::string, ScopeElement> stack;

int main()
{
  std::cout << "\n  Testing Scope Stack";
  std::cout << "\n =====================\n";

  std::cout << "\n  pushing items onto ScopeStack instance";
  std::cout << "\n ----------------------------------------";
 
  std::pair<std::string, ScopeElement> item;

  item.first = "Function";
  item.second.name = "AddConfigureParser";
  item.second.lineNumber = 300;
  stack::push(item);

  item.first = "Control";
  item.second.name = "While";
  item.second.lineNumber = 67;
   stack::push(item);

  item.first = "Brace";
  item.second.name = "{";
  item.second.lineNumber = 45;
   stack::push(item);

  showStack<std::string, ScopeElement>(false);
  std::cout << std::endl;

  std::cout << "\n  pushing items onto ScopeStack with static methods";
  std::cout << "\n ---------------------------------------------------";

  item.first = "Function";
  item.second.name = "AddConfigureParser";
  item.second.lineNumber = 10;
  stack::push(item);

  item.first = "Control";
  item.second.name = "While";
  item.second.lineNumber = 20;
  stack::push(item);

  item.first = "Brace";
  item.second.name = "{";
  item.second.lineNumber = 30;
  stack::push(item);

  showStack<std::string, ScopeElement>(false);
  std::cout << std::endl;

  std::cout << "\n  Popping two items off ScopeStack";
  std::cout << "\n ----------------------------------";

  stack::iterator it = stack::end();

  it--;

  std::cout<<"Iterator : "<<it->first;

   stack::pop();
  stack::pop();

  showStack<std::string, ScopeElement>(false);
  std::cout << "\n\n";

  std::getchar();
}

#endif
