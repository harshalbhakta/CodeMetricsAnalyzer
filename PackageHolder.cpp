////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PackageHolder.cpp (ver 1.0)  -  Class holder to hold multiple packages and perform add/update operations.    // 																					   
//		 																									  //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #1 - CodeMetricsAnalyzer, Spring 2011								  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include "PackageHolder.h"

///////////////////////////////////////////////////////////////
// Static Map to hold all the packages.
std::map<std::string,Package> PackageHolder::PackageRepository;

///////////////////////////////////////////////////////////////
// Add Pacakge if does not exist. Else update FileName.
void PackageHolder::addPackage(std::string key,Package pk)
{
	if ( PackageHolder::PackageRepository.find(key) == PackageHolder::PackageRepository.end() )
	{
		PackageHolder::PackageRepository[key] = pk;
	}
	else 
	{
		if ( pk.getHeaderFile() != "" )
		{ PackageRepository[key].setHeaderFile(pk.getHeaderFile());	}
		if ( pk.getSourceFile() != "" )
		{ PackageRepository[key].setSourceFile(pk.getSourceFile());	}
	}
}

//////////////////////////////////////////////////////////////////
// Get vector of pair of < Header File Path , Source File Path >
std::vector<std::pair<std::string,std::string>> PackageHolder::getFilePackages()
{
	std::map<std::string,Package>::iterator iter;

	std::vector<std::pair<std::string,std::string>> vectReturn;

	for ( iter = PackageHolder::PackageRepository.begin() ; iter != PackageHolder::PackageRepository.end(); iter++)
	{
		std::pair<std::string,std::string> temp;

		temp.first = iter->second.getHeaderFile();
		temp.second = iter->second.getSourceFile();

		vectReturn.push_back(temp);
	}

	return vectReturn;
}

//////////////////////////////////////////////////////////////////
// Get vector of package names.
std::set<std::string> PackageHolder::getPackageList()
{
	std::map<std::string,Package>::iterator iter;

	std::set<std::string> vectPacakges;

	for ( iter = PackageHolder::PackageRepository.begin() ; iter != PackageHolder::PackageRepository.end(); iter++)
	{
		std::string temp;

		temp = iter->first;

		vectPacakges.insert(temp);
	}

	return vectPacakges;
}

///////////////////////////////////////////////////////////////
// Return the reference for the Package based on key.
Package* PackageHolder::getPackage(std::string key)
{
	return &PackageHolder::PackageRepository[key];
}

///////////////////////////////////////////////////////////////
// Return the Function Object vector for the package name.
std::vector<Function> PackageHolder::getFunctionList(std::string package)
{
	return PackageHolder::PackageRepository[package].getFunctionList();
}

///////////////////////////////////////////////////////////////
// Return the Control Object vector for the package name.
std::vector<Control> PackageHolder::getControlList(std::string package)
{
	return PackageHolder::PackageRepository[package].getControlList();
}

///////////////////////////////////////////////////////////////
// Add Function to the Package.
void PackageHolder::addFunctionToPackage(std::string package,Function fn)
{
	PackageRepository[package].addFunction(fn);
}

///////////////////////////////////////////////////////////////
// Add Control to the Package.
void PackageHolder::addControlToPackage(std::string package,Control ct)
{
	PackageRepository[package].addControl(ct);
}

///////////////////////////////////////////////////////////////
// Add / Update Variable to the Package. If varaible already exist, Update Locality of Reference.
void PackageHolder::addUpdateVariableToPackage(std::string package,std::string name, std::string fromFile ,int fromLine,std::string toFile,int toLine,int loc_reference)
{
	Package* pkPtr = PackageHolder::getPackage(package);

	pkPtr->addVariable( package,name,fromFile ,fromLine,toFile, toLine, loc_reference);
}

///////////////////////////////////////////////////////////////
// Get the Package to print / display.
Package PackageHolder::getPackageToPrint(std::string pkg)
{
	return PackageHolder::PackageRepository[pkg];
}

///////////////////////////////////////////////////////////////
// Function to get the Depth of Nesting.
int PackageHolder::getDepthOfNesting(std::string key)
{
	Package* pkPtr = PackageHolder::getPackage(key);

	return pkPtr->getDepthOfNesting();
}

///////////////////////////////////////////////////////////////
// Function to update the Depth of Nesting.
void PackageHolder::setDepthOfNesting(std::string key,int scope)
{
	Package* pkPtr = PackageHolder::getPackage(key);

	if (pkPtr->getDepthOfNesting() < scope)
		pkPtr->setDepthOfNesting(scope);
}

///////////////////////////////////////////////////////////////
// Test Stub.
#ifdef TEST_PACKAGE_HOLDER
int main(int argc, char* argv[])
{
	/* 

	Package pk;

	PackageHolder::addPackage("Package1",pk);	

	PackageHolder::add

	Variable vb;

	vb.setVariableName("TestVariable");
	vb.setRefDensity(12);
	vb.setLocReference(2);

	pkPtr->addVariable(vb);

	std::vector<Variable>* vbPtr =  pkPtr->getVariableList();

	for ( int i = 0 ; i < (int)((*vbPtr).size()) ; i++)
	{
	    std::cout<<std::endl<<"Value is "<<(*vbPtr)[i].getVariableName();	
	}

	std::getchar();
	*/
}

#endif 

