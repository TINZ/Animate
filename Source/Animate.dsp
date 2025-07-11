# Microsoft Developer Studio Project File - Name="Animate" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Animate - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Animate.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Animate.mak" CFG="Animate - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Animate - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Animate - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Animate - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Animate - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Animate - Win32 Release"
# Name "Animate - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Administrator.cpp
# End Source File
# Begin Source File

SOURCE=.\Agent.cpp
# End Source File
# Begin Source File

SOURCE=.\Animate.cpp
# End Source File
# Begin Source File

SOURCE=.\Animate.rc
# End Source File
# Begin Source File

SOURCE=.\AnimateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Arbitrator.cpp
# End Source File
# Begin Source File

SOURCE=.\CDib.cpp
# End Source File
# Begin Source File

SOURCE=.\ChainMiner.cpp
# End Source File
# Begin Source File

SOURCE=.\Crowd.cpp
# End Source File
# Begin Source File

SOURCE=.\Environment.cpp
# End Source File
# Begin Source File

SOURCE=.\Grid.cpp
# End Source File
# Begin Source File

SOURCE=.\Intent.cpp
# End Source File
# Begin Source File

SOURCE=.\MapEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\Miner.cpp
# End Source File
# Begin Source File

SOURCE=.\Predator.cpp
# End Source File
# Begin Source File

SOURCE=.\Prey.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Administrator.h
# End Source File
# Begin Source File

SOURCE=.\Agent.h
# End Source File
# Begin Source File

SOURCE=.\Animate.h
# End Source File
# Begin Source File

SOURCE=.\AnimateDlg.h
# End Source File
# Begin Source File

SOURCE=.\Arbitrator.h
# End Source File
# Begin Source File

SOURCE=.\CDib.h
# End Source File
# Begin Source File

SOURCE=.\ChainMiner.h
# End Source File
# Begin Source File

SOURCE=.\Crowd.h
# End Source File
# Begin Source File

SOURCE=.\DataStructures.h
# End Source File
# Begin Source File

SOURCE=.\Environment.h
# End Source File
# Begin Source File

SOURCE=.\Grid.h
# End Source File
# Begin Source File

SOURCE=.\Intent.h
# End Source File
# Begin Source File

SOURCE=.\MapEditor.h
# End Source File
# Begin Source File

SOURCE=.\Miner.h
# End Source File
# Begin Source File

SOURCE=.\Predator.h
# End Source File
# Begin Source File

SOURCE=.\Prey.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Animate.ico
# End Source File
# Begin Source File

SOURCE=.\res\Animate.rc2
# End Source File
# Begin Source File

SOURCE=.\res\editor_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\editor_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\editor_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\editor_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\jump_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\jump_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\jump_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\jump_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\legend.bmp
# End Source File
# Begin Source File

SOURCE=.\res\level_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\level_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\level_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\level_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\load_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\load_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\load_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\load_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\objects.bmp
# End Source File
# Begin Source File

SOURCE=.\res\path_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\path_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\path_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\path_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\paul.bmp
# End Source File
# Begin Source File

SOURCE=.\res\play_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\play_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\play_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\play_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rand_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rand_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rand_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rand_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reset_begin_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reset_begin_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reset_begin_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reset_begin_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reset_end_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reset_end_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reset_end_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reset_end_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rubout_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rubout_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rubout_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rubout_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\run_abort_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\run_abort_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\run_abort_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\run_abort_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\run_anim_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\run_anim_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\run_anim_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\run_anim_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\run_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\run_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\run_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\run_pause_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\run_pause_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\run_pause_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\run_pause_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\run_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\save_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\save_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\save_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\save_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\step_b_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\step_b_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\step_b_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\step_b_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\step_f_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\step_f_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\step_f_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\step_f_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stop_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stop_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stop_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stop_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\valid_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\valid_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\valid_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\valid_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wipe_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wipe_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wipe_focus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wipe_up.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
