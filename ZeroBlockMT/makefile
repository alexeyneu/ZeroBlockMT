CC=cl
CFLAGSMT=-c /D_WIN64  /D"_ATL_DLL" /D"_AFXDLL" /MD /nologo /W3 /WX- /O2 /D_AMD64_ /Oi /Ot /Oy- /DWIN32 /D_WINDOWS /DNDEBUG /D_UNICODE /DUNICODE /Gm- /GS- /Gy /arch:SSE2 /fp:precise /Zc:wchar_t /Zc:forScope /Fax64\Release\ /Fox64\Release\ /Fdx64\Release\vc100.pdb /Gd /errorReport:none /Iinclude
LINKER=link
GUIFLAGS=-SUBSYSTEM:windows /OUT:x64\Release\ZeroBlockMT.exe /NOLOGO  /PDB:"x64\Release\ZeroBlockMT.pdb" /SUBSYSTEM:WINDOWS /OPT:REF /OPT:NOICF /TLBID:1 /DYNAMICBASE /NXCOMPAT /MACHINE:X64 /ERRORREPORT:NONE /ENTRY:wWinMainCRTStartup
DLLFLAGS=-SUBSYSTEM:windows -DLL
GUILIBS=
RC=rc
RCVARS=/DWIN32 /D_WIN64  /DNDEBUG /D_UNICODE /DUNICODE /D_AFXDLL   /l0x0409 /Ix64\Release\ /nologo /fox64\Release\ZeroBlockMT.res
MT=mt
MTSTUFF=/nologo /verbose  -manifest x64\Release\ZeroBlockMT.exe.manifest

docks : trail x64\Release\ZeroBlockMT.exe
	$(MT) $(MTSTUFF) -outputresource:x64\Release\ZeroBlockMT.exe

x64\Release\ZeroBlockMT.exe : x64\Release\ZeroBlockMT.obj x64\Release\MainFrm.obj x64\Release\mount.obj x64\Release\ZeroBlockMT.res
     $(LINKER) $(GUIFLAGS)   x64\Release\MainFrm.obj x64\Release\ZeroBlockMT.obj x64\Release\mount.obj  x64\Release\ZeroBlockMT.res $(GUILIBS) 
	 
trail:
	-@ if NOT EXIST "x64" mkdir "x64"
	-@ if NOT EXIST "x64\Release" mkdir "x64\Release"

x64\Release\ZeroBlockMT.obj : ZeroBlockMT.cpp ZeroBlockMT.h StdAfx.h resource.h MainFrm.h
	 $(CC) $(CFLAGSMT) ZeroBlockMT.cpp

x64\Release\mount.obj : mount.cpp ZeroBlockMT.h StdAfx.h resource.h MainFrm.h
	 $(CC) $(CFLAGSMT) mount.cpp

x64\Release\MainFrm.obj : MainFrm.cpp MainFrm.h StdAfx.h resource.h 
     $(CC) $(CFLAGSMT) MainFrm.cpp

x64\Release\ZeroBlockMT.res : ZeroBlockMT.rc resource.h res\ZeroBlockMT.rc2 
	$(RC) $(RCVARS) ZeroBlockMT.rc




