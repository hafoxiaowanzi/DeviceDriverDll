# Microsoft Developer Studio Project File - Name="UDLServer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=UDLServer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UDLServer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UDLServer.mak" CFG="UDLServer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UDLServer - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UDLServer - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UDLServer - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UDLServer - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UDLServer - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UDLServer - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UDLServer - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../bin/UDL.DLM.dll" /pdbtype:sept
# Begin Custom Build - Performing registration
OutDir=.\Debug
TargetPath=\Project\testgroup\UDLDriver\NetVersion\code\UDL_Client - switch\bin\UDL.DLM.dll
InputPath=\Project\testgroup\UDLDriver\NetVersion\code\UDL_Client - switch\bin\UDL.DLM.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Execute mtxrereg.exe before using MTS components in MTS 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "UDLServer - Win32 Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 mtx.lib mtxguid.lib delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept /delayload:mtxex.dll
# Begin Custom Build - Performing registration
OutDir=.\DebugU
TargetPath=.\DebugU\UDLServer.dll
InputPath=.\DebugU\UDLServer.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Execute mtxrereg.exe before using MTS components in MTS 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "UDLServer - Win32 Release MinSize"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_WINDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"../bin/UDL.DLM.dll "
# Begin Custom Build - Performing registration
OutDir=.\../lib
TargetPath=\Project\testgroup\UDLDriver\NetVersion\code\UDL_Client - switch\bin\UDL.DLM.dll
InputPath=\Project\testgroup\UDLDriver\NetVersion\code\UDL_Client - switch\bin\UDL.DLM.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Execute mtxrereg.exe before using MTS components in MTS 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "UDLServer - Win32 Release MinDependency"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 mtx.lib mtxguid.lib delayimp.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../bin/UDL.DLM.dll " /delayload:mtxex.dll
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinDependency
TargetPath=\Project\testgroup\UDLDriver\NetVersion\code\UDL_Client - switch\bin\UDL.DLM.dll
InputPath=\Project\testgroup\UDLDriver\NetVersion\code\UDL_Client - switch\bin\UDL.DLM.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Execute mtxrereg.exe before using MTS components in MTS 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "UDLServer - Win32 Unicode Release MinSize"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinSize"
# PROP BASE Intermediate_Dir "ReleaseUMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinSize"
# PROP Intermediate_Dir "ReleaseUMinSize"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 mtx.lib mtxguid.lib delayimp.lib /nologo /subsystem:windows /dll /machine:I386 /delayload:mtxex.dll
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\UDLServer.dll
InputPath=.\ReleaseUMinSize\UDLServer.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Execute mtxrereg.exe before using MTS components in MTS 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "UDLServer - Win32 Unicode Release MinDependency"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinDependency"
# PROP BASE Intermediate_Dir "ReleaseUMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinDependency"
# PROP Intermediate_Dir "ReleaseUMinDependency"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 mtx.lib mtxguid.lib delayimp.lib /nologo /subsystem:windows /dll /machine:I386 /delayload:mtxex.dll
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\UDLServer.dll
InputPath=.\ReleaseUMinDependency\UDLServer.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Execute mtxrereg.exe before using MTS components in MTS 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "UDLServer - Win32 Debug"
# Name "UDLServer - Win32 Unicode Debug"
# Name "UDLServer - Win32 Release MinSize"
# Name "UDLServer - Win32 Release MinDependency"
# Name "UDLServer - Win32 Unicode Release MinSize"
# Name "UDLServer - Win32 Unicode Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AlgorithmFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\ChamberInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\DeviceManger.cpp
# End Source File
# Begin Source File

SOURCE=.\dlldatax.c
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\EngineMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\IComDevInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\IOSAInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\IPMInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\IPolInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\ISwitchBoxInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\ITLSInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\IVOAInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\Markup.cpp
# End Source File
# Begin Source File

SOURCE=.\ScanInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UDLServer.cpp
# End Source File
# Begin Source File

SOURCE=.\UDLServer.def
# End Source File
# Begin Source File

SOURCE=.\UDLServer.idl

!IF  "$(CFG)" == "UDLServer - Win32 Debug"

# ADD MTL /tlb ".\UDLServer.tlb" /h "UDLServer.h" /iid "UDLServer_i.c" /Oicf

!ELSEIF  "$(CFG)" == "UDLServer - Win32 Unicode Debug"

# ADD MTL /tlb ".\UDLServer.tlb" /h "UDLServer.h" /iid "UDLServer_i.c" /Oicf

!ELSEIF  "$(CFG)" == "UDLServer - Win32 Release MinSize"

# ADD MTL /tlb ".\UDLServer.tlb" /h "UDLServer.h" /iid "UDLServer_i.c" /Oicf

!ELSEIF  "$(CFG)" == "UDLServer - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "UDLServer - Win32 Unicode Release MinSize"

# ADD MTL /tlb ".\UDLServer.tlb" /h "UDLServer.h" /iid "UDLServer_i.c" /Oicf

!ELSEIF  "$(CFG)" == "UDLServer - Win32 Unicode Release MinDependency"

# ADD MTL /tlb ".\UDLServer.tlb" /h "UDLServer.h" /iid "UDLServer_i.c" /Oicf

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\UDLServer.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\AlgorithmFunction.h
# End Source File
# Begin Source File

SOURCE=.\ChamberInterface.h
# End Source File
# Begin Source File

SOURCE=.\DeviceManger.h
# End Source File
# Begin Source File

SOURCE=.\dlldatax.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\EngineMgr.h
# End Source File
# Begin Source File

SOURCE=..\include\hearder.h
# End Source File
# Begin Source File

SOURCE=.\IComDevInterface.h
# End Source File
# Begin Source File

SOURCE=.\IOSAInterface.h
# End Source File
# Begin Source File

SOURCE=.\IPMInterface.h
# End Source File
# Begin Source File

SOURCE=.\IPolInterface.h
# End Source File
# Begin Source File

SOURCE=.\ISwitchBoxInterface.h
# End Source File
# Begin Source File

SOURCE=.\ITLSInterface.h
# End Source File
# Begin Source File

SOURCE=.\IVOAInterface.h
# End Source File
# Begin Source File

SOURCE=.\Markup.h
# End Source File
# Begin Source File

SOURCE=..\PMUDL\PMControlDll.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScanInterface.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UDLServerCP.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\ChamberInterface.rgs
# End Source File
# Begin Source File

SOURCE=.\CIPolInterface.rgs
# End Source File
# Begin Source File

SOURCE=.\EngineMgr.rgs
# End Source File
# Begin Source File

SOURCE=.\EnginePtr.rgs
# End Source File
# Begin Source File

SOURCE=.\IComDevInterface.rgs
# End Source File
# Begin Source File

SOURCE=.\IOSAInterface.rgs
# End Source File
# Begin Source File

SOURCE=.\IPMInterface.rgs
# End Source File
# Begin Source File

SOURCE=.\IPolInterface.rgs
# End Source File
# Begin Source File

SOURCE=.\ISwitchBoxInterface.rgs
# End Source File
# Begin Source File

SOURCE=.\ITLSInterface.rgs
# End Source File
# Begin Source File

SOURCE=.\IVOAInterface.rgs
# End Source File
# Begin Source File

SOURCE=.\ScanInterface.rgs
# End Source File
# End Group
# End Target
# End Project
