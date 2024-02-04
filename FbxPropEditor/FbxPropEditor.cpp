// FbxPropEditor.cpp : This file contains the 'main' function. 
//
#include <iostream>
#include "cmdParser.h"
#include "FbxUtils.h"


void printHelp()
{
    std::cout << "______________________________________________________________" << std::endl;
    std::cout << "FbxPropEditor \n Developed by Prudhvi Tummala \n MIT License (2024)" << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl;
    std::cout << "-h , --help : to view availble parameters" << std::endl;
    std::cout << "-f , --file : to input file location eg. (.../FbxPropEditor.exe -f .../file.fbx)" << std::endl;
    std::cout << "-d , --docinfo : to modify properties related to DocumentInfo of a fbx file  eg. (.../FbxPropEditor.exe -f .../file.fbx -d \"LastSaved|ApplicationName\" )" << std::endl;
    std::cout << "-g , --globalprop : to modify properties related to GlobalSettings of a fbx file (simillar to DocumentInfo)" << std::endl;
    std::cout << "-v , --value : new value of the property eg. (.../FbxPropEditor.exe -f .../file.fbx -d \"LastSaved|ApplicationName\" -v FbxPropEditor )" << std::endl;
    std::cout << "-l , --list : to view availble properties in fbx file eg. (.../FbxPropEditor.exe -f .../file.fbx -l)" << std::endl;
    std::cout << "-a , --ascii : export file as ascii if not mentioned file will be exported as binary eg. (.../FbxPropEditor.exe -f .../file.fbx -a)" << std::endl;
    return;
}


int main(int argc, char* argv[])
{
    cli::Parser cmdParser(argc, argv);
    cmdParser.set_optional<std::string>("f", "file", "");
    cmdParser.set_optional<std::string>("d", "docinfo", "");
    cmdParser.set_optional<std::string>("g", "globalprop", "");
    cmdParser.set_optional<std::string>("v", "value", "");
    cmdParser.set_optional<bool>("l", "list", false, "");
    cmdParser.set_optional<bool>("a", "ascii", false, "");
    cmdParser.disable_help();
    cmdParser.set_optional<bool>("h", "help", false, "");

    
    

    if (cmdParser.run())
    {
        bool lHelp = cmdParser.get<bool>("h");

        if (lHelp)
        {
            printHelp();
            return 0;
        }

        auto pFile = cmdParser.get<std::string>("f");
        auto pDocinfo = cmdParser.get<std::string>("d");
        auto pGlobalProp = cmdParser.get<std::string>("g");
        auto pValue = cmdParser.get<std::string>("v");
        bool pIsList = cmdParser.get<bool>("l");
        bool pIsAscii = cmdParser.get<bool>("a");
        FbxUtils FBXutils;
        if (!FBXutils.basicCheck(pFile, pDocinfo, pGlobalProp, pValue, pIsList, pIsAscii))
        {
            FBXutils.findFunction(pFile, pDocinfo, pGlobalProp, pValue, pIsList, pIsAscii);
        }

    }
    else
    {
        std::cout << "Error invalid input";
        printHelp();
    }
    return 0;
}


