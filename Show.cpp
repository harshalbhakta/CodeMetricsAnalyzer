////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Show.cpp (ver 1.0)  -  Module to display analysis results.												  // 																					   
//		 																									  //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #1 - CodeMetricsAnalyzer, Spring 2011								  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Show.h"
#include "PackageHolder.h"
#include <iomanip>
#include <set>
#include <sstream>

///////////////////////////////////////////////////////////////
// Default Values to be considerd when printing values.
//
#define CYCLO_LIMIT 10
#define MAX_FUNC_SIZE 50
#define LOC_OF_REFERENCE 20
#define PAK_REFERENCE_DENSITY 10
#define BREADTH_CONTROL_SIZE 20
#define MAX_IDENTIFIERS 20

///////////////////////////////////////////////////////////////
//  Function to print statistics in the normal mode.
void Show::printVerbose(std::string package)
{
	try 
	{

	Package pkg = PackageHolder::getPackageToPrint(package);

	std::cout<<"\n\n  "<<package<<"\n "<<std::string(50,'=')<<"\n";

		printVerboseFunctions(pkg);

		printVerboseControls(pkg);

		printVerboseVariables(pkg);

		printSummary(pkg);
	}
	catch ( std::exception ex)
	{ std::cout<<"Error Displaying values : "<<ex.what(); }
}

///////////////////////////////////////////////////////////////
//  Function to print summary.
void Show::printSummary(Package pk)
{
		std::cout<<"\n\n  Summary"<<"\n";
		std::cout<<"  "<<std::string(49,'-')<<"\n";
		
		std::vector<Function> fnPtr =  pk.getFunctionList();
		std::vector<Control> ctPtr =  pk.getControlList();
		std::vector<Variable> vbPtr = pk.getVariableListPrint();

		int maxComplexity = 0 ; int maxFunctionSize = 0;
		int maxBreadthControl = 0; int maxLocOfRef = 0;
		int maxRefDensity = 0;

		for ( int i = 0 ; i < (int)(fnPtr.size()) ; i++)
		{   // Fetch Max Complexity and Function Size.
			if ( fnPtr[i].getCycloComplexity() > maxComplexity )
				maxComplexity = fnPtr[i].getCycloComplexity();
			if ( fnPtr[i].getNoOfLines() > maxFunctionSize )
				maxFunctionSize = fnPtr[i].getNoOfLines();
		}
		for ( int i = 0 ; i < (int)(ctPtr.size()) ; i++)
		{   // Fetch Max Breadth Control.
			if ( ctPtr[i].getBreadthControlSpan() > maxBreadthControl )
				maxBreadthControl = ctPtr[i].getBreadthControlSpan();
		}
		for ( int i = 0 ; i < (int)(vbPtr.size()) ; i++)
		{   // Fetch Max Loc of reference & Ref. Density.
			if ( vbPtr[i].getLocReference() > maxLocOfRef )
				maxLocOfRef = vbPtr[i].getLocReference();
			if ( vbPtr[i].getRefDensity() > maxRefDensity )
				maxRefDensity = vbPtr[i].getRefDensity();
		}
		std::cout<<"  Depth Of Scope Nesting	: "<< pk.getDepthOfNesting()<<"\n";
		std::cout<<"  Maximum Function Size		: "<< maxFunctionSize<<"\n";
		std::cout<<"  Maximum Function Complexity	: "<< maxComplexity<<"\n";
		std::cout<<"  Maximum Control Size		: "<< maxBreadthControl<<"\n";
		std::cout<<"  Maximum Loc Of Reference	: "<< maxLocOfRef<<"\n";
		std::cout<<"  Maximum Reference Density	: "<< maxRefDensity<<"\n";
		int NumberOfIdentifiers = CalculateNumberOfIdentifiers(pk);
		std::cout<<"  Number of Identifiers 	: "<< NumberOfIdentifiers;
}

int Show::CalculateNumberOfIdentifiers(Package pk)
{
	std::vector<Function> fnPtr =  pk.getFunctionList();
	std::vector<Variable> vbPtr = pk.getVariableListPrint();

	std::set<std::string> names;

		for ( int i = 0 ; i < (int)(fnPtr.size()) ; i++)
		{   // Fetch Max Complexity and Function Size.
			names.insert(fnPtr[i].getFunctionName().substr(0,fnPtr[i].getFunctionName().find_first_of("(")));
		}

		for ( int i = 0 ; i < (int)(vbPtr.size()) ; i++)
		{   // Fetch Max Loc of reference & Ref. Density.
			names.insert(vbPtr[i].getVariableName().substr(vbPtr[i].getVariableName().find_last_of("::")+1));
		}

		return names.size();
}

