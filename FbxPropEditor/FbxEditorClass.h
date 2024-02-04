#pragma once
#include <fbxsdk.h>
#include <assert.h>
#include<iostream>
#include <string>
#include <vector>

class FbxEditorClass
{
public:
	FbxManager* FbxSdkMngr = nullptr;

	FbxEditorClass()
	{
		FbxSdkMngr = FbxManager::Create();
		assert(FbxSdkMngr != nullptr);
	}

	~FbxEditorClass()
	{
		FbxSdkMngr->Destroy();
		FbxSdkMngr = nullptr;
	}
	FbxScene* createScene(std::string lFile)
	{
		FbxScene* pScene = nullptr;
		FbxImporter* lImporter = FbxImporter::Create(FbxSdkMngr, "FBXimporter");
		if(lFile.empty())
		{
			std::cout << "empty" << std::endl;
		}
		if (!lImporter->Initialize(lFile.c_str(), -1, FbxSdkMngr->GetIOSettings()))
		{
			std::cout << "Error! Faild to load file " + lFile + " \n use -h or --help for options" << std::endl;
			lImporter->Destroy();
			return pScene;
		}
		pScene = FbxScene::Create(FbxSdkMngr, "importScene");

		if (!lImporter->Import(pScene))
		{
			std::cout << "Error! Faild to import scene " + lFile +" \n use -h or --help for options" << std::endl;
			lImporter->Destroy();
			return pScene;
		}
		lImporter->Destroy();
		return pScene;
	}

	void PrintProperties(std::string pFile)
	{
		FbxScene* lScene = createScene(pFile);
		if (lScene == nullptr)
		{
			return;
		}
		FbxDocumentInfo* lDocInfo = FbxDocumentInfo::Create(FbxSdkMngr, "docinfo");
		FbxGlobalSettings* lGlobalProps = FbxGlobalSettings::Create(FbxSdkMngr, "globalProps");
		FbxProperty lProperty = lDocInfo->GetFirstProperty();
		std::cout << "Document_Info :" << std::endl;
		while (lProperty.IsValid())
		{
			std::cout << "\t" + lProperty.GetHierarchicalName() << std::endl;
			lProperty = lDocInfo->GetNextProperty(lProperty);
			
		}
		lProperty = lGlobalProps->GetFirstProperty();
		std::cout << "Global_Settings :" << std::endl;
		while (lProperty.IsValid())
		{
			std::cout << "\t" + lProperty.GetHierarchicalName() << std::endl;
			lProperty = lGlobalProps->GetNextProperty(lProperty);

		}


	}

	void docInfoEditor(std::string pFile, std::string lPropName, std::string lValue, bool pIsAscii)
	{
		FbxScene* pScene = createScene(pFile);
		if (pScene == nullptr)
		{
			return;
		}
		FbxDocumentInfo* lDocInfo = FbxDocumentInfo::Create(FbxSdkMngr, "docinfo");
		FbxProperty lProperty = lDocInfo->FindPropertyHierarchical(lPropName.c_str());
		if (!lProperty.IsValid())
		{
			std::cout << "Error! Unable to locate the property \n use -h or --help for options";
			return;
		}
		FbxDataType lDataType = propDataType(lProperty);
		if (lDataType.Is(FbxStringDT))
		{
			pScene->GetDocumentInfo()->FindPropertyHierarchical(lPropName.c_str()).Set<FbxString>(lValue.c_str());
		}
		else if (lDataType.Is(FbxDateTimeDT))
		{
			FbxDateTime lDateTime;
			if (!lDateTime.fromString(lValue.c_str()))
			{
				std::cout << "Error! invalid time input \n use -h or --help for options";
				return;
			}
			pScene->GetDocumentInfo()->FindPropertyHierarchical(lPropName.c_str()).Set(lDateTime);
		}

		else if (lDataType.Is(FbxIntDT))
		{
			pScene->GetDocumentInfo()->FindPropertyHierarchical(lPropName.c_str()).Set(FbxInt(lValue.c_str()));
		}
		else if (lDataType.Is(FbxDoubleDT))
		{
			pScene->GetDocumentInfo()->FindPropertyHierarchical(lPropName.c_str()).Set(FbxInt(lValue.c_str()));
		}
		else if (lDataType.Is(FbxTimeDT))
		{
			pScene->GetDocumentInfo()->FindPropertyHierarchical(lPropName.c_str()).Set(FbxInt(lValue.c_str()));
		}
		else if (lDataType.Is(FbxEnumDT))
		{
			pScene->GetDocumentInfo()->FindPropertyHierarchical(lPropName.c_str()).Set(FbxInt(lValue.c_str()));
		}
		else if (lDataType.Is(FbxColor3DT))
		{
			pScene->GetDocumentInfo()->FindPropertyHierarchical(lPropName.c_str()).Set(FbxInt(lValue.c_str()));
		}

		exportFbx(pFile, pScene, pIsAscii);

	}


