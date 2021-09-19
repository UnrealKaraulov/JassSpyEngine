#define _WIN32_WINNT _WIN32_WINNT_WINXP // _WIN32_WINNT_WINXP
#define WINVER _WIN32_WINNT_WINXP // _WIN32_WINNT_WINXP
#define NTDDI_VERSION NTDDI_WINXP
#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <share.h>
#include <stdlib.h>
#include <io.h>

#include "IniReader.h"
#include "IniWriter.h"

using namespace std;
#include <MinHook.h>
#pragma comment(lib, "libMinHook.x86.lib")
#define jassgetchar(JSTR)  *(char **)((*(DWORD*)((DWORD)JSTR+8))+0x1C)
struct JassStringData; 
struct CJassString;

#define MYDWORD CJassString *