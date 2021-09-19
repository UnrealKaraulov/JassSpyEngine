#include "Includes.h"
#include "JassFuncs.h"
#include "InitSpy.h"
using namespace std;

static FILE * logfile;

const std::string currentDateTime( )
{
	time_t     now = time( 0 );
	struct tm  tstruct;
	char buf[ 55 ];
	localtime_s( &tstruct , &now );
	strftime( buf , 55 , "%X" , &tstruct );
	return buf;
}

DWORD dwGameBase = 0;


CHAR* DoTheMagic(DWORD JSID)
{
	if (dwGameBase == 0)
		dwGameBase =    (DWORD)GetModuleHandle("Game.dll");
    DWORD Convert =    dwGameBase + 0x459640;
    DWORD GetCurrentJassEnvironment =    dwGameBase + 0x44B2E0;
    CHAR* cRet;

    __asm
    {
        push JSID;
        mov ecx, 1;
        call GetCurrentJassEnvironment;
        mov ecx, eax;
        call Convert;
        mov ecx,dword ptr ds:[eax+0x08];
        mov eax,dword ptr ds:[ecx+0x1C];
        mov cRet, eax;
    }

    return cRet;
}

typedef int( __cdecl *GAME_AbilityId )( void * abilityIdString );
GAME_AbilityId GAME_AbilityIdorg = NULL;
GAME_AbilityId GAME_AbilityIdold = NULL;

int __cdecl GAME_AbilityIdmy( void * abilityIdString )
{
	fprintf_s( logfile , "%s" , "AbilityIdmy\n" );
	fflush( logfile );

	int retvalue = GAME_AbilityIdold( abilityIdString );
	fprintf_s( logfile , "%s:[-->GAME_AbilityId<--  abilityIdString: \"%s\"] RETURN-> %i\n" , currentDateTime( ).c_str( ) , jassgetchar( abilityIdString ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_AbilityId2String )( int abilityId );
GAME_AbilityId2String GAME_AbilityId2Stringorg = NULL;
GAME_AbilityId2String GAME_AbilityId2Stringold = NULL;

DWORD __cdecl GAME_AbilityId2Stringmy( int abilityId )
{
	fprintf_s( logfile , "%s" , "AbilityId2Stringmy\n" );
	fflush( logfile );

	DWORD retvalue = GAME_AbilityId2Stringold( abilityId );
	fprintf_s( logfile , "%s:[-->GAME_AbilityId2String<--  abilityId: %i] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , abilityId , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_Acos )( float *x );
GAME_Acos GAME_Acosorg = NULL;
GAME_Acos GAME_Acosold = NULL;

DWFP __cdecl GAME_Acosmy( float *x )
{
	fprintf_s( logfile , "%s\n" , "Acosmy" );
	fflush( logfile );

	DWFP retvalue = GAME_Acosold( x );
	fprintf_s( logfile , "%s:[-->GAME_Acos<--  x: %f] RETURN-> %f\n" , currentDateTime( ).c_str( ) , *( float * ) x , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_AddAssault )( int arg1 , int arg2 );
GAME_AddAssault GAME_AddAssaultorg = NULL;
GAME_AddAssault GAME_AddAssaultold = NULL;

BOOL __cdecl GAME_AddAssaultmy( int arg1 , int arg2 )
{
	fprintf_s( logfile , "%s\n" , "AddAssaultmy" );
	fflush( logfile );

	BOOL retvalue = GAME_AddAssaultold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_AddAssault<--  arg1: %i arg2: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , arg1 , arg2 , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_AddDefenders )( int arg1 , int arg2 );
GAME_AddDefenders GAME_AddDefendersorg = NULL;
GAME_AddDefenders GAME_AddDefendersold = NULL;

BOOL __cdecl GAME_AddDefendersmy( int arg1 , int arg2 )
{
	fprintf_s( logfile , "%s" , "AddDefendersmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_AddDefendersold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_AddDefenders<--  arg1: %i arg2: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , arg1 , arg2 , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_AddGuardPost )( int arg1 , float *arg2 , float *arg3 );
GAME_AddGuardPost GAME_AddGuardPostorg = NULL;
GAME_AddGuardPost GAME_AddGuardPostold = NULL;

void __cdecl GAME_AddGuardPostmy( int arg1 , float *arg2 , float *arg3 )
{
	fprintf_s( logfile , "%s" , "AddGuardPostmy\n" );
	fflush( logfile );

	GAME_AddGuardPostold( arg1 , arg2 , arg3 );
	fprintf_s( logfile , "%s:[-->GAME_AddGuardPost<--  arg1: %i arg2: %f arg3: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 , *( float * ) arg2 , *( float * ) arg3 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_AddHeroXP )( HUNIT whichHero , int xpToAdd , BOOL showEyeCandy );
GAME_AddHeroXP GAME_AddHeroXPorg = NULL;
GAME_AddHeroXP GAME_AddHeroXPold = NULL;

void __cdecl GAME_AddHeroXPmy( HUNIT whichHero , int xpToAdd , BOOL showEyeCandy )
{
	fprintf_s( logfile , "%s\n" , "AddHeroXPmy" );
	fflush( logfile );

	GAME_AddHeroXPold( whichHero , xpToAdd , showEyeCandy );
	fprintf_s( logfile , "%s:[-->GAME_AddHeroXP<--  whichHero: %X xpToAdd: %i showEyeCandy: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichHero , xpToAdd , showEyeCandy ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_AddIndicator )( HWIDGET whichWidget , int red , int green , int blue , int alpha );
GAME_AddIndicator GAME_AddIndicatororg = NULL;
GAME_AddIndicator GAME_AddIndicatorold = NULL;

void __cdecl GAME_AddIndicatormy( HWIDGET whichWidget , int red , int green , int blue , int alpha )
{
	fprintf_s( logfile , "%s" , "AddIndicatormy\n" );
	fflush( logfile );

	GAME_AddIndicatorold( whichWidget , red , green , blue , alpha );
	fprintf_s( logfile , "%s:[-->GAME_AddIndicator<--  whichWidget: %X red: %i green: %i blue: %i alpha: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichWidget , red , green , blue , alpha );
	fflush( logfile );

}


typedef void( __cdecl *GAME_AddItemToAllStock )( int itemId , int currentStock , int stockMax );
GAME_AddItemToAllStock GAME_AddItemToAllStockorg = NULL;
GAME_AddItemToAllStock GAME_AddItemToAllStockold = NULL;

void __cdecl GAME_AddItemToAllStockmy( int itemId , int currentStock , int stockMax )
{
	fprintf_s( logfile , "%s\n" , "AddItemToAllStockmy" );
	fflush( logfile );

	GAME_AddItemToAllStockold( itemId , currentStock , stockMax );
	fprintf_s( logfile , "%s:[-->GAME_AddItemToAllStock<--  itemId: %i currentStock: %i stockMax: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , itemId , currentStock , stockMax );
	fflush( logfile );

}


typedef void( __cdecl *GAME_AddItemToStock )( HUNIT whichUnit , int itemId , int currentStock , int stockMax );
GAME_AddItemToStock GAME_AddItemToStockorg = NULL;
GAME_AddItemToStock GAME_AddItemToStockold = NULL;

void __cdecl GAME_AddItemToStockmy( HUNIT whichUnit , int itemId , int currentStock , int stockMax )
{
	fprintf_s( logfile , "%s\n" , "AddItemToStockmy" );
	fflush( logfile );

	GAME_AddItemToStockold( whichUnit , itemId , currentStock , stockMax );
	fprintf_s( logfile , "%s:[-->GAME_AddItemToStock<--  whichUnit: %X itemId: %i currentStock: %i stockMax: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , itemId , currentStock , stockMax );
	fflush( logfile );

}


typedef HLIGHTNING( __cdecl *GAME_AddLightning )( void * codeName , BOOL checkVisibility , float *x1 , float *y1 , float *x2 , float *y2 );
GAME_AddLightning GAME_AddLightningorg = NULL;
GAME_AddLightning GAME_AddLightningold = NULL;

HLIGHTNING __cdecl GAME_AddLightningmy( void * codeName , BOOL checkVisibility , float *x1 , float *y1 , float *x2 , float *y2 )
{
	fprintf_s( logfile , "%s\n" , "AddLightningmy" );
	fflush( logfile );

	HLIGHTNING retvalue = GAME_AddLightningold( codeName , checkVisibility , x1 , y1 , x2 , y2 );
	fprintf_s( logfile , "%s:[-->GAME_AddLightning<--  codeName: \"%s\" checkVisibility: %s x1: %f y1: %f x2: %f y2: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , jassgetchar( codeName ) , checkVisibility ? "TRUE" : "FALSE" , *( float * ) x1 , *( float * ) y1 , *( float * ) x2 , *( float * ) y2 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HLIGHTNING( __cdecl *GAME_AddLightningEx )( void * codeName , BOOL checkVisibility , float *x1 , float *y1 , float *z1 , float *x2 , float *y2 , float *z2 );
GAME_AddLightningEx GAME_AddLightningExorg = NULL;
GAME_AddLightningEx GAME_AddLightningExold = NULL;

HLIGHTNING __cdecl GAME_AddLightningExmy( void * codeName , BOOL checkVisibility , float *x1 , float *y1 , float *z1 , float *x2 , float *y2 , float *z2 )
{
	fprintf_s( logfile , "%s" , "AddLightningExmy\n" );
	fflush( logfile );

	HLIGHTNING retvalue = GAME_AddLightningExold( codeName , checkVisibility , x1 , y1 , z1 , x2 , y2 , z2 );
	fprintf_s( logfile , "%s:[-->GAME_AddLightningEx<--  codeName: \"%s\" checkVisibility: %s x1: %f y1: %f z1: %f x2: %f y2: %f z2: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , jassgetchar( codeName ) , checkVisibility ? "TRUE" : "FALSE" , *( float * ) x1 , *( float * ) y1 , *( float * ) z1 , *( float * ) x2 , *( float * ) y2 , *( float * ) z2 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_AddPlayerTechResearched )( HPLAYER whichPlayer , int techid , int levels );
GAME_AddPlayerTechResearched GAME_AddPlayerTechResearchedorg = NULL;
GAME_AddPlayerTechResearched GAME_AddPlayerTechResearchedold = NULL;

void __cdecl GAME_AddPlayerTechResearchedmy( HPLAYER whichPlayer , int techid , int levels )
{
	fprintf_s( logfile , "%s" , "AddPlayerTechResearchedmy\n" );
	fflush( logfile );

	GAME_AddPlayerTechResearchedold( whichPlayer , techid , levels );
	fprintf_s( logfile , "%s:[-->GAME_AddPlayerTechResearched<--  whichPlayer: %X techid: %i levels: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , techid , levels );
	fflush( logfile );

}


typedef void( __cdecl *GAME_AddResourceAmount )( HUNIT whichUnit , int amount );
GAME_AddResourceAmount GAME_AddResourceAmountorg = NULL;
GAME_AddResourceAmount GAME_AddResourceAmountold = NULL;

void __cdecl GAME_AddResourceAmountmy( HUNIT whichUnit , int amount )
{
	fprintf_s( logfile , "%s\n" , "AddResourceAmountmy" );
	fflush( logfile );

	GAME_AddResourceAmountold( whichUnit , amount );
	fprintf_s( logfile , "%s:[-->GAME_AddResourceAmount<--  whichUnit: %X amount: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , amount );
	fflush( logfile );

}


typedef HEFFECT( __cdecl *GAME_AddSpecialEffect )( void * modelName , float *x , float *y );
GAME_AddSpecialEffect GAME_AddSpecialEffectorg = NULL;
GAME_AddSpecialEffect GAME_AddSpecialEffectold = NULL;

HEFFECT __cdecl GAME_AddSpecialEffectmy( void * modelName , float *x , float *y )
{
	fprintf_s( logfile , "%s\n" , "AddSpecialEffectmy" );
	fflush( logfile );

	HEFFECT retvalue = GAME_AddSpecialEffectold( modelName , x , y );
	fprintf_s( logfile , "%s:[-->GAME_AddSpecialEffect<--  modelName: \"%s\" x: %f y: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , jassgetchar( modelName ) , *( float * ) x , *( float * ) y , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEFFECT( __cdecl *GAME_AddSpecialEffectLoc )( void * modelName , HLOCATION where );
GAME_AddSpecialEffectLoc GAME_AddSpecialEffectLocorg = NULL;
GAME_AddSpecialEffectLoc GAME_AddSpecialEffectLocold = NULL;

HEFFECT __cdecl GAME_AddSpecialEffectLocmy( void * modelName , HLOCATION where )
{
	fprintf_s( logfile , "%s" , "AddSpecialEffectLocmy\n" );
	fflush( logfile );

	HEFFECT retvalue = GAME_AddSpecialEffectLocold( modelName , where );
	fprintf_s( logfile , "%s:[-->GAME_AddSpecialEffectLoc<--  modelName: \"%s\" where: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , jassgetchar( modelName ) , where , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEFFECT( __cdecl *GAME_AddSpecialEffectTarget )( void * modelName , HWIDGET targetWidget , void * attachPointName );
GAME_AddSpecialEffectTarget GAME_AddSpecialEffectTargetorg = NULL;
GAME_AddSpecialEffectTarget GAME_AddSpecialEffectTargetold = NULL;

HEFFECT __cdecl GAME_AddSpecialEffectTargetmy( void * modelName , HWIDGET targetWidget , void * attachPointName )
{
	fprintf_s( logfile , "%s" , "AddSpecialEffectTargetmy\n" );
	fflush( logfile );

	HEFFECT retvalue = GAME_AddSpecialEffectTargetold( modelName , targetWidget , attachPointName );
	fprintf_s( logfile , "%s:[-->GAME_AddSpecialEffectTarget<--  modelName: \"%s\" targetWidget: %X attachPointName: \"%s\"] RETURN-> %X\n" , currentDateTime( ).c_str( ) , jassgetchar( modelName ) , targetWidget , jassgetchar( attachPointName ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEFFECT( __cdecl *GAME_AddSpellEffect )( void * abilityString , HEFFECTTYPE t , float *x , float *y );
GAME_AddSpellEffect GAME_AddSpellEffectorg = NULL;
GAME_AddSpellEffect GAME_AddSpellEffectold = NULL;

HEFFECT __cdecl GAME_AddSpellEffectmy( void * abilityString , HEFFECTTYPE t , float *x , float *y )
{
	fprintf_s( logfile , "%s" , "AddSpellEffectmy\n" );
	fflush( logfile );

	HEFFECT retvalue = GAME_AddSpellEffectold( abilityString , t , x , y );
	fprintf_s( logfile , "%s:[-->GAME_AddSpellEffect<--  abilityString: \"%s\" t: %X x: %f y: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , jassgetchar( abilityString ) , t , *( float * ) x , *( float * ) y , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEFFECT( __cdecl *GAME_AddSpellEffectById )( int abilityId , HEFFECTTYPE t , float *x , float *y );
GAME_AddSpellEffectById GAME_AddSpellEffectByIdorg = NULL;
GAME_AddSpellEffectById GAME_AddSpellEffectByIdold = NULL;

HEFFECT __cdecl GAME_AddSpellEffectByIdmy( int abilityId , HEFFECTTYPE t , float *x , float *y )
{
	fprintf_s( logfile , "%s" , "AddSpellEffectByIdmy\n" );
	fflush( logfile );

	HEFFECT retvalue = GAME_AddSpellEffectByIdold( abilityId , t , x , y );
	fprintf_s( logfile , "%s:[-->GAME_AddSpellEffectById<--  abilityId: %i t: %X x: %f y: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , abilityId , t , *( float * ) x , *( float * ) y , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEFFECT( __cdecl *GAME_AddSpellEffectByIdLoc )( int abilityId , HEFFECTTYPE t , HLOCATION where );
GAME_AddSpellEffectByIdLoc GAME_AddSpellEffectByIdLocorg = NULL;
GAME_AddSpellEffectByIdLoc GAME_AddSpellEffectByIdLocold = NULL;

HEFFECT __cdecl GAME_AddSpellEffectByIdLocmy( int abilityId , HEFFECTTYPE t , HLOCATION where )
{
	fprintf_s( logfile , "%s\n" , "AddSpellEffectByIdLocmy" );
	fflush( logfile );

	HEFFECT retvalue = GAME_AddSpellEffectByIdLocold( abilityId , t , where );
	fprintf_s( logfile , "%s:[-->GAME_AddSpellEffectByIdLoc<--  abilityId: %i t: %X where: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , abilityId , t , where , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEFFECT( __cdecl *GAME_AddSpellEffectLoc )( void * abilityString , HEFFECTTYPE t , HLOCATION where );
GAME_AddSpellEffectLoc GAME_AddSpellEffectLocorg = NULL;
GAME_AddSpellEffectLoc GAME_AddSpellEffectLocold = NULL;

HEFFECT __cdecl GAME_AddSpellEffectLocmy( void * abilityString , HEFFECTTYPE t , HLOCATION where )
{
	fprintf_s( logfile , "%s\n" , "AddSpellEffectLocmy" );
	fflush( logfile );

	HEFFECT retvalue = GAME_AddSpellEffectLocold( abilityString , t , where );
	fprintf_s( logfile , "%s:[-->GAME_AddSpellEffectLoc<--  abilityString: \"%s\" t: %X where: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , jassgetchar( abilityString ) , t , where , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEFFECT( __cdecl *GAME_AddSpellEffectTarget )( void * modelName , HEFFECTTYPE t , HWIDGET targetWidget , void * attachPoint );
GAME_AddSpellEffectTarget GAME_AddSpellEffectTargetorg = NULL;
GAME_AddSpellEffectTarget GAME_AddSpellEffectTargetold = NULL;

HEFFECT __cdecl GAME_AddSpellEffectTargetmy( void * modelName , HEFFECTTYPE t , HWIDGET targetWidget , void * attachPoint )
{
	fprintf_s( logfile , "%s" , "AddSpellEffectTargetmy\n" );
	fflush( logfile );

	HEFFECT retvalue = GAME_AddSpellEffectTargetold( modelName , t , targetWidget , attachPoint );
	fprintf_s( logfile , "%s:[-->GAME_AddSpellEffectTarget<--  modelName: \"%s\" t: %X targetWidget: %X attachPoint: \"%s\"] RETURN-> %X\n" , currentDateTime( ).c_str( ) , jassgetchar( modelName ) , t , targetWidget , jassgetchar( attachPoint ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEFFECT( __cdecl *GAME_AddSpellEffectTargetById )( int abilityId , HEFFECTTYPE t , HWIDGET targetWidget , void * attachPoint );
GAME_AddSpellEffectTargetById GAME_AddSpellEffectTargetByIdorg = NULL;
GAME_AddSpellEffectTargetById GAME_AddSpellEffectTargetByIdold = NULL;

HEFFECT __cdecl GAME_AddSpellEffectTargetByIdmy( int abilityId , HEFFECTTYPE t , HWIDGET targetWidget , void * attachPoint )
{
	fprintf_s( logfile , "%s" , "AddSpellEffectTargetByIdmy\n" );
	fflush( logfile );

	HEFFECT retvalue = GAME_AddSpellEffectTargetByIdold( abilityId , t , targetWidget , attachPoint );
	fprintf_s( logfile , "%s:[-->GAME_AddSpellEffectTargetById<--  abilityId: %i t: %X targetWidget: %X attachPoint: \"%s\"] RETURN-> %X\n" , currentDateTime( ).c_str( ) , abilityId , t , targetWidget , jassgetchar( attachPoint ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_AddUnitAnimationProperties )( HUNIT whichUnit , void * animProperties , BOOL add );
GAME_AddUnitAnimationProperties GAME_AddUnitAnimationPropertiesorg = NULL;
GAME_AddUnitAnimationProperties GAME_AddUnitAnimationPropertiesold = NULL;

void __cdecl GAME_AddUnitAnimationPropertiesmy( HUNIT whichUnit , void * animProperties , BOOL add )
{
	fprintf_s( logfile , "%s" , "AddUnitAnimationPropertiesmy\n" );
	fflush( logfile );

	GAME_AddUnitAnimationPropertiesold( whichUnit , animProperties , add );
	fprintf_s( logfile , "%s:[-->GAME_AddUnitAnimationProperties<--  whichUnit: %X animProperties: \"%s\" add: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , jassgetchar( animProperties ) , add ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_AddUnitToAllStock )( int unitId , int currentStock , int stockMax );
GAME_AddUnitToAllStock GAME_AddUnitToAllStockorg = NULL;
GAME_AddUnitToAllStock GAME_AddUnitToAllStockold = NULL;

void __cdecl GAME_AddUnitToAllStockmy( int unitId , int currentStock , int stockMax )
{
	fprintf_s( logfile , "%s" , "AddUnitToAllStockmy\n" );
	fflush( logfile );

	GAME_AddUnitToAllStockold( unitId , currentStock , stockMax );
	fprintf_s( logfile , "%s:[-->GAME_AddUnitToAllStock<--  unitId: %i currentStock: %i stockMax: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , unitId , currentStock , stockMax );
	fflush( logfile );

}


typedef void( __cdecl *GAME_AddUnitToStock )( HUNIT whichUnit , int unitId , int currentStock , int stockMax );
GAME_AddUnitToStock GAME_AddUnitToStockorg = NULL;
GAME_AddUnitToStock GAME_AddUnitToStockold = NULL;

void __cdecl GAME_AddUnitToStockmy( HUNIT whichUnit , int unitId , int currentStock , int stockMax )
{
	fprintf_s( logfile , "%s\n" , "AddUnitToStockmy" );
	fflush( logfile );

	GAME_AddUnitToStockold( whichUnit , unitId , currentStock , stockMax );
	fprintf_s( logfile , "%s:[-->GAME_AddUnitToStock<--  whichUnit: %X unitId: %i currentStock: %i stockMax: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , unitId , currentStock , stockMax );
	fflush( logfile );

}


typedef HWEATHEREFFECT( __cdecl *GAME_AddWeatherEffect )( HRECT where , int effectID );
GAME_AddWeatherEffect GAME_AddWeatherEffectorg = NULL;
GAME_AddWeatherEffect GAME_AddWeatherEffectold = NULL;

HWEATHEREFFECT __cdecl GAME_AddWeatherEffectmy( HRECT where , int effectID )
{
	fprintf_s( logfile , "%s\n" , "AddWeatherEffectmy" );
	fflush( logfile );

	HWEATHEREFFECT retvalue = GAME_AddWeatherEffectold( where , effectID );
	fprintf_s( logfile , "%s:[-->GAME_AddWeatherEffect<--  where: %X effectID: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , where , effectID , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_AdjustCameraField )( HCAMERAFIELD whichField , float *offset , float *duration );
GAME_AdjustCameraField GAME_AdjustCameraFieldorg = NULL;
GAME_AdjustCameraField GAME_AdjustCameraFieldold = NULL;

void __cdecl GAME_AdjustCameraFieldmy( HCAMERAFIELD whichField , float *offset , float *duration )
{
	fprintf_s( logfile , "%s\n" , "AdjustCameraFieldmy" );
	fflush( logfile );

	GAME_AdjustCameraFieldold( whichField , offset , duration );
	fprintf_s( logfile , "%s:[-->GAME_AdjustCameraField<--  whichField: %X offset: %f duration: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichField , *( float * ) offset , *( float * ) duration );
	fflush( logfile );

}


typedef HBOOLEXPR( __cdecl *GAME_And )( HBOOLEXPR operandA , HBOOLEXPR operandB );
GAME_And GAME_Andorg = NULL;
GAME_And GAME_Andold = NULL;

HBOOLEXPR __cdecl GAME_Andmy( HBOOLEXPR operandA , HBOOLEXPR operandB )
{
	fprintf_s( logfile , "%s\n" , "Andmy" );
	fflush( logfile );

	HBOOLEXPR retvalue = GAME_Andold( operandA , operandB );
	fprintf_s( logfile , "%s:[-->GAME_And<--  operandA: %X operandB: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , operandA , operandB , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_Asin )( float *y );
GAME_Asin GAME_Asinorg = NULL;
GAME_Asin GAME_Asinold = NULL;

DWFP __cdecl GAME_Asinmy( float *y )
{
	fprintf_s( logfile , "%s\n" , "Asinmy" );
	fflush( logfile );

	DWFP retvalue = GAME_Asinold( y );
	fprintf_s( logfile , "%s:[-->GAME_Asin<--  y: %f] RETURN-> %f\n" , currentDateTime( ).c_str( ) , *( float * ) y , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_Atan )( float *x );
GAME_Atan GAME_Atanorg = NULL;
GAME_Atan GAME_Atanold = NULL;

DWFP __cdecl GAME_Atanmy( float *x )
{
	fprintf_s( logfile , "%s\n" , "Atanmy" );
	fflush( logfile );

	DWFP retvalue = GAME_Atanold( x );
	fprintf_s( logfile , "%s:[-->GAME_Atan<--  x: %f] RETURN-> %f\n" , currentDateTime( ).c_str( ) , *( float * ) x , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_Atan2 )( float *y , float *x );
GAME_Atan2 GAME_Atan2org = NULL;
GAME_Atan2 GAME_Atan2old = NULL;

DWFP __cdecl GAME_Atan2my( float *y , float *x )
{
	fprintf_s( logfile , "%s\n" , "Atan2my" );
	fflush( logfile );

	DWFP retvalue = GAME_Atan2old( y , x );
	fprintf_s( logfile , "%s:[-->GAME_Atan2<--  y: %f x: %f] RETURN-> %f\n" , currentDateTime( ).c_str( ) , *( float * ) y , *( float * ) x , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_AttachSoundToUnit )( HSOUND soundHandle , HUNIT whichUnit );
GAME_AttachSoundToUnit GAME_AttachSoundToUnitorg = NULL;
GAME_AttachSoundToUnit GAME_AttachSoundToUnitold = NULL;

void __cdecl GAME_AttachSoundToUnitmy( HSOUND soundHandle , HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "AttachSoundToUnitmy" );
	fflush( logfile );

	GAME_AttachSoundToUnitold( soundHandle , whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_AttachSoundToUnit<--  soundHandle: %X whichUnit: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , soundHandle , whichUnit );
	fflush( logfile );

}


typedef void( __cdecl *GAME_AttackMoveKill )( HUNIT arg1 );
GAME_AttackMoveKill GAME_AttackMoveKillorg = NULL;
GAME_AttackMoveKill GAME_AttackMoveKillold = NULL;

void __cdecl GAME_AttackMoveKillmy( HUNIT arg1 )
{
	fprintf_s( logfile , "%s\n" , "AttackMoveKillmy" );
	fflush( logfile );

	GAME_AttackMoveKillold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_AttackMoveKill<--  arg1: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_AttackMoveXY )( int arg1 , int arg2 );
GAME_AttackMoveXY GAME_AttackMoveXYorg = NULL;
GAME_AttackMoveXY GAME_AttackMoveXYold = NULL;

void __cdecl GAME_AttackMoveXYmy( int arg1 , int arg2 )
{
	fprintf_s( logfile , "%s\n" , "AttackMoveXYmy" );
	fflush( logfile );

	GAME_AttackMoveXYold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_AttackMoveXY<--  arg1: %i arg2: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 , arg2 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_CachePlayerHeroData )( HPLAYER whichPlayer );
GAME_CachePlayerHeroData GAME_CachePlayerHeroDataorg = NULL;
GAME_CachePlayerHeroData GAME_CachePlayerHeroDataold = NULL;

void __cdecl GAME_CachePlayerHeroDatamy( HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s\n" , "CachePlayerHeroDatamy" );
	fflush( logfile );

	GAME_CachePlayerHeroDataold( whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_CachePlayerHeroData<--  whichPlayer: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer );
	fflush( logfile );

}


typedef void( __cdecl *GAME_CameraSetSmoothingFactor )( float *factor );
GAME_CameraSetSmoothingFactor GAME_CameraSetSmoothingFactororg = NULL;
GAME_CameraSetSmoothingFactor GAME_CameraSetSmoothingFactorold = NULL;

void __cdecl GAME_CameraSetSmoothingFactormy( float *factor )
{
	fprintf_s( logfile , "%s\n" , "CameraSetSmoothingFactormy" );
	fflush( logfile );

	GAME_CameraSetSmoothingFactorold( factor );
	fprintf_s( logfile , "%s:[-->GAME_CameraSetSmoothingFactor<--  factor: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) factor );
	fflush( logfile );

}


typedef void( __cdecl *GAME_CameraSetSourceNoise )( float *mag , float *velocity );
GAME_CameraSetSourceNoise GAME_CameraSetSourceNoiseorg = NULL;
GAME_CameraSetSourceNoise GAME_CameraSetSourceNoiseold = NULL;

void __cdecl GAME_CameraSetSourceNoisemy( float *mag , float *velocity )
{
	fprintf_s( logfile , "%s\n" , "CameraSetSourceNoisemy" );
	fflush( logfile );

	GAME_CameraSetSourceNoiseold( mag , velocity );
	fprintf_s( logfile , "%s:[-->GAME_CameraSetSourceNoise<--  mag: %f velocity: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) mag , *( float * ) velocity );
	fflush( logfile );

}


typedef void( __cdecl *GAME_CameraSetSourceNoiseEx )( float *mag , float *velocity , BOOL vertOnly );
GAME_CameraSetSourceNoiseEx GAME_CameraSetSourceNoiseExorg = NULL;
GAME_CameraSetSourceNoiseEx GAME_CameraSetSourceNoiseExold = NULL;

void __cdecl GAME_CameraSetSourceNoiseExmy( float *mag , float *velocity , BOOL vertOnly )
{
	fprintf_s( logfile , "%s\n" , "CameraSetSourceNoiseExmy" );
	fflush( logfile );

	GAME_CameraSetSourceNoiseExold( mag , velocity , vertOnly );
	fprintf_s( logfile , "%s:[-->GAME_CameraSetSourceNoiseEx<--  mag: %f velocity: %f vertOnly: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) mag , *( float * ) velocity , vertOnly ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_CameraSetTargetNoise )( float *mag , float *velocity );
GAME_CameraSetTargetNoise GAME_CameraSetTargetNoiseorg = NULL;
GAME_CameraSetTargetNoise GAME_CameraSetTargetNoiseold = NULL;

void __cdecl GAME_CameraSetTargetNoisemy( float *mag , float *velocity )
{
	fprintf_s( logfile , "%s" , "CameraSetTargetNoisemy\n" );
	fflush( logfile );

	GAME_CameraSetTargetNoiseold( mag , velocity );
	fprintf_s( logfile , "%s:[-->GAME_CameraSetTargetNoise<--  mag: %f velocity: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) mag , *( float * ) velocity );
	fflush( logfile );

}


typedef void( __cdecl *GAME_CameraSetTargetNoiseEx )( float *mag , float *velocity , BOOL vertOnly );
GAME_CameraSetTargetNoiseEx GAME_CameraSetTargetNoiseExorg = NULL;
GAME_CameraSetTargetNoiseEx GAME_CameraSetTargetNoiseExold = NULL;

void __cdecl GAME_CameraSetTargetNoiseExmy( float *mag , float *velocity , BOOL vertOnly )
{
	fprintf_s( logfile , "%s\n" , "CameraSetTargetNoiseExmy" );
	fflush( logfile );

	GAME_CameraSetTargetNoiseExold( mag , velocity , vertOnly );
	fprintf_s( logfile , "%s:[-->GAME_CameraSetTargetNoiseEx<--  mag: %f velocity: %f vertOnly: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) mag , *( float * ) velocity , vertOnly ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_CameraSetupApply )( HCAMERASETUP whichSetup , BOOL doPan , BOOL panTimed );
GAME_CameraSetupApply GAME_CameraSetupApplyorg = NULL;
GAME_CameraSetupApply GAME_CameraSetupApplyold = NULL;

void __cdecl GAME_CameraSetupApplymy( HCAMERASETUP whichSetup , BOOL doPan , BOOL panTimed )
{
	fprintf_s( logfile , "%s" , "CameraSetupApplymy\n" );
	fflush( logfile );

	GAME_CameraSetupApplyold( whichSetup , doPan , panTimed );
	fprintf_s( logfile , "%s:[-->GAME_CameraSetupApply<--  whichSetup: %X doPan: %s panTimed: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichSetup , doPan ? "TRUE\n" : "FALSE" , panTimed ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_CameraSetupApplyForceDuration )( HCAMERASETUP whichSetup , BOOL doPan , float *forceDuration );
GAME_CameraSetupApplyForceDuration GAME_CameraSetupApplyForceDurationorg = NULL;
GAME_CameraSetupApplyForceDuration GAME_CameraSetupApplyForceDurationold = NULL;

void __cdecl GAME_CameraSetupApplyForceDurationmy( HCAMERASETUP whichSetup , BOOL doPan , float *forceDuration )
{
	fprintf_s( logfile , "%s" , "CameraSetupApplyForceDurationmy\n" );
	fflush( logfile );

	GAME_CameraSetupApplyForceDurationold( whichSetup , doPan , forceDuration );
	fprintf_s( logfile , "%s:[-->GAME_CameraSetupApplyForceDuration<--  whichSetup: %X doPan: %s forceDuration: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichSetup , doPan ? "TRUE\n" : "FALSE" , *( float * ) forceDuration );
	fflush( logfile );

}


typedef void( __cdecl *GAME_CameraSetupApplyForceDurationWithZ )( HCAMERASETUP whichSetup , float *zDestOffset , float *forceDuration );
GAME_CameraSetupApplyForceDurationWithZ GAME_CameraSetupApplyForceDurationWithZorg = NULL;
GAME_CameraSetupApplyForceDurationWithZ GAME_CameraSetupApplyForceDurationWithZold = NULL;

void __cdecl GAME_CameraSetupApplyForceDurationWithZmy( HCAMERASETUP whichSetup , float *zDestOffset , float *forceDuration )
{
	fprintf_s( logfile , "%s" , "CameraSetupApplyForceDurationWithZmy\n" );
	fflush( logfile );

	GAME_CameraSetupApplyForceDurationWithZold( whichSetup , zDestOffset , forceDuration );
	fprintf_s( logfile , "%s:[-->GAME_CameraSetupApplyForceDurationWithZ<--  whichSetup: %X zDestOffset: %f forceDuration: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichSetup , *( float * ) zDestOffset , *( float * ) forceDuration );
	fflush( logfile );

}


typedef void( __cdecl *GAME_CameraSetupApplyWithZ )( HCAMERASETUP whichSetup , float *zDestOffset );
GAME_CameraSetupApplyWithZ GAME_CameraSetupApplyWithZorg = NULL;
GAME_CameraSetupApplyWithZ GAME_CameraSetupApplyWithZold = NULL;

void __cdecl GAME_CameraSetupApplyWithZmy( HCAMERASETUP whichSetup , float *zDestOffset )
{
	fprintf_s( logfile , "%s\n" , "CameraSetupApplyWithZmy" );
	fflush( logfile );

	GAME_CameraSetupApplyWithZold( whichSetup , zDestOffset );
	fprintf_s( logfile , "%s:[-->GAME_CameraSetupApplyWithZ<--  whichSetup: %X zDestOffset: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichSetup , *( float * ) zDestOffset );
	fflush( logfile );

}


typedef HLOCATION( __cdecl *GAME_CameraSetupGetDestPositionLoc )( HCAMERASETUP whichSetup );
GAME_CameraSetupGetDestPositionLoc GAME_CameraSetupGetDestPositionLocorg = NULL;
GAME_CameraSetupGetDestPositionLoc GAME_CameraSetupGetDestPositionLocold = NULL;

HLOCATION __cdecl GAME_CameraSetupGetDestPositionLocmy( HCAMERASETUP whichSetup )
{
	fprintf_s( logfile , "%s\n" , "CameraSetupGetDestPositionLocmy" );
	fflush( logfile );

	HLOCATION retvalue = GAME_CameraSetupGetDestPositionLocold( whichSetup );
	fprintf_s( logfile , "%s:[-->GAME_CameraSetupGetDestPositionLoc<--  whichSetup: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichSetup , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_CameraSetupGetDestPositionX )( HCAMERASETUP whichSetup );
GAME_CameraSetupGetDestPositionX GAME_CameraSetupGetDestPositionXorg = NULL;
GAME_CameraSetupGetDestPositionX GAME_CameraSetupGetDestPositionXold = NULL;

DWFP __cdecl GAME_CameraSetupGetDestPositionXmy( HCAMERASETUP whichSetup )
{
	fprintf_s( logfile , "%s\n" , "CameraSetupGetDestPositionXmy" );
	fflush( logfile );

	DWFP retvalue = GAME_CameraSetupGetDestPositionXold( whichSetup );
	fprintf_s( logfile , "%s:[-->GAME_CameraSetupGetDestPositionX<--  whichSetup: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichSetup , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_CameraSetupGetDestPositionY )( HCAMERASETUP whichSetup );
GAME_CameraSetupGetDestPositionY GAME_CameraSetupGetDestPositionYorg = NULL;
GAME_CameraSetupGetDestPositionY GAME_CameraSetupGetDestPositionYold = NULL;

DWFP __cdecl GAME_CameraSetupGetDestPositionYmy( HCAMERASETUP whichSetup )
{
	fprintf_s( logfile , "%s\n" , "CameraSetupGetDestPositionYmy" );
	fflush( logfile );

	DWFP retvalue = GAME_CameraSetupGetDestPositionYold( whichSetup );
	fprintf_s( logfile , "%s:[-->GAME_CameraSetupGetDestPositionY<--  whichSetup: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichSetup , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_CameraSetupGetField )( HCAMERASETUP whichSetup , HCAMERAFIELD whichField );
GAME_CameraSetupGetField GAME_CameraSetupGetFieldorg = NULL;
GAME_CameraSetupGetField GAME_CameraSetupGetFieldold = NULL;

DWFP __cdecl GAME_CameraSetupGetFieldmy( HCAMERASETUP whichSetup , HCAMERAFIELD whichField )
{
	fprintf_s( logfile , "%s\n" , "CameraSetupGetFieldmy" );
	fflush( logfile );

	DWFP retvalue = GAME_CameraSetupGetFieldold( whichSetup , whichField );
	fprintf_s( logfile , "%s:[-->GAME_CameraSetupGetField<--  whichSetup: %X whichField: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichSetup , whichField , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_CameraSetupSetDestPosition )( HCAMERASETUP whichSetup , float *x , float *y , float *duration );
GAME_CameraSetupSetDestPosition GAME_CameraSetupSetDestPositionorg = NULL;
GAME_CameraSetupSetDestPosition GAME_CameraSetupSetDestPositionold = NULL;

void __cdecl GAME_CameraSetupSetDestPositionmy( HCAMERASETUP whichSetup , float *x , float *y , float *duration )
{
	fprintf_s( logfile , "%s\n" , "CameraSetupSetDestPositionmy" );
	fflush( logfile );

	GAME_CameraSetupSetDestPositionold( whichSetup , x , y , duration );
	fprintf_s( logfile , "%s:[-->GAME_CameraSetupSetDestPosition<--  whichSetup: %X x: %f y: %f duration: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichSetup , *( float * ) x , *( float * ) y , *( float * ) duration );
	fflush( logfile );

}


typedef void( __cdecl *GAME_CameraSetupSetField )( HCAMERASETUP whichSetup , HCAMERAFIELD whichField , float *value , float *duration );
GAME_CameraSetupSetField GAME_CameraSetupSetFieldorg = NULL;
GAME_CameraSetupSetField GAME_CameraSetupSetFieldold = NULL;

void __cdecl GAME_CameraSetupSetFieldmy( HCAMERASETUP whichSetup , HCAMERAFIELD whichField , float *value , float *duration )
{
	fprintf_s( logfile , "%s\n" , "CameraSetupSetFieldmy" );
	fflush( logfile );

	GAME_CameraSetupSetFieldold( whichSetup , whichField , value , duration );
	fprintf_s( logfile , "%s:[-->GAME_CameraSetupSetField<--  whichSetup: %X whichField: %X value: %f duration: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichSetup , whichField , *( float * ) value , *( float * ) duration );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_CaptainAtGoal )( );
GAME_CaptainAtGoal GAME_CaptainAtGoalorg = NULL;
GAME_CaptainAtGoal GAME_CaptainAtGoalold = NULL;

BOOL __cdecl GAME_CaptainAtGoalmy( )
{
	fprintf_s( logfile , "%s\n" , "CaptainAtGoalmy" );
	fflush( logfile );

	BOOL retvalue = GAME_CaptainAtGoalold( );
	fprintf_s( logfile , "%s:[-->GAME_CaptainAtGoal<-- ] RETURN-> %s\n" , currentDateTime( ).c_str( ) , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_CaptainAttack )( float *arg1 , float *arg2 );
GAME_CaptainAttack GAME_CaptainAttackorg = NULL;
GAME_CaptainAttack GAME_CaptainAttackold = NULL;

void __cdecl GAME_CaptainAttackmy( float *arg1 , float *arg2 )
{
	fprintf_s( logfile , "%s" , "CaptainAttackmy\n" );
	fflush( logfile );

	GAME_CaptainAttackold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_CaptainAttack<--  arg1: %f arg2: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) arg1 , *( float * ) arg2 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_CaptainGoHome )( );
GAME_CaptainGoHome GAME_CaptainGoHomeorg = NULL;
GAME_CaptainGoHome GAME_CaptainGoHomeold = NULL;

void __cdecl GAME_CaptainGoHomemy( )
{
	fprintf_s( logfile , "%s\n" , "CaptainGoHomemy" );
	fflush( logfile );

	GAME_CaptainGoHomeold( );
	fprintf_s( logfile , "%s:[-->GAME_CaptainGoHome<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef int( __cdecl *GAME_CaptainGroupSize )( );
GAME_CaptainGroupSize GAME_CaptainGroupSizeorg = NULL;
GAME_CaptainGroupSize GAME_CaptainGroupSizeold = NULL;

int __cdecl GAME_CaptainGroupSizemy( )
{
	fprintf_s( logfile , "%s\n" , "CaptainGroupSizemy" );
	fflush( logfile );

	int retvalue = GAME_CaptainGroupSizeold( );
	fprintf_s( logfile , "%s:[-->GAME_CaptainGroupSize<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_CaptainInCombat )( BOOL arg1 );
GAME_CaptainInCombat GAME_CaptainInCombatorg = NULL;
GAME_CaptainInCombat GAME_CaptainInCombatold = NULL;

BOOL __cdecl GAME_CaptainInCombatmy( BOOL arg1 )
{
	fprintf_s( logfile , "%s\n" , "CaptainInCombatmy" );
	fflush( logfile );

	BOOL retvalue = GAME_CaptainInCombatold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_CaptainInCombat<--  arg1: %s] RETURN-> %s\n" , currentDateTime( ).c_str( ) , arg1 ? "TRUE\n" : "FALSE" , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_CaptainIsEmpty )( );
GAME_CaptainIsEmpty GAME_CaptainIsEmptyorg = NULL;
GAME_CaptainIsEmpty GAME_CaptainIsEmptyold = NULL;

BOOL __cdecl GAME_CaptainIsEmptymy( )
{
	fprintf_s( logfile , "%s" , "CaptainIsEmptymy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_CaptainIsEmptyold( );
	fprintf_s( logfile , "%s:[-->GAME_CaptainIsEmpty<-- ] RETURN-> %s\n" , currentDateTime( ).c_str( ) , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_CaptainIsFull )( );
GAME_CaptainIsFull GAME_CaptainIsFullorg = NULL;
GAME_CaptainIsFull GAME_CaptainIsFullold = NULL;

BOOL __cdecl GAME_CaptainIsFullmy( )
{
	fprintf_s( logfile , "%s" , "CaptainIsFullmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_CaptainIsFullold( );
	fprintf_s( logfile , "%s:[-->GAME_CaptainIsFull<-- ] RETURN-> %s\n" , currentDateTime( ).c_str( ) , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_CaptainIsHome )( );
GAME_CaptainIsHome GAME_CaptainIsHomeorg = NULL;
GAME_CaptainIsHome GAME_CaptainIsHomeold = NULL;

BOOL __cdecl GAME_CaptainIsHomemy( )
{
	fprintf_s( logfile , "%s" , "CaptainIsHomemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_CaptainIsHomeold( );
	fprintf_s( logfile , "%s:[-->GAME_CaptainIsHome<-- ] RETURN-> %s\n" , currentDateTime( ).c_str( ) , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_CaptainReadiness )( );
GAME_CaptainReadiness GAME_CaptainReadinessorg = NULL;
GAME_CaptainReadiness GAME_CaptainReadinessold = NULL;

int __cdecl GAME_CaptainReadinessmy( )
{
	fprintf_s( logfile , "%s" , "CaptainReadinessmy\n" );
	fflush( logfile );

	int retvalue = GAME_CaptainReadinessold( );
	fprintf_s( logfile , "%s:[-->GAME_CaptainReadiness<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_CaptainReadinessHP )( );
GAME_CaptainReadinessHP GAME_CaptainReadinessHPorg = NULL;
GAME_CaptainReadinessHP GAME_CaptainReadinessHPold = NULL;

int __cdecl GAME_CaptainReadinessHPmy( )
{
	fprintf_s( logfile , "%s\n" , "CaptainReadinessHPmy" );
	fflush( logfile );

	int retvalue = GAME_CaptainReadinessHPold( );
	fprintf_s( logfile , "%s:[-->GAME_CaptainReadinessHP<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_CaptainReadinessMa )( );
GAME_CaptainReadinessMa GAME_CaptainReadinessMaorg = NULL;
GAME_CaptainReadinessMa GAME_CaptainReadinessMaold = NULL;

int __cdecl GAME_CaptainReadinessMamy( )
{
	fprintf_s( logfile , "%s\n" , "CaptainReadinessMamy" );
	fflush( logfile );

	int retvalue = GAME_CaptainReadinessMaold( );
	fprintf_s( logfile , "%s:[-->GAME_CaptainReadinessMa<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_CaptainRetreating )( );
GAME_CaptainRetreating GAME_CaptainRetreatingorg = NULL;
GAME_CaptainRetreating GAME_CaptainRetreatingold = NULL;

BOOL __cdecl GAME_CaptainRetreatingmy( )
{
	fprintf_s( logfile , "%s\n" , "CaptainRetreatingmy" );
	fflush( logfile );

	BOOL retvalue = GAME_CaptainRetreatingold( );
	fprintf_s( logfile , "%s:[-->GAME_CaptainRetreating<-- ] RETURN-> %s\n" , currentDateTime( ).c_str( ) , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_CaptainVsPlayer )( HPLAYER arg1 );
GAME_CaptainVsPlayer GAME_CaptainVsPlayerorg = NULL;
GAME_CaptainVsPlayer GAME_CaptainVsPlayerold = NULL;

void __cdecl GAME_CaptainVsPlayermy( HPLAYER arg1 )
{
	fprintf_s( logfile , "%s" , "CaptainVsPlayermy\n" );
	fflush( logfile );

	GAME_CaptainVsPlayerold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_CaptainVsPlayer<--  arg1: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_CaptainVsUnits )( HPLAYER arg1 );
GAME_CaptainVsUnits GAME_CaptainVsUnitsorg = NULL;
GAME_CaptainVsUnits GAME_CaptainVsUnitsold = NULL;

void __cdecl GAME_CaptainVsUnitsmy( HPLAYER arg1 )
{
	fprintf_s( logfile , "%s\n" , "CaptainVsUnitsmy" );
	fflush( logfile );

	GAME_CaptainVsUnitsold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_CaptainVsUnits<--  arg1: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ChangeLevel )( void * newLevel , BOOL doScoreScreen );
GAME_ChangeLevel GAME_ChangeLevelorg = NULL;
GAME_ChangeLevel GAME_ChangeLevelold = NULL;

void __cdecl GAME_ChangeLevelmy( void * newLevel , BOOL doScoreScreen )
{
	fprintf_s( logfile , "%s\n" , "ChangeLevelmy" );
	fflush( logfile );

	GAME_ChangeLevelold( newLevel , doScoreScreen );
	fprintf_s( logfile , "%s:[-->GAME_ChangeLevel<--  newLevel: \"%s\" doScoreScreen: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( newLevel ) , doScoreScreen ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_Cheat )( void * cheatStr );
GAME_Cheat GAME_Cheatorg = NULL;
GAME_Cheat GAME_Cheatold = NULL;

void __cdecl GAME_Cheatmy( void * cheatStr )
{
	fprintf_s( logfile , "%s" , "Cheatmy\n" );
	fflush( logfile );

	GAME_Cheatold( cheatStr );
	fprintf_s( logfile , "%s:[-->GAME_Cheat<--  cheatStr: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( cheatStr ) );
	fflush( logfile );

}


typedef int( __cdecl *GAME_ChooseRandomCreep )( int level );
GAME_ChooseRandomCreep GAME_ChooseRandomCreeporg = NULL;
GAME_ChooseRandomCreep GAME_ChooseRandomCreepold = NULL;

int __cdecl GAME_ChooseRandomCreepmy( int level )
{
	fprintf_s( logfile , "%s" , "ChooseRandomCreepmy\n" );
	fflush( logfile );

	int retvalue = GAME_ChooseRandomCreepold( level );
	fprintf_s( logfile , "%s:[-->GAME_ChooseRandomCreep<--  level: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , level , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_ChooseRandomItem )( int level );
GAME_ChooseRandomItem GAME_ChooseRandomItemorg = NULL;
GAME_ChooseRandomItem GAME_ChooseRandomItemold = NULL;

int __cdecl GAME_ChooseRandomItemmy( int level )
{
	fprintf_s( logfile , "%s\n" , "ChooseRandomItemmy" );
	fflush( logfile );

	int retvalue = GAME_ChooseRandomItemold( level );
	fprintf_s( logfile , "%s:[-->GAME_ChooseRandomItem<--  level: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , level , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_ChooseRandomItemEx )( HITEMTYPE whichType , int level );
GAME_ChooseRandomItemEx GAME_ChooseRandomItemExorg = NULL;
GAME_ChooseRandomItemEx GAME_ChooseRandomItemExold = NULL;

int __cdecl GAME_ChooseRandomItemExmy( HITEMTYPE whichType , int level )
{
	fprintf_s( logfile , "%s\n" , "ChooseRandomItemExmy" );
	fflush( logfile );

	int retvalue = GAME_ChooseRandomItemExold( whichType , level );
	fprintf_s( logfile , "%s:[-->GAME_ChooseRandomItemEx<--  whichType: %X level: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichType , level , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_ChooseRandomNPBuilding )( );
GAME_ChooseRandomNPBuilding GAME_ChooseRandomNPBuildingorg = NULL;
GAME_ChooseRandomNPBuilding GAME_ChooseRandomNPBuildingold = NULL;

int __cdecl GAME_ChooseRandomNPBuildingmy( )
{
	fprintf_s( logfile , "%s\n" , "ChooseRandomNPBuildingmy" );
	fflush( logfile );

	int retvalue = GAME_ChooseRandomNPBuildingold( );
	fprintf_s( logfile , "%s:[-->GAME_ChooseRandomNPBuilding<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_ClearCaptainTargets )( );
GAME_ClearCaptainTargets GAME_ClearCaptainTargetsorg = NULL;
GAME_ClearCaptainTargets GAME_ClearCaptainTargetsold = NULL;

void __cdecl GAME_ClearCaptainTargetsmy( )
{
	fprintf_s( logfile , "%s\n" , "ClearCaptainTargetsmy" );
	fflush( logfile );

	GAME_ClearCaptainTargetsold( );
	fprintf_s( logfile , "%s:[-->GAME_ClearCaptainTargets<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ClearHarvestAI )( );
GAME_ClearHarvestAI GAME_ClearHarvestAIorg = NULL;
GAME_ClearHarvestAI GAME_ClearHarvestAIold = NULL;

void __cdecl GAME_ClearHarvestAImy( )
{
	fprintf_s( logfile , "%s\n" , "ClearHarvestAImy" );
	fflush( logfile );

	GAME_ClearHarvestAIold( );
	fprintf_s( logfile , "%s:[-->GAME_ClearHarvestAI<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ClearMapMusic )( );
GAME_ClearMapMusic GAME_ClearMapMusicorg = NULL;
GAME_ClearMapMusic GAME_ClearMapMusicold = NULL;

void __cdecl GAME_ClearMapMusicmy( )
{
	fprintf_s( logfile , "%s\n" , "ClearMapMusicmy" );
	fflush( logfile );

	GAME_ClearMapMusicold( );
	fprintf_s( logfile , "%s:[-->GAME_ClearMapMusic<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ClearSelection )( );
GAME_ClearSelection GAME_ClearSelectionorg = NULL;
GAME_ClearSelection GAME_ClearSelectionold = NULL;

void __cdecl GAME_ClearSelectionmy( )
{
	fprintf_s( logfile , "%s\n" , "ClearSelectionmy" );
	fflush( logfile );

	GAME_ClearSelectionold( );
	fprintf_s( logfile , "%s:[-->GAME_ClearSelection<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ClearStackedSound )( void * arg1 , float *arg2 , float *arg3 );
GAME_ClearStackedSound GAME_ClearStackedSoundorg = NULL;
GAME_ClearStackedSound GAME_ClearStackedSoundold = NULL;

void __cdecl GAME_ClearStackedSoundmy( void * arg1 , float *arg2 , float *arg3 )
{
	fprintf_s( logfile , "%s\n" , "ClearStackedSoundmy" );
	fflush( logfile );

	GAME_ClearStackedSoundold( arg1 , arg2 , arg3 );
	fprintf_s( logfile , "%s:[-->GAME_ClearStackedSound<--  arg1: \"%s\" arg2: %f arg3: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( arg1 ) , *( float * ) arg2 , *( float * ) arg3 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ClearStackedSoundRect )( void * arg1 , HRECT arg2 );
GAME_ClearStackedSoundRect GAME_ClearStackedSoundRectorg = NULL;
GAME_ClearStackedSoundRect GAME_ClearStackedSoundRectold = NULL;

void __cdecl GAME_ClearStackedSoundRectmy( void * arg1 , HRECT arg2 )
{
	fprintf_s( logfile , "%s" , "ClearStackedSoundRectmy\n" );
	fflush( logfile );

	GAME_ClearStackedSoundRectold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_ClearStackedSoundRect<--  arg1: \"%s\" arg2: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( arg1 ) , arg2 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ClearTextMessages )( );
GAME_ClearTextMessages GAME_ClearTextMessagesorg = NULL;
GAME_ClearTextMessages GAME_ClearTextMessagesold = NULL;

void __cdecl GAME_ClearTextMessagesmy( )
{
	fprintf_s( logfile , "%s" , "ClearTextMessagesmy\n" );
	fflush( logfile );

	GAME_ClearTextMessagesold( );
	fprintf_s( logfile , "%s:[-->GAME_ClearTextMessages<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_CommandAI )( HPLAYER num , int command , int data );
GAME_CommandAI GAME_CommandAIorg = NULL;
GAME_CommandAI GAME_CommandAIold = NULL;

void __cdecl GAME_CommandAImy( HPLAYER num , int command , int data )
{
	fprintf_s( logfile , "%s\n" , "CommandAImy" );
	fflush( logfile );

	GAME_CommandAIold( num , command , data );
	fprintf_s( logfile , "%s:[-->GAME_CommandAI<--  num: %X command: %i data: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , num , command , data );
	fflush( logfile );

}


typedef int( __cdecl *GAME_CommandsWaiting )( );
GAME_CommandsWaiting GAME_CommandsWaitingorg = NULL;
GAME_CommandsWaiting GAME_CommandsWaitingold = NULL;

int __cdecl GAME_CommandsWaitingmy( )
{
	fprintf_s( logfile , "%s\n" , "CommandsWaitingmy" );
	fflush( logfile );

	int retvalue = GAME_CommandsWaitingold( );
	fprintf_s( logfile , "%s:[-->GAME_CommandsWaiting<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HCONDITIONFUNC( __cdecl *GAME_Condition )( CODE func );
GAME_Condition GAME_Conditionorg = NULL;
GAME_Condition GAME_Conditionold = NULL;

HCONDITIONFUNC __cdecl GAME_Conditionmy( CODE func )
{
	fprintf_s( logfile , "%s\n" , "Conditionmy" );
	fflush( logfile );

	HCONDITIONFUNC retvalue = GAME_Conditionold( func );
	fprintf_s( logfile , "%s:[-->GAME_Condition<--  func: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , func , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HAIDIFFICULTY( __cdecl *GAME_ConvertAIDifficulty )( int i );
GAME_ConvertAIDifficulty GAME_ConvertAIDifficultyorg = NULL;
GAME_ConvertAIDifficulty GAME_ConvertAIDifficultyold = NULL;

HAIDIFFICULTY __cdecl GAME_ConvertAIDifficultymy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertAIDifficultymy" );
	fflush( logfile );

	HAIDIFFICULTY retvalue = GAME_ConvertAIDifficultyold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertAIDifficulty<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HALLIANCETYPE( __cdecl *GAME_ConvertAllianceType )( int i );
GAME_ConvertAllianceType GAME_ConvertAllianceTypeorg = NULL;
GAME_ConvertAllianceType GAME_ConvertAllianceTypeold = NULL;

HALLIANCETYPE __cdecl GAME_ConvertAllianceTypemy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertAllianceTypemy" );
	fflush( logfile );

	HALLIANCETYPE retvalue = GAME_ConvertAllianceTypeold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertAllianceType<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HATTACKTYPE( __cdecl *GAME_ConvertAttackType )( int i );
GAME_ConvertAttackType GAME_ConvertAttackTypeorg = NULL;
GAME_ConvertAttackType GAME_ConvertAttackTypeold = NULL;

HATTACKTYPE __cdecl GAME_ConvertAttackTypemy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertAttackTypemy" );
	fflush( logfile );

	HATTACKTYPE retvalue = GAME_ConvertAttackTypeold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertAttackType<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HBLENDMODE( __cdecl *GAME_ConvertBlendMode )( int i );
GAME_ConvertBlendMode GAME_ConvertBlendModeorg = NULL;
GAME_ConvertBlendMode GAME_ConvertBlendModeold = NULL;

HBLENDMODE __cdecl GAME_ConvertBlendModemy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertBlendModemy" );
	fflush( logfile );

	HBLENDMODE retvalue = GAME_ConvertBlendModeold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertBlendMode<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HCAMERAFIELD( __cdecl *GAME_ConvertCameraField )( int i );
GAME_ConvertCameraField GAME_ConvertCameraFieldorg = NULL;
GAME_ConvertCameraField GAME_ConvertCameraFieldold = NULL;

HCAMERAFIELD __cdecl GAME_ConvertCameraFieldmy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertCameraFieldmy" );
	fflush( logfile );

	HCAMERAFIELD retvalue = GAME_ConvertCameraFieldold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertCameraField<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HDAMAGETYPE( __cdecl *GAME_ConvertDamageType )( int i );
GAME_ConvertDamageType GAME_ConvertDamageTypeorg = NULL;
GAME_ConvertDamageType GAME_ConvertDamageTypeold = NULL;

HDAMAGETYPE __cdecl GAME_ConvertDamageTypemy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertDamageTypemy" );
	fflush( logfile );

	HDAMAGETYPE retvalue = GAME_ConvertDamageTypeold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertDamageType<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HDIALOGEVENT( __cdecl *GAME_ConvertDialogEvent )( int i );
GAME_ConvertDialogEvent GAME_ConvertDialogEventorg = NULL;
GAME_ConvertDialogEvent GAME_ConvertDialogEventold = NULL;

HDIALOGEVENT __cdecl GAME_ConvertDialogEventmy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertDialogEventmy" );
	fflush( logfile );

	HDIALOGEVENT retvalue = GAME_ConvertDialogEventold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertDialogEvent<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEFFECTTYPE( __cdecl *GAME_ConvertEffectType )( int i );
GAME_ConvertEffectType GAME_ConvertEffectTypeorg = NULL;
GAME_ConvertEffectType GAME_ConvertEffectTypeold = NULL;

HEFFECTTYPE __cdecl GAME_ConvertEffectTypemy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertEffectTypemy" );
	fflush( logfile );

	HEFFECTTYPE retvalue = GAME_ConvertEffectTypeold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertEffectType<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HFGAMESTATE( __cdecl *GAME_ConvertFGameState )( int i );
GAME_ConvertFGameState GAME_ConvertFGameStateorg = NULL;
GAME_ConvertFGameState GAME_ConvertFGameStateold = NULL;

HFGAMESTATE __cdecl GAME_ConvertFGameStatemy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertFGameStatemy" );
	fflush( logfile );

	HFGAMESTATE retvalue = GAME_ConvertFGameStateold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertFGameState<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HFOGSTATE( __cdecl *GAME_ConvertFogState )( int i );
GAME_ConvertFogState GAME_ConvertFogStateorg = NULL;
GAME_ConvertFogState GAME_ConvertFogStateold = NULL;

HFOGSTATE __cdecl GAME_ConvertFogStatemy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertFogStatemy" );
	fflush( logfile );

	HFOGSTATE retvalue = GAME_ConvertFogStateold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertFogState<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HGAMEDIFFICULTY( __cdecl *GAME_ConvertGameDifficulty )( int i );
GAME_ConvertGameDifficulty GAME_ConvertGameDifficultyorg = NULL;
GAME_ConvertGameDifficulty GAME_ConvertGameDifficultyold = NULL;

HGAMEDIFFICULTY __cdecl GAME_ConvertGameDifficultymy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertGameDifficultymy" );
	fflush( logfile );

	HGAMEDIFFICULTY retvalue = GAME_ConvertGameDifficultyold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertGameDifficulty<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HGAMEEVENT( __cdecl *GAME_ConvertGameEvent )( int i );
GAME_ConvertGameEvent GAME_ConvertGameEventorg = NULL;
GAME_ConvertGameEvent GAME_ConvertGameEventold = NULL;

HGAMEEVENT __cdecl GAME_ConvertGameEventmy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertGameEventmy" );
	fflush( logfile );

	HGAMEEVENT retvalue = GAME_ConvertGameEventold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertGameEvent<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HGAMESPEED( __cdecl *GAME_ConvertGameSpeed )( int i );
GAME_ConvertGameSpeed GAME_ConvertGameSpeedorg = NULL;
GAME_ConvertGameSpeed GAME_ConvertGameSpeedold = NULL;

HGAMESPEED __cdecl GAME_ConvertGameSpeedmy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertGameSpeedmy" );
	fflush( logfile );

	HGAMESPEED retvalue = GAME_ConvertGameSpeedold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertGameSpeed<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HGAMETYPE( __cdecl *GAME_ConvertGameType )( int i );
GAME_ConvertGameType GAME_ConvertGameTypeorg = NULL;
GAME_ConvertGameType GAME_ConvertGameTypeold = NULL;

HGAMETYPE __cdecl GAME_ConvertGameTypemy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertGameTypemy" );
	fflush( logfile );

	HGAMETYPE retvalue = GAME_ConvertGameTypeold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertGameType<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HIGAMESTATE( __cdecl *GAME_ConvertIGameState )( int i );
GAME_ConvertIGameState GAME_ConvertIGameStateorg = NULL;
GAME_ConvertIGameState GAME_ConvertIGameStateold = NULL;

HIGAMESTATE __cdecl GAME_ConvertIGameStatemy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertIGameStatemy" );
	fflush( logfile );

	HIGAMESTATE retvalue = GAME_ConvertIGameStateold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertIGameState<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HITEMTYPE( __cdecl *GAME_ConvertItemType )( int i );
GAME_ConvertItemType GAME_ConvertItemTypeorg = NULL;
GAME_ConvertItemType GAME_ConvertItemTypeold = NULL;

HITEMTYPE __cdecl GAME_ConvertItemTypemy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertItemTypemy" );
	fflush( logfile );

	HITEMTYPE retvalue = GAME_ConvertItemTypeold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertItemType<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HLIMITOP( __cdecl *GAME_ConvertLimitOp )( int i );
GAME_ConvertLimitOp GAME_ConvertLimitOporg = NULL;
GAME_ConvertLimitOp GAME_ConvertLimitOpold = NULL;

HLIMITOP __cdecl GAME_ConvertLimitOpmy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertLimitOpmy" );
	fflush( logfile );

	HLIMITOP retvalue = GAME_ConvertLimitOpold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertLimitOp<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HMAPCONTROL( __cdecl *GAME_ConvertMapControl )( int i );
GAME_ConvertMapControl GAME_ConvertMapControlorg = NULL;
GAME_ConvertMapControl GAME_ConvertMapControlold = NULL;

HMAPCONTROL __cdecl GAME_ConvertMapControlmy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertMapControlmy" );
	fflush( logfile );

	HMAPCONTROL retvalue = GAME_ConvertMapControlold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertMapControl<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HMAPDENSITY( __cdecl *GAME_ConvertMapDensity )( int i );
GAME_ConvertMapDensity GAME_ConvertMapDensityorg = NULL;
GAME_ConvertMapDensity GAME_ConvertMapDensityold = NULL;

HMAPDENSITY __cdecl GAME_ConvertMapDensitymy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertMapDensitymy" );
	fflush( logfile );

	HMAPDENSITY retvalue = GAME_ConvertMapDensityold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertMapDensity<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HMAPFLAG( __cdecl *GAME_ConvertMapFlag )( int i );
GAME_ConvertMapFlag GAME_ConvertMapFlagorg = NULL;
GAME_ConvertMapFlag GAME_ConvertMapFlagold = NULL;

HMAPFLAG __cdecl GAME_ConvertMapFlagmy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertMapFlagmy" );
	fflush( logfile );

	HMAPFLAG retvalue = GAME_ConvertMapFlagold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertMapFlag<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HMAPSETTING( __cdecl *GAME_ConvertMapSetting )( int i );
GAME_ConvertMapSetting GAME_ConvertMapSettingorg = NULL;
GAME_ConvertMapSetting GAME_ConvertMapSettingold = NULL;

HMAPSETTING __cdecl GAME_ConvertMapSettingmy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertMapSettingmy" );
	fflush( logfile );

	HMAPSETTING retvalue = GAME_ConvertMapSettingold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertMapSetting<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HMAPVISIBILITY( __cdecl *GAME_ConvertMapVisibility )( int i );
GAME_ConvertMapVisibility GAME_ConvertMapVisibilityorg = NULL;
GAME_ConvertMapVisibility GAME_ConvertMapVisibilityold = NULL;

HMAPVISIBILITY __cdecl GAME_ConvertMapVisibilitymy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertMapVisibilitymy" );
	fflush( logfile );

	HMAPVISIBILITY retvalue = GAME_ConvertMapVisibilityold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertMapVisibility<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HPATHINGTYPE( __cdecl *GAME_ConvertPathingType )( int i );
GAME_ConvertPathingType GAME_ConvertPathingTypeorg = NULL;
GAME_ConvertPathingType GAME_ConvertPathingTypeold = NULL;

HPATHINGTYPE __cdecl GAME_ConvertPathingTypemy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertPathingTypemy" );
	fflush( logfile );

	HPATHINGTYPE retvalue = GAME_ConvertPathingTypeold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertPathingType<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HPLACEMENT( __cdecl *GAME_ConvertPlacement )( int i );
GAME_ConvertPlacement GAME_ConvertPlacementorg = NULL;
GAME_ConvertPlacement GAME_ConvertPlacementold = NULL;

HPLACEMENT __cdecl GAME_ConvertPlacementmy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertPlacementmy" );
	fflush( logfile );

	HPLACEMENT retvalue = GAME_ConvertPlacementold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertPlacement<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYERCOLOR( __cdecl *GAME_ConvertPlayerColor )( int i );
GAME_ConvertPlayerColor GAME_ConvertPlayerColororg = NULL;
GAME_ConvertPlayerColor GAME_ConvertPlayerColorold = NULL;

HPLAYERCOLOR __cdecl GAME_ConvertPlayerColormy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertPlayerColormy" );
	fflush( logfile );

	HPLAYERCOLOR retvalue = GAME_ConvertPlayerColorold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertPlayerColor<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYEREVENT( __cdecl *GAME_ConvertPlayerEvent )( int i );
GAME_ConvertPlayerEvent GAME_ConvertPlayerEventorg = NULL;
GAME_ConvertPlayerEvent GAME_ConvertPlayerEventold = NULL;

HPLAYEREVENT __cdecl GAME_ConvertPlayerEventmy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertPlayerEventmy" );
	fflush( logfile );

	HPLAYEREVENT retvalue = GAME_ConvertPlayerEventold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertPlayerEvent<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYERGAMERESULT( __cdecl *GAME_ConvertPlayerGameResult )( int i );
GAME_ConvertPlayerGameResult GAME_ConvertPlayerGameResultorg = NULL;
GAME_ConvertPlayerGameResult GAME_ConvertPlayerGameResultold = NULL;

HPLAYERGAMERESULT __cdecl GAME_ConvertPlayerGameResultmy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertPlayerGameResultmy" );
	fflush( logfile );

	HPLAYERGAMERESULT retvalue = GAME_ConvertPlayerGameResultold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertPlayerGameResult<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYERSCORE( __cdecl *GAME_ConvertPlayerScore )( int i );
GAME_ConvertPlayerScore GAME_ConvertPlayerScoreorg = NULL;
GAME_ConvertPlayerScore GAME_ConvertPlayerScoreold = NULL;

HPLAYERSCORE __cdecl GAME_ConvertPlayerScoremy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertPlayerScoremy" );
	fflush( logfile );

	HPLAYERSCORE retvalue = GAME_ConvertPlayerScoreold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertPlayerScore<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYERSLOTSTATE( __cdecl *GAME_ConvertPlayerSlotState )( int i );
GAME_ConvertPlayerSlotState GAME_ConvertPlayerSlotStateorg = NULL;
GAME_ConvertPlayerSlotState GAME_ConvertPlayerSlotStateold = NULL;

HPLAYERSLOTSTATE __cdecl GAME_ConvertPlayerSlotStatemy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertPlayerSlotStatemy" );
	fflush( logfile );

	HPLAYERSLOTSTATE retvalue = GAME_ConvertPlayerSlotStateold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertPlayerSlotState<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYERSTATE( __cdecl *GAME_ConvertPlayerState )( int i );
GAME_ConvertPlayerState GAME_ConvertPlayerStateorg = NULL;
GAME_ConvertPlayerState GAME_ConvertPlayerStateold = NULL;

HPLAYERSTATE __cdecl GAME_ConvertPlayerStatemy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertPlayerStatemy" );
	fflush( logfile );

	HPLAYERSTATE retvalue = GAME_ConvertPlayerStateold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertPlayerState<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYERUNITEVENT( __cdecl *GAME_ConvertPlayerUnitEvent )( int i );
GAME_ConvertPlayerUnitEvent GAME_ConvertPlayerUnitEventorg = NULL;
GAME_ConvertPlayerUnitEvent GAME_ConvertPlayerUnitEventold = NULL;

HPLAYERUNITEVENT __cdecl GAME_ConvertPlayerUnitEventmy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertPlayerUnitEventmy" );
	fflush( logfile );

	HPLAYERUNITEVENT retvalue = GAME_ConvertPlayerUnitEventold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertPlayerUnitEvent<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HRACE( __cdecl *GAME_ConvertRace )( int i );
GAME_ConvertRace GAME_ConvertRaceorg = NULL;
GAME_ConvertRace GAME_ConvertRaceold = NULL;

HRACE __cdecl GAME_ConvertRacemy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertRacemy" );
	fflush( logfile );

	HRACE retvalue = GAME_ConvertRaceold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertRace<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HRACEPREFERENCE( __cdecl *GAME_ConvertRacePref )( int i );
GAME_ConvertRacePref GAME_ConvertRacePreforg = NULL;
GAME_ConvertRacePref GAME_ConvertRacePrefold = NULL;

HRACEPREFERENCE __cdecl GAME_ConvertRacePrefmy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertRacePrefmy" );
	fflush( logfile );

	HRACEPREFERENCE retvalue = GAME_ConvertRacePrefold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertRacePref<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HRARITYCONTROL( __cdecl *GAME_ConvertRarityControl )( int i );
GAME_ConvertRarityControl GAME_ConvertRarityControlorg = NULL;
GAME_ConvertRarityControl GAME_ConvertRarityControlold = NULL;

HRARITYCONTROL __cdecl GAME_ConvertRarityControlmy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertRarityControlmy" );
	fflush( logfile );

	HRARITYCONTROL retvalue = GAME_ConvertRarityControlold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertRarityControl<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HSOUNDTYPE( __cdecl *GAME_ConvertSoundType )( int i );
GAME_ConvertSoundType GAME_ConvertSoundTypeorg = NULL;
GAME_ConvertSoundType GAME_ConvertSoundTypeold = NULL;

HSOUNDTYPE __cdecl GAME_ConvertSoundTypemy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertSoundTypemy" );
	fflush( logfile );

	HSOUNDTYPE retvalue = GAME_ConvertSoundTypeold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertSoundType<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HSTARTLOCPRIO( __cdecl *GAME_ConvertStartLocPrio )( int i );
GAME_ConvertStartLocPrio GAME_ConvertStartLocPrioorg = NULL;
GAME_ConvertStartLocPrio GAME_ConvertStartLocPrioold = NULL;

HSTARTLOCPRIO __cdecl GAME_ConvertStartLocPriomy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertStartLocPriomy" );
	fflush( logfile );

	HSTARTLOCPRIO retvalue = GAME_ConvertStartLocPrioold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertStartLocPrio<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTEXMAPFLAGS( __cdecl *GAME_ConvertTexMapFlags )( int i );
GAME_ConvertTexMapFlags GAME_ConvertTexMapFlagsorg = NULL;
GAME_ConvertTexMapFlags GAME_ConvertTexMapFlagsold = NULL;

HTEXMAPFLAGS __cdecl GAME_ConvertTexMapFlagsmy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertTexMapFlagsmy" );
	fflush( logfile );

	HTEXMAPFLAGS retvalue = GAME_ConvertTexMapFlagsold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertTexMapFlags<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNITEVENT( __cdecl *GAME_ConvertUnitEvent )( int i );
GAME_ConvertUnitEvent GAME_ConvertUnitEventorg = NULL;
GAME_ConvertUnitEvent GAME_ConvertUnitEventold = NULL;

HUNITEVENT __cdecl GAME_ConvertUnitEventmy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertUnitEventmy" );
	fflush( logfile );

	HUNITEVENT retvalue = GAME_ConvertUnitEventold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertUnitEvent<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNITSTATE( __cdecl *GAME_ConvertUnitState )( int i );
GAME_ConvertUnitState GAME_ConvertUnitStateorg = NULL;
GAME_ConvertUnitState GAME_ConvertUnitStateold = NULL;

HUNITSTATE __cdecl GAME_ConvertUnitStatemy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertUnitStatemy" );
	fflush( logfile );

	HUNITSTATE retvalue = GAME_ConvertUnitStateold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertUnitState<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNITTYPE( __cdecl *GAME_ConvertUnitType )( int i );
GAME_ConvertUnitType GAME_ConvertUnitTypeorg = NULL;
GAME_ConvertUnitType GAME_ConvertUnitTypeold = NULL;

HUNITTYPE __cdecl GAME_ConvertUnitTypemy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertUnitTypemy" );
	fflush( logfile );

	HUNITTYPE retvalue = GAME_ConvertUnitTypeold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertUnitType<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_ConvertUnits )( int arg1 , int arg2 );
GAME_ConvertUnits GAME_ConvertUnitsorg = NULL;
GAME_ConvertUnits GAME_ConvertUnitsold = NULL;

BOOL __cdecl GAME_ConvertUnitsmy( int arg1 , int arg2 )
{
	fprintf_s( logfile , "%s\n" , "ConvertUnitsmy" );
	fflush( logfile );

	BOOL retvalue = GAME_ConvertUnitsold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_ConvertUnits<--  arg1: %i arg2: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , arg1 , arg2 , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef HVERSION( __cdecl *GAME_ConvertVersion )( int i );
GAME_ConvertVersion GAME_ConvertVersionorg = NULL;
GAME_ConvertVersion GAME_ConvertVersionold = NULL;

HVERSION __cdecl GAME_ConvertVersionmy( int i )
{
	fprintf_s( logfile , "%s" , "ConvertVersionmy\n" );
	fflush( logfile );

	HVERSION retvalue = GAME_ConvertVersionold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertVersion<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HVOLUMEGROUP( __cdecl *GAME_ConvertVolumeGroup )( int i );
GAME_ConvertVolumeGroup GAME_ConvertVolumeGrouporg = NULL;
GAME_ConvertVolumeGroup GAME_ConvertVolumeGroupold = NULL;

HVOLUMEGROUP __cdecl GAME_ConvertVolumeGroupmy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertVolumeGroupmy" );
	fflush( logfile );

	HVOLUMEGROUP retvalue = GAME_ConvertVolumeGroupold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertVolumeGroup<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HWEAPONTYPE( __cdecl *GAME_ConvertWeaponType )( int i );
GAME_ConvertWeaponType GAME_ConvertWeaponTypeorg = NULL;
GAME_ConvertWeaponType GAME_ConvertWeaponTypeold = NULL;

HWEAPONTYPE __cdecl GAME_ConvertWeaponTypemy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertWeaponTypemy" );
	fflush( logfile );

	HWEAPONTYPE retvalue = GAME_ConvertWeaponTypeold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertWeaponType<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HWIDGETEVENT( __cdecl *GAME_ConvertWidgetEvent )( int i );
GAME_ConvertWidgetEvent GAME_ConvertWidgetEventorg = NULL;
GAME_ConvertWidgetEvent GAME_ConvertWidgetEventold = NULL;

HWIDGETEVENT __cdecl GAME_ConvertWidgetEventmy( int i )
{
	fprintf_s( logfile , "%s\n" , "ConvertWidgetEventmy" );
	fflush( logfile );

	HWIDGETEVENT retvalue = GAME_ConvertWidgetEventold( i );
	fprintf_s( logfile , "%s:[-->GAME_ConvertWidgetEvent<--  i: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_CopySaveGame )( void * sourceSaveName , void * destSaveName );
GAME_CopySaveGame GAME_CopySaveGameorg = NULL;
GAME_CopySaveGame GAME_CopySaveGameold = NULL;

BOOL __cdecl GAME_CopySaveGamemy( void * sourceSaveName , void * destSaveName )
{
	fprintf_s( logfile , "%s\n" , "CopySaveGamemy" );
	fflush( logfile );

	BOOL retvalue = GAME_CopySaveGameold( sourceSaveName , destSaveName );
	fprintf_s( logfile , "%s:[-->GAME_CopySaveGame<--  sourceSaveName: \"%s\" destSaveName: \"%s\"] RETURN-> %s\n" , currentDateTime( ).c_str( ) , jassgetchar( sourceSaveName ) , jassgetchar( destSaveName ) , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_Cos )( float *radians );
GAME_Cos GAME_Cosorg = NULL;
GAME_Cos GAME_Cosold = NULL;

DWFP __cdecl GAME_Cosmy( float *radians )
{
	fprintf_s( logfile , "%s" , "Cosmy\n" );
	fflush( logfile );

	DWFP retvalue = GAME_Cosold( radians );
	fprintf_s( logfile , "%s:[-->GAME_Cos<--  radians: %f] RETURN-> %f\n" , currentDateTime( ).c_str( ) , *( float * ) radians , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_CreateBlightedGoldmine )( HPLAYER id , float *x , float *y , float *face );
GAME_CreateBlightedGoldmine GAME_CreateBlightedGoldmineorg = NULL;
GAME_CreateBlightedGoldmine GAME_CreateBlightedGoldmineold = NULL;

HUNIT __cdecl GAME_CreateBlightedGoldminemy( HPLAYER id , float *x , float *y , float *face )
{
	fprintf_s( logfile , "%s\n" , "CreateBlightedGoldminemy" );
	fflush( logfile );

	HUNIT retvalue = GAME_CreateBlightedGoldmineold( id , x , y , face );
	fprintf_s( logfile , "%s:[-->GAME_CreateBlightedGoldmine<--  id: %X x: %f y: %f face: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , id , *( float * ) x , *( float * ) y , *( float * ) face , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HCAMERASETUP( __cdecl *GAME_CreateCameraSetup )( );
GAME_CreateCameraSetup GAME_CreateCameraSetuporg = NULL;
GAME_CreateCameraSetup GAME_CreateCameraSetupold = NULL;

HCAMERASETUP __cdecl GAME_CreateCameraSetupmy( )
{
	fprintf_s( logfile , "%s\n" , "CreateCameraSetupmy" );
	fflush( logfile );

	HCAMERASETUP retvalue = GAME_CreateCameraSetupold( );
	fprintf_s( logfile , "%s:[-->GAME_CreateCameraSetup<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_CreateCaptains )( );
GAME_CreateCaptains GAME_CreateCaptainsorg = NULL;
GAME_CreateCaptains GAME_CreateCaptainsold = NULL;

void __cdecl GAME_CreateCaptainsmy( )
{
	fprintf_s( logfile , "%s\n" , "CreateCaptainsmy" );
	fflush( logfile );

	GAME_CreateCaptainsold( );
	fprintf_s( logfile , "%s:[-->GAME_CreateCaptains<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef HUNIT( __cdecl *GAME_CreateCorpse )( HPLAYER whichPlayer , int unitid , float *x , float *y , float *face );
GAME_CreateCorpse GAME_CreateCorpseorg = NULL;
GAME_CreateCorpse GAME_CreateCorpseold = NULL;

HUNIT __cdecl GAME_CreateCorpsemy( HPLAYER whichPlayer , int unitid , float *x , float *y , float *face )
{
	fprintf_s( logfile , "%s\n" , "CreateCorpsemy" );
	fflush( logfile );

	HUNIT retvalue = GAME_CreateCorpseold( whichPlayer , unitid , x , y , face );
	fprintf_s( logfile , "%s:[-->GAME_CreateCorpse<--  whichPlayer: %X unitid: %i x: %f y: %f face: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichPlayer , unitid , *( float * ) x , *( float * ) y , *( float * ) face , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HDESTRUCTABLE( __cdecl *GAME_CreateDeadDestructable )( int objectid , float *x , float *y , float *face , float *scale , int variation );
GAME_CreateDeadDestructable GAME_CreateDeadDestructableorg = NULL;
GAME_CreateDeadDestructable GAME_CreateDeadDestructableold = NULL;

HDESTRUCTABLE __cdecl GAME_CreateDeadDestructablemy( int objectid , float *x , float *y , float *face , float *scale , int variation )
{
	fprintf_s( logfile , "%s\n" , "CreateDeadDestructablemy" );
	fflush( logfile );

	HDESTRUCTABLE retvalue = GAME_CreateDeadDestructableold( objectid , x , y , face , scale , variation );
	fprintf_s( logfile , "%s:[-->GAME_CreateDeadDestructable<--  objectid: %i x: %f y: %f face: %f scale: %f variation: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , objectid , *( float * ) x , *( float * ) y , *( float * ) face , *( float * ) scale , variation , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HDESTRUCTABLE( __cdecl *GAME_CreateDeadDestructableZ )( int objectid , float *x , float *y , float *z , float *face , float *scale , int variation );
GAME_CreateDeadDestructableZ GAME_CreateDeadDestructableZorg = NULL;
GAME_CreateDeadDestructableZ GAME_CreateDeadDestructableZold = NULL;

HDESTRUCTABLE __cdecl GAME_CreateDeadDestructableZmy( int objectid , float *x , float *y , float *z , float *face , float *scale , int variation )
{
	fprintf_s( logfile , "%s\n" , "CreateDeadDestructableZmy" );
	fflush( logfile );

	HDESTRUCTABLE retvalue = GAME_CreateDeadDestructableZold( objectid , x , y , z , face , scale , variation );
	fprintf_s( logfile , "%s:[-->GAME_CreateDeadDestructableZ<--  objectid: %i x: %f y: %f z: %f face: %f scale: %f variation: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , objectid , *( float * ) x , *( float * ) y , *( float * ) z , *( float * ) face , *( float * ) scale , variation , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HDEFEATCONDITION( __cdecl *GAME_CreateDefeatCondition )( );
GAME_CreateDefeatCondition GAME_CreateDefeatConditionorg = NULL;
GAME_CreateDefeatCondition GAME_CreateDefeatConditionold = NULL;

HDEFEATCONDITION __cdecl GAME_CreateDefeatConditionmy( )
{
	fprintf_s( logfile , "%s\n" , "CreateDefeatConditionmy" );
	fflush( logfile );

	HDEFEATCONDITION retvalue = GAME_CreateDefeatConditionold( );
	fprintf_s( logfile , "%s:[-->GAME_CreateDefeatCondition<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HDESTRUCTABLE( __cdecl *GAME_CreateDestructable )( int objectid , float *x , float *y , float *face , float *scale , int variation );
GAME_CreateDestructable GAME_CreateDestructableorg = NULL;
GAME_CreateDestructable GAME_CreateDestructableold = NULL;

HDESTRUCTABLE __cdecl GAME_CreateDestructablemy( int objectid , float *x , float *y , float *face , float *scale , int variation )
{
	fprintf_s( logfile , "%s\n" , "CreateDestructablemy" );
	fflush( logfile );

	HDESTRUCTABLE retvalue = GAME_CreateDestructableold( objectid , x , y , face , scale , variation );
	fprintf_s( logfile , "%s:[-->GAME_CreateDestructable<--  objectid: %i x: %f y: %f face: %f scale: %f variation: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , objectid , *( float * ) x , *( float * ) y , *( float * ) face , *( float * ) scale , variation , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HDESTRUCTABLE( __cdecl *GAME_CreateDestructableZ )( int objectid , float *x , float *y , float *z , float *face , float *scale , int variation );
GAME_CreateDestructableZ GAME_CreateDestructableZorg = NULL;
GAME_CreateDestructableZ GAME_CreateDestructableZold = NULL;

HDESTRUCTABLE __cdecl GAME_CreateDestructableZmy( int objectid , float *x , float *y , float *z , float *face , float *scale , int variation )
{
	fprintf_s( logfile , "%s\n" , "CreateDestructableZmy" );
	fflush( logfile );

	HDESTRUCTABLE retvalue = GAME_CreateDestructableZold( objectid , x , y , z , face , scale , variation );
	fprintf_s( logfile , "%s:[-->GAME_CreateDestructableZ<--  objectid: %i x: %f y: %f z: %f face: %f scale: %f variation: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , objectid , *( float * ) x , *( float * ) y , *( float * ) z , *( float * ) face , *( float * ) scale , variation , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HFOGMODIFIER( __cdecl *GAME_CreateFogModifierRadius )( HPLAYER forWhichPlayer , HFOGSTATE whichState , float *centerx , float *centerY , float *radius , BOOL useSharedVision , BOOL afterUnits );
GAME_CreateFogModifierRadius GAME_CreateFogModifierRadiusorg = NULL;
GAME_CreateFogModifierRadius GAME_CreateFogModifierRadiusold = NULL;

HFOGMODIFIER __cdecl GAME_CreateFogModifierRadiusmy( HPLAYER forWhichPlayer , HFOGSTATE whichState , float *centerx , float *centerY , float *radius , BOOL useSharedVision , BOOL afterUnits )
{
	fprintf_s( logfile , "%s\n" , "CreateFogModifierRadiusmy" );
	fflush( logfile );

	HFOGMODIFIER retvalue = GAME_CreateFogModifierRadiusold( forWhichPlayer , whichState , centerx , centerY , radius , useSharedVision , afterUnits );
	fprintf_s( logfile , "%s:[-->GAME_CreateFogModifierRadius<--  forWhichPlayer: %X whichState: %X centerx: %f centerY: %f radius: %f useSharedVision: %s afterUnits: %s] RETURN-> %X\n" , currentDateTime( ).c_str( ) , forWhichPlayer , whichState , *( float * ) centerx , *( float * ) centerY , *( float * ) radius , useSharedVision ? "TRUE\n" : "FALSE" , afterUnits ? "TRUE" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HFOGMODIFIER( __cdecl *GAME_CreateFogModifierRadiusLoc )( HPLAYER forWhichPlayer , HFOGSTATE whichState , HLOCATION center , float *radius , BOOL useSharedVision , BOOL afterUnits );
GAME_CreateFogModifierRadiusLoc GAME_CreateFogModifierRadiusLocorg = NULL;
GAME_CreateFogModifierRadiusLoc GAME_CreateFogModifierRadiusLocold = NULL;

HFOGMODIFIER __cdecl GAME_CreateFogModifierRadiusLocmy( HPLAYER forWhichPlayer , HFOGSTATE whichState , HLOCATION center , float *radius , BOOL useSharedVision , BOOL afterUnits )
{
	fprintf_s( logfile , "%s" , "CreateFogModifierRadiusLocmy\n" );
	fflush( logfile );

	HFOGMODIFIER retvalue = GAME_CreateFogModifierRadiusLocold( forWhichPlayer , whichState , center , radius , useSharedVision , afterUnits );
	fprintf_s( logfile , "%s:[-->GAME_CreateFogModifierRadiusLoc<--  forWhichPlayer: %X whichState: %X center: %X radius: %f useSharedVision: %s afterUnits: %s] RETURN-> %X\n" , currentDateTime( ).c_str( ) , forWhichPlayer , whichState , center , *( float * ) radius , useSharedVision ? "TRUE\n" : "FALSE" , afterUnits ? "TRUE" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HFOGMODIFIER( __cdecl *GAME_CreateFogModifierRect )( HPLAYER forWhichPlayer , HFOGSTATE whichState , HRECT where , BOOL useSharedVision , BOOL afterUnits );
GAME_CreateFogModifierRect GAME_CreateFogModifierRectorg = NULL;
GAME_CreateFogModifierRect GAME_CreateFogModifierRectold = NULL;

HFOGMODIFIER __cdecl GAME_CreateFogModifierRectmy( HPLAYER forWhichPlayer , HFOGSTATE whichState , HRECT where , BOOL useSharedVision , BOOL afterUnits )
{
	fprintf_s( logfile , "%s" , "CreateFogModifierRectmy\n" );
	fflush( logfile );

	HFOGMODIFIER retvalue = GAME_CreateFogModifierRectold( forWhichPlayer , whichState , where , useSharedVision , afterUnits );
	fprintf_s( logfile , "%s:[-->GAME_CreateFogModifierRect<--  forWhichPlayer: %X whichState: %X where: %X useSharedVision: %s afterUnits: %s] RETURN-> %X\n" , currentDateTime( ).c_str( ) , forWhichPlayer , whichState , where , useSharedVision ? "TRUE\n" : "FALSE" , afterUnits ? "TRUE" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HFORCE( __cdecl *GAME_CreateForce )( );
GAME_CreateForce GAME_CreateForceorg = NULL;
GAME_CreateForce GAME_CreateForceold = NULL;

HFORCE __cdecl GAME_CreateForcemy( )
{
	fprintf_s( logfile , "%s" , "CreateForcemy\n" );
	fflush( logfile );

	HFORCE retvalue = GAME_CreateForceold( );
	fprintf_s( logfile , "%s:[-->GAME_CreateForce<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HGROUP( __cdecl *GAME_CreateGroup )( );
GAME_CreateGroup GAME_CreateGrouporg = NULL;
GAME_CreateGroup GAME_CreateGroupold = NULL;

HGROUP __cdecl GAME_CreateGroupmy( )
{
	fprintf_s( logfile , "%s\n" , "CreateGroupmy" );
	fflush( logfile );

	HGROUP retvalue = GAME_CreateGroupold( );
	fprintf_s( logfile , "%s:[-->GAME_CreateGroup<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HIMAGE( __cdecl *GAME_CreateImage )( void * file , float *sizeX , float *sizeY , float *sizeZ , float *posX , float *posY , float *posZ , float *originX , float *originY , float *originZ , int imageType );
GAME_CreateImage GAME_CreateImageorg = NULL;
GAME_CreateImage GAME_CreateImageold = NULL;

HIMAGE __cdecl GAME_CreateImagemy( void * file , float *sizeX , float *sizeY , float *sizeZ , float *posX , float *posY , float *posZ , float *originX , float *originY , float *originZ , int imageType )
{
	fprintf_s( logfile , "%s\n" , "CreateImagemy" );
	fflush( logfile );

	HIMAGE retvalue = GAME_CreateImageold( file , sizeX , sizeY , sizeZ , posX , posY , posZ , originX , originY , originZ , imageType );
	fprintf_s( logfile , "%s:[-->GAME_CreateImage<--  file: \"%s\" sizeX: %f sizeY: %f sizeZ: %f posX: %f posY: %f posZ: %f originX: %f originY: %f originZ: %f imageType: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , jassgetchar( file ) , *( float * ) sizeX , *( float * ) sizeY , *( float * ) sizeZ , *( float * ) posX , *( float * ) posY , *( float * ) posZ , *( float * ) originX , *( float * ) originY , *( float * ) originZ , imageType , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HITEM( __cdecl *GAME_CreateItem )( int itemid , float *x , float *y );
GAME_CreateItem GAME_CreateItemorg = NULL;
GAME_CreateItem GAME_CreateItemold = NULL;

HITEM __cdecl GAME_CreateItemmy( int itemid , float *x , float *y )
{
	fprintf_s( logfile , "%s" , "CreateItemmy\n" );
	fflush( logfile );

	HITEM retvalue = GAME_CreateItemold( itemid , x , y );
	fprintf_s( logfile , "%s:[-->GAME_CreateItem<--  itemid: %i x: %f y: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , itemid , *( float * ) x , *( float * ) y , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HITEMPOOL( __cdecl *GAME_CreateItemPool )( );
GAME_CreateItemPool GAME_CreateItemPoolorg = NULL;
GAME_CreateItemPool GAME_CreateItemPoolold = NULL;

HITEMPOOL __cdecl GAME_CreateItemPoolmy( )
{
	fprintf_s( logfile , "%s\n" , "CreateItemPoolmy" );
	fflush( logfile );

	HITEMPOOL retvalue = GAME_CreateItemPoolold( );
	fprintf_s( logfile , "%s:[-->GAME_CreateItemPool<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HLEADERBOARD( __cdecl *GAME_CreateLeaderboard )( );
GAME_CreateLeaderboard GAME_CreateLeaderboardorg = NULL;
GAME_CreateLeaderboard GAME_CreateLeaderboardold = NULL;

HLEADERBOARD __cdecl GAME_CreateLeaderboardmy( )
{
	fprintf_s( logfile , "%s\n" , "CreateLeaderboardmy" );
	fflush( logfile );

	HLEADERBOARD retvalue = GAME_CreateLeaderboardold( );
	fprintf_s( logfile , "%s:[-->GAME_CreateLeaderboard<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HSOUND( __cdecl *GAME_CreateMIDISound )( void * soundLabel , int fadeInRate , int fadeOutRate );
GAME_CreateMIDISound GAME_CreateMIDISoundorg = NULL;
GAME_CreateMIDISound GAME_CreateMIDISoundold = NULL;

HSOUND __cdecl GAME_CreateMIDISoundmy( void * soundLabel , int fadeInRate , int fadeOutRate )
{
	fprintf_s( logfile , "%s\n" , "CreateMIDISoundmy" );
	fflush( logfile );

	HSOUND retvalue = GAME_CreateMIDISoundold( soundLabel , fadeInRate , fadeOutRate );
	fprintf_s( logfile , "%s:[-->GAME_CreateMIDISound<--  soundLabel: \"%s\" fadeInRate: %i fadeOutRate: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , jassgetchar( soundLabel ) , fadeInRate , fadeOutRate , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HMULTIBOARD( __cdecl *GAME_CreateMultiboard )( );
GAME_CreateMultiboard GAME_CreateMultiboardorg = NULL;
GAME_CreateMultiboard GAME_CreateMultiboardold = NULL;

HMULTIBOARD __cdecl GAME_CreateMultiboardmy( )
{
	fprintf_s( logfile , "%s" , "CreateMultiboardmy\n" );
	fflush( logfile );

	HMULTIBOARD retvalue = GAME_CreateMultiboardold( );
	fprintf_s( logfile , "%s:[-->GAME_CreateMultiboard<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HQUEST( __cdecl *GAME_CreateQuest )( );
GAME_CreateQuest GAME_CreateQuestorg = NULL;
GAME_CreateQuest GAME_CreateQuestold = NULL;

HQUEST __cdecl GAME_CreateQuestmy( )
{
	fprintf_s( logfile , "%s\n" , "CreateQuestmy" );
	fflush( logfile );

	HQUEST retvalue = GAME_CreateQuestold( );
	fprintf_s( logfile , "%s:[-->GAME_CreateQuest<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HREGION( __cdecl *GAME_CreateRegion )( );
GAME_CreateRegion GAME_CreateRegionorg = NULL;
GAME_CreateRegion GAME_CreateRegionold = NULL;

HREGION __cdecl GAME_CreateRegionmy( )
{
	fprintf_s( logfile , "%s\n" , "CreateRegionmy" );
	fflush( logfile );

	HREGION retvalue = GAME_CreateRegionold( );
	fprintf_s( logfile , "%s:[-->GAME_CreateRegion<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HSOUND( __cdecl *GAME_CreateSound )( void * fileName , BOOL looping , BOOL is3D , BOOL stopwhenoutofrange , int fadeInRate , int fadeOutRate , void * eaxSetting );
GAME_CreateSound GAME_CreateSoundorg = NULL;
GAME_CreateSound GAME_CreateSoundold = NULL;

HSOUND __cdecl GAME_CreateSoundmy( void * fileName , BOOL looping , BOOL is3D , BOOL stopwhenoutofrange , int fadeInRate , int fadeOutRate , void * eaxSetting )
{
	fprintf_s( logfile , "%s\n" , "CreateSoundmy" );
	fflush( logfile );

	HSOUND retvalue = GAME_CreateSoundold( fileName , looping , is3D , stopwhenoutofrange , fadeInRate , fadeOutRate , eaxSetting );
	fprintf_s( logfile , "%s:[-->GAME_CreateSound<--  fileName: \"%s\" looping: %s is3D: %s stopwhenoutofrange: %s fadeInRate: %i fadeOutRate: %i eaxSetting: \"%s\"] RETURN-> %X\n" , currentDateTime( ).c_str( ) , jassgetchar( fileName ) , looping ? "TRUE" : "FALSE" , is3D ? "TRUE" : "FALSE" , stopwhenoutofrange ? "TRUE" : "FALSE" , fadeInRate , fadeOutRate , jassgetchar( eaxSetting ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HSOUND( __cdecl *GAME_CreateSoundFilenameWithLabel )( void * fileName , BOOL looping , BOOL is3D , BOOL stopwhenoutofrange , int fadeInRate , int fadeOutRate , void * SLKEntryName );
GAME_CreateSoundFilenameWithLabel GAME_CreateSoundFilenameWithLabelorg = NULL;
GAME_CreateSoundFilenameWithLabel GAME_CreateSoundFilenameWithLabelold = NULL;

HSOUND __cdecl GAME_CreateSoundFilenameWithLabelmy( void * fileName , BOOL looping , BOOL is3D , BOOL stopwhenoutofrange , int fadeInRate , int fadeOutRate , void * SLKEntryName )
{
	fprintf_s( logfile , "%s" , "CreateSoundFilenameWithLabelmy\n" );
	fflush( logfile );

	HSOUND retvalue = GAME_CreateSoundFilenameWithLabelold( fileName , looping , is3D , stopwhenoutofrange , fadeInRate , fadeOutRate , SLKEntryName );
	fprintf_s( logfile , "%s:[-->GAME_CreateSoundFilenameWithLabel<--  fileName: \"%s\" looping: %s is3D: %s stopwhenoutofrange: %s fadeInRate: %i fadeOutRate: %i SLKEntryName: \"%s\"] RETURN-> %X\n" , currentDateTime( ).c_str( ) , jassgetchar( fileName ) , looping ? "TRUE" : "FALSE" , is3D ? "TRUE" : "FALSE" , stopwhenoutofrange ? "TRUE" : "FALSE" , fadeInRate , fadeOutRate , jassgetchar( SLKEntryName ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HSOUND( __cdecl *GAME_CreateSoundFromLabel )( void * soundLabel , BOOL looping , BOOL is3D , BOOL stopwhenoutofrange , int fadeInRate , int fadeOutRate );
GAME_CreateSoundFromLabel GAME_CreateSoundFromLabelorg = NULL;
GAME_CreateSoundFromLabel GAME_CreateSoundFromLabelold = NULL;

HSOUND __cdecl GAME_CreateSoundFromLabelmy( void * soundLabel , BOOL looping , BOOL is3D , BOOL stopwhenoutofrange , int fadeInRate , int fadeOutRate )
{
	fprintf_s( logfile , "%s" , "CreateSoundFromLabelmy\n" );
	fflush( logfile );

	HSOUND retvalue = GAME_CreateSoundFromLabelold( soundLabel , looping , is3D , stopwhenoutofrange , fadeInRate , fadeOutRate );
	fprintf_s( logfile , "%s:[-->GAME_CreateSoundFromLabel<--  soundLabel: \"%s\" looping: %s is3D: %s stopwhenoutofrange: %s fadeInRate: %i fadeOutRate: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , jassgetchar( soundLabel ) , looping ? "TRUE" : "FALSE" , is3D ? "TRUE" : "FALSE" , stopwhenoutofrange ? "TRUE" : "FALSE" , fadeInRate , fadeOutRate , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTEXTTAG( __cdecl *GAME_CreateTextTag )( );
GAME_CreateTextTag GAME_CreateTextTagorg = NULL;
GAME_CreateTextTag GAME_CreateTextTagold = NULL;

HTEXTTAG __cdecl GAME_CreateTextTagmy( )
{
	fprintf_s( logfile , "%s" , "CreateTextTagmy\n" );
	fflush( logfile );

	HTEXTTAG retvalue = GAME_CreateTextTagold( );
	fprintf_s( logfile , "%s:[-->GAME_CreateTextTag<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTIMER( __cdecl *GAME_CreateTimer )( );
GAME_CreateTimer GAME_CreateTimerorg = NULL;
GAME_CreateTimer GAME_CreateTimerold = NULL;

HTIMER __cdecl GAME_CreateTimermy( )
{
	fprintf_s( logfile , "%s\n" , "CreateTimermy" );
	fflush( logfile );

	HTIMER retvalue = GAME_CreateTimerold( );
	fprintf_s( logfile , "%s:[-->GAME_CreateTimer<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTIMERDIALOG( __cdecl *GAME_CreateTimerDialog )( HTIMER t );
GAME_CreateTimerDialog GAME_CreateTimerDialogorg = NULL;
GAME_CreateTimerDialog GAME_CreateTimerDialogold = NULL;

HTIMERDIALOG __cdecl GAME_CreateTimerDialogmy( HTIMER t )
{
	fprintf_s( logfile , "%s\n" , "CreateTimerDialogmy" );
	fflush( logfile );

	HTIMERDIALOG retvalue = GAME_CreateTimerDialogold( t );
	fprintf_s( logfile , "%s:[-->GAME_CreateTimerDialog<--  t: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , t , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTRACKABLE( __cdecl *GAME_CreateTrackable )( void * trackableModelPath , float *x , float *y , float *facing );
GAME_CreateTrackable GAME_CreateTrackableorg = NULL;
GAME_CreateTrackable GAME_CreateTrackableold = NULL;

HTRACKABLE __cdecl GAME_CreateTrackablemy( void * trackableModelPath , float *x , float *y , float *facing )
{
	fprintf_s( logfile , "%s\n" , "CreateTrackablemy" );
	fflush( logfile );

	HTRACKABLE retvalue = GAME_CreateTrackableold( trackableModelPath , x , y , facing );
	fprintf_s( logfile , "%s:[-->GAME_CreateTrackable<--  trackableModelPath: \"%s\" x: %f y: %f facing: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , jassgetchar( trackableModelPath ) , *( float * ) x , *( float * ) y , *( float * ) facing , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTRIGGER( __cdecl *GAME_CreateTrigger )( );
GAME_CreateTrigger GAME_CreateTriggerorg = NULL;
GAME_CreateTrigger GAME_CreateTriggerold = NULL;

HTRIGGER __cdecl GAME_CreateTriggermy( )
{
	fprintf_s( logfile , "%s" , "CreateTriggermy\n" );
	fflush( logfile );

	HTRIGGER retvalue = GAME_CreateTriggerold( );
	fprintf_s( logfile , "%s:[-->GAME_CreateTrigger<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUBERSPLAT( __cdecl *GAME_CreateUbersplat )( float *x , float *y , void * name , int red , int green , int blue , int alpha , BOOL forcePaused , BOOL noBirthTime );
GAME_CreateUbersplat GAME_CreateUbersplatorg = NULL;
GAME_CreateUbersplat GAME_CreateUbersplatold = NULL;

HUBERSPLAT __cdecl GAME_CreateUbersplatmy( float *x , float *y , void * name , int red , int green , int blue , int alpha , BOOL forcePaused , BOOL noBirthTime )
{
	fprintf_s( logfile , "%s\n" , "CreateUbersplatmy" );
	fflush( logfile );

	HUBERSPLAT retvalue = GAME_CreateUbersplatold( x , y , name , red , green , blue , alpha , forcePaused , noBirthTime );
	fprintf_s( logfile , "%s:[-->GAME_CreateUbersplat<--  x: %f y: %f name: \"%s\" red: %i green: %i blue: %i alpha: %i forcePaused: %s noBirthTime: %s] RETURN-> %X\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , jassgetchar( name ) , red , green , blue , alpha , forcePaused ? "TRUE" : "FALSE" , noBirthTime ? "TRUE" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_CreateUnit )( HPLAYER id , int unitid , float *x , float *y , float *face );
GAME_CreateUnit GAME_CreateUnitorg = NULL;
GAME_CreateUnit GAME_CreateUnitold = NULL;

HUNIT __cdecl GAME_CreateUnitmy( HPLAYER id , int unitid , float *x , float *y , float *face )
{
	fprintf_s( logfile , "%s" , "CreateUnitmy\n" );
	fflush( logfile );

	HUNIT retvalue = GAME_CreateUnitold( id , unitid , x , y , face );
	fprintf_s( logfile , "%s:[-->GAME_CreateUnit<--  id: %X unitid: %i x: %f y: %f face: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , id , unitid , *( float * ) x , *( float * ) y , *( float * ) face , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_CreateUnitAtLoc )( HPLAYER id , int unitid , HLOCATION whichLocation , float *face );
GAME_CreateUnitAtLoc GAME_CreateUnitAtLocorg = NULL;
GAME_CreateUnitAtLoc GAME_CreateUnitAtLocold = NULL;

HUNIT __cdecl GAME_CreateUnitAtLocmy( HPLAYER id , int unitid , HLOCATION whichLocation , float *face )
{
	fprintf_s( logfile , "%s\n" , "CreateUnitAtLocmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_CreateUnitAtLocold( id , unitid , whichLocation , face );
	fprintf_s( logfile , "%s:[-->GAME_CreateUnitAtLoc<--  id: %X unitid: %i whichLocation: %X face: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , id , unitid , whichLocation , *( float * ) face , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_CreateUnitAtLocByName )( HPLAYER id , void * unitname , HLOCATION whichLocation , float *face );
GAME_CreateUnitAtLocByName GAME_CreateUnitAtLocByNameorg = NULL;
GAME_CreateUnitAtLocByName GAME_CreateUnitAtLocByNameold = NULL;

HUNIT __cdecl GAME_CreateUnitAtLocByNamemy( HPLAYER id , void * unitname , HLOCATION whichLocation , float *face )
{
	fprintf_s( logfile , "%s\n" , "CreateUnitAtLocByNamemy" );
	fflush( logfile );

	HUNIT retvalue = GAME_CreateUnitAtLocByNameold( id , unitname , whichLocation , face );
	fprintf_s( logfile , "%s:[-->GAME_CreateUnitAtLocByName<--  id: %X unitname: \"%s\" whichLocation: %X face: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , id , jassgetchar( unitname ) , whichLocation , *( float * ) face , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_CreateUnitByName )( HPLAYER whichPlayer , void * unitname , float *x , float *y , float *face );
GAME_CreateUnitByName GAME_CreateUnitByNameorg = NULL;
GAME_CreateUnitByName GAME_CreateUnitByNameold = NULL;

HUNIT __cdecl GAME_CreateUnitByNamemy( HPLAYER whichPlayer , void * unitname , float *x , float *y , float *face )
{
	fprintf_s( logfile , "%s" , "CreateUnitByNamemy\n" );
	fflush( logfile );

	HUNIT retvalue = GAME_CreateUnitByNameold( whichPlayer , unitname , x , y , face );
	fprintf_s( logfile , "%s:[-->GAME_CreateUnitByName<--  whichPlayer: %X unitname: \"%s\" x: %f y: %f face: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichPlayer , jassgetchar( unitname ) , *( float * ) x , *( float * ) y , *( float * ) face , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNITPOOL( __cdecl *GAME_CreateUnitPool )( );
GAME_CreateUnitPool GAME_CreateUnitPoolorg = NULL;
GAME_CreateUnitPool GAME_CreateUnitPoolold = NULL;

HUNITPOOL __cdecl GAME_CreateUnitPoolmy( )
{
	fprintf_s( logfile , "%s" , "CreateUnitPoolmy\n" );
	fflush( logfile );

	HUNITPOOL retvalue = GAME_CreateUnitPoolold( );
	fprintf_s( logfile , "%s:[-->GAME_CreateUnitPool<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_CreepsOnMap )( );
GAME_CreepsOnMap GAME_CreepsOnMaporg = NULL;
GAME_CreepsOnMap GAME_CreepsOnMapold = NULL;

BOOL __cdecl GAME_CreepsOnMapmy( )
{
	fprintf_s( logfile , "%s\n" , "CreepsOnMapmy" );
	fflush( logfile );

	BOOL retvalue = GAME_CreepsOnMapold( );
	fprintf_s( logfile , "%s:[-->GAME_CreepsOnMap<-- ] RETURN-> %s\n" , currentDateTime( ).c_str( ) , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_CripplePlayer )( HPLAYER whichPlayer , HFORCE toWhichPlayers , BOOL flag );
GAME_CripplePlayer GAME_CripplePlayerorg = NULL;
GAME_CripplePlayer GAME_CripplePlayerold = NULL;

void __cdecl GAME_CripplePlayermy( HPLAYER whichPlayer , HFORCE toWhichPlayers , BOOL flag )
{
	fprintf_s( logfile , "%s" , "CripplePlayermy\n" );
	fflush( logfile );

	GAME_CripplePlayerold( whichPlayer , toWhichPlayers , flag );
	fprintf_s( logfile , "%s:[-->GAME_CripplePlayer<--  whichPlayer: %X toWhichPlayers: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , toWhichPlayers , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DebugBreak )( int arg1 );
GAME_DebugBreak GAME_DebugBreakorg = NULL;
GAME_DebugBreak GAME_DebugBreakold = NULL;

void __cdecl GAME_DebugBreakmy( int arg1 )
{
	fprintf_s( logfile , "%s" , "DebugBreakmy\n" );
	fflush( logfile );

	GAME_DebugBreakold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_DebugBreak<--  arg1: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DebugFI )( void * arg1 , int arg2 );
GAME_DebugFI GAME_DebugFIorg = NULL;
GAME_DebugFI GAME_DebugFIold = NULL;

void __cdecl GAME_DebugFImy( void * arg1 , int arg2 )
{
	fprintf_s( logfile , "%s\n" , "DebugFImy" );
	fflush( logfile );

	GAME_DebugFIold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_DebugFI<--  arg1: \"%s\" arg2: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( arg1 ) , arg2 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DebugS )( void * arg1 );
GAME_DebugS GAME_DebugSorg = NULL;
GAME_DebugS GAME_DebugSold = NULL;

void __cdecl GAME_DebugSmy( void * arg1 )
{
	fprintf_s( logfile , "%s" , "DebugSmy\n" );
	fflush( logfile );

	GAME_DebugSold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_DebugS<--  arg1: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( arg1 ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DebugUnitID )( void * arg1 , int arg2 );
GAME_DebugUnitID GAME_DebugUnitIDorg = NULL;
GAME_DebugUnitID GAME_DebugUnitIDold = NULL;

void __cdecl GAME_DebugUnitIDmy( void * arg1 , int arg2 )
{
	fprintf_s( logfile , "%s" , "DebugUnitIDmy\n" );
	fflush( logfile );

	GAME_DebugUnitIDold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_DebugUnitID<--  arg1: \"%s\" arg2: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( arg1 ) , arg2 );
	fflush( logfile );

}


typedef int( __cdecl *GAME_FastError )( int a1 , int a2 );
GAME_FastError GAME_FastErrororg = NULL;
GAME_FastError GAME_FastErrorold = NULL;

int __cdecl GAME_FastErrormy( int a1 , int a2 )
{
	fprintf_s( logfile , "%s" , "FastErrormy\n" );
	fflush( logfile );

	int retvalue = GAME_FastErrorold( a1 , a2 );
	fprintf_s( logfile , "%s:[-->GAME_FastError<--  a1: %i a2: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , a1 , a2 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_Ordinal578 )( int a1 , size_t a2 , const char *Format , char a4 );
GAME_Ordinal578 GAME_Ordinal578org = NULL;
GAME_Ordinal578 GAME_Ordinal578old = NULL;

int __cdecl GAME_Ordinal578my( int a1 , size_t a2 , const char *Format , char a4 )
{
	fprintf_s( logfile , "%s\n" , "Ordinal578my" );
	fflush( logfile );

	int retvalue = GAME_Ordinal578old( a1 , a2 , Format , a4 );
	fprintf_s( logfile , "%s:[-->GAME_Ordinal578<--  a1: %i a2: %X Format: %X a4: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , a1 , a2 , *( const char * ) Format , a4 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_Ordinal289 )( int a1 , int a2 , char a3 );
GAME_Ordinal289 GAME_Ordinal289org = NULL;
GAME_Ordinal289 GAME_Ordinal289old = NULL;

int __cdecl GAME_Ordinal289my( int a1 , int a2 , char a3 )
{
	fprintf_s( logfile , "%s\n" , "Ordinal289my" );
	fflush( logfile );

	int retvalue = GAME_Ordinal289old( a1 , a2 , a3 );
	fprintf_s( logfile , "%s:[-->GAME_Ordinal289<--  a1: %i a2: %i a3: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , a1 , a2 , a3 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_sub_10006020 )( );
GAME_sub_10006020 GAME_sub_10006020org = NULL;
GAME_sub_10006020 GAME_sub_10006020old = NULL;

int __cdecl GAME_sub_10006020my( )
{
	fprintf_s( logfile , "%s\n" , "sub_10006020my" );
	fflush( logfile );

	int retvalue = GAME_sub_10006020old( );
	fprintf_s( logfile , "%s:[-->GAME_sub_10006020<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_reconnect1 )( int a1 );
GAME_reconnect1 GAME_reconnect1org = NULL;
GAME_reconnect1 GAME_reconnect1old = NULL;

void __cdecl GAME_reconnect1my( int a1 )
{
	fprintf_s( logfile , "%s\n" , "reconnect1my" );
	fflush( logfile );

	GAME_reconnect1old( a1 );
	fprintf_s( logfile , "%s:[-->GAME_reconnect1<--  a1: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , a1 );
	fflush( logfile );

}


typedef int( __cdecl *GAME_DllMainRECO )( LPVOID lpParameter , DWORD ThreadId , int a3 );
GAME_DllMainRECO GAME_DllMainRECOorg = NULL;
GAME_DllMainRECO GAME_DllMainRECOold = NULL;

int __cdecl GAME_DllMainRECOmy( LPVOID lpParameter , DWORD ThreadId , int a3 )
{
	fprintf_s( logfile , "%s\n" , "DllMainRECOmy" );
	fflush( logfile );

	int retvalue = GAME_DllMainRECOold( lpParameter , ThreadId , a3 );
	fprintf_s( logfile , "%s:[-->GAME_DllMainRECO<--  lpParameter: %X ThreadId: %X a3: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , lpParameter , ThreadId , a3 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_sub_6F4CBF60 )( int a1 , int a2 );
GAME_sub_6F4CBF60 GAME_sub_6F4CBF60org = NULL;
GAME_sub_6F4CBF60 GAME_sub_6F4CBF60old = NULL;

int __cdecl GAME_sub_6F4CBF60my( int a1 , int a2 )
{
	fprintf_s( logfile , "%s\n" , "sub_6F4CBF60my" );
	fflush( logfile );

	int retvalue = GAME_sub_6F4CBF60old( a1 , a2 );
	fprintf_s( logfile , "%s:[-->GAME_sub_6F4CBF60<--  a1: %i a2: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , a1 , a2 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_VersionGM )( int a1 , int a2 );
GAME_VersionGM GAME_VersionGMorg = NULL;
GAME_VersionGM GAME_VersionGMold = NULL;

int __cdecl GAME_VersionGMmy( int a1 , int a2 )
{
	fprintf_s( logfile , "%s\n" , "VersionGMmy" );
	fflush( logfile );

	int retvalue = GAME_VersionGMold( a1 , a2 );
	fprintf_s( logfile , "%s:[-->GAME_VersionGM<--  a1: %i a2: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , a1 , a2 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_CreateGameMessage )( int a1 , int a2 , int a3 );
GAME_CreateGameMessage GAME_CreateGameMessageorg = NULL;
GAME_CreateGameMessage GAME_CreateGameMessageold = NULL;

int __cdecl GAME_CreateGameMessagemy( int a1 , int a2 , int a3 )
{
	fprintf_s( logfile , "%s\n" , "CreateGameMessagemy" );
	fflush( logfile );

	int retvalue = GAME_CreateGameMessageold( a1 , a2 , a3 );
	fprintf_s( logfile , "%s:[-->GAME_CreateGameMessage<--  a1: %i a2: %i a3: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , a1 , a2 , a3 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_BeforeSendMessage2 )( );
GAME_BeforeSendMessage2 GAME_BeforeSendMessage2org = NULL;
GAME_BeforeSendMessage2 GAME_BeforeSendMessage2old = NULL;

int __cdecl GAME_BeforeSendMessage2my( )
{
	fprintf_s( logfile , "%s\n" , "BeforeSendMessage2my" );
	fflush( logfile );

	int retvalue = GAME_BeforeSendMessage2old( );
	fprintf_s( logfile , "%s:[-->GAME_BeforeSendMessage2<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_CreateGameDefaultBNETErrorMessage )( int a1 , double a2 , int a3 );
GAME_CreateGameDefaultBNETErrorMessage GAME_CreateGameDefaultBNETErrorMessageorg = NULL;
GAME_CreateGameDefaultBNETErrorMessage GAME_CreateGameDefaultBNETErrorMessageold = NULL;

int __cdecl GAME_CreateGameDefaultBNETErrorMessagemy( int a1 , double a2 , int a3 )
{
	fprintf_s( logfile , "%s\n" , "CreateGameDefaultBNETErrorMessagemy" );
	fflush( logfile );

	int retvalue = GAME_CreateGameDefaultBNETErrorMessageold( a1 , a2 , a3 );
	fprintf_s( logfile , "%s:[-->GAME_CreateGameDefaultBNETErrorMessage<--  a1: %i a2: %X a3: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , a1 , a2 , a3 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_BeforeSendMessage )( );
GAME_BeforeSendMessage GAME_BeforeSendMessageorg = NULL;
GAME_BeforeSendMessage GAME_BeforeSendMessageold = NULL;

void __cdecl GAME_BeforeSendMessagemy( )
{
	fprintf_s( logfile , "%s\n" , "BeforeSendMessagemy" );
	fflush( logfile );

	GAME_BeforeSendMessageold( );
	fprintf_s( logfile , "%s:[-->GAME_BeforeSendMessage<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ShowGameMessage )( int a1 , signed int a2 , double a3 , int a4 , int a5 , int a6 , int a7 , int a8 );
GAME_ShowGameMessage GAME_ShowGameMessageorg = NULL;
GAME_ShowGameMessage GAME_ShowGameMessageold = NULL;

void __cdecl GAME_ShowGameMessagemy( int a1 , signed int a2 , double a3 , int a4 , int a5 , int a6 , int a7 , int a8 )
{
	fprintf_s( logfile , "%s\n" , "ShowGameMessagemy" );
	fflush( logfile );

	GAME_ShowGameMessageold( a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 );
	fprintf_s( logfile , "%s:[-->GAME_ShowGameMessage<--  a1: %i a2: %i a3: %X a4: %i a5: %i a6: %i a7: %i a8: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 );
	fflush( logfile );

}


typedef int( __cdecl *GAME_DecUnitAbilityLevel )( HUNIT whichUnit , int abilcode );
GAME_DecUnitAbilityLevel GAME_DecUnitAbilityLevelorg = NULL;
GAME_DecUnitAbilityLevel GAME_DecUnitAbilityLevelold = NULL;

int __cdecl GAME_DecUnitAbilityLevelmy( HUNIT whichUnit , int abilcode )
{
	fprintf_s( logfile , "%s\n" , "DecUnitAbilityLevelmy" );
	fflush( logfile );

	int retvalue = GAME_DecUnitAbilityLevelold( whichUnit , abilcode );
	fprintf_s( logfile , "%s:[-->GAME_DecUnitAbilityLevel<--  whichUnit: %X abilcode: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichUnit , abilcode , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_DefeatConditionSetDescription )( HDEFEATCONDITION whichCondition , void * description );
GAME_DefeatConditionSetDescription GAME_DefeatConditionSetDescriptionorg = NULL;
GAME_DefeatConditionSetDescription GAME_DefeatConditionSetDescriptionold = NULL;

void __cdecl GAME_DefeatConditionSetDescriptionmy( HDEFEATCONDITION whichCondition , void * description )
{
	fprintf_s( logfile , "%s\n" , "DefeatConditionSetDescriptionmy" );
	fflush( logfile );

	GAME_DefeatConditionSetDescriptionold( whichCondition , description );
	fprintf_s( logfile , "%s:[-->GAME_DefeatConditionSetDescription<--  whichCondition: %X description: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichCondition , jassgetchar( description ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DefineStartLocation )( int whichStartLoc , float *x , float *y );
GAME_DefineStartLocation GAME_DefineStartLocationorg = NULL;
GAME_DefineStartLocation GAME_DefineStartLocationold = NULL;

void __cdecl GAME_DefineStartLocationmy( int whichStartLoc , float *x , float *y )
{
	fprintf_s( logfile , "%s" , "DefineStartLocationmy\n" );
	fflush( logfile );

	GAME_DefineStartLocationold( whichStartLoc , x , y );
	fprintf_s( logfile , "%s:[-->GAME_DefineStartLocation<--  whichStartLoc: %i x: %f y: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichStartLoc , *( float * ) x , *( float * ) y );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DefineStartLocationLoc )( int whichStartLoc , HLOCATION whichLocation );
GAME_DefineStartLocationLoc GAME_DefineStartLocationLocorg = NULL;
GAME_DefineStartLocationLoc GAME_DefineStartLocationLocold = NULL;

void __cdecl GAME_DefineStartLocationLocmy( int whichStartLoc , HLOCATION whichLocation )
{
	fprintf_s( logfile , "%s\n" , "DefineStartLocationLocmy" );
	fflush( logfile );

	GAME_DefineStartLocationLocold( whichStartLoc , whichLocation );
	fprintf_s( logfile , "%s:[-->GAME_DefineStartLocationLoc<--  whichStartLoc: %i whichLocation: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichStartLoc , whichLocation );
	fflush( logfile );

}


typedef DWFP( __cdecl *GAME_Deg2Rad )( float *degrees );
GAME_Deg2Rad GAME_Deg2Radorg = NULL;
GAME_Deg2Rad GAME_Deg2Radold = NULL;

DWFP __cdecl GAME_Deg2Radmy( float *degrees )
{
	fprintf_s( logfile , "%s\n" , "Deg2Radmy" );
	fflush( logfile );

	DWFP retvalue = GAME_Deg2Radold( degrees );
	fprintf_s( logfile , "%s:[-->GAME_Deg2Rad<--  degrees: %f] RETURN-> %f\n" , currentDateTime( ).c_str( ) , *( float * ) degrees , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_DestroyBOOLExpr )( HBOOLEXPR e );
GAME_DestroyBOOLExpr GAME_DestroyBOOLExprorg = NULL;
GAME_DestroyBOOLExpr GAME_DestroyBOOLExprold = NULL;

void __cdecl GAME_DestroyBOOLExprmy( HBOOLEXPR e )
{
	fprintf_s( logfile , "%s\n" , "DestroyBOOLExprmy" );
	fflush( logfile );

	GAME_DestroyBOOLExprold( e );
	fprintf_s( logfile , "%s:[-->GAME_DestroyBOOLExpr<--  e: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , e );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DestroyCondition )( HCONDITIONFUNC c );
GAME_DestroyCondition GAME_DestroyConditionorg = NULL;
GAME_DestroyCondition GAME_DestroyConditionold = NULL;

void __cdecl GAME_DestroyConditionmy( HCONDITIONFUNC c )
{
	fprintf_s( logfile , "%s\n" , "DestroyConditionmy" );
	fflush( logfile );

	GAME_DestroyConditionold( c );
	fprintf_s( logfile , "%s:[-->GAME_DestroyCondition<--  c: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , c );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DestroyDefeatCondition )( HDEFEATCONDITION whichCondition );
GAME_DestroyDefeatCondition GAME_DestroyDefeatConditionorg = NULL;
GAME_DestroyDefeatCondition GAME_DestroyDefeatConditionold = NULL;

void __cdecl GAME_DestroyDefeatConditionmy( HDEFEATCONDITION whichCondition )
{
	fprintf_s( logfile , "%s\n" , "DestroyDefeatConditionmy" );
	fflush( logfile );

	GAME_DestroyDefeatConditionold( whichCondition );
	fprintf_s( logfile , "%s:[-->GAME_DestroyDefeatCondition<--  whichCondition: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichCondition );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DestroyEffect )( HEFFECT whichEffect );
GAME_DestroyEffect GAME_DestroyEffectorg = NULL;
GAME_DestroyEffect GAME_DestroyEffectold = NULL;

void __cdecl GAME_DestroyEffectmy( HEFFECT whichEffect )
{
	fprintf_s( logfile , "%s\n" , "DestroyEffectmy" );
	fflush( logfile );

	GAME_DestroyEffectold( whichEffect );
	fprintf_s( logfile , "%s:[-->GAME_DestroyEffect<--  whichEffect: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichEffect );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DestroyFilter )( HFILTERFUNC f );
GAME_DestroyFilter GAME_DestroyFilterorg = NULL;
GAME_DestroyFilter GAME_DestroyFilterold = NULL;

void __cdecl GAME_DestroyFiltermy( HFILTERFUNC f )
{
	fprintf_s( logfile , "%s\n" , "DestroyFiltermy" );
	fflush( logfile );

	GAME_DestroyFilterold( f );
	fprintf_s( logfile , "%s:[-->GAME_DestroyFilter<--  f: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , f );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DestroyFogModifier )( HFOGMODIFIER whichFogModifier );
GAME_DestroyFogModifier GAME_DestroyFogModifierorg = NULL;
GAME_DestroyFogModifier GAME_DestroyFogModifierold = NULL;

void __cdecl GAME_DestroyFogModifiermy( HFOGMODIFIER whichFogModifier )
{
	fprintf_s( logfile , "%s\n" , "DestroyFogModifiermy" );
	fflush( logfile );

	GAME_DestroyFogModifierold( whichFogModifier );
	fprintf_s( logfile , "%s:[-->GAME_DestroyFogModifier<--  whichFogModifier: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichFogModifier );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DestroyForce )( HFORCE whichForce );
GAME_DestroyForce GAME_DestroyForceorg = NULL;
GAME_DestroyForce GAME_DestroyForceold = NULL;

void __cdecl GAME_DestroyForcemy( HFORCE whichForce )
{
	fprintf_s( logfile , "%s\n" , "DestroyForcemy" );
	fflush( logfile );

	GAME_DestroyForceold( whichForce );
	fprintf_s( logfile , "%s:[-->GAME_DestroyForce<--  whichForce: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichForce );
	fflush( logfile );

}


typedef int( __cdecl *GAME_DebugTerrainCONSOLE )( );
GAME_DebugTerrainCONSOLE GAME_DebugTerrainCONSOLEorg = NULL;
GAME_DebugTerrainCONSOLE GAME_DebugTerrainCONSOLEold = NULL;

int __cdecl GAME_DebugTerrainCONSOLEmy( )
{
	fprintf_s( logfile , "%s\n" , "DebugTerrainCONSOLEmy" );
	fflush( logfile );

	int retvalue = GAME_DebugTerrainCONSOLEold( );
	fprintf_s( logfile , "%s:[-->GAME_DebugTerrainCONSOLE<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_DebugTerrainFILE )( );
GAME_DebugTerrainFILE GAME_DebugTerrainFILEorg = NULL;
GAME_DebugTerrainFILE GAME_DebugTerrainFILEold = NULL;

int __cdecl GAME_DebugTerrainFILEmy( )
{
	fprintf_s( logfile , "%s\n" , "DebugTerrainFILEmy" );
	fflush( logfile );

	int retvalue = GAME_DebugTerrainFILEold( );
	fprintf_s( logfile , "%s:[-->GAME_DebugTerrainFILE<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_DestroyGroup )( HGROUP whichGroup );
GAME_DestroyGroup GAME_DestroyGrouporg = NULL;
GAME_DestroyGroup GAME_DestroyGroupold = NULL;

void __cdecl GAME_DestroyGroupmy( HGROUP whichGroup )
{
	fprintf_s( logfile , "%s\n" , "DestroyGroupmy" );
	fflush( logfile );

	GAME_DestroyGroupold( whichGroup );
	fprintf_s( logfile , "%s:[-->GAME_DestroyGroup<--  whichGroup: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichGroup );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DestroyImage )( HIMAGE whichImage );
GAME_DestroyImage GAME_DestroyImageorg = NULL;
GAME_DestroyImage GAME_DestroyImageold = NULL;

void __cdecl GAME_DestroyImagemy( HIMAGE whichImage )
{
	fprintf_s( logfile , "%s\n" , "DestroyImagemy" );
	fflush( logfile );

	GAME_DestroyImageold( whichImage );
	fprintf_s( logfile , "%s:[-->GAME_DestroyImage<--  whichImage: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichImage );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DestroyItemPool )( HITEMPOOL whichItemPool );
GAME_DestroyItemPool GAME_DestroyItemPoolorg = NULL;
GAME_DestroyItemPool GAME_DestroyItemPoolold = NULL;

void __cdecl GAME_DestroyItemPoolmy( HITEMPOOL whichItemPool )
{
	fprintf_s( logfile , "%s\n" , "DestroyItemPoolmy" );
	fflush( logfile );

	GAME_DestroyItemPoolold( whichItemPool );
	fprintf_s( logfile , "%s:[-->GAME_DestroyItemPool<--  whichItemPool: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichItemPool );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DestroyLeaderboard )( HLEADERBOARD lb );
GAME_DestroyLeaderboard GAME_DestroyLeaderboardorg = NULL;
GAME_DestroyLeaderboard GAME_DestroyLeaderboardold = NULL;

void __cdecl GAME_DestroyLeaderboardmy( HLEADERBOARD lb )
{
	fprintf_s( logfile , "%s\n" , "DestroyLeaderboardmy" );
	fflush( logfile );

	GAME_DestroyLeaderboardold( lb );
	fprintf_s( logfile , "%s:[-->GAME_DestroyLeaderboard<--  lb: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_DestroyLightning )( HLIGHTNING whichBolt );
GAME_DestroyLightning GAME_DestroyLightningorg = NULL;
GAME_DestroyLightning GAME_DestroyLightningold = NULL;

BOOL __cdecl GAME_DestroyLightningmy( HLIGHTNING whichBolt )
{
	fprintf_s( logfile , "%s\n" , "DestroyLightningmy" );
	fflush( logfile );

	BOOL retvalue = GAME_DestroyLightningold( whichBolt );
	fprintf_s( logfile , "%s:[-->GAME_DestroyLightning<--  whichBolt: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichBolt , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_DestroyMultiboard )( HMULTIBOARD lb );
GAME_DestroyMultiboard GAME_DestroyMultiboardorg = NULL;
GAME_DestroyMultiboard GAME_DestroyMultiboardold = NULL;

void __cdecl GAME_DestroyMultiboardmy( HMULTIBOARD lb )
{
	fprintf_s( logfile , "%s" , "DestroyMultiboardmy\n" );
	fflush( logfile );

	GAME_DestroyMultiboardold( lb );
	fprintf_s( logfile , "%s:[-->GAME_DestroyMultiboard<--  lb: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DestroyQuest )( HQUEST whichQuest );
GAME_DestroyQuest GAME_DestroyQuestorg = NULL;
GAME_DestroyQuest GAME_DestroyQuestold = NULL;

void __cdecl GAME_DestroyQuestmy( HQUEST whichQuest )
{
	fprintf_s( logfile , "%s\n" , "DestroyQuestmy" );
	fflush( logfile );

	GAME_DestroyQuestold( whichQuest );
	fprintf_s( logfile , "%s:[-->GAME_DestroyQuest<--  whichQuest: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichQuest );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DestroyTextTag )( HTEXTTAG t );
GAME_DestroyTextTag GAME_DestroyTextTagorg = NULL;
GAME_DestroyTextTag GAME_DestroyTextTagold = NULL;

void __cdecl GAME_DestroyTextTagmy( HTEXTTAG t )
{
	fprintf_s( logfile , "%s\n" , "DestroyTextTagmy" );
	fflush( logfile );

	GAME_DestroyTextTagold( t );
	fprintf_s( logfile , "%s:[-->GAME_DestroyTextTag<--  t: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , t );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DestroyTimer )( HTIMER whichTimer );
GAME_DestroyTimer GAME_DestroyTimerorg = NULL;
GAME_DestroyTimer GAME_DestroyTimerold = NULL;

void __cdecl GAME_DestroyTimermy( HTIMER whichTimer )
{
	fprintf_s( logfile , "%s\n" , "DestroyTimermy" );
	fflush( logfile );

	GAME_DestroyTimerold( whichTimer );
	fprintf_s( logfile , "%s:[-->GAME_DestroyTimer<--  whichTimer: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichTimer );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DestroyTimerDialog )( HTIMERDIALOG whichDialog );
GAME_DestroyTimerDialog GAME_DestroyTimerDialogorg = NULL;
GAME_DestroyTimerDialog GAME_DestroyTimerDialogold = NULL;

void __cdecl GAME_DestroyTimerDialogmy( HTIMERDIALOG whichDialog )
{
	fprintf_s( logfile , "%s\n" , "DestroyTimerDialogmy" );
	fflush( logfile );

	GAME_DestroyTimerDialogold( whichDialog );
	fprintf_s( logfile , "%s:[-->GAME_DestroyTimerDialog<--  whichDialog: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichDialog );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DestroyTrigger )( HTRIGGER whichTrigger );
GAME_DestroyTrigger GAME_DestroyTriggerorg = NULL;
GAME_DestroyTrigger GAME_DestroyTriggerold = NULL;

void __cdecl GAME_DestroyTriggermy( HTRIGGER whichTrigger )
{
	fprintf_s( logfile , "%s\n" , "DestroyTriggermy" );
	fflush( logfile );

	GAME_DestroyTriggerold( whichTrigger );
	fprintf_s( logfile , "%s:[-->GAME_DestroyTrigger<--  whichTrigger: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichTrigger );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DestroyUbersplat )( HUBERSPLAT whichSplat );
GAME_DestroyUbersplat GAME_DestroyUbersplatorg = NULL;
GAME_DestroyUbersplat GAME_DestroyUbersplatold = NULL;

void __cdecl GAME_DestroyUbersplatmy( HUBERSPLAT whichSplat )
{
	fprintf_s( logfile , "%s\n" , "DestroyUbersplatmy" );
	fflush( logfile );

	GAME_DestroyUbersplatold( whichSplat );
	fprintf_s( logfile , "%s:[-->GAME_DestroyUbersplat<--  whichSplat: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichSplat );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DestroyUnitPool )( HUNITPOOL whichPool );
GAME_DestroyUnitPool GAME_DestroyUnitPoolorg = NULL;
GAME_DestroyUnitPool GAME_DestroyUnitPoolold = NULL;

void __cdecl GAME_DestroyUnitPoolmy( HUNITPOOL whichPool )
{
	fprintf_s( logfile , "%s\n" , "DestroyUnitPoolmy" );
	fflush( logfile );

	GAME_DestroyUnitPoolold( whichPool );
	fprintf_s( logfile , "%s:[-->GAME_DestroyUnitPool<--  whichPool: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPool );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DestructableRestoreLife )( HDESTRUCTABLE d , float *life , BOOL birth );
GAME_DestructableRestoreLife GAME_DestructableRestoreLifeorg = NULL;
GAME_DestructableRestoreLife GAME_DestructableRestoreLifeold = NULL;

void __cdecl GAME_DestructableRestoreLifemy( HDESTRUCTABLE d , float *life , BOOL birth )
{
	fprintf_s( logfile , "%s\n" , "DestructableRestoreLifemy" );
	fflush( logfile );

	GAME_DestructableRestoreLifeold( d , life , birth );
	fprintf_s( logfile , "%s:[-->GAME_DestructableRestoreLife<--  d: %X life: %f birth: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , d , *( float * ) life , birth ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef HBUTTON( __cdecl *GAME_DialogAddButton )( HDIALOG whichDialog , void * buttonText , int hotkey );
GAME_DialogAddButton GAME_DialogAddButtonorg = NULL;
GAME_DialogAddButton GAME_DialogAddButtonold = NULL;

HBUTTON __cdecl GAME_DialogAddButtonmy( HDIALOG whichDialog , void * buttonText , int hotkey )
{
	fprintf_s( logfile , "%s" , "DialogAddButtonmy\n" );
	fflush( logfile );

	HBUTTON retvalue = GAME_DialogAddButtonold( whichDialog , buttonText , hotkey );
	fprintf_s( logfile , "%s:[-->GAME_DialogAddButton<--  whichDialog: %X buttonText: \"%s\" hotkey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichDialog , jassgetchar( buttonText ) , hotkey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HBUTTON( __cdecl *GAME_DialogAddQuitButton )( HDIALOG whichDialog , BOOL doScoreScreen , void * buttonText , int hotkey );
GAME_DialogAddQuitButton GAME_DialogAddQuitButtonorg = NULL;
GAME_DialogAddQuitButton GAME_DialogAddQuitButtonold = NULL;

HBUTTON __cdecl GAME_DialogAddQuitButtonmy( HDIALOG whichDialog , BOOL doScoreScreen , void * buttonText , int hotkey )
{
	fprintf_s( logfile , "%s" , "DialogAddQuitButtonmy\n" );
	fflush( logfile );

	HBUTTON retvalue = GAME_DialogAddQuitButtonold( whichDialog , doScoreScreen , buttonText , hotkey );
	fprintf_s( logfile , "%s:[-->GAME_DialogAddQuitButton<--  whichDialog: %X doScoreScreen: %s buttonText: \"%s\" hotkey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichDialog , doScoreScreen ? "TRUE" : "FALSE" , jassgetchar( buttonText ) , hotkey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_DialogClear )( HDIALOG whichDialog );
GAME_DialogClear GAME_DialogClearorg = NULL;
GAME_DialogClear GAME_DialogClearold = NULL;

void __cdecl GAME_DialogClearmy( HDIALOG whichDialog )
{
	fprintf_s( logfile , "%s" , "DialogClearmy\n" );
	fflush( logfile );

	GAME_DialogClearold( whichDialog );
	fprintf_s( logfile , "%s:[-->GAME_DialogClear<--  whichDialog: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichDialog );
	fflush( logfile );

}


typedef HDIALOG( __cdecl *GAME_DialogCreate )( );
GAME_DialogCreate GAME_DialogCreateorg = NULL;
GAME_DialogCreate GAME_DialogCreateold = NULL;

HDIALOG __cdecl GAME_DialogCreatemy( )
{
	fprintf_s( logfile , "%s\n" , "DialogCreatemy" );
	fflush( logfile );

	HDIALOG retvalue = GAME_DialogCreateold( );
	fprintf_s( logfile , "%s:[-->GAME_DialogCreate<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_DialogDestroy )( HDIALOG whichDialog );
GAME_DialogDestroy GAME_DialogDestroyorg = NULL;
GAME_DialogDestroy GAME_DialogDestroyold = NULL;

void __cdecl GAME_DialogDestroymy( HDIALOG whichDialog )
{
	fprintf_s( logfile , "%s\n" , "DialogDestroymy" );
	fflush( logfile );

	GAME_DialogDestroyold( whichDialog );
	fprintf_s( logfile , "%s:[-->GAME_DialogDestroy<--  whichDialog: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichDialog );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DialogDisplay )( HPLAYER whichPlayer , HDIALOG whichDialog , BOOL flag );
GAME_DialogDisplay GAME_DialogDisplayorg = NULL;
GAME_DialogDisplay GAME_DialogDisplayold = NULL;

void __cdecl GAME_DialogDisplaymy( HPLAYER whichPlayer , HDIALOG whichDialog , BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "DialogDisplaymy" );
	fflush( logfile );

	GAME_DialogDisplayold( whichPlayer , whichDialog , flag );
	fprintf_s( logfile , "%s:[-->GAME_DialogDisplay<--  whichPlayer: %X whichDialog: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , whichDialog , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DialogSetAsync )( HDIALOG arg1 );
GAME_DialogSetAsync GAME_DialogSetAsyncorg = NULL;
GAME_DialogSetAsync GAME_DialogSetAsyncold = NULL;

void __cdecl GAME_DialogSetAsyncmy( HDIALOG arg1 )
{
	fprintf_s( logfile , "%s" , "DialogSetAsyncmy\n" );
	fflush( logfile );

	GAME_DialogSetAsyncold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_DialogSetAsync<--  arg1: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DialogSetMessage )( HDIALOG whichDialog , void * messageText );
GAME_DialogSetMessage GAME_DialogSetMessageorg = NULL;
GAME_DialogSetMessage GAME_DialogSetMessageold = NULL;

void __cdecl GAME_DialogSetMessagemy( HDIALOG whichDialog , void * messageText )
{
	fprintf_s( logfile , "%s\n" , "DialogSetMessagemy" );
	fflush( logfile );

	GAME_DialogSetMessageold( whichDialog , messageText );
	fprintf_s( logfile , "%s:[-->GAME_DialogSetMessage<--  whichDialog: %X messageText: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichDialog , jassgetchar( messageText ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DisablePathing )( );
GAME_DisablePathing GAME_DisablePathingorg = NULL;
GAME_DisablePathing GAME_DisablePathingold = NULL;

void __cdecl GAME_DisablePathingmy( )
{
	fprintf_s( logfile , "%s" , "DisablePathingmy\n" );
	fflush( logfile );

	GAME_DisablePathingold( );
	fprintf_s( logfile , "%s:[-->GAME_DisablePathing<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DisableRestartMission )( BOOL flag );
GAME_DisableRestartMission GAME_DisableRestartMissionorg = NULL;
GAME_DisableRestartMission GAME_DisableRestartMissionold = NULL;

void __cdecl GAME_DisableRestartMissionmy( BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "DisableRestartMissionmy" );
	fflush( logfile );

	GAME_DisableRestartMissionold( flag );
	fprintf_s( logfile , "%s:[-->GAME_DisableRestartMission<--  flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DisableTrigger )( HTRIGGER whichTrigger );
GAME_DisableTrigger GAME_DisableTriggerorg = NULL;
GAME_DisableTrigger GAME_DisableTriggerold = NULL;

void __cdecl GAME_DisableTriggermy( HTRIGGER whichTrigger )
{
	fprintf_s( logfile , "%s" , "DisableTriggermy\n" );
	fflush( logfile );

	GAME_DisableTriggerold( whichTrigger );
	fprintf_s( logfile , "%s:[-->GAME_DisableTrigger<--  whichTrigger: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichTrigger );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DisplayCineFilter )( BOOL flag );
GAME_DisplayCineFilter GAME_DisplayCineFilterorg = NULL;
GAME_DisplayCineFilter GAME_DisplayCineFilterold = NULL;

void __cdecl GAME_DisplayCineFiltermy( BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "DisplayCineFiltermy" );
	fflush( logfile );

	GAME_DisplayCineFilterold( flag );
	fprintf_s( logfile , "%s:[-->GAME_DisplayCineFilter<--  flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DisplayLoadDialog )( );
GAME_DisplayLoadDialog GAME_DisplayLoadDialogorg = NULL;
GAME_DisplayLoadDialog GAME_DisplayLoadDialogold = NULL;

void __cdecl GAME_DisplayLoadDialogmy( )
{
	fprintf_s( logfile , "%s" , "DisplayLoadDialogmy\n" );
	fflush( logfile );

	GAME_DisplayLoadDialogold( );
	fprintf_s( logfile , "%s:[-->GAME_DisplayLoadDialog<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DisplayText )( int arg1 , void * arg2 );
GAME_DisplayText GAME_DisplayTextorg = NULL;
GAME_DisplayText GAME_DisplayTextold = NULL;

void __cdecl GAME_DisplayTextmy( int arg1 , void * arg2 )
{
	fprintf_s( logfile , "%s\n" , "DisplayTextmy" );
	fflush( logfile );

	GAME_DisplayTextold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_DisplayText<--  arg1: %i arg2: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 , jassgetchar( arg2 ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DisplayTextI )( int arg1 , void * arg2 , int arg3 );
GAME_DisplayTextI GAME_DisplayTextIorg = NULL;
GAME_DisplayTextI GAME_DisplayTextIold = NULL;

void __cdecl GAME_DisplayTextImy( int arg1 , void * arg2 , int arg3 )
{
	fprintf_s( logfile , "%s" , "DisplayTextImy\n" );
	fflush( logfile );

	GAME_DisplayTextIold( arg1 , arg2 , arg3 );
	fprintf_s( logfile , "%s:[-->GAME_DisplayTextI<--  arg1: %i arg2: \"%s\" arg3: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 , jassgetchar( arg2 ) , arg3 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DisplayTextII )( int arg1 , void * arg2 , int arg3 , int arg4 );
GAME_DisplayTextII GAME_DisplayTextIIorg = NULL;
GAME_DisplayTextII GAME_DisplayTextIIold = NULL;

void __cdecl GAME_DisplayTextIImy( int arg1 , void * arg2 , int arg3 , int arg4 )
{
	fprintf_s( logfile , "%s" , "DisplayTextIImy\n" );
	fflush( logfile );

	GAME_DisplayTextIIold( arg1 , arg2 , arg3 , arg4 );
	fprintf_s( logfile , "%s:[-->GAME_DisplayTextII<--  arg1: %i arg2: \"%s\" arg3: %i arg4: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 , jassgetchar( arg2 ) , arg3 , arg4 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DisplayTextIII )( int arg1 , void * arg2 , int arg3 , int arg4 , int arg5 );
GAME_DisplayTextIII GAME_DisplayTextIIIorg = NULL;
GAME_DisplayTextIII GAME_DisplayTextIIIold = NULL;

void __cdecl GAME_DisplayTextIIImy( int arg1 , void * arg2 , int arg3 , int arg4 , int arg5 )
{
	fprintf_s( logfile , "%s" , "DisplayTextIIImy\n" );
	fflush( logfile );

	GAME_DisplayTextIIIold( arg1 , arg2 , arg3 , arg4 , arg5 );
	fprintf_s( logfile , "%s:[-->GAME_DisplayTextIII<--  arg1: %i arg2: \"%s\" arg3: %i arg4: %i arg5: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 , jassgetchar( arg2 ) , arg3 , arg4 , arg5 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DisplayTextToPlayer )( HPLAYER toPlayer , float *x , float *y , void * message );
GAME_DisplayTextToPlayer GAME_DisplayTextToPlayerorg = NULL;
GAME_DisplayTextToPlayer GAME_DisplayTextToPlayerold = NULL;

void __cdecl GAME_DisplayTextToPlayermy( HPLAYER toPlayer , float *x , float *y , void * message )
{
	fprintf_s( logfile , "%s" , "DisplayTextToPlayermy\n" );
	fflush( logfile );

	GAME_DisplayTextToPlayerold( toPlayer , x , y , message );
	fprintf_s( logfile , "%s:[-->GAME_DisplayTextToPlayer<--  toPlayer: %X x: %f y: %f message: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , toPlayer , *( float * ) x , *( float * ) y , jassgetchar( message ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DisplayTimedTextFromPlayer )( HPLAYER toPlayer , float *x , float *y , float *duration , void * message );
GAME_DisplayTimedTextFromPlayer GAME_DisplayTimedTextFromPlayerorg = NULL;
GAME_DisplayTimedTextFromPlayer GAME_DisplayTimedTextFromPlayerold = NULL;

void __cdecl GAME_DisplayTimedTextFromPlayermy( HPLAYER toPlayer , float *x , float *y , float *duration , void * message )
{
	fprintf_s( logfile , "%s" , "DisplayTimedTextFromPlayermy\n" );
	fflush( logfile );

	GAME_DisplayTimedTextFromPlayerold( toPlayer , x , y , duration , message );
	fprintf_s( logfile , "%s:[-->GAME_DisplayTimedTextFromPlayer<--  toPlayer: %X x: %f y: %f duration: %f message: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , toPlayer , *( float * ) x , *( float * ) y , *( float * ) duration , jassgetchar( message ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_DisplayTimedTextToPlayer )( HPLAYER toPlayer , float *x , float *y , float *duration , void * message );
GAME_DisplayTimedTextToPlayer GAME_DisplayTimedTextToPlayerorg = NULL;
GAME_DisplayTimedTextToPlayer GAME_DisplayTimedTextToPlayerold = NULL;

void __cdecl GAME_DisplayTimedTextToPlayermy( HPLAYER toPlayer , float *x , float *y , float *duration , void * message )
{
	fprintf_s( logfile , "%s" , "DisplayTimedTextToPlayermy\n" );
	fflush( logfile );

	GAME_DisplayTimedTextToPlayerold( toPlayer , x , y , duration , message );
	fprintf_s( logfile , "%s:[-->GAME_DisplayTimedTextToPlayer<--  toPlayer: %X x: %f y: %f duration: %f message: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , toPlayer , *( float * ) x , *( float * ) y , *( float * ) duration , jassgetchar( message ) );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_DoAiScriptDebug )( );
GAME_DoAiScriptDebug GAME_DoAiScriptDebugorg = NULL;
GAME_DoAiScriptDebug GAME_DoAiScriptDebugold = NULL;

BOOL __cdecl GAME_DoAiScriptDebugmy( )
{
	fprintf_s( logfile , "%s" , "DoAiScriptDebugmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_DoAiScriptDebugold( );
	fprintf_s( logfile , "%s:[-->GAME_DoAiScriptDebug<-- ] RETURN-> %s\n" , currentDateTime( ).c_str( ) , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_DoNotSaveReplay )( );
GAME_DoNotSaveReplay GAME_DoNotSaveReplayorg = NULL;
GAME_DoNotSaveReplay GAME_DoNotSaveReplayold = NULL;

void __cdecl GAME_DoNotSaveReplaymy( )
{
	fprintf_s( logfile , "%s" , "DoNotSaveReplaymy\n" );
	fflush( logfile );

	GAME_DoNotSaveReplayold( );
	fprintf_s( logfile , "%s:[-->GAME_DoNotSaveReplay<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_EnableDragSelect )( BOOL state , BOOL ui );
GAME_EnableDragSelect GAME_EnableDragSelectorg = NULL;
GAME_EnableDragSelect GAME_EnableDragSelectold = NULL;

void __cdecl GAME_EnableDragSelectmy( BOOL state , BOOL ui )
{
	fprintf_s( logfile , "%s\n" , "EnableDragSelectmy" );
	fflush( logfile );

	GAME_EnableDragSelectold( state , ui );
	fprintf_s( logfile , "%s:[-->GAME_EnableDragSelect<--  state: %s ui: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , state ? "TRUE\n" : "FALSE" , ui ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_EnableMinimapFilterButtons )( BOOL enableAlly , BOOL enableCreep );
GAME_EnableMinimapFilterButtons GAME_EnableMinimapFilterButtonsorg = NULL;
GAME_EnableMinimapFilterButtons GAME_EnableMinimapFilterButtonsold = NULL;

void __cdecl GAME_EnableMinimapFilterButtonsmy( BOOL enableAlly , BOOL enableCreep )
{
	fprintf_s( logfile , "%s" , "EnableMinimapFilterButtonsmy\n" );
	fflush( logfile );

	GAME_EnableMinimapFilterButtonsold( enableAlly , enableCreep );
	fprintf_s( logfile , "%s:[-->GAME_EnableMinimapFilterButtons<--  enableAlly: %s enableCreep: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , enableAlly ? "TRUE\n" : "FALSE" , enableCreep ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_EnableOcclusion )( BOOL flag );
GAME_EnableOcclusion GAME_EnableOcclusionorg = NULL;
GAME_EnableOcclusion GAME_EnableOcclusionold = NULL;

void __cdecl GAME_EnableOcclusionmy( BOOL flag )
{
	fprintf_s( logfile , "%s" , "EnableOcclusionmy\n" );
	fflush( logfile );

	GAME_EnableOcclusionold( flag );
	fprintf_s( logfile , "%s:[-->GAME_EnableOcclusion<--  flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_EnablePreSelect )( BOOL state , BOOL ui );
GAME_EnablePreSelect GAME_EnablePreSelectorg = NULL;
GAME_EnablePreSelect GAME_EnablePreSelectold = NULL;

void __cdecl GAME_EnablePreSelectmy( BOOL state , BOOL ui )
{
	fprintf_s( logfile , "%s" , "EnablePreSelectmy\n" );
	fflush( logfile );

	GAME_EnablePreSelectold( state , ui );
	fprintf_s( logfile , "%s:[-->GAME_EnablePreSelect<--  state: %s ui: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , state ? "TRUE\n" : "FALSE" , ui ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_EnableSelect )( BOOL state , BOOL ui );
GAME_EnableSelect GAME_EnableSelectorg = NULL;
GAME_EnableSelect GAME_EnableSelectold = NULL;

void __cdecl GAME_EnableSelectmy( BOOL state , BOOL ui )
{
	fprintf_s( logfile , "%s" , "EnableSelectmy\n" );
	fflush( logfile );

	GAME_EnableSelectold( state , ui );
	fprintf_s( logfile , "%s:[-->GAME_EnableSelect<--  state: %s ui: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , state ? "TRUE\n" : "FALSE" , ui ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_EnableTrigger )( HTRIGGER whichTrigger );
GAME_EnableTrigger GAME_EnableTriggerorg = NULL;
GAME_EnableTrigger GAME_EnableTriggerold = NULL;

void __cdecl GAME_EnableTriggermy( HTRIGGER whichTrigger )
{
	fprintf_s( logfile , "%s" , "EnableTriggermy\n" );
	fflush( logfile );

	GAME_EnableTriggerold( whichTrigger );
	fprintf_s( logfile , "%s:[-->GAME_EnableTrigger<--  whichTrigger: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichTrigger );
	fflush( logfile );

}


typedef void( __cdecl *GAME_EnableUserControl )( BOOL b );
GAME_EnableUserControl GAME_EnableUserControlorg = NULL;
GAME_EnableUserControl GAME_EnableUserControlold = NULL;

void __cdecl GAME_EnableUserControlmy( BOOL b )
{
	fprintf_s( logfile , "%s\n" , "EnableUserControlmy" );
	fflush( logfile );

	GAME_EnableUserControlold( b );
	fprintf_s( logfile , "%s:[-->GAME_EnableUserControl<--  b: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , b ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_EnableUserUI )( BOOL b );
GAME_EnableUserUI GAME_EnableUserUIorg = NULL;
GAME_EnableUserUI GAME_EnableUserUIold = NULL;

void __cdecl GAME_EnableUserUImy( BOOL b )
{
	fprintf_s( logfile , "%s" , "EnableUserUImy\n" );
	fflush( logfile );

	GAME_EnableUserUIold( b );
	fprintf_s( logfile , "%s:[-->GAME_EnableUserUI<--  b: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , b ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_EnableWeatherEffect )( HWEATHEREFFECT whichEffect , BOOL enable );
GAME_EnableWeatherEffect GAME_EnableWeatherEffectorg = NULL;
GAME_EnableWeatherEffect GAME_EnableWeatherEffectold = NULL;

void __cdecl GAME_EnableWeatherEffectmy( HWEATHEREFFECT whichEffect , BOOL enable )
{
	fprintf_s( logfile , "%s" , "EnableWeatherEffectmy\n" );
	fflush( logfile );

	GAME_EnableWeatherEffectold( whichEffect , enable );
	fprintf_s( logfile , "%s:[-->GAME_EnableWeatherEffect<--  whichEffect: %X enable: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichEffect , enable ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_EnableWorldFogBoundary )( BOOL b );
GAME_EnableWorldFogBoundary GAME_EnableWorldFogBoundaryorg = NULL;
GAME_EnableWorldFogBoundary GAME_EnableWorldFogBoundaryold = NULL;

void __cdecl GAME_EnableWorldFogBoundarymy( BOOL b )
{
	fprintf_s( logfile , "%s" , "EnableWorldFogBoundarymy\n" );
	fflush( logfile );

	GAME_EnableWorldFogBoundaryold( b );
	fprintf_s( logfile , "%s:[-->GAME_EnableWorldFogBoundary<--  b: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , b ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_EndCinematicScene )( );
GAME_EndCinematicScene GAME_EndCinematicSceneorg = NULL;
GAME_EndCinematicScene GAME_EndCinematicSceneold = NULL;

void __cdecl GAME_EndCinematicScenemy( )
{
	fprintf_s( logfile , "%s" , "EndCinematicScenemy\n" );
	fflush( logfile );

	GAME_EndCinematicSceneold( );
	fprintf_s( logfile , "%s:[-->GAME_EndCinematicScene<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_EndGame )( BOOL doScoreScreen );
GAME_EndGame GAME_EndGameorg = NULL;
GAME_EndGame GAME_EndGameold = NULL;

void __cdecl GAME_EndGamemy( BOOL doScoreScreen )
{
	fprintf_s( logfile , "%s\n" , "EndGamemy" );
	fflush( logfile );

	GAME_EndGameold( doScoreScreen );
	fprintf_s( logfile , "%s:[-->GAME_EndGame<--  doScoreScreen: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , doScoreScreen ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_EndThematicMusic )( );
GAME_EndThematicMusic GAME_EndThematicMusicorg = NULL;
GAME_EndThematicMusic GAME_EndThematicMusicold = NULL;

void __cdecl GAME_EndThematicMusicmy( )
{
	fprintf_s( logfile , "%s" , "EndThematicMusicmy\n" );
	fflush( logfile );

	GAME_EndThematicMusicold( );
	fprintf_s( logfile , "%s:[-->GAME_EndThematicMusic<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_EnumDestructablesInRect )( HRECT r , HBOOLEXPR filter , CODE actionFunc );
GAME_EnumDestructablesInRect GAME_EnumDestructablesInRectorg = NULL;
GAME_EnumDestructablesInRect GAME_EnumDestructablesInRectold = NULL;

void __cdecl GAME_EnumDestructablesInRectmy( HRECT r , HBOOLEXPR filter , CODE actionFunc )
{
	fprintf_s( logfile , "%s\n" , "EnumDestructablesInRectmy" );
	fflush( logfile );

	GAME_EnumDestructablesInRectold( r , filter , actionFunc );
	fprintf_s( logfile , "%s:[-->GAME_EnumDestructablesInRect<--  r: %X filter: %X actionFunc: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , r , filter , actionFunc );
	fflush( logfile );

}


typedef void( __cdecl *GAME_EnumItemsInRect )( HRECT r , HBOOLEXPR filter , CODE actionFunc );
GAME_EnumItemsInRect GAME_EnumItemsInRectorg = NULL;
GAME_EnumItemsInRect GAME_EnumItemsInRectold = NULL;

void __cdecl GAME_EnumItemsInRectmy( HRECT r , HBOOLEXPR filter , CODE actionFunc )
{
	fprintf_s( logfile , "%s\n" , "EnumItemsInRectmy" );
	fflush( logfile );

	GAME_EnumItemsInRectold( r , filter , actionFunc );
	fprintf_s( logfile , "%s:[-->GAME_EnumItemsInRect<--  r: %X filter: %X actionFunc: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , r , filter , actionFunc );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ExecuteFunc )( void * funcName );
GAME_ExecuteFunc GAME_ExecuteFuncorg = NULL;
GAME_ExecuteFunc GAME_ExecuteFuncold = NULL;

void __cdecl GAME_ExecuteFuncmy( void * funcName )
{
	fprintf_s( logfile , "%s\n" , "ExecuteFuncmy" );
	fflush( logfile );

	GAME_ExecuteFuncold( funcName );
	fprintf_s( logfile , "%s:[-->GAME_ExecuteFunc<--  funcName: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( funcName ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_FillGuardPosts )( );
GAME_FillGuardPosts GAME_FillGuardPostsorg = NULL;
GAME_FillGuardPosts GAME_FillGuardPostsold = NULL;

void __cdecl GAME_FillGuardPostsmy( )
{
	fprintf_s( logfile , "%s" , "FillGuardPostsmy\n" );
	fflush( logfile );

	GAME_FillGuardPostsold( );
	fprintf_s( logfile , "%s:[-->GAME_FillGuardPosts<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef HFILTERFUNC( __cdecl *GAME_Filter )( CODE func );
GAME_Filter GAME_Filterorg = NULL;
GAME_Filter GAME_Filterold = NULL;

HFILTERFUNC __cdecl GAME_Filtermy( CODE func )
{
	fprintf_s( logfile , "%s\n" , "Filtermy" );
	fflush( logfile );

	HFILTERFUNC retvalue = GAME_Filterold( func );
	fprintf_s( logfile , "%s:[-->GAME_Filter<--  func: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , func , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_FinishUbersplat )( HUBERSPLAT whichSplat );
GAME_FinishUbersplat GAME_FinishUbersplatorg = NULL;
GAME_FinishUbersplat GAME_FinishUbersplatold = NULL;

void __cdecl GAME_FinishUbersplatmy( HUBERSPLAT whichSplat )
{
	fprintf_s( logfile , "%s\n" , "FinishUbersplatmy" );
	fflush( logfile );

	GAME_FinishUbersplatold( whichSplat );
	fprintf_s( logfile , "%s:[-->GAME_FinishUbersplat<--  whichSplat: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichSplat );
	fflush( logfile );

}


typedef HUNIT( __cdecl *GAME_FirstOfGroup )( HGROUP whichGroup );
GAME_FirstOfGroup GAME_FirstOfGrouporg = NULL;
GAME_FirstOfGroup GAME_FirstOfGroupold = NULL;

HUNIT __cdecl GAME_FirstOfGroupmy( HGROUP whichGroup )
{
	fprintf_s( logfile , "%s\n" , "FirstOfGroupmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_FirstOfGroupold( whichGroup );
	fprintf_s( logfile , "%s:[-->GAME_FirstOfGroup<--  whichGroup: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichGroup , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_FlashQuestDialogButton )( );
GAME_FlashQuestDialogButton GAME_FlashQuestDialogButtonorg = NULL;
GAME_FlashQuestDialogButton GAME_FlashQuestDialogButtonold = NULL;

void __cdecl GAME_FlashQuestDialogButtonmy( )
{
	fprintf_s( logfile , "%s\n" , "FlashQuestDialogButtonmy" );
	fflush( logfile );

	GAME_FlashQuestDialogButtonold( );
	fprintf_s( logfile , "%s:[-->GAME_FlashQuestDialogButton<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_FlushChildHashtable )( HHASHTABLE table , int parentKey );
GAME_FlushChildHashtable GAME_FlushChildHashtableorg = NULL;
GAME_FlushChildHashtable GAME_FlushChildHashtableold = NULL;

void __cdecl GAME_FlushChildHashtablemy( HHASHTABLE table , int parentKey )
{
	fprintf_s( logfile , "%s\n" , "FlushChildHashtablemy" );
	fflush( logfile );

	GAME_FlushChildHashtableold( table , parentKey );
	fprintf_s( logfile , "%s:[-->GAME_FlushChildHashtable<--  table: %X parentKey: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , table , parentKey );
	fflush( logfile );

}


typedef void( __cdecl *GAME_FlushGameCache )( HGAMECACHE cache );
GAME_FlushGameCache GAME_FlushGameCacheorg = NULL;
GAME_FlushGameCache GAME_FlushGameCacheold = NULL;

void __cdecl GAME_FlushGameCachemy( HGAMECACHE cache )
{
	fprintf_s( logfile , "%s\n" , "FlushGameCachemy" );
	fflush( logfile );

	GAME_FlushGameCacheold( cache );
	fprintf_s( logfile , "%s:[-->GAME_FlushGameCache<--  cache: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , cache );
	fflush( logfile );

}


typedef void( __cdecl *GAME_FlushParentHashtable )( HHASHTABLE table );
GAME_FlushParentHashtable GAME_FlushParentHashtableorg = NULL;
GAME_FlushParentHashtable GAME_FlushParentHashtableold = NULL;

void __cdecl GAME_FlushParentHashtablemy( HHASHTABLE table )
{
	fprintf_s( logfile , "%s\n" , "FlushParentHashtablemy" );
	fflush( logfile );

	GAME_FlushParentHashtableold( table );
	fprintf_s( logfile , "%s:[-->GAME_FlushParentHashtable<--  table: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , table );
	fflush( logfile );

}


typedef void( __cdecl *GAME_FlushStoredBOOLean )( HGAMECACHE cache , void * missionKey , void * key );
GAME_FlushStoredBOOLean GAME_FlushStoredBOOLeanorg = NULL;
GAME_FlushStoredBOOLean GAME_FlushStoredBOOLeanold = NULL;

void __cdecl GAME_FlushStoredBOOLeanmy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s\n" , "FlushStoredBOOLeanmy" );
	fflush( logfile );

	GAME_FlushStoredBOOLeanold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_FlushStoredBOOLean<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_FlushStoredInteger )( HGAMECACHE cache , void * missionKey , void * key );
GAME_FlushStoredInteger GAME_FlushStoredIntegerorg = NULL;
GAME_FlushStoredInteger GAME_FlushStoredIntegerold = NULL;

void __cdecl GAME_FlushStoredIntegermy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s" , "FlushStoredIntegermy\n" );
	fflush( logfile );

	GAME_FlushStoredIntegerold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_FlushStoredInteger<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_FlushStoredMission )( HGAMECACHE cache , void * missionKey );
GAME_FlushStoredMission GAME_FlushStoredMissionorg = NULL;
GAME_FlushStoredMission GAME_FlushStoredMissionold = NULL;

void __cdecl GAME_FlushStoredMissionmy( HGAMECACHE cache , void * missionKey )
{
	fprintf_s( logfile , "%s" , "FlushStoredMissionmy\n" );
	fflush( logfile );

	GAME_FlushStoredMissionold( cache , missionKey );
	fprintf_s( logfile , "%s:[-->GAME_FlushStoredMission<--  cache: %X missionKey: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_FlushStoredReal )( HGAMECACHE cache , void * missionKey , void * key );
GAME_FlushStoredReal GAME_FlushStoredRealorg = NULL;
GAME_FlushStoredReal GAME_FlushStoredRealold = NULL;

void __cdecl GAME_FlushStoredRealmy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s" , "FlushStoredRealmy\n" );
	fflush( logfile );

	GAME_FlushStoredRealold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_FlushStoredReal<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_FlushStoredString )( HGAMECACHE cache , void * missionKey , void * key );
GAME_FlushStoredString GAME_FlushStoredStringorg = NULL;
GAME_FlushStoredString GAME_FlushStoredStringold = NULL;

void __cdecl GAME_FlushStoredStringmy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s" , "FlushStoredStringmy\n" );
	fflush( logfile );

	GAME_FlushStoredStringold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_FlushStoredString<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_FlushStoredUnit )( HGAMECACHE cache , void * missionKey , void * key );
GAME_FlushStoredUnit GAME_FlushStoredUnitorg = NULL;
GAME_FlushStoredUnit GAME_FlushStoredUnitold = NULL;

void __cdecl GAME_FlushStoredUnitmy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s" , "FlushStoredUnitmy\n" );
	fflush( logfile );

	GAME_FlushStoredUnitold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_FlushStoredUnit<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_FogEnable )( BOOL enable );
GAME_FogEnable GAME_FogEnableorg = NULL;
GAME_FogEnable GAME_FogEnableold = NULL;

void __cdecl GAME_FogEnablemy( BOOL enable )
{
	fprintf_s( logfile , "%s" , "FogEnablemy\n" );
	fflush( logfile );

	GAME_FogEnableold( enable );
	fprintf_s( logfile , "%s:[-->GAME_FogEnable<--  enable: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , enable ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_FogMaskEnable )( BOOL enable );
GAME_FogMaskEnable GAME_FogMaskEnableorg = NULL;
GAME_FogMaskEnable GAME_FogMaskEnableold = NULL;

void __cdecl GAME_FogMaskEnablemy( BOOL enable )
{
	fprintf_s( logfile , "%s" , "FogMaskEnablemy\n" );
	fflush( logfile );

	GAME_FogMaskEnableold( enable );
	fprintf_s( logfile , "%s:[-->GAME_FogMaskEnable<--  enable: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , enable ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_FogModifierStart )( HFOGMODIFIER whichFogModifier );
GAME_FogModifierStart GAME_FogModifierStartorg = NULL;
GAME_FogModifierStart GAME_FogModifierStartold = NULL;

void __cdecl GAME_FogModifierStartmy( HFOGMODIFIER whichFogModifier )
{
	fprintf_s( logfile , "%s" , "FogModifierStartmy\n" );
	fflush( logfile );

	GAME_FogModifierStartold( whichFogModifier );
	fprintf_s( logfile , "%s:[-->GAME_FogModifierStart<--  whichFogModifier: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichFogModifier );
	fflush( logfile );

}


typedef void( __cdecl *GAME_FogModifierStop )( HFOGMODIFIER whichFogModifier );
GAME_FogModifierStop GAME_FogModifierStoporg = NULL;
GAME_FogModifierStop GAME_FogModifierStopold = NULL;

void __cdecl GAME_FogModifierStopmy( HFOGMODIFIER whichFogModifier )
{
	fprintf_s( logfile , "%s\n" , "FogModifierStopmy" );
	fflush( logfile );

	GAME_FogModifierStopold( whichFogModifier );
	fprintf_s( logfile , "%s:[-->GAME_FogModifierStop<--  whichFogModifier: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichFogModifier );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ForForce )( HFORCE whichForce , CODE callback );
GAME_ForForce GAME_ForForceorg = NULL;
GAME_ForForce GAME_ForForceold = NULL;

void __cdecl GAME_ForForcemy( HFORCE whichForce , CODE callback )
{
	fprintf_s( logfile , "%s\n" , "ForForcemy" );
	fflush( logfile );

	GAME_ForForceold( whichForce , callback );
	fprintf_s( logfile , "%s:[-->GAME_ForForce<--  whichForce: %X callback: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichForce , callback );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ForGroup )( HGROUP whichGroup , CODE callback );
GAME_ForGroup GAME_ForGrouporg = NULL;
GAME_ForGroup GAME_ForGroupold = NULL;

void __cdecl GAME_ForGroupmy( HGROUP whichGroup , CODE callback )
{
	fprintf_s( logfile , "%s\n" , "ForGroupmy" );
	fflush( logfile );

	GAME_ForGroupold( whichGroup , callback );
	fprintf_s( logfile , "%s:[-->GAME_ForGroup<--  whichGroup: %X callback: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichGroup , callback );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ForceAddPlayer )( HFORCE whichForce , HPLAYER whichPlayer );
GAME_ForceAddPlayer GAME_ForceAddPlayerorg = NULL;
GAME_ForceAddPlayer GAME_ForceAddPlayerold = NULL;

void __cdecl GAME_ForceAddPlayermy( HFORCE whichForce , HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s\n" , "ForceAddPlayermy" );
	fflush( logfile );

	GAME_ForceAddPlayerold( whichForce , whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_ForceAddPlayer<--  whichForce: %X whichPlayer: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichForce , whichPlayer );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ForceCampaignSelectScreen )( );
GAME_ForceCampaignSelectScreen GAME_ForceCampaignSelectScreenorg = NULL;
GAME_ForceCampaignSelectScreen GAME_ForceCampaignSelectScreenold = NULL;

void __cdecl GAME_ForceCampaignSelectScreenmy( )
{
	fprintf_s( logfile , "%s\n" , "ForceCampaignSelectScreenmy" );
	fflush( logfile );

	GAME_ForceCampaignSelectScreenold( );
	fprintf_s( logfile , "%s:[-->GAME_ForceCampaignSelectScreen<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ForceCinematicSubtitles )( BOOL flag );
GAME_ForceCinematicSubtitles GAME_ForceCinematicSubtitlesorg = NULL;
GAME_ForceCinematicSubtitles GAME_ForceCinematicSubtitlesold = NULL;

void __cdecl GAME_ForceCinematicSubtitlesmy( BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "ForceCinematicSubtitlesmy" );
	fflush( logfile );

	GAME_ForceCinematicSubtitlesold( flag );
	fprintf_s( logfile , "%s:[-->GAME_ForceCinematicSubtitles<--  flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ForceClear )( HFORCE whichForce );
GAME_ForceClear GAME_ForceClearorg = NULL;
GAME_ForceClear GAME_ForceClearold = NULL;

void __cdecl GAME_ForceClearmy( HFORCE whichForce )
{
	fprintf_s( logfile , "%s" , "ForceClearmy\n" );
	fflush( logfile );

	GAME_ForceClearold( whichForce );
	fprintf_s( logfile , "%s:[-->GAME_ForceClear<--  whichForce: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichForce );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ForceEnumAllies )( HFORCE whichForce , HPLAYER whichPlayer , HBOOLEXPR filter );
GAME_ForceEnumAllies GAME_ForceEnumAlliesorg = NULL;
GAME_ForceEnumAllies GAME_ForceEnumAlliesold = NULL;

void __cdecl GAME_ForceEnumAlliesmy( HFORCE whichForce , HPLAYER whichPlayer , HBOOLEXPR filter )
{
	fprintf_s( logfile , "%s\n" , "ForceEnumAlliesmy" );
	fflush( logfile );

	GAME_ForceEnumAlliesold( whichForce , whichPlayer , filter );
	fprintf_s( logfile , "%s:[-->GAME_ForceEnumAllies<--  whichForce: %X whichPlayer: %X filter: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichForce , whichPlayer , filter );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ForceEnumEnemies )( HFORCE whichForce , HPLAYER whichPlayer , HBOOLEXPR filter );
GAME_ForceEnumEnemies GAME_ForceEnumEnemiesorg = NULL;
GAME_ForceEnumEnemies GAME_ForceEnumEnemiesold = NULL;

void __cdecl GAME_ForceEnumEnemiesmy( HFORCE whichForce , HPLAYER whichPlayer , HBOOLEXPR filter )
{
	fprintf_s( logfile , "%s\n" , "ForceEnumEnemiesmy" );
	fflush( logfile );

	GAME_ForceEnumEnemiesold( whichForce , whichPlayer , filter );
	fprintf_s( logfile , "%s:[-->GAME_ForceEnumEnemies<--  whichForce: %X whichPlayer: %X filter: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichForce , whichPlayer , filter );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ForceEnumPlayers )( HFORCE whichForce , HBOOLEXPR filter );
GAME_ForceEnumPlayers GAME_ForceEnumPlayersorg = NULL;
GAME_ForceEnumPlayers GAME_ForceEnumPlayersold = NULL;

void __cdecl GAME_ForceEnumPlayersmy( HFORCE whichForce , HBOOLEXPR filter )
{
	fprintf_s( logfile , "%s\n" , "ForceEnumPlayersmy" );
	fflush( logfile );

	GAME_ForceEnumPlayersold( whichForce , filter );
	fprintf_s( logfile , "%s:[-->GAME_ForceEnumPlayers<--  whichForce: %X filter: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichForce , filter );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ForceEnumPlayersCounted )( HFORCE whichForce , HBOOLEXPR filter , int countLimit );
GAME_ForceEnumPlayersCounted GAME_ForceEnumPlayersCountedorg = NULL;
GAME_ForceEnumPlayersCounted GAME_ForceEnumPlayersCountedold = NULL;

void __cdecl GAME_ForceEnumPlayersCountedmy( HFORCE whichForce , HBOOLEXPR filter , int countLimit )
{
	fprintf_s( logfile , "%s\n" , "ForceEnumPlayersCountedmy" );
	fflush( logfile );

	GAME_ForceEnumPlayersCountedold( whichForce , filter , countLimit );
	fprintf_s( logfile , "%s:[-->GAME_ForceEnumPlayersCounted<--  whichForce: %X filter: %X countLimit: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichForce , filter , countLimit );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ForcePlayerStartLocation )( HPLAYER whichPlayer , int startLocIndex );
GAME_ForcePlayerStartLocation GAME_ForcePlayerStartLocationorg = NULL;
GAME_ForcePlayerStartLocation GAME_ForcePlayerStartLocationold = NULL;

void __cdecl GAME_ForcePlayerStartLocationmy( HPLAYER whichPlayer , int startLocIndex )
{
	fprintf_s( logfile , "%s\n" , "ForcePlayerStartLocationmy" );
	fflush( logfile );

	GAME_ForcePlayerStartLocationold( whichPlayer , startLocIndex );
	fprintf_s( logfile , "%s:[-->GAME_ForcePlayerStartLocation<--  whichPlayer: %X startLocIndex: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , startLocIndex );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ForceQuestDialogUpdate )( );
GAME_ForceQuestDialogUpdate GAME_ForceQuestDialogUpdateorg = NULL;
GAME_ForceQuestDialogUpdate GAME_ForceQuestDialogUpdateold = NULL;

void __cdecl GAME_ForceQuestDialogUpdatemy( )
{
	fprintf_s( logfile , "%s\n" , "ForceQuestDialogUpdatemy" );
	fflush( logfile );

	GAME_ForceQuestDialogUpdateold( );
	fprintf_s( logfile , "%s:[-->GAME_ForceQuestDialogUpdate<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ForceRemovePlayer )( HFORCE whichForce , HPLAYER whichPlayer );
GAME_ForceRemovePlayer GAME_ForceRemovePlayerorg = NULL;
GAME_ForceRemovePlayer GAME_ForceRemovePlayerold = NULL;

void __cdecl GAME_ForceRemovePlayermy( HFORCE whichForce , HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s\n" , "ForceRemovePlayermy" );
	fflush( logfile );

	GAME_ForceRemovePlayerold( whichForce , whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_ForceRemovePlayer<--  whichForce: %X whichPlayer: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichForce , whichPlayer );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ForceUICancel )( );
GAME_ForceUICancel GAME_ForceUICancelorg = NULL;
GAME_ForceUICancel GAME_ForceUICancelold = NULL;

void __cdecl GAME_ForceUICancelmy( )
{
	fprintf_s( logfile , "%s\n" , "ForceUICancelmy" );
	fflush( logfile );

	GAME_ForceUICancelold( );
	fprintf_s( logfile , "%s:[-->GAME_ForceUICancel<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ForceUIKey )( void * key );
GAME_ForceUIKey GAME_ForceUIKeyorg = NULL;
GAME_ForceUIKey GAME_ForceUIKeyold = NULL;

void __cdecl GAME_ForceUIKeymy( void * key )
{
	fprintf_s( logfile , "%s\n" , "ForceUIKeymy" );
	fflush( logfile );

	GAME_ForceUIKeyold( key );
	fprintf_s( logfile , "%s:[-->GAME_ForceUIKey<--  key: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( key ) );
	fflush( logfile );

}


typedef HAIDIFFICULTY( __cdecl *GAME_GetAIDifficulty )( HPLAYER num );
GAME_GetAIDifficulty GAME_GetAIDifficultyorg = NULL;
GAME_GetAIDifficulty GAME_GetAIDifficultyold = NULL;

HAIDIFFICULTY __cdecl GAME_GetAIDifficultymy( HPLAYER num )
{
	fprintf_s( logfile , "%s" , "GetAIDifficultymy\n" );
	fflush( logfile );

	HAIDIFFICULTY retvalue = GAME_GetAIDifficultyold( num );
	fprintf_s( logfile , "%s:[-->GAME_GetAIDifficulty<--  num: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , num , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_GetAbilityEffect )( void * abilityString , HEFFECTTYPE t , int index );
GAME_GetAbilityEffect GAME_GetAbilityEffectorg = NULL;
GAME_GetAbilityEffect GAME_GetAbilityEffectold = NULL;

DWORD __cdecl GAME_GetAbilityEffectmy( void * abilityString , HEFFECTTYPE t , int index )
{
	fprintf_s( logfile , "%s\n" , "GetAbilityEffectmy" );
	fflush( logfile );

	DWORD retvalue = GAME_GetAbilityEffectold( abilityString , t , index );
	fprintf_s( logfile , "%s:[-->GAME_GetAbilityEffect<--  abilityString: \"%s\" t: %X index: %i] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , jassgetchar( abilityString ) , t , index , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_GetAbilityEffectById )( int abilityId , HEFFECTTYPE t , int index );
GAME_GetAbilityEffectById GAME_GetAbilityEffectByIdorg = NULL;
GAME_GetAbilityEffectById GAME_GetAbilityEffectByIdold = NULL;

DWORD __cdecl GAME_GetAbilityEffectByIdmy( int abilityId , HEFFECTTYPE t , int index )
{
	fprintf_s( logfile , "%s" , "GetAbilityEffectByIdmy\n" );
	fflush( logfile );

	DWORD retvalue = GAME_GetAbilityEffectByIdold( abilityId , t , index );
	fprintf_s( logfile , "%s:[-->GAME_GetAbilityEffectById<--  abilityId: %i t: %X index: %i] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , abilityId , t , index , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_GetAbilitySound )( void * abilityString , HSOUNDTYPE t );
GAME_GetAbilitySound GAME_GetAbilitySoundorg = NULL;
GAME_GetAbilitySound GAME_GetAbilitySoundold = NULL;

DWORD __cdecl GAME_GetAbilitySoundmy( void * abilityString , HSOUNDTYPE t )
{
	fprintf_s( logfile , "%s\n" , "GetAbilitySoundmy" );
	fflush( logfile );

	DWORD retvalue = GAME_GetAbilitySoundold( abilityString , t );
	fprintf_s( logfile , "%s:[-->GAME_GetAbilitySound<--  abilityString: \"%s\" t: %X] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , jassgetchar( abilityString ) , t , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_GetAbilitySoundById )( int abilityId , HSOUNDTYPE t );
GAME_GetAbilitySoundById GAME_GetAbilitySoundByIdorg = NULL;
GAME_GetAbilitySoundById GAME_GetAbilitySoundByIdold = NULL;

DWORD __cdecl GAME_GetAbilitySoundByIdmy( int abilityId , HSOUNDTYPE t )
{
	fprintf_s( logfile , "%s" , "GetAbilitySoundByIdmy\n" );
	fflush( logfile );

	DWORD retvalue = GAME_GetAbilitySoundByIdold( abilityId , t );
	fprintf_s( logfile , "%s:[-->GAME_GetAbilitySoundById<--  abilityId: %i t: %X] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , abilityId , t , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetAiPlayer )( );
GAME_GetAiPlayer GAME_GetAiPlayerorg = NULL;
GAME_GetAiPlayer GAME_GetAiPlayerold = NULL;

int __cdecl GAME_GetAiPlayermy( )
{
	fprintf_s( logfile , "%s\n" , "GetAiPlayermy" );
	fflush( logfile );

	int retvalue = GAME_GetAiPlayerold( );
	fprintf_s( logfile , "%s:[-->GAME_GetAiPlayer<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_Ordinal266 )( const char *Str , int a2 , int a3 , int a4 );
GAME_Ordinal266 GAME_Ordinal266org = NULL;
GAME_Ordinal266 GAME_Ordinal266old = NULL;

int __cdecl GAME_Ordinal266my( const char *Str , int a2 , int a3 , int a4 )
{
	fprintf_s( logfile , "%s\n" , "Ordinal266my" );
	fflush( logfile );

	int retvalue = GAME_Ordinal266old( Str , a2 , a3 , a4 );
	fprintf_s( logfile , "%s:[-->GAME_Ordinal266<--  Str: %X a2: %i a3: %i a4: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , *( const char * ) Str , a2 , a3 , a4 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_Ordinal293 )( int a1 , const char *Str , int a3 , int a4 , int a5 );
GAME_Ordinal293 GAME_Ordinal293org = NULL;
GAME_Ordinal293 GAME_Ordinal293old = NULL;

int __cdecl GAME_Ordinal293my( int a1 , const char *Str , int a3 , int a4 , int a5 )
{
	fprintf_s( logfile , "%s\n" , "Ordinal293my" );
	fflush( logfile );

	int retvalue = GAME_Ordinal293old( a1 , Str , a3 , a4 , a5 );
	fprintf_s( logfile , "%s:[-->GAME_Ordinal293<--  a1: %i Str: %X a3: %i a4: %i a5: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , a1 , *( const char * ) Str , a3 , a4 , a5 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef signed int( __cdecl *GAME_AutoCast )( );
GAME_AutoCast GAME_AutoCastorg = NULL;
GAME_AutoCast GAME_AutoCastold = NULL;

signed int __cdecl GAME_AutoCastmy( )
{
	fprintf_s( logfile , "%s\n" , "AutoCastmy" );
	fflush( logfile );

	signed int retvalue = GAME_AutoCastold( );
	fprintf_s( logfile , "%s:[-->GAME_AutoCast<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef VOID( __cdecl *GAME_INIDEB )( );
GAME_INIDEB GAME_INIDEBorg = NULL;
GAME_INIDEB GAME_INIDEBold = NULL;

VOID __cdecl GAME_INIDEBmy( )
{
	fprintf_s( logfile , "%s\n" , "INIDEBmy" );
	fflush( logfile );

	GAME_INIDEBold( );
	fprintf_s( logfile , "%s:[-->GAME_INIDEB<-- ] RETURN-> BAD\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );



}

typedef HUNIT( __cdecl *GAME_GetAllianceTarget )( );
GAME_GetAllianceTarget GAME_GetAllianceTargetorg = NULL;
GAME_GetAllianceTarget GAME_GetAllianceTargetold = NULL;

HUNIT __cdecl GAME_GetAllianceTargetmy( )
{
	fprintf_s( logfile , "%s\n" , "GetAllianceTargetmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetAllianceTargetold( );
	fprintf_s( logfile , "%s:[-->GAME_GetAllianceTarget<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetAllyColorFilterState )( );
GAME_GetAllyColorFilterState GAME_GetAllyColorFilterStateorg = NULL;
GAME_GetAllyColorFilterState GAME_GetAllyColorFilterStateold = NULL;

int __cdecl GAME_GetAllyColorFilterStatemy( )
{
	fprintf_s( logfile , "%s\n" , "GetAllyColorFilterStatemy" );
	fflush( logfile );

	int retvalue = GAME_GetAllyColorFilterStateold( );
	fprintf_s( logfile , "%s:[-->GAME_GetAllyColorFilterState<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetAttacker )( );
GAME_GetAttacker GAME_GetAttackerorg = NULL;
GAME_GetAttacker GAME_GetAttackerold = NULL;

HUNIT __cdecl GAME_GetAttackermy( )
{
	fprintf_s( logfile , "%s\n" , "GetAttackermy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetAttackerold( );
	fprintf_s( logfile , "%s:[-->GAME_GetAttacker<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetBuilding )( HPLAYER arg1 );
GAME_GetBuilding GAME_GetBuildingorg = NULL;
GAME_GetBuilding GAME_GetBuildingold = NULL;

HUNIT __cdecl GAME_GetBuildingmy( HPLAYER arg1 )
{
	fprintf_s( logfile , "%s\n" , "GetBuildingmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetBuildingold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_GetBuilding<--  arg1: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , arg1 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetBuyingUnit )( );
GAME_GetBuyingUnit GAME_GetBuyingUnitorg = NULL;
GAME_GetBuyingUnit GAME_GetBuyingUnitold = NULL;

HUNIT __cdecl GAME_GetBuyingUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetBuyingUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetBuyingUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetBuyingUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetCameraBoundMaxX )( );
GAME_GetCameraBoundMaxX GAME_GetCameraBoundMaxXorg = NULL;
GAME_GetCameraBoundMaxX GAME_GetCameraBoundMaxXold = NULL;

DWFP __cdecl GAME_GetCameraBoundMaxXmy( )
{
	fprintf_s( logfile , "%s\n" , "GetCameraBoundMaxXmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetCameraBoundMaxXold( );
	fprintf_s( logfile , "%s:[-->GAME_GetCameraBoundMaxX<-- ] RETURN-> %f\n" , currentDateTime( ).c_str( ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetCameraBoundMaxY )( );
GAME_GetCameraBoundMaxY GAME_GetCameraBoundMaxYorg = NULL;
GAME_GetCameraBoundMaxY GAME_GetCameraBoundMaxYold = NULL;

DWFP __cdecl GAME_GetCameraBoundMaxYmy( )
{
	fprintf_s( logfile , "%s\n" , "GetCameraBoundMaxYmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetCameraBoundMaxYold( );
	fprintf_s( logfile , "%s:[-->GAME_GetCameraBoundMaxY<-- ] RETURN-> %f\n" , currentDateTime( ).c_str( ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetCameraBoundMinX )( );
GAME_GetCameraBoundMinX GAME_GetCameraBoundMinXorg = NULL;
GAME_GetCameraBoundMinX GAME_GetCameraBoundMinXold = NULL;

DWFP __cdecl GAME_GetCameraBoundMinXmy( )
{
	fprintf_s( logfile , "%s\n" , "GetCameraBoundMinXmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetCameraBoundMinXold( );
	fprintf_s( logfile , "%s:[-->GAME_GetCameraBoundMinX<-- ] RETURN-> %f\n" , currentDateTime( ).c_str( ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetCameraBoundMinY )( );
GAME_GetCameraBoundMinY GAME_GetCameraBoundMinYorg = NULL;
GAME_GetCameraBoundMinY GAME_GetCameraBoundMinYold = NULL;

DWFP __cdecl GAME_GetCameraBoundMinYmy( )
{
	fprintf_s( logfile , "%s\n" , "GetCameraBoundMinYmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetCameraBoundMinYold( );
	fprintf_s( logfile , "%s:[-->GAME_GetCameraBoundMinY<-- ] RETURN-> %f\n" , currentDateTime( ).c_str( ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef HLOCATION( __cdecl *GAME_GetCameraEyePositionLoc )( );
GAME_GetCameraEyePositionLoc GAME_GetCameraEyePositionLocorg = NULL;
GAME_GetCameraEyePositionLoc GAME_GetCameraEyePositionLocold = NULL;

HLOCATION __cdecl GAME_GetCameraEyePositionLocmy( )
{
	fprintf_s( logfile , "%s\n" , "GetCameraEyePositionLocmy" );
	fflush( logfile );

	HLOCATION retvalue = GAME_GetCameraEyePositionLocold( );
	fprintf_s( logfile , "%s:[-->GAME_GetCameraEyePositionLoc<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetCameraEyePositionX )( );
GAME_GetCameraEyePositionX GAME_GetCameraEyePositionXorg = NULL;
GAME_GetCameraEyePositionX GAME_GetCameraEyePositionXold = NULL;

DWFP __cdecl GAME_GetCameraEyePositionXmy( )
{
	fprintf_s( logfile , "%s\n" , "GetCameraEyePositionXmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetCameraEyePositionXold( );
	fprintf_s( logfile , "%s:[-->GAME_GetCameraEyePositionX<-- ] RETURN-> %f\n" , currentDateTime( ).c_str( ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetCameraEyePositionY )( );
GAME_GetCameraEyePositionY GAME_GetCameraEyePositionYorg = NULL;
GAME_GetCameraEyePositionY GAME_GetCameraEyePositionYold = NULL;

DWFP __cdecl GAME_GetCameraEyePositionYmy( )
{
	fprintf_s( logfile , "%s\n" , "GetCameraEyePositionYmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetCameraEyePositionYold( );
	fprintf_s( logfile , "%s:[-->GAME_GetCameraEyePositionY<-- ] RETURN-> %f\n" , currentDateTime( ).c_str( ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetCameraEyePositionZ )( );
GAME_GetCameraEyePositionZ GAME_GetCameraEyePositionZorg = NULL;
GAME_GetCameraEyePositionZ GAME_GetCameraEyePositionZold = NULL;

DWFP __cdecl GAME_GetCameraEyePositionZmy( )
{
	fprintf_s( logfile , "%s\n" , "GetCameraEyePositionZmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetCameraEyePositionZold( );
	fprintf_s( logfile , "%s:[-->GAME_GetCameraEyePositionZ<-- ] RETURN-> %f\n" , currentDateTime( ).c_str( ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetCameraField )( HCAMERAFIELD whichField );
GAME_GetCameraField GAME_GetCameraFieldorg = NULL;
GAME_GetCameraField GAME_GetCameraFieldold = NULL;

DWFP __cdecl GAME_GetCameraFieldmy( HCAMERAFIELD whichField )
{
	fprintf_s( logfile , "%s\n" , "GetCameraFieldmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetCameraFieldold( whichField );
	fprintf_s( logfile , "%s:[-->GAME_GetCameraField<--  whichField: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichField , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetCameraMargin )( int whichMargin );
GAME_GetCameraMargin GAME_GetCameraMarginorg = NULL;
GAME_GetCameraMargin GAME_GetCameraMarginold = NULL;

DWFP __cdecl GAME_GetCameraMarginmy( int whichMargin )
{
	fprintf_s( logfile , "%s\n" , "GetCameraMarginmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetCameraMarginold( whichMargin );
	fprintf_s( logfile , "%s:[-->GAME_GetCameraMargin<--  whichMargin: %i] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichMargin , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef HLOCATION( __cdecl *GAME_GetCameraTargetPositionLoc )( );
GAME_GetCameraTargetPositionLoc GAME_GetCameraTargetPositionLocorg = NULL;
GAME_GetCameraTargetPositionLoc GAME_GetCameraTargetPositionLocold = NULL;

HLOCATION __cdecl GAME_GetCameraTargetPositionLocmy( )
{
	fprintf_s( logfile , "%s\n" , "GetCameraTargetPositionLocmy" );
	fflush( logfile );

	HLOCATION retvalue = GAME_GetCameraTargetPositionLocold( );
	fprintf_s( logfile , "%s:[-->GAME_GetCameraTargetPositionLoc<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetCameraTargetPositionX )( );
GAME_GetCameraTargetPositionX GAME_GetCameraTargetPositionXorg = NULL;
GAME_GetCameraTargetPositionX GAME_GetCameraTargetPositionXold = NULL;

DWFP __cdecl GAME_GetCameraTargetPositionXmy( )
{
	fprintf_s( logfile , "%s\n" , "GetCameraTargetPositionXmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetCameraTargetPositionXold( );
	fprintf_s( logfile , "%s:[-->GAME_GetCameraTargetPositionX<-- ] RETURN-> %f\n" , currentDateTime( ).c_str( ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetCameraTargetPositionY )( );
GAME_GetCameraTargetPositionY GAME_GetCameraTargetPositionYorg = NULL;
GAME_GetCameraTargetPositionY GAME_GetCameraTargetPositionYold = NULL;

DWFP __cdecl GAME_GetCameraTargetPositionYmy( )
{
	fprintf_s( logfile , "%s\n" , "GetCameraTargetPositionYmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetCameraTargetPositionYold( );
	fprintf_s( logfile , "%s:[-->GAME_GetCameraTargetPositionY<-- ] RETURN-> %f\n" , currentDateTime( ).c_str( ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetCameraTargetPositionZ )( );
GAME_GetCameraTargetPositionZ GAME_GetCameraTargetPositionZorg = NULL;
GAME_GetCameraTargetPositionZ GAME_GetCameraTargetPositionZold = NULL;

DWFP __cdecl GAME_GetCameraTargetPositionZmy( )
{
	fprintf_s( logfile , "%s\n" , "GetCameraTargetPositionZmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetCameraTargetPositionZold( );
	fprintf_s( logfile , "%s:[-->GAME_GetCameraTargetPositionZ<-- ] RETURN-> %f\n" , currentDateTime( ).c_str( ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetCancelledStructure )( );
GAME_GetCancelledStructure GAME_GetCancelledStructureorg = NULL;
GAME_GetCancelledStructure GAME_GetCancelledStructureold = NULL;

HUNIT __cdecl GAME_GetCancelledStructuremy( )
{
	fprintf_s( logfile , "%s\n" , "GetCancelledStructuremy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetCancelledStructureold( );
	fprintf_s( logfile , "%s:[-->GAME_GetCancelledStructure<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetChangingUnit )( );
GAME_GetChangingUnit GAME_GetChangingUnitorg = NULL;
GAME_GetChangingUnit GAME_GetChangingUnitold = NULL;

HUNIT __cdecl GAME_GetChangingUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetChangingUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetChangingUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetChangingUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYER( __cdecl *GAME_GetChangingUnitPrevOwner )( );
GAME_GetChangingUnitPrevOwner GAME_GetChangingUnitPrevOwnerorg = NULL;
GAME_GetChangingUnitPrevOwner GAME_GetChangingUnitPrevOwnerold = NULL;

HPLAYER __cdecl GAME_GetChangingUnitPrevOwnermy( )
{
	fprintf_s( logfile , "%s\n" , "GetChangingUnitPrevOwnermy" );
	fflush( logfile );

	HPLAYER retvalue = GAME_GetChangingUnitPrevOwnerold( );
	fprintf_s( logfile , "%s:[-->GAME_GetChangingUnitPrevOwner<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HBUTTON( __cdecl *GAME_GetClickedButton )( );
GAME_GetClickedButton GAME_GetClickedButtonorg = NULL;
GAME_GetClickedButton GAME_GetClickedButtonold = NULL;

HBUTTON __cdecl GAME_GetClickedButtonmy( )
{
	fprintf_s( logfile , "%s\n" , "GetClickedButtonmy" );
	fflush( logfile );

	HBUTTON retvalue = GAME_GetClickedButtonold( );
	fprintf_s( logfile , "%s:[-->GAME_GetClickedButton<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HDIALOG( __cdecl *GAME_GetClickedDialog )( );
GAME_GetClickedDialog GAME_GetClickedDialogorg = NULL;
GAME_GetClickedDialog GAME_GetClickedDialogold = NULL;

HDIALOG __cdecl GAME_GetClickedDialogmy( )
{
	fprintf_s( logfile , "%s\n" , "GetClickedDialogmy" );
	fflush( logfile );

	HDIALOG retvalue = GAME_GetClickedDialogold( );
	fprintf_s( logfile , "%s:[-->GAME_GetClickedDialog<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetConstructedStructure )( );
GAME_GetConstructedStructure GAME_GetConstructedStructureorg = NULL;
GAME_GetConstructedStructure GAME_GetConstructedStructureold = NULL;

HUNIT __cdecl GAME_GetConstructedStructuremy( )
{
	fprintf_s( logfile , "%s\n" , "GetConstructedStructuremy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetConstructedStructureold( );
	fprintf_s( logfile , "%s:[-->GAME_GetConstructedStructure<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetConstructingStructure )( );
GAME_GetConstructingStructure GAME_GetConstructingStructureorg = NULL;
GAME_GetConstructingStructure GAME_GetConstructingStructureold = NULL;

HUNIT __cdecl GAME_GetConstructingStructuremy( )
{
	fprintf_s( logfile , "%s\n" , "GetConstructingStructuremy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetConstructingStructureold( );
	fprintf_s( logfile , "%s:[-->GAME_GetConstructingStructure<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HMAPDENSITY( __cdecl *GAME_GetCreatureDensity )( );
GAME_GetCreatureDensity GAME_GetCreatureDensityorg = NULL;
GAME_GetCreatureDensity GAME_GetCreatureDensityold = NULL;

HMAPDENSITY __cdecl GAME_GetCreatureDensitymy( )
{
	fprintf_s( logfile , "%s\n" , "GetCreatureDensitymy" );
	fflush( logfile );

	HMAPDENSITY retvalue = GAME_GetCreatureDensityold( );
	fprintf_s( logfile , "%s:[-->GAME_GetCreatureDensity<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetCreepCamp )( int arg1 , int arg2 , BOOL arg3 );
GAME_GetCreepCamp GAME_GetCreepCamporg = NULL;
GAME_GetCreepCamp GAME_GetCreepCampold = NULL;

HUNIT __cdecl GAME_GetCreepCampmy( int arg1 , int arg2 , BOOL arg3 )
{
	fprintf_s( logfile , "%s\n" , "GetCreepCampmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetCreepCampold( arg1 , arg2 , arg3 );
	fprintf_s( logfile , "%s:[-->GAME_GetCreepCamp<--  arg1: %i arg2: %i arg3: %s] RETURN-> %X\n" , currentDateTime( ).c_str( ) , arg1 , arg2 , arg3 ? "TRUE\n" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_GetCreepCampFilterState )( );
GAME_GetCreepCampFilterState GAME_GetCreepCampFilterStateorg = NULL;
GAME_GetCreepCampFilterState GAME_GetCreepCampFilterStateold = NULL;

BOOL __cdecl GAME_GetCreepCampFilterStatemy( )
{
	fprintf_s( logfile , "%s" , "GetCreepCampFilterStatemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_GetCreepCampFilterStateold( );
	fprintf_s( logfile , "%s:[-->GAME_GetCreepCampFilterState<-- ] RETURN-> %s\n" , currentDateTime( ).c_str( ) , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_GetCustomCampaignButtonVisible )( int whichButton );
GAME_GetCustomCampaignButtonVisible GAME_GetCustomCampaignButtonVisibleorg = NULL;
GAME_GetCustomCampaignButtonVisible GAME_GetCustomCampaignButtonVisibleold = NULL;

BOOL __cdecl GAME_GetCustomCampaignButtonVisiblemy( int whichButton )
{
	fprintf_s( logfile , "%s" , "GetCustomCampaignButtonVisiblemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_GetCustomCampaignButtonVisibleold( whichButton );
	fprintf_s( logfile , "%s:[-->GAME_GetCustomCampaignButtonVisible<--  whichButton: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichButton , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetDecayingUnit )( );
GAME_GetDecayingUnit GAME_GetDecayingUnitorg = NULL;
GAME_GetDecayingUnit GAME_GetDecayingUnitold = NULL;

HUNIT __cdecl GAME_GetDecayingUnitmy( )
{
	fprintf_s( logfile , "%s" , "GetDecayingUnitmy\n" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetDecayingUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetDecayingUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HGAMEDIFFICULTY( __cdecl *GAME_GetDefaultDifficulty )( );
GAME_GetDefaultDifficulty GAME_GetDefaultDifficultyorg = NULL;
GAME_GetDefaultDifficulty GAME_GetDefaultDifficultyold = NULL;

HGAMEDIFFICULTY __cdecl GAME_GetDefaultDifficultymy( )
{
	fprintf_s( logfile , "%s\n" , "GetDefaultDifficultymy" );
	fflush( logfile );

	HGAMEDIFFICULTY retvalue = GAME_GetDefaultDifficultyold( );
	fprintf_s( logfile , "%s:[-->GAME_GetDefaultDifficulty<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetDestructableLife )( HDESTRUCTABLE d );
GAME_GetDestructableLife GAME_GetDestructableLifeorg = NULL;
GAME_GetDestructableLife GAME_GetDestructableLifeold = NULL;

DWFP __cdecl GAME_GetDestructableLifemy( HDESTRUCTABLE d )
{
	fprintf_s( logfile , "%s\n" , "GetDestructableLifemy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetDestructableLifeold( d );
	fprintf_s( logfile , "%s:[-->GAME_GetDestructableLife<--  d: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , d , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetDestructableMaxLife )( HDESTRUCTABLE d );
GAME_GetDestructableMaxLife GAME_GetDestructableMaxLifeorg = NULL;
GAME_GetDestructableMaxLife GAME_GetDestructableMaxLifeold = NULL;

DWFP __cdecl GAME_GetDestructableMaxLifemy( HDESTRUCTABLE d )
{
	fprintf_s( logfile , "%s\n" , "GetDestructableMaxLifemy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetDestructableMaxLifeold( d );
	fprintf_s( logfile , "%s:[-->GAME_GetDestructableMaxLife<--  d: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , d , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_GetDestructableName )( HDESTRUCTABLE d );
GAME_GetDestructableName GAME_GetDestructableNameorg = NULL;
GAME_GetDestructableName GAME_GetDestructableNameold = NULL;

DWORD __cdecl GAME_GetDestructableNamemy( HDESTRUCTABLE d )
{
	fprintf_s( logfile , "%s\n" , "GetDestructableNamemy" );
	fflush( logfile );

	DWORD retvalue = GAME_GetDestructableNameold( d );
	fprintf_s( logfile , "%s:[-->GAME_GetDestructableName<--  d: %X] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , d , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetDestructableOccluderHeight )( HDESTRUCTABLE d );
GAME_GetDestructableOccluderHeight GAME_GetDestructableOccluderHeightorg = NULL;
GAME_GetDestructableOccluderHeight GAME_GetDestructableOccluderHeightold = NULL;

DWFP __cdecl GAME_GetDestructableOccluderHeightmy( HDESTRUCTABLE d )
{
	fprintf_s( logfile , "%s\n" , "GetDestructableOccluderHeightmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetDestructableOccluderHeightold( d );
	fprintf_s( logfile , "%s:[-->GAME_GetDestructableOccluderHeight<--  d: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , d , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetDestructableTypeId )( HDESTRUCTABLE d );
GAME_GetDestructableTypeId GAME_GetDestructableTypeIdorg = NULL;
GAME_GetDestructableTypeId GAME_GetDestructableTypeIdold = NULL;

int __cdecl GAME_GetDestructableTypeIdmy( HDESTRUCTABLE d )
{
	fprintf_s( logfile , "%s\n" , "GetDestructableTypeIdmy" );
	fflush( logfile );

	int retvalue = GAME_GetDestructableTypeIdold( d );
	fprintf_s( logfile , "%s:[-->GAME_GetDestructableTypeId<--  d: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , d , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetDestructableX )( HDESTRUCTABLE d );
GAME_GetDestructableX GAME_GetDestructableXorg = NULL;
GAME_GetDestructableX GAME_GetDestructableXold = NULL;

DWFP __cdecl GAME_GetDestructableXmy( HDESTRUCTABLE d )
{
	fprintf_s( logfile , "%s\n" , "GetDestructableXmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetDestructableXold( d );
	fprintf_s( logfile , "%s:[-->GAME_GetDestructableX<--  d: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , d , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetDestructableY )( HDESTRUCTABLE d );
GAME_GetDestructableY GAME_GetDestructableYorg = NULL;
GAME_GetDestructableY GAME_GetDestructableYold = NULL;

DWFP __cdecl GAME_GetDestructableYmy( HDESTRUCTABLE d )
{
	fprintf_s( logfile , "%s\n" , "GetDestructableYmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetDestructableYold( d );
	fprintf_s( logfile , "%s:[-->GAME_GetDestructableY<--  d: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , d , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetDetectedUnit )( );
GAME_GetDetectedUnit GAME_GetDetectedUnitorg = NULL;
GAME_GetDetectedUnit GAME_GetDetectedUnitold = NULL;

HUNIT __cdecl GAME_GetDetectedUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetDetectedUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetDetectedUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetDetectedUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetDyingUnit )( );
GAME_GetDyingUnit GAME_GetDyingUnitorg = NULL;
GAME_GetDyingUnit GAME_GetDyingUnitold = NULL;

HUNIT __cdecl GAME_GetDyingUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetDyingUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetDyingUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetDyingUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetEnemyBase )( );
GAME_GetEnemyBase GAME_GetEnemyBaseorg = NULL;
GAME_GetEnemyBase GAME_GetEnemyBaseold = NULL;

HUNIT __cdecl GAME_GetEnemyBasemy( )
{
	fprintf_s( logfile , "%s\n" , "GetEnemyBasemy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetEnemyBaseold( );
	fprintf_s( logfile , "%s:[-->GAME_GetEnemyBase<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetEnemyExpansion )( );
GAME_GetEnemyExpansion GAME_GetEnemyExpansionorg = NULL;
GAME_GetEnemyExpansion GAME_GetEnemyExpansionold = NULL;

HUNIT __cdecl GAME_GetEnemyExpansionmy( )
{
	fprintf_s( logfile , "%s\n" , "GetEnemyExpansionmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetEnemyExpansionold( );
	fprintf_s( logfile , "%s:[-->GAME_GetEnemyExpansion<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetEnemyPower )( );
GAME_GetEnemyPower GAME_GetEnemyPowerorg = NULL;
GAME_GetEnemyPower GAME_GetEnemyPowerold = NULL;

int __cdecl GAME_GetEnemyPowermy( )
{
	fprintf_s( logfile , "%s\n" , "GetEnemyPowermy" );
	fflush( logfile );

	int retvalue = GAME_GetEnemyPowerold( );
	fprintf_s( logfile , "%s:[-->GAME_GetEnemyPower<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetEnteringUnit )( );
GAME_GetEnteringUnit GAME_GetEnteringUnitorg = NULL;
GAME_GetEnteringUnit GAME_GetEnteringUnitold = NULL;

HUNIT __cdecl GAME_GetEnteringUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetEnteringUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetEnteringUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetEnteringUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HDESTRUCTABLE( __cdecl *GAME_GetEnumDestructable )( );
GAME_GetEnumDestructable GAME_GetEnumDestructableorg = NULL;
GAME_GetEnumDestructable GAME_GetEnumDestructableold = NULL;

HDESTRUCTABLE __cdecl GAME_GetEnumDestructablemy( )
{
	fprintf_s( logfile , "%s\n" , "GetEnumDestructablemy" );
	fflush( logfile );

	HDESTRUCTABLE retvalue = GAME_GetEnumDestructableold( );
	fprintf_s( logfile , "%s:[-->GAME_GetEnumDestructable<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HITEM( __cdecl *GAME_GetEnumItem )( );
GAME_GetEnumItem GAME_GetEnumItemorg = NULL;
GAME_GetEnumItem GAME_GetEnumItemold = NULL;

HITEM __cdecl GAME_GetEnumItemmy( )
{
	fprintf_s( logfile , "%s\n" , "GetEnumItemmy" );
	fflush( logfile );

	HITEM retvalue = GAME_GetEnumItemold( );
	fprintf_s( logfile , "%s:[-->GAME_GetEnumItem<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYER( __cdecl *GAME_GetEnumPlayer )( );
GAME_GetEnumPlayer GAME_GetEnumPlayerorg = NULL;
GAME_GetEnumPlayer GAME_GetEnumPlayerold = NULL;

HPLAYER __cdecl GAME_GetEnumPlayermy( )
{
	fprintf_s( logfile , "%s\n" , "GetEnumPlayermy" );
	fflush( logfile );

	HPLAYER retvalue = GAME_GetEnumPlayerold( );
	fprintf_s( logfile , "%s:[-->GAME_GetEnumPlayer<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetEnumUnit )( );
GAME_GetEnumUnit GAME_GetEnumUnitorg = NULL;
GAME_GetEnumUnit GAME_GetEnumUnitold = NULL;

HUNIT __cdecl GAME_GetEnumUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetEnumUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetEnumUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetEnumUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetEventDamage )( );
GAME_GetEventDamage GAME_GetEventDamageorg = NULL;
GAME_GetEventDamage GAME_GetEventDamageold = NULL;

DWFP __cdecl GAME_GetEventDamagemy( )
{
	fprintf_s( logfile , "%s\n" , "GetEventDamagemy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetEventDamageold( );
	fprintf_s( logfile , "%s:[-->GAME_GetEventDamage<-- ] RETURN-> %f\n" , currentDateTime( ).c_str( ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetEventDamageSource )( );
GAME_GetEventDamageSource GAME_GetEventDamageSourceorg = NULL;
GAME_GetEventDamageSource GAME_GetEventDamageSourceold = NULL;

HUNIT __cdecl GAME_GetEventDamageSourcemy( )
{
	fprintf_s( logfile , "%s\n" , "GetEventDamageSourcemy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetEventDamageSourceold( );
	fprintf_s( logfile , "%s:[-->GAME_GetEventDamageSource<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYER( __cdecl *GAME_GetEventDetectingPlayer )( );
GAME_GetEventDetectingPlayer GAME_GetEventDetectingPlayerorg = NULL;
GAME_GetEventDetectingPlayer GAME_GetEventDetectingPlayerold = NULL;

HPLAYER __cdecl GAME_GetEventDetectingPlayermy( )
{
	fprintf_s( logfile , "%s\n" , "GetEventDetectingPlayermy" );
	fflush( logfile );

	HPLAYER retvalue = GAME_GetEventDetectingPlayerold( );
	fprintf_s( logfile , "%s:[-->GAME_GetEventDetectingPlayer<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HGAMESTATE( __cdecl *GAME_GetEventGameState )( );
GAME_GetEventGameState GAME_GetEventGameStateorg = NULL;
GAME_GetEventGameState GAME_GetEventGameStateold = NULL;

HGAMESTATE __cdecl GAME_GetEventGameStatemy( )
{
	fprintf_s( logfile , "%s\n" , "GetEventGameStatemy" );
	fflush( logfile );

	HGAMESTATE retvalue = GAME_GetEventGameStateold( );
	fprintf_s( logfile , "%s:[-->GAME_GetEventGameState<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_GetEventPlayerChatString )( );
GAME_GetEventPlayerChatString GAME_GetEventPlayerChatStringorg = NULL;
GAME_GetEventPlayerChatString GAME_GetEventPlayerChatStringold = NULL;

DWORD __cdecl GAME_GetEventPlayerChatStringmy( )
{
	fprintf_s( logfile , "%s\n" , "GetEventPlayerChatStringmy" );
	fflush( logfile );

	DWORD retvalue = GAME_GetEventPlayerChatStringold( );
	fprintf_s( logfile , "%s:[-->GAME_GetEventPlayerChatString<-- ] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_GetEventPlayerChatStringMatched )( );
GAME_GetEventPlayerChatStringMatched GAME_GetEventPlayerChatStringMatchedorg = NULL;
GAME_GetEventPlayerChatStringMatched GAME_GetEventPlayerChatStringMatchedold = NULL;

DWORD __cdecl GAME_GetEventPlayerChatStringMatchedmy( )
{
	fprintf_s( logfile , "%s\n" , "GetEventPlayerChatStringMatchedmy" );
	fflush( logfile );

	DWORD retvalue = GAME_GetEventPlayerChatStringMatchedold( );
	fprintf_s( logfile , "%s:[-->GAME_GetEventPlayerChatStringMatched<-- ] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYERSTATE( __cdecl *GAME_GetEventPlayerState )( );
GAME_GetEventPlayerState GAME_GetEventPlayerStateorg = NULL;
GAME_GetEventPlayerState GAME_GetEventPlayerStateold = NULL;

HPLAYERSTATE __cdecl GAME_GetEventPlayerStatemy( )
{
	fprintf_s( logfile , "%s\n" , "GetEventPlayerStatemy" );
	fflush( logfile );

	HPLAYERSTATE retvalue = GAME_GetEventPlayerStateold( );
	fprintf_s( logfile , "%s:[-->GAME_GetEventPlayerState<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetEventTargetUnit )( );
GAME_GetEventTargetUnit GAME_GetEventTargetUnitorg = NULL;
GAME_GetEventTargetUnit GAME_GetEventTargetUnitold = NULL;

HUNIT __cdecl GAME_GetEventTargetUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetEventTargetUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetEventTargetUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetEventTargetUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNITSTATE( __cdecl *GAME_GetEventUnitState )( );
GAME_GetEventUnitState GAME_GetEventUnitStateorg = NULL;
GAME_GetEventUnitState GAME_GetEventUnitStateold = NULL;

HUNITSTATE __cdecl GAME_GetEventUnitStatemy( )
{
	fprintf_s( logfile , "%s\n" , "GetEventUnitStatemy" );
	fflush( logfile );

	HUNITSTATE retvalue = GAME_GetEventUnitStateold( );
	fprintf_s( logfile , "%s:[-->GAME_GetEventUnitState<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetExpansionFoe )( );
GAME_GetExpansionFoe GAME_GetExpansionFoeorg = NULL;
GAME_GetExpansionFoe GAME_GetExpansionFoeold = NULL;

HUNIT __cdecl GAME_GetExpansionFoemy( )
{
	fprintf_s( logfile , "%s\n" , "GetExpansionFoemy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetExpansionFoeold( );
	fprintf_s( logfile , "%s:[-->GAME_GetExpansionFoe<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetExpansionPeon )( );
GAME_GetExpansionPeon GAME_GetExpansionPeonorg = NULL;
GAME_GetExpansionPeon GAME_GetExpansionPeonold = NULL;

HUNIT __cdecl GAME_GetExpansionPeonmy( )
{
	fprintf_s( logfile , "%s\n" , "GetExpansionPeonmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetExpansionPeonold( );
	fprintf_s( logfile , "%s:[-->GAME_GetExpansionPeon<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetExpansionX )( );
GAME_GetExpansionX GAME_GetExpansionXorg = NULL;
GAME_GetExpansionX GAME_GetExpansionXold = NULL;

int __cdecl GAME_GetExpansionXmy( )
{
	fprintf_s( logfile , "%s\n" , "GetExpansionXmy" );
	fflush( logfile );

	int retvalue = GAME_GetExpansionXold( );
	fprintf_s( logfile , "%s:[-->GAME_GetExpansionX<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetExpansionY )( );
GAME_GetExpansionY GAME_GetExpansionYorg = NULL;
GAME_GetExpansionY GAME_GetExpansionYold = NULL;

int __cdecl GAME_GetExpansionYmy( )
{
	fprintf_s( logfile , "%s\n" , "GetExpansionYmy" );
	fflush( logfile );

	int retvalue = GAME_GetExpansionYold( );
	fprintf_s( logfile , "%s:[-->GAME_GetExpansionY<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTIMER( __cdecl *GAME_GetExpiredTimer )( );
GAME_GetExpiredTimer GAME_GetExpiredTimerorg = NULL;
GAME_GetExpiredTimer GAME_GetExpiredTimerold = NULL;

HTIMER __cdecl GAME_GetExpiredTimermy( )
{
	fprintf_s( logfile , "%s\n" , "GetExpiredTimermy" );
	fflush( logfile );

	HTIMER retvalue = GAME_GetExpiredTimerold( );
	fprintf_s( logfile , "%s:[-->GAME_GetExpiredTimer<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HDESTRUCTABLE( __cdecl *GAME_GetFilterDestructable )( );
GAME_GetFilterDestructable GAME_GetFilterDestructableorg = NULL;
GAME_GetFilterDestructable GAME_GetFilterDestructableold = NULL;

HDESTRUCTABLE __cdecl GAME_GetFilterDestructablemy( )
{
	fprintf_s( logfile , "%s\n" , "GetFilterDestructablemy" );
	fflush( logfile );

	HDESTRUCTABLE retvalue = GAME_GetFilterDestructableold( );
	fprintf_s( logfile , "%s:[-->GAME_GetFilterDestructable<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HITEM( __cdecl *GAME_GetFilterItem )( );
GAME_GetFilterItem GAME_GetFilterItemorg = NULL;
GAME_GetFilterItem GAME_GetFilterItemold = NULL;

HITEM __cdecl GAME_GetFilterItemmy( )
{
	fprintf_s( logfile , "%s\n" , "GetFilterItemmy" );
	fflush( logfile );

	HITEM retvalue = GAME_GetFilterItemold( );
	fprintf_s( logfile , "%s:[-->GAME_GetFilterItem<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYER( __cdecl *GAME_GetFilterPlayer )( );
GAME_GetFilterPlayer GAME_GetFilterPlayerorg = NULL;
GAME_GetFilterPlayer GAME_GetFilterPlayerold = NULL;

HPLAYER __cdecl GAME_GetFilterPlayermy( )
{
	fprintf_s( logfile , "%s\n" , "GetFilterPlayermy" );
	fflush( logfile );

	HPLAYER retvalue = GAME_GetFilterPlayerold( );
	fprintf_s( logfile , "%s:[-->GAME_GetFilterPlayer<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetFilterUnit )( );
GAME_GetFilterUnit GAME_GetFilterUnitorg = NULL;
GAME_GetFilterUnit GAME_GetFilterUnitold = NULL;

HUNIT __cdecl GAME_GetFilterUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetFilterUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetFilterUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetFilterUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetFloatGameState )( HFGAMESTATE whichFloatGameState );
GAME_GetFloatGameState GAME_GetFloatGameStateorg = NULL;
GAME_GetFloatGameState GAME_GetFloatGameStateold = NULL;

DWFP __cdecl GAME_GetFloatGameStatemy( HFGAMESTATE whichFloatGameState )
{
	fprintf_s( logfile , "%s\n" , "GetFloatGameStatemy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetFloatGameStateold( whichFloatGameState );
	fprintf_s( logfile , "%s:[-->GAME_GetFloatGameState<--  whichFloatGameState: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichFloatGameState , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetFoodMade )( int unitId );
GAME_GetFoodMade GAME_GetFoodMadeorg = NULL;
GAME_GetFoodMade GAME_GetFoodMadeold = NULL;

int __cdecl GAME_GetFoodMademy( int unitId )
{
	fprintf_s( logfile , "%s\n" , "GetFoodMademy" );
	fflush( logfile );

	int retvalue = GAME_GetFoodMadeold( unitId );
	fprintf_s( logfile , "%s:[-->GAME_GetFoodMade<--  unitId: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , unitId , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetFoodUsed )( int unitId );
GAME_GetFoodUsed GAME_GetFoodUsedorg = NULL;
GAME_GetFoodUsed GAME_GetFoodUsedold = NULL;

int __cdecl GAME_GetFoodUsedmy( int unitId )
{
	fprintf_s( logfile , "%s\n" , "GetFoodUsedmy" );
	fflush( logfile );

	int retvalue = GAME_GetFoodUsedold( unitId );
	fprintf_s( logfile , "%s:[-->GAME_GetFoodUsed<--  unitId: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , unitId , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HGAMEDIFFICULTY( __cdecl *GAME_GetGameDifficulty )( );
GAME_GetGameDifficulty GAME_GetGameDifficultyorg = NULL;
GAME_GetGameDifficulty GAME_GetGameDifficultyold = NULL;

HGAMEDIFFICULTY __cdecl GAME_GetGameDifficultymy( )
{
	fprintf_s( logfile , "%s\n" , "GetGameDifficultymy" );
	fflush( logfile );

	HGAMEDIFFICULTY retvalue = GAME_GetGameDifficultyold( );
	fprintf_s( logfile , "%s:[-->GAME_GetGameDifficulty<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HPLACEMENT( __cdecl *GAME_GetGamePlacement )( );
GAME_GetGamePlacement GAME_GetGamePlacementorg = NULL;
GAME_GetGamePlacement GAME_GetGamePlacementold = NULL;

HPLACEMENT __cdecl GAME_GetGamePlacementmy( )
{
	fprintf_s( logfile , "%s\n" , "GetGamePlacementmy" );
	fflush( logfile );

	HPLACEMENT retvalue = GAME_GetGamePlacementold( );
	fprintf_s( logfile , "%s:[-->GAME_GetGamePlacement<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HGAMESPEED( __cdecl *GAME_GetGameSpeed )( );
GAME_GetGameSpeed GAME_GetGameSpeedorg = NULL;
GAME_GetGameSpeed GAME_GetGameSpeedold = NULL;

HGAMESPEED __cdecl GAME_GetGameSpeedmy( )
{
	fprintf_s( logfile , "%s\n" , "GetGameSpeedmy" );
	fflush( logfile );

	HGAMESPEED retvalue = GAME_GetGameSpeedold( );
	fprintf_s( logfile , "%s:[-->GAME_GetGameSpeed<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HGAMETYPE( __cdecl *GAME_GetGameTypeSelected )( );
GAME_GetGameTypeSelected GAME_GetGameTypeSelectedorg = NULL;
GAME_GetGameTypeSelected GAME_GetGameTypeSelectedold = NULL;

HGAMETYPE __cdecl GAME_GetGameTypeSelectedmy( )
{
	fprintf_s( logfile , "%s\n" , "GetGameTypeSelectedmy" );
	fflush( logfile );

	HGAMETYPE retvalue = GAME_GetGameTypeSelectedold( );
	fprintf_s( logfile , "%s:[-->GAME_GetGameTypeSelected<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetGoldOwned )( );
GAME_GetGoldOwned GAME_GetGoldOwnedorg = NULL;
GAME_GetGoldOwned GAME_GetGoldOwnedold = NULL;

int __cdecl GAME_GetGoldOwnedmy( )
{
	fprintf_s( logfile , "%s\n" , "GetGoldOwnedmy" );
	fflush( logfile );

	int retvalue = GAME_GetGoldOwnedold( );
	fprintf_s( logfile , "%s:[-->GAME_GetGoldOwned<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetHandleId )( HHANDLE h );
GAME_GetHandleId GAME_GetHandleIdorg = NULL;
GAME_GetHandleId GAME_GetHandleIdold = NULL;

int __cdecl GAME_GetHandleIdmy( HHANDLE h )
{
	fprintf_s( logfile , "%s\n" , "GetHandleIdmy" );
	fflush( logfile );

	int retvalue = GAME_GetHandleIdold( h );
	fprintf_s( logfile , "%s:[-->GAME_GetHandleId<--  h: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , h , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetHeroAgi )( HUNIT whichHero , BOOL includeBonuses );
GAME_GetHeroAgi GAME_GetHeroAgiorg = NULL;
GAME_GetHeroAgi GAME_GetHeroAgiold = NULL;

int __cdecl GAME_GetHeroAgimy( HUNIT whichHero , BOOL includeBonuses )
{
	fprintf_s( logfile , "%s\n" , "GetHeroAgimy" );
	fflush( logfile );

	int retvalue = GAME_GetHeroAgiold( whichHero , includeBonuses );
	fprintf_s( logfile , "%s:[-->GAME_GetHeroAgi<--  whichHero: %X includeBonuses: %s] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichHero , includeBonuses ? "TRUE\n" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetHeroId )( );
GAME_GetHeroId GAME_GetHeroIdorg = NULL;
GAME_GetHeroId GAME_GetHeroIdold = NULL;

int __cdecl GAME_GetHeroIdmy( )
{
	fprintf_s( logfile , "%s" , "GetHeroIdmy\n" );
	fflush( logfile );

	int retvalue = GAME_GetHeroIdold( );
	fprintf_s( logfile , "%s:[-->GAME_GetHeroId<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetHeroInt )( HUNIT whichHero , BOOL includeBonuses );
GAME_GetHeroInt GAME_GetHeroIntorg = NULL;
GAME_GetHeroInt GAME_GetHeroIntold = NULL;

int __cdecl GAME_GetHeroIntmy( HUNIT whichHero , BOOL includeBonuses )
{
	fprintf_s( logfile , "%s\n" , "GetHeroIntmy" );
	fflush( logfile );

	int retvalue = GAME_GetHeroIntold( whichHero , includeBonuses );
	fprintf_s( logfile , "%s:[-->GAME_GetHeroInt<--  whichHero: %X includeBonuses: %s] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichHero , includeBonuses ? "TRUE\n" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetHeroLevel )( HUNIT whichHero );
GAME_GetHeroLevel GAME_GetHeroLevelorg = NULL;
GAME_GetHeroLevel GAME_GetHeroLevelold = NULL;

int __cdecl GAME_GetHeroLevelmy( HUNIT whichHero )
{
	fprintf_s( logfile , "%s" , "GetHeroLevelmy\n" );
	fflush( logfile );

	int retvalue = GAME_GetHeroLevelold( whichHero );
	fprintf_s( logfile , "%s:[-->GAME_GetHeroLevel<--  whichHero: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichHero , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetHeroLevelAI )( );
GAME_GetHeroLevelAI GAME_GetHeroLevelAIorg = NULL;
GAME_GetHeroLevelAI GAME_GetHeroLevelAIold = NULL;

int __cdecl GAME_GetHeroLevelAImy( )
{
	fprintf_s( logfile , "%s\n" , "GetHeroLevelAImy" );
	fflush( logfile );

	int retvalue = GAME_GetHeroLevelAIold( );
	fprintf_s( logfile , "%s:[-->GAME_GetHeroLevelAI<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_GetHeroProperName )( HUNIT whichHero );
GAME_GetHeroProperName GAME_GetHeroProperNameorg = NULL;
GAME_GetHeroProperName GAME_GetHeroProperNameold = NULL;

DWORD __cdecl GAME_GetHeroProperNamemy( HUNIT whichHero )
{
	fprintf_s( logfile , "%s\n" , "GetHeroProperNamemy" );
	fflush( logfile );

	DWORD retvalue = GAME_GetHeroProperNameold( whichHero );
	fprintf_s( logfile , "%s:[-->GAME_GetHeroProperName<--  whichHero: %X] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , whichHero , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetHeroSkillPoints )( HUNIT whichHero );
GAME_GetHeroSkillPoints GAME_GetHeroSkillPointsorg = NULL;
GAME_GetHeroSkillPoints GAME_GetHeroSkillPointsold = NULL;

int __cdecl GAME_GetHeroSkillPointsmy( HUNIT whichHero )
{
	fprintf_s( logfile , "%s\n" , "GetHeroSkillPointsmy" );
	fflush( logfile );

	int retvalue = GAME_GetHeroSkillPointsold( whichHero );
	fprintf_s( logfile , "%s:[-->GAME_GetHeroSkillPoints<--  whichHero: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichHero , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetHeroStr )( HUNIT whichHero , BOOL includeBonuses );
GAME_GetHeroStr GAME_GetHeroStrorg = NULL;
GAME_GetHeroStr GAME_GetHeroStrold = NULL;

int __cdecl GAME_GetHeroStrmy( HUNIT whichHero , BOOL includeBonuses )
{
	fprintf_s( logfile , "%s\n" , "GetHeroStrmy" );
	fflush( logfile );

	int retvalue = GAME_GetHeroStrold( whichHero , includeBonuses );
	fprintf_s( logfile , "%s:[-->GAME_GetHeroStr<--  whichHero: %X includeBonuses: %s] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichHero , includeBonuses ? "TRUE\n" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetHeroXP )( HUNIT whichHero );
GAME_GetHeroXP GAME_GetHeroXPorg = NULL;
GAME_GetHeroXP GAME_GetHeroXPold = NULL;

int __cdecl GAME_GetHeroXPmy( HUNIT whichHero )
{
	fprintf_s( logfile , "%s" , "GetHeroXPmy\n" );
	fflush( logfile );

	int retvalue = GAME_GetHeroXPold( whichHero );
	fprintf_s( logfile , "%s:[-->GAME_GetHeroXP<--  whichHero: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichHero , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetIntegerGameState )( HIGAMESTATE whichIntegerGameState );
GAME_GetIntegerGameState GAME_GetIntegerGameStateorg = NULL;
GAME_GetIntegerGameState GAME_GetIntegerGameStateold = NULL;

int __cdecl GAME_GetIntegerGameStatemy( HIGAMESTATE whichIntegerGameState )
{
	fprintf_s( logfile , "%s\n" , "GetIntegerGameStatemy" );
	fflush( logfile );

	int retvalue = GAME_GetIntegerGameStateold( whichIntegerGameState );
	fprintf_s( logfile , "%s:[-->GAME_GetIntegerGameState<--  whichIntegerGameState: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichIntegerGameState , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetIssuedOrderId )( );
GAME_GetIssuedOrderId GAME_GetIssuedOrderIdorg = NULL;
GAME_GetIssuedOrderId GAME_GetIssuedOrderIdold = NULL;

int __cdecl GAME_GetIssuedOrderIdmy( )
{
	fprintf_s( logfile , "%s\n" , "GetIssuedOrderIdmy" );
	fflush( logfile );

	int retvalue = GAME_GetIssuedOrderIdold( );
	fprintf_s( logfile , "%s:[-->GAME_GetIssuedOrderId<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetItemCharges )( HITEM whichItem );
GAME_GetItemCharges GAME_GetItemChargesorg = NULL;
GAME_GetItemCharges GAME_GetItemChargesold = NULL;

int __cdecl GAME_GetItemChargesmy( HITEM whichItem )
{
	fprintf_s( logfile , "%s\n" , "GetItemChargesmy" );
	fflush( logfile );

	int retvalue = GAME_GetItemChargesold( whichItem );
	fprintf_s( logfile , "%s:[-->GAME_GetItemCharges<--  whichItem: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichItem , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetItemLevel )( HITEM whichItem );
GAME_GetItemLevel GAME_GetItemLevelorg = NULL;
GAME_GetItemLevel GAME_GetItemLevelold = NULL;

int __cdecl GAME_GetItemLevelmy( HITEM whichItem )
{
	fprintf_s( logfile , "%s\n" , "GetItemLevelmy" );
	fflush( logfile );

	int retvalue = GAME_GetItemLevelold( whichItem );
	fprintf_s( logfile , "%s:[-->GAME_GetItemLevel<--  whichItem: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichItem , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_GetItemName )( HITEM whichItem );
GAME_GetItemName GAME_GetItemNameorg = NULL;
GAME_GetItemName GAME_GetItemNameold = NULL;

DWORD __cdecl GAME_GetItemNamemy( HITEM whichItem )
{
	fprintf_s( logfile , "%s\n" , "GetItemNamemy" );
	fflush( logfile );

	DWORD retvalue = GAME_GetItemNameold( whichItem );
	fprintf_s( logfile , "%s:[-->GAME_GetItemName<--  whichItem: %X] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , whichItem , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYER( __cdecl *GAME_GetItemPlayer )( HITEM whichItem );
GAME_GetItemPlayer GAME_GetItemPlayerorg = NULL;
GAME_GetItemPlayer GAME_GetItemPlayerold = NULL;

HPLAYER __cdecl GAME_GetItemPlayermy( HITEM whichItem )
{
	fprintf_s( logfile , "%s\n" , "GetItemPlayermy" );
	fflush( logfile );

	HPLAYER retvalue = GAME_GetItemPlayerold( whichItem );
	fprintf_s( logfile , "%s:[-->GAME_GetItemPlayer<--  whichItem: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichItem , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HITEMTYPE( __cdecl *GAME_GetItemType )( HITEM whichItem );
GAME_GetItemType GAME_GetItemTypeorg = NULL;
GAME_GetItemType GAME_GetItemTypeold = NULL;

HITEMTYPE __cdecl GAME_GetItemTypemy( HITEM whichItem )
{
	fprintf_s( logfile , "%s\n" , "GetItemTypemy" );
	fflush( logfile );

	HITEMTYPE retvalue = GAME_GetItemTypeold( whichItem );
	fprintf_s( logfile , "%s:[-->GAME_GetItemType<--  whichItem: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichItem , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetItemTypeId )( HITEM i );
GAME_GetItemTypeId GAME_GetItemTypeIdorg = NULL;
GAME_GetItemTypeId GAME_GetItemTypeIdold = NULL;

int __cdecl GAME_GetItemTypeIdmy( HITEM i )
{
	fprintf_s( logfile , "%s\n" , "GetItemTypeIdmy" );
	fflush( logfile );

	int retvalue = GAME_GetItemTypeIdold( i );
	fprintf_s( logfile , "%s:[-->GAME_GetItemTypeId<--  i: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , i , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetItemUserData )( HITEM whichItem );
GAME_GetItemUserData GAME_GetItemUserDataorg = NULL;
GAME_GetItemUserData GAME_GetItemUserDataold = NULL;

int __cdecl GAME_GetItemUserDatamy( HITEM whichItem )
{
	fprintf_s( logfile , "%s\n" , "GetItemUserDatamy" );
	fflush( logfile );

	int retvalue = GAME_GetItemUserDataold( whichItem );
	fprintf_s( logfile , "%s:[-->GAME_GetItemUserData<--  whichItem: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichItem , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetItemX )( HITEM i );
GAME_GetItemX GAME_GetItemXorg = NULL;
GAME_GetItemX GAME_GetItemXold = NULL;

DWFP __cdecl GAME_GetItemXmy( HITEM i )
{
	fprintf_s( logfile , "%s\n" , "GetItemXmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetItemXold( i );
	fprintf_s( logfile , "%s:[-->GAME_GetItemX<--  i: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , i , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetItemY )( HITEM i );
GAME_GetItemY GAME_GetItemYorg = NULL;
GAME_GetItemY GAME_GetItemYold = NULL;

DWFP __cdecl GAME_GetItemYmy( HITEM i )
{
	fprintf_s( logfile , "%s\n" , "GetItemYmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetItemYold( i );
	fprintf_s( logfile , "%s:[-->GAME_GetItemY<--  i: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , i , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetKillingUnit )( );
GAME_GetKillingUnit GAME_GetKillingUnitorg = NULL;
GAME_GetKillingUnit GAME_GetKillingUnitold = NULL;

HUNIT __cdecl GAME_GetKillingUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetKillingUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetKillingUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetKillingUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetLastCommand )( );
GAME_GetLastCommand GAME_GetLastCommandorg = NULL;
GAME_GetLastCommand GAME_GetLastCommandold = NULL;

int __cdecl GAME_GetLastCommandmy( )
{
	fprintf_s( logfile , "%s\n" , "GetLastCommandmy" );
	fflush( logfile );

	int retvalue = GAME_GetLastCommandold( );
	fprintf_s( logfile , "%s:[-->GAME_GetLastCommand<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetLastData )( );
GAME_GetLastData GAME_GetLastDataorg = NULL;
GAME_GetLastData GAME_GetLastDataold = NULL;

int __cdecl GAME_GetLastDatamy( )
{
	fprintf_s( logfile , "%s\n" , "GetLastDatamy" );
	fflush( logfile );

	int retvalue = GAME_GetLastDataold( );
	fprintf_s( logfile , "%s:[-->GAME_GetLastData<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetLearnedSkill )( );
GAME_GetLearnedSkill GAME_GetLearnedSkillorg = NULL;
GAME_GetLearnedSkill GAME_GetLearnedSkillold = NULL;

int __cdecl GAME_GetLearnedSkillmy( )
{
	fprintf_s( logfile , "%s\n" , "GetLearnedSkillmy" );
	fflush( logfile );

	int retvalue = GAME_GetLearnedSkillold( );
	fprintf_s( logfile , "%s:[-->GAME_GetLearnedSkill<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetLearnedSkillLevel )( );
GAME_GetLearnedSkillLevel GAME_GetLearnedSkillLevelorg = NULL;
GAME_GetLearnedSkillLevel GAME_GetLearnedSkillLevelold = NULL;

int __cdecl GAME_GetLearnedSkillLevelmy( )
{
	fprintf_s( logfile , "%s\n" , "GetLearnedSkillLevelmy" );
	fflush( logfile );

	int retvalue = GAME_GetLearnedSkillLevelold( );
	fprintf_s( logfile , "%s:[-->GAME_GetLearnedSkillLevel<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetLearningUnit )( );
GAME_GetLearningUnit GAME_GetLearningUnitorg = NULL;
GAME_GetLearningUnit GAME_GetLearningUnitold = NULL;

HUNIT __cdecl GAME_GetLearningUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetLearningUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetLearningUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetLearningUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetLeavingUnit )( );
GAME_GetLeavingUnit GAME_GetLeavingUnitorg = NULL;
GAME_GetLeavingUnit GAME_GetLeavingUnitold = NULL;

HUNIT __cdecl GAME_GetLeavingUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetLeavingUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetLeavingUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetLeavingUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetLevelingUnit )( );
GAME_GetLevelingUnit GAME_GetLevelingUnitorg = NULL;
GAME_GetLevelingUnit GAME_GetLevelingUnitold = NULL;

HUNIT __cdecl GAME_GetLevelingUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetLevelingUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetLevelingUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetLevelingUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetLightningColorA )( HLIGHTNING whichBolt );
GAME_GetLightningColorA GAME_GetLightningColorAorg = NULL;
GAME_GetLightningColorA GAME_GetLightningColorAold = NULL;

DWFP __cdecl GAME_GetLightningColorAmy( HLIGHTNING whichBolt )
{
	fprintf_s( logfile , "%s\n" , "GetLightningColorAmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetLightningColorAold( whichBolt );
	fprintf_s( logfile , "%s:[-->GAME_GetLightningColorA<--  whichBolt: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichBolt , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetLightningColorB )( HLIGHTNING whichBolt );
GAME_GetLightningColorB GAME_GetLightningColorBorg = NULL;
GAME_GetLightningColorB GAME_GetLightningColorBold = NULL;

DWFP __cdecl GAME_GetLightningColorBmy( HLIGHTNING whichBolt )
{
	fprintf_s( logfile , "%s\n" , "GetLightningColorBmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetLightningColorBold( whichBolt );
	fprintf_s( logfile , "%s:[-->GAME_GetLightningColorB<--  whichBolt: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichBolt , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetLightningColorG )( HLIGHTNING whichBolt );
GAME_GetLightningColorG GAME_GetLightningColorGorg = NULL;
GAME_GetLightningColorG GAME_GetLightningColorGold = NULL;

DWFP __cdecl GAME_GetLightningColorGmy( HLIGHTNING whichBolt )
{
	fprintf_s( logfile , "%s\n" , "GetLightningColorGmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetLightningColorGold( whichBolt );
	fprintf_s( logfile , "%s:[-->GAME_GetLightningColorG<--  whichBolt: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichBolt , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetLightningColorR )( HLIGHTNING whichBolt );
GAME_GetLightningColorR GAME_GetLightningColorRorg = NULL;
GAME_GetLightningColorR GAME_GetLightningColorRold = NULL;

DWFP __cdecl GAME_GetLightningColorRmy( HLIGHTNING whichBolt )
{
	fprintf_s( logfile , "%s\n" , "GetLightningColorRmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetLightningColorRold( whichBolt );
	fprintf_s( logfile , "%s:[-->GAME_GetLightningColorR<--  whichBolt: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichBolt , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetLoadedUnit )( );
GAME_GetLoadedUnit GAME_GetLoadedUnitorg = NULL;
GAME_GetLoadedUnit GAME_GetLoadedUnitold = NULL;

HUNIT __cdecl GAME_GetLoadedUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetLoadedUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetLoadedUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetLoadedUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYER( __cdecl *GAME_GetLocalPlayer )( );
GAME_GetLocalPlayer GAME_GetLocalPlayerorg = NULL;
GAME_GetLocalPlayer GAME_GetLocalPlayerold = NULL;

HPLAYER __cdecl GAME_GetLocalPlayermy( )
{
	fprintf_s( logfile , "%s\n" , "GetLocalPlayermy" );
	fflush( logfile );

	HPLAYER retvalue = GAME_GetLocalPlayerold( );
	fprintf_s( logfile , "%s:[-->GAME_GetLocalPlayer<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetLocalizedHotkey )( void * source );
GAME_GetLocalizedHotkey GAME_GetLocalizedHotkeyorg = NULL;
GAME_GetLocalizedHotkey GAME_GetLocalizedHotkeyold = NULL;

int __cdecl GAME_GetLocalizedHotkeymy( void * source )
{
	fprintf_s( logfile , "%s\n" , "GetLocalizedHotkeymy" );
	fflush( logfile );

	int retvalue = GAME_GetLocalizedHotkeyold( source );
	fprintf_s( logfile , "%s:[-->GAME_GetLocalizedHotkey<--  source: \"%s\"] RETURN-> %i\n" , currentDateTime( ).c_str( ) , jassgetchar( source ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_GetLocalizedString )( void * source );
GAME_GetLocalizedString GAME_GetLocalizedStringorg = NULL;
GAME_GetLocalizedString GAME_GetLocalizedStringold = NULL;

DWORD __cdecl GAME_GetLocalizedStringmy( void * source )
{
	fprintf_s( logfile , "%s" , "GetLocalizedStringmy\n" );
	fflush( logfile );

	DWORD retvalue = GAME_GetLocalizedStringold( source );
	fprintf_s( logfile , "%s:[-->GAME_GetLocalizedString<--  source: \"%s\"] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , jassgetchar( source ) , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetLocationX )( HLOCATION whichLocation );
GAME_GetLocationX GAME_GetLocationXorg = NULL;
GAME_GetLocationX GAME_GetLocationXold = NULL;

DWFP __cdecl GAME_GetLocationXmy( HLOCATION whichLocation )
{
	fprintf_s( logfile , "%s" , "GetLocationXmy\n" );
	fflush( logfile );

	DWFP retvalue = GAME_GetLocationXold( whichLocation );
	fprintf_s( logfile , "%s:[-->GAME_GetLocationX<--  whichLocation: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichLocation , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetLocationY )( HLOCATION whichLocation );
GAME_GetLocationY GAME_GetLocationYorg = NULL;
GAME_GetLocationY GAME_GetLocationYold = NULL;

DWFP __cdecl GAME_GetLocationYmy( HLOCATION whichLocation )
{
	fprintf_s( logfile , "%s\n" , "GetLocationYmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetLocationYold( whichLocation );
	fprintf_s( logfile , "%s:[-->GAME_GetLocationY<--  whichLocation: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichLocation , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetLocationZ )( HLOCATION whichLocation );
GAME_GetLocationZ GAME_GetLocationZorg = NULL;
GAME_GetLocationZ GAME_GetLocationZold = NULL;

DWFP __cdecl GAME_GetLocationZmy( HLOCATION whichLocation )
{
	fprintf_s( logfile , "%s\n" , "GetLocationZmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetLocationZold( whichLocation );
	fprintf_s( logfile , "%s:[-->GAME_GetLocationZ<--  whichLocation: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichLocation , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef HITEM( __cdecl *GAME_GetManipulatedItem )( );
GAME_GetManipulatedItem GAME_GetManipulatedItemorg = NULL;
GAME_GetManipulatedItem GAME_GetManipulatedItemold = NULL;

HITEM __cdecl GAME_GetManipulatedItemmy( )
{
	fprintf_s( logfile , "%s\n" , "GetManipulatedItemmy" );
	fflush( logfile );

	HITEM retvalue = GAME_GetManipulatedItemold( );
	fprintf_s( logfile , "%s:[-->GAME_GetManipulatedItem<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetManipulatingUnit )( );
GAME_GetManipulatingUnit GAME_GetManipulatingUnitorg = NULL;
GAME_GetManipulatingUnit GAME_GetManipulatingUnitold = NULL;

HUNIT __cdecl GAME_GetManipulatingUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetManipulatingUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetManipulatingUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetManipulatingUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetMegaTarget )( );
GAME_GetMegaTarget GAME_GetMegaTargetorg = NULL;
GAME_GetMegaTarget GAME_GetMegaTargetold = NULL;

HUNIT __cdecl GAME_GetMegaTargetmy( )
{
	fprintf_s( logfile , "%s\n" , "GetMegaTargetmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetMegaTargetold( );
	fprintf_s( logfile , "%s:[-->GAME_GetMegaTarget<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetMinesOwned )( );
GAME_GetMinesOwned GAME_GetMinesOwnedorg = NULL;
GAME_GetMinesOwned GAME_GetMinesOwnedold = NULL;

int __cdecl GAME_GetMinesOwnedmy( )
{
	fprintf_s( logfile , "%s\n" , "GetMinesOwnedmy" );
	fflush( logfile );

	int retvalue = GAME_GetMinesOwnedold( );
	fprintf_s( logfile , "%s:[-->GAME_GetMinesOwned<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetNextExpansion )( );
GAME_GetNextExpansion GAME_GetNextExpansionorg = NULL;
GAME_GetNextExpansion GAME_GetNextExpansionold = NULL;

int __cdecl GAME_GetNextExpansionmy( )
{
	fprintf_s( logfile , "%s\n" , "GetNextExpansionmy" );
	fflush( logfile );

	int retvalue = GAME_GetNextExpansionold( );
	fprintf_s( logfile , "%s:[-->GAME_GetNextExpansion<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_GetObjectName )( int objectId );
GAME_GetObjectName GAME_GetObjectNameorg = NULL;
GAME_GetObjectName GAME_GetObjectNameold = NULL;

DWORD __cdecl GAME_GetObjectNamemy( int objectId )
{
	fprintf_s( logfile , "%s\n" , "GetObjectNamemy" );
	fflush( logfile );

	DWORD retvalue = GAME_GetObjectNameold( objectId );
	fprintf_s( logfile , "%s:[-->GAME_GetObjectName<--  objectId: %i] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , objectId , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef HLOCATION( __cdecl *GAME_GetOrderPointLoc )( );
GAME_GetOrderPointLoc GAME_GetOrderPointLocorg = NULL;
GAME_GetOrderPointLoc GAME_GetOrderPointLocold = NULL;

HLOCATION __cdecl GAME_GetOrderPointLocmy( )
{
	fprintf_s( logfile , "%s\n" , "GetOrderPointLocmy" );
	fflush( logfile );

	HLOCATION retvalue = GAME_GetOrderPointLocold( );
	fprintf_s( logfile , "%s:[-->GAME_GetOrderPointLoc<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetOrderPointX )( );
GAME_GetOrderPointX GAME_GetOrderPointXorg = NULL;
GAME_GetOrderPointX GAME_GetOrderPointXold = NULL;

DWFP __cdecl GAME_GetOrderPointXmy( )
{
	fprintf_s( logfile , "%s\n" , "GetOrderPointXmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetOrderPointXold( );
	fprintf_s( logfile , "%s:[-->GAME_GetOrderPointX<-- ] RETURN-> %f\n" , currentDateTime( ).c_str( ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetOrderPointY )( );
GAME_GetOrderPointY GAME_GetOrderPointYorg = NULL;
GAME_GetOrderPointY GAME_GetOrderPointYold = NULL;

DWFP __cdecl GAME_GetOrderPointYmy( )
{
	fprintf_s( logfile , "%s\n" , "GetOrderPointYmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetOrderPointYold( );
	fprintf_s( logfile , "%s:[-->GAME_GetOrderPointY<-- ] RETURN-> %f\n" , currentDateTime( ).c_str( ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef HWIDGET( __cdecl *GAME_GetOrderTarget )( );
GAME_GetOrderTarget GAME_GetOrderTargetorg = NULL;
GAME_GetOrderTarget GAME_GetOrderTargetold = NULL;

HWIDGET __cdecl GAME_GetOrderTargetmy( )
{
	fprintf_s( logfile , "%s\n" , "GetOrderTargetmy" );
	fflush( logfile );

	HWIDGET retvalue = GAME_GetOrderTargetold( );
	fprintf_s( logfile , "%s:[-->GAME_GetOrderTarget<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HDESTRUCTABLE( __cdecl *GAME_GetOrderTargetDestructable )( );
GAME_GetOrderTargetDestructable GAME_GetOrderTargetDestructableorg = NULL;
GAME_GetOrderTargetDestructable GAME_GetOrderTargetDestructableold = NULL;

HDESTRUCTABLE __cdecl GAME_GetOrderTargetDestructablemy( )
{
	fprintf_s( logfile , "%s\n" , "GetOrderTargetDestructablemy" );
	fflush( logfile );

	HDESTRUCTABLE retvalue = GAME_GetOrderTargetDestructableold( );
	fprintf_s( logfile , "%s:[-->GAME_GetOrderTargetDestructable<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HITEM( __cdecl *GAME_GetOrderTargetItem )( );
GAME_GetOrderTargetItem GAME_GetOrderTargetItemorg = NULL;
GAME_GetOrderTargetItem GAME_GetOrderTargetItemold = NULL;

HITEM __cdecl GAME_GetOrderTargetItemmy( )
{
	fprintf_s( logfile , "%s\n" , "GetOrderTargetItemmy" );
	fflush( logfile );

	HITEM retvalue = GAME_GetOrderTargetItemold( );
	fprintf_s( logfile , "%s:[-->GAME_GetOrderTargetItem<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetOrderTargetUnit )( );
GAME_GetOrderTargetUnit GAME_GetOrderTargetUnitorg = NULL;
GAME_GetOrderTargetUnit GAME_GetOrderTargetUnitold = NULL;

HUNIT __cdecl GAME_GetOrderTargetUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetOrderTargetUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetOrderTargetUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetOrderTargetUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetOrderedUnit )( );
GAME_GetOrderedUnit GAME_GetOrderedUnitorg = NULL;
GAME_GetOrderedUnit GAME_GetOrderedUnitold = NULL;

HUNIT __cdecl GAME_GetOrderedUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetOrderedUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetOrderedUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetOrderedUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYER( __cdecl *GAME_GetOwningPlayer )( HUNIT whichUnit );
GAME_GetOwningPlayer GAME_GetOwningPlayerorg = NULL;
GAME_GetOwningPlayer GAME_GetOwningPlayerold = NULL;

HPLAYER __cdecl GAME_GetOwningPlayermy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetOwningPlayermy" );
	fflush( logfile );

	HPLAYER retvalue = GAME_GetOwningPlayerold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetOwningPlayer<--  whichUnit: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_GetPlayerAlliance )( HPLAYER sourcePlayer , HPLAYER otherPlayer , HALLIANCETYPE whichAllianceSetting );
GAME_GetPlayerAlliance GAME_GetPlayerAllianceorg = NULL;
GAME_GetPlayerAlliance GAME_GetPlayerAllianceold = NULL;

BOOL __cdecl GAME_GetPlayerAlliancemy( HPLAYER sourcePlayer , HPLAYER otherPlayer , HALLIANCETYPE whichAllianceSetting )
{
	fprintf_s( logfile , "%s\n" , "GetPlayerAlliancemy" );
	fflush( logfile );

	BOOL retvalue = GAME_GetPlayerAllianceold( sourcePlayer , otherPlayer , whichAllianceSetting );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerAlliance<--  sourcePlayer: %X otherPlayer: %X whichAllianceSetting: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , sourcePlayer , otherPlayer , whichAllianceSetting , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYERCOLOR( __cdecl *GAME_GetPlayerColor )( HPLAYER whichPlayer );
GAME_GetPlayerColor GAME_GetPlayerColororg = NULL;
GAME_GetPlayerColor GAME_GetPlayerColorold = NULL;

HPLAYERCOLOR __cdecl GAME_GetPlayerColormy( HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "GetPlayerColormy\n" );
	fflush( logfile );

	HPLAYERCOLOR retvalue = GAME_GetPlayerColorold( whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerColor<--  whichPlayer: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichPlayer , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HMAPCONTROL( __cdecl *GAME_GetPlayerController )( HPLAYER whichPlayer );
GAME_GetPlayerController GAME_GetPlayerControllerorg = NULL;
GAME_GetPlayerController GAME_GetPlayerControllerold = NULL;

HMAPCONTROL __cdecl GAME_GetPlayerControllermy( HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s\n" , "GetPlayerControllermy" );
	fflush( logfile );

	HMAPCONTROL retvalue = GAME_GetPlayerControllerold( whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerController<--  whichPlayer: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichPlayer , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetPlayerHandicap )( HPLAYER whichPlayer );
GAME_GetPlayerHandicap GAME_GetPlayerHandicaporg = NULL;
GAME_GetPlayerHandicap GAME_GetPlayerHandicapold = NULL;

DWFP __cdecl GAME_GetPlayerHandicapmy( HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s\n" , "GetPlayerHandicapmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetPlayerHandicapold( whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerHandicap<--  whichPlayer: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichPlayer , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetPlayerHandicapXP )( HPLAYER whichPlayer );
GAME_GetPlayerHandicapXP GAME_GetPlayerHandicapXPorg = NULL;
GAME_GetPlayerHandicapXP GAME_GetPlayerHandicapXPold = NULL;

DWFP __cdecl GAME_GetPlayerHandicapXPmy( HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s\n" , "GetPlayerHandicapXPmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetPlayerHandicapXPold( whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerHandicapXP<--  whichPlayer: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichPlayer , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetPlayerId )( HPLAYER whichPlayer );
GAME_GetPlayerId GAME_GetPlayerIdorg = NULL;
GAME_GetPlayerId GAME_GetPlayerIdold = NULL;

int __cdecl GAME_GetPlayerIdmy( HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s\n" , "GetPlayerIdmy" );
	fflush( logfile );

	int retvalue = GAME_GetPlayerIdold( whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerId<--  whichPlayer: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichPlayer , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_GetPlayerName )( HPLAYER whichPlayer );
GAME_GetPlayerName GAME_GetPlayerNameorg = NULL;
GAME_GetPlayerName GAME_GetPlayerNameold = NULL;

DWORD __cdecl GAME_GetPlayerNamemy( HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s\n" , "GetPlayerNamemy" );
	fflush( logfile );

	DWORD retvalue = GAME_GetPlayerNameold( whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerName<--  whichPlayer: %X] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , whichPlayer , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef HRACE( __cdecl *GAME_GetPlayerRace )( HPLAYER whichPlayer );
GAME_GetPlayerRace GAME_GetPlayerRaceorg = NULL;
GAME_GetPlayerRace GAME_GetPlayerRaceold = NULL;

HRACE __cdecl GAME_GetPlayerRacemy( HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s\n" , "GetPlayerRacemy" );
	fflush( logfile );

	HRACE retvalue = GAME_GetPlayerRaceold( whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerRace<--  whichPlayer: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichPlayer , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetPlayerScore )( HPLAYER whichPlayer , HPLAYERSCORE whichPlayerScore );
GAME_GetPlayerScore GAME_GetPlayerScoreorg = NULL;
GAME_GetPlayerScore GAME_GetPlayerScoreold = NULL;

int __cdecl GAME_GetPlayerScoremy( HPLAYER whichPlayer , HPLAYERSCORE whichPlayerScore )
{
	fprintf_s( logfile , "%s\n" , "GetPlayerScoremy" );
	fflush( logfile );

	int retvalue = GAME_GetPlayerScoreold( whichPlayer , whichPlayerScore );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerScore<--  whichPlayer: %X whichPlayerScore: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichPlayer , whichPlayerScore , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_GetPlayerSelectable )( HPLAYER whichPlayer );
GAME_GetPlayerSelectable GAME_GetPlayerSelectableorg = NULL;
GAME_GetPlayerSelectable GAME_GetPlayerSelectableold = NULL;

BOOL __cdecl GAME_GetPlayerSelectablemy( HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s\n" , "GetPlayerSelectablemy" );
	fflush( logfile );

	BOOL retvalue = GAME_GetPlayerSelectableold( whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerSelectable<--  whichPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYERSLOTSTATE( __cdecl *GAME_GetPlayerSlotState )( HPLAYER whichPlayer );
GAME_GetPlayerSlotState GAME_GetPlayerSlotStateorg = NULL;
GAME_GetPlayerSlotState GAME_GetPlayerSlotStateold = NULL;

HPLAYERSLOTSTATE __cdecl GAME_GetPlayerSlotStatemy( HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "GetPlayerSlotStatemy\n" );
	fflush( logfile );

	HPLAYERSLOTSTATE retvalue = GAME_GetPlayerSlotStateold( whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerSlotState<--  whichPlayer: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichPlayer , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetPlayerStartLocation )( HPLAYER whichPlayer );
GAME_GetPlayerStartLocation GAME_GetPlayerStartLocationorg = NULL;
GAME_GetPlayerStartLocation GAME_GetPlayerStartLocationold = NULL;

int __cdecl GAME_GetPlayerStartLocationmy( HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s\n" , "GetPlayerStartLocationmy" );
	fflush( logfile );

	int retvalue = GAME_GetPlayerStartLocationold( whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerStartLocation<--  whichPlayer: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichPlayer , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetPlayerStartLocationX )( HPLAYER arg1 );
GAME_GetPlayerStartLocationX GAME_GetPlayerStartLocationXorg = NULL;
GAME_GetPlayerStartLocationX GAME_GetPlayerStartLocationXold = NULL;

DWFP __cdecl GAME_GetPlayerStartLocationXmy( HPLAYER arg1 )
{
	fprintf_s( logfile , "%s\n" , "GetPlayerStartLocationXmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetPlayerStartLocationXold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerStartLocationX<--  arg1: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , arg1 , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetPlayerStartLocationY )( HPLAYER arg1 );
GAME_GetPlayerStartLocationY GAME_GetPlayerStartLocationYorg = NULL;
GAME_GetPlayerStartLocationY GAME_GetPlayerStartLocationYold = NULL;

DWFP __cdecl GAME_GetPlayerStartLocationYmy( HPLAYER arg1 )
{
	fprintf_s( logfile , "%s\n" , "GetPlayerStartLocationYmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetPlayerStartLocationYold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerStartLocationY<--  arg1: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , arg1 , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetPlayerState )( HPLAYER whichPlayer , HPLAYERSTATE whichPlayerState );
GAME_GetPlayerState GAME_GetPlayerStateorg = NULL;
GAME_GetPlayerState GAME_GetPlayerStateold = NULL;

int __cdecl GAME_GetPlayerStatemy( HPLAYER whichPlayer , HPLAYERSTATE whichPlayerState )
{
	fprintf_s( logfile , "%s\n" , "GetPlayerStatemy" );
	fflush( logfile );

	int retvalue = GAME_GetPlayerStateold( whichPlayer , whichPlayerState );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerState<--  whichPlayer: %X whichPlayerState: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichPlayer , whichPlayerState , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetPlayerStructureCount )( HPLAYER whichPlayer , BOOL includeIncomplete );
GAME_GetPlayerStructureCount GAME_GetPlayerStructureCountorg = NULL;
GAME_GetPlayerStructureCount GAME_GetPlayerStructureCountold = NULL;

int __cdecl GAME_GetPlayerStructureCountmy( HPLAYER whichPlayer , BOOL includeIncomplete )
{
	fprintf_s( logfile , "%s\n" , "GetPlayerStructureCountmy" );
	fflush( logfile );

	int retvalue = GAME_GetPlayerStructureCountold( whichPlayer , includeIncomplete );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerStructureCount<--  whichPlayer: %X includeIncomplete: %s] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichPlayer , includeIncomplete ? "TRUE\n" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetPlayerTaxRate )( HPLAYER sourcePlayer , HPLAYER otherPlayer , HPLAYERSTATE whichResource );
GAME_GetPlayerTaxRate GAME_GetPlayerTaxRateorg = NULL;
GAME_GetPlayerTaxRate GAME_GetPlayerTaxRateold = NULL;

int __cdecl GAME_GetPlayerTaxRatemy( HPLAYER sourcePlayer , HPLAYER otherPlayer , HPLAYERSTATE whichResource )
{
	fprintf_s( logfile , "%s" , "GetPlayerTaxRatemy\n" );
	fflush( logfile );

	int retvalue = GAME_GetPlayerTaxRateold( sourcePlayer , otherPlayer , whichResource );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerTaxRate<--  sourcePlayer: %X otherPlayer: %X whichResource: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , sourcePlayer , otherPlayer , whichResource , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetPlayerTeam )( HPLAYER whichPlayer );
GAME_GetPlayerTeam GAME_GetPlayerTeamorg = NULL;
GAME_GetPlayerTeam GAME_GetPlayerTeamold = NULL;

int __cdecl GAME_GetPlayerTeammy( HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s\n" , "GetPlayerTeammy" );
	fflush( logfile );

	int retvalue = GAME_GetPlayerTeamold( whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerTeam<--  whichPlayer: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichPlayer , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetPlayerTechCount )( HPLAYER whichPlayer , int techid , BOOL specificonly );
GAME_GetPlayerTechCount GAME_GetPlayerTechCountorg = NULL;
GAME_GetPlayerTechCount GAME_GetPlayerTechCountold = NULL;

int __cdecl GAME_GetPlayerTechCountmy( HPLAYER whichPlayer , int techid , BOOL specificonly )
{
	fprintf_s( logfile , "%s\n" , "GetPlayerTechCountmy" );
	fflush( logfile );

	int retvalue = GAME_GetPlayerTechCountold( whichPlayer , techid , specificonly );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerTechCount<--  whichPlayer: %X techid: %i specificonly: %s] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichPlayer , techid , specificonly ? "TRUE\n" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetPlayerTechMaxAllowed )( HPLAYER whichPlayer , int techid );
GAME_GetPlayerTechMaxAllowed GAME_GetPlayerTechMaxAllowedorg = NULL;
GAME_GetPlayerTechMaxAllowed GAME_GetPlayerTechMaxAllowedold = NULL;

int __cdecl GAME_GetPlayerTechMaxAllowedmy( HPLAYER whichPlayer , int techid )
{
	fprintf_s( logfile , "%s" , "GetPlayerTechMaxAllowedmy\n" );
	fflush( logfile );

	int retvalue = GAME_GetPlayerTechMaxAllowedold( whichPlayer , techid );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerTechMaxAllowed<--  whichPlayer: %X techid: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichPlayer , techid , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_GetPlayerTechResearched )( HPLAYER whichPlayer , int techid , BOOL specificonly );
GAME_GetPlayerTechResearched GAME_GetPlayerTechResearchedorg = NULL;
GAME_GetPlayerTechResearched GAME_GetPlayerTechResearchedold = NULL;

BOOL __cdecl GAME_GetPlayerTechResearchedmy( HPLAYER whichPlayer , int techid , BOOL specificonly )
{
	fprintf_s( logfile , "%s\n" , "GetPlayerTechResearchedmy" );
	fflush( logfile );

	BOOL retvalue = GAME_GetPlayerTechResearchedold( whichPlayer , techid , specificonly );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerTechResearched<--  whichPlayer: %X techid: %i specificonly: %s] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichPlayer , techid , specificonly ? "TRUE\n" : "FALSE" , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetPlayerTypedUnitCount )( HPLAYER whichPlayer , void * unitName , BOOL includeIncomplete , BOOL includeUpgrades );
GAME_GetPlayerTypedUnitCount GAME_GetPlayerTypedUnitCountorg = NULL;
GAME_GetPlayerTypedUnitCount GAME_GetPlayerTypedUnitCountold = NULL;

int __cdecl GAME_GetPlayerTypedUnitCountmy( HPLAYER whichPlayer , void * unitName , BOOL includeIncomplete , BOOL includeUpgrades )
{
	fprintf_s( logfile , "%s" , "GetPlayerTypedUnitCountmy\n" );
	fflush( logfile );

	int retvalue = GAME_GetPlayerTypedUnitCountold( whichPlayer , unitName , includeIncomplete , includeUpgrades );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerTypedUnitCount<--  whichPlayer: %X unitName: \"%s\" includeIncomplete: %s includeUpgrades: %s] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichPlayer , jassgetchar( unitName ) , includeIncomplete ? "TRUE" : "FALSE" , includeUpgrades ? "TRUE" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetPlayerUnitCount )( HPLAYER whichPlayer , BOOL includeIncomplete );
GAME_GetPlayerUnitCount GAME_GetPlayerUnitCountorg = NULL;
GAME_GetPlayerUnitCount GAME_GetPlayerUnitCountold = NULL;

int __cdecl GAME_GetPlayerUnitCountmy( HPLAYER whichPlayer , BOOL includeIncomplete )
{
	fprintf_s( logfile , "%s" , "GetPlayerUnitCountmy\n" );
	fflush( logfile );

	int retvalue = GAME_GetPlayerUnitCountold( whichPlayer , includeIncomplete );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerUnitCount<--  whichPlayer: %X includeIncomplete: %s] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichPlayer , includeIncomplete ? "TRUE\n" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetPlayerUnitTypeCount )( HPLAYER arg1 , int arg2 );
GAME_GetPlayerUnitTypeCount GAME_GetPlayerUnitTypeCountorg = NULL;
GAME_GetPlayerUnitTypeCount GAME_GetPlayerUnitTypeCountold = NULL;

int __cdecl GAME_GetPlayerUnitTypeCountmy( HPLAYER arg1 , int arg2 )
{
	fprintf_s( logfile , "%s" , "GetPlayerUnitTypeCountmy\n" );
	fflush( logfile );

	int retvalue = GAME_GetPlayerUnitTypeCountold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayerUnitTypeCount<--  arg1: %X arg2: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , arg1 , arg2 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetPlayers )( );
GAME_GetPlayers GAME_GetPlayersorg = NULL;
GAME_GetPlayers GAME_GetPlayersold = NULL;

int __cdecl GAME_GetPlayersmy( )
{
	fprintf_s( logfile , "%s\n" , "GetPlayersmy" );
	fflush( logfile );

	int retvalue = GAME_GetPlayersold( );
	fprintf_s( logfile , "%s:[-->GAME_GetPlayers<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetRandomInt )( int lowBound , int highBound );
GAME_GetRandomInt GAME_GetRandomIntorg = NULL;
GAME_GetRandomInt GAME_GetRandomIntold = NULL;

int __cdecl GAME_GetRandomIntmy( int lowBound , int highBound )
{
	fprintf_s( logfile , "%s\n" , "GetRandomIntmy" );
	fflush( logfile );

	int retvalue = GAME_GetRandomIntold( lowBound , highBound );
	fprintf_s( logfile , "%s:[-->GAME_GetRandomInt<--  lowBound: %i highBound: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , lowBound , highBound , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetRandomReal )( float *lowBound , float *highBound );
GAME_GetRandomReal GAME_GetRandomRealorg = NULL;
GAME_GetRandomReal GAME_GetRandomRealold = NULL;

DWFP __cdecl GAME_GetRandomRealmy( float *lowBound , float *highBound )
{
	fprintf_s( logfile , "%s\n" , "GetRandomRealmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetRandomRealold( lowBound , highBound );
	fprintf_s( logfile , "%s:[-->GAME_GetRandomReal<--  lowBound: %f highBound: %f] RETURN-> %f\n" , currentDateTime( ).c_str( ) , *( float * ) lowBound , *( float * ) highBound , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetRectCenterX )( HRECT whichRect );
GAME_GetRectCenterX GAME_GetRectCenterXorg = NULL;
GAME_GetRectCenterX GAME_GetRectCenterXold = NULL;

DWFP __cdecl GAME_GetRectCenterXmy( HRECT whichRect )
{
	fprintf_s( logfile , "%s\n" , "GetRectCenterXmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetRectCenterXold( whichRect );
	fprintf_s( logfile , "%s:[-->GAME_GetRectCenterX<--  whichRect: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichRect , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetRectCenterY )( HRECT whichRect );
GAME_GetRectCenterY GAME_GetRectCenterYorg = NULL;
GAME_GetRectCenterY GAME_GetRectCenterYold = NULL;

DWFP __cdecl GAME_GetRectCenterYmy( HRECT whichRect )
{
	fprintf_s( logfile , "%s\n" , "GetRectCenterYmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetRectCenterYold( whichRect );
	fprintf_s( logfile , "%s:[-->GAME_GetRectCenterY<--  whichRect: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichRect , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetRectMaxX )( HRECT whichRect );
GAME_GetRectMaxX GAME_GetRectMaxXorg = NULL;
GAME_GetRectMaxX GAME_GetRectMaxXold = NULL;

DWFP __cdecl GAME_GetRectMaxXmy( HRECT whichRect )
{
	fprintf_s( logfile , "%s\n" , "GetRectMaxXmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetRectMaxXold( whichRect );
	fprintf_s( logfile , "%s:[-->GAME_GetRectMaxX<--  whichRect: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichRect , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetRectMaxY )( HRECT whichRect );
GAME_GetRectMaxY GAME_GetRectMaxYorg = NULL;
GAME_GetRectMaxY GAME_GetRectMaxYold = NULL;

DWFP __cdecl GAME_GetRectMaxYmy( HRECT whichRect )
{
	fprintf_s( logfile , "%s\n" , "GetRectMaxYmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetRectMaxYold( whichRect );
	fprintf_s( logfile , "%s:[-->GAME_GetRectMaxY<--  whichRect: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichRect , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetRectMinX )( HRECT whichRect );
GAME_GetRectMinX GAME_GetRectMinXorg = NULL;
GAME_GetRectMinX GAME_GetRectMinXold = NULL;

DWFP __cdecl GAME_GetRectMinXmy( HRECT whichRect )
{
	fprintf_s( logfile , "%s\n" , "GetRectMinXmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetRectMinXold( whichRect );
	fprintf_s( logfile , "%s:[-->GAME_GetRectMinX<--  whichRect: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichRect , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetRectMinY )( HRECT whichRect );
GAME_GetRectMinY GAME_GetRectMinYorg = NULL;
GAME_GetRectMinY GAME_GetRectMinYold = NULL;

DWFP __cdecl GAME_GetRectMinYmy( HRECT whichRect )
{
	fprintf_s( logfile , "%s\n" , "GetRectMinYmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetRectMinYold( whichRect );
	fprintf_s( logfile , "%s:[-->GAME_GetRectMinY<--  whichRect: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichRect , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetRescuer )( );
GAME_GetRescuer GAME_GetRescuerorg = NULL;
GAME_GetRescuer GAME_GetRescuerold = NULL;

HUNIT __cdecl GAME_GetRescuermy( )
{
	fprintf_s( logfile , "%s\n" , "GetRescuermy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetRescuerold( );
	fprintf_s( logfile , "%s:[-->GAME_GetRescuer<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetResearched )( );
GAME_GetResearched GAME_GetResearchedorg = NULL;
GAME_GetResearched GAME_GetResearchedold = NULL;

int __cdecl GAME_GetResearchedmy( )
{
	fprintf_s( logfile , "%s\n" , "GetResearchedmy" );
	fflush( logfile );

	int retvalue = GAME_GetResearchedold( );
	fprintf_s( logfile , "%s:[-->GAME_GetResearched<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetResearchingUnit )( );
GAME_GetResearchingUnit GAME_GetResearchingUnitorg = NULL;
GAME_GetResearchingUnit GAME_GetResearchingUnitold = NULL;

HUNIT __cdecl GAME_GetResearchingUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetResearchingUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetResearchingUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetResearchingUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetResourceAmount )( HUNIT whichUnit );
GAME_GetResourceAmount GAME_GetResourceAmountorg = NULL;
GAME_GetResourceAmount GAME_GetResourceAmountold = NULL;

int __cdecl GAME_GetResourceAmountmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetResourceAmountmy" );
	fflush( logfile );

	int retvalue = GAME_GetResourceAmountold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetResourceAmount<--  whichUnit: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HMAPDENSITY( __cdecl *GAME_GetResourceDensity )( );
GAME_GetResourceDensity GAME_GetResourceDensityorg = NULL;
GAME_GetResourceDensity GAME_GetResourceDensityold = NULL;

HMAPDENSITY __cdecl GAME_GetResourceDensitymy( )
{
	fprintf_s( logfile , "%s\n" , "GetResourceDensitymy" );
	fflush( logfile );

	HMAPDENSITY retvalue = GAME_GetResourceDensityold( );
	fprintf_s( logfile , "%s:[-->GAME_GetResourceDensity<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetRevivableUnit )( );
GAME_GetRevivableUnit GAME_GetRevivableUnitorg = NULL;
GAME_GetRevivableUnit GAME_GetRevivableUnitold = NULL;

HUNIT __cdecl GAME_GetRevivableUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetRevivableUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetRevivableUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetRevivableUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetRevivingUnit )( );
GAME_GetRevivingUnit GAME_GetRevivingUnitorg = NULL;
GAME_GetRevivingUnit GAME_GetRevivingUnitold = NULL;

HUNIT __cdecl GAME_GetRevivingUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetRevivingUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetRevivingUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetRevivingUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_GetSaveBasicFilename )( );
GAME_GetSaveBasicFilename GAME_GetSaveBasicFilenameorg = NULL;
GAME_GetSaveBasicFilename GAME_GetSaveBasicFilenameold = NULL;

DWORD __cdecl GAME_GetSaveBasicFilenamemy( )
{
	fprintf_s( logfile , "%s\n" , "GetSaveBasicFilenamemy" );
	fflush( logfile );

	DWORD retvalue = GAME_GetSaveBasicFilenameold( );
	fprintf_s( logfile , "%s:[-->GAME_GetSaveBasicFilename<-- ] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetSellingUnit )( );
GAME_GetSellingUnit GAME_GetSellingUnitorg = NULL;
GAME_GetSellingUnit GAME_GetSellingUnitold = NULL;

HUNIT __cdecl GAME_GetSellingUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetSellingUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetSellingUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetSellingUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HITEM( __cdecl *GAME_GetSoldItem )( );
GAME_GetSoldItem GAME_GetSoldItemorg = NULL;
GAME_GetSoldItem GAME_GetSoldItemold = NULL;

HITEM __cdecl GAME_GetSoldItemmy( )
{
	fprintf_s( logfile , "%s\n" , "GetSoldItemmy" );
	fflush( logfile );

	HITEM retvalue = GAME_GetSoldItemold( );
	fprintf_s( logfile , "%s:[-->GAME_GetSoldItem<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetSoldUnit )( );
GAME_GetSoldUnit GAME_GetSoldUnitorg = NULL;
GAME_GetSoldUnit GAME_GetSoldUnitold = NULL;

HUNIT __cdecl GAME_GetSoldUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetSoldUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetSoldUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetSoldUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetSoundDuration )( HSOUND soundHandle );
GAME_GetSoundDuration GAME_GetSoundDurationorg = NULL;
GAME_GetSoundDuration GAME_GetSoundDurationold = NULL;

int __cdecl GAME_GetSoundDurationmy( HSOUND soundHandle )
{
	fprintf_s( logfile , "%s\n" , "GetSoundDurationmy" );
	fflush( logfile );

	int retvalue = GAME_GetSoundDurationold( soundHandle );
	fprintf_s( logfile , "%s:[-->GAME_GetSoundDuration<--  soundHandle: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , soundHandle , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetSoundFileDuration )( void * musicFileName );
GAME_GetSoundFileDuration GAME_GetSoundFileDurationorg = NULL;
GAME_GetSoundFileDuration GAME_GetSoundFileDurationold = NULL;

int __cdecl GAME_GetSoundFileDurationmy( void * musicFileName )
{
	fprintf_s( logfile , "%s\n" , "GetSoundFileDurationmy" );
	fflush( logfile );

	int retvalue = GAME_GetSoundFileDurationold( musicFileName );
	fprintf_s( logfile , "%s:[-->GAME_GetSoundFileDuration<--  musicFileName: \"%s\"] RETURN-> %i\n" , currentDateTime( ).c_str( ) , jassgetchar( musicFileName ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_GetSoundIsLoading )( HSOUND soundHandle );
GAME_GetSoundIsLoading GAME_GetSoundIsLoadingorg = NULL;
GAME_GetSoundIsLoading GAME_GetSoundIsLoadingold = NULL;

BOOL __cdecl GAME_GetSoundIsLoadingmy( HSOUND soundHandle )
{
	fprintf_s( logfile , "%s" , "GetSoundIsLoadingmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_GetSoundIsLoadingold( soundHandle );
	fprintf_s( logfile , "%s:[-->GAME_GetSoundIsLoading<--  soundHandle: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , soundHandle , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_GetSoundIsPlaying )( HSOUND soundHandle );
GAME_GetSoundIsPlaying GAME_GetSoundIsPlayingorg = NULL;
GAME_GetSoundIsPlaying GAME_GetSoundIsPlayingold = NULL;

BOOL __cdecl GAME_GetSoundIsPlayingmy( HSOUND soundHandle )
{
	fprintf_s( logfile , "%s" , "GetSoundIsPlayingmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_GetSoundIsPlayingold( soundHandle );
	fprintf_s( logfile , "%s:[-->GAME_GetSoundIsPlaying<--  soundHandle: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , soundHandle , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef HABILITY( __cdecl *GAME_GetSpellAbility )( );
GAME_GetSpellAbility GAME_GetSpellAbilityorg = NULL;
GAME_GetSpellAbility GAME_GetSpellAbilityold = NULL;

HABILITY __cdecl GAME_GetSpellAbilitymy( )
{
	fprintf_s( logfile , "%s" , "GetSpellAbilitymy\n" );
	fflush( logfile );

	HABILITY retvalue = GAME_GetSpellAbilityold( );
	fprintf_s( logfile , "%s:[-->GAME_GetSpellAbility<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetSpellAbilityId )( );
GAME_GetSpellAbilityId GAME_GetSpellAbilityIdorg = NULL;
GAME_GetSpellAbilityId GAME_GetSpellAbilityIdold = NULL;

int __cdecl GAME_GetSpellAbilityIdmy( )
{
	fprintf_s( logfile , "%s\n" , "GetSpellAbilityIdmy" );
	fflush( logfile );

	int retvalue = GAME_GetSpellAbilityIdold( );
	fprintf_s( logfile , "%s:[-->GAME_GetSpellAbilityId<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetSpellAbilityUnit )( );
GAME_GetSpellAbilityUnit GAME_GetSpellAbilityUnitorg = NULL;
GAME_GetSpellAbilityUnit GAME_GetSpellAbilityUnitold = NULL;

HUNIT __cdecl GAME_GetSpellAbilityUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetSpellAbilityUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetSpellAbilityUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetSpellAbilityUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HDESTRUCTABLE( __cdecl *GAME_GetSpellTargetDestructable )( );
GAME_GetSpellTargetDestructable GAME_GetSpellTargetDestructableorg = NULL;
GAME_GetSpellTargetDestructable GAME_GetSpellTargetDestructableold = NULL;

HDESTRUCTABLE __cdecl GAME_GetSpellTargetDestructablemy( )
{
	fprintf_s( logfile , "%s\n" , "GetSpellTargetDestructablemy" );
	fflush( logfile );

	HDESTRUCTABLE retvalue = GAME_GetSpellTargetDestructableold( );
	fprintf_s( logfile , "%s:[-->GAME_GetSpellTargetDestructable<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HITEM( __cdecl *GAME_GetSpellTargetItem )( );
GAME_GetSpellTargetItem GAME_GetSpellTargetItemorg = NULL;
GAME_GetSpellTargetItem GAME_GetSpellTargetItemold = NULL;

HITEM __cdecl GAME_GetSpellTargetItemmy( )
{
	fprintf_s( logfile , "%s\n" , "GetSpellTargetItemmy" );
	fflush( logfile );

	HITEM retvalue = GAME_GetSpellTargetItemold( );
	fprintf_s( logfile , "%s:[-->GAME_GetSpellTargetItem<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HLOCATION( __cdecl *GAME_GetSpellTargetLoc )( );
GAME_GetSpellTargetLoc GAME_GetSpellTargetLocorg = NULL;
GAME_GetSpellTargetLoc GAME_GetSpellTargetLocold = NULL;

HLOCATION __cdecl GAME_GetSpellTargetLocmy( )
{
	fprintf_s( logfile , "%s\n" , "GetSpellTargetLocmy" );
	fflush( logfile );

	HLOCATION retvalue = GAME_GetSpellTargetLocold( );
	fprintf_s( logfile , "%s:[-->GAME_GetSpellTargetLoc<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetSpellTargetUnit )( );
GAME_GetSpellTargetUnit GAME_GetSpellTargetUnitorg = NULL;
GAME_GetSpellTargetUnit GAME_GetSpellTargetUnitold = NULL;

HUNIT __cdecl GAME_GetSpellTargetUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetSpellTargetUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetSpellTargetUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetSpellTargetUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetSpellTargetX )( );
GAME_GetSpellTargetX GAME_GetSpellTargetXorg = NULL;
GAME_GetSpellTargetX GAME_GetSpellTargetXold = NULL;

DWFP __cdecl GAME_GetSpellTargetXmy( )
{
	fprintf_s( logfile , "%s\n" , "GetSpellTargetXmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetSpellTargetXold( );
	fprintf_s( logfile , "%s:[-->GAME_GetSpellTargetX<-- ] RETURN-> %f\n" , currentDateTime( ).c_str( ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetSpellTargetY )( );
GAME_GetSpellTargetY GAME_GetSpellTargetYorg = NULL;
GAME_GetSpellTargetY GAME_GetSpellTargetYold = NULL;

DWFP __cdecl GAME_GetSpellTargetYmy( )
{
	fprintf_s( logfile , "%s\n" , "GetSpellTargetYmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetSpellTargetYold( );
	fprintf_s( logfile , "%s:[-->GAME_GetSpellTargetY<-- ] RETURN-> %f\n" , currentDateTime( ).c_str( ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef HSTARTLOCPRIO( __cdecl *GAME_GetStartLocPrio )( int whichStartLoc , int prioSlotIndex );
GAME_GetStartLocPrio GAME_GetStartLocPrioorg = NULL;
GAME_GetStartLocPrio GAME_GetStartLocPrioold = NULL;

HSTARTLOCPRIO __cdecl GAME_GetStartLocPriomy( int whichStartLoc , int prioSlotIndex )
{
	fprintf_s( logfile , "%s\n" , "GetStartLocPriomy" );
	fflush( logfile );

	HSTARTLOCPRIO retvalue = GAME_GetStartLocPrioold( whichStartLoc , prioSlotIndex );
	fprintf_s( logfile , "%s:[-->GAME_GetStartLocPrio<--  whichStartLoc: %i prioSlotIndex: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichStartLoc , prioSlotIndex , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetStartLocPrioSlot )( int whichStartLoc , int prioSlotIndex );
GAME_GetStartLocPrioSlot GAME_GetStartLocPrioSlotorg = NULL;
GAME_GetStartLocPrioSlot GAME_GetStartLocPrioSlotold = NULL;

int __cdecl GAME_GetStartLocPrioSlotmy( int whichStartLoc , int prioSlotIndex )
{
	fprintf_s( logfile , "%s\n" , "GetStartLocPrioSlotmy" );
	fflush( logfile );

	int retvalue = GAME_GetStartLocPrioSlotold( whichStartLoc , prioSlotIndex );
	fprintf_s( logfile , "%s:[-->GAME_GetStartLocPrioSlot<--  whichStartLoc: %i prioSlotIndex: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichStartLoc , prioSlotIndex , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HLOCATION( __cdecl *GAME_GetStartLocationLoc )( int whichStartLocation );
GAME_GetStartLocationLoc GAME_GetStartLocationLocorg = NULL;
GAME_GetStartLocationLoc GAME_GetStartLocationLocold = NULL;

HLOCATION __cdecl GAME_GetStartLocationLocmy( int whichStartLocation )
{
	fprintf_s( logfile , "%s\n" , "GetStartLocationLocmy" );
	fflush( logfile );

	HLOCATION retvalue = GAME_GetStartLocationLocold( whichStartLocation );
	fprintf_s( logfile , "%s:[-->GAME_GetStartLocationLoc<--  whichStartLocation: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichStartLocation , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetStartLocationX )( int whichStartLocation );
GAME_GetStartLocationX GAME_GetStartLocationXorg = NULL;
GAME_GetStartLocationX GAME_GetStartLocationXold = NULL;

DWFP __cdecl GAME_GetStartLocationXmy( int whichStartLocation )
{
	fprintf_s( logfile , "%s\n" , "GetStartLocationXmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetStartLocationXold( whichStartLocation );
	fprintf_s( logfile , "%s:[-->GAME_GetStartLocationX<--  whichStartLocation: %i] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichStartLocation , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetStartLocationY )( int whichStartLocation );
GAME_GetStartLocationY GAME_GetStartLocationYorg = NULL;
GAME_GetStartLocationY GAME_GetStartLocationYold = NULL;

DWFP __cdecl GAME_GetStartLocationYmy( int whichStartLocation )
{
	fprintf_s( logfile , "%s\n" , "GetStartLocationYmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetStartLocationYold( whichStartLocation );
	fprintf_s( logfile , "%s:[-->GAME_GetStartLocationY<--  whichStartLocation: %i] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichStartLocation , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_GetStoredBOOLean )( HGAMECACHE cache , void * missionKey , void * key );
GAME_GetStoredBOOLean GAME_GetStoredBOOLeanorg = NULL;
GAME_GetStoredBOOLean GAME_GetStoredBOOLeanold = NULL;

BOOL __cdecl GAME_GetStoredBOOLeanmy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s\n" , "GetStoredBOOLeanmy" );
	fflush( logfile );

	BOOL retvalue = GAME_GetStoredBOOLeanold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_GetStoredBOOLean<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> %s\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetStoredInteger )( HGAMECACHE cache , void * missionKey , void * key );
GAME_GetStoredInteger GAME_GetStoredIntegerorg = NULL;
GAME_GetStoredInteger GAME_GetStoredIntegerold = NULL;

int __cdecl GAME_GetStoredIntegermy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s" , "GetStoredIntegermy\n" );
	fflush( logfile );

	int retvalue = GAME_GetStoredIntegerold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_GetStoredInteger<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> %i\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetStoredReal )( HGAMECACHE cache , void * missionKey , void * key );
GAME_GetStoredReal GAME_GetStoredRealorg = NULL;
GAME_GetStoredReal GAME_GetStoredRealold = NULL;

DWFP __cdecl GAME_GetStoredRealmy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s" , "GetStoredRealmy\n" );
	fflush( logfile );

	DWFP retvalue = GAME_GetStoredRealold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_GetStoredReal<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> %f\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_GetStoredString )( HGAMECACHE cache , void * missionKey , void * key );
GAME_GetStoredString GAME_GetStoredStringorg = NULL;
GAME_GetStoredString GAME_GetStoredStringold = NULL;

DWORD __cdecl GAME_GetStoredStringmy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s" , "GetStoredStringmy\n" );
	fflush( logfile );

	DWORD retvalue = GAME_GetStoredStringold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_GetStoredString<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetSummonedUnit )( );
GAME_GetSummonedUnit GAME_GetSummonedUnitorg = NULL;
GAME_GetSummonedUnit GAME_GetSummonedUnitold = NULL;

HUNIT __cdecl GAME_GetSummonedUnitmy( )
{
	fprintf_s( logfile , "%s" , "GetSummonedUnitmy\n" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetSummonedUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetSummonedUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetSummoningUnit )( );
GAME_GetSummoningUnit GAME_GetSummoningUnitorg = NULL;
GAME_GetSummoningUnit GAME_GetSummoningUnitold = NULL;

HUNIT __cdecl GAME_GetSummoningUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetSummoningUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetSummoningUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetSummoningUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetTeams )( );
GAME_GetTeams GAME_GetTeamsorg = NULL;
GAME_GetTeams GAME_GetTeamsold = NULL;

int __cdecl GAME_GetTeamsmy( )
{
	fprintf_s( logfile , "%s\n" , "GetTeamsmy" );
	fflush( logfile );

	int retvalue = GAME_GetTeamsold( );
	fprintf_s( logfile , "%s:[-->GAME_GetTeams<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetTerrainCliffLevel )( float *x , float *y );
GAME_GetTerrainCliffLevel GAME_GetTerrainCliffLevelorg = NULL;
GAME_GetTerrainCliffLevel GAME_GetTerrainCliffLevelold = NULL;

int __cdecl GAME_GetTerrainCliffLevelmy( float *x , float *y )
{
	fprintf_s( logfile , "%s\n" , "GetTerrainCliffLevelmy" );
	fflush( logfile );

	int retvalue = GAME_GetTerrainCliffLevelold( x , y );
	fprintf_s( logfile , "%s:[-->GAME_GetTerrainCliffLevel<--  x: %f y: %f] RETURN-> %i\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetTerrainType )( float *x , float *y );
GAME_GetTerrainType GAME_GetTerrainTypeorg = NULL;
GAME_GetTerrainType GAME_GetTerrainTypeold = NULL;

int __cdecl GAME_GetTerrainTypemy( float *x , float *y )
{
	fprintf_s( logfile , "%s\n" , "GetTerrainTypemy" );
	fflush( logfile );

	int retvalue = GAME_GetTerrainTypeold( x , y );
	fprintf_s( logfile , "%s:[-->GAME_GetTerrainType<--  x: %f y: %f] RETURN-> %i\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetTerrainVariance )( float *x , float *y );
GAME_GetTerrainVariance GAME_GetTerrainVarianceorg = NULL;
GAME_GetTerrainVariance GAME_GetTerrainVarianceold = NULL;

int __cdecl GAME_GetTerrainVariancemy( float *x , float *y )
{
	fprintf_s( logfile , "%s\n" , "GetTerrainVariancemy" );
	fflush( logfile );

	int retvalue = GAME_GetTerrainVarianceold( x , y );
	fprintf_s( logfile , "%s:[-->GAME_GetTerrainVariance<--  x: %f y: %f] RETURN-> %i\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetTimeOfDayScale )( );
GAME_GetTimeOfDayScale GAME_GetTimeOfDayScaleorg = NULL;
GAME_GetTimeOfDayScale GAME_GetTimeOfDayScaleold = NULL;

DWFP __cdecl GAME_GetTimeOfDayScalemy( )
{
	fprintf_s( logfile , "%s\n" , "GetTimeOfDayScalemy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetTimeOfDayScaleold( );
	fprintf_s( logfile , "%s:[-->GAME_GetTimeOfDayScale<-- ] RETURN-> %f\n" , currentDateTime( ).c_str( ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYER( __cdecl *GAME_GetTournamentFinishNowPlayer )( );
GAME_GetTournamentFinishNowPlayer GAME_GetTournamentFinishNowPlayerorg = NULL;
GAME_GetTournamentFinishNowPlayer GAME_GetTournamentFinishNowPlayerold = NULL;

HPLAYER __cdecl GAME_GetTournamentFinishNowPlayermy( )
{
	fprintf_s( logfile , "%s\n" , "GetTournamentFinishNowPlayermy" );
	fflush( logfile );

	HPLAYER retvalue = GAME_GetTournamentFinishNowPlayerold( );
	fprintf_s( logfile , "%s:[-->GAME_GetTournamentFinishNowPlayer<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetTournamentFinishNowRule )( );
GAME_GetTournamentFinishNowRule GAME_GetTournamentFinishNowRuleorg = NULL;
GAME_GetTournamentFinishNowRule GAME_GetTournamentFinishNowRuleold = NULL;

int __cdecl GAME_GetTournamentFinishNowRulemy( )
{
	fprintf_s( logfile , "%s\n" , "GetTournamentFinishNowRulemy" );
	fflush( logfile );

	int retvalue = GAME_GetTournamentFinishNowRuleold( );
	fprintf_s( logfile , "%s:[-->GAME_GetTournamentFinishNowRule<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetTournamentFinishSoonTimeRemaining )( );
GAME_GetTournamentFinishSoonTimeRemaining GAME_GetTournamentFinishSoonTimeRemainingorg = NULL;
GAME_GetTournamentFinishSoonTimeRemaining GAME_GetTournamentFinishSoonTimeRemainingold = NULL;

DWFP __cdecl GAME_GetTournamentFinishSoonTimeRemainingmy( )
{
	fprintf_s( logfile , "%s\n" , "GetTournamentFinishSoonTimeRemainingmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetTournamentFinishSoonTimeRemainingold( );
	fprintf_s( logfile , "%s:[-->GAME_GetTournamentFinishSoonTimeRemaining<-- ] RETURN-> %f\n" , currentDateTime( ).c_str( ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetTournamentScore )( HPLAYER whichPlayer );
GAME_GetTournamentScore GAME_GetTournamentScoreorg = NULL;
GAME_GetTournamentScore GAME_GetTournamentScoreold = NULL;

int __cdecl GAME_GetTournamentScoremy( HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s\n" , "GetTournamentScoremy" );
	fflush( logfile );

	int retvalue = GAME_GetTournamentScoreold( whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_GetTournamentScore<--  whichPlayer: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichPlayer , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetTownUnitCount )( int arg1 , int arg2 , BOOL arg3 );
GAME_GetTownUnitCount GAME_GetTownUnitCountorg = NULL;
GAME_GetTownUnitCount GAME_GetTownUnitCountold = NULL;

int __cdecl GAME_GetTownUnitCountmy( int arg1 , int arg2 , BOOL arg3 )
{
	fprintf_s( logfile , "%s\n" , "GetTownUnitCountmy" );
	fflush( logfile );

	int retvalue = GAME_GetTownUnitCountold( arg1 , arg2 , arg3 );
	fprintf_s( logfile , "%s:[-->GAME_GetTownUnitCount<--  arg1: %i arg2: %i arg3: %s] RETURN-> %i\n" , currentDateTime( ).c_str( ) , arg1 , arg2 , arg3 ? "TRUE\n" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetTrainedUnit )( );
GAME_GetTrainedUnit GAME_GetTrainedUnitorg = NULL;
GAME_GetTrainedUnit GAME_GetTrainedUnitold = NULL;

HUNIT __cdecl GAME_GetTrainedUnitmy( )
{
	fprintf_s( logfile , "%s" , "GetTrainedUnitmy\n" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetTrainedUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetTrainedUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetTrainedUnitType )( );
GAME_GetTrainedUnitType GAME_GetTrainedUnitTypeorg = NULL;
GAME_GetTrainedUnitType GAME_GetTrainedUnitTypeold = NULL;

int __cdecl GAME_GetTrainedUnitTypemy( )
{
	fprintf_s( logfile , "%s\n" , "GetTrainedUnitTypemy" );
	fflush( logfile );

	int retvalue = GAME_GetTrainedUnitTypeold( );
	fprintf_s( logfile , "%s:[-->GAME_GetTrainedUnitType<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetTransportUnit )( );
GAME_GetTransportUnit GAME_GetTransportUnitorg = NULL;
GAME_GetTransportUnit GAME_GetTransportUnitold = NULL;

HUNIT __cdecl GAME_GetTransportUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetTransportUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetTransportUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetTransportUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HDESTRUCTABLE( __cdecl *GAME_GetTriggerDestructable )( );
GAME_GetTriggerDestructable GAME_GetTriggerDestructableorg = NULL;
GAME_GetTriggerDestructable GAME_GetTriggerDestructableold = NULL;

HDESTRUCTABLE __cdecl GAME_GetTriggerDestructablemy( )
{
	fprintf_s( logfile , "%s\n" , "GetTriggerDestructablemy" );
	fflush( logfile );

	HDESTRUCTABLE retvalue = GAME_GetTriggerDestructableold( );
	fprintf_s( logfile , "%s:[-->GAME_GetTriggerDestructable<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetTriggerEvalCount )( HTRIGGER whichTrigger );
GAME_GetTriggerEvalCount GAME_GetTriggerEvalCountorg = NULL;
GAME_GetTriggerEvalCount GAME_GetTriggerEvalCountold = NULL;

int __cdecl GAME_GetTriggerEvalCountmy( HTRIGGER whichTrigger )
{
	fprintf_s( logfile , "%s\n" , "GetTriggerEvalCountmy" );
	fflush( logfile );

	int retvalue = GAME_GetTriggerEvalCountold( whichTrigger );
	fprintf_s( logfile , "%s:[-->GAME_GetTriggerEvalCount<--  whichTrigger: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichTrigger , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENTID( __cdecl *GAME_GetTriggerEventId )( );
GAME_GetTriggerEventId GAME_GetTriggerEventIdorg = NULL;
GAME_GetTriggerEventId GAME_GetTriggerEventIdold = NULL;

HEVENTID __cdecl GAME_GetTriggerEventIdmy( )
{
	fprintf_s( logfile , "%s\n" , "GetTriggerEventIdmy" );
	fflush( logfile );

	HEVENTID retvalue = GAME_GetTriggerEventIdold( );
	fprintf_s( logfile , "%s:[-->GAME_GetTriggerEventId<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetTriggerExecCount )( HTRIGGER whichTrigger );
GAME_GetTriggerExecCount GAME_GetTriggerExecCountorg = NULL;
GAME_GetTriggerExecCount GAME_GetTriggerExecCountold = NULL;

int __cdecl GAME_GetTriggerExecCountmy( HTRIGGER whichTrigger )
{
	fprintf_s( logfile , "%s\n" , "GetTriggerExecCountmy" );
	fflush( logfile );

	int retvalue = GAME_GetTriggerExecCountold( whichTrigger );
	fprintf_s( logfile , "%s:[-->GAME_GetTriggerExecCount<--  whichTrigger: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichTrigger , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYER( __cdecl *GAME_GetTriggerPlayer )( );
GAME_GetTriggerPlayer GAME_GetTriggerPlayerorg = NULL;
GAME_GetTriggerPlayer GAME_GetTriggerPlayerold = NULL;

HPLAYER __cdecl GAME_GetTriggerPlayermy( )
{
	fprintf_s( logfile , "%s\n" , "GetTriggerPlayermy" );
	fflush( logfile );

	HPLAYER retvalue = GAME_GetTriggerPlayerold( );
	fprintf_s( logfile , "%s:[-->GAME_GetTriggerPlayer<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetTriggerUnit )( );
GAME_GetTriggerUnit GAME_GetTriggerUnitorg = NULL;
GAME_GetTriggerUnit GAME_GetTriggerUnitold = NULL;

HUNIT __cdecl GAME_GetTriggerUnitmy( )
{
	fprintf_s( logfile , "%s\n" , "GetTriggerUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetTriggerUnitold( );
	fprintf_s( logfile , "%s:[-->GAME_GetTriggerUnit<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HWIDGET( __cdecl *GAME_GetTriggerWidget )( );
GAME_GetTriggerWidget GAME_GetTriggerWidgetorg = NULL;
GAME_GetTriggerWidget GAME_GetTriggerWidgetold = NULL;

HWIDGET __cdecl GAME_GetTriggerWidgetmy( )
{
	fprintf_s( logfile , "%s\n" , "GetTriggerWidgetmy" );
	fflush( logfile );

	HWIDGET retvalue = GAME_GetTriggerWidgetold( );
	fprintf_s( logfile , "%s:[-->GAME_GetTriggerWidget<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HREGION( __cdecl *GAME_GetTriggeringRegion )( );
GAME_GetTriggeringRegion GAME_GetTriggeringRegionorg = NULL;
GAME_GetTriggeringRegion GAME_GetTriggeringRegionold = NULL;

HREGION __cdecl GAME_GetTriggeringRegionmy( )
{
	fprintf_s( logfile , "%s\n" , "GetTriggeringRegionmy" );
	fflush( logfile );

	HREGION retvalue = GAME_GetTriggeringRegionold( );
	fprintf_s( logfile , "%s:[-->GAME_GetTriggeringRegion<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTRACKABLE( __cdecl *GAME_GetTriggeringTrackable )( );
GAME_GetTriggeringTrackable GAME_GetTriggeringTrackableorg = NULL;
GAME_GetTriggeringTrackable GAME_GetTriggeringTrackableold = NULL;

HTRACKABLE __cdecl GAME_GetTriggeringTrackablemy( )
{
	fprintf_s( logfile , "%s\n" , "GetTriggeringTrackablemy" );
	fflush( logfile );

	HTRACKABLE retvalue = GAME_GetTriggeringTrackableold( );
	fprintf_s( logfile , "%s:[-->GAME_GetTriggeringTrackable<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTRIGGER( __cdecl *GAME_GetTriggeringTrigger )( );
GAME_GetTriggeringTrigger GAME_GetTriggeringTriggerorg = NULL;
GAME_GetTriggeringTrigger GAME_GetTriggeringTriggerold = NULL;

HTRIGGER __cdecl GAME_GetTriggeringTriggermy( )
{
	fprintf_s( logfile , "%s\n" , "GetTriggeringTriggermy" );
	fflush( logfile );

	HTRIGGER retvalue = GAME_GetTriggeringTriggerold( );
	fprintf_s( logfile , "%s:[-->GAME_GetTriggeringTrigger<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetUnitAbilityLevel )( HUNIT whichUnit , int abilcode );
GAME_GetUnitAbilityLevel GAME_GetUnitAbilityLevelorg = NULL;
GAME_GetUnitAbilityLevel GAME_GetUnitAbilityLevelold = NULL;

int __cdecl GAME_GetUnitAbilityLevelmy( HUNIT whichUnit , int abilcode )
{
	fprintf_s( logfile , "%s\n" , "GetUnitAbilityLevelmy" );
	fflush( logfile );

	int retvalue = GAME_GetUnitAbilityLevelold( whichUnit , abilcode );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitAbilityLevel<--  whichUnit: %X abilcode: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichUnit , abilcode , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetUnitAcquireRange )( HUNIT whichUnit );
GAME_GetUnitAcquireRange GAME_GetUnitAcquireRangeorg = NULL;
GAME_GetUnitAcquireRange GAME_GetUnitAcquireRangeold = NULL;

DWFP __cdecl GAME_GetUnitAcquireRangemy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitAcquireRangemy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetUnitAcquireRangeold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitAcquireRange<--  whichUnit: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetUnitBuildTime )( int arg1 );
GAME_GetUnitBuildTime GAME_GetUnitBuildTimeorg = NULL;
GAME_GetUnitBuildTime GAME_GetUnitBuildTimeold = NULL;

int __cdecl GAME_GetUnitBuildTimemy( int arg1 )
{
	fprintf_s( logfile , "%s\n" , "GetUnitBuildTimemy" );
	fflush( logfile );

	int retvalue = GAME_GetUnitBuildTimeold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitBuildTime<--  arg1: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , arg1 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetUnitCount )( int arg1 );
GAME_GetUnitCount GAME_GetUnitCountorg = NULL;
GAME_GetUnitCount GAME_GetUnitCountold = NULL;

int __cdecl GAME_GetUnitCountmy( int arg1 )
{
	fprintf_s( logfile , "%s\n" , "GetUnitCountmy" );
	fflush( logfile );

	int retvalue = GAME_GetUnitCountold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitCount<--  arg1: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , arg1 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetUnitCountDone )( int arg1 );
GAME_GetUnitCountDone GAME_GetUnitCountDoneorg = NULL;
GAME_GetUnitCountDone GAME_GetUnitCountDoneold = NULL;

int __cdecl GAME_GetUnitCountDonemy( int arg1 )
{
	fprintf_s( logfile , "%s\n" , "GetUnitCountDonemy" );
	fflush( logfile );

	int retvalue = GAME_GetUnitCountDoneold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitCountDone<--  arg1: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , arg1 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetUnitCurrentOrder )( HUNIT whichUnit );
GAME_GetUnitCurrentOrder GAME_GetUnitCurrentOrderorg = NULL;
GAME_GetUnitCurrentOrder GAME_GetUnitCurrentOrderold = NULL;

int __cdecl GAME_GetUnitCurrentOrdermy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitCurrentOrdermy" );
	fflush( logfile );

	int retvalue = GAME_GetUnitCurrentOrderold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitCurrentOrder<--  whichUnit: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetUnitDefaultAcquireRange )( HUNIT whichUnit );
GAME_GetUnitDefaultAcquireRange GAME_GetUnitDefaultAcquireRangeorg = NULL;
GAME_GetUnitDefaultAcquireRange GAME_GetUnitDefaultAcquireRangeold = NULL;

DWFP __cdecl GAME_GetUnitDefaultAcquireRangemy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitDefaultAcquireRangemy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetUnitDefaultAcquireRangeold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitDefaultAcquireRange<--  whichUnit: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetUnitDefaultFlyHeight )( HUNIT whichUnit );
GAME_GetUnitDefaultFlyHeight GAME_GetUnitDefaultFlyHeightorg = NULL;
GAME_GetUnitDefaultFlyHeight GAME_GetUnitDefaultFlyHeightold = NULL;

DWFP __cdecl GAME_GetUnitDefaultFlyHeightmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitDefaultFlyHeightmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetUnitDefaultFlyHeightold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitDefaultFlyHeight<--  whichUnit: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetUnitDefaultMoveSpeed )( HUNIT whichUnit );
GAME_GetUnitDefaultMoveSpeed GAME_GetUnitDefaultMoveSpeedorg = NULL;
GAME_GetUnitDefaultMoveSpeed GAME_GetUnitDefaultMoveSpeedold = NULL;

DWFP __cdecl GAME_GetUnitDefaultMoveSpeedmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitDefaultMoveSpeedmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetUnitDefaultMoveSpeedold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitDefaultMoveSpeed<--  whichUnit: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetUnitDefaultPropWindow )( HUNIT whichUnit );
GAME_GetUnitDefaultPropWindow GAME_GetUnitDefaultPropWindoworg = NULL;
GAME_GetUnitDefaultPropWindow GAME_GetUnitDefaultPropWindowold = NULL;

DWFP __cdecl GAME_GetUnitDefaultPropWindowmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitDefaultPropWindowmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetUnitDefaultPropWindowold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitDefaultPropWindow<--  whichUnit: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetUnitDefaultTurnSpeed )( HUNIT whichUnit );
GAME_GetUnitDefaultTurnSpeed GAME_GetUnitDefaultTurnSpeedorg = NULL;
GAME_GetUnitDefaultTurnSpeed GAME_GetUnitDefaultTurnSpeedold = NULL;

DWFP __cdecl GAME_GetUnitDefaultTurnSpeedmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitDefaultTurnSpeedmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetUnitDefaultTurnSpeedold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitDefaultTurnSpeed<--  whichUnit: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetUnitFacing )( HUNIT whichUnit );
GAME_GetUnitFacing GAME_GetUnitFacingorg = NULL;
GAME_GetUnitFacing GAME_GetUnitFacingold = NULL;

DWFP __cdecl GAME_GetUnitFacingmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitFacingmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetUnitFacingold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitFacing<--  whichUnit: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetUnitFlyHeight )( HUNIT whichUnit );
GAME_GetUnitFlyHeight GAME_GetUnitFlyHeightorg = NULL;
GAME_GetUnitFlyHeight GAME_GetUnitFlyHeightold = NULL;

DWFP __cdecl GAME_GetUnitFlyHeightmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitFlyHeightmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetUnitFlyHeightold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitFlyHeight<--  whichUnit: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetUnitFoodMade )( HUNIT whichUnit );
GAME_GetUnitFoodMade GAME_GetUnitFoodMadeorg = NULL;
GAME_GetUnitFoodMade GAME_GetUnitFoodMadeold = NULL;

int __cdecl GAME_GetUnitFoodMademy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitFoodMademy" );
	fflush( logfile );

	int retvalue = GAME_GetUnitFoodMadeold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitFoodMade<--  whichUnit: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetUnitFoodUsed )( HUNIT whichUnit );
GAME_GetUnitFoodUsed GAME_GetUnitFoodUsedorg = NULL;
GAME_GetUnitFoodUsed GAME_GetUnitFoodUsedold = NULL;

int __cdecl GAME_GetUnitFoodUsedmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitFoodUsedmy" );
	fflush( logfile );

	int retvalue = GAME_GetUnitFoodUsedold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitFoodUsed<--  whichUnit: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetUnitGoldCost )( int arg1 );
GAME_GetUnitGoldCost GAME_GetUnitGoldCostorg = NULL;
GAME_GetUnitGoldCost GAME_GetUnitGoldCostold = NULL;

int __cdecl GAME_GetUnitGoldCostmy( int arg1 )
{
	fprintf_s( logfile , "%s\n" , "GetUnitGoldCostmy" );
	fflush( logfile );

	int retvalue = GAME_GetUnitGoldCostold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitGoldCost<--  arg1: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , arg1 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetUnitLevel )( HUNIT whichUnit );
GAME_GetUnitLevel GAME_GetUnitLevelorg = NULL;
GAME_GetUnitLevel GAME_GetUnitLevelold = NULL;

int __cdecl GAME_GetUnitLevelmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitLevelmy" );
	fflush( logfile );

	int retvalue = GAME_GetUnitLevelold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitLevel<--  whichUnit: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HLOCATION( __cdecl *GAME_GetUnitLoc )( HUNIT whichUnit );
GAME_GetUnitLoc GAME_GetUnitLocorg = NULL;
GAME_GetUnitLoc GAME_GetUnitLocold = NULL;

HLOCATION __cdecl GAME_GetUnitLocmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitLocmy" );
	fflush( logfile );

	HLOCATION retvalue = GAME_GetUnitLocold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitLoc<--  whichUnit: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetUnitMoveSpeed )( HUNIT whichUnit );
GAME_GetUnitMoveSpeed GAME_GetUnitMoveSpeedorg = NULL;
GAME_GetUnitMoveSpeed GAME_GetUnitMoveSpeedold = NULL;

DWFP __cdecl GAME_GetUnitMoveSpeedmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitMoveSpeedmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetUnitMoveSpeedold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitMoveSpeed<--  whichUnit: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_GetUnitName )( HUNIT whichUnit );
GAME_GetUnitName GAME_GetUnitNameorg = NULL;
GAME_GetUnitName GAME_GetUnitNameold = NULL;

DWORD __cdecl GAME_GetUnitNamemy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitNamemy" );
	fflush( logfile );

	DWORD retvalue = GAME_GetUnitNameold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitName<--  whichUnit: %X] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , whichUnit , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetUnitPointValue )( HUNIT whichUnit );
GAME_GetUnitPointValue GAME_GetUnitPointValueorg = NULL;
GAME_GetUnitPointValue GAME_GetUnitPointValueold = NULL;

int __cdecl GAME_GetUnitPointValuemy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitPointValuemy" );
	fflush( logfile );

	int retvalue = GAME_GetUnitPointValueold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitPointValue<--  whichUnit: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetUnitPointValueByType )( int unitType );
GAME_GetUnitPointValueByType GAME_GetUnitPointValueByTypeorg = NULL;
GAME_GetUnitPointValueByType GAME_GetUnitPointValueByTypeold = NULL;

int __cdecl GAME_GetUnitPointValueByTypemy( int unitType )
{
	fprintf_s( logfile , "%s\n" , "GetUnitPointValueByTypemy" );
	fflush( logfile );

	int retvalue = GAME_GetUnitPointValueByTypeold( unitType );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitPointValueByType<--  unitType: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , unitType , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetUnitPropWindow )( HUNIT whichUnit );
GAME_GetUnitPropWindow GAME_GetUnitPropWindoworg = NULL;
GAME_GetUnitPropWindow GAME_GetUnitPropWindowold = NULL;

DWFP __cdecl GAME_GetUnitPropWindowmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitPropWindowmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetUnitPropWindowold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitPropWindow<--  whichUnit: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef HRACE( __cdecl *GAME_GetUnitRace )( HUNIT whichUnit );
GAME_GetUnitRace GAME_GetUnitRaceorg = NULL;
GAME_GetUnitRace GAME_GetUnitRaceold = NULL;

HRACE __cdecl GAME_GetUnitRacemy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitRacemy" );
	fflush( logfile );

	HRACE retvalue = GAME_GetUnitRaceold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitRace<--  whichUnit: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HDESTRUCTABLE( __cdecl *GAME_GetUnitRallyDestructable )( HUNIT whichUnit );
GAME_GetUnitRallyDestructable GAME_GetUnitRallyDestructableorg = NULL;
GAME_GetUnitRallyDestructable GAME_GetUnitRallyDestructableold = NULL;

HDESTRUCTABLE __cdecl GAME_GetUnitRallyDestructablemy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitRallyDestructablemy" );
	fflush( logfile );

	HDESTRUCTABLE retvalue = GAME_GetUnitRallyDestructableold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitRallyDestructable<--  whichUnit: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HLOCATION( __cdecl *GAME_GetUnitRallyPoint )( HUNIT whichUnit );
GAME_GetUnitRallyPoint GAME_GetUnitRallyPointorg = NULL;
GAME_GetUnitRallyPoint GAME_GetUnitRallyPointold = NULL;

HLOCATION __cdecl GAME_GetUnitRallyPointmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitRallyPointmy" );
	fflush( logfile );

	HLOCATION retvalue = GAME_GetUnitRallyPointold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitRallyPoint<--  whichUnit: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_GetUnitRallyUnit )( HUNIT whichUnit );
GAME_GetUnitRallyUnit GAME_GetUnitRallyUnitorg = NULL;
GAME_GetUnitRallyUnit GAME_GetUnitRallyUnitold = NULL;

HUNIT __cdecl GAME_GetUnitRallyUnitmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitRallyUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_GetUnitRallyUnitold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitRallyUnit<--  whichUnit: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetUnitState )( HUNIT whichUnit , HUNITSTATE whichUnitState );
GAME_GetUnitState GAME_GetUnitStateorg = NULL;
GAME_GetUnitState GAME_GetUnitStateold = NULL;

DWFP __cdecl GAME_GetUnitStatemy( HUNIT whichUnit , HUNITSTATE whichUnitState )
{
	fprintf_s( logfile , "%s\n" , "GetUnitStatemy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetUnitStateold( whichUnit , whichUnitState );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitState<--  whichUnit: %X whichUnitState: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichUnit , whichUnitState , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetUnitTurnSpeed )( HUNIT whichUnit );
GAME_GetUnitTurnSpeed GAME_GetUnitTurnSpeedorg = NULL;
GAME_GetUnitTurnSpeed GAME_GetUnitTurnSpeedold = NULL;

DWFP __cdecl GAME_GetUnitTurnSpeedmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitTurnSpeedmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetUnitTurnSpeedold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitTurnSpeed<--  whichUnit: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetUnitTypeId )( HUNIT whichUnit );
GAME_GetUnitTypeId GAME_GetUnitTypeIdorg = NULL;
GAME_GetUnitTypeId GAME_GetUnitTypeIdold = NULL;

int __cdecl GAME_GetUnitTypeIdmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitTypeIdmy" );
	fflush( logfile );

	int retvalue = GAME_GetUnitTypeIdold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitTypeId<--  whichUnit: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetUnitUserData )( HUNIT whichUnit );
GAME_GetUnitUserData GAME_GetUnitUserDataorg = NULL;
GAME_GetUnitUserData GAME_GetUnitUserDataold = NULL;

int __cdecl GAME_GetUnitUserDatamy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitUserDatamy" );
	fflush( logfile );

	int retvalue = GAME_GetUnitUserDataold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitUserData<--  whichUnit: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetUnitWoodCost )( int arg1 );
GAME_GetUnitWoodCost GAME_GetUnitWoodCostorg = NULL;
GAME_GetUnitWoodCost GAME_GetUnitWoodCostold = NULL;

int __cdecl GAME_GetUnitWoodCostmy( int arg1 )
{
	fprintf_s( logfile , "%s\n" , "GetUnitWoodCostmy" );
	fflush( logfile );

	int retvalue = GAME_GetUnitWoodCostold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitWoodCost<--  arg1: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , arg1 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetUnitX )( HUNIT whichUnit );
GAME_GetUnitX GAME_GetUnitXorg = NULL;
GAME_GetUnitX GAME_GetUnitXold = NULL;

DWFP __cdecl GAME_GetUnitXmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitXmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetUnitXold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitX<--  whichUnit: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetUnitY )( HUNIT whichUnit );
GAME_GetUnitY GAME_GetUnitYorg = NULL;
GAME_GetUnitY GAME_GetUnitYold = NULL;

DWFP __cdecl GAME_GetUnitYmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GetUnitYmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetUnitYold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GetUnitY<--  whichUnit: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetUpgradeGoldCost )( int arg1 );
GAME_GetUpgradeGoldCost GAME_GetUpgradeGoldCostorg = NULL;
GAME_GetUpgradeGoldCost GAME_GetUpgradeGoldCostold = NULL;

int __cdecl GAME_GetUpgradeGoldCostmy( int arg1 )
{
	fprintf_s( logfile , "%s\n" , "GetUpgradeGoldCostmy" );
	fflush( logfile );

	int retvalue = GAME_GetUpgradeGoldCostold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_GetUpgradeGoldCost<--  arg1: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , arg1 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetUpgradeLevel )( int arg1 );
GAME_GetUpgradeLevel GAME_GetUpgradeLevelorg = NULL;
GAME_GetUpgradeLevel GAME_GetUpgradeLevelold = NULL;

int __cdecl GAME_GetUpgradeLevelmy( int arg1 )
{
	fprintf_s( logfile , "%s\n" , "GetUpgradeLevelmy" );
	fflush( logfile );

	int retvalue = GAME_GetUpgradeLevelold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_GetUpgradeLevel<--  arg1: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , arg1 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_GetUpgradeWoodCost )( int arg1 );
GAME_GetUpgradeWoodCost GAME_GetUpgradeWoodCostorg = NULL;
GAME_GetUpgradeWoodCost GAME_GetUpgradeWoodCostold = NULL;

int __cdecl GAME_GetUpgradeWoodCostmy( int arg1 )
{
	fprintf_s( logfile , "%s\n" , "GetUpgradeWoodCostmy" );
	fflush( logfile );

	int retvalue = GAME_GetUpgradeWoodCostold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_GetUpgradeWoodCost<--  arg1: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , arg1 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetWidgetLife )( HWIDGET whichWidget );
GAME_GetWidgetLife GAME_GetWidgetLifeorg = NULL;
GAME_GetWidgetLife GAME_GetWidgetLifeold = NULL;

DWFP __cdecl GAME_GetWidgetLifemy( HWIDGET whichWidget )
{
	fprintf_s( logfile , "%s\n" , "GetWidgetLifemy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetWidgetLifeold( whichWidget );
	fprintf_s( logfile , "%s:[-->GAME_GetWidgetLife<--  whichWidget: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichWidget , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetWidgetX )( HWIDGET whichWidget );
GAME_GetWidgetX GAME_GetWidgetXorg = NULL;
GAME_GetWidgetX GAME_GetWidgetXold = NULL;

DWFP __cdecl GAME_GetWidgetXmy( HWIDGET whichWidget )
{
	fprintf_s( logfile , "%s\n" , "GetWidgetXmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetWidgetXold( whichWidget );
	fprintf_s( logfile , "%s:[-->GAME_GetWidgetX<--  whichWidget: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichWidget , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_GetWidgetY )( HWIDGET whichWidget );
GAME_GetWidgetY GAME_GetWidgetYorg = NULL;
GAME_GetWidgetY GAME_GetWidgetYold = NULL;

DWFP __cdecl GAME_GetWidgetYmy( HWIDGET whichWidget )
{
	fprintf_s( logfile , "%s\n" , "GetWidgetYmy" );
	fflush( logfile );

	DWFP retvalue = GAME_GetWidgetYold( whichWidget );
	fprintf_s( logfile , "%s:[-->GAME_GetWidgetY<--  whichWidget: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichWidget , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYER( __cdecl *GAME_GetWinningPlayer )( );
GAME_GetWinningPlayer GAME_GetWinningPlayerorg = NULL;
GAME_GetWinningPlayer GAME_GetWinningPlayerold = NULL;

HPLAYER __cdecl GAME_GetWinningPlayermy( )
{
	fprintf_s( logfile , "%s\n" , "GetWinningPlayermy" );
	fflush( logfile );

	HPLAYER retvalue = GAME_GetWinningPlayerold( );
	fprintf_s( logfile , "%s:[-->GAME_GetWinningPlayer<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HRECT( __cdecl *GAME_GetWorldBounds )( );
GAME_GetWorldBounds GAME_GetWorldBoundsorg = NULL;
GAME_GetWorldBounds GAME_GetWorldBoundsold = NULL;

HRECT __cdecl GAME_GetWorldBoundsmy( )
{
	fprintf_s( logfile , "%s\n" , "GetWorldBoundsmy" );
	fflush( logfile );

	HRECT retvalue = GAME_GetWorldBoundsold( );
	fprintf_s( logfile , "%s:[-->GAME_GetWorldBounds<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_GroupAddUnit )( HGROUP whichGroup , HUNIT whichUnit );
GAME_GroupAddUnit GAME_GroupAddUnitorg = NULL;
GAME_GroupAddUnit GAME_GroupAddUnitold = NULL;

void __cdecl GAME_GroupAddUnitmy( HGROUP whichGroup , HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "GroupAddUnitmy" );
	fflush( logfile );

	GAME_GroupAddUnitold( whichGroup , whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GroupAddUnit<--  whichGroup: %X whichUnit: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichGroup , whichUnit );
	fflush( logfile );

}


typedef void( __cdecl *GAME_GroupClear )( HGROUP whichGroup );
GAME_GroupClear GAME_GroupClearorg = NULL;
GAME_GroupClear GAME_GroupClearold = NULL;

void __cdecl GAME_GroupClearmy( HGROUP whichGroup )
{
	fprintf_s( logfile , "%s\n" , "GroupClearmy" );
	fflush( logfile );

	GAME_GroupClearold( whichGroup );
	fprintf_s( logfile , "%s:[-->GAME_GroupClear<--  whichGroup: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichGroup );
	fflush( logfile );

}


typedef void( __cdecl *GAME_GroupEnumUnitsInRange )( HGROUP whichGroup , float *x , float *y , float *radius , HBOOLEXPR filter );
GAME_GroupEnumUnitsInRange GAME_GroupEnumUnitsInRangeorg = NULL;
GAME_GroupEnumUnitsInRange GAME_GroupEnumUnitsInRangeold = NULL;

void __cdecl GAME_GroupEnumUnitsInRangemy( HGROUP whichGroup , float *x , float *y , float *radius , HBOOLEXPR filter )
{
	fprintf_s( logfile , "%s\n" , "GroupEnumUnitsInRangemy" );
	fflush( logfile );

	GAME_GroupEnumUnitsInRangeold( whichGroup , x , y , radius , filter );
	fprintf_s( logfile , "%s:[-->GAME_GroupEnumUnitsInRange<--  whichGroup: %X x: %f y: %f radius: %f filter: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichGroup , *( float * ) x , *( float * ) y , *( float * ) radius , filter );
	fflush( logfile );

}


typedef void( __cdecl *GAME_GroupEnumUnitsInRangeCounted )( HGROUP whichGroup , float *x , float *y , float *radius , HBOOLEXPR filter , int countLimit );
GAME_GroupEnumUnitsInRangeCounted GAME_GroupEnumUnitsInRangeCountedorg = NULL;
GAME_GroupEnumUnitsInRangeCounted GAME_GroupEnumUnitsInRangeCountedold = NULL;

void __cdecl GAME_GroupEnumUnitsInRangeCountedmy( HGROUP whichGroup , float *x , float *y , float *radius , HBOOLEXPR filter , int countLimit )
{
	fprintf_s( logfile , "%s\n" , "GroupEnumUnitsInRangeCountedmy" );
	fflush( logfile );

	GAME_GroupEnumUnitsInRangeCountedold( whichGroup , x , y , radius , filter , countLimit );
	fprintf_s( logfile , "%s:[-->GAME_GroupEnumUnitsInRangeCounted<--  whichGroup: %X x: %f y: %f radius: %f filter: %X countLimit: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichGroup , *( float * ) x , *( float * ) y , *( float * ) radius , filter , countLimit );
	fflush( logfile );

}


typedef void( __cdecl *GAME_GroupEnumUnitsInRangeOfLoc )( HGROUP whichGroup , HLOCATION whichLocation , float *radius , HBOOLEXPR filter );
GAME_GroupEnumUnitsInRangeOfLoc GAME_GroupEnumUnitsInRangeOfLocorg = NULL;
GAME_GroupEnumUnitsInRangeOfLoc GAME_GroupEnumUnitsInRangeOfLocold = NULL;

void __cdecl GAME_GroupEnumUnitsInRangeOfLocmy( HGROUP whichGroup , HLOCATION whichLocation , float *radius , HBOOLEXPR filter )
{
	fprintf_s( logfile , "%s\n" , "GroupEnumUnitsInRangeOfLocmy" );
	fflush( logfile );

	GAME_GroupEnumUnitsInRangeOfLocold( whichGroup , whichLocation , radius , filter );
	fprintf_s( logfile , "%s:[-->GAME_GroupEnumUnitsInRangeOfLoc<--  whichGroup: %X whichLocation: %X radius: %f filter: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichGroup , whichLocation , *( float * ) radius , filter );
	fflush( logfile );

}


typedef void( __cdecl *GAME_GroupEnumUnitsInRangeOfLocCounted )( HGROUP whichGroup , HLOCATION whichLocation , float *radius , HBOOLEXPR filter , int countLimit );
GAME_GroupEnumUnitsInRangeOfLocCounted GAME_GroupEnumUnitsInRangeOfLocCountedorg = NULL;
GAME_GroupEnumUnitsInRangeOfLocCounted GAME_GroupEnumUnitsInRangeOfLocCountedold = NULL;

void __cdecl GAME_GroupEnumUnitsInRangeOfLocCountedmy( HGROUP whichGroup , HLOCATION whichLocation , float *radius , HBOOLEXPR filter , int countLimit )
{
	fprintf_s( logfile , "%s\n" , "GroupEnumUnitsInRangeOfLocCountedmy" );
	fflush( logfile );

	GAME_GroupEnumUnitsInRangeOfLocCountedold( whichGroup , whichLocation , radius , filter , countLimit );
	fprintf_s( logfile , "%s:[-->GAME_GroupEnumUnitsInRangeOfLocCounted<--  whichGroup: %X whichLocation: %X radius: %f filter: %X countLimit: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichGroup , whichLocation , *( float * ) radius , filter , countLimit );
	fflush( logfile );

}


typedef void( __cdecl *GAME_GroupEnumUnitsInRect )( HGROUP whichGroup , HRECT r , HBOOLEXPR filter );
GAME_GroupEnumUnitsInRect GAME_GroupEnumUnitsInRectorg = NULL;
GAME_GroupEnumUnitsInRect GAME_GroupEnumUnitsInRectold = NULL;

void __cdecl GAME_GroupEnumUnitsInRectmy( HGROUP whichGroup , HRECT r , HBOOLEXPR filter )
{
	fprintf_s( logfile , "%s\n" , "GroupEnumUnitsInRectmy" );
	fflush( logfile );

	GAME_GroupEnumUnitsInRectold( whichGroup , r , filter );
	fprintf_s( logfile , "%s:[-->GAME_GroupEnumUnitsInRect<--  whichGroup: %X r: %X filter: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichGroup , r , filter );
	fflush( logfile );

}


typedef void( __cdecl *GAME_GroupEnumUnitsInRectCounted )( HGROUP whichGroup , HRECT r , HBOOLEXPR filter , int countLimit );
GAME_GroupEnumUnitsInRectCounted GAME_GroupEnumUnitsInRectCountedorg = NULL;
GAME_GroupEnumUnitsInRectCounted GAME_GroupEnumUnitsInRectCountedold = NULL;

void __cdecl GAME_GroupEnumUnitsInRectCountedmy( HGROUP whichGroup , HRECT r , HBOOLEXPR filter , int countLimit )
{
	fprintf_s( logfile , "%s\n" , "GroupEnumUnitsInRectCountedmy" );
	fflush( logfile );

	GAME_GroupEnumUnitsInRectCountedold( whichGroup , r , filter , countLimit );
	fprintf_s( logfile , "%s:[-->GAME_GroupEnumUnitsInRectCounted<--  whichGroup: %X r: %X filter: %X countLimit: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichGroup , r , filter , countLimit );
	fflush( logfile );

}


typedef void( __cdecl *GAME_GroupEnumUnitsOfPlayer )( HGROUP whichGroup , HPLAYER whichPlayer , HBOOLEXPR filter );
GAME_GroupEnumUnitsOfPlayer GAME_GroupEnumUnitsOfPlayerorg = NULL;
GAME_GroupEnumUnitsOfPlayer GAME_GroupEnumUnitsOfPlayerold = NULL;

void __cdecl GAME_GroupEnumUnitsOfPlayermy( HGROUP whichGroup , HPLAYER whichPlayer , HBOOLEXPR filter )
{
	fprintf_s( logfile , "%s\n" , "GroupEnumUnitsOfPlayermy" );
	fflush( logfile );

	GAME_GroupEnumUnitsOfPlayerold( whichGroup , whichPlayer , filter );
	fprintf_s( logfile , "%s:[-->GAME_GroupEnumUnitsOfPlayer<--  whichGroup: %X whichPlayer: %X filter: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichGroup , whichPlayer , filter );
	fflush( logfile );

}


typedef void( __cdecl *GAME_GroupEnumUnitsOfType )( HGROUP whichGroup , void * unitname , HBOOLEXPR filter );
GAME_GroupEnumUnitsOfType GAME_GroupEnumUnitsOfTypeorg = NULL;
GAME_GroupEnumUnitsOfType GAME_GroupEnumUnitsOfTypeold = NULL;

void __cdecl GAME_GroupEnumUnitsOfTypemy( HGROUP whichGroup , void * unitname , HBOOLEXPR filter )
{
	fprintf_s( logfile , "%s\n" , "GroupEnumUnitsOfTypemy" );
	fflush( logfile );

	GAME_GroupEnumUnitsOfTypeold( whichGroup , unitname , filter );
	fprintf_s( logfile , "%s:[-->GAME_GroupEnumUnitsOfType<--  whichGroup: %X unitname: \"%s\" filter: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichGroup , jassgetchar( unitname ) , filter );
	fflush( logfile );

}


typedef void( __cdecl *GAME_GroupEnumUnitsOfTypeCounted )( HGROUP whichGroup , void * unitname , HBOOLEXPR filter , int countLimit );
GAME_GroupEnumUnitsOfTypeCounted GAME_GroupEnumUnitsOfTypeCountedorg = NULL;
GAME_GroupEnumUnitsOfTypeCounted GAME_GroupEnumUnitsOfTypeCountedold = NULL;

void __cdecl GAME_GroupEnumUnitsOfTypeCountedmy( HGROUP whichGroup , void * unitname , HBOOLEXPR filter , int countLimit )
{
	fprintf_s( logfile , "%s" , "GroupEnumUnitsOfTypeCountedmy\n" );
	fflush( logfile );

	GAME_GroupEnumUnitsOfTypeCountedold( whichGroup , unitname , filter , countLimit );
	fprintf_s( logfile , "%s:[-->GAME_GroupEnumUnitsOfTypeCounted<--  whichGroup: %X unitname: \"%s\" filter: %X countLimit: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichGroup , jassgetchar( unitname ) , filter , countLimit );
	fflush( logfile );

}


typedef void( __cdecl *GAME_GroupEnumUnitsSelected )( HGROUP whichGroup , HPLAYER whichPlayer , HBOOLEXPR filter );
GAME_GroupEnumUnitsSelected GAME_GroupEnumUnitsSelectedorg = NULL;
GAME_GroupEnumUnitsSelected GAME_GroupEnumUnitsSelectedold = NULL;

void __cdecl GAME_GroupEnumUnitsSelectedmy( HGROUP whichGroup , HPLAYER whichPlayer , HBOOLEXPR filter )
{
	fprintf_s( logfile , "%s" , "GroupEnumUnitsSelectedmy\n" );
	fflush( logfile );

	GAME_GroupEnumUnitsSelectedold( whichGroup , whichPlayer , filter );
	fprintf_s( logfile , "%s:[-->GAME_GroupEnumUnitsSelected<--  whichGroup: %X whichPlayer: %X filter: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichGroup , whichPlayer , filter );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_GroupImmediateOrder )( HGROUP whichGroup , void * order );
GAME_GroupImmediateOrder GAME_GroupImmediateOrderorg = NULL;
GAME_GroupImmediateOrder GAME_GroupImmediateOrderold = NULL;

BOOL __cdecl GAME_GroupImmediateOrdermy( HGROUP whichGroup , void * order )
{
	fprintf_s( logfile , "%s\n" , "GroupImmediateOrdermy" );
	fflush( logfile );

	BOOL retvalue = GAME_GroupImmediateOrderold( whichGroup , order );
	fprintf_s( logfile , "%s:[-->GAME_GroupImmediateOrder<--  whichGroup: %X order: \"%s\"] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichGroup , jassgetchar( order ) , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_GroupImmediateOrderById )( HGROUP whichGroup , int order );
GAME_GroupImmediateOrderById GAME_GroupImmediateOrderByIdorg = NULL;
GAME_GroupImmediateOrderById GAME_GroupImmediateOrderByIdold = NULL;

BOOL __cdecl GAME_GroupImmediateOrderByIdmy( HGROUP whichGroup , int order )
{
	fprintf_s( logfile , "%s" , "GroupImmediateOrderByIdmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_GroupImmediateOrderByIdold( whichGroup , order );
	fprintf_s( logfile , "%s:[-->GAME_GroupImmediateOrderById<--  whichGroup: %X order: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichGroup , order , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_GroupPointOrder )( HGROUP whichGroup , void * order , float *x , float *y );
GAME_GroupPointOrder GAME_GroupPointOrderorg = NULL;
GAME_GroupPointOrder GAME_GroupPointOrderold = NULL;

BOOL __cdecl GAME_GroupPointOrdermy( HGROUP whichGroup , void * order , float *x , float *y )
{
	fprintf_s( logfile , "%s" , "GroupPointOrdermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_GroupPointOrderold( whichGroup , order , x , y );
	fprintf_s( logfile , "%s:[-->GAME_GroupPointOrder<--  whichGroup: %X order: \"%s\" x: %f y: %f] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichGroup , jassgetchar( order ) , *( float * ) x , *( float * ) y , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_GroupPointOrderById )( HGROUP whichGroup , int order , float *x , float *y );
GAME_GroupPointOrderById GAME_GroupPointOrderByIdorg = NULL;
GAME_GroupPointOrderById GAME_GroupPointOrderByIdold = NULL;

BOOL __cdecl GAME_GroupPointOrderByIdmy( HGROUP whichGroup , int order , float *x , float *y )
{
	fprintf_s( logfile , "%s" , "GroupPointOrderByIdmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_GroupPointOrderByIdold( whichGroup , order , x , y );
	fprintf_s( logfile , "%s:[-->GAME_GroupPointOrderById<--  whichGroup: %X order: %i x: %f y: %f] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichGroup , order , *( float * ) x , *( float * ) y , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_GroupPointOrderByIdLoc )( HGROUP whichGroup , int order , HLOCATION whichLocation );
GAME_GroupPointOrderByIdLoc GAME_GroupPointOrderByIdLocorg = NULL;
GAME_GroupPointOrderByIdLoc GAME_GroupPointOrderByIdLocold = NULL;

BOOL __cdecl GAME_GroupPointOrderByIdLocmy( HGROUP whichGroup , int order , HLOCATION whichLocation )
{
	fprintf_s( logfile , "%s" , "GroupPointOrderByIdLocmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_GroupPointOrderByIdLocold( whichGroup , order , whichLocation );
	fprintf_s( logfile , "%s:[-->GAME_GroupPointOrderByIdLoc<--  whichGroup: %X order: %i whichLocation: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichGroup , order , whichLocation , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_GroupPointOrderLoc )( HGROUP whichGroup , void * order , HLOCATION whichLocation );
GAME_GroupPointOrderLoc GAME_GroupPointOrderLocorg = NULL;
GAME_GroupPointOrderLoc GAME_GroupPointOrderLocold = NULL;

BOOL __cdecl GAME_GroupPointOrderLocmy( HGROUP whichGroup , void * order , HLOCATION whichLocation )
{
	fprintf_s( logfile , "%s" , "GroupPointOrderLocmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_GroupPointOrderLocold( whichGroup , order , whichLocation );
	fprintf_s( logfile , "%s:[-->GAME_GroupPointOrderLoc<--  whichGroup: %X order: \"%s\" whichLocation: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichGroup , jassgetchar( order ) , whichLocation , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_GroupRemoveUnit )( HGROUP whichGroup , HUNIT whichUnit );
GAME_GroupRemoveUnit GAME_GroupRemoveUnitorg = NULL;
GAME_GroupRemoveUnit GAME_GroupRemoveUnitold = NULL;

void __cdecl GAME_GroupRemoveUnitmy( HGROUP whichGroup , HUNIT whichUnit )
{
	fprintf_s( logfile , "%s" , "GroupRemoveUnitmy\n" );
	fflush( logfile );

	GAME_GroupRemoveUnitold( whichGroup , whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_GroupRemoveUnit<--  whichGroup: %X whichUnit: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichGroup , whichUnit );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_GroupTargetOrder )( HGROUP whichGroup , void * order , HWIDGET targetWidget );
GAME_GroupTargetOrder GAME_GroupTargetOrderorg = NULL;
GAME_GroupTargetOrder GAME_GroupTargetOrderold = NULL;

BOOL __cdecl GAME_GroupTargetOrdermy( HGROUP whichGroup , void * order , HWIDGET targetWidget )
{
	fprintf_s( logfile , "%s\n" , "GroupTargetOrdermy" );
	fflush( logfile );

	BOOL retvalue = GAME_GroupTargetOrderold( whichGroup , order , targetWidget );
	fprintf_s( logfile , "%s:[-->GAME_GroupTargetOrder<--  whichGroup: %X order: \"%s\" targetWidget: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichGroup , jassgetchar( order ) , targetWidget , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_GroupTargetOrderById )( HGROUP whichGroup , int order , HWIDGET targetWidget );
GAME_GroupTargetOrderById GAME_GroupTargetOrderByIdorg = NULL;
GAME_GroupTargetOrderById GAME_GroupTargetOrderByIdold = NULL;

BOOL __cdecl GAME_GroupTargetOrderByIdmy( HGROUP whichGroup , int order , HWIDGET targetWidget )
{
	fprintf_s( logfile , "%s" , "GroupTargetOrderByIdmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_GroupTargetOrderByIdold( whichGroup , order , targetWidget );
	fprintf_s( logfile , "%s:[-->GAME_GroupTargetOrderById<--  whichGroup: %X order: %i targetWidget: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichGroup , order , targetWidget , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_GroupTimedLife )( BOOL arg1 );
GAME_GroupTimedLife GAME_GroupTimedLifeorg = NULL;
GAME_GroupTimedLife GAME_GroupTimedLifeold = NULL;

void __cdecl GAME_GroupTimedLifemy( BOOL arg1 )
{
	fprintf_s( logfile , "%s" , "GroupTimedLifemy\n" );
	fflush( logfile );

	GAME_GroupTimedLifeold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_GroupTimedLife<--  arg1: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_HarvestGold )( int arg1 , int arg2 );
GAME_HarvestGold GAME_HarvestGoldorg = NULL;
GAME_HarvestGold GAME_HarvestGoldold = NULL;

void __cdecl GAME_HarvestGoldmy( int arg1 , int arg2 )
{
	fprintf_s( logfile , "%s" , "HarvestGoldmy\n" );
	fflush( logfile );

	GAME_HarvestGoldold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_HarvestGold<--  arg1: %i arg2: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 , arg2 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_HarvestWood )( int arg1 , int arg2 );
GAME_HarvestWood GAME_HarvestWoodorg = NULL;
GAME_HarvestWood GAME_HarvestWoodold = NULL;

void __cdecl GAME_HarvestWoodmy( int arg1 , int arg2 )
{
	fprintf_s( logfile , "%s\n" , "HarvestWoodmy" );
	fflush( logfile );

	GAME_HarvestWoodold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_HarvestWood<--  arg1: %i arg2: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 , arg2 );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_HaveSavedBOOLean )( HHASHTABLE table , int parentKey , int childKey );
GAME_HaveSavedBOOLean GAME_HaveSavedBOOLeanorg = NULL;
GAME_HaveSavedBOOLean GAME_HaveSavedBOOLeanold = NULL;

BOOL __cdecl GAME_HaveSavedBOOLeanmy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "HaveSavedBOOLeanmy" );
	fflush( logfile );

	BOOL retvalue = GAME_HaveSavedBOOLeanold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_HaveSavedBOOLean<--  table: %X parentKey: %i childKey: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_HaveSavedHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_HaveSavedHandle GAME_HaveSavedHandleorg = NULL;
GAME_HaveSavedHandle GAME_HaveSavedHandleold = NULL;

BOOL __cdecl GAME_HaveSavedHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s" , "HaveSavedHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_HaveSavedHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_HaveSavedHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_HaveSavedInteger )( HHASHTABLE table , int parentKey , int childKey );
GAME_HaveSavedInteger GAME_HaveSavedIntegerorg = NULL;
GAME_HaveSavedInteger GAME_HaveSavedIntegerold = NULL;

BOOL __cdecl GAME_HaveSavedIntegermy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s" , "HaveSavedIntegermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_HaveSavedIntegerold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_HaveSavedInteger<--  table: %X parentKey: %i childKey: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_HaveSavedReal )( HHASHTABLE table , int parentKey , int childKey );
GAME_HaveSavedReal GAME_HaveSavedRealorg = NULL;
GAME_HaveSavedReal GAME_HaveSavedRealold = NULL;

BOOL __cdecl GAME_HaveSavedRealmy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s" , "HaveSavedRealmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_HaveSavedRealold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_HaveSavedReal<--  table: %X parentKey: %i childKey: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_HaveSavedString )( HHASHTABLE table , int parentKey , int childKey );
GAME_HaveSavedString GAME_HaveSavedStringorg = NULL;
GAME_HaveSavedString GAME_HaveSavedStringold = NULL;

BOOL __cdecl GAME_HaveSavedStringmy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s" , "HaveSavedStringmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_HaveSavedStringold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_HaveSavedString<--  table: %X parentKey: %i childKey: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_HaveStoredBOOLean )( HGAMECACHE cache , void * missionKey , void * key );
GAME_HaveStoredBOOLean GAME_HaveStoredBOOLeanorg = NULL;
GAME_HaveStoredBOOLean GAME_HaveStoredBOOLeanold = NULL;

BOOL __cdecl GAME_HaveStoredBOOLeanmy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s" , "HaveStoredBOOLeanmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_HaveStoredBOOLeanold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_HaveStoredBOOLean<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> %s\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_HaveStoredInteger )( HGAMECACHE cache , void * missionKey , void * key );
GAME_HaveStoredInteger GAME_HaveStoredIntegerorg = NULL;
GAME_HaveStoredInteger GAME_HaveStoredIntegerold = NULL;

BOOL __cdecl GAME_HaveStoredIntegermy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s" , "HaveStoredIntegermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_HaveStoredIntegerold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_HaveStoredInteger<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> %s\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_HaveStoredReal )( HGAMECACHE cache , void * missionKey , void * key );
GAME_HaveStoredReal GAME_HaveStoredRealorg = NULL;
GAME_HaveStoredReal GAME_HaveStoredRealold = NULL;

BOOL __cdecl GAME_HaveStoredRealmy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s" , "HaveStoredRealmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_HaveStoredRealold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_HaveStoredReal<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> %s\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_HaveStoredString )( HGAMECACHE cache , void * missionKey , void * key );
GAME_HaveStoredString GAME_HaveStoredStringorg = NULL;
GAME_HaveStoredString GAME_HaveStoredStringold = NULL;

BOOL __cdecl GAME_HaveStoredStringmy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s" , "HaveStoredStringmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_HaveStoredStringold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_HaveStoredString<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> %s\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_HaveStoredUnit )( HGAMECACHE cache , void * missionKey , void * key );
GAME_HaveStoredUnit GAME_HaveStoredUnitorg = NULL;
GAME_HaveStoredUnit GAME_HaveStoredUnitold = NULL;

BOOL __cdecl GAME_HaveStoredUnitmy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s" , "HaveStoredUnitmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_HaveStoredUnitold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_HaveStoredUnit<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> %s\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_I2R )( int i );
GAME_I2R GAME_I2Rorg = NULL;
GAME_I2R GAME_I2Rold = NULL;

DWFP __cdecl GAME_I2Rmy( int i )
{
	fprintf_s( logfile , "%s" , "I2Rmy\n" );
	fflush( logfile );

	DWFP retvalue = GAME_I2Rold( i );
	fprintf_s( logfile , "%s:[-->GAME_I2R<--  i: %i] RETURN-> %f\n" , currentDateTime( ).c_str( ) , i , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_I2S )( int i );
GAME_I2S GAME_I2Sorg = NULL;
GAME_I2S GAME_I2Sold = NULL;

DWORD __cdecl GAME_I2Smy( int i )
{
	fprintf_s( logfile , "%s\n" , "I2Smy" );
	fflush( logfile );

	DWORD retvalue = GAME_I2Sold( i );
	fprintf_s( logfile , "%s:[-->GAME_I2S<--  i: %i] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , i , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_IgnoredUnits )( int arg1 );
GAME_IgnoredUnits GAME_IgnoredUnitsorg = NULL;
GAME_IgnoredUnits GAME_IgnoredUnitsold = NULL;

int __cdecl GAME_IgnoredUnitsmy( int arg1 )
{
	fprintf_s( logfile , "%s\n" , "IgnoredUnitsmy" );
	fflush( logfile );

	int retvalue = GAME_IgnoredUnitsold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_IgnoredUnits<--  arg1: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , arg1 , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_IncUnitAbilityLevel )( HUNIT whichUnit , int abilcode );
GAME_IncUnitAbilityLevel GAME_IncUnitAbilityLevelorg = NULL;
GAME_IncUnitAbilityLevel GAME_IncUnitAbilityLevelold = NULL;

int __cdecl GAME_IncUnitAbilityLevelmy( HUNIT whichUnit , int abilcode )
{
	fprintf_s( logfile , "%s\n" , "IncUnitAbilityLevelmy" );
	fflush( logfile );

	int retvalue = GAME_IncUnitAbilityLevelold( whichUnit , abilcode );
	fprintf_s( logfile , "%s:[-->GAME_IncUnitAbilityLevel<--  whichUnit: %X abilcode: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichUnit , abilcode , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_InitAssault )( );
GAME_InitAssault GAME_InitAssaultorg = NULL;
GAME_InitAssault GAME_InitAssaultold = NULL;

void __cdecl GAME_InitAssaultmy( )
{
	fprintf_s( logfile , "%s\n" , "InitAssaultmy" );
	fflush( logfile );

	GAME_InitAssaultold( );
	fprintf_s( logfile , "%s:[-->GAME_InitAssault<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef HGAMECACHE( __cdecl *GAME_InitGameCache )( void * campaignFile );
GAME_InitGameCache GAME_InitGameCacheorg = NULL;
GAME_InitGameCache GAME_InitGameCacheold = NULL;

HGAMECACHE __cdecl GAME_InitGameCachemy( void * campaignFile )
{
	fprintf_s( logfile , "%s\n" , "InitGameCachemy" );
	fflush( logfile );

	HGAMECACHE retvalue = GAME_InitGameCacheold( campaignFile );
	fprintf_s( logfile , "%s:[-->GAME_InitGameCache<--  campaignFile: \"%s\"] RETURN-> %X\n" , currentDateTime( ).c_str( ) , jassgetchar( campaignFile ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HHASHTABLE( __cdecl *GAME_InitHashtable )( );
GAME_InitHashtable GAME_InitHashtableorg = NULL;
GAME_InitHashtable GAME_InitHashtableold = NULL;

HHASHTABLE __cdecl GAME_InitHashtablemy( )
{
	fprintf_s( logfile , "%s" , "InitHashtablemy\n" );
	fflush( logfile );

	HHASHTABLE retvalue = GAME_InitHashtableold( );
	fprintf_s( logfile , "%s:[-->GAME_InitHashtable<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsCineFilterDisplayed )( );
GAME_IsCineFilterDisplayed GAME_IsCineFilterDisplayedorg = NULL;
GAME_IsCineFilterDisplayed GAME_IsCineFilterDisplayedold = NULL;

BOOL __cdecl GAME_IsCineFilterDisplayedmy( )
{
	fprintf_s( logfile , "%s\n" , "IsCineFilterDisplayedmy" );
	fflush( logfile );

	BOOL retvalue = GAME_IsCineFilterDisplayedold( );
	fprintf_s( logfile , "%s:[-->GAME_IsCineFilterDisplayed<-- ] RETURN-> %s\n" , currentDateTime( ).c_str( ) , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsDestructableInvulnerable )( HDESTRUCTABLE d );
GAME_IsDestructableInvulnerable GAME_IsDestructableInvulnerableorg = NULL;
GAME_IsDestructableInvulnerable GAME_IsDestructableInvulnerableold = NULL;

BOOL __cdecl GAME_IsDestructableInvulnerablemy( HDESTRUCTABLE d )
{
	fprintf_s( logfile , "%s" , "IsDestructableInvulnerablemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsDestructableInvulnerableold( d );
	fprintf_s( logfile , "%s:[-->GAME_IsDestructableInvulnerable<--  d: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , d , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsFogEnabled )( );
GAME_IsFogEnabled GAME_IsFogEnabledorg = NULL;
GAME_IsFogEnabled GAME_IsFogEnabledold = NULL;

BOOL __cdecl GAME_IsFogEnabledmy( )
{
	fprintf_s( logfile , "%s" , "IsFogEnabledmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsFogEnabledold( );
	fprintf_s( logfile , "%s:[-->GAME_IsFogEnabled<-- ] RETURN-> %s\n" , currentDateTime( ).c_str( ) , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsFogMaskEnabled )( );
GAME_IsFogMaskEnabled GAME_IsFogMaskEnabledorg = NULL;
GAME_IsFogMaskEnabled GAME_IsFogMaskEnabledold = NULL;

BOOL __cdecl GAME_IsFogMaskEnabledmy( )
{
	fprintf_s( logfile , "%s" , "IsFogMaskEnabledmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsFogMaskEnabledold( );
	fprintf_s( logfile , "%s:[-->GAME_IsFogMaskEnabled<-- ] RETURN-> %s\n" , currentDateTime( ).c_str( ) , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsFoggedToPlayer )( float *x , float *y , HPLAYER whichPlayer );
GAME_IsFoggedToPlayer GAME_IsFoggedToPlayerorg = NULL;
GAME_IsFoggedToPlayer GAME_IsFoggedToPlayerold = NULL;

BOOL __cdecl GAME_IsFoggedToPlayermy( float *x , float *y , HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "IsFoggedToPlayermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsFoggedToPlayerold( x , y , whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_IsFoggedToPlayer<--  x: %f y: %f whichPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , whichPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsGameTypeSupported )( HGAMETYPE whichGameType );
GAME_IsGameTypeSupported GAME_IsGameTypeSupportedorg = NULL;
GAME_IsGameTypeSupported GAME_IsGameTypeSupportedold = NULL;

BOOL __cdecl GAME_IsGameTypeSupportedmy( HGAMETYPE whichGameType )
{
	fprintf_s( logfile , "%s" , "IsGameTypeSupportedmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsGameTypeSupportedold( whichGameType );
	fprintf_s( logfile , "%s:[-->GAME_IsGameTypeSupported<--  whichGameType: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichGameType , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsHeroUnitId )( int unitId );
GAME_IsHeroUnitId GAME_IsHeroUnitIdorg = NULL;
GAME_IsHeroUnitId GAME_IsHeroUnitIdold = NULL;

BOOL __cdecl GAME_IsHeroUnitIdmy( int unitId )
{
	fprintf_s( logfile , "%s" , "IsHeroUnitIdmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsHeroUnitIdold( unitId );
	fprintf_s( logfile , "%s:[-->GAME_IsHeroUnitId<--  unitId: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , unitId , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsItemIdPawnable )( int itemId );
GAME_IsItemIdPawnable GAME_IsItemIdPawnableorg = NULL;
GAME_IsItemIdPawnable GAME_IsItemIdPawnableold = NULL;

BOOL __cdecl GAME_IsItemIdPawnablemy( int itemId )
{
	fprintf_s( logfile , "%s" , "IsItemIdPawnablemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsItemIdPawnableold( itemId );
	fprintf_s( logfile , "%s:[-->GAME_IsItemIdPawnable<--  itemId: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , itemId , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsItemIdPowerup )( int itemId );
GAME_IsItemIdPowerup GAME_IsItemIdPoweruporg = NULL;
GAME_IsItemIdPowerup GAME_IsItemIdPowerupold = NULL;

BOOL __cdecl GAME_IsItemIdPowerupmy( int itemId )
{
	fprintf_s( logfile , "%s" , "IsItemIdPowerupmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsItemIdPowerupold( itemId );
	fprintf_s( logfile , "%s:[-->GAME_IsItemIdPowerup<--  itemId: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , itemId , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsItemIdSellable )( int itemId );
GAME_IsItemIdSellable GAME_IsItemIdSellableorg = NULL;
GAME_IsItemIdSellable GAME_IsItemIdSellableold = NULL;

BOOL __cdecl GAME_IsItemIdSellablemy( int itemId )
{
	fprintf_s( logfile , "%s" , "IsItemIdSellablemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsItemIdSellableold( itemId );
	fprintf_s( logfile , "%s:[-->GAME_IsItemIdSellable<--  itemId: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , itemId , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsItemInvulnerable )( HITEM whichItem );
GAME_IsItemInvulnerable GAME_IsItemInvulnerableorg = NULL;
GAME_IsItemInvulnerable GAME_IsItemInvulnerableold = NULL;

BOOL __cdecl GAME_IsItemInvulnerablemy( HITEM whichItem )
{
	fprintf_s( logfile , "%s" , "IsItemInvulnerablemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsItemInvulnerableold( whichItem );
	fprintf_s( logfile , "%s:[-->GAME_IsItemInvulnerable<--  whichItem: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichItem , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsItemOwned )( HITEM whichItem );
GAME_IsItemOwned GAME_IsItemOwnedorg = NULL;
GAME_IsItemOwned GAME_IsItemOwnedold = NULL;

BOOL __cdecl GAME_IsItemOwnedmy( HITEM whichItem )
{
	fprintf_s( logfile , "%s" , "IsItemOwnedmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsItemOwnedold( whichItem );
	fprintf_s( logfile , "%s:[-->GAME_IsItemOwned<--  whichItem: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichItem , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsItemPawnable )( HITEM whichItem );
GAME_IsItemPawnable GAME_IsItemPawnableorg = NULL;
GAME_IsItemPawnable GAME_IsItemPawnableold = NULL;

BOOL __cdecl GAME_IsItemPawnablemy( HITEM whichItem )
{
	fprintf_s( logfile , "%s" , "IsItemPawnablemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsItemPawnableold( whichItem );
	fprintf_s( logfile , "%s:[-->GAME_IsItemPawnable<--  whichItem: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichItem , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsItemPowerup )( HITEM whichItem );
GAME_IsItemPowerup GAME_IsItemPoweruporg = NULL;
GAME_IsItemPowerup GAME_IsItemPowerupold = NULL;

BOOL __cdecl GAME_IsItemPowerupmy( HITEM whichItem )
{
	fprintf_s( logfile , "%s" , "IsItemPowerupmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsItemPowerupold( whichItem );
	fprintf_s( logfile , "%s:[-->GAME_IsItemPowerup<--  whichItem: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichItem , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsItemSellable )( HITEM whichItem );
GAME_IsItemSellable GAME_IsItemSellableorg = NULL;
GAME_IsItemSellable GAME_IsItemSellableold = NULL;

BOOL __cdecl GAME_IsItemSellablemy( HITEM whichItem )
{
	fprintf_s( logfile , "%s" , "IsItemSellablemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsItemSellableold( whichItem );
	fprintf_s( logfile , "%s:[-->GAME_IsItemSellable<--  whichItem: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichItem , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsItemVisible )( HITEM whichItem );
GAME_IsItemVisible GAME_IsItemVisibleorg = NULL;
GAME_IsItemVisible GAME_IsItemVisibleold = NULL;

BOOL __cdecl GAME_IsItemVisiblemy( HITEM whichItem )
{
	fprintf_s( logfile , "%s" , "IsItemVisiblemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsItemVisibleold( whichItem );
	fprintf_s( logfile , "%s:[-->GAME_IsItemVisible<--  whichItem: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichItem , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsLeaderboardDisplayed )( HLEADERBOARD lb );
GAME_IsLeaderboardDisplayed GAME_IsLeaderboardDisplayedorg = NULL;
GAME_IsLeaderboardDisplayed GAME_IsLeaderboardDisplayedold = NULL;

BOOL __cdecl GAME_IsLeaderboardDisplayedmy( HLEADERBOARD lb )
{
	fprintf_s( logfile , "%s" , "IsLeaderboardDisplayedmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsLeaderboardDisplayedold( lb );
	fprintf_s( logfile , "%s:[-->GAME_IsLeaderboardDisplayed<--  lb: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , lb , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsLocationFoggedToPlayer )( HLOCATION whichLocation , HPLAYER whichPlayer );
GAME_IsLocationFoggedToPlayer GAME_IsLocationFoggedToPlayerorg = NULL;
GAME_IsLocationFoggedToPlayer GAME_IsLocationFoggedToPlayerold = NULL;

BOOL __cdecl GAME_IsLocationFoggedToPlayermy( HLOCATION whichLocation , HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "IsLocationFoggedToPlayermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsLocationFoggedToPlayerold( whichLocation , whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_IsLocationFoggedToPlayer<--  whichLocation: %X whichPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichLocation , whichPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsLocationInRegion )( HREGION whichRegion , HLOCATION whichLocation );
GAME_IsLocationInRegion GAME_IsLocationInRegionorg = NULL;
GAME_IsLocationInRegion GAME_IsLocationInRegionold = NULL;

BOOL __cdecl GAME_IsLocationInRegionmy( HREGION whichRegion , HLOCATION whichLocation )
{
	fprintf_s( logfile , "%s" , "IsLocationInRegionmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsLocationInRegionold( whichRegion , whichLocation );
	fprintf_s( logfile , "%s:[-->GAME_IsLocationInRegion<--  whichRegion: %X whichLocation: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichRegion , whichLocation , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsLocationMaskedToPlayer )( HLOCATION whichLocation , HPLAYER whichPlayer );
GAME_IsLocationMaskedToPlayer GAME_IsLocationMaskedToPlayerorg = NULL;
GAME_IsLocationMaskedToPlayer GAME_IsLocationMaskedToPlayerold = NULL;

BOOL __cdecl GAME_IsLocationMaskedToPlayermy( HLOCATION whichLocation , HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "IsLocationMaskedToPlayermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsLocationMaskedToPlayerold( whichLocation , whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_IsLocationMaskedToPlayer<--  whichLocation: %X whichPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichLocation , whichPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsLocationVisibleToPlayer )( HLOCATION whichLocation , HPLAYER whichPlayer );
GAME_IsLocationVisibleToPlayer GAME_IsLocationVisibleToPlayerorg = NULL;
GAME_IsLocationVisibleToPlayer GAME_IsLocationVisibleToPlayerold = NULL;

BOOL __cdecl GAME_IsLocationVisibleToPlayermy( HLOCATION whichLocation , HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "IsLocationVisibleToPlayermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsLocationVisibleToPlayerold( whichLocation , whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_IsLocationVisibleToPlayer<--  whichLocation: %X whichPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichLocation , whichPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsMapFlagSet )( HMAPFLAG whichMapFlag );
GAME_IsMapFlagSet GAME_IsMapFlagSetorg = NULL;
GAME_IsMapFlagSet GAME_IsMapFlagSetold = NULL;

BOOL __cdecl GAME_IsMapFlagSetmy( HMAPFLAG whichMapFlag )
{
	fprintf_s( logfile , "%s" , "IsMapFlagSetmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsMapFlagSetold( whichMapFlag );
	fprintf_s( logfile , "%s:[-->GAME_IsMapFlagSet<--  whichMapFlag: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichMapFlag , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsMaskedToPlayer )( float *x , float *y , HPLAYER whichPlayer );
GAME_IsMaskedToPlayer GAME_IsMaskedToPlayerorg = NULL;
GAME_IsMaskedToPlayer GAME_IsMaskedToPlayerold = NULL;

BOOL __cdecl GAME_IsMaskedToPlayermy( float *x , float *y , HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "IsMaskedToPlayermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsMaskedToPlayerold( x , y , whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_IsMaskedToPlayer<--  x: %f y: %f whichPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , whichPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsMultiboardDisplayed )( HMULTIBOARD lb );
GAME_IsMultiboardDisplayed GAME_IsMultiboardDisplayedorg = NULL;
GAME_IsMultiboardDisplayed GAME_IsMultiboardDisplayedold = NULL;

BOOL __cdecl GAME_IsMultiboardDisplayedmy( HMULTIBOARD lb )
{
	fprintf_s( logfile , "%s" , "IsMultiboardDisplayedmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsMultiboardDisplayedold( lb );
	fprintf_s( logfile , "%s:[-->GAME_IsMultiboardDisplayed<--  lb: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , lb , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsMultiboardMinimized )( HMULTIBOARD lb );
GAME_IsMultiboardMinimized GAME_IsMultiboardMinimizedorg = NULL;
GAME_IsMultiboardMinimized GAME_IsMultiboardMinimizedold = NULL;

BOOL __cdecl GAME_IsMultiboardMinimizedmy( HMULTIBOARD lb )
{
	fprintf_s( logfile , "%s" , "IsMultiboardMinimizedmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsMultiboardMinimizedold( lb );
	fprintf_s( logfile , "%s:[-->GAME_IsMultiboardMinimized<--  lb: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , lb , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsNoDefeatCheat )( );
GAME_IsNoDefeatCheat GAME_IsNoDefeatCheatorg = NULL;
GAME_IsNoDefeatCheat GAME_IsNoDefeatCheatold = NULL;

BOOL __cdecl GAME_IsNoDefeatCheatmy( )
{
	fprintf_s( logfile , "%s" , "IsNoDefeatCheatmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsNoDefeatCheatold( );
	fprintf_s( logfile , "%s:[-->GAME_IsNoDefeatCheat<-- ] RETURN-> %s\n" , currentDateTime( ).c_str( ) , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsNoVictoryCheat )( );
GAME_IsNoVictoryCheat GAME_IsNoVictoryCheatorg = NULL;
GAME_IsNoVictoryCheat GAME_IsNoVictoryCheatold = NULL;

BOOL __cdecl GAME_IsNoVictoryCheatmy( )
{
	fprintf_s( logfile , "%s" , "IsNoVictoryCheatmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsNoVictoryCheatold( );
	fprintf_s( logfile , "%s:[-->GAME_IsNoVictoryCheat<-- ] RETURN-> %s\n" , currentDateTime( ).c_str( ) , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsPlayerAlly )( HPLAYER whichPlayer , HPLAYER otherPlayer );
GAME_IsPlayerAlly GAME_IsPlayerAllyorg = NULL;
GAME_IsPlayerAlly GAME_IsPlayerAllyold = NULL;

BOOL __cdecl GAME_IsPlayerAllymy( HPLAYER whichPlayer , HPLAYER otherPlayer )
{
	fprintf_s( logfile , "%s" , "IsPlayerAllymy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsPlayerAllyold( whichPlayer , otherPlayer );
	fprintf_s( logfile , "%s:[-->GAME_IsPlayerAlly<--  whichPlayer: %X otherPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichPlayer , otherPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsPlayerEnemy )( HPLAYER whichPlayer , HPLAYER otherPlayer );
GAME_IsPlayerEnemy GAME_IsPlayerEnemyorg = NULL;
GAME_IsPlayerEnemy GAME_IsPlayerEnemyold = NULL;

BOOL __cdecl GAME_IsPlayerEnemymy( HPLAYER whichPlayer , HPLAYER otherPlayer )
{
	fprintf_s( logfile , "%s" , "IsPlayerEnemymy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsPlayerEnemyold( whichPlayer , otherPlayer );
	fprintf_s( logfile , "%s:[-->GAME_IsPlayerEnemy<--  whichPlayer: %X otherPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichPlayer , otherPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsPlayerInForce )( HPLAYER whichPlayer , HFORCE whichForce );
GAME_IsPlayerInForce GAME_IsPlayerInForceorg = NULL;
GAME_IsPlayerInForce GAME_IsPlayerInForceold = NULL;

BOOL __cdecl GAME_IsPlayerInForcemy( HPLAYER whichPlayer , HFORCE whichForce )
{
	fprintf_s( logfile , "%s" , "IsPlayerInForcemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsPlayerInForceold( whichPlayer , whichForce );
	fprintf_s( logfile , "%s:[-->GAME_IsPlayerInForce<--  whichPlayer: %X whichForce: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichPlayer , whichForce , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsPlayerObserver )( HPLAYER whichPlayer );
GAME_IsPlayerObserver GAME_IsPlayerObserverorg = NULL;
GAME_IsPlayerObserver GAME_IsPlayerObserverold = NULL;

BOOL __cdecl GAME_IsPlayerObservermy( HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "IsPlayerObservermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsPlayerObserverold( whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_IsPlayerObserver<--  whichPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsPlayerRacePrefSet )( HPLAYER whichPlayer , HRACEPREFERENCE pref );
GAME_IsPlayerRacePrefSet GAME_IsPlayerRacePrefSetorg = NULL;
GAME_IsPlayerRacePrefSet GAME_IsPlayerRacePrefSetold = NULL;

BOOL __cdecl GAME_IsPlayerRacePrefSetmy( HPLAYER whichPlayer , HRACEPREFERENCE pref )
{
	fprintf_s( logfile , "%s" , "IsPlayerRacePrefSetmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsPlayerRacePrefSetold( whichPlayer , pref );
	fprintf_s( logfile , "%s:[-->GAME_IsPlayerRacePrefSet<--  whichPlayer: %X pref: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichPlayer , pref , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsPointBlighted )( float *x , float *y );
GAME_IsPointBlighted GAME_IsPointBlightedorg = NULL;
GAME_IsPointBlighted GAME_IsPointBlightedold = NULL;

BOOL __cdecl GAME_IsPointBlightedmy( float *x , float *y )
{
	fprintf_s( logfile , "%s" , "IsPointBlightedmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsPointBlightedold( x , y );
	fprintf_s( logfile , "%s:[-->GAME_IsPointBlighted<--  x: %f y: %f] RETURN-> %s\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsPointInRegion )( HREGION whichRegion , float *x , float *y );
GAME_IsPointInRegion GAME_IsPointInRegionorg = NULL;
GAME_IsPointInRegion GAME_IsPointInRegionold = NULL;

BOOL __cdecl GAME_IsPointInRegionmy( HREGION whichRegion , float *x , float *y )
{
	fprintf_s( logfile , "%s" , "IsPointInRegionmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsPointInRegionold( whichRegion , x , y );
	fprintf_s( logfile , "%s:[-->GAME_IsPointInRegion<--  whichRegion: %X x: %f y: %f] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichRegion , *( float * ) x , *( float * ) y , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsQuestCompleted )( HQUEST whichQuest );
GAME_IsQuestCompleted GAME_IsQuestCompletedorg = NULL;
GAME_IsQuestCompleted GAME_IsQuestCompletedold = NULL;

BOOL __cdecl GAME_IsQuestCompletedmy( HQUEST whichQuest )
{
	fprintf_s( logfile , "%s" , "IsQuestCompletedmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsQuestCompletedold( whichQuest );
	fprintf_s( logfile , "%s:[-->GAME_IsQuestCompleted<--  whichQuest: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichQuest , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsQuestDiscovered )( HQUEST whichQuest );
GAME_IsQuestDiscovered GAME_IsQuestDiscoveredorg = NULL;
GAME_IsQuestDiscovered GAME_IsQuestDiscoveredold = NULL;

BOOL __cdecl GAME_IsQuestDiscoveredmy( HQUEST whichQuest )
{
	fprintf_s( logfile , "%s" , "IsQuestDiscoveredmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsQuestDiscoveredold( whichQuest );
	fprintf_s( logfile , "%s:[-->GAME_IsQuestDiscovered<--  whichQuest: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichQuest , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsQuestEnabled )( HQUEST whichQuest );
GAME_IsQuestEnabled GAME_IsQuestEnabledorg = NULL;
GAME_IsQuestEnabled GAME_IsQuestEnabledold = NULL;

BOOL __cdecl GAME_IsQuestEnabledmy( HQUEST whichQuest )
{
	fprintf_s( logfile , "%s" , "IsQuestEnabledmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsQuestEnabledold( whichQuest );
	fprintf_s( logfile , "%s:[-->GAME_IsQuestEnabled<--  whichQuest: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichQuest , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsQuestFailed )( HQUEST whichQuest );
GAME_IsQuestFailed GAME_IsQuestFailedorg = NULL;
GAME_IsQuestFailed GAME_IsQuestFailedold = NULL;

BOOL __cdecl GAME_IsQuestFailedmy( HQUEST whichQuest )
{
	fprintf_s( logfile , "%s" , "IsQuestFailedmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsQuestFailedold( whichQuest );
	fprintf_s( logfile , "%s:[-->GAME_IsQuestFailed<--  whichQuest: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichQuest , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsQuestItemCompleted )( HQUESTITEM whichQuestItem );
GAME_IsQuestItemCompleted GAME_IsQuestItemCompletedorg = NULL;
GAME_IsQuestItemCompleted GAME_IsQuestItemCompletedold = NULL;

BOOL __cdecl GAME_IsQuestItemCompletedmy( HQUESTITEM whichQuestItem )
{
	fprintf_s( logfile , "%s" , "IsQuestItemCompletedmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsQuestItemCompletedold( whichQuestItem );
	fprintf_s( logfile , "%s:[-->GAME_IsQuestItemCompleted<--  whichQuestItem: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichQuestItem , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsQuestRequired )( HQUEST whichQuest );
GAME_IsQuestRequired GAME_IsQuestRequiredorg = NULL;
GAME_IsQuestRequired GAME_IsQuestRequiredold = NULL;

BOOL __cdecl GAME_IsQuestRequiredmy( HQUEST whichQuest )
{
	fprintf_s( logfile , "%s" , "IsQuestRequiredmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsQuestRequiredold( whichQuest );
	fprintf_s( logfile , "%s:[-->GAME_IsQuestRequired<--  whichQuest: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichQuest , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsSuspendedXP )( HUNIT whichHero );
GAME_IsSuspendedXP GAME_IsSuspendedXPorg = NULL;
GAME_IsSuspendedXP GAME_IsSuspendedXPold = NULL;

BOOL __cdecl GAME_IsSuspendedXPmy( HUNIT whichHero )
{
	fprintf_s( logfile , "%s" , "IsSuspendedXPmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsSuspendedXPold( whichHero );
	fprintf_s( logfile , "%s:[-->GAME_IsSuspendedXP<--  whichHero: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichHero , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsTerrainPathable )( float *x , float *y , HPATHINGTYPE t );
GAME_IsTerrainPathable GAME_IsTerrainPathableorg = NULL;
GAME_IsTerrainPathable GAME_IsTerrainPathableold = NULL;

BOOL __cdecl GAME_IsTerrainPathablemy( float *x , float *y , HPATHINGTYPE t )
{
	fprintf_s( logfile , "%s" , "IsTerrainPathablemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsTerrainPathableold( x , y , t );
	fprintf_s( logfile , "%s:[-->GAME_IsTerrainPathable<--  x: %f y: %f t: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , t , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsTimerDialogDisplayed )( HTIMERDIALOG whichDialog );
GAME_IsTimerDialogDisplayed GAME_IsTimerDialogDisplayedorg = NULL;
GAME_IsTimerDialogDisplayed GAME_IsTimerDialogDisplayedold = NULL;

BOOL __cdecl GAME_IsTimerDialogDisplayedmy( HTIMERDIALOG whichDialog )
{
	fprintf_s( logfile , "%s" , "IsTimerDialogDisplayedmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsTimerDialogDisplayedold( whichDialog );
	fprintf_s( logfile , "%s:[-->GAME_IsTimerDialogDisplayed<--  whichDialog: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichDialog , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsTowered )( HUNIT arg1 );
GAME_IsTowered GAME_IsToweredorg = NULL;
GAME_IsTowered GAME_IsToweredold = NULL;

BOOL __cdecl GAME_IsToweredmy( HUNIT arg1 )
{
	fprintf_s( logfile , "%s" , "IsToweredmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsToweredold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_IsTowered<--  arg1: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , arg1 , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsTriggerEnabled )( HTRIGGER whichTrigger );
GAME_IsTriggerEnabled GAME_IsTriggerEnabledorg = NULL;
GAME_IsTriggerEnabled GAME_IsTriggerEnabledold = NULL;

BOOL __cdecl GAME_IsTriggerEnabledmy( HTRIGGER whichTrigger )
{
	fprintf_s( logfile , "%s" , "IsTriggerEnabledmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsTriggerEnabledold( whichTrigger );
	fprintf_s( logfile , "%s:[-->GAME_IsTriggerEnabled<--  whichTrigger: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichTrigger , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsTriggerWaitOnSleeps )( HTRIGGER whichTrigger );
GAME_IsTriggerWaitOnSleeps GAME_IsTriggerWaitOnSleepsorg = NULL;
GAME_IsTriggerWaitOnSleeps GAME_IsTriggerWaitOnSleepsold = NULL;

BOOL __cdecl GAME_IsTriggerWaitOnSleepsmy( HTRIGGER whichTrigger )
{
	fprintf_s( logfile , "%s" , "IsTriggerWaitOnSleepsmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsTriggerWaitOnSleepsold( whichTrigger );
	fprintf_s( logfile , "%s:[-->GAME_IsTriggerWaitOnSleeps<--  whichTrigger: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichTrigger , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnit )( HUNIT whichUnit , HUNIT whichSpecifiedUnit );
GAME_IsUnit GAME_IsUnitorg = NULL;
GAME_IsUnit GAME_IsUnitold = NULL;

BOOL __cdecl GAME_IsUnitmy( HUNIT whichUnit , HUNIT whichSpecifiedUnit )
{
	fprintf_s( logfile , "%s" , "IsUnitmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitold( whichUnit , whichSpecifiedUnit );
	fprintf_s( logfile , "%s:[-->GAME_IsUnit<--  whichUnit: %X whichSpecifiedUnit: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichSpecifiedUnit , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitAlly )( HUNIT whichUnit , HPLAYER whichPlayer );
GAME_IsUnitAlly GAME_IsUnitAllyorg = NULL;
GAME_IsUnitAlly GAME_IsUnitAllyold = NULL;

BOOL __cdecl GAME_IsUnitAllymy( HUNIT whichUnit , HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "IsUnitAllymy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitAllyold( whichUnit , whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitAlly<--  whichUnit: %X whichPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitDetected )( HUNIT whichUnit , HPLAYER whichPlayer );
GAME_IsUnitDetected GAME_IsUnitDetectedorg = NULL;
GAME_IsUnitDetected GAME_IsUnitDetectedold = NULL;

BOOL __cdecl GAME_IsUnitDetectedmy( HUNIT whichUnit , HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "IsUnitDetectedmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitDetectedold( whichUnit , whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitDetected<--  whichUnit: %X whichPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitEnemy )( HUNIT whichUnit , HPLAYER whichPlayer );
GAME_IsUnitEnemy GAME_IsUnitEnemyorg = NULL;
GAME_IsUnitEnemy GAME_IsUnitEnemyold = NULL;

BOOL __cdecl GAME_IsUnitEnemymy( HUNIT whichUnit , HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "IsUnitEnemymy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitEnemyold( whichUnit , whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitEnemy<--  whichUnit: %X whichPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitFogged )( HUNIT whichUnit , HPLAYER whichPlayer );
GAME_IsUnitFogged GAME_IsUnitFoggedorg = NULL;
GAME_IsUnitFogged GAME_IsUnitFoggedold = NULL;

BOOL __cdecl GAME_IsUnitFoggedmy( HUNIT whichUnit , HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "IsUnitFoggedmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitFoggedold( whichUnit , whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitFogged<--  whichUnit: %X whichPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitHidden )( HUNIT whichUnit );
GAME_IsUnitHidden GAME_IsUnitHiddenorg = NULL;
GAME_IsUnitHidden GAME_IsUnitHiddenold = NULL;

BOOL __cdecl GAME_IsUnitHiddenmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s" , "IsUnitHiddenmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitHiddenold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitHidden<--  whichUnit: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitIdType )( int unitId , HUNITTYPE whichUnitType );
GAME_IsUnitIdType GAME_IsUnitIdTypeorg = NULL;
GAME_IsUnitIdType GAME_IsUnitIdTypeold = NULL;

BOOL __cdecl GAME_IsUnitIdTypemy( int unitId , HUNITTYPE whichUnitType )
{
	fprintf_s( logfile , "%s" , "IsUnitIdTypemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitIdTypeold( unitId , whichUnitType );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitIdType<--  unitId: %i whichUnitType: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , unitId , whichUnitType , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitIllusion )( HUNIT whichUnit );
GAME_IsUnitIllusion GAME_IsUnitIllusionorg = NULL;
GAME_IsUnitIllusion GAME_IsUnitIllusionold = NULL;

BOOL __cdecl GAME_IsUnitIllusionmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s" , "IsUnitIllusionmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitIllusionold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitIllusion<--  whichUnit: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitInForce )( HUNIT whichUnit , HFORCE whichForce );
GAME_IsUnitInForce GAME_IsUnitInForceorg = NULL;
GAME_IsUnitInForce GAME_IsUnitInForceold = NULL;

BOOL __cdecl GAME_IsUnitInForcemy( HUNIT whichUnit , HFORCE whichForce )
{
	fprintf_s( logfile , "%s" , "IsUnitInForcemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitInForceold( whichUnit , whichForce );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitInForce<--  whichUnit: %X whichForce: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichForce , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitInGroup )( HUNIT whichUnit , HGROUP whichGroup );
GAME_IsUnitInGroup GAME_IsUnitInGrouporg = NULL;
GAME_IsUnitInGroup GAME_IsUnitInGroupold = NULL;

BOOL __cdecl GAME_IsUnitInGroupmy( HUNIT whichUnit , HGROUP whichGroup )
{
	fprintf_s( logfile , "%s" , "IsUnitInGroupmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitInGroupold( whichUnit , whichGroup );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitInGroup<--  whichUnit: %X whichGroup: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichGroup , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitInRange )( HUNIT whichUnit , HUNIT otherUnit , float *distance );
GAME_IsUnitInRange GAME_IsUnitInRangeorg = NULL;
GAME_IsUnitInRange GAME_IsUnitInRangeold = NULL;

BOOL __cdecl GAME_IsUnitInRangemy( HUNIT whichUnit , HUNIT otherUnit , float *distance )
{
	fprintf_s( logfile , "%s" , "IsUnitInRangemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitInRangeold( whichUnit , otherUnit , distance );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitInRange<--  whichUnit: %X otherUnit: %X distance: %f] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , otherUnit , *( float * ) distance , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitInRangeLoc )( HUNIT whichUnit , HLOCATION whichLocation , float *distance );
GAME_IsUnitInRangeLoc GAME_IsUnitInRangeLocorg = NULL;
GAME_IsUnitInRangeLoc GAME_IsUnitInRangeLocold = NULL;

BOOL __cdecl GAME_IsUnitInRangeLocmy( HUNIT whichUnit , HLOCATION whichLocation , float *distance )
{
	fprintf_s( logfile , "%s" , "IsUnitInRangeLocmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitInRangeLocold( whichUnit , whichLocation , distance );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitInRangeLoc<--  whichUnit: %X whichLocation: %X distance: %f] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichLocation , *( float * ) distance , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitInRangeXY )( HUNIT whichUnit , float *x , float *y , float *distance );
GAME_IsUnitInRangeXY GAME_IsUnitInRangeXYorg = NULL;
GAME_IsUnitInRangeXY GAME_IsUnitInRangeXYold = NULL;

BOOL __cdecl GAME_IsUnitInRangeXYmy( HUNIT whichUnit , float *x , float *y , float *distance )
{
	fprintf_s( logfile , "%s" , "IsUnitInRangeXYmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitInRangeXYold( whichUnit , x , y , distance );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitInRangeXY<--  whichUnit: %X x: %f y: %f distance: %f] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , *( float * ) x , *( float * ) y , *( float * ) distance , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitInRegion )( HREGION whichRegion , HUNIT whichUnit );
GAME_IsUnitInRegion GAME_IsUnitInRegionorg = NULL;
GAME_IsUnitInRegion GAME_IsUnitInRegionold = NULL;

BOOL __cdecl GAME_IsUnitInRegionmy( HREGION whichRegion , HUNIT whichUnit )
{
	fprintf_s( logfile , "%s" , "IsUnitInRegionmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitInRegionold( whichRegion , whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitInRegion<--  whichRegion: %X whichUnit: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichRegion , whichUnit , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitInTransport )( HUNIT whichUnit , HUNIT whichTransport );
GAME_IsUnitInTransport GAME_IsUnitInTransportorg = NULL;
GAME_IsUnitInTransport GAME_IsUnitInTransportold = NULL;

BOOL __cdecl GAME_IsUnitInTransportmy( HUNIT whichUnit , HUNIT whichTransport )
{
	fprintf_s( logfile , "%s" , "IsUnitInTransportmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitInTransportold( whichUnit , whichTransport );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitInTransport<--  whichUnit: %X whichTransport: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichTransport , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitInvisible )( HUNIT whichUnit , HPLAYER whichPlayer );
GAME_IsUnitInvisible GAME_IsUnitInvisibleorg = NULL;
GAME_IsUnitInvisible GAME_IsUnitInvisibleold = NULL;

BOOL __cdecl GAME_IsUnitInvisiblemy( HUNIT whichUnit , HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "IsUnitInvisiblemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitInvisibleold( whichUnit , whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitInvisible<--  whichUnit: %X whichPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitLoaded )( HUNIT whichUnit );
GAME_IsUnitLoaded GAME_IsUnitLoadedorg = NULL;
GAME_IsUnitLoaded GAME_IsUnitLoadedold = NULL;

BOOL __cdecl GAME_IsUnitLoadedmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s" , "IsUnitLoadedmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitLoadedold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitLoaded<--  whichUnit: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitMasked )( HUNIT whichUnit , HPLAYER whichPlayer );
GAME_IsUnitMasked GAME_IsUnitMaskedorg = NULL;
GAME_IsUnitMasked GAME_IsUnitMaskedold = NULL;

BOOL __cdecl GAME_IsUnitMaskedmy( HUNIT whichUnit , HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "IsUnitMaskedmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitMaskedold( whichUnit , whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitMasked<--  whichUnit: %X whichPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitOwnedByPlayer )( HUNIT whichUnit , HPLAYER whichPlayer );
GAME_IsUnitOwnedByPlayer GAME_IsUnitOwnedByPlayerorg = NULL;
GAME_IsUnitOwnedByPlayer GAME_IsUnitOwnedByPlayerold = NULL;

BOOL __cdecl GAME_IsUnitOwnedByPlayermy( HUNIT whichUnit , HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "IsUnitOwnedByPlayermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitOwnedByPlayerold( whichUnit , whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitOwnedByPlayer<--  whichUnit: %X whichPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitPaused )( HUNIT whichHero );
GAME_IsUnitPaused GAME_IsUnitPausedorg = NULL;
GAME_IsUnitPaused GAME_IsUnitPausedold = NULL;

BOOL __cdecl GAME_IsUnitPausedmy( HUNIT whichHero )
{
	fprintf_s( logfile , "%s" , "IsUnitPausedmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitPausedold( whichHero );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitPaused<--  whichHero: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichHero , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitRace )( HUNIT whichUnit , HRACE whichRace );
GAME_IsUnitRace GAME_IsUnitRaceorg = NULL;
GAME_IsUnitRace GAME_IsUnitRaceold = NULL;

BOOL __cdecl GAME_IsUnitRacemy( HUNIT whichUnit , HRACE whichRace )
{
	fprintf_s( logfile , "%s" , "IsUnitRacemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitRaceold( whichUnit , whichRace );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitRace<--  whichUnit: %X whichRace: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichRace , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitSelected )( HUNIT whichUnit , HPLAYER whichPlayer );
GAME_IsUnitSelected GAME_IsUnitSelectedorg = NULL;
GAME_IsUnitSelected GAME_IsUnitSelectedold = NULL;

BOOL __cdecl GAME_IsUnitSelectedmy( HUNIT whichUnit , HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "IsUnitSelectedmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitSelectedold( whichUnit , whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitSelected<--  whichUnit: %X whichPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitType )( HUNIT whichUnit , HUNITTYPE whichUnitType );
GAME_IsUnitType GAME_IsUnitTypeorg = NULL;
GAME_IsUnitType GAME_IsUnitTypeold = NULL;

BOOL __cdecl GAME_IsUnitTypemy( HUNIT whichUnit , HUNITTYPE whichUnitType )
{
	fprintf_s( logfile , "%s" , "IsUnitTypemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitTypeold( whichUnit , whichUnitType );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitType<--  whichUnit: %X whichUnitType: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichUnitType , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsUnitVisible )( HUNIT whichUnit , HPLAYER whichPlayer );
GAME_IsUnitVisible GAME_IsUnitVisibleorg = NULL;
GAME_IsUnitVisible GAME_IsUnitVisibleold = NULL;

BOOL __cdecl GAME_IsUnitVisiblemy( HUNIT whichUnit , HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "IsUnitVisiblemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsUnitVisibleold( whichUnit , whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_IsUnitVisible<--  whichUnit: %X whichPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IsVisibleToPlayer )( float *x , float *y , HPLAYER whichPlayer );
GAME_IsVisibleToPlayer GAME_IsVisibleToPlayerorg = NULL;
GAME_IsVisibleToPlayer GAME_IsVisibleToPlayerold = NULL;

BOOL __cdecl GAME_IsVisibleToPlayermy( float *x , float *y , HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "IsVisibleToPlayermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IsVisibleToPlayerold( x , y , whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_IsVisibleToPlayer<--  x: %f y: %f whichPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , whichPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssueBuildOrder )( HUNIT whichPeon , void * unitToBuild , float *x , float *y );
GAME_IssueBuildOrder GAME_IssueBuildOrderorg = NULL;
GAME_IssueBuildOrder GAME_IssueBuildOrderold = NULL;

BOOL __cdecl GAME_IssueBuildOrdermy( HUNIT whichPeon , void * unitToBuild , float *x , float *y )
{
	fprintf_s( logfile , "%s" , "IssueBuildOrdermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssueBuildOrderold( whichPeon , unitToBuild , x , y );
	fprintf_s( logfile , "%s:[-->GAME_IssueBuildOrder<--  whichPeon: %X unitToBuild: \"%s\" x: %f y: %f] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichPeon , jassgetchar( unitToBuild ) , *( float * ) x , *( float * ) y , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssueBuildOrderById )( HUNIT whichPeon , int unitId , float *x , float *y );
GAME_IssueBuildOrderById GAME_IssueBuildOrderByIdorg = NULL;
GAME_IssueBuildOrderById GAME_IssueBuildOrderByIdold = NULL;

BOOL __cdecl GAME_IssueBuildOrderByIdmy( HUNIT whichPeon , int unitId , float *x , float *y )
{
	fprintf_s( logfile , "%s" , "IssueBuildOrderByIdmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssueBuildOrderByIdold( whichPeon , unitId , x , y );
	fprintf_s( logfile , "%s:[-->GAME_IssueBuildOrderById<--  whichPeon: %X unitId: %i x: %f y: %f] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichPeon , unitId , *( float * ) x , *( float * ) y , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssueImmediateOrder )( HUNIT whichUnit , void * order );
GAME_IssueImmediateOrder GAME_IssueImmediateOrderorg = NULL;
GAME_IssueImmediateOrder GAME_IssueImmediateOrderold = NULL;

BOOL __cdecl GAME_IssueImmediateOrdermy( HUNIT whichUnit , void * order )
{
	fprintf_s( logfile , "%s" , "IssueImmediateOrdermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssueImmediateOrderold( whichUnit , order );
	fprintf_s( logfile , "%s:[-->GAME_IssueImmediateOrder<--  whichUnit: %X order: \"%s\"] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , jassgetchar( order ) , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssueImmediateOrderById )( HUNIT whichUnit , int order );
GAME_IssueImmediateOrderById GAME_IssueImmediateOrderByIdorg = NULL;
GAME_IssueImmediateOrderById GAME_IssueImmediateOrderByIdold = NULL;

BOOL __cdecl GAME_IssueImmediateOrderByIdmy( HUNIT whichUnit , int order )
{
	fprintf_s( logfile , "%s" , "IssueImmediateOrderByIdmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssueImmediateOrderByIdold( whichUnit , order );
	fprintf_s( logfile , "%s:[-->GAME_IssueImmediateOrderById<--  whichUnit: %X order: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , order , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssueInstantPointOrder )( HUNIT whichUnit , void * order , float *x , float *y , HWIDGET instantTargetWidget );
GAME_IssueInstantPointOrder GAME_IssueInstantPointOrderorg = NULL;
GAME_IssueInstantPointOrder GAME_IssueInstantPointOrderold = NULL;

BOOL __cdecl GAME_IssueInstantPointOrdermy( HUNIT whichUnit , void * order , float *x , float *y , HWIDGET instantTargetWidget )
{
	fprintf_s( logfile , "%s" , "IssueInstantPointOrdermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssueInstantPointOrderold( whichUnit , order , x , y , instantTargetWidget );
	fprintf_s( logfile , "%s:[-->GAME_IssueInstantPointOrder<--  whichUnit: %X order: \"%s\" x: %f y: %f instantTargetWidget: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , jassgetchar( order ) , *( float * ) x , *( float * ) y , instantTargetWidget , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssueInstantPointOrderById )( HUNIT whichUnit , int order , float *x , float *y , HWIDGET instantTargetWidget );
GAME_IssueInstantPointOrderById GAME_IssueInstantPointOrderByIdorg = NULL;
GAME_IssueInstantPointOrderById GAME_IssueInstantPointOrderByIdold = NULL;

BOOL __cdecl GAME_IssueInstantPointOrderByIdmy( HUNIT whichUnit , int order , float *x , float *y , HWIDGET instantTargetWidget )
{
	fprintf_s( logfile , "%s" , "IssueInstantPointOrderByIdmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssueInstantPointOrderByIdold( whichUnit , order , x , y , instantTargetWidget );
	fprintf_s( logfile , "%s:[-->GAME_IssueInstantPointOrderById<--  whichUnit: %X order: %i x: %f y: %f instantTargetWidget: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , order , *( float * ) x , *( float * ) y , instantTargetWidget , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssueInstantTargetOrder )( HUNIT whichUnit , void * order , HWIDGET targetWidget , HWIDGET instantTargetWidget );
GAME_IssueInstantTargetOrder GAME_IssueInstantTargetOrderorg = NULL;
GAME_IssueInstantTargetOrder GAME_IssueInstantTargetOrderold = NULL;

BOOL __cdecl GAME_IssueInstantTargetOrdermy( HUNIT whichUnit , void * order , HWIDGET targetWidget , HWIDGET instantTargetWidget )
{
	fprintf_s( logfile , "%s" , "IssueInstantTargetOrdermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssueInstantTargetOrderold( whichUnit , order , targetWidget , instantTargetWidget );
	fprintf_s( logfile , "%s:[-->GAME_IssueInstantTargetOrder<--  whichUnit: %X order: \"%s\" targetWidget: %X instantTargetWidget: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , jassgetchar( order ) , targetWidget , instantTargetWidget , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssueInstantTargetOrderById )( HUNIT whichUnit , int order , HWIDGET targetWidget , HWIDGET instantTargetWidget );
GAME_IssueInstantTargetOrderById GAME_IssueInstantTargetOrderByIdorg = NULL;
GAME_IssueInstantTargetOrderById GAME_IssueInstantTargetOrderByIdold = NULL;

BOOL __cdecl GAME_IssueInstantTargetOrderByIdmy( HUNIT whichUnit , int order , HWIDGET targetWidget , HWIDGET instantTargetWidget )
{
	fprintf_s( logfile , "%s" , "IssueInstantTargetOrderByIdmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssueInstantTargetOrderByIdold( whichUnit , order , targetWidget , instantTargetWidget );
	fprintf_s( logfile , "%s:[-->GAME_IssueInstantTargetOrderById<--  whichUnit: %X order: %i targetWidget: %X instantTargetWidget: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , order , targetWidget , instantTargetWidget , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssueNeutralImmediateOrder )( HPLAYER forWhichPlayer , HUNIT neutralStructure , void * unitToBuild );
GAME_IssueNeutralImmediateOrder GAME_IssueNeutralImmediateOrderorg = NULL;
GAME_IssueNeutralImmediateOrder GAME_IssueNeutralImmediateOrderold = NULL;

BOOL __cdecl GAME_IssueNeutralImmediateOrdermy( HPLAYER forWhichPlayer , HUNIT neutralStructure , void * unitToBuild )
{
	fprintf_s( logfile , "%s" , "IssueNeutralImmediateOrdermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssueNeutralImmediateOrderold( forWhichPlayer , neutralStructure , unitToBuild );
	fprintf_s( logfile , "%s:[-->GAME_IssueNeutralImmediateOrder<--  forWhichPlayer: %X neutralStructure: %X unitToBuild: \"%s\"] RETURN-> %s\n" , currentDateTime( ).c_str( ) , forWhichPlayer , neutralStructure , jassgetchar( unitToBuild ) , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssueNeutralImmediateOrderById )( HPLAYER forWhichPlayer , HUNIT neutralStructure , int unitId );
GAME_IssueNeutralImmediateOrderById GAME_IssueNeutralImmediateOrderByIdorg = NULL;
GAME_IssueNeutralImmediateOrderById GAME_IssueNeutralImmediateOrderByIdold = NULL;

BOOL __cdecl GAME_IssueNeutralImmediateOrderByIdmy( HPLAYER forWhichPlayer , HUNIT neutralStructure , int unitId )
{
	fprintf_s( logfile , "%s" , "IssueNeutralImmediateOrderByIdmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssueNeutralImmediateOrderByIdold( forWhichPlayer , neutralStructure , unitId );
	fprintf_s( logfile , "%s:[-->GAME_IssueNeutralImmediateOrderById<--  forWhichPlayer: %X neutralStructure: %X unitId: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , forWhichPlayer , neutralStructure , unitId , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssueNeutralPointOrder )( HPLAYER forWhichPlayer , HUNIT neutralStructure , void * unitToBuild , float *x , float *y );
GAME_IssueNeutralPointOrder GAME_IssueNeutralPointOrderorg = NULL;
GAME_IssueNeutralPointOrder GAME_IssueNeutralPointOrderold = NULL;

BOOL __cdecl GAME_IssueNeutralPointOrdermy( HPLAYER forWhichPlayer , HUNIT neutralStructure , void * unitToBuild , float *x , float *y )
{
	fprintf_s( logfile , "%s" , "IssueNeutralPointOrdermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssueNeutralPointOrderold( forWhichPlayer , neutralStructure , unitToBuild , x , y );
	fprintf_s( logfile , "%s:[-->GAME_IssueNeutralPointOrder<--  forWhichPlayer: %X neutralStructure: %X unitToBuild: \"%s\" x: %f y: %f] RETURN-> %s\n" , currentDateTime( ).c_str( ) , forWhichPlayer , neutralStructure , jassgetchar( unitToBuild ) , *( float * ) x , *( float * ) y , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssueNeutralPointOrderById )( HPLAYER forWhichPlayer , HUNIT neutralStructure , int unitId , float *x , float *y );
GAME_IssueNeutralPointOrderById GAME_IssueNeutralPointOrderByIdorg = NULL;
GAME_IssueNeutralPointOrderById GAME_IssueNeutralPointOrderByIdold = NULL;

BOOL __cdecl GAME_IssueNeutralPointOrderByIdmy( HPLAYER forWhichPlayer , HUNIT neutralStructure , int unitId , float *x , float *y )
{
	fprintf_s( logfile , "%s" , "IssueNeutralPointOrderByIdmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssueNeutralPointOrderByIdold( forWhichPlayer , neutralStructure , unitId , x , y );
	fprintf_s( logfile , "%s:[-->GAME_IssueNeutralPointOrderById<--  forWhichPlayer: %X neutralStructure: %X unitId: %i x: %f y: %f] RETURN-> %s\n" , currentDateTime( ).c_str( ) , forWhichPlayer , neutralStructure , unitId , *( float * ) x , *( float * ) y , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssueNeutralTargetOrder )( HPLAYER forWhichPlayer , HUNIT neutralStructure , void * unitToBuild , HWIDGET target );
GAME_IssueNeutralTargetOrder GAME_IssueNeutralTargetOrderorg = NULL;
GAME_IssueNeutralTargetOrder GAME_IssueNeutralTargetOrderold = NULL;

BOOL __cdecl GAME_IssueNeutralTargetOrdermy( HPLAYER forWhichPlayer , HUNIT neutralStructure , void * unitToBuild , HWIDGET target )
{
	fprintf_s( logfile , "%s" , "IssueNeutralTargetOrdermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssueNeutralTargetOrderold( forWhichPlayer , neutralStructure , unitToBuild , target );
	fprintf_s( logfile , "%s:[-->GAME_IssueNeutralTargetOrder<--  forWhichPlayer: %X neutralStructure: %X unitToBuild: \"%s\" target: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , forWhichPlayer , neutralStructure , jassgetchar( unitToBuild ) , target , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssueNeutralTargetOrderById )( HPLAYER forWhichPlayer , HUNIT neutralStructure , int unitId , HWIDGET target );
GAME_IssueNeutralTargetOrderById GAME_IssueNeutralTargetOrderByIdorg = NULL;
GAME_IssueNeutralTargetOrderById GAME_IssueNeutralTargetOrderByIdold = NULL;

BOOL __cdecl GAME_IssueNeutralTargetOrderByIdmy( HPLAYER forWhichPlayer , HUNIT neutralStructure , int unitId , HWIDGET target )
{
	fprintf_s( logfile , "%s" , "IssueNeutralTargetOrderByIdmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssueNeutralTargetOrderByIdold( forWhichPlayer , neutralStructure , unitId , target );
	fprintf_s( logfile , "%s:[-->GAME_IssueNeutralTargetOrderById<--  forWhichPlayer: %X neutralStructure: %X unitId: %i target: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , forWhichPlayer , neutralStructure , unitId , target , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssuePointOrder )( HUNIT whichUnit , void * order , float *x , float *y );
GAME_IssuePointOrder GAME_IssuePointOrderorg = NULL;
GAME_IssuePointOrder GAME_IssuePointOrderold = NULL;

BOOL __cdecl GAME_IssuePointOrdermy( HUNIT whichUnit , void * order , float *x , float *y )
{
	fprintf_s( logfile , "%s" , "IssuePointOrdermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssuePointOrderold( whichUnit , order , x , y );
	fprintf_s( logfile , "%s:[-->GAME_IssuePointOrder<--  whichUnit: %X order: \"%s\" x: %f y: %f] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , jassgetchar( order ) , *( float * ) x , *( float * ) y , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssuePointOrderById )( HUNIT whichUnit , int order , float *x , float *y );
GAME_IssuePointOrderById GAME_IssuePointOrderByIdorg = NULL;
GAME_IssuePointOrderById GAME_IssuePointOrderByIdold = NULL;

BOOL __cdecl GAME_IssuePointOrderByIdmy( HUNIT whichUnit , int order , float *x , float *y )
{
	fprintf_s( logfile , "%s" , "IssuePointOrderByIdmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssuePointOrderByIdold( whichUnit , order , x , y );
	fprintf_s( logfile , "%s:[-->GAME_IssuePointOrderById<--  whichUnit: %X order: %i x: %f y: %f] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , order , *( float * ) x , *( float * ) y , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssuePointOrderByIdLoc )( HUNIT whichUnit , int order , HLOCATION whichLocation );
GAME_IssuePointOrderByIdLoc GAME_IssuePointOrderByIdLocorg = NULL;
GAME_IssuePointOrderByIdLoc GAME_IssuePointOrderByIdLocold = NULL;

BOOL __cdecl GAME_IssuePointOrderByIdLocmy( HUNIT whichUnit , int order , HLOCATION whichLocation )
{
	fprintf_s( logfile , "%s" , "IssuePointOrderByIdLocmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssuePointOrderByIdLocold( whichUnit , order , whichLocation );
	fprintf_s( logfile , "%s:[-->GAME_IssuePointOrderByIdLoc<--  whichUnit: %X order: %i whichLocation: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , order , whichLocation , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssuePointOrderLoc )( HUNIT whichUnit , void * order , HLOCATION whichLocation );
GAME_IssuePointOrderLoc GAME_IssuePointOrderLocorg = NULL;
GAME_IssuePointOrderLoc GAME_IssuePointOrderLocold = NULL;

BOOL __cdecl GAME_IssuePointOrderLocmy( HUNIT whichUnit , void * order , HLOCATION whichLocation )
{
	fprintf_s( logfile , "%s" , "IssuePointOrderLocmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssuePointOrderLocold( whichUnit , order , whichLocation );
	fprintf_s( logfile , "%s:[-->GAME_IssuePointOrderLoc<--  whichUnit: %X order: \"%s\" whichLocation: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , jassgetchar( order ) , whichLocation , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssueTargetOrder )( HUNIT whichUnit , void * order , HWIDGET targetWidget );
GAME_IssueTargetOrder GAME_IssueTargetOrderorg = NULL;
GAME_IssueTargetOrder GAME_IssueTargetOrderold = NULL;

BOOL __cdecl GAME_IssueTargetOrdermy( HUNIT whichUnit , void * order , HWIDGET targetWidget )
{
	fprintf_s( logfile , "%s" , "IssueTargetOrdermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssueTargetOrderold( whichUnit , order , targetWidget );
	fprintf_s( logfile , "%s:[-->GAME_IssueTargetOrder<--  whichUnit: %X order: \"%s\" targetWidget: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , jassgetchar( order ) , targetWidget , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_IssueTargetOrderById )( HUNIT whichUnit , int order , HWIDGET targetWidget );
GAME_IssueTargetOrderById GAME_IssueTargetOrderByIdorg = NULL;
GAME_IssueTargetOrderById GAME_IssueTargetOrderByIdold = NULL;

BOOL __cdecl GAME_IssueTargetOrderByIdmy( HUNIT whichUnit , int order , HWIDGET targetWidget )
{
	fprintf_s( logfile , "%s" , "IssueTargetOrderByIdmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_IssueTargetOrderByIdold( whichUnit , order , targetWidget );
	fprintf_s( logfile , "%s:[-->GAME_IssueTargetOrderById<--  whichUnit: %X order: %i targetWidget: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , order , targetWidget , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_ItemPoolAddItemType )( HITEMPOOL whichItemPool , int itemId , float *weight );
GAME_ItemPoolAddItemType GAME_ItemPoolAddItemTypeorg = NULL;
GAME_ItemPoolAddItemType GAME_ItemPoolAddItemTypeold = NULL;

void __cdecl GAME_ItemPoolAddItemTypemy( HITEMPOOL whichItemPool , int itemId , float *weight )
{
	fprintf_s( logfile , "%s" , "ItemPoolAddItemTypemy\n" );
	fflush( logfile );

	GAME_ItemPoolAddItemTypeold( whichItemPool , itemId , weight );
	fprintf_s( logfile , "%s:[-->GAME_ItemPoolAddItemType<--  whichItemPool: %X itemId: %i weight: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichItemPool , itemId , *( float * ) weight );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ItemPoolRemoveItemType )( HITEMPOOL whichItemPool , int itemId );
GAME_ItemPoolRemoveItemType GAME_ItemPoolRemoveItemTypeorg = NULL;
GAME_ItemPoolRemoveItemType GAME_ItemPoolRemoveItemTypeold = NULL;

void __cdecl GAME_ItemPoolRemoveItemTypemy( HITEMPOOL whichItemPool , int itemId )
{
	fprintf_s( logfile , "%s\n" , "ItemPoolRemoveItemTypemy" );
	fflush( logfile );

	GAME_ItemPoolRemoveItemTypeold( whichItemPool , itemId );
	fprintf_s( logfile , "%s:[-->GAME_ItemPoolRemoveItemType<--  whichItemPool: %X itemId: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichItemPool , itemId );
	fflush( logfile );

}


typedef void( __cdecl *GAME_KillDestructable )( HDESTRUCTABLE d );
GAME_KillDestructable GAME_KillDestructableorg = NULL;
GAME_KillDestructable GAME_KillDestructableold = NULL;

void __cdecl GAME_KillDestructablemy( HDESTRUCTABLE d )
{
	fprintf_s( logfile , "%s\n" , "KillDestructablemy" );
	fflush( logfile );

	GAME_KillDestructableold( d );
	fprintf_s( logfile , "%s:[-->GAME_KillDestructable<--  d: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , d );
	fflush( logfile );

}


typedef void( __cdecl *GAME_KillSoundWhenDone )( HSOUND soundHandle );
GAME_KillSoundWhenDone GAME_KillSoundWhenDoneorg = NULL;
GAME_KillSoundWhenDone GAME_KillSoundWhenDoneold = NULL;

void __cdecl GAME_KillSoundWhenDonemy( HSOUND soundHandle )
{
	fprintf_s( logfile , "%s\n" , "KillSoundWhenDonemy" );
	fflush( logfile );

	GAME_KillSoundWhenDoneold( soundHandle );
	fprintf_s( logfile , "%s:[-->GAME_KillSoundWhenDone<--  soundHandle: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , soundHandle );
	fflush( logfile );

}


typedef void( __cdecl *GAME_KillUnit )( HUNIT whichUnit );
GAME_KillUnit GAME_KillUnitorg = NULL;
GAME_KillUnit GAME_KillUnitold = NULL;

void __cdecl GAME_KillUnitmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "KillUnitmy" );
	fflush( logfile );

	GAME_KillUnitold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_KillUnit<--  whichUnit: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit );
	fflush( logfile );

}


typedef void( __cdecl *GAME_LeaderboardAddItem )( HLEADERBOARD lb , void * label , int value , HPLAYER p );
GAME_LeaderboardAddItem GAME_LeaderboardAddItemorg = NULL;
GAME_LeaderboardAddItem GAME_LeaderboardAddItemold = NULL;

void __cdecl GAME_LeaderboardAddItemmy( HLEADERBOARD lb , void * label , int value , HPLAYER p )
{
	fprintf_s( logfile , "%s\n" , "LeaderboardAddItemmy" );
	fflush( logfile );

	GAME_LeaderboardAddItemold( lb , label , value , p );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardAddItem<--  lb: %X label: \"%s\" value: %i p: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , jassgetchar( label ) , value , p );
	fflush( logfile );

}


typedef void( __cdecl *GAME_LeaderboardClear )( HLEADERBOARD lb );
GAME_LeaderboardClear GAME_LeaderboardClearorg = NULL;
GAME_LeaderboardClear GAME_LeaderboardClearold = NULL;

void __cdecl GAME_LeaderboardClearmy( HLEADERBOARD lb )
{
	fprintf_s( logfile , "%s" , "LeaderboardClearmy\n" );
	fflush( logfile );

	GAME_LeaderboardClearold( lb );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardClear<--  lb: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb );
	fflush( logfile );

}


typedef void( __cdecl *GAME_LeaderboardDisplay )( HLEADERBOARD lb , BOOL show );
GAME_LeaderboardDisplay GAME_LeaderboardDisplayorg = NULL;
GAME_LeaderboardDisplay GAME_LeaderboardDisplayold = NULL;

void __cdecl GAME_LeaderboardDisplaymy( HLEADERBOARD lb , BOOL show )
{
	fprintf_s( logfile , "%s\n" , "LeaderboardDisplaymy" );
	fflush( logfile );

	GAME_LeaderboardDisplayold( lb , show );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardDisplay<--  lb: %X show: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , show ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef int( __cdecl *GAME_LeaderboardGetItemCount )( HLEADERBOARD lb );
GAME_LeaderboardGetItemCount GAME_LeaderboardGetItemCountorg = NULL;
GAME_LeaderboardGetItemCount GAME_LeaderboardGetItemCountold = NULL;

int __cdecl GAME_LeaderboardGetItemCountmy( HLEADERBOARD lb )
{
	fprintf_s( logfile , "%s" , "LeaderboardGetItemCountmy\n" );
	fflush( logfile );

	int retvalue = GAME_LeaderboardGetItemCountold( lb );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardGetItemCount<--  lb: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , lb , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_LeaderboardGetLabelText )( HLEADERBOARD lb );
GAME_LeaderboardGetLabelText GAME_LeaderboardGetLabelTextorg = NULL;
GAME_LeaderboardGetLabelText GAME_LeaderboardGetLabelTextold = NULL;

DWORD __cdecl GAME_LeaderboardGetLabelTextmy( HLEADERBOARD lb )
{
	fprintf_s( logfile , "%s\n" , "LeaderboardGetLabelTextmy" );
	fflush( logfile );

	DWORD retvalue = GAME_LeaderboardGetLabelTextold( lb );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardGetLabelText<--  lb: %X] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , lb , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_LeaderboardGetPlayerIndex )( HLEADERBOARD lb , HPLAYER p );
GAME_LeaderboardGetPlayerIndex GAME_LeaderboardGetPlayerIndexorg = NULL;
GAME_LeaderboardGetPlayerIndex GAME_LeaderboardGetPlayerIndexold = NULL;

int __cdecl GAME_LeaderboardGetPlayerIndexmy( HLEADERBOARD lb , HPLAYER p )
{
	fprintf_s( logfile , "%s\n" , "LeaderboardGetPlayerIndexmy" );
	fflush( logfile );

	int retvalue = GAME_LeaderboardGetPlayerIndexold( lb , p );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardGetPlayerIndex<--  lb: %X p: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , lb , p , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_LeaderboardHasPlayerItem )( HLEADERBOARD lb , HPLAYER p );
GAME_LeaderboardHasPlayerItem GAME_LeaderboardHasPlayerItemorg = NULL;
GAME_LeaderboardHasPlayerItem GAME_LeaderboardHasPlayerItemold = NULL;

BOOL __cdecl GAME_LeaderboardHasPlayerItemmy( HLEADERBOARD lb , HPLAYER p )
{
	fprintf_s( logfile , "%s\n" , "LeaderboardHasPlayerItemmy" );
	fflush( logfile );

	BOOL retvalue = GAME_LeaderboardHasPlayerItemold( lb , p );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardHasPlayerItem<--  lb: %X p: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , lb , p , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_LeaderboardRemoveItem )( HLEADERBOARD lb , int index );
GAME_LeaderboardRemoveItem GAME_LeaderboardRemoveItemorg = NULL;
GAME_LeaderboardRemoveItem GAME_LeaderboardRemoveItemold = NULL;

void __cdecl GAME_LeaderboardRemoveItemmy( HLEADERBOARD lb , int index )
{
	fprintf_s( logfile , "%s" , "LeaderboardRemoveItemmy\n" );
	fflush( logfile );

	GAME_LeaderboardRemoveItemold( lb , index );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardRemoveItem<--  lb: %X index: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , index );
	fflush( logfile );

}


typedef void( __cdecl *GAME_LeaderboardRemovePlayerItem )( HLEADERBOARD lb , HPLAYER p );
GAME_LeaderboardRemovePlayerItem GAME_LeaderboardRemovePlayerItemorg = NULL;
GAME_LeaderboardRemovePlayerItem GAME_LeaderboardRemovePlayerItemold = NULL;

void __cdecl GAME_LeaderboardRemovePlayerItemmy( HLEADERBOARD lb , HPLAYER p )
{
	fprintf_s( logfile , "%s\n" , "LeaderboardRemovePlayerItemmy" );
	fflush( logfile );

	GAME_LeaderboardRemovePlayerItemold( lb , p );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardRemovePlayerItem<--  lb: %X p: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , p );
	fflush( logfile );

}


typedef void( __cdecl *GAME_LeaderboardSetItemLabel )( HLEADERBOARD lb , int whichItem , void * val );
GAME_LeaderboardSetItemLabel GAME_LeaderboardSetItemLabelorg = NULL;
GAME_LeaderboardSetItemLabel GAME_LeaderboardSetItemLabelold = NULL;

void __cdecl GAME_LeaderboardSetItemLabelmy( HLEADERBOARD lb , int whichItem , void * val )
{
	fprintf_s( logfile , "%s\n" , "LeaderboardSetItemLabelmy" );
	fflush( logfile );

	GAME_LeaderboardSetItemLabelold( lb , whichItem , val );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardSetItemLabel<--  lb: %X whichItem: %i val: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , whichItem , jassgetchar( val ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_LeaderboardSetItemLabelColor )( HLEADERBOARD lb , int whichItem , int red , int green , int blue , int alpha );
GAME_LeaderboardSetItemLabelColor GAME_LeaderboardSetItemLabelColororg = NULL;
GAME_LeaderboardSetItemLabelColor GAME_LeaderboardSetItemLabelColorold = NULL;

void __cdecl GAME_LeaderboardSetItemLabelColormy( HLEADERBOARD lb , int whichItem , int red , int green , int blue , int alpha )
{
	fprintf_s( logfile , "%s" , "LeaderboardSetItemLabelColormy\n" );
	fflush( logfile );

	GAME_LeaderboardSetItemLabelColorold( lb , whichItem , red , green , blue , alpha );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardSetItemLabelColor<--  lb: %X whichItem: %i red: %i green: %i blue: %i alpha: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , whichItem , red , green , blue , alpha );
	fflush( logfile );

}


typedef void( __cdecl *GAME_LeaderboardSetItemStyle )( HLEADERBOARD lb , int whichItem , BOOL showLabel , BOOL showValue , BOOL showIcon );
GAME_LeaderboardSetItemStyle GAME_LeaderboardSetItemStyleorg = NULL;
GAME_LeaderboardSetItemStyle GAME_LeaderboardSetItemStyleold = NULL;

void __cdecl GAME_LeaderboardSetItemStylemy( HLEADERBOARD lb , int whichItem , BOOL showLabel , BOOL showValue , BOOL showIcon )
{
	fprintf_s( logfile , "%s\n" , "LeaderboardSetItemStylemy" );
	fflush( logfile );

	GAME_LeaderboardSetItemStyleold( lb , whichItem , showLabel , showValue , showIcon );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardSetItemStyle<--  lb: %X whichItem: %i showLabel: %s showValue: %s showIcon: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , whichItem , showLabel ? "TRUE\n" : "FALSE" , showValue ? "TRUE" : "FALSE" , showIcon ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_LeaderboardSetItemValue )( HLEADERBOARD lb , int whichItem , int val );
GAME_LeaderboardSetItemValue GAME_LeaderboardSetItemValueorg = NULL;
GAME_LeaderboardSetItemValue GAME_LeaderboardSetItemValueold = NULL;

void __cdecl GAME_LeaderboardSetItemValuemy( HLEADERBOARD lb , int whichItem , int val )
{
	fprintf_s( logfile , "%s" , "LeaderboardSetItemValuemy\n" );
	fflush( logfile );

	GAME_LeaderboardSetItemValueold( lb , whichItem , val );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardSetItemValue<--  lb: %X whichItem: %i val: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , whichItem , val );
	fflush( logfile );

}


typedef void( __cdecl *GAME_LeaderboardSetItemValueColor )( HLEADERBOARD lb , int whichItem , int red , int green , int blue , int alpha );
GAME_LeaderboardSetItemValueColor GAME_LeaderboardSetItemValueColororg = NULL;
GAME_LeaderboardSetItemValueColor GAME_LeaderboardSetItemValueColorold = NULL;

void __cdecl GAME_LeaderboardSetItemValueColormy( HLEADERBOARD lb , int whichItem , int red , int green , int blue , int alpha )
{
	fprintf_s( logfile , "%s\n" , "LeaderboardSetItemValueColormy" );
	fflush( logfile );

	GAME_LeaderboardSetItemValueColorold( lb , whichItem , red , green , blue , alpha );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardSetItemValueColor<--  lb: %X whichItem: %i red: %i green: %i blue: %i alpha: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , whichItem , red , green , blue , alpha );
	fflush( logfile );

}


typedef void( __cdecl *GAME_LeaderboardSetLabel )( HLEADERBOARD lb , void * label );
GAME_LeaderboardSetLabel GAME_LeaderboardSetLabelorg = NULL;
GAME_LeaderboardSetLabel GAME_LeaderboardSetLabelold = NULL;

void __cdecl GAME_LeaderboardSetLabelmy( HLEADERBOARD lb , void * label )
{
	fprintf_s( logfile , "%s\n" , "LeaderboardSetLabelmy" );
	fflush( logfile );

	GAME_LeaderboardSetLabelold( lb , label );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardSetLabel<--  lb: %X label: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , jassgetchar( label ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_LeaderboardSetLabelColor )( HLEADERBOARD lb , int red , int green , int blue , int alpha );
GAME_LeaderboardSetLabelColor GAME_LeaderboardSetLabelColororg = NULL;
GAME_LeaderboardSetLabelColor GAME_LeaderboardSetLabelColorold = NULL;

void __cdecl GAME_LeaderboardSetLabelColormy( HLEADERBOARD lb , int red , int green , int blue , int alpha )
{
	fprintf_s( logfile , "%s" , "LeaderboardSetLabelColormy\n" );
	fflush( logfile );

	GAME_LeaderboardSetLabelColorold( lb , red , green , blue , alpha );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardSetLabelColor<--  lb: %X red: %i green: %i blue: %i alpha: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , red , green , blue , alpha );
	fflush( logfile );

}


typedef void( __cdecl *GAME_LeaderboardSetSizeByItemCount )( HLEADERBOARD lb , int count );
GAME_LeaderboardSetSizeByItemCount GAME_LeaderboardSetSizeByItemCountorg = NULL;
GAME_LeaderboardSetSizeByItemCount GAME_LeaderboardSetSizeByItemCountold = NULL;

void __cdecl GAME_LeaderboardSetSizeByItemCountmy( HLEADERBOARD lb , int count )
{
	fprintf_s( logfile , "%s\n" , "LeaderboardSetSizeByItemCountmy" );
	fflush( logfile );

	GAME_LeaderboardSetSizeByItemCountold( lb , count );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardSetSizeByItemCount<--  lb: %X count: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , count );
	fflush( logfile );

}


typedef void( __cdecl *GAME_LeaderboardSetStyle )( HLEADERBOARD lb , BOOL showLabel , BOOL showNames , BOOL showValues , BOOL showIcons );
GAME_LeaderboardSetStyle GAME_LeaderboardSetStyleorg = NULL;
GAME_LeaderboardSetStyle GAME_LeaderboardSetStyleold = NULL;

void __cdecl GAME_LeaderboardSetStylemy( HLEADERBOARD lb , BOOL showLabel , BOOL showNames , BOOL showValues , BOOL showIcons )
{
	fprintf_s( logfile , "%s\n" , "LeaderboardSetStylemy" );
	fflush( logfile );

	GAME_LeaderboardSetStyleold( lb , showLabel , showNames , showValues , showIcons );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardSetStyle<--  lb: %X showLabel: %s showNames: %s showValues: %s showIcons: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , showLabel ? "TRUE\n" : "FALSE" , showNames ? "TRUE" : "FALSE" , showValues ? "TRUE" : "FALSE" , showIcons ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_LeaderboardSetValueColor )( HLEADERBOARD lb , int red , int green , int blue , int alpha );
GAME_LeaderboardSetValueColor GAME_LeaderboardSetValueColororg = NULL;
GAME_LeaderboardSetValueColor GAME_LeaderboardSetValueColorold = NULL;

void __cdecl GAME_LeaderboardSetValueColormy( HLEADERBOARD lb , int red , int green , int blue , int alpha )
{
	fprintf_s( logfile , "%s" , "LeaderboardSetValueColormy\n" );
	fflush( logfile );

	GAME_LeaderboardSetValueColorold( lb , red , green , blue , alpha );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardSetValueColor<--  lb: %X red: %i green: %i blue: %i alpha: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , red , green , blue , alpha );
	fflush( logfile );

}


typedef void( __cdecl *GAME_LeaderboardSortItemsByLabel )( HLEADERBOARD lb , BOOL ascending );
GAME_LeaderboardSortItemsByLabel GAME_LeaderboardSortItemsByLabelorg = NULL;
GAME_LeaderboardSortItemsByLabel GAME_LeaderboardSortItemsByLabelold = NULL;

void __cdecl GAME_LeaderboardSortItemsByLabelmy( HLEADERBOARD lb , BOOL ascending )
{
	fprintf_s( logfile , "%s\n" , "LeaderboardSortItemsByLabelmy" );
	fflush( logfile );

	GAME_LeaderboardSortItemsByLabelold( lb , ascending );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardSortItemsByLabel<--  lb: %X ascending: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , ascending ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_LeaderboardSortItemsByPlayer )( HLEADERBOARD lb , BOOL ascending );
GAME_LeaderboardSortItemsByPlayer GAME_LeaderboardSortItemsByPlayerorg = NULL;
GAME_LeaderboardSortItemsByPlayer GAME_LeaderboardSortItemsByPlayerold = NULL;

void __cdecl GAME_LeaderboardSortItemsByPlayermy( HLEADERBOARD lb , BOOL ascending )
{
	fprintf_s( logfile , "%s" , "LeaderboardSortItemsByPlayermy\n" );
	fflush( logfile );

	GAME_LeaderboardSortItemsByPlayerold( lb , ascending );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardSortItemsByPlayer<--  lb: %X ascending: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , ascending ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_LeaderboardSortItemsByValue )( HLEADERBOARD lb , BOOL ascending );
GAME_LeaderboardSortItemsByValue GAME_LeaderboardSortItemsByValueorg = NULL;
GAME_LeaderboardSortItemsByValue GAME_LeaderboardSortItemsByValueold = NULL;

void __cdecl GAME_LeaderboardSortItemsByValuemy( HLEADERBOARD lb , BOOL ascending )
{
	fprintf_s( logfile , "%s" , "LeaderboardSortItemsByValuemy\n" );
	fflush( logfile );

	GAME_LeaderboardSortItemsByValueold( lb , ascending );
	fprintf_s( logfile , "%s:[-->GAME_LeaderboardSortItemsByValue<--  lb: %X ascending: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , ascending ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef HABILITY( __cdecl *GAME_LoadAbilityHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadAbilityHandle GAME_LoadAbilityHandleorg = NULL;
GAME_LoadAbilityHandle GAME_LoadAbilityHandleold = NULL;

HABILITY __cdecl GAME_LoadAbilityHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s" , "LoadAbilityHandlemy\n" );
	fflush( logfile );

	HABILITY retvalue = GAME_LoadAbilityHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadAbilityHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_LoadBOOLean )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadBOOLean GAME_LoadBOOLeanorg = NULL;
GAME_LoadBOOLean GAME_LoadBOOLeanold = NULL;

BOOL __cdecl GAME_LoadBOOLeanmy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadBOOLeanmy" );
	fflush( logfile );

	BOOL retvalue = GAME_LoadBOOLeanold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadBOOLean<--  table: %X parentKey: %i childKey: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef HBOOLEXPR( __cdecl *GAME_LoadBOOLeanExprHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadBOOLeanExprHandle GAME_LoadBOOLeanExprHandleorg = NULL;
GAME_LoadBOOLeanExprHandle GAME_LoadBOOLeanExprHandleold = NULL;

HBOOLEXPR __cdecl GAME_LoadBOOLeanExprHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s" , "LoadBOOLeanExprHandlemy\n" );
	fflush( logfile );

	HBOOLEXPR retvalue = GAME_LoadBOOLeanExprHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadBOOLeanExprHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HBUTTON( __cdecl *GAME_LoadButtonHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadButtonHandle GAME_LoadButtonHandleorg = NULL;
GAME_LoadButtonHandle GAME_LoadButtonHandleold = NULL;

HBUTTON __cdecl GAME_LoadButtonHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadButtonHandlemy" );
	fflush( logfile );

	HBUTTON retvalue = GAME_LoadButtonHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadButtonHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HDEFEATCONDITION( __cdecl *GAME_LoadDefeatConditionHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadDefeatConditionHandle GAME_LoadDefeatConditionHandleorg = NULL;
GAME_LoadDefeatConditionHandle GAME_LoadDefeatConditionHandleold = NULL;

HDEFEATCONDITION __cdecl GAME_LoadDefeatConditionHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadDefeatConditionHandlemy" );
	fflush( logfile );

	HDEFEATCONDITION retvalue = GAME_LoadDefeatConditionHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadDefeatConditionHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HDESTRUCTABLE( __cdecl *GAME_LoadDestructableHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadDestructableHandle GAME_LoadDestructableHandleorg = NULL;
GAME_LoadDestructableHandle GAME_LoadDestructableHandleold = NULL;

HDESTRUCTABLE __cdecl GAME_LoadDestructableHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadDestructableHandlemy" );
	fflush( logfile );

	HDESTRUCTABLE retvalue = GAME_LoadDestructableHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadDestructableHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HDIALOG( __cdecl *GAME_LoadDialogHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadDialogHandle GAME_LoadDialogHandleorg = NULL;
GAME_LoadDialogHandle GAME_LoadDialogHandleold = NULL;

HDIALOG __cdecl GAME_LoadDialogHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadDialogHandlemy" );
	fflush( logfile );

	HDIALOG retvalue = GAME_LoadDialogHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadDialogHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEFFECT( __cdecl *GAME_LoadEffectHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadEffectHandle GAME_LoadEffectHandleorg = NULL;
GAME_LoadEffectHandle GAME_LoadEffectHandleold = NULL;

HEFFECT __cdecl GAME_LoadEffectHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadEffectHandlemy" );
	fflush( logfile );

	HEFFECT retvalue = GAME_LoadEffectHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadEffectHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HFOGMODIFIER( __cdecl *GAME_LoadFogModifierHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadFogModifierHandle GAME_LoadFogModifierHandleorg = NULL;
GAME_LoadFogModifierHandle GAME_LoadFogModifierHandleold = NULL;

HFOGMODIFIER __cdecl GAME_LoadFogModifierHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadFogModifierHandlemy" );
	fflush( logfile );

	HFOGMODIFIER retvalue = GAME_LoadFogModifierHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadFogModifierHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HFOGSTATE( __cdecl *GAME_LoadFogStateHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadFogStateHandle GAME_LoadFogStateHandleorg = NULL;
GAME_LoadFogStateHandle GAME_LoadFogStateHandleold = NULL;

HFOGSTATE __cdecl GAME_LoadFogStateHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadFogStateHandlemy" );
	fflush( logfile );

	HFOGSTATE retvalue = GAME_LoadFogStateHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadFogStateHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HFORCE( __cdecl *GAME_LoadForceHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadForceHandle GAME_LoadForceHandleorg = NULL;
GAME_LoadForceHandle GAME_LoadForceHandleold = NULL;

HFORCE __cdecl GAME_LoadForceHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadForceHandlemy" );
	fflush( logfile );

	HFORCE retvalue = GAME_LoadForceHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadForceHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_LoadGame )( void * saveFileName , BOOL doScoreScreen );
GAME_LoadGame GAME_LoadGameorg = NULL;
GAME_LoadGame GAME_LoadGameold = NULL;

void __cdecl GAME_LoadGamemy( void * saveFileName , BOOL doScoreScreen )
{
	fprintf_s( logfile , "%s\n" , "LoadGamemy" );
	fflush( logfile );

	GAME_LoadGameold( saveFileName , doScoreScreen );
	fprintf_s( logfile , "%s:[-->GAME_LoadGame<--  saveFileName: \"%s\" doScoreScreen: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( saveFileName ) , doScoreScreen ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef HGROUP( __cdecl *GAME_LoadGroupHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadGroupHandle GAME_LoadGroupHandleorg = NULL;
GAME_LoadGroupHandle GAME_LoadGroupHandleold = NULL;

HGROUP __cdecl GAME_LoadGroupHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s" , "LoadGroupHandlemy\n" );
	fflush( logfile );

	HGROUP retvalue = GAME_LoadGroupHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadGroupHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HHASHTABLE( __cdecl *GAME_LoadHashtableHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadHashtableHandle GAME_LoadHashtableHandleorg = NULL;
GAME_LoadHashtableHandle GAME_LoadHashtableHandleold = NULL;

HHASHTABLE __cdecl GAME_LoadHashtableHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadHashtableHandlemy" );
	fflush( logfile );

	HHASHTABLE retvalue = GAME_LoadHashtableHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadHashtableHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HIMAGE( __cdecl *GAME_LoadImageHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadImageHandle GAME_LoadImageHandleorg = NULL;
GAME_LoadImageHandle GAME_LoadImageHandleold = NULL;

HIMAGE __cdecl GAME_LoadImageHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadImageHandlemy" );
	fflush( logfile );

	HIMAGE retvalue = GAME_LoadImageHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadImageHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_LoadInteger )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadInteger GAME_LoadIntegerorg = NULL;
GAME_LoadInteger GAME_LoadIntegerold = NULL;

int __cdecl GAME_LoadIntegermy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadIntegermy" );
	fflush( logfile );

	int retvalue = GAME_LoadIntegerold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadInteger<--  table: %X parentKey: %i childKey: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HITEM( __cdecl *GAME_LoadItemHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadItemHandle GAME_LoadItemHandleorg = NULL;
GAME_LoadItemHandle GAME_LoadItemHandleold = NULL;

HITEM __cdecl GAME_LoadItemHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadItemHandlemy" );
	fflush( logfile );

	HITEM retvalue = GAME_LoadItemHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadItemHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HITEMPOOL( __cdecl *GAME_LoadItemPoolHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadItemPoolHandle GAME_LoadItemPoolHandleorg = NULL;
GAME_LoadItemPoolHandle GAME_LoadItemPoolHandleold = NULL;

HITEMPOOL __cdecl GAME_LoadItemPoolHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadItemPoolHandlemy" );
	fflush( logfile );

	HITEMPOOL retvalue = GAME_LoadItemPoolHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadItemPoolHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HLEADERBOARD( __cdecl *GAME_LoadLeaderboardHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadLeaderboardHandle GAME_LoadLeaderboardHandleorg = NULL;
GAME_LoadLeaderboardHandle GAME_LoadLeaderboardHandleold = NULL;

HLEADERBOARD __cdecl GAME_LoadLeaderboardHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadLeaderboardHandlemy" );
	fflush( logfile );

	HLEADERBOARD retvalue = GAME_LoadLeaderboardHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadLeaderboardHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HLIGHTNING( __cdecl *GAME_LoadLightningHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadLightningHandle GAME_LoadLightningHandleorg = NULL;
GAME_LoadLightningHandle GAME_LoadLightningHandleold = NULL;

HLIGHTNING __cdecl GAME_LoadLightningHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadLightningHandlemy" );
	fflush( logfile );

	HLIGHTNING retvalue = GAME_LoadLightningHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadLightningHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HLOCATION( __cdecl *GAME_LoadLocationHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadLocationHandle GAME_LoadLocationHandleorg = NULL;
GAME_LoadLocationHandle GAME_LoadLocationHandleold = NULL;

HLOCATION __cdecl GAME_LoadLocationHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadLocationHandlemy" );
	fflush( logfile );

	HLOCATION retvalue = GAME_LoadLocationHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadLocationHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HMULTIBOARD( __cdecl *GAME_LoadMultiboardHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadMultiboardHandle GAME_LoadMultiboardHandleorg = NULL;
GAME_LoadMultiboardHandle GAME_LoadMultiboardHandleold = NULL;

HMULTIBOARD __cdecl GAME_LoadMultiboardHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadMultiboardHandlemy" );
	fflush( logfile );

	HMULTIBOARD retvalue = GAME_LoadMultiboardHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadMultiboardHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HMULTIBOARDITEM( __cdecl *GAME_LoadMultiboardItemHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadMultiboardItemHandle GAME_LoadMultiboardItemHandleorg = NULL;
GAME_LoadMultiboardItemHandle GAME_LoadMultiboardItemHandleold = NULL;

HMULTIBOARDITEM __cdecl GAME_LoadMultiboardItemHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadMultiboardItemHandlemy" );
	fflush( logfile );

	HMULTIBOARDITEM retvalue = GAME_LoadMultiboardItemHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadMultiboardItemHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HPLAYER( __cdecl *GAME_LoadPlayerHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadPlayerHandle GAME_LoadPlayerHandleorg = NULL;
GAME_LoadPlayerHandle GAME_LoadPlayerHandleold = NULL;

HPLAYER __cdecl GAME_LoadPlayerHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadPlayerHandlemy" );
	fflush( logfile );

	HPLAYER retvalue = GAME_LoadPlayerHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadPlayerHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HQUEST( __cdecl *GAME_LoadQuestHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadQuestHandle GAME_LoadQuestHandleorg = NULL;
GAME_LoadQuestHandle GAME_LoadQuestHandleold = NULL;

HQUEST __cdecl GAME_LoadQuestHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadQuestHandlemy" );
	fflush( logfile );

	HQUEST retvalue = GAME_LoadQuestHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadQuestHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HQUESTITEM( __cdecl *GAME_LoadQuestItemHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadQuestItemHandle GAME_LoadQuestItemHandleorg = NULL;
GAME_LoadQuestItemHandle GAME_LoadQuestItemHandleold = NULL;

HQUESTITEM __cdecl GAME_LoadQuestItemHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadQuestItemHandlemy" );
	fflush( logfile );

	HQUESTITEM retvalue = GAME_LoadQuestItemHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadQuestItemHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_LoadReal )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadReal GAME_LoadRealorg = NULL;
GAME_LoadReal GAME_LoadRealold = NULL;

DWFP __cdecl GAME_LoadRealmy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadRealmy" );
	fflush( logfile );

	DWFP retvalue = GAME_LoadRealold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadReal<--  table: %X parentKey: %i childKey: %i] RETURN-> %f\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef HRECT( __cdecl *GAME_LoadRectHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadRectHandle GAME_LoadRectHandleorg = NULL;
GAME_LoadRectHandle GAME_LoadRectHandleold = NULL;

HRECT __cdecl GAME_LoadRectHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadRectHandlemy" );
	fflush( logfile );

	HRECT retvalue = GAME_LoadRectHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadRectHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HREGION( __cdecl *GAME_LoadRegionHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadRegionHandle GAME_LoadRegionHandleorg = NULL;
GAME_LoadRegionHandle GAME_LoadRegionHandleold = NULL;

HREGION __cdecl GAME_LoadRegionHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadRegionHandlemy" );
	fflush( logfile );

	HREGION retvalue = GAME_LoadRegionHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadRegionHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HSOUND( __cdecl *GAME_LoadSoundHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadSoundHandle GAME_LoadSoundHandleorg = NULL;
GAME_LoadSoundHandle GAME_LoadSoundHandleold = NULL;

HSOUND __cdecl GAME_LoadSoundHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadSoundHandlemy" );
	fflush( logfile );

	HSOUND retvalue = GAME_LoadSoundHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadSoundHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_LoadStr )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadStr GAME_LoadStrorg = NULL;
GAME_LoadStr GAME_LoadStrold = NULL;

DWORD __cdecl GAME_LoadStrmy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadStrmy" );
	fflush( logfile );

	DWORD retvalue = GAME_LoadStrold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadStr<--  table: %X parentKey: %i childKey: %i] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef HTEXTTAG( __cdecl *GAME_LoadTextTagHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadTextTagHandle GAME_LoadTextTagHandleorg = NULL;
GAME_LoadTextTagHandle GAME_LoadTextTagHandleold = NULL;

HTEXTTAG __cdecl GAME_LoadTextTagHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadTextTagHandlemy" );
	fflush( logfile );

	HTEXTTAG retvalue = GAME_LoadTextTagHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadTextTagHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTIMERDIALOG( __cdecl *GAME_LoadTimerDialogHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadTimerDialogHandle GAME_LoadTimerDialogHandleorg = NULL;
GAME_LoadTimerDialogHandle GAME_LoadTimerDialogHandleold = NULL;

HTIMERDIALOG __cdecl GAME_LoadTimerDialogHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadTimerDialogHandlemy" );
	fflush( logfile );

	HTIMERDIALOG retvalue = GAME_LoadTimerDialogHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadTimerDialogHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTIMER( __cdecl *GAME_LoadTimerHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadTimerHandle GAME_LoadTimerHandleorg = NULL;
GAME_LoadTimerHandle GAME_LoadTimerHandleold = NULL;

HTIMER __cdecl GAME_LoadTimerHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadTimerHandlemy" );
	fflush( logfile );

	HTIMER retvalue = GAME_LoadTimerHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadTimerHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTRACKABLE( __cdecl *GAME_LoadTrackableHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadTrackableHandle GAME_LoadTrackableHandleorg = NULL;
GAME_LoadTrackableHandle GAME_LoadTrackableHandleold = NULL;

HTRACKABLE __cdecl GAME_LoadTrackableHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadTrackableHandlemy" );
	fflush( logfile );

	HTRACKABLE retvalue = GAME_LoadTrackableHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadTrackableHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTRIGGERACTION( __cdecl *GAME_LoadTriggerActionHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadTriggerActionHandle GAME_LoadTriggerActionHandleorg = NULL;
GAME_LoadTriggerActionHandle GAME_LoadTriggerActionHandleold = NULL;

HTRIGGERACTION __cdecl GAME_LoadTriggerActionHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadTriggerActionHandlemy" );
	fflush( logfile );

	HTRIGGERACTION retvalue = GAME_LoadTriggerActionHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadTriggerActionHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTRIGGERCONDITION( __cdecl *GAME_LoadTriggerConditionHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadTriggerConditionHandle GAME_LoadTriggerConditionHandleorg = NULL;
GAME_LoadTriggerConditionHandle GAME_LoadTriggerConditionHandleold = NULL;

HTRIGGERCONDITION __cdecl GAME_LoadTriggerConditionHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadTriggerConditionHandlemy" );
	fflush( logfile );

	HTRIGGERCONDITION retvalue = GAME_LoadTriggerConditionHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadTriggerConditionHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_LoadTriggerEventHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadTriggerEventHandle GAME_LoadTriggerEventHandleorg = NULL;
GAME_LoadTriggerEventHandle GAME_LoadTriggerEventHandleold = NULL;

HEVENT __cdecl GAME_LoadTriggerEventHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadTriggerEventHandlemy" );
	fflush( logfile );

	HEVENT retvalue = GAME_LoadTriggerEventHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadTriggerEventHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTRIGGER( __cdecl *GAME_LoadTriggerHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadTriggerHandle GAME_LoadTriggerHandleorg = NULL;
GAME_LoadTriggerHandle GAME_LoadTriggerHandleold = NULL;

HTRIGGER __cdecl GAME_LoadTriggerHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadTriggerHandlemy" );
	fflush( logfile );

	HTRIGGER retvalue = GAME_LoadTriggerHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadTriggerHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUBERSPLAT( __cdecl *GAME_LoadUbersplatHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadUbersplatHandle GAME_LoadUbersplatHandleorg = NULL;
GAME_LoadUbersplatHandle GAME_LoadUbersplatHandleold = NULL;

HUBERSPLAT __cdecl GAME_LoadUbersplatHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadUbersplatHandlemy" );
	fflush( logfile );

	HUBERSPLAT retvalue = GAME_LoadUbersplatHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadUbersplatHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_LoadUnitHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadUnitHandle GAME_LoadUnitHandleorg = NULL;
GAME_LoadUnitHandle GAME_LoadUnitHandleold = NULL;

HUNIT __cdecl GAME_LoadUnitHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadUnitHandlemy" );
	fflush( logfile );

	HUNIT retvalue = GAME_LoadUnitHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadUnitHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNITPOOL( __cdecl *GAME_LoadUnitPoolHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadUnitPoolHandle GAME_LoadUnitPoolHandleorg = NULL;
GAME_LoadUnitPoolHandle GAME_LoadUnitPoolHandleold = NULL;

HUNITPOOL __cdecl GAME_LoadUnitPoolHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadUnitPoolHandlemy" );
	fflush( logfile );

	HUNITPOOL retvalue = GAME_LoadUnitPoolHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadUnitPoolHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HWIDGET( __cdecl *GAME_LoadWidgetHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_LoadWidgetHandle GAME_LoadWidgetHandleorg = NULL;
GAME_LoadWidgetHandle GAME_LoadWidgetHandleold = NULL;

HWIDGET __cdecl GAME_LoadWidgetHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "LoadWidgetHandlemy" );
	fflush( logfile );

	HWIDGET retvalue = GAME_LoadWidgetHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_LoadWidgetHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_LoadZepWave )( int arg1 , int arg2 );
GAME_LoadZepWave GAME_LoadZepWaveorg = NULL;
GAME_LoadZepWave GAME_LoadZepWaveold = NULL;

void __cdecl GAME_LoadZepWavemy( int arg1 , int arg2 )
{
	fprintf_s( logfile , "%s\n" , "LoadZepWavemy" );
	fflush( logfile );

	GAME_LoadZepWaveold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_LoadZepWave<--  arg1: %i arg2: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 , arg2 );
	fflush( logfile );

}


typedef HLOCATION( __cdecl *GAME_Location )( float *x , float *y );
GAME_Location GAME_Locationorg = NULL;
GAME_Location GAME_Locationold = NULL;

HLOCATION __cdecl GAME_Locationmy( float *x , float *y )
{
	fprintf_s( logfile , "%s\n" , "Locationmy" );
	fflush( logfile );

	HLOCATION retvalue = GAME_Locationold( x , y );
	fprintf_s( logfile , "%s:[-->GAME_Location<--  x: %f y: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_MeleeDifficulty )( );
GAME_MeleeDifficulty GAME_MeleeDifficultyorg = NULL;
GAME_MeleeDifficulty GAME_MeleeDifficultyold = NULL;

int __cdecl GAME_MeleeDifficultymy( )
{
	fprintf_s( logfile , "%s\n" , "MeleeDifficultymy" );
	fflush( logfile );

	int retvalue = GAME_MeleeDifficultyold( );
	fprintf_s( logfile , "%s:[-->GAME_MeleeDifficulty<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_MergeUnits )( int arg1 , int arg2 , int arg3 , int arg4 );
GAME_MergeUnits GAME_MergeUnitsorg = NULL;
GAME_MergeUnits GAME_MergeUnitsold = NULL;

BOOL __cdecl GAME_MergeUnitsmy( int arg1 , int arg2 , int arg3 , int arg4 )
{
	fprintf_s( logfile , "%s\n" , "MergeUnitsmy" );
	fflush( logfile );

	BOOL retvalue = GAME_MergeUnitsold( arg1 , arg2 , arg3 , arg4 );
	fprintf_s( logfile , "%s:[-->GAME_MergeUnits<--  arg1: %i arg2: %i arg3: %i arg4: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , arg1 , arg2 , arg3 , arg4 , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_MoveLightning )( HLIGHTNING whichBolt , BOOL checkVisibility , float *x1 , float *y1 , float *x2 , float *y2 );
GAME_MoveLightning GAME_MoveLightningorg = NULL;
GAME_MoveLightning GAME_MoveLightningold = NULL;

BOOL __cdecl GAME_MoveLightningmy( HLIGHTNING whichBolt , BOOL checkVisibility , float *x1 , float *y1 , float *x2 , float *y2 )
{
	fprintf_s( logfile , "%s" , "MoveLightningmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_MoveLightningold( whichBolt , checkVisibility , x1 , y1 , x2 , y2 );
	fprintf_s( logfile , "%s:[-->GAME_MoveLightning<--  whichBolt: %X checkVisibility: %s x1: %f y1: %f x2: %f y2: %f] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichBolt , checkVisibility ? "TRUE\n" : "FALSE" , *( float * ) x1 , *( float * ) y1 , *( float * ) x2 , *( float * ) y2 , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_MoveLightningEx )( HLIGHTNING whichBolt , BOOL checkVisibility , float *x1 , float *y1 , float *z1 , float *x2 , float *y2 , float *z2 );
GAME_MoveLightningEx GAME_MoveLightningExorg = NULL;
GAME_MoveLightningEx GAME_MoveLightningExold = NULL;

BOOL __cdecl GAME_MoveLightningExmy( HLIGHTNING whichBolt , BOOL checkVisibility , float *x1 , float *y1 , float *z1 , float *x2 , float *y2 , float *z2 )
{
	fprintf_s( logfile , "%s" , "MoveLightningExmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_MoveLightningExold( whichBolt , checkVisibility , x1 , y1 , z1 , x2 , y2 , z2 );
	fprintf_s( logfile , "%s:[-->GAME_MoveLightningEx<--  whichBolt: %X checkVisibility: %s x1: %f y1: %f z1: %f x2: %f y2: %f z2: %f] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichBolt , checkVisibility ? "TRUE\n" : "FALSE" , *( float * ) x1 , *( float * ) y1 , *( float * ) z1 , *( float * ) x2 , *( float * ) y2 , *( float * ) z2 , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_MoveLocation )( HLOCATION whichLocation , float *newX , float *newY );
GAME_MoveLocation GAME_MoveLocationorg = NULL;
GAME_MoveLocation GAME_MoveLocationold = NULL;

void __cdecl GAME_MoveLocationmy( HLOCATION whichLocation , float *newX , float *newY )
{
	fprintf_s( logfile , "%s" , "MoveLocationmy\n" );
	fflush( logfile );

	GAME_MoveLocationold( whichLocation , newX , newY );
	fprintf_s( logfile , "%s:[-->GAME_MoveLocation<--  whichLocation: %X newX: %f newY: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichLocation , *( float * ) newX , *( float * ) newY );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MoveRectTo )( HRECT whichRect , float *newCenterX , float *newCenterY );
GAME_MoveRectTo GAME_MoveRectToorg = NULL;
GAME_MoveRectTo GAME_MoveRectToold = NULL;

void __cdecl GAME_MoveRectTomy( HRECT whichRect , float *newCenterX , float *newCenterY )
{
	fprintf_s( logfile , "%s\n" , "MoveRectTomy" );
	fflush( logfile );

	GAME_MoveRectToold( whichRect , newCenterX , newCenterY );
	fprintf_s( logfile , "%s:[-->GAME_MoveRectTo<--  whichRect: %X newCenterX: %f newCenterY: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichRect , *( float * ) newCenterX , *( float * ) newCenterY );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MoveRectToLoc )( HRECT whichRect , HLOCATION newCenterLoc );
GAME_MoveRectToLoc GAME_MoveRectToLocorg = NULL;
GAME_MoveRectToLoc GAME_MoveRectToLocold = NULL;

void __cdecl GAME_MoveRectToLocmy( HRECT whichRect , HLOCATION newCenterLoc )
{
	fprintf_s( logfile , "%s\n" , "MoveRectToLocmy" );
	fflush( logfile );

	GAME_MoveRectToLocold( whichRect , newCenterLoc );
	fprintf_s( logfile , "%s:[-->GAME_MoveRectToLoc<--  whichRect: %X newCenterLoc: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichRect , newCenterLoc );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MultiboardClear )( HMULTIBOARD lb );
GAME_MultiboardClear GAME_MultiboardClearorg = NULL;
GAME_MultiboardClear GAME_MultiboardClearold = NULL;

void __cdecl GAME_MultiboardClearmy( HMULTIBOARD lb )
{
	fprintf_s( logfile , "%s\n" , "MultiboardClearmy" );
	fflush( logfile );

	GAME_MultiboardClearold( lb );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardClear<--  lb: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MultiboardDisplay )( HMULTIBOARD lb , BOOL show );
GAME_MultiboardDisplay GAME_MultiboardDisplayorg = NULL;
GAME_MultiboardDisplay GAME_MultiboardDisplayold = NULL;

void __cdecl GAME_MultiboardDisplaymy( HMULTIBOARD lb , BOOL show )
{
	fprintf_s( logfile , "%s\n" , "MultiboardDisplaymy" );
	fflush( logfile );

	GAME_MultiboardDisplayold( lb , show );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardDisplay<--  lb: %X show: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , show ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef int( __cdecl *GAME_MultiboardGetColumnCount )( HMULTIBOARD lb );
GAME_MultiboardGetColumnCount GAME_MultiboardGetColumnCountorg = NULL;
GAME_MultiboardGetColumnCount GAME_MultiboardGetColumnCountold = NULL;

int __cdecl GAME_MultiboardGetColumnCountmy( HMULTIBOARD lb )
{
	fprintf_s( logfile , "%s" , "MultiboardGetColumnCountmy\n" );
	fflush( logfile );

	int retvalue = GAME_MultiboardGetColumnCountold( lb );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardGetColumnCount<--  lb: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , lb , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HMULTIBOARDITEM( __cdecl *GAME_MultiboardGetItem )( HMULTIBOARD lb , int row , int column );
GAME_MultiboardGetItem GAME_MultiboardGetItemorg = NULL;
GAME_MultiboardGetItem GAME_MultiboardGetItemold = NULL;

HMULTIBOARDITEM __cdecl GAME_MultiboardGetItemmy( HMULTIBOARD lb , int row , int column )
{
	fprintf_s( logfile , "%s\n" , "MultiboardGetItemmy" );
	fflush( logfile );

	HMULTIBOARDITEM retvalue = GAME_MultiboardGetItemold( lb , row , column );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardGetItem<--  lb: %X row: %i column: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , lb , row , column , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_MultiboardGetRowCount )( HMULTIBOARD lb );
GAME_MultiboardGetRowCount GAME_MultiboardGetRowCountorg = NULL;
GAME_MultiboardGetRowCount GAME_MultiboardGetRowCountold = NULL;

int __cdecl GAME_MultiboardGetRowCountmy( HMULTIBOARD lb )
{
	fprintf_s( logfile , "%s\n" , "MultiboardGetRowCountmy" );
	fflush( logfile );

	int retvalue = GAME_MultiboardGetRowCountold( lb );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardGetRowCount<--  lb: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , lb , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_MultiboardGetTitleText )( HMULTIBOARD lb );
GAME_MultiboardGetTitleText GAME_MultiboardGetTitleTextorg = NULL;
GAME_MultiboardGetTitleText GAME_MultiboardGetTitleTextold = NULL;

DWORD __cdecl GAME_MultiboardGetTitleTextmy( HMULTIBOARD lb )
{
	fprintf_s( logfile , "%s\n" , "MultiboardGetTitleTextmy" );
	fflush( logfile );

	DWORD retvalue = GAME_MultiboardGetTitleTextold( lb );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardGetTitleText<--  lb: %X] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , lb , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_MultiboardMinimize )( HMULTIBOARD lb , BOOL minimize );
GAME_MultiboardMinimize GAME_MultiboardMinimizeorg = NULL;
GAME_MultiboardMinimize GAME_MultiboardMinimizeold = NULL;

void __cdecl GAME_MultiboardMinimizemy( HMULTIBOARD lb , BOOL minimize )
{
	fprintf_s( logfile , "%s\n" , "MultiboardMinimizemy" );
	fflush( logfile );

	GAME_MultiboardMinimizeold( lb , minimize );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardMinimize<--  lb: %X minimize: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , minimize ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MultiboardReleaseItem )( HMULTIBOARDITEM mbi );
GAME_MultiboardReleaseItem GAME_MultiboardReleaseItemorg = NULL;
GAME_MultiboardReleaseItem GAME_MultiboardReleaseItemold = NULL;

void __cdecl GAME_MultiboardReleaseItemmy( HMULTIBOARDITEM mbi )
{
	fprintf_s( logfile , "%s" , "MultiboardReleaseItemmy\n" );
	fflush( logfile );

	GAME_MultiboardReleaseItemold( mbi );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardReleaseItem<--  mbi: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , mbi );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MultiboardSetColumnCount )( HMULTIBOARD lb , int count );
GAME_MultiboardSetColumnCount GAME_MultiboardSetColumnCountorg = NULL;
GAME_MultiboardSetColumnCount GAME_MultiboardSetColumnCountold = NULL;

void __cdecl GAME_MultiboardSetColumnCountmy( HMULTIBOARD lb , int count )
{
	fprintf_s( logfile , "%s\n" , "MultiboardSetColumnCountmy" );
	fflush( logfile );

	GAME_MultiboardSetColumnCountold( lb , count );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardSetColumnCount<--  lb: %X count: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , count );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MultiboardSetItemIcon )( HMULTIBOARDITEM mbi , void * iconFileName );
GAME_MultiboardSetItemIcon GAME_MultiboardSetItemIconorg = NULL;
GAME_MultiboardSetItemIcon GAME_MultiboardSetItemIconold = NULL;

void __cdecl GAME_MultiboardSetItemIconmy( HMULTIBOARDITEM mbi , void * iconFileName )
{
	fprintf_s( logfile , "%s\n" , "MultiboardSetItemIconmy" );
	fflush( logfile );

	GAME_MultiboardSetItemIconold( mbi , iconFileName );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardSetItemIcon<--  mbi: %X iconFileName: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , mbi , jassgetchar( iconFileName ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MultiboardSetItemStyle )( HMULTIBOARDITEM mbi , BOOL showValue , BOOL showIcon );
GAME_MultiboardSetItemStyle GAME_MultiboardSetItemStyleorg = NULL;
GAME_MultiboardSetItemStyle GAME_MultiboardSetItemStyleold = NULL;

void __cdecl GAME_MultiboardSetItemStylemy( HMULTIBOARDITEM mbi , BOOL showValue , BOOL showIcon )
{
	fprintf_s( logfile , "%s" , "MultiboardSetItemStylemy\n" );
	fflush( logfile );

	GAME_MultiboardSetItemStyleold( mbi , showValue , showIcon );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardSetItemStyle<--  mbi: %X showValue: %s showIcon: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , mbi , showValue ? "TRUE\n" : "FALSE" , showIcon ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MultiboardSetItemValue )( HMULTIBOARDITEM mbi , void * val );
GAME_MultiboardSetItemValue GAME_MultiboardSetItemValueorg = NULL;
GAME_MultiboardSetItemValue GAME_MultiboardSetItemValueold = NULL;

void __cdecl GAME_MultiboardSetItemValuemy( HMULTIBOARDITEM mbi , void * val )
{
	fprintf_s( logfile , "%s" , "MultiboardSetItemValuemy\n" );
	fflush( logfile );

	GAME_MultiboardSetItemValueold( mbi , val );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardSetItemValue<--  mbi: %X val: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , mbi , jassgetchar( val ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MultiboardSetItemValueColor )( HMULTIBOARDITEM mbi , int red , int green , int blue , int alpha );
GAME_MultiboardSetItemValueColor GAME_MultiboardSetItemValueColororg = NULL;
GAME_MultiboardSetItemValueColor GAME_MultiboardSetItemValueColorold = NULL;

void __cdecl GAME_MultiboardSetItemValueColormy( HMULTIBOARDITEM mbi , int red , int green , int blue , int alpha )
{
	fprintf_s( logfile , "%s" , "MultiboardSetItemValueColormy\n" );
	fflush( logfile );

	GAME_MultiboardSetItemValueColorold( mbi , red , green , blue , alpha );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardSetItemValueColor<--  mbi: %X red: %i green: %i blue: %i alpha: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , mbi , red , green , blue , alpha );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MultiboardSetItemWidth )( HMULTIBOARDITEM mbi , float *width );
GAME_MultiboardSetItemWidth GAME_MultiboardSetItemWidthorg = NULL;
GAME_MultiboardSetItemWidth GAME_MultiboardSetItemWidthold = NULL;

void __cdecl GAME_MultiboardSetItemWidthmy( HMULTIBOARDITEM mbi , float *width )
{
	fprintf_s( logfile , "%s\n" , "MultiboardSetItemWidthmy" );
	fflush( logfile );

	GAME_MultiboardSetItemWidthold( mbi , width );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardSetItemWidth<--  mbi: %X width: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , mbi , *( float * ) width );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MultiboardSetItemsIcon )( HMULTIBOARD lb , void * iconPath );
GAME_MultiboardSetItemsIcon GAME_MultiboardSetItemsIconorg = NULL;
GAME_MultiboardSetItemsIcon GAME_MultiboardSetItemsIconold = NULL;

void __cdecl GAME_MultiboardSetItemsIconmy( HMULTIBOARD lb , void * iconPath )
{
	fprintf_s( logfile , "%s\n" , "MultiboardSetItemsIconmy" );
	fflush( logfile );

	GAME_MultiboardSetItemsIconold( lb , iconPath );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardSetItemsIcon<--  lb: %X iconPath: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , jassgetchar( iconPath ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MultiboardSetItemsStyle )( HMULTIBOARD lb , BOOL showValues , BOOL showIcons );
GAME_MultiboardSetItemsStyle GAME_MultiboardSetItemsStyleorg = NULL;
GAME_MultiboardSetItemsStyle GAME_MultiboardSetItemsStyleold = NULL;

void __cdecl GAME_MultiboardSetItemsStylemy( HMULTIBOARD lb , BOOL showValues , BOOL showIcons )
{
	fprintf_s( logfile , "%s" , "MultiboardSetItemsStylemy\n" );
	fflush( logfile );

	GAME_MultiboardSetItemsStyleold( lb , showValues , showIcons );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardSetItemsStyle<--  lb: %X showValues: %s showIcons: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , showValues ? "TRUE\n" : "FALSE" , showIcons ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MultiboardSetItemsValue )( HMULTIBOARD lb , void * value );
GAME_MultiboardSetItemsValue GAME_MultiboardSetItemsValueorg = NULL;
GAME_MultiboardSetItemsValue GAME_MultiboardSetItemsValueold = NULL;

void __cdecl GAME_MultiboardSetItemsValuemy( HMULTIBOARD lb , void * value )
{
	fprintf_s( logfile , "%s" , "MultiboardSetItemsValuemy\n" );
	fflush( logfile );

	GAME_MultiboardSetItemsValueold( lb , value );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardSetItemsValue<--  lb: %X value: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , jassgetchar( value ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MultiboardSetItemsValueColor )( HMULTIBOARD lb , int red , int green , int blue , int alpha );
GAME_MultiboardSetItemsValueColor GAME_MultiboardSetItemsValueColororg = NULL;
GAME_MultiboardSetItemsValueColor GAME_MultiboardSetItemsValueColorold = NULL;

void __cdecl GAME_MultiboardSetItemsValueColormy( HMULTIBOARD lb , int red , int green , int blue , int alpha )
{
	fprintf_s( logfile , "%s" , "MultiboardSetItemsValueColormy\n" );
	fflush( logfile );

	GAME_MultiboardSetItemsValueColorold( lb , red , green , blue , alpha );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardSetItemsValueColor<--  lb: %X red: %i green: %i blue: %i alpha: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , red , green , blue , alpha );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MultiboardSetItemsWidth )( HMULTIBOARD lb , float *width );
GAME_MultiboardSetItemsWidth GAME_MultiboardSetItemsWidthorg = NULL;
GAME_MultiboardSetItemsWidth GAME_MultiboardSetItemsWidthold = NULL;

void __cdecl GAME_MultiboardSetItemsWidthmy( HMULTIBOARD lb , float *width )
{
	fprintf_s( logfile , "%s\n" , "MultiboardSetItemsWidthmy" );
	fflush( logfile );

	GAME_MultiboardSetItemsWidthold( lb , width );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardSetItemsWidth<--  lb: %X width: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , *( float * ) width );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MultiboardSetRowCount )( HMULTIBOARD lb , int count );
GAME_MultiboardSetRowCount GAME_MultiboardSetRowCountorg = NULL;
GAME_MultiboardSetRowCount GAME_MultiboardSetRowCountold = NULL;

void __cdecl GAME_MultiboardSetRowCountmy( HMULTIBOARD lb , int count )
{
	fprintf_s( logfile , "%s\n" , "MultiboardSetRowCountmy" );
	fflush( logfile );

	GAME_MultiboardSetRowCountold( lb , count );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardSetRowCount<--  lb: %X count: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , count );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MultiboardSetTitleText )( HMULTIBOARD lb , void * label );
GAME_MultiboardSetTitleText GAME_MultiboardSetTitleTextorg = NULL;
GAME_MultiboardSetTitleText GAME_MultiboardSetTitleTextold = NULL;

void __cdecl GAME_MultiboardSetTitleTextmy( HMULTIBOARD lb , void * label )
{
	fprintf_s( logfile , "%s\n" , "MultiboardSetTitleTextmy" );
	fflush( logfile );

	GAME_MultiboardSetTitleTextold( lb , label );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardSetTitleText<--  lb: %X label: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , jassgetchar( label ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MultiboardSetTitleTextColor )( HMULTIBOARD lb , int red , int green , int blue , int alpha );
GAME_MultiboardSetTitleTextColor GAME_MultiboardSetTitleTextColororg = NULL;
GAME_MultiboardSetTitleTextColor GAME_MultiboardSetTitleTextColorold = NULL;

void __cdecl GAME_MultiboardSetTitleTextColormy( HMULTIBOARD lb , int red , int green , int blue , int alpha )
{
	fprintf_s( logfile , "%s" , "MultiboardSetTitleTextColormy\n" );
	fflush( logfile );

	GAME_MultiboardSetTitleTextColorold( lb , red , green , blue , alpha );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardSetTitleTextColor<--  lb: %X red: %i green: %i blue: %i alpha: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , lb , red , green , blue , alpha );
	fflush( logfile );

}


typedef void( __cdecl *GAME_MultiboardSuppressDisplay )( BOOL flag );
GAME_MultiboardSuppressDisplay GAME_MultiboardSuppressDisplayorg = NULL;
GAME_MultiboardSuppressDisplay GAME_MultiboardSuppressDisplayold = NULL;

void __cdecl GAME_MultiboardSuppressDisplaymy( BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "MultiboardSuppressDisplaymy" );
	fflush( logfile );

	GAME_MultiboardSuppressDisplayold( flag );
	fprintf_s( logfile , "%s:[-->GAME_MultiboardSuppressDisplay<--  flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_NewSoundEnvironment )( void * environmentName );
GAME_NewSoundEnvironment GAME_NewSoundEnvironmentorg = NULL;
GAME_NewSoundEnvironment GAME_NewSoundEnvironmentold = NULL;

void __cdecl GAME_NewSoundEnvironmentmy( void * environmentName )
{
	fprintf_s( logfile , "%s" , "NewSoundEnvironmentmy\n" );
	fflush( logfile );

	GAME_NewSoundEnvironmentold( environmentName );
	fprintf_s( logfile , "%s:[-->GAME_NewSoundEnvironment<--  environmentName: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( environmentName ) );
	fflush( logfile );

}


typedef HBOOLEXPR( __cdecl *GAME_Not )( HBOOLEXPR operand );
GAME_Not GAME_Notorg = NULL;
GAME_Not GAME_Notold = NULL;

HBOOLEXPR __cdecl GAME_Notmy( HBOOLEXPR operand )
{
	fprintf_s( logfile , "%s" , "Notmy\n" );
	fflush( logfile );

	HBOOLEXPR retvalue = GAME_Notold( operand );
	fprintf_s( logfile , "%s:[-->GAME_Not<--  operand: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , operand , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HBOOLEXPR( __cdecl *GAME_Or )( HBOOLEXPR operandA , HBOOLEXPR operandB );
GAME_Or GAME_Ororg = NULL;
GAME_Or GAME_Orold = NULL;

HBOOLEXPR __cdecl GAME_Ormy( HBOOLEXPR operandA , HBOOLEXPR operandB )
{
	fprintf_s( logfile , "%s\n" , "Ormy" );
	fflush( logfile );

	HBOOLEXPR retvalue = GAME_Orold( operandA , operandB );
	fprintf_s( logfile , "%s:[-->GAME_Or<--  operandA: %X operandB: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , operandA , operandB , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_OrderId )( void * orderIdString );
GAME_OrderId GAME_OrderIdorg = NULL;
GAME_OrderId GAME_OrderIdold = NULL;

int __cdecl GAME_OrderIdmy( void * orderIdString )
{
	fprintf_s( logfile , "%s\n" , "OrderIdmy" );
	fflush( logfile );

	int retvalue = GAME_OrderIdold( orderIdString );
	fprintf_s( logfile , "%s:[-->GAME_OrderId<--  orderIdString: \"%s\"] RETURN-> %i\n" , currentDateTime( ).c_str( ) , jassgetchar( orderIdString ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_OrderId2String )( int orderId );
GAME_OrderId2String GAME_OrderId2Stringorg = NULL;
GAME_OrderId2String GAME_OrderId2Stringold = NULL;

DWORD __cdecl GAME_OrderId2Stringmy( int orderId )
{
	fprintf_s( logfile , "%s" , "OrderId2Stringmy\n" );
	fflush( logfile );

	DWORD retvalue = GAME_OrderId2Stringold( orderId );
	fprintf_s( logfile , "%s:[-->GAME_OrderId2String<--  orderId: %i] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , orderId , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_PanCameraTo )( float *x , float *y );
GAME_PanCameraTo GAME_PanCameraToorg = NULL;
GAME_PanCameraTo GAME_PanCameraToold = NULL;

void __cdecl GAME_PanCameraTomy( float *x , float *y )
{
	fprintf_s( logfile , "%s\n" , "PanCameraTomy" );
	fflush( logfile );

	GAME_PanCameraToold( x , y );
	fprintf_s( logfile , "%s:[-->GAME_PanCameraTo<--  x: %f y: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PanCameraToTimed )( float *x , float *y , float *duration );
GAME_PanCameraToTimed GAME_PanCameraToTimedorg = NULL;
GAME_PanCameraToTimed GAME_PanCameraToTimedold = NULL;

void __cdecl GAME_PanCameraToTimedmy( float *x , float *y , float *duration )
{
	fprintf_s( logfile , "%s\n" , "PanCameraToTimedmy" );
	fflush( logfile );

	GAME_PanCameraToTimedold( x , y , duration );
	fprintf_s( logfile , "%s:[-->GAME_PanCameraToTimed<--  x: %f y: %f duration: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , *( float * ) duration );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PanCameraToTimedWithZ )( float *x , float *y , float *zOffsetDest , float *duration );
GAME_PanCameraToTimedWithZ GAME_PanCameraToTimedWithZorg = NULL;
GAME_PanCameraToTimedWithZ GAME_PanCameraToTimedWithZold = NULL;

void __cdecl GAME_PanCameraToTimedWithZmy( float *x , float *y , float *zOffsetDest , float *duration )
{
	fprintf_s( logfile , "%s\n" , "PanCameraToTimedWithZmy" );
	fflush( logfile );

	GAME_PanCameraToTimedWithZold( x , y , zOffsetDest , duration );
	fprintf_s( logfile , "%s:[-->GAME_PanCameraToTimedWithZ<--  x: %f y: %f zOffsetDest: %f duration: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , *( float * ) zOffsetDest , *( float * ) duration );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PanCameraToWithZ )( float *x , float *y , float *zOffsetDest );
GAME_PanCameraToWithZ GAME_PanCameraToWithZorg = NULL;
GAME_PanCameraToWithZ GAME_PanCameraToWithZold = NULL;

void __cdecl GAME_PanCameraToWithZmy( float *x , float *y , float *zOffsetDest )
{
	fprintf_s( logfile , "%s\n" , "PanCameraToWithZmy" );
	fflush( logfile );

	GAME_PanCameraToWithZold( x , y , zOffsetDest );
	fprintf_s( logfile , "%s:[-->GAME_PanCameraToWithZ<--  x: %f y: %f zOffsetDest: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , *( float * ) zOffsetDest );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PauseCompAI )( HPLAYER p , BOOL pause );
GAME_PauseCompAI GAME_PauseCompAIorg = NULL;
GAME_PauseCompAI GAME_PauseCompAIold = NULL;

void __cdecl GAME_PauseCompAImy( HPLAYER p , BOOL pause )
{
	fprintf_s( logfile , "%s\n" , "PauseCompAImy" );
	fflush( logfile );

	GAME_PauseCompAIold( p , pause );
	fprintf_s( logfile , "%s:[-->GAME_PauseCompAI<--  p: %X pause: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , p , pause ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PauseGame )( BOOL flag );
GAME_PauseGame GAME_PauseGameorg = NULL;
GAME_PauseGame GAME_PauseGameold = NULL;

void __cdecl GAME_PauseGamemy( BOOL flag )
{
	fprintf_s( logfile , "%s" , "PauseGamemy\n" );
	fflush( logfile );

	GAME_PauseGameold( flag );
	fprintf_s( logfile , "%s:[-->GAME_PauseGame<--  flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PauseTimer )( HTIMER whichTimer );
GAME_PauseTimer GAME_PauseTimerorg = NULL;
GAME_PauseTimer GAME_PauseTimerold = NULL;

void __cdecl GAME_PauseTimermy( HTIMER whichTimer )
{
	fprintf_s( logfile , "%s" , "PauseTimermy\n" );
	fflush( logfile );

	GAME_PauseTimerold( whichTimer );
	fprintf_s( logfile , "%s:[-->GAME_PauseTimer<--  whichTimer: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichTimer );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PauseUnit )( HUNIT whichUnit , BOOL flag );
GAME_PauseUnit GAME_PauseUnitorg = NULL;
GAME_PauseUnit GAME_PauseUnitold = NULL;

void __cdecl GAME_PauseUnitmy( HUNIT whichUnit , BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "PauseUnitmy" );
	fflush( logfile );

	GAME_PauseUnitold( whichUnit , flag );
	fprintf_s( logfile , "%s:[-->GAME_PauseUnit<--  whichUnit: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PingMinimap )( float *x , float *y , float *duration );
GAME_PingMinimap GAME_PingMinimaporg = NULL;
GAME_PingMinimap GAME_PingMinimapold = NULL;

void __cdecl GAME_PingMinimapmy( float *x , float *y , float *duration )
{
	fprintf_s( logfile , "%s" , "PingMinimapmy\n" );
	fflush( logfile );

	GAME_PingMinimapold( x , y , duration );
	fprintf_s( logfile , "%s:[-->GAME_PingMinimap<--  x: %f y: %f duration: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , *( float * ) duration );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PingMinimapEx )( float *x , float *y , float *duration , int red , int green , int blue , BOOL extraEffects );
GAME_PingMinimapEx GAME_PingMinimapExorg = NULL;
GAME_PingMinimapEx GAME_PingMinimapExold = NULL;

void __cdecl GAME_PingMinimapExmy( float *x , float *y , float *duration , int red , int green , int blue , BOOL extraEffects )
{
	fprintf_s( logfile , "%s\n" , "PingMinimapExmy" );
	fflush( logfile );

	GAME_PingMinimapExold( x , y , duration , red , green , blue , extraEffects );
	fprintf_s( logfile , "%s:[-->GAME_PingMinimapEx<--  x: %f y: %f duration: %f red: %i green: %i blue: %i extraEffects: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , *( float * ) duration , red , green , blue , extraEffects ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef HITEM( __cdecl *GAME_PlaceRandomItem )( HITEMPOOL whichItemPool , float *x , float *y );
GAME_PlaceRandomItem GAME_PlaceRandomItemorg = NULL;
GAME_PlaceRandomItem GAME_PlaceRandomItemold = NULL;

HITEM __cdecl GAME_PlaceRandomItemmy( HITEMPOOL whichItemPool , float *x , float *y )
{
	fprintf_s( logfile , "%s" , "PlaceRandomItemmy\n" );
	fflush( logfile );

	HITEM retvalue = GAME_PlaceRandomItemold( whichItemPool , x , y );
	fprintf_s( logfile , "%s:[-->GAME_PlaceRandomItem<--  whichItemPool: %X x: %f y: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichItemPool , *( float * ) x , *( float * ) y , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HUNIT( __cdecl *GAME_PlaceRandomUnit )( HUNITPOOL whichPool , HPLAYER forWhichPlayer , float *x , float *y , float *facing );
GAME_PlaceRandomUnit GAME_PlaceRandomUnitorg = NULL;
GAME_PlaceRandomUnit GAME_PlaceRandomUnitold = NULL;

HUNIT __cdecl GAME_PlaceRandomUnitmy( HUNITPOOL whichPool , HPLAYER forWhichPlayer , float *x , float *y , float *facing )
{
	fprintf_s( logfile , "%s\n" , "PlaceRandomUnitmy" );
	fflush( logfile );

	HUNIT retvalue = GAME_PlaceRandomUnitold( whichPool , forWhichPlayer , x , y , facing );
	fprintf_s( logfile , "%s:[-->GAME_PlaceRandomUnit<--  whichPool: %X forWhichPlayer: %X x: %f y: %f facing: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichPool , forWhichPlayer , *( float * ) x , *( float * ) y , *( float * ) facing , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_PlayCinematic )( void * movieName );
GAME_PlayCinematic GAME_PlayCinematicorg = NULL;
GAME_PlayCinematic GAME_PlayCinematicold = NULL;

void __cdecl GAME_PlayCinematicmy( void * movieName )
{
	fprintf_s( logfile , "%s\n" , "PlayCinematicmy" );
	fflush( logfile );

	GAME_PlayCinematicold( movieName );
	fprintf_s( logfile , "%s:[-->GAME_PlayCinematic<--  movieName: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( movieName ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PlayModelCinematic )( void * modelName );
GAME_PlayModelCinematic GAME_PlayModelCinematicorg = NULL;
GAME_PlayModelCinematic GAME_PlayModelCinematicold = NULL;

void __cdecl GAME_PlayModelCinematicmy( void * modelName )
{
	fprintf_s( logfile , "%s" , "PlayModelCinematicmy\n" );
	fflush( logfile );

	GAME_PlayModelCinematicold( modelName );
	fprintf_s( logfile , "%s:[-->GAME_PlayModelCinematic<--  modelName: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( modelName ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PlayMusic )( void * musicName );
GAME_PlayMusic GAME_PlayMusicorg = NULL;
GAME_PlayMusic GAME_PlayMusicold = NULL;

void __cdecl GAME_PlayMusicmy( void * musicName )
{
	fprintf_s( logfile , "%s" , "PlayMusicmy\n" );
	fflush( logfile );

	GAME_PlayMusicold( musicName );
	fprintf_s( logfile , "%s:[-->GAME_PlayMusic<--  musicName: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( musicName ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PlayMusicEx )( void * musicName , int frommsecs , int fadeinmsecs );
GAME_PlayMusicEx GAME_PlayMusicExorg = NULL;
GAME_PlayMusicEx GAME_PlayMusicExold = NULL;

void __cdecl GAME_PlayMusicExmy( void * musicName , int frommsecs , int fadeinmsecs )
{
	fprintf_s( logfile , "%s" , "PlayMusicExmy\n" );
	fflush( logfile );

	GAME_PlayMusicExold( musicName , frommsecs , fadeinmsecs );
	fprintf_s( logfile , "%s:[-->GAME_PlayMusicEx<--  musicName: \"%s\" frommsecs: %i fadeinmsecs: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( musicName ) , frommsecs , fadeinmsecs );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PlayThematicMusic )( void * musicFileName );
GAME_PlayThematicMusic GAME_PlayThematicMusicorg = NULL;
GAME_PlayThematicMusic GAME_PlayThematicMusicold = NULL;

void __cdecl GAME_PlayThematicMusicmy( void * musicFileName )
{
	fprintf_s( logfile , "%s" , "PlayThematicMusicmy\n" );
	fflush( logfile );

	GAME_PlayThematicMusicold( musicFileName );
	fprintf_s( logfile , "%s:[-->GAME_PlayThematicMusic<--  musicFileName: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( musicFileName ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PlayThematicMusicEx )( void * musicFileName , int frommsecs );
GAME_PlayThematicMusicEx GAME_PlayThematicMusicExorg = NULL;
GAME_PlayThematicMusicEx GAME_PlayThematicMusicExold = NULL;

void __cdecl GAME_PlayThematicMusicExmy( void * musicFileName , int frommsecs )
{
	fprintf_s( logfile , "%s" , "PlayThematicMusicExmy\n" );
	fflush( logfile );

	GAME_PlayThematicMusicExold( musicFileName , frommsecs );
	fprintf_s( logfile , "%s:[-->GAME_PlayThematicMusicEx<--  musicFileName: \"%s\" frommsecs: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( musicFileName ) , frommsecs );
	fflush( logfile );

}


typedef HPLAYER( __cdecl *GAME_Player )( int number );
GAME_Player GAME_Playerorg = NULL;
GAME_Player GAME_Playerold = NULL;

HPLAYER __cdecl GAME_Playermy( int number )
{
	fprintf_s( logfile , "%s" , "Playermy\n" );
	fflush( logfile );

	HPLAYER retvalue = GAME_Playerold( number );
	fprintf_s( logfile , "%s:[-->GAME_Player<--  number: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , number , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HLEADERBOARD( __cdecl *GAME_PlayerGetLeaderboard )( HPLAYER toPlayer );
GAME_PlayerGetLeaderboard GAME_PlayerGetLeaderboardorg = NULL;
GAME_PlayerGetLeaderboard GAME_PlayerGetLeaderboardold = NULL;

HLEADERBOARD __cdecl GAME_PlayerGetLeaderboardmy( HPLAYER toPlayer )
{
	fprintf_s( logfile , "%s\n" , "PlayerGetLeaderboardmy" );
	fflush( logfile );

	HLEADERBOARD retvalue = GAME_PlayerGetLeaderboardold( toPlayer );
	fprintf_s( logfile , "%s:[-->GAME_PlayerGetLeaderboard<--  toPlayer: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , toPlayer , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_PlayerSetLeaderboard )( HPLAYER toPlayer , HLEADERBOARD lb );
GAME_PlayerSetLeaderboard GAME_PlayerSetLeaderboardorg = NULL;
GAME_PlayerSetLeaderboard GAME_PlayerSetLeaderboardold = NULL;

void __cdecl GAME_PlayerSetLeaderboardmy( HPLAYER toPlayer , HLEADERBOARD lb )
{
	fprintf_s( logfile , "%s\n" , "PlayerSetLeaderboardmy" );
	fflush( logfile );

	GAME_PlayerSetLeaderboardold( toPlayer , lb );
	fprintf_s( logfile , "%s:[-->GAME_PlayerSetLeaderboard<--  toPlayer: %X lb: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , toPlayer , lb );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PopLastCommand )( );
GAME_PopLastCommand GAME_PopLastCommandorg = NULL;
GAME_PopLastCommand GAME_PopLastCommandold = NULL;

void __cdecl GAME_PopLastCommandmy( )
{
	fprintf_s( logfile , "%s\n" , "PopLastCommandmy" );
	fflush( logfile );

	GAME_PopLastCommandold( );
	fprintf_s( logfile , "%s:[-->GAME_PopLastCommand<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef DWFP( __cdecl *GAME_Pow )( float *x , float *power );
GAME_Pow GAME_Poworg = NULL;
GAME_Pow GAME_Powold = NULL;

DWFP __cdecl GAME_Powmy( float *x , float *power )
{
	fprintf_s( logfile , "%s\n" , "Powmy" );
	fflush( logfile );

	DWFP retvalue = GAME_Powold( x , power );
	fprintf_s( logfile , "%s:[-->GAME_Pow<--  x: %f power: %f] RETURN-> %f\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) power , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_Preload )( void * filename );
GAME_Preload GAME_Preloadorg = NULL;
GAME_Preload GAME_Preloadold = NULL;

void __cdecl GAME_Preloadmy( void * filename )
{
	fprintf_s( logfile , "%s\n" , "Preloadmy" );
	fflush( logfile );

	GAME_Preloadold( filename );
	fprintf_s( logfile , "%s:[-->GAME_Preload<--  filename: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( filename ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PreloadEnd )( float *timeout );
GAME_PreloadEnd GAME_PreloadEndorg = NULL;
GAME_PreloadEnd GAME_PreloadEndold = NULL;

void __cdecl GAME_PreloadEndmy( float *timeout )
{
	fprintf_s( logfile , "%s" , "PreloadEndmy\n" );
	fflush( logfile );

	GAME_PreloadEndold( timeout );
	fprintf_s( logfile , "%s:[-->GAME_PreloadEnd<--  timeout: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) timeout );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PreloadEndEx )( );
GAME_PreloadEndEx GAME_PreloadEndExorg = NULL;
GAME_PreloadEndEx GAME_PreloadEndExold = NULL;

void __cdecl GAME_PreloadEndExmy( )
{
	fprintf_s( logfile , "%s\n" , "PreloadEndExmy" );
	fflush( logfile );

	GAME_PreloadEndExold( );
	fprintf_s( logfile , "%s:[-->GAME_PreloadEndEx<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PreloadGenClear )( );
GAME_PreloadGenClear GAME_PreloadGenClearorg = NULL;
GAME_PreloadGenClear GAME_PreloadGenClearold = NULL;

void __cdecl GAME_PreloadGenClearmy( )
{
	fprintf_s( logfile , "%s\n" , "PreloadGenClearmy" );
	fflush( logfile );

	GAME_PreloadGenClearold( );
	fprintf_s( logfile , "%s:[-->GAME_PreloadGenClear<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PreloadGenEnd )( void * filename );
GAME_PreloadGenEnd GAME_PreloadGenEndorg = NULL;
GAME_PreloadGenEnd GAME_PreloadGenEndold = NULL;

void __cdecl GAME_PreloadGenEndmy( void * filename )
{
	fprintf_s( logfile , "%s\n" , "PreloadGenEndmy" );
	fflush( logfile );

	GAME_PreloadGenEndold( filename );
	fprintf_s( logfile , "%s:[-->GAME_PreloadGenEnd<--  filename: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( filename ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PreloadGenStart )( );
GAME_PreloadGenStart GAME_PreloadGenStartorg = NULL;
GAME_PreloadGenStart GAME_PreloadGenStartold = NULL;

void __cdecl GAME_PreloadGenStartmy( )
{
	fprintf_s( logfile , "%s" , "PreloadGenStartmy\n" );
	fflush( logfile );

	GAME_PreloadGenStartold( );
	fprintf_s( logfile , "%s:[-->GAME_PreloadGenStart<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PreloadRefresh )( );
GAME_PreloadRefresh GAME_PreloadRefreshorg = NULL;
GAME_PreloadRefresh GAME_PreloadRefreshold = NULL;

void __cdecl GAME_PreloadRefreshmy( )
{
	fprintf_s( logfile , "%s\n" , "PreloadRefreshmy" );
	fflush( logfile );

	GAME_PreloadRefreshold( );
	fprintf_s( logfile , "%s:[-->GAME_PreloadRefresh<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PreloadStart )( );
GAME_PreloadStart GAME_PreloadStartorg = NULL;
GAME_PreloadStart GAME_PreloadStartold = NULL;

void __cdecl GAME_PreloadStartmy( )
{
	fprintf_s( logfile , "%s\n" , "PreloadStartmy" );
	fflush( logfile );

	GAME_PreloadStartold( );
	fprintf_s( logfile , "%s:[-->GAME_PreloadStart<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_Preloader )( void * filename );
GAME_Preloader GAME_Preloaderorg = NULL;
GAME_Preloader GAME_Preloaderold = NULL;

void __cdecl GAME_Preloadermy( void * filename )
{
	fprintf_s( logfile , "%s\n" , "Preloadermy" );
	fflush( logfile );

	GAME_Preloaderold( filename );
	fprintf_s( logfile , "%s:[-->GAME_Preloader<--  filename: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( filename ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_PurchaseZeppelin )( );
GAME_PurchaseZeppelin GAME_PurchaseZeppelinorg = NULL;
GAME_PurchaseZeppelin GAME_PurchaseZeppelinold = NULL;

void __cdecl GAME_PurchaseZeppelinmy( )
{
	fprintf_s( logfile , "%s" , "PurchaseZeppelinmy\n" );
	fflush( logfile );

	GAME_PurchaseZeppelinold( );
	fprintf_s( logfile , "%s:[-->GAME_PurchaseZeppelin<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef HQUESTITEM( __cdecl *GAME_QuestCreateItem )( HQUEST whichQuest );
GAME_QuestCreateItem GAME_QuestCreateItemorg = NULL;
GAME_QuestCreateItem GAME_QuestCreateItemold = NULL;

HQUESTITEM __cdecl GAME_QuestCreateItemmy( HQUEST whichQuest )
{
	fprintf_s( logfile , "%s\n" , "QuestCreateItemmy" );
	fflush( logfile );

	HQUESTITEM retvalue = GAME_QuestCreateItemold( whichQuest );
	fprintf_s( logfile , "%s:[-->GAME_QuestCreateItem<--  whichQuest: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichQuest , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_QuestItemSetCompleted )( HQUESTITEM whichQuestItem , BOOL completed );
GAME_QuestItemSetCompleted GAME_QuestItemSetCompletedorg = NULL;
GAME_QuestItemSetCompleted GAME_QuestItemSetCompletedold = NULL;

void __cdecl GAME_QuestItemSetCompletedmy( HQUESTITEM whichQuestItem , BOOL completed )
{
	fprintf_s( logfile , "%s\n" , "QuestItemSetCompletedmy" );
	fflush( logfile );

	GAME_QuestItemSetCompletedold( whichQuestItem , completed );
	fprintf_s( logfile , "%s:[-->GAME_QuestItemSetCompleted<--  whichQuestItem: %X completed: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichQuestItem , completed ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_QuestItemSetDescription )( HQUESTITEM whichQuestItem , void * description );
GAME_QuestItemSetDescription GAME_QuestItemSetDescriptionorg = NULL;
GAME_QuestItemSetDescription GAME_QuestItemSetDescriptionold = NULL;

void __cdecl GAME_QuestItemSetDescriptionmy( HQUESTITEM whichQuestItem , void * description )
{
	fprintf_s( logfile , "%s" , "QuestItemSetDescriptionmy\n" );
	fflush( logfile );

	GAME_QuestItemSetDescriptionold( whichQuestItem , description );
	fprintf_s( logfile , "%s:[-->GAME_QuestItemSetDescription<--  whichQuestItem: %X description: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichQuestItem , jassgetchar( description ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_QuestSetCompleted )( HQUEST whichQuest , BOOL completed );
GAME_QuestSetCompleted GAME_QuestSetCompletedorg = NULL;
GAME_QuestSetCompleted GAME_QuestSetCompletedold = NULL;

void __cdecl GAME_QuestSetCompletedmy( HQUEST whichQuest , BOOL completed )
{
	fprintf_s( logfile , "%s" , "QuestSetCompletedmy\n" );
	fflush( logfile );

	GAME_QuestSetCompletedold( whichQuest , completed );
	fprintf_s( logfile , "%s:[-->GAME_QuestSetCompleted<--  whichQuest: %X completed: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichQuest , completed ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_QuestSetDescription )( HQUEST whichQuest , void * description );
GAME_QuestSetDescription GAME_QuestSetDescriptionorg = NULL;
GAME_QuestSetDescription GAME_QuestSetDescriptionold = NULL;

void __cdecl GAME_QuestSetDescriptionmy( HQUEST whichQuest , void * description )
{
	fprintf_s( logfile , "%s" , "QuestSetDescriptionmy\n" );
	fflush( logfile );

	GAME_QuestSetDescriptionold( whichQuest , description );
	fprintf_s( logfile , "%s:[-->GAME_QuestSetDescription<--  whichQuest: %X description: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichQuest , jassgetchar( description ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_QuestSetDiscovered )( HQUEST whichQuest , BOOL discovered );
GAME_QuestSetDiscovered GAME_QuestSetDiscoveredorg = NULL;
GAME_QuestSetDiscovered GAME_QuestSetDiscoveredold = NULL;

void __cdecl GAME_QuestSetDiscoveredmy( HQUEST whichQuest , BOOL discovered )
{
	fprintf_s( logfile , "%s" , "QuestSetDiscoveredmy\n" );
	fflush( logfile );

	GAME_QuestSetDiscoveredold( whichQuest , discovered );
	fprintf_s( logfile , "%s:[-->GAME_QuestSetDiscovered<--  whichQuest: %X discovered: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichQuest , discovered ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_QuestSetEnabled )( HQUEST whichQuest , BOOL enabled );
GAME_QuestSetEnabled GAME_QuestSetEnabledorg = NULL;
GAME_QuestSetEnabled GAME_QuestSetEnabledold = NULL;

void __cdecl GAME_QuestSetEnabledmy( HQUEST whichQuest , BOOL enabled )
{
	fprintf_s( logfile , "%s" , "QuestSetEnabledmy\n" );
	fflush( logfile );

	GAME_QuestSetEnabledold( whichQuest , enabled );
	fprintf_s( logfile , "%s:[-->GAME_QuestSetEnabled<--  whichQuest: %X enabled: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichQuest , enabled ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_QuestSetFailed )( HQUEST whichQuest , BOOL failed );
GAME_QuestSetFailed GAME_QuestSetFailedorg = NULL;
GAME_QuestSetFailed GAME_QuestSetFailedold = NULL;

void __cdecl GAME_QuestSetFailedmy( HQUEST whichQuest , BOOL failed )
{
	fprintf_s( logfile , "%s" , "QuestSetFailedmy\n" );
	fflush( logfile );

	GAME_QuestSetFailedold( whichQuest , failed );
	fprintf_s( logfile , "%s:[-->GAME_QuestSetFailed<--  whichQuest: %X failed: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichQuest , failed ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_QuestSetIconPath )( HQUEST whichQuest , void * iconPath );
GAME_QuestSetIconPath GAME_QuestSetIconPathorg = NULL;
GAME_QuestSetIconPath GAME_QuestSetIconPathold = NULL;

void __cdecl GAME_QuestSetIconPathmy( HQUEST whichQuest , void * iconPath )
{
	fprintf_s( logfile , "%s" , "QuestSetIconPathmy\n" );
	fflush( logfile );

	GAME_QuestSetIconPathold( whichQuest , iconPath );
	fprintf_s( logfile , "%s:[-->GAME_QuestSetIconPath<--  whichQuest: %X iconPath: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichQuest , jassgetchar( iconPath ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_QuestSetRequired )( HQUEST whichQuest , BOOL required );
GAME_QuestSetRequired GAME_QuestSetRequiredorg = NULL;
GAME_QuestSetRequired GAME_QuestSetRequiredold = NULL;

void __cdecl GAME_QuestSetRequiredmy( HQUEST whichQuest , BOOL required )
{
	fprintf_s( logfile , "%s" , "QuestSetRequiredmy\n" );
	fflush( logfile );

	GAME_QuestSetRequiredold( whichQuest , required );
	fprintf_s( logfile , "%s:[-->GAME_QuestSetRequired<--  whichQuest: %X required: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichQuest , required ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_QuestSetTitle )( HQUEST whichQuest , void * title );
GAME_QuestSetTitle GAME_QuestSetTitleorg = NULL;
GAME_QuestSetTitle GAME_QuestSetTitleold = NULL;

void __cdecl GAME_QuestSetTitlemy( HQUEST whichQuest , void * title )
{
	fprintf_s( logfile , "%s" , "QuestSetTitlemy\n" );
	fflush( logfile );

	GAME_QuestSetTitleold( whichQuest , title );
	fprintf_s( logfile , "%s:[-->GAME_QuestSetTitle<--  whichQuest: %X title: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichQuest , jassgetchar( title ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_QueueDestructableAnimation )( HDESTRUCTABLE d , void * whichAnimation );
GAME_QueueDestructableAnimation GAME_QueueDestructableAnimationorg = NULL;
GAME_QueueDestructableAnimation GAME_QueueDestructableAnimationold = NULL;

void __cdecl GAME_QueueDestructableAnimationmy( HDESTRUCTABLE d , void * whichAnimation )
{
	fprintf_s( logfile , "%s" , "QueueDestructableAnimationmy\n" );
	fflush( logfile );

	GAME_QueueDestructableAnimationold( d , whichAnimation );
	fprintf_s( logfile , "%s:[-->GAME_QueueDestructableAnimation<--  d: %X whichAnimation: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , d , jassgetchar( whichAnimation ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_QueueUnitAnimation )( HUNIT whichUnit , void * whichAnimation );
GAME_QueueUnitAnimation GAME_QueueUnitAnimationorg = NULL;
GAME_QueueUnitAnimation GAME_QueueUnitAnimationold = NULL;

void __cdecl GAME_QueueUnitAnimationmy( HUNIT whichUnit , void * whichAnimation )
{
	fprintf_s( logfile , "%s" , "QueueUnitAnimationmy\n" );
	fflush( logfile );

	GAME_QueueUnitAnimationold( whichUnit , whichAnimation );
	fprintf_s( logfile , "%s:[-->GAME_QueueUnitAnimation<--  whichUnit: %X whichAnimation: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , jassgetchar( whichAnimation ) );
	fflush( logfile );

}


typedef int( __cdecl *GAME_R2I )( float *r );
GAME_R2I GAME_R2Iorg = NULL;
GAME_R2I GAME_R2Iold = NULL;

int __cdecl GAME_R2Imy( float *r )
{
	fprintf_s( logfile , "%s" , "R2Imy\n" );
	fflush( logfile );

	int retvalue = GAME_R2Iold( r );
	fprintf_s( logfile , "%s:[-->GAME_R2I<--  r: %f] RETURN-> %i\n" , currentDateTime( ).c_str( ) , *( float * ) r , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_R2S )( float *r );
GAME_R2S GAME_R2Sorg = NULL;
GAME_R2S GAME_R2Sold = NULL;

DWORD __cdecl GAME_R2Smy( float *r )
{
	fprintf_s( logfile , "%s\n" , "R2Smy" );
	fflush( logfile );

	DWORD retvalue = GAME_R2Sold( r );
	fprintf_s( logfile , "%s:[-->GAME_R2S<--  r: %f] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , *( float * ) r , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_R2SW )( float *r , int width , int precision );
GAME_R2SW GAME_R2SWorg = NULL;
GAME_R2SW GAME_R2SWold = NULL;

DWORD __cdecl GAME_R2SWmy( float *r , int width , int precision )
{
	fprintf_s( logfile , "%s\n" , "R2SWmy" );
	fflush( logfile );

	DWORD retvalue = GAME_R2SWold( r , width , precision );
	fprintf_s( logfile , "%s:[-->GAME_R2SW<--  r: %f width: %i precision: %i] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , *( float * ) r , width , precision , DoTheMagic(retvalue) );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_Rad2Deg )( float *radians );
GAME_Rad2Deg GAME_Rad2Degorg = NULL;
GAME_Rad2Deg GAME_Rad2Degold = NULL;

DWFP __cdecl GAME_Rad2Degmy( float *radians )
{
	fprintf_s( logfile , "%s\n" , "Rad2Degmy" );
	fflush( logfile );

	DWFP retvalue = GAME_Rad2Degold( radians );
	fprintf_s( logfile , "%s:[-->GAME_Rad2Deg<--  radians: %f] RETURN-> %f\n" , currentDateTime( ).c_str( ) , *( float * ) radians , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef HRECT( __cdecl *GAME_Rect )( float *minx , float *miny , float *maxx , float *maxy );
GAME_Rect GAME_Rectorg = NULL;
GAME_Rect GAME_Rectold = NULL;

HRECT __cdecl GAME_Rectmy( float *minx , float *miny , float *maxx , float *maxy )
{
	fprintf_s( logfile , "%s\n" , "Rectmy" );
	fflush( logfile );

	HRECT retvalue = GAME_Rectold( minx , miny , maxx , maxy );
	fprintf_s( logfile , "%s:[-->GAME_Rect<--  minx: %f miny: %f maxx: %f maxy: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , *( float * ) minx , *( float * ) miny , *( float * ) maxx , *( float * ) maxy , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HRECT( __cdecl *GAME_RectFromLoc )( HLOCATION min , HLOCATION max );
GAME_RectFromLoc GAME_RectFromLocorg = NULL;
GAME_RectFromLoc GAME_RectFromLocold = NULL;

HRECT __cdecl GAME_RectFromLocmy( HLOCATION min , HLOCATION max )
{
	fprintf_s( logfile , "%s\n" , "RectFromLocmy" );
	fflush( logfile );

	HRECT retvalue = GAME_RectFromLocold( min , max );
	fprintf_s( logfile , "%s:[-->GAME_RectFromLoc<--  min: %X max: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , min , max , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_RecycleGuardPosition )( HUNIT hUnit );
GAME_RecycleGuardPosition GAME_RecycleGuardPositionorg = NULL;
GAME_RecycleGuardPosition GAME_RecycleGuardPositionold = NULL;

void __cdecl GAME_RecycleGuardPositionmy( HUNIT hUnit )
{
	fprintf_s( logfile , "%s\n" , "RecycleGuardPositionmy" );
	fflush( logfile );

	GAME_RecycleGuardPositionold( hUnit );
	fprintf_s( logfile , "%s:[-->GAME_RecycleGuardPosition<--  hUnit: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , hUnit );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RegionAddCell )( HREGION whichRegion , float *x , float *y );
GAME_RegionAddCell GAME_RegionAddCellorg = NULL;
GAME_RegionAddCell GAME_RegionAddCellold = NULL;

void __cdecl GAME_RegionAddCellmy( HREGION whichRegion , float *x , float *y )
{
	fprintf_s( logfile , "%s\n" , "RegionAddCellmy" );
	fflush( logfile );

	GAME_RegionAddCellold( whichRegion , x , y );
	fprintf_s( logfile , "%s:[-->GAME_RegionAddCell<--  whichRegion: %X x: %f y: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichRegion , *( float * ) x , *( float * ) y );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RegionAddCellAtLoc )( HREGION whichRegion , HLOCATION whichLocation );
GAME_RegionAddCellAtLoc GAME_RegionAddCellAtLocorg = NULL;
GAME_RegionAddCellAtLoc GAME_RegionAddCellAtLocold = NULL;

void __cdecl GAME_RegionAddCellAtLocmy( HREGION whichRegion , HLOCATION whichLocation )
{
	fprintf_s( logfile , "%s\n" , "RegionAddCellAtLocmy" );
	fflush( logfile );

	GAME_RegionAddCellAtLocold( whichRegion , whichLocation );
	fprintf_s( logfile , "%s:[-->GAME_RegionAddCellAtLoc<--  whichRegion: %X whichLocation: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichRegion , whichLocation );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RegionAddRect )( HREGION whichRegion , HRECT r );
GAME_RegionAddRect GAME_RegionAddRectorg = NULL;
GAME_RegionAddRect GAME_RegionAddRectold = NULL;

void __cdecl GAME_RegionAddRectmy( HREGION whichRegion , HRECT r )
{
	fprintf_s( logfile , "%s\n" , "RegionAddRectmy" );
	fflush( logfile );

	GAME_RegionAddRectold( whichRegion , r );
	fprintf_s( logfile , "%s:[-->GAME_RegionAddRect<--  whichRegion: %X r: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichRegion , r );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RegionClearCell )( HREGION whichRegion , float *x , float *y );
GAME_RegionClearCell GAME_RegionClearCellorg = NULL;
GAME_RegionClearCell GAME_RegionClearCellold = NULL;

void __cdecl GAME_RegionClearCellmy( HREGION whichRegion , float *x , float *y )
{
	fprintf_s( logfile , "%s\n" , "RegionClearCellmy" );
	fflush( logfile );

	GAME_RegionClearCellold( whichRegion , x , y );
	fprintf_s( logfile , "%s:[-->GAME_RegionClearCell<--  whichRegion: %X x: %f y: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichRegion , *( float * ) x , *( float * ) y );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RegionClearCellAtLoc )( HREGION whichRegion , HLOCATION whichLocation );
GAME_RegionClearCellAtLoc GAME_RegionClearCellAtLocorg = NULL;
GAME_RegionClearCellAtLoc GAME_RegionClearCellAtLocold = NULL;

void __cdecl GAME_RegionClearCellAtLocmy( HREGION whichRegion , HLOCATION whichLocation )
{
	fprintf_s( logfile , "%s\n" , "RegionClearCellAtLocmy" );
	fflush( logfile );

	GAME_RegionClearCellAtLocold( whichRegion , whichLocation );
	fprintf_s( logfile , "%s:[-->GAME_RegionClearCellAtLoc<--  whichRegion: %X whichLocation: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichRegion , whichLocation );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RegionClearRect )( HREGION whichRegion , HRECT r );
GAME_RegionClearRect GAME_RegionClearRectorg = NULL;
GAME_RegionClearRect GAME_RegionClearRectold = NULL;

void __cdecl GAME_RegionClearRectmy( HREGION whichRegion , HRECT r )
{
	fprintf_s( logfile , "%s\n" , "RegionClearRectmy" );
	fflush( logfile );

	GAME_RegionClearRectold( whichRegion , r );
	fprintf_s( logfile , "%s:[-->GAME_RegionClearRect<--  whichRegion: %X r: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichRegion , r );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RegisterStackedSound )( HSOUND soundHandle , BOOL byPosition , float *rectwidth , float *rectheight );
GAME_RegisterStackedSound GAME_RegisterStackedSoundorg = NULL;
GAME_RegisterStackedSound GAME_RegisterStackedSoundold = NULL;

void __cdecl GAME_RegisterStackedSoundmy( HSOUND soundHandle , BOOL byPosition , float *rectwidth , float *rectheight )
{
	fprintf_s( logfile , "%s\n" , "RegisterStackedSoundmy" );
	fflush( logfile );

	GAME_RegisterStackedSoundold( soundHandle , byPosition , rectwidth , rectheight );
	fprintf_s( logfile , "%s:[-->GAME_RegisterStackedSound<--  soundHandle: %X byPosition: %s rectwidth: %f rectheight: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , soundHandle , byPosition ? "TRUE\n" : "FALSE" , *( float * ) rectwidth , *( float * ) rectheight );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ReloadGame )( );
GAME_ReloadGame GAME_ReloadGameorg = NULL;
GAME_ReloadGame GAME_ReloadGameold = NULL;

void __cdecl GAME_ReloadGamemy( )
{
	fprintf_s( logfile , "%s" , "ReloadGamemy\n" );
	fflush( logfile );

	GAME_ReloadGameold( );
	fprintf_s( logfile , "%s:[-->GAME_ReloadGame<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_ReloadGameCachesFromDisk )( );
GAME_ReloadGameCachesFromDisk GAME_ReloadGameCachesFromDiskorg = NULL;
GAME_ReloadGameCachesFromDisk GAME_ReloadGameCachesFromDiskold = NULL;

BOOL __cdecl GAME_ReloadGameCachesFromDiskmy( )
{
	fprintf_s( logfile , "%s\n" , "ReloadGameCachesFromDiskmy" );
	fflush( logfile );

	BOOL retvalue = GAME_ReloadGameCachesFromDiskold( );
	fprintf_s( logfile , "%s:[-->GAME_ReloadGameCachesFromDisk<-- ] RETURN-> %s\n" , currentDateTime( ).c_str( ) , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_RemoveAllGuardPositions )( HPLAYER num );
GAME_RemoveAllGuardPositions GAME_RemoveAllGuardPositionsorg = NULL;
GAME_RemoveAllGuardPositions GAME_RemoveAllGuardPositionsold = NULL;

void __cdecl GAME_RemoveAllGuardPositionsmy( HPLAYER num )
{
	fprintf_s( logfile , "%s" , "RemoveAllGuardPositionsmy\n" );
	fflush( logfile );

	GAME_RemoveAllGuardPositionsold( num );
	fprintf_s( logfile , "%s:[-->GAME_RemoveAllGuardPositions<--  num: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , num );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemoveDestructable )( HDESTRUCTABLE d );
GAME_RemoveDestructable GAME_RemoveDestructableorg = NULL;
GAME_RemoveDestructable GAME_RemoveDestructableold = NULL;

void __cdecl GAME_RemoveDestructablemy( HDESTRUCTABLE d )
{
	fprintf_s( logfile , "%s\n" , "RemoveDestructablemy" );
	fflush( logfile );

	GAME_RemoveDestructableold( d );
	fprintf_s( logfile , "%s:[-->GAME_RemoveDestructable<--  d: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , d );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemoveGuardPosition )( HUNIT hUnit );
GAME_RemoveGuardPosition GAME_RemoveGuardPositionorg = NULL;
GAME_RemoveGuardPosition GAME_RemoveGuardPositionold = NULL;

void __cdecl GAME_RemoveGuardPositionmy( HUNIT hUnit )
{
	fprintf_s( logfile , "%s\n" , "RemoveGuardPositionmy" );
	fflush( logfile );

	GAME_RemoveGuardPositionold( hUnit );
	fprintf_s( logfile , "%s:[-->GAME_RemoveGuardPosition<--  hUnit: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , hUnit );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemoveInjuries )( );
GAME_RemoveInjuries GAME_RemoveInjuriesorg = NULL;
GAME_RemoveInjuries GAME_RemoveInjuriesold = NULL;

void __cdecl GAME_RemoveInjuriesmy( )
{
	fprintf_s( logfile , "%s\n" , "RemoveInjuriesmy" );
	fflush( logfile );

	GAME_RemoveInjuriesold( );
	fprintf_s( logfile , "%s:[-->GAME_RemoveInjuries<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemoveItem )( HITEM whichItem );
GAME_RemoveItem GAME_RemoveItemorg = NULL;
GAME_RemoveItem GAME_RemoveItemold = NULL;

void __cdecl GAME_RemoveItemmy( HITEM whichItem )
{
	fprintf_s( logfile , "%s\n" , "RemoveItemmy" );
	fflush( logfile );

	GAME_RemoveItemold( whichItem );
	fprintf_s( logfile , "%s:[-->GAME_RemoveItem<--  whichItem: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichItem );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemoveItemFromAllStock )( int itemId );
GAME_RemoveItemFromAllStock GAME_RemoveItemFromAllStockorg = NULL;
GAME_RemoveItemFromAllStock GAME_RemoveItemFromAllStockold = NULL;

void __cdecl GAME_RemoveItemFromAllStockmy( int itemId )
{
	fprintf_s( logfile , "%s\n" , "RemoveItemFromAllStockmy" );
	fflush( logfile );

	GAME_RemoveItemFromAllStockold( itemId );
	fprintf_s( logfile , "%s:[-->GAME_RemoveItemFromAllStock<--  itemId: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , itemId );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemoveItemFromStock )( HUNIT whichUnit , int itemId );
GAME_RemoveItemFromStock GAME_RemoveItemFromStockorg = NULL;
GAME_RemoveItemFromStock GAME_RemoveItemFromStockold = NULL;

void __cdecl GAME_RemoveItemFromStockmy( HUNIT whichUnit , int itemId )
{
	fprintf_s( logfile , "%s\n" , "RemoveItemFromStockmy" );
	fflush( logfile );

	GAME_RemoveItemFromStockold( whichUnit , itemId );
	fprintf_s( logfile , "%s:[-->GAME_RemoveItemFromStock<--  whichUnit: %X itemId: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , itemId );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemoveLocation )( HLOCATION whichLocation );
GAME_RemoveLocation GAME_RemoveLocationorg = NULL;
GAME_RemoveLocation GAME_RemoveLocationold = NULL;

void __cdecl GAME_RemoveLocationmy( HLOCATION whichLocation )
{
	fprintf_s( logfile , "%s\n" , "RemoveLocationmy" );
	fflush( logfile );

	GAME_RemoveLocationold( whichLocation );
	fprintf_s( logfile , "%s:[-->GAME_RemoveLocation<--  whichLocation: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichLocation );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemovePlayer )( HPLAYER whichPlayer , HPLAYERGAMERESULT gameResult );
GAME_RemovePlayer GAME_RemovePlayerorg = NULL;
GAME_RemovePlayer GAME_RemovePlayerold = NULL;

void __cdecl GAME_RemovePlayermy( HPLAYER whichPlayer , HPLAYERGAMERESULT gameResult )
{
	fprintf_s( logfile , "%s\n" , "RemovePlayermy" );
	fflush( logfile );

	GAME_RemovePlayerold( whichPlayer , gameResult );
	fprintf_s( logfile , "%s:[-->GAME_RemovePlayer<--  whichPlayer: %X gameResult: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , gameResult );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemoveRect )( HRECT whichRect );
GAME_RemoveRect GAME_RemoveRectorg = NULL;
GAME_RemoveRect GAME_RemoveRectold = NULL;

void __cdecl GAME_RemoveRectmy( HRECT whichRect )
{
	fprintf_s( logfile , "%s\n" , "RemoveRectmy" );
	fflush( logfile );

	GAME_RemoveRectold( whichRect );
	fprintf_s( logfile , "%s:[-->GAME_RemoveRect<--  whichRect: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichRect );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemoveRegion )( HREGION whichRegion );
GAME_RemoveRegion GAME_RemoveRegionorg = NULL;
GAME_RemoveRegion GAME_RemoveRegionold = NULL;

void __cdecl GAME_RemoveRegionmy( HREGION whichRegion )
{
	fprintf_s( logfile , "%s\n" , "RemoveRegionmy" );
	fflush( logfile );

	GAME_RemoveRegionold( whichRegion );
	fprintf_s( logfile , "%s:[-->GAME_RemoveRegion<--  whichRegion: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichRegion );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_RemoveSaveDirectory )( void * sourceDirName );
GAME_RemoveSaveDirectory GAME_RemoveSaveDirectoryorg = NULL;
GAME_RemoveSaveDirectory GAME_RemoveSaveDirectoryold = NULL;

BOOL __cdecl GAME_RemoveSaveDirectorymy( void * sourceDirName )
{
	fprintf_s( logfile , "%s\n" , "RemoveSaveDirectorymy" );
	fflush( logfile );

	BOOL retvalue = GAME_RemoveSaveDirectoryold( sourceDirName );
	fprintf_s( logfile , "%s:[-->GAME_RemoveSaveDirectory<--  sourceDirName: \"%s\"] RETURN-> %s\n" , currentDateTime( ).c_str( ) , jassgetchar( sourceDirName ) , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_RemoveSavedBOOLean )( HHASHTABLE table , int parentKey , int childKey );
GAME_RemoveSavedBOOLean GAME_RemoveSavedBOOLeanorg = NULL;
GAME_RemoveSavedBOOLean GAME_RemoveSavedBOOLeanold = NULL;

void __cdecl GAME_RemoveSavedBOOLeanmy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s" , "RemoveSavedBOOLeanmy\n" );
	fflush( logfile );

	GAME_RemoveSavedBOOLeanold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_RemoveSavedBOOLean<--  table: %X parentKey: %i childKey: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemoveSavedHandle )( HHASHTABLE table , int parentKey , int childKey );
GAME_RemoveSavedHandle GAME_RemoveSavedHandleorg = NULL;
GAME_RemoveSavedHandle GAME_RemoveSavedHandleold = NULL;

void __cdecl GAME_RemoveSavedHandlemy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "RemoveSavedHandlemy" );
	fflush( logfile );

	GAME_RemoveSavedHandleold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_RemoveSavedHandle<--  table: %X parentKey: %i childKey: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemoveSavedInteger )( HHASHTABLE table , int parentKey , int childKey );
GAME_RemoveSavedInteger GAME_RemoveSavedIntegerorg = NULL;
GAME_RemoveSavedInteger GAME_RemoveSavedIntegerold = NULL;

void __cdecl GAME_RemoveSavedIntegermy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "RemoveSavedIntegermy" );
	fflush( logfile );

	GAME_RemoveSavedIntegerold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_RemoveSavedInteger<--  table: %X parentKey: %i childKey: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemoveSavedReal )( HHASHTABLE table , int parentKey , int childKey );
GAME_RemoveSavedReal GAME_RemoveSavedRealorg = NULL;
GAME_RemoveSavedReal GAME_RemoveSavedRealold = NULL;

void __cdecl GAME_RemoveSavedRealmy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "RemoveSavedRealmy" );
	fflush( logfile );

	GAME_RemoveSavedRealold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_RemoveSavedReal<--  table: %X parentKey: %i childKey: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemoveSavedString )( HHASHTABLE table , int parentKey , int childKey );
GAME_RemoveSavedString GAME_RemoveSavedStringorg = NULL;
GAME_RemoveSavedString GAME_RemoveSavedStringold = NULL;

void __cdecl GAME_RemoveSavedStringmy( HHASHTABLE table , int parentKey , int childKey )
{
	fprintf_s( logfile , "%s\n" , "RemoveSavedStringmy" );
	fflush( logfile );

	GAME_RemoveSavedStringold( table , parentKey , childKey );
	fprintf_s( logfile , "%s:[-->GAME_RemoveSavedString<--  table: %X parentKey: %i childKey: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemoveSiege )( );
GAME_RemoveSiege GAME_RemoveSiegeorg = NULL;
GAME_RemoveSiege GAME_RemoveSiegeold = NULL;

void __cdecl GAME_RemoveSiegemy( )
{
	fprintf_s( logfile , "%s\n" , "RemoveSiegemy" );
	fflush( logfile );

	GAME_RemoveSiegeold( );
	fprintf_s( logfile , "%s:[-->GAME_RemoveSiege<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemoveUnit )( HUNIT whichUnit );
GAME_RemoveUnit GAME_RemoveUnitorg = NULL;
GAME_RemoveUnit GAME_RemoveUnitold = NULL;

void __cdecl GAME_RemoveUnitmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "RemoveUnitmy" );
	fflush( logfile );

	GAME_RemoveUnitold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_RemoveUnit<--  whichUnit: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemoveUnitFromAllStock )( int unitId );
GAME_RemoveUnitFromAllStock GAME_RemoveUnitFromAllStockorg = NULL;
GAME_RemoveUnitFromAllStock GAME_RemoveUnitFromAllStockold = NULL;

void __cdecl GAME_RemoveUnitFromAllStockmy( int unitId )
{
	fprintf_s( logfile , "%s\n" , "RemoveUnitFromAllStockmy" );
	fflush( logfile );

	GAME_RemoveUnitFromAllStockold( unitId );
	fprintf_s( logfile , "%s:[-->GAME_RemoveUnitFromAllStock<--  unitId: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , unitId );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemoveUnitFromStock )( HUNIT whichUnit , int unitId );
GAME_RemoveUnitFromStock GAME_RemoveUnitFromStockorg = NULL;
GAME_RemoveUnitFromStock GAME_RemoveUnitFromStockold = NULL;

void __cdecl GAME_RemoveUnitFromStockmy( HUNIT whichUnit , int unitId )
{
	fprintf_s( logfile , "%s\n" , "RemoveUnitFromStockmy" );
	fflush( logfile );

	GAME_RemoveUnitFromStockold( whichUnit , unitId );
	fprintf_s( logfile , "%s:[-->GAME_RemoveUnitFromStock<--  whichUnit: %X unitId: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , unitId );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RemoveWeatherEffect )( HWEATHEREFFECT whichEffect );
GAME_RemoveWeatherEffect GAME_RemoveWeatherEffectorg = NULL;
GAME_RemoveWeatherEffect GAME_RemoveWeatherEffectold = NULL;

void __cdecl GAME_RemoveWeatherEffectmy( HWEATHEREFFECT whichEffect )
{
	fprintf_s( logfile , "%s\n" , "RemoveWeatherEffectmy" );
	fflush( logfile );

	GAME_RemoveWeatherEffectold( whichEffect );
	fprintf_s( logfile , "%s:[-->GAME_RemoveWeatherEffect<--  whichEffect: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichEffect );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_RenameSaveDirectory )( void * sourceDirName , void * destDirName );
GAME_RenameSaveDirectory GAME_RenameSaveDirectoryorg = NULL;
GAME_RenameSaveDirectory GAME_RenameSaveDirectoryold = NULL;

BOOL __cdecl GAME_RenameSaveDirectorymy( void * sourceDirName , void * destDirName )
{
	fprintf_s( logfile , "%s\n" , "RenameSaveDirectorymy" );
	fflush( logfile );

	BOOL retvalue = GAME_RenameSaveDirectoryold( sourceDirName , destDirName );
	fprintf_s( logfile , "%s:[-->GAME_RenameSaveDirectory<--  sourceDirName: \"%s\" destDirName: \"%s\"] RETURN-> %s\n" , currentDateTime( ).c_str( ) , jassgetchar( sourceDirName ) , jassgetchar( destDirName ) , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_ResetCaptainLocs )( );
GAME_ResetCaptainLocs GAME_ResetCaptainLocsorg = NULL;
GAME_ResetCaptainLocs GAME_ResetCaptainLocsold = NULL;

void __cdecl GAME_ResetCaptainLocsmy( )
{
	fprintf_s( logfile , "%s" , "ResetCaptainLocsmy\n" );
	fflush( logfile );

	GAME_ResetCaptainLocsold( );
	fprintf_s( logfile , "%s:[-->GAME_ResetCaptainLocs<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ResetTerrainFog )( );
GAME_ResetTerrainFog GAME_ResetTerrainFogorg = NULL;
GAME_ResetTerrainFog GAME_ResetTerrainFogold = NULL;

void __cdecl GAME_ResetTerrainFogmy( )
{
	fprintf_s( logfile , "%s\n" , "ResetTerrainFogmy" );
	fflush( logfile );

	GAME_ResetTerrainFogold( );
	fprintf_s( logfile , "%s:[-->GAME_ResetTerrainFog<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ResetToGameCamera )( float *duration );
GAME_ResetToGameCamera GAME_ResetToGameCameraorg = NULL;
GAME_ResetToGameCamera GAME_ResetToGameCameraold = NULL;

void __cdecl GAME_ResetToGameCameramy( float *duration )
{
	fprintf_s( logfile , "%s\n" , "ResetToGameCameramy" );
	fflush( logfile );

	GAME_ResetToGameCameraold( duration );
	fprintf_s( logfile , "%s:[-->GAME_ResetToGameCamera<--  duration: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) duration );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ResetTrigger )( HTRIGGER whichTrigger );
GAME_ResetTrigger GAME_ResetTriggerorg = NULL;
GAME_ResetTrigger GAME_ResetTriggerold = NULL;

void __cdecl GAME_ResetTriggermy( HTRIGGER whichTrigger )
{
	fprintf_s( logfile , "%s\n" , "ResetTriggermy" );
	fflush( logfile );

	GAME_ResetTriggerold( whichTrigger );
	fprintf_s( logfile , "%s:[-->GAME_ResetTrigger<--  whichTrigger: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichTrigger );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ResetUbersplat )( HUBERSPLAT whichSplat );
GAME_ResetUbersplat GAME_ResetUbersplatorg = NULL;
GAME_ResetUbersplat GAME_ResetUbersplatold = NULL;

void __cdecl GAME_ResetUbersplatmy( HUBERSPLAT whichSplat )
{
	fprintf_s( logfile , "%s\n" , "ResetUbersplatmy" );
	fflush( logfile );

	GAME_ResetUbersplatold( whichSplat );
	fprintf_s( logfile , "%s:[-->GAME_ResetUbersplat<--  whichSplat: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichSplat );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ResetUnitLookAt )( HUNIT whichUnit );
GAME_ResetUnitLookAt GAME_ResetUnitLookAtorg = NULL;
GAME_ResetUnitLookAt GAME_ResetUnitLookAtold = NULL;

void __cdecl GAME_ResetUnitLookAtmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "ResetUnitLookAtmy" );
	fflush( logfile );

	GAME_ResetUnitLookAtold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_ResetUnitLookAt<--  whichUnit: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit );
	fflush( logfile );

}


typedef void( __cdecl *GAME_RestartGame )( BOOL doScoreScreen );
GAME_RestartGame GAME_RestartGameorg = NULL;
GAME_RestartGame GAME_RestartGameold = NULL;

void __cdecl GAME_RestartGamemy( BOOL doScoreScreen )
{
	fprintf_s( logfile , "%s\n" , "RestartGamemy" );
	fflush( logfile );

	GAME_RestartGameold( doScoreScreen );
	fprintf_s( logfile , "%s:[-->GAME_RestartGame<--  doScoreScreen: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , doScoreScreen ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef HUNIT( __cdecl *GAME_RestoreUnit )( HGAMECACHE cache , void * missionKey , void * key , HPLAYER forWhichPlayer , float *x , float *y , float *facing );
GAME_RestoreUnit GAME_RestoreUnitorg = NULL;
GAME_RestoreUnit GAME_RestoreUnitold = NULL;

HUNIT __cdecl GAME_RestoreUnitmy( HGAMECACHE cache , void * missionKey , void * key , HPLAYER forWhichPlayer , float *x , float *y , float *facing )
{
	fprintf_s( logfile , "%s" , "RestoreUnitmy\n" );
	fflush( logfile );

	HUNIT retvalue = GAME_RestoreUnitold( cache , missionKey , key , forWhichPlayer , x , y , facing );
	fprintf_s( logfile , "%s:[-->GAME_RestoreUnit<--  cache: %X missionKey: \"%s\" key: \"%s\" forWhichPlayer: %X x: %f y: %f facing: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) , forWhichPlayer , *( float * ) x , *( float * ) y , *( float * ) facing , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_ResumeMusic )( );
GAME_ResumeMusic GAME_ResumeMusicorg = NULL;
GAME_ResumeMusic GAME_ResumeMusicold = NULL;

void __cdecl GAME_ResumeMusicmy( )
{
	fprintf_s( logfile , "%s" , "ResumeMusicmy\n" );
	fflush( logfile );

	GAME_ResumeMusicold( );
	fprintf_s( logfile , "%s:[-->GAME_ResumeMusic<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ResumeTimer )( HTIMER whichTimer );
GAME_ResumeTimer GAME_ResumeTimerorg = NULL;
GAME_ResumeTimer GAME_ResumeTimerold = NULL;

void __cdecl GAME_ResumeTimermy( HTIMER whichTimer )
{
	fprintf_s( logfile , "%s\n" , "ResumeTimermy" );
	fflush( logfile );

	GAME_ResumeTimerold( whichTimer );
	fprintf_s( logfile , "%s:[-->GAME_ResumeTimer<--  whichTimer: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichTimer );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ReturnGuardPosts )( );
GAME_ReturnGuardPosts GAME_ReturnGuardPostsorg = NULL;
GAME_ReturnGuardPosts GAME_ReturnGuardPostsold = NULL;

void __cdecl GAME_ReturnGuardPostsmy( )
{
	fprintf_s( logfile , "%s\n" , "ReturnGuardPostsmy" );
	fflush( logfile );

	GAME_ReturnGuardPostsold( );
	fprintf_s( logfile , "%s:[-->GAME_ReturnGuardPosts<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_ReviveHero )( HUNIT whichHero , float *x , float *y , BOOL doEyecandy );
GAME_ReviveHero GAME_ReviveHeroorg = NULL;
GAME_ReviveHero GAME_ReviveHeroold = NULL;

BOOL __cdecl GAME_ReviveHeromy( HUNIT whichHero , float *x , float *y , BOOL doEyecandy )
{
	fprintf_s( logfile , "%s\n" , "ReviveHeromy" );
	fflush( logfile );

	BOOL retvalue = GAME_ReviveHeroold( whichHero , x , y , doEyecandy );
	fprintf_s( logfile , "%s:[-->GAME_ReviveHero<--  whichHero: %X x: %f y: %f doEyecandy: %s] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichHero , *( float * ) x , *( float * ) y , doEyecandy ? "TRUE\n" : "FALSE" , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_ReviveHeroLoc )( HUNIT whichHero , HLOCATION loc , BOOL doEyecandy );
GAME_ReviveHeroLoc GAME_ReviveHeroLocorg = NULL;
GAME_ReviveHeroLoc GAME_ReviveHeroLocold = NULL;

BOOL __cdecl GAME_ReviveHeroLocmy( HUNIT whichHero , HLOCATION loc , BOOL doEyecandy )
{
	fprintf_s( logfile , "%s" , "ReviveHeroLocmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_ReviveHeroLocold( whichHero , loc , doEyecandy );
	fprintf_s( logfile , "%s:[-->GAME_ReviveHeroLoc<--  whichHero: %X loc: %X doEyecandy: %s] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichHero , loc , doEyecandy ? "TRUE\n" : "FALSE" , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_S2I )( void * s );
GAME_S2I GAME_S2Iorg = NULL;
GAME_S2I GAME_S2Iold = NULL;

int __cdecl GAME_S2Imy( void * s )
{
	fprintf_s( logfile , "%s" , "S2Imy\n" );
	fflush( logfile );

	int retvalue = GAME_S2Iold( s );
	fprintf_s( logfile , "%s:[-->GAME_S2I<--  s: \"%s\"] RETURN-> %i\n" , currentDateTime( ).c_str( ) , jassgetchar( s ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_S2R )( void * s );
GAME_S2R GAME_S2Rorg = NULL;
GAME_S2R GAME_S2Rold = NULL;

DWFP __cdecl GAME_S2Rmy( void * s )
{
	fprintf_s( logfile , "%s" , "S2Rmy\n" );
	fflush( logfile );

	DWFP retvalue = GAME_S2Rold( s );
	fprintf_s( logfile , "%s:[-->GAME_S2R<--  s: \"%s\"] RETURN-> %f\n" , currentDateTime( ).c_str( ) , jassgetchar( s ) , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveAbilityHandle )( HHASHTABLE table , int parentKey , int childKey , HABILITY whichAbility );
GAME_SaveAbilityHandle GAME_SaveAbilityHandleorg = NULL;
GAME_SaveAbilityHandle GAME_SaveAbilityHandleold = NULL;

BOOL __cdecl GAME_SaveAbilityHandlemy( HHASHTABLE table , int parentKey , int childKey , HABILITY whichAbility )
{
	fprintf_s( logfile , "%s" , "SaveAbilityHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveAbilityHandleold( table , parentKey , childKey , whichAbility );
	fprintf_s( logfile , "%s:[-->GAME_SaveAbilityHandle<--  table: %X parentKey: %i childKey: %i whichAbility: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichAbility , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveAgentHandle )( HHASHTABLE table , int parentKey , int childKey , HAGENT whichAgent );
GAME_SaveAgentHandle GAME_SaveAgentHandleorg = NULL;
GAME_SaveAgentHandle GAME_SaveAgentHandleold = NULL;

BOOL __cdecl GAME_SaveAgentHandlemy( HHASHTABLE table , int parentKey , int childKey , HAGENT whichAgent )
{
	fprintf_s( logfile , "%s" , "SaveAgentHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveAgentHandleold( table , parentKey , childKey , whichAgent );
	fprintf_s( logfile , "%s:[-->GAME_SaveAgentHandle<--  table: %X parentKey: %i childKey: %i whichAgent: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichAgent , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_SaveBOOLean )( HHASHTABLE table , int parentKey , int childKey , BOOL value );
GAME_SaveBOOLean GAME_SaveBOOLeanorg = NULL;
GAME_SaveBOOLean GAME_SaveBOOLeanold = NULL;

void __cdecl GAME_SaveBOOLeanmy( HHASHTABLE table , int parentKey , int childKey , BOOL value )
{
	fprintf_s( logfile , "%s" , "SaveBOOLeanmy\n" );
	fflush( logfile );

	GAME_SaveBOOLeanold( table , parentKey , childKey , value );
	fprintf_s( logfile , "%s:[-->GAME_SaveBOOLean<--  table: %X parentKey: %i childKey: %i value: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , value ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_SaveBOOLeanExprHandle )( HHASHTABLE table , int parentKey , int childKey , HBOOLEXPR whichBOOLexpr );
GAME_SaveBOOLeanExprHandle GAME_SaveBOOLeanExprHandleorg = NULL;
GAME_SaveBOOLeanExprHandle GAME_SaveBOOLeanExprHandleold = NULL;

BOOL __cdecl GAME_SaveBOOLeanExprHandlemy( HHASHTABLE table , int parentKey , int childKey , HBOOLEXPR whichBOOLexpr )
{
	fprintf_s( logfile , "%s" , "SaveBOOLeanExprHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveBOOLeanExprHandleold( table , parentKey , childKey , whichBOOLexpr );
	fprintf_s( logfile , "%s:[-->GAME_SaveBOOLeanExprHandle<--  table: %X parentKey: %i childKey: %i whichBOOLexpr: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichBOOLexpr , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveButtonHandle )( HHASHTABLE table , int parentKey , int childKey , HBUTTON whichButton );
GAME_SaveButtonHandle GAME_SaveButtonHandleorg = NULL;
GAME_SaveButtonHandle GAME_SaveButtonHandleold = NULL;

BOOL __cdecl GAME_SaveButtonHandlemy( HHASHTABLE table , int parentKey , int childKey , HBUTTON whichButton )
{
	fprintf_s( logfile , "%s" , "SaveButtonHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveButtonHandleold( table , parentKey , childKey , whichButton );
	fprintf_s( logfile , "%s:[-->GAME_SaveButtonHandle<--  table: %X parentKey: %i childKey: %i whichButton: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichButton , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveDefeatConditionHandle )( HHASHTABLE table , int parentKey , int childKey , HDEFEATCONDITION whichDefeatcondition );
GAME_SaveDefeatConditionHandle GAME_SaveDefeatConditionHandleorg = NULL;
GAME_SaveDefeatConditionHandle GAME_SaveDefeatConditionHandleold = NULL;

BOOL __cdecl GAME_SaveDefeatConditionHandlemy( HHASHTABLE table , int parentKey , int childKey , HDEFEATCONDITION whichDefeatcondition )
{
	fprintf_s( logfile , "%s" , "SaveDefeatConditionHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveDefeatConditionHandleold( table , parentKey , childKey , whichDefeatcondition );
	fprintf_s( logfile , "%s:[-->GAME_SaveDefeatConditionHandle<--  table: %X parentKey: %i childKey: %i whichDefeatcondition: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichDefeatcondition , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveDestructableHandle )( HHASHTABLE table , int parentKey , int childKey , HDESTRUCTABLE whichDestructable );
GAME_SaveDestructableHandle GAME_SaveDestructableHandleorg = NULL;
GAME_SaveDestructableHandle GAME_SaveDestructableHandleold = NULL;

BOOL __cdecl GAME_SaveDestructableHandlemy( HHASHTABLE table , int parentKey , int childKey , HDESTRUCTABLE whichDestructable )
{
	fprintf_s( logfile , "%s" , "SaveDestructableHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveDestructableHandleold( table , parentKey , childKey , whichDestructable );
	fprintf_s( logfile , "%s:[-->GAME_SaveDestructableHandle<--  table: %X parentKey: %i childKey: %i whichDestructable: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichDestructable , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveDialogHandle )( HHASHTABLE table , int parentKey , int childKey , HDIALOG whichDialog );
GAME_SaveDialogHandle GAME_SaveDialogHandleorg = NULL;
GAME_SaveDialogHandle GAME_SaveDialogHandleold = NULL;

BOOL __cdecl GAME_SaveDialogHandlemy( HHASHTABLE table , int parentKey , int childKey , HDIALOG whichDialog )
{
	fprintf_s( logfile , "%s" , "SaveDialogHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveDialogHandleold( table , parentKey , childKey , whichDialog );
	fprintf_s( logfile , "%s:[-->GAME_SaveDialogHandle<--  table: %X parentKey: %i childKey: %i whichDialog: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichDialog , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveEffectHandle )( HHASHTABLE table , int parentKey , int childKey , HEFFECT whichEffect );
GAME_SaveEffectHandle GAME_SaveEffectHandleorg = NULL;
GAME_SaveEffectHandle GAME_SaveEffectHandleold = NULL;

BOOL __cdecl GAME_SaveEffectHandlemy( HHASHTABLE table , int parentKey , int childKey , HEFFECT whichEffect )
{
	fprintf_s( logfile , "%s" , "SaveEffectHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveEffectHandleold( table , parentKey , childKey , whichEffect );
	fprintf_s( logfile , "%s:[-->GAME_SaveEffectHandle<--  table: %X parentKey: %i childKey: %i whichEffect: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichEffect , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveFogModifierHandle )( HHASHTABLE table , int parentKey , int childKey , HFOGMODIFIER whichFogModifier );
GAME_SaveFogModifierHandle GAME_SaveFogModifierHandleorg = NULL;
GAME_SaveFogModifierHandle GAME_SaveFogModifierHandleold = NULL;

BOOL __cdecl GAME_SaveFogModifierHandlemy( HHASHTABLE table , int parentKey , int childKey , HFOGMODIFIER whichFogModifier )
{
	fprintf_s( logfile , "%s" , "SaveFogModifierHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveFogModifierHandleold( table , parentKey , childKey , whichFogModifier );
	fprintf_s( logfile , "%s:[-->GAME_SaveFogModifierHandle<--  table: %X parentKey: %i childKey: %i whichFogModifier: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichFogModifier , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveFogStateHandle )( HHASHTABLE table , int parentKey , int childKey , HFOGSTATE whichFogState );
GAME_SaveFogStateHandle GAME_SaveFogStateHandleorg = NULL;
GAME_SaveFogStateHandle GAME_SaveFogStateHandleold = NULL;

BOOL __cdecl GAME_SaveFogStateHandlemy( HHASHTABLE table , int parentKey , int childKey , HFOGSTATE whichFogState )
{
	fprintf_s( logfile , "%s" , "SaveFogStateHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveFogStateHandleold( table , parentKey , childKey , whichFogState );
	fprintf_s( logfile , "%s:[-->GAME_SaveFogStateHandle<--  table: %X parentKey: %i childKey: %i whichFogState: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichFogState , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveForceHandle )( HHASHTABLE table , int parentKey , int childKey , HFORCE whichForce );
GAME_SaveForceHandle GAME_SaveForceHandleorg = NULL;
GAME_SaveForceHandle GAME_SaveForceHandleold = NULL;

BOOL __cdecl GAME_SaveForceHandlemy( HHASHTABLE table , int parentKey , int childKey , HFORCE whichForce )
{
	fprintf_s( logfile , "%s" , "SaveForceHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveForceHandleold( table , parentKey , childKey , whichForce );
	fprintf_s( logfile , "%s:[-->GAME_SaveForceHandle<--  table: %X parentKey: %i childKey: %i whichForce: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichForce , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_SaveGame )( void * saveFileName );
GAME_SaveGame GAME_SaveGameorg = NULL;
GAME_SaveGame GAME_SaveGameold = NULL;

void __cdecl GAME_SaveGamemy( void * saveFileName )
{
	fprintf_s( logfile , "%s" , "SaveGamemy\n" );
	fflush( logfile );

	GAME_SaveGameold( saveFileName );
	fprintf_s( logfile , "%s:[-->GAME_SaveGame<--  saveFileName: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( saveFileName ) );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_SaveGameCache )( HGAMECACHE whichCache );
GAME_SaveGameCache GAME_SaveGameCacheorg = NULL;
GAME_SaveGameCache GAME_SaveGameCacheold = NULL;

BOOL __cdecl GAME_SaveGameCachemy( HGAMECACHE whichCache )
{
	fprintf_s( logfile , "%s" , "SaveGameCachemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveGameCacheold( whichCache );
	fprintf_s( logfile , "%s:[-->GAME_SaveGameCache<--  whichCache: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichCache , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveGameExists )( void * saveName );
GAME_SaveGameExists GAME_SaveGameExistsorg = NULL;
GAME_SaveGameExists GAME_SaveGameExistsold = NULL;

BOOL __cdecl GAME_SaveGameExistsmy( void * saveName )
{
	fprintf_s( logfile , "%s" , "SaveGameExistsmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveGameExistsold( saveName );
	fprintf_s( logfile , "%s:[-->GAME_SaveGameExists<--  saveName: \"%s\"] RETURN-> %s\n" , currentDateTime( ).c_str( ) , jassgetchar( saveName ) , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveGroupHandle )( HHASHTABLE table , int parentKey , int childKey , HGROUP whichGroup );
GAME_SaveGroupHandle GAME_SaveGroupHandleorg = NULL;
GAME_SaveGroupHandle GAME_SaveGroupHandleold = NULL;

BOOL __cdecl GAME_SaveGroupHandlemy( HHASHTABLE table , int parentKey , int childKey , HGROUP whichGroup )
{
	fprintf_s( logfile , "%s" , "SaveGroupHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveGroupHandleold( table , parentKey , childKey , whichGroup );
	fprintf_s( logfile , "%s:[-->GAME_SaveGroupHandle<--  table: %X parentKey: %i childKey: %i whichGroup: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichGroup , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveHashtableHandle )( HHASHTABLE table , int parentKey , int childKey , HHASHTABLE whichHashtable );
GAME_SaveHashtableHandle GAME_SaveHashtableHandleorg = NULL;
GAME_SaveHashtableHandle GAME_SaveHashtableHandleold = NULL;

BOOL __cdecl GAME_SaveHashtableHandlemy( HHASHTABLE table , int parentKey , int childKey , HHASHTABLE whichHashtable )
{
	fprintf_s( logfile , "%s" , "SaveHashtableHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveHashtableHandleold( table , parentKey , childKey , whichHashtable );
	fprintf_s( logfile , "%s:[-->GAME_SaveHashtableHandle<--  table: %X parentKey: %i childKey: %i whichHashtable: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichHashtable , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveImageHandle )( HHASHTABLE table , int parentKey , int childKey , HIMAGE whichImage );
GAME_SaveImageHandle GAME_SaveImageHandleorg = NULL;
GAME_SaveImageHandle GAME_SaveImageHandleold = NULL;

BOOL __cdecl GAME_SaveImageHandlemy( HHASHTABLE table , int parentKey , int childKey , HIMAGE whichImage )
{
	fprintf_s( logfile , "%s" , "SaveImageHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveImageHandleold( table , parentKey , childKey , whichImage );
	fprintf_s( logfile , "%s:[-->GAME_SaveImageHandle<--  table: %X parentKey: %i childKey: %i whichImage: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichImage , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_SaveInteger )( HHASHTABLE table , int parentKey , int childKey , int value );
GAME_SaveInteger GAME_SaveIntegerorg = NULL;
GAME_SaveInteger GAME_SaveIntegerold = NULL;

void __cdecl GAME_SaveIntegermy( HHASHTABLE table , int parentKey , int childKey , int value )
{
	fprintf_s( logfile , "%s" , "SaveIntegermy\n" );
	fflush( logfile );

	GAME_SaveIntegerold( table , parentKey , childKey , value );
	fprintf_s( logfile , "%s:[-->GAME_SaveInteger<--  table: %X parentKey: %i childKey: %i value: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , value );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_SaveItemHandle )( HHASHTABLE table , int parentKey , int childKey , HITEM whichItem );
GAME_SaveItemHandle GAME_SaveItemHandleorg = NULL;
GAME_SaveItemHandle GAME_SaveItemHandleold = NULL;

BOOL __cdecl GAME_SaveItemHandlemy( HHASHTABLE table , int parentKey , int childKey , HITEM whichItem )
{
	fprintf_s( logfile , "%s\n" , "SaveItemHandlemy" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveItemHandleold( table , parentKey , childKey , whichItem );
	fprintf_s( logfile , "%s:[-->GAME_SaveItemHandle<--  table: %X parentKey: %i childKey: %i whichItem: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichItem , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveItemPoolHandle )( HHASHTABLE table , int parentKey , int childKey , HITEMPOOL whichItempool );
GAME_SaveItemPoolHandle GAME_SaveItemPoolHandleorg = NULL;
GAME_SaveItemPoolHandle GAME_SaveItemPoolHandleold = NULL;

BOOL __cdecl GAME_SaveItemPoolHandlemy( HHASHTABLE table , int parentKey , int childKey , HITEMPOOL whichItempool )
{
	fprintf_s( logfile , "%s" , "SaveItemPoolHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveItemPoolHandleold( table , parentKey , childKey , whichItempool );
	fprintf_s( logfile , "%s:[-->GAME_SaveItemPoolHandle<--  table: %X parentKey: %i childKey: %i whichItempool: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichItempool , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveLeaderboardHandle )( HHASHTABLE table , int parentKey , int childKey , HLEADERBOARD whichLeaderboard );
GAME_SaveLeaderboardHandle GAME_SaveLeaderboardHandleorg = NULL;
GAME_SaveLeaderboardHandle GAME_SaveLeaderboardHandleold = NULL;

BOOL __cdecl GAME_SaveLeaderboardHandlemy( HHASHTABLE table , int parentKey , int childKey , HLEADERBOARD whichLeaderboard )
{
	fprintf_s( logfile , "%s" , "SaveLeaderboardHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveLeaderboardHandleold( table , parentKey , childKey , whichLeaderboard );
	fprintf_s( logfile , "%s:[-->GAME_SaveLeaderboardHandle<--  table: %X parentKey: %i childKey: %i whichLeaderboard: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichLeaderboard , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveLightningHandle )( HHASHTABLE table , int parentKey , int childKey , HLIGHTNING whichLightning );
GAME_SaveLightningHandle GAME_SaveLightningHandleorg = NULL;
GAME_SaveLightningHandle GAME_SaveLightningHandleold = NULL;

BOOL __cdecl GAME_SaveLightningHandlemy( HHASHTABLE table , int parentKey , int childKey , HLIGHTNING whichLightning )
{
	fprintf_s( logfile , "%s" , "SaveLightningHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveLightningHandleold( table , parentKey , childKey , whichLightning );
	fprintf_s( logfile , "%s:[-->GAME_SaveLightningHandle<--  table: %X parentKey: %i childKey: %i whichLightning: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichLightning , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveLocationHandle )( HHASHTABLE table , int parentKey , int childKey , HLOCATION whichLocation );
GAME_SaveLocationHandle GAME_SaveLocationHandleorg = NULL;
GAME_SaveLocationHandle GAME_SaveLocationHandleold = NULL;

BOOL __cdecl GAME_SaveLocationHandlemy( HHASHTABLE table , int parentKey , int childKey , HLOCATION whichLocation )
{
	fprintf_s( logfile , "%s" , "SaveLocationHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveLocationHandleold( table , parentKey , childKey , whichLocation );
	fprintf_s( logfile , "%s:[-->GAME_SaveLocationHandle<--  table: %X parentKey: %i childKey: %i whichLocation: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichLocation , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveMultiboardHandle )( HHASHTABLE table , int parentKey , int childKey , HMULTIBOARD whichMultiboard );
GAME_SaveMultiboardHandle GAME_SaveMultiboardHandleorg = NULL;
GAME_SaveMultiboardHandle GAME_SaveMultiboardHandleold = NULL;

BOOL __cdecl GAME_SaveMultiboardHandlemy( HHASHTABLE table , int parentKey , int childKey , HMULTIBOARD whichMultiboard )
{
	fprintf_s( logfile , "%s" , "SaveMultiboardHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveMultiboardHandleold( table , parentKey , childKey , whichMultiboard );
	fprintf_s( logfile , "%s:[-->GAME_SaveMultiboardHandle<--  table: %X parentKey: %i childKey: %i whichMultiboard: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichMultiboard , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveMultiboardItemHandle )( HHASHTABLE table , int parentKey , int childKey , HMULTIBOARDITEM whichMultiboarditem );
GAME_SaveMultiboardItemHandle GAME_SaveMultiboardItemHandleorg = NULL;
GAME_SaveMultiboardItemHandle GAME_SaveMultiboardItemHandleold = NULL;

BOOL __cdecl GAME_SaveMultiboardItemHandlemy( HHASHTABLE table , int parentKey , int childKey , HMULTIBOARDITEM whichMultiboarditem )
{
	fprintf_s( logfile , "%s" , "SaveMultiboardItemHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveMultiboardItemHandleold( table , parentKey , childKey , whichMultiboarditem );
	fprintf_s( logfile , "%s:[-->GAME_SaveMultiboardItemHandle<--  table: %X parentKey: %i childKey: %i whichMultiboarditem: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichMultiboarditem , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SavePlayerHandle )( HHASHTABLE table , int parentKey , int childKey , HPLAYER whichPlayer );
GAME_SavePlayerHandle GAME_SavePlayerHandleorg = NULL;
GAME_SavePlayerHandle GAME_SavePlayerHandleold = NULL;

BOOL __cdecl GAME_SavePlayerHandlemy( HHASHTABLE table , int parentKey , int childKey , HPLAYER whichPlayer )
{
	fprintf_s( logfile , "%s" , "SavePlayerHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SavePlayerHandleold( table , parentKey , childKey , whichPlayer );
	fprintf_s( logfile , "%s:[-->GAME_SavePlayerHandle<--  table: %X parentKey: %i childKey: %i whichPlayer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichPlayer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveQuestHandle )( HHASHTABLE table , int parentKey , int childKey , HQUEST whichQuest );
GAME_SaveQuestHandle GAME_SaveQuestHandleorg = NULL;
GAME_SaveQuestHandle GAME_SaveQuestHandleold = NULL;

BOOL __cdecl GAME_SaveQuestHandlemy( HHASHTABLE table , int parentKey , int childKey , HQUEST whichQuest )
{
	fprintf_s( logfile , "%s" , "SaveQuestHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveQuestHandleold( table , parentKey , childKey , whichQuest );
	fprintf_s( logfile , "%s:[-->GAME_SaveQuestHandle<--  table: %X parentKey: %i childKey: %i whichQuest: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichQuest , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveQuestItemHandle )( HHASHTABLE table , int parentKey , int childKey , HQUESTITEM whichQuestitem );
GAME_SaveQuestItemHandle GAME_SaveQuestItemHandleorg = NULL;
GAME_SaveQuestItemHandle GAME_SaveQuestItemHandleold = NULL;

BOOL __cdecl GAME_SaveQuestItemHandlemy( HHASHTABLE table , int parentKey , int childKey , HQUESTITEM whichQuestitem )
{
	fprintf_s( logfile , "%s" , "SaveQuestItemHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveQuestItemHandleold( table , parentKey , childKey , whichQuestitem );
	fprintf_s( logfile , "%s:[-->GAME_SaveQuestItemHandle<--  table: %X parentKey: %i childKey: %i whichQuestitem: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichQuestitem , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_SaveReal )( HHASHTABLE table , int parentKey , int childKey , float *value );
GAME_SaveReal GAME_SaveRealorg = NULL;
GAME_SaveReal GAME_SaveRealold = NULL;

void __cdecl GAME_SaveRealmy( HHASHTABLE table , int parentKey , int childKey , float *value )
{
	fprintf_s( logfile , "%s" , "SaveRealmy\n" );
	fflush( logfile );

	GAME_SaveRealold( table , parentKey , childKey , value );
	fprintf_s( logfile , "%s:[-->GAME_SaveReal<--  table: %X parentKey: %i childKey: %i value: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , *( float * ) value );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_SaveRectHandle )( HHASHTABLE table , int parentKey , int childKey , HRECT whichRect );
GAME_SaveRectHandle GAME_SaveRectHandleorg = NULL;
GAME_SaveRectHandle GAME_SaveRectHandleold = NULL;

BOOL __cdecl GAME_SaveRectHandlemy( HHASHTABLE table , int parentKey , int childKey , HRECT whichRect )
{
	fprintf_s( logfile , "%s\n" , "SaveRectHandlemy" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveRectHandleold( table , parentKey , childKey , whichRect );
	fprintf_s( logfile , "%s:[-->GAME_SaveRectHandle<--  table: %X parentKey: %i childKey: %i whichRect: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichRect , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveRegionHandle )( HHASHTABLE table , int parentKey , int childKey , HREGION whichRegion );
GAME_SaveRegionHandle GAME_SaveRegionHandleorg = NULL;
GAME_SaveRegionHandle GAME_SaveRegionHandleold = NULL;

BOOL __cdecl GAME_SaveRegionHandlemy( HHASHTABLE table , int parentKey , int childKey , HREGION whichRegion )
{
	fprintf_s( logfile , "%s" , "SaveRegionHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveRegionHandleold( table , parentKey , childKey , whichRegion );
	fprintf_s( logfile , "%s:[-->GAME_SaveRegionHandle<--  table: %X parentKey: %i childKey: %i whichRegion: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichRegion , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveSoundHandle )( HHASHTABLE table , int parentKey , int childKey , HSOUND whichSound );
GAME_SaveSoundHandle GAME_SaveSoundHandleorg = NULL;
GAME_SaveSoundHandle GAME_SaveSoundHandleold = NULL;

BOOL __cdecl GAME_SaveSoundHandlemy( HHASHTABLE table , int parentKey , int childKey , HSOUND whichSound )
{
	fprintf_s( logfile , "%s" , "SaveSoundHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveSoundHandleold( table , parentKey , childKey , whichSound );
	fprintf_s( logfile , "%s:[-->GAME_SaveSoundHandle<--  table: %X parentKey: %i childKey: %i whichSound: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichSound , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveStr )( HHASHTABLE table , int parentKey , int childKey , void * value );
GAME_SaveStr GAME_SaveStrorg = NULL;
GAME_SaveStr GAME_SaveStrold = NULL;

BOOL __cdecl GAME_SaveStrmy( HHASHTABLE table , int parentKey , int childKey , void * value )
{
	fprintf_s( logfile , "%s" , "SaveStrmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveStrold( table , parentKey , childKey , value );
	fprintf_s( logfile , "%s:[-->GAME_SaveStr<--  table: %X parentKey: %i childKey: %i value: \"%s\"] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , jassgetchar( value ) , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveTextTagHandle )( HHASHTABLE table , int parentKey , int childKey , HTEXTTAG whichTexttag );
GAME_SaveTextTagHandle GAME_SaveTextTagHandleorg = NULL;
GAME_SaveTextTagHandle GAME_SaveTextTagHandleold = NULL;

BOOL __cdecl GAME_SaveTextTagHandlemy( HHASHTABLE table , int parentKey , int childKey , HTEXTTAG whichTexttag )
{
	fprintf_s( logfile , "%s" , "SaveTextTagHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveTextTagHandleold( table , parentKey , childKey , whichTexttag );
	fprintf_s( logfile , "%s:[-->GAME_SaveTextTagHandle<--  table: %X parentKey: %i childKey: %i whichTexttag: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichTexttag , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveTimerDialogHandle )( HHASHTABLE table , int parentKey , int childKey , HTIMERDIALOG whichTimerdialog );
GAME_SaveTimerDialogHandle GAME_SaveTimerDialogHandleorg = NULL;
GAME_SaveTimerDialogHandle GAME_SaveTimerDialogHandleold = NULL;

BOOL __cdecl GAME_SaveTimerDialogHandlemy( HHASHTABLE table , int parentKey , int childKey , HTIMERDIALOG whichTimerdialog )
{
	fprintf_s( logfile , "%s" , "SaveTimerDialogHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveTimerDialogHandleold( table , parentKey , childKey , whichTimerdialog );
	fprintf_s( logfile , "%s:[-->GAME_SaveTimerDialogHandle<--  table: %X parentKey: %i childKey: %i whichTimerdialog: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichTimerdialog , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveTimerHandle )( HHASHTABLE table , int parentKey , int childKey , HTIMER whichTimer );
GAME_SaveTimerHandle GAME_SaveTimerHandleorg = NULL;
GAME_SaveTimerHandle GAME_SaveTimerHandleold = NULL;

BOOL __cdecl GAME_SaveTimerHandlemy( HHASHTABLE table , int parentKey , int childKey , HTIMER whichTimer )
{
	fprintf_s( logfile , "%s" , "SaveTimerHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveTimerHandleold( table , parentKey , childKey , whichTimer );
	fprintf_s( logfile , "%s:[-->GAME_SaveTimerHandle<--  table: %X parentKey: %i childKey: %i whichTimer: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichTimer , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveTrackableHandle )( HHASHTABLE table , int parentKey , int childKey , HTRACKABLE whichTrackable );
GAME_SaveTrackableHandle GAME_SaveTrackableHandleorg = NULL;
GAME_SaveTrackableHandle GAME_SaveTrackableHandleold = NULL;

BOOL __cdecl GAME_SaveTrackableHandlemy( HHASHTABLE table , int parentKey , int childKey , HTRACKABLE whichTrackable )
{
	fprintf_s( logfile , "%s" , "SaveTrackableHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveTrackableHandleold( table , parentKey , childKey , whichTrackable );
	fprintf_s( logfile , "%s:[-->GAME_SaveTrackableHandle<--  table: %X parentKey: %i childKey: %i whichTrackable: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichTrackable , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveTriggerActionHandle )( HHASHTABLE table , int parentKey , int childKey , HTRIGGERACTION whichTriggeraction );
GAME_SaveTriggerActionHandle GAME_SaveTriggerActionHandleorg = NULL;
GAME_SaveTriggerActionHandle GAME_SaveTriggerActionHandleold = NULL;

BOOL __cdecl GAME_SaveTriggerActionHandlemy( HHASHTABLE table , int parentKey , int childKey , HTRIGGERACTION whichTriggeraction )
{
	fprintf_s( logfile , "%s" , "SaveTriggerActionHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveTriggerActionHandleold( table , parentKey , childKey , whichTriggeraction );
	fprintf_s( logfile , "%s:[-->GAME_SaveTriggerActionHandle<--  table: %X parentKey: %i childKey: %i whichTriggeraction: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichTriggeraction , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveTriggerConditionHandle )( HHASHTABLE table , int parentKey , int childKey , HTRIGGERCONDITION whichTriggercondition );
GAME_SaveTriggerConditionHandle GAME_SaveTriggerConditionHandleorg = NULL;
GAME_SaveTriggerConditionHandle GAME_SaveTriggerConditionHandleold = NULL;

BOOL __cdecl GAME_SaveTriggerConditionHandlemy( HHASHTABLE table , int parentKey , int childKey , HTRIGGERCONDITION whichTriggercondition )
{
	fprintf_s( logfile , "%s" , "SaveTriggerConditionHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveTriggerConditionHandleold( table , parentKey , childKey , whichTriggercondition );
	fprintf_s( logfile , "%s:[-->GAME_SaveTriggerConditionHandle<--  table: %X parentKey: %i childKey: %i whichTriggercondition: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichTriggercondition , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveTriggerEventHandle )( HHASHTABLE table , int parentKey , int childKey , HEVENT whichEvent );
GAME_SaveTriggerEventHandle GAME_SaveTriggerEventHandleorg = NULL;
GAME_SaveTriggerEventHandle GAME_SaveTriggerEventHandleold = NULL;

BOOL __cdecl GAME_SaveTriggerEventHandlemy( HHASHTABLE table , int parentKey , int childKey , HEVENT whichEvent )
{
	fprintf_s( logfile , "%s" , "SaveTriggerEventHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveTriggerEventHandleold( table , parentKey , childKey , whichEvent );
	fprintf_s( logfile , "%s:[-->GAME_SaveTriggerEventHandle<--  table: %X parentKey: %i childKey: %i whichEvent: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichEvent , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveTriggerHandle )( HHASHTABLE table , int parentKey , int childKey , HTRIGGER whichTrigger );
GAME_SaveTriggerHandle GAME_SaveTriggerHandleorg = NULL;
GAME_SaveTriggerHandle GAME_SaveTriggerHandleold = NULL;

BOOL __cdecl GAME_SaveTriggerHandlemy( HHASHTABLE table , int parentKey , int childKey , HTRIGGER whichTrigger )
{
	fprintf_s( logfile , "%s" , "SaveTriggerHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveTriggerHandleold( table , parentKey , childKey , whichTrigger );
	fprintf_s( logfile , "%s:[-->GAME_SaveTriggerHandle<--  table: %X parentKey: %i childKey: %i whichTrigger: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichTrigger , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveUbersplatHandle )( HHASHTABLE table , int parentKey , int childKey , HUBERSPLAT whichUbersplat );
GAME_SaveUbersplatHandle GAME_SaveUbersplatHandleorg = NULL;
GAME_SaveUbersplatHandle GAME_SaveUbersplatHandleold = NULL;

BOOL __cdecl GAME_SaveUbersplatHandlemy( HHASHTABLE table , int parentKey , int childKey , HUBERSPLAT whichUbersplat )
{
	fprintf_s( logfile , "%s" , "SaveUbersplatHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveUbersplatHandleold( table , parentKey , childKey , whichUbersplat );
	fprintf_s( logfile , "%s:[-->GAME_SaveUbersplatHandle<--  table: %X parentKey: %i childKey: %i whichUbersplat: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichUbersplat , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveUnitHandle )( HHASHTABLE table , int parentKey , int childKey , HUNIT whichUnit );
GAME_SaveUnitHandle GAME_SaveUnitHandleorg = NULL;
GAME_SaveUnitHandle GAME_SaveUnitHandleold = NULL;

BOOL __cdecl GAME_SaveUnitHandlemy( HHASHTABLE table , int parentKey , int childKey , HUNIT whichUnit )
{
	fprintf_s( logfile , "%s" , "SaveUnitHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveUnitHandleold( table , parentKey , childKey , whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_SaveUnitHandle<--  table: %X parentKey: %i childKey: %i whichUnit: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichUnit , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveUnitPoolHandle )( HHASHTABLE table , int parentKey , int childKey , HUNITPOOL whichUnitpool );
GAME_SaveUnitPoolHandle GAME_SaveUnitPoolHandleorg = NULL;
GAME_SaveUnitPoolHandle GAME_SaveUnitPoolHandleold = NULL;

BOOL __cdecl GAME_SaveUnitPoolHandlemy( HHASHTABLE table , int parentKey , int childKey , HUNITPOOL whichUnitpool )
{
	fprintf_s( logfile , "%s" , "SaveUnitPoolHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveUnitPoolHandleold( table , parentKey , childKey , whichUnitpool );
	fprintf_s( logfile , "%s:[-->GAME_SaveUnitPoolHandle<--  table: %X parentKey: %i childKey: %i whichUnitpool: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichUnitpool , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SaveWidgetHandle )( HHASHTABLE table , int parentKey , int childKey , HWIDGET whichWidget );
GAME_SaveWidgetHandle GAME_SaveWidgetHandleorg = NULL;
GAME_SaveWidgetHandle GAME_SaveWidgetHandleold = NULL;

BOOL __cdecl GAME_SaveWidgetHandlemy( HHASHTABLE table , int parentKey , int childKey , HWIDGET whichWidget )
{
	fprintf_s( logfile , "%s" , "SaveWidgetHandlemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SaveWidgetHandleold( table , parentKey , childKey , whichWidget );
	fprintf_s( logfile , "%s:[-->GAME_SaveWidgetHandle<--  table: %X parentKey: %i childKey: %i whichWidget: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , table , parentKey , childKey , whichWidget , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_SelectHeroSkill )( HUNIT whichHero , int abilcode );
GAME_SelectHeroSkill GAME_SelectHeroSkillorg = NULL;
GAME_SelectHeroSkill GAME_SelectHeroSkillold = NULL;

void __cdecl GAME_SelectHeroSkillmy( HUNIT whichHero , int abilcode )
{
	fprintf_s( logfile , "%s" , "SelectHeroSkillmy\n" );
	fflush( logfile );

	GAME_SelectHeroSkillold( whichHero , abilcode );
	fprintf_s( logfile , "%s:[-->GAME_SelectHeroSkill<--  whichHero: %X abilcode: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichHero , abilcode );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SelectUnit )( HUNIT whichUnit , BOOL flag );
GAME_SelectUnit GAME_SelectUnitorg = NULL;
GAME_SelectUnit GAME_SelectUnitold = NULL;

void __cdecl GAME_SelectUnitmy( HUNIT whichUnit , BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "SelectUnitmy" );
	fflush( logfile );

	GAME_SelectUnitold( whichUnit , flag );
	fprintf_s( logfile , "%s:[-->GAME_SelectUnit<--  whichUnit: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetAllItemTypeSlots )( int slots );
GAME_SetAllItemTypeSlots GAME_SetAllItemTypeSlotsorg = NULL;
GAME_SetAllItemTypeSlots GAME_SetAllItemTypeSlotsold = NULL;

void __cdecl GAME_SetAllItemTypeSlotsmy( int slots )
{
	fprintf_s( logfile , "%s" , "SetAllItemTypeSlotsmy\n" );
	fflush( logfile );

	GAME_SetAllItemTypeSlotsold( slots );
	fprintf_s( logfile , "%s:[-->GAME_SetAllItemTypeSlots<--  slots: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , slots );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetAllUnitTypeSlots )( int slots );
GAME_SetAllUnitTypeSlots GAME_SetAllUnitTypeSlotsorg = NULL;
GAME_SetAllUnitTypeSlots GAME_SetAllUnitTypeSlotsold = NULL;

void __cdecl GAME_SetAllUnitTypeSlotsmy( int slots )
{
	fprintf_s( logfile , "%s\n" , "SetAllUnitTypeSlotsmy" );
	fflush( logfile );

	GAME_SetAllUnitTypeSlotsold( slots );
	fprintf_s( logfile , "%s:[-->GAME_SetAllUnitTypeSlots<--  slots: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , slots );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetAllianceTarget )( HUNIT arg1 );
GAME_SetAllianceTarget GAME_SetAllianceTargetorg = NULL;
GAME_SetAllianceTarget GAME_SetAllianceTargetold = NULL;

void __cdecl GAME_SetAllianceTargetmy( HUNIT arg1 )
{
	fprintf_s( logfile , "%s\n" , "SetAllianceTargetmy" );
	fflush( logfile );

	GAME_SetAllianceTargetold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetAllianceTarget<--  arg1: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetAllyColorFilterState )( int state );
GAME_SetAllyColorFilterState GAME_SetAllyColorFilterStateorg = NULL;
GAME_SetAllyColorFilterState GAME_SetAllyColorFilterStateold = NULL;

void __cdecl GAME_SetAllyColorFilterStatemy( int state )
{
	fprintf_s( logfile , "%s\n" , "SetAllyColorFilterStatemy" );
	fflush( logfile );

	GAME_SetAllyColorFilterStateold( state );
	fprintf_s( logfile , "%s:[-->GAME_SetAllyColorFilterState<--  state: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , state );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetAltMinimapIcon )( void * iconPath );
GAME_SetAltMinimapIcon GAME_SetAltMinimapIconorg = NULL;
GAME_SetAltMinimapIcon GAME_SetAltMinimapIconold = NULL;

void __cdecl GAME_SetAltMinimapIconmy( void * iconPath )
{
	fprintf_s( logfile , "%s\n" , "SetAltMinimapIconmy" );
	fflush( logfile );

	GAME_SetAltMinimapIconold( iconPath );
	fprintf_s( logfile , "%s:[-->GAME_SetAltMinimapIcon<--  iconPath: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( iconPath ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetAmphibious )( );
GAME_SetAmphibious GAME_SetAmphibiousorg = NULL;
GAME_SetAmphibious GAME_SetAmphibiousold = NULL;

void __cdecl GAME_SetAmphibiousmy( )
{
	fprintf_s( logfile , "%s" , "SetAmphibiousmy\n" );
	fflush( logfile );

	GAME_SetAmphibiousold( );
	fprintf_s( logfile , "%s:[-->GAME_SetAmphibious<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetBlight )( HPLAYER whichPlayer , float *x , float *y , float *radius , BOOL addBlight );
GAME_SetBlight GAME_SetBlightorg = NULL;
GAME_SetBlight GAME_SetBlightold = NULL;

void __cdecl GAME_SetBlightmy( HPLAYER whichPlayer , float *x , float *y , float *radius , BOOL addBlight )
{
	fprintf_s( logfile , "%s\n" , "SetBlightmy" );
	fflush( logfile );

	GAME_SetBlightold( whichPlayer , x , y , radius , addBlight );
	fprintf_s( logfile , "%s:[-->GAME_SetBlight<--  whichPlayer: %X x: %f y: %f radius: %f addBlight: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , *( float * ) x , *( float * ) y , *( float * ) radius , addBlight ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetBlightLoc )( HPLAYER whichPlayer , HLOCATION whichLocation , float *radius , BOOL addBlight );
GAME_SetBlightLoc GAME_SetBlightLocorg = NULL;
GAME_SetBlightLoc GAME_SetBlightLocold = NULL;

void __cdecl GAME_SetBlightLocmy( HPLAYER whichPlayer , HLOCATION whichLocation , float *radius , BOOL addBlight )
{
	fprintf_s( logfile , "%s" , "SetBlightLocmy\n" );
	fflush( logfile );

	GAME_SetBlightLocold( whichPlayer , whichLocation , radius , addBlight );
	fprintf_s( logfile , "%s:[-->GAME_SetBlightLoc<--  whichPlayer: %X whichLocation: %X radius: %f addBlight: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , whichLocation , *( float * ) radius , addBlight ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetBlightPoint )( HPLAYER whichPlayer , float *x , float *y , BOOL addBlight );
GAME_SetBlightPoint GAME_SetBlightPointorg = NULL;
GAME_SetBlightPoint GAME_SetBlightPointold = NULL;

void __cdecl GAME_SetBlightPointmy( HPLAYER whichPlayer , float *x , float *y , BOOL addBlight )
{
	fprintf_s( logfile , "%s" , "SetBlightPointmy\n" );
	fflush( logfile );

	GAME_SetBlightPointold( whichPlayer , x , y , addBlight );
	fprintf_s( logfile , "%s:[-->GAME_SetBlightPoint<--  whichPlayer: %X x: %f y: %f addBlight: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , *( float * ) x , *( float * ) y , addBlight ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetBlightRect )( HPLAYER whichPlayer , HRECT r , BOOL addBlight );
GAME_SetBlightRect GAME_SetBlightRectorg = NULL;
GAME_SetBlightRect GAME_SetBlightRectold = NULL;

void __cdecl GAME_SetBlightRectmy( HPLAYER whichPlayer , HRECT r , BOOL addBlight )
{
	fprintf_s( logfile , "%s" , "SetBlightRectmy\n" );
	fflush( logfile );

	GAME_SetBlightRectold( whichPlayer , r , addBlight );
	fprintf_s( logfile , "%s:[-->GAME_SetBlightRect<--  whichPlayer: %X r: %X addBlight: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , r , addBlight ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCameraBounds )( float *x1 , float *y1 , float *x2 , float *y2 , float *x3 , float *y3 , float *x4 , float *y4 );
GAME_SetCameraBounds GAME_SetCameraBoundsorg = NULL;
GAME_SetCameraBounds GAME_SetCameraBoundsold = NULL;

void __cdecl GAME_SetCameraBoundsmy( float *x1 , float *y1 , float *x2 , float *y2 , float *x3 , float *y3 , float *x4 , float *y4 )
{
	fprintf_s( logfile , "%s" , "SetCameraBoundsmy\n" );
	fflush( logfile );

	GAME_SetCameraBoundsold( x1 , y1 , x2 , y2 , x3 , y3 , x4 , y4 );
	fprintf_s( logfile , "%s:[-->GAME_SetCameraBounds<--  x1: %f y1: %f x2: %f y2: %f x3: %f y3: %f x4: %f y4: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) x1 , *( float * ) y1 , *( float * ) x2 , *( float * ) y2 , *( float * ) x3 , *( float * ) y3 , *( float * ) x4 , *( float * ) y4 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCameraField )( HCAMERAFIELD whichField , float *value , float *duration );
GAME_SetCameraField GAME_SetCameraFieldorg = NULL;
GAME_SetCameraField GAME_SetCameraFieldold = NULL;

void __cdecl GAME_SetCameraFieldmy( HCAMERAFIELD whichField , float *value , float *duration )
{
	fprintf_s( logfile , "%s\n" , "SetCameraFieldmy" );
	fflush( logfile );

	GAME_SetCameraFieldold( whichField , value , duration );
	fprintf_s( logfile , "%s:[-->GAME_SetCameraField<--  whichField: %X value: %f duration: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichField , *( float * ) value , *( float * ) duration );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCameraOrientController )( HUNIT whichUnit , float *xoffset , float *yoffset );
GAME_SetCameraOrientController GAME_SetCameraOrientControllerorg = NULL;
GAME_SetCameraOrientController GAME_SetCameraOrientControllerold = NULL;

void __cdecl GAME_SetCameraOrientControllermy( HUNIT whichUnit , float *xoffset , float *yoffset )
{
	fprintf_s( logfile , "%s\n" , "SetCameraOrientControllermy" );
	fflush( logfile );

	GAME_SetCameraOrientControllerold( whichUnit , xoffset , yoffset );
	fprintf_s( logfile , "%s:[-->GAME_SetCameraOrientController<--  whichUnit: %X xoffset: %f yoffset: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , *( float * ) xoffset , *( float * ) yoffset );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCameraPosition )( float *x , float *y );
GAME_SetCameraPosition GAME_SetCameraPositionorg = NULL;
GAME_SetCameraPosition GAME_SetCameraPositionold = NULL;

void __cdecl GAME_SetCameraPositionmy( float *x , float *y )
{
	fprintf_s( logfile , "%s\n" , "SetCameraPositionmy" );
	fflush( logfile );

	GAME_SetCameraPositionold( x , y );
	fprintf_s( logfile , "%s:[-->GAME_SetCameraPosition<--  x: %f y: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCameraQuickPosition )( float *x , float *y );
GAME_SetCameraQuickPosition GAME_SetCameraQuickPositionorg = NULL;
GAME_SetCameraQuickPosition GAME_SetCameraQuickPositionold = NULL;

void __cdecl GAME_SetCameraQuickPositionmy( float *x , float *y )
{
	fprintf_s( logfile , "%s\n" , "SetCameraQuickPositionmy" );
	fflush( logfile );

	GAME_SetCameraQuickPositionold( x , y );
	fprintf_s( logfile , "%s:[-->GAME_SetCameraQuickPosition<--  x: %f y: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCameraRotateMode )( float *x , float *y , float *radiansToSweep , float *duration );
GAME_SetCameraRotateMode GAME_SetCameraRotateModeorg = NULL;
GAME_SetCameraRotateMode GAME_SetCameraRotateModeold = NULL;

void __cdecl GAME_SetCameraRotateModemy( float *x , float *y , float *radiansToSweep , float *duration )
{
	fprintf_s( logfile , "%s\n" , "SetCameraRotateModemy" );
	fflush( logfile );

	GAME_SetCameraRotateModeold( x , y , radiansToSweep , duration );
	fprintf_s( logfile , "%s:[-->GAME_SetCameraRotateMode<--  x: %f y: %f radiansToSweep: %f duration: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , *( float * ) radiansToSweep , *( float * ) duration );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCameraTargetController )( HUNIT whichUnit , float *xoffset , float *yoffset , BOOL inheritOrientation );
GAME_SetCameraTargetController GAME_SetCameraTargetControllerorg = NULL;
GAME_SetCameraTargetController GAME_SetCameraTargetControllerold = NULL;

void __cdecl GAME_SetCameraTargetControllermy( HUNIT whichUnit , float *xoffset , float *yoffset , BOOL inheritOrientation )
{
	fprintf_s( logfile , "%s\n" , "SetCameraTargetControllermy" );
	fflush( logfile );

	GAME_SetCameraTargetControllerold( whichUnit , xoffset , yoffset , inheritOrientation );
	fprintf_s( logfile , "%s:[-->GAME_SetCameraTargetController<--  whichUnit: %X xoffset: %f yoffset: %f inheritOrientation: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , *( float * ) xoffset , *( float * ) yoffset , inheritOrientation ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCampaignAI )( );
GAME_SetCampaignAI GAME_SetCampaignAIorg = NULL;
GAME_SetCampaignAI GAME_SetCampaignAIold = NULL;

void __cdecl GAME_SetCampaignAImy( )
{
	fprintf_s( logfile , "%s" , "SetCampaignAImy\n" );
	fflush( logfile );

	GAME_SetCampaignAIold( );
	fprintf_s( logfile , "%s:[-->GAME_SetCampaignAI<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCampaignAvailable )( int campaignNumber , BOOL available );
GAME_SetCampaignAvailable GAME_SetCampaignAvailableorg = NULL;
GAME_SetCampaignAvailable GAME_SetCampaignAvailableold = NULL;

void __cdecl GAME_SetCampaignAvailablemy( int campaignNumber , BOOL available )
{
	fprintf_s( logfile , "%s\n" , "SetCampaignAvailablemy" );
	fflush( logfile );

	GAME_SetCampaignAvailableold( campaignNumber , available );
	fprintf_s( logfile , "%s:[-->GAME_SetCampaignAvailable<--  campaignNumber: %i available: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , campaignNumber , available ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCampaignMenuRace )( HRACE r );
GAME_SetCampaignMenuRace GAME_SetCampaignMenuRaceorg = NULL;
GAME_SetCampaignMenuRace GAME_SetCampaignMenuRaceold = NULL;

void __cdecl GAME_SetCampaignMenuRacemy( HRACE r )
{
	fprintf_s( logfile , "%s" , "SetCampaignMenuRacemy\n" );
	fflush( logfile );

	GAME_SetCampaignMenuRaceold( r );
	fprintf_s( logfile , "%s:[-->GAME_SetCampaignMenuRace<--  r: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , r );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCampaignMenuRaceEx )( int campaignIndex );
GAME_SetCampaignMenuRaceEx GAME_SetCampaignMenuRaceExorg = NULL;
GAME_SetCampaignMenuRaceEx GAME_SetCampaignMenuRaceExold = NULL;

void __cdecl GAME_SetCampaignMenuRaceExmy( int campaignIndex )
{
	fprintf_s( logfile , "%s\n" , "SetCampaignMenuRaceExmy" );
	fflush( logfile );

	GAME_SetCampaignMenuRaceExold( campaignIndex );
	fprintf_s( logfile , "%s:[-->GAME_SetCampaignMenuRaceEx<--  campaignIndex: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , campaignIndex );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCaptainChanges )( BOOL arg1 );
GAME_SetCaptainChanges GAME_SetCaptainChangesorg = NULL;
GAME_SetCaptainChanges GAME_SetCaptainChangesold = NULL;

void __cdecl GAME_SetCaptainChangesmy( BOOL arg1 )
{
	fprintf_s( logfile , "%s\n" , "SetCaptainChangesmy" );
	fflush( logfile );

	GAME_SetCaptainChangesold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetCaptainChanges<--  arg1: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCaptainHome )( int arg1 , float *arg2 , float *arg3 );
GAME_SetCaptainHome GAME_SetCaptainHomeorg = NULL;
GAME_SetCaptainHome GAME_SetCaptainHomeold = NULL;

void __cdecl GAME_SetCaptainHomemy( int arg1 , float *arg2 , float *arg3 )
{
	fprintf_s( logfile , "%s" , "SetCaptainHomemy\n" );
	fflush( logfile );

	GAME_SetCaptainHomeold( arg1 , arg2 , arg3 );
	fprintf_s( logfile , "%s:[-->GAME_SetCaptainHome<--  arg1: %i arg2: %f arg3: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 , *( float * ) arg2 , *( float * ) arg3 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCineFilterBlendMode )( HBLENDMODE whichMode );
GAME_SetCineFilterBlendMode GAME_SetCineFilterBlendModeorg = NULL;
GAME_SetCineFilterBlendMode GAME_SetCineFilterBlendModeold = NULL;

void __cdecl GAME_SetCineFilterBlendModemy( HBLENDMODE whichMode )
{
	fprintf_s( logfile , "%s\n" , "SetCineFilterBlendModemy" );
	fflush( logfile );

	GAME_SetCineFilterBlendModeold( whichMode );
	fprintf_s( logfile , "%s:[-->GAME_SetCineFilterBlendMode<--  whichMode: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichMode );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCineFilterDuration )( float *duration );
GAME_SetCineFilterDuration GAME_SetCineFilterDurationorg = NULL;
GAME_SetCineFilterDuration GAME_SetCineFilterDurationold = NULL;

void __cdecl GAME_SetCineFilterDurationmy( float *duration )
{
	fprintf_s( logfile , "%s\n" , "SetCineFilterDurationmy" );
	fflush( logfile );

	GAME_SetCineFilterDurationold( duration );
	fprintf_s( logfile , "%s:[-->GAME_SetCineFilterDuration<--  duration: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) duration );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCineFilterEndColor )( int red , int green , int blue , int alpha );
GAME_SetCineFilterEndColor GAME_SetCineFilterEndColororg = NULL;
GAME_SetCineFilterEndColor GAME_SetCineFilterEndColorold = NULL;

void __cdecl GAME_SetCineFilterEndColormy( int red , int green , int blue , int alpha )
{
	fprintf_s( logfile , "%s\n" , "SetCineFilterEndColormy" );
	fflush( logfile );

	GAME_SetCineFilterEndColorold( red , green , blue , alpha );
	fprintf_s( logfile , "%s:[-->GAME_SetCineFilterEndColor<--  red: %i green: %i blue: %i alpha: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , red , green , blue , alpha );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCineFilterEndUV )( float *minu , float *minv , float *maxu , float *maxv );
GAME_SetCineFilterEndUV GAME_SetCineFilterEndUVorg = NULL;
GAME_SetCineFilterEndUV GAME_SetCineFilterEndUVold = NULL;

void __cdecl GAME_SetCineFilterEndUVmy( float *minu , float *minv , float *maxu , float *maxv )
{
	fprintf_s( logfile , "%s\n" , "SetCineFilterEndUVmy" );
	fflush( logfile );

	GAME_SetCineFilterEndUVold( minu , minv , maxu , maxv );
	fprintf_s( logfile , "%s:[-->GAME_SetCineFilterEndUV<--  minu: %f minv: %f maxu: %f maxv: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) minu , *( float * ) minv , *( float * ) maxu , *( float * ) maxv );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCineFilterStartColor )( int red , int green , int blue , int alpha );
GAME_SetCineFilterStartColor GAME_SetCineFilterStartColororg = NULL;
GAME_SetCineFilterStartColor GAME_SetCineFilterStartColorold = NULL;

void __cdecl GAME_SetCineFilterStartColormy( int red , int green , int blue , int alpha )
{
	fprintf_s( logfile , "%s\n" , "SetCineFilterStartColormy" );
	fflush( logfile );

	GAME_SetCineFilterStartColorold( red , green , blue , alpha );
	fprintf_s( logfile , "%s:[-->GAME_SetCineFilterStartColor<--  red: %i green: %i blue: %i alpha: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , red , green , blue , alpha );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCineFilterStartUV )( float *minu , float *minv , float *maxu , float *maxv );
GAME_SetCineFilterStartUV GAME_SetCineFilterStartUVorg = NULL;
GAME_SetCineFilterStartUV GAME_SetCineFilterStartUVold = NULL;

void __cdecl GAME_SetCineFilterStartUVmy( float *minu , float *minv , float *maxu , float *maxv )
{
	fprintf_s( logfile , "%s\n" , "SetCineFilterStartUVmy" );
	fflush( logfile );

	GAME_SetCineFilterStartUVold( minu , minv , maxu , maxv );
	fprintf_s( logfile , "%s:[-->GAME_SetCineFilterStartUV<--  minu: %f minv: %f maxu: %f maxv: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) minu , *( float * ) minv , *( float * ) maxu , *( float * ) maxv );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCineFilterTexMapFlags )( HTEXMAPFLAGS whichFlags );
GAME_SetCineFilterTexMapFlags GAME_SetCineFilterTexMapFlagsorg = NULL;
GAME_SetCineFilterTexMapFlags GAME_SetCineFilterTexMapFlagsold = NULL;

void __cdecl GAME_SetCineFilterTexMapFlagsmy( HTEXMAPFLAGS whichFlags )
{
	fprintf_s( logfile , "%s\n" , "SetCineFilterTexMapFlagsmy" );
	fflush( logfile );

	GAME_SetCineFilterTexMapFlagsold( whichFlags );
	fprintf_s( logfile , "%s:[-->GAME_SetCineFilterTexMapFlags<--  whichFlags: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichFlags );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCineFilterTexture )( void * filename );
GAME_SetCineFilterTexture GAME_SetCineFilterTextureorg = NULL;
GAME_SetCineFilterTexture GAME_SetCineFilterTextureold = NULL;

void __cdecl GAME_SetCineFilterTexturemy( void * filename )
{
	fprintf_s( logfile , "%s\n" , "SetCineFilterTexturemy" );
	fflush( logfile );

	GAME_SetCineFilterTextureold( filename );
	fprintf_s( logfile , "%s:[-->GAME_SetCineFilterTexture<--  filename: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( filename ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCinematicCamera )( void * cameraModelFile );
GAME_SetCinematicCamera GAME_SetCinematicCameraorg = NULL;
GAME_SetCinematicCamera GAME_SetCinematicCameraold = NULL;

void __cdecl GAME_SetCinematicCameramy( void * cameraModelFile )
{
	fprintf_s( logfile , "%s" , "SetCinematicCameramy\n" );
	fflush( logfile );

	GAME_SetCinematicCameraold( cameraModelFile );
	fprintf_s( logfile , "%s:[-->GAME_SetCinematicCamera<--  cameraModelFile: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( cameraModelFile ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCinematicScene )( int portraitUnitId , HPLAYERCOLOR color , void * speakerTitle , void * text , float *sceneDuration , float *voiceoverDuration );
GAME_SetCinematicScene GAME_SetCinematicSceneorg = NULL;
GAME_SetCinematicScene GAME_SetCinematicSceneold = NULL;

void __cdecl GAME_SetCinematicScenemy( int portraitUnitId , HPLAYERCOLOR color , void * speakerTitle , void * text , float *sceneDuration , float *voiceoverDuration )
{
	fprintf_s( logfile , "%s" , "SetCinematicScenemy\n" );
	fflush( logfile );

	GAME_SetCinematicSceneold( portraitUnitId , color , speakerTitle , text , sceneDuration , voiceoverDuration );
	fprintf_s( logfile , "%s:[-->GAME_SetCinematicScene<--  portraitUnitId: %i color: %X speakerTitle: \"%s\" text: \"%s\" sceneDuration: %f voiceoverDuration: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , portraitUnitId , color , jassgetchar( speakerTitle ) , jassgetchar( text ) , *( float * ) sceneDuration , *( float * ) voiceoverDuration );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCreatureDensity )( HMAPDENSITY whichdensity );
GAME_SetCreatureDensity GAME_SetCreatureDensityorg = NULL;
GAME_SetCreatureDensity GAME_SetCreatureDensityold = NULL;

void __cdecl GAME_SetCreatureDensitymy( HMAPDENSITY whichdensity )
{
	fprintf_s( logfile , "%s" , "SetCreatureDensitymy\n" );
	fflush( logfile );

	GAME_SetCreatureDensityold( whichdensity );
	fprintf_s( logfile , "%s:[-->GAME_SetCreatureDensity<--  whichdensity: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichdensity );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCreepCampFilterState )( BOOL state );
GAME_SetCreepCampFilterState GAME_SetCreepCampFilterStateorg = NULL;
GAME_SetCreepCampFilterState GAME_SetCreepCampFilterStateold = NULL;

void __cdecl GAME_SetCreepCampFilterStatemy( BOOL state )
{
	fprintf_s( logfile , "%s\n" , "SetCreepCampFilterStatemy" );
	fflush( logfile );

	GAME_SetCreepCampFilterStateold( state );
	fprintf_s( logfile , "%s:[-->GAME_SetCreepCampFilterState<--  state: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , state ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetCustomCampaignButtonVisible )( int whichButton , BOOL visible );
GAME_SetCustomCampaignButtonVisible GAME_SetCustomCampaignButtonVisibleorg = NULL;
GAME_SetCustomCampaignButtonVisible GAME_SetCustomCampaignButtonVisibleold = NULL;

void __cdecl GAME_SetCustomCampaignButtonVisiblemy( int whichButton , BOOL visible )
{
	fprintf_s( logfile , "%s" , "SetCustomCampaignButtonVisiblemy\n" );
	fflush( logfile );

	GAME_SetCustomCampaignButtonVisibleold( whichButton , visible );
	fprintf_s( logfile , "%s:[-->GAME_SetCustomCampaignButtonVisible<--  whichButton: %i visible: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichButton , visible ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetDayNightModels )( void * terrainDNCFile , void * unitDNCFile );
GAME_SetDayNightModels GAME_SetDayNightModelsorg = NULL;
GAME_SetDayNightModels GAME_SetDayNightModelsold = NULL;

void __cdecl GAME_SetDayNightModelsmy( void * terrainDNCFile , void * unitDNCFile )
{
	fprintf_s( logfile , "%s" , "SetDayNightModelsmy\n" );
	fflush( logfile );

	GAME_SetDayNightModelsold( terrainDNCFile , unitDNCFile );
	fprintf_s( logfile , "%s:[-->GAME_SetDayNightModels<--  terrainDNCFile: \"%s\" unitDNCFile: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( terrainDNCFile ) , jassgetchar( unitDNCFile ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetDefaultDifficulty )( HGAMEDIFFICULTY g );
GAME_SetDefaultDifficulty GAME_SetDefaultDifficultyorg = NULL;
GAME_SetDefaultDifficulty GAME_SetDefaultDifficultyold = NULL;

void __cdecl GAME_SetDefaultDifficultymy( HGAMEDIFFICULTY g )
{
	fprintf_s( logfile , "%s" , "SetDefaultDifficultymy\n" );
	fflush( logfile );

	GAME_SetDefaultDifficultyold( g );
	fprintf_s( logfile , "%s:[-->GAME_SetDefaultDifficulty<--  g: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , g );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetDefendPlayer )( BOOL arg1 );
GAME_SetDefendPlayer GAME_SetDefendPlayerorg = NULL;
GAME_SetDefendPlayer GAME_SetDefendPlayerold = NULL;

void __cdecl GAME_SetDefendPlayermy( BOOL arg1 )
{
	fprintf_s( logfile , "%s\n" , "SetDefendPlayermy" );
	fflush( logfile );

	GAME_SetDefendPlayerold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetDefendPlayer<--  arg1: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetDestructableAnimation )( HDESTRUCTABLE d , void * whichAnimation );
GAME_SetDestructableAnimation GAME_SetDestructableAnimationorg = NULL;
GAME_SetDestructableAnimation GAME_SetDestructableAnimationold = NULL;

void __cdecl GAME_SetDestructableAnimationmy( HDESTRUCTABLE d , void * whichAnimation )
{
	fprintf_s( logfile , "%s" , "SetDestructableAnimationmy\n" );
	fflush( logfile );

	GAME_SetDestructableAnimationold( d , whichAnimation );
	fprintf_s( logfile , "%s:[-->GAME_SetDestructableAnimation<--  d: %X whichAnimation: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , d , jassgetchar( whichAnimation ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetDestructableAnimationSpeed )( HDESTRUCTABLE d , float *speedFactor );
GAME_SetDestructableAnimationSpeed GAME_SetDestructableAnimationSpeedorg = NULL;
GAME_SetDestructableAnimationSpeed GAME_SetDestructableAnimationSpeedold = NULL;

void __cdecl GAME_SetDestructableAnimationSpeedmy( HDESTRUCTABLE d , float *speedFactor )
{
	fprintf_s( logfile , "%s" , "SetDestructableAnimationSpeedmy\n" );
	fflush( logfile );

	GAME_SetDestructableAnimationSpeedold( d , speedFactor );
	fprintf_s( logfile , "%s:[-->GAME_SetDestructableAnimationSpeed<--  d: %X speedFactor: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , d , *( float * ) speedFactor );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetDestructableInvulnerable )( HDESTRUCTABLE d , BOOL flag );
GAME_SetDestructableInvulnerable GAME_SetDestructableInvulnerableorg = NULL;
GAME_SetDestructableInvulnerable GAME_SetDestructableInvulnerableold = NULL;

void __cdecl GAME_SetDestructableInvulnerablemy( HDESTRUCTABLE d , BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "SetDestructableInvulnerablemy" );
	fflush( logfile );

	GAME_SetDestructableInvulnerableold( d , flag );
	fprintf_s( logfile , "%s:[-->GAME_SetDestructableInvulnerable<--  d: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , d , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetDestructableLife )( HDESTRUCTABLE d , float *life );
GAME_SetDestructableLife GAME_SetDestructableLifeorg = NULL;
GAME_SetDestructableLife GAME_SetDestructableLifeold = NULL;

void __cdecl GAME_SetDestructableLifemy( HDESTRUCTABLE d , float *life )
{
	fprintf_s( logfile , "%s" , "SetDestructableLifemy\n" );
	fflush( logfile );

	GAME_SetDestructableLifeold( d , life );
	fprintf_s( logfile , "%s:[-->GAME_SetDestructableLife<--  d: %X life: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , d , *( float * ) life );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetDestructableMaxLife )( HDESTRUCTABLE d , float *max );
GAME_SetDestructableMaxLife GAME_SetDestructableMaxLifeorg = NULL;
GAME_SetDestructableMaxLife GAME_SetDestructableMaxLifeold = NULL;

void __cdecl GAME_SetDestructableMaxLifemy( HDESTRUCTABLE d , float *max )
{
	fprintf_s( logfile , "%s\n" , "SetDestructableMaxLifemy" );
	fflush( logfile );

	GAME_SetDestructableMaxLifeold( d , max );
	fprintf_s( logfile , "%s:[-->GAME_SetDestructableMaxLife<--  d: %X max: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , d , *( float * ) max );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetDestructableOccluderHeight )( HDESTRUCTABLE d , float *height );
GAME_SetDestructableOccluderHeight GAME_SetDestructableOccluderHeightorg = NULL;
GAME_SetDestructableOccluderHeight GAME_SetDestructableOccluderHeightold = NULL;

void __cdecl GAME_SetDestructableOccluderHeightmy( HDESTRUCTABLE d , float *height )
{
	fprintf_s( logfile , "%s\n" , "SetDestructableOccluderHeightmy" );
	fflush( logfile );

	GAME_SetDestructableOccluderHeightold( d , height );
	fprintf_s( logfile , "%s:[-->GAME_SetDestructableOccluderHeight<--  d: %X height: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , d , *( float * ) height );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetDoodadAnimation )( float *x , float *y , float *radius , int doodadID , BOOL nearestOnly , void * animName , BOOL animRandom );
GAME_SetDoodadAnimation GAME_SetDoodadAnimationorg = NULL;
GAME_SetDoodadAnimation GAME_SetDoodadAnimationold = NULL;

void __cdecl GAME_SetDoodadAnimationmy( float *x , float *y , float *radius , int doodadID , BOOL nearestOnly , void * animName , BOOL animRandom )
{
	fprintf_s( logfile , "%s\n" , "SetDoodadAnimationmy" );
	fflush( logfile );

	GAME_SetDoodadAnimationold( x , y , radius , doodadID , nearestOnly , animName , animRandom );
	fprintf_s( logfile , "%s:[-->GAME_SetDoodadAnimation<--  x: %f y: %f radius: %f doodadID: %i nearestOnly: %s animName: \"%s\" animRandom: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , *( float * ) radius , doodadID , nearestOnly ? "TRUE" : "FALSE" , jassgetchar( animName ) , animRandom ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetDoodadAnimationRect )( HRECT r , int doodadID , void * animName , BOOL animRandom );
GAME_SetDoodadAnimationRect GAME_SetDoodadAnimationRectorg = NULL;
GAME_SetDoodadAnimationRect GAME_SetDoodadAnimationRectold = NULL;

void __cdecl GAME_SetDoodadAnimationRectmy( HRECT r , int doodadID , void * animName , BOOL animRandom )
{
	fprintf_s( logfile , "%s" , "SetDoodadAnimationRectmy\n" );
	fflush( logfile );

	GAME_SetDoodadAnimationRectold( r , doodadID , animName , animRandom );
	fprintf_s( logfile , "%s:[-->GAME_SetDoodadAnimationRect<--  r: %X doodadID: %i animName: \"%s\" animRandom: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , r , doodadID , jassgetchar( animName ) , animRandom ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetEdCinematicAvailable )( int campaignNumber , BOOL available );
GAME_SetEdCinematicAvailable GAME_SetEdCinematicAvailableorg = NULL;
GAME_SetEdCinematicAvailable GAME_SetEdCinematicAvailableold = NULL;

void __cdecl GAME_SetEdCinematicAvailablemy( int campaignNumber , BOOL available )
{
	fprintf_s( logfile , "%s" , "SetEdCinematicAvailablemy\n" );
	fflush( logfile );

	GAME_SetEdCinematicAvailableold( campaignNumber , available );
	fprintf_s( logfile , "%s:[-->GAME_SetEdCinematicAvailable<--  campaignNumber: %i available: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , campaignNumber , available ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_SetExpansion )( HUNIT arg1 , int arg2 );
GAME_SetExpansion GAME_SetExpansionorg = NULL;
GAME_SetExpansion GAME_SetExpansionold = NULL;

BOOL __cdecl GAME_SetExpansionmy( HUNIT arg1 , int arg2 )
{
	fprintf_s( logfile , "%s" , "SetExpansionmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SetExpansionold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_SetExpansion<--  arg1: %X arg2: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , arg1 , arg2 , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_SetFloatGameState )( HFGAMESTATE whichFloatGameState , float *value );
GAME_SetFloatGameState GAME_SetFloatGameStateorg = NULL;
GAME_SetFloatGameState GAME_SetFloatGameStateold = NULL;

void __cdecl GAME_SetFloatGameStatemy( HFGAMESTATE whichFloatGameState , float *value )
{
	fprintf_s( logfile , "%s" , "SetFloatGameStatemy\n" );
	fflush( logfile );

	GAME_SetFloatGameStateold( whichFloatGameState , value );
	fprintf_s( logfile , "%s:[-->GAME_SetFloatGameState<--  whichFloatGameState: %X value: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichFloatGameState , *( float * ) value );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetFogStateRadius )( HPLAYER forWhichPlayer , HFOGSTATE whichState , float *centerx , float *centerY , float *radius , BOOL useSharedVision );
GAME_SetFogStateRadius GAME_SetFogStateRadiusorg = NULL;
GAME_SetFogStateRadius GAME_SetFogStateRadiusold = NULL;

void __cdecl GAME_SetFogStateRadiusmy( HPLAYER forWhichPlayer , HFOGSTATE whichState , float *centerx , float *centerY , float *radius , BOOL useSharedVision )
{
	fprintf_s( logfile , "%s\n" , "SetFogStateRadiusmy" );
	fflush( logfile );

	GAME_SetFogStateRadiusold( forWhichPlayer , whichState , centerx , centerY , radius , useSharedVision );
	fprintf_s( logfile , "%s:[-->GAME_SetFogStateRadius<--  forWhichPlayer: %X whichState: %X centerx: %f centerY: %f radius: %f useSharedVision: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , forWhichPlayer , whichState , *( float * ) centerx , *( float * ) centerY , *( float * ) radius , useSharedVision ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetFogStateRadiusLoc )( HPLAYER forWhichPlayer , HFOGSTATE whichState , HLOCATION center , float *radius , BOOL useSharedVision );
GAME_SetFogStateRadiusLoc GAME_SetFogStateRadiusLocorg = NULL;
GAME_SetFogStateRadiusLoc GAME_SetFogStateRadiusLocold = NULL;

void __cdecl GAME_SetFogStateRadiusLocmy( HPLAYER forWhichPlayer , HFOGSTATE whichState , HLOCATION center , float *radius , BOOL useSharedVision )
{
	fprintf_s( logfile , "%s" , "SetFogStateRadiusLocmy\n" );
	fflush( logfile );

	GAME_SetFogStateRadiusLocold( forWhichPlayer , whichState , center , radius , useSharedVision );
	fprintf_s( logfile , "%s:[-->GAME_SetFogStateRadiusLoc<--  forWhichPlayer: %X whichState: %X center: %X radius: %f useSharedVision: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , forWhichPlayer , whichState , center , *( float * ) radius , useSharedVision ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetFogStateRect )( HPLAYER forWhichPlayer , HFOGSTATE whichState , HRECT where , BOOL useSharedVision );
GAME_SetFogStateRect GAME_SetFogStateRectorg = NULL;
GAME_SetFogStateRect GAME_SetFogStateRectold = NULL;

void __cdecl GAME_SetFogStateRectmy( HPLAYER forWhichPlayer , HFOGSTATE whichState , HRECT where , BOOL useSharedVision )
{
	fprintf_s( logfile , "%s" , "SetFogStateRectmy\n" );
	fflush( logfile );

	GAME_SetFogStateRectold( forWhichPlayer , whichState , where , useSharedVision );
	fprintf_s( logfile , "%s:[-->GAME_SetFogStateRect<--  forWhichPlayer: %X whichState: %X where: %X useSharedVision: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , forWhichPlayer , whichState , where , useSharedVision ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetGameDifficulty )( HGAMEDIFFICULTY whichdifficulty );
GAME_SetGameDifficulty GAME_SetGameDifficultyorg = NULL;
GAME_SetGameDifficulty GAME_SetGameDifficultyold = NULL;

void __cdecl GAME_SetGameDifficultymy( HGAMEDIFFICULTY whichdifficulty )
{
	fprintf_s( logfile , "%s" , "SetGameDifficultymy\n" );
	fflush( logfile );

	GAME_SetGameDifficultyold( whichdifficulty );
	fprintf_s( logfile , "%s:[-->GAME_SetGameDifficulty<--  whichdifficulty: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichdifficulty );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetGamePlacement )( HPLACEMENT whichPlacementType );
GAME_SetGamePlacement GAME_SetGamePlacementorg = NULL;
GAME_SetGamePlacement GAME_SetGamePlacementold = NULL;

void __cdecl GAME_SetGamePlacementmy( HPLACEMENT whichPlacementType )
{
	fprintf_s( logfile , "%s\n" , "SetGamePlacementmy" );
	fflush( logfile );

	GAME_SetGamePlacementold( whichPlacementType );
	fprintf_s( logfile , "%s:[-->GAME_SetGamePlacement<--  whichPlacementType: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlacementType );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetGameSpeed )( HGAMESPEED whichspeed );
GAME_SetGameSpeed GAME_SetGameSpeedorg = NULL;
GAME_SetGameSpeed GAME_SetGameSpeedold = NULL;

void __cdecl GAME_SetGameSpeedmy( HGAMESPEED whichspeed )
{
	fprintf_s( logfile , "%s\n" , "SetGameSpeedmy" );
	fflush( logfile );

	GAME_SetGameSpeedold( whichspeed );
	fprintf_s( logfile , "%s:[-->GAME_SetGameSpeed<--  whichspeed: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichspeed );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetGameTypeSupported )( HGAMETYPE whichGameType , BOOL value );
GAME_SetGameTypeSupported GAME_SetGameTypeSupportedorg = NULL;
GAME_SetGameTypeSupported GAME_SetGameTypeSupportedold = NULL;

void __cdecl GAME_SetGameTypeSupportedmy( HGAMETYPE whichGameType , BOOL value )
{
	fprintf_s( logfile , "%s\n" , "SetGameTypeSupportedmy" );
	fflush( logfile );

	GAME_SetGameTypeSupportedold( whichGameType , value );
	fprintf_s( logfile , "%s:[-->GAME_SetGameTypeSupported<--  whichGameType: %X value: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichGameType , value ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetGroupsFlee )( BOOL arg1 );
GAME_SetGroupsFlee GAME_SetGroupsFleeorg = NULL;
GAME_SetGroupsFlee GAME_SetGroupsFleeold = NULL;

void __cdecl GAME_SetGroupsFleemy( BOOL arg1 )
{
	fprintf_s( logfile , "%s" , "SetGroupsFleemy\n" );
	fflush( logfile );

	GAME_SetGroupsFleeold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetGroupsFlee<--  arg1: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetHeroAgi )( HUNIT whichHero , int newAgi , BOOL permanent );
GAME_SetHeroAgi GAME_SetHeroAgiorg = NULL;
GAME_SetHeroAgi GAME_SetHeroAgiold = NULL;

void __cdecl GAME_SetHeroAgimy( HUNIT whichHero , int newAgi , BOOL permanent )
{
	fprintf_s( logfile , "%s" , "SetHeroAgimy\n" );
	fflush( logfile );

	GAME_SetHeroAgiold( whichHero , newAgi , permanent );
	fprintf_s( logfile , "%s:[-->GAME_SetHeroAgi<--  whichHero: %X newAgi: %i permanent: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichHero , newAgi , permanent ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetHeroInt )( HUNIT whichHero , int newInt , BOOL permanent );
GAME_SetHeroInt GAME_SetHeroIntorg = NULL;
GAME_SetHeroInt GAME_SetHeroIntold = NULL;

void __cdecl GAME_SetHeroIntmy( HUNIT whichHero , int newInt , BOOL permanent )
{
	fprintf_s( logfile , "%s" , "SetHeroIntmy\n" );
	fflush( logfile );

	GAME_SetHeroIntold( whichHero , newInt , permanent );
	fprintf_s( logfile , "%s:[-->GAME_SetHeroInt<--  whichHero: %X newInt: %i permanent: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichHero , newInt , permanent ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetHeroLevel )( HUNIT whichHero , int level , BOOL showEyeCandy );
GAME_SetHeroLevel GAME_SetHeroLevelorg = NULL;
GAME_SetHeroLevel GAME_SetHeroLevelold = NULL;

void __cdecl GAME_SetHeroLevelmy( HUNIT whichHero , int level , BOOL showEyeCandy )
{
	fprintf_s( logfile , "%s" , "SetHeroLevelmy\n" );
	fflush( logfile );

	GAME_SetHeroLevelold( whichHero , level , showEyeCandy );
	fprintf_s( logfile , "%s:[-->GAME_SetHeroLevel<--  whichHero: %X level: %i showEyeCandy: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichHero , level , showEyeCandy ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetHeroLevels )( CODE arg1 );
GAME_SetHeroLevels GAME_SetHeroLevelsorg = NULL;
GAME_SetHeroLevels GAME_SetHeroLevelsold = NULL;

void __cdecl GAME_SetHeroLevelsmy( CODE arg1 )
{
	fprintf_s( logfile , "%s" , "SetHeroLevelsmy\n" );
	fflush( logfile );

	GAME_SetHeroLevelsold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetHeroLevels<--  arg1: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetHeroStr )( HUNIT whichHero , int newStr , BOOL permanent );
GAME_SetHeroStr GAME_SetHeroStrorg = NULL;
GAME_SetHeroStr GAME_SetHeroStrold = NULL;

void __cdecl GAME_SetHeroStrmy( HUNIT whichHero , int newStr , BOOL permanent )
{
	fprintf_s( logfile , "%s\n" , "SetHeroStrmy" );
	fflush( logfile );

	GAME_SetHeroStrold( whichHero , newStr , permanent );
	fprintf_s( logfile , "%s:[-->GAME_SetHeroStr<--  whichHero: %X newStr: %i permanent: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichHero , newStr , permanent ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetHeroXP )( HUNIT whichHero , int newXpVal , BOOL showEyeCandy );
GAME_SetHeroXP GAME_SetHeroXPorg = NULL;
GAME_SetHeroXP GAME_SetHeroXPold = NULL;

void __cdecl GAME_SetHeroXPmy( HUNIT whichHero , int newXpVal , BOOL showEyeCandy )
{
	fprintf_s( logfile , "%s" , "SetHeroXPmy\n" );
	fflush( logfile );

	GAME_SetHeroXPold( whichHero , newXpVal , showEyeCandy );
	fprintf_s( logfile , "%s:[-->GAME_SetHeroXP<--  whichHero: %X newXpVal: %i showEyeCandy: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichHero , newXpVal , showEyeCandy ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetHeroesBuyItems )( BOOL arg1 );
GAME_SetHeroesBuyItems GAME_SetHeroesBuyItemsorg = NULL;
GAME_SetHeroesBuyItems GAME_SetHeroesBuyItemsold = NULL;

void __cdecl GAME_SetHeroesBuyItemsmy( BOOL arg1 )
{
	fprintf_s( logfile , "%s" , "SetHeroesBuyItemsmy\n" );
	fflush( logfile );

	GAME_SetHeroesBuyItemsold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetHeroesBuyItems<--  arg1: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetHeroesFlee )( BOOL arg1 );
GAME_SetHeroesFlee GAME_SetHeroesFleeorg = NULL;
GAME_SetHeroesFlee GAME_SetHeroesFleeold = NULL;

void __cdecl GAME_SetHeroesFleemy( BOOL arg1 )
{
	fprintf_s( logfile , "%s" , "SetHeroesFleemy\n" );
	fflush( logfile );

	GAME_SetHeroesFleeold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetHeroesFlee<--  arg1: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetHeroesTakeItems )( BOOL arg1 );
GAME_SetHeroesTakeItems GAME_SetHeroesTakeItemsorg = NULL;
GAME_SetHeroesTakeItems GAME_SetHeroesTakeItemsold = NULL;

void __cdecl GAME_SetHeroesTakeItemsmy( BOOL arg1 )
{
	fprintf_s( logfile , "%s" , "SetHeroesTakeItemsmy\n" );
	fflush( logfile );

	GAME_SetHeroesTakeItemsold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetHeroesTakeItems<--  arg1: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetIgnoreInjured )( BOOL arg1 );
GAME_SetIgnoreInjured GAME_SetIgnoreInjuredorg = NULL;
GAME_SetIgnoreInjured GAME_SetIgnoreInjuredold = NULL;

void __cdecl GAME_SetIgnoreInjuredmy( BOOL arg1 )
{
	fprintf_s( logfile , "%s" , "SetIgnoreInjuredmy\n" );
	fflush( logfile );

	GAME_SetIgnoreInjuredold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetIgnoreInjured<--  arg1: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetImageAboveWater )( HIMAGE whichImage , BOOL flag , BOOL useWaterAlpha );
GAME_SetImageAboveWater GAME_SetImageAboveWaterorg = NULL;
GAME_SetImageAboveWater GAME_SetImageAboveWaterold = NULL;

void __cdecl GAME_SetImageAboveWatermy( HIMAGE whichImage , BOOL flag , BOOL useWaterAlpha )
{
	fprintf_s( logfile , "%s" , "SetImageAboveWatermy\n" );
	fflush( logfile );

	GAME_SetImageAboveWaterold( whichImage , flag , useWaterAlpha );
	fprintf_s( logfile , "%s:[-->GAME_SetImageAboveWater<--  whichImage: %X flag: %s useWaterAlpha: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichImage , flag ? "TRUE\n" : "FALSE" , useWaterAlpha ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetImageColor )( HIMAGE whichImage , int red , int green , int blue , int alpha );
GAME_SetImageColor GAME_SetImageColororg = NULL;
GAME_SetImageColor GAME_SetImageColorold = NULL;

void __cdecl GAME_SetImageColormy( HIMAGE whichImage , int red , int green , int blue , int alpha )
{
	fprintf_s( logfile , "%s" , "SetImageColormy\n" );
	fflush( logfile );

	GAME_SetImageColorold( whichImage , red , green , blue , alpha );
	fprintf_s( logfile , "%s:[-->GAME_SetImageColor<--  whichImage: %X red: %i green: %i blue: %i alpha: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichImage , red , green , blue , alpha );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetImageConstantHeight )( HIMAGE whichImage , BOOL flag , float *height );
GAME_SetImageConstantHeight GAME_SetImageConstantHeightorg = NULL;
GAME_SetImageConstantHeight GAME_SetImageConstantHeightold = NULL;

void __cdecl GAME_SetImageConstantHeightmy( HIMAGE whichImage , BOOL flag , float *height )
{
	fprintf_s( logfile , "%s\n" , "SetImageConstantHeightmy" );
	fflush( logfile );

	GAME_SetImageConstantHeightold( whichImage , flag , height );
	fprintf_s( logfile , "%s:[-->GAME_SetImageConstantHeight<--  whichImage: %X flag: %s height: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichImage , flag ? "TRUE\n" : "FALSE" , *( float * ) height );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetImagePosition )( HIMAGE whichImage , float *x , float *y , float *z );
GAME_SetImagePosition GAME_SetImagePositionorg = NULL;
GAME_SetImagePosition GAME_SetImagePositionold = NULL;

void __cdecl GAME_SetImagePositionmy( HIMAGE whichImage , float *x , float *y , float *z )
{
	fprintf_s( logfile , "%s" , "SetImagePositionmy\n" );
	fflush( logfile );

	GAME_SetImagePositionold( whichImage , x , y , z );
	fprintf_s( logfile , "%s:[-->GAME_SetImagePosition<--  whichImage: %X x: %f y: %f z: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichImage , *( float * ) x , *( float * ) y , *( float * ) z );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetImageRender )( HIMAGE whichImage , BOOL flag );
GAME_SetImageRender GAME_SetImageRenderorg = NULL;
GAME_SetImageRender GAME_SetImageRenderold = NULL;

void __cdecl GAME_SetImageRendermy( HIMAGE whichImage , BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "SetImageRendermy" );
	fflush( logfile );

	GAME_SetImageRenderold( whichImage , flag );
	fprintf_s( logfile , "%s:[-->GAME_SetImageRender<--  whichImage: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichImage , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetImageRenderAlways )( HIMAGE whichImage , BOOL flag );
GAME_SetImageRenderAlways GAME_SetImageRenderAlwaysorg = NULL;
GAME_SetImageRenderAlways GAME_SetImageRenderAlwaysold = NULL;

void __cdecl GAME_SetImageRenderAlwaysmy( HIMAGE whichImage , BOOL flag )
{
	fprintf_s( logfile , "%s" , "SetImageRenderAlwaysmy\n" );
	fflush( logfile );

	GAME_SetImageRenderAlwaysold( whichImage , flag );
	fprintf_s( logfile , "%s:[-->GAME_SetImageRenderAlways<--  whichImage: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichImage , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetImageType )( HIMAGE whichImage , int imageType );
GAME_SetImageType GAME_SetImageTypeorg = NULL;
GAME_SetImageType GAME_SetImageTypeold = NULL;

void __cdecl GAME_SetImageTypemy( HIMAGE whichImage , int imageType )
{
	fprintf_s( logfile , "%s" , "SetImageTypemy\n" );
	fflush( logfile );

	GAME_SetImageTypeold( whichImage , imageType );
	fprintf_s( logfile , "%s:[-->GAME_SetImageType<--  whichImage: %X imageType: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichImage , imageType );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetIntegerGameState )( HIGAMESTATE whichIntegerGameState , int value );
GAME_SetIntegerGameState GAME_SetIntegerGameStateorg = NULL;
GAME_SetIntegerGameState GAME_SetIntegerGameStateold = NULL;

void __cdecl GAME_SetIntegerGameStatemy( HIGAMESTATE whichIntegerGameState , int value )
{
	fprintf_s( logfile , "%s\n" , "SetIntegerGameStatemy" );
	fflush( logfile );

	GAME_SetIntegerGameStateold( whichIntegerGameState , value );
	fprintf_s( logfile , "%s:[-->GAME_SetIntegerGameState<--  whichIntegerGameState: %X value: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichIntegerGameState , value );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetIntroShotModel )( void * introModelPath );
GAME_SetIntroShotModel GAME_SetIntroShotModelorg = NULL;
GAME_SetIntroShotModel GAME_SetIntroShotModelold = NULL;

void __cdecl GAME_SetIntroShotModelmy( void * introModelPath )
{
	fprintf_s( logfile , "%s\n" , "SetIntroShotModelmy" );
	fflush( logfile );

	GAME_SetIntroShotModelold( introModelPath );
	fprintf_s( logfile , "%s:[-->GAME_SetIntroShotModel<--  introModelPath: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( introModelPath ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetIntroShotText )( void * introText );
GAME_SetIntroShotText GAME_SetIntroShotTextorg = NULL;
GAME_SetIntroShotText GAME_SetIntroShotTextold = NULL;

void __cdecl GAME_SetIntroShotTextmy( void * introText )
{
	fprintf_s( logfile , "%s" , "SetIntroShotTextmy\n" );
	fflush( logfile );

	GAME_SetIntroShotTextold( introText );
	fprintf_s( logfile , "%s:[-->GAME_SetIntroShotText<--  introText: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( introText ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetItemCharges )( HITEM whichItem , int charges );
GAME_SetItemCharges GAME_SetItemChargesorg = NULL;
GAME_SetItemCharges GAME_SetItemChargesold = NULL;

void __cdecl GAME_SetItemChargesmy( HITEM whichItem , int charges )
{
	fprintf_s( logfile , "%s" , "SetItemChargesmy\n" );
	fflush( logfile );

	GAME_SetItemChargesold( whichItem , charges );
	fprintf_s( logfile , "%s:[-->GAME_SetItemCharges<--  whichItem: %X charges: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichItem , charges );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetItemDropID )( HITEM whichItem , int unitId );
GAME_SetItemDropID GAME_SetItemDropIDorg = NULL;
GAME_SetItemDropID GAME_SetItemDropIDold = NULL;

void __cdecl GAME_SetItemDropIDmy( HITEM whichItem , int unitId )
{
	fprintf_s( logfile , "%s\n" , "SetItemDropIDmy" );
	fflush( logfile );

	GAME_SetItemDropIDold( whichItem , unitId );
	fprintf_s( logfile , "%s:[-->GAME_SetItemDropID<--  whichItem: %X unitId: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichItem , unitId );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetItemDropOnDeath )( HITEM whichItem , BOOL flag );
GAME_SetItemDropOnDeath GAME_SetItemDropOnDeathorg = NULL;
GAME_SetItemDropOnDeath GAME_SetItemDropOnDeathold = NULL;

void __cdecl GAME_SetItemDropOnDeathmy( HITEM whichItem , BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "SetItemDropOnDeathmy" );
	fflush( logfile );

	GAME_SetItemDropOnDeathold( whichItem , flag );
	fprintf_s( logfile , "%s:[-->GAME_SetItemDropOnDeath<--  whichItem: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichItem , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetItemDroppable )( HITEM i , BOOL flag );
GAME_SetItemDroppable GAME_SetItemDroppableorg = NULL;
GAME_SetItemDroppable GAME_SetItemDroppableold = NULL;

void __cdecl GAME_SetItemDroppablemy( HITEM i , BOOL flag )
{
	fprintf_s( logfile , "%s" , "SetItemDroppablemy\n" );
	fflush( logfile );

	GAME_SetItemDroppableold( i , flag );
	fprintf_s( logfile , "%s:[-->GAME_SetItemDroppable<--  i: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , i , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetItemInvulnerable )( HITEM whichItem , BOOL flag );
GAME_SetItemInvulnerable GAME_SetItemInvulnerableorg = NULL;
GAME_SetItemInvulnerable GAME_SetItemInvulnerableold = NULL;

void __cdecl GAME_SetItemInvulnerablemy( HITEM whichItem , BOOL flag )
{
	fprintf_s( logfile , "%s" , "SetItemInvulnerablemy\n" );
	fflush( logfile );

	GAME_SetItemInvulnerableold( whichItem , flag );
	fprintf_s( logfile , "%s:[-->GAME_SetItemInvulnerable<--  whichItem: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichItem , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetItemPawnable )( HITEM i , BOOL flag );
GAME_SetItemPawnable GAME_SetItemPawnableorg = NULL;
GAME_SetItemPawnable GAME_SetItemPawnableold = NULL;

void __cdecl GAME_SetItemPawnablemy( HITEM i , BOOL flag )
{
	fprintf_s( logfile , "%s" , "SetItemPawnablemy\n" );
	fflush( logfile );

	GAME_SetItemPawnableold( i , flag );
	fprintf_s( logfile , "%s:[-->GAME_SetItemPawnable<--  i: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , i , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetItemPlayer )( HITEM whichItem , HPLAYER whichPlayer , BOOL changeColor );
GAME_SetItemPlayer GAME_SetItemPlayerorg = NULL;
GAME_SetItemPlayer GAME_SetItemPlayerold = NULL;

void __cdecl GAME_SetItemPlayermy( HITEM whichItem , HPLAYER whichPlayer , BOOL changeColor )
{
	fprintf_s( logfile , "%s" , "SetItemPlayermy\n" );
	fflush( logfile );

	GAME_SetItemPlayerold( whichItem , whichPlayer , changeColor );
	fprintf_s( logfile , "%s:[-->GAME_SetItemPlayer<--  whichItem: %X whichPlayer: %X changeColor: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichItem , whichPlayer , changeColor ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetItemPosition )( HITEM i , float *x , float *y );
GAME_SetItemPosition GAME_SetItemPositionorg = NULL;
GAME_SetItemPosition GAME_SetItemPositionold = NULL;

void __cdecl GAME_SetItemPositionmy( HITEM i , float *x , float *y )
{
	fprintf_s( logfile , "%s" , "SetItemPositionmy\n" );
	fflush( logfile );

	GAME_SetItemPositionold( i , x , y );
	fprintf_s( logfile , "%s:[-->GAME_SetItemPosition<--  i: %X x: %f y: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , i , *( float * ) x , *( float * ) y );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetItemTypeSlots )( HUNIT whichUnit , int slots );
GAME_SetItemTypeSlots GAME_SetItemTypeSlotsorg = NULL;
GAME_SetItemTypeSlots GAME_SetItemTypeSlotsold = NULL;

void __cdecl GAME_SetItemTypeSlotsmy( HUNIT whichUnit , int slots )
{
	fprintf_s( logfile , "%s\n" , "SetItemTypeSlotsmy" );
	fflush( logfile );

	GAME_SetItemTypeSlotsold( whichUnit , slots );
	fprintf_s( logfile , "%s:[-->GAME_SetItemTypeSlots<--  whichUnit: %X slots: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , slots );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetItemUserData )( HITEM whichItem , int data );
GAME_SetItemUserData GAME_SetItemUserDataorg = NULL;
GAME_SetItemUserData GAME_SetItemUserDataold = NULL;

void __cdecl GAME_SetItemUserDatamy( HITEM whichItem , int data )
{
	fprintf_s( logfile , "%s\n" , "SetItemUserDatamy" );
	fflush( logfile );

	GAME_SetItemUserDataold( whichItem , data );
	fprintf_s( logfile , "%s:[-->GAME_SetItemUserData<--  whichItem: %X data: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichItem , data );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetItemVisible )( HITEM whichItem , BOOL show );
GAME_SetItemVisible GAME_SetItemVisibleorg = NULL;
GAME_SetItemVisible GAME_SetItemVisibleold = NULL;

void __cdecl GAME_SetItemVisiblemy( HITEM whichItem , BOOL show )
{
	fprintf_s( logfile , "%s\n" , "SetItemVisiblemy" );
	fflush( logfile );

	GAME_SetItemVisibleold( whichItem , show );
	fprintf_s( logfile , "%s:[-->GAME_SetItemVisible<--  whichItem: %X show: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichItem , show ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_SetLightningColor )( HLIGHTNING whichBolt , float *r , float *g , float *b , float *a );
GAME_SetLightningColor GAME_SetLightningColororg = NULL;
GAME_SetLightningColor GAME_SetLightningColorold = NULL;

BOOL __cdecl GAME_SetLightningColormy( HLIGHTNING whichBolt , float *r , float *g , float *b , float *a )
{
	fprintf_s( logfile , "%s" , "SetLightningColormy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SetLightningColorold( whichBolt , r , g , b , a );
	fprintf_s( logfile , "%s:[-->GAME_SetLightningColor<--  whichBolt: %X r: %f g: %f b: %f a: %f] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichBolt , *( float * ) r , *( float * ) g , *( float * ) b , *( float * ) a , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_SetMapDescription )( void * description );
GAME_SetMapDescription GAME_SetMapDescriptionorg = NULL;
GAME_SetMapDescription GAME_SetMapDescriptionold = NULL;

void __cdecl GAME_SetMapDescriptionmy( void * description )
{
	fprintf_s( logfile , "%s" , "SetMapDescriptionmy\n" );
	fflush( logfile );

	GAME_SetMapDescriptionold( description );
	fprintf_s( logfile , "%s:[-->GAME_SetMapDescription<--  description: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( description ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetMapFlag )( HMAPFLAG whichMapFlag , BOOL value );
GAME_SetMapFlag GAME_SetMapFlagorg = NULL;
GAME_SetMapFlag GAME_SetMapFlagold = NULL;

void __cdecl GAME_SetMapFlagmy( HMAPFLAG whichMapFlag , BOOL value )
{
	fprintf_s( logfile , "%s" , "SetMapFlagmy\n" );
	fflush( logfile );

	GAME_SetMapFlagold( whichMapFlag , value );
	fprintf_s( logfile , "%s:[-->GAME_SetMapFlag<--  whichMapFlag: %X value: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichMapFlag , value ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetMapMusic )( void * musicName , BOOL random , int index );
GAME_SetMapMusic GAME_SetMapMusicorg = NULL;
GAME_SetMapMusic GAME_SetMapMusicold = NULL;

void __cdecl GAME_SetMapMusicmy( void * musicName , BOOL random , int index )
{
	fprintf_s( logfile , "%s" , "SetMapMusicmy\n" );
	fflush( logfile );

	GAME_SetMapMusicold( musicName , random , index );
	fprintf_s( logfile , "%s:[-->GAME_SetMapMusic<--  musicName: \"%s\" random: %s index: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( musicName ) , random ? "TRUE" : "FALSE" , index );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetMapName )( void * name );
GAME_SetMapName GAME_SetMapNameorg = NULL;
GAME_SetMapName GAME_SetMapNameold = NULL;

void __cdecl GAME_SetMapNamemy( void * name )
{
	fprintf_s( logfile , "%s" , "SetMapNamemy\n" );
	fflush( logfile );

	GAME_SetMapNameold( name );
	fprintf_s( logfile , "%s:[-->GAME_SetMapName<--  name: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( name ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetMeleeAI )( );
GAME_SetMeleeAI GAME_SetMeleeAIorg = NULL;
GAME_SetMeleeAI GAME_SetMeleeAIold = NULL;

void __cdecl GAME_SetMeleeAImy( )
{
	fprintf_s( logfile , "%s" , "SetMeleeAImy\n" );
	fflush( logfile );

	GAME_SetMeleeAIold( );
	fprintf_s( logfile , "%s:[-->GAME_SetMeleeAI<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetMissionAvailable )( int campaignNumber , int missionNumber , BOOL available );
GAME_SetMissionAvailable GAME_SetMissionAvailableorg = NULL;
GAME_SetMissionAvailable GAME_SetMissionAvailableold = NULL;

void __cdecl GAME_SetMissionAvailablemy( int campaignNumber , int missionNumber , BOOL available )
{
	fprintf_s( logfile , "%s\n" , "SetMissionAvailablemy" );
	fflush( logfile );

	GAME_SetMissionAvailableold( campaignNumber , missionNumber , available );
	fprintf_s( logfile , "%s:[-->GAME_SetMissionAvailable<--  campaignNumber: %i missionNumber: %i available: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , campaignNumber , missionNumber , available ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetMusicPlayPosition )( int millisecs );
GAME_SetMusicPlayPosition GAME_SetMusicPlayPositionorg = NULL;
GAME_SetMusicPlayPosition GAME_SetMusicPlayPositionold = NULL;

void __cdecl GAME_SetMusicPlayPositionmy( int millisecs )
{
	fprintf_s( logfile , "%s" , "SetMusicPlayPositionmy\n" );
	fflush( logfile );

	GAME_SetMusicPlayPositionold( millisecs );
	fprintf_s( logfile , "%s:[-->GAME_SetMusicPlayPosition<--  millisecs: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , millisecs );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetMusicVolume )( int volume );
GAME_SetMusicVolume GAME_SetMusicVolumeorg = NULL;
GAME_SetMusicVolume GAME_SetMusicVolumeold = NULL;

void __cdecl GAME_SetMusicVolumemy( int volume )
{
	fprintf_s( logfile , "%s\n" , "SetMusicVolumemy" );
	fflush( logfile );

	GAME_SetMusicVolumeold( volume );
	fprintf_s( logfile , "%s:[-->GAME_SetMusicVolume<--  volume: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , volume );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetNewHeroes )( BOOL arg1 );
GAME_SetNewHeroes GAME_SetNewHeroesorg = NULL;
GAME_SetNewHeroes GAME_SetNewHeroesold = NULL;

void __cdecl GAME_SetNewHeroesmy( BOOL arg1 )
{
	fprintf_s( logfile , "%s\n" , "SetNewHeroesmy" );
	fflush( logfile );

	GAME_SetNewHeroesold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetNewHeroes<--  arg1: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetOpCinematicAvailable )( int campaignNumber , BOOL available );
GAME_SetOpCinematicAvailable GAME_SetOpCinematicAvailableorg = NULL;
GAME_SetOpCinematicAvailable GAME_SetOpCinematicAvailableold = NULL;

void __cdecl GAME_SetOpCinematicAvailablemy( int campaignNumber , BOOL available )
{
	fprintf_s( logfile , "%s" , "SetOpCinematicAvailablemy\n" );
	fflush( logfile );

	GAME_SetOpCinematicAvailableold( campaignNumber , available );
	fprintf_s( logfile , "%s:[-->GAME_SetOpCinematicAvailable<--  campaignNumber: %i available: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , campaignNumber , available ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPeonsRepair )( BOOL arg1 );
GAME_SetPeonsRepair GAME_SetPeonsRepairorg = NULL;
GAME_SetPeonsRepair GAME_SetPeonsRepairold = NULL;

void __cdecl GAME_SetPeonsRepairmy( BOOL arg1 )
{
	fprintf_s( logfile , "%s" , "SetPeonsRepairmy\n" );
	fflush( logfile );

	GAME_SetPeonsRepairold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetPeonsRepair<--  arg1: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPlayerAbilityAvailable )( HPLAYER whichPlayer , int abilid , BOOL avail );
GAME_SetPlayerAbilityAvailable GAME_SetPlayerAbilityAvailableorg = NULL;
GAME_SetPlayerAbilityAvailable GAME_SetPlayerAbilityAvailableold = NULL;

void __cdecl GAME_SetPlayerAbilityAvailablemy( HPLAYER whichPlayer , int abilid , BOOL avail )
{
	fprintf_s( logfile , "%s" , "SetPlayerAbilityAvailablemy\n" );
	fflush( logfile );

	GAME_SetPlayerAbilityAvailableold( whichPlayer , abilid , avail );
	fprintf_s( logfile , "%s:[-->GAME_SetPlayerAbilityAvailable<--  whichPlayer: %X abilid: %i avail: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , abilid , avail ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPlayerAlliance )( HPLAYER sourcePlayer , HPLAYER otherPlayer , HALLIANCETYPE whichAllianceSetting , BOOL value );
GAME_SetPlayerAlliance GAME_SetPlayerAllianceorg = NULL;
GAME_SetPlayerAlliance GAME_SetPlayerAllianceold = NULL;

void __cdecl GAME_SetPlayerAlliancemy( HPLAYER sourcePlayer , HPLAYER otherPlayer , HALLIANCETYPE whichAllianceSetting , BOOL value )
{
	fprintf_s( logfile , "%s" , "SetPlayerAlliancemy\n" );
	fflush( logfile );

	GAME_SetPlayerAllianceold( sourcePlayer , otherPlayer , whichAllianceSetting , value );
	fprintf_s( logfile , "%s:[-->GAME_SetPlayerAlliance<--  sourcePlayer: %X otherPlayer: %X whichAllianceSetting: %X value: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , sourcePlayer , otherPlayer , whichAllianceSetting , value ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPlayerColor )( HPLAYER whichPlayer , HPLAYERCOLOR color );
GAME_SetPlayerColor GAME_SetPlayerColororg = NULL;
GAME_SetPlayerColor GAME_SetPlayerColorold = NULL;

void __cdecl GAME_SetPlayerColormy( HPLAYER whichPlayer , HPLAYERCOLOR color )
{
	fprintf_s( logfile , "%s" , "SetPlayerColormy\n" );
	fflush( logfile );

	GAME_SetPlayerColorold( whichPlayer , color );
	fprintf_s( logfile , "%s:[-->GAME_SetPlayerColor<--  whichPlayer: %X color: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , color );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPlayerController )( HPLAYER whichPlayer , HMAPCONTROL controlType );
GAME_SetPlayerController GAME_SetPlayerControllerorg = NULL;
GAME_SetPlayerController GAME_SetPlayerControllerold = NULL;

void __cdecl GAME_SetPlayerControllermy( HPLAYER whichPlayer , HMAPCONTROL controlType )
{
	fprintf_s( logfile , "%s\n" , "SetPlayerControllermy" );
	fflush( logfile );

	GAME_SetPlayerControllerold( whichPlayer , controlType );
	fprintf_s( logfile , "%s:[-->GAME_SetPlayerController<--  whichPlayer: %X controlType: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , controlType );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPlayerHandicap )( HPLAYER whichPlayer , float *handicap );
GAME_SetPlayerHandicap GAME_SetPlayerHandicaporg = NULL;
GAME_SetPlayerHandicap GAME_SetPlayerHandicapold = NULL;

void __cdecl GAME_SetPlayerHandicapmy( HPLAYER whichPlayer , float *handicap )
{
	fprintf_s( logfile , "%s\n" , "SetPlayerHandicapmy" );
	fflush( logfile );

	GAME_SetPlayerHandicapold( whichPlayer , handicap );
	fprintf_s( logfile , "%s:[-->GAME_SetPlayerHandicap<--  whichPlayer: %X handicap: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , *( float * ) handicap );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPlayerHandicapXP )( HPLAYER whichPlayer , float *handicap );
GAME_SetPlayerHandicapXP GAME_SetPlayerHandicapXPorg = NULL;
GAME_SetPlayerHandicapXP GAME_SetPlayerHandicapXPold = NULL;

void __cdecl GAME_SetPlayerHandicapXPmy( HPLAYER whichPlayer , float *handicap )
{
	fprintf_s( logfile , "%s\n" , "SetPlayerHandicapXPmy" );
	fflush( logfile );

	GAME_SetPlayerHandicapXPold( whichPlayer , handicap );
	fprintf_s( logfile , "%s:[-->GAME_SetPlayerHandicapXP<--  whichPlayer: %X handicap: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , *( float * ) handicap );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPlayerName )( HPLAYER whichPlayer , void * name );
GAME_SetPlayerName GAME_SetPlayerNameorg = NULL;
GAME_SetPlayerName GAME_SetPlayerNameold = NULL;

void __cdecl GAME_SetPlayerNamemy( HPLAYER whichPlayer , void * name )
{
	fprintf_s( logfile , "%s\n" , "SetPlayerNamemy" );
	fflush( logfile );

	GAME_SetPlayerNameold( whichPlayer , name );
	fprintf_s( logfile , "%s:[-->GAME_SetPlayerName<--  whichPlayer: %X name: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , jassgetchar( name ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPlayerOnScoreScreen )( HPLAYER whichPlayer , BOOL flag );
GAME_SetPlayerOnScoreScreen GAME_SetPlayerOnScoreScreenorg = NULL;
GAME_SetPlayerOnScoreScreen GAME_SetPlayerOnScoreScreenold = NULL;

void __cdecl GAME_SetPlayerOnScoreScreenmy( HPLAYER whichPlayer , BOOL flag )
{
	fprintf_s( logfile , "%s" , "SetPlayerOnScoreScreenmy\n" );
	fflush( logfile );

	GAME_SetPlayerOnScoreScreenold( whichPlayer , flag );
	fprintf_s( logfile , "%s:[-->GAME_SetPlayerOnScoreScreen<--  whichPlayer: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPlayerRacePreference )( HPLAYER whichPlayer , HRACEPREFERENCE whichRacePreference );
GAME_SetPlayerRacePreference GAME_SetPlayerRacePreferenceorg = NULL;
GAME_SetPlayerRacePreference GAME_SetPlayerRacePreferenceold = NULL;

void __cdecl GAME_SetPlayerRacePreferencemy( HPLAYER whichPlayer , HRACEPREFERENCE whichRacePreference )
{
	fprintf_s( logfile , "%s" , "SetPlayerRacePreferencemy\n" );
	fflush( logfile );

	GAME_SetPlayerRacePreferenceold( whichPlayer , whichRacePreference );
	fprintf_s( logfile , "%s:[-->GAME_SetPlayerRacePreference<--  whichPlayer: %X whichRacePreference: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , whichRacePreference );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPlayerRaceSelectable )( HPLAYER whichPlayer , BOOL value );
GAME_SetPlayerRaceSelectable GAME_SetPlayerRaceSelectableorg = NULL;
GAME_SetPlayerRaceSelectable GAME_SetPlayerRaceSelectableold = NULL;

void __cdecl GAME_SetPlayerRaceSelectablemy( HPLAYER whichPlayer , BOOL value )
{
	fprintf_s( logfile , "%s\n" , "SetPlayerRaceSelectablemy" );
	fflush( logfile );

	GAME_SetPlayerRaceSelectableold( whichPlayer , value );
	fprintf_s( logfile , "%s:[-->GAME_SetPlayerRaceSelectable<--  whichPlayer: %X value: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , value ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPlayerStartLocation )( HPLAYER whichPlayer , int startLocIndex );
GAME_SetPlayerStartLocation GAME_SetPlayerStartLocationorg = NULL;
GAME_SetPlayerStartLocation GAME_SetPlayerStartLocationold = NULL;

void __cdecl GAME_SetPlayerStartLocationmy( HPLAYER whichPlayer , int startLocIndex )
{
	fprintf_s( logfile , "%s" , "SetPlayerStartLocationmy\n" );
	fflush( logfile );

	GAME_SetPlayerStartLocationold( whichPlayer , startLocIndex );
	fprintf_s( logfile , "%s:[-->GAME_SetPlayerStartLocation<--  whichPlayer: %X startLocIndex: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , startLocIndex );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPlayerState )( HPLAYER whichPlayer , HPLAYERSTATE whichPlayerState , int value );
GAME_SetPlayerState GAME_SetPlayerStateorg = NULL;
GAME_SetPlayerState GAME_SetPlayerStateold = NULL;

void __cdecl GAME_SetPlayerStatemy( HPLAYER whichPlayer , HPLAYERSTATE whichPlayerState , int value )
{
	fprintf_s( logfile , "%s\n" , "SetPlayerStatemy" );
	fflush( logfile );

	GAME_SetPlayerStateold( whichPlayer , whichPlayerState , value );
	fprintf_s( logfile , "%s:[-->GAME_SetPlayerState<--  whichPlayer: %X whichPlayerState: %X value: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , whichPlayerState , value );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPlayerTaxRate )( HPLAYER sourcePlayer , HPLAYER otherPlayer , HPLAYERSTATE whichResource , int rate );
GAME_SetPlayerTaxRate GAME_SetPlayerTaxRateorg = NULL;
GAME_SetPlayerTaxRate GAME_SetPlayerTaxRateold = NULL;

void __cdecl GAME_SetPlayerTaxRatemy( HPLAYER sourcePlayer , HPLAYER otherPlayer , HPLAYERSTATE whichResource , int rate )
{
	fprintf_s( logfile , "%s\n" , "SetPlayerTaxRatemy" );
	fflush( logfile );

	GAME_SetPlayerTaxRateold( sourcePlayer , otherPlayer , whichResource , rate );
	fprintf_s( logfile , "%s:[-->GAME_SetPlayerTaxRate<--  sourcePlayer: %X otherPlayer: %X whichResource: %X rate: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , sourcePlayer , otherPlayer , whichResource , rate );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPlayerTeam )( HPLAYER whichPlayer , int whichTeam );
GAME_SetPlayerTeam GAME_SetPlayerTeamorg = NULL;
GAME_SetPlayerTeam GAME_SetPlayerTeamold = NULL;

void __cdecl GAME_SetPlayerTeammy( HPLAYER whichPlayer , int whichTeam )
{
	fprintf_s( logfile , "%s\n" , "SetPlayerTeammy" );
	fflush( logfile );

	GAME_SetPlayerTeamold( whichPlayer , whichTeam );
	fprintf_s( logfile , "%s:[-->GAME_SetPlayerTeam<--  whichPlayer: %X whichTeam: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , whichTeam );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPlayerTechMaxAllowed )( HPLAYER whichPlayer , int techid , int maximum );
GAME_SetPlayerTechMaxAllowed GAME_SetPlayerTechMaxAllowedorg = NULL;
GAME_SetPlayerTechMaxAllowed GAME_SetPlayerTechMaxAllowedold = NULL;

void __cdecl GAME_SetPlayerTechMaxAllowedmy( HPLAYER whichPlayer , int techid , int maximum )
{
	fprintf_s( logfile , "%s\n" , "SetPlayerTechMaxAllowedmy" );
	fflush( logfile );

	GAME_SetPlayerTechMaxAllowedold( whichPlayer , techid , maximum );
	fprintf_s( logfile , "%s:[-->GAME_SetPlayerTechMaxAllowed<--  whichPlayer: %X techid: %i maximum: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , techid , maximum );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPlayerTechResearched )( HPLAYER whichPlayer , int techid , int setToLevel );
GAME_SetPlayerTechResearched GAME_SetPlayerTechResearchedorg = NULL;
GAME_SetPlayerTechResearched GAME_SetPlayerTechResearchedold = NULL;

void __cdecl GAME_SetPlayerTechResearchedmy( HPLAYER whichPlayer , int techid , int setToLevel )
{
	fprintf_s( logfile , "%s\n" , "SetPlayerTechResearchedmy" );
	fflush( logfile );

	GAME_SetPlayerTechResearchedold( whichPlayer , techid , setToLevel );
	fprintf_s( logfile , "%s:[-->GAME_SetPlayerTechResearched<--  whichPlayer: %X techid: %i setToLevel: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , techid , setToLevel );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPlayerUnitsOwner )( HPLAYER whichPlayer , int newOwner );
GAME_SetPlayerUnitsOwner GAME_SetPlayerUnitsOwnerorg = NULL;
GAME_SetPlayerUnitsOwner GAME_SetPlayerUnitsOwnerold = NULL;

void __cdecl GAME_SetPlayerUnitsOwnermy( HPLAYER whichPlayer , int newOwner )
{
	fprintf_s( logfile , "%s\n" , "SetPlayerUnitsOwnermy" );
	fflush( logfile );

	GAME_SetPlayerUnitsOwnerold( whichPlayer , newOwner );
	fprintf_s( logfile , "%s:[-->GAME_SetPlayerUnitsOwner<--  whichPlayer: %X newOwner: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPlayer , newOwner );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetPlayers )( int playercount );
GAME_SetPlayers GAME_SetPlayersorg = NULL;
GAME_SetPlayers GAME_SetPlayersold = NULL;

void __cdecl GAME_SetPlayersmy( int playercount )
{
	fprintf_s( logfile , "%s\n" , "SetPlayersmy" );
	fflush( logfile );

	GAME_SetPlayersold( playercount );
	fprintf_s( logfile , "%s:[-->GAME_SetPlayers<--  playercount: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , playercount );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_SetProduce )( int arg1 , int arg2 , int arg3 );
GAME_SetProduce GAME_SetProduceorg = NULL;
GAME_SetProduce GAME_SetProduceold = NULL;

BOOL __cdecl GAME_SetProducemy( int arg1 , int arg2 , int arg3 )
{
	fprintf_s( logfile , "%s\n" , "SetProducemy" );
	fflush( logfile );

	BOOL retvalue = GAME_SetProduceold( arg1 , arg2 , arg3 );
	fprintf_s( logfile , "%s:[-->GAME_SetProduce<--  arg1: %i arg2: %i arg3: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , arg1 , arg2 , arg3 , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_SetRandomPaths )( BOOL arg1 );
GAME_SetRandomPaths GAME_SetRandomPathsorg = NULL;
GAME_SetRandomPaths GAME_SetRandomPathsold = NULL;

void __cdecl GAME_SetRandomPathsmy( BOOL arg1 )
{
	fprintf_s( logfile , "%s" , "SetRandomPathsmy\n" );
	fflush( logfile );

	GAME_SetRandomPathsold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetRandomPaths<--  arg1: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetRandomSeed )( int seed );
GAME_SetRandomSeed GAME_SetRandomSeedorg = NULL;
GAME_SetRandomSeed GAME_SetRandomSeedold = NULL;

void __cdecl GAME_SetRandomSeedmy( int seed )
{
	fprintf_s( logfile , "%s" , "SetRandomSeedmy\n" );
	fflush( logfile );

	GAME_SetRandomSeedold( seed );
	fprintf_s( logfile , "%s:[-->GAME_SetRandomSeed<--  seed: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , seed );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetRect )( HRECT whichRect , float *minx , float *miny , float *maxx , float *maxy );
GAME_SetRect GAME_SetRectorg = NULL;
GAME_SetRect GAME_SetRectold = NULL;

void __cdecl GAME_SetRectmy( HRECT whichRect , float *minx , float *miny , float *maxx , float *maxy )
{
	fprintf_s( logfile , "%s\n" , "SetRectmy" );
	fflush( logfile );

	GAME_SetRectold( whichRect , minx , miny , maxx , maxy );
	fprintf_s( logfile , "%s:[-->GAME_SetRect<--  whichRect: %X minx: %f miny: %f maxx: %f maxy: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichRect , *( float * ) minx , *( float * ) miny , *( float * ) maxx , *( float * ) maxy );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetRectFromLoc )( HRECT whichRect , HLOCATION min , HLOCATION max );
GAME_SetRectFromLoc GAME_SetRectFromLocorg = NULL;
GAME_SetRectFromLoc GAME_SetRectFromLocold = NULL;

void __cdecl GAME_SetRectFromLocmy( HRECT whichRect , HLOCATION min , HLOCATION max )
{
	fprintf_s( logfile , "%s\n" , "SetRectFromLocmy" );
	fflush( logfile );

	GAME_SetRectFromLocold( whichRect , min , max );
	fprintf_s( logfile , "%s:[-->GAME_SetRectFromLoc<--  whichRect: %X min: %X max: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichRect , min , max );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetReplacementCount )( int arg1 );
GAME_SetReplacementCount GAME_SetReplacementCountorg = NULL;
GAME_SetReplacementCount GAME_SetReplacementCountold = NULL;

void __cdecl GAME_SetReplacementCountmy( int arg1 )
{
	fprintf_s( logfile , "%s\n" , "SetReplacementCountmy" );
	fflush( logfile );

	GAME_SetReplacementCountold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetReplacementCount<--  arg1: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetReservedLocalHeroButtons )( int reserved );
GAME_SetReservedLocalHeroButtons GAME_SetReservedLocalHeroButtonsorg = NULL;
GAME_SetReservedLocalHeroButtons GAME_SetReservedLocalHeroButtonsold = NULL;

void __cdecl GAME_SetReservedLocalHeroButtonsmy( int reserved )
{
	fprintf_s( logfile , "%s\n" , "SetReservedLocalHeroButtonsmy" );
	fflush( logfile );

	GAME_SetReservedLocalHeroButtonsold( reserved );
	fprintf_s( logfile , "%s:[-->GAME_SetReservedLocalHeroButtons<--  reserved: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , reserved );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetResourceAmount )( HUNIT whichUnit , int amount );
GAME_SetResourceAmount GAME_SetResourceAmountorg = NULL;
GAME_SetResourceAmount GAME_SetResourceAmountold = NULL;

void __cdecl GAME_SetResourceAmountmy( HUNIT whichUnit , int amount )
{
	fprintf_s( logfile , "%s\n" , "SetResourceAmountmy" );
	fflush( logfile );

	GAME_SetResourceAmountold( whichUnit , amount );
	fprintf_s( logfile , "%s:[-->GAME_SetResourceAmount<--  whichUnit: %X amount: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , amount );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetResourceDensity )( HMAPDENSITY whichdensity );
GAME_SetResourceDensity GAME_SetResourceDensityorg = NULL;
GAME_SetResourceDensity GAME_SetResourceDensityold = NULL;

void __cdecl GAME_SetResourceDensitymy( HMAPDENSITY whichdensity )
{
	fprintf_s( logfile , "%s\n" , "SetResourceDensitymy" );
	fflush( logfile );

	GAME_SetResourceDensityold( whichdensity );
	fprintf_s( logfile , "%s:[-->GAME_SetResourceDensity<--  whichdensity: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichdensity );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetSkyModel )( void * skyModelFile );
GAME_SetSkyModel GAME_SetSkyModelorg = NULL;
GAME_SetSkyModel GAME_SetSkyModelold = NULL;

void __cdecl GAME_SetSkyModelmy( void * skyModelFile )
{
	fprintf_s( logfile , "%s\n" , "SetSkyModelmy" );
	fflush( logfile );

	GAME_SetSkyModelold( skyModelFile );
	fprintf_s( logfile , "%s:[-->GAME_SetSkyModel<--  skyModelFile: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( skyModelFile ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetSlowChopping )( BOOL arg1 );
GAME_SetSlowChopping GAME_SetSlowChoppingorg = NULL;
GAME_SetSlowChopping GAME_SetSlowChoppingold = NULL;

void __cdecl GAME_SetSlowChoppingmy( BOOL arg1 )
{
	fprintf_s( logfile , "%s" , "SetSlowChoppingmy\n" );
	fflush( logfile );

	GAME_SetSlowChoppingold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetSlowChopping<--  arg1: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetSmartArtillery )( BOOL arg1 );
GAME_SetSmartArtillery GAME_SetSmartArtilleryorg = NULL;
GAME_SetSmartArtillery GAME_SetSmartArtilleryold = NULL;

void __cdecl GAME_SetSmartArtillerymy( BOOL arg1 )
{
	fprintf_s( logfile , "%s" , "SetSmartArtillerymy\n" );
	fflush( logfile );

	GAME_SetSmartArtilleryold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetSmartArtillery<--  arg1: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetSoundChannel )( HSOUND soundHandle , int channel );
GAME_SetSoundChannel GAME_SetSoundChannelorg = NULL;
GAME_SetSoundChannel GAME_SetSoundChannelold = NULL;

void __cdecl GAME_SetSoundChannelmy( HSOUND soundHandle , int channel )
{
	fprintf_s( logfile , "%s" , "SetSoundChannelmy\n" );
	fflush( logfile );

	GAME_SetSoundChannelold( soundHandle , channel );
	fprintf_s( logfile , "%s:[-->GAME_SetSoundChannel<--  soundHandle: %X channel: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , soundHandle , channel );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetSoundConeAngles )( HSOUND soundHandle , float *inside , float *outside , int outsideVolume );
GAME_SetSoundConeAngles GAME_SetSoundConeAnglesorg = NULL;
GAME_SetSoundConeAngles GAME_SetSoundConeAnglesold = NULL;

void __cdecl GAME_SetSoundConeAnglesmy( HSOUND soundHandle , float *inside , float *outside , int outsideVolume )
{
	fprintf_s( logfile , "%s\n" , "SetSoundConeAnglesmy" );
	fflush( logfile );

	GAME_SetSoundConeAnglesold( soundHandle , inside , outside , outsideVolume );
	fprintf_s( logfile , "%s:[-->GAME_SetSoundConeAngles<--  soundHandle: %X inside: %f outside: %f outsideVolume: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , soundHandle , *( float * ) inside , *( float * ) outside , outsideVolume );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetSoundConeOrientation )( HSOUND soundHandle , float *x , float *y , float *z );
GAME_SetSoundConeOrientation GAME_SetSoundConeOrientationorg = NULL;
GAME_SetSoundConeOrientation GAME_SetSoundConeOrientationold = NULL;

void __cdecl GAME_SetSoundConeOrientationmy( HSOUND soundHandle , float *x , float *y , float *z )
{
	fprintf_s( logfile , "%s\n" , "SetSoundConeOrientationmy" );
	fflush( logfile );

	GAME_SetSoundConeOrientationold( soundHandle , x , y , z );
	fprintf_s( logfile , "%s:[-->GAME_SetSoundConeOrientation<--  soundHandle: %X x: %f y: %f z: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , soundHandle , *( float * ) x , *( float * ) y , *( float * ) z );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetSoundDistanceCutoff )( HSOUND soundHandle , float *cutoff );
GAME_SetSoundDistanceCutoff GAME_SetSoundDistanceCutofforg = NULL;
GAME_SetSoundDistanceCutoff GAME_SetSoundDistanceCutoffold = NULL;

void __cdecl GAME_SetSoundDistanceCutoffmy( HSOUND soundHandle , float *cutoff )
{
	fprintf_s( logfile , "%s\n" , "SetSoundDistanceCutoffmy" );
	fflush( logfile );

	GAME_SetSoundDistanceCutoffold( soundHandle , cutoff );
	fprintf_s( logfile , "%s:[-->GAME_SetSoundDistanceCutoff<--  soundHandle: %X cutoff: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , soundHandle , *( float * ) cutoff );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetSoundDistances )( HSOUND soundHandle , float *minDist , float *maxDist );
GAME_SetSoundDistances GAME_SetSoundDistancesorg = NULL;
GAME_SetSoundDistances GAME_SetSoundDistancesold = NULL;

void __cdecl GAME_SetSoundDistancesmy( HSOUND soundHandle , float *minDist , float *maxDist )
{
	fprintf_s( logfile , "%s\n" , "SetSoundDistancesmy" );
	fflush( logfile );

	GAME_SetSoundDistancesold( soundHandle , minDist , maxDist );
	fprintf_s( logfile , "%s:[-->GAME_SetSoundDistances<--  soundHandle: %X minDist: %f maxDist: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , soundHandle , *( float * ) minDist , *( float * ) maxDist );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetSoundDuration )( HSOUND soundHandle , int duration );
GAME_SetSoundDuration GAME_SetSoundDurationorg = NULL;
GAME_SetSoundDuration GAME_SetSoundDurationold = NULL;

void __cdecl GAME_SetSoundDurationmy( HSOUND soundHandle , int duration )
{
	fprintf_s( logfile , "%s\n" , "SetSoundDurationmy" );
	fflush( logfile );

	GAME_SetSoundDurationold( soundHandle , duration );
	fprintf_s( logfile , "%s:[-->GAME_SetSoundDuration<--  soundHandle: %X duration: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , soundHandle , duration );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetSoundParamsFromLabel )( HSOUND soundHandle , void * soundLabel );
GAME_SetSoundParamsFromLabel GAME_SetSoundParamsFromLabelorg = NULL;
GAME_SetSoundParamsFromLabel GAME_SetSoundParamsFromLabelold = NULL;

void __cdecl GAME_SetSoundParamsFromLabelmy( HSOUND soundHandle , void * soundLabel )
{
	fprintf_s( logfile , "%s\n" , "SetSoundParamsFromLabelmy" );
	fflush( logfile );

	GAME_SetSoundParamsFromLabelold( soundHandle , soundLabel );
	fprintf_s( logfile , "%s:[-->GAME_SetSoundParamsFromLabel<--  soundHandle: %X soundLabel: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , soundHandle , jassgetchar( soundLabel ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetSoundPitch )( HSOUND soundHandle , float *pitch );
GAME_SetSoundPitch GAME_SetSoundPitchorg = NULL;
GAME_SetSoundPitch GAME_SetSoundPitchold = NULL;

void __cdecl GAME_SetSoundPitchmy( HSOUND soundHandle , float *pitch )
{
	fprintf_s( logfile , "%s" , "SetSoundPitchmy\n" );
	fflush( logfile );

	GAME_SetSoundPitchold( soundHandle , pitch );
	fprintf_s( logfile , "%s:[-->GAME_SetSoundPitch<--  soundHandle: %X pitch: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , soundHandle , *( float * ) pitch );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetSoundPlayPosition )( HSOUND soundHandle , int millisecs );
GAME_SetSoundPlayPosition GAME_SetSoundPlayPositionorg = NULL;
GAME_SetSoundPlayPosition GAME_SetSoundPlayPositionold = NULL;

void __cdecl GAME_SetSoundPlayPositionmy( HSOUND soundHandle , int millisecs )
{
	fprintf_s( logfile , "%s\n" , "SetSoundPlayPositionmy" );
	fflush( logfile );

	GAME_SetSoundPlayPositionold( soundHandle , millisecs );
	fprintf_s( logfile , "%s:[-->GAME_SetSoundPlayPosition<--  soundHandle: %X millisecs: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , soundHandle , millisecs );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetSoundPosition )( HSOUND soundHandle , float *x , float *y , float *z );
GAME_SetSoundPosition GAME_SetSoundPositionorg = NULL;
GAME_SetSoundPosition GAME_SetSoundPositionold = NULL;

void __cdecl GAME_SetSoundPositionmy( HSOUND soundHandle , float *x , float *y , float *z )
{
	fprintf_s( logfile , "%s\n" , "SetSoundPositionmy" );
	fflush( logfile );

	GAME_SetSoundPositionold( soundHandle , x , y , z );
	fprintf_s( logfile , "%s:[-->GAME_SetSoundPosition<--  soundHandle: %X x: %f y: %f z: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , soundHandle , *( float * ) x , *( float * ) y , *( float * ) z );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetSoundVelocity )( HSOUND soundHandle , float *x , float *y , float *z );
GAME_SetSoundVelocity GAME_SetSoundVelocityorg = NULL;
GAME_SetSoundVelocity GAME_SetSoundVelocityold = NULL;

void __cdecl GAME_SetSoundVelocitymy( HSOUND soundHandle , float *x , float *y , float *z )
{
	fprintf_s( logfile , "%s\n" , "SetSoundVelocitymy" );
	fflush( logfile );

	GAME_SetSoundVelocityold( soundHandle , x , y , z );
	fprintf_s( logfile , "%s:[-->GAME_SetSoundVelocity<--  soundHandle: %X x: %f y: %f z: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , soundHandle , *( float * ) x , *( float * ) y , *( float * ) z );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetSoundVolume )( HSOUND soundHandle , int volume );
GAME_SetSoundVolume GAME_SetSoundVolumeorg = NULL;
GAME_SetSoundVolume GAME_SetSoundVolumeold = NULL;

void __cdecl GAME_SetSoundVolumemy( HSOUND soundHandle , int volume )
{
	fprintf_s( logfile , "%s\n" , "SetSoundVolumemy" );
	fflush( logfile );

	GAME_SetSoundVolumeold( soundHandle , volume );
	fprintf_s( logfile , "%s:[-->GAME_SetSoundVolume<--  soundHandle: %X volume: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , soundHandle , volume );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetStackedSound )( void * arg1 , float *arg2 , float *arg3 );
GAME_SetStackedSound GAME_SetStackedSoundorg = NULL;
GAME_SetStackedSound GAME_SetStackedSoundold = NULL;

void __cdecl GAME_SetStackedSoundmy( void * arg1 , float *arg2 , float *arg3 )
{
	fprintf_s( logfile , "%s\n" , "SetStackedSoundmy" );
	fflush( logfile );

	GAME_SetStackedSoundold( arg1 , arg2 , arg3 );
	fprintf_s( logfile , "%s:[-->GAME_SetStackedSound<--  arg1: \"%s\" arg2: %f arg3: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( arg1 ) , *( float * ) arg2 , *( float * ) arg3 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetStackedSoundRect )( void * arg1 , HRECT arg2 );
GAME_SetStackedSoundRect GAME_SetStackedSoundRectorg = NULL;
GAME_SetStackedSoundRect GAME_SetStackedSoundRectold = NULL;

void __cdecl GAME_SetStackedSoundRectmy( void * arg1 , HRECT arg2 )
{
	fprintf_s( logfile , "%s" , "SetStackedSoundRectmy\n" );
	fflush( logfile );

	GAME_SetStackedSoundRectold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_SetStackedSoundRect<--  arg1: \"%s\" arg2: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , jassgetchar( arg1 ) , arg2 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetStagePoint )( float *arg1 , float *arg2 );
GAME_SetStagePoint GAME_SetStagePointorg = NULL;
GAME_SetStagePoint GAME_SetStagePointold = NULL;

void __cdecl GAME_SetStagePointmy( float *arg1 , float *arg2 )
{
	fprintf_s( logfile , "%s" , "SetStagePointmy\n" );
	fflush( logfile );

	GAME_SetStagePointold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_SetStagePoint<--  arg1: %f arg2: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) arg1 , *( float * ) arg2 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetStartLocPrio )( int whichStartLoc , int prioSlotIndex , int otherStartLocIndex , HSTARTLOCPRIO priority );
GAME_SetStartLocPrio GAME_SetStartLocPrioorg = NULL;
GAME_SetStartLocPrio GAME_SetStartLocPrioold = NULL;

void __cdecl GAME_SetStartLocPriomy( int whichStartLoc , int prioSlotIndex , int otherStartLocIndex , HSTARTLOCPRIO priority )
{
	fprintf_s( logfile , "%s\n" , "SetStartLocPriomy" );
	fflush( logfile );

	GAME_SetStartLocPrioold( whichStartLoc , prioSlotIndex , otherStartLocIndex , priority );
	fprintf_s( logfile , "%s:[-->GAME_SetStartLocPrio<--  whichStartLoc: %i prioSlotIndex: %i otherStartLocIndex: %i priority: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichStartLoc , prioSlotIndex , otherStartLocIndex , priority );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetStartLocPrioCount )( int whichStartLoc , int prioSlotCount );
GAME_SetStartLocPrioCount GAME_SetStartLocPrioCountorg = NULL;
GAME_SetStartLocPrioCount GAME_SetStartLocPrioCountold = NULL;

void __cdecl GAME_SetStartLocPrioCountmy( int whichStartLoc , int prioSlotCount )
{
	fprintf_s( logfile , "%s\n" , "SetStartLocPrioCountmy" );
	fflush( logfile );

	GAME_SetStartLocPrioCountold( whichStartLoc , prioSlotCount );
	fprintf_s( logfile , "%s:[-->GAME_SetStartLocPrioCount<--  whichStartLoc: %i prioSlotCount: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichStartLoc , prioSlotCount );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTargetHeroes )( BOOL arg1 );
GAME_SetTargetHeroes GAME_SetTargetHeroesorg = NULL;
GAME_SetTargetHeroes GAME_SetTargetHeroesold = NULL;

void __cdecl GAME_SetTargetHeroesmy( BOOL arg1 )
{
	fprintf_s( logfile , "%s\n" , "SetTargetHeroesmy" );
	fflush( logfile );

	GAME_SetTargetHeroesold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetTargetHeroes<--  arg1: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTeams )( int teamcount );
GAME_SetTeams GAME_SetTeamsorg = NULL;
GAME_SetTeams GAME_SetTeamsold = NULL;

void __cdecl GAME_SetTeamsmy( int teamcount )
{
	fprintf_s( logfile , "%s" , "SetTeamsmy\n" );
	fflush( logfile );

	GAME_SetTeamsold( teamcount );
	fprintf_s( logfile , "%s:[-->GAME_SetTeams<--  teamcount: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , teamcount );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTerrainFog )( float *a , float *b , float *c , float *d , float *e );
GAME_SetTerrainFog GAME_SetTerrainFogorg = NULL;
GAME_SetTerrainFog GAME_SetTerrainFogold = NULL;

void __cdecl GAME_SetTerrainFogmy( float *a , float *b , float *c , float *d , float *e )
{
	fprintf_s( logfile , "%s\n" , "SetTerrainFogmy" );
	fflush( logfile );

	GAME_SetTerrainFogold( a , b , c , d , e );
	fprintf_s( logfile , "%s:[-->GAME_SetTerrainFog<--  a: %f b: %f c: %f d: %f e: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) a , *( float * ) b , *( float * ) c , *( float * ) d , *( float * ) e );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTerrainFogEx )( int style , float *zstart , float *zend , float *density , float *red , float *green , float *blue );
GAME_SetTerrainFogEx GAME_SetTerrainFogExorg = NULL;
GAME_SetTerrainFogEx GAME_SetTerrainFogExold = NULL;

void __cdecl GAME_SetTerrainFogExmy( int style , float *zstart , float *zend , float *density , float *red , float *green , float *blue )
{
	fprintf_s( logfile , "%s\n" , "SetTerrainFogExmy" );
	fflush( logfile );

	GAME_SetTerrainFogExold( style , zstart , zend , density , red , green , blue );
	fprintf_s( logfile , "%s:[-->GAME_SetTerrainFogEx<--  style: %i zstart: %f zend: %f density: %f red: %f green: %f blue: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , style , *( float * ) zstart , *( float * ) zend , *( float * ) density , *( float * ) red , *( float * ) green , *( float * ) blue );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTerrainPathable )( float *x , float *y , HPATHINGTYPE t , BOOL flag );
GAME_SetTerrainPathable GAME_SetTerrainPathableorg = NULL;
GAME_SetTerrainPathable GAME_SetTerrainPathableold = NULL;

void __cdecl GAME_SetTerrainPathablemy( float *x , float *y , HPATHINGTYPE t , BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "SetTerrainPathablemy" );
	fflush( logfile );

	GAME_SetTerrainPathableold( x , y , t , flag );
	fprintf_s( logfile , "%s:[-->GAME_SetTerrainPathable<--  x: %f y: %f t: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , t , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTerrainType )( float *x , float *y , int terrainType , int variation , int area , int shape );
GAME_SetTerrainType GAME_SetTerrainTypeorg = NULL;
GAME_SetTerrainType GAME_SetTerrainTypeold = NULL;

void __cdecl GAME_SetTerrainTypemy( float *x , float *y , int terrainType , int variation , int area , int shape )
{
	fprintf_s( logfile , "%s" , "SetTerrainTypemy\n" );
	fflush( logfile );

	GAME_SetTerrainTypeold( x , y , terrainType , variation , area , shape );
	fprintf_s( logfile , "%s:[-->GAME_SetTerrainType<--  x: %f y: %f terrainType: %i variation: %i area: %i shape: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , terrainType , variation , area , shape );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTextTagAge )( HTEXTTAG t , float *age );
GAME_SetTextTagAge GAME_SetTextTagAgeorg = NULL;
GAME_SetTextTagAge GAME_SetTextTagAgeold = NULL;

void __cdecl GAME_SetTextTagAgemy( HTEXTTAG t , float *age )
{
	fprintf_s( logfile , "%s\n" , "SetTextTagAgemy" );
	fflush( logfile );

	GAME_SetTextTagAgeold( t , age );
	fprintf_s( logfile , "%s:[-->GAME_SetTextTagAge<--  t: %X age: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , t , *( float * ) age );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTextTagColor )( HTEXTTAG t , int red , int green , int blue , int alpha );
GAME_SetTextTagColor GAME_SetTextTagColororg = NULL;
GAME_SetTextTagColor GAME_SetTextTagColorold = NULL;

void __cdecl GAME_SetTextTagColormy( HTEXTTAG t , int red , int green , int blue , int alpha )
{
	fprintf_s( logfile , "%s\n" , "SetTextTagColormy" );
	fflush( logfile );

	GAME_SetTextTagColorold( t , red , green , blue , alpha );
	fprintf_s( logfile , "%s:[-->GAME_SetTextTagColor<--  t: %X red: %i green: %i blue: %i alpha: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , t , red , green , blue , alpha );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTextTagFadepoint )( HTEXTTAG t , float *fadepoint );
GAME_SetTextTagFadepoint GAME_SetTextTagFadepointorg = NULL;
GAME_SetTextTagFadepoint GAME_SetTextTagFadepointold = NULL;

void __cdecl GAME_SetTextTagFadepointmy( HTEXTTAG t , float *fadepoint )
{
	fprintf_s( logfile , "%s\n" , "SetTextTagFadepointmy" );
	fflush( logfile );

	GAME_SetTextTagFadepointold( t , fadepoint );
	fprintf_s( logfile , "%s:[-->GAME_SetTextTagFadepoint<--  t: %X fadepoint: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , t , *( float * ) fadepoint );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTextTagLifespan )( HTEXTTAG t , float *lifespan );
GAME_SetTextTagLifespan GAME_SetTextTagLifespanorg = NULL;
GAME_SetTextTagLifespan GAME_SetTextTagLifespanold = NULL;

void __cdecl GAME_SetTextTagLifespanmy( HTEXTTAG t , float *lifespan )
{
	fprintf_s( logfile , "%s\n" , "SetTextTagLifespanmy" );
	fflush( logfile );

	GAME_SetTextTagLifespanold( t , lifespan );
	fprintf_s( logfile , "%s:[-->GAME_SetTextTagLifespan<--  t: %X lifespan: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , t , *( float * ) lifespan );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTextTagPermanent )( HTEXTTAG t , BOOL flag );
GAME_SetTextTagPermanent GAME_SetTextTagPermanentorg = NULL;
GAME_SetTextTagPermanent GAME_SetTextTagPermanentold = NULL;

void __cdecl GAME_SetTextTagPermanentmy( HTEXTTAG t , BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "SetTextTagPermanentmy" );
	fflush( logfile );

	GAME_SetTextTagPermanentold( t , flag );
	fprintf_s( logfile , "%s:[-->GAME_SetTextTagPermanent<--  t: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , t , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTextTagPos )( HTEXTTAG t , float *x , float *y , float *heightOffset );
GAME_SetTextTagPos GAME_SetTextTagPosorg = NULL;
GAME_SetTextTagPos GAME_SetTextTagPosold = NULL;

void __cdecl GAME_SetTextTagPosmy( HTEXTTAG t , float *x , float *y , float *heightOffset )
{
	fprintf_s( logfile , "%s" , "SetTextTagPosmy\n" );
	fflush( logfile );

	GAME_SetTextTagPosold( t , x , y , heightOffset );
	fprintf_s( logfile , "%s:[-->GAME_SetTextTagPos<--  t: %X x: %f y: %f heightOffset: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , t , *( float * ) x , *( float * ) y , *( float * ) heightOffset );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTextTagPosUnit )( HTEXTTAG t , HUNIT whichUnit , float *heightOffset );
GAME_SetTextTagPosUnit GAME_SetTextTagPosUnitorg = NULL;
GAME_SetTextTagPosUnit GAME_SetTextTagPosUnitold = NULL;

void __cdecl GAME_SetTextTagPosUnitmy( HTEXTTAG t , HUNIT whichUnit , float *heightOffset )
{
	fprintf_s( logfile , "%s\n" , "SetTextTagPosUnitmy" );
	fflush( logfile );

	GAME_SetTextTagPosUnitold( t , whichUnit , heightOffset );
	fprintf_s( logfile , "%s:[-->GAME_SetTextTagPosUnit<--  t: %X whichUnit: %X heightOffset: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , t , whichUnit , *( float * ) heightOffset );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTextTagSuspended )( HTEXTTAG t , BOOL flag );
GAME_SetTextTagSuspended GAME_SetTextTagSuspendedorg = NULL;
GAME_SetTextTagSuspended GAME_SetTextTagSuspendedold = NULL;

void __cdecl GAME_SetTextTagSuspendedmy( HTEXTTAG t , BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "SetTextTagSuspendedmy" );
	fflush( logfile );

	GAME_SetTextTagSuspendedold( t , flag );
	fprintf_s( logfile , "%s:[-->GAME_SetTextTagSuspended<--  t: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , t , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTextTagText )( HTEXTTAG t , void * s , float *height );
GAME_SetTextTagText GAME_SetTextTagTextorg = NULL;
GAME_SetTextTagText GAME_SetTextTagTextold = NULL;

void __cdecl GAME_SetTextTagTextmy( HTEXTTAG t , void * s , float *height )
{
	fprintf_s( logfile , "%s" , "SetTextTagTextmy\n" );
	fflush( logfile );

	GAME_SetTextTagTextold( t , s , height );
	fprintf_s( logfile , "%s:[-->GAME_SetTextTagText<--  t: %X s: \"%s\" height: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , t , jassgetchar( s ) , *( float * ) height );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTextTagVelocity )( HTEXTTAG t , float *xvel , float *yvel );
GAME_SetTextTagVelocity GAME_SetTextTagVelocityorg = NULL;
GAME_SetTextTagVelocity GAME_SetTextTagVelocityold = NULL;

void __cdecl GAME_SetTextTagVelocitymy( HTEXTTAG t , float *xvel , float *yvel )
{
	fprintf_s( logfile , "%s" , "SetTextTagVelocitymy\n" );
	fflush( logfile );

	GAME_SetTextTagVelocityold( t , xvel , yvel );
	fprintf_s( logfile , "%s:[-->GAME_SetTextTagVelocity<--  t: %X xvel: %f yvel: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , t , *( float * ) xvel , *( float * ) yvel );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTextTagVisibility )( HTEXTTAG t , BOOL flag );
GAME_SetTextTagVisibility GAME_SetTextTagVisibilityorg = NULL;
GAME_SetTextTagVisibility GAME_SetTextTagVisibilityold = NULL;

void __cdecl GAME_SetTextTagVisibilitymy( HTEXTTAG t , BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "SetTextTagVisibilitymy" );
	fflush( logfile );

	GAME_SetTextTagVisibilityold( t , flag );
	fprintf_s( logfile , "%s:[-->GAME_SetTextTagVisibility<--  t: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , t , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetThematicMusicPlayPosition )( int millisecs );
GAME_SetThematicMusicPlayPosition GAME_SetThematicMusicPlayPositionorg = NULL;
GAME_SetThematicMusicPlayPosition GAME_SetThematicMusicPlayPositionold = NULL;

void __cdecl GAME_SetThematicMusicPlayPositionmy( int millisecs )
{
	fprintf_s( logfile , "%s" , "SetThematicMusicPlayPositionmy\n" );
	fflush( logfile );

	GAME_SetThematicMusicPlayPositionold( millisecs );
	fprintf_s( logfile , "%s:[-->GAME_SetThematicMusicPlayPosition<--  millisecs: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , millisecs );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTimeOfDayScale )( float *r );
GAME_SetTimeOfDayScale GAME_SetTimeOfDayScaleorg = NULL;
GAME_SetTimeOfDayScale GAME_SetTimeOfDayScaleold = NULL;

void __cdecl GAME_SetTimeOfDayScalemy( float *r )
{
	fprintf_s( logfile , "%s\n" , "SetTimeOfDayScalemy" );
	fflush( logfile );

	GAME_SetTimeOfDayScaleold( r );
	fprintf_s( logfile , "%s:[-->GAME_SetTimeOfDayScale<--  r: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) r );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetTutorialCleared )( BOOL cleared );
GAME_SetTutorialCleared GAME_SetTutorialClearedorg = NULL;
GAME_SetTutorialCleared GAME_SetTutorialClearedold = NULL;

void __cdecl GAME_SetTutorialClearedmy( BOOL cleared )
{
	fprintf_s( logfile , "%s\n" , "SetTutorialClearedmy" );
	fflush( logfile );

	GAME_SetTutorialClearedold( cleared );
	fprintf_s( logfile , "%s:[-->GAME_SetTutorialCleared<--  cleared: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , cleared ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUbersplatRender )( HUBERSPLAT whichSplat , BOOL flag );
GAME_SetUbersplatRender GAME_SetUbersplatRenderorg = NULL;
GAME_SetUbersplatRender GAME_SetUbersplatRenderold = NULL;

void __cdecl GAME_SetUbersplatRendermy( HUBERSPLAT whichSplat , BOOL flag )
{
	fprintf_s( logfile , "%s" , "SetUbersplatRendermy\n" );
	fflush( logfile );

	GAME_SetUbersplatRenderold( whichSplat , flag );
	fprintf_s( logfile , "%s:[-->GAME_SetUbersplatRender<--  whichSplat: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichSplat , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUbersplatRenderAlways )( HUBERSPLAT whichSplat , BOOL flag );
GAME_SetUbersplatRenderAlways GAME_SetUbersplatRenderAlwaysorg = NULL;
GAME_SetUbersplatRenderAlways GAME_SetUbersplatRenderAlwaysold = NULL;

void __cdecl GAME_SetUbersplatRenderAlwaysmy( HUBERSPLAT whichSplat , BOOL flag )
{
	fprintf_s( logfile , "%s" , "SetUbersplatRenderAlwaysmy\n" );
	fflush( logfile );

	GAME_SetUbersplatRenderAlwaysold( whichSplat , flag );
	fprintf_s( logfile , "%s:[-->GAME_SetUbersplatRenderAlways<--  whichSplat: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichSplat , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef int( __cdecl *GAME_SetUnitAbilityLevel )( HUNIT whichUnit , int abilcode , int level );
GAME_SetUnitAbilityLevel GAME_SetUnitAbilityLevelorg = NULL;
GAME_SetUnitAbilityLevel GAME_SetUnitAbilityLevelold = NULL;

int __cdecl GAME_SetUnitAbilityLevelmy( HUNIT whichUnit , int abilcode , int level )
{
	fprintf_s( logfile , "%s" , "SetUnitAbilityLevelmy\n" );
	fflush( logfile );

	int retvalue = GAME_SetUnitAbilityLevelold( whichUnit , abilcode , level );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitAbilityLevel<--  whichUnit: %X abilcode: %i level: %i] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichUnit , abilcode , level , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_SetUnitAcquireRange )( HUNIT whichUnit , float *newAcquireRange );
GAME_SetUnitAcquireRange GAME_SetUnitAcquireRangeorg = NULL;
GAME_SetUnitAcquireRange GAME_SetUnitAcquireRangeold = NULL;

void __cdecl GAME_SetUnitAcquireRangemy( HUNIT whichUnit , float *newAcquireRange )
{
	fprintf_s( logfile , "%s\n" , "SetUnitAcquireRangemy" );
	fflush( logfile );

	GAME_SetUnitAcquireRangeold( whichUnit , newAcquireRange );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitAcquireRange<--  whichUnit: %X newAcquireRange: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , *( float * ) newAcquireRange );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitAnimation )( HUNIT whichUnit , void * whichAnimation );
GAME_SetUnitAnimation GAME_SetUnitAnimationorg = NULL;
GAME_SetUnitAnimation GAME_SetUnitAnimationold = NULL;

void __cdecl GAME_SetUnitAnimationmy( HUNIT whichUnit , void * whichAnimation )
{
	fprintf_s( logfile , "%s\n" , "SetUnitAnimationmy" );
	fflush( logfile );

	GAME_SetUnitAnimationold( whichUnit , whichAnimation );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitAnimation<--  whichUnit: %X whichAnimation: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , jassgetchar( whichAnimation ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitAnimationByIndex )( HUNIT whichUnit , int whichAnimation );
GAME_SetUnitAnimationByIndex GAME_SetUnitAnimationByIndexorg = NULL;
GAME_SetUnitAnimationByIndex GAME_SetUnitAnimationByIndexold = NULL;

void __cdecl GAME_SetUnitAnimationByIndexmy( HUNIT whichUnit , int whichAnimation )
{
	fprintf_s( logfile , "%s" , "SetUnitAnimationByIndexmy\n" );
	fflush( logfile );

	GAME_SetUnitAnimationByIndexold( whichUnit , whichAnimation );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitAnimationByIndex<--  whichUnit: %X whichAnimation: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , whichAnimation );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitAnimationWithRarity )( HUNIT whichUnit , void * whichAnimation , HRARITYCONTROL rarity );
GAME_SetUnitAnimationWithRarity GAME_SetUnitAnimationWithRarityorg = NULL;
GAME_SetUnitAnimationWithRarity GAME_SetUnitAnimationWithRarityold = NULL;

void __cdecl GAME_SetUnitAnimationWithRaritymy( HUNIT whichUnit , void * whichAnimation , HRARITYCONTROL rarity )
{
	fprintf_s( logfile , "%s\n" , "SetUnitAnimationWithRaritymy" );
	fflush( logfile );

	GAME_SetUnitAnimationWithRarityold( whichUnit , whichAnimation , rarity );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitAnimationWithRarity<--  whichUnit: %X whichAnimation: \"%s\" rarity: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , jassgetchar( whichAnimation ) , rarity );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitBlendTime )( HUNIT whichUnit , float *blendTime );
GAME_SetUnitBlendTime GAME_SetUnitBlendTimeorg = NULL;
GAME_SetUnitBlendTime GAME_SetUnitBlendTimeold = NULL;

void __cdecl GAME_SetUnitBlendTimemy( HUNIT whichUnit , float *blendTime )
{
	fprintf_s( logfile , "%s" , "SetUnitBlendTimemy\n" );
	fflush( logfile );

	GAME_SetUnitBlendTimeold( whichUnit , blendTime );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitBlendTime<--  whichUnit: %X blendTime: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , *( float * ) blendTime );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitColor )( HUNIT whichUnit , HPLAYERCOLOR whichColor );
GAME_SetUnitColor GAME_SetUnitColororg = NULL;
GAME_SetUnitColor GAME_SetUnitColorold = NULL;

void __cdecl GAME_SetUnitColormy( HUNIT whichUnit , HPLAYERCOLOR whichColor )
{
	fprintf_s( logfile , "%s\n" , "SetUnitColormy" );
	fflush( logfile );

	GAME_SetUnitColorold( whichUnit , whichColor );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitColor<--  whichUnit: %X whichColor: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , whichColor );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitCreepGuard )( HUNIT whichUnit , BOOL creepGuard );
GAME_SetUnitCreepGuard GAME_SetUnitCreepGuardorg = NULL;
GAME_SetUnitCreepGuard GAME_SetUnitCreepGuardold = NULL;

void __cdecl GAME_SetUnitCreepGuardmy( HUNIT whichUnit , BOOL creepGuard )
{
	fprintf_s( logfile , "%s\n" , "SetUnitCreepGuardmy" );
	fflush( logfile );

	GAME_SetUnitCreepGuardold( whichUnit , creepGuard );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitCreepGuard<--  whichUnit: %X creepGuard: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , creepGuard ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitExploded )( HUNIT whichUnit , BOOL exploded );
GAME_SetUnitExploded GAME_SetUnitExplodedorg = NULL;
GAME_SetUnitExploded GAME_SetUnitExplodedold = NULL;

void __cdecl GAME_SetUnitExplodedmy( HUNIT whichUnit , BOOL exploded )
{
	fprintf_s( logfile , "%s" , "SetUnitExplodedmy\n" );
	fflush( logfile );

	GAME_SetUnitExplodedold( whichUnit , exploded );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitExploded<--  whichUnit: %X exploded: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , exploded ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitFacing )( HUNIT whichUnit , float *facingAngle );
GAME_SetUnitFacing GAME_SetUnitFacingorg = NULL;
GAME_SetUnitFacing GAME_SetUnitFacingold = NULL;

void __cdecl GAME_SetUnitFacingmy( HUNIT whichUnit , float *facingAngle )
{
	fprintf_s( logfile , "%s" , "SetUnitFacingmy\n" );
	fflush( logfile );

	GAME_SetUnitFacingold( whichUnit , facingAngle );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitFacing<--  whichUnit: %X facingAngle: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , *( float * ) facingAngle );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitFacingTimed )( HUNIT whichUnit , float *facingAngle , float *duration );
GAME_SetUnitFacingTimed GAME_SetUnitFacingTimedorg = NULL;
GAME_SetUnitFacingTimed GAME_SetUnitFacingTimedold = NULL;

void __cdecl GAME_SetUnitFacingTimedmy( HUNIT whichUnit , float *facingAngle , float *duration )
{
	fprintf_s( logfile , "%s\n" , "SetUnitFacingTimedmy" );
	fflush( logfile );

	GAME_SetUnitFacingTimedold( whichUnit , facingAngle , duration );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitFacingTimed<--  whichUnit: %X facingAngle: %f duration: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , *( float * ) facingAngle , *( float * ) duration );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitFlyHeight )( HUNIT whichUnit , float *newHeight , float *rate );
GAME_SetUnitFlyHeight GAME_SetUnitFlyHeightorg = NULL;
GAME_SetUnitFlyHeight GAME_SetUnitFlyHeightold = NULL;

void __cdecl GAME_SetUnitFlyHeightmy( HUNIT whichUnit , float *newHeight , float *rate )
{
	fprintf_s( logfile , "%s\n" , "SetUnitFlyHeightmy" );
	fflush( logfile );

	GAME_SetUnitFlyHeightold( whichUnit , newHeight , rate );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitFlyHeight<--  whichUnit: %X newHeight: %f rate: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , *( float * ) newHeight , *( float * ) rate );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitFog )( float *a , float *b , float *c , float *d , float *e );
GAME_SetUnitFog GAME_SetUnitFogorg = NULL;
GAME_SetUnitFog GAME_SetUnitFogold = NULL;

void __cdecl GAME_SetUnitFogmy( float *a , float *b , float *c , float *d , float *e )
{
	fprintf_s( logfile , "%s\n" , "SetUnitFogmy" );
	fflush( logfile );

	GAME_SetUnitFogold( a , b , c , d , e );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitFog<--  a: %f b: %f c: %f d: %f e: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) a , *( float * ) b , *( float * ) c , *( float * ) d , *( float * ) e );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitInvulnerable )( HUNIT whichUnit , BOOL flag );
GAME_SetUnitInvulnerable GAME_SetUnitInvulnerableorg = NULL;
GAME_SetUnitInvulnerable GAME_SetUnitInvulnerableold = NULL;

void __cdecl GAME_SetUnitInvulnerablemy( HUNIT whichUnit , BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "SetUnitInvulnerablemy" );
	fflush( logfile );

	GAME_SetUnitInvulnerableold( whichUnit , flag );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitInvulnerable<--  whichUnit: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitLookAt )( HUNIT whichUnit , void * whichBone , HUNIT lookAtTarget , float *offsetX , float *offsetY , float *offsetZ );
GAME_SetUnitLookAt GAME_SetUnitLookAtorg = NULL;
GAME_SetUnitLookAt GAME_SetUnitLookAtold = NULL;

void __cdecl GAME_SetUnitLookAtmy( HUNIT whichUnit , void * whichBone , HUNIT lookAtTarget , float *offsetX , float *offsetY , float *offsetZ )
{
	fprintf_s( logfile , "%s" , "SetUnitLookAtmy\n" );
	fflush( logfile );

	GAME_SetUnitLookAtold( whichUnit , whichBone , lookAtTarget , offsetX , offsetY , offsetZ );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitLookAt<--  whichUnit: %X whichBone: \"%s\" lookAtTarget: %X offsetX: %f offsetY: %f offsetZ: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , jassgetchar( whichBone ) , lookAtTarget , *( float * ) offsetX , *( float * ) offsetY , *( float * ) offsetZ );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitMoveSpeed )( HUNIT whichUnit , float *newSpeed );
GAME_SetUnitMoveSpeed GAME_SetUnitMoveSpeedorg = NULL;
GAME_SetUnitMoveSpeed GAME_SetUnitMoveSpeedold = NULL;

void __cdecl GAME_SetUnitMoveSpeedmy( HUNIT whichUnit , float *newSpeed )
{
	fprintf_s( logfile , "%s" , "SetUnitMoveSpeedmy\n" );
	fflush( logfile );

	GAME_SetUnitMoveSpeedold( whichUnit , newSpeed );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitMoveSpeed<--  whichUnit: %X newSpeed: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , *( float * ) newSpeed );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitOwner )( HUNIT whichUnit , HPLAYER whichPlayer , BOOL changeColor );
GAME_SetUnitOwner GAME_SetUnitOwnerorg = NULL;
GAME_SetUnitOwner GAME_SetUnitOwnerold = NULL;

void __cdecl GAME_SetUnitOwnermy( HUNIT whichUnit , HPLAYER whichPlayer , BOOL changeColor )
{
	fprintf_s( logfile , "%s\n" , "SetUnitOwnermy" );
	fflush( logfile );

	GAME_SetUnitOwnerold( whichUnit , whichPlayer , changeColor );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitOwner<--  whichUnit: %X whichPlayer: %X changeColor: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , whichPlayer , changeColor ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitPathing )( HUNIT whichUnit , BOOL flag );
GAME_SetUnitPathing GAME_SetUnitPathingorg = NULL;
GAME_SetUnitPathing GAME_SetUnitPathingold = NULL;

void __cdecl GAME_SetUnitPathingmy( HUNIT whichUnit , BOOL flag )
{
	fprintf_s( logfile , "%s" , "SetUnitPathingmy\n" );
	fflush( logfile );

	GAME_SetUnitPathingold( whichUnit , flag );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitPathing<--  whichUnit: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitPosition )( HUNIT whichUnit , float *newX , float *newY );
GAME_SetUnitPosition GAME_SetUnitPositionorg = NULL;
GAME_SetUnitPosition GAME_SetUnitPositionold = NULL;

void __cdecl GAME_SetUnitPositionmy( HUNIT whichUnit , float *newX , float *newY )
{
	fprintf_s( logfile , "%s" , "SetUnitPositionmy\n" );
	fflush( logfile );

	GAME_SetUnitPositionold( whichUnit , newX , newY );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitPosition<--  whichUnit: %X newX: %f newY: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , *( float * ) newX , *( float * ) newY );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitPositionLoc )( HUNIT whichUnit , HLOCATION whichLocation );
GAME_SetUnitPositionLoc GAME_SetUnitPositionLocorg = NULL;
GAME_SetUnitPositionLoc GAME_SetUnitPositionLocold = NULL;

void __cdecl GAME_SetUnitPositionLocmy( HUNIT whichUnit , HLOCATION whichLocation )
{
	fprintf_s( logfile , "%s\n" , "SetUnitPositionLocmy" );
	fflush( logfile );

	GAME_SetUnitPositionLocold( whichUnit , whichLocation );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitPositionLoc<--  whichUnit: %X whichLocation: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , whichLocation );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitPropWindow )( HUNIT whichUnit , float *newPropWindowAngle );
GAME_SetUnitPropWindow GAME_SetUnitPropWindoworg = NULL;
GAME_SetUnitPropWindow GAME_SetUnitPropWindowold = NULL;

void __cdecl GAME_SetUnitPropWindowmy( HUNIT whichUnit , float *newPropWindowAngle )
{
	fprintf_s( logfile , "%s\n" , "SetUnitPropWindowmy" );
	fflush( logfile );

	GAME_SetUnitPropWindowold( whichUnit , newPropWindowAngle );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitPropWindow<--  whichUnit: %X newPropWindowAngle: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , *( float * ) newPropWindowAngle );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitRescuable )( HUNIT whichUnit , HPLAYER byWhichPlayer , BOOL flag );
GAME_SetUnitRescuable GAME_SetUnitRescuableorg = NULL;
GAME_SetUnitRescuable GAME_SetUnitRescuableold = NULL;

void __cdecl GAME_SetUnitRescuablemy( HUNIT whichUnit , HPLAYER byWhichPlayer , BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "SetUnitRescuablemy" );
	fflush( logfile );

	GAME_SetUnitRescuableold( whichUnit , byWhichPlayer , flag );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitRescuable<--  whichUnit: %X byWhichPlayer: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , byWhichPlayer , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitRescueRange )( HUNIT whichUnit , float *range );
GAME_SetUnitRescueRange GAME_SetUnitRescueRangeorg = NULL;
GAME_SetUnitRescueRange GAME_SetUnitRescueRangeold = NULL;

void __cdecl GAME_SetUnitRescueRangemy( HUNIT whichUnit , float *range )
{
	fprintf_s( logfile , "%s" , "SetUnitRescueRangemy\n" );
	fflush( logfile );

	GAME_SetUnitRescueRangeold( whichUnit , range );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitRescueRange<--  whichUnit: %X range: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , *( float * ) range );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitScale )( HUNIT whichUnit , float *scaleX , float *scaleY , float *scaleZ );
GAME_SetUnitScale GAME_SetUnitScaleorg = NULL;
GAME_SetUnitScale GAME_SetUnitScaleold = NULL;

void __cdecl GAME_SetUnitScalemy( HUNIT whichUnit , float *scaleX , float *scaleY , float *scaleZ )
{
	fprintf_s( logfile , "%s\n" , "SetUnitScalemy" );
	fflush( logfile );

	GAME_SetUnitScaleold( whichUnit , scaleX , scaleY , scaleZ );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitScale<--  whichUnit: %X scaleX: %f scaleY: %f scaleZ: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , *( float * ) scaleX , *( float * ) scaleY , *( float * ) scaleZ );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitState )( HUNIT whichUnit , HUNITSTATE whichUnitState , float *newVal );
GAME_SetUnitState GAME_SetUnitStateorg = NULL;
GAME_SetUnitState GAME_SetUnitStateold = NULL;

void __cdecl GAME_SetUnitStatemy( HUNIT whichUnit , HUNITSTATE whichUnitState , float *newVal )
{
	fprintf_s( logfile , "%s\n" , "SetUnitStatemy" );
	fflush( logfile );

	GAME_SetUnitStateold( whichUnit , whichUnitState , newVal );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitState<--  whichUnit: %X whichUnitState: %X newVal: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , whichUnitState , *( float * ) newVal );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitTimeScale )( HUNIT whichUnit , float *timeScale );
GAME_SetUnitTimeScale GAME_SetUnitTimeScaleorg = NULL;
GAME_SetUnitTimeScale GAME_SetUnitTimeScaleold = NULL;

void __cdecl GAME_SetUnitTimeScalemy( HUNIT whichUnit , float *timeScale )
{
	fprintf_s( logfile , "%s\n" , "SetUnitTimeScalemy" );
	fflush( logfile );

	GAME_SetUnitTimeScaleold( whichUnit , timeScale );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitTimeScale<--  whichUnit: %X timeScale: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , *( float * ) timeScale );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitTurnSpeed )( HUNIT whichUnit , float *newTurnSpeed );
GAME_SetUnitTurnSpeed GAME_SetUnitTurnSpeedorg = NULL;
GAME_SetUnitTurnSpeed GAME_SetUnitTurnSpeedold = NULL;

void __cdecl GAME_SetUnitTurnSpeedmy( HUNIT whichUnit , float *newTurnSpeed )
{
	fprintf_s( logfile , "%s\n" , "SetUnitTurnSpeedmy" );
	fflush( logfile );

	GAME_SetUnitTurnSpeedold( whichUnit , newTurnSpeed );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitTurnSpeed<--  whichUnit: %X newTurnSpeed: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , *( float * ) newTurnSpeed );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitTypeSlots )( HUNIT whichUnit , int slots );
GAME_SetUnitTypeSlots GAME_SetUnitTypeSlotsorg = NULL;
GAME_SetUnitTypeSlots GAME_SetUnitTypeSlotsold = NULL;

void __cdecl GAME_SetUnitTypeSlotsmy( HUNIT whichUnit , int slots )
{
	fprintf_s( logfile , "%s\n" , "SetUnitTypeSlotsmy" );
	fflush( logfile );

	GAME_SetUnitTypeSlotsold( whichUnit , slots );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitTypeSlots<--  whichUnit: %X slots: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , slots );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitUseFood )( HUNIT whichUnit , BOOL useFood );
GAME_SetUnitUseFood GAME_SetUnitUseFoodorg = NULL;
GAME_SetUnitUseFood GAME_SetUnitUseFoodold = NULL;

void __cdecl GAME_SetUnitUseFoodmy( HUNIT whichUnit , BOOL useFood )
{
	fprintf_s( logfile , "%s\n" , "SetUnitUseFoodmy" );
	fflush( logfile );

	GAME_SetUnitUseFoodold( whichUnit , useFood );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitUseFood<--  whichUnit: %X useFood: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , useFood ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitUserData )( HUNIT whichUnit , int data );
GAME_SetUnitUserData GAME_SetUnitUserDataorg = NULL;
GAME_SetUnitUserData GAME_SetUnitUserDataold = NULL;

void __cdecl GAME_SetUnitUserDatamy( HUNIT whichUnit , int data )
{
	fprintf_s( logfile , "%s" , "SetUnitUserDatamy\n" );
	fflush( logfile );

	GAME_SetUnitUserDataold( whichUnit , data );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitUserData<--  whichUnit: %X data: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , data );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitVertexColor )( HUNIT whichUnit , int red , int green , int blue , int alpha );
GAME_SetUnitVertexColor GAME_SetUnitVertexColororg = NULL;
GAME_SetUnitVertexColor GAME_SetUnitVertexColorold = NULL;

void __cdecl GAME_SetUnitVertexColormy( HUNIT whichUnit , int red , int green , int blue , int alpha )
{
	fprintf_s( logfile , "%s\n" , "SetUnitVertexColormy" );
	fflush( logfile );

	GAME_SetUnitVertexColorold( whichUnit , red , green , blue , alpha );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitVertexColor<--  whichUnit: %X red: %i green: %i blue: %i alpha: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , red , green , blue , alpha );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitX )( HUNIT whichUnit , float *newX );
GAME_SetUnitX GAME_SetUnitXorg = NULL;
GAME_SetUnitX GAME_SetUnitXold = NULL;

void __cdecl GAME_SetUnitXmy( HUNIT whichUnit , float *newX )
{
	fprintf_s( logfile , "%s\n" , "SetUnitXmy" );
	fflush( logfile );

	GAME_SetUnitXold( whichUnit , newX );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitX<--  whichUnit: %X newX: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , *( float * ) newX );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitY )( HUNIT whichUnit , float *newY );
GAME_SetUnitY GAME_SetUnitYorg = NULL;
GAME_SetUnitY GAME_SetUnitYold = NULL;

void __cdecl GAME_SetUnitYmy( HUNIT whichUnit , float *newY )
{
	fprintf_s( logfile , "%s\n" , "SetUnitYmy" );
	fflush( logfile );

	GAME_SetUnitYold( whichUnit , newY );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitY<--  whichUnit: %X newY: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , *( float * ) newY );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetUnitsFlee )( BOOL arg1 );
GAME_SetUnitsFlee GAME_SetUnitsFleeorg = NULL;
GAME_SetUnitsFlee GAME_SetUnitsFleeold = NULL;

void __cdecl GAME_SetUnitsFleemy( BOOL arg1 )
{
	fprintf_s( logfile , "%s\n" , "SetUnitsFleemy" );
	fflush( logfile );

	GAME_SetUnitsFleeold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetUnitsFlee<--  arg1: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_SetUpgrade )( int arg1 );
GAME_SetUpgrade GAME_SetUpgradeorg = NULL;
GAME_SetUpgrade GAME_SetUpgradeold = NULL;

BOOL __cdecl GAME_SetUpgrademy( int arg1 )
{
	fprintf_s( logfile , "%s" , "SetUpgrademy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SetUpgradeold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetUpgrade<--  arg1: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , arg1 , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_SetWatchMegaTargets )( BOOL arg1 );
GAME_SetWatchMegaTargets GAME_SetWatchMegaTargetsorg = NULL;
GAME_SetWatchMegaTargets GAME_SetWatchMegaTargetsold = NULL;

void __cdecl GAME_SetWatchMegaTargetsmy( BOOL arg1 )
{
	fprintf_s( logfile , "%s" , "SetWatchMegaTargetsmy\n" );
	fflush( logfile );

	GAME_SetWatchMegaTargetsold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_SetWatchMegaTargets<--  arg1: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetWaterBaseColor )( int red , int green , int blue , int alpha );
GAME_SetWaterBaseColor GAME_SetWaterBaseColororg = NULL;
GAME_SetWaterBaseColor GAME_SetWaterBaseColorold = NULL;

void __cdecl GAME_SetWaterBaseColormy( int red , int green , int blue , int alpha )
{
	fprintf_s( logfile , "%s" , "SetWaterBaseColormy\n" );
	fflush( logfile );

	GAME_SetWaterBaseColorold( red , green , blue , alpha );
	fprintf_s( logfile , "%s:[-->GAME_SetWaterBaseColor<--  red: %i green: %i blue: %i alpha: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , red , green , blue , alpha );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetWaterDeforms )( BOOL val );
GAME_SetWaterDeforms GAME_SetWaterDeformsorg = NULL;
GAME_SetWaterDeforms GAME_SetWaterDeformsold = NULL;

void __cdecl GAME_SetWaterDeformsmy( BOOL val )
{
	fprintf_s( logfile , "%s\n" , "SetWaterDeformsmy" );
	fflush( logfile );

	GAME_SetWaterDeformsold( val );
	fprintf_s( logfile , "%s:[-->GAME_SetWaterDeforms<--  val: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , val ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SetWidgetLife )( HWIDGET whichWidget , float *newLife );
GAME_SetWidgetLife GAME_SetWidgetLifeorg = NULL;
GAME_SetWidgetLife GAME_SetWidgetLifeold = NULL;

void __cdecl GAME_SetWidgetLifemy( HWIDGET whichWidget , float *newLife )
{
	fprintf_s( logfile , "%s" , "SetWidgetLifemy\n" );
	fflush( logfile );

	GAME_SetWidgetLifeold( whichWidget , newLife );
	fprintf_s( logfile , "%s:[-->GAME_SetWidgetLife<--  whichWidget: %X newLife: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichWidget , *( float * ) newLife );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ShiftTownSpot )( float *arg1 , float *arg2 );
GAME_ShiftTownSpot GAME_ShiftTownSpotorg = NULL;
GAME_ShiftTownSpot GAME_ShiftTownSpotold = NULL;

void __cdecl GAME_ShiftTownSpotmy( float *arg1 , float *arg2 )
{
	fprintf_s( logfile , "%s\n" , "ShiftTownSpotmy" );
	fflush( logfile );

	GAME_ShiftTownSpotold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_ShiftTownSpot<--  arg1: %f arg2: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) arg1 , *( float * ) arg2 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ShowDestructable )( HDESTRUCTABLE d , BOOL flag );
GAME_ShowDestructable GAME_ShowDestructableorg = NULL;
GAME_ShowDestructable GAME_ShowDestructableold = NULL;

void __cdecl GAME_ShowDestructablemy( HDESTRUCTABLE d , BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "ShowDestructablemy" );
	fflush( logfile );

	GAME_ShowDestructableold( d , flag );
	fprintf_s( logfile , "%s:[-->GAME_ShowDestructable<--  d: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , d , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ShowImage )( HIMAGE whichImage , BOOL flag );
GAME_ShowImage GAME_ShowImageorg = NULL;
GAME_ShowImage GAME_ShowImageold = NULL;

void __cdecl GAME_ShowImagemy( HIMAGE whichImage , BOOL flag )
{
	fprintf_s( logfile , "%s" , "ShowImagemy\n" );
	fflush( logfile );

	GAME_ShowImageold( whichImage , flag );
	fprintf_s( logfile , "%s:[-->GAME_ShowImage<--  whichImage: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichImage , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ShowInterface )( BOOL flag , float *fadeDuration );
GAME_ShowInterface GAME_ShowInterfaceorg = NULL;
GAME_ShowInterface GAME_ShowInterfaceold = NULL;

void __cdecl GAME_ShowInterfacemy( BOOL flag , float *fadeDuration )
{
	fprintf_s( logfile , "%s" , "ShowInterfacemy\n" );
	fflush( logfile );

	GAME_ShowInterfaceold( flag , fadeDuration );
	fprintf_s( logfile , "%s:[-->GAME_ShowInterface<--  flag: %s fadeDuration: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , flag ? "TRUE\n" : "FALSE" , *( float * ) fadeDuration );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ShowUbersplat )( HUBERSPLAT whichSplat , BOOL flag );
GAME_ShowUbersplat GAME_ShowUbersplatorg = NULL;
GAME_ShowUbersplat GAME_ShowUbersplatold = NULL;

void __cdecl GAME_ShowUbersplatmy( HUBERSPLAT whichSplat , BOOL flag )
{
	fprintf_s( logfile , "%s" , "ShowUbersplatmy\n" );
	fflush( logfile );

	GAME_ShowUbersplatold( whichSplat , flag );
	fprintf_s( logfile , "%s:[-->GAME_ShowUbersplat<--  whichSplat: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichSplat , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_ShowUnit )( HUNIT whichUnit , BOOL show );
GAME_ShowUnit GAME_ShowUnitorg = NULL;
GAME_ShowUnit GAME_ShowUnitold = NULL;

void __cdecl GAME_ShowUnitmy( HUNIT whichUnit , BOOL show )
{
	fprintf_s( logfile , "%s" , "ShowUnitmy\n" );
	fflush( logfile );

	GAME_ShowUnitold( whichUnit , show );
	fprintf_s( logfile , "%s:[-->GAME_ShowUnit<--  whichUnit: %X show: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , show ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef DWFP( __cdecl *GAME_Sin )( float *radians );
GAME_Sin GAME_Sinorg = NULL;
GAME_Sin GAME_Sinold = NULL;

DWFP __cdecl GAME_Sinmy( float *radians )
{
	fprintf_s( logfile , "%s" , "Sinmy\n" );
	fflush( logfile );

	DWFP retvalue = GAME_Sinold( radians );
	fprintf_s( logfile , "%s:[-->GAME_Sin<--  radians: %f] RETURN-> %f\n" , currentDateTime( ).c_str( ) , *( float * ) radians , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_Sleep )( float *arg1 );
GAME_Sleep GAME_Sleeporg = NULL;
GAME_Sleep GAME_Sleepold = NULL;

void __cdecl GAME_Sleepmy( float *arg1 )
{
	fprintf_s( logfile , "%s\n" , "Sleepmy" );
	fflush( logfile );

	GAME_Sleepold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_Sleep<--  arg1: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) arg1 );
	fflush( logfile );

}


typedef DWFP( __cdecl *GAME_SquareRoot )( float *x );
GAME_SquareRoot GAME_SquareRootorg = NULL;
GAME_SquareRoot GAME_SquareRootold = NULL;

DWFP __cdecl GAME_SquareRootmy( float *x )
{
	fprintf_s( logfile , "%s\n" , "SquareRootmy" );
	fflush( logfile );

	DWFP retvalue = GAME_SquareRootold( x );
	fprintf_s( logfile , "%s:[-->GAME_SquareRoot<--  x: %f] RETURN-> %f\n" , currentDateTime( ).c_str( ) , *( float * ) x , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_StartCampaignAI )( HPLAYER num , void * script );
GAME_StartCampaignAI GAME_StartCampaignAIorg = NULL;
GAME_StartCampaignAI GAME_StartCampaignAIold = NULL;

void __cdecl GAME_StartCampaignAImy( HPLAYER num , void * script )
{
	fprintf_s( logfile , "%s\n" , "StartCampaignAImy" );
	fflush( logfile );

	GAME_StartCampaignAIold( num , script );
	fprintf_s( logfile , "%s:[-->GAME_StartCampaignAI<--  num: %X script: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , num , jassgetchar( script ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_StartGetEnemyBase )( );
GAME_StartGetEnemyBase GAME_StartGetEnemyBaseorg = NULL;
GAME_StartGetEnemyBase GAME_StartGetEnemyBaseold = NULL;

void __cdecl GAME_StartGetEnemyBasemy( )
{
	fprintf_s( logfile , "%s" , "StartGetEnemyBasemy\n" );
	fflush( logfile );

	GAME_StartGetEnemyBaseold( );
	fprintf_s( logfile , "%s:[-->GAME_StartGetEnemyBase<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_StartMeleeAI )( HPLAYER num , void * script );
GAME_StartMeleeAI GAME_StartMeleeAIorg = NULL;
GAME_StartMeleeAI GAME_StartMeleeAIold = NULL;

void __cdecl GAME_StartMeleeAImy( HPLAYER num , void * script )
{
	fprintf_s( logfile , "%s\n" , "StartMeleeAImy" );
	fflush( logfile );

	GAME_StartMeleeAIold( num , script );
	fprintf_s( logfile , "%s:[-->GAME_StartMeleeAI<--  num: %X script: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , num , jassgetchar( script ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_StartSound )( HSOUND soundHandle );
GAME_StartSound GAME_StartSoundorg = NULL;
GAME_StartSound GAME_StartSoundold = NULL;

void __cdecl GAME_StartSoundmy( HSOUND soundHandle )
{
	fprintf_s( logfile , "%s" , "StartSoundmy\n" );
	fflush( logfile );

	GAME_StartSoundold( soundHandle );
	fprintf_s( logfile , "%s:[-->GAME_StartSound<--  soundHandle: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , soundHandle );
	fflush( logfile );

}


typedef void( __cdecl *GAME_StartThread )( CODE arg1 );
GAME_StartThread GAME_StartThreadorg = NULL;
GAME_StartThread GAME_StartThreadold = NULL;

void __cdecl GAME_StartThreadmy( CODE arg1 )
{
	fprintf_s( logfile , "%s\n" , "StartThreadmy" );
	fflush( logfile );

	GAME_StartThreadold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_StartThread<--  arg1: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_StopCamera )( );
GAME_StopCamera GAME_StopCameraorg = NULL;
GAME_StopCamera GAME_StopCameraold = NULL;

void __cdecl GAME_StopCameramy( )
{
	fprintf_s( logfile , "%s\n" , "StopCameramy" );
	fflush( logfile );

	GAME_StopCameraold( );
	fprintf_s( logfile , "%s:[-->GAME_StopCamera<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_StopGathering )( );
GAME_StopGathering GAME_StopGatheringorg = NULL;
GAME_StopGathering GAME_StopGatheringold = NULL;

void __cdecl GAME_StopGatheringmy( )
{
	fprintf_s( logfile , "%s\n" , "StopGatheringmy" );
	fflush( logfile );

	GAME_StopGatheringold( );
	fprintf_s( logfile , "%s:[-->GAME_StopGathering<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_StopMusic )( BOOL fadeOut );
GAME_StopMusic GAME_StopMusicorg = NULL;
GAME_StopMusic GAME_StopMusicold = NULL;

void __cdecl GAME_StopMusicmy( BOOL fadeOut )
{
	fprintf_s( logfile , "%s\n" , "StopMusicmy" );
	fflush( logfile );

	GAME_StopMusicold( fadeOut );
	fprintf_s( logfile , "%s:[-->GAME_StopMusic<--  fadeOut: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , fadeOut ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_StopSound )( HSOUND soundHandle , BOOL killWhenDone , BOOL fadeOut );
GAME_StopSound GAME_StopSoundorg = NULL;
GAME_StopSound GAME_StopSoundold = NULL;

void __cdecl GAME_StopSoundmy( HSOUND soundHandle , BOOL killWhenDone , BOOL fadeOut )
{
	fprintf_s( logfile , "%s" , "StopSoundmy\n" );
	fflush( logfile );

	GAME_StopSoundold( soundHandle , killWhenDone , fadeOut );
	fprintf_s( logfile , "%s:[-->GAME_StopSound<--  soundHandle: %X killWhenDone: %s fadeOut: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , soundHandle , killWhenDone ? "TRUE\n" : "FALSE" , fadeOut ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_StoreBOOLean )( HGAMECACHE cache , void * missionKey , void * key , BOOL value );
GAME_StoreBOOLean GAME_StoreBOOLeanorg = NULL;
GAME_StoreBOOLean GAME_StoreBOOLeanold = NULL;

void __cdecl GAME_StoreBOOLeanmy( HGAMECACHE cache , void * missionKey , void * key , BOOL value )
{
	fprintf_s( logfile , "%s" , "StoreBOOLeanmy\n" );
	fflush( logfile );

	GAME_StoreBOOLeanold( cache , missionKey , key , value );
	fprintf_s( logfile , "%s:[-->GAME_StoreBOOLean<--  cache: %X missionKey: \"%s\" key: \"%s\" value: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) , value ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_StoreInteger )( HGAMECACHE cache , void * missionKey , void * key , int value );
GAME_StoreInteger GAME_StoreIntegerorg = NULL;
GAME_StoreInteger GAME_StoreIntegerold = NULL;

void __cdecl GAME_StoreIntegermy( HGAMECACHE cache , void * missionKey , void * key , int value )
{
	fprintf_s( logfile , "%s" , "StoreIntegermy\n" );
	fflush( logfile );

	GAME_StoreIntegerold( cache , missionKey , key , value );
	fprintf_s( logfile , "%s:[-->GAME_StoreInteger<--  cache: %X missionKey: \"%s\" key: \"%s\" value: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) , value );
	fflush( logfile );

}


typedef void( __cdecl *GAME_StoreReal )( HGAMECACHE cache , void * missionKey , void * key , float *value );
GAME_StoreReal GAME_StoreRealorg = NULL;
GAME_StoreReal GAME_StoreRealold = NULL;

void __cdecl GAME_StoreRealmy( HGAMECACHE cache , void * missionKey , void * key , float *value )
{
	fprintf_s( logfile , "%s" , "StoreRealmy\n" );
	fflush( logfile );

	GAME_StoreRealold( cache , missionKey , key , value );
	fprintf_s( logfile , "%s:[-->GAME_StoreReal<--  cache: %X missionKey: \"%s\" key: \"%s\" value: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) , *( float * ) value );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_StoreString )( HGAMECACHE cache , void * missionKey , void * key , void * value );
GAME_StoreString GAME_StoreStringorg = NULL;
GAME_StoreString GAME_StoreStringold = NULL;

BOOL __cdecl GAME_StoreStringmy( HGAMECACHE cache , void * missionKey , void * key , void * value )
{
	fprintf_s( logfile , "%s" , "StoreStringmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_StoreStringold( cache , missionKey , key , value );
	fprintf_s( logfile , "%s:[-->GAME_StoreString<--  cache: %X missionKey: \"%s\" key: \"%s\" value: \"%s\"] RETURN-> %s\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) , jassgetchar( value ) , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_StoreUnit )( HGAMECACHE cache , void * missionKey , void * key , HUNIT whichUnit );
GAME_StoreUnit GAME_StoreUnitorg = NULL;
GAME_StoreUnit GAME_StoreUnitold = NULL;

BOOL __cdecl GAME_StoreUnitmy( HGAMECACHE cache , void * missionKey , void * key , HUNIT whichUnit )
{
	fprintf_s( logfile , "%s" , "StoreUnitmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_StoreUnitold( cache , missionKey , key , whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_StoreUnit<--  cache: %X missionKey: \"%s\" key: \"%s\" whichUnit: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) , whichUnit , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_StringCase )( void * source , BOOL upper );
GAME_StringCase GAME_StringCaseorg = NULL;
GAME_StringCase GAME_StringCaseold = NULL;

DWORD __cdecl GAME_StringCasemy( void * source , BOOL upper )
{
	fprintf_s( logfile , "%s" , "StringCasemy\n" );
	fflush( logfile );

	DWORD retvalue = GAME_StringCaseold( source , upper );
	fprintf_s( logfile , "%s:[-->GAME_StringCase<--  source: \"%s\" upper: %s] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , jassgetchar( source ) , upper ? "TRUE" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_StringHash )( void * s );
GAME_StringHash GAME_StringHashorg = NULL;
GAME_StringHash GAME_StringHashold = NULL;

int __cdecl GAME_StringHashmy( void * s )
{
	fprintf_s( logfile , "%s" , "StringHashmy\n" );
	fflush( logfile );

	int retvalue = GAME_StringHashold( s );
	fprintf_s( logfile , "%s:[-->GAME_StringHash<--  s: \"%s\"] RETURN-> %i\n" , currentDateTime( ).c_str( ) , jassgetchar( s ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_StringLength )( void * s );
GAME_StringLength GAME_StringLengthorg = NULL;
GAME_StringLength GAME_StringLengthold = NULL;

int __cdecl GAME_StringLengthmy( void * s )
{
	fprintf_s( logfile , "%s" , "StringLengthmy\n" );
	fflush( logfile );

	int retvalue = GAME_StringLengthold( s );
	fprintf_s( logfile , "%s:[-->GAME_StringLength<--  s: \"%s\"] RETURN-> %i\n" , currentDateTime( ).c_str( ) , jassgetchar( s ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_SubString )( void * source , int start , int end );
GAME_SubString GAME_SubStringorg = NULL;
GAME_SubString GAME_SubStringold = NULL;

DWORD __cdecl GAME_SubStringmy( void * source , int start , int end )
{
	fprintf_s( logfile , "%s" , "SubStringmy\n" );
	fflush( logfile );

	DWORD retvalue = GAME_SubStringold( source , start , end );
	fprintf_s( logfile , "%s:[-->GAME_SubString<--  source: \"%s\" start: %i end: %i] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , jassgetchar( source ) , start , end , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SuicidePlayer )( HPLAYER arg1 , BOOL arg2 );
GAME_SuicidePlayer GAME_SuicidePlayerorg = NULL;
GAME_SuicidePlayer GAME_SuicidePlayerold = NULL;

BOOL __cdecl GAME_SuicidePlayermy( HPLAYER arg1 , BOOL arg2 )
{
	fprintf_s( logfile , "%s" , "SuicidePlayermy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SuicidePlayerold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_SuicidePlayer<--  arg1: %X arg2: %s] RETURN-> %s\n" , currentDateTime( ).c_str( ) , arg1 , arg2 ? "TRUE\n" : "FALSE" , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_SuicidePlayerUnits )( HPLAYER arg1 , BOOL arg2 );
GAME_SuicidePlayerUnits GAME_SuicidePlayerUnitsorg = NULL;
GAME_SuicidePlayerUnits GAME_SuicidePlayerUnitsold = NULL;

BOOL __cdecl GAME_SuicidePlayerUnitsmy( HPLAYER arg1 , BOOL arg2 )
{
	fprintf_s( logfile , "%s" , "SuicidePlayerUnitsmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_SuicidePlayerUnitsold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_SuicidePlayerUnits<--  arg1: %X arg2: %s] RETURN-> %s\n" , currentDateTime( ).c_str( ) , arg1 , arg2 ? "TRUE\n" : "FALSE" , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_SuicideUnit )( int arg1 , int arg2 );
GAME_SuicideUnit GAME_SuicideUnitorg = NULL;
GAME_SuicideUnit GAME_SuicideUnitold = NULL;

void __cdecl GAME_SuicideUnitmy( int arg1 , int arg2 )
{
	fprintf_s( logfile , "%s" , "SuicideUnitmy\n" );
	fflush( logfile );

	GAME_SuicideUnitold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_SuicideUnit<--  arg1: %i arg2: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 , arg2 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SuicideUnitEx )( int arg1 , int arg2 , int arg3 );
GAME_SuicideUnitEx GAME_SuicideUnitExorg = NULL;
GAME_SuicideUnitEx GAME_SuicideUnitExold = NULL;

void __cdecl GAME_SuicideUnitExmy( int arg1 , int arg2 , int arg3 )
{
	fprintf_s( logfile , "%s\n" , "SuicideUnitExmy" );
	fflush( logfile );

	GAME_SuicideUnitExold( arg1 , arg2 , arg3 );
	fprintf_s( logfile , "%s:[-->GAME_SuicideUnitEx<--  arg1: %i arg2: %i arg3: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 , arg2 , arg3 );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SuspendHeroXP )( HUNIT whichHero , BOOL flag );
GAME_SuspendHeroXP GAME_SuspendHeroXPorg = NULL;
GAME_SuspendHeroXP GAME_SuspendHeroXPold = NULL;

void __cdecl GAME_SuspendHeroXPmy( HUNIT whichHero , BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "SuspendHeroXPmy" );
	fflush( logfile );

	GAME_SuspendHeroXPold( whichHero , flag );
	fprintf_s( logfile , "%s:[-->GAME_SuspendHeroXP<--  whichHero: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichHero , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SuspendTimeOfDay )( BOOL b );
GAME_SuspendTimeOfDay GAME_SuspendTimeOfDayorg = NULL;
GAME_SuspendTimeOfDay GAME_SuspendTimeOfDayold = NULL;

void __cdecl GAME_SuspendTimeOfDaymy( BOOL b )
{
	fprintf_s( logfile , "%s" , "SuspendTimeOfDaymy\n" );
	fflush( logfile );

	GAME_SuspendTimeOfDayold( b );
	fprintf_s( logfile , "%s:[-->GAME_SuspendTimeOfDay<--  b: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , b ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SyncSelections )( );
GAME_SyncSelections GAME_SyncSelectionsorg = NULL;
GAME_SyncSelections GAME_SyncSelectionsold = NULL;

void __cdecl GAME_SyncSelectionsmy( )
{
	fprintf_s( logfile , "%s" , "SyncSelectionsmy\n" );
	fflush( logfile );

	GAME_SyncSelectionsold( );
	fprintf_s( logfile , "%s:[-->GAME_SyncSelections<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SyncStoredBOOLean )( HGAMECACHE cache , void * missionKey , void * key );
GAME_SyncStoredBOOLean GAME_SyncStoredBOOLeanorg = NULL;
GAME_SyncStoredBOOLean GAME_SyncStoredBOOLeanold = NULL;

void __cdecl GAME_SyncStoredBOOLeanmy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s\n" , "SyncStoredBOOLeanmy" );
	fflush( logfile );

	GAME_SyncStoredBOOLeanold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_SyncStoredBOOLean<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SyncStoredInteger )( HGAMECACHE cache , void * missionKey , void * key );
GAME_SyncStoredInteger GAME_SyncStoredIntegerorg = NULL;
GAME_SyncStoredInteger GAME_SyncStoredIntegerold = NULL;

void __cdecl GAME_SyncStoredIntegermy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s" , "SyncStoredIntegermy\n" );
	fflush( logfile );

	GAME_SyncStoredIntegerold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_SyncStoredInteger<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SyncStoredReal )( HGAMECACHE cache , void * missionKey , void * key );
GAME_SyncStoredReal GAME_SyncStoredRealorg = NULL;
GAME_SyncStoredReal GAME_SyncStoredRealold = NULL;

void __cdecl GAME_SyncStoredRealmy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s" , "SyncStoredRealmy\n" );
	fflush( logfile );

	GAME_SyncStoredRealold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_SyncStoredReal<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SyncStoredString )( HGAMECACHE cache , void * missionKey , void * key );
GAME_SyncStoredString GAME_SyncStoredStringorg = NULL;
GAME_SyncStoredString GAME_SyncStoredStringold = NULL;

void __cdecl GAME_SyncStoredStringmy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s" , "SyncStoredStringmy\n" );
	fflush( logfile );

	GAME_SyncStoredStringold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_SyncStoredString<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_SyncStoredUnit )( HGAMECACHE cache , void * missionKey , void * key );
GAME_SyncStoredUnit GAME_SyncStoredUnitorg = NULL;
GAME_SyncStoredUnit GAME_SyncStoredUnitold = NULL;

void __cdecl GAME_SyncStoredUnitmy( HGAMECACHE cache , void * missionKey , void * key )
{
	fprintf_s( logfile , "%s" , "SyncStoredUnitmy\n" );
	fflush( logfile );

	GAME_SyncStoredUnitold( cache , missionKey , key );
	fprintf_s( logfile , "%s:[-->GAME_SyncStoredUnit<--  cache: %X missionKey: \"%s\" key: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , cache , jassgetchar( missionKey ) , jassgetchar( key ) );
	fflush( logfile );

}


typedef DWFP( __cdecl *GAME_Tan )( float *radians );
GAME_Tan GAME_Tanorg = NULL;
GAME_Tan GAME_Tanold = NULL;

DWFP __cdecl GAME_Tanmy( float *radians )
{
	fprintf_s( logfile , "%s" , "Tanmy\n" );
	fflush( logfile );

	DWFP retvalue = GAME_Tanold( radians );
	fprintf_s( logfile , "%s:[-->GAME_Tan<--  radians: %f] RETURN-> %f\n" , currentDateTime( ).c_str( ) , *( float * ) radians , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_TeleportCaptain )( float *arg1 , float *arg2 );
GAME_TeleportCaptain GAME_TeleportCaptainorg = NULL;
GAME_TeleportCaptain GAME_TeleportCaptainold = NULL;

void __cdecl GAME_TeleportCaptainmy( float *arg1 , float *arg2 )
{
	fprintf_s( logfile , "%s\n" , "TeleportCaptainmy" );
	fflush( logfile );

	GAME_TeleportCaptainold( arg1 , arg2 );
	fprintf_s( logfile , "%s:[-->GAME_TeleportCaptain<--  arg1: %f arg2: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) arg1 , *( float * ) arg2 );
	fflush( logfile );

}


typedef HTERRAINDEFORMATION( __cdecl *GAME_TerrainDeformCrater )( float *x , float *y , float *radius , float *depth , int duration , BOOL permanent );
GAME_TerrainDeformCrater GAME_TerrainDeformCraterorg = NULL;
GAME_TerrainDeformCrater GAME_TerrainDeformCraterold = NULL;

HTERRAINDEFORMATION __cdecl GAME_TerrainDeformCratermy( float *x , float *y , float *radius , float *depth , int duration , BOOL permanent )
{
	fprintf_s( logfile , "%s\n" , "TerrainDeformCratermy" );
	fflush( logfile );

	HTERRAINDEFORMATION retvalue = GAME_TerrainDeformCraterold( x , y , radius , depth , duration , permanent );
	fprintf_s( logfile , "%s:[-->GAME_TerrainDeformCrater<--  x: %f y: %f radius: %f depth: %f duration: %i permanent: %s] RETURN-> %X\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , *( float * ) radius , *( float * ) depth , duration , permanent ? "TRUE\n" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTERRAINDEFORMATION( __cdecl *GAME_TerrainDeformRandom )( float *x , float *y , float *radius , float *minDelta , float *maxDelta , int duration , int updateInterval );
GAME_TerrainDeformRandom GAME_TerrainDeformRandomorg = NULL;
GAME_TerrainDeformRandom GAME_TerrainDeformRandomold = NULL;

HTERRAINDEFORMATION __cdecl GAME_TerrainDeformRandommy( float *x , float *y , float *radius , float *minDelta , float *maxDelta , int duration , int updateInterval )
{
	fprintf_s( logfile , "%s" , "TerrainDeformRandommy\n" );
	fflush( logfile );

	HTERRAINDEFORMATION retvalue = GAME_TerrainDeformRandomold( x , y , radius , minDelta , maxDelta , duration , updateInterval );
	fprintf_s( logfile , "%s:[-->GAME_TerrainDeformRandom<--  x: %f y: %f radius: %f minDelta: %f maxDelta: %f duration: %i updateInterval: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , *( float * ) radius , *( float * ) minDelta , *( float * ) maxDelta , duration , updateInterval , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTERRAINDEFORMATION( __cdecl *GAME_TerrainDeformRipple )( float *x , float *y , float *radius , float *depth , int duration , int count , float *spaceWaves , float *timeWaves , float *radiusStartPct , BOOL limitNeg );
GAME_TerrainDeformRipple GAME_TerrainDeformRippleorg = NULL;
GAME_TerrainDeformRipple GAME_TerrainDeformRippleold = NULL;

HTERRAINDEFORMATION __cdecl GAME_TerrainDeformRipplemy( float *x , float *y , float *radius , float *depth , int duration , int count , float *spaceWaves , float *timeWaves , float *radiusStartPct , BOOL limitNeg )
{
	fprintf_s( logfile , "%s\n" , "TerrainDeformRipplemy" );
	fflush( logfile );

	HTERRAINDEFORMATION retvalue = GAME_TerrainDeformRippleold( x , y , radius , depth , duration , count , spaceWaves , timeWaves , radiusStartPct , limitNeg );
	fprintf_s( logfile , "%s:[-->GAME_TerrainDeformRipple<--  x: %f y: %f radius: %f depth: %f duration: %i count: %i spaceWaves: %f timeWaves: %f radiusStartPct: %f limitNeg: %s] RETURN-> %X\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , *( float * ) radius , *( float * ) depth , duration , count , *( float * ) spaceWaves , *( float * ) timeWaves , *( float * ) radiusStartPct , limitNeg ? "TRUE\n" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_TerrainDeformStop )( HTERRAINDEFORMATION deformation , int duration );
GAME_TerrainDeformStop GAME_TerrainDeformStoporg = NULL;
GAME_TerrainDeformStop GAME_TerrainDeformStopold = NULL;

void __cdecl GAME_TerrainDeformStopmy( HTERRAINDEFORMATION deformation , int duration )
{
	fprintf_s( logfile , "%s" , "TerrainDeformStopmy\n" );
	fflush( logfile );

	GAME_TerrainDeformStopold( deformation , duration );
	fprintf_s( logfile , "%s:[-->GAME_TerrainDeformStop<--  deformation: %X duration: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , deformation , duration );
	fflush( logfile );

}


typedef void( __cdecl *GAME_TerrainDeformStopAll )( );
GAME_TerrainDeformStopAll GAME_TerrainDeformStopAllorg = NULL;
GAME_TerrainDeformStopAll GAME_TerrainDeformStopAllold = NULL;

void __cdecl GAME_TerrainDeformStopAllmy( )
{
	fprintf_s( logfile , "%s\n" , "TerrainDeformStopAllmy" );
	fflush( logfile );

	GAME_TerrainDeformStopAllold( );
	fprintf_s( logfile , "%s:[-->GAME_TerrainDeformStopAll<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef HTERRAINDEFORMATION( __cdecl *GAME_TerrainDeformWave )( float *x , float *y , float *dirX , float *dirY , float *distance , float *speed , float *radius , float *depth , int trailTime , int count );
GAME_TerrainDeformWave GAME_TerrainDeformWaveorg = NULL;
GAME_TerrainDeformWave GAME_TerrainDeformWaveold = NULL;

HTERRAINDEFORMATION __cdecl GAME_TerrainDeformWavemy( float *x , float *y , float *dirX , float *dirY , float *distance , float *speed , float *radius , float *depth , int trailTime , int count )
{
	fprintf_s( logfile , "%s\n" , "TerrainDeformWavemy" );
	fflush( logfile );

	HTERRAINDEFORMATION retvalue = GAME_TerrainDeformWaveold( x , y , dirX , dirY , distance , speed , radius , depth , trailTime , count );
	fprintf_s( logfile , "%s:[-->GAME_TerrainDeformWave<--  x: %f y: %f dirX: %f dirY: %f distance: %f speed: %f radius: %f depth: %f trailTime: %i count: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , *( float * ) x , *( float * ) y , *( float * ) dirX , *( float * ) dirY , *( float * ) distance , *( float * ) speed , *( float * ) radius , *( float * ) depth , trailTime , count , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_TimerDialogDisplay )( HTIMERDIALOG whichDialog , BOOL display );
GAME_TimerDialogDisplay GAME_TimerDialogDisplayorg = NULL;
GAME_TimerDialogDisplay GAME_TimerDialogDisplayold = NULL;

void __cdecl GAME_TimerDialogDisplaymy( HTIMERDIALOG whichDialog , BOOL display )
{
	fprintf_s( logfile , "%s\n" , "TimerDialogDisplaymy" );
	fflush( logfile );

	GAME_TimerDialogDisplayold( whichDialog , display );
	fprintf_s( logfile , "%s:[-->GAME_TimerDialogDisplay<--  whichDialog: %X display: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichDialog , display ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_TimerDialogSetRealTimeRemaining )( HTIMERDIALOG whichDialog , float *timeRemaining );
GAME_TimerDialogSetRealTimeRemaining GAME_TimerDialogSetRealTimeRemainingorg = NULL;
GAME_TimerDialogSetRealTimeRemaining GAME_TimerDialogSetRealTimeRemainingold = NULL;

void __cdecl GAME_TimerDialogSetRealTimeRemainingmy( HTIMERDIALOG whichDialog , float *timeRemaining )
{
	fprintf_s( logfile , "%s" , "TimerDialogSetRealTimeRemainingmy\n" );
	fflush( logfile );

	GAME_TimerDialogSetRealTimeRemainingold( whichDialog , timeRemaining );
	fprintf_s( logfile , "%s:[-->GAME_TimerDialogSetRealTimeRemaining<--  whichDialog: %X timeRemaining: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichDialog , *( float * ) timeRemaining );
	fflush( logfile );

}


typedef void( __cdecl *GAME_TimerDialogSetSpeed )( HTIMERDIALOG whichDialog , float *speedMultFactor );
GAME_TimerDialogSetSpeed GAME_TimerDialogSetSpeedorg = NULL;
GAME_TimerDialogSetSpeed GAME_TimerDialogSetSpeedold = NULL;

void __cdecl GAME_TimerDialogSetSpeedmy( HTIMERDIALOG whichDialog , float *speedMultFactor )
{
	fprintf_s( logfile , "%s\n" , "TimerDialogSetSpeedmy" );
	fflush( logfile );

	GAME_TimerDialogSetSpeedold( whichDialog , speedMultFactor );
	fprintf_s( logfile , "%s:[-->GAME_TimerDialogSetSpeed<--  whichDialog: %X speedMultFactor: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichDialog , *( float * ) speedMultFactor );
	fflush( logfile );

}


typedef void( __cdecl *GAME_TimerDialogSetTimeColor )( HTIMERDIALOG whichDialog , int red , int green , int blue , int alpha );
GAME_TimerDialogSetTimeColor GAME_TimerDialogSetTimeColororg = NULL;
GAME_TimerDialogSetTimeColor GAME_TimerDialogSetTimeColorold = NULL;

void __cdecl GAME_TimerDialogSetTimeColormy( HTIMERDIALOG whichDialog , int red , int green , int blue , int alpha )
{
	fprintf_s( logfile , "%s\n" , "TimerDialogSetTimeColormy" );
	fflush( logfile );

	GAME_TimerDialogSetTimeColorold( whichDialog , red , green , blue , alpha );
	fprintf_s( logfile , "%s:[-->GAME_TimerDialogSetTimeColor<--  whichDialog: %X red: %i green: %i blue: %i alpha: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichDialog , red , green , blue , alpha );
	fflush( logfile );

}


typedef void( __cdecl *GAME_TimerDialogSetTitle )( HTIMERDIALOG whichDialog , void * title );
GAME_TimerDialogSetTitle GAME_TimerDialogSetTitleorg = NULL;
GAME_TimerDialogSetTitle GAME_TimerDialogSetTitleold = NULL;

void __cdecl GAME_TimerDialogSetTitlemy( HTIMERDIALOG whichDialog , void * title )
{
	fprintf_s( logfile , "%s\n" , "TimerDialogSetTitlemy" );
	fflush( logfile );

	GAME_TimerDialogSetTitleold( whichDialog , title );
	fprintf_s( logfile , "%s:[-->GAME_TimerDialogSetTitle<--  whichDialog: %X title: \"%s\"] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichDialog , jassgetchar( title ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_TimerDialogSetTitleColor )( HTIMERDIALOG whichDialog , int red , int green , int blue , int alpha );
GAME_TimerDialogSetTitleColor GAME_TimerDialogSetTitleColororg = NULL;
GAME_TimerDialogSetTitleColor GAME_TimerDialogSetTitleColorold = NULL;

void __cdecl GAME_TimerDialogSetTitleColormy( HTIMERDIALOG whichDialog , int red , int green , int blue , int alpha )
{
	fprintf_s( logfile , "%s" , "TimerDialogSetTitleColormy\n" );
	fflush( logfile );

	GAME_TimerDialogSetTitleColorold( whichDialog , red , green , blue , alpha );
	fprintf_s( logfile , "%s:[-->GAME_TimerDialogSetTitleColor<--  whichDialog: %X red: %i green: %i blue: %i alpha: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichDialog , red , green , blue , alpha );
	fflush( logfile );

}


typedef DWFP( __cdecl *GAME_TimerGetElapsed )( HTIMER whichTimer );
GAME_TimerGetElapsed GAME_TimerGetElapsedorg = NULL;
GAME_TimerGetElapsed GAME_TimerGetElapsedold = NULL;

DWFP __cdecl GAME_TimerGetElapsedmy( HTIMER whichTimer )
{
	fprintf_s( logfile , "%s\n" , "TimerGetElapsedmy" );
	fflush( logfile );

	DWFP retvalue = GAME_TimerGetElapsedold( whichTimer );
	fprintf_s( logfile , "%s:[-->GAME_TimerGetElapsed<--  whichTimer: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichTimer , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_TimerGetRemaining )( HTIMER whichTimer );
GAME_TimerGetRemaining GAME_TimerGetRemainingorg = NULL;
GAME_TimerGetRemaining GAME_TimerGetRemainingold = NULL;

DWFP __cdecl GAME_TimerGetRemainingmy( HTIMER whichTimer )
{
	fprintf_s( logfile , "%s\n" , "TimerGetRemainingmy" );
	fflush( logfile );

	DWFP retvalue = GAME_TimerGetRemainingold( whichTimer );
	fprintf_s( logfile , "%s:[-->GAME_TimerGetRemaining<--  whichTimer: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichTimer , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_TimerGetTimeout )( HTIMER whichTimer );
GAME_TimerGetTimeout GAME_TimerGetTimeoutorg = NULL;
GAME_TimerGetTimeout GAME_TimerGetTimeoutold = NULL;

DWFP __cdecl GAME_TimerGetTimeoutmy( HTIMER whichTimer )
{
	fprintf_s( logfile , "%s\n" , "TimerGetTimeoutmy" );
	fflush( logfile );

	DWFP retvalue = GAME_TimerGetTimeoutold( whichTimer );
	fprintf_s( logfile , "%s:[-->GAME_TimerGetTimeout<--  whichTimer: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , whichTimer , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_TimerStart )( HTIMER whichTimer , float *timeout , BOOL periodic , CODE handlerFunc );
GAME_TimerStart GAME_TimerStartorg = NULL;
GAME_TimerStart GAME_TimerStartold = NULL;

void __cdecl GAME_TimerStartmy( HTIMER whichTimer , float *timeout , BOOL periodic , CODE handlerFunc )
{
	fprintf_s( logfile , "%s\n" , "TimerStartmy" );
	fflush( logfile );

	GAME_TimerStartold( whichTimer , timeout , periodic , handlerFunc );
	fprintf_s( logfile , "%s:[-->GAME_TimerStart<--  whichTimer: %X timeout: %f periodic: %s handlerFunc: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichTimer , *( float * ) timeout , periodic ? "TRUE\n" : "FALSE" , handlerFunc );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_TownHasHall )( int arg1 );
GAME_TownHasHall GAME_TownHasHallorg = NULL;
GAME_TownHasHall GAME_TownHasHallold = NULL;

BOOL __cdecl GAME_TownHasHallmy( int arg1 )
{
	fprintf_s( logfile , "%s" , "TownHasHallmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_TownHasHallold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_TownHasHall<--  arg1: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , arg1 , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_TownHasMine )( int arg1 );
GAME_TownHasMine GAME_TownHasMineorg = NULL;
GAME_TownHasMine GAME_TownHasMineold = NULL;

BOOL __cdecl GAME_TownHasMinemy( int arg1 )
{
	fprintf_s( logfile , "%s" , "TownHasMinemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_TownHasMineold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_TownHasMine<--  arg1: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , arg1 , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_TownThreatened )( );
GAME_TownThreatened GAME_TownThreatenedorg = NULL;
GAME_TownThreatened GAME_TownThreatenedold = NULL;

BOOL __cdecl GAME_TownThreatenedmy( )
{
	fprintf_s( logfile , "%s" , "TownThreatenedmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_TownThreatenedold( );
	fprintf_s( logfile , "%s:[-->GAME_TownThreatened<-- ] RETURN-> %s\n" , currentDateTime( ).c_str( ) , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_TownWithMine )( );
GAME_TownWithMine GAME_TownWithMineorg = NULL;
GAME_TownWithMine GAME_TownWithMineold = NULL;

int __cdecl GAME_TownWithMinemy( )
{
	fprintf_s( logfile , "%s" , "TownWithMinemy\n" );
	fflush( logfile );

	int retvalue = GAME_TownWithMineold( );
	fprintf_s( logfile , "%s:[-->GAME_TownWithMine<-- ] RETURN-> %i\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTRIGGERACTION( __cdecl *GAME_TriggerAddAction )( HTRIGGER whichTrigger , CODE actionFunc );
GAME_TriggerAddAction GAME_TriggerAddActionorg = NULL;
GAME_TriggerAddAction GAME_TriggerAddActionold = NULL;

HTRIGGERACTION __cdecl GAME_TriggerAddActionmy( HTRIGGER whichTrigger , CODE actionFunc )
{
	fprintf_s( logfile , "%s\n" , "TriggerAddActionmy" );
	fflush( logfile );

	HTRIGGERACTION retvalue = GAME_TriggerAddActionold( whichTrigger , actionFunc );
	fprintf_s( logfile , "%s:[-->GAME_TriggerAddAction<--  whichTrigger: %X actionFunc: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , actionFunc , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HTRIGGERCONDITION( __cdecl *GAME_TriggerAddCondition )( HTRIGGER whichTrigger , HBOOLEXPR condition );
GAME_TriggerAddCondition GAME_TriggerAddConditionorg = NULL;
GAME_TriggerAddCondition GAME_TriggerAddConditionold = NULL;

HTRIGGERCONDITION __cdecl GAME_TriggerAddConditionmy( HTRIGGER whichTrigger , HBOOLEXPR condition )
{
	fprintf_s( logfile , "%s\n" , "TriggerAddConditionmy" );
	fflush( logfile );

	HTRIGGERCONDITION retvalue = GAME_TriggerAddConditionold( whichTrigger , condition );
	fprintf_s( logfile , "%s:[-->GAME_TriggerAddCondition<--  whichTrigger: %X condition: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , condition , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_TriggerClearActions )( HTRIGGER whichTrigger );
GAME_TriggerClearActions GAME_TriggerClearActionsorg = NULL;
GAME_TriggerClearActions GAME_TriggerClearActionsold = NULL;

void __cdecl GAME_TriggerClearActionsmy( HTRIGGER whichTrigger )
{
	fprintf_s( logfile , "%s\n" , "TriggerClearActionsmy" );
	fflush( logfile );

	GAME_TriggerClearActionsold( whichTrigger );
	fprintf_s( logfile , "%s:[-->GAME_TriggerClearActions<--  whichTrigger: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichTrigger );
	fflush( logfile );

}


typedef void( __cdecl *GAME_TriggerClearConditions )( HTRIGGER whichTrigger );
GAME_TriggerClearConditions GAME_TriggerClearConditionsorg = NULL;
GAME_TriggerClearConditions GAME_TriggerClearConditionsold = NULL;

void __cdecl GAME_TriggerClearConditionsmy( HTRIGGER whichTrigger )
{
	fprintf_s( logfile , "%s\n" , "TriggerClearConditionsmy" );
	fflush( logfile );

	GAME_TriggerClearConditionsold( whichTrigger );
	fprintf_s( logfile , "%s:[-->GAME_TriggerClearConditions<--  whichTrigger: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichTrigger );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_TriggerEvaluate )( HTRIGGER whichTrigger );
GAME_TriggerEvaluate GAME_TriggerEvaluateorg = NULL;
GAME_TriggerEvaluate GAME_TriggerEvaluateold = NULL;

BOOL __cdecl GAME_TriggerEvaluatemy( HTRIGGER whichTrigger )
{
	fprintf_s( logfile , "%s\n" , "TriggerEvaluatemy" );
	fflush( logfile );

	BOOL retvalue = GAME_TriggerEvaluateold( whichTrigger );
	fprintf_s( logfile , "%s:[-->GAME_TriggerEvaluate<--  whichTrigger: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichTrigger , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_TriggerExecute )( HTRIGGER whichTrigger );
GAME_TriggerExecute GAME_TriggerExecuteorg = NULL;
GAME_TriggerExecute GAME_TriggerExecuteold = NULL;

void __cdecl GAME_TriggerExecutemy( HTRIGGER whichTrigger )
{
	fprintf_s( logfile , "%s" , "TriggerExecutemy\n" );
	fflush( logfile );

	GAME_TriggerExecuteold( whichTrigger );
	fprintf_s( logfile , "%s:[-->GAME_TriggerExecute<--  whichTrigger: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichTrigger );
	fflush( logfile );

}


typedef void( __cdecl *GAME_TriggerExecuteWait )( HTRIGGER whichTrigger );
GAME_TriggerExecuteWait GAME_TriggerExecuteWaitorg = NULL;
GAME_TriggerExecuteWait GAME_TriggerExecuteWaitold = NULL;

void __cdecl GAME_TriggerExecuteWaitmy( HTRIGGER whichTrigger )
{
	fprintf_s( logfile , "%s\n" , "TriggerExecuteWaitmy" );
	fflush( logfile );

	GAME_TriggerExecuteWaitold( whichTrigger );
	fprintf_s( logfile , "%s:[-->GAME_TriggerExecuteWait<--  whichTrigger: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichTrigger );
	fflush( logfile );

}


typedef HEVENT( __cdecl *GAME_TriggerRegisterDeathEvent )( HTRIGGER whichTrigger , HWIDGET whichWidget );
GAME_TriggerRegisterDeathEvent GAME_TriggerRegisterDeathEventorg = NULL;
GAME_TriggerRegisterDeathEvent GAME_TriggerRegisterDeathEventold = NULL;

HEVENT __cdecl GAME_TriggerRegisterDeathEventmy( HTRIGGER whichTrigger , HWIDGET whichWidget )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterDeathEventmy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterDeathEventold( whichTrigger , whichWidget );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterDeathEvent<--  whichTrigger: %X whichWidget: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , whichWidget , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterDialogButtonEvent )( HTRIGGER whichTrigger , HBUTTON whichButton );
GAME_TriggerRegisterDialogButtonEvent GAME_TriggerRegisterDialogButtonEventorg = NULL;
GAME_TriggerRegisterDialogButtonEvent GAME_TriggerRegisterDialogButtonEventold = NULL;

HEVENT __cdecl GAME_TriggerRegisterDialogButtonEventmy( HTRIGGER whichTrigger , HBUTTON whichButton )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterDialogButtonEventmy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterDialogButtonEventold( whichTrigger , whichButton );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterDialogButtonEvent<--  whichTrigger: %X whichButton: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , whichButton , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterDialogEvent )( HTRIGGER whichTrigger , HDIALOG whichDialog );
GAME_TriggerRegisterDialogEvent GAME_TriggerRegisterDialogEventorg = NULL;
GAME_TriggerRegisterDialogEvent GAME_TriggerRegisterDialogEventold = NULL;

HEVENT __cdecl GAME_TriggerRegisterDialogEventmy( HTRIGGER whichTrigger , HDIALOG whichDialog )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterDialogEventmy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterDialogEventold( whichTrigger , whichDialog );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterDialogEvent<--  whichTrigger: %X whichDialog: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , whichDialog , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterEnterRegion )( HTRIGGER whichTrigger , HREGION whichRegion , HBOOLEXPR filter );
GAME_TriggerRegisterEnterRegion GAME_TriggerRegisterEnterRegionorg = NULL;
GAME_TriggerRegisterEnterRegion GAME_TriggerRegisterEnterRegionold = NULL;

HEVENT __cdecl GAME_TriggerRegisterEnterRegionmy( HTRIGGER whichTrigger , HREGION whichRegion , HBOOLEXPR filter )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterEnterRegionmy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterEnterRegionold( whichTrigger , whichRegion , filter );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterEnterRegion<--  whichTrigger: %X whichRegion: %X filter: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , whichRegion , filter , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterFilterUnitEvent )( HTRIGGER whichTrigger , HUNIT whichUnit , HUNITEVENT whichEvent , HBOOLEXPR filter );
GAME_TriggerRegisterFilterUnitEvent GAME_TriggerRegisterFilterUnitEventorg = NULL;
GAME_TriggerRegisterFilterUnitEvent GAME_TriggerRegisterFilterUnitEventold = NULL;

HEVENT __cdecl GAME_TriggerRegisterFilterUnitEventmy( HTRIGGER whichTrigger , HUNIT whichUnit , HUNITEVENT whichEvent , HBOOLEXPR filter )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterFilterUnitEventmy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterFilterUnitEventold( whichTrigger , whichUnit , whichEvent , filter );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterFilterUnitEvent<--  whichTrigger: %X whichUnit: %X whichEvent: %X filter: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , whichUnit , whichEvent , filter , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterGameEvent )( HTRIGGER whichTrigger , HGAMEEVENT whichGameEvent );
GAME_TriggerRegisterGameEvent GAME_TriggerRegisterGameEventorg = NULL;
GAME_TriggerRegisterGameEvent GAME_TriggerRegisterGameEventold = NULL;

HEVENT __cdecl GAME_TriggerRegisterGameEventmy( HTRIGGER whichTrigger , HGAMEEVENT whichGameEvent )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterGameEventmy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterGameEventold( whichTrigger , whichGameEvent );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterGameEvent<--  whichTrigger: %X whichGameEvent: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , whichGameEvent , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterGameStateEvent )( HTRIGGER whichTrigger , HGAMESTATE whichState , HLIMITOP opcode , float *limitval );
GAME_TriggerRegisterGameStateEvent GAME_TriggerRegisterGameStateEventorg = NULL;
GAME_TriggerRegisterGameStateEvent GAME_TriggerRegisterGameStateEventold = NULL;

HEVENT __cdecl GAME_TriggerRegisterGameStateEventmy( HTRIGGER whichTrigger , HGAMESTATE whichState , HLIMITOP opcode , float *limitval )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterGameStateEventmy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterGameStateEventold( whichTrigger , whichState , opcode , limitval );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterGameStateEvent<--  whichTrigger: %X whichState: %X opcode: %X limitval: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , whichState , opcode , *( float * ) limitval , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterLeaveRegion )( HTRIGGER whichTrigger , HREGION whichRegion , HBOOLEXPR filter );
GAME_TriggerRegisterLeaveRegion GAME_TriggerRegisterLeaveRegionorg = NULL;
GAME_TriggerRegisterLeaveRegion GAME_TriggerRegisterLeaveRegionold = NULL;

HEVENT __cdecl GAME_TriggerRegisterLeaveRegionmy( HTRIGGER whichTrigger , HREGION whichRegion , HBOOLEXPR filter )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterLeaveRegionmy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterLeaveRegionold( whichTrigger , whichRegion , filter );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterLeaveRegion<--  whichTrigger: %X whichRegion: %X filter: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , whichRegion , filter , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterPlayerAllianceChange )( HTRIGGER whichTrigger , HPLAYER whichPlayer , HALLIANCETYPE whichAlliance );
GAME_TriggerRegisterPlayerAllianceChange GAME_TriggerRegisterPlayerAllianceChangeorg = NULL;
GAME_TriggerRegisterPlayerAllianceChange GAME_TriggerRegisterPlayerAllianceChangeold = NULL;

HEVENT __cdecl GAME_TriggerRegisterPlayerAllianceChangemy( HTRIGGER whichTrigger , HPLAYER whichPlayer , HALLIANCETYPE whichAlliance )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterPlayerAllianceChangemy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterPlayerAllianceChangeold( whichTrigger , whichPlayer , whichAlliance );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterPlayerAllianceChange<--  whichTrigger: %X whichPlayer: %X whichAlliance: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , whichPlayer , whichAlliance , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterPlayerChatEvent )( HTRIGGER whichTrigger , HPLAYER whichPlayer , void * chatMessageToDetect , BOOL exactMatchOnly );
GAME_TriggerRegisterPlayerChatEvent GAME_TriggerRegisterPlayerChatEventorg = NULL;
GAME_TriggerRegisterPlayerChatEvent GAME_TriggerRegisterPlayerChatEventold = NULL;

HEVENT __cdecl GAME_TriggerRegisterPlayerChatEventmy( HTRIGGER whichTrigger , HPLAYER whichPlayer , void * chatMessageToDetect , BOOL exactMatchOnly )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterPlayerChatEventmy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterPlayerChatEventold( whichTrigger , whichPlayer , chatMessageToDetect , exactMatchOnly );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterPlayerChatEvent<--  whichTrigger: %X whichPlayer: %X chatMessageToDetect: \"%s\" exactMatchOnly: %s] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , whichPlayer , jassgetchar( chatMessageToDetect ) , exactMatchOnly ? "TRUE" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterPlayerEvent )( HTRIGGER whichTrigger , HPLAYER whichPlayer , HPLAYEREVENT whichPlayerEvent );
GAME_TriggerRegisterPlayerEvent GAME_TriggerRegisterPlayerEventorg = NULL;
GAME_TriggerRegisterPlayerEvent GAME_TriggerRegisterPlayerEventold = NULL;

HEVENT __cdecl GAME_TriggerRegisterPlayerEventmy( HTRIGGER whichTrigger , HPLAYER whichPlayer , HPLAYEREVENT whichPlayerEvent )
{
	fprintf_s( logfile , "%s" , "TriggerRegisterPlayerEventmy\n" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterPlayerEventold( whichTrigger , whichPlayer , whichPlayerEvent );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterPlayerEvent<--  whichTrigger: %X whichPlayer: %X whichPlayerEvent: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , whichPlayer , whichPlayerEvent , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterPlayerStateEvent )( HTRIGGER whichTrigger , HPLAYER whichPlayer , HPLAYERSTATE whichState , HLIMITOP opcode , float *limitval );
GAME_TriggerRegisterPlayerStateEvent GAME_TriggerRegisterPlayerStateEventorg = NULL;
GAME_TriggerRegisterPlayerStateEvent GAME_TriggerRegisterPlayerStateEventold = NULL;

HEVENT __cdecl GAME_TriggerRegisterPlayerStateEventmy( HTRIGGER whichTrigger , HPLAYER whichPlayer , HPLAYERSTATE whichState , HLIMITOP opcode , float *limitval )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterPlayerStateEventmy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterPlayerStateEventold( whichTrigger , whichPlayer , whichState , opcode , limitval );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterPlayerStateEvent<--  whichTrigger: %X whichPlayer: %X whichState: %X opcode: %X limitval: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , whichPlayer , whichState , opcode , *( float * ) limitval , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterPlayerUnitEvent )( HTRIGGER whichTrigger , HPLAYER whichPlayer , HPLAYERUNITEVENT whichPlayerUnitEvent , HBOOLEXPR filter );
GAME_TriggerRegisterPlayerUnitEvent GAME_TriggerRegisterPlayerUnitEventorg = NULL;
GAME_TriggerRegisterPlayerUnitEvent GAME_TriggerRegisterPlayerUnitEventold = NULL;

HEVENT __cdecl GAME_TriggerRegisterPlayerUnitEventmy( HTRIGGER whichTrigger , HPLAYER whichPlayer , HPLAYERUNITEVENT whichPlayerUnitEvent , HBOOLEXPR filter )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterPlayerUnitEventmy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterPlayerUnitEventold( whichTrigger , whichPlayer , whichPlayerUnitEvent , filter );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterPlayerUnitEvent<--  whichTrigger: %X whichPlayer: %X whichPlayerUnitEvent: %X filter: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , whichPlayer , whichPlayerUnitEvent , filter , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterTimerEvent )( HTRIGGER whichTrigger , float *timeout , BOOL periodic );
GAME_TriggerRegisterTimerEvent GAME_TriggerRegisterTimerEventorg = NULL;
GAME_TriggerRegisterTimerEvent GAME_TriggerRegisterTimerEventold = NULL;

HEVENT __cdecl GAME_TriggerRegisterTimerEventmy( HTRIGGER whichTrigger , float *timeout , BOOL periodic )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterTimerEventmy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterTimerEventold( whichTrigger , timeout , periodic );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterTimerEvent<--  whichTrigger: %X timeout: %f periodic: %s] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , *( float * ) timeout , periodic ? "TRUE\n" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterTimerExpireEvent )( HTRIGGER whichTrigger , HTIMER t );
GAME_TriggerRegisterTimerExpireEvent GAME_TriggerRegisterTimerExpireEventorg = NULL;
GAME_TriggerRegisterTimerExpireEvent GAME_TriggerRegisterTimerExpireEventold = NULL;

HEVENT __cdecl GAME_TriggerRegisterTimerExpireEventmy( HTRIGGER whichTrigger , HTIMER t )
{
	fprintf_s( logfile , "%s" , "TriggerRegisterTimerExpireEventmy\n" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterTimerExpireEventold( whichTrigger , t );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterTimerExpireEvent<--  whichTrigger: %X t: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , t , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterTrackableHitEvent )( HTRIGGER whichTrigger , HTRACKABLE t );
GAME_TriggerRegisterTrackableHitEvent GAME_TriggerRegisterTrackableHitEventorg = NULL;
GAME_TriggerRegisterTrackableHitEvent GAME_TriggerRegisterTrackableHitEventold = NULL;

HEVENT __cdecl GAME_TriggerRegisterTrackableHitEventmy( HTRIGGER whichTrigger , HTRACKABLE t )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterTrackableHitEventmy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterTrackableHitEventold( whichTrigger , t );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterTrackableHitEvent<--  whichTrigger: %X t: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , t , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterTrackableTrackEvent )( HTRIGGER whichTrigger , HTRACKABLE t );
GAME_TriggerRegisterTrackableTrackEvent GAME_TriggerRegisterTrackableTrackEventorg = NULL;
GAME_TriggerRegisterTrackableTrackEvent GAME_TriggerRegisterTrackableTrackEventold = NULL;

HEVENT __cdecl GAME_TriggerRegisterTrackableTrackEventmy( HTRIGGER whichTrigger , HTRACKABLE t )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterTrackableTrackEventmy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterTrackableTrackEventold( whichTrigger , t );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterTrackableTrackEvent<--  whichTrigger: %X t: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , t , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterUnitEvent )( HTRIGGER whichTrigger , HUNIT whichUnit , HUNITEVENT whichEvent );
GAME_TriggerRegisterUnitEvent GAME_TriggerRegisterUnitEventorg = NULL;
GAME_TriggerRegisterUnitEvent GAME_TriggerRegisterUnitEventold = NULL;

HEVENT __cdecl GAME_TriggerRegisterUnitEventmy( HTRIGGER whichTrigger , HUNIT whichUnit , HUNITEVENT whichEvent )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterUnitEventmy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterUnitEventold( whichTrigger , whichUnit , whichEvent );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterUnitEvent<--  whichTrigger: %X whichUnit: %X whichEvent: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , whichUnit , whichEvent , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterUnitInRange )( HTRIGGER whichTrigger , HUNIT whichUnit , float *range , HBOOLEXPR filter );
GAME_TriggerRegisterUnitInRange GAME_TriggerRegisterUnitInRangeorg = NULL;
GAME_TriggerRegisterUnitInRange GAME_TriggerRegisterUnitInRangeold = NULL;

HEVENT __cdecl GAME_TriggerRegisterUnitInRangemy( HTRIGGER whichTrigger , HUNIT whichUnit , float *range , HBOOLEXPR filter )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterUnitInRangemy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterUnitInRangeold( whichTrigger , whichUnit , range , filter );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterUnitInRange<--  whichTrigger: %X whichUnit: %X range: %f filter: %X] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , whichUnit , *( float * ) range , filter , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterUnitStateEvent )( HTRIGGER whichTrigger , HUNIT whichUnit , HUNITSTATE whichState , HLIMITOP opcode , float *limitval );
GAME_TriggerRegisterUnitStateEvent GAME_TriggerRegisterUnitStateEventorg = NULL;
GAME_TriggerRegisterUnitStateEvent GAME_TriggerRegisterUnitStateEventold = NULL;

HEVENT __cdecl GAME_TriggerRegisterUnitStateEventmy( HTRIGGER whichTrigger , HUNIT whichUnit , HUNITSTATE whichState , HLIMITOP opcode , float *limitval )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterUnitStateEventmy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterUnitStateEventold( whichTrigger , whichUnit , whichState , opcode , limitval );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterUnitStateEvent<--  whichTrigger: %X whichUnit: %X whichState: %X opcode: %X limitval: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , whichUnit , whichState , opcode , *( float * ) limitval , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef HEVENT( __cdecl *GAME_TriggerRegisterVariableEvent )( HTRIGGER whichTrigger , void * varName , HLIMITOP opcode , float *limitval );
GAME_TriggerRegisterVariableEvent GAME_TriggerRegisterVariableEventorg = NULL;
GAME_TriggerRegisterVariableEvent GAME_TriggerRegisterVariableEventold = NULL;

HEVENT __cdecl GAME_TriggerRegisterVariableEventmy( HTRIGGER whichTrigger , void * varName , HLIMITOP opcode , float *limitval )
{
	fprintf_s( logfile , "%s\n" , "TriggerRegisterVariableEventmy" );
	fflush( logfile );

	HEVENT retvalue = GAME_TriggerRegisterVariableEventold( whichTrigger , varName , opcode , limitval );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRegisterVariableEvent<--  whichTrigger: %X varName: \"%s\" opcode: %X limitval: %f] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichTrigger , jassgetchar( varName ) , opcode , *( float * ) limitval , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_TriggerRemoveAction )( HTRIGGER whichTrigger , HTRIGGERACTION whichAction );
GAME_TriggerRemoveAction GAME_TriggerRemoveActionorg = NULL;
GAME_TriggerRemoveAction GAME_TriggerRemoveActionold = NULL;

void __cdecl GAME_TriggerRemoveActionmy( HTRIGGER whichTrigger , HTRIGGERACTION whichAction )
{
	fprintf_s( logfile , "%s" , "TriggerRemoveActionmy\n" );
	fflush( logfile );

	GAME_TriggerRemoveActionold( whichTrigger , whichAction );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRemoveAction<--  whichTrigger: %X whichAction: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichTrigger , whichAction );
	fflush( logfile );

}


typedef void( __cdecl *GAME_TriggerRemoveCondition )( HTRIGGER whichTrigger , HTRIGGERCONDITION whichCondition );
GAME_TriggerRemoveCondition GAME_TriggerRemoveConditionorg = NULL;
GAME_TriggerRemoveCondition GAME_TriggerRemoveConditionold = NULL;

void __cdecl GAME_TriggerRemoveConditionmy( HTRIGGER whichTrigger , HTRIGGERCONDITION whichCondition )
{
	fprintf_s( logfile , "%s\n" , "TriggerRemoveConditionmy" );
	fflush( logfile );

	GAME_TriggerRemoveConditionold( whichTrigger , whichCondition );
	fprintf_s( logfile , "%s:[-->GAME_TriggerRemoveCondition<--  whichTrigger: %X whichCondition: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichTrigger , whichCondition );
	fflush( logfile );

}


typedef void( __cdecl *GAME_TriggerSleepAction )( float *timeout );
GAME_TriggerSleepAction GAME_TriggerSleepActionorg = NULL;
GAME_TriggerSleepAction GAME_TriggerSleepActionold = NULL;

void __cdecl GAME_TriggerSleepActionmy( float *timeout )
{
	fprintf_s( logfile , "%s\n" , "TriggerSleepActionmy" );
	fflush( logfile );

	GAME_TriggerSleepActionold( timeout );
	fprintf_s( logfile , "%s:[-->GAME_TriggerSleepAction<--  timeout: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , *( float * ) timeout );
	fflush( logfile );

}


typedef void( __cdecl *GAME_TriggerSyncReady )( );
GAME_TriggerSyncReady GAME_TriggerSyncReadyorg = NULL;
GAME_TriggerSyncReady GAME_TriggerSyncReadyold = NULL;

void __cdecl GAME_TriggerSyncReadymy( )
{
	fprintf_s( logfile , "%s\n" , "TriggerSyncReadymy" );
	fflush( logfile );

	GAME_TriggerSyncReadyold( );
	fprintf_s( logfile , "%s:[-->GAME_TriggerSyncReady<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_TriggerSyncStart )( );
GAME_TriggerSyncStart GAME_TriggerSyncStartorg = NULL;
GAME_TriggerSyncStart GAME_TriggerSyncStartold = NULL;

void __cdecl GAME_TriggerSyncStartmy( )
{
	fprintf_s( logfile , "%s\n" , "TriggerSyncStartmy" );
	fflush( logfile );

	GAME_TriggerSyncStartold( );
	fprintf_s( logfile , "%s:[-->GAME_TriggerSyncStart<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_TriggerWaitForSound )( HSOUND s , float *offset );
GAME_TriggerWaitForSound GAME_TriggerWaitForSoundorg = NULL;
GAME_TriggerWaitForSound GAME_TriggerWaitForSoundold = NULL;

void __cdecl GAME_TriggerWaitForSoundmy( HSOUND s , float *offset )
{
	fprintf_s( logfile , "%s\n" , "TriggerWaitForSoundmy" );
	fflush( logfile );

	GAME_TriggerWaitForSoundold( s , offset );
	fprintf_s( logfile , "%s:[-->GAME_TriggerWaitForSound<--  s: %X offset: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , s , *( float * ) offset );
	fflush( logfile );

}


typedef void( __cdecl *GAME_TriggerWaitOnSleeps )( HTRIGGER whichTrigger , BOOL flag );
GAME_TriggerWaitOnSleeps GAME_TriggerWaitOnSleepsorg = NULL;
GAME_TriggerWaitOnSleeps GAME_TriggerWaitOnSleepsold = NULL;

void __cdecl GAME_TriggerWaitOnSleepsmy( HTRIGGER whichTrigger , BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "TriggerWaitOnSleepsmy" );
	fflush( logfile );

	GAME_TriggerWaitOnSleepsold( whichTrigger , flag );
	fprintf_s( logfile , "%s:[-->GAME_TriggerWaitOnSleeps<--  whichTrigger: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichTrigger , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_UnitAddAbility )( HUNIT whichUnit , int abilityId );
GAME_UnitAddAbility GAME_UnitAddAbilityorg = NULL;
GAME_UnitAddAbility GAME_UnitAddAbilityold = NULL;

BOOL __cdecl GAME_UnitAddAbilitymy( HUNIT whichUnit , int abilityId )
{
	fprintf_s( logfile , "%s" , "UnitAddAbilitymy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitAddAbilityold( whichUnit , abilityId );
	fprintf_s( logfile , "%s:[-->GAME_UnitAddAbility<--  whichUnit: %X abilityId: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , abilityId , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_UnitAddIndicator )( HUNIT whichUnit , int red , int green , int blue , int alpha );
GAME_UnitAddIndicator GAME_UnitAddIndicatororg = NULL;
GAME_UnitAddIndicator GAME_UnitAddIndicatorold = NULL;

void __cdecl GAME_UnitAddIndicatormy( HUNIT whichUnit , int red , int green , int blue , int alpha )
{
	fprintf_s( logfile , "%s" , "UnitAddIndicatormy\n" );
	fflush( logfile );

	GAME_UnitAddIndicatorold( whichUnit , red , green , blue , alpha );
	fprintf_s( logfile , "%s:[-->GAME_UnitAddIndicator<--  whichUnit: %X red: %i green: %i blue: %i alpha: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , red , green , blue , alpha );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_UnitAddItem )( HUNIT whichUnit , HITEM whichItem );
GAME_UnitAddItem GAME_UnitAddItemorg = NULL;
GAME_UnitAddItem GAME_UnitAddItemold = NULL;

BOOL __cdecl GAME_UnitAddItemmy( HUNIT whichUnit , HITEM whichItem )
{
	fprintf_s( logfile , "%s\n" , "UnitAddItemmy" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitAddItemold( whichUnit , whichItem );
	fprintf_s( logfile , "%s:[-->GAME_UnitAddItem<--  whichUnit: %X whichItem: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichItem , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef HITEM( __cdecl *GAME_UnitAddItemById )( HUNIT whichUnit , int itemId );
GAME_UnitAddItemById GAME_UnitAddItemByIdorg = NULL;
GAME_UnitAddItemById GAME_UnitAddItemByIdold = NULL;

HITEM __cdecl GAME_UnitAddItemByIdmy( HUNIT whichUnit , int itemId )
{
	fprintf_s( logfile , "%s" , "UnitAddItemByIdmy\n" );
	fflush( logfile );

	HITEM retvalue = GAME_UnitAddItemByIdold( whichUnit , itemId );
	fprintf_s( logfile , "%s:[-->GAME_UnitAddItemById<--  whichUnit: %X itemId: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichUnit , itemId , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitAddItemToSlotById )( HUNIT whichUnit , int itemId , int itemSlot );
GAME_UnitAddItemToSlotById GAME_UnitAddItemToSlotByIdorg = NULL;
GAME_UnitAddItemToSlotById GAME_UnitAddItemToSlotByIdold = NULL;

BOOL __cdecl GAME_UnitAddItemToSlotByIdmy( HUNIT whichUnit , int itemId , int itemSlot )
{
	fprintf_s( logfile , "%s\n" , "UnitAddItemToSlotByIdmy" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitAddItemToSlotByIdold( whichUnit , itemId , itemSlot );
	fprintf_s( logfile , "%s:[-->GAME_UnitAddItemToSlotById<--  whichUnit: %X itemId: %i itemSlot: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , itemId , itemSlot , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_UnitAddSleep )( HUNIT whichUnit , BOOL add );
GAME_UnitAddSleep GAME_UnitAddSleeporg = NULL;
GAME_UnitAddSleep GAME_UnitAddSleepold = NULL;

void __cdecl GAME_UnitAddSleepmy( HUNIT whichUnit , BOOL add )
{
	fprintf_s( logfile , "%s" , "UnitAddSleepmy\n" );
	fflush( logfile );

	GAME_UnitAddSleepold( whichUnit , add );
	fprintf_s( logfile , "%s:[-->GAME_UnitAddSleep<--  whichUnit: %X add: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , add ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_UnitAddSleepPerm )( HUNIT whichUnit , BOOL add );
GAME_UnitAddSleepPerm GAME_UnitAddSleepPermorg = NULL;
GAME_UnitAddSleepPerm GAME_UnitAddSleepPermold = NULL;

void __cdecl GAME_UnitAddSleepPermmy( HUNIT whichUnit , BOOL add )
{
	fprintf_s( logfile , "%s" , "UnitAddSleepPermmy\n" );
	fflush( logfile );

	GAME_UnitAddSleepPermold( whichUnit , add );
	fprintf_s( logfile , "%s:[-->GAME_UnitAddSleepPerm<--  whichUnit: %X add: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , add ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_UnitAddType )( HUNIT whichUnit , HUNITTYPE whichUnitType );
GAME_UnitAddType GAME_UnitAddTypeorg = NULL;
GAME_UnitAddType GAME_UnitAddTypeold = NULL;

BOOL __cdecl GAME_UnitAddTypemy( HUNIT whichUnit , HUNITTYPE whichUnitType )
{
	fprintf_s( logfile , "%s" , "UnitAddTypemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitAddTypeold( whichUnit , whichUnitType );
	fprintf_s( logfile , "%s:[-->GAME_UnitAddType<--  whichUnit: %X whichUnitType: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichUnitType , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitAlive )( HUNIT arg1 );
GAME_UnitAlive GAME_UnitAliveorg = NULL;
GAME_UnitAlive GAME_UnitAliveold = NULL;

BOOL __cdecl GAME_UnitAlivemy( HUNIT arg1 )
{
	fprintf_s( logfile , "%s" , "UnitAlivemy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitAliveold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_UnitAlive<--  arg1: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , arg1 , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_UnitApplyTimedLife )( HUNIT whichUnit , int buffId , float *duration );
GAME_UnitApplyTimedLife GAME_UnitApplyTimedLifeorg = NULL;
GAME_UnitApplyTimedLife GAME_UnitApplyTimedLifeold = NULL;

void __cdecl GAME_UnitApplyTimedLifemy( HUNIT whichUnit , int buffId , float *duration )
{
	fprintf_s( logfile , "%s" , "UnitApplyTimedLifemy\n" );
	fflush( logfile );

	GAME_UnitApplyTimedLifeold( whichUnit , buffId , duration );
	fprintf_s( logfile , "%s:[-->GAME_UnitApplyTimedLife<--  whichUnit: %X buffId: %i duration: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , buffId , *( float * ) duration );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_UnitCanSleep )( HUNIT whichUnit );
GAME_UnitCanSleep GAME_UnitCanSleeporg = NULL;
GAME_UnitCanSleep GAME_UnitCanSleepold = NULL;

BOOL __cdecl GAME_UnitCanSleepmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s\n" , "UnitCanSleepmy" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitCanSleepold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_UnitCanSleep<--  whichUnit: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitCanSleepPerm )( HUNIT whichUnit );
GAME_UnitCanSleepPerm GAME_UnitCanSleepPermorg = NULL;
GAME_UnitCanSleepPerm GAME_UnitCanSleepPermold = NULL;

BOOL __cdecl GAME_UnitCanSleepPermmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s" , "UnitCanSleepPermmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitCanSleepPermold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_UnitCanSleepPerm<--  whichUnit: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_UnitCountBuffsEx )( HUNIT whichUnit , BOOL removePositive , BOOL removeNegative , BOOL magic , BOOL physical , BOOL timedLife , BOOL aura , BOOL autoDispel );
GAME_UnitCountBuffsEx GAME_UnitCountBuffsExorg = NULL;
GAME_UnitCountBuffsEx GAME_UnitCountBuffsExold = NULL;

int __cdecl GAME_UnitCountBuffsExmy( HUNIT whichUnit , BOOL removePositive , BOOL removeNegative , BOOL magic , BOOL physical , BOOL timedLife , BOOL aura , BOOL autoDispel )
{
	fprintf_s( logfile , "%s" , "UnitCountBuffsExmy\n" );
	fflush( logfile );

	int retvalue = GAME_UnitCountBuffsExold( whichUnit , removePositive , removeNegative , magic , physical , timedLife , aura , autoDispel );
	fprintf_s( logfile , "%s:[-->GAME_UnitCountBuffsEx<--  whichUnit: %X removePositive: %s removeNegative: %s magic: %s physical: %s timedLife: %s aura: %s autoDispel: %s] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichUnit , removePositive ? "TRUE\n" : "FALSE" , removeNegative ? "TRUE" : "FALSE" , magic ? "TRUE" : "FALSE" , physical ? "TRUE" : "FALSE" , timedLife ? "TRUE" : "FALSE" , aura ? "TRUE" : "FALSE" , autoDispel ? "TRUE" : "FALSE" , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitDamagePoint )( HUNIT whichUnit , float *delay , float *radius , float *x , float *y , float *amount , BOOL attack , BOOL ranged , HATTACKTYPE attackType , HDAMAGETYPE damageType , HWEAPONTYPE weaponType );
GAME_UnitDamagePoint GAME_UnitDamagePointorg = NULL;
GAME_UnitDamagePoint GAME_UnitDamagePointold = NULL;

BOOL __cdecl GAME_UnitDamagePointmy( HUNIT whichUnit , float *delay , float *radius , float *x , float *y , float *amount , BOOL attack , BOOL ranged , HATTACKTYPE attackType , HDAMAGETYPE damageType , HWEAPONTYPE weaponType )
{
	fprintf_s( logfile , "%s" , "UnitDamagePointmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitDamagePointold( whichUnit , delay , radius , x , y , amount , attack , ranged , attackType , damageType , weaponType );
	fprintf_s( logfile , "%s:[-->GAME_UnitDamagePoint<--  whichUnit: %X delay: %f radius: %f x: %f y: %f amount: %f attack: %s ranged: %s attackType: %X damageType: %X weaponType: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , *( float * ) delay , *( float * ) radius , *( float * ) x , *( float * ) y , *( float * ) amount , attack ? "TRUE\n" : "FALSE" , ranged ? "TRUE" : "FALSE" , attackType , damageType , weaponType , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitDamageTarget )( HUNIT whichUnit , HWIDGET target , float *amount , BOOL attack , BOOL ranged , HATTACKTYPE attackType , HDAMAGETYPE damageType , HWEAPONTYPE weaponType );
GAME_UnitDamageTarget GAME_UnitDamageTargetorg = NULL;
GAME_UnitDamageTarget GAME_UnitDamageTargetold = NULL;

BOOL __cdecl GAME_UnitDamageTargetmy( HUNIT whichUnit , HWIDGET target , float *amount , BOOL attack , BOOL ranged , HATTACKTYPE attackType , HDAMAGETYPE damageType , HWEAPONTYPE weaponType )
{
	fprintf_s( logfile , "%s" , "UnitDamageTargetmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitDamageTargetold( whichUnit , target , amount , attack , ranged , attackType , damageType , weaponType );
	fprintf_s( logfile , "%s:[-->GAME_UnitDamageTarget<--  whichUnit: %X target: %X amount: %f attack: %s ranged: %s attackType: %X damageType: %X weaponType: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , target , *( float * ) amount , attack ? "TRUE\n" : "FALSE" , ranged ? "TRUE" : "FALSE" , attackType , damageType , weaponType , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitDropItemPoint )( HUNIT whichUnit , HITEM whichItem , float *x , float *y );
GAME_UnitDropItemPoint GAME_UnitDropItemPointorg = NULL;
GAME_UnitDropItemPoint GAME_UnitDropItemPointold = NULL;

BOOL __cdecl GAME_UnitDropItemPointmy( HUNIT whichUnit , HITEM whichItem , float *x , float *y )
{
	fprintf_s( logfile , "%s" , "UnitDropItemPointmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitDropItemPointold( whichUnit , whichItem , x , y );
	fprintf_s( logfile , "%s:[-->GAME_UnitDropItemPoint<--  whichUnit: %X whichItem: %X x: %f y: %f] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichItem , *( float * ) x , *( float * ) y , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitDropItemSlot )( HUNIT whichUnit , HITEM whichItem , int slot );
GAME_UnitDropItemSlot GAME_UnitDropItemSlotorg = NULL;
GAME_UnitDropItemSlot GAME_UnitDropItemSlotold = NULL;

BOOL __cdecl GAME_UnitDropItemSlotmy( HUNIT whichUnit , HITEM whichItem , int slot )
{
	fprintf_s( logfile , "%s" , "UnitDropItemSlotmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitDropItemSlotold( whichUnit , whichItem , slot );
	fprintf_s( logfile , "%s:[-->GAME_UnitDropItemSlot<--  whichUnit: %X whichItem: %X slot: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichItem , slot , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitDropItemTarget )( HUNIT whichUnit , HITEM whichItem , HWIDGET target );
GAME_UnitDropItemTarget GAME_UnitDropItemTargetorg = NULL;
GAME_UnitDropItemTarget GAME_UnitDropItemTargetold = NULL;

BOOL __cdecl GAME_UnitDropItemTargetmy( HUNIT whichUnit , HITEM whichItem , HWIDGET target )
{
	fprintf_s( logfile , "%s" , "UnitDropItemTargetmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitDropItemTargetold( whichUnit , whichItem , target );
	fprintf_s( logfile , "%s:[-->GAME_UnitDropItemTarget<--  whichUnit: %X whichItem: %X target: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichItem , target , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitHasBuffsEx )( HUNIT whichUnit , BOOL removePositive , BOOL removeNegative , BOOL magic , BOOL physical , BOOL timedLife , BOOL aura , BOOL autoDispel );
GAME_UnitHasBuffsEx GAME_UnitHasBuffsExorg = NULL;
GAME_UnitHasBuffsEx GAME_UnitHasBuffsExold = NULL;

BOOL __cdecl GAME_UnitHasBuffsExmy( HUNIT whichUnit , BOOL removePositive , BOOL removeNegative , BOOL magic , BOOL physical , BOOL timedLife , BOOL aura , BOOL autoDispel )
{
	fprintf_s( logfile , "%s" , "UnitHasBuffsExmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitHasBuffsExold( whichUnit , removePositive , removeNegative , magic , physical , timedLife , aura , autoDispel );
	fprintf_s( logfile , "%s:[-->GAME_UnitHasBuffsEx<--  whichUnit: %X removePositive: %s removeNegative: %s magic: %s physical: %s timedLife: %s aura: %s autoDispel: %s] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , removePositive ? "TRUE\n" : "FALSE" , removeNegative ? "TRUE" : "FALSE" , magic ? "TRUE" : "FALSE" , physical ? "TRUE" : "FALSE" , timedLife ? "TRUE" : "FALSE" , aura ? "TRUE" : "FALSE" , autoDispel ? "TRUE" : "FALSE" , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitHasItem )( HUNIT whichUnit , HITEM whichItem );
GAME_UnitHasItem GAME_UnitHasItemorg = NULL;
GAME_UnitHasItem GAME_UnitHasItemold = NULL;

BOOL __cdecl GAME_UnitHasItemmy( HUNIT whichUnit , HITEM whichItem )
{
	fprintf_s( logfile , "%s" , "UnitHasItemmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitHasItemold( whichUnit , whichItem );
	fprintf_s( logfile , "%s:[-->GAME_UnitHasItem<--  whichUnit: %X whichItem: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichItem , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_UnitId )( void * unitIdString );
GAME_UnitId GAME_UnitIdorg = NULL;
GAME_UnitId GAME_UnitIdold = NULL;

int __cdecl GAME_UnitIdmy( void * unitIdString )
{
	fprintf_s( logfile , "%s" , "UnitIdmy\n" );
	fflush( logfile );

	int retvalue = GAME_UnitIdold( unitIdString );
	fprintf_s( logfile , "%s:[-->GAME_UnitId<--  unitIdString: \"%s\"] RETURN-> %i\n" , currentDateTime( ).c_str( ) , jassgetchar( unitIdString ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef DWORD( __cdecl *GAME_UnitId2String )( int unitId );
GAME_UnitId2String GAME_UnitId2Stringorg = NULL;
GAME_UnitId2String GAME_UnitId2Stringold = NULL;

DWORD __cdecl GAME_UnitId2Stringmy( int unitId )
{
	fprintf_s( logfile , "%s" , "UnitId2Stringmy\n" );
	fflush( logfile );

	DWORD retvalue = GAME_UnitId2Stringold( unitId );
	fprintf_s( logfile , "%s:[-->GAME_UnitId2String<--  unitId: %i] RETURN-> STR:%S\n" , currentDateTime( ).c_str( ) , unitId , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitIgnoreAlarm )( HUNIT whichUnit , BOOL flag );
GAME_UnitIgnoreAlarm GAME_UnitIgnoreAlarmorg = NULL;
GAME_UnitIgnoreAlarm GAME_UnitIgnoreAlarmold = NULL;

BOOL __cdecl GAME_UnitIgnoreAlarmmy( HUNIT whichUnit , BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "UnitIgnoreAlarmmy" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitIgnoreAlarmold( whichUnit , flag );
	fprintf_s( logfile , "%s:[-->GAME_UnitIgnoreAlarm<--  whichUnit: %X flag: %s] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , flag ? "TRUE\n" : "FALSE" , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitIgnoreAlarmToggled )( HUNIT whichUnit );
GAME_UnitIgnoreAlarmToggled GAME_UnitIgnoreAlarmToggledorg = NULL;
GAME_UnitIgnoreAlarmToggled GAME_UnitIgnoreAlarmToggledold = NULL;

BOOL __cdecl GAME_UnitIgnoreAlarmToggledmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s" , "UnitIgnoreAlarmToggledmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitIgnoreAlarmToggledold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_UnitIgnoreAlarmToggled<--  whichUnit: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef int( __cdecl *GAME_UnitInventorySize )( HUNIT whichUnit );
GAME_UnitInventorySize GAME_UnitInventorySizeorg = NULL;
GAME_UnitInventorySize GAME_UnitInventorySizeold = NULL;

int __cdecl GAME_UnitInventorySizemy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s" , "UnitInventorySizemy\n" );
	fflush( logfile );

	int retvalue = GAME_UnitInventorySizeold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_UnitInventorySize<--  whichUnit: %X] RETURN-> %i\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitInvis )( HUNIT arg1 );
GAME_UnitInvis GAME_UnitInvisorg = NULL;
GAME_UnitInvis GAME_UnitInvisold = NULL;

BOOL __cdecl GAME_UnitInvismy( HUNIT arg1 )
{
	fprintf_s( logfile , "%s\n" , "UnitInvismy" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitInvisold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_UnitInvis<--  arg1: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , arg1 , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitIsSleeping )( HUNIT whichUnit );
GAME_UnitIsSleeping GAME_UnitIsSleepingorg = NULL;
GAME_UnitIsSleeping GAME_UnitIsSleepingold = NULL;

BOOL __cdecl GAME_UnitIsSleepingmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s" , "UnitIsSleepingmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitIsSleepingold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_UnitIsSleeping<--  whichUnit: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef HITEM( __cdecl *GAME_UnitItemInSlot )( HUNIT whichUnit , int itemSlot );
GAME_UnitItemInSlot GAME_UnitItemInSlotorg = NULL;
GAME_UnitItemInSlot GAME_UnitItemInSlotold = NULL;

HITEM __cdecl GAME_UnitItemInSlotmy( HUNIT whichUnit , int itemSlot )
{
	fprintf_s( logfile , "%s" , "UnitItemInSlotmy\n" );
	fflush( logfile );

	HITEM retvalue = GAME_UnitItemInSlotold( whichUnit , itemSlot );
	fprintf_s( logfile , "%s:[-->GAME_UnitItemInSlot<--  whichUnit: %X itemSlot: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichUnit , itemSlot , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitMakeAbilityPermanent )( HUNIT whichUnit , BOOL permanent , int abilityId );
GAME_UnitMakeAbilityPermanent GAME_UnitMakeAbilityPermanentorg = NULL;
GAME_UnitMakeAbilityPermanent GAME_UnitMakeAbilityPermanentold = NULL;

BOOL __cdecl GAME_UnitMakeAbilityPermanentmy( HUNIT whichUnit , BOOL permanent , int abilityId )
{
	fprintf_s( logfile , "%s\n" , "UnitMakeAbilityPermanentmy" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitMakeAbilityPermanentold( whichUnit , permanent , abilityId );
	fprintf_s( logfile , "%s:[-->GAME_UnitMakeAbilityPermanent<--  whichUnit: %X permanent: %s abilityId: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , permanent ? "TRUE\n" : "FALSE" , abilityId , retvalue ? "TRUE" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitModifySkillPoints )( HUNIT whichHero , int skillPointDelta );
GAME_UnitModifySkillPoints GAME_UnitModifySkillPointsorg = NULL;
GAME_UnitModifySkillPoints GAME_UnitModifySkillPointsold = NULL;

BOOL __cdecl GAME_UnitModifySkillPointsmy( HUNIT whichHero , int skillPointDelta )
{
	fprintf_s( logfile , "%s" , "UnitModifySkillPointsmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitModifySkillPointsold( whichHero , skillPointDelta );
	fprintf_s( logfile , "%s:[-->GAME_UnitModifySkillPoints<--  whichHero: %X skillPointDelta: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichHero , skillPointDelta , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_UnitPauseTimedLife )( HUNIT whichUnit , BOOL flag );
GAME_UnitPauseTimedLife GAME_UnitPauseTimedLifeorg = NULL;
GAME_UnitPauseTimedLife GAME_UnitPauseTimedLifeold = NULL;

void __cdecl GAME_UnitPauseTimedLifemy( HUNIT whichUnit , BOOL flag )
{
	fprintf_s( logfile , "%s" , "UnitPauseTimedLifemy\n" );
	fflush( logfile );

	GAME_UnitPauseTimedLifeold( whichUnit , flag );
	fprintf_s( logfile , "%s:[-->GAME_UnitPauseTimedLife<--  whichUnit: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_UnitPoolAddUnitType )( HUNITPOOL whichPool , int unitId , float *weight );
GAME_UnitPoolAddUnitType GAME_UnitPoolAddUnitTypeorg = NULL;
GAME_UnitPoolAddUnitType GAME_UnitPoolAddUnitTypeold = NULL;

void __cdecl GAME_UnitPoolAddUnitTypemy( HUNITPOOL whichPool , int unitId , float *weight )
{
	fprintf_s( logfile , "%s" , "UnitPoolAddUnitTypemy\n" );
	fflush( logfile );

	GAME_UnitPoolAddUnitTypeold( whichPool , unitId , weight );
	fprintf_s( logfile , "%s:[-->GAME_UnitPoolAddUnitType<--  whichPool: %X unitId: %i weight: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPool , unitId , *( float * ) weight );
	fflush( logfile );

}


typedef void( __cdecl *GAME_UnitPoolRemoveUnitType )( HUNITPOOL whichPool , int unitId );
GAME_UnitPoolRemoveUnitType GAME_UnitPoolRemoveUnitTypeorg = NULL;
GAME_UnitPoolRemoveUnitType GAME_UnitPoolRemoveUnitTypeold = NULL;

void __cdecl GAME_UnitPoolRemoveUnitTypemy( HUNITPOOL whichPool , int unitId )
{
	fprintf_s( logfile , "%s\n" , "UnitPoolRemoveUnitTypemy" );
	fflush( logfile );

	GAME_UnitPoolRemoveUnitTypeold( whichPool , unitId );
	fprintf_s( logfile , "%s:[-->GAME_UnitPoolRemoveUnitType<--  whichPool: %X unitId: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichPool , unitId );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_UnitRemoveAbility )( HUNIT whichUnit , int abilityId );
GAME_UnitRemoveAbility GAME_UnitRemoveAbilityorg = NULL;
GAME_UnitRemoveAbility GAME_UnitRemoveAbilityold = NULL;

BOOL __cdecl GAME_UnitRemoveAbilitymy( HUNIT whichUnit , int abilityId )
{
	fprintf_s( logfile , "%s\n" , "UnitRemoveAbilitymy" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitRemoveAbilityold( whichUnit , abilityId );
	fprintf_s( logfile , "%s:[-->GAME_UnitRemoveAbility<--  whichUnit: %X abilityId: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , abilityId , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_UnitRemoveBuffs )( HUNIT whichUnit , BOOL removePositive , BOOL removeNegative );
GAME_UnitRemoveBuffs GAME_UnitRemoveBuffsorg = NULL;
GAME_UnitRemoveBuffs GAME_UnitRemoveBuffsold = NULL;

void __cdecl GAME_UnitRemoveBuffsmy( HUNIT whichUnit , BOOL removePositive , BOOL removeNegative )
{
	fprintf_s( logfile , "%s" , "UnitRemoveBuffsmy\n" );
	fflush( logfile );

	GAME_UnitRemoveBuffsold( whichUnit , removePositive , removeNegative );
	fprintf_s( logfile , "%s:[-->GAME_UnitRemoveBuffs<--  whichUnit: %X removePositive: %s removeNegative: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , removePositive ? "TRUE\n" : "FALSE" , removeNegative ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_UnitRemoveBuffsEx )( HUNIT whichUnit , BOOL removePositive , BOOL removeNegative , BOOL magic , BOOL physical , BOOL timedLife , BOOL aura , BOOL autoDispel );
GAME_UnitRemoveBuffsEx GAME_UnitRemoveBuffsExorg = NULL;
GAME_UnitRemoveBuffsEx GAME_UnitRemoveBuffsExold = NULL;

void __cdecl GAME_UnitRemoveBuffsExmy( HUNIT whichUnit , BOOL removePositive , BOOL removeNegative , BOOL magic , BOOL physical , BOOL timedLife , BOOL aura , BOOL autoDispel )
{
	fprintf_s( logfile , "%s" , "UnitRemoveBuffsExmy\n" );
	fflush( logfile );

	GAME_UnitRemoveBuffsExold( whichUnit , removePositive , removeNegative , magic , physical , timedLife , aura , autoDispel );
	fprintf_s( logfile , "%s:[-->GAME_UnitRemoveBuffsEx<--  whichUnit: %X removePositive: %s removeNegative: %s magic: %s physical: %s timedLife: %s aura: %s autoDispel: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , removePositive ? "TRUE\n" : "FALSE" , removeNegative ? "TRUE" : "FALSE" , magic ? "TRUE" : "FALSE" , physical ? "TRUE" : "FALSE" , timedLife ? "TRUE" : "FALSE" , aura ? "TRUE" : "FALSE" , autoDispel ? "TRUE" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_UnitRemoveItem )( HUNIT whichUnit , HITEM whichItem );
GAME_UnitRemoveItem GAME_UnitRemoveItemorg = NULL;
GAME_UnitRemoveItem GAME_UnitRemoveItemold = NULL;

void __cdecl GAME_UnitRemoveItemmy( HUNIT whichUnit , HITEM whichItem )
{
	fprintf_s( logfile , "%s" , "UnitRemoveItemmy\n" );
	fflush( logfile );

	GAME_UnitRemoveItemold( whichUnit , whichItem );
	fprintf_s( logfile , "%s:[-->GAME_UnitRemoveItem<--  whichUnit: %X whichItem: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , whichItem );
	fflush( logfile );

}


typedef HITEM( __cdecl *GAME_UnitRemoveItemFromSlot )( HUNIT whichUnit , int itemSlot );
GAME_UnitRemoveItemFromSlot GAME_UnitRemoveItemFromSlotorg = NULL;
GAME_UnitRemoveItemFromSlot GAME_UnitRemoveItemFromSlotold = NULL;

HITEM __cdecl GAME_UnitRemoveItemFromSlotmy( HUNIT whichUnit , int itemSlot )
{
	fprintf_s( logfile , "%s\n" , "UnitRemoveItemFromSlotmy" );
	fflush( logfile );

	HITEM retvalue = GAME_UnitRemoveItemFromSlotold( whichUnit , itemSlot );
	fprintf_s( logfile , "%s:[-->GAME_UnitRemoveItemFromSlot<--  whichUnit: %X itemSlot: %i] RETURN-> %X\n" , currentDateTime( ).c_str( ) , whichUnit , itemSlot , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitRemoveType )( HUNIT whichUnit , HUNITTYPE whichUnitType );
GAME_UnitRemoveType GAME_UnitRemoveTypeorg = NULL;
GAME_UnitRemoveType GAME_UnitRemoveTypeold = NULL;

BOOL __cdecl GAME_UnitRemoveTypemy( HUNIT whichUnit , HUNITTYPE whichUnitType )
{
	fprintf_s( logfile , "%s\n" , "UnitRemoveTypemy" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitRemoveTypeold( whichUnit , whichUnitType );
	fprintf_s( logfile , "%s:[-->GAME_UnitRemoveType<--  whichUnit: %X whichUnitType: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichUnitType , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_UnitResetCooldown )( HUNIT whichUnit );
GAME_UnitResetCooldown GAME_UnitResetCooldownorg = NULL;
GAME_UnitResetCooldown GAME_UnitResetCooldownold = NULL;

void __cdecl GAME_UnitResetCooldownmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s" , "UnitResetCooldownmy\n" );
	fflush( logfile );

	GAME_UnitResetCooldownold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_UnitResetCooldown<--  whichUnit: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit );
	fflush( logfile );

}


typedef void( __cdecl *GAME_UnitSetConstructionProgress )( HUNIT whichUnit , int constructionPercentage );
GAME_UnitSetConstructionProgress GAME_UnitSetConstructionProgressorg = NULL;
GAME_UnitSetConstructionProgress GAME_UnitSetConstructionProgressold = NULL;

void __cdecl GAME_UnitSetConstructionProgressmy( HUNIT whichUnit , int constructionPercentage )
{
	fprintf_s( logfile , "%s\n" , "UnitSetConstructionProgressmy" );
	fflush( logfile );

	GAME_UnitSetConstructionProgressold( whichUnit , constructionPercentage );
	fprintf_s( logfile , "%s:[-->GAME_UnitSetConstructionProgress<--  whichUnit: %X constructionPercentage: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , constructionPercentage );
	fflush( logfile );

}


typedef void( __cdecl *GAME_UnitSetUpgradeProgress )( HUNIT whichUnit , int upgradePercentage );
GAME_UnitSetUpgradeProgress GAME_UnitSetUpgradeProgressorg = NULL;
GAME_UnitSetUpgradeProgress GAME_UnitSetUpgradeProgressold = NULL;

void __cdecl GAME_UnitSetUpgradeProgressmy( HUNIT whichUnit , int upgradePercentage )
{
	fprintf_s( logfile , "%s\n" , "UnitSetUpgradeProgressmy" );
	fflush( logfile );

	GAME_UnitSetUpgradeProgressold( whichUnit , upgradePercentage );
	fprintf_s( logfile , "%s:[-->GAME_UnitSetUpgradeProgress<--  whichUnit: %X upgradePercentage: %i] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , upgradePercentage );
	fflush( logfile );

}


typedef void( __cdecl *GAME_UnitSetUsesAltIcon )( HUNIT whichUnit , BOOL flag );
GAME_UnitSetUsesAltIcon GAME_UnitSetUsesAltIconorg = NULL;
GAME_UnitSetUsesAltIcon GAME_UnitSetUsesAltIconold = NULL;

void __cdecl GAME_UnitSetUsesAltIconmy( HUNIT whichUnit , BOOL flag )
{
	fprintf_s( logfile , "%s\n" , "UnitSetUsesAltIconmy" );
	fflush( logfile );

	GAME_UnitSetUsesAltIconold( whichUnit , flag );
	fprintf_s( logfile , "%s:[-->GAME_UnitSetUsesAltIcon<--  whichUnit: %X flag: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , flag ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef void( __cdecl *GAME_UnitShareVision )( HUNIT whichUnit , HPLAYER whichPlayer , BOOL share );
GAME_UnitShareVision GAME_UnitShareVisionorg = NULL;
GAME_UnitShareVision GAME_UnitShareVisionold = NULL;

void __cdecl GAME_UnitShareVisionmy( HUNIT whichUnit , HPLAYER whichPlayer , BOOL share )
{
	fprintf_s( logfile , "%s" , "UnitShareVisionmy\n" );
	fflush( logfile );

	GAME_UnitShareVisionold( whichUnit , whichPlayer , share );
	fprintf_s( logfile , "%s:[-->GAME_UnitShareVision<--  whichUnit: %X whichPlayer: %X share: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , whichPlayer , share ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_UnitStripHeroLevel )( HUNIT whichHero , int howManyLevels );
GAME_UnitStripHeroLevel GAME_UnitStripHeroLevelorg = NULL;
GAME_UnitStripHeroLevel GAME_UnitStripHeroLevelold = NULL;

BOOL __cdecl GAME_UnitStripHeroLevelmy( HUNIT whichHero , int howManyLevels )
{
	fprintf_s( logfile , "%s" , "UnitStripHeroLevelmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitStripHeroLevelold( whichHero , howManyLevels );
	fprintf_s( logfile , "%s:[-->GAME_UnitStripHeroLevel<--  whichHero: %X howManyLevels: %i] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichHero , howManyLevels , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_UnitSuspendDecay )( HUNIT whichUnit , BOOL suspend );
GAME_UnitSuspendDecay GAME_UnitSuspendDecayorg = NULL;
GAME_UnitSuspendDecay GAME_UnitSuspendDecayold = NULL;

void __cdecl GAME_UnitSuspendDecaymy( HUNIT whichUnit , BOOL suspend )
{
	fprintf_s( logfile , "%s" , "UnitSuspendDecaymy\n" );
	fflush( logfile );

	GAME_UnitSuspendDecayold( whichUnit , suspend );
	fprintf_s( logfile , "%s:[-->GAME_UnitSuspendDecay<--  whichUnit: %X suspend: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit , suspend ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_UnitUseItem )( HUNIT whichUnit , HITEM whichItem );
GAME_UnitUseItem GAME_UnitUseItemorg = NULL;
GAME_UnitUseItem GAME_UnitUseItemold = NULL;

BOOL __cdecl GAME_UnitUseItemmy( HUNIT whichUnit , HITEM whichItem )
{
	fprintf_s( logfile , "%s" , "UnitUseItemmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitUseItemold( whichUnit , whichItem );
	fprintf_s( logfile , "%s:[-->GAME_UnitUseItem<--  whichUnit: %X whichItem: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichItem , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitUseItemPoint )( HUNIT whichUnit , HITEM whichItem , float *x , float *y );
GAME_UnitUseItemPoint GAME_UnitUseItemPointorg = NULL;
GAME_UnitUseItemPoint GAME_UnitUseItemPointold = NULL;

BOOL __cdecl GAME_UnitUseItemPointmy( HUNIT whichUnit , HITEM whichItem , float *x , float *y )
{
	fprintf_s( logfile , "%s" , "UnitUseItemPointmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitUseItemPointold( whichUnit , whichItem , x , y );
	fprintf_s( logfile , "%s:[-->GAME_UnitUseItemPoint<--  whichUnit: %X whichItem: %X x: %f y: %f] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichItem , *( float * ) x , *( float * ) y , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_UnitUseItemTarget )( HUNIT whichUnit , HITEM whichItem , HWIDGET target );
GAME_UnitUseItemTarget GAME_UnitUseItemTargetorg = NULL;
GAME_UnitUseItemTarget GAME_UnitUseItemTargetold = NULL;

BOOL __cdecl GAME_UnitUseItemTargetmy( HUNIT whichUnit , HITEM whichItem , HWIDGET target )
{
	fprintf_s( logfile , "%s" , "UnitUseItemTargetmy\n" );
	fflush( logfile );

	BOOL retvalue = GAME_UnitUseItemTargetold( whichUnit , whichItem , target );
	fprintf_s( logfile , "%s:[-->GAME_UnitUseItemTarget<--  whichUnit: %X whichItem: %X target: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichUnit , whichItem , target , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_UnitWakeUp )( HUNIT whichUnit );
GAME_UnitWakeUp GAME_UnitWakeUporg = NULL;
GAME_UnitWakeUp GAME_UnitWakeUpold = NULL;

void __cdecl GAME_UnitWakeUpmy( HUNIT whichUnit )
{
	fprintf_s( logfile , "%s" , "UnitWakeUpmy\n" );
	fflush( logfile );

	GAME_UnitWakeUpold( whichUnit );
	fprintf_s( logfile , "%s:[-->GAME_UnitWakeUp<--  whichUnit: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , whichUnit );
	fflush( logfile );

}


typedef void( __cdecl *GAME_UnregisterStackedSound )( HSOUND soundHandle , BOOL byPosition , float *rectwidth , float *rectheight );
GAME_UnregisterStackedSound GAME_UnregisterStackedSoundorg = NULL;
GAME_UnregisterStackedSound GAME_UnregisterStackedSoundold = NULL;

void __cdecl GAME_UnregisterStackedSoundmy( HSOUND soundHandle , BOOL byPosition , float *rectwidth , float *rectheight )
{
	fprintf_s( logfile , "%s\n" , "UnregisterStackedSoundmy" );
	fflush( logfile );

	GAME_UnregisterStackedSoundold( soundHandle , byPosition , rectwidth , rectheight );
	fprintf_s( logfile , "%s:[-->GAME_UnregisterStackedSound<--  soundHandle: %X byPosition: %s rectwidth: %f rectheight: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , soundHandle , byPosition ? "TRUE\n" : "FALSE" , *( float * ) rectwidth , *( float * ) rectheight );
	fflush( logfile );

}


typedef void( __cdecl *GAME_Unsummon )( HUNIT arg1 );
GAME_Unsummon GAME_Unsummonorg = NULL;
GAME_Unsummon GAME_Unsummonold = NULL;

void __cdecl GAME_Unsummonmy( HUNIT arg1 )
{
	fprintf_s( logfile , "%s" , "Unsummonmy\n" );
	fflush( logfile );

	GAME_Unsummonold( arg1 );
	fprintf_s( logfile , "%s:[-->GAME_Unsummon<--  arg1: %X] RETURN-> NO\n" , currentDateTime( ).c_str( ) , arg1 );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_VersionCompatible )( HVERSION whichVersion );
GAME_VersionCompatible GAME_VersionCompatibleorg = NULL;
GAME_VersionCompatible GAME_VersionCompatibleold = NULL;

BOOL __cdecl GAME_VersionCompatiblemy( HVERSION whichVersion )
{
	fprintf_s( logfile , "%s\n" , "VersionCompatiblemy" );
	fflush( logfile );

	BOOL retvalue = GAME_VersionCompatibleold( whichVersion );
	fprintf_s( logfile , "%s:[-->GAME_VersionCompatible<--  whichVersion: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichVersion , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef HVERSION( __cdecl *GAME_VersionGet )( );
GAME_VersionGet GAME_VersionGetorg = NULL;
GAME_VersionGet GAME_VersionGetold = NULL;

HVERSION __cdecl GAME_VersionGetmy( )
{
	fprintf_s( logfile , "%s" , "VersionGetmy\n" );
	fflush( logfile );

	HVERSION retvalue = GAME_VersionGetold( );
	fprintf_s( logfile , "%s:[-->GAME_VersionGet<-- ] RETURN-> %X\n" , currentDateTime( ).c_str( ) , retvalue );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_VersionSupported )( HVERSION whichVersion );
GAME_VersionSupported GAME_VersionSupportedorg = NULL;
GAME_VersionSupported GAME_VersionSupportedold = NULL;

BOOL __cdecl GAME_VersionSupportedmy( HVERSION whichVersion )
{
	fprintf_s( logfile , "%s\n" , "VersionSupportedmy" );
	fflush( logfile );

	BOOL retvalue = GAME_VersionSupportedold( whichVersion );
	fprintf_s( logfile , "%s:[-->GAME_VersionSupported<--  whichVersion: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , whichVersion , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_VolumeGroupReset )( );
GAME_VolumeGroupReset GAME_VolumeGroupResetorg = NULL;
GAME_VolumeGroupReset GAME_VolumeGroupResetold = NULL;

void __cdecl GAME_VolumeGroupResetmy( )
{
	fprintf_s( logfile , "%s" , "VolumeGroupResetmy\n" );
	fflush( logfile );

	GAME_VolumeGroupResetold( );
	fprintf_s( logfile , "%s:[-->GAME_VolumeGroupReset<-- ] RETURN-> NO\n" , currentDateTime( ).c_str( ) );
	fflush( logfile );

}


typedef void( __cdecl *GAME_VolumeGroupSetVolume )( HVOLUMEGROUP vgroup , float *scale );
GAME_VolumeGroupSetVolume GAME_VolumeGroupSetVolumeorg = NULL;
GAME_VolumeGroupSetVolume GAME_VolumeGroupSetVolumeold = NULL;

void __cdecl GAME_VolumeGroupSetVolumemy( HVOLUMEGROUP vgroup , float *scale )
{
	fprintf_s( logfile , "%s\n" , "VolumeGroupSetVolumemy" );
	fflush( logfile );

	GAME_VolumeGroupSetVolumeold( vgroup , scale );
	fprintf_s( logfile , "%s:[-->GAME_VolumeGroupSetVolume<--  vgroup: %X scale: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , vgroup , *( float * ) scale );
	fflush( logfile );

}


typedef BOOL( __cdecl *GAME_WaitGetEnemyBase )( );
GAME_WaitGetEnemyBase GAME_WaitGetEnemyBaseorg = NULL;
GAME_WaitGetEnemyBase GAME_WaitGetEnemyBaseold = NULL;

BOOL __cdecl GAME_WaitGetEnemyBasemy( )
{
	fprintf_s( logfile , "%s\n" , "WaitGetEnemyBasemy" );
	fflush( logfile );

	BOOL retvalue = GAME_WaitGetEnemyBaseold( );
	fprintf_s( logfile , "%s:[-->GAME_WaitGetEnemyBase<-- ] RETURN-> %s\n" , currentDateTime( ).c_str( ) , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_WaygateActivate )( HUNIT waygate , BOOL activate );
GAME_WaygateActivate GAME_WaygateActivateorg = NULL;
GAME_WaygateActivate GAME_WaygateActivateold = NULL;

void __cdecl GAME_WaygateActivatemy( HUNIT waygate , BOOL activate )
{
	fprintf_s( logfile , "%s" , "WaygateActivatemy\n" );
	fflush( logfile );

	GAME_WaygateActivateold( waygate , activate );
	fprintf_s( logfile , "%s:[-->GAME_WaygateActivate<--  waygate: %X activate: %s] RETURN-> NO\n" , currentDateTime( ).c_str( ) , waygate , activate ? "TRUE\n" : "FALSE" );
	fflush( logfile );

}


typedef DWFP( __cdecl *GAME_WaygateGetDestinationX )( HUNIT waygate );
GAME_WaygateGetDestinationX GAME_WaygateGetDestinationXorg = NULL;
GAME_WaygateGetDestinationX GAME_WaygateGetDestinationXold = NULL;

DWFP __cdecl GAME_WaygateGetDestinationXmy( HUNIT waygate )
{
	fprintf_s( logfile , "%s" , "WaygateGetDestinationXmy\n" );
	fflush( logfile );

	DWFP retvalue = GAME_WaygateGetDestinationXold( waygate );
	fprintf_s( logfile , "%s:[-->GAME_WaygateGetDestinationX<--  waygate: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , waygate , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef DWFP( __cdecl *GAME_WaygateGetDestinationY )( HUNIT waygate );
GAME_WaygateGetDestinationY GAME_WaygateGetDestinationYorg = NULL;
GAME_WaygateGetDestinationY GAME_WaygateGetDestinationYold = NULL;

DWFP __cdecl GAME_WaygateGetDestinationYmy( HUNIT waygate )
{
	fprintf_s( logfile , "%s\n" , "WaygateGetDestinationYmy" );
	fflush( logfile );

	DWFP retvalue = GAME_WaygateGetDestinationYold( waygate );
	fprintf_s( logfile , "%s:[-->GAME_WaygateGetDestinationY<--  waygate: %X] RETURN-> %f\n" , currentDateTime( ).c_str( ) , waygate , retvalue.fl );
	fflush( logfile );

	return retvalue;


}

typedef BOOL( __cdecl *GAME_WaygateIsActive )( HUNIT waygate );
GAME_WaygateIsActive GAME_WaygateIsActiveorg = NULL;
GAME_WaygateIsActive GAME_WaygateIsActiveold = NULL;

BOOL __cdecl GAME_WaygateIsActivemy( HUNIT waygate )
{
	fprintf_s( logfile , "%s\n" , "WaygateIsActivemy" );
	fflush( logfile );

	BOOL retvalue = GAME_WaygateIsActiveold( waygate );
	fprintf_s( logfile , "%s:[-->GAME_WaygateIsActive<--  waygate: %X] RETURN-> %s\n" , currentDateTime( ).c_str( ) , waygate , retvalue ? "TRUE\n" : "FALSE" );
	fflush( logfile );

	return retvalue;


}

typedef void( __cdecl *GAME_WaygateSetDestination )( HUNIT waygate , float *x , float *y );
GAME_WaygateSetDestination GAME_WaygateSetDestinationorg = NULL;
GAME_WaygateSetDestination GAME_WaygateSetDestinationold = NULL;

void __cdecl GAME_WaygateSetDestinationmy( HUNIT waygate , float *x , float *y )
{
	fprintf_s( logfile , "%s" , "WaygateSetDestinationmy\n" );
	fflush( logfile );

	GAME_WaygateSetDestinationold( waygate , x , y );
	fprintf_s( logfile , "%s:[-->GAME_WaygateSetDestination<--  waygate: %X x: %f y: %f] RETURN-> NO\n" , currentDateTime( ).c_str( ) , waygate , *( float * ) x , *( float * ) y );
	fflush( logfile );

}





typedef void( __thiscall * Game_SendMessageTimed )( int Inter , const char * text , float time , char unkbyte );
Game_SendMessageTimed SendMessageTimed = NULL;
typedef int( __fastcall * Game_GetInter )( int a1 , int a2 );
Game_GetInter GetInter = NULL;


static DWORD GameDll;

static BOOL gamestart = FALSE;
BOOL IsGame( void )
{
	return *( BOOL* ) ( GameDll + 0xACF678 ) || *( int* ) ( GameDll + 0xAB62A4 ) > 0;
}

static BOOL chatopen = FALSE;
BOOL IsChat( void )
{
	return *( BOOL* ) ( GameDll + 0xAD15F0 );
}
static HANDLE GameF;



DWORD GameFoo( PVOID )
{
restart:
	Sleep( 80 );

	if ( chatopen && !IsChat( ) )
	{
		chatopen = FALSE;
		fprintf_s( logfile , "%s %s\n" , currentDateTime( ).c_str( ) , ": The player closes the game chat." );
		fflush( logfile );

		//logfile << currentDateTime() << ": The player closes the game chat." << endl;

	}
	else if ( !chatopen && IsChat( ) )
	{
		chatopen = TRUE;
		fprintf_s( logfile , "%s %s\n" , currentDateTime( ).c_str( ) , ": The player opens the game chat." );
		fflush( logfile );

		//logfile << currentDateTime() << ": The player opens the game chat." << endl;

	}

	if ( gamestart && !IsGame( ) )
	{
		gamestart = FALSE;
		fprintf_s( logfile , "%s %s\n" , currentDateTime( ).c_str( ) , ": The player leaves the game." );
		fflush( logfile );

		//logfile << currentDateTime() << ": The player leaves the game." << endl;


	}
	else if ( !gamestart && IsGame( ) )
	{
		gamestart = TRUE;
		SendMessageTimed( GetInter( 0 , 0 ) , "|c00FF8000JassSpy|r is activated!" , 5.f , -1 );
		fprintf_s( logfile , "%s %s\n" , currentDateTime( ).c_str( ) , ": The player enters the game." );
		fflush( logfile );

		//logfile << currentDateTime() << ": The player enters the game." << endl;

	}



	goto restart;
	return 0;
}

BOOL APIENTRY DllMain( HINSTANCE hDLL , DWORD reason , LPVOID reserved )
{

	// hDLL is also wc3 instance
	switch ( reason )
	{
		case DLL_PROCESS_ATTACH:
		{
								   GameDll = ( DWORD ) GetModuleHandle( "Game.dll\n" );
								   SendMessageTimed = ( Game_SendMessageTimed ) ( 0x2F69A0 + GameDll );
								   GetInter = ( Game_GetInter ) ( 0x300710 + GameDll );
								   fopen_s( &logfile , "JassSpy.txt" , "a+t" );
								   fprintf_s( logfile , ".......JassSpy for Warcraft 1.26a......" );
								   fflush( logfile );

								   GameF = CreateThread( NULL , NULL , ( LPTHREAD_START_ROUTINE ) GameFoo , NULL , NULL , NULL );

								   MH_Initialize( );
								   InitHack( );

								   break;
		}
		case DLL_PROCESS_DETACH:
		{
								   TerminateThread( GameF , 0 );

								   fclose( logfile );
								   MH_Uninitialize( );
								   break;
		}

	}
	return TRUE;
}
