// dllmain.cpp : Defines the entry point for the DLL application.#include "stdafx.h"

#include <Windows.h>
#include <string>
#include <Strsafe.h>
#include <direct.h>



bool bDataCompare( const BYTE* pData, const BYTE* bMask, const char* szMask )
{
	for ( ; *szMask; ++szMask, ++pData, ++bMask )
	{
		if ( *szMask == 'x' && *pData != *bMask )
		{
			return false;
		}
	}
	return ( *szMask ) == NULL;
}
//---------------------------------------------------------------------------
DWORD dwFindPattern( DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * szMask )
{
	for ( DWORD i = 0; i < dwLen; i++ )
	{
		if ( bDataCompare( ( BYTE* )( dwAddress + i ), bMask, szMask ) )
		{
			return ( DWORD )( dwAddress + i );
		}
	}


	return 0;
}
//---------------------------------------------------------------------------


BOOL APIENTRY DllMain( HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch ( ul_reason_for_call )
	{
	case DLL_PROCESS_ATTACH:
	{
		FILE *pFile;
		char path[ MAX_PATH ];
		sprintf_s( path, "%s\\Functions.txt", _getcwd( NULL, MAX_PATH ) );
		DeleteFileA( path );
		fopen_s(&pFile, path, "a" );


		int factor;
		int interval = 5;


		DWORD g_dwGameBase = ( DWORD )GetModuleHandle( "game.dll" );




		DWORD list1 = 0x1E9A51 + g_dwGameBase;
		DWORD list2 = 0x892DBC + g_dwGameBase;



		DWORD searchBase[ 2 ] = { list1, list2 };
		for ( int i = 0; i < 2; i++ )
		{
			factor = 0;
			while ( 1 )
			{
				BYTE SIGNTEST = *( BYTE* )( searchBase[ i ] - 1 + ( 1 * interval ) + factor );
				if ( SIGNTEST != 0x68 ) // if params is different from PUSH, then the list is finished
				{
					break;
				}
			
				//DWORD ignore    = *(DWORD*)(searchBase[i] + (0*interval) + factor);
				DWORD params = *( DWORD* )( searchBase[ i ] + ( 1 * interval ) + factor );
				DWORD name = *( DWORD* )( searchBase[ i ] + ( 2 * interval ) + factor );
				DWORD address = *( DWORD* )( searchBase[ i ] + ( 3 * interval ) + factor ) - g_dwGameBase;

				fprintf_s( pFile, "\"%s\" located at 0x%X with parameters \"%s\"\n", &( *( char** )name ), address, &( *( char** )params ) );
	
				factor = factor + 0x14; // go to next block
				
			}
		}
		fclose( pFile );
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return FALSE;
}