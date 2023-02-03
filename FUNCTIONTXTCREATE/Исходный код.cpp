// dllmain.cpp : Defines the entry point for the DLL application.#include "stdafx.h"

#include <Windows.h>
#include <string>
#include <Strsafe.h>
#include <direct.h>



bool bDataCompare(const unsigned char* pData, const unsigned char* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
	{
		if (*szMask == 'x' && *pData != *bMask)
		{
			return false;
		}
	}
	return (*szMask) == NULL;
}
//---------------------------------------------------------------------------
DWORD dwFindPattern(DWORD dwAddress, DWORD dwLen, unsigned char* bMask, char* szMask)
{
	for (DWORD i = 0; i < dwLen; i++)
	{
		if (bDataCompare((unsigned char*)(dwAddress + i), bMask, szMask))
		{
			return (DWORD)(dwAddress + i);
		}
	}


	return 0;
}
//---------------------------------------------------------------------------


BOOL APIENTRY DllMain(HMODULE hModule,
					  DWORD  ul_reason_for_call,
					  LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		FILE* pFile;
		char path[MAX_PATH];
		sprintf_s(path, "%s\\Functions.txt", _getcwd(NULL, MAX_PATH));
		DeleteFileA(path);
		fopen_s(&pFile, path, "a");


		int factor;
		int interval = 5;


		DWORD g_dwGameBase = (DWORD)GetModuleHandle("game.dll");


		DWORD list = 0x2E3D90 + g_dwGameBase;

		
		factor = 0;
		while (1)
		{
			unsigned char * SIGNTEST = (unsigned char*)(list + factor);
			if (*SIGNTEST != 0x68) // if params is different from PUSH, then the list is finished
			{
				break;
			}
			//DWORD ignore    = *(DWORD*)(list + (0*interval) + factor);
			SIGNTEST += 1;
			DWORD params = *(DWORD*)(SIGNTEST);
			SIGNTEST += 4;
			SIGNTEST += 1;
			DWORD name = *(DWORD*)(SIGNTEST);
			SIGNTEST += 4;
			SIGNTEST += 1;
			DWORD address = *(DWORD*)(SIGNTEST) - g_dwGameBase;
			
			fprintf_s(pFile, "\"%s\" located at 0x%X with parameters \"%s\"\n", &(*(char**)name), address, &(*(char**)params));

			factor = factor + 0x14; // go to next block
		}
		list = 0x3d4025 + g_dwGameBase;
		factor = 0;
		while (1)
		{
			unsigned char* SIGNTEST = (unsigned char*)(list + factor);
			if (*SIGNTEST != 0x68) // if params is different from PUSH, then the list is finished
			{
				break;
			}
			//DWORD ignore    = *(DWORD*)(list + (0*interval) + factor);
			SIGNTEST += 1;
			DWORD params = *(DWORD*)(SIGNTEST);
			SIGNTEST += 4;
			SIGNTEST += 1;
			DWORD name = *(DWORD*)(SIGNTEST);
			SIGNTEST += 4;
			SIGNTEST += 1;
			DWORD address = *(DWORD*)(SIGNTEST)-g_dwGameBase;

			fprintf_s(pFile, "\"%s\" located at 0x%X with parameters \"%s\"\n", &(*(char**)name), address, &(*(char**)params));

			factor = factor + 0x14; // go to next block
		}
		fclose(pFile);
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return FALSE;
}