#pragma once
#include <iostream>
#include "FbxEditorClass.h"
class FbxUtils
{
public:

	bool basicCheck(std::string pFile, std::string lDocinfo, std::string lGlobalProp, std::string lValue, bool lIsList, bool lIsAscii)
	{
		if (pFile.empty())
		{
			std::cout << "Error! no file input \n use -h or --help for options" << std::endl;
			return true;
		}
		if (!lDocinfo.empty() && !lGlobalProp.empty())
		{
			std::cout << "Error! chose only one type of property \n use -h or --help for options" << std::endl;
			return true;
		}
		if ((!lDocinfo.empty() || !lGlobalProp.empty()) && lIsList)
		{
			std::cout << "Error! chose only one type of option \n use -h or --help for options" << std::endl;
			return true;
		}
		if ((!lDocinfo.empty() || !lGlobalProp.empty()) && lValue.empty())
		{
			std::cout << "Error! please input Value using -v or --Value \n use -h or --help for options"<< std::endl;
			return true;
		}
		if (!hasEnding(pFile, ".fbx"))
		{
			std::cout << "Error! invalid file(input file is not fbx \n use -h or --help for options) " << std::endl;
			return true;
		}
		return false;
	}

	void findFunction(std::string pFile, std::string pDocinfo, std::string pGlobalProp, std::string pValue, bool pIsList, bool pIsAscii)
	{
		FbxEditorClass fbxEditor;
		if (pIsList)
		{
			fbxEditor.PrintProperties(pFile);
		}
		else if(!pDocinfo.empty())
		{
			fbxEditor.docInfoEditor(pFile, pDocinfo, pValue, pIsAscii);
		}
		else if (!pGlobalProp.empty())
		{
			fbxEditor.globalPropEditor(pFile, pGlobalProp, pValue, pIsAscii);
		}
		else if ((pDocinfo.empty() && pGlobalProp.empty()) && !pIsList)
		{
			fbxEditor.simpleExporter(pFile, pIsAscii);
		}
	}

	bool hasEnding(std::string const& lFullString, std::string const& lEnding) 
	{
		if (lFullString.length() >= lEnding.length()) {
			return (0 == lFullString.compare(lFullString.length() - lEnding.length(), lEnding.length(), lEnding));
		}
		else {

			return false;
		}
	}


};