///////////////////////////////////////////////////////////////
//  Function to print Function Statistics.
void Show::printVerboseFunctions(Package pk)
{
		std::vector<Function> fnPtr =  pk.getFunctionList();

		std::cout<<"\n  "<<std::setw(5)<<"cyclo"<<" "<<"lines"<<" "<<"  function name"<<"\n";

		std::cout<<"  "<<std::string(49,'-')<<"\n";

		for ( int i = 0 ; i < (int)(fnPtr.size()) ; i++)
		{
			std::cout<<"  "<<std::setw(5)<<fnPtr[i].getCycloComplexity()<<" "<<std::setw(5)<<fnPtr[i].getNoOfLines()<<"   "<<fnPtr[i].getFunctionName().substr(0,fnPtr[i].getFunctionName().find_first_of("("))<<"\n";
		}
}

///////////////////////////////////////////////////////////////
//  Function to print Control Statistics.
void Show::printVerboseControls(Package pk)
{
	    std::vector<Control> ctPtr =  pk.getControlList();

		std::cout<<"\n  "<<std::setw(5)<<"size"<<" "<<"  control name"<<"\n";

		std::cout<<"  "<<std::string(49,'-')<<"\n";

		for ( int i = 0 ; i < (int)(ctPtr.size()) ; i++)
		{
			std::cout<<"  "<<std::setw(5)<<ctPtr[i].getBreadthControlSpan() <<"   "<<ctPtr[i].getControlName()<<"\n";
		}
}

///////////////////////////////////////////////////////////////
//  Function to print Variable Statistics.
void Show::printVerboseVariables(Package pk)
{
		std::vector<Variable> vbPtr =  pk.getVariableListPrint();

		std::cout<<"\n"<<std::setw(10)<<"from"<<" "<<std::setw(10)<<"to"<<" "<<std::setw(8)<<"locality"<<" "<<std::setw(8)<<"density"<<"   "<<"variable name"<<"\n";

		std::cout<<"  "<<std::string(49,'-')<<"\n";

		for ( int i = 0 ; i < (int)(vbPtr.size()) ; i++)
		{

			std::string fromFile = "";
			std::string toFile = "";

			if (vbPtr[i].getFromFileName().length() > 2 && vbPtr[i].getFromFileName().substr(vbPtr[i].getFromFileName().length()-2) == ".h")
				fromFile = ".h"; // Display .h when fromLine comes from Header File.
			else 
				fromFile = ".cpp";// Display .cpp when fromLine comes from Source File.

			if (vbPtr[i].getToFileName().length() > 2 && vbPtr[i].getToFileName().substr(vbPtr[i].getToFileName().length()-2) == ".h")
				toFile = ".h";  
			else 
				toFile = ".cpp";

			{
			std::stringstream out;
			out << vbPtr[i].getFromFileLine();
			fromFile = fromFile + "-" + out.str();
			}

			{
			std::stringstream out;
			out << vbPtr[i].getToFileLine();
			toFile = toFile + "-" + out.str();
			}

			std::cout<<"\n"<<std::setw(10)<<fromFile<<" "<<std::setw(10)<<toFile<<" "<<std::setw(8)<<vbPtr[i].getLocReference()<<" "<<std::setw(8)<<vbPtr[i].getRefDensity()<<"   "<<vbPtr[i].getVariableName(); 
		}
}

///////////////////// NORMAL //////////////////////////////

void Show::printNormal(std::string package)
{
	try 
	{
	Package pkg = PackageHolder::getPackageToPrint(package);

	std::cout<<"\n\n  "<<package<<"\n "<<std::string(50,'=')<<"\n";

		printFunctions(pkg);

		printControls(pkg);

		printVariables(pkg);

		printSummary(pkg);
	}
	catch ( std::exception ex)
	{ std::cout<<"Error displaying values. : "<<ex.what(); }
}