	void globalPropEditor(std::string pFile, std::string lPropName, std::string lValue, bool pIsAscii)
	{
		FbxScene* pScene = createScene(pFile);
		if (pScene == nullptr)
		{
			return;
		}
		FbxGlobalSettings* lGlobalProps = FbxGlobalSettings::Create(FbxSdkMngr, "globalProps");
		FbxProperty lProperty = lGlobalProps->FindPropertyHierarchical(lPropName.c_str());
		if (!lProperty.IsValid())
		{
			std::cout << "Unable to locate the property";
			return;
		}
		FbxDataType lDataType = propDataType(lProperty);
		if (lDataType.Is(FbxStringDT))
		{
			pScene->GetGlobalSettings().FindPropertyHierarchical(lPropName.c_str()).Set<FbxString>(lValue.c_str());
		}
		else if (lDataType.Is(FbxDateTimeDT))
		{
			FbxDateTime lDateTime;
			if (!lDateTime.fromString(lValue.c_str()))
			{
				std::cout << "Error! invalid time input \n use -h or --help for options";
				return;
			}
			pScene->GetGlobalSettings().FindPropertyHierarchical(lPropName.c_str()).Set(lDateTime);
		}

		else if (lDataType.Is(FbxIntDT))
		{
			pScene->GetGlobalSettings().FindPropertyHierarchical(lPropName.c_str()).Set(FbxInt(lValue.c_str()));
		}
		else if (lDataType.Is(FbxDoubleDT))
		{
			pScene->GetGlobalSettings().FindPropertyHierarchical(lPropName.c_str()).Set(std::stod(lValue.c_str()));
		}
		else if (lDataType.Is(FbxTimeDT))
		{
			FbxTime lTime;
			lTime.SetSecondDouble(std::stoi(lValue.c_str()));
			pScene->GetGlobalSettings().FindPropertyHierarchical(lPropName.c_str()).Set(lTime);
		}
		else if (lDataType.Is(FbxEnumDT))
		{
			
			pScene->GetGlobalSettings().FindPropertyHierarchical(lPropName.c_str()).Set(std::stoi(lValue.c_str()));
		}
		else if (lDataType.Is(FbxColor3DT))
		{
			std::vector<double> mVector = splitColor(lValue);
			if (mVector.size() != 3)
			{
				return;
			}
			pScene->GetGlobalSettings().FindPropertyHierarchical(lPropName.c_str()).Set(FbxColor(mVector[0], mVector[1],mVector[2]));
		}

		exportFbx(pFile, pScene, pIsAscii);

	}


	void exportFbx(std::string lFile, FbxScene* lScene, bool lIsAscii)
	{
		lScene->GetDocumentInfo()->mComment = "This Fbx file has been modified using FbxPropEditor";
		FbxExporter* lExporter = FbxExporter::Create(FbxSdkMngr, "FBX Exporter");
		int lCnvrtId;
		if (lIsAscii)
		{
			lCnvrtId = FbxSdkMngr->GetIOPluginRegistry()->FindWriterIDByDescription("FBX ascii (*.fbx)");
		}
		else
		{
			lCnvrtId = FbxSdkMngr->GetIOPluginRegistry()->FindWriterIDByDescription("FBX binary (*.fbx)");
		}
		if (!lExporter->Initialize(lFile.c_str(), lCnvrtId, FbxSdkMngr->GetIOSettings()))
		{
			std::cout << "Error! failed to initialize exporter \n use -h or --help for options" << std::endl;
			lExporter->Destroy();
			return;
		}
		if (!lExporter->Export(lScene))
		{
			std::cout << "Error! failed to export file \n use -h or --help for options" << std::endl;
			lExporter->Destroy();
			return;
		}
		lExporter->Destroy();
		std::cout << "Succes" << std::endl;
		return;
	}

	FbxDataType propDataType(FbxProperty lProperty)
	{
		return lProperty.GetPropertyDataType();
	}

	std::vector<double> splitColor(std::string lInput)
	{
		std::vector<double> mVector;
		std::stringstream ss(lInput);
		std::string item;

		while (getline(ss, item, ',')) {
			mVector.push_back(std::stod(item));
		}

		return mVector;
	}

	void simpleExporter(std::string pFile , bool pIsAscii)
	{
		FbxScene* pScene = createScene(pFile);
		exportFbx(pFile, pScene, pIsAscii);
	}


	
};




