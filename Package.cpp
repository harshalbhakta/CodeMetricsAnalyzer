////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Package.cpp (ver 1.0)  -  Class to hold information about each package ( .h + .cpp ) file.				  // 																					   
//		 																									  //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #1 - CodeMetricsAnalyzer, Spring 2011								  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Package.h"

///////////////////////////////////////////////////////////////
// Function to add the control to the list of controls.
void Package::addControl(Control ct)
{ ControlList.push_back(ct); }

///////////////////////////////////////////////////////////////
// Function to add the function to the list of controls.
void Package::addFunction(Function fn)
{ FunctionList.push_back(fn);  }

///////////////////////////////////////////////////////////////
// Function to add the variable to the list of controls.
void Package::addVariable(std::string package,std::string name, std::string fromFile ,int fromLine,std::string toFile,int toLine,int loc_reference)
{ 

	std::vector<Variable>* vbPtr = this->getVariableList();
	
	bool variable_exists = false;

	for ( int i = 0 ; i < (int)(*vbPtr).size() ; i++)
	{
		if ( (*vbPtr)[i].getVariableName() == name )
		{ 
			variable_exists = true; 
			
			(*vbPtr)[i].setRefDensity((*vbPtr)[i].getRefDensity()+1);
			
			if ( (*vbPtr)[i].getLocReference() < loc_reference )
			{   // Update only when new locality of reference detected.
				(*vbPtr)[i].setLocReference(loc_reference); 
				(*vbPtr)[i].setFromFileName(fromFile);
				(*vbPtr)[i].setFromFileLine(fromLine);
				(*vbPtr)[i].setToFileName(toFile);
				(*vbPtr)[i].setToFileLine(toLine);
			}

			break; 
		}
	}

	if  ( !variable_exists )
	{   // Variable not detected yet. Add to list.
		Variable vb;

		vb.setVariableName(name);
		vb.setFromFileName(fromFile);
		vb.setFromFileLine(fromLine);
		vb.setToFileName(toFile);
		vb.setToFileLine(toLine);
		vb.setRefDensity(1);
		vb.setLocReference(loc_reference);

		(*vbPtr).push_back(vb);
	}

}

///////////////////////////////////////////////////////////////
// Test Stub.
#ifdef TEST_PACKAGE

void main ( int argc , char *argv[] )
{

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
	// ct.setBreadthControlSpan(12);

	std::cout<<"CT -> Breadth Control Span = " << ct.getBreadthControlSpan();

	pk.addFunction(fk);
	pk.addControl(ct);
	pk.addVariable(vb);

	std::getchar();
}

#endif