///////////////////////////////////////////////////////////////
//  Function to print Function Statistics.
void Show::printFunctions(Package pk)
{
		std::vector<Function> fnPtr =  pk.getFunctionList();

		std::cout<<"\n  "<<std::setw(5)<<"cyclo"<<" "<<"lines"<<" "<<"  function name"<<"\n";

		std::cout<<"  "<<std::string(49,'-')<<"\n";

		for ( int i = 0 ; i < (int)(fnPtr.size()) ; i++)
		{
			if ( fnPtr[i].getNoOfLines() > MAX_FUNC_SIZE || fnPtr[i].getCycloComplexity() > CYCLO_LIMIT )
			std::cout<<"  "<<std::setw(5)<<fnPtr[i].getCycloComplexity()<<" "<<std::setw(5)<<fnPtr[i].getNoOfLines()<<"   "<<fnPtr[i].getFunctionName().substr(0,fnPtr[i].getFunctionName().find_first_of("("))<<"\n";
		}
}

///////////////////////////////////////////////////////////////
//  Function to print Control Statistics.
void Show::printControls(Package pk)
{
	    std::vector<Control> ctPtr =  pk.getControlList();

		std::cout<<"\n  "<<std::setw(5)<<"size"<<" "<<"  control name"<<"\n";

		std::cout<<"  "<<std::string(49,'-')<<"\n";

		for ( int i = 0 ; i < (int)(ctPtr.size()) ; i++)
		{
			if ( ctPtr[i].getBreadthControlSpan() > BREADTH_CONTROL_SIZE )
			{ std::cout<<"  "<<std::setw(5)<<ctPtr[i].getBreadthControlSpan() <<"   "<<ctPtr[i].getControlName()<<"\n"; }
		}
}

///////////////////////////////////////////////////////////////
//  Function to print Variable Statistics.
void Show::printVariables(Package pk)
{
		std::vector<Variable> vbPtr =  pk.getVariableListPrint();

		std::cout<<"\n"<<std::setw(10)<<"from"<<" "<<std::setw(10)<<"to"<<" "<<std::setw(8)<<"locality"<<" "<<std::setw(8)<<"density"<<"   "<<"variable name"<<"\n";

		std::cout<<"  "<<std::string(49,'-')<<"\n";

		for ( int i = 0 ; i < (int)(vbPtr.size()) ; i++)
		{

			std::string fromFile = "";
			std::string toFile = "";

			if (vbPtr[i].getFromFileName().length() > 2 && vbPtr[i].getFromFileName().substr(vbPtr[i].getFromFileName().length()-2) == ".h")
			{ fromFile = ".h"; } // Display .h when fromLine comes from Header File.
			else 
			{ fromFile = ".cpp"; } // Display .cpp when fromLine comes from Source File. 

			if (vbPtr[i].getToFileName().length() > 2 && vbPtr[i].getToFileName().substr(vbPtr[i].getToFileName().length()-2) == ".h")
			{ toFile = ".h";  }
			else 
			{ toFile = ".cpp"; }

			if ( vbPtr[i].getLocReference() > LOC_OF_REFERENCE || vbPtr[i].getRefDensity() > PAK_REFERENCE_DENSITY ) 
			{
				{
				std::stringstream out;
				out << vbPtr[i].getFromFileLine();
				fromFile = fromFile + "-" + out.str();
				}

				{
				std::stringstream out;
				out << vbPtr[i].getToFileLine();
				toFile = toFile + "-" + out.str();
				}

				std::cout<<"\n"<<std::setw(10)<<fromFile<<" "<<std::setw(10)<<toFile<<" "<<std::setw(8)<<vbPtr[i].getLocReference()<<" "<<std::setw(8)<<vbPtr[i].getRefDensity()<<"   "<<vbPtr[i].getVariableName().substr(vbPtr[i].getVariableName().find_last_of("::")+1); 
			}
		}
}

///////////////////////////////////////////////////////////////
//  Print Header for the CMA application.
void Show::printHeader()
{
		std::cout<<std::endl<<"--------------------------------------------------------";
		std::cout<<std::endl<<"	  Code Metrics Analyzer : CMA , v1.0	";
		std::cout<<std::endl<<"--------------------------------------------------------";
		std::cout<<std::endl<<"C++ Code Analysis Program		Harshal Bhakta	";
		std::cout<<std::endl<<"--------------------------------------------------------";
		std::cout<<std::endl<<"---     MAX_FUNC_SIZE : 50	   CYCLO_LIMIT : 10  ---";
		std::cout<<std::endl<<"---  LOC_OF_REFERENCE : 20     MAX_IDENTIFIERS : 20  ---";
		std::cout<<std::endl<<"--- REFERENCE_DENSITY : 10     BREADTH_CONTROL : 20  ---";
		std::cout<<std::endl<<"--------------------------------------------------------";
		std::cout<<std::endl;

		std::cout<<std::endl<<"--------------------------------------------------------";
		std::cout<<std::endl<<"	 GATHERING FILES FOR ANALYSIS				";
		std::cout<<std::endl<<"--------------------------------------------------------";
}

