#ifndef SCOPESTACK_H
#define SCOPESTACK_H
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ScopeStack.h (ver 3.0)  -  Added the ScopeElement Struct for holing 2 values.							  // 																					   
//		 					  Added the StackOperation to perform custom stack operations.			   	      //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #1 - CodeMetricsAnalyzer, Spring 2011								  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// ScopeStack.h - implements template stack holding items with two values  //
//                                                                         //
// version 2.0 - fixed bug in pop() method found by Drumil Bhattad         //
//                                                                         //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2011               //
/////////////////////////////////////////////////////////////////////////////

/*
  Module Operations: 
  ==================

  This module defines a a ScopeStack that will hold a String and a ScopeElement. Basic functionalities 
  related to a stack are supported. Push - Pop. Stack will be static as it has to be shared accross program.

  Public Interface:
  =================
  std::pair<std::string, ScopeElement> item;	// Access Stack

  item.first = "Function";	// Add First String
  item.second.name = "AddConfigureParser";	// Scope Element -> First
  item.second.lineNumber = 300;	// Scope Element -> Second
  stack::push(item);
	
  showStack<std::string, ScopeElement>(false);	// Show Stack.

  stack::pop();	// Pop Stack.

  pop_from_stack(int ); // Pop element from the stack. Current line number is the input.

  recursive_pop(int ); // Recursively pop element from stack based on scope.

  push(std::string ,std::string ,int ); // Push element to stack.
 
  std::string getCurrentScope(); // Get Current Scope.

  Build Process:
  ==============
  Required files
    - ScopeStack.cpp
  Build commands
    - devenv CodeMetricsAnalyzer.sln /rebuild debug

  Maintenance History:
  ====================
  ver 3.0 : 25 Feb 11
  - Added Scope Element to hold 2 values.
*/

#include <list>
#include <string>

struct ScopeElement{
	std::string name;
	int lineNumber;
};

///////////////////////////////////////////////////////////////
// Class with Static Method to pop element from stack.
class StackOperation {

	static void UpdateDepthScopeNesting();

	static void addFunctionToReporitory(std::string ,int ,int ,std::string ,int , int  );

	static void addControlToReporitory(std::string ,int ,std::string ,int , int  );

public : 

	static void pop_from_stack(int );

	static void recursive_pop(int );

	static void push(std::string ,std::string ,int );

	static std::string getCurrentScope();

};

///////////////////////////////////////////////////////////////
//  Class : Stack
template<typename T, typename N>
class ScopeStack {
public:
  typename typedef std::list< std::pair<T,N> >::iterator iterator;
  static void push(const std::pair<T,N>& item);
  static std::pair<T,N> pop();
  static size_t size();
  static iterator begin();
  static iterator end();
private:
  static std::list< std::pair<T,N> > stack;
};
template<typename T, typename N>
std::list< std::pair<T,N> > ScopeStack<typename T, typename N>::stack;

template<typename T, typename N>
typename inline size_t ScopeStack<T,N>::size() { return stack.size(); }

///////////////////////////////////////////////////////////////
//  ScopeStack : Basic Stack.
template<typename T, typename N>
typename inline ScopeStack<T,N>::iterator ScopeStack<T,N>::begin() { return stack.begin(); }

///////////////////////////////////////////////////////////////
//  Stack
template<typename T, typename N>
typename inline ScopeStack<T,N>::iterator ScopeStack<T,N>::end() { return stack.end(); }

///////////////////////////////////////////////////////////////
//  Push the item.
template<typename T, typename N>
void ScopeStack<T,N>::push(const std::pair<T,N>& item)
{
  stack.push_back(item);
}

///////////////////////////////////////////////////////////////
//  Pop the item.
template<typename T, typename N>
std::pair<T,N> ScopeStack<T,N>::pop() 
{ 
  std::pair<T,N> item = stack.back(); 
  stack.pop_back(); 
  return item; 
}

///////////////////////////////////////////////////////////////
//  Display Stack.
template<typename T, typename N>
void showStack(bool indent=true)
{
  if(ScopeStack<T,N>::size() == 0)
  {
    std::cout << "\n  ScopeStack is empty";
    return;
  }
  ScopeStack<T,N>::iterator iter = ScopeStack<T,N>::begin();
  while(iter != ScopeStack<T,N>::end())
  {
    std::string strIndent = std::string(2*ScopeStack<T,N>::size(),' ');
    if(!indent)
      strIndent = "";
    std::cout << "\n  " << strIndent << "(" << (*iter).first;
	std::cout << ", " << (*iter).second.name << ", " << (*iter).second.lineNumber << ")";
    ++iter;
  }
}
#endif
