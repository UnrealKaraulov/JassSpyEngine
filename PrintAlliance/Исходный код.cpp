
#include <Windows.h>
#include <string>

using namespace std;

int GameDll = 0;
int game1addr = 0;

void TextPrint( const char *szText , float fDuration )
{

	UINT32 dwDuration = *( ( UINT32 * ) &fDuration );
	UINT32 GAME_GlobalClass = GameDll + 0xAB4F80;
	UINT32 GAME_PrintToScreen = GameDll + 0x2F8E40;
	__asm
	{
		PUSH	0xFFFFFFFF
			PUSH	dwDuration
			PUSH	szText
			PUSH	0x0
			PUSH	0x0
			MOV		ECX , [ GAME_GlobalClass ]
			MOV		ECX , [ ECX ]
			CALL	GAME_PrintToScreen
	}
}


int GetMaxUnitForMap( )
{
	int tmp = 0;
	int tmpaddr = *( int* ) ( GameDll + 0xAAE2FC );
	if ( tmpaddr )
	{
		tmp += *( int* ) ( tmpaddr + 0x428 );
		if ( tmp )
		{
			tmp += 0x100000;
			if ( tmp == 0x100000 )
				return 0x1FFFFF;
		}
	}
	return tmp;
}

#define IsKeyPressed(CODE) (GetAsyncKeyState(CODE) & 0x8000) > 0



__declspec( naked ) BOOL __cdecl IsUnitSelected( int whichUnit , int whichPlayer )
{
	_asm
	{
		mov eax , GameDll
			add eax , 0x3C7E00
			jmp eax
	}
}


__declspec( naked ) int __cdecl Player( int number )
{
	_asm
	{
		mov eax , GameDll
			add eax , 0x3BBB30
			jmp eax
	}
}

__declspec( naked ) void __cdecl KillUnit( int whichUnit )
{
	_asm
	{
		mov eax , GameDll
			add eax , 0x3C8040
			jmp eax
	}
}


__declspec( naked ) int __cdecl GetOwningPlayer( int whichUnit )
{
	_asm
	{
		mov eax , GameDll
			add eax , 0x3C8190
			jmp eax
	}
}

__declspec( naked ) int __cdecl GetPlayerId( int whichPlayer )
{
	_asm
	{
		mov eax , GameDll
			add eax , 0x3C9640
			jmp eax
	}
}


__declspec( naked ) bool __cdecl GetPlayerAlliance( int sourcePlayer , int otherPlayer , int whichAllianceSetting )
{
	_asm
	{
		mov eax , GameDll
			add eax , 0x3C9D70
			jmp eax
	}
}


int GetNormalPlayer( int notnormal )
{
	switch ( notnormal )
	{
		case 1:
			return 0;
		case 2:
			return 1;
		case 3:
			return 2;
		case 4:
			return 3;
		case 5:
			return 4;

		default:
			break;
	}

	return 0;
}

int GetSelectedPlayer( )
{
	return *( int* ) ( GameDll + 0xAB632C );
}

int GetSelectedUnit( )
{
	int retvalue = 0;
	for ( int i = 0x100000; i < GetMaxUnitForMap( ); i++ )
	{
		if ( IsUnitSelected( i , Player( GetSelectedPlayer( ) ) ) )
		{
			return i;
		}
	}
	return retvalue;
}

void KillSelectedUnit( )
{
	KillUnit( GetSelectedUnit( ) );
}

void SetTlsForMe( )
{
	UINT32 Data = *( UINT32 * ) ( GameDll + 0xACEB4C );
	UINT32 TlsIndex = *( UINT32 * ) ( GameDll + 0xAB7BF4 );
	if ( TlsIndex )
	{
		UINT32 v5 = **( UINT32 ** ) ( *( UINT32 * ) ( *( UINT32 * ) ( GameDll + 0xACEB5C ) + 4 * Data ) + 44 );
		if ( !v5 || !( *( LPVOID * ) ( v5 + 520 ) ) )
		{
			Sleep( 1000 );
			SetTlsForMe( );
			return;
		}
		TlsSetValue( TlsIndex , *( LPVOID * ) ( v5 + 520 ) );
	}
	else
	{
		Sleep( 1000 );
		SetTlsForMe( );
		return;
	}
}


HANDLE ttt;


BOOL IsGame( )
{
	return ( *( int* ) ( ( UINT32 ) GameDll + 0xACF678 ) > 0 || *( int* ) ( ( UINT32 ) GameDll + 0xAB62A4 ) > 0 );
}