///////////////////////////////////////////////////////////////
//  Print overall summmary afte all analysis is done.
void Show::printOverAllSummary()
{

	try
	{

		std::set<std::string> packages = PackageHolder::getPackageList();
		
		int maxComplexity = 0 ; int maxFunctionSize = 0;
		int maxBreadthControl = 0; int maxLocOfRef = 0; int maxRefDensity = 0;

		std::vector<Function> displayFnPtr; std::vector<Control> displayCtPtr; std::vector<Variable> displayVbPtr;

		for each ( std::string package in packages)
		{
		
		 Package pk = PackageHolder::getPackageToPrint(package);

		  getExceededFunction(pk,displayFnPtr,maxComplexity,maxFunctionSize);

		  getExceededControl(pk,displayCtPtr,maxBreadthControl);

		  getExceededVariable(pk,displayVbPtr,maxLocOfRef,maxRefDensity);

		}
		printOverAllStatistics(displayFnPtr,displayCtPtr,displayVbPtr);

		std::cout<<"\n\n  Summary"<<"\n";
		std::cout<<"  "<<std::string(49,'-')<<"\n";

		std::cout<<"  Maximum Function Size		: "<< maxFunctionSize<<"\n";
		std::cout<<"  Maximum Function Complexity	: "<< maxComplexity<<"\n";
		std::cout<<"  Maximum Control Size		: "<< maxBreadthControl<<"\n";
		std::cout<<"  Maximum Loc Of Reference	: "<< maxLocOfRef<<"\n";
		std::cout<<"  Maximum Reference Density	: "<< maxRefDensity<<"\n";
	}
	catch ( std::exception ex )
		{ std::cout<<"Error displaying Overall Summary : "<<ex.what(); }
}

///////////////////////////////////////////////////////////////
//  Function to print statistics related to exceeded entries.
void Show::printOverAllStatistics(std::vector<Function> fnPtr,std::vector<Control> ctPtr,std::vector<Variable> vbPtr)
{
		std::cout<<"\n\n  Overall Summary (Violations listed below)\n "<<std::string(50,'=')<<"\n";

		std::cout<<"\n  "<<std::setw(5)<<"cyclo"<<" "<<"lines"<<" "<<"  function name"<<"\n"; std::cout<<"  "<<std::string(49,'-')<<"\n";

		for ( int i = 0 ; i < (int)(fnPtr.size()) ; i++)
		{
			if ( fnPtr[i].getNoOfLines() > MAX_FUNC_SIZE || fnPtr[i].getCycloComplexity() > CYCLO_LIMIT )
			std::cout<<"  "<<std::setw(5)<<fnPtr[i].getCycloComplexity()<<" "<<std::setw(5)<<fnPtr[i].getNoOfLines()<<"   "<<fnPtr[i].getFunctionName().substr(0,fnPtr[i].getFunctionName().find_first_of("("))<<"\n";
		}

		std::cout<<"\n  "<<std::setw(5)<<"size"<<" "<<"  control name"<<"\n"; std::cout<<"  "<<std::string(49,'-')<<"\n";

		for ( int i = 0 ; i < (int)(ctPtr.size()) ; i++)
		{
			if ( ctPtr[i].getBreadthControlSpan() > BREADTH_CONTROL_SIZE )
			{ std::cout<<"  "<<std::setw(5)<<ctPtr[i].getBreadthControlSpan() <<"   "<<ctPtr[i].getControlName()<<"\n"; }
		}
		std::cout<<"\n"<<std::setw(10)<<"from"<<" "<<std::setw(10)<<"to"<<" "<<std::setw(8)<<"locality"<<" "<<std::setw(8)<<"density"<<"   "<<"variable name"<<"\n"; std::cout<<"  "<<std::string(49,'-')<<"\n";

		for ( int i = 0 ; i < (int)(vbPtr.size()) ; i++)
		{
			std::string fromFile = ""; std::string toFile = "";

			if (vbPtr[i].getFromFileName().length() > 2 && vbPtr[i].getFromFileName().substr(vbPtr[i].getFromFileName().length()-2) == ".h")
				fromFile = ".h"; // Display .h when fromLine comes from Header File.
			else 
				fromFile = ".cpp";// Display .cpp when fromLine comes from Source File.
			if (vbPtr[i].getToFileName().length() > 2 && vbPtr[i].getToFileName().substr(vbPtr[i].getToFileName().length()-2) == ".h")
				toFile = ".h";  
			else 
				toFile = ".cpp";

			{ std::stringstream out;	out << vbPtr[i].getFromFileLine(); fromFile = fromFile + "-" + out.str(); }

			{ std::stringstream out; 	out << vbPtr[i].getToFileLine(); toFile = toFile + "-" + out.str();       }

			std::cout<<"\n"<<std::setw(10)<<fromFile<<" "<<std::setw(10)<<toFile<<" "<<std::setw(8)<<vbPtr[i].getLocReference()<<" "<<std::setw(8)<<vbPtr[i].getRefDensity()<<"   "<<vbPtr[i].getVariableName().substr(vbPtr[i].getVariableName().find_last_of("::")+1); 
		}
}

