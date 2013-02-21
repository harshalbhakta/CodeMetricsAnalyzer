////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TestingNamespace.cpp (ver 1.0)  -  TEst file to test is namespace detection works.							  // 																					   
//		 																									  //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #1 - CodeMetricsAnalyzer, Spring 2011								  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "TestingNamespace.h"

using namespace OuterNameSpace::InnerNameSpace;

void TestingClass::function_cpp()
{

	int local_data = 10;	// Line : 19

	int member_data = 15;	// Line : 21
	member_data++;
	member_data++;
	member_data++;

	local_data = 15;	// Line : 26

}

void TestingClass::fucntion_cpp_2()
{
	#ifndef _7ZIP_ST
	{
	
	member_data = 20;
	
	}
	#endif
}


#ifdef TESTING

int main ( int argc, char* argv[] )
{


}

#endif
