# FbxPropEditor
This Project can be used modify DocumentInfo  and GlobalSettings of Fbx File (eg. Original|ApplicationName, TimeMode, CustomFrameRate etc.)
This can also be used to export Fbx as ascii or binary (by default fbx will be exported as binary)

# Build
You need to install FBX SDK installed in your PC which you can download from Autodesk website (this project is developed with "FBX SDK 2020.3.4")
in FbxPropEditorProps.props file you need to change FBX_SDK_DIR to your FBX SDK installation directory and make changes to AdditionalLibraryDirectories directory in props file if required eg:((FBX_SDK_DIR)lib\vs2022\x64\debug\)
Now you can open .sln file in visual studio and build

# How to use

-h , --help : for help eg. (.../FbxPropEditor.exe -h)
-f , --file : to input file location eg. (.../FbxPropEditor.exe -f .../file.fbx)
-d , --docinfo : to modify properties related to DocumentInfo of a fbx file  eg. (.../FbxPropEditor.exe -f .../file.fbx -d "LastSaved|ApplicationName" )
-g , --globalprop : to modify properties related to GlobalSettings of a fbx file (simillar to DocumentInfo)
-v , --value : new value of the property eg. (.../FbxPropEditor.exe -f .../file.fbx -d "LastSaved|ApplicationName" -v FbxPropEditor )
-l , --list : to view availble properties in fbx file eg. (.../FbxPropEditor.exe -f .../file.fbx -l)
-a , --ascii : export file as ascii if not mentioned file will be exported as binary eg. (.../FbxPropEditor.exe -f .../file.fbx -a)

# Notes
This project uses CmdParser ( https://github.com/FlorianRappl/CmdParser )
I have used Fbx Format Converter by Bobby Anguelov (https://github.com/BobbyAnguelov/FbxFormatConverter/) as refernce project for handling FBX SDK