void TechiesThread( )
{
	int PlayerID = 0;
	int AllianceType = 0;
	string data;
	Sleep( 3500 );

	GameDll = ( int ) GetModuleHandle( "Game.dll" );
	if ( !GameDll )
	{
		MessageBox( 0 , "Error no game.dll found" , "Error" , MB_OK );
		return;
	}
	SetTlsForMe( );
	game1addr = GameDll + 0xAAE470;

	bool FirstGameFound = false;

	while ( true )
	{
		if ( IsGame( ) )
		{
			if ( !FirstGameFound )
			{
				FirstGameFound = true;
				TextPrint( "Select unit and press F7 to print alliance type" , 5.0f );
				TextPrint( "and unit owner player." , 5.0f );
				TextPrint( "Current Alliance Type: 0 [Press CTRL+1/2 to + / - alliance type]" , 5.0f );
				TextPrint( "Current Player: 0 [Press CTRL+3/4 to + / - player id]" , 5.0f );
			}

			if ( IsKeyPressed( VK_NUMPAD1 ) || IsKeyPressed( '1' ) )
			{
				if ( IsKeyPressed( VK_MENU ) || IsKeyPressed( VK_LMENU ) )
				{
					while ( IsKeyPressed( VK_NUMPAD1 ) || IsKeyPressed( '1' ) )
					{
						Sleep( 30 );
					}
					AllianceType--;
					data = string( "Current Alliance Type: " + to_string( AllianceType ) + " [Press CTRL+1/2 to + / - alliance type]" );
					TextPrint( data.c_str( ) , 5.0f );
				}
			}


			if ( IsKeyPressed( VK_NUMPAD2 ) || IsKeyPressed( '2' ) )
			{
				if ( IsKeyPressed( VK_MENU ) || IsKeyPressed( VK_LMENU ) )
				{
					while ( IsKeyPressed( VK_NUMPAD2 ) || IsKeyPressed( '2' ) )
					{
						Sleep( 30 );
					}
					AllianceType++;
					data = string( "Current Alliance Type: " + to_string( AllianceType ) + " [Press CTRL+1/2 to + / - alliance type]" );
					TextPrint( data.c_str( ) , 5.0f );
				}
			}



			if ( IsKeyPressed( VK_NUMPAD3 ) || IsKeyPressed( '3' ) )
			{
				if ( IsKeyPressed( VK_MENU ) || IsKeyPressed( VK_LMENU ) )
				{
					while ( IsKeyPressed( VK_NUMPAD3 ) || IsKeyPressed( '3' ) )
					{
						Sleep( 30 );
					}
					PlayerID--;
					data = string(  "Current Player: "+to_string(PlayerID)+" [Press CTRL+3/4 to + / - player id]" );
					TextPrint( data.c_str( ) , 5.0f );
					
				}
			}


			if ( IsKeyPressed( VK_NUMPAD4 ) || IsKeyPressed( '4' ) )
			{
				if ( IsKeyPressed( VK_MENU ) || IsKeyPressed( VK_LMENU ) )
				{
					while ( IsKeyPressed( VK_NUMPAD4 ) || IsKeyPressed( '4' ) )
					{
						Sleep( 30 );
					}
					PlayerID++;
					data = string( "Current Player: " + to_string( PlayerID ) + " [Press CTRL+3/4 to + / - player id]" );
					TextPrint( data.c_str( ) , 5.0f );
				}
			}

			if ( IsKeyPressed( VK_F7 ) )
			{


				while ( IsKeyPressed( VK_F7 ) )
				{
					Sleep( 40 );
				}
				data = string( "Local player: " + to_string( GetSelectedPlayer( ) ) );
				TextPrint( data.c_str( ) , 5.0f );
				data = string( "Player owner: " + to_string( GetPlayerId( GetOwningPlayer( GetSelectedUnit( ) ) ) ) );
				TextPrint( data.c_str( ) , 5.0f );
				data = string( "Alliance type " + to_string( AllianceType ) + " for Player " + to_string( PlayerID ) + " = " + (GetPlayerAlliance(GetOwningPlayer(GetSelectedUnit()),Player(PlayerID),AllianceType) ? "TRUE" : "FALSE") );
				TextPrint( data.c_str( ) , 5.0f );
				//KillSelectedUnit( );
				/*	int selectedunit = GetSelectedUnit( );
					if ( selectedunit > 0 )
					{
					MessageBox( 0 , "KILLED" , "KILLED" , 0 );
					KillUnit( selectedunit );
					MessageBox( 0 , "KILLED" , "KILLED" , 0 );
					}*/
			}
		}
		Sleep( 100 );
	}
}

DWORD __stdcall temptechiesthread( LPVOID )
{
	TechiesThread( );
	return 0;
}
BOOL WINAPI DllMain( HINSTANCE hDLL , UINT reason , LPVOID reserved )
{
	if ( reason == DLL_PROCESS_ATTACH )
	{
		ttt = CreateThread( 0 , 0 , temptechiesthread , 0 , 0 , 0 );
	}
	else if ( reason == DLL_PROCESS_DETACH )
	{
		TerminateThread( ttt , 0 );
	}
	return TRUE;
}