///////////////////////////////////////////////////////////////
//  Function to fetch the list of exceeded functions
void Show::getExceededFunction(Package pk,std::vector<Function>& displayFnPtr,int& maxComplexity,int& maxFunctionSize)
{
	
		std::vector<Function> fnPtr =  pk.getFunctionList();

		for ( int i = 0 ; i < (int)(fnPtr.size()) ; i++)
		{   // Fetch Max Complexity and Function Size.
			if ( fnPtr[i].getCycloComplexity() > maxComplexity )
				maxComplexity = fnPtr[i].getCycloComplexity();
			if ( fnPtr[i].getNoOfLines() > maxFunctionSize )
				maxFunctionSize = fnPtr[i].getNoOfLines();
			if ( fnPtr[i].getNoOfLines() > MAX_FUNC_SIZE || fnPtr[i].getCycloComplexity() > CYCLO_LIMIT )
			{ displayFnPtr.push_back(fnPtr[i]); }
		}

}

///////////////////////////////////////////////////////////////
//  Function to fetch the list of exceeded controls.
 void Show::getExceededControl(Package pk,std::vector<Control>& displayCtPtr,int &maxBreadthControl)
 {
		std::vector<Control> ctPtr =  pk.getControlList();
 
		for ( int i = 0 ; i < (int)(ctPtr.size()) ; i++)
		{   // Fetch Max Breadth Control.
			if ( ctPtr[i].getBreadthControlSpan() > maxBreadthControl )
				maxBreadthControl = ctPtr[i].getBreadthControlSpan();
			if ( ctPtr[i].getBreadthControlSpan() > BREADTH_CONTROL_SIZE )
			{ displayCtPtr.push_back(ctPtr[i]);	}
		}
 }

 ///////////////////////////////////////////////////////////////
//  Function to fetch the list of exceeded variables.
void Show::getExceededVariable(Package pk,std::vector<Variable>& displayVbPtr,int& maxLocOfRef,int& maxRefDensity)
{
		std::vector<Variable> vbPtr =  pk.getVariableListPrint();

		for ( int i = 0 ; i < (int)(vbPtr.size()) ; i++)
		{   // Fetch Max Loc of reference & Ref. Density.
			if ( vbPtr[i].getLocReference() > maxLocOfRef )
				maxLocOfRef = vbPtr[i].getLocReference();
			if ( vbPtr[i].getRefDensity() > maxRefDensity )
				maxRefDensity = vbPtr[i].getRefDensity();
			if ( vbPtr[i].getLocReference() > LOC_OF_REFERENCE || vbPtr[i].getRefDensity() > PAK_REFERENCE_DENSITY ) 
			{ displayVbPtr.push_back(vbPtr[i]);	}
		}
}

#ifdef TEST_SHOW

int main(int argc,char* argv[])
{

	Package pk;

	Function fk;

	fk.setFunctionName("Test");
	fk.setNoOfLines(12);
	fk.setCycloComplexity(15);

	Variable vb;

	vb.setVariableName("LocOfReference");
	vb.setLocReference(20);
	vb.setRefDensity(5);
	vb.setFromFileLine(3);
	vb.setFromFileName("asda");
	vb.setToFileLine(2);

	Control ct;

	ct.setControlName("For");
	ct.setBreadthControlSpan(10);
	ct.setFromLine(2);
	ct.setToLine(5);
	ct.setScope("TYPE");

	pk.addFunction(fk);
	pk.addControl(ct);
	pk.addVariable("test","sad","asdas" ,12,"asd", 34, 2);

	PackageHolder::addPackage("test",pk);

	PackageHolder::setDepthOfNesting("test",15);

	Show::printNormal("test");

	std::getchar();
}

#endif