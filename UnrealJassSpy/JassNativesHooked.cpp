#include <Windows.h>
#include <time.h>
#include <sstream>
#include <string>
#include "JassNativesHeader.h"
using namespace std;
static int GameDll = (int) GetModuleHandle( "Game.dll");
FILE * logfile;
char * funcname1 = "NULLNAME";
char * funcname2 = "NULLNAME";
void SpyJassLog( const char * format , ... )
{
	/*char buffer[ 256 ]; va_list args; va_start( args , format );
	vsprintf_s( buffer , 256 , format , args ); va_end( args );
	int lentowrite = strlen( buffer );
	fwrite( &buffer , lentowrite , 1 , logfile ); fflush( logfile );*/
	va_list args;
 va_start( args , format );
 vfprintf_s( logfile , format , args );
 va_end( args );
 /*fflush( logfile );*/
}
string GetStrID( int id )
{
    char buff[ 7 ];
    char buff2[ 4 ];
    CopyMemory( buff2 , &id , 4 );
    buff[ 0 ] = '\'';
    buff[ 1 ] = buff2[ 3 ];
    buff[ 2 ] = buff2[ 2 ];
	   buff[ 3 ] = buff2[ 1 ];
    buff[ 4 ] = buff2[ 0 ];
    buff[ 5 ] = '\'';
    buff[ 6 ] = '\0';
    bool needreturnid = true;
    for ( int i = 1; i < 5; i++ )
    {
        if ( !isalnum( buff[ i ] ) )
        {
            needreturnid = false;
            break;
        }
    }
    if ( needreturnid )
      return string( buff );
    return to_string( id );
}
const char * BoolToStr( BOOL boolean )
{
    return boolean ? "true" : "false";
}
float GetFloatFromDWFP( DWFP val )
{
    return val.fl;
}
char * ReadJassStringNormal( int JASSSTRING )
{
    if ( JASSSTRING == NULL || JASSSTRING >= INT_MAX ) { return " "; }
    int offset1 = *( int* ) ( ( int ) JASSSTRING + 8 );
    if ( offset1 == NULL || offset1 >= INT_MAX ) { return " "; }
    int offset2 = *( int * ) ( ( *( int* ) ( ( int ) JASSSTRING + 8 ) ) + 0x1C );
    if ( offset2 == NULL || offset2 >= INT_MAX ) { return " "; }
    return *( char ** ) ( ( *( int* ) ( ( int ) JASSSTRING + 8 ) ) + 0x1C );
}
char * ReadJassSID( int JSID )
{
	int Convert = GameDll + 0x7EDA90; int GetCurrentJassEnvironment = GameDll + 0x7E0400;
	char * cRet = NULL;
	__asm
	{
		push JSID;
		mov ecx, 1;
		call GetCurrentJassEnvironment;
		mov ecx, eax;
		call Convert;
		mov ecx, dword ptr ds : [eax + 0x08];
		mov eax, dword ptr ds : [ecx + 0x1C];
		mov cRet, eax;
	}
	return cRet;
}
string GetUnitHID( int unitid )
{
   if ( unitid == 0 ) return "null";
        stringstream s; s << unitid; s << "(" << GetStrID( GetUnitTypeId_ptr(unitid) ) << ")";
    return s.str( );
}
string GetItemHID( int itemid )
{
   if ( itemid == 0 ) return "null";
        stringstream s; s << itemid; s << "(" << GetStrID( GetItemTypeId_ptr( itemid ) ) << ")";
    return s.str( );
}
int _cdecl AbilityId_my(CJassString abilityIdString)
{
   funcname1 = "AbilityId";
   SpyJassLog(" Exec:AbilityId[abilityIdString:%s]...",ReadJassStringNormal(abilityIdString));
   int returnvalue; 
   returnvalue = AbilityId_ptr(abilityIdString);
   SpyJassLog("[AbilityId] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
CJassStringSID _cdecl AbilityId2String_my(int AbilID)
{
   funcname1 = "AbilityId2String";
   SpyJassLog(" Exec:AbilityId2String[AbilID:%s]...",GetStrID(AbilID).c_str( ));
   CJassStringSID returnvalue; 
   returnvalue = AbilityId2String_ptr(AbilID);
   SpyJassLog("[AbilityId2String] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
DWFP _cdecl Acos_my(float *x)
{
   funcname1 = "Acos";
   SpyJassLog(" Exec:Acos[x:%.4g]...",(*x));
   DWFP returnvalue; 
   returnvalue = Acos_ptr(x);
   SpyJassLog("[Acos] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
BOOL _cdecl AddAssault_my(int arg1, int arg2)
{
   funcname1 = "AddAssault";
   SpyJassLog(" Exec:AddAssault[arg1:%s, arg2:%s]...",GetStrID(arg1).c_str( ), GetStrID(arg2).c_str( ));
   BOOL returnvalue; 
   returnvalue = AddAssault_ptr(arg1, arg2);
   SpyJassLog("[AddAssault] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl AddDefenders_my(int arg1, int arg2)
{
   funcname1 = "AddDefenders";
   SpyJassLog(" Exec:AddDefenders[arg1:%s, arg2:%s]...",GetStrID(arg1).c_str( ), GetStrID(arg2).c_str( ));
   BOOL returnvalue; 
   returnvalue = AddDefenders_ptr(arg1, arg2);
   SpyJassLog("[AddDefenders] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl AddGuardPost_my(int arg1, float *arg2, float *arg3)
{
   funcname1 = "AddGuardPost";
   SpyJassLog(" Exec:AddGuardPost...");
   AddGuardPost_ptr(arg1, arg2, arg3);
   SpyJassLog("[AddGuardPost] OK [arg1:%s, arg2:%.4g, arg3:%.4g]\n",GetStrID(arg1).c_str( ), (*arg2), (*arg3));
}
void _cdecl AddHeroXP_my(HUNIT hero, int xpToAdd, BOOL showEyeCandy)
{
   funcname1 = "AddHeroXP";
   SpyJassLog(" Exec:AddHeroXP...");
   AddHeroXP_ptr(hero, xpToAdd, showEyeCandy);
   SpyJassLog("[AddHeroXP] OK [hero:%s, xpToAdd:%s, showEyeCandy:%s]\n",GetUnitHID(hero).c_str( ), GetStrID(xpToAdd).c_str( ), BoolToStr(showEyeCandy));
}
void _cdecl AddIndicator_my(HWIDGET widget, int red, int green, int blue, int alpha)
{
   funcname1 = "AddIndicator";
   SpyJassLog(" Exec:AddIndicator...");
   AddIndicator_ptr(widget, red, green, blue, alpha);
   SpyJassLog("[AddIndicator] OK [widget:%s, red:%s, green:%s, blue:%s, alpha:%s]\n",GetStrID(widget).c_str( ), GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), GetStrID(alpha).c_str( ));
}
void _cdecl AddItemToAllStock_my(int itemId, int currentStock, int stockMax)
{
   funcname1 = "AddItemToAllStock";
   SpyJassLog(" Exec:AddItemToAllStock...");
   AddItemToAllStock_ptr(itemId, currentStock, stockMax);
   SpyJassLog("[AddItemToAllStock] OK [itemId:%s, currentStock:%s, stockMax:%s]\n",GetStrID(itemId).c_str( ), GetStrID(currentStock).c_str( ), GetStrID(stockMax).c_str( ));
}
void _cdecl AddItemToStock_my(HUNIT unit, int itemId, int currentStock, int stockMax)
{
   funcname1 = "AddItemToStock";
   SpyJassLog(" Exec:AddItemToStock...");
   AddItemToStock_ptr(unit, itemId, currentStock, stockMax);
   SpyJassLog("[AddItemToStock] OK [unit:%s, itemId:%s, currentStock:%s, stockMax:%s]\n",GetUnitHID(unit).c_str( ), GetStrID(itemId).c_str( ), GetStrID(currentStock).c_str( ), GetStrID(stockMax).c_str( ));
}
HLIGHTNING _cdecl AddLightning_my(CJassString codeName, BOOL checkVisibility, float *x1, float *y1, float *x2, float *y2)
{
   funcname1 = "AddLightning";
   SpyJassLog(" Exec:AddLightning[codeName:%s, checkVisibility:%s, x1:%.4g, y1:%.4g, x2:%.4g, y2:%.4g]...",ReadJassStringNormal(codeName), BoolToStr(checkVisibility), (*x1), (*y1), (*x2), (*y2));
   HLIGHTNING returnvalue; 
   returnvalue = AddLightning_ptr(codeName, checkVisibility, x1, y1, x2, y2);
   SpyJassLog("[AddLightning] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HLIGHTNING _cdecl AddLightningEx_my(CJassString codeName, BOOL checkVisibility, float *x1, float *y1, float *z1, float *x2, float *y2, float *z2)
{
   funcname1 = "AddLightningEx";
   SpyJassLog(" Exec:AddLightningEx[codeName:%s, checkVisibility:%s, x1:%.4g, y1:%.4g, z1:%.4g, x2:%.4g, y2:%.4g, z2:%.4g]...",ReadJassStringNormal(codeName), BoolToStr(checkVisibility), (*x1), (*y1), (*z1), (*x2), (*y2), (*z2));
   HLIGHTNING returnvalue; 
   returnvalue = AddLightningEx_ptr(codeName, checkVisibility, x1, y1, z1, x2, y2, z2);
   SpyJassLog("[AddLightningEx] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl AddPlayerTechResearched_my(HPLAYER player, int techid, int levels)
{
   funcname1 = "AddPlayerTechResearched";
   SpyJassLog(" Exec:AddPlayerTechResearched...");
   AddPlayerTechResearched_ptr(player, techid, levels);
   SpyJassLog("[AddPlayerTechResearched] OK [player:%i, techid:%s, levels:%s]\n",GetPlayerId_ptr(player), GetStrID(techid).c_str( ), GetStrID(levels).c_str( ));
}
void _cdecl AddResourceAmount_my(HUNIT unit, int amount)
{
   funcname1 = "AddResourceAmount";
   SpyJassLog(" Exec:AddResourceAmount...");
   AddResourceAmount_ptr(unit, amount);
   SpyJassLog("[AddResourceAmount] OK [unit:%s, amount:%s]\n",GetUnitHID(unit).c_str( ), GetStrID(amount).c_str( ));
}
HEFFECT _cdecl AddSpecialEffect_my(CJassString modelName, float *x, float *y)
{
   funcname1 = "AddSpecialEffect";
   SpyJassLog(" Exec:AddSpecialEffect[modelName:%s, x:%.4g, y:%.4g]...",ReadJassStringNormal(modelName), (*x), (*y));
   HEFFECT returnvalue; 
   returnvalue = AddSpecialEffect_ptr(modelName, x, y);
   SpyJassLog("[AddSpecialEffect] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEFFECT _cdecl AddSpecialEffectLoc_my(CJassString modelName, HLOCATION where)
{
   funcname1 = "AddSpecialEffectLoc";
   SpyJassLog(" Exec:AddSpecialEffectLoc[modelName:%s, where:%s]...",ReadJassStringNormal(modelName), GetStrID(where).c_str( ));
   HEFFECT returnvalue; 
   returnvalue = AddSpecialEffectLoc_ptr(modelName, where);
   SpyJassLog("[AddSpecialEffectLoc] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEFFECT _cdecl AddSpecialEffectTarget_my(CJassString modelName, HWIDGET targetWidget, CJassString attachPointName)
{
   funcname1 = "AddSpecialEffectTarget";
   SpyJassLog(" Exec:AddSpecialEffectTarget[modelName:%s, targetWidget:%s, attachPointName:%s]...",ReadJassStringNormal(modelName), GetStrID(targetWidget).c_str( ), ReadJassStringNormal(attachPointName));
   HEFFECT returnvalue; 
   returnvalue = AddSpecialEffectTarget_ptr(modelName, targetWidget, attachPointName);
   SpyJassLog("[AddSpecialEffectTarget] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEFFECT _cdecl AddSpellEffect_my(CJassString abilityString, HEFFECTTYPE t, float *x, float *y)
{
   funcname1 = "AddSpellEffect";
   SpyJassLog(" Exec:AddSpellEffect[abilityString:%s, t:%s, x:%.4g, y:%.4g]...",ReadJassStringNormal(abilityString), GetStrID(t).c_str( ), (*x), (*y));
   HEFFECT returnvalue; 
   returnvalue = AddSpellEffect_ptr(abilityString, t, x, y);
   SpyJassLog("[AddSpellEffect] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEFFECT _cdecl AddSpellEffectById_my(int AbilID, HEFFECTTYPE t, float *x, float *y)
{
   funcname1 = "AddSpellEffectById";
   SpyJassLog(" Exec:AddSpellEffectById[AbilID:%s, t:%s, x:%.4g, y:%.4g]...",GetStrID(AbilID).c_str( ), GetStrID(t).c_str( ), (*x), (*y));
   HEFFECT returnvalue; 
   returnvalue = AddSpellEffectById_ptr(AbilID, t, x, y);
   SpyJassLog("[AddSpellEffectById] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEFFECT _cdecl AddSpellEffectByIdLoc_my(int AbilID, HEFFECTTYPE t, HLOCATION where)
{
   funcname1 = "AddSpellEffectByIdLoc";
   SpyJassLog(" Exec:AddSpellEffectByIdLoc[AbilID:%s, t:%s, where:%s]...",GetStrID(AbilID).c_str( ), GetStrID(t).c_str( ), GetStrID(where).c_str( ));
   HEFFECT returnvalue; 
   returnvalue = AddSpellEffectByIdLoc_ptr(AbilID, t, where);
   SpyJassLog("[AddSpellEffectByIdLoc] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEFFECT _cdecl AddSpellEffectLoc_my(CJassString abilityString, HEFFECTTYPE t, HLOCATION where)
{
   funcname1 = "AddSpellEffectLoc";
   SpyJassLog(" Exec:AddSpellEffectLoc[abilityString:%s, t:%s, where:%s]...",ReadJassStringNormal(abilityString), GetStrID(t).c_str( ), GetStrID(where).c_str( ));
   HEFFECT returnvalue; 
   returnvalue = AddSpellEffectLoc_ptr(abilityString, t, where);
   SpyJassLog("[AddSpellEffectLoc] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEFFECT _cdecl AddSpellEffectTarget_my(CJassString modelName, HEFFECTTYPE t, HWIDGET targetWidget, CJassString attachPoint)
{
   funcname1 = "AddSpellEffectTarget";
   SpyJassLog(" Exec:AddSpellEffectTarget[modelName:%s, t:%s, targetWidget:%s, attachPoint:%s]...",ReadJassStringNormal(modelName), GetStrID(t).c_str( ), GetStrID(targetWidget).c_str( ), ReadJassStringNormal(attachPoint));
   HEFFECT returnvalue; 
   returnvalue = AddSpellEffectTarget_ptr(modelName, t, targetWidget, attachPoint);
   SpyJassLog("[AddSpellEffectTarget] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEFFECT _cdecl AddSpellEffectTargetById_my(int AbilID, HEFFECTTYPE t, HWIDGET targetWidget, CJassString attachPoint)
{
   funcname1 = "AddSpellEffectTargetById";
   SpyJassLog(" Exec:AddSpellEffectTargetById[AbilID:%s, t:%s, targetWidget:%s, attachPoint:%s]...",GetStrID(AbilID).c_str( ), GetStrID(t).c_str( ), GetStrID(targetWidget).c_str( ), ReadJassStringNormal(attachPoint));
   HEFFECT returnvalue; 
   returnvalue = AddSpellEffectTargetById_ptr(AbilID, t, targetWidget, attachPoint);
   SpyJassLog("[AddSpellEffectTargetById] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl AddUnitAnimationProperties_my(HUNIT unit, CJassString animProperties, BOOL add)
{
   funcname1 = "AddUnitAnimationProperties";
   SpyJassLog(" Exec:AddUnitAnimationProperties...");
   AddUnitAnimationProperties_ptr(unit, animProperties, add);
   SpyJassLog("[AddUnitAnimationProperties] OK [unit:%s, animProperties:%s, add:%s]\n",GetUnitHID(unit).c_str( ), ReadJassStringNormal(animProperties), BoolToStr(add));
}
void _cdecl AddUnitToAllStock_my(int unitId, int currentStock, int stockMax)
{
   funcname1 = "AddUnitToAllStock";
   SpyJassLog(" Exec:AddUnitToAllStock...");
   AddUnitToAllStock_ptr(unitId, currentStock, stockMax);
   SpyJassLog("[AddUnitToAllStock] OK [unitId:%s, currentStock:%s, stockMax:%s]\n",GetStrID(unitId).c_str( ), GetStrID(currentStock).c_str( ), GetStrID(stockMax).c_str( ));
}
void _cdecl AddUnitToStock_my(HUNIT unit, int unitId, int currentStock, int stockMax)
{
   funcname1 = "AddUnitToStock";
   SpyJassLog(" Exec:AddUnitToStock...");
   AddUnitToStock_ptr(unit, unitId, currentStock, stockMax);
   SpyJassLog("[AddUnitToStock] OK [unit:%s, unitId:%s, currentStock:%s, stockMax:%s]\n",GetUnitHID(unit).c_str( ), GetStrID(unitId).c_str( ), GetStrID(currentStock).c_str( ), GetStrID(stockMax).c_str( ));
}
HWEATHEREFFECT _cdecl AddWeatherEffect_my(HRECT where, int effectID)
{
   funcname1 = "AddWeatherEffect";
   SpyJassLog(" Exec:AddWeatherEffect[where:%s, effectID:%s]...",GetStrID(where).c_str( ), GetStrID(effectID).c_str( ));
   HWEATHEREFFECT returnvalue; 
   returnvalue = AddWeatherEffect_ptr(where, effectID);
   SpyJassLog("[AddWeatherEffect] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl AdjustCameraField_my(HCAMERAFIELD field, float *offset, float *duration)
{
   funcname1 = "AdjustCameraField";
   SpyJassLog(" Exec:AdjustCameraField...");
   AdjustCameraField_ptr(field, offset, duration);
   SpyJassLog("[AdjustCameraField] OK [field:%s, offset:%.4g, duration:%.4g]\n",GetStrID(field).c_str( ), (*offset), (*duration));
}
HBOOLEXPR _cdecl And_my(HBOOLEXPR operandA, HBOOLEXPR operandB)
{
   funcname1 = "And";
   SpyJassLog(" Exec:And[operandA:%s, operandB:%s]...",GetStrID(operandA).c_str( ), GetStrID(operandB).c_str( ));
   HBOOLEXPR returnvalue; 
   returnvalue = And_ptr(operandA, operandB);
   SpyJassLog("[And] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl Asin_my(float *y)
{
   funcname1 = "Asin";
   SpyJassLog(" Exec:Asin[y:%.4g]...",(*y));
   DWFP returnvalue; 
   returnvalue = Asin_ptr(y);
   SpyJassLog("[Asin] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl Atan_my(float *x)
{
   funcname1 = "Atan";
   SpyJassLog(" Exec:Atan[x:%.4g]...",(*x));
   DWFP returnvalue; 
   returnvalue = Atan_ptr(x);
   SpyJassLog("[Atan] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl Atan2_my(float *y, float *x)
{
   funcname1 = "Atan2";
   SpyJassLog(" Exec:Atan2[y:%.4g, x:%.4g]...",(*y), (*x));
   DWFP returnvalue; 
   returnvalue = Atan2_ptr(y, x);
   SpyJassLog("[Atan2] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
void _cdecl AttachSoundToUnit_my(HSOUND soundHandle, HUNIT unit)
{
   funcname1 = "AttachSoundToUnit";
   SpyJassLog(" Exec:AttachSoundToUnit...");
   AttachSoundToUnit_ptr(soundHandle, unit);
   SpyJassLog("[AttachSoundToUnit] OK [soundHandle:%s, unit:%s]\n",GetStrID(soundHandle).c_str( ), GetUnitHID(unit).c_str( ));
}
void _cdecl AttackMoveKill_my(HUNIT arg1)
{
   funcname1 = "AttackMoveKill";
   SpyJassLog(" Exec:AttackMoveKill...");
   AttackMoveKill_ptr(arg1);
   SpyJassLog("[AttackMoveKill] OK [arg1:%s]\n",GetUnitHID(arg1).c_str( ));
}
void _cdecl AttackMoveXY_my(int arg1, int arg2)
{
   funcname1 = "AttackMoveXY";
   SpyJassLog(" Exec:AttackMoveXY...");
   AttackMoveXY_ptr(arg1, arg2);
   SpyJassLog("[AttackMoveXY] OK [arg1:%s, arg2:%s]\n",GetStrID(arg1).c_str( ), GetStrID(arg2).c_str( ));
}
void _cdecl CachePlayerHeroData_my(HPLAYER player)
{
   funcname1 = "CachePlayerHeroData";
   SpyJassLog(" Exec:CachePlayerHeroData...");
   CachePlayerHeroData_ptr(player);
   SpyJassLog("[CachePlayerHeroData] OK [player:%i]\n",GetPlayerId_ptr(player));
}
void _cdecl CameraSetSmoothingFactor_my(float *factor)
{
   funcname1 = "CameraSetSmoothingFactor";
   SpyJassLog(" Exec:CameraSetSmoothingFactor...");
   CameraSetSmoothingFactor_ptr(factor);
   SpyJassLog("[CameraSetSmoothingFactor] OK [factor:%.4g]\n",(*factor));
}
void _cdecl CameraSetSourceNoise_my(float *mag, float *velocity)
{
   funcname1 = "CameraSetSourceNoise";
   SpyJassLog(" Exec:CameraSetSourceNoise...");
   CameraSetSourceNoise_ptr(mag, velocity);
   SpyJassLog("[CameraSetSourceNoise] OK [mag:%.4g, velocity:%.4g]\n",(*mag), (*velocity));
}
void _cdecl CameraSetSourceNoiseEx_my(float *mag, float *velocity, BOOL vertOnly)
{
   funcname1 = "CameraSetSourceNoiseEx";
   SpyJassLog(" Exec:CameraSetSourceNoiseEx...");
   CameraSetSourceNoiseEx_ptr(mag, velocity, vertOnly);
   SpyJassLog("[CameraSetSourceNoiseEx] OK [mag:%.4g, velocity:%.4g, vertOnly:%s]\n",(*mag), (*velocity), BoolToStr(vertOnly));
}
void _cdecl CameraSetTargetNoise_my(float *mag, float *velocity)
{
   funcname1 = "CameraSetTargetNoise";
   SpyJassLog(" Exec:CameraSetTargetNoise...");
   CameraSetTargetNoise_ptr(mag, velocity);
   SpyJassLog("[CameraSetTargetNoise] OK [mag:%.4g, velocity:%.4g]\n",(*mag), (*velocity));
}
void _cdecl CameraSetTargetNoiseEx_my(float *mag, float *velocity, BOOL vertOnly)
{
   funcname1 = "CameraSetTargetNoiseEx";
   SpyJassLog(" Exec:CameraSetTargetNoiseEx...");
   CameraSetTargetNoiseEx_ptr(mag, velocity, vertOnly);
   SpyJassLog("[CameraSetTargetNoiseEx] OK [mag:%.4g, velocity:%.4g, vertOnly:%s]\n",(*mag), (*velocity), BoolToStr(vertOnly));
}
void _cdecl CameraSetupApply_my(HCAMERASETUP Setup, BOOL doPan, BOOL panTimed)
{
   funcname1 = "CameraSetupApply";
   SpyJassLog(" Exec:CameraSetupApply...");
   CameraSetupApply_ptr(Setup, doPan, panTimed);
   SpyJassLog("[CameraSetupApply] OK [Setup:%s, doPan:%s, panTimed:%s]\n",GetStrID(Setup).c_str( ), BoolToStr(doPan), BoolToStr(panTimed));
}
void _cdecl CameraSetupApplyForceDuration_my(HCAMERASETUP Setup, BOOL doPan, float *forceDuration)
{
   funcname1 = "CameraSetupApplyForceDuration";
   SpyJassLog(" Exec:CameraSetupApplyForceDuration...");
   CameraSetupApplyForceDuration_ptr(Setup, doPan, forceDuration);
   SpyJassLog("[CameraSetupApplyForceDuration] OK [Setup:%s, doPan:%s, forceDuration:%.4g]\n",GetStrID(Setup).c_str( ), BoolToStr(doPan), (*forceDuration));
}
void _cdecl CameraSetupApplyForceDurationWithZ_my(HCAMERASETUP Setup, float *zDestOffset, float *forceDuration)
{
   funcname1 = "CameraSetupApplyForceDurationWithZ";
   SpyJassLog(" Exec:CameraSetupApplyForceDurationWithZ...");
   CameraSetupApplyForceDurationWithZ_ptr(Setup, zDestOffset, forceDuration);
   SpyJassLog("[CameraSetupApplyForceDurationWithZ] OK [Setup:%s, zDestOffset:%.4g, forceDuration:%.4g]\n",GetStrID(Setup).c_str( ), (*zDestOffset), (*forceDuration));
}
void _cdecl CameraSetupApplyWithZ_my(HCAMERASETUP Setup, float *zDestOffset)
{
   funcname1 = "CameraSetupApplyWithZ";
   SpyJassLog(" Exec:CameraSetupApplyWithZ...");
   CameraSetupApplyWithZ_ptr(Setup, zDestOffset);
   SpyJassLog("[CameraSetupApplyWithZ] OK [Setup:%s, zDestOffset:%.4g]\n",GetStrID(Setup).c_str( ), (*zDestOffset));
}
HLOCATION _cdecl CameraSetupGetDestPositionLoc_my(HCAMERASETUP Setup)
{
   funcname1 = "CameraSetupGetDestPositionLoc";
   SpyJassLog(" Exec:CameraSetupGetDestPositionLoc[Setup:%s]...",GetStrID(Setup).c_str( ));
   HLOCATION returnvalue; 
   returnvalue = CameraSetupGetDestPositionLoc_ptr(Setup);
   SpyJassLog("[CameraSetupGetDestPositionLoc] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl CameraSetupGetDestPositionX_my(HCAMERASETUP Setup)
{
   funcname1 = "CameraSetupGetDestPositionX";
   SpyJassLog(" Exec:CameraSetupGetDestPositionX[Setup:%s]...",GetStrID(Setup).c_str( ));
   DWFP returnvalue; 
   returnvalue = CameraSetupGetDestPositionX_ptr(Setup);
   SpyJassLog("[CameraSetupGetDestPositionX] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl CameraSetupGetDestPositionY_my(HCAMERASETUP Setup)
{
   funcname1 = "CameraSetupGetDestPositionY";
   SpyJassLog(" Exec:CameraSetupGetDestPositionY[Setup:%s]...",GetStrID(Setup).c_str( ));
   DWFP returnvalue; 
   returnvalue = CameraSetupGetDestPositionY_ptr(Setup);
   SpyJassLog("[CameraSetupGetDestPositionY] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl CameraSetupGetField_my(HCAMERASETUP Setup, HCAMERAFIELD field)
{
   funcname1 = "CameraSetupGetField";
   SpyJassLog(" Exec:CameraSetupGetField[Setup:%s, field:%s]...",GetStrID(Setup).c_str( ), GetStrID(field).c_str( ));
   DWFP returnvalue; 
   returnvalue = CameraSetupGetField_ptr(Setup, field);
   SpyJassLog("[CameraSetupGetField] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
void _cdecl CameraSetupSetDestPosition_my(HCAMERASETUP Setup, float *x, float *y, float *duration)
{
   funcname1 = "CameraSetupSetDestPosition";
   SpyJassLog(" Exec:CameraSetupSetDestPosition...");
   CameraSetupSetDestPosition_ptr(Setup, x, y, duration);
   SpyJassLog("[CameraSetupSetDestPosition] OK [Setup:%s, x:%.4g, y:%.4g, duration:%.4g]\n",GetStrID(Setup).c_str( ), (*x), (*y), (*duration));
}
void _cdecl CameraSetupSetField_my(HCAMERASETUP Setup, HCAMERAFIELD field, float *value, float *duration)
{
   funcname1 = "CameraSetupSetField";
   SpyJassLog(" Exec:CameraSetupSetField...");
   CameraSetupSetField_ptr(Setup, field, value, duration);
   SpyJassLog("[CameraSetupSetField] OK [Setup:%s, field:%s, value:%.4g, duration:%.4g]\n",GetStrID(Setup).c_str( ), GetStrID(field).c_str( ), (*value), (*duration));
}
BOOL _cdecl CaptainAtGoal_my()
{
   funcname1 = "CaptainAtGoal";
   SpyJassLog(" Exec:CaptainAtGoal[]...");
   BOOL returnvalue; 
   returnvalue = CaptainAtGoal_ptr();
   SpyJassLog("[CaptainAtGoal] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl CaptainAttack_my(float *arg1, float *arg2)
{
   funcname1 = "CaptainAttack";
   SpyJassLog(" Exec:CaptainAttack...");
   CaptainAttack_ptr(arg1, arg2);
   SpyJassLog("[CaptainAttack] OK [arg1:%.4g, arg2:%.4g]\n",(*arg1), (*arg2));
}
void _cdecl CaptainGoHome_my()
{
   funcname1 = "CaptainGoHome";
   SpyJassLog(" Exec:CaptainGoHome...");
   CaptainGoHome_ptr();
   SpyJassLog("[CaptainGoHome] OK []\n");
}
int _cdecl CaptainGroupSize_my()
{
   funcname1 = "CaptainGroupSize";
   SpyJassLog(" Exec:CaptainGroupSize[]...");
   int returnvalue; 
   returnvalue = CaptainGroupSize_ptr();
   SpyJassLog("[CaptainGroupSize] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
BOOL _cdecl CaptainInCombat_my(BOOL arg1)
{
   funcname1 = "CaptainInCombat";
   SpyJassLog(" Exec:CaptainInCombat[arg1:%s]...",BoolToStr(arg1));
   BOOL returnvalue; 
   returnvalue = CaptainInCombat_ptr(arg1);
   SpyJassLog("[CaptainInCombat] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl CaptainIsEmpty_my()
{
   funcname1 = "CaptainIsEmpty";
   SpyJassLog(" Exec:CaptainIsEmpty[]...");
   BOOL returnvalue; 
   returnvalue = CaptainIsEmpty_ptr();
   SpyJassLog("[CaptainIsEmpty] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl CaptainIsFull_my()
{
   funcname1 = "CaptainIsFull";
   SpyJassLog(" Exec:CaptainIsFull[]...");
   BOOL returnvalue; 
   returnvalue = CaptainIsFull_ptr();
   SpyJassLog("[CaptainIsFull] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl CaptainIsHome_my()
{
   funcname1 = "CaptainIsHome";
   SpyJassLog(" Exec:CaptainIsHome[]...");
   BOOL returnvalue; 
   returnvalue = CaptainIsHome_ptr();
   SpyJassLog("[CaptainIsHome] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
int _cdecl CaptainReadiness_my()
{
   funcname1 = "CaptainReadiness";
   SpyJassLog(" Exec:CaptainReadiness[]...");
   int returnvalue; 
   returnvalue = CaptainReadiness_ptr();
   SpyJassLog("[CaptainReadiness] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl CaptainReadinessHP_my()
{
   funcname1 = "CaptainReadinessHP";
   SpyJassLog(" Exec:CaptainReadinessHP[]...");
   int returnvalue; 
   returnvalue = CaptainReadinessHP_ptr();
   SpyJassLog("[CaptainReadinessHP] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl CaptainReadinessMa_my()
{
   funcname1 = "CaptainReadinessMa";
   SpyJassLog(" Exec:CaptainReadinessMa[]...");
   int returnvalue; 
   returnvalue = CaptainReadinessMa_ptr();
   SpyJassLog("[CaptainReadinessMa] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
BOOL _cdecl CaptainRetreating_my()
{
   funcname1 = "CaptainRetreating";
   SpyJassLog(" Exec:CaptainRetreating[]...");
   BOOL returnvalue; 
   returnvalue = CaptainRetreating_ptr();
   SpyJassLog("[CaptainRetreating] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl CaptainVsPlayer_my(HPLAYER arg1)
{
   funcname1 = "CaptainVsPlayer";
   SpyJassLog(" Exec:CaptainVsPlayer...");
   CaptainVsPlayer_ptr(arg1);
   SpyJassLog("[CaptainVsPlayer] OK [arg1:%i]\n",GetPlayerId_ptr(arg1));
}
void _cdecl CaptainVsUnits_my(HPLAYER arg1)
{
   funcname1 = "CaptainVsUnits";
   SpyJassLog(" Exec:CaptainVsUnits...");
   CaptainVsUnits_ptr(arg1);
   SpyJassLog("[CaptainVsUnits] OK [arg1:%i]\n",GetPlayerId_ptr(arg1));
}
void _cdecl ChangeLevel_my(CJassString newLevel, BOOL doScoreScreen)
{
   funcname1 = "ChangeLevel";
   SpyJassLog(" Exec:ChangeLevel...");
   ChangeLevel_ptr(newLevel, doScoreScreen);
   SpyJassLog("[ChangeLevel] OK [newLevel:%s, doScoreScreen:%s]\n",ReadJassStringNormal(newLevel), BoolToStr(doScoreScreen));
}
void _cdecl Cheat_my(CJassString cheatStr)
{
   funcname1 = "Cheat";
   SpyJassLog(" Exec:Cheat...");
   Cheat_ptr(cheatStr);
   SpyJassLog("[Cheat] OK [cheatStr:%s]\n",ReadJassStringNormal(cheatStr));
}
int _cdecl ChooseRandomCreep_my(int level)
{
   funcname1 = "ChooseRandomCreep";
   SpyJassLog(" Exec:ChooseRandomCreep[level:%s]...",GetStrID(level).c_str( ));
   int returnvalue; 
   returnvalue = ChooseRandomCreep_ptr(level);
   SpyJassLog("[ChooseRandomCreep] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl ChooseRandomItem_my(int level)
{
   funcname1 = "ChooseRandomItem";
   SpyJassLog(" Exec:ChooseRandomItem[level:%s]...",GetStrID(level).c_str( ));
   int returnvalue; 
   returnvalue = ChooseRandomItem_ptr(level);
   SpyJassLog("[ChooseRandomItem] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl ChooseRandomItemEx_my(HITEMTYPE Type, int level)
{
   funcname1 = "ChooseRandomItemEx";
   SpyJassLog(" Exec:ChooseRandomItemEx[Type:%s, level:%s]...",GetStrID(Type).c_str( ), GetStrID(level).c_str( ));
   int returnvalue; 
   returnvalue = ChooseRandomItemEx_ptr(Type, level);
   SpyJassLog("[ChooseRandomItemEx] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl ChooseRandomNPBuilding_my()
{
   funcname1 = "ChooseRandomNPBuilding";
   SpyJassLog(" Exec:ChooseRandomNPBuilding[]...");
   int returnvalue; 
   returnvalue = ChooseRandomNPBuilding_ptr();
   SpyJassLog("[ChooseRandomNPBuilding] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl ClearCaptainTargets_my()
{
   funcname1 = "ClearCaptainTargets";
   SpyJassLog(" Exec:ClearCaptainTargets...");
   ClearCaptainTargets_ptr();
   SpyJassLog("[ClearCaptainTargets] OK []\n");
}
void _cdecl ClearHarvestAI_my()
{
   funcname1 = "ClearHarvestAI";
   SpyJassLog(" Exec:ClearHarvestAI...");
   ClearHarvestAI_ptr();
   SpyJassLog("[ClearHarvestAI] OK []\n");
}
void _cdecl ClearMapMusic_my()
{
   funcname1 = "ClearMapMusic";
   SpyJassLog(" Exec:ClearMapMusic...");
   ClearMapMusic_ptr();
   SpyJassLog("[ClearMapMusic] OK []\n");
}
void _cdecl ClearSelection_my()
{
   funcname1 = "ClearSelection";
   SpyJassLog(" Exec:ClearSelection...");
   ClearSelection_ptr();
   SpyJassLog("[ClearSelection] OK []\n");
}
void _cdecl ClearStackedSound_my(CJassString arg1, float *arg2, float *arg3)
{
   funcname1 = "ClearStackedSound";
   SpyJassLog(" Exec:ClearStackedSound...");
   ClearStackedSound_ptr(arg1, arg2, arg3);
   SpyJassLog("[ClearStackedSound] OK [arg1:%s, arg2:%.4g, arg3:%.4g]\n",ReadJassStringNormal(arg1), (*arg2), (*arg3));
}
void _cdecl ClearStackedSoundRect_my(CJassString arg1, HRECT arg2)
{
   funcname1 = "ClearStackedSoundRect";
   SpyJassLog(" Exec:ClearStackedSoundRect...");
   ClearStackedSoundRect_ptr(arg1, arg2);
   SpyJassLog("[ClearStackedSoundRect] OK [arg1:%s, arg2:%s]\n",ReadJassStringNormal(arg1), GetStrID(arg2).c_str( ));
}
void _cdecl ClearTextMessages_my()
{
   funcname1 = "ClearTextMessages";
   SpyJassLog(" Exec:ClearTextMessages...");
   ClearTextMessages_ptr();
   SpyJassLog("[ClearTextMessages] OK []\n");
}
void _cdecl CommandAI_my(HPLAYER num, int command, int data)
{
   funcname1 = "CommandAI";
   SpyJassLog(" Exec:CommandAI...");
   CommandAI_ptr(num, command, data);
   SpyJassLog("[CommandAI] OK [num:%i, command:%s, data:%s]\n",GetPlayerId_ptr(num), GetStrID(command).c_str( ), GetStrID(data).c_str( ));
}
int _cdecl CommandsWaiting_my()
{
   funcname1 = "CommandsWaiting";
   SpyJassLog(" Exec:CommandsWaiting[]...");
   int returnvalue; 
   returnvalue = CommandsWaiting_ptr();
   SpyJassLog("[CommandsWaiting] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HCONDITIONFUNC _cdecl Condition_my(CODE func)
{
   funcname1 = "Condition";
   SpyJassLog(" Exec:Condition[func:%s]...",GetStrID(func).c_str( ));
   HCONDITIONFUNC returnvalue; 
   returnvalue = Condition_ptr(func);
   SpyJassLog("[Condition] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HAIDIFFICULTY _cdecl ConvertAIDifficulty_my(int i)
{
   funcname1 = "ConvertAIDifficulty";
   SpyJassLog(" Exec:ConvertAIDifficulty[i:%s]...",GetStrID(i).c_str( ));
   HAIDIFFICULTY returnvalue; 
   returnvalue = ConvertAIDifficulty_ptr(i);
   SpyJassLog("[ConvertAIDifficulty] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HALLIANCETYPE _cdecl ConvertAllianceType_my(int i)
{
   funcname1 = "ConvertAllianceType";
   SpyJassLog(" Exec:ConvertAllianceType[i:%s]...",GetStrID(i).c_str( ));
   HALLIANCETYPE returnvalue; 
   returnvalue = ConvertAllianceType_ptr(i);
   SpyJassLog("[ConvertAllianceType] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HATTACKTYPE _cdecl ConvertAttackType_my(int i)
{
   funcname1 = "ConvertAttackType";
   SpyJassLog(" Exec:ConvertAttackType[i:%s]...",GetStrID(i).c_str( ));
   HATTACKTYPE returnvalue; 
   returnvalue = ConvertAttackType_ptr(i);
   SpyJassLog("[ConvertAttackType] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HBLENDMODE _cdecl ConvertBlendMode_my(int i)
{
   funcname1 = "ConvertBlendMode";
   SpyJassLog(" Exec:ConvertBlendMode[i:%s]...",GetStrID(i).c_str( ));
   HBLENDMODE returnvalue; 
   returnvalue = ConvertBlendMode_ptr(i);
   SpyJassLog("[ConvertBlendMode] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HCAMERAFIELD _cdecl ConvertCameraField_my(int i)
{
   funcname1 = "ConvertCameraField";
   SpyJassLog(" Exec:ConvertCameraField[i:%s]...",GetStrID(i).c_str( ));
   HCAMERAFIELD returnvalue; 
   returnvalue = ConvertCameraField_ptr(i);
   SpyJassLog("[ConvertCameraField] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HDAMAGETYPE _cdecl ConvertDamageType_my(int i)
{
   funcname1 = "ConvertDamageType";
   SpyJassLog(" Exec:ConvertDamageType[i:%s]...",GetStrID(i).c_str( ));
   HDAMAGETYPE returnvalue; 
   returnvalue = ConvertDamageType_ptr(i);
   SpyJassLog("[ConvertDamageType] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HDIALOGEVENT _cdecl ConvertDialogEvent_my(int i)
{
   funcname1 = "ConvertDialogEvent";
   SpyJassLog(" Exec:ConvertDialogEvent[i:%s]...",GetStrID(i).c_str( ));
   HDIALOGEVENT returnvalue; 
   returnvalue = ConvertDialogEvent_ptr(i);
   SpyJassLog("[ConvertDialogEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEFFECTTYPE _cdecl ConvertEffectType_my(int i)
{
   funcname1 = "ConvertEffectType";
   SpyJassLog(" Exec:ConvertEffectType[i:%s]...",GetStrID(i).c_str( ));
   HEFFECTTYPE returnvalue; 
   returnvalue = ConvertEffectType_ptr(i);
   SpyJassLog("[ConvertEffectType] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HFGAMESTATE _cdecl ConvertFGameState_my(int i)
{
   funcname1 = "ConvertFGameState";
   SpyJassLog(" Exec:ConvertFGameState[i:%s]...",GetStrID(i).c_str( ));
   HFGAMESTATE returnvalue; 
   returnvalue = ConvertFGameState_ptr(i);
   SpyJassLog("[ConvertFGameState] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HFOGSTATE _cdecl ConvertFogState_my(int i)
{
   funcname1 = "ConvertFogState";
   SpyJassLog(" Exec:ConvertFogState[i:%s]...",GetStrID(i).c_str( ));
   HFOGSTATE returnvalue; 
   returnvalue = ConvertFogState_ptr(i);
   SpyJassLog("[ConvertFogState] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HGAMEDIFFICULTY _cdecl ConvertGameDifficulty_my(int i)
{
   funcname1 = "ConvertGameDifficulty";
   SpyJassLog(" Exec:ConvertGameDifficulty[i:%s]...",GetStrID(i).c_str( ));
   HGAMEDIFFICULTY returnvalue; 
   returnvalue = ConvertGameDifficulty_ptr(i);
   SpyJassLog("[ConvertGameDifficulty] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HGAMEEVENT _cdecl ConvertGameEvent_my(int i)
{
   funcname1 = "ConvertGameEvent";
   SpyJassLog(" Exec:ConvertGameEvent[i:%s]...",GetStrID(i).c_str( ));
   HGAMEEVENT returnvalue; 
   returnvalue = ConvertGameEvent_ptr(i);
   SpyJassLog("[ConvertGameEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HGAMESPEED _cdecl ConvertGameSpeed_my(int i)
{
   funcname1 = "ConvertGameSpeed";
   SpyJassLog(" Exec:ConvertGameSpeed[i:%s]...",GetStrID(i).c_str( ));
   HGAMESPEED returnvalue; 
   returnvalue = ConvertGameSpeed_ptr(i);
   SpyJassLog("[ConvertGameSpeed] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HGAMETYPE _cdecl ConvertGameType_my(int i)
{
   funcname1 = "ConvertGameType";
   SpyJassLog(" Exec:ConvertGameType[i:%s]...",GetStrID(i).c_str( ));
   HGAMETYPE returnvalue; 
   returnvalue = ConvertGameType_ptr(i);
   SpyJassLog("[ConvertGameType] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HIGAMESTATE _cdecl ConvertIGameState_my(int i)
{
   funcname1 = "ConvertIGameState";
   SpyJassLog(" Exec:ConvertIGameState[i:%s]...",GetStrID(i).c_str( ));
   HIGAMESTATE returnvalue; 
   returnvalue = ConvertIGameState_ptr(i);
   SpyJassLog("[ConvertIGameState] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HITEMTYPE _cdecl ConvertItemType_my(int i)
{
   funcname1 = "ConvertItemType";
   SpyJassLog(" Exec:ConvertItemType[i:%s]...",GetStrID(i).c_str( ));
   HITEMTYPE returnvalue; 
   returnvalue = ConvertItemType_ptr(i);
   SpyJassLog("[ConvertItemType] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HLIMITOP _cdecl ConvertLimitOp_my(int i)
{
   funcname1 = "ConvertLimitOp";
   SpyJassLog(" Exec:ConvertLimitOp[i:%s]...",GetStrID(i).c_str( ));
   HLIMITOP returnvalue; 
   returnvalue = ConvertLimitOp_ptr(i);
   SpyJassLog("[ConvertLimitOp] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HMAPCONTROL _cdecl ConvertMapControl_my(int i)
{
   funcname1 = "ConvertMapControl";
   SpyJassLog(" Exec:ConvertMapControl[i:%s]...",GetStrID(i).c_str( ));
   HMAPCONTROL returnvalue; 
   returnvalue = ConvertMapControl_ptr(i);
   SpyJassLog("[ConvertMapControl] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HMAPDENSITY _cdecl ConvertMapDensity_my(int i)
{
   funcname1 = "ConvertMapDensity";
   SpyJassLog(" Exec:ConvertMapDensity[i:%s]...",GetStrID(i).c_str( ));
   HMAPDENSITY returnvalue; 
   returnvalue = ConvertMapDensity_ptr(i);
   SpyJassLog("[ConvertMapDensity] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HMAPFLAG _cdecl ConvertMapFlag_my(int i)
{
   funcname1 = "ConvertMapFlag";
   SpyJassLog(" Exec:ConvertMapFlag[i:%s]...",GetStrID(i).c_str( ));
   HMAPFLAG returnvalue; 
   returnvalue = ConvertMapFlag_ptr(i);
   SpyJassLog("[ConvertMapFlag] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HMAPSETTING _cdecl ConvertMapSetting_my(int i)
{
   funcname1 = "ConvertMapSetting";
   SpyJassLog(" Exec:ConvertMapSetting[i:%s]...",GetStrID(i).c_str( ));
   HMAPSETTING returnvalue; 
   returnvalue = ConvertMapSetting_ptr(i);
   SpyJassLog("[ConvertMapSetting] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HMAPVISIBILITY _cdecl ConvertMapVisibility_my(int i)
{
   funcname1 = "ConvertMapVisibility";
   SpyJassLog(" Exec:ConvertMapVisibility[i:%s]...",GetStrID(i).c_str( ));
   HMAPVISIBILITY returnvalue; 
   returnvalue = ConvertMapVisibility_ptr(i);
   SpyJassLog("[ConvertMapVisibility] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HPATHINGTYPE _cdecl ConvertPathingType_my(int i)
{
   funcname1 = "ConvertPathingType";
   SpyJassLog(" Exec:ConvertPathingType[i:%s]...",GetStrID(i).c_str( ));
   HPATHINGTYPE returnvalue; 
   returnvalue = ConvertPathingType_ptr(i);
   SpyJassLog("[ConvertPathingType] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HPLACEMENT _cdecl ConvertPlacement_my(int i)
{
   funcname1 = "ConvertPlacement";
   SpyJassLog(" Exec:ConvertPlacement[i:%s]...",GetStrID(i).c_str( ));
   HPLACEMENT returnvalue; 
   returnvalue = ConvertPlacement_ptr(i);
   SpyJassLog("[ConvertPlacement] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HPLAYERCOLOR _cdecl ConvertPlayerColor_my(int i)
{
   funcname1 = "ConvertPlayerColor";
   SpyJassLog(" Exec:ConvertPlayerColor[i:%s]...",GetStrID(i).c_str( ));
   HPLAYERCOLOR returnvalue; 
   returnvalue = ConvertPlayerColor_ptr(i);
   SpyJassLog("[ConvertPlayerColor] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HPLAYEREVENT _cdecl ConvertPlayerEvent_my(int i)
{
   funcname1 = "ConvertPlayerEvent";
   SpyJassLog(" Exec:ConvertPlayerEvent[i:%s]...",GetStrID(i).c_str( ));
   HPLAYEREVENT returnvalue; 
   returnvalue = ConvertPlayerEvent_ptr(i);
   SpyJassLog("[ConvertPlayerEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HPLAYERGAMERESULT _cdecl ConvertPlayerGameResult_my(int i)
{
   funcname1 = "ConvertPlayerGameResult";
   SpyJassLog(" Exec:ConvertPlayerGameResult[i:%s]...",GetStrID(i).c_str( ));
   HPLAYERGAMERESULT returnvalue; 
   returnvalue = ConvertPlayerGameResult_ptr(i);
   SpyJassLog("[ConvertPlayerGameResult] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HPLAYERSCORE _cdecl ConvertPlayerScore_my(int i)
{
   funcname1 = "ConvertPlayerScore";
   SpyJassLog(" Exec:ConvertPlayerScore[i:%s]...",GetStrID(i).c_str( ));
   HPLAYERSCORE returnvalue; 
   returnvalue = ConvertPlayerScore_ptr(i);
   SpyJassLog("[ConvertPlayerScore] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HPLAYERSLOTSTATE _cdecl ConvertPlayerSlotState_my(int i)
{
   funcname1 = "ConvertPlayerSlotState";
   SpyJassLog(" Exec:ConvertPlayerSlotState[i:%s]...",GetStrID(i).c_str( ));
   HPLAYERSLOTSTATE returnvalue; 
   returnvalue = ConvertPlayerSlotState_ptr(i);
   SpyJassLog("[ConvertPlayerSlotState] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HPLAYERSTATE _cdecl ConvertPlayerState_my(int i)
{
   funcname1 = "ConvertPlayerState";
   SpyJassLog(" Exec:ConvertPlayerState[i:%s]...",GetStrID(i).c_str( ));
   HPLAYERSTATE returnvalue; 
   returnvalue = ConvertPlayerState_ptr(i);
   SpyJassLog("[ConvertPlayerState] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HPLAYERUNITEVENT _cdecl ConvertPlayerUnitEvent_my(int i)
{
   funcname1 = "ConvertPlayerUnitEvent";
   SpyJassLog(" Exec:ConvertPlayerUnitEvent[i:%s]...",GetStrID(i).c_str( ));
   HPLAYERUNITEVENT returnvalue; 
   returnvalue = ConvertPlayerUnitEvent_ptr(i);
   SpyJassLog("[ConvertPlayerUnitEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HRACE _cdecl ConvertRace_my(int i)
{
   funcname1 = "ConvertRace";
   SpyJassLog(" Exec:ConvertRace[i:%s]...",GetStrID(i).c_str( ));
   HRACE returnvalue; 
   returnvalue = ConvertRace_ptr(i);
   SpyJassLog("[ConvertRace] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HRACEPREFERENCE _cdecl ConvertRacePref_my(int i)
{
   funcname1 = "ConvertRacePref";
   SpyJassLog(" Exec:ConvertRacePref[i:%s]...",GetStrID(i).c_str( ));
   HRACEPREFERENCE returnvalue; 
   returnvalue = ConvertRacePref_ptr(i);
   SpyJassLog("[ConvertRacePref] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HRARITYCONTROL _cdecl ConvertRarityControl_my(int i)
{
   funcname1 = "ConvertRarityControl";
   SpyJassLog(" Exec:ConvertRarityControl[i:%s]...",GetStrID(i).c_str( ));
   HRARITYCONTROL returnvalue; 
   returnvalue = ConvertRarityControl_ptr(i);
   SpyJassLog("[ConvertRarityControl] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HSOUNDTYPE _cdecl ConvertSoundType_my(int i)
{
   funcname1 = "ConvertSoundType";
   SpyJassLog(" Exec:ConvertSoundType[i:%s]...",GetStrID(i).c_str( ));
   HSOUNDTYPE returnvalue; 
   returnvalue = ConvertSoundType_ptr(i);
   SpyJassLog("[ConvertSoundType] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HSTARTLOCPRIO _cdecl ConvertStartLocPrio_my(int i)
{
   funcname1 = "ConvertStartLocPrio";
   SpyJassLog(" Exec:ConvertStartLocPrio[i:%s]...",GetStrID(i).c_str( ));
   HSTARTLOCPRIO returnvalue; 
   returnvalue = ConvertStartLocPrio_ptr(i);
   SpyJassLog("[ConvertStartLocPrio] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTEXMAPFLAGS _cdecl ConvertTexMapFlags_my(int i)
{
   funcname1 = "ConvertTexMapFlags";
   SpyJassLog(" Exec:ConvertTexMapFlags[i:%s]...",GetStrID(i).c_str( ));
   HTEXMAPFLAGS returnvalue; 
   returnvalue = ConvertTexMapFlags_ptr(i);
   SpyJassLog("[ConvertTexMapFlags] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNITEVENT _cdecl ConvertUnitEvent_my(int i)
{
   funcname1 = "ConvertUnitEvent";
   SpyJassLog(" Exec:ConvertUnitEvent[i:%s]...",GetStrID(i).c_str( ));
   HUNITEVENT returnvalue; 
   returnvalue = ConvertUnitEvent_ptr(i);
   SpyJassLog("[ConvertUnitEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNITSTATE _cdecl ConvertUnitState_my(int i)
{
   funcname1 = "ConvertUnitState";
   SpyJassLog(" Exec:ConvertUnitState[i:%s]...",GetStrID(i).c_str( ));
   HUNITSTATE returnvalue; 
   returnvalue = ConvertUnitState_ptr(i);
   SpyJassLog("[ConvertUnitState] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNITTYPE _cdecl ConvertUnitType_my(int i)
{
   funcname1 = "ConvertUnitType";
   SpyJassLog(" Exec:ConvertUnitType[i:%s]...",GetStrID(i).c_str( ));
   HUNITTYPE returnvalue; 
   returnvalue = ConvertUnitType_ptr(i);
   SpyJassLog("[ConvertUnitType] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
BOOL _cdecl ConvertUnits_my(int arg1, int arg2)
{
   funcname1 = "ConvertUnits";
   SpyJassLog(" Exec:ConvertUnits[arg1:%s, arg2:%s]...",GetStrID(arg1).c_str( ), GetStrID(arg2).c_str( ));
   BOOL returnvalue; 
   returnvalue = ConvertUnits_ptr(arg1, arg2);
   SpyJassLog("[ConvertUnits] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
HVERSION _cdecl ConvertVersion_my(int i)
{
   funcname1 = "ConvertVersion";
   SpyJassLog(" Exec:ConvertVersion[i:%s]...",GetStrID(i).c_str( ));
   HVERSION returnvalue; 
   returnvalue = ConvertVersion_ptr(i);
   SpyJassLog("[ConvertVersion] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HVOLUMEGROUP _cdecl ConvertVolumeGroup_my(int i)
{
   funcname1 = "ConvertVolumeGroup";
   SpyJassLog(" Exec:ConvertVolumeGroup[i:%s]...",GetStrID(i).c_str( ));
   HVOLUMEGROUP returnvalue; 
   returnvalue = ConvertVolumeGroup_ptr(i);
   SpyJassLog("[ConvertVolumeGroup] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HWEAPONTYPE _cdecl ConvertWeaponType_my(int i)
{
   funcname1 = "ConvertWeaponType";
   SpyJassLog(" Exec:ConvertWeaponType[i:%s]...",GetStrID(i).c_str( ));
   HWEAPONTYPE returnvalue; 
   returnvalue = ConvertWeaponType_ptr(i);
   SpyJassLog("[ConvertWeaponType] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HWIDGETEVENT _cdecl ConvertWidgetEvent_my(int i)
{
   funcname1 = "ConvertWidgetEvent";
   SpyJassLog(" Exec:ConvertWidgetEvent[i:%s]...",GetStrID(i).c_str( ));
   HWIDGETEVENT returnvalue; 
   returnvalue = ConvertWidgetEvent_ptr(i);
   SpyJassLog("[ConvertWidgetEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
BOOL _cdecl CopySaveGame_my(CJassString sourceSaveName, CJassString destSaveName)
{
   funcname1 = "CopySaveGame";
   SpyJassLog(" Exec:CopySaveGame[sourceSaveName:%s, destSaveName:%s]...",ReadJassStringNormal(sourceSaveName), ReadJassStringNormal(destSaveName));
   BOOL returnvalue; 
   returnvalue = CopySaveGame_ptr(sourceSaveName, destSaveName);
   SpyJassLog("[CopySaveGame] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
DWFP _cdecl Cos_my(float *radians)
{
   funcname1 = "Cos";
   SpyJassLog(" Exec:Cos[radians:%.4g]...",(*radians));
   DWFP returnvalue; 
   returnvalue = Cos_ptr(radians);
   SpyJassLog("[Cos] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
HUNIT _cdecl CreateBlightedGoldmine_my(HPLAYER id, float *x, float *y, float *face)
{
   funcname1 = "CreateBlightedGoldmine";
   SpyJassLog(" Exec:CreateBlightedGoldmine[id:%i, x:%.4g, y:%.4g, face:%.4g]...",GetPlayerId_ptr(id), (*x), (*y), (*face));
   HUNIT returnvalue; 
   returnvalue = CreateBlightedGoldmine_ptr(id, x, y, face);
   SpyJassLog("[CreateBlightedGoldmine] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HCAMERASETUP _cdecl CreateCameraSetup_my()
{
   funcname1 = "CreateCameraSetup";
   SpyJassLog(" Exec:CreateCameraSetup[]...");
   HCAMERASETUP returnvalue; 
   returnvalue = CreateCameraSetup_ptr();
   SpyJassLog("[CreateCameraSetup] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl CreateCaptains_my()
{
   funcname1 = "CreateCaptains";
   SpyJassLog(" Exec:CreateCaptains...");
   CreateCaptains_ptr();
   SpyJassLog("[CreateCaptains] OK []\n");
}
HUNIT _cdecl CreateCorpse_my(HPLAYER player, int unitid, float *x, float *y, float *face)
{
   funcname1 = "CreateCorpse";
   SpyJassLog(" Exec:CreateCorpse[player:%i, unitid:%s, x:%.4g, y:%.4g, face:%.4g]...",GetPlayerId_ptr(player), GetStrID(unitid).c_str( ), (*x), (*y), (*face));
   HUNIT returnvalue; 
   returnvalue = CreateCorpse_ptr(player, unitid, x, y, face);
   SpyJassLog("[CreateCorpse] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HDESTRUCTABLE _cdecl CreateDeadDestructable_my(int objectid, float *x, float *y, float *face, float *scale, int variation)
{
   funcname1 = "CreateDeadDestructable";
   SpyJassLog(" Exec:CreateDeadDestructable[objectid:%s, x:%.4g, y:%.4g, face:%.4g, scale:%.4g, variation:%s]...",GetStrID(objectid).c_str( ), (*x), (*y), (*face), (*scale), GetStrID(variation).c_str( ));
   HDESTRUCTABLE returnvalue; 
   returnvalue = CreateDeadDestructable_ptr(objectid, x, y, face, scale, variation);
   SpyJassLog("[CreateDeadDestructable] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HDESTRUCTABLE _cdecl CreateDeadDestructableZ_my(int objectid, float *x, float *y, float *z, float *face, float *scale, int variation)
{
   funcname1 = "CreateDeadDestructableZ";
   SpyJassLog(" Exec:CreateDeadDestructableZ[objectid:%s, x:%.4g, y:%.4g, z:%.4g, face:%.4g, scale:%.4g, variation:%s]...",GetStrID(objectid).c_str( ), (*x), (*y), (*z), (*face), (*scale), GetStrID(variation).c_str( ));
   HDESTRUCTABLE returnvalue; 
   returnvalue = CreateDeadDestructableZ_ptr(objectid, x, y, z, face, scale, variation);
   SpyJassLog("[CreateDeadDestructableZ] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HDEFEATCONDITION _cdecl CreateDefeatCondition_my()
{
   funcname1 = "CreateDefeatCondition";
   SpyJassLog(" Exec:CreateDefeatCondition[]...");
   HDEFEATCONDITION returnvalue; 
   returnvalue = CreateDefeatCondition_ptr();
   SpyJassLog("[CreateDefeatCondition] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HDESTRUCTABLE _cdecl CreateDestructable_my(int objectid, float *x, float *y, float *face, float *scale, int variation)
{
   funcname1 = "CreateDestructable";
   SpyJassLog(" Exec:CreateDestructable[objectid:%s, x:%.4g, y:%.4g, face:%.4g, scale:%.4g, variation:%s]...",GetStrID(objectid).c_str( ), (*x), (*y), (*face), (*scale), GetStrID(variation).c_str( ));
   HDESTRUCTABLE returnvalue; 
   returnvalue = CreateDestructable_ptr(objectid, x, y, face, scale, variation);
   SpyJassLog("[CreateDestructable] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HDESTRUCTABLE _cdecl CreateDestructableZ_my(int objectid, float *x, float *y, float *z, float *face, float *scale, int variation)
{
   funcname1 = "CreateDestructableZ";
   SpyJassLog(" Exec:CreateDestructableZ[objectid:%s, x:%.4g, y:%.4g, z:%.4g, face:%.4g, scale:%.4g, variation:%s]...",GetStrID(objectid).c_str( ), (*x), (*y), (*z), (*face), (*scale), GetStrID(variation).c_str( ));
   HDESTRUCTABLE returnvalue; 
   returnvalue = CreateDestructableZ_ptr(objectid, x, y, z, face, scale, variation);
   SpyJassLog("[CreateDestructableZ] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HFOGMODIFIER _cdecl CreateFogModifierRadius_my(HPLAYER forWhichPlayer, HFOGSTATE State, float *centerx, float *centerY, float *radius, BOOL useSharedVision, BOOL afterUnits)
{
   funcname1 = "CreateFogModifierRadius";
   SpyJassLog(" Exec:CreateFogModifierRadius[forWhichPlayer:%i, State:%s, centerx:%.4g, centerY:%.4g, radius:%.4g, useSharedVision:%s, afterUnits:%s]...",GetPlayerId_ptr(forWhichPlayer), GetStrID(State).c_str( ), (*centerx), (*centerY), (*radius), BoolToStr(useSharedVision), BoolToStr(afterUnits));
   HFOGMODIFIER returnvalue; 
   returnvalue = CreateFogModifierRadius_ptr(forWhichPlayer, State, centerx, centerY, radius, useSharedVision, afterUnits);
   SpyJassLog("[CreateFogModifierRadius] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HFOGMODIFIER _cdecl CreateFogModifierRadiusLoc_my(HPLAYER forWhichPlayer, HFOGSTATE State, HLOCATION center, float *radius, BOOL useSharedVision, BOOL afterUnits)
{
   funcname1 = "CreateFogModifierRadiusLoc";
   SpyJassLog(" Exec:CreateFogModifierRadiusLoc[forWhichPlayer:%i, State:%s, center:%s, radius:%.4g, useSharedVision:%s, afterUnits:%s]...",GetPlayerId_ptr(forWhichPlayer), GetStrID(State).c_str( ), GetStrID(center).c_str( ), (*radius), BoolToStr(useSharedVision), BoolToStr(afterUnits));
   HFOGMODIFIER returnvalue; 
   returnvalue = CreateFogModifierRadiusLoc_ptr(forWhichPlayer, State, center, radius, useSharedVision, afterUnits);
   SpyJassLog("[CreateFogModifierRadiusLoc] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HFOGMODIFIER _cdecl CreateFogModifierRect_my(HPLAYER forWhichPlayer, HFOGSTATE State, HRECT where, BOOL useSharedVision, BOOL afterUnits)
{
   funcname1 = "CreateFogModifierRect";
   SpyJassLog(" Exec:CreateFogModifierRect[forWhichPlayer:%i, State:%s, where:%s, useSharedVision:%s, afterUnits:%s]...",GetPlayerId_ptr(forWhichPlayer), GetStrID(State).c_str( ), GetStrID(where).c_str( ), BoolToStr(useSharedVision), BoolToStr(afterUnits));
   HFOGMODIFIER returnvalue; 
   returnvalue = CreateFogModifierRect_ptr(forWhichPlayer, State, where, useSharedVision, afterUnits);
   SpyJassLog("[CreateFogModifierRect] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HFORCE _cdecl CreateForce_my()
{
   funcname1 = "CreateForce";
   SpyJassLog(" Exec:CreateForce[]...");
   HFORCE returnvalue; 
   returnvalue = CreateForce_ptr();
   SpyJassLog("[CreateForce] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HGROUP _cdecl CreateGroup_my()
{
   funcname1 = "CreateGroup";
   SpyJassLog(" Exec:CreateGroup[]...");
   HGROUP returnvalue; 
   returnvalue = CreateGroup_ptr();
   SpyJassLog("[CreateGroup] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HIMAGE _cdecl CreateImage_my(CJassString file, float *sizeX, float *sizeY, float *sizeZ, float *posX, float *posY, float *posZ, float *originX, float *originY, float *originZ, int imageType)
{
   funcname1 = "CreateImage";
   SpyJassLog(" Exec:CreateImage[file:%s, sizeX:%.4g, sizeY:%.4g, sizeZ:%.4g, posX:%.4g, posY:%.4g, posZ:%.4g, originX:%.4g, originY:%.4g, originZ:%.4g, imageType:%s]...",ReadJassStringNormal(file), (*sizeX), (*sizeY), (*sizeZ), (*posX), (*posY), (*posZ), (*originX), (*originY), (*originZ), GetStrID(imageType).c_str( ));
   HIMAGE returnvalue; 
   returnvalue = CreateImage_ptr(file, sizeX, sizeY, sizeZ, posX, posY, posZ, originX, originY, originZ, imageType);
   SpyJassLog("[CreateImage] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HITEM _cdecl CreateItem_my(int itemid, float *x, float *y)
{
   funcname1 = "CreateItem";
   SpyJassLog(" Exec:CreateItem[itemid:%s, x:%.4g, y:%.4g]...",GetStrID(itemid).c_str( ), (*x), (*y));
   HITEM returnvalue; 
   returnvalue = CreateItem_ptr(itemid, x, y);
   SpyJassLog("[CreateItem] OK [%s]\n",GetItemHID(returnvalue).c_str( ));
   return returnvalue;
}
HITEMPOOL _cdecl CreateItemPool_my()
{
   funcname1 = "CreateItemPool";
   SpyJassLog(" Exec:CreateItemPool[]...");
   HITEMPOOL returnvalue; 
   returnvalue = CreateItemPool_ptr();
   SpyJassLog("[CreateItemPool] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HLEADERBOARD _cdecl CreateLeaderboard_my()
{
   funcname1 = "CreateLeaderboard";
   SpyJassLog(" Exec:CreateLeaderboard[]...");
   HLEADERBOARD returnvalue; 
   returnvalue = CreateLeaderboard_ptr();
   SpyJassLog("[CreateLeaderboard] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HSOUND _cdecl CreateMIDISound_my(CJassString soundLabel, int fadeInRate, int fadeOutRate)
{
   funcname1 = "CreateMIDISound";
   SpyJassLog(" Exec:CreateMIDISound[soundLabel:%s, fadeInRate:%s, fadeOutRate:%s]...",ReadJassStringNormal(soundLabel), GetStrID(fadeInRate).c_str( ), GetStrID(fadeOutRate).c_str( ));
   HSOUND returnvalue; 
   returnvalue = CreateMIDISound_ptr(soundLabel, fadeInRate, fadeOutRate);
   SpyJassLog("[CreateMIDISound] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HMULTIBOARD _cdecl CreateMultiboard_my()
{
   funcname1 = "CreateMultiboard";
   SpyJassLog(" Exec:CreateMultiboard[]...");
   HMULTIBOARD returnvalue; 
   returnvalue = CreateMultiboard_ptr();
   SpyJassLog("[CreateMultiboard] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HQUEST _cdecl CreateQuest_my()
{
   funcname1 = "CreateQuest";
   SpyJassLog(" Exec:CreateQuest[]...");
   HQUEST returnvalue; 
   returnvalue = CreateQuest_ptr();
   SpyJassLog("[CreateQuest] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HREGION _cdecl CreateRegion_my()
{
   funcname1 = "CreateRegion";
   SpyJassLog(" Exec:CreateRegion[]...");
   HREGION returnvalue; 
   returnvalue = CreateRegion_ptr();
   SpyJassLog("[CreateRegion] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HSOUND _cdecl CreateSound_my(CJassString fileName, BOOL looping, BOOL is3D, BOOL stopwhenoutofrange, int fadeInRate, int fadeOutRate, CJassString eaxSetting)
{
   funcname1 = "CreateSound";
   SpyJassLog(" Exec:CreateSound[fileName:%s, looping:%s, is3D:%s, stopwhenoutofrange:%s, fadeInRate:%s, fadeOutRate:%s, eaxSetting:%s]...",ReadJassStringNormal(fileName), BoolToStr(looping), BoolToStr(is3D), BoolToStr(stopwhenoutofrange), GetStrID(fadeInRate).c_str( ), GetStrID(fadeOutRate).c_str( ), ReadJassStringNormal(eaxSetting));
   HSOUND returnvalue; 
   returnvalue = CreateSound_ptr(fileName, looping, is3D, stopwhenoutofrange, fadeInRate, fadeOutRate, eaxSetting);
   SpyJassLog("[CreateSound] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HSOUND _cdecl CreateSoundFilenameWithLabel_my(CJassString fileName, BOOL looping, BOOL is3D, BOOL stopwhenoutofrange, int fadeInRate, int fadeOutRate, CJassString SLKEntryName)
{
   funcname1 = "CreateSoundFilenameWithLabel";
   SpyJassLog(" Exec:CreateSoundFilenameWithLabel[fileName:%s, looping:%s, is3D:%s, stopwhenoutofrange:%s, fadeInRate:%s, fadeOutRate:%s, SLKEntryName:%s]...",ReadJassStringNormal(fileName), BoolToStr(looping), BoolToStr(is3D), BoolToStr(stopwhenoutofrange), GetStrID(fadeInRate).c_str( ), GetStrID(fadeOutRate).c_str( ), ReadJassStringNormal(SLKEntryName));
   HSOUND returnvalue; 
   returnvalue = CreateSoundFilenameWithLabel_ptr(fileName, looping, is3D, stopwhenoutofrange, fadeInRate, fadeOutRate, SLKEntryName);
   SpyJassLog("[CreateSoundFilenameWithLabel] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HSOUND _cdecl CreateSoundFromLabel_my(CJassString soundLabel, BOOL looping, BOOL is3D, BOOL stopwhenoutofrange, int fadeInRate, int fadeOutRate)
{
   funcname1 = "CreateSoundFromLabel";
   SpyJassLog(" Exec:CreateSoundFromLabel[soundLabel:%s, looping:%s, is3D:%s, stopwhenoutofrange:%s, fadeInRate:%s, fadeOutRate:%s]...",ReadJassStringNormal(soundLabel), BoolToStr(looping), BoolToStr(is3D), BoolToStr(stopwhenoutofrange), GetStrID(fadeInRate).c_str( ), GetStrID(fadeOutRate).c_str( ));
   HSOUND returnvalue; 
   returnvalue = CreateSoundFromLabel_ptr(soundLabel, looping, is3D, stopwhenoutofrange, fadeInRate, fadeOutRate);
   SpyJassLog("[CreateSoundFromLabel] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTEXTTAG _cdecl CreateTextTag_my()
{
   funcname1 = "CreateTextTag";
   SpyJassLog(" Exec:CreateTextTag[]...");
   HTEXTTAG returnvalue; 
   returnvalue = CreateTextTag_ptr();
   SpyJassLog("[CreateTextTag] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTIMER _cdecl CreateTimer_my()
{
   funcname1 = "CreateTimer";
   SpyJassLog(" Exec:CreateTimer[]...");
   HTIMER returnvalue; 
   returnvalue = CreateTimer_ptr();
   SpyJassLog("[CreateTimer] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTIMERDIALOG _cdecl CreateTimerDialog_my(HTIMER t)
{
   funcname1 = "CreateTimerDialog";
   SpyJassLog(" Exec:CreateTimerDialog[t:%s]...",GetStrID(t).c_str( ));
   HTIMERDIALOG returnvalue; 
   returnvalue = CreateTimerDialog_ptr(t);
   SpyJassLog("[CreateTimerDialog] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTRACKABLE _cdecl CreateTrackable_my(CJassString trackableModelPath, float *x, float *y, float *facing)
{
   funcname1 = "CreateTrackable";
   SpyJassLog(" Exec:CreateTrackable[trackableModelPath:%s, x:%.4g, y:%.4g, facing:%.4g]...",ReadJassStringNormal(trackableModelPath), (*x), (*y), (*facing));
   HTRACKABLE returnvalue; 
   returnvalue = CreateTrackable_ptr(trackableModelPath, x, y, facing);
   SpyJassLog("[CreateTrackable] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTRIGGER _cdecl CreateTrigger_my()
{
   funcname1 = "CreateTrigger";
   SpyJassLog(" Exec:CreateTrigger[]...");
   HTRIGGER returnvalue; 
   returnvalue = CreateTrigger_ptr();
   SpyJassLog("[CreateTrigger] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUBERSPLAT _cdecl CreateUbersplat_my(float *x, float *y, CJassString name, int red, int green, int blue, int alpha, BOOL forcePaused, BOOL noBirthTime)
{
   funcname1 = "CreateUbersplat";
   SpyJassLog(" Exec:CreateUbersplat[x:%.4g, y:%.4g, name:%s, red:%s, green:%s, blue:%s, alpha:%s, forcePaused:%s, noBirthTime:%s]...",(*x), (*y), ReadJassStringNormal(name), GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), GetStrID(alpha).c_str( ), BoolToStr(forcePaused), BoolToStr(noBirthTime));
   HUBERSPLAT returnvalue; 
   returnvalue = CreateUbersplat_ptr(x, y, name, red, green, blue, alpha, forcePaused, noBirthTime);
   SpyJassLog("[CreateUbersplat] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNIT _cdecl CreateUnit_my(HPLAYER id, int unitid, float *x, float *y, float *face)
{
   funcname1 = "CreateUnit";
   SpyJassLog(" Exec:CreateUnit[id:%i, unitid:%s, x:%.4g, y:%.4g, face:%.4g]...",GetPlayerId_ptr(id), GetStrID(unitid).c_str( ), (*x), (*y), (*face));
   HUNIT returnvalue; 
   returnvalue = CreateUnit_ptr(id, unitid, x, y, face);
   SpyJassLog("[CreateUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl CreateUnitAtLoc_my(HPLAYER id, int unitid, HLOCATION Location, float *face)
{
   funcname1 = "CreateUnitAtLoc";
   SpyJassLog(" Exec:CreateUnitAtLoc[id:%i, unitid:%s, Location:%s, face:%.4g]...",GetPlayerId_ptr(id), GetStrID(unitid).c_str( ), GetStrID(Location).c_str( ), (*face));
   HUNIT returnvalue; 
   returnvalue = CreateUnitAtLoc_ptr(id, unitid, Location, face);
   SpyJassLog("[CreateUnitAtLoc] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl CreateUnitAtLocByName_my(HPLAYER id, CJassString unitname, HLOCATION Location, float *face)
{
   funcname1 = "CreateUnitAtLocByName";
   SpyJassLog(" Exec:CreateUnitAtLocByName[id:%i, unitname:%s, Location:%s, face:%.4g]...",GetPlayerId_ptr(id), ReadJassStringNormal(unitname), GetStrID(Location).c_str( ), (*face));
   HUNIT returnvalue; 
   returnvalue = CreateUnitAtLocByName_ptr(id, unitname, Location, face);
   SpyJassLog("[CreateUnitAtLocByName] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl CreateUnitByName_my(HPLAYER player, CJassString unitname, float *x, float *y, float *face)
{
   funcname1 = "CreateUnitByName";
   SpyJassLog(" Exec:CreateUnitByName[player:%i, unitname:%s, x:%.4g, y:%.4g, face:%.4g]...",GetPlayerId_ptr(player), ReadJassStringNormal(unitname), (*x), (*y), (*face));
   HUNIT returnvalue; 
   returnvalue = CreateUnitByName_ptr(player, unitname, x, y, face);
   SpyJassLog("[CreateUnitByName] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNITPOOL _cdecl CreateUnitPool_my()
{
   funcname1 = "CreateUnitPool";
   SpyJassLog(" Exec:CreateUnitPool[]...");
   HUNITPOOL returnvalue; 
   returnvalue = CreateUnitPool_ptr();
   SpyJassLog("[CreateUnitPool] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
BOOL _cdecl CreepsOnMap_my()
{
   funcname1 = "CreepsOnMap";
   SpyJassLog(" Exec:CreepsOnMap[]...");
   BOOL returnvalue; 
   returnvalue = CreepsOnMap_ptr();
   SpyJassLog("[CreepsOnMap] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl CripplePlayer_my(HPLAYER player, HFORCE toWhichPlayers, BOOL flag)
{
   funcname1 = "CripplePlayer";
   SpyJassLog(" Exec:CripplePlayer...");
   CripplePlayer_ptr(player, toWhichPlayers, flag);
   SpyJassLog("[CripplePlayer] OK [player:%i, toWhichPlayers:%s, flag:%s]\n",GetPlayerId_ptr(player), GetStrID(toWhichPlayers).c_str( ), BoolToStr(flag));
}
void _cdecl DebugBreak_my(int arg1)
{
   funcname1 = "DebugBreak";
   SpyJassLog(" Exec:DebugBreak...");
   DebugBreak_ptr(arg1);
   SpyJassLog("[DebugBreak] OK [arg1:%s]\n",GetStrID(arg1).c_str( ));
}
void _cdecl DebugFI_my(CJassString arg1, int arg2)
{
   funcname1 = "DebugFI";
   SpyJassLog(" Exec:DebugFI...");
   DebugFI_ptr(arg1, arg2);
   SpyJassLog("[DebugFI] OK [arg1:%s, arg2:%s]\n",ReadJassStringNormal(arg1), GetStrID(arg2).c_str( ));
}
void _cdecl DebugS_my(CJassString arg1)
{
   funcname1 = "DebugS";
   SpyJassLog(" Exec:DebugS...");
   DebugS_ptr(arg1);
   SpyJassLog("[DebugS] OK [arg1:%s]\n",ReadJassStringNormal(arg1));
}
void _cdecl DebugUnitID_my(CJassString arg1, int arg2)
{
   funcname1 = "DebugUnitID";
   SpyJassLog(" Exec:DebugUnitID...");
   DebugUnitID_ptr(arg1, arg2);
   SpyJassLog("[DebugUnitID] OK [arg1:%s, arg2:%s]\n",ReadJassStringNormal(arg1), GetStrID(arg2).c_str( ));
}
int _cdecl DecUnitAbilityLevel_my(HUNIT unit, int abilcode)
{
   funcname1 = "DecUnitAbilityLevel";
   SpyJassLog(" Exec:DecUnitAbilityLevel[unit:%s, abilcode:%s]...",GetUnitHID(unit).c_str( ), GetStrID(abilcode).c_str( ));
   int returnvalue; 
   returnvalue = DecUnitAbilityLevel_ptr(unit, abilcode);
   SpyJassLog("[DecUnitAbilityLevel] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl DefeatConditionSetDescription_my(HDEFEATCONDITION Condition, CJassString description)
{
   funcname1 = "DefeatConditionSetDescription";
   SpyJassLog(" Exec:DefeatConditionSetDescription...");
   DefeatConditionSetDescription_ptr(Condition, description);
   SpyJassLog("[DefeatConditionSetDescription] OK [Condition:%s, description:%s]\n",GetStrID(Condition).c_str( ), ReadJassStringNormal(description));
}
void _cdecl DefineStartLocation_my(int StartLoc, float *x, float *y)
{
   funcname1 = "DefineStartLocation";
   SpyJassLog(" Exec:DefineStartLocation...");
   DefineStartLocation_ptr(StartLoc, x, y);
   SpyJassLog("[DefineStartLocation] OK [StartLoc:%s, x:%.4g, y:%.4g]\n",GetStrID(StartLoc).c_str( ), (*x), (*y));
}
void _cdecl DefineStartLocationLoc_my(int StartLoc, HLOCATION Location)
{
   funcname1 = "DefineStartLocationLoc";
   SpyJassLog(" Exec:DefineStartLocationLoc...");
   DefineStartLocationLoc_ptr(StartLoc, Location);
   SpyJassLog("[DefineStartLocationLoc] OK [StartLoc:%s, Location:%s]\n",GetStrID(StartLoc).c_str( ), GetStrID(Location).c_str( ));
}
DWFP _cdecl Deg2Rad_my(float *degrees)
{
   funcname1 = "Deg2Rad";
   SpyJassLog(" Exec:Deg2Rad[degrees:%.4g]...",(*degrees));
   DWFP returnvalue; 
   returnvalue = Deg2Rad_ptr(degrees);
   SpyJassLog("[Deg2Rad] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
void _cdecl DestroyBoolExpr_my(HBOOLEXPR e)
{
   funcname1 = "DestroyBoolExpr";
   SpyJassLog(" Exec:DestroyBoolExpr...");
   DestroyBoolExpr_ptr(e);
   SpyJassLog("[DestroyBoolExpr] OK [e:%s]\n",GetStrID(e).c_str( ));
}
void _cdecl DestroyCondition_my(HCONDITIONFUNC c)
{
   funcname1 = "DestroyCondition";
   SpyJassLog(" Exec:DestroyCondition...");
   DestroyCondition_ptr(c);
   SpyJassLog("[DestroyCondition] OK [c:%s]\n",GetStrID(c).c_str( ));
}
void _cdecl DestroyDefeatCondition_my(HDEFEATCONDITION Condition)
{
   funcname1 = "DestroyDefeatCondition";
   SpyJassLog(" Exec:DestroyDefeatCondition...");
   DestroyDefeatCondition_ptr(Condition);
   SpyJassLog("[DestroyDefeatCondition] OK [Condition:%s]\n",GetStrID(Condition).c_str( ));
}
void _cdecl DestroyEffect_my(HEFFECT Effect)
{
   funcname1 = "DestroyEffect";
   SpyJassLog(" Exec:DestroyEffect...");
   DestroyEffect_ptr(Effect);
   SpyJassLog("[DestroyEffect] OK [Effect:%s]\n",GetStrID(Effect).c_str( ));
}
void _cdecl DestroyFilter_my(HFILTERFUNC f)
{
   funcname1 = "DestroyFilter";
   SpyJassLog(" Exec:DestroyFilter...");
   DestroyFilter_ptr(f);
   SpyJassLog("[DestroyFilter] OK [f:%s]\n",GetStrID(f).c_str( ));
}
void _cdecl DestroyFogModifier_my(HFOGMODIFIER FogModifier)
{
   funcname1 = "DestroyFogModifier";
   SpyJassLog(" Exec:DestroyFogModifier...");
   DestroyFogModifier_ptr(FogModifier);
   SpyJassLog("[DestroyFogModifier] OK [FogModifier:%s]\n",GetStrID(FogModifier).c_str( ));
}
void _cdecl DestroyForce_my(HFORCE Force)
{
   funcname1 = "DestroyForce";
   SpyJassLog(" Exec:DestroyForce...");
   DestroyForce_ptr(Force);
   SpyJassLog("[DestroyForce] OK [Force:%s]\n",GetStrID(Force).c_str( ));
}
void _cdecl DestroyGroup_my(HGROUP Group)
{
   funcname1 = "DestroyGroup";
   SpyJassLog(" Exec:DestroyGroup...");
   DestroyGroup_ptr(Group);
   SpyJassLog("[DestroyGroup] OK [Group:%s]\n",GetStrID(Group).c_str( ));
}
void _cdecl DestroyImage_my(HIMAGE Image)
{
   funcname1 = "DestroyImage";
   SpyJassLog(" Exec:DestroyImage...");
   DestroyImage_ptr(Image);
   SpyJassLog("[DestroyImage] OK [Image:%s]\n",GetStrID(Image).c_str( ));
}
void _cdecl DestroyItemPool_my(HITEMPOOL ItemPool)
{
   funcname1 = "DestroyItemPool";
   SpyJassLog(" Exec:DestroyItemPool...");
   DestroyItemPool_ptr(ItemPool);
   SpyJassLog("[DestroyItemPool] OK [ItemPool:%s]\n",GetStrID(ItemPool).c_str( ));
}
void _cdecl DestroyLeaderboard_my(HLEADERBOARD lb)
{
   funcname1 = "DestroyLeaderboard";
   SpyJassLog(" Exec:DestroyLeaderboard...");
   DestroyLeaderboard_ptr(lb);
   SpyJassLog("[DestroyLeaderboard] OK [lb:%s]\n",GetStrID(lb).c_str( ));
}
BOOL _cdecl DestroyLightning_my(HLIGHTNING Bolt)
{
   funcname1 = "DestroyLightning";
   SpyJassLog(" Exec:DestroyLightning[Bolt:%s]...",GetStrID(Bolt).c_str( ));
   BOOL returnvalue; 
   returnvalue = DestroyLightning_ptr(Bolt);
   SpyJassLog("[DestroyLightning] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl DestroyMultiboard_my(HMULTIBOARD lb)
{
   funcname1 = "DestroyMultiboard";
   SpyJassLog(" Exec:DestroyMultiboard...");
   DestroyMultiboard_ptr(lb);
   SpyJassLog("[DestroyMultiboard] OK [lb:%s]\n",GetStrID(lb).c_str( ));
}
void _cdecl DestroyQuest_my(HQUEST Quest)
{
   funcname1 = "DestroyQuest";
   SpyJassLog(" Exec:DestroyQuest...");
   DestroyQuest_ptr(Quest);
   SpyJassLog("[DestroyQuest] OK [Quest:%s]\n",GetStrID(Quest).c_str( ));
}
void _cdecl DestroyTextTag_my(HTEXTTAG t)
{
   funcname1 = "DestroyTextTag";
   SpyJassLog(" Exec:DestroyTextTag...");
   DestroyTextTag_ptr(t);
   SpyJassLog("[DestroyTextTag] OK [t:%s]\n",GetStrID(t).c_str( ));
}
void _cdecl DestroyTimer_my(HTIMER Timer)
{
   funcname1 = "DestroyTimer";
   SpyJassLog(" Exec:DestroyTimer...");
   DestroyTimer_ptr(Timer);
   SpyJassLog("[DestroyTimer] OK [Timer:%s]\n",GetStrID(Timer).c_str( ));
}
void _cdecl DestroyTimerDialog_my(HTIMERDIALOG Dialog)
{
   funcname1 = "DestroyTimerDialog";
   SpyJassLog(" Exec:DestroyTimerDialog...");
   DestroyTimerDialog_ptr(Dialog);
   SpyJassLog("[DestroyTimerDialog] OK [Dialog:%s]\n",GetStrID(Dialog).c_str( ));
}
void _cdecl DestroyTrigger_my(HTRIGGER Trigger)
{
   funcname1 = "DestroyTrigger";
   SpyJassLog(" Exec:DestroyTrigger...");
   DestroyTrigger_ptr(Trigger);
   SpyJassLog("[DestroyTrigger] OK [Trigger:%s]\n",GetStrID(Trigger).c_str( ));
}
void _cdecl DestroyUbersplat_my(HUBERSPLAT Splat)
{
   funcname1 = "DestroyUbersplat";
   SpyJassLog(" Exec:DestroyUbersplat...");
   DestroyUbersplat_ptr(Splat);
   SpyJassLog("[DestroyUbersplat] OK [Splat:%s]\n",GetStrID(Splat).c_str( ));
}
void _cdecl DestroyUnitPool_my(HUNITPOOL Pool)
{
   funcname1 = "DestroyUnitPool";
   SpyJassLog(" Exec:DestroyUnitPool...");
   DestroyUnitPool_ptr(Pool);
   SpyJassLog("[DestroyUnitPool] OK [Pool:%s]\n",GetStrID(Pool).c_str( ));
}
void _cdecl DestructableRestoreLife_my(HDESTRUCTABLE d, float *life, BOOL birth)
{
   funcname1 = "DestructableRestoreLife";
   SpyJassLog(" Exec:DestructableRestoreLife...");
   DestructableRestoreLife_ptr(d, life, birth);
   SpyJassLog("[DestructableRestoreLife] OK [d:%s, life:%.4g, birth:%s]\n",GetStrID(d).c_str( ), (*life), BoolToStr(birth));
}
HBUTTON _cdecl DialogAddButton_my(HDIALOG Dialog, CJassString buttonText, int hotkey)
{
   funcname1 = "DialogAddButton";
   SpyJassLog(" Exec:DialogAddButton[Dialog:%s, buttonText:%s, hotkey:%s]...",GetStrID(Dialog).c_str( ), ReadJassStringNormal(buttonText), GetStrID(hotkey).c_str( ));
   HBUTTON returnvalue; 
   returnvalue = DialogAddButton_ptr(Dialog, buttonText, hotkey);
   SpyJassLog("[DialogAddButton] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HBUTTON _cdecl DialogAddQuitButton_my(HDIALOG Dialog, BOOL doScoreScreen, CJassString buttonText, int hotkey)
{
   funcname1 = "DialogAddQuitButton";
   SpyJassLog(" Exec:DialogAddQuitButton[Dialog:%s, doScoreScreen:%s, buttonText:%s, hotkey:%s]...",GetStrID(Dialog).c_str( ), BoolToStr(doScoreScreen), ReadJassStringNormal(buttonText), GetStrID(hotkey).c_str( ));
   HBUTTON returnvalue; 
   returnvalue = DialogAddQuitButton_ptr(Dialog, doScoreScreen, buttonText, hotkey);
   SpyJassLog("[DialogAddQuitButton] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl DialogClear_my(HDIALOG Dialog)
{
   funcname1 = "DialogClear";
   SpyJassLog(" Exec:DialogClear...");
   DialogClear_ptr(Dialog);
   SpyJassLog("[DialogClear] OK [Dialog:%s]\n",GetStrID(Dialog).c_str( ));
}
HDIALOG _cdecl DialogCreate_my()
{
   funcname1 = "DialogCreate";
   SpyJassLog(" Exec:DialogCreate[]...");
   HDIALOG returnvalue; 
   returnvalue = DialogCreate_ptr();
   SpyJassLog("[DialogCreate] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl DialogDestroy_my(HDIALOG Dialog)
{
   funcname1 = "DialogDestroy";
   SpyJassLog(" Exec:DialogDestroy...");
   DialogDestroy_ptr(Dialog);
   SpyJassLog("[DialogDestroy] OK [Dialog:%s]\n",GetStrID(Dialog).c_str( ));
}
void _cdecl DialogDisplay_my(HPLAYER player, HDIALOG Dialog, BOOL flag)
{
   funcname1 = "DialogDisplay";
   SpyJassLog(" Exec:DialogDisplay...");
   DialogDisplay_ptr(player, Dialog, flag);
   SpyJassLog("[DialogDisplay] OK [player:%i, Dialog:%s, flag:%s]\n",GetPlayerId_ptr(player), GetStrID(Dialog).c_str( ), BoolToStr(flag));
}
void _cdecl DialogSetAsync_my(HDIALOG arg1)
{
   funcname1 = "DialogSetAsync";
   SpyJassLog(" Exec:DialogSetAsync...");
   DialogSetAsync_ptr(arg1);
   SpyJassLog("[DialogSetAsync] OK [arg1:%s]\n",GetStrID(arg1).c_str( ));
}
void _cdecl DialogSetMessage_my(HDIALOG Dialog, CJassString messageText)
{
   funcname1 = "DialogSetMessage";
   SpyJassLog(" Exec:DialogSetMessage...");
   DialogSetMessage_ptr(Dialog, messageText);
   SpyJassLog("[DialogSetMessage] OK [Dialog:%s, messageText:%s]\n",GetStrID(Dialog).c_str( ), ReadJassStringNormal(messageText));
}
void _cdecl DisablePathing_my()
{
   funcname1 = "DisablePathing";
   SpyJassLog(" Exec:DisablePathing...");
   DisablePathing_ptr();
   SpyJassLog("[DisablePathing] OK []\n");
}
void _cdecl DisableRestartMission_my(BOOL flag)
{
   funcname1 = "DisableRestartMission";
   SpyJassLog(" Exec:DisableRestartMission...");
   DisableRestartMission_ptr(flag);
   SpyJassLog("[DisableRestartMission] OK [flag:%s]\n",BoolToStr(flag));
}
void _cdecl DisableTrigger_my(HTRIGGER Trigger)
{
   funcname1 = "DisableTrigger";
   SpyJassLog(" Exec:DisableTrigger...");
   DisableTrigger_ptr(Trigger);
   SpyJassLog("[DisableTrigger] OK [Trigger:%s]\n",GetStrID(Trigger).c_str( ));
}
void _cdecl DisplayCineFilter_my(BOOL flag)
{
   funcname1 = "DisplayCineFilter";
   SpyJassLog(" Exec:DisplayCineFilter...");
   DisplayCineFilter_ptr(flag);
   SpyJassLog("[DisplayCineFilter] OK [flag:%s]\n",BoolToStr(flag));
}
void _cdecl DisplayLoadDialog_my()
{
   funcname1 = "DisplayLoadDialog";
   SpyJassLog(" Exec:DisplayLoadDialog...");
   DisplayLoadDialog_ptr();
   SpyJassLog("[DisplayLoadDialog] OK []\n");
}
void _cdecl DisplayText_my(int arg1, CJassString arg2)
{
   funcname1 = "DisplayText";
   SpyJassLog(" Exec:DisplayText...");
   DisplayText_ptr(arg1, arg2);
   SpyJassLog("[DisplayText] OK [arg1:%s, arg2:%s]\n",GetStrID(arg1).c_str( ), ReadJassStringNormal(arg2));
}
void _cdecl DisplayTextI_my(int arg1, CJassString arg2, int arg3)
{
   funcname1 = "DisplayTextI";
   SpyJassLog(" Exec:DisplayTextI...");
   DisplayTextI_ptr(arg1, arg2, arg3);
   SpyJassLog("[DisplayTextI] OK [arg1:%s, arg2:%s, arg3:%s]\n",GetStrID(arg1).c_str( ), ReadJassStringNormal(arg2), GetStrID(arg3).c_str( ));
}
void _cdecl DisplayTextII_my(int arg1, CJassString arg2, int arg3, int arg4)
{
   funcname1 = "DisplayTextII";
   SpyJassLog(" Exec:DisplayTextII...");
   DisplayTextII_ptr(arg1, arg2, arg3, arg4);
   SpyJassLog("[DisplayTextII] OK [arg1:%s, arg2:%s, arg3:%s, arg4:%s]\n",GetStrID(arg1).c_str( ), ReadJassStringNormal(arg2), GetStrID(arg3).c_str( ), GetStrID(arg4).c_str( ));
}
void _cdecl DisplayTextIII_my(int arg1, CJassString arg2, int arg3, int arg4, int arg5)
{
   funcname1 = "DisplayTextIII";
   SpyJassLog(" Exec:DisplayTextIII...");
   DisplayTextIII_ptr(arg1, arg2, arg3, arg4, arg5);
   SpyJassLog("[DisplayTextIII] OK [arg1:%s, arg2:%s, arg3:%s, arg4:%s, arg5:%s]\n",GetStrID(arg1).c_str( ), ReadJassStringNormal(arg2), GetStrID(arg3).c_str( ), GetStrID(arg4).c_str( ), GetStrID(arg5).c_str( ));
}
void _cdecl DisplayTextToPlayer_my(HPLAYER toPlayer, float *x, float *y, CJassString message)
{
   funcname1 = "DisplayTextToPlayer";
   SpyJassLog(" Exec:DisplayTextToPlayer...");
   DisplayTextToPlayer_ptr(toPlayer, x, y, message);
   SpyJassLog("[DisplayTextToPlayer] OK [toPlayer:%i, x:%.4g, y:%.4g, message:%s]\n",GetPlayerId_ptr(toPlayer), (*x), (*y), ReadJassStringNormal(message));
}
void _cdecl DisplayTimedTextFromPlayer_my(HPLAYER toPlayer, float *x, float *y, float *duration, CJassString message)
{
   funcname1 = "DisplayTimedTextFromPlayer";
   SpyJassLog(" Exec:DisplayTimedTextFromPlayer...");
   DisplayTimedTextFromPlayer_ptr(toPlayer, x, y, duration, message);
   SpyJassLog("[DisplayTimedTextFromPlayer] OK [toPlayer:%i, x:%.4g, y:%.4g, duration:%.4g, message:%s]\n",GetPlayerId_ptr(toPlayer), (*x), (*y), (*duration), ReadJassStringNormal(message));
}
void _cdecl DisplayTimedTextToPlayer_my(HPLAYER toPlayer, float *x, float *y, float *duration, CJassString message)
{
   funcname1 = "DisplayTimedTextToPlayer";
   SpyJassLog(" Exec:DisplayTimedTextToPlayer...");
   DisplayTimedTextToPlayer_ptr(toPlayer, x, y, duration, message);
   SpyJassLog("[DisplayTimedTextToPlayer] OK [toPlayer:%i, x:%.4g, y:%.4g, duration:%.4g, message:%s]\n",GetPlayerId_ptr(toPlayer), (*x), (*y), (*duration), ReadJassStringNormal(message));
}
BOOL _cdecl DoAiScriptDebug_my()
{
   funcname1 = "DoAiScriptDebug";
   SpyJassLog(" Exec:DoAiScriptDebug[]...");
   BOOL returnvalue; 
   returnvalue = DoAiScriptDebug_ptr();
   SpyJassLog("[DoAiScriptDebug] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl DoNotSaveReplay_my()
{
   funcname1 = "DoNotSaveReplay";
   SpyJassLog(" Exec:DoNotSaveReplay...");
   DoNotSaveReplay_ptr();
   SpyJassLog("[DoNotSaveReplay] OK []\n");
}
void _cdecl EnableDragSelect_my(BOOL state, BOOL ui)
{
   funcname1 = "EnableDragSelect";
   SpyJassLog(" Exec:EnableDragSelect...");
   EnableDragSelect_ptr(state, ui);
   SpyJassLog("[EnableDragSelect] OK [state:%s, ui:%s]\n",BoolToStr(state), BoolToStr(ui));
}
void _cdecl EnableMinimapFilterButtons_my(BOOL enableAlly, BOOL enableCreep)
{
   funcname1 = "EnableMinimapFilterButtons";
   SpyJassLog(" Exec:EnableMinimapFilterButtons...");
   EnableMinimapFilterButtons_ptr(enableAlly, enableCreep);
   SpyJassLog("[EnableMinimapFilterButtons] OK [enableAlly:%s, enableCreep:%s]\n",BoolToStr(enableAlly), BoolToStr(enableCreep));
}
void _cdecl EnableOcclusion_my(BOOL flag)
{
   funcname1 = "EnableOcclusion";
   SpyJassLog(" Exec:EnableOcclusion...");
   EnableOcclusion_ptr(flag);
   SpyJassLog("[EnableOcclusion] OK [flag:%s]\n",BoolToStr(flag));
}
void _cdecl EnablePreSelect_my(BOOL state, BOOL ui)
{
   funcname1 = "EnablePreSelect";
   SpyJassLog(" Exec:EnablePreSelect...");
   EnablePreSelect_ptr(state, ui);
   SpyJassLog("[EnablePreSelect] OK [state:%s, ui:%s]\n",BoolToStr(state), BoolToStr(ui));
}
void _cdecl EnableSelect_my(BOOL state, BOOL ui)
{
   funcname1 = "EnableSelect";
   SpyJassLog(" Exec:EnableSelect...");
   EnableSelect_ptr(state, ui);
   SpyJassLog("[EnableSelect] OK [state:%s, ui:%s]\n",BoolToStr(state), BoolToStr(ui));
}
void _cdecl EnableTrigger_my(HTRIGGER Trigger)
{
   funcname1 = "EnableTrigger";
   SpyJassLog(" Exec:EnableTrigger...");
   EnableTrigger_ptr(Trigger);
   SpyJassLog("[EnableTrigger] OK [Trigger:%s]\n",GetStrID(Trigger).c_str( ));
}
void _cdecl EnableUserControl_my(BOOL b)
{
   funcname1 = "EnableUserControl";
   SpyJassLog(" Exec:EnableUserControl...");
   EnableUserControl_ptr(b);
   SpyJassLog("[EnableUserControl] OK [b:%s]\n",BoolToStr(b));
}
void _cdecl EnableUserUI_my(BOOL b)
{
   funcname1 = "EnableUserUI";
   SpyJassLog(" Exec:EnableUserUI...");
   EnableUserUI_ptr(b);
   SpyJassLog("[EnableUserUI] OK [b:%s]\n",BoolToStr(b));
}
void _cdecl EnableWeatherEffect_my(HWEATHEREFFECT Effect, BOOL enable)
{
   funcname1 = "EnableWeatherEffect";
   SpyJassLog(" Exec:EnableWeatherEffect...");
   EnableWeatherEffect_ptr(Effect, enable);
   SpyJassLog("[EnableWeatherEffect] OK [Effect:%s, enable:%s]\n",GetStrID(Effect).c_str( ), BoolToStr(enable));
}
void _cdecl EnableWorldFogBoundary_my(BOOL b)
{
   funcname1 = "EnableWorldFogBoundary";
   SpyJassLog(" Exec:EnableWorldFogBoundary...");
   EnableWorldFogBoundary_ptr(b);
   SpyJassLog("[EnableWorldFogBoundary] OK [b:%s]\n",BoolToStr(b));
}
void _cdecl EndCinematicScene_my()
{
   funcname1 = "EndCinematicScene";
   SpyJassLog(" Exec:EndCinematicScene...");
   EndCinematicScene_ptr();
   SpyJassLog("[EndCinematicScene] OK []\n");
}
void _cdecl EndGame_my(BOOL doScoreScreen)
{
   funcname1 = "EndGame";
   SpyJassLog(" Exec:EndGame...");
   EndGame_ptr(doScoreScreen);
   SpyJassLog("[EndGame] OK [doScoreScreen:%s]\n",BoolToStr(doScoreScreen));
}
void _cdecl EndThematicMusic_my()
{
   funcname1 = "EndThematicMusic";
   SpyJassLog(" Exec:EndThematicMusic...");
   EndThematicMusic_ptr();
   SpyJassLog("[EndThematicMusic] OK []\n");
}
void _cdecl EnumDestructablesInRect_my(HRECT r, HBOOLEXPR filter, CODE actionFunc)
{
   funcname1 = "EnumDestructablesInRect";
   SpyJassLog(" Exec:EnumDestructablesInRect...");
   EnumDestructablesInRect_ptr(r, filter, actionFunc);
   SpyJassLog("[EnumDestructablesInRect] OK [r:%s, filter:%s, actionFunc:%s]\n",GetStrID(r).c_str( ), GetStrID(filter).c_str( ), GetStrID(actionFunc).c_str( ));
}
void _cdecl EnumItemsInRect_my(HRECT r, HBOOLEXPR filter, CODE actionFunc)
{
   funcname1 = "EnumItemsInRect";
   SpyJassLog(" Exec:EnumItemsInRect...");
   EnumItemsInRect_ptr(r, filter, actionFunc);
   SpyJassLog("[EnumItemsInRect] OK [r:%s, filter:%s, actionFunc:%s]\n",GetStrID(r).c_str( ), GetStrID(filter).c_str( ), GetStrID(actionFunc).c_str( ));
}
void _cdecl ExecuteFunc_my(CJassString funcName)
{
   funcname1 = "ExecuteFunc";
   SpyJassLog(" Exec:ExecuteFunc...");
   ExecuteFunc_ptr(funcName);
   SpyJassLog("[ExecuteFunc] OK [funcName:%s]\n",ReadJassStringNormal(funcName));
}
void _cdecl FillGuardPosts_my()
{
   funcname1 = "FillGuardPosts";
   SpyJassLog(" Exec:FillGuardPosts...");
   FillGuardPosts_ptr();
   SpyJassLog("[FillGuardPosts] OK []\n");
}
HFILTERFUNC _cdecl Filter_my(CODE func)
{
   funcname1 = "Filter";
   SpyJassLog(" Exec:Filter[func:%s]...",GetStrID(func).c_str( ));
   HFILTERFUNC returnvalue; 
   returnvalue = Filter_ptr(func);
   SpyJassLog("[Filter] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl FinishUbersplat_my(HUBERSPLAT Splat)
{
   funcname1 = "FinishUbersplat";
   SpyJassLog(" Exec:FinishUbersplat...");
   FinishUbersplat_ptr(Splat);
   SpyJassLog("[FinishUbersplat] OK [Splat:%s]\n",GetStrID(Splat).c_str( ));
}
HUNIT _cdecl FirstOfGroup_my(HGROUP Group)
{
   funcname1 = "FirstOfGroup";
   SpyJassLog(" Exec:FirstOfGroup[Group:%s]...",GetStrID(Group).c_str( ));
   HUNIT returnvalue; 
   returnvalue = FirstOfGroup_ptr(Group);
   SpyJassLog("[FirstOfGroup] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
void _cdecl FlashQuestDialogButton_my()
{
   funcname1 = "FlashQuestDialogButton";
   SpyJassLog(" Exec:FlashQuestDialogButton...");
   FlashQuestDialogButton_ptr();
   SpyJassLog("[FlashQuestDialogButton] OK []\n");
}
void _cdecl FlushChildHashtable_my(HHASHTABLE table, int parentKey)
{
   funcname1 = "FlushChildHashtable";
   SpyJassLog(" Exec:FlushChildHashtable...");
   FlushChildHashtable_ptr(table, parentKey);
   SpyJassLog("[FlushChildHashtable] OK [table:%s, parentKey:%s]\n",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ));
}
void _cdecl FlushGameCache_my(HGAMECACHE cache)
{
   funcname1 = "FlushGameCache";
   SpyJassLog(" Exec:FlushGameCache...");
   FlushGameCache_ptr(cache);
   SpyJassLog("[FlushGameCache] OK [cache:%s]\n",GetStrID(cache).c_str( ));
}
void _cdecl FlushParentHashtable_my(HHASHTABLE table)
{
   funcname1 = "FlushParentHashtable";
   SpyJassLog(" Exec:FlushParentHashtable...");
   FlushParentHashtable_ptr(table);
   SpyJassLog("[FlushParentHashtable] OK [table:%s]\n",GetStrID(table).c_str( ));
}
void _cdecl FlushStoredBoolean_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "FlushStoredBoolean";
   SpyJassLog(" Exec:FlushStoredBoolean...");
   FlushStoredBoolean_ptr(cache, missionKey, key);
   SpyJassLog("[FlushStoredBoolean] OK [cache:%s, missionKey:%s, key:%s]\n",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
}
void _cdecl FlushStoredInteger_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "FlushStoredInteger";
   SpyJassLog(" Exec:FlushStoredInteger...");
   FlushStoredInteger_ptr(cache, missionKey, key);
   SpyJassLog("[FlushStoredInteger] OK [cache:%s, missionKey:%s, key:%s]\n",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
}
void _cdecl FlushStoredMission_my(HGAMECACHE cache, CJassString missionKey)
{
   funcname1 = "FlushStoredMission";
   SpyJassLog(" Exec:FlushStoredMission...");
   FlushStoredMission_ptr(cache, missionKey);
   SpyJassLog("[FlushStoredMission] OK [cache:%s, missionKey:%s]\n",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey));
}
void _cdecl FlushStoredReal_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "FlushStoredReal";
   SpyJassLog(" Exec:FlushStoredReal...");
   FlushStoredReal_ptr(cache, missionKey, key);
   SpyJassLog("[FlushStoredReal] OK [cache:%s, missionKey:%s, key:%s]\n",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
}
void _cdecl FlushStoredString_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "FlushStoredString";
   SpyJassLog(" Exec:FlushStoredString...");
   FlushStoredString_ptr(cache, missionKey, key);
   SpyJassLog("[FlushStoredString] OK [cache:%s, missionKey:%s, key:%s]\n",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
}
void _cdecl FlushStoredUnit_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "FlushStoredUnit";
   SpyJassLog(" Exec:FlushStoredUnit...");
   FlushStoredUnit_ptr(cache, missionKey, key);
   SpyJassLog("[FlushStoredUnit] OK [cache:%s, missionKey:%s, key:%s]\n",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
}
void _cdecl FogEnable_my(BOOL enable)
{
   funcname1 = "FogEnable";
   SpyJassLog(" Exec:FogEnable...");
   FogEnable_ptr(enable);
   SpyJassLog("[FogEnable] OK [enable:%s]\n",BoolToStr(enable));
}
void _cdecl FogMaskEnable_my(BOOL enable)
{
   funcname1 = "FogMaskEnable";
   SpyJassLog(" Exec:FogMaskEnable...");
   FogMaskEnable_ptr(enable);
   SpyJassLog("[FogMaskEnable] OK [enable:%s]\n",BoolToStr(enable));
}
void _cdecl FogModifierStart_my(HFOGMODIFIER FogModifier)
{
   funcname1 = "FogModifierStart";
   SpyJassLog(" Exec:FogModifierStart...");
   FogModifierStart_ptr(FogModifier);
   SpyJassLog("[FogModifierStart] OK [FogModifier:%s]\n",GetStrID(FogModifier).c_str( ));
}
void _cdecl FogModifierStop_my(HFOGMODIFIER FogModifier)
{
   funcname1 = "FogModifierStop";
   SpyJassLog(" Exec:FogModifierStop...");
   FogModifierStop_ptr(FogModifier);
   SpyJassLog("[FogModifierStop] OK [FogModifier:%s]\n",GetStrID(FogModifier).c_str( ));
}
void _cdecl ForForce_my(HFORCE Force, CODE callback)
{
   funcname1 = "ForForce";
   SpyJassLog(" Exec:ForForce...");
   ForForce_ptr(Force, callback);
   SpyJassLog("[ForForce] OK [Force:%s, callback:%s]\n",GetStrID(Force).c_str( ), GetStrID(callback).c_str( ));
}
void _cdecl ForGroup_my(HGROUP Group, CODE callback)
{
   funcname1 = "ForGroup";
   SpyJassLog(" Exec:ForGroup...");
   ForGroup_ptr(Group, callback);
   SpyJassLog("[ForGroup] OK [Group:%s, callback:%s]\n",GetStrID(Group).c_str( ), GetStrID(callback).c_str( ));
}
void _cdecl ForceAddPlayer_my(HFORCE Force, HPLAYER player)
{
   funcname1 = "ForceAddPlayer";
   SpyJassLog(" Exec:ForceAddPlayer...");
   ForceAddPlayer_ptr(Force, player);
   SpyJassLog("[ForceAddPlayer] OK [Force:%s, player:%i]\n",GetStrID(Force).c_str( ), GetPlayerId_ptr(player));
}
void _cdecl ForceCampaignSelectScreen_my()
{
   funcname1 = "ForceCampaignSelectScreen";
   SpyJassLog(" Exec:ForceCampaignSelectScreen...");
   ForceCampaignSelectScreen_ptr();
   SpyJassLog("[ForceCampaignSelectScreen] OK []\n");
}
void _cdecl ForceCinematicSubtitles_my(BOOL flag)
{
   funcname1 = "ForceCinematicSubtitles";
   SpyJassLog(" Exec:ForceCinematicSubtitles...");
   ForceCinematicSubtitles_ptr(flag);
   SpyJassLog("[ForceCinematicSubtitles] OK [flag:%s]\n",BoolToStr(flag));
}
void _cdecl ForceClear_my(HFORCE Force)
{
   funcname1 = "ForceClear";
   SpyJassLog(" Exec:ForceClear...");
   ForceClear_ptr(Force);
   SpyJassLog("[ForceClear] OK [Force:%s]\n",GetStrID(Force).c_str( ));
}
void _cdecl ForceEnumAllies_my(HFORCE Force, HPLAYER player, HBOOLEXPR filter)
{
   funcname1 = "ForceEnumAllies";
   SpyJassLog(" Exec:ForceEnumAllies...");
   ForceEnumAllies_ptr(Force, player, filter);
   SpyJassLog("[ForceEnumAllies] OK [Force:%s, player:%i, filter:%s]\n",GetStrID(Force).c_str( ), GetPlayerId_ptr(player), GetStrID(filter).c_str( ));
}
void _cdecl ForceEnumEnemies_my(HFORCE Force, HPLAYER player, HBOOLEXPR filter)
{
   funcname1 = "ForceEnumEnemies";
   SpyJassLog(" Exec:ForceEnumEnemies...");
   ForceEnumEnemies_ptr(Force, player, filter);
   SpyJassLog("[ForceEnumEnemies] OK [Force:%s, player:%i, filter:%s]\n",GetStrID(Force).c_str( ), GetPlayerId_ptr(player), GetStrID(filter).c_str( ));
}
void _cdecl ForceEnumPlayers_my(HFORCE Force, HBOOLEXPR filter)
{
   funcname1 = "ForceEnumPlayers";
   SpyJassLog(" Exec:ForceEnumPlayers...");
   ForceEnumPlayers_ptr(Force, filter);
   SpyJassLog("[ForceEnumPlayers] OK [Force:%s, filter:%s]\n",GetStrID(Force).c_str( ), GetStrID(filter).c_str( ));
}
void _cdecl ForceEnumPlayersCounted_my(HFORCE Force, HBOOLEXPR filter, int countLimit)
{
   funcname1 = "ForceEnumPlayersCounted";
   SpyJassLog(" Exec:ForceEnumPlayersCounted...");
   ForceEnumPlayersCounted_ptr(Force, filter, countLimit);
   SpyJassLog("[ForceEnumPlayersCounted] OK [Force:%s, filter:%s, countLimit:%s]\n",GetStrID(Force).c_str( ), GetStrID(filter).c_str( ), GetStrID(countLimit).c_str( ));
}
void _cdecl ForcePlayerStartLocation_my(HPLAYER player, int startLocIndex)
{
   funcname1 = "ForcePlayerStartLocation";
   SpyJassLog(" Exec:ForcePlayerStartLocation...");
   ForcePlayerStartLocation_ptr(player, startLocIndex);
   SpyJassLog("[ForcePlayerStartLocation] OK [player:%i, startLocIndex:%s]\n",GetPlayerId_ptr(player), GetStrID(startLocIndex).c_str( ));
}
void _cdecl ForceQuestDialogUpdate_my()
{
   funcname1 = "ForceQuestDialogUpdate";
   SpyJassLog(" Exec:ForceQuestDialogUpdate...");
   ForceQuestDialogUpdate_ptr();
   SpyJassLog("[ForceQuestDialogUpdate] OK []\n");
}
void _cdecl ForceRemovePlayer_my(HFORCE Force, HPLAYER player)
{
   funcname1 = "ForceRemovePlayer";
   SpyJassLog(" Exec:ForceRemovePlayer...");
   ForceRemovePlayer_ptr(Force, player);
   SpyJassLog("[ForceRemovePlayer] OK [Force:%s, player:%i]\n",GetStrID(Force).c_str( ), GetPlayerId_ptr(player));
}
void _cdecl ForceUICancel_my()
{
   funcname1 = "ForceUICancel";
   SpyJassLog(" Exec:ForceUICancel...");
   ForceUICancel_ptr();
   SpyJassLog("[ForceUICancel] OK []\n");
}
void _cdecl ForceUIKey_my(CJassString key)
{
   funcname1 = "ForceUIKey";
   SpyJassLog(" Exec:ForceUIKey...");
   ForceUIKey_ptr(key);
   SpyJassLog("[ForceUIKey] OK [key:%s]\n",ReadJassStringNormal(key));
}
HAIDIFFICULTY _cdecl GetAIDifficulty_my(HPLAYER num)
{
   funcname1 = "GetAIDifficulty";
   SpyJassLog(" Exec:GetAIDifficulty[num:%i]...",GetPlayerId_ptr(num));
   HAIDIFFICULTY returnvalue; 
   returnvalue = GetAIDifficulty_ptr(num);
   SpyJassLog("[GetAIDifficulty] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
CJassStringSID _cdecl GetAbilityEffect_my(CJassString abilityString, HEFFECTTYPE t, int index)
{
   funcname1 = "GetAbilityEffect";
   SpyJassLog(" Exec:GetAbilityEffect[abilityString:%s, t:%s, index:%s]...",ReadJassStringNormal(abilityString), GetStrID(t).c_str( ), GetStrID(index).c_str( ));
   CJassStringSID returnvalue; 
   returnvalue = GetAbilityEffect_ptr(abilityString, t, index);
   SpyJassLog("[GetAbilityEffect] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
CJassStringSID _cdecl GetAbilityEffectById_my(int AbilID, HEFFECTTYPE t, int index)
{
   funcname1 = "GetAbilityEffectById";
   SpyJassLog(" Exec:GetAbilityEffectById[AbilID:%s, t:%s, index:%s]...",GetStrID(AbilID).c_str( ), GetStrID(t).c_str( ), GetStrID(index).c_str( ));
   CJassStringSID returnvalue; 
   returnvalue = GetAbilityEffectById_ptr(AbilID, t, index);
   SpyJassLog("[GetAbilityEffectById] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
CJassStringSID _cdecl GetAbilitySound_my(CJassString abilityString, HSOUNDTYPE t)
{
   funcname1 = "GetAbilitySound";
   SpyJassLog(" Exec:GetAbilitySound[abilityString:%s, t:%s]...",ReadJassStringNormal(abilityString), GetStrID(t).c_str( ));
   CJassStringSID returnvalue; 
   returnvalue = GetAbilitySound_ptr(abilityString, t);
   SpyJassLog("[GetAbilitySound] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
CJassStringSID _cdecl GetAbilitySoundById_my(int AbilID, HSOUNDTYPE t)
{
   funcname1 = "GetAbilitySoundById";
   SpyJassLog(" Exec:GetAbilitySoundById[AbilID:%s, t:%s]...",GetStrID(AbilID).c_str( ), GetStrID(t).c_str( ));
   CJassStringSID returnvalue; 
   returnvalue = GetAbilitySoundById_ptr(AbilID, t);
   SpyJassLog("[GetAbilitySoundById] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
int _cdecl GetAiPlayer_my()
{
   funcname1 = "GetAiPlayer";
   SpyJassLog(" Exec:GetAiPlayer[]...");
   int returnvalue; 
   returnvalue = GetAiPlayer_ptr();
   SpyJassLog("[GetAiPlayer] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetAllianceTarget_my()
{
   funcname1 = "GetAllianceTarget";
   SpyJassLog(" Exec:GetAllianceTarget[]...");
   HUNIT returnvalue; 
   returnvalue = GetAllianceTarget_ptr();
   SpyJassLog("[GetAllianceTarget] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
int _cdecl GetAllyColorFilterState_my()
{
   funcname1 = "GetAllyColorFilterState";
   SpyJassLog(" Exec:GetAllyColorFilterState[]...");
   int returnvalue; 
   returnvalue = GetAllyColorFilterState_ptr();
   SpyJassLog("[GetAllyColorFilterState] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetAttacker_my()
{
   funcname1 = "GetAttacker";
   SpyJassLog(" Exec:GetAttacker[]...");
   HUNIT returnvalue; 
   returnvalue = GetAttacker_ptr();
   SpyJassLog("[GetAttacker] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetBuilding_my(HPLAYER arg1)
{
   funcname1 = "GetBuilding";
   SpyJassLog(" Exec:GetBuilding[arg1:%i]...",GetPlayerId_ptr(arg1));
   HUNIT returnvalue; 
   returnvalue = GetBuilding_ptr(arg1);
   SpyJassLog("[GetBuilding] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetBuyingUnit_my()
{
   funcname1 = "GetBuyingUnit";
   SpyJassLog(" Exec:GetBuyingUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetBuyingUnit_ptr();
   SpyJassLog("[GetBuyingUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetCameraBoundMaxX_my()
{
   funcname1 = "GetCameraBoundMaxX";
   SpyJassLog(" Exec:GetCameraBoundMaxX[]...");
   DWFP returnvalue; 
   returnvalue = GetCameraBoundMaxX_ptr();
   SpyJassLog("[GetCameraBoundMaxX] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetCameraBoundMaxY_my()
{
   funcname1 = "GetCameraBoundMaxY";
   SpyJassLog(" Exec:GetCameraBoundMaxY[]...");
   DWFP returnvalue; 
   returnvalue = GetCameraBoundMaxY_ptr();
   SpyJassLog("[GetCameraBoundMaxY] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetCameraBoundMinX_my()
{
   funcname1 = "GetCameraBoundMinX";
   SpyJassLog(" Exec:GetCameraBoundMinX[]...");
   DWFP returnvalue; 
   returnvalue = GetCameraBoundMinX_ptr();
   SpyJassLog("[GetCameraBoundMinX] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetCameraBoundMinY_my()
{
   funcname1 = "GetCameraBoundMinY";
   SpyJassLog(" Exec:GetCameraBoundMinY[]...");
   DWFP returnvalue; 
   returnvalue = GetCameraBoundMinY_ptr();
   SpyJassLog("[GetCameraBoundMinY] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
HLOCATION _cdecl GetCameraEyePositionLoc_my()
{
   funcname1 = "GetCameraEyePositionLoc";
   SpyJassLog(" Exec:GetCameraEyePositionLoc[]...");
   HLOCATION returnvalue; 
   returnvalue = GetCameraEyePositionLoc_ptr();
   SpyJassLog("[GetCameraEyePositionLoc] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetCameraEyePositionX_my()
{
   funcname1 = "GetCameraEyePositionX";
   SpyJassLog(" Exec:GetCameraEyePositionX[]...");
   DWFP returnvalue; 
   returnvalue = GetCameraEyePositionX_ptr();
   SpyJassLog("[GetCameraEyePositionX] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetCameraEyePositionY_my()
{
   funcname1 = "GetCameraEyePositionY";
   SpyJassLog(" Exec:GetCameraEyePositionY[]...");
   DWFP returnvalue; 
   returnvalue = GetCameraEyePositionY_ptr();
   SpyJassLog("[GetCameraEyePositionY] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetCameraEyePositionZ_my()
{
   funcname1 = "GetCameraEyePositionZ";
   SpyJassLog(" Exec:GetCameraEyePositionZ[]...");
   DWFP returnvalue; 
   returnvalue = GetCameraEyePositionZ_ptr();
   SpyJassLog("[GetCameraEyePositionZ] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetCameraField_my(HCAMERAFIELD field)
{
   funcname1 = "GetCameraField";
   SpyJassLog(" Exec:GetCameraField[field:%s]...",GetStrID(field).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetCameraField_ptr(field);
   SpyJassLog("[GetCameraField] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetCameraMargin_my(int Margin)
{
   funcname1 = "GetCameraMargin";
   SpyJassLog(" Exec:GetCameraMargin[Margin:%s]...",GetStrID(Margin).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetCameraMargin_ptr(Margin);
   SpyJassLog("[GetCameraMargin] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
HLOCATION _cdecl GetCameraTargetPositionLoc_my()
{
   funcname1 = "GetCameraTargetPositionLoc";
   SpyJassLog(" Exec:GetCameraTargetPositionLoc[]...");
   HLOCATION returnvalue; 
   returnvalue = GetCameraTargetPositionLoc_ptr();
   SpyJassLog("[GetCameraTargetPositionLoc] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetCameraTargetPositionX_my()
{
   funcname1 = "GetCameraTargetPositionX";
   SpyJassLog(" Exec:GetCameraTargetPositionX[]...");
   DWFP returnvalue; 
   returnvalue = GetCameraTargetPositionX_ptr();
   SpyJassLog("[GetCameraTargetPositionX] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetCameraTargetPositionY_my()
{
   funcname1 = "GetCameraTargetPositionY";
   SpyJassLog(" Exec:GetCameraTargetPositionY[]...");
   DWFP returnvalue; 
   returnvalue = GetCameraTargetPositionY_ptr();
   SpyJassLog("[GetCameraTargetPositionY] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetCameraTargetPositionZ_my()
{
   funcname1 = "GetCameraTargetPositionZ";
   SpyJassLog(" Exec:GetCameraTargetPositionZ[]...");
   DWFP returnvalue; 
   returnvalue = GetCameraTargetPositionZ_ptr();
   SpyJassLog("[GetCameraTargetPositionZ] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
HUNIT _cdecl GetCancelledStructure_my()
{
   funcname1 = "GetCancelledStructure";
   SpyJassLog(" Exec:GetCancelledStructure[]...");
   HUNIT returnvalue; 
   returnvalue = GetCancelledStructure_ptr();
   SpyJassLog("[GetCancelledStructure] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetChangingUnit_my()
{
   funcname1 = "GetChangingUnit";
   SpyJassLog(" Exec:GetChangingUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetChangingUnit_ptr();
   SpyJassLog("[GetChangingUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HPLAYER _cdecl GetChangingUnitPrevOwner_my()
{
   funcname1 = "GetChangingUnitPrevOwner";
   SpyJassLog(" Exec:GetChangingUnitPrevOwner[]...");
   HPLAYER returnvalue; 
   returnvalue = GetChangingUnitPrevOwner_ptr();
   SpyJassLog("[GetChangingUnitPrevOwner] OK [%i]\n",GetPlayerId_ptr(returnvalue));
   return returnvalue;
}
HBUTTON _cdecl GetClickedButton_my()
{
   funcname1 = "GetClickedButton";
   SpyJassLog(" Exec:GetClickedButton[]...");
   HBUTTON returnvalue; 
   returnvalue = GetClickedButton_ptr();
   SpyJassLog("[GetClickedButton] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HDIALOG _cdecl GetClickedDialog_my()
{
   funcname1 = "GetClickedDialog";
   SpyJassLog(" Exec:GetClickedDialog[]...");
   HDIALOG returnvalue; 
   returnvalue = GetClickedDialog_ptr();
   SpyJassLog("[GetClickedDialog] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetConstructedStructure_my()
{
   funcname1 = "GetConstructedStructure";
   SpyJassLog(" Exec:GetConstructedStructure[]...");
   HUNIT returnvalue; 
   returnvalue = GetConstructedStructure_ptr();
   SpyJassLog("[GetConstructedStructure] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetConstructingStructure_my()
{
   funcname1 = "GetConstructingStructure";
   SpyJassLog(" Exec:GetConstructingStructure[]...");
   HUNIT returnvalue; 
   returnvalue = GetConstructingStructure_ptr();
   SpyJassLog("[GetConstructingStructure] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HMAPDENSITY _cdecl GetCreatureDensity_my()
{
   funcname1 = "GetCreatureDensity";
   SpyJassLog(" Exec:GetCreatureDensity[]...");
   HMAPDENSITY returnvalue; 
   returnvalue = GetCreatureDensity_ptr();
   SpyJassLog("[GetCreatureDensity] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetCreepCamp_my(int arg1, int arg2, BOOL arg3)
{
   funcname1 = "GetCreepCamp";
   SpyJassLog(" Exec:GetCreepCamp[arg1:%s, arg2:%s, arg3:%s]...",GetStrID(arg1).c_str( ), GetStrID(arg2).c_str( ), BoolToStr(arg3));
   HUNIT returnvalue; 
   returnvalue = GetCreepCamp_ptr(arg1, arg2, arg3);
   SpyJassLog("[GetCreepCamp] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
BOOL _cdecl GetCreepCampFilterState_my()
{
   funcname1 = "GetCreepCampFilterState";
   SpyJassLog(" Exec:GetCreepCampFilterState[]...");
   BOOL returnvalue; 
   returnvalue = GetCreepCampFilterState_ptr();
   SpyJassLog("[GetCreepCampFilterState] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl GetCustomCampaignButtonVisible_my(int Button)
{
   funcname1 = "GetCustomCampaignButtonVisible";
   SpyJassLog(" Exec:GetCustomCampaignButtonVisible[Button:%s]...",GetStrID(Button).c_str( ));
   BOOL returnvalue; 
   returnvalue = GetCustomCampaignButtonVisible_ptr(Button);
   SpyJassLog("[GetCustomCampaignButtonVisible] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
HUNIT _cdecl GetDecayingUnit_my()
{
   funcname1 = "GetDecayingUnit";
   SpyJassLog(" Exec:GetDecayingUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetDecayingUnit_ptr();
   SpyJassLog("[GetDecayingUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HGAMEDIFFICULTY _cdecl GetDefaultDifficulty_my()
{
   funcname1 = "GetDefaultDifficulty";
   SpyJassLog(" Exec:GetDefaultDifficulty[]...");
   HGAMEDIFFICULTY returnvalue; 
   returnvalue = GetDefaultDifficulty_ptr();
   SpyJassLog("[GetDefaultDifficulty] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetDestructableLife_my(HDESTRUCTABLE d)
{
   funcname1 = "GetDestructableLife";
   SpyJassLog(" Exec:GetDestructableLife[d:%s]...",GetStrID(d).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetDestructableLife_ptr(d);
   SpyJassLog("[GetDestructableLife] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetDestructableMaxLife_my(HDESTRUCTABLE d)
{
   funcname1 = "GetDestructableMaxLife";
   SpyJassLog(" Exec:GetDestructableMaxLife[d:%s]...",GetStrID(d).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetDestructableMaxLife_ptr(d);
   SpyJassLog("[GetDestructableMaxLife] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
CJassStringSID _cdecl GetDestructableName_my(HDESTRUCTABLE d)
{
   funcname1 = "GetDestructableName";
   SpyJassLog(" Exec:GetDestructableName[d:%s]...",GetStrID(d).c_str( ));
   CJassStringSID returnvalue; 
   returnvalue = GetDestructableName_ptr(d);
   SpyJassLog("[GetDestructableName] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetDestructableOccluderHeight_my(HDESTRUCTABLE d)
{
   funcname1 = "GetDestructableOccluderHeight";
   SpyJassLog(" Exec:GetDestructableOccluderHeight[d:%s]...",GetStrID(d).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetDestructableOccluderHeight_ptr(d);
   SpyJassLog("[GetDestructableOccluderHeight] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
int _cdecl GetDestructableTypeId_my(HDESTRUCTABLE d)
{
   funcname1 = "GetDestructableTypeId";
   SpyJassLog(" Exec:GetDestructableTypeId[d:%s]...",GetStrID(d).c_str( ));
   int returnvalue; 
   returnvalue = GetDestructableTypeId_ptr(d);
   SpyJassLog("[GetDestructableTypeId] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetDestructableX_my(HDESTRUCTABLE d)
{
   funcname1 = "GetDestructableX";
   SpyJassLog(" Exec:GetDestructableX[d:%s]...",GetStrID(d).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetDestructableX_ptr(d);
   SpyJassLog("[GetDestructableX] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetDestructableY_my(HDESTRUCTABLE d)
{
   funcname1 = "GetDestructableY";
   SpyJassLog(" Exec:GetDestructableY[d:%s]...",GetStrID(d).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetDestructableY_ptr(d);
   SpyJassLog("[GetDestructableY] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
HUNIT _cdecl GetDetectedUnit_my()
{
   funcname1 = "GetDetectedUnit";
   SpyJassLog(" Exec:GetDetectedUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetDetectedUnit_ptr();
   SpyJassLog("[GetDetectedUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetDyingUnit_my()
{
   funcname1 = "GetDyingUnit";
   SpyJassLog(" Exec:GetDyingUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetDyingUnit_ptr();
   SpyJassLog("[GetDyingUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetEnemyBase_my()
{
   funcname1 = "GetEnemyBase";
   SpyJassLog(" Exec:GetEnemyBase[]...");
   HUNIT returnvalue; 
   returnvalue = GetEnemyBase_ptr();
   SpyJassLog("[GetEnemyBase] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetEnemyExpansion_my()
{
   funcname1 = "GetEnemyExpansion";
   SpyJassLog(" Exec:GetEnemyExpansion[]...");
   HUNIT returnvalue; 
   returnvalue = GetEnemyExpansion_ptr();
   SpyJassLog("[GetEnemyExpansion] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
int _cdecl GetEnemyPower_my()
{
   funcname1 = "GetEnemyPower";
   SpyJassLog(" Exec:GetEnemyPower[]...");
   int returnvalue; 
   returnvalue = GetEnemyPower_ptr();
   SpyJassLog("[GetEnemyPower] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetEnteringUnit_my()
{
   funcname1 = "GetEnteringUnit";
   SpyJassLog(" Exec:GetEnteringUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetEnteringUnit_ptr();
   SpyJassLog("[GetEnteringUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HDESTRUCTABLE _cdecl GetEnumDestructable_my()
{
   funcname1 = "GetEnumDestructable";
   SpyJassLog(" Exec:GetEnumDestructable[]...");
   HDESTRUCTABLE returnvalue; 
   returnvalue = GetEnumDestructable_ptr();
   SpyJassLog("[GetEnumDestructable] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HITEM _cdecl GetEnumItem_my()
{
   funcname1 = "GetEnumItem";
   SpyJassLog(" Exec:GetEnumItem[]...");
   HITEM returnvalue; 
   returnvalue = GetEnumItem_ptr();
   SpyJassLog("[GetEnumItem] OK [%s]\n",GetItemHID(returnvalue).c_str( ));
   return returnvalue;
}
HPLAYER _cdecl GetEnumPlayer_my()
{
   funcname1 = "GetEnumPlayer";
   SpyJassLog(" Exec:GetEnumPlayer[]...");
   HPLAYER returnvalue; 
   returnvalue = GetEnumPlayer_ptr();
   SpyJassLog("[GetEnumPlayer] OK [%i]\n",GetPlayerId_ptr(returnvalue));
   return returnvalue;
}
HUNIT _cdecl GetEnumUnit_my()
{
   funcname1 = "GetEnumUnit";
   SpyJassLog(" Exec:GetEnumUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetEnumUnit_ptr();
   SpyJassLog("[GetEnumUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetEventDamage_my()
{
   funcname1 = "GetEventDamage";
   SpyJassLog(" Exec:GetEventDamage[]...");
   DWFP returnvalue; 
   returnvalue = GetEventDamage_ptr();
   SpyJassLog("[GetEventDamage] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
HUNIT _cdecl GetEventDamageSource_my()
{
   funcname1 = "GetEventDamageSource";
   SpyJassLog(" Exec:GetEventDamageSource[]...");
   HUNIT returnvalue; 
   returnvalue = GetEventDamageSource_ptr();
   SpyJassLog("[GetEventDamageSource] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HPLAYER _cdecl GetEventDetectingPlayer_my()
{
   funcname1 = "GetEventDetectingPlayer";
   SpyJassLog(" Exec:GetEventDetectingPlayer[]...");
   HPLAYER returnvalue; 
   returnvalue = GetEventDetectingPlayer_ptr();
   SpyJassLog("[GetEventDetectingPlayer] OK [%i]\n",GetPlayerId_ptr(returnvalue));
   return returnvalue;
}
HGAMESTATE _cdecl GetEventGameState_my()
{
   funcname1 = "GetEventGameState";
   SpyJassLog(" Exec:GetEventGameState[]...");
   HGAMESTATE returnvalue; 
   returnvalue = GetEventGameState_ptr();
   SpyJassLog("[GetEventGameState] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
CJassStringSID _cdecl GetEventPlayerChatString_my()
{
   funcname1 = "GetEventPlayerChatString";
   SpyJassLog(" Exec:GetEventPlayerChatString[]...");
   CJassStringSID returnvalue; 
   returnvalue = GetEventPlayerChatString_ptr();
   SpyJassLog("[GetEventPlayerChatString] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
CJassStringSID _cdecl GetEventPlayerChatStringMatched_my()
{
   funcname1 = "GetEventPlayerChatStringMatched";
   SpyJassLog(" Exec:GetEventPlayerChatStringMatched[]...");
   CJassStringSID returnvalue; 
   returnvalue = GetEventPlayerChatStringMatched_ptr();
   SpyJassLog("[GetEventPlayerChatStringMatched] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
HPLAYERSTATE _cdecl GetEventPlayerState_my()
{
   funcname1 = "GetEventPlayerState";
   SpyJassLog(" Exec:GetEventPlayerState[]...");
   HPLAYERSTATE returnvalue; 
   returnvalue = GetEventPlayerState_ptr();
   SpyJassLog("[GetEventPlayerState] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetEventTargetUnit_my()
{
   funcname1 = "GetEventTargetUnit";
   SpyJassLog(" Exec:GetEventTargetUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetEventTargetUnit_ptr();
   SpyJassLog("[GetEventTargetUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNITSTATE _cdecl GetEventUnitState_my()
{
   funcname1 = "GetEventUnitState";
   SpyJassLog(" Exec:GetEventUnitState[]...");
   HUNITSTATE returnvalue; 
   returnvalue = GetEventUnitState_ptr();
   SpyJassLog("[GetEventUnitState] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetExpansionFoe_my()
{
   funcname1 = "GetExpansionFoe";
   SpyJassLog(" Exec:GetExpansionFoe[]...");
   HUNIT returnvalue; 
   returnvalue = GetExpansionFoe_ptr();
   SpyJassLog("[GetExpansionFoe] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetExpansionPeon_my()
{
   funcname1 = "GetExpansionPeon";
   SpyJassLog(" Exec:GetExpansionPeon[]...");
   HUNIT returnvalue; 
   returnvalue = GetExpansionPeon_ptr();
   SpyJassLog("[GetExpansionPeon] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
int _cdecl GetExpansionX_my()
{
   funcname1 = "GetExpansionX";
   SpyJassLog(" Exec:GetExpansionX[]...");
   int returnvalue; 
   returnvalue = GetExpansionX_ptr();
   SpyJassLog("[GetExpansionX] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetExpansionY_my()
{
   funcname1 = "GetExpansionY";
   SpyJassLog(" Exec:GetExpansionY[]...");
   int returnvalue; 
   returnvalue = GetExpansionY_ptr();
   SpyJassLog("[GetExpansionY] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTIMER _cdecl GetExpiredTimer_my()
{
   funcname1 = "GetExpiredTimer";
   SpyJassLog(" Exec:GetExpiredTimer[]...");
   HTIMER returnvalue; 
   returnvalue = GetExpiredTimer_ptr();
   SpyJassLog("[GetExpiredTimer] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HDESTRUCTABLE _cdecl GetFilterDestructable_my()
{
   funcname1 = "GetFilterDestructable";
   SpyJassLog(" Exec:GetFilterDestructable[]...");
   HDESTRUCTABLE returnvalue; 
   returnvalue = GetFilterDestructable_ptr();
   SpyJassLog("[GetFilterDestructable] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HITEM _cdecl GetFilterItem_my()
{
   funcname1 = "GetFilterItem";
   SpyJassLog(" Exec:GetFilterItem[]...");
   HITEM returnvalue; 
   returnvalue = GetFilterItem_ptr();
   SpyJassLog("[GetFilterItem] OK [%s]\n",GetItemHID(returnvalue).c_str( ));
   return returnvalue;
}
HPLAYER _cdecl GetFilterPlayer_my()
{
   funcname1 = "GetFilterPlayer";
   SpyJassLog(" Exec:GetFilterPlayer[]...");
   HPLAYER returnvalue; 
   returnvalue = GetFilterPlayer_ptr();
   SpyJassLog("[GetFilterPlayer] OK [%i]\n",GetPlayerId_ptr(returnvalue));
   return returnvalue;
}
HUNIT _cdecl GetFilterUnit_my()
{
   funcname1 = "GetFilterUnit";
   SpyJassLog(" Exec:GetFilterUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetFilterUnit_ptr();
   SpyJassLog("[GetFilterUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetFloatGameState_my(HFGAMESTATE FloatGameState)
{
   funcname1 = "GetFloatGameState";
   SpyJassLog(" Exec:GetFloatGameState[FloatGameState:%s]...",GetStrID(FloatGameState).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetFloatGameState_ptr(FloatGameState);
   SpyJassLog("[GetFloatGameState] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
int _cdecl GetFoodMade_my(int unitId)
{
   funcname1 = "GetFoodMade";
   SpyJassLog(" Exec:GetFoodMade[unitId:%s]...",GetStrID(unitId).c_str( ));
   int returnvalue; 
   returnvalue = GetFoodMade_ptr(unitId);
   SpyJassLog("[GetFoodMade] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetFoodUsed_my(int unitId)
{
   funcname1 = "GetFoodUsed";
   SpyJassLog(" Exec:GetFoodUsed[unitId:%s]...",GetStrID(unitId).c_str( ));
   int returnvalue; 
   returnvalue = GetFoodUsed_ptr(unitId);
   SpyJassLog("[GetFoodUsed] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HGAMEDIFFICULTY _cdecl GetGameDifficulty_my()
{
   funcname1 = "GetGameDifficulty";
   SpyJassLog(" Exec:GetGameDifficulty[]...");
   HGAMEDIFFICULTY returnvalue; 
   returnvalue = GetGameDifficulty_ptr();
   SpyJassLog("[GetGameDifficulty] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HPLACEMENT _cdecl GetGamePlacement_my()
{
   funcname1 = "GetGamePlacement";
   SpyJassLog(" Exec:GetGamePlacement[]...");
   HPLACEMENT returnvalue; 
   returnvalue = GetGamePlacement_ptr();
   SpyJassLog("[GetGamePlacement] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HGAMESPEED _cdecl GetGameSpeed_my()
{
   funcname1 = "GetGameSpeed";
   SpyJassLog(" Exec:GetGameSpeed[]...");
   HGAMESPEED returnvalue; 
   returnvalue = GetGameSpeed_ptr();
   SpyJassLog("[GetGameSpeed] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HGAMETYPE _cdecl GetGameTypeSelected_my()
{
   funcname1 = "GetGameTypeSelected";
   SpyJassLog(" Exec:GetGameTypeSelected[]...");
   HGAMETYPE returnvalue; 
   returnvalue = GetGameTypeSelected_ptr();
   SpyJassLog("[GetGameTypeSelected] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetGoldOwned_my()
{
   funcname1 = "GetGoldOwned";
   SpyJassLog(" Exec:GetGoldOwned[]...");
   int returnvalue; 
   returnvalue = GetGoldOwned_ptr();
   SpyJassLog("[GetGoldOwned] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetHandleId_my(HHANDLE h)
{
   funcname1 = "GetHandleId";
   SpyJassLog(" Exec:GetHandleId[h:%s]...",GetStrID(h).c_str( ));
   int returnvalue; 
   returnvalue = GetHandleId_ptr(h);
   SpyJassLog("[GetHandleId] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetHeroAgi_my(HUNIT hero, BOOL includeBonuses)
{
   funcname1 = "GetHeroAgi";
   SpyJassLog(" Exec:GetHeroAgi[hero:%s, includeBonuses:%s]...",GetUnitHID(hero).c_str( ), BoolToStr(includeBonuses));
   int returnvalue; 
   returnvalue = GetHeroAgi_ptr(hero, includeBonuses);
   SpyJassLog("[GetHeroAgi] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetHeroId_my()
{
   funcname1 = "GetHeroId";
   SpyJassLog(" Exec:GetHeroId[]...");
   int returnvalue; 
   returnvalue = GetHeroId_ptr();
   SpyJassLog("[GetHeroId] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetHeroInt_my(HUNIT hero, BOOL includeBonuses)
{
   funcname1 = "GetHeroInt";
   SpyJassLog(" Exec:GetHeroInt[hero:%s, includeBonuses:%s]...",GetUnitHID(hero).c_str( ), BoolToStr(includeBonuses));
   int returnvalue; 
   returnvalue = GetHeroInt_ptr(hero, includeBonuses);
   SpyJassLog("[GetHeroInt] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetHeroLevel_my(HUNIT hero)
{
   funcname1 = "GetHeroLevel";
   SpyJassLog(" Exec:GetHeroLevel[hero:%s]...",GetUnitHID(hero).c_str( ));
   int returnvalue; 
   returnvalue = GetHeroLevel_ptr(hero);
   SpyJassLog("[GetHeroLevel] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetHeroLevelAI_my()
{
   funcname1 = "GetHeroLevelAI";
   SpyJassLog(" Exec:GetHeroLevelAI[]...");
   int returnvalue; 
   returnvalue = GetHeroLevelAI_ptr();
   SpyJassLog("[GetHeroLevelAI] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
CJassStringSID _cdecl GetHeroProperName_my(HUNIT hero)
{
   funcname1 = "GetHeroProperName";
   SpyJassLog(" Exec:GetHeroProperName[hero:%s]...",GetUnitHID(hero).c_str( ));
   CJassStringSID returnvalue; 
   returnvalue = GetHeroProperName_ptr(hero);
   SpyJassLog("[GetHeroProperName] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
int _cdecl GetHeroSkillPoints_my(HUNIT hero)
{
   funcname1 = "GetHeroSkillPoints";
   SpyJassLog(" Exec:GetHeroSkillPoints[hero:%s]...",GetUnitHID(hero).c_str( ));
   int returnvalue; 
   returnvalue = GetHeroSkillPoints_ptr(hero);
   SpyJassLog("[GetHeroSkillPoints] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetHeroStr_my(HUNIT hero, BOOL includeBonuses)
{
   funcname1 = "GetHeroStr";
   SpyJassLog(" Exec:GetHeroStr[hero:%s, includeBonuses:%s]...",GetUnitHID(hero).c_str( ), BoolToStr(includeBonuses));
   int returnvalue; 
   returnvalue = GetHeroStr_ptr(hero, includeBonuses);
   SpyJassLog("[GetHeroStr] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetHeroXP_my(HUNIT hero)
{
   funcname1 = "GetHeroXP";
   SpyJassLog(" Exec:GetHeroXP[hero:%s]...",GetUnitHID(hero).c_str( ));
   int returnvalue; 
   returnvalue = GetHeroXP_ptr(hero);
   SpyJassLog("[GetHeroXP] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetIntegerGameState_my(HIGAMESTATE IntegerGameState)
{
   funcname1 = "GetIntegerGameState";
   SpyJassLog(" Exec:GetIntegerGameState[IntegerGameState:%s]...",GetStrID(IntegerGameState).c_str( ));
   int returnvalue; 
   returnvalue = GetIntegerGameState_ptr(IntegerGameState);
   SpyJassLog("[GetIntegerGameState] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetIssuedOrderId_my()
{
   funcname1 = "GetIssuedOrderId";
   SpyJassLog(" Exec:GetIssuedOrderId[]...");
   int returnvalue; 
   returnvalue = GetIssuedOrderId_ptr();
   SpyJassLog("[GetIssuedOrderId] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetItemCharges_my(HITEM item)
{
   funcname1 = "GetItemCharges";
   SpyJassLog(" Exec:GetItemCharges[item:%s]...",GetItemHID(item).c_str( ));
   int returnvalue; 
   returnvalue = GetItemCharges_ptr(item);
   SpyJassLog("[GetItemCharges] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetItemLevel_my(HITEM item)
{
   funcname1 = "GetItemLevel";
   SpyJassLog(" Exec:GetItemLevel[item:%s]...",GetItemHID(item).c_str( ));
   int returnvalue; 
   returnvalue = GetItemLevel_ptr(item);
   SpyJassLog("[GetItemLevel] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
CJassStringSID _cdecl GetItemName_my(HITEM item)
{
   funcname1 = "GetItemName";
   SpyJassLog(" Exec:GetItemName[item:%s]...",GetItemHID(item).c_str( ));
   CJassStringSID returnvalue; 
   returnvalue = GetItemName_ptr(item);
   SpyJassLog("[GetItemName] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
HPLAYER _cdecl GetItemPlayer_my(HITEM item)
{
   funcname1 = "GetItemPlayer";
   SpyJassLog(" Exec:GetItemPlayer[item:%s]...",GetItemHID(item).c_str( ));
   HPLAYER returnvalue; 
   returnvalue = GetItemPlayer_ptr(item);
   SpyJassLog("[GetItemPlayer] OK [%i]\n",GetPlayerId_ptr(returnvalue));
   return returnvalue;
}
HITEMTYPE _cdecl GetItemType_my(HITEM item)
{
   funcname1 = "GetItemType";
   SpyJassLog(" Exec:GetItemType[item:%s]...",GetItemHID(item).c_str( ));
   HITEMTYPE returnvalue; 
   returnvalue = GetItemType_ptr(item);
   SpyJassLog("[GetItemType] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetItemTypeId_my(HITEM i)
{
   funcname1 = "GetItemTypeId";
   SpyJassLog(" Exec:GetItemTypeId[i:%s]...",GetItemHID(i).c_str( ));
   int returnvalue; 
   returnvalue = GetItemTypeId_ptr(i);
   SpyJassLog("[GetItemTypeId] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetItemUserData_my(HITEM item)
{
   funcname1 = "GetItemUserData";
   SpyJassLog(" Exec:GetItemUserData[item:%s]...",GetItemHID(item).c_str( ));
   int returnvalue; 
   returnvalue = GetItemUserData_ptr(item);
   SpyJassLog("[GetItemUserData] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetItemX_my(HITEM i)
{
   funcname1 = "GetItemX";
   SpyJassLog(" Exec:GetItemX[i:%s]...",GetItemHID(i).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetItemX_ptr(i);
   SpyJassLog("[GetItemX] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetItemY_my(HITEM i)
{
   funcname1 = "GetItemY";
   SpyJassLog(" Exec:GetItemY[i:%s]...",GetItemHID(i).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetItemY_ptr(i);
   SpyJassLog("[GetItemY] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
HUNIT _cdecl GetKillingUnit_my()
{
   funcname1 = "GetKillingUnit";
   SpyJassLog(" Exec:GetKillingUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetKillingUnit_ptr();
   SpyJassLog("[GetKillingUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
int _cdecl GetLastCommand_my()
{
   funcname1 = "GetLastCommand";
   SpyJassLog(" Exec:GetLastCommand[]...");
   int returnvalue; 
   returnvalue = GetLastCommand_ptr();
   SpyJassLog("[GetLastCommand] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetLastData_my()
{
   funcname1 = "GetLastData";
   SpyJassLog(" Exec:GetLastData[]...");
   int returnvalue; 
   returnvalue = GetLastData_ptr();
   SpyJassLog("[GetLastData] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetLearnedSkill_my()
{
   funcname1 = "GetLearnedSkill";
   SpyJassLog(" Exec:GetLearnedSkill[]...");
   int returnvalue; 
   returnvalue = GetLearnedSkill_ptr();
   SpyJassLog("[GetLearnedSkill] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetLearnedSkillLevel_my()
{
   funcname1 = "GetLearnedSkillLevel";
   SpyJassLog(" Exec:GetLearnedSkillLevel[]...");
   int returnvalue; 
   returnvalue = GetLearnedSkillLevel_ptr();
   SpyJassLog("[GetLearnedSkillLevel] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetLearningUnit_my()
{
   funcname1 = "GetLearningUnit";
   SpyJassLog(" Exec:GetLearningUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetLearningUnit_ptr();
   SpyJassLog("[GetLearningUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetLeavingUnit_my()
{
   funcname1 = "GetLeavingUnit";
   SpyJassLog(" Exec:GetLeavingUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetLeavingUnit_ptr();
   SpyJassLog("[GetLeavingUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetLevelingUnit_my()
{
   funcname1 = "GetLevelingUnit";
   SpyJassLog(" Exec:GetLevelingUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetLevelingUnit_ptr();
   SpyJassLog("[GetLevelingUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetLightningColorA_my(HLIGHTNING Bolt)
{
   funcname1 = "GetLightningColorA";
   SpyJassLog(" Exec:GetLightningColorA[Bolt:%s]...",GetStrID(Bolt).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetLightningColorA_ptr(Bolt);
   SpyJassLog("[GetLightningColorA] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetLightningColorB_my(HLIGHTNING Bolt)
{
   funcname1 = "GetLightningColorB";
   SpyJassLog(" Exec:GetLightningColorB[Bolt:%s]...",GetStrID(Bolt).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetLightningColorB_ptr(Bolt);
   SpyJassLog("[GetLightningColorB] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetLightningColorG_my(HLIGHTNING Bolt)
{
   funcname1 = "GetLightningColorG";
   SpyJassLog(" Exec:GetLightningColorG[Bolt:%s]...",GetStrID(Bolt).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetLightningColorG_ptr(Bolt);
   SpyJassLog("[GetLightningColorG] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetLightningColorR_my(HLIGHTNING Bolt)
{
   funcname1 = "GetLightningColorR";
   SpyJassLog(" Exec:GetLightningColorR[Bolt:%s]...",GetStrID(Bolt).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetLightningColorR_ptr(Bolt);
   SpyJassLog("[GetLightningColorR] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
HUNIT _cdecl GetLoadedUnit_my()
{
   funcname1 = "GetLoadedUnit";
   SpyJassLog(" Exec:GetLoadedUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetLoadedUnit_ptr();
   SpyJassLog("[GetLoadedUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HPLAYER _cdecl GetLocalPlayer_my()
{
   funcname1 = "GetLocalPlayer";
   SpyJassLog(" Exec:GetLocalPlayer[]...");
   HPLAYER returnvalue; 
   returnvalue = GetLocalPlayer_ptr();
   SpyJassLog("[GetLocalPlayer] OK [%i]\n",GetPlayerId_ptr(returnvalue));
   return returnvalue;
}
int _cdecl GetLocalizedHotkey_my(CJassString source)
{
   funcname1 = "GetLocalizedHotkey";
   SpyJassLog(" Exec:GetLocalizedHotkey[source:%s]...",ReadJassStringNormal(source));
   int returnvalue; 
   returnvalue = GetLocalizedHotkey_ptr(source);
   SpyJassLog("[GetLocalizedHotkey] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
CJassStringSID _cdecl GetLocalizedString_my(CJassString source)
{
   funcname1 = "GetLocalizedString";
   SpyJassLog(" Exec:GetLocalizedString[source:%s]...",ReadJassStringNormal(source));
   CJassStringSID returnvalue; 
   returnvalue = GetLocalizedString_ptr(source);
   SpyJassLog("[GetLocalizedString] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetLocationX_my(HLOCATION Location)
{
   funcname1 = "GetLocationX";
   SpyJassLog(" Exec:GetLocationX[Location:%s]...",GetStrID(Location).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetLocationX_ptr(Location);
   SpyJassLog("[GetLocationX] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetLocationY_my(HLOCATION Location)
{
   funcname1 = "GetLocationY";
   SpyJassLog(" Exec:GetLocationY[Location:%s]...",GetStrID(Location).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetLocationY_ptr(Location);
   SpyJassLog("[GetLocationY] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetLocationZ_my(HLOCATION Location)
{
   funcname1 = "GetLocationZ";
   SpyJassLog(" Exec:GetLocationZ[Location:%s]...",GetStrID(Location).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetLocationZ_ptr(Location);
   SpyJassLog("[GetLocationZ] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
HITEM _cdecl GetManipulatedItem_my()
{
   funcname1 = "GetManipulatedItem";
   SpyJassLog(" Exec:GetManipulatedItem[]...");
   HITEM returnvalue; 
   returnvalue = GetManipulatedItem_ptr();
   SpyJassLog("[GetManipulatedItem] OK [%s]\n",GetItemHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetManipulatingUnit_my()
{
   funcname1 = "GetManipulatingUnit";
   SpyJassLog(" Exec:GetManipulatingUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetManipulatingUnit_ptr();
   SpyJassLog("[GetManipulatingUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetMegaTarget_my()
{
   funcname1 = "GetMegaTarget";
   SpyJassLog(" Exec:GetMegaTarget[]...");
   HUNIT returnvalue; 
   returnvalue = GetMegaTarget_ptr();
   SpyJassLog("[GetMegaTarget] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
int _cdecl GetMinesOwned_my()
{
   funcname1 = "GetMinesOwned";
   SpyJassLog(" Exec:GetMinesOwned[]...");
   int returnvalue; 
   returnvalue = GetMinesOwned_ptr();
   SpyJassLog("[GetMinesOwned] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetNextExpansion_my()
{
   funcname1 = "GetNextExpansion";
   SpyJassLog(" Exec:GetNextExpansion[]...");
   int returnvalue; 
   returnvalue = GetNextExpansion_ptr();
   SpyJassLog("[GetNextExpansion] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
CJassStringSID _cdecl GetObjectName_my(int objectId)
{
   funcname1 = "GetObjectName";
   SpyJassLog(" Exec:GetObjectName[objectId:%s]...",GetStrID(objectId).c_str( ));
   CJassStringSID returnvalue; 
   returnvalue = GetObjectName_ptr(objectId);
   SpyJassLog("[GetObjectName] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
HLOCATION _cdecl GetOrderPointLoc_my()
{
   funcname1 = "GetOrderPointLoc";
   SpyJassLog(" Exec:GetOrderPointLoc[]...");
   HLOCATION returnvalue; 
   returnvalue = GetOrderPointLoc_ptr();
   SpyJassLog("[GetOrderPointLoc] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetOrderPointX_my()
{
   funcname1 = "GetOrderPointX";
   SpyJassLog(" Exec:GetOrderPointX[]...");
   DWFP returnvalue; 
   returnvalue = GetOrderPointX_ptr();
   SpyJassLog("[GetOrderPointX] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetOrderPointY_my()
{
   funcname1 = "GetOrderPointY";
   SpyJassLog(" Exec:GetOrderPointY[]...");
   DWFP returnvalue; 
   returnvalue = GetOrderPointY_ptr();
   SpyJassLog("[GetOrderPointY] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
HWIDGET _cdecl GetOrderTarget_my()
{
   funcname1 = "GetOrderTarget";
   SpyJassLog(" Exec:GetOrderTarget[]...");
   HWIDGET returnvalue; 
   returnvalue = GetOrderTarget_ptr();
   SpyJassLog("[GetOrderTarget] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HDESTRUCTABLE _cdecl GetOrderTargetDestructable_my()
{
   funcname1 = "GetOrderTargetDestructable";
   SpyJassLog(" Exec:GetOrderTargetDestructable[]...");
   HDESTRUCTABLE returnvalue; 
   returnvalue = GetOrderTargetDestructable_ptr();
   SpyJassLog("[GetOrderTargetDestructable] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HITEM _cdecl GetOrderTargetItem_my()
{
   funcname1 = "GetOrderTargetItem";
   SpyJassLog(" Exec:GetOrderTargetItem[]...");
   HITEM returnvalue; 
   returnvalue = GetOrderTargetItem_ptr();
   SpyJassLog("[GetOrderTargetItem] OK [%s]\n",GetItemHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetOrderTargetUnit_my()
{
   funcname1 = "GetOrderTargetUnit";
   SpyJassLog(" Exec:GetOrderTargetUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetOrderTargetUnit_ptr();
   SpyJassLog("[GetOrderTargetUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetOrderedUnit_my()
{
   funcname1 = "GetOrderedUnit";
   SpyJassLog(" Exec:GetOrderedUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetOrderedUnit_ptr();
   SpyJassLog("[GetOrderedUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HPLAYER _cdecl GetOwningPlayer_my(HUNIT unit)
{
   funcname1 = "GetOwningPlayer";
   SpyJassLog(" Exec:GetOwningPlayer[unit:%s]...",GetUnitHID(unit).c_str( ));
   HPLAYER returnvalue; 
   returnvalue = GetOwningPlayer_ptr(unit);
   SpyJassLog("[GetOwningPlayer] OK [%i]\n",GetPlayerId_ptr(returnvalue));
   return returnvalue;
}
BOOL _cdecl GetPlayerAlliance_my(HPLAYER sourcePlayer, HPLAYER otherPlayer, HALLIANCETYPE AllianceSetting)
{
   funcname1 = "GetPlayerAlliance";
   SpyJassLog(" Exec:GetPlayerAlliance[sourcePlayer:%i, otherPlayer:%i, AllianceSetting:%s]...",GetPlayerId_ptr(sourcePlayer), GetPlayerId_ptr(otherPlayer), GetStrID(AllianceSetting).c_str( ));
   BOOL returnvalue; 
   returnvalue = GetPlayerAlliance_ptr(sourcePlayer, otherPlayer, AllianceSetting);
   SpyJassLog("[GetPlayerAlliance] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
HPLAYERCOLOR _cdecl GetPlayerColor_my(HPLAYER player)
{
   funcname1 = "GetPlayerColor";
   SpyJassLog(" Exec:GetPlayerColor[player:%i]...",GetPlayerId_ptr(player));
   HPLAYERCOLOR returnvalue; 
   returnvalue = GetPlayerColor_ptr(player);
   SpyJassLog("[GetPlayerColor] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HMAPCONTROL _cdecl GetPlayerController_my(HPLAYER player)
{
   funcname1 = "GetPlayerController";
   SpyJassLog(" Exec:GetPlayerController[player:%i]...",GetPlayerId_ptr(player));
   HMAPCONTROL returnvalue; 
   returnvalue = GetPlayerController_ptr(player);
   SpyJassLog("[GetPlayerController] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetPlayerHandicap_my(HPLAYER player)
{
   funcname1 = "GetPlayerHandicap";
   SpyJassLog(" Exec:GetPlayerHandicap[player:%i]...",GetPlayerId_ptr(player));
   DWFP returnvalue; 
   returnvalue = GetPlayerHandicap_ptr(player);
   SpyJassLog("[GetPlayerHandicap] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetPlayerHandicapXP_my(HPLAYER player)
{
   funcname1 = "GetPlayerHandicapXP";
   SpyJassLog(" Exec:GetPlayerHandicapXP[player:%i]...",GetPlayerId_ptr(player));
   DWFP returnvalue; 
   returnvalue = GetPlayerHandicapXP_ptr(player);
   SpyJassLog("[GetPlayerHandicapXP] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
int _cdecl GetPlayerId_my(HPLAYER player)
{
   funcname1 = "GetPlayerId";
   SpyJassLog(" Exec:GetPlayerId[player:%i]...",GetPlayerId_ptr(player));
   int returnvalue; 
   returnvalue = GetPlayerId_ptr(player);
   SpyJassLog("[GetPlayerId] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
CJassStringSID _cdecl GetPlayerName_my(HPLAYER player)
{
   funcname1 = "GetPlayerName";
   SpyJassLog(" Exec:GetPlayerName[player:%i]...",GetPlayerId_ptr(player));
   CJassStringSID returnvalue; 
   returnvalue = GetPlayerName_ptr(player);
   SpyJassLog("[GetPlayerName] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
HRACE _cdecl GetPlayerRace_my(HPLAYER player)
{
   funcname1 = "GetPlayerRace";
   SpyJassLog(" Exec:GetPlayerRace[player:%i]...",GetPlayerId_ptr(player));
   HRACE returnvalue; 
   returnvalue = GetPlayerRace_ptr(player);
   SpyJassLog("[GetPlayerRace] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetPlayerScore_my(HPLAYER player, HPLAYERSCORE PlayerScore)
{
   funcname1 = "GetPlayerScore";
   SpyJassLog(" Exec:GetPlayerScore[player:%i, PlayerScore:%s]...",GetPlayerId_ptr(player), GetStrID(PlayerScore).c_str( ));
   int returnvalue; 
   returnvalue = GetPlayerScore_ptr(player, PlayerScore);
   SpyJassLog("[GetPlayerScore] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
BOOL _cdecl GetPlayerSelectable_my(HPLAYER player)
{
   funcname1 = "GetPlayerSelectable";
   SpyJassLog(" Exec:GetPlayerSelectable[player:%i]...",GetPlayerId_ptr(player));
   BOOL returnvalue; 
   returnvalue = GetPlayerSelectable_ptr(player);
   SpyJassLog("[GetPlayerSelectable] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
HPLAYERSLOTSTATE _cdecl GetPlayerSlotState_my(HPLAYER player)
{
   funcname1 = "GetPlayerSlotState";
   SpyJassLog(" Exec:GetPlayerSlotState[player:%i]...",GetPlayerId_ptr(player));
   HPLAYERSLOTSTATE returnvalue; 
   returnvalue = GetPlayerSlotState_ptr(player);
   SpyJassLog("[GetPlayerSlotState] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetPlayerStartLocation_my(HPLAYER player)
{
   funcname1 = "GetPlayerStartLocation";
   SpyJassLog(" Exec:GetPlayerStartLocation[player:%i]...",GetPlayerId_ptr(player));
   int returnvalue; 
   returnvalue = GetPlayerStartLocation_ptr(player);
   SpyJassLog("[GetPlayerStartLocation] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetPlayerStartLocationX_my(HPLAYER arg1)
{
   funcname1 = "GetPlayerStartLocationX";
   SpyJassLog(" Exec:GetPlayerStartLocationX[arg1:%i]...",GetPlayerId_ptr(arg1));
   DWFP returnvalue; 
   returnvalue = GetPlayerStartLocationX_ptr(arg1);
   SpyJassLog("[GetPlayerStartLocationX] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetPlayerStartLocationY_my(HPLAYER arg1)
{
   funcname1 = "GetPlayerStartLocationY";
   SpyJassLog(" Exec:GetPlayerStartLocationY[arg1:%i]...",GetPlayerId_ptr(arg1));
   DWFP returnvalue; 
   returnvalue = GetPlayerStartLocationY_ptr(arg1);
   SpyJassLog("[GetPlayerStartLocationY] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
int _cdecl GetPlayerState_my(HPLAYER player, HPLAYERSTATE PlayerState)
{
   funcname1 = "GetPlayerState";
   SpyJassLog(" Exec:GetPlayerState[player:%i, PlayerState:%s]...",GetPlayerId_ptr(player), GetStrID(PlayerState).c_str( ));
   int returnvalue; 
   returnvalue = GetPlayerState_ptr(player, PlayerState);
   SpyJassLog("[GetPlayerState] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetPlayerStructureCount_my(HPLAYER player, BOOL includeIncomplete)
{
   funcname1 = "GetPlayerStructureCount";
   SpyJassLog(" Exec:GetPlayerStructureCount[player:%i, includeIncomplete:%s]...",GetPlayerId_ptr(player), BoolToStr(includeIncomplete));
   int returnvalue; 
   returnvalue = GetPlayerStructureCount_ptr(player, includeIncomplete);
   SpyJassLog("[GetPlayerStructureCount] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetPlayerTaxRate_my(HPLAYER sourcePlayer, HPLAYER otherPlayer, HPLAYERSTATE Resource)
{
   funcname1 = "GetPlayerTaxRate";
   SpyJassLog(" Exec:GetPlayerTaxRate[sourcePlayer:%i, otherPlayer:%i, Resource:%s]...",GetPlayerId_ptr(sourcePlayer), GetPlayerId_ptr(otherPlayer), GetStrID(Resource).c_str( ));
   int returnvalue; 
   returnvalue = GetPlayerTaxRate_ptr(sourcePlayer, otherPlayer, Resource);
   SpyJassLog("[GetPlayerTaxRate] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetPlayerTeam_my(HPLAYER player)
{
   funcname1 = "GetPlayerTeam";
   SpyJassLog(" Exec:GetPlayerTeam[player:%i]...",GetPlayerId_ptr(player));
   int returnvalue; 
   returnvalue = GetPlayerTeam_ptr(player);
   SpyJassLog("[GetPlayerTeam] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetPlayerTechCount_my(HPLAYER player, int techid, BOOL specificonly)
{
   funcname1 = "GetPlayerTechCount";
   SpyJassLog(" Exec:GetPlayerTechCount[player:%i, techid:%s, specificonly:%s]...",GetPlayerId_ptr(player), GetStrID(techid).c_str( ), BoolToStr(specificonly));
   int returnvalue; 
   returnvalue = GetPlayerTechCount_ptr(player, techid, specificonly);
   SpyJassLog("[GetPlayerTechCount] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetPlayerTechMaxAllowed_my(HPLAYER player, int techid)
{
   funcname1 = "GetPlayerTechMaxAllowed";
   SpyJassLog(" Exec:GetPlayerTechMaxAllowed[player:%i, techid:%s]...",GetPlayerId_ptr(player), GetStrID(techid).c_str( ));
   int returnvalue; 
   returnvalue = GetPlayerTechMaxAllowed_ptr(player, techid);
   SpyJassLog("[GetPlayerTechMaxAllowed] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
BOOL _cdecl GetPlayerTechResearched_my(HPLAYER player, int techid, BOOL specificonly)
{
   funcname1 = "GetPlayerTechResearched";
   SpyJassLog(" Exec:GetPlayerTechResearched[player:%i, techid:%s, specificonly:%s]...",GetPlayerId_ptr(player), GetStrID(techid).c_str( ), BoolToStr(specificonly));
   BOOL returnvalue; 
   returnvalue = GetPlayerTechResearched_ptr(player, techid, specificonly);
   SpyJassLog("[GetPlayerTechResearched] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
int _cdecl GetPlayerTypedUnitCount_my(HPLAYER player, CJassString unitName, BOOL includeIncomplete, BOOL includeUpgrades)
{
   funcname1 = "GetPlayerTypedUnitCount";
   SpyJassLog(" Exec:GetPlayerTypedUnitCount[player:%i, unitName:%s, includeIncomplete:%s, includeUpgrades:%s]...",GetPlayerId_ptr(player), ReadJassStringNormal(unitName), BoolToStr(includeIncomplete), BoolToStr(includeUpgrades));
   int returnvalue; 
   returnvalue = GetPlayerTypedUnitCount_ptr(player, unitName, includeIncomplete, includeUpgrades);
   SpyJassLog("[GetPlayerTypedUnitCount] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetPlayerUnitCount_my(HPLAYER player, BOOL includeIncomplete)
{
   funcname1 = "GetPlayerUnitCount";
   SpyJassLog(" Exec:GetPlayerUnitCount[player:%i, includeIncomplete:%s]...",GetPlayerId_ptr(player), BoolToStr(includeIncomplete));
   int returnvalue; 
   returnvalue = GetPlayerUnitCount_ptr(player, includeIncomplete);
   SpyJassLog("[GetPlayerUnitCount] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetPlayerUnitTypeCount_my(HPLAYER arg1, int arg2)
{
   funcname1 = "GetPlayerUnitTypeCount";
   SpyJassLog(" Exec:GetPlayerUnitTypeCount[arg1:%i, arg2:%s]...",GetPlayerId_ptr(arg1), GetStrID(arg2).c_str( ));
   int returnvalue; 
   returnvalue = GetPlayerUnitTypeCount_ptr(arg1, arg2);
   SpyJassLog("[GetPlayerUnitTypeCount] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetPlayers_my()
{
   funcname1 = "GetPlayers";
   SpyJassLog(" Exec:GetPlayers[]...");
   int returnvalue; 
   returnvalue = GetPlayers_ptr();
   SpyJassLog("[GetPlayers] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetRandomInt_my(int lowBound, int highBound)
{
   funcname1 = "GetRandomInt";
   SpyJassLog(" Exec:GetRandomInt[lowBound:%s, highBound:%s]...",GetStrID(lowBound).c_str( ), GetStrID(highBound).c_str( ));
   int returnvalue; 
   returnvalue = GetRandomInt_ptr(lowBound, highBound);
   SpyJassLog("[GetRandomInt] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetRandomReal_my(float *lowBound, float *highBound)
{
   funcname1 = "GetRandomReal";
   SpyJassLog(" Exec:GetRandomReal[lowBound:%.4g, highBound:%.4g]...",(*lowBound), (*highBound));
   DWFP returnvalue; 
   returnvalue = GetRandomReal_ptr(lowBound, highBound);
   SpyJassLog("[GetRandomReal] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetRectCenterX_my(HRECT Rect)
{
   funcname1 = "GetRectCenterX";
   SpyJassLog(" Exec:GetRectCenterX[Rect:%s]...",GetStrID(Rect).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetRectCenterX_ptr(Rect);
   SpyJassLog("[GetRectCenterX] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetRectCenterY_my(HRECT Rect)
{
   funcname1 = "GetRectCenterY";
   SpyJassLog(" Exec:GetRectCenterY[Rect:%s]...",GetStrID(Rect).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetRectCenterY_ptr(Rect);
   SpyJassLog("[GetRectCenterY] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetRectMaxX_my(HRECT Rect)
{
   funcname1 = "GetRectMaxX";
   SpyJassLog(" Exec:GetRectMaxX[Rect:%s]...",GetStrID(Rect).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetRectMaxX_ptr(Rect);
   SpyJassLog("[GetRectMaxX] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetRectMaxY_my(HRECT Rect)
{
   funcname1 = "GetRectMaxY";
   SpyJassLog(" Exec:GetRectMaxY[Rect:%s]...",GetStrID(Rect).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetRectMaxY_ptr(Rect);
   SpyJassLog("[GetRectMaxY] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetRectMinX_my(HRECT Rect)
{
   funcname1 = "GetRectMinX";
   SpyJassLog(" Exec:GetRectMinX[Rect:%s]...",GetStrID(Rect).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetRectMinX_ptr(Rect);
   SpyJassLog("[GetRectMinX] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetRectMinY_my(HRECT Rect)
{
   funcname1 = "GetRectMinY";
   SpyJassLog(" Exec:GetRectMinY[Rect:%s]...",GetStrID(Rect).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetRectMinY_ptr(Rect);
   SpyJassLog("[GetRectMinY] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
HUNIT _cdecl GetRescuer_my()
{
   funcname1 = "GetRescuer";
   SpyJassLog(" Exec:GetRescuer[]...");
   HUNIT returnvalue; 
   returnvalue = GetRescuer_ptr();
   SpyJassLog("[GetRescuer] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
int _cdecl GetResearched_my()
{
   funcname1 = "GetResearched";
   SpyJassLog(" Exec:GetResearched[]...");
   int returnvalue; 
   returnvalue = GetResearched_ptr();
   SpyJassLog("[GetResearched] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetResearchingUnit_my()
{
   funcname1 = "GetResearchingUnit";
   SpyJassLog(" Exec:GetResearchingUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetResearchingUnit_ptr();
   SpyJassLog("[GetResearchingUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
int _cdecl GetResourceAmount_my(HUNIT unit)
{
   funcname1 = "GetResourceAmount";
   SpyJassLog(" Exec:GetResourceAmount[unit:%s]...",GetUnitHID(unit).c_str( ));
   int returnvalue; 
   returnvalue = GetResourceAmount_ptr(unit);
   SpyJassLog("[GetResourceAmount] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HMAPDENSITY _cdecl GetResourceDensity_my()
{
   funcname1 = "GetResourceDensity";
   SpyJassLog(" Exec:GetResourceDensity[]...");
   HMAPDENSITY returnvalue; 
   returnvalue = GetResourceDensity_ptr();
   SpyJassLog("[GetResourceDensity] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetRevivableUnit_my()
{
   funcname1 = "GetRevivableUnit";
   SpyJassLog(" Exec:GetRevivableUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetRevivableUnit_ptr();
   SpyJassLog("[GetRevivableUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetRevivingUnit_my()
{
   funcname1 = "GetRevivingUnit";
   SpyJassLog(" Exec:GetRevivingUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetRevivingUnit_ptr();
   SpyJassLog("[GetRevivingUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
CJassStringSID _cdecl GetSaveBasicFilename_my()
{
   funcname1 = "GetSaveBasicFilename";
   SpyJassLog(" Exec:GetSaveBasicFilename[]...");
   CJassStringSID returnvalue; 
   returnvalue = GetSaveBasicFilename_ptr();
   SpyJassLog("[GetSaveBasicFilename] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
HUNIT _cdecl GetSellingUnit_my()
{
   funcname1 = "GetSellingUnit";
   SpyJassLog(" Exec:GetSellingUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetSellingUnit_ptr();
   SpyJassLog("[GetSellingUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HITEM _cdecl GetSoldItem_my()
{
   funcname1 = "GetSoldItem";
   SpyJassLog(" Exec:GetSoldItem[]...");
   HITEM returnvalue; 
   returnvalue = GetSoldItem_ptr();
   SpyJassLog("[GetSoldItem] OK [%s]\n",GetItemHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetSoldUnit_my()
{
   funcname1 = "GetSoldUnit";
   SpyJassLog(" Exec:GetSoldUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetSoldUnit_ptr();
   SpyJassLog("[GetSoldUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
int _cdecl GetSoundDuration_my(HSOUND soundHandle)
{
   funcname1 = "GetSoundDuration";
   SpyJassLog(" Exec:GetSoundDuration[soundHandle:%s]...",GetStrID(soundHandle).c_str( ));
   int returnvalue; 
   returnvalue = GetSoundDuration_ptr(soundHandle);
   SpyJassLog("[GetSoundDuration] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetSoundFileDuration_my(CJassString musicFileName)
{
   funcname1 = "GetSoundFileDuration";
   SpyJassLog(" Exec:GetSoundFileDuration[musicFileName:%s]...",ReadJassStringNormal(musicFileName));
   int returnvalue; 
   returnvalue = GetSoundFileDuration_ptr(musicFileName);
   SpyJassLog("[GetSoundFileDuration] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
BOOL _cdecl GetSoundIsLoading_my(HSOUND soundHandle)
{
   funcname1 = "GetSoundIsLoading";
   SpyJassLog(" Exec:GetSoundIsLoading[soundHandle:%s]...",GetStrID(soundHandle).c_str( ));
   BOOL returnvalue; 
   returnvalue = GetSoundIsLoading_ptr(soundHandle);
   SpyJassLog("[GetSoundIsLoading] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl GetSoundIsPlaying_my(HSOUND soundHandle)
{
   funcname1 = "GetSoundIsPlaying";
   SpyJassLog(" Exec:GetSoundIsPlaying[soundHandle:%s]...",GetStrID(soundHandle).c_str( ));
   BOOL returnvalue; 
   returnvalue = GetSoundIsPlaying_ptr(soundHandle);
   SpyJassLog("[GetSoundIsPlaying] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
HABILITY _cdecl GetSpellAbility_my()
{
   funcname1 = "GetSpellAbility";
   SpyJassLog(" Exec:GetSpellAbility[]...");
   HABILITY returnvalue; 
   returnvalue = GetSpellAbility_ptr();
   SpyJassLog("[GetSpellAbility] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetSpellAbilityId_my()
{
   funcname1 = "GetSpellAbilityId";
   SpyJassLog(" Exec:GetSpellAbilityId[]...");
   int returnvalue; 
   returnvalue = GetSpellAbilityId_ptr();
   SpyJassLog("[GetSpellAbilityId] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetSpellAbilityUnit_my()
{
   funcname1 = "GetSpellAbilityUnit";
   SpyJassLog(" Exec:GetSpellAbilityUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetSpellAbilityUnit_ptr();
   SpyJassLog("[GetSpellAbilityUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HDESTRUCTABLE _cdecl GetSpellTargetDestructable_my()
{
   funcname1 = "GetSpellTargetDestructable";
   SpyJassLog(" Exec:GetSpellTargetDestructable[]...");
   HDESTRUCTABLE returnvalue; 
   returnvalue = GetSpellTargetDestructable_ptr();
   SpyJassLog("[GetSpellTargetDestructable] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HITEM _cdecl GetSpellTargetItem_my()
{
   funcname1 = "GetSpellTargetItem";
   SpyJassLog(" Exec:GetSpellTargetItem[]...");
   HITEM returnvalue; 
   returnvalue = GetSpellTargetItem_ptr();
   SpyJassLog("[GetSpellTargetItem] OK [%s]\n",GetItemHID(returnvalue).c_str( ));
   return returnvalue;
}
HLOCATION _cdecl GetSpellTargetLoc_my()
{
   funcname1 = "GetSpellTargetLoc";
   SpyJassLog(" Exec:GetSpellTargetLoc[]...");
   HLOCATION returnvalue; 
   returnvalue = GetSpellTargetLoc_ptr();
   SpyJassLog("[GetSpellTargetLoc] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetSpellTargetUnit_my()
{
   funcname1 = "GetSpellTargetUnit";
   SpyJassLog(" Exec:GetSpellTargetUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetSpellTargetUnit_ptr();
   SpyJassLog("[GetSpellTargetUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetSpellTargetX_my()
{
   funcname1 = "GetSpellTargetX";
   SpyJassLog(" Exec:GetSpellTargetX[]...");
   DWFP returnvalue; 
   returnvalue = GetSpellTargetX_ptr();
   SpyJassLog("[GetSpellTargetX] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetSpellTargetY_my()
{
   funcname1 = "GetSpellTargetY";
   SpyJassLog(" Exec:GetSpellTargetY[]...");
   DWFP returnvalue; 
   returnvalue = GetSpellTargetY_ptr();
   SpyJassLog("[GetSpellTargetY] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
HSTARTLOCPRIO _cdecl GetStartLocPrio_my(int StartLoc, int prioSlotIndex)
{
   funcname1 = "GetStartLocPrio";
   SpyJassLog(" Exec:GetStartLocPrio[StartLoc:%s, prioSlotIndex:%s]...",GetStrID(StartLoc).c_str( ), GetStrID(prioSlotIndex).c_str( ));
   HSTARTLOCPRIO returnvalue; 
   returnvalue = GetStartLocPrio_ptr(StartLoc, prioSlotIndex);
   SpyJassLog("[GetStartLocPrio] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetStartLocPrioSlot_my(int StartLoc, int prioSlotIndex)
{
   funcname1 = "GetStartLocPrioSlot";
   SpyJassLog(" Exec:GetStartLocPrioSlot[StartLoc:%s, prioSlotIndex:%s]...",GetStrID(StartLoc).c_str( ), GetStrID(prioSlotIndex).c_str( ));
   int returnvalue; 
   returnvalue = GetStartLocPrioSlot_ptr(StartLoc, prioSlotIndex);
   SpyJassLog("[GetStartLocPrioSlot] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HLOCATION _cdecl GetStartLocationLoc_my(int StartLocation)
{
   funcname1 = "GetStartLocationLoc";
   SpyJassLog(" Exec:GetStartLocationLoc[StartLocation:%s]...",GetStrID(StartLocation).c_str( ));
   HLOCATION returnvalue; 
   returnvalue = GetStartLocationLoc_ptr(StartLocation);
   SpyJassLog("[GetStartLocationLoc] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetStartLocationX_my(int StartLocation)
{
   funcname1 = "GetStartLocationX";
   SpyJassLog(" Exec:GetStartLocationX[StartLocation:%s]...",GetStrID(StartLocation).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetStartLocationX_ptr(StartLocation);
   SpyJassLog("[GetStartLocationX] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetStartLocationY_my(int StartLocation)
{
   funcname1 = "GetStartLocationY";
   SpyJassLog(" Exec:GetStartLocationY[StartLocation:%s]...",GetStrID(StartLocation).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetStartLocationY_ptr(StartLocation);
   SpyJassLog("[GetStartLocationY] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
BOOL _cdecl GetStoredBoolean_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "GetStoredBoolean";
   SpyJassLog(" Exec:GetStoredBoolean[cache:%s, missionKey:%s, key:%s]...",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
   BOOL returnvalue; 
   returnvalue = GetStoredBoolean_ptr(cache, missionKey, key);
   SpyJassLog("[GetStoredBoolean] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
int _cdecl GetStoredInteger_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "GetStoredInteger";
   SpyJassLog(" Exec:GetStoredInteger[cache:%s, missionKey:%s, key:%s]...",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
   int returnvalue; 
   returnvalue = GetStoredInteger_ptr(cache, missionKey, key);
   SpyJassLog("[GetStoredInteger] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetStoredReal_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "GetStoredReal";
   SpyJassLog(" Exec:GetStoredReal[cache:%s, missionKey:%s, key:%s]...",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
   DWFP returnvalue; 
   returnvalue = GetStoredReal_ptr(cache, missionKey, key);
   SpyJassLog("[GetStoredReal] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
CJassStringSID _cdecl GetStoredString_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "GetStoredString";
   SpyJassLog(" Exec:GetStoredString[cache:%s, missionKey:%s, key:%s]...",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
   CJassStringSID returnvalue; 
   returnvalue = GetStoredString_ptr(cache, missionKey, key);
   SpyJassLog("[GetStoredString] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
HUNIT _cdecl GetSummonedUnit_my()
{
   funcname1 = "GetSummonedUnit";
   SpyJassLog(" Exec:GetSummonedUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetSummonedUnit_ptr();
   SpyJassLog("[GetSummonedUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetSummoningUnit_my()
{
   funcname1 = "GetSummoningUnit";
   SpyJassLog(" Exec:GetSummoningUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetSummoningUnit_ptr();
   SpyJassLog("[GetSummoningUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
int _cdecl GetTeams_my()
{
   funcname1 = "GetTeams";
   SpyJassLog(" Exec:GetTeams[]...");
   int returnvalue; 
   returnvalue = GetTeams_ptr();
   SpyJassLog("[GetTeams] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetTerrainCliffLevel_my(float *x, float *y)
{
   funcname1 = "GetTerrainCliffLevel";
   SpyJassLog(" Exec:GetTerrainCliffLevel[x:%.4g, y:%.4g]...",(*x), (*y));
   int returnvalue; 
   returnvalue = GetTerrainCliffLevel_ptr(x, y);
   SpyJassLog("[GetTerrainCliffLevel] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetTerrainType_my(float *x, float *y)
{
   funcname1 = "GetTerrainType";
   SpyJassLog(" Exec:GetTerrainType[x:%.4g, y:%.4g]...",(*x), (*y));
   int returnvalue; 
   returnvalue = GetTerrainType_ptr(x, y);
   SpyJassLog("[GetTerrainType] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetTerrainVariance_my(float *x, float *y)
{
   funcname1 = "GetTerrainVariance";
   SpyJassLog(" Exec:GetTerrainVariance[x:%.4g, y:%.4g]...",(*x), (*y));
   int returnvalue; 
   returnvalue = GetTerrainVariance_ptr(x, y);
   SpyJassLog("[GetTerrainVariance] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetTimeOfDayScale_my()
{
   funcname1 = "GetTimeOfDayScale";
   SpyJassLog(" Exec:GetTimeOfDayScale[]...");
   DWFP returnvalue; 
   returnvalue = GetTimeOfDayScale_ptr();
   SpyJassLog("[GetTimeOfDayScale] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
HPLAYER _cdecl GetTournamentFinishNowPlayer_my()
{
   funcname1 = "GetTournamentFinishNowPlayer";
   SpyJassLog(" Exec:GetTournamentFinishNowPlayer[]...");
   HPLAYER returnvalue; 
   returnvalue = GetTournamentFinishNowPlayer_ptr();
   SpyJassLog("[GetTournamentFinishNowPlayer] OK [%i]\n",GetPlayerId_ptr(returnvalue));
   return returnvalue;
}
int _cdecl GetTournamentFinishNowRule_my()
{
   funcname1 = "GetTournamentFinishNowRule";
   SpyJassLog(" Exec:GetTournamentFinishNowRule[]...");
   int returnvalue; 
   returnvalue = GetTournamentFinishNowRule_ptr();
   SpyJassLog("[GetTournamentFinishNowRule] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetTournamentFinishSoonTimeRemaining_my()
{
   funcname1 = "GetTournamentFinishSoonTimeRemaining";
   SpyJassLog(" Exec:GetTournamentFinishSoonTimeRemaining[]...");
   DWFP returnvalue; 
   returnvalue = GetTournamentFinishSoonTimeRemaining_ptr();
   SpyJassLog("[GetTournamentFinishSoonTimeRemaining] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
int _cdecl GetTournamentScore_my(HPLAYER player)
{
   funcname1 = "GetTournamentScore";
   SpyJassLog(" Exec:GetTournamentScore[player:%i]...",GetPlayerId_ptr(player));
   int returnvalue; 
   returnvalue = GetTournamentScore_ptr(player);
   SpyJassLog("[GetTournamentScore] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetTownUnitCount_my(int arg1, int arg2, BOOL arg3)
{
   funcname1 = "GetTownUnitCount";
   SpyJassLog(" Exec:GetTownUnitCount[arg1:%s, arg2:%s, arg3:%s]...",GetStrID(arg1).c_str( ), GetStrID(arg2).c_str( ), BoolToStr(arg3));
   int returnvalue; 
   returnvalue = GetTownUnitCount_ptr(arg1, arg2, arg3);
   SpyJassLog("[GetTownUnitCount] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetTrainedUnit_my()
{
   funcname1 = "GetTrainedUnit";
   SpyJassLog(" Exec:GetTrainedUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetTrainedUnit_ptr();
   SpyJassLog("[GetTrainedUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
int _cdecl GetTrainedUnitType_my()
{
   funcname1 = "GetTrainedUnitType";
   SpyJassLog(" Exec:GetTrainedUnitType[]...");
   int returnvalue; 
   returnvalue = GetTrainedUnitType_ptr();
   SpyJassLog("[GetTrainedUnitType] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetTransportUnit_my()
{
   funcname1 = "GetTransportUnit";
   SpyJassLog(" Exec:GetTransportUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetTransportUnit_ptr();
   SpyJassLog("[GetTransportUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HDESTRUCTABLE _cdecl GetTriggerDestructable_my()
{
   funcname1 = "GetTriggerDestructable";
   SpyJassLog(" Exec:GetTriggerDestructable[]...");
   HDESTRUCTABLE returnvalue; 
   returnvalue = GetTriggerDestructable_ptr();
   SpyJassLog("[GetTriggerDestructable] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetTriggerEvalCount_my(HTRIGGER Trigger)
{
   funcname1 = "GetTriggerEvalCount";
   SpyJassLog(" Exec:GetTriggerEvalCount[Trigger:%s]...",GetStrID(Trigger).c_str( ));
   int returnvalue; 
   returnvalue = GetTriggerEvalCount_ptr(Trigger);
   SpyJassLog("[GetTriggerEvalCount] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENTID _cdecl GetTriggerEventId_my()
{
   funcname1 = "GetTriggerEventId";
   SpyJassLog(" Exec:GetTriggerEventId[]...");
   HEVENTID returnvalue; 
   returnvalue = GetTriggerEventId_ptr();
   SpyJassLog("[GetTriggerEventId] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetTriggerExecCount_my(HTRIGGER Trigger)
{
   funcname1 = "GetTriggerExecCount";
   SpyJassLog(" Exec:GetTriggerExecCount[Trigger:%s]...",GetStrID(Trigger).c_str( ));
   int returnvalue; 
   returnvalue = GetTriggerExecCount_ptr(Trigger);
   SpyJassLog("[GetTriggerExecCount] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HPLAYER _cdecl GetTriggerPlayer_my()
{
   funcname1 = "GetTriggerPlayer";
   SpyJassLog(" Exec:GetTriggerPlayer[]...");
   HPLAYER returnvalue; 
   returnvalue = GetTriggerPlayer_ptr();
   SpyJassLog("[GetTriggerPlayer] OK [%i]\n",GetPlayerId_ptr(returnvalue));
   return returnvalue;
}
HUNIT _cdecl GetTriggerUnit_my()
{
   funcname1 = "GetTriggerUnit";
   SpyJassLog(" Exec:GetTriggerUnit[]...");
   HUNIT returnvalue; 
   returnvalue = GetTriggerUnit_ptr();
   SpyJassLog("[GetTriggerUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HWIDGET _cdecl GetTriggerWidget_my()
{
   funcname1 = "GetTriggerWidget";
   SpyJassLog(" Exec:GetTriggerWidget[]...");
   HWIDGET returnvalue; 
   returnvalue = GetTriggerWidget_ptr();
   SpyJassLog("[GetTriggerWidget] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HREGION _cdecl GetTriggeringRegion_my()
{
   funcname1 = "GetTriggeringRegion";
   SpyJassLog(" Exec:GetTriggeringRegion[]...");
   HREGION returnvalue; 
   returnvalue = GetTriggeringRegion_ptr();
   SpyJassLog("[GetTriggeringRegion] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTRACKABLE _cdecl GetTriggeringTrackable_my()
{
   funcname1 = "GetTriggeringTrackable";
   SpyJassLog(" Exec:GetTriggeringTrackable[]...");
   HTRACKABLE returnvalue; 
   returnvalue = GetTriggeringTrackable_ptr();
   SpyJassLog("[GetTriggeringTrackable] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTRIGGER _cdecl GetTriggeringTrigger_my()
{
   funcname1 = "GetTriggeringTrigger";
   SpyJassLog(" Exec:GetTriggeringTrigger[]...");
   HTRIGGER returnvalue; 
   returnvalue = GetTriggeringTrigger_ptr();
   SpyJassLog("[GetTriggeringTrigger] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetUnitAbilityLevel_my(HUNIT unit, int abilcode)
{
   funcname1 = "GetUnitAbilityLevel";
   SpyJassLog(" Exec:GetUnitAbilityLevel[unit:%s, abilcode:%s]...",GetUnitHID(unit).c_str( ), GetStrID(abilcode).c_str( ));
   int returnvalue; 
   returnvalue = GetUnitAbilityLevel_ptr(unit, abilcode);
   SpyJassLog("[GetUnitAbilityLevel] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetUnitAcquireRange_my(HUNIT unit)
{
   funcname1 = "GetUnitAcquireRange";
   SpyJassLog(" Exec:GetUnitAcquireRange[unit:%s]...",GetUnitHID(unit).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetUnitAcquireRange_ptr(unit);
   SpyJassLog("[GetUnitAcquireRange] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
int _cdecl GetUnitBuildTime_my(int arg1)
{
   funcname1 = "GetUnitBuildTime";
   SpyJassLog(" Exec:GetUnitBuildTime[arg1:%s]...",GetStrID(arg1).c_str( ));
   int returnvalue; 
   returnvalue = GetUnitBuildTime_ptr(arg1);
   SpyJassLog("[GetUnitBuildTime] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetUnitCount_my(int arg1)
{
   funcname1 = "GetUnitCount";
   SpyJassLog(" Exec:GetUnitCount[arg1:%s]...",GetStrID(arg1).c_str( ));
   int returnvalue; 
   returnvalue = GetUnitCount_ptr(arg1);
   SpyJassLog("[GetUnitCount] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetUnitCountDone_my(int arg1)
{
   funcname1 = "GetUnitCountDone";
   SpyJassLog(" Exec:GetUnitCountDone[arg1:%s]...",GetStrID(arg1).c_str( ));
   int returnvalue; 
   returnvalue = GetUnitCountDone_ptr(arg1);
   SpyJassLog("[GetUnitCountDone] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetUnitCurrentOrder_my(HUNIT unit)
{
   funcname1 = "GetUnitCurrentOrder";
   SpyJassLog(" Exec:GetUnitCurrentOrder[unit:%s]...",GetUnitHID(unit).c_str( ));
   int returnvalue; 
   returnvalue = GetUnitCurrentOrder_ptr(unit);
   SpyJassLog("[GetUnitCurrentOrder] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetUnitDefaultAcquireRange_my(HUNIT unit)
{
   funcname1 = "GetUnitDefaultAcquireRange";
   SpyJassLog(" Exec:GetUnitDefaultAcquireRange[unit:%s]...",GetUnitHID(unit).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetUnitDefaultAcquireRange_ptr(unit);
   SpyJassLog("[GetUnitDefaultAcquireRange] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetUnitDefaultFlyHeight_my(HUNIT unit)
{
   funcname1 = "GetUnitDefaultFlyHeight";
   SpyJassLog(" Exec:GetUnitDefaultFlyHeight[unit:%s]...",GetUnitHID(unit).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetUnitDefaultFlyHeight_ptr(unit);
   SpyJassLog("[GetUnitDefaultFlyHeight] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetUnitDefaultMoveSpeed_my(HUNIT unit)
{
   funcname1 = "GetUnitDefaultMoveSpeed";
   SpyJassLog(" Exec:GetUnitDefaultMoveSpeed[unit:%s]...",GetUnitHID(unit).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetUnitDefaultMoveSpeed_ptr(unit);
   SpyJassLog("[GetUnitDefaultMoveSpeed] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetUnitDefaultPropWindow_my(HUNIT unit)
{
   funcname1 = "GetUnitDefaultPropWindow";
   SpyJassLog(" Exec:GetUnitDefaultPropWindow[unit:%s]...",GetUnitHID(unit).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetUnitDefaultPropWindow_ptr(unit);
   SpyJassLog("[GetUnitDefaultPropWindow] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetUnitDefaultTurnSpeed_my(HUNIT unit)
{
   funcname1 = "GetUnitDefaultTurnSpeed";
   SpyJassLog(" Exec:GetUnitDefaultTurnSpeed[unit:%s]...",GetUnitHID(unit).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetUnitDefaultTurnSpeed_ptr(unit);
   SpyJassLog("[GetUnitDefaultTurnSpeed] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetUnitFacing_my(HUNIT unit)
{
   funcname1 = "GetUnitFacing";
   SpyJassLog(" Exec:GetUnitFacing[unit:%s]...",GetUnitHID(unit).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetUnitFacing_ptr(unit);
   SpyJassLog("[GetUnitFacing] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetUnitFlyHeight_my(HUNIT unit)
{
   funcname1 = "GetUnitFlyHeight";
   SpyJassLog(" Exec:GetUnitFlyHeight[unit:%s]...",GetUnitHID(unit).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetUnitFlyHeight_ptr(unit);
   SpyJassLog("[GetUnitFlyHeight] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
int _cdecl GetUnitFoodMade_my(HUNIT unit)
{
   funcname1 = "GetUnitFoodMade";
   SpyJassLog(" Exec:GetUnitFoodMade[unit:%s]...",GetUnitHID(unit).c_str( ));
   int returnvalue; 
   returnvalue = GetUnitFoodMade_ptr(unit);
   SpyJassLog("[GetUnitFoodMade] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetUnitFoodUsed_my(HUNIT unit)
{
   funcname1 = "GetUnitFoodUsed";
   SpyJassLog(" Exec:GetUnitFoodUsed[unit:%s]...",GetUnitHID(unit).c_str( ));
   int returnvalue; 
   returnvalue = GetUnitFoodUsed_ptr(unit);
   SpyJassLog("[GetUnitFoodUsed] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetUnitGoldCost_my(int arg1)
{
   funcname1 = "GetUnitGoldCost";
   SpyJassLog(" Exec:GetUnitGoldCost[arg1:%s]...",GetStrID(arg1).c_str( ));
   int returnvalue; 
   returnvalue = GetUnitGoldCost_ptr(arg1);
   SpyJassLog("[GetUnitGoldCost] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetUnitLevel_my(HUNIT unit)
{
   funcname1 = "GetUnitLevel";
   SpyJassLog(" Exec:GetUnitLevel[unit:%s]...",GetUnitHID(unit).c_str( ));
   int returnvalue; 
   returnvalue = GetUnitLevel_ptr(unit);
   SpyJassLog("[GetUnitLevel] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HLOCATION _cdecl GetUnitLoc_my(HUNIT unit)
{
   funcname1 = "GetUnitLoc";
   SpyJassLog(" Exec:GetUnitLoc[unit:%s]...",GetUnitHID(unit).c_str( ));
   HLOCATION returnvalue; 
   returnvalue = GetUnitLoc_ptr(unit);
   SpyJassLog("[GetUnitLoc] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetUnitMoveSpeed_my(HUNIT unit)
{
   funcname1 = "GetUnitMoveSpeed";
   SpyJassLog(" Exec:GetUnitMoveSpeed[unit:%s]...",GetUnitHID(unit).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetUnitMoveSpeed_ptr(unit);
   SpyJassLog("[GetUnitMoveSpeed] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
CJassStringSID _cdecl GetUnitName_my(HUNIT unit)
{
   funcname1 = "GetUnitName";
   SpyJassLog(" Exec:GetUnitName[unit:%s]...",GetUnitHID(unit).c_str( ));
   CJassStringSID returnvalue; 
   returnvalue = GetUnitName_ptr(unit);
   SpyJassLog("[GetUnitName] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
int _cdecl GetUnitPointValue_my(HUNIT unit)
{
   funcname1 = "GetUnitPointValue";
   SpyJassLog(" Exec:GetUnitPointValue[unit:%s]...",GetUnitHID(unit).c_str( ));
   int returnvalue; 
   returnvalue = GetUnitPointValue_ptr(unit);
   SpyJassLog("[GetUnitPointValue] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetUnitPointValueByType_my(int unitType)
{
   funcname1 = "GetUnitPointValueByType";
   SpyJassLog(" Exec:GetUnitPointValueByType[unitType:%s]...",GetStrID(unitType).c_str( ));
   int returnvalue; 
   returnvalue = GetUnitPointValueByType_ptr(unitType);
   SpyJassLog("[GetUnitPointValueByType] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetUnitPropWindow_my(HUNIT unit)
{
   funcname1 = "GetUnitPropWindow";
   SpyJassLog(" Exec:GetUnitPropWindow[unit:%s]...",GetUnitHID(unit).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetUnitPropWindow_ptr(unit);
   SpyJassLog("[GetUnitPropWindow] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
HRACE _cdecl GetUnitRace_my(HUNIT unit)
{
   funcname1 = "GetUnitRace";
   SpyJassLog(" Exec:GetUnitRace[unit:%s]...",GetUnitHID(unit).c_str( ));
   HRACE returnvalue; 
   returnvalue = GetUnitRace_ptr(unit);
   SpyJassLog("[GetUnitRace] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HDESTRUCTABLE _cdecl GetUnitRallyDestructable_my(HUNIT unit)
{
   funcname1 = "GetUnitRallyDestructable";
   SpyJassLog(" Exec:GetUnitRallyDestructable[unit:%s]...",GetUnitHID(unit).c_str( ));
   HDESTRUCTABLE returnvalue; 
   returnvalue = GetUnitRallyDestructable_ptr(unit);
   SpyJassLog("[GetUnitRallyDestructable] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HLOCATION _cdecl GetUnitRallyPoint_my(HUNIT unit)
{
   funcname1 = "GetUnitRallyPoint";
   SpyJassLog(" Exec:GetUnitRallyPoint[unit:%s]...",GetUnitHID(unit).c_str( ));
   HLOCATION returnvalue; 
   returnvalue = GetUnitRallyPoint_ptr(unit);
   SpyJassLog("[GetUnitRallyPoint] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNIT _cdecl GetUnitRallyUnit_my(HUNIT unit)
{
   funcname1 = "GetUnitRallyUnit";
   SpyJassLog(" Exec:GetUnitRallyUnit[unit:%s]...",GetUnitHID(unit).c_str( ));
   HUNIT returnvalue; 
   returnvalue = GetUnitRallyUnit_ptr(unit);
   SpyJassLog("[GetUnitRallyUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetUnitState_my(HUNIT unit, HUNITSTATE UnitState)
{
   funcname1 = "GetUnitState";
   SpyJassLog(" Exec:GetUnitState[unit:%s, UnitState:%s]...",GetUnitHID(unit).c_str( ), GetStrID(UnitState).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetUnitState_ptr(unit, UnitState);
   SpyJassLog("[GetUnitState] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetUnitTurnSpeed_my(HUNIT unit)
{
   funcname1 = "GetUnitTurnSpeed";
   SpyJassLog(" Exec:GetUnitTurnSpeed[unit:%s]...",GetUnitHID(unit).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetUnitTurnSpeed_ptr(unit);
   SpyJassLog("[GetUnitTurnSpeed] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
int _cdecl GetUnitTypeId_my(HUNIT unit)
{
   funcname1 = "GetUnitTypeId";
   SpyJassLog(" Exec:GetUnitTypeId[unit:%s]...",GetUnitHID(unit).c_str( ));
   int returnvalue; 
   returnvalue = GetUnitTypeId_ptr(unit);
   SpyJassLog("[GetUnitTypeId] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetUnitUserData_my(HUNIT unit)
{
   funcname1 = "GetUnitUserData";
   SpyJassLog(" Exec:GetUnitUserData[unit:%s]...",GetUnitHID(unit).c_str( ));
   int returnvalue; 
   returnvalue = GetUnitUserData_ptr(unit);
   SpyJassLog("[GetUnitUserData] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetUnitWoodCost_my(int arg1)
{
   funcname1 = "GetUnitWoodCost";
   SpyJassLog(" Exec:GetUnitWoodCost[arg1:%s]...",GetStrID(arg1).c_str( ));
   int returnvalue; 
   returnvalue = GetUnitWoodCost_ptr(arg1);
   SpyJassLog("[GetUnitWoodCost] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetUnitX_my(HUNIT unit)
{
   funcname1 = "GetUnitX";
   SpyJassLog(" Exec:GetUnitX[unit:%s]...",GetUnitHID(unit).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetUnitX_ptr(unit);
   SpyJassLog("[GetUnitX] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetUnitY_my(HUNIT unit)
{
   funcname1 = "GetUnitY";
   SpyJassLog(" Exec:GetUnitY[unit:%s]...",GetUnitHID(unit).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetUnitY_ptr(unit);
   SpyJassLog("[GetUnitY] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
int _cdecl GetUpgradeGoldCost_my(int arg1)
{
   funcname1 = "GetUpgradeGoldCost";
   SpyJassLog(" Exec:GetUpgradeGoldCost[arg1:%s]...",GetStrID(arg1).c_str( ));
   int returnvalue; 
   returnvalue = GetUpgradeGoldCost_ptr(arg1);
   SpyJassLog("[GetUpgradeGoldCost] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetUpgradeLevel_my(int arg1)
{
   funcname1 = "GetUpgradeLevel";
   SpyJassLog(" Exec:GetUpgradeLevel[arg1:%s]...",GetStrID(arg1).c_str( ));
   int returnvalue; 
   returnvalue = GetUpgradeLevel_ptr(arg1);
   SpyJassLog("[GetUpgradeLevel] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl GetUpgradeWoodCost_my(int arg1)
{
   funcname1 = "GetUpgradeWoodCost";
   SpyJassLog(" Exec:GetUpgradeWoodCost[arg1:%s]...",GetStrID(arg1).c_str( ));
   int returnvalue; 
   returnvalue = GetUpgradeWoodCost_ptr(arg1);
   SpyJassLog("[GetUpgradeWoodCost] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl GetWidgetLife_my(HWIDGET widget)
{
   funcname1 = "GetWidgetLife";
   SpyJassLog(" Exec:GetWidgetLife[widget:%s]...",GetStrID(widget).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetWidgetLife_ptr(widget);
   SpyJassLog("[GetWidgetLife] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetWidgetX_my(HWIDGET widget)
{
   funcname1 = "GetWidgetX";
   SpyJassLog(" Exec:GetWidgetX[widget:%s]...",GetStrID(widget).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetWidgetX_ptr(widget);
   SpyJassLog("[GetWidgetX] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl GetWidgetY_my(HWIDGET widget)
{
   funcname1 = "GetWidgetY";
   SpyJassLog(" Exec:GetWidgetY[widget:%s]...",GetStrID(widget).c_str( ));
   DWFP returnvalue; 
   returnvalue = GetWidgetY_ptr(widget);
   SpyJassLog("[GetWidgetY] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
HPLAYER _cdecl GetWinningPlayer_my()
{
   funcname1 = "GetWinningPlayer";
   SpyJassLog(" Exec:GetWinningPlayer[]...");
   HPLAYER returnvalue; 
   returnvalue = GetWinningPlayer_ptr();
   SpyJassLog("[GetWinningPlayer] OK [%i]\n",GetPlayerId_ptr(returnvalue));
   return returnvalue;
}
HRECT _cdecl GetWorldBounds_my()
{
   funcname1 = "GetWorldBounds";
   SpyJassLog(" Exec:GetWorldBounds[]...");
   HRECT returnvalue; 
   returnvalue = GetWorldBounds_ptr();
   SpyJassLog("[GetWorldBounds] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl GroupAddUnit_my(HGROUP Group, HUNIT unit)
{
   funcname1 = "GroupAddUnit";
   SpyJassLog(" Exec:GroupAddUnit...");
   GroupAddUnit_ptr(Group, unit);
   SpyJassLog("[GroupAddUnit] OK [Group:%s, unit:%s]\n",GetStrID(Group).c_str( ), GetUnitHID(unit).c_str( ));
}
void _cdecl GroupClear_my(HGROUP Group)
{
   funcname1 = "GroupClear";
   SpyJassLog(" Exec:GroupClear...");
   GroupClear_ptr(Group);
   SpyJassLog("[GroupClear] OK [Group:%s]\n",GetStrID(Group).c_str( ));
}
void _cdecl GroupEnumUnitsInRange_my(HGROUP Group, float *x, float *y, float *radius, HBOOLEXPR filter)
{
   funcname1 = "GroupEnumUnitsInRange";
   SpyJassLog(" Exec:GroupEnumUnitsInRange...");
   GroupEnumUnitsInRange_ptr(Group, x, y, radius, filter);
   SpyJassLog("[GroupEnumUnitsInRange] OK [Group:%s, x:%.4g, y:%.4g, radius:%.4g, filter:%s]\n",GetStrID(Group).c_str( ), (*x), (*y), (*radius), GetStrID(filter).c_str( ));
}
void _cdecl GroupEnumUnitsInRangeCounted_my(HGROUP Group, float *x, float *y, float *radius, HBOOLEXPR filter, int countLimit)
{
   funcname1 = "GroupEnumUnitsInRangeCounted";
   SpyJassLog(" Exec:GroupEnumUnitsInRangeCounted...");
   GroupEnumUnitsInRangeCounted_ptr(Group, x, y, radius, filter, countLimit);
   SpyJassLog("[GroupEnumUnitsInRangeCounted] OK [Group:%s, x:%.4g, y:%.4g, radius:%.4g, filter:%s, countLimit:%s]\n",GetStrID(Group).c_str( ), (*x), (*y), (*radius), GetStrID(filter).c_str( ), GetStrID(countLimit).c_str( ));
}
void _cdecl GroupEnumUnitsInRangeOfLoc_my(HGROUP Group, HLOCATION Location, float *radius, HBOOLEXPR filter)
{
   funcname1 = "GroupEnumUnitsInRangeOfLoc";
   SpyJassLog(" Exec:GroupEnumUnitsInRangeOfLoc...");
   GroupEnumUnitsInRangeOfLoc_ptr(Group, Location, radius, filter);
   SpyJassLog("[GroupEnumUnitsInRangeOfLoc] OK [Group:%s, Location:%s, radius:%.4g, filter:%s]\n",GetStrID(Group).c_str( ), GetStrID(Location).c_str( ), (*radius), GetStrID(filter).c_str( ));
}
void _cdecl GroupEnumUnitsInRangeOfLocCounted_my(HGROUP Group, HLOCATION Location, float *radius, HBOOLEXPR filter, int countLimit)
{
   funcname1 = "GroupEnumUnitsInRangeOfLocCounted";
   SpyJassLog(" Exec:GroupEnumUnitsInRangeOfLocCounted...");
   GroupEnumUnitsInRangeOfLocCounted_ptr(Group, Location, radius, filter, countLimit);
   SpyJassLog("[GroupEnumUnitsInRangeOfLocCounted] OK [Group:%s, Location:%s, radius:%.4g, filter:%s, countLimit:%s]\n",GetStrID(Group).c_str( ), GetStrID(Location).c_str( ), (*radius), GetStrID(filter).c_str( ), GetStrID(countLimit).c_str( ));
}
void _cdecl GroupEnumUnitsInRect_my(HGROUP Group, HRECT r, HBOOLEXPR filter)
{
   funcname1 = "GroupEnumUnitsInRect";
   SpyJassLog(" Exec:GroupEnumUnitsInRect...");
   GroupEnumUnitsInRect_ptr(Group, r, filter);
   SpyJassLog("[GroupEnumUnitsInRect] OK [Group:%s, r:%s, filter:%s]\n",GetStrID(Group).c_str( ), GetStrID(r).c_str( ), GetStrID(filter).c_str( ));
}
void _cdecl GroupEnumUnitsInRectCounted_my(HGROUP Group, HRECT r, HBOOLEXPR filter, int countLimit)
{
   funcname1 = "GroupEnumUnitsInRectCounted";
   SpyJassLog(" Exec:GroupEnumUnitsInRectCounted...");
   GroupEnumUnitsInRectCounted_ptr(Group, r, filter, countLimit);
   SpyJassLog("[GroupEnumUnitsInRectCounted] OK [Group:%s, r:%s, filter:%s, countLimit:%s]\n",GetStrID(Group).c_str( ), GetStrID(r).c_str( ), GetStrID(filter).c_str( ), GetStrID(countLimit).c_str( ));
}
void _cdecl GroupEnumUnitsOfPlayer_my(HGROUP Group, HPLAYER player, HBOOLEXPR filter)
{
   funcname1 = "GroupEnumUnitsOfPlayer";
   SpyJassLog(" Exec:GroupEnumUnitsOfPlayer...");
   GroupEnumUnitsOfPlayer_ptr(Group, player, filter);
   SpyJassLog("[GroupEnumUnitsOfPlayer] OK [Group:%s, player:%i, filter:%s]\n",GetStrID(Group).c_str( ), GetPlayerId_ptr(player), GetStrID(filter).c_str( ));
}
void _cdecl GroupEnumUnitsOfType_my(HGROUP Group, CJassString unitname, HBOOLEXPR filter)
{
   funcname1 = "GroupEnumUnitsOfType";
   SpyJassLog(" Exec:GroupEnumUnitsOfType...");
   GroupEnumUnitsOfType_ptr(Group, unitname, filter);
   SpyJassLog("[GroupEnumUnitsOfType] OK [Group:%s, unitname:%s, filter:%s]\n",GetStrID(Group).c_str( ), ReadJassStringNormal(unitname), GetStrID(filter).c_str( ));
}
void _cdecl GroupEnumUnitsOfTypeCounted_my(HGROUP Group, CJassString unitname, HBOOLEXPR filter, int countLimit)
{
   funcname1 = "GroupEnumUnitsOfTypeCounted";
   SpyJassLog(" Exec:GroupEnumUnitsOfTypeCounted...");
   GroupEnumUnitsOfTypeCounted_ptr(Group, unitname, filter, countLimit);
   SpyJassLog("[GroupEnumUnitsOfTypeCounted] OK [Group:%s, unitname:%s, filter:%s, countLimit:%s]\n",GetStrID(Group).c_str( ), ReadJassStringNormal(unitname), GetStrID(filter).c_str( ), GetStrID(countLimit).c_str( ));
}
void _cdecl GroupEnumUnitsSelected_my(HGROUP Group, HPLAYER player, HBOOLEXPR filter)
{
   funcname1 = "GroupEnumUnitsSelected";
   SpyJassLog(" Exec:GroupEnumUnitsSelected...");
   GroupEnumUnitsSelected_ptr(Group, player, filter);
   SpyJassLog("[GroupEnumUnitsSelected] OK [Group:%s, player:%i, filter:%s]\n",GetStrID(Group).c_str( ), GetPlayerId_ptr(player), GetStrID(filter).c_str( ));
}
BOOL _cdecl GroupImmediateOrder_my(HGROUP Group, CJassString order)
{
   funcname1 = "GroupImmediateOrder";
   SpyJassLog(" Exec:GroupImmediateOrder[Group:%s, order:%s]...",GetStrID(Group).c_str( ), ReadJassStringNormal(order));
   BOOL returnvalue; 
   returnvalue = GroupImmediateOrder_ptr(Group, order);
   SpyJassLog("[GroupImmediateOrder] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl GroupImmediateOrderById_my(HGROUP Group, int order)
{
   funcname1 = "GroupImmediateOrderById";
   SpyJassLog(" Exec:GroupImmediateOrderById[Group:%s, order:%s]...",GetStrID(Group).c_str( ), GetStrID(order).c_str( ));
   BOOL returnvalue; 
   returnvalue = GroupImmediateOrderById_ptr(Group, order);
   SpyJassLog("[GroupImmediateOrderById] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl GroupPointOrder_my(HGROUP Group, CJassString order, float *x, float *y)
{
   funcname1 = "GroupPointOrder";
   SpyJassLog(" Exec:GroupPointOrder[Group:%s, order:%s, x:%.4g, y:%.4g]...",GetStrID(Group).c_str( ), ReadJassStringNormal(order), (*x), (*y));
   BOOL returnvalue; 
   returnvalue = GroupPointOrder_ptr(Group, order, x, y);
   SpyJassLog("[GroupPointOrder] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl GroupPointOrderById_my(HGROUP Group, int order, float *x, float *y)
{
   funcname1 = "GroupPointOrderById";
   SpyJassLog(" Exec:GroupPointOrderById[Group:%s, order:%s, x:%.4g, y:%.4g]...",GetStrID(Group).c_str( ), GetStrID(order).c_str( ), (*x), (*y));
   BOOL returnvalue; 
   returnvalue = GroupPointOrderById_ptr(Group, order, x, y);
   SpyJassLog("[GroupPointOrderById] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl GroupPointOrderByIdLoc_my(HGROUP Group, int order, HLOCATION Location)
{
   funcname1 = "GroupPointOrderByIdLoc";
   SpyJassLog(" Exec:GroupPointOrderByIdLoc[Group:%s, order:%s, Location:%s]...",GetStrID(Group).c_str( ), GetStrID(order).c_str( ), GetStrID(Location).c_str( ));
   BOOL returnvalue; 
   returnvalue = GroupPointOrderByIdLoc_ptr(Group, order, Location);
   SpyJassLog("[GroupPointOrderByIdLoc] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl GroupPointOrderLoc_my(HGROUP Group, CJassString order, HLOCATION Location)
{
   funcname1 = "GroupPointOrderLoc";
   SpyJassLog(" Exec:GroupPointOrderLoc[Group:%s, order:%s, Location:%s]...",GetStrID(Group).c_str( ), ReadJassStringNormal(order), GetStrID(Location).c_str( ));
   BOOL returnvalue; 
   returnvalue = GroupPointOrderLoc_ptr(Group, order, Location);
   SpyJassLog("[GroupPointOrderLoc] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl GroupRemoveUnit_my(HGROUP Group, HUNIT unit)
{
   funcname1 = "GroupRemoveUnit";
   SpyJassLog(" Exec:GroupRemoveUnit...");
   GroupRemoveUnit_ptr(Group, unit);
   SpyJassLog("[GroupRemoveUnit] OK [Group:%s, unit:%s]\n",GetStrID(Group).c_str( ), GetUnitHID(unit).c_str( ));
}
BOOL _cdecl GroupTargetOrder_my(HGROUP Group, CJassString order, HWIDGET targetWidget)
{
   funcname1 = "GroupTargetOrder";
   SpyJassLog(" Exec:GroupTargetOrder[Group:%s, order:%s, targetWidget:%s]...",GetStrID(Group).c_str( ), ReadJassStringNormal(order), GetStrID(targetWidget).c_str( ));
   BOOL returnvalue; 
   returnvalue = GroupTargetOrder_ptr(Group, order, targetWidget);
   SpyJassLog("[GroupTargetOrder] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl GroupTargetOrderById_my(HGROUP Group, int order, HWIDGET targetWidget)
{
   funcname1 = "GroupTargetOrderById";
   SpyJassLog(" Exec:GroupTargetOrderById[Group:%s, order:%s, targetWidget:%s]...",GetStrID(Group).c_str( ), GetStrID(order).c_str( ), GetStrID(targetWidget).c_str( ));
   BOOL returnvalue; 
   returnvalue = GroupTargetOrderById_ptr(Group, order, targetWidget);
   SpyJassLog("[GroupTargetOrderById] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl GroupTimedLife_my(BOOL arg1)
{
   funcname1 = "GroupTimedLife";
   SpyJassLog(" Exec:GroupTimedLife...");
   GroupTimedLife_ptr(arg1);
   SpyJassLog("[GroupTimedLife] OK [arg1:%s]\n",BoolToStr(arg1));
}
void _cdecl HarvestGold_my(int arg1, int arg2)
{
   funcname1 = "HarvestGold";
   SpyJassLog(" Exec:HarvestGold...");
   HarvestGold_ptr(arg1, arg2);
   SpyJassLog("[HarvestGold] OK [arg1:%s, arg2:%s]\n",GetStrID(arg1).c_str( ), GetStrID(arg2).c_str( ));
}
void _cdecl HarvestWood_my(int arg1, int arg2)
{
   funcname1 = "HarvestWood";
   SpyJassLog(" Exec:HarvestWood...");
   HarvestWood_ptr(arg1, arg2);
   SpyJassLog("[HarvestWood] OK [arg1:%s, arg2:%s]\n",GetStrID(arg1).c_str( ), GetStrID(arg2).c_str( ));
}
BOOL _cdecl HaveSavedBoolean_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "HaveSavedBoolean";
   SpyJassLog(" Exec:HaveSavedBoolean[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   BOOL returnvalue; 
   returnvalue = HaveSavedBoolean_ptr(table, parentKey, childKey);
   SpyJassLog("[HaveSavedBoolean] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl HaveSavedHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "HaveSavedHandle";
   SpyJassLog(" Exec:HaveSavedHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   BOOL returnvalue; 
   returnvalue = HaveSavedHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[HaveSavedHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl HaveSavedInteger_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "HaveSavedInteger";
   SpyJassLog(" Exec:HaveSavedInteger[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   BOOL returnvalue; 
   returnvalue = HaveSavedInteger_ptr(table, parentKey, childKey);
   SpyJassLog("[HaveSavedInteger] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl HaveSavedReal_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "HaveSavedReal";
   SpyJassLog(" Exec:HaveSavedReal[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   BOOL returnvalue; 
   returnvalue = HaveSavedReal_ptr(table, parentKey, childKey);
   SpyJassLog("[HaveSavedReal] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl HaveSavedString_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "HaveSavedString";
   SpyJassLog(" Exec:HaveSavedString[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   BOOL returnvalue; 
   returnvalue = HaveSavedString_ptr(table, parentKey, childKey);
   SpyJassLog("[HaveSavedString] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl HaveStoredBoolean_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "HaveStoredBoolean";
   SpyJassLog(" Exec:HaveStoredBoolean[cache:%s, missionKey:%s, key:%s]...",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
   BOOL returnvalue; 
   returnvalue = HaveStoredBoolean_ptr(cache, missionKey, key);
   SpyJassLog("[HaveStoredBoolean] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl HaveStoredInteger_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "HaveStoredInteger";
   SpyJassLog(" Exec:HaveStoredInteger[cache:%s, missionKey:%s, key:%s]...",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
   BOOL returnvalue; 
   returnvalue = HaveStoredInteger_ptr(cache, missionKey, key);
   SpyJassLog("[HaveStoredInteger] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl HaveStoredReal_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "HaveStoredReal";
   SpyJassLog(" Exec:HaveStoredReal[cache:%s, missionKey:%s, key:%s]...",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
   BOOL returnvalue; 
   returnvalue = HaveStoredReal_ptr(cache, missionKey, key);
   SpyJassLog("[HaveStoredReal] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl HaveStoredString_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "HaveStoredString";
   SpyJassLog(" Exec:HaveStoredString[cache:%s, missionKey:%s, key:%s]...",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
   BOOL returnvalue; 
   returnvalue = HaveStoredString_ptr(cache, missionKey, key);
   SpyJassLog("[HaveStoredString] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl HaveStoredUnit_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "HaveStoredUnit";
   SpyJassLog(" Exec:HaveStoredUnit[cache:%s, missionKey:%s, key:%s]...",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
   BOOL returnvalue; 
   returnvalue = HaveStoredUnit_ptr(cache, missionKey, key);
   SpyJassLog("[HaveStoredUnit] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
DWFP _cdecl I2R_my(int i)
{
   funcname1 = "I2R";
   SpyJassLog(" Exec:I2R[i:%s]...",GetStrID(i).c_str( ));
   DWFP returnvalue; 
   returnvalue = I2R_ptr(i);
   SpyJassLog("[I2R] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
CJassStringSID _cdecl I2S_my(int i)
{
   funcname1 = "I2S";
   SpyJassLog(" Exec:I2S[i:%s]...",GetStrID(i).c_str( ));
   CJassStringSID returnvalue; 
   returnvalue = I2S_ptr(i);
   SpyJassLog("[I2S] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
int _cdecl IgnoredUnits_my(int arg1)
{
   funcname1 = "IgnoredUnits";
   SpyJassLog(" Exec:IgnoredUnits[arg1:%s]...",GetStrID(arg1).c_str( ));
   int returnvalue; 
   returnvalue = IgnoredUnits_ptr(arg1);
   SpyJassLog("[IgnoredUnits] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl IncUnitAbilityLevel_my(HUNIT unit, int abilcode)
{
   funcname1 = "IncUnitAbilityLevel";
   SpyJassLog(" Exec:IncUnitAbilityLevel[unit:%s, abilcode:%s]...",GetUnitHID(unit).c_str( ), GetStrID(abilcode).c_str( ));
   int returnvalue; 
   returnvalue = IncUnitAbilityLevel_ptr(unit, abilcode);
   SpyJassLog("[IncUnitAbilityLevel] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl InitAssault_my()
{
   funcname1 = "InitAssault";
   SpyJassLog(" Exec:InitAssault...");
   InitAssault_ptr();
   SpyJassLog("[InitAssault] OK []\n");
}
HGAMECACHE _cdecl InitGameCache_my(CJassString campaignFile)
{
   funcname1 = "InitGameCache";
   SpyJassLog(" Exec:InitGameCache[campaignFile:%s]...",ReadJassStringNormal(campaignFile));
   HGAMECACHE returnvalue; 
   returnvalue = InitGameCache_ptr(campaignFile);
   SpyJassLog("[InitGameCache] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HHASHTABLE _cdecl InitHashtable_my()
{
   funcname1 = "InitHashtable";
   SpyJassLog(" Exec:InitHashtable[]...");
   HHASHTABLE returnvalue; 
   returnvalue = InitHashtable_ptr();
   SpyJassLog("[InitHashtable] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
BOOL _cdecl IsCineFilterDisplayed_my()
{
   funcname1 = "IsCineFilterDisplayed";
   SpyJassLog(" Exec:IsCineFilterDisplayed[]...");
   BOOL returnvalue; 
   returnvalue = IsCineFilterDisplayed_ptr();
   SpyJassLog("[IsCineFilterDisplayed] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsDestructableInvulnerable_my(HDESTRUCTABLE d)
{
   funcname1 = "IsDestructableInvulnerable";
   SpyJassLog(" Exec:IsDestructableInvulnerable[d:%s]...",GetStrID(d).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsDestructableInvulnerable_ptr(d);
   SpyJassLog("[IsDestructableInvulnerable] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsFogEnabled_my()
{
   funcname1 = "IsFogEnabled";
   SpyJassLog(" Exec:IsFogEnabled[]...");
   BOOL returnvalue; 
   returnvalue = IsFogEnabled_ptr();
   SpyJassLog("[IsFogEnabled] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsFogMaskEnabled_my()
{
   funcname1 = "IsFogMaskEnabled";
   SpyJassLog(" Exec:IsFogMaskEnabled[]...");
   BOOL returnvalue; 
   returnvalue = IsFogMaskEnabled_ptr();
   SpyJassLog("[IsFogMaskEnabled] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsFoggedToPlayer_my(float *x, float *y, HPLAYER player)
{
   funcname1 = "IsFoggedToPlayer";
   SpyJassLog(" Exec:IsFoggedToPlayer[x:%.4g, y:%.4g, player:%i]...",(*x), (*y), GetPlayerId_ptr(player));
   BOOL returnvalue; 
   returnvalue = IsFoggedToPlayer_ptr(x, y, player);
   SpyJassLog("[IsFoggedToPlayer] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsGameTypeSupported_my(HGAMETYPE GameType)
{
   funcname1 = "IsGameTypeSupported";
   SpyJassLog(" Exec:IsGameTypeSupported[GameType:%s]...",GetStrID(GameType).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsGameTypeSupported_ptr(GameType);
   SpyJassLog("[IsGameTypeSupported] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsHeroUnitId_my(int unitId)
{
   funcname1 = "IsHeroUnitId";
   SpyJassLog(" Exec:IsHeroUnitId[unitId:%s]...",GetStrID(unitId).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsHeroUnitId_ptr(unitId);
   SpyJassLog("[IsHeroUnitId] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsItemIdPawnable_my(int itemId)
{
   funcname1 = "IsItemIdPawnable";
   SpyJassLog(" Exec:IsItemIdPawnable[itemId:%s]...",GetStrID(itemId).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsItemIdPawnable_ptr(itemId);
   SpyJassLog("[IsItemIdPawnable] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsItemIdPowerup_my(int itemId)
{
   funcname1 = "IsItemIdPowerup";
   SpyJassLog(" Exec:IsItemIdPowerup[itemId:%s]...",GetStrID(itemId).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsItemIdPowerup_ptr(itemId);
   SpyJassLog("[IsItemIdPowerup] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsItemIdSellable_my(int itemId)
{
   funcname1 = "IsItemIdSellable";
   SpyJassLog(" Exec:IsItemIdSellable[itemId:%s]...",GetStrID(itemId).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsItemIdSellable_ptr(itemId);
   SpyJassLog("[IsItemIdSellable] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsItemInvulnerable_my(HITEM item)
{
   funcname1 = "IsItemInvulnerable";
   SpyJassLog(" Exec:IsItemInvulnerable[item:%s]...",GetItemHID(item).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsItemInvulnerable_ptr(item);
   SpyJassLog("[IsItemInvulnerable] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsItemOwned_my(HITEM item)
{
   funcname1 = "IsItemOwned";
   SpyJassLog(" Exec:IsItemOwned[item:%s]...",GetItemHID(item).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsItemOwned_ptr(item);
   SpyJassLog("[IsItemOwned] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsItemPawnable_my(HITEM item)
{
   funcname1 = "IsItemPawnable";
   SpyJassLog(" Exec:IsItemPawnable[item:%s]...",GetItemHID(item).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsItemPawnable_ptr(item);
   SpyJassLog("[IsItemPawnable] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsItemPowerup_my(HITEM item)
{
   funcname1 = "IsItemPowerup";
   SpyJassLog(" Exec:IsItemPowerup[item:%s]...",GetItemHID(item).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsItemPowerup_ptr(item);
   SpyJassLog("[IsItemPowerup] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsItemSellable_my(HITEM item)
{
   funcname1 = "IsItemSellable";
   SpyJassLog(" Exec:IsItemSellable[item:%s]...",GetItemHID(item).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsItemSellable_ptr(item);
   SpyJassLog("[IsItemSellable] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsItemVisible_my(HITEM item)
{
   funcname1 = "IsItemVisible";
   SpyJassLog(" Exec:IsItemVisible[item:%s]...",GetItemHID(item).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsItemVisible_ptr(item);
   SpyJassLog("[IsItemVisible] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsLeaderboardDisplayed_my(HLEADERBOARD lb)
{
   funcname1 = "IsLeaderboardDisplayed";
   SpyJassLog(" Exec:IsLeaderboardDisplayed[lb:%s]...",GetStrID(lb).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsLeaderboardDisplayed_ptr(lb);
   SpyJassLog("[IsLeaderboardDisplayed] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsLocationFoggedToPlayer_my(HLOCATION Location, HPLAYER player)
{
   funcname1 = "IsLocationFoggedToPlayer";
   SpyJassLog(" Exec:IsLocationFoggedToPlayer[Location:%s, player:%i]...",GetStrID(Location).c_str( ), GetPlayerId_ptr(player));
   BOOL returnvalue; 
   returnvalue = IsLocationFoggedToPlayer_ptr(Location, player);
   SpyJassLog("[IsLocationFoggedToPlayer] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsLocationInRegion_my(HREGION Region, HLOCATION Location)
{
   funcname1 = "IsLocationInRegion";
   SpyJassLog(" Exec:IsLocationInRegion[Region:%s, Location:%s]...",GetStrID(Region).c_str( ), GetStrID(Location).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsLocationInRegion_ptr(Region, Location);
   SpyJassLog("[IsLocationInRegion] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsLocationMaskedToPlayer_my(HLOCATION Location, HPLAYER player)
{
   funcname1 = "IsLocationMaskedToPlayer";
   SpyJassLog(" Exec:IsLocationMaskedToPlayer[Location:%s, player:%i]...",GetStrID(Location).c_str( ), GetPlayerId_ptr(player));
   BOOL returnvalue; 
   returnvalue = IsLocationMaskedToPlayer_ptr(Location, player);
   SpyJassLog("[IsLocationMaskedToPlayer] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsLocationVisibleToPlayer_my(HLOCATION Location, HPLAYER player)
{
   funcname1 = "IsLocationVisibleToPlayer";
   SpyJassLog(" Exec:IsLocationVisibleToPlayer[Location:%s, player:%i]...",GetStrID(Location).c_str( ), GetPlayerId_ptr(player));
   BOOL returnvalue; 
   returnvalue = IsLocationVisibleToPlayer_ptr(Location, player);
   SpyJassLog("[IsLocationVisibleToPlayer] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsMapFlagSet_my(HMAPFLAG MapFlag)
{
   funcname1 = "IsMapFlagSet";
   SpyJassLog(" Exec:IsMapFlagSet[MapFlag:%s]...",GetStrID(MapFlag).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsMapFlagSet_ptr(MapFlag);
   SpyJassLog("[IsMapFlagSet] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsMaskedToPlayer_my(float *x, float *y, HPLAYER player)
{
   funcname1 = "IsMaskedToPlayer";
   SpyJassLog(" Exec:IsMaskedToPlayer[x:%.4g, y:%.4g, player:%i]...",(*x), (*y), GetPlayerId_ptr(player));
   BOOL returnvalue; 
   returnvalue = IsMaskedToPlayer_ptr(x, y, player);
   SpyJassLog("[IsMaskedToPlayer] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsMultiboardDisplayed_my(HMULTIBOARD lb)
{
   funcname1 = "IsMultiboardDisplayed";
   SpyJassLog(" Exec:IsMultiboardDisplayed[lb:%s]...",GetStrID(lb).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsMultiboardDisplayed_ptr(lb);
   SpyJassLog("[IsMultiboardDisplayed] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsMultiboardMinimized_my(HMULTIBOARD lb)
{
   funcname1 = "IsMultiboardMinimized";
   SpyJassLog(" Exec:IsMultiboardMinimized[lb:%s]...",GetStrID(lb).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsMultiboardMinimized_ptr(lb);
   SpyJassLog("[IsMultiboardMinimized] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsNoDefeatCheat_my()
{
   funcname1 = "IsNoDefeatCheat";
   SpyJassLog(" Exec:IsNoDefeatCheat[]...");
   BOOL returnvalue; 
   returnvalue = IsNoDefeatCheat_ptr();
   SpyJassLog("[IsNoDefeatCheat] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsNoVictoryCheat_my()
{
   funcname1 = "IsNoVictoryCheat";
   SpyJassLog(" Exec:IsNoVictoryCheat[]...");
   BOOL returnvalue; 
   returnvalue = IsNoVictoryCheat_ptr();
   SpyJassLog("[IsNoVictoryCheat] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsPlayerAlly_my(HPLAYER player, HPLAYER otherPlayer)
{
   funcname1 = "IsPlayerAlly";
   SpyJassLog(" Exec:IsPlayerAlly[player:%i, otherPlayer:%i]...",GetPlayerId_ptr(player), GetPlayerId_ptr(otherPlayer));
   BOOL returnvalue; 
   returnvalue = IsPlayerAlly_ptr(player, otherPlayer);
   SpyJassLog("[IsPlayerAlly] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsPlayerEnemy_my(HPLAYER player, HPLAYER otherPlayer)
{
   funcname1 = "IsPlayerEnemy";
   SpyJassLog(" Exec:IsPlayerEnemy[player:%i, otherPlayer:%i]...",GetPlayerId_ptr(player), GetPlayerId_ptr(otherPlayer));
   BOOL returnvalue; 
   returnvalue = IsPlayerEnemy_ptr(player, otherPlayer);
   SpyJassLog("[IsPlayerEnemy] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsPlayerInForce_my(HPLAYER player, HFORCE Force)
{
   funcname1 = "IsPlayerInForce";
   SpyJassLog(" Exec:IsPlayerInForce[player:%i, Force:%s]...",GetPlayerId_ptr(player), GetStrID(Force).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsPlayerInForce_ptr(player, Force);
   SpyJassLog("[IsPlayerInForce] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsPlayerObserver_my(HPLAYER player)
{
   funcname1 = "IsPlayerObserver";
   SpyJassLog(" Exec:IsPlayerObserver[player:%i]...",GetPlayerId_ptr(player));
   BOOL returnvalue; 
   returnvalue = IsPlayerObserver_ptr(player);
   SpyJassLog("[IsPlayerObserver] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsPlayerRacePrefSet_my(HPLAYER player, HRACEPREFERENCE pref)
{
   funcname1 = "IsPlayerRacePrefSet";
   SpyJassLog(" Exec:IsPlayerRacePrefSet[player:%i, pref:%s]...",GetPlayerId_ptr(player), GetStrID(pref).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsPlayerRacePrefSet_ptr(player, pref);
   SpyJassLog("[IsPlayerRacePrefSet] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsPointBlighted_my(float *x, float *y)
{
   funcname1 = "IsPointBlighted";
   SpyJassLog(" Exec:IsPointBlighted[x:%.4g, y:%.4g]...",(*x), (*y));
   BOOL returnvalue; 
   returnvalue = IsPointBlighted_ptr(x, y);
   SpyJassLog("[IsPointBlighted] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsPointInRegion_my(HREGION Region, float *x, float *y)
{
   funcname1 = "IsPointInRegion";
   SpyJassLog(" Exec:IsPointInRegion[Region:%s, x:%.4g, y:%.4g]...",GetStrID(Region).c_str( ), (*x), (*y));
   BOOL returnvalue; 
   returnvalue = IsPointInRegion_ptr(Region, x, y);
   SpyJassLog("[IsPointInRegion] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsQuestCompleted_my(HQUEST Quest)
{
   funcname1 = "IsQuestCompleted";
   SpyJassLog(" Exec:IsQuestCompleted[Quest:%s]...",GetStrID(Quest).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsQuestCompleted_ptr(Quest);
   SpyJassLog("[IsQuestCompleted] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsQuestDiscovered_my(HQUEST Quest)
{
   funcname1 = "IsQuestDiscovered";
   SpyJassLog(" Exec:IsQuestDiscovered[Quest:%s]...",GetStrID(Quest).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsQuestDiscovered_ptr(Quest);
   SpyJassLog("[IsQuestDiscovered] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsQuestEnabled_my(HQUEST Quest)
{
   funcname1 = "IsQuestEnabled";
   SpyJassLog(" Exec:IsQuestEnabled[Quest:%s]...",GetStrID(Quest).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsQuestEnabled_ptr(Quest);
   SpyJassLog("[IsQuestEnabled] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsQuestFailed_my(HQUEST Quest)
{
   funcname1 = "IsQuestFailed";
   SpyJassLog(" Exec:IsQuestFailed[Quest:%s]...",GetStrID(Quest).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsQuestFailed_ptr(Quest);
   SpyJassLog("[IsQuestFailed] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsQuestItemCompleted_my(HQUESTITEM QuestItem)
{
   funcname1 = "IsQuestItemCompleted";
   SpyJassLog(" Exec:IsQuestItemCompleted[QuestItem:%s]...",GetStrID(QuestItem).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsQuestItemCompleted_ptr(QuestItem);
   SpyJassLog("[IsQuestItemCompleted] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsQuestRequired_my(HQUEST Quest)
{
   funcname1 = "IsQuestRequired";
   SpyJassLog(" Exec:IsQuestRequired[Quest:%s]...",GetStrID(Quest).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsQuestRequired_ptr(Quest);
   SpyJassLog("[IsQuestRequired] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsSuspendedXP_my(HUNIT hero)
{
   funcname1 = "IsSuspendedXP";
   SpyJassLog(" Exec:IsSuspendedXP[hero:%s]...",GetUnitHID(hero).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsSuspendedXP_ptr(hero);
   SpyJassLog("[IsSuspendedXP] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsTerrainPathable_my(float *x, float *y, HPATHINGTYPE t)
{
   funcname1 = "IsTerrainPathable";
   SpyJassLog(" Exec:IsTerrainPathable[x:%.4g, y:%.4g, t:%s]...",(*x), (*y), GetStrID(t).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsTerrainPathable_ptr(x, y, t);
   SpyJassLog("[IsTerrainPathable] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsTimerDialogDisplayed_my(HTIMERDIALOG Dialog)
{
   funcname1 = "IsTimerDialogDisplayed";
   SpyJassLog(" Exec:IsTimerDialogDisplayed[Dialog:%s]...",GetStrID(Dialog).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsTimerDialogDisplayed_ptr(Dialog);
   SpyJassLog("[IsTimerDialogDisplayed] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsTowered_my(HUNIT arg1)
{
   funcname1 = "IsTowered";
   SpyJassLog(" Exec:IsTowered[arg1:%s]...",GetUnitHID(arg1).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsTowered_ptr(arg1);
   SpyJassLog("[IsTowered] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsTriggerEnabled_my(HTRIGGER Trigger)
{
   funcname1 = "IsTriggerEnabled";
   SpyJassLog(" Exec:IsTriggerEnabled[Trigger:%s]...",GetStrID(Trigger).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsTriggerEnabled_ptr(Trigger);
   SpyJassLog("[IsTriggerEnabled] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsTriggerWaitOnSleeps_my(HTRIGGER Trigger)
{
   funcname1 = "IsTriggerWaitOnSleeps";
   SpyJassLog(" Exec:IsTriggerWaitOnSleeps[Trigger:%s]...",GetStrID(Trigger).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsTriggerWaitOnSleeps_ptr(Trigger);
   SpyJassLog("[IsTriggerWaitOnSleeps] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnit_my(HUNIT unit, HUNIT SpecifiedUnit)
{
   funcname1 = "IsUnit";
   SpyJassLog(" Exec:IsUnit[unit:%s, SpecifiedUnit:%s]...",GetUnitHID(unit).c_str( ), GetUnitHID(SpecifiedUnit).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsUnit_ptr(unit, SpecifiedUnit);
   SpyJassLog("[IsUnit] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitAlly_my(HUNIT unit, HPLAYER player)
{
   funcname1 = "IsUnitAlly";
   SpyJassLog(" Exec:IsUnitAlly[unit:%s, player:%i]...",GetUnitHID(unit).c_str( ), GetPlayerId_ptr(player));
   BOOL returnvalue; 
   returnvalue = IsUnitAlly_ptr(unit, player);
   SpyJassLog("[IsUnitAlly] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitDetected_my(HUNIT unit, HPLAYER player)
{
   funcname1 = "IsUnitDetected";
   SpyJassLog(" Exec:IsUnitDetected[unit:%s, player:%i]...",GetUnitHID(unit).c_str( ), GetPlayerId_ptr(player));
   BOOL returnvalue; 
   returnvalue = IsUnitDetected_ptr(unit, player);
   SpyJassLog("[IsUnitDetected] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitEnemy_my(HUNIT unit, HPLAYER player)
{
   funcname1 = "IsUnitEnemy";
   SpyJassLog(" Exec:IsUnitEnemy[unit:%s, player:%i]...",GetUnitHID(unit).c_str( ), GetPlayerId_ptr(player));
   BOOL returnvalue; 
   returnvalue = IsUnitEnemy_ptr(unit, player);
   SpyJassLog("[IsUnitEnemy] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitFogged_my(HUNIT unit, HPLAYER player)
{
   funcname1 = "IsUnitFogged";
   SpyJassLog(" Exec:IsUnitFogged[unit:%s, player:%i]...",GetUnitHID(unit).c_str( ), GetPlayerId_ptr(player));
   BOOL returnvalue; 
   returnvalue = IsUnitFogged_ptr(unit, player);
   SpyJassLog("[IsUnitFogged] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitHidden_my(HUNIT unit)
{
   funcname1 = "IsUnitHidden";
   SpyJassLog(" Exec:IsUnitHidden[unit:%s]...",GetUnitHID(unit).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsUnitHidden_ptr(unit);
   SpyJassLog("[IsUnitHidden] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitIdType_my(int unitId, HUNITTYPE UnitType)
{
   funcname1 = "IsUnitIdType";
   SpyJassLog(" Exec:IsUnitIdType[unitId:%s, UnitType:%s]...",GetStrID(unitId).c_str( ), GetStrID(UnitType).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsUnitIdType_ptr(unitId, UnitType);
   SpyJassLog("[IsUnitIdType] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitIllusion_my(HUNIT unit)
{
   funcname1 = "IsUnitIllusion";
   SpyJassLog(" Exec:IsUnitIllusion[unit:%s]...",GetUnitHID(unit).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsUnitIllusion_ptr(unit);
   SpyJassLog("[IsUnitIllusion] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitInForce_my(HUNIT unit, HFORCE Force)
{
   funcname1 = "IsUnitInForce";
   SpyJassLog(" Exec:IsUnitInForce[unit:%s, Force:%s]...",GetUnitHID(unit).c_str( ), GetStrID(Force).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsUnitInForce_ptr(unit, Force);
   SpyJassLog("[IsUnitInForce] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitInGroup_my(HUNIT unit, HGROUP Group)
{
   funcname1 = "IsUnitInGroup";
   SpyJassLog(" Exec:IsUnitInGroup[unit:%s, Group:%s]...",GetUnitHID(unit).c_str( ), GetStrID(Group).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsUnitInGroup_ptr(unit, Group);
   SpyJassLog("[IsUnitInGroup] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitInRange_my(HUNIT unit, HUNIT otherUnit, float *distance)
{
   funcname1 = "IsUnitInRange";
   SpyJassLog(" Exec:IsUnitInRange[unit:%s, otherUnit:%s, distance:%.4g]...",GetUnitHID(unit).c_str( ), GetUnitHID(otherUnit).c_str( ), (*distance));
   BOOL returnvalue; 
   returnvalue = IsUnitInRange_ptr(unit, otherUnit, distance);
   SpyJassLog("[IsUnitInRange] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitInRangeLoc_my(HUNIT unit, HLOCATION Location, float *distance)
{
   funcname1 = "IsUnitInRangeLoc";
   SpyJassLog(" Exec:IsUnitInRangeLoc[unit:%s, Location:%s, distance:%.4g]...",GetUnitHID(unit).c_str( ), GetStrID(Location).c_str( ), (*distance));
   BOOL returnvalue; 
   returnvalue = IsUnitInRangeLoc_ptr(unit, Location, distance);
   SpyJassLog("[IsUnitInRangeLoc] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitInRangeXY_my(HUNIT unit, float *x, float *y, float *distance)
{
   funcname1 = "IsUnitInRangeXY";
   SpyJassLog(" Exec:IsUnitInRangeXY[unit:%s, x:%.4g, y:%.4g, distance:%.4g]...",GetUnitHID(unit).c_str( ), (*x), (*y), (*distance));
   BOOL returnvalue; 
   returnvalue = IsUnitInRangeXY_ptr(unit, x, y, distance);
   SpyJassLog("[IsUnitInRangeXY] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitInRegion_my(HREGION Region, HUNIT unit)
{
   funcname1 = "IsUnitInRegion";
   SpyJassLog(" Exec:IsUnitInRegion[Region:%s, unit:%s]...",GetStrID(Region).c_str( ), GetUnitHID(unit).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsUnitInRegion_ptr(Region, unit);
   SpyJassLog("[IsUnitInRegion] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitInTransport_my(HUNIT unit, HUNIT Transport)
{
   funcname1 = "IsUnitInTransport";
   SpyJassLog(" Exec:IsUnitInTransport[unit:%s, Transport:%s]...",GetUnitHID(unit).c_str( ), GetUnitHID(Transport).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsUnitInTransport_ptr(unit, Transport);
   SpyJassLog("[IsUnitInTransport] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitInvisible_my(HUNIT unit, HPLAYER player)
{
   funcname1 = "IsUnitInvisible";
   SpyJassLog(" Exec:IsUnitInvisible[unit:%s, player:%i]...",GetUnitHID(unit).c_str( ), GetPlayerId_ptr(player));
   BOOL returnvalue; 
   returnvalue = IsUnitInvisible_ptr(unit, player);
   SpyJassLog("[IsUnitInvisible] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitLoaded_my(HUNIT unit)
{
   funcname1 = "IsUnitLoaded";
   SpyJassLog(" Exec:IsUnitLoaded[unit:%s]...",GetUnitHID(unit).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsUnitLoaded_ptr(unit);
   SpyJassLog("[IsUnitLoaded] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitMasked_my(HUNIT unit, HPLAYER player)
{
   funcname1 = "IsUnitMasked";
   SpyJassLog(" Exec:IsUnitMasked[unit:%s, player:%i]...",GetUnitHID(unit).c_str( ), GetPlayerId_ptr(player));
   BOOL returnvalue; 
   returnvalue = IsUnitMasked_ptr(unit, player);
   SpyJassLog("[IsUnitMasked] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitOwnedByPlayer_my(HUNIT unit, HPLAYER player)
{
   funcname1 = "IsUnitOwnedByPlayer";
   SpyJassLog(" Exec:IsUnitOwnedByPlayer[unit:%s, player:%i]...",GetUnitHID(unit).c_str( ), GetPlayerId_ptr(player));
   BOOL returnvalue; 
   returnvalue = IsUnitOwnedByPlayer_ptr(unit, player);
   SpyJassLog("[IsUnitOwnedByPlayer] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitPaused_my(HUNIT hero)
{
   funcname1 = "IsUnitPaused";
   SpyJassLog(" Exec:IsUnitPaused[hero:%s]...",GetUnitHID(hero).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsUnitPaused_ptr(hero);
   SpyJassLog("[IsUnitPaused] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitRace_my(HUNIT unit, HRACE Race)
{
   funcname1 = "IsUnitRace";
   SpyJassLog(" Exec:IsUnitRace[unit:%s, Race:%s]...",GetUnitHID(unit).c_str( ), GetStrID(Race).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsUnitRace_ptr(unit, Race);
   SpyJassLog("[IsUnitRace] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitSelected_my(HUNIT unit, HPLAYER player)
{
   funcname1 = "IsUnitSelected";
   SpyJassLog(" Exec:IsUnitSelected[unit:%s, player:%i]...",GetUnitHID(unit).c_str( ), GetPlayerId_ptr(player));
   BOOL returnvalue; 
   returnvalue = IsUnitSelected_ptr(unit, player);
   SpyJassLog("[IsUnitSelected] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitType_my(HUNIT unit, HUNITTYPE UnitType)
{
   funcname1 = "IsUnitType";
   SpyJassLog(" Exec:IsUnitType[unit:%s, UnitType:%s]...",GetUnitHID(unit).c_str( ), GetStrID(UnitType).c_str( ));
   BOOL returnvalue; 
   returnvalue = IsUnitType_ptr(unit, UnitType);
   SpyJassLog("[IsUnitType] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsUnitVisible_my(HUNIT unit, HPLAYER player)
{
   funcname1 = "IsUnitVisible";
   SpyJassLog(" Exec:IsUnitVisible[unit:%s, player:%i]...",GetUnitHID(unit).c_str( ), GetPlayerId_ptr(player));
   BOOL returnvalue; 
   returnvalue = IsUnitVisible_ptr(unit, player);
   SpyJassLog("[IsUnitVisible] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IsVisibleToPlayer_my(float *x, float *y, HPLAYER player)
{
   funcname1 = "IsVisibleToPlayer";
   SpyJassLog(" Exec:IsVisibleToPlayer[x:%.4g, y:%.4g, player:%i]...",(*x), (*y), GetPlayerId_ptr(player));
   BOOL returnvalue; 
   returnvalue = IsVisibleToPlayer_ptr(x, y, player);
   SpyJassLog("[IsVisibleToPlayer] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssueBuildOrder_my(HUNIT Peon, CJassString unitToBuild, float *x, float *y)
{
   funcname1 = "IssueBuildOrder";
   SpyJassLog(" Exec:IssueBuildOrder[Peon:%s, unitToBuild:%s, x:%.4g, y:%.4g]...",GetUnitHID(Peon).c_str( ), ReadJassStringNormal(unitToBuild), (*x), (*y));
   BOOL returnvalue; 
   returnvalue = IssueBuildOrder_ptr(Peon, unitToBuild, x, y);
   SpyJassLog("[IssueBuildOrder] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssueBuildOrderById_my(HUNIT Peon, int unitId, float *x, float *y)
{
   funcname1 = "IssueBuildOrderById";
   SpyJassLog(" Exec:IssueBuildOrderById[Peon:%s, unitId:%s, x:%.4g, y:%.4g]...",GetUnitHID(Peon).c_str( ), GetStrID(unitId).c_str( ), (*x), (*y));
   BOOL returnvalue; 
   returnvalue = IssueBuildOrderById_ptr(Peon, unitId, x, y);
   SpyJassLog("[IssueBuildOrderById] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssueImmediateOrder_my(HUNIT unit, CJassString order)
{
   funcname1 = "IssueImmediateOrder";
   SpyJassLog(" Exec:IssueImmediateOrder[unit:%s, order:%s]...",GetUnitHID(unit).c_str( ), ReadJassStringNormal(order));
   BOOL returnvalue; 
   returnvalue = IssueImmediateOrder_ptr(unit, order);
   SpyJassLog("[IssueImmediateOrder] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssueImmediateOrderById_my(HUNIT unit, int order)
{
   funcname1 = "IssueImmediateOrderById";
   SpyJassLog(" Exec:IssueImmediateOrderById[unit:%s, order:%s]...",GetUnitHID(unit).c_str( ), GetStrID(order).c_str( ));
   BOOL returnvalue; 
   returnvalue = IssueImmediateOrderById_ptr(unit, order);
   SpyJassLog("[IssueImmediateOrderById] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssueInstantPointOrder_my(HUNIT unit, CJassString order, float *x, float *y, HWIDGET instantTargetWidget)
{
   funcname1 = "IssueInstantPointOrder";
   SpyJassLog(" Exec:IssueInstantPointOrder[unit:%s, order:%s, x:%.4g, y:%.4g, instantTargetWidget:%s]...",GetUnitHID(unit).c_str( ), ReadJassStringNormal(order), (*x), (*y), GetStrID(instantTargetWidget).c_str( ));
   BOOL returnvalue; 
   returnvalue = IssueInstantPointOrder_ptr(unit, order, x, y, instantTargetWidget);
   SpyJassLog("[IssueInstantPointOrder] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssueInstantPointOrderById_my(HUNIT unit, int order, float *x, float *y, HWIDGET instantTargetWidget)
{
   funcname1 = "IssueInstantPointOrderById";
   SpyJassLog(" Exec:IssueInstantPointOrderById[unit:%s, order:%s, x:%.4g, y:%.4g, instantTargetWidget:%s]...",GetUnitHID(unit).c_str( ), GetStrID(order).c_str( ), (*x), (*y), GetStrID(instantTargetWidget).c_str( ));
   BOOL returnvalue; 
   returnvalue = IssueInstantPointOrderById_ptr(unit, order, x, y, instantTargetWidget);
   SpyJassLog("[IssueInstantPointOrderById] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssueInstantTargetOrder_my(HUNIT unit, CJassString order, HWIDGET targetWidget, HWIDGET instantTargetWidget)
{
   funcname1 = "IssueInstantTargetOrder";
   SpyJassLog(" Exec:IssueInstantTargetOrder[unit:%s, order:%s, targetWidget:%s, instantTargetWidget:%s]...",GetUnitHID(unit).c_str( ), ReadJassStringNormal(order), GetStrID(targetWidget).c_str( ), GetStrID(instantTargetWidget).c_str( ));
   BOOL returnvalue; 
   returnvalue = IssueInstantTargetOrder_ptr(unit, order, targetWidget, instantTargetWidget);
   SpyJassLog("[IssueInstantTargetOrder] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssueInstantTargetOrderById_my(HUNIT unit, int order, HWIDGET targetWidget, HWIDGET instantTargetWidget)
{
   funcname1 = "IssueInstantTargetOrderById";
   SpyJassLog(" Exec:IssueInstantTargetOrderById[unit:%s, order:%s, targetWidget:%s, instantTargetWidget:%s]...",GetUnitHID(unit).c_str( ), GetStrID(order).c_str( ), GetStrID(targetWidget).c_str( ), GetStrID(instantTargetWidget).c_str( ));
   BOOL returnvalue; 
   returnvalue = IssueInstantTargetOrderById_ptr(unit, order, targetWidget, instantTargetWidget);
   SpyJassLog("[IssueInstantTargetOrderById] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssueNeutralImmediateOrder_my(HPLAYER forWhichPlayer, HUNIT neutralStructure, CJassString unitToBuild)
{
   funcname1 = "IssueNeutralImmediateOrder";
   SpyJassLog(" Exec:IssueNeutralImmediateOrder[forWhichPlayer:%i, neutralStructure:%s, unitToBuild:%s]...",GetPlayerId_ptr(forWhichPlayer), GetUnitHID(neutralStructure).c_str( ), ReadJassStringNormal(unitToBuild));
   BOOL returnvalue; 
   returnvalue = IssueNeutralImmediateOrder_ptr(forWhichPlayer, neutralStructure, unitToBuild);
   SpyJassLog("[IssueNeutralImmediateOrder] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssueNeutralImmediateOrderById_my(HPLAYER forWhichPlayer, HUNIT neutralStructure, int unitId)
{
   funcname1 = "IssueNeutralImmediateOrderById";
   SpyJassLog(" Exec:IssueNeutralImmediateOrderById[forWhichPlayer:%i, neutralStructure:%s, unitId:%s]...",GetPlayerId_ptr(forWhichPlayer), GetUnitHID(neutralStructure).c_str( ), GetStrID(unitId).c_str( ));
   BOOL returnvalue; 
   returnvalue = IssueNeutralImmediateOrderById_ptr(forWhichPlayer, neutralStructure, unitId);
   SpyJassLog("[IssueNeutralImmediateOrderById] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssueNeutralPointOrder_my(HPLAYER forWhichPlayer, HUNIT neutralStructure, CJassString unitToBuild, float *x, float *y)
{
   funcname1 = "IssueNeutralPointOrder";
   SpyJassLog(" Exec:IssueNeutralPointOrder[forWhichPlayer:%i, neutralStructure:%s, unitToBuild:%s, x:%.4g, y:%.4g]...",GetPlayerId_ptr(forWhichPlayer), GetUnitHID(neutralStructure).c_str( ), ReadJassStringNormal(unitToBuild), (*x), (*y));
   BOOL returnvalue; 
   returnvalue = IssueNeutralPointOrder_ptr(forWhichPlayer, neutralStructure, unitToBuild, x, y);
   SpyJassLog("[IssueNeutralPointOrder] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssueNeutralPointOrderById_my(HPLAYER forWhichPlayer, HUNIT neutralStructure, int unitId, float *x, float *y)
{
   funcname1 = "IssueNeutralPointOrderById";
   SpyJassLog(" Exec:IssueNeutralPointOrderById[forWhichPlayer:%i, neutralStructure:%s, unitId:%s, x:%.4g, y:%.4g]...",GetPlayerId_ptr(forWhichPlayer), GetUnitHID(neutralStructure).c_str( ), GetStrID(unitId).c_str( ), (*x), (*y));
   BOOL returnvalue; 
   returnvalue = IssueNeutralPointOrderById_ptr(forWhichPlayer, neutralStructure, unitId, x, y);
   SpyJassLog("[IssueNeutralPointOrderById] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssueNeutralTargetOrder_my(HPLAYER forWhichPlayer, HUNIT neutralStructure, CJassString unitToBuild, HWIDGET target)
{
   funcname1 = "IssueNeutralTargetOrder";
   SpyJassLog(" Exec:IssueNeutralTargetOrder[forWhichPlayer:%i, neutralStructure:%s, unitToBuild:%s, target:%s]...",GetPlayerId_ptr(forWhichPlayer), GetUnitHID(neutralStructure).c_str( ), ReadJassStringNormal(unitToBuild), GetStrID(target).c_str( ));
   BOOL returnvalue; 
   returnvalue = IssueNeutralTargetOrder_ptr(forWhichPlayer, neutralStructure, unitToBuild, target);
   SpyJassLog("[IssueNeutralTargetOrder] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssueNeutralTargetOrderById_my(HPLAYER forWhichPlayer, HUNIT neutralStructure, int unitId, HWIDGET target)
{
   funcname1 = "IssueNeutralTargetOrderById";
   SpyJassLog(" Exec:IssueNeutralTargetOrderById[forWhichPlayer:%i, neutralStructure:%s, unitId:%s, target:%s]...",GetPlayerId_ptr(forWhichPlayer), GetUnitHID(neutralStructure).c_str( ), GetStrID(unitId).c_str( ), GetStrID(target).c_str( ));
   BOOL returnvalue; 
   returnvalue = IssueNeutralTargetOrderById_ptr(forWhichPlayer, neutralStructure, unitId, target);
   SpyJassLog("[IssueNeutralTargetOrderById] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssuePointOrder_my(HUNIT unit, CJassString order, float *x, float *y)
{
   funcname1 = "IssuePointOrder";
   SpyJassLog(" Exec:IssuePointOrder[unit:%s, order:%s, x:%.4g, y:%.4g]...",GetUnitHID(unit).c_str( ), ReadJassStringNormal(order), (*x), (*y));
   BOOL returnvalue; 
   returnvalue = IssuePointOrder_ptr(unit, order, x, y);
   SpyJassLog("[IssuePointOrder] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssuePointOrderById_my(HUNIT unit, int order, float *x, float *y)
{
   funcname1 = "IssuePointOrderById";
   SpyJassLog(" Exec:IssuePointOrderById[unit:%s, order:%s, x:%.4g, y:%.4g]...",GetUnitHID(unit).c_str( ), GetStrID(order).c_str( ), (*x), (*y));
   BOOL returnvalue; 
   returnvalue = IssuePointOrderById_ptr(unit, order, x, y);
   SpyJassLog("[IssuePointOrderById] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssuePointOrderByIdLoc_my(HUNIT unit, int order, HLOCATION Location)
{
   funcname1 = "IssuePointOrderByIdLoc";
   SpyJassLog(" Exec:IssuePointOrderByIdLoc[unit:%s, order:%s, Location:%s]...",GetUnitHID(unit).c_str( ), GetStrID(order).c_str( ), GetStrID(Location).c_str( ));
   BOOL returnvalue; 
   returnvalue = IssuePointOrderByIdLoc_ptr(unit, order, Location);
   SpyJassLog("[IssuePointOrderByIdLoc] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssuePointOrderLoc_my(HUNIT unit, CJassString order, HLOCATION Location)
{
   funcname1 = "IssuePointOrderLoc";
   SpyJassLog(" Exec:IssuePointOrderLoc[unit:%s, order:%s, Location:%s]...",GetUnitHID(unit).c_str( ), ReadJassStringNormal(order), GetStrID(Location).c_str( ));
   BOOL returnvalue; 
   returnvalue = IssuePointOrderLoc_ptr(unit, order, Location);
   SpyJassLog("[IssuePointOrderLoc] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssueTargetOrder_my(HUNIT unit, CJassString order, HWIDGET targetWidget)
{
   funcname1 = "IssueTargetOrder";
   SpyJassLog(" Exec:IssueTargetOrder[unit:%s, order:%s, targetWidget:%s]...",GetUnitHID(unit).c_str( ), ReadJassStringNormal(order), GetStrID(targetWidget).c_str( ));
   BOOL returnvalue; 
   returnvalue = IssueTargetOrder_ptr(unit, order, targetWidget);
   SpyJassLog("[IssueTargetOrder] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl IssueTargetOrderById_my(HUNIT unit, int order, HWIDGET targetWidget)
{
   funcname1 = "IssueTargetOrderById";
   SpyJassLog(" Exec:IssueTargetOrderById[unit:%s, order:%s, targetWidget:%s]...",GetUnitHID(unit).c_str( ), GetStrID(order).c_str( ), GetStrID(targetWidget).c_str( ));
   BOOL returnvalue; 
   returnvalue = IssueTargetOrderById_ptr(unit, order, targetWidget);
   SpyJassLog("[IssueTargetOrderById] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl ItemPoolAddItemType_my(HITEMPOOL ItemPool, int itemId, float *weight)
{
   funcname1 = "ItemPoolAddItemType";
   SpyJassLog(" Exec:ItemPoolAddItemType...");
   ItemPoolAddItemType_ptr(ItemPool, itemId, weight);
   SpyJassLog("[ItemPoolAddItemType] OK [ItemPool:%s, itemId:%s, weight:%.4g]\n",GetStrID(ItemPool).c_str( ), GetStrID(itemId).c_str( ), (*weight));
}
void _cdecl ItemPoolRemoveItemType_my(HITEMPOOL ItemPool, int itemId)
{
   funcname1 = "ItemPoolRemoveItemType";
   SpyJassLog(" Exec:ItemPoolRemoveItemType...");
   ItemPoolRemoveItemType_ptr(ItemPool, itemId);
   SpyJassLog("[ItemPoolRemoveItemType] OK [ItemPool:%s, itemId:%s]\n",GetStrID(ItemPool).c_str( ), GetStrID(itemId).c_str( ));
}
void _cdecl KillDestructable_my(HDESTRUCTABLE d)
{
   funcname1 = "KillDestructable";
   SpyJassLog(" Exec:KillDestructable...");
   KillDestructable_ptr(d);
   SpyJassLog("[KillDestructable] OK [d:%s]\n",GetStrID(d).c_str( ));
}
void _cdecl KillSoundWhenDone_my(HSOUND soundHandle)
{
   funcname1 = "KillSoundWhenDone";
   SpyJassLog(" Exec:KillSoundWhenDone...");
   KillSoundWhenDone_ptr(soundHandle);
   SpyJassLog("[KillSoundWhenDone] OK [soundHandle:%s]\n",GetStrID(soundHandle).c_str( ));
}
void _cdecl KillUnit_my(HUNIT unit)
{
   funcname1 = "KillUnit";
   SpyJassLog(" Exec:KillUnit...");
   KillUnit_ptr(unit);
   SpyJassLog("[KillUnit] OK [unit:%s]\n",GetUnitHID(unit).c_str( ));
}
void _cdecl LeaderboardAddItem_my(HLEADERBOARD lb, CJassString label, int value, HPLAYER p)
{
   funcname1 = "LeaderboardAddItem";
   SpyJassLog(" Exec:LeaderboardAddItem...");
   LeaderboardAddItem_ptr(lb, label, value, p);
   SpyJassLog("[LeaderboardAddItem] OK [lb:%s, label:%s, value:%s, p:%i]\n",GetStrID(lb).c_str( ), ReadJassStringNormal(label), GetStrID(value).c_str( ), GetPlayerId_ptr(p));
}
void _cdecl LeaderboardClear_my(HLEADERBOARD lb)
{
   funcname1 = "LeaderboardClear";
   SpyJassLog(" Exec:LeaderboardClear...");
   LeaderboardClear_ptr(lb);
   SpyJassLog("[LeaderboardClear] OK [lb:%s]\n",GetStrID(lb).c_str( ));
}
void _cdecl LeaderboardDisplay_my(HLEADERBOARD lb, BOOL show)
{
   funcname1 = "LeaderboardDisplay";
   SpyJassLog(" Exec:LeaderboardDisplay...");
   LeaderboardDisplay_ptr(lb, show);
   SpyJassLog("[LeaderboardDisplay] OK [lb:%s, show:%s]\n",GetStrID(lb).c_str( ), BoolToStr(show));
}
int _cdecl LeaderboardGetItemCount_my(HLEADERBOARD lb)
{
   funcname1 = "LeaderboardGetItemCount";
   SpyJassLog(" Exec:LeaderboardGetItemCount[lb:%s]...",GetStrID(lb).c_str( ));
   int returnvalue; 
   returnvalue = LeaderboardGetItemCount_ptr(lb);
   SpyJassLog("[LeaderboardGetItemCount] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
CJassStringSID _cdecl LeaderboardGetLabelText_my(HLEADERBOARD lb)
{
   funcname1 = "LeaderboardGetLabelText";
   SpyJassLog(" Exec:LeaderboardGetLabelText[lb:%s]...",GetStrID(lb).c_str( ));
   CJassStringSID returnvalue; 
   returnvalue = LeaderboardGetLabelText_ptr(lb);
   SpyJassLog("[LeaderboardGetLabelText] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
int _cdecl LeaderboardGetPlayerIndex_my(HLEADERBOARD lb, HPLAYER p)
{
   funcname1 = "LeaderboardGetPlayerIndex";
   SpyJassLog(" Exec:LeaderboardGetPlayerIndex[lb:%s, p:%i]...",GetStrID(lb).c_str( ), GetPlayerId_ptr(p));
   int returnvalue; 
   returnvalue = LeaderboardGetPlayerIndex_ptr(lb, p);
   SpyJassLog("[LeaderboardGetPlayerIndex] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
BOOL _cdecl LeaderboardHasPlayerItem_my(HLEADERBOARD lb, HPLAYER p)
{
   funcname1 = "LeaderboardHasPlayerItem";
   SpyJassLog(" Exec:LeaderboardHasPlayerItem[lb:%s, p:%i]...",GetStrID(lb).c_str( ), GetPlayerId_ptr(p));
   BOOL returnvalue; 
   returnvalue = LeaderboardHasPlayerItem_ptr(lb, p);
   SpyJassLog("[LeaderboardHasPlayerItem] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl LeaderboardRemoveItem_my(HLEADERBOARD lb, int index)
{
   funcname1 = "LeaderboardRemoveItem";
   SpyJassLog(" Exec:LeaderboardRemoveItem...");
   LeaderboardRemoveItem_ptr(lb, index);
   SpyJassLog("[LeaderboardRemoveItem] OK [lb:%s, index:%s]\n",GetStrID(lb).c_str( ), GetStrID(index).c_str( ));
}
void _cdecl LeaderboardRemovePlayerItem_my(HLEADERBOARD lb, HPLAYER p)
{
   funcname1 = "LeaderboardRemovePlayerItem";
   SpyJassLog(" Exec:LeaderboardRemovePlayerItem...");
   LeaderboardRemovePlayerItem_ptr(lb, p);
   SpyJassLog("[LeaderboardRemovePlayerItem] OK [lb:%s, p:%i]\n",GetStrID(lb).c_str( ), GetPlayerId_ptr(p));
}
void _cdecl LeaderboardSetItemLabel_my(HLEADERBOARD lb, int item, CJassString val)
{
   funcname1 = "LeaderboardSetItemLabel";
   SpyJassLog(" Exec:LeaderboardSetItemLabel...");
   LeaderboardSetItemLabel_ptr(lb, item, val);
   SpyJassLog("[LeaderboardSetItemLabel] OK [lb:%s, item:%s, val:%s]\n",GetStrID(lb).c_str( ), GetStrID(item).c_str( ), ReadJassStringNormal(val));
}
void _cdecl LeaderboardSetItemLabelColor_my(HLEADERBOARD lb, int item, int red, int green, int blue, int alpha)
{
   funcname1 = "LeaderboardSetItemLabelColor";
   SpyJassLog(" Exec:LeaderboardSetItemLabelColor...");
   LeaderboardSetItemLabelColor_ptr(lb, item, red, green, blue, alpha);
   SpyJassLog("[LeaderboardSetItemLabelColor] OK [lb:%s, item:%s, red:%s, green:%s, blue:%s, alpha:%s]\n",GetStrID(lb).c_str( ), GetStrID(item).c_str( ), GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), GetStrID(alpha).c_str( ));
}
void _cdecl LeaderboardSetItemStyle_my(HLEADERBOARD lb, int item, BOOL showLabel, BOOL showValue, BOOL showIcon)
{
   funcname1 = "LeaderboardSetItemStyle";
   SpyJassLog(" Exec:LeaderboardSetItemStyle...");
   LeaderboardSetItemStyle_ptr(lb, item, showLabel, showValue, showIcon);
   SpyJassLog("[LeaderboardSetItemStyle] OK [lb:%s, item:%s, showLabel:%s, showValue:%s, showIcon:%s]\n",GetStrID(lb).c_str( ), GetStrID(item).c_str( ), BoolToStr(showLabel), BoolToStr(showValue), BoolToStr(showIcon));
}
void _cdecl LeaderboardSetItemValue_my(HLEADERBOARD lb, int item, int val)
{
   funcname1 = "LeaderboardSetItemValue";
   SpyJassLog(" Exec:LeaderboardSetItemValue...");
   LeaderboardSetItemValue_ptr(lb, item, val);
   SpyJassLog("[LeaderboardSetItemValue] OK [lb:%s, item:%s, val:%s]\n",GetStrID(lb).c_str( ), GetStrID(item).c_str( ), GetStrID(val).c_str( ));
}
void _cdecl LeaderboardSetItemValueColor_my(HLEADERBOARD lb, int item, int red, int green, int blue, int alpha)
{
   funcname1 = "LeaderboardSetItemValueColor";
   SpyJassLog(" Exec:LeaderboardSetItemValueColor...");
   LeaderboardSetItemValueColor_ptr(lb, item, red, green, blue, alpha);
   SpyJassLog("[LeaderboardSetItemValueColor] OK [lb:%s, item:%s, red:%s, green:%s, blue:%s, alpha:%s]\n",GetStrID(lb).c_str( ), GetStrID(item).c_str( ), GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), GetStrID(alpha).c_str( ));
}
void _cdecl LeaderboardSetLabel_my(HLEADERBOARD lb, CJassString label)
{
   funcname1 = "LeaderboardSetLabel";
   SpyJassLog(" Exec:LeaderboardSetLabel...");
   LeaderboardSetLabel_ptr(lb, label);
   SpyJassLog("[LeaderboardSetLabel] OK [lb:%s, label:%s]\n",GetStrID(lb).c_str( ), ReadJassStringNormal(label));
}
void _cdecl LeaderboardSetLabelColor_my(HLEADERBOARD lb, int red, int green, int blue, int alpha)
{
   funcname1 = "LeaderboardSetLabelColor";
   SpyJassLog(" Exec:LeaderboardSetLabelColor...");
   LeaderboardSetLabelColor_ptr(lb, red, green, blue, alpha);
   SpyJassLog("[LeaderboardSetLabelColor] OK [lb:%s, red:%s, green:%s, blue:%s, alpha:%s]\n",GetStrID(lb).c_str( ), GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), GetStrID(alpha).c_str( ));
}
void _cdecl LeaderboardSetSizeByItemCount_my(HLEADERBOARD lb, int count)
{
   funcname1 = "LeaderboardSetSizeByItemCount";
   SpyJassLog(" Exec:LeaderboardSetSizeByItemCount...");
   LeaderboardSetSizeByItemCount_ptr(lb, count);
   SpyJassLog("[LeaderboardSetSizeByItemCount] OK [lb:%s, count:%s]\n",GetStrID(lb).c_str( ), GetStrID(count).c_str( ));
}
void _cdecl LeaderboardSetStyle_my(HLEADERBOARD lb, BOOL showLabel, BOOL showNames, BOOL showValues, BOOL showIcons)
{
   funcname1 = "LeaderboardSetStyle";
   SpyJassLog(" Exec:LeaderboardSetStyle...");
   LeaderboardSetStyle_ptr(lb, showLabel, showNames, showValues, showIcons);
   SpyJassLog("[LeaderboardSetStyle] OK [lb:%s, showLabel:%s, showNames:%s, showValues:%s, showIcons:%s]\n",GetStrID(lb).c_str( ), BoolToStr(showLabel), BoolToStr(showNames), BoolToStr(showValues), BoolToStr(showIcons));
}
void _cdecl LeaderboardSetValueColor_my(HLEADERBOARD lb, int red, int green, int blue, int alpha)
{
   funcname1 = "LeaderboardSetValueColor";
   SpyJassLog(" Exec:LeaderboardSetValueColor...");
   LeaderboardSetValueColor_ptr(lb, red, green, blue, alpha);
   SpyJassLog("[LeaderboardSetValueColor] OK [lb:%s, red:%s, green:%s, blue:%s, alpha:%s]\n",GetStrID(lb).c_str( ), GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), GetStrID(alpha).c_str( ));
}
void _cdecl LeaderboardSortItemsByLabel_my(HLEADERBOARD lb, BOOL ascending)
{
   funcname1 = "LeaderboardSortItemsByLabel";
   SpyJassLog(" Exec:LeaderboardSortItemsByLabel...");
   LeaderboardSortItemsByLabel_ptr(lb, ascending);
   SpyJassLog("[LeaderboardSortItemsByLabel] OK [lb:%s, ascending:%s]\n",GetStrID(lb).c_str( ), BoolToStr(ascending));
}
void _cdecl LeaderboardSortItemsByPlayer_my(HLEADERBOARD lb, BOOL ascending)
{
   funcname1 = "LeaderboardSortItemsByPlayer";
   SpyJassLog(" Exec:LeaderboardSortItemsByPlayer...");
   LeaderboardSortItemsByPlayer_ptr(lb, ascending);
   SpyJassLog("[LeaderboardSortItemsByPlayer] OK [lb:%s, ascending:%s]\n",GetStrID(lb).c_str( ), BoolToStr(ascending));
}
void _cdecl LeaderboardSortItemsByValue_my(HLEADERBOARD lb, BOOL ascending)
{
   funcname1 = "LeaderboardSortItemsByValue";
   SpyJassLog(" Exec:LeaderboardSortItemsByValue...");
   LeaderboardSortItemsByValue_ptr(lb, ascending);
   SpyJassLog("[LeaderboardSortItemsByValue] OK [lb:%s, ascending:%s]\n",GetStrID(lb).c_str( ), BoolToStr(ascending));
}
HABILITY _cdecl LoadAbilityHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadAbilityHandle";
   SpyJassLog(" Exec:LoadAbilityHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HABILITY returnvalue; 
   returnvalue = LoadAbilityHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadAbilityHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
BOOL _cdecl LoadBoolean_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadBoolean";
   SpyJassLog(" Exec:LoadBoolean[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   BOOL returnvalue; 
   returnvalue = LoadBoolean_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadBoolean] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
HBOOLEXPR _cdecl LoadBooleanExprHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadBooleanExprHandle";
   SpyJassLog(" Exec:LoadBooleanExprHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HBOOLEXPR returnvalue; 
   returnvalue = LoadBooleanExprHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadBooleanExprHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HBUTTON _cdecl LoadButtonHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadButtonHandle";
   SpyJassLog(" Exec:LoadButtonHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HBUTTON returnvalue; 
   returnvalue = LoadButtonHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadButtonHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HDEFEATCONDITION _cdecl LoadDefeatConditionHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadDefeatConditionHandle";
   SpyJassLog(" Exec:LoadDefeatConditionHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HDEFEATCONDITION returnvalue; 
   returnvalue = LoadDefeatConditionHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadDefeatConditionHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HDESTRUCTABLE _cdecl LoadDestructableHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadDestructableHandle";
   SpyJassLog(" Exec:LoadDestructableHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HDESTRUCTABLE returnvalue; 
   returnvalue = LoadDestructableHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadDestructableHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HDIALOG _cdecl LoadDialogHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadDialogHandle";
   SpyJassLog(" Exec:LoadDialogHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HDIALOG returnvalue; 
   returnvalue = LoadDialogHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadDialogHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEFFECT _cdecl LoadEffectHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadEffectHandle";
   SpyJassLog(" Exec:LoadEffectHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HEFFECT returnvalue; 
   returnvalue = LoadEffectHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadEffectHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HFOGMODIFIER _cdecl LoadFogModifierHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadFogModifierHandle";
   SpyJassLog(" Exec:LoadFogModifierHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HFOGMODIFIER returnvalue; 
   returnvalue = LoadFogModifierHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadFogModifierHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HFOGSTATE _cdecl LoadFogStateHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadFogStateHandle";
   SpyJassLog(" Exec:LoadFogStateHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HFOGSTATE returnvalue; 
   returnvalue = LoadFogStateHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadFogStateHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HFORCE _cdecl LoadForceHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadForceHandle";
   SpyJassLog(" Exec:LoadForceHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HFORCE returnvalue; 
   returnvalue = LoadForceHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadForceHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl LoadGame_my(CJassString saveFileName, BOOL doScoreScreen)
{
   funcname1 = "LoadGame";
   SpyJassLog(" Exec:LoadGame...");
   LoadGame_ptr(saveFileName, doScoreScreen);
   SpyJassLog("[LoadGame] OK [saveFileName:%s, doScoreScreen:%s]\n",ReadJassStringNormal(saveFileName), BoolToStr(doScoreScreen));
}
HGROUP _cdecl LoadGroupHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadGroupHandle";
   SpyJassLog(" Exec:LoadGroupHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HGROUP returnvalue; 
   returnvalue = LoadGroupHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadGroupHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HHASHTABLE _cdecl LoadHashtableHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadHashtableHandle";
   SpyJassLog(" Exec:LoadHashtableHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HHASHTABLE returnvalue; 
   returnvalue = LoadHashtableHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadHashtableHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HIMAGE _cdecl LoadImageHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadImageHandle";
   SpyJassLog(" Exec:LoadImageHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HIMAGE returnvalue; 
   returnvalue = LoadImageHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadImageHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl LoadInteger_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadInteger";
   SpyJassLog(" Exec:LoadInteger[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   int returnvalue; 
   returnvalue = LoadInteger_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadInteger] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HITEM _cdecl LoadItemHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadItemHandle";
   SpyJassLog(" Exec:LoadItemHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HITEM returnvalue; 
   returnvalue = LoadItemHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadItemHandle] OK [%s]\n",GetItemHID(returnvalue).c_str( ));
   return returnvalue;
}
HITEMPOOL _cdecl LoadItemPoolHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadItemPoolHandle";
   SpyJassLog(" Exec:LoadItemPoolHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HITEMPOOL returnvalue; 
   returnvalue = LoadItemPoolHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadItemPoolHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HLEADERBOARD _cdecl LoadLeaderboardHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadLeaderboardHandle";
   SpyJassLog(" Exec:LoadLeaderboardHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HLEADERBOARD returnvalue; 
   returnvalue = LoadLeaderboardHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadLeaderboardHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HLIGHTNING _cdecl LoadLightningHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadLightningHandle";
   SpyJassLog(" Exec:LoadLightningHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HLIGHTNING returnvalue; 
   returnvalue = LoadLightningHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadLightningHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HLOCATION _cdecl LoadLocationHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadLocationHandle";
   SpyJassLog(" Exec:LoadLocationHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HLOCATION returnvalue; 
   returnvalue = LoadLocationHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadLocationHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HMULTIBOARD _cdecl LoadMultiboardHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadMultiboardHandle";
   SpyJassLog(" Exec:LoadMultiboardHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HMULTIBOARD returnvalue; 
   returnvalue = LoadMultiboardHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadMultiboardHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HMULTIBOARDITEM _cdecl LoadMultiboardItemHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadMultiboardItemHandle";
   SpyJassLog(" Exec:LoadMultiboardItemHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HMULTIBOARDITEM returnvalue; 
   returnvalue = LoadMultiboardItemHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadMultiboardItemHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HPLAYER _cdecl LoadPlayerHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadPlayerHandle";
   SpyJassLog(" Exec:LoadPlayerHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HPLAYER returnvalue; 
   returnvalue = LoadPlayerHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadPlayerHandle] OK [%i]\n",GetPlayerId_ptr(returnvalue));
   return returnvalue;
}
HQUEST _cdecl LoadQuestHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadQuestHandle";
   SpyJassLog(" Exec:LoadQuestHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HQUEST returnvalue; 
   returnvalue = LoadQuestHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadQuestHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HQUESTITEM _cdecl LoadQuestItemHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadQuestItemHandle";
   SpyJassLog(" Exec:LoadQuestItemHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HQUESTITEM returnvalue; 
   returnvalue = LoadQuestItemHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadQuestItemHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl LoadReal_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadReal";
   SpyJassLog(" Exec:LoadReal[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   DWFP returnvalue; 
   returnvalue = LoadReal_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadReal] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
HRECT _cdecl LoadRectHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadRectHandle";
   SpyJassLog(" Exec:LoadRectHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HRECT returnvalue; 
   returnvalue = LoadRectHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadRectHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HREGION _cdecl LoadRegionHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadRegionHandle";
   SpyJassLog(" Exec:LoadRegionHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HREGION returnvalue; 
   returnvalue = LoadRegionHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadRegionHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HSOUND _cdecl LoadSoundHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadSoundHandle";
   SpyJassLog(" Exec:LoadSoundHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HSOUND returnvalue; 
   returnvalue = LoadSoundHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadSoundHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
CJassStringSID _cdecl LoadStr_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadStr";
   SpyJassLog(" Exec:LoadStr[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   CJassStringSID returnvalue; 
   returnvalue = LoadStr_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadStr] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
HTEXTTAG _cdecl LoadTextTagHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadTextTagHandle";
   SpyJassLog(" Exec:LoadTextTagHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HTEXTTAG returnvalue; 
   returnvalue = LoadTextTagHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadTextTagHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTIMERDIALOG _cdecl LoadTimerDialogHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadTimerDialogHandle";
   SpyJassLog(" Exec:LoadTimerDialogHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HTIMERDIALOG returnvalue; 
   returnvalue = LoadTimerDialogHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadTimerDialogHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTIMER _cdecl LoadTimerHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadTimerHandle";
   SpyJassLog(" Exec:LoadTimerHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HTIMER returnvalue; 
   returnvalue = LoadTimerHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadTimerHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTRACKABLE _cdecl LoadTrackableHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadTrackableHandle";
   SpyJassLog(" Exec:LoadTrackableHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HTRACKABLE returnvalue; 
   returnvalue = LoadTrackableHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadTrackableHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTRIGGERACTION _cdecl LoadTriggerActionHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadTriggerActionHandle";
   SpyJassLog(" Exec:LoadTriggerActionHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HTRIGGERACTION returnvalue; 
   returnvalue = LoadTriggerActionHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadTriggerActionHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTRIGGERCONDITION _cdecl LoadTriggerConditionHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadTriggerConditionHandle";
   SpyJassLog(" Exec:LoadTriggerConditionHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HTRIGGERCONDITION returnvalue; 
   returnvalue = LoadTriggerConditionHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadTriggerConditionHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl LoadTriggerEventHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadTriggerEventHandle";
   SpyJassLog(" Exec:LoadTriggerEventHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HEVENT returnvalue; 
   returnvalue = LoadTriggerEventHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadTriggerEventHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTRIGGER _cdecl LoadTriggerHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadTriggerHandle";
   SpyJassLog(" Exec:LoadTriggerHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HTRIGGER returnvalue; 
   returnvalue = LoadTriggerHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadTriggerHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUBERSPLAT _cdecl LoadUbersplatHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadUbersplatHandle";
   SpyJassLog(" Exec:LoadUbersplatHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HUBERSPLAT returnvalue; 
   returnvalue = LoadUbersplatHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadUbersplatHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HUNIT _cdecl LoadUnitHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadUnitHandle";
   SpyJassLog(" Exec:LoadUnitHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HUNIT returnvalue; 
   returnvalue = LoadUnitHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadUnitHandle] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNITPOOL _cdecl LoadUnitPoolHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadUnitPoolHandle";
   SpyJassLog(" Exec:LoadUnitPoolHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HUNITPOOL returnvalue; 
   returnvalue = LoadUnitPoolHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadUnitPoolHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HWIDGET _cdecl LoadWidgetHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "LoadWidgetHandle";
   SpyJassLog(" Exec:LoadWidgetHandle[table:%s, parentKey:%s, childKey:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
   HWIDGET returnvalue; 
   returnvalue = LoadWidgetHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[LoadWidgetHandle] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl LoadZepWave_my(int arg1, int arg2)
{
   funcname1 = "LoadZepWave";
   SpyJassLog(" Exec:LoadZepWave...");
   LoadZepWave_ptr(arg1, arg2);
   SpyJassLog("[LoadZepWave] OK [arg1:%s, arg2:%s]\n",GetStrID(arg1).c_str( ), GetStrID(arg2).c_str( ));
}
HLOCATION _cdecl Location_my(float *x, float *y)
{
   funcname1 = "Location";
   SpyJassLog(" Exec:Location[x:%.4g, y:%.4g]...",(*x), (*y));
   HLOCATION returnvalue; 
   returnvalue = Location_ptr(x, y);
   SpyJassLog("[Location] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl MeleeDifficulty_my()
{
   funcname1 = "MeleeDifficulty";
   SpyJassLog(" Exec:MeleeDifficulty[]...");
   int returnvalue; 
   returnvalue = MeleeDifficulty_ptr();
   SpyJassLog("[MeleeDifficulty] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
BOOL _cdecl MergeUnits_my(int arg1, int arg2, int arg3, int arg4)
{
   funcname1 = "MergeUnits";
   SpyJassLog(" Exec:MergeUnits[arg1:%s, arg2:%s, arg3:%s, arg4:%s]...",GetStrID(arg1).c_str( ), GetStrID(arg2).c_str( ), GetStrID(arg3).c_str( ), GetStrID(arg4).c_str( ));
   BOOL returnvalue; 
   returnvalue = MergeUnits_ptr(arg1, arg2, arg3, arg4);
   SpyJassLog("[MergeUnits] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl MoveLightning_my(HLIGHTNING Bolt, BOOL checkVisibility, float *x1, float *y1, float *x2, float *y2)
{
   funcname1 = "MoveLightning";
   SpyJassLog(" Exec:MoveLightning[Bolt:%s, checkVisibility:%s, x1:%.4g, y1:%.4g, x2:%.4g, y2:%.4g]...",GetStrID(Bolt).c_str( ), BoolToStr(checkVisibility), (*x1), (*y1), (*x2), (*y2));
   BOOL returnvalue; 
   returnvalue = MoveLightning_ptr(Bolt, checkVisibility, x1, y1, x2, y2);
   SpyJassLog("[MoveLightning] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl MoveLightningEx_my(HLIGHTNING Bolt, BOOL checkVisibility, float *x1, float *y1, float *z1, float *x2, float *y2, float *z2)
{
   funcname1 = "MoveLightningEx";
   SpyJassLog(" Exec:MoveLightningEx[Bolt:%s, checkVisibility:%s, x1:%.4g, y1:%.4g, z1:%.4g, x2:%.4g, y2:%.4g, z2:%.4g]...",GetStrID(Bolt).c_str( ), BoolToStr(checkVisibility), (*x1), (*y1), (*z1), (*x2), (*y2), (*z2));
   BOOL returnvalue; 
   returnvalue = MoveLightningEx_ptr(Bolt, checkVisibility, x1, y1, z1, x2, y2, z2);
   SpyJassLog("[MoveLightningEx] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl MoveLocation_my(HLOCATION Location, float *newX, float *newY)
{
   funcname1 = "MoveLocation";
   SpyJassLog(" Exec:MoveLocation...");
   MoveLocation_ptr(Location, newX, newY);
   SpyJassLog("[MoveLocation] OK [Location:%s, newX:%.4g, newY:%.4g]\n",GetStrID(Location).c_str( ), (*newX), (*newY));
}
void _cdecl MoveRectTo_my(HRECT Rect, float *newCenterX, float *newCenterY)
{
   funcname1 = "MoveRectTo";
   SpyJassLog(" Exec:MoveRectTo...");
   MoveRectTo_ptr(Rect, newCenterX, newCenterY);
   SpyJassLog("[MoveRectTo] OK [Rect:%s, newCenterX:%.4g, newCenterY:%.4g]\n",GetStrID(Rect).c_str( ), (*newCenterX), (*newCenterY));
}
void _cdecl MoveRectToLoc_my(HRECT Rect, HLOCATION newCenterLoc)
{
   funcname1 = "MoveRectToLoc";
   SpyJassLog(" Exec:MoveRectToLoc...");
   MoveRectToLoc_ptr(Rect, newCenterLoc);
   SpyJassLog("[MoveRectToLoc] OK [Rect:%s, newCenterLoc:%s]\n",GetStrID(Rect).c_str( ), GetStrID(newCenterLoc).c_str( ));
}
void _cdecl MultiboardClear_my(HMULTIBOARD lb)
{
   funcname1 = "MultiboardClear";
   SpyJassLog(" Exec:MultiboardClear...");
   MultiboardClear_ptr(lb);
   SpyJassLog("[MultiboardClear] OK [lb:%s]\n",GetStrID(lb).c_str( ));
}
void _cdecl MultiboardDisplay_my(HMULTIBOARD lb, BOOL show)
{
   funcname1 = "MultiboardDisplay";
   SpyJassLog(" Exec:MultiboardDisplay...");
   MultiboardDisplay_ptr(lb, show);
   SpyJassLog("[MultiboardDisplay] OK [lb:%s, show:%s]\n",GetStrID(lb).c_str( ), BoolToStr(show));
}
int _cdecl MultiboardGetColumnCount_my(HMULTIBOARD lb)
{
   funcname1 = "MultiboardGetColumnCount";
   SpyJassLog(" Exec:MultiboardGetColumnCount[lb:%s]...",GetStrID(lb).c_str( ));
   int returnvalue; 
   returnvalue = MultiboardGetColumnCount_ptr(lb);
   SpyJassLog("[MultiboardGetColumnCount] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HMULTIBOARDITEM _cdecl MultiboardGetItem_my(HMULTIBOARD lb, int row, int column)
{
   funcname1 = "MultiboardGetItem";
   SpyJassLog(" Exec:MultiboardGetItem[lb:%s, row:%s, column:%s]...",GetStrID(lb).c_str( ), GetStrID(row).c_str( ), GetStrID(column).c_str( ));
   HMULTIBOARDITEM returnvalue; 
   returnvalue = MultiboardGetItem_ptr(lb, row, column);
   SpyJassLog("[MultiboardGetItem] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl MultiboardGetRowCount_my(HMULTIBOARD lb)
{
   funcname1 = "MultiboardGetRowCount";
   SpyJassLog(" Exec:MultiboardGetRowCount[lb:%s]...",GetStrID(lb).c_str( ));
   int returnvalue; 
   returnvalue = MultiboardGetRowCount_ptr(lb);
   SpyJassLog("[MultiboardGetRowCount] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
CJassStringSID _cdecl MultiboardGetTitleText_my(HMULTIBOARD lb)
{
   funcname1 = "MultiboardGetTitleText";
   SpyJassLog(" Exec:MultiboardGetTitleText[lb:%s]...",GetStrID(lb).c_str( ));
   CJassStringSID returnvalue; 
   returnvalue = MultiboardGetTitleText_ptr(lb);
   SpyJassLog("[MultiboardGetTitleText] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
void _cdecl MultiboardMinimize_my(HMULTIBOARD lb, BOOL minimize)
{
   funcname1 = "MultiboardMinimize";
   SpyJassLog(" Exec:MultiboardMinimize...");
   MultiboardMinimize_ptr(lb, minimize);
   SpyJassLog("[MultiboardMinimize] OK [lb:%s, minimize:%s]\n",GetStrID(lb).c_str( ), BoolToStr(minimize));
}
void _cdecl MultiboardReleaseItem_my(HMULTIBOARDITEM mbi)
{
   funcname1 = "MultiboardReleaseItem";
   SpyJassLog(" Exec:MultiboardReleaseItem...");
   MultiboardReleaseItem_ptr(mbi);
   SpyJassLog("[MultiboardReleaseItem] OK [mbi:%s]\n",GetStrID(mbi).c_str( ));
}
void _cdecl MultiboardSetColumnCount_my(HMULTIBOARD lb, int count)
{
   funcname1 = "MultiboardSetColumnCount";
   SpyJassLog(" Exec:MultiboardSetColumnCount...");
   MultiboardSetColumnCount_ptr(lb, count);
   SpyJassLog("[MultiboardSetColumnCount] OK [lb:%s, count:%s]\n",GetStrID(lb).c_str( ), GetStrID(count).c_str( ));
}
void _cdecl MultiboardSetItemIcon_my(HMULTIBOARDITEM mbi, CJassString iconFileName)
{
   funcname1 = "MultiboardSetItemIcon";
   SpyJassLog(" Exec:MultiboardSetItemIcon...");
   MultiboardSetItemIcon_ptr(mbi, iconFileName);
   SpyJassLog("[MultiboardSetItemIcon] OK [mbi:%s, iconFileName:%s]\n",GetStrID(mbi).c_str( ), ReadJassStringNormal(iconFileName));
}
void _cdecl MultiboardSetItemStyle_my(HMULTIBOARDITEM mbi, BOOL showValue, BOOL showIcon)
{
   funcname1 = "MultiboardSetItemStyle";
   SpyJassLog(" Exec:MultiboardSetItemStyle...");
   MultiboardSetItemStyle_ptr(mbi, showValue, showIcon);
   SpyJassLog("[MultiboardSetItemStyle] OK [mbi:%s, showValue:%s, showIcon:%s]\n",GetStrID(mbi).c_str( ), BoolToStr(showValue), BoolToStr(showIcon));
}
void _cdecl MultiboardSetItemValue_my(HMULTIBOARDITEM mbi, CJassString val)
{
   funcname1 = "MultiboardSetItemValue";
   SpyJassLog(" Exec:MultiboardSetItemValue...");
   MultiboardSetItemValue_ptr(mbi, val);
   SpyJassLog("[MultiboardSetItemValue] OK [mbi:%s, val:%s]\n",GetStrID(mbi).c_str( ), ReadJassStringNormal(val));
}
void _cdecl MultiboardSetItemValueColor_my(HMULTIBOARDITEM mbi, int red, int green, int blue, int alpha)
{
   funcname1 = "MultiboardSetItemValueColor";
   SpyJassLog(" Exec:MultiboardSetItemValueColor...");
   MultiboardSetItemValueColor_ptr(mbi, red, green, blue, alpha);
   SpyJassLog("[MultiboardSetItemValueColor] OK [mbi:%s, red:%s, green:%s, blue:%s, alpha:%s]\n",GetStrID(mbi).c_str( ), GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), GetStrID(alpha).c_str( ));
}
void _cdecl MultiboardSetItemWidth_my(HMULTIBOARDITEM mbi, float *width)
{
   funcname1 = "MultiboardSetItemWidth";
   SpyJassLog(" Exec:MultiboardSetItemWidth...");
   MultiboardSetItemWidth_ptr(mbi, width);
   SpyJassLog("[MultiboardSetItemWidth] OK [mbi:%s, width:%.4g]\n",GetStrID(mbi).c_str( ), (*width));
}
void _cdecl MultiboardSetItemsIcon_my(HMULTIBOARD lb, CJassString iconPath)
{
   funcname1 = "MultiboardSetItemsIcon";
   SpyJassLog(" Exec:MultiboardSetItemsIcon...");
   MultiboardSetItemsIcon_ptr(lb, iconPath);
   SpyJassLog("[MultiboardSetItemsIcon] OK [lb:%s, iconPath:%s]\n",GetStrID(lb).c_str( ), ReadJassStringNormal(iconPath));
}
void _cdecl MultiboardSetItemsStyle_my(HMULTIBOARD lb, BOOL showValues, BOOL showIcons)
{
   funcname1 = "MultiboardSetItemsStyle";
   SpyJassLog(" Exec:MultiboardSetItemsStyle...");
   MultiboardSetItemsStyle_ptr(lb, showValues, showIcons);
   SpyJassLog("[MultiboardSetItemsStyle] OK [lb:%s, showValues:%s, showIcons:%s]\n",GetStrID(lb).c_str( ), BoolToStr(showValues), BoolToStr(showIcons));
}
void _cdecl MultiboardSetItemsValue_my(HMULTIBOARD lb, CJassString value)
{
   funcname1 = "MultiboardSetItemsValue";
   SpyJassLog(" Exec:MultiboardSetItemsValue...");
   MultiboardSetItemsValue_ptr(lb, value);
   SpyJassLog("[MultiboardSetItemsValue] OK [lb:%s, value:%s]\n",GetStrID(lb).c_str( ), ReadJassStringNormal(value));
}
void _cdecl MultiboardSetItemsValueColor_my(HMULTIBOARD lb, int red, int green, int blue, int alpha)
{
   funcname1 = "MultiboardSetItemsValueColor";
   SpyJassLog(" Exec:MultiboardSetItemsValueColor...");
   MultiboardSetItemsValueColor_ptr(lb, red, green, blue, alpha);
   SpyJassLog("[MultiboardSetItemsValueColor] OK [lb:%s, red:%s, green:%s, blue:%s, alpha:%s]\n",GetStrID(lb).c_str( ), GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), GetStrID(alpha).c_str( ));
}
void _cdecl MultiboardSetItemsWidth_my(HMULTIBOARD lb, float *width)
{
   funcname1 = "MultiboardSetItemsWidth";
   SpyJassLog(" Exec:MultiboardSetItemsWidth...");
   MultiboardSetItemsWidth_ptr(lb, width);
   SpyJassLog("[MultiboardSetItemsWidth] OK [lb:%s, width:%.4g]\n",GetStrID(lb).c_str( ), (*width));
}
void _cdecl MultiboardSetRowCount_my(HMULTIBOARD lb, int count)
{
   funcname1 = "MultiboardSetRowCount";
   SpyJassLog(" Exec:MultiboardSetRowCount...");
   MultiboardSetRowCount_ptr(lb, count);
   SpyJassLog("[MultiboardSetRowCount] OK [lb:%s, count:%s]\n",GetStrID(lb).c_str( ), GetStrID(count).c_str( ));
}
void _cdecl MultiboardSetTitleText_my(HMULTIBOARD lb, CJassString label)
{
   funcname1 = "MultiboardSetTitleText";
   SpyJassLog(" Exec:MultiboardSetTitleText...");
   MultiboardSetTitleText_ptr(lb, label);
   SpyJassLog("[MultiboardSetTitleText] OK [lb:%s, label:%s]\n",GetStrID(lb).c_str( ), ReadJassStringNormal(label));
}
void _cdecl MultiboardSetTitleTextColor_my(HMULTIBOARD lb, int red, int green, int blue, int alpha)
{
   funcname1 = "MultiboardSetTitleTextColor";
   SpyJassLog(" Exec:MultiboardSetTitleTextColor...");
   MultiboardSetTitleTextColor_ptr(lb, red, green, blue, alpha);
   SpyJassLog("[MultiboardSetTitleTextColor] OK [lb:%s, red:%s, green:%s, blue:%s, alpha:%s]\n",GetStrID(lb).c_str( ), GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), GetStrID(alpha).c_str( ));
}
void _cdecl MultiboardSuppressDisplay_my(BOOL flag)
{
   funcname1 = "MultiboardSuppressDisplay";
   SpyJassLog(" Exec:MultiboardSuppressDisplay...");
   MultiboardSuppressDisplay_ptr(flag);
   SpyJassLog("[MultiboardSuppressDisplay] OK [flag:%s]\n",BoolToStr(flag));
}
void _cdecl NewSoundEnvironment_my(CJassString environmentName)
{
   funcname1 = "NewSoundEnvironment";
   SpyJassLog(" Exec:NewSoundEnvironment...");
   NewSoundEnvironment_ptr(environmentName);
   SpyJassLog("[NewSoundEnvironment] OK [environmentName:%s]\n",ReadJassStringNormal(environmentName));
}
HBOOLEXPR _cdecl Not_my(HBOOLEXPR operand)
{
   funcname1 = "Not";
   SpyJassLog(" Exec:Not[operand:%s]...",GetStrID(operand).c_str( ));
   HBOOLEXPR returnvalue; 
   returnvalue = Not_ptr(operand);
   SpyJassLog("[Not] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HBOOLEXPR _cdecl Or_my(HBOOLEXPR operandA, HBOOLEXPR operandB)
{
   funcname1 = "Or";
   SpyJassLog(" Exec:Or[operandA:%s, operandB:%s]...",GetStrID(operandA).c_str( ), GetStrID(operandB).c_str( ));
   HBOOLEXPR returnvalue; 
   returnvalue = Or_ptr(operandA, operandB);
   SpyJassLog("[Or] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl OrderId_my(CJassString orderIdString)
{
   funcname1 = "OrderId";
   SpyJassLog(" Exec:OrderId[orderIdString:%s]...",ReadJassStringNormal(orderIdString));
   int returnvalue; 
   returnvalue = OrderId_ptr(orderIdString);
   SpyJassLog("[OrderId] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
CJassStringSID _cdecl OrderId2String_my(int orderId)
{
   funcname1 = "OrderId2String";
   SpyJassLog(" Exec:OrderId2String[orderId:%s]...",GetStrID(orderId).c_str( ));
   CJassStringSID returnvalue; 
   returnvalue = OrderId2String_ptr(orderId);
   SpyJassLog("[OrderId2String] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
void _cdecl PanCameraTo_my(float *x, float *y)
{
   funcname1 = "PanCameraTo";
   SpyJassLog(" Exec:PanCameraTo...");
   PanCameraTo_ptr(x, y);
   SpyJassLog("[PanCameraTo] OK [x:%.4g, y:%.4g]\n",(*x), (*y));
}
void _cdecl PanCameraToTimed_my(float *x, float *y, float *duration)
{
   funcname1 = "PanCameraToTimed";
   SpyJassLog(" Exec:PanCameraToTimed...");
   PanCameraToTimed_ptr(x, y, duration);
   SpyJassLog("[PanCameraToTimed] OK [x:%.4g, y:%.4g, duration:%.4g]\n",(*x), (*y), (*duration));
}
void _cdecl PanCameraToTimedWithZ_my(float *x, float *y, float *zOffsetDest, float *duration)
{
   funcname1 = "PanCameraToTimedWithZ";
   SpyJassLog(" Exec:PanCameraToTimedWithZ...");
   PanCameraToTimedWithZ_ptr(x, y, zOffsetDest, duration);
   SpyJassLog("[PanCameraToTimedWithZ] OK [x:%.4g, y:%.4g, zOffsetDest:%.4g, duration:%.4g]\n",(*x), (*y), (*zOffsetDest), (*duration));
}
void _cdecl PanCameraToWithZ_my(float *x, float *y, float *zOffsetDest)
{
   funcname1 = "PanCameraToWithZ";
   SpyJassLog(" Exec:PanCameraToWithZ...");
   PanCameraToWithZ_ptr(x, y, zOffsetDest);
   SpyJassLog("[PanCameraToWithZ] OK [x:%.4g, y:%.4g, zOffsetDest:%.4g]\n",(*x), (*y), (*zOffsetDest));
}
void _cdecl PauseCompAI_my(HPLAYER p, BOOL pause)
{
   funcname1 = "PauseCompAI";
   SpyJassLog(" Exec:PauseCompAI...");
   PauseCompAI_ptr(p, pause);
   SpyJassLog("[PauseCompAI] OK [p:%i, pause:%s]\n",GetPlayerId_ptr(p), BoolToStr(pause));
}
void _cdecl PauseGame_my(BOOL flag)
{
   funcname1 = "PauseGame";
   SpyJassLog(" Exec:PauseGame...");
   PauseGame_ptr(flag);
   SpyJassLog("[PauseGame] OK [flag:%s]\n",BoolToStr(flag));
}
void _cdecl PauseTimer_my(HTIMER Timer)
{
   funcname1 = "PauseTimer";
   SpyJassLog(" Exec:PauseTimer...");
   PauseTimer_ptr(Timer);
   SpyJassLog("[PauseTimer] OK [Timer:%s]\n",GetStrID(Timer).c_str( ));
}
void _cdecl PauseUnit_my(HUNIT unit, BOOL flag)
{
   funcname1 = "PauseUnit";
   SpyJassLog(" Exec:PauseUnit...");
   PauseUnit_ptr(unit, flag);
   SpyJassLog("[PauseUnit] OK [unit:%s, flag:%s]\n",GetUnitHID(unit).c_str( ), BoolToStr(flag));
}
void _cdecl PingMinimap_my(float *x, float *y, float *duration)
{
   funcname1 = "PingMinimap";
   SpyJassLog(" Exec:PingMinimap...");
   PingMinimap_ptr(x, y, duration);
   SpyJassLog("[PingMinimap] OK [x:%.4g, y:%.4g, duration:%.4g]\n",(*x), (*y), (*duration));
}
void _cdecl PingMinimapEx_my(float *x, float *y, float *duration, int red, int green, int blue, BOOL extraEffects)
{
   funcname1 = "PingMinimapEx";
   SpyJassLog(" Exec:PingMinimapEx...");
   PingMinimapEx_ptr(x, y, duration, red, green, blue, extraEffects);
   SpyJassLog("[PingMinimapEx] OK [x:%.4g, y:%.4g, duration:%.4g, red:%s, green:%s, blue:%s, extraEffects:%s]\n",(*x), (*y), (*duration), GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), BoolToStr(extraEffects));
}
HITEM _cdecl PlaceRandomItem_my(HITEMPOOL ItemPool, float *x, float *y)
{
   funcname1 = "PlaceRandomItem";
   SpyJassLog(" Exec:PlaceRandomItem[ItemPool:%s, x:%.4g, y:%.4g]...",GetStrID(ItemPool).c_str( ), (*x), (*y));
   HITEM returnvalue; 
   returnvalue = PlaceRandomItem_ptr(ItemPool, x, y);
   SpyJassLog("[PlaceRandomItem] OK [%s]\n",GetItemHID(returnvalue).c_str( ));
   return returnvalue;
}
HUNIT _cdecl PlaceRandomUnit_my(HUNITPOOL Pool, HPLAYER forWhichPlayer, float *x, float *y, float *facing)
{
   funcname1 = "PlaceRandomUnit";
   SpyJassLog(" Exec:PlaceRandomUnit[Pool:%s, forWhichPlayer:%i, x:%.4g, y:%.4g, facing:%.4g]...",GetStrID(Pool).c_str( ), GetPlayerId_ptr(forWhichPlayer), (*x), (*y), (*facing));
   HUNIT returnvalue; 
   returnvalue = PlaceRandomUnit_ptr(Pool, forWhichPlayer, x, y, facing);
   SpyJassLog("[PlaceRandomUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
void _cdecl PlayCinematic_my(CJassString movieName)
{
   funcname1 = "PlayCinematic";
   SpyJassLog(" Exec:PlayCinematic...");
   PlayCinematic_ptr(movieName);
   SpyJassLog("[PlayCinematic] OK [movieName:%s]\n",ReadJassStringNormal(movieName));
}
void _cdecl PlayModelCinematic_my(CJassString modelName)
{
   funcname1 = "PlayModelCinematic";
   SpyJassLog(" Exec:PlayModelCinematic...");
   PlayModelCinematic_ptr(modelName);
   SpyJassLog("[PlayModelCinematic] OK [modelName:%s]\n",ReadJassStringNormal(modelName));
}
void _cdecl PlayMusic_my(CJassString musicName)
{
   funcname1 = "PlayMusic";
   SpyJassLog(" Exec:PlayMusic...");
   PlayMusic_ptr(musicName);
   SpyJassLog("[PlayMusic] OK [musicName:%s]\n",ReadJassStringNormal(musicName));
}
void _cdecl PlayMusicEx_my(CJassString musicName, int frommsecs, int fadeinmsecs)
{
   funcname1 = "PlayMusicEx";
   SpyJassLog(" Exec:PlayMusicEx...");
   PlayMusicEx_ptr(musicName, frommsecs, fadeinmsecs);
   SpyJassLog("[PlayMusicEx] OK [musicName:%s, frommsecs:%s, fadeinmsecs:%s]\n",ReadJassStringNormal(musicName), GetStrID(frommsecs).c_str( ), GetStrID(fadeinmsecs).c_str( ));
}
void _cdecl PlayThematicMusic_my(CJassString musicFileName)
{
   funcname1 = "PlayThematicMusic";
   SpyJassLog(" Exec:PlayThematicMusic...");
   PlayThematicMusic_ptr(musicFileName);
   SpyJassLog("[PlayThematicMusic] OK [musicFileName:%s]\n",ReadJassStringNormal(musicFileName));
}
void _cdecl PlayThematicMusicEx_my(CJassString musicFileName, int frommsecs)
{
   funcname1 = "PlayThematicMusicEx";
   SpyJassLog(" Exec:PlayThematicMusicEx...");
   PlayThematicMusicEx_ptr(musicFileName, frommsecs);
   SpyJassLog("[PlayThematicMusicEx] OK [musicFileName:%s, frommsecs:%s]\n",ReadJassStringNormal(musicFileName), GetStrID(frommsecs).c_str( ));
}
HPLAYER _cdecl Player_my(int number)
{
   funcname1 = "Player";
   SpyJassLog(" Exec:Player[number:%s]...",GetStrID(number).c_str( ));
   HPLAYER returnvalue; 
   returnvalue = Player_ptr(number);
   SpyJassLog("[Player] OK [%i]\n",GetPlayerId_ptr(returnvalue));
   return returnvalue;
}
HLEADERBOARD _cdecl PlayerGetLeaderboard_my(HPLAYER toPlayer)
{
   funcname1 = "PlayerGetLeaderboard";
   SpyJassLog(" Exec:PlayerGetLeaderboard[toPlayer:%i]...",GetPlayerId_ptr(toPlayer));
   HLEADERBOARD returnvalue; 
   returnvalue = PlayerGetLeaderboard_ptr(toPlayer);
   SpyJassLog("[PlayerGetLeaderboard] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl PlayerSetLeaderboard_my(HPLAYER toPlayer, HLEADERBOARD lb)
{
   funcname1 = "PlayerSetLeaderboard";
   SpyJassLog(" Exec:PlayerSetLeaderboard...");
   PlayerSetLeaderboard_ptr(toPlayer, lb);
   SpyJassLog("[PlayerSetLeaderboard] OK [toPlayer:%i, lb:%s]\n",GetPlayerId_ptr(toPlayer), GetStrID(lb).c_str( ));
}
void _cdecl PopLastCommand_my()
{
   funcname1 = "PopLastCommand";
   SpyJassLog(" Exec:PopLastCommand...");
   PopLastCommand_ptr();
   SpyJassLog("[PopLastCommand] OK []\n");
}
DWFP _cdecl Pow_my(float *x, float *power)
{
   funcname1 = "Pow";
   SpyJassLog(" Exec:Pow[x:%.4g, power:%.4g]...",(*x), (*power));
   DWFP returnvalue; 
   returnvalue = Pow_ptr(x, power);
   SpyJassLog("[Pow] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
void _cdecl Preload_my(CJassString filename)
{
   funcname1 = "Preload";
   SpyJassLog(" Exec:Preload...");
   Preload_ptr(filename);
   SpyJassLog("[Preload] OK [filename:%s]\n",ReadJassStringNormal(filename));
}
void _cdecl PreloadEnd_my(float *timeout)
{
   funcname1 = "PreloadEnd";
   SpyJassLog(" Exec:PreloadEnd...");
   PreloadEnd_ptr(timeout);
   SpyJassLog("[PreloadEnd] OK [timeout:%.4g]\n",(*timeout));
}
void _cdecl PreloadEndEx_my()
{
   funcname1 = "PreloadEndEx";
   SpyJassLog(" Exec:PreloadEndEx...");
   PreloadEndEx_ptr();
   SpyJassLog("[PreloadEndEx] OK []\n");
}
void _cdecl PreloadGenClear_my()
{
   funcname1 = "PreloadGenClear";
   SpyJassLog(" Exec:PreloadGenClear...");
   PreloadGenClear_ptr();
   SpyJassLog("[PreloadGenClear] OK []\n");
}
void _cdecl PreloadGenEnd_my(CJassString filename)
{
   funcname1 = "PreloadGenEnd";
   SpyJassLog(" Exec:PreloadGenEnd...");
   PreloadGenEnd_ptr(filename);
   SpyJassLog("[PreloadGenEnd] OK [filename:%s]\n",ReadJassStringNormal(filename));
}
void _cdecl PreloadGenStart_my()
{
   funcname1 = "PreloadGenStart";
   SpyJassLog(" Exec:PreloadGenStart...");
   PreloadGenStart_ptr();
   SpyJassLog("[PreloadGenStart] OK []\n");
}
void _cdecl PreloadRefresh_my()
{
   funcname1 = "PreloadRefresh";
   SpyJassLog(" Exec:PreloadRefresh...");
   PreloadRefresh_ptr();
   SpyJassLog("[PreloadRefresh] OK []\n");
}
void _cdecl PreloadStart_my()
{
   funcname1 = "PreloadStart";
   SpyJassLog(" Exec:PreloadStart...");
   PreloadStart_ptr();
   SpyJassLog("[PreloadStart] OK []\n");
}
void _cdecl Preloader_my(CJassString filename)
{
   funcname1 = "Preloader";
   SpyJassLog(" Exec:Preloader...");
   Preloader_ptr(filename);
   SpyJassLog("[Preloader] OK [filename:%s]\n",ReadJassStringNormal(filename));
}
void _cdecl PurchaseZeppelin_my()
{
   funcname1 = "PurchaseZeppelin";
   SpyJassLog(" Exec:PurchaseZeppelin...");
   PurchaseZeppelin_ptr();
   SpyJassLog("[PurchaseZeppelin] OK []\n");
}
HQUESTITEM _cdecl QuestCreateItem_my(HQUEST Quest)
{
   funcname1 = "QuestCreateItem";
   SpyJassLog(" Exec:QuestCreateItem[Quest:%s]...",GetStrID(Quest).c_str( ));
   HQUESTITEM returnvalue; 
   returnvalue = QuestCreateItem_ptr(Quest);
   SpyJassLog("[QuestCreateItem] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl QuestItemSetCompleted_my(HQUESTITEM QuestItem, BOOL completed)
{
   funcname1 = "QuestItemSetCompleted";
   SpyJassLog(" Exec:QuestItemSetCompleted...");
   QuestItemSetCompleted_ptr(QuestItem, completed);
   SpyJassLog("[QuestItemSetCompleted] OK [QuestItem:%s, completed:%s]\n",GetStrID(QuestItem).c_str( ), BoolToStr(completed));
}
void _cdecl QuestItemSetDescription_my(HQUESTITEM QuestItem, CJassString description)
{
   funcname1 = "QuestItemSetDescription";
   SpyJassLog(" Exec:QuestItemSetDescription...");
   QuestItemSetDescription_ptr(QuestItem, description);
   SpyJassLog("[QuestItemSetDescription] OK [QuestItem:%s, description:%s]\n",GetStrID(QuestItem).c_str( ), ReadJassStringNormal(description));
}
void _cdecl QuestSetCompleted_my(HQUEST Quest, BOOL completed)
{
   funcname1 = "QuestSetCompleted";
   SpyJassLog(" Exec:QuestSetCompleted...");
   QuestSetCompleted_ptr(Quest, completed);
   SpyJassLog("[QuestSetCompleted] OK [Quest:%s, completed:%s]\n",GetStrID(Quest).c_str( ), BoolToStr(completed));
}
void _cdecl QuestSetDescription_my(HQUEST Quest, CJassString description)
{
   funcname1 = "QuestSetDescription";
   SpyJassLog(" Exec:QuestSetDescription...");
   QuestSetDescription_ptr(Quest, description);
   SpyJassLog("[QuestSetDescription] OK [Quest:%s, description:%s]\n",GetStrID(Quest).c_str( ), ReadJassStringNormal(description));
}
void _cdecl QuestSetDiscovered_my(HQUEST Quest, BOOL discovered)
{
   funcname1 = "QuestSetDiscovered";
   SpyJassLog(" Exec:QuestSetDiscovered...");
   QuestSetDiscovered_ptr(Quest, discovered);
   SpyJassLog("[QuestSetDiscovered] OK [Quest:%s, discovered:%s]\n",GetStrID(Quest).c_str( ), BoolToStr(discovered));
}
void _cdecl QuestSetEnabled_my(HQUEST Quest, BOOL enabled)
{
   funcname1 = "QuestSetEnabled";
   SpyJassLog(" Exec:QuestSetEnabled...");
   QuestSetEnabled_ptr(Quest, enabled);
   SpyJassLog("[QuestSetEnabled] OK [Quest:%s, enabled:%s]\n",GetStrID(Quest).c_str( ), BoolToStr(enabled));
}
void _cdecl QuestSetFailed_my(HQUEST Quest, BOOL failed)
{
   funcname1 = "QuestSetFailed";
   SpyJassLog(" Exec:QuestSetFailed...");
   QuestSetFailed_ptr(Quest, failed);
   SpyJassLog("[QuestSetFailed] OK [Quest:%s, failed:%s]\n",GetStrID(Quest).c_str( ), BoolToStr(failed));
}
void _cdecl QuestSetIconPath_my(HQUEST Quest, CJassString iconPath)
{
   funcname1 = "QuestSetIconPath";
   SpyJassLog(" Exec:QuestSetIconPath...");
   QuestSetIconPath_ptr(Quest, iconPath);
   SpyJassLog("[QuestSetIconPath] OK [Quest:%s, iconPath:%s]\n",GetStrID(Quest).c_str( ), ReadJassStringNormal(iconPath));
}
void _cdecl QuestSetRequired_my(HQUEST Quest, BOOL required)
{
   funcname1 = "QuestSetRequired";
   SpyJassLog(" Exec:QuestSetRequired...");
   QuestSetRequired_ptr(Quest, required);
   SpyJassLog("[QuestSetRequired] OK [Quest:%s, required:%s]\n",GetStrID(Quest).c_str( ), BoolToStr(required));
}
void _cdecl QuestSetTitle_my(HQUEST Quest, CJassString title)
{
   funcname1 = "QuestSetTitle";
   SpyJassLog(" Exec:QuestSetTitle...");
   QuestSetTitle_ptr(Quest, title);
   SpyJassLog("[QuestSetTitle] OK [Quest:%s, title:%s]\n",GetStrID(Quest).c_str( ), ReadJassStringNormal(title));
}
void _cdecl QueueDestructableAnimation_my(HDESTRUCTABLE d, CJassString Animation)
{
   funcname1 = "QueueDestructableAnimation";
   SpyJassLog(" Exec:QueueDestructableAnimation...");
   QueueDestructableAnimation_ptr(d, Animation);
   SpyJassLog("[QueueDestructableAnimation] OK [d:%s, Animation:%s]\n",GetStrID(d).c_str( ), ReadJassStringNormal(Animation));
}
void _cdecl QueueUnitAnimation_my(HUNIT unit, CJassString Animation)
{
   funcname1 = "QueueUnitAnimation";
   SpyJassLog(" Exec:QueueUnitAnimation...");
   QueueUnitAnimation_ptr(unit, Animation);
   SpyJassLog("[QueueUnitAnimation] OK [unit:%s, Animation:%s]\n",GetUnitHID(unit).c_str( ), ReadJassStringNormal(Animation));
}
int _cdecl R2I_my(float *r)
{
   funcname1 = "R2I";
   SpyJassLog(" Exec:R2I[r:%.4g]...",(*r));
   int returnvalue; 
   returnvalue = R2I_ptr(r);
   SpyJassLog("[R2I] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
CJassStringSID _cdecl R2S_my(float *r)
{
   funcname1 = "R2S";
   SpyJassLog(" Exec:R2S[r:%.4g]...",(*r));
   CJassStringSID returnvalue; 
   returnvalue = R2S_ptr(r);
   SpyJassLog("[R2S] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
CJassStringSID _cdecl R2SW_my(float *r, int width, int precision)
{
   funcname1 = "R2SW";
   SpyJassLog(" Exec:R2SW[r:%.4g, width:%s, precision:%s]...",(*r), GetStrID(width).c_str( ), GetStrID(precision).c_str( ));
   CJassStringSID returnvalue; 
   returnvalue = R2SW_ptr(r, width, precision);
   SpyJassLog("[R2SW] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
DWFP _cdecl Rad2Deg_my(float *radians)
{
   funcname1 = "Rad2Deg";
   SpyJassLog(" Exec:Rad2Deg[radians:%.4g]...",(*radians));
   DWFP returnvalue; 
   returnvalue = Rad2Deg_ptr(radians);
   SpyJassLog("[Rad2Deg] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
HRECT _cdecl Rect_my(float *minx, float *miny, float *maxx, float *maxy)
{
   funcname1 = "Rect";
   SpyJassLog(" Exec:Rect[minx:%.4g, miny:%.4g, maxx:%.4g, maxy:%.4g]...",(*minx), (*miny), (*maxx), (*maxy));
   HRECT returnvalue; 
   returnvalue = Rect_ptr(minx, miny, maxx, maxy);
   SpyJassLog("[Rect] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HRECT _cdecl RectFromLoc_my(HLOCATION min, HLOCATION max)
{
   funcname1 = "RectFromLoc";
   SpyJassLog(" Exec:RectFromLoc[min:%s, max:%s]...",GetStrID(min).c_str( ), GetStrID(max).c_str( ));
   HRECT returnvalue; 
   returnvalue = RectFromLoc_ptr(min, max);
   SpyJassLog("[RectFromLoc] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl RecycleGuardPosition_my(HUNIT hUnit)
{
   funcname1 = "RecycleGuardPosition";
   SpyJassLog(" Exec:RecycleGuardPosition...");
   RecycleGuardPosition_ptr(hUnit);
   SpyJassLog("[RecycleGuardPosition] OK [hUnit:%s]\n",GetUnitHID(hUnit).c_str( ));
}
void _cdecl RegionAddCell_my(HREGION Region, float *x, float *y)
{
   funcname1 = "RegionAddCell";
   SpyJassLog(" Exec:RegionAddCell...");
   RegionAddCell_ptr(Region, x, y);
   SpyJassLog("[RegionAddCell] OK [Region:%s, x:%.4g, y:%.4g]\n",GetStrID(Region).c_str( ), (*x), (*y));
}
void _cdecl RegionAddCellAtLoc_my(HREGION Region, HLOCATION Location)
{
   funcname1 = "RegionAddCellAtLoc";
   SpyJassLog(" Exec:RegionAddCellAtLoc...");
   RegionAddCellAtLoc_ptr(Region, Location);
   SpyJassLog("[RegionAddCellAtLoc] OK [Region:%s, Location:%s]\n",GetStrID(Region).c_str( ), GetStrID(Location).c_str( ));
}
void _cdecl RegionAddRect_my(HREGION Region, HRECT r)
{
   funcname1 = "RegionAddRect";
   SpyJassLog(" Exec:RegionAddRect...");
   RegionAddRect_ptr(Region, r);
   SpyJassLog("[RegionAddRect] OK [Region:%s, r:%s]\n",GetStrID(Region).c_str( ), GetStrID(r).c_str( ));
}
void _cdecl RegionClearCell_my(HREGION Region, float *x, float *y)
{
   funcname1 = "RegionClearCell";
   SpyJassLog(" Exec:RegionClearCell...");
   RegionClearCell_ptr(Region, x, y);
   SpyJassLog("[RegionClearCell] OK [Region:%s, x:%.4g, y:%.4g]\n",GetStrID(Region).c_str( ), (*x), (*y));
}
void _cdecl RegionClearCellAtLoc_my(HREGION Region, HLOCATION Location)
{
   funcname1 = "RegionClearCellAtLoc";
   SpyJassLog(" Exec:RegionClearCellAtLoc...");
   RegionClearCellAtLoc_ptr(Region, Location);
   SpyJassLog("[RegionClearCellAtLoc] OK [Region:%s, Location:%s]\n",GetStrID(Region).c_str( ), GetStrID(Location).c_str( ));
}
void _cdecl RegionClearRect_my(HREGION Region, HRECT r)
{
   funcname1 = "RegionClearRect";
   SpyJassLog(" Exec:RegionClearRect...");
   RegionClearRect_ptr(Region, r);
   SpyJassLog("[RegionClearRect] OK [Region:%s, r:%s]\n",GetStrID(Region).c_str( ), GetStrID(r).c_str( ));
}
void _cdecl RegisterStackedSound_my(HSOUND soundHandle, BOOL byPosition, float *rectwidth, float *rectheight)
{
   funcname1 = "RegisterStackedSound";
   SpyJassLog(" Exec:RegisterStackedSound...");
   RegisterStackedSound_ptr(soundHandle, byPosition, rectwidth, rectheight);
   SpyJassLog("[RegisterStackedSound] OK [soundHandle:%s, byPosition:%s, rectwidth:%.4g, rectheight:%.4g]\n",GetStrID(soundHandle).c_str( ), BoolToStr(byPosition), (*rectwidth), (*rectheight));
}
void _cdecl ReloadGame_my()
{
   funcname1 = "ReloadGame";
   SpyJassLog(" Exec:ReloadGame...");
   ReloadGame_ptr();
   SpyJassLog("[ReloadGame] OK []\n");
}
BOOL _cdecl ReloadGameCachesFromDisk_my()
{
   funcname1 = "ReloadGameCachesFromDisk";
   SpyJassLog(" Exec:ReloadGameCachesFromDisk[]...");
   BOOL returnvalue; 
   returnvalue = ReloadGameCachesFromDisk_ptr();
   SpyJassLog("[ReloadGameCachesFromDisk] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl RemoveAllGuardPositions_my(HPLAYER num)
{
   funcname1 = "RemoveAllGuardPositions";
   SpyJassLog(" Exec:RemoveAllGuardPositions...");
   RemoveAllGuardPositions_ptr(num);
   SpyJassLog("[RemoveAllGuardPositions] OK [num:%i]\n",GetPlayerId_ptr(num));
}
void _cdecl RemoveDestructable_my(HDESTRUCTABLE d)
{
   funcname1 = "RemoveDestructable";
   SpyJassLog(" Exec:RemoveDestructable...");
   RemoveDestructable_ptr(d);
   SpyJassLog("[RemoveDestructable] OK [d:%s]\n",GetStrID(d).c_str( ));
}
void _cdecl RemoveGuardPosition_my(HUNIT hUnit)
{
   funcname1 = "RemoveGuardPosition";
   SpyJassLog(" Exec:RemoveGuardPosition...");
   RemoveGuardPosition_ptr(hUnit);
   SpyJassLog("[RemoveGuardPosition] OK [hUnit:%s]\n",GetUnitHID(hUnit).c_str( ));
}
void _cdecl RemoveInjuries_my()
{
   funcname1 = "RemoveInjuries";
   SpyJassLog(" Exec:RemoveInjuries...");
   RemoveInjuries_ptr();
   SpyJassLog("[RemoveInjuries] OK []\n");
}
void _cdecl RemoveItem_my(HITEM item)
{
   funcname1 = "RemoveItem";
   SpyJassLog(" Exec:RemoveItem...");
   RemoveItem_ptr(item);
   SpyJassLog("[RemoveItem] OK [item:%s]\n",GetItemHID(item).c_str( ));
}
void _cdecl RemoveItemFromAllStock_my(int itemId)
{
   funcname1 = "RemoveItemFromAllStock";
   SpyJassLog(" Exec:RemoveItemFromAllStock...");
   RemoveItemFromAllStock_ptr(itemId);
   SpyJassLog("[RemoveItemFromAllStock] OK [itemId:%s]\n",GetStrID(itemId).c_str( ));
}
void _cdecl RemoveItemFromStock_my(HUNIT unit, int itemId)
{
   funcname1 = "RemoveItemFromStock";
   SpyJassLog(" Exec:RemoveItemFromStock...");
   RemoveItemFromStock_ptr(unit, itemId);
   SpyJassLog("[RemoveItemFromStock] OK [unit:%s, itemId:%s]\n",GetUnitHID(unit).c_str( ), GetStrID(itemId).c_str( ));
}
void _cdecl RemoveLocation_my(HLOCATION Location)
{
   funcname1 = "RemoveLocation";
   SpyJassLog(" Exec:RemoveLocation...");
   RemoveLocation_ptr(Location);
   SpyJassLog("[RemoveLocation] OK [Location:%s]\n",GetStrID(Location).c_str( ));
}
void _cdecl RemovePlayer_my(HPLAYER player, HPLAYERGAMERESULT gameResult)
{
   funcname1 = "RemovePlayer";
   SpyJassLog(" Exec:RemovePlayer...");
   RemovePlayer_ptr(player, gameResult);
   SpyJassLog("[RemovePlayer] OK [player:%i, gameResult:%s]\n",GetPlayerId_ptr(player), GetStrID(gameResult).c_str( ));
}
void _cdecl RemoveRect_my(HRECT Rect)
{
   funcname1 = "RemoveRect";
   SpyJassLog(" Exec:RemoveRect...");
   RemoveRect_ptr(Rect);
   SpyJassLog("[RemoveRect] OK [Rect:%s]\n",GetStrID(Rect).c_str( ));
}
void _cdecl RemoveRegion_my(HREGION Region)
{
   funcname1 = "RemoveRegion";
   SpyJassLog(" Exec:RemoveRegion...");
   RemoveRegion_ptr(Region);
   SpyJassLog("[RemoveRegion] OK [Region:%s]\n",GetStrID(Region).c_str( ));
}
BOOL _cdecl RemoveSaveDirectory_my(CJassString sourceDirName)
{
   funcname1 = "RemoveSaveDirectory";
   SpyJassLog(" Exec:RemoveSaveDirectory[sourceDirName:%s]...",ReadJassStringNormal(sourceDirName));
   BOOL returnvalue; 
   returnvalue = RemoveSaveDirectory_ptr(sourceDirName);
   SpyJassLog("[RemoveSaveDirectory] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl RemoveSavedBoolean_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "RemoveSavedBoolean";
   SpyJassLog(" Exec:RemoveSavedBoolean...");
   RemoveSavedBoolean_ptr(table, parentKey, childKey);
   SpyJassLog("[RemoveSavedBoolean] OK [table:%s, parentKey:%s, childKey:%s]\n",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
}
void _cdecl RemoveSavedHandle_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "RemoveSavedHandle";
   SpyJassLog(" Exec:RemoveSavedHandle...");
   RemoveSavedHandle_ptr(table, parentKey, childKey);
   SpyJassLog("[RemoveSavedHandle] OK [table:%s, parentKey:%s, childKey:%s]\n",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
}
void _cdecl RemoveSavedInteger_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "RemoveSavedInteger";
   SpyJassLog(" Exec:RemoveSavedInteger...");
   RemoveSavedInteger_ptr(table, parentKey, childKey);
   SpyJassLog("[RemoveSavedInteger] OK [table:%s, parentKey:%s, childKey:%s]\n",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
}
void _cdecl RemoveSavedReal_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "RemoveSavedReal";
   SpyJassLog(" Exec:RemoveSavedReal...");
   RemoveSavedReal_ptr(table, parentKey, childKey);
   SpyJassLog("[RemoveSavedReal] OK [table:%s, parentKey:%s, childKey:%s]\n",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
}
void _cdecl RemoveSavedString_my(HHASHTABLE table, int parentKey, int childKey)
{
   funcname1 = "RemoveSavedString";
   SpyJassLog(" Exec:RemoveSavedString...");
   RemoveSavedString_ptr(table, parentKey, childKey);
   SpyJassLog("[RemoveSavedString] OK [table:%s, parentKey:%s, childKey:%s]\n",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ));
}
void _cdecl RemoveSiege_my()
{
   funcname1 = "RemoveSiege";
   SpyJassLog(" Exec:RemoveSiege...");
   RemoveSiege_ptr();
   SpyJassLog("[RemoveSiege] OK []\n");
}
void _cdecl RemoveUnit_my(HUNIT unit)
{
   funcname1 = "RemoveUnit";
   SpyJassLog(" Exec:RemoveUnit...");
   RemoveUnit_ptr(unit);
   SpyJassLog("[RemoveUnit] OK [unit:%s]\n",GetUnitHID(unit).c_str( ));
}
void _cdecl RemoveUnitFromAllStock_my(int unitId)
{
   funcname1 = "RemoveUnitFromAllStock";
   SpyJassLog(" Exec:RemoveUnitFromAllStock...");
   RemoveUnitFromAllStock_ptr(unitId);
   SpyJassLog("[RemoveUnitFromAllStock] OK [unitId:%s]\n",GetStrID(unitId).c_str( ));
}
void _cdecl RemoveUnitFromStock_my(HUNIT unit, int unitId)
{
   funcname1 = "RemoveUnitFromStock";
   SpyJassLog(" Exec:RemoveUnitFromStock...");
   RemoveUnitFromStock_ptr(unit, unitId);
   SpyJassLog("[RemoveUnitFromStock] OK [unit:%s, unitId:%s]\n",GetUnitHID(unit).c_str( ), GetStrID(unitId).c_str( ));
}
void _cdecl RemoveWeatherEffect_my(HWEATHEREFFECT Effect)
{
   funcname1 = "RemoveWeatherEffect";
   SpyJassLog(" Exec:RemoveWeatherEffect...");
   RemoveWeatherEffect_ptr(Effect);
   SpyJassLog("[RemoveWeatherEffect] OK [Effect:%s]\n",GetStrID(Effect).c_str( ));
}
BOOL _cdecl RenameSaveDirectory_my(CJassString sourceDirName, CJassString destDirName)
{
   funcname1 = "RenameSaveDirectory";
   SpyJassLog(" Exec:RenameSaveDirectory[sourceDirName:%s, destDirName:%s]...",ReadJassStringNormal(sourceDirName), ReadJassStringNormal(destDirName));
   BOOL returnvalue; 
   returnvalue = RenameSaveDirectory_ptr(sourceDirName, destDirName);
   SpyJassLog("[RenameSaveDirectory] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl ResetCaptainLocs_my()
{
   funcname1 = "ResetCaptainLocs";
   SpyJassLog(" Exec:ResetCaptainLocs...");
   ResetCaptainLocs_ptr();
   SpyJassLog("[ResetCaptainLocs] OK []\n");
}
void _cdecl ResetTerrainFog_my()
{
   funcname1 = "ResetTerrainFog";
   SpyJassLog(" Exec:ResetTerrainFog...");
   ResetTerrainFog_ptr();
   SpyJassLog("[ResetTerrainFog] OK []\n");
}
void _cdecl ResetToGameCamera_my(float *duration)
{
   funcname1 = "ResetToGameCamera";
   SpyJassLog(" Exec:ResetToGameCamera...");
   ResetToGameCamera_ptr(duration);
   SpyJassLog("[ResetToGameCamera] OK [duration:%.4g]\n",(*duration));
}
void _cdecl ResetTrigger_my(HTRIGGER Trigger)
{
   funcname1 = "ResetTrigger";
   SpyJassLog(" Exec:ResetTrigger...");
   ResetTrigger_ptr(Trigger);
   SpyJassLog("[ResetTrigger] OK [Trigger:%s]\n",GetStrID(Trigger).c_str( ));
}
void _cdecl ResetUbersplat_my(HUBERSPLAT Splat)
{
   funcname1 = "ResetUbersplat";
   SpyJassLog(" Exec:ResetUbersplat...");
   ResetUbersplat_ptr(Splat);
   SpyJassLog("[ResetUbersplat] OK [Splat:%s]\n",GetStrID(Splat).c_str( ));
}
void _cdecl ResetUnitLookAt_my(HUNIT unit)
{
   funcname1 = "ResetUnitLookAt";
   SpyJassLog(" Exec:ResetUnitLookAt...");
   ResetUnitLookAt_ptr(unit);
   SpyJassLog("[ResetUnitLookAt] OK [unit:%s]\n",GetUnitHID(unit).c_str( ));
}
void _cdecl RestartGame_my(BOOL doScoreScreen)
{
   funcname1 = "RestartGame";
   SpyJassLog(" Exec:RestartGame...");
   RestartGame_ptr(doScoreScreen);
   SpyJassLog("[RestartGame] OK [doScoreScreen:%s]\n",BoolToStr(doScoreScreen));
}
HUNIT _cdecl RestoreUnit_my(HGAMECACHE cache, CJassString missionKey, CJassString key, HPLAYER forWhichPlayer, float *x, float *y, float *facing)
{
   funcname1 = "RestoreUnit";
   SpyJassLog(" Exec:RestoreUnit[cache:%s, missionKey:%s, key:%s, forWhichPlayer:%i, x:%.4g, y:%.4g, facing:%.4g]...",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key), GetPlayerId_ptr(forWhichPlayer), (*x), (*y), (*facing));
   HUNIT returnvalue; 
   returnvalue = RestoreUnit_ptr(cache, missionKey, key, forWhichPlayer, x, y, facing);
   SpyJassLog("[RestoreUnit] OK [%s]\n",GetUnitHID(returnvalue).c_str( ));
   return returnvalue;
}
void _cdecl ResumeMusic_my()
{
   funcname1 = "ResumeMusic";
   SpyJassLog(" Exec:ResumeMusic...");
   ResumeMusic_ptr();
   SpyJassLog("[ResumeMusic] OK []\n");
}
void _cdecl ResumeTimer_my(HTIMER Timer)
{
   funcname1 = "ResumeTimer";
   SpyJassLog(" Exec:ResumeTimer...");
   ResumeTimer_ptr(Timer);
   SpyJassLog("[ResumeTimer] OK [Timer:%s]\n",GetStrID(Timer).c_str( ));
}
void _cdecl ReturnGuardPosts_my()
{
   funcname1 = "ReturnGuardPosts";
   SpyJassLog(" Exec:ReturnGuardPosts...");
   ReturnGuardPosts_ptr();
   SpyJassLog("[ReturnGuardPosts] OK []\n");
}
BOOL _cdecl ReviveHero_my(HUNIT hero, float *x, float *y, BOOL doEyecandy)
{
   funcname1 = "ReviveHero";
   SpyJassLog(" Exec:ReviveHero[hero:%s, x:%.4g, y:%.4g, doEyecandy:%s]...",GetUnitHID(hero).c_str( ), (*x), (*y), BoolToStr(doEyecandy));
   BOOL returnvalue; 
   returnvalue = ReviveHero_ptr(hero, x, y, doEyecandy);
   SpyJassLog("[ReviveHero] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl ReviveHeroLoc_my(HUNIT hero, HLOCATION loc, BOOL doEyecandy)
{
   funcname1 = "ReviveHeroLoc";
   SpyJassLog(" Exec:ReviveHeroLoc[hero:%s, loc:%s, doEyecandy:%s]...",GetUnitHID(hero).c_str( ), GetStrID(loc).c_str( ), BoolToStr(doEyecandy));
   BOOL returnvalue; 
   returnvalue = ReviveHeroLoc_ptr(hero, loc, doEyecandy);
   SpyJassLog("[ReviveHeroLoc] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
int _cdecl S2I_my(CJassString s)
{
   funcname1 = "S2I";
   SpyJassLog(" Exec:S2I[s:%s]...",ReadJassStringNormal(s));
   int returnvalue; 
   returnvalue = S2I_ptr(s);
   SpyJassLog("[S2I] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
DWFP _cdecl S2R_my(CJassString s)
{
   funcname1 = "S2R";
   SpyJassLog(" Exec:S2R[s:%s]...",ReadJassStringNormal(s));
   DWFP returnvalue; 
   returnvalue = S2R_ptr(s);
   SpyJassLog("[S2R] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveAbilityHandle_my(HHASHTABLE table, int parentKey, int childKey, HABILITY Ability)
{
   funcname1 = "SaveAbilityHandle";
   SpyJassLog(" Exec:SaveAbilityHandle[table:%s, parentKey:%s, childKey:%s, Ability:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Ability).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveAbilityHandle_ptr(table, parentKey, childKey, Ability);
   SpyJassLog("[SaveAbilityHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveAgentHandle_my(HHASHTABLE table, int parentKey, int childKey, HAGENT Agent)
{
   funcname1 = "SaveAgentHandle";
   SpyJassLog(" Exec:SaveAgentHandle[table:%s, parentKey:%s, childKey:%s, Agent:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Agent).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveAgentHandle_ptr(table, parentKey, childKey, Agent);
   SpyJassLog("[SaveAgentHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl SaveBoolean_my(HHASHTABLE table, int parentKey, int childKey, BOOL value)
{
   funcname1 = "SaveBoolean";
   SpyJassLog(" Exec:SaveBoolean...");
   SaveBoolean_ptr(table, parentKey, childKey, value);
   SpyJassLog("[SaveBoolean] OK [table:%s, parentKey:%s, childKey:%s, value:%s]\n",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), BoolToStr(value));
}
BOOL _cdecl SaveBooleanExprHandle_my(HHASHTABLE table, int parentKey, int childKey, HBOOLEXPR Boolexpr)
{
   funcname1 = "SaveBooleanExprHandle";
   SpyJassLog(" Exec:SaveBooleanExprHandle[table:%s, parentKey:%s, childKey:%s, Boolexpr:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Boolexpr).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveBooleanExprHandle_ptr(table, parentKey, childKey, Boolexpr);
   SpyJassLog("[SaveBooleanExprHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveButtonHandle_my(HHASHTABLE table, int parentKey, int childKey, HBUTTON Button)
{
   funcname1 = "SaveButtonHandle";
   SpyJassLog(" Exec:SaveButtonHandle[table:%s, parentKey:%s, childKey:%s, Button:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Button).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveButtonHandle_ptr(table, parentKey, childKey, Button);
   SpyJassLog("[SaveButtonHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveDefeatConditionHandle_my(HHASHTABLE table, int parentKey, int childKey, HDEFEATCONDITION Defeatcondition)
{
   funcname1 = "SaveDefeatConditionHandle";
   SpyJassLog(" Exec:SaveDefeatConditionHandle[table:%s, parentKey:%s, childKey:%s, Defeatcondition:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Defeatcondition).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveDefeatConditionHandle_ptr(table, parentKey, childKey, Defeatcondition);
   SpyJassLog("[SaveDefeatConditionHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveDestructableHandle_my(HHASHTABLE table, int parentKey, int childKey, HDESTRUCTABLE Destructable)
{
   funcname1 = "SaveDestructableHandle";
   SpyJassLog(" Exec:SaveDestructableHandle[table:%s, parentKey:%s, childKey:%s, Destructable:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Destructable).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveDestructableHandle_ptr(table, parentKey, childKey, Destructable);
   SpyJassLog("[SaveDestructableHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveDialogHandle_my(HHASHTABLE table, int parentKey, int childKey, HDIALOG Dialog)
{
   funcname1 = "SaveDialogHandle";
   SpyJassLog(" Exec:SaveDialogHandle[table:%s, parentKey:%s, childKey:%s, Dialog:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Dialog).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveDialogHandle_ptr(table, parentKey, childKey, Dialog);
   SpyJassLog("[SaveDialogHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveEffectHandle_my(HHASHTABLE table, int parentKey, int childKey, HEFFECT Effect)
{
   funcname1 = "SaveEffectHandle";
   SpyJassLog(" Exec:SaveEffectHandle[table:%s, parentKey:%s, childKey:%s, Effect:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Effect).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveEffectHandle_ptr(table, parentKey, childKey, Effect);
   SpyJassLog("[SaveEffectHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveFogModifierHandle_my(HHASHTABLE table, int parentKey, int childKey, HFOGMODIFIER FogModifier)
{
   funcname1 = "SaveFogModifierHandle";
   SpyJassLog(" Exec:SaveFogModifierHandle[table:%s, parentKey:%s, childKey:%s, FogModifier:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(FogModifier).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveFogModifierHandle_ptr(table, parentKey, childKey, FogModifier);
   SpyJassLog("[SaveFogModifierHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveFogStateHandle_my(HHASHTABLE table, int parentKey, int childKey, HFOGSTATE FogState)
{
   funcname1 = "SaveFogStateHandle";
   SpyJassLog(" Exec:SaveFogStateHandle[table:%s, parentKey:%s, childKey:%s, FogState:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(FogState).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveFogStateHandle_ptr(table, parentKey, childKey, FogState);
   SpyJassLog("[SaveFogStateHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveForceHandle_my(HHASHTABLE table, int parentKey, int childKey, HFORCE Force)
{
   funcname1 = "SaveForceHandle";
   SpyJassLog(" Exec:SaveForceHandle[table:%s, parentKey:%s, childKey:%s, Force:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Force).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveForceHandle_ptr(table, parentKey, childKey, Force);
   SpyJassLog("[SaveForceHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl SaveGame_my(CJassString saveFileName)
{
   funcname1 = "SaveGame";
   SpyJassLog(" Exec:SaveGame...");
   SaveGame_ptr(saveFileName);
   SpyJassLog("[SaveGame] OK [saveFileName:%s]\n",ReadJassStringNormal(saveFileName));
}
BOOL _cdecl SaveGameCache_my(HGAMECACHE Cache)
{
   funcname1 = "SaveGameCache";
   SpyJassLog(" Exec:SaveGameCache[Cache:%s]...",GetStrID(Cache).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveGameCache_ptr(Cache);
   SpyJassLog("[SaveGameCache] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveGameExists_my(CJassString saveName)
{
   funcname1 = "SaveGameExists";
   SpyJassLog(" Exec:SaveGameExists[saveName:%s]...",ReadJassStringNormal(saveName));
   BOOL returnvalue; 
   returnvalue = SaveGameExists_ptr(saveName);
   SpyJassLog("[SaveGameExists] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveGroupHandle_my(HHASHTABLE table, int parentKey, int childKey, HGROUP Group)
{
   funcname1 = "SaveGroupHandle";
   SpyJassLog(" Exec:SaveGroupHandle[table:%s, parentKey:%s, childKey:%s, Group:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Group).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveGroupHandle_ptr(table, parentKey, childKey, Group);
   SpyJassLog("[SaveGroupHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveHashtableHandle_my(HHASHTABLE table, int parentKey, int childKey, HHASHTABLE Hashtable)
{
   funcname1 = "SaveHashtableHandle";
   SpyJassLog(" Exec:SaveHashtableHandle[table:%s, parentKey:%s, childKey:%s, Hashtable:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Hashtable).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveHashtableHandle_ptr(table, parentKey, childKey, Hashtable);
   SpyJassLog("[SaveHashtableHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveImageHandle_my(HHASHTABLE table, int parentKey, int childKey, HIMAGE Image)
{
   funcname1 = "SaveImageHandle";
   SpyJassLog(" Exec:SaveImageHandle[table:%s, parentKey:%s, childKey:%s, Image:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Image).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveImageHandle_ptr(table, parentKey, childKey, Image);
   SpyJassLog("[SaveImageHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl SaveInteger_my(HHASHTABLE table, int parentKey, int childKey, int value)
{
   funcname1 = "SaveInteger";
   SpyJassLog(" Exec:SaveInteger...");
   SaveInteger_ptr(table, parentKey, childKey, value);
   SpyJassLog("[SaveInteger] OK [table:%s, parentKey:%s, childKey:%s, value:%s]\n",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(value).c_str( ));
}
BOOL _cdecl SaveItemHandle_my(HHASHTABLE table, int parentKey, int childKey, HITEM item)
{
   funcname1 = "SaveItemHandle";
   SpyJassLog(" Exec:SaveItemHandle[table:%s, parentKey:%s, childKey:%s, item:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetItemHID(item).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveItemHandle_ptr(table, parentKey, childKey, item);
   SpyJassLog("[SaveItemHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveItemPoolHandle_my(HHASHTABLE table, int parentKey, int childKey, HITEMPOOL Itempool)
{
   funcname1 = "SaveItemPoolHandle";
   SpyJassLog(" Exec:SaveItemPoolHandle[table:%s, parentKey:%s, childKey:%s, Itempool:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Itempool).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveItemPoolHandle_ptr(table, parentKey, childKey, Itempool);
   SpyJassLog("[SaveItemPoolHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveLeaderboardHandle_my(HHASHTABLE table, int parentKey, int childKey, HLEADERBOARD Leaderboard)
{
   funcname1 = "SaveLeaderboardHandle";
   SpyJassLog(" Exec:SaveLeaderboardHandle[table:%s, parentKey:%s, childKey:%s, Leaderboard:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Leaderboard).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveLeaderboardHandle_ptr(table, parentKey, childKey, Leaderboard);
   SpyJassLog("[SaveLeaderboardHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveLightningHandle_my(HHASHTABLE table, int parentKey, int childKey, HLIGHTNING Lightning)
{
   funcname1 = "SaveLightningHandle";
   SpyJassLog(" Exec:SaveLightningHandle[table:%s, parentKey:%s, childKey:%s, Lightning:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Lightning).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveLightningHandle_ptr(table, parentKey, childKey, Lightning);
   SpyJassLog("[SaveLightningHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveLocationHandle_my(HHASHTABLE table, int parentKey, int childKey, HLOCATION Location)
{
   funcname1 = "SaveLocationHandle";
   SpyJassLog(" Exec:SaveLocationHandle[table:%s, parentKey:%s, childKey:%s, Location:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Location).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveLocationHandle_ptr(table, parentKey, childKey, Location);
   SpyJassLog("[SaveLocationHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveMultiboardHandle_my(HHASHTABLE table, int parentKey, int childKey, HMULTIBOARD Multiboard)
{
   funcname1 = "SaveMultiboardHandle";
   SpyJassLog(" Exec:SaveMultiboardHandle[table:%s, parentKey:%s, childKey:%s, Multiboard:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Multiboard).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveMultiboardHandle_ptr(table, parentKey, childKey, Multiboard);
   SpyJassLog("[SaveMultiboardHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveMultiboardItemHandle_my(HHASHTABLE table, int parentKey, int childKey, HMULTIBOARDITEM Multiboarditem)
{
   funcname1 = "SaveMultiboardItemHandle";
   SpyJassLog(" Exec:SaveMultiboardItemHandle[table:%s, parentKey:%s, childKey:%s, Multiboarditem:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Multiboarditem).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveMultiboardItemHandle_ptr(table, parentKey, childKey, Multiboarditem);
   SpyJassLog("[SaveMultiboardItemHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SavePlayerHandle_my(HHASHTABLE table, int parentKey, int childKey, HPLAYER player)
{
   funcname1 = "SavePlayerHandle";
   SpyJassLog(" Exec:SavePlayerHandle[table:%s, parentKey:%s, childKey:%s, player:%i]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetPlayerId_ptr(player));
   BOOL returnvalue; 
   returnvalue = SavePlayerHandle_ptr(table, parentKey, childKey, player);
   SpyJassLog("[SavePlayerHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveQuestHandle_my(HHASHTABLE table, int parentKey, int childKey, HQUEST Quest)
{
   funcname1 = "SaveQuestHandle";
   SpyJassLog(" Exec:SaveQuestHandle[table:%s, parentKey:%s, childKey:%s, Quest:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Quest).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveQuestHandle_ptr(table, parentKey, childKey, Quest);
   SpyJassLog("[SaveQuestHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveQuestItemHandle_my(HHASHTABLE table, int parentKey, int childKey, HQUESTITEM Questitem)
{
   funcname1 = "SaveQuestItemHandle";
   SpyJassLog(" Exec:SaveQuestItemHandle[table:%s, parentKey:%s, childKey:%s, Questitem:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Questitem).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveQuestItemHandle_ptr(table, parentKey, childKey, Questitem);
   SpyJassLog("[SaveQuestItemHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl SaveReal_my(HHASHTABLE table, int parentKey, int childKey, float *value)
{
   funcname1 = "SaveReal";
   SpyJassLog(" Exec:SaveReal...");
   SaveReal_ptr(table, parentKey, childKey, value);
   SpyJassLog("[SaveReal] OK [table:%s, parentKey:%s, childKey:%s, value:%.4g]\n",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), (*value));
}
BOOL _cdecl SaveRectHandle_my(HHASHTABLE table, int parentKey, int childKey, HRECT Rect)
{
   funcname1 = "SaveRectHandle";
   SpyJassLog(" Exec:SaveRectHandle[table:%s, parentKey:%s, childKey:%s, Rect:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Rect).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveRectHandle_ptr(table, parentKey, childKey, Rect);
   SpyJassLog("[SaveRectHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveRegionHandle_my(HHASHTABLE table, int parentKey, int childKey, HREGION Region)
{
   funcname1 = "SaveRegionHandle";
   SpyJassLog(" Exec:SaveRegionHandle[table:%s, parentKey:%s, childKey:%s, Region:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Region).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveRegionHandle_ptr(table, parentKey, childKey, Region);
   SpyJassLog("[SaveRegionHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveSoundHandle_my(HHASHTABLE table, int parentKey, int childKey, HSOUND Sound)
{
   funcname1 = "SaveSoundHandle";
   SpyJassLog(" Exec:SaveSoundHandle[table:%s, parentKey:%s, childKey:%s, Sound:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Sound).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveSoundHandle_ptr(table, parentKey, childKey, Sound);
   SpyJassLog("[SaveSoundHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveStr_my(HHASHTABLE table, int parentKey, int childKey, CJassString value)
{
   funcname1 = "SaveStr";
   SpyJassLog(" Exec:SaveStr[table:%s, parentKey:%s, childKey:%s, value:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), ReadJassStringNormal(value));
   BOOL returnvalue; 
   returnvalue = SaveStr_ptr(table, parentKey, childKey, value);
   SpyJassLog("[SaveStr] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveTextTagHandle_my(HHASHTABLE table, int parentKey, int childKey, HTEXTTAG Texttag)
{
   funcname1 = "SaveTextTagHandle";
   SpyJassLog(" Exec:SaveTextTagHandle[table:%s, parentKey:%s, childKey:%s, Texttag:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Texttag).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveTextTagHandle_ptr(table, parentKey, childKey, Texttag);
   SpyJassLog("[SaveTextTagHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveTimerDialogHandle_my(HHASHTABLE table, int parentKey, int childKey, HTIMERDIALOG Timerdialog)
{
   funcname1 = "SaveTimerDialogHandle";
   SpyJassLog(" Exec:SaveTimerDialogHandle[table:%s, parentKey:%s, childKey:%s, Timerdialog:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Timerdialog).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveTimerDialogHandle_ptr(table, parentKey, childKey, Timerdialog);
   SpyJassLog("[SaveTimerDialogHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveTimerHandle_my(HHASHTABLE table, int parentKey, int childKey, HTIMER Timer)
{
   funcname1 = "SaveTimerHandle";
   SpyJassLog(" Exec:SaveTimerHandle[table:%s, parentKey:%s, childKey:%s, Timer:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Timer).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveTimerHandle_ptr(table, parentKey, childKey, Timer);
   SpyJassLog("[SaveTimerHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveTrackableHandle_my(HHASHTABLE table, int parentKey, int childKey, HTRACKABLE Trackable)
{
   funcname1 = "SaveTrackableHandle";
   SpyJassLog(" Exec:SaveTrackableHandle[table:%s, parentKey:%s, childKey:%s, Trackable:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Trackable).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveTrackableHandle_ptr(table, parentKey, childKey, Trackable);
   SpyJassLog("[SaveTrackableHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveTriggerActionHandle_my(HHASHTABLE table, int parentKey, int childKey, HTRIGGERACTION Triggeraction)
{
   funcname1 = "SaveTriggerActionHandle";
   SpyJassLog(" Exec:SaveTriggerActionHandle[table:%s, parentKey:%s, childKey:%s, Triggeraction:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Triggeraction).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveTriggerActionHandle_ptr(table, parentKey, childKey, Triggeraction);
   SpyJassLog("[SaveTriggerActionHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveTriggerConditionHandle_my(HHASHTABLE table, int parentKey, int childKey, HTRIGGERCONDITION Triggercondition)
{
   funcname1 = "SaveTriggerConditionHandle";
   SpyJassLog(" Exec:SaveTriggerConditionHandle[table:%s, parentKey:%s, childKey:%s, Triggercondition:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Triggercondition).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveTriggerConditionHandle_ptr(table, parentKey, childKey, Triggercondition);
   SpyJassLog("[SaveTriggerConditionHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveTriggerEventHandle_my(HHASHTABLE table, int parentKey, int childKey, HEVENT Event)
{
   funcname1 = "SaveTriggerEventHandle";
   SpyJassLog(" Exec:SaveTriggerEventHandle[table:%s, parentKey:%s, childKey:%s, Event:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Event).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveTriggerEventHandle_ptr(table, parentKey, childKey, Event);
   SpyJassLog("[SaveTriggerEventHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveTriggerHandle_my(HHASHTABLE table, int parentKey, int childKey, HTRIGGER Trigger)
{
   funcname1 = "SaveTriggerHandle";
   SpyJassLog(" Exec:SaveTriggerHandle[table:%s, parentKey:%s, childKey:%s, Trigger:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Trigger).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveTriggerHandle_ptr(table, parentKey, childKey, Trigger);
   SpyJassLog("[SaveTriggerHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveUbersplatHandle_my(HHASHTABLE table, int parentKey, int childKey, HUBERSPLAT Ubersplat)
{
   funcname1 = "SaveUbersplatHandle";
   SpyJassLog(" Exec:SaveUbersplatHandle[table:%s, parentKey:%s, childKey:%s, Ubersplat:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Ubersplat).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveUbersplatHandle_ptr(table, parentKey, childKey, Ubersplat);
   SpyJassLog("[SaveUbersplatHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveUnitHandle_my(HHASHTABLE table, int parentKey, int childKey, HUNIT unit)
{
   funcname1 = "SaveUnitHandle";
   SpyJassLog(" Exec:SaveUnitHandle[table:%s, parentKey:%s, childKey:%s, unit:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetUnitHID(unit).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveUnitHandle_ptr(table, parentKey, childKey, unit);
   SpyJassLog("[SaveUnitHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveUnitPoolHandle_my(HHASHTABLE table, int parentKey, int childKey, HUNITPOOL Unitpool)
{
   funcname1 = "SaveUnitPoolHandle";
   SpyJassLog(" Exec:SaveUnitPoolHandle[table:%s, parentKey:%s, childKey:%s, Unitpool:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(Unitpool).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveUnitPoolHandle_ptr(table, parentKey, childKey, Unitpool);
   SpyJassLog("[SaveUnitPoolHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SaveWidgetHandle_my(HHASHTABLE table, int parentKey, int childKey, HWIDGET widget)
{
   funcname1 = "SaveWidgetHandle";
   SpyJassLog(" Exec:SaveWidgetHandle[table:%s, parentKey:%s, childKey:%s, widget:%s]...",GetStrID(table).c_str( ), GetStrID(parentKey).c_str( ), GetStrID(childKey).c_str( ), GetStrID(widget).c_str( ));
   BOOL returnvalue; 
   returnvalue = SaveWidgetHandle_ptr(table, parentKey, childKey, widget);
   SpyJassLog("[SaveWidgetHandle] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl SelectHeroSkill_my(HUNIT hero, int abilcode)
{
   funcname1 = "SelectHeroSkill";
   SpyJassLog(" Exec:SelectHeroSkill...");
   SelectHeroSkill_ptr(hero, abilcode);
   SpyJassLog("[SelectHeroSkill] OK [hero:%s, abilcode:%s]\n",GetUnitHID(hero).c_str( ), GetStrID(abilcode).c_str( ));
}
void _cdecl SelectUnit_my(HUNIT unit, BOOL flag)
{
   funcname1 = "SelectUnit";
   SpyJassLog(" Exec:SelectUnit...");
   SelectUnit_ptr(unit, flag);
   SpyJassLog("[SelectUnit] OK [unit:%s, flag:%s]\n",GetUnitHID(unit).c_str( ), BoolToStr(flag));
}
void _cdecl SetAllItemTypeSlots_my(int slots)
{
   funcname1 = "SetAllItemTypeSlots";
   SpyJassLog(" Exec:SetAllItemTypeSlots...");
   SetAllItemTypeSlots_ptr(slots);
   SpyJassLog("[SetAllItemTypeSlots] OK [slots:%s]\n",GetStrID(slots).c_str( ));
}
void _cdecl SetAllUnitTypeSlots_my(int slots)
{
   funcname1 = "SetAllUnitTypeSlots";
   SpyJassLog(" Exec:SetAllUnitTypeSlots...");
   SetAllUnitTypeSlots_ptr(slots);
   SpyJassLog("[SetAllUnitTypeSlots] OK [slots:%s]\n",GetStrID(slots).c_str( ));
}
void _cdecl SetAllianceTarget_my(HUNIT arg1)
{
   funcname1 = "SetAllianceTarget";
   SpyJassLog(" Exec:SetAllianceTarget...");
   SetAllianceTarget_ptr(arg1);
   SpyJassLog("[SetAllianceTarget] OK [arg1:%s]\n",GetUnitHID(arg1).c_str( ));
}
void _cdecl SetAllyColorFilterState_my(int state)
{
   funcname1 = "SetAllyColorFilterState";
   SpyJassLog(" Exec:SetAllyColorFilterState...");
   SetAllyColorFilterState_ptr(state);
   SpyJassLog("[SetAllyColorFilterState] OK [state:%s]\n",GetStrID(state).c_str( ));
}
void _cdecl SetAltMinimapIcon_my(CJassString iconPath)
{
   funcname1 = "SetAltMinimapIcon";
   SpyJassLog(" Exec:SetAltMinimapIcon...");
   SetAltMinimapIcon_ptr(iconPath);
   SpyJassLog("[SetAltMinimapIcon] OK [iconPath:%s]\n",ReadJassStringNormal(iconPath));
}
void _cdecl SetAmphibious_my()
{
   funcname1 = "SetAmphibious";
   SpyJassLog(" Exec:SetAmphibious...");
   SetAmphibious_ptr();
   SpyJassLog("[SetAmphibious] OK []\n");
}
void _cdecl SetBlight_my(HPLAYER player, float *x, float *y, float *radius, BOOL addBlight)
{
   funcname1 = "SetBlight";
   SpyJassLog(" Exec:SetBlight...");
   SetBlight_ptr(player, x, y, radius, addBlight);
   SpyJassLog("[SetBlight] OK [player:%i, x:%.4g, y:%.4g, radius:%.4g, addBlight:%s]\n",GetPlayerId_ptr(player), (*x), (*y), (*radius), BoolToStr(addBlight));
}
void _cdecl SetBlightLoc_my(HPLAYER player, HLOCATION Location, float *radius, BOOL addBlight)
{
   funcname1 = "SetBlightLoc";
   SpyJassLog(" Exec:SetBlightLoc...");
   SetBlightLoc_ptr(player, Location, radius, addBlight);
   SpyJassLog("[SetBlightLoc] OK [player:%i, Location:%s, radius:%.4g, addBlight:%s]\n",GetPlayerId_ptr(player), GetStrID(Location).c_str( ), (*radius), BoolToStr(addBlight));
}
void _cdecl SetBlightPoint_my(HPLAYER player, float *x, float *y, BOOL addBlight)
{
   funcname1 = "SetBlightPoint";
   SpyJassLog(" Exec:SetBlightPoint...");
   SetBlightPoint_ptr(player, x, y, addBlight);
   SpyJassLog("[SetBlightPoint] OK [player:%i, x:%.4g, y:%.4g, addBlight:%s]\n",GetPlayerId_ptr(player), (*x), (*y), BoolToStr(addBlight));
}
void _cdecl SetBlightRect_my(HPLAYER player, HRECT r, BOOL addBlight)
{
   funcname1 = "SetBlightRect";
   SpyJassLog(" Exec:SetBlightRect...");
   SetBlightRect_ptr(player, r, addBlight);
   SpyJassLog("[SetBlightRect] OK [player:%i, r:%s, addBlight:%s]\n",GetPlayerId_ptr(player), GetStrID(r).c_str( ), BoolToStr(addBlight));
}
void _cdecl SetCameraBounds_my(float *x1, float *y1, float *x2, float *y2, float *x3, float *y3, float *x4, float *y4)
{
   funcname1 = "SetCameraBounds";
   SpyJassLog(" Exec:SetCameraBounds...");
   SetCameraBounds_ptr(x1, y1, x2, y2, x3, y3, x4, y4);
   SpyJassLog("[SetCameraBounds] OK [x1:%.4g, y1:%.4g, x2:%.4g, y2:%.4g, x3:%.4g, y3:%.4g, x4:%.4g, y4:%.4g]\n",(*x1), (*y1), (*x2), (*y2), (*x3), (*y3), (*x4), (*y4));
}
void _cdecl SetCameraField_my(HCAMERAFIELD field, float *value, float *duration)
{
   funcname1 = "SetCameraField";
   SpyJassLog(" Exec:SetCameraField...");
   SetCameraField_ptr(field, value, duration);
   SpyJassLog("[SetCameraField] OK [field:%s, value:%.4g, duration:%.4g]\n",GetStrID(field).c_str( ), (*value), (*duration));
}
void _cdecl SetCameraOrientController_my(HUNIT unit, float *xoffset, float *yoffset)
{
   funcname1 = "SetCameraOrientController";
   SpyJassLog(" Exec:SetCameraOrientController...");
   SetCameraOrientController_ptr(unit, xoffset, yoffset);
   SpyJassLog("[SetCameraOrientController] OK [unit:%s, xoffset:%.4g, yoffset:%.4g]\n",GetUnitHID(unit).c_str( ), (*xoffset), (*yoffset));
}
void _cdecl SetCameraPosition_my(float *x, float *y)
{
   funcname1 = "SetCameraPosition";
   SpyJassLog(" Exec:SetCameraPosition...");
   SetCameraPosition_ptr(x, y);
   SpyJassLog("[SetCameraPosition] OK [x:%.4g, y:%.4g]\n",(*x), (*y));
}
void _cdecl SetCameraQuickPosition_my(float *x, float *y)
{
   funcname1 = "SetCameraQuickPosition";
   SpyJassLog(" Exec:SetCameraQuickPosition...");
   SetCameraQuickPosition_ptr(x, y);
   SpyJassLog("[SetCameraQuickPosition] OK [x:%.4g, y:%.4g]\n",(*x), (*y));
}
void _cdecl SetCameraRotateMode_my(float *x, float *y, float *radiansToSweep, float *duration)
{
   funcname1 = "SetCameraRotateMode";
   SpyJassLog(" Exec:SetCameraRotateMode...");
   SetCameraRotateMode_ptr(x, y, radiansToSweep, duration);
   SpyJassLog("[SetCameraRotateMode] OK [x:%.4g, y:%.4g, radiansToSweep:%.4g, duration:%.4g]\n",(*x), (*y), (*radiansToSweep), (*duration));
}
void _cdecl SetCameraTargetController_my(HUNIT unit, float *xoffset, float *yoffset, BOOL inheritOrientation)
{
   funcname1 = "SetCameraTargetController";
   SpyJassLog(" Exec:SetCameraTargetController...");
   SetCameraTargetController_ptr(unit, xoffset, yoffset, inheritOrientation);
   SpyJassLog("[SetCameraTargetController] OK [unit:%s, xoffset:%.4g, yoffset:%.4g, inheritOrientation:%s]\n",GetUnitHID(unit).c_str( ), (*xoffset), (*yoffset), BoolToStr(inheritOrientation));
}
void _cdecl SetCampaignAI_my()
{
   funcname1 = "SetCampaignAI";
   SpyJassLog(" Exec:SetCampaignAI...");
   SetCampaignAI_ptr();
   SpyJassLog("[SetCampaignAI] OK []\n");
}
void _cdecl SetCampaignAvailable_my(int campaignNumber, BOOL available)
{
   funcname1 = "SetCampaignAvailable";
   SpyJassLog(" Exec:SetCampaignAvailable...");
   SetCampaignAvailable_ptr(campaignNumber, available);
   SpyJassLog("[SetCampaignAvailable] OK [campaignNumber:%s, available:%s]\n",GetStrID(campaignNumber).c_str( ), BoolToStr(available));
}
void _cdecl SetCampaignMenuRace_my(HRACE r)
{
   funcname1 = "SetCampaignMenuRace";
   SpyJassLog(" Exec:SetCampaignMenuRace...");
   SetCampaignMenuRace_ptr(r);
   SpyJassLog("[SetCampaignMenuRace] OK [r:%s]\n",GetStrID(r).c_str( ));
}
void _cdecl SetCampaignMenuRaceEx_my(int campaignIndex)
{
   funcname1 = "SetCampaignMenuRaceEx";
   SpyJassLog(" Exec:SetCampaignMenuRaceEx...");
   SetCampaignMenuRaceEx_ptr(campaignIndex);
   SpyJassLog("[SetCampaignMenuRaceEx] OK [campaignIndex:%s]\n",GetStrID(campaignIndex).c_str( ));
}
void _cdecl SetCaptainChanges_my(BOOL arg1)
{
   funcname1 = "SetCaptainChanges";
   SpyJassLog(" Exec:SetCaptainChanges...");
   SetCaptainChanges_ptr(arg1);
   SpyJassLog("[SetCaptainChanges] OK [arg1:%s]\n",BoolToStr(arg1));
}
void _cdecl SetCaptainHome_my(int arg1, float *arg2, float *arg3)
{
   funcname1 = "SetCaptainHome";
   SpyJassLog(" Exec:SetCaptainHome...");
   SetCaptainHome_ptr(arg1, arg2, arg3);
   SpyJassLog("[SetCaptainHome] OK [arg1:%s, arg2:%.4g, arg3:%.4g]\n",GetStrID(arg1).c_str( ), (*arg2), (*arg3));
}
void _cdecl SetCineFilterBlendMode_my(HBLENDMODE Mode)
{
   funcname1 = "SetCineFilterBlendMode";
   SpyJassLog(" Exec:SetCineFilterBlendMode...");
   SetCineFilterBlendMode_ptr(Mode);
   SpyJassLog("[SetCineFilterBlendMode] OK [Mode:%s]\n",GetStrID(Mode).c_str( ));
}
void _cdecl SetCineFilterDuration_my(float *duration)
{
   funcname1 = "SetCineFilterDuration";
   SpyJassLog(" Exec:SetCineFilterDuration...");
   SetCineFilterDuration_ptr(duration);
   SpyJassLog("[SetCineFilterDuration] OK [duration:%.4g]\n",(*duration));
}
void _cdecl SetCineFilterEndColor_my(int red, int green, int blue, int alpha)
{
   funcname1 = "SetCineFilterEndColor";
   SpyJassLog(" Exec:SetCineFilterEndColor...");
   SetCineFilterEndColor_ptr(red, green, blue, alpha);
   SpyJassLog("[SetCineFilterEndColor] OK [red:%s, green:%s, blue:%s, alpha:%s]\n",GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), GetStrID(alpha).c_str( ));
}
void _cdecl SetCineFilterEndUV_my(float *minu, float *minv, float *maxu, float *maxv)
{
   funcname1 = "SetCineFilterEndUV";
   SpyJassLog(" Exec:SetCineFilterEndUV...");
   SetCineFilterEndUV_ptr(minu, minv, maxu, maxv);
   SpyJassLog("[SetCineFilterEndUV] OK [minu:%.4g, minv:%.4g, maxu:%.4g, maxv:%.4g]\n",(*minu), (*minv), (*maxu), (*maxv));
}
void _cdecl SetCineFilterStartColor_my(int red, int green, int blue, int alpha)
{
   funcname1 = "SetCineFilterStartColor";
   SpyJassLog(" Exec:SetCineFilterStartColor...");
   SetCineFilterStartColor_ptr(red, green, blue, alpha);
   SpyJassLog("[SetCineFilterStartColor] OK [red:%s, green:%s, blue:%s, alpha:%s]\n",GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), GetStrID(alpha).c_str( ));
}
void _cdecl SetCineFilterStartUV_my(float *minu, float *minv, float *maxu, float *maxv)
{
   funcname1 = "SetCineFilterStartUV";
   SpyJassLog(" Exec:SetCineFilterStartUV...");
   SetCineFilterStartUV_ptr(minu, minv, maxu, maxv);
   SpyJassLog("[SetCineFilterStartUV] OK [minu:%.4g, minv:%.4g, maxu:%.4g, maxv:%.4g]\n",(*minu), (*minv), (*maxu), (*maxv));
}
void _cdecl SetCineFilterTexMapFlags_my(HTEXMAPFLAGS Flags)
{
   funcname1 = "SetCineFilterTexMapFlags";
   SpyJassLog(" Exec:SetCineFilterTexMapFlags...");
   SetCineFilterTexMapFlags_ptr(Flags);
   SpyJassLog("[SetCineFilterTexMapFlags] OK [Flags:%s]\n",GetStrID(Flags).c_str( ));
}
void _cdecl SetCineFilterTexture_my(CJassString filename)
{
   funcname1 = "SetCineFilterTexture";
   SpyJassLog(" Exec:SetCineFilterTexture...");
   SetCineFilterTexture_ptr(filename);
   SpyJassLog("[SetCineFilterTexture] OK [filename:%s]\n",ReadJassStringNormal(filename));
}
void _cdecl SetCinematicCamera_my(CJassString cameraModelFile)
{
   funcname1 = "SetCinematicCamera";
   SpyJassLog(" Exec:SetCinematicCamera...");
   SetCinematicCamera_ptr(cameraModelFile);
   SpyJassLog("[SetCinematicCamera] OK [cameraModelFile:%s]\n",ReadJassStringNormal(cameraModelFile));
}
void _cdecl SetCinematicScene_my(int portraitUnitId, HPLAYERCOLOR color, CJassString speakerTitle, CJassString text, float *sceneDuration, float *voiceoverDuration)
{
   funcname1 = "SetCinematicScene";
   SpyJassLog(" Exec:SetCinematicScene...");
   SetCinematicScene_ptr(portraitUnitId, color, speakerTitle, text, sceneDuration, voiceoverDuration);
   SpyJassLog("[SetCinematicScene] OK [portraitUnitId:%s, color:%s, speakerTitle:%s, text:%s, sceneDuration:%.4g, voiceoverDuration:%.4g]\n",GetStrID(portraitUnitId).c_str( ), GetStrID(color).c_str( ), ReadJassStringNormal(speakerTitle), ReadJassStringNormal(text), (*sceneDuration), (*voiceoverDuration));
}
void _cdecl SetCreatureDensity_my(HMAPDENSITY density)
{
   funcname1 = "SetCreatureDensity";
   SpyJassLog(" Exec:SetCreatureDensity...");
   SetCreatureDensity_ptr(density);
   SpyJassLog("[SetCreatureDensity] OK [density:%s]\n",GetStrID(density).c_str( ));
}
void _cdecl SetCreepCampFilterState_my(BOOL state)
{
   funcname1 = "SetCreepCampFilterState";
   SpyJassLog(" Exec:SetCreepCampFilterState...");
   SetCreepCampFilterState_ptr(state);
   SpyJassLog("[SetCreepCampFilterState] OK [state:%s]\n",BoolToStr(state));
}
void _cdecl SetCustomCampaignButtonVisible_my(int Button, BOOL visible)
{
   funcname1 = "SetCustomCampaignButtonVisible";
   SpyJassLog(" Exec:SetCustomCampaignButtonVisible...");
   SetCustomCampaignButtonVisible_ptr(Button, visible);
   SpyJassLog("[SetCustomCampaignButtonVisible] OK [Button:%s, visible:%s]\n",GetStrID(Button).c_str( ), BoolToStr(visible));
}
void _cdecl SetDayNightModels_my(CJassString terrainDNCFile, CJassString unitDNCFile)
{
   funcname1 = "SetDayNightModels";
   SpyJassLog(" Exec:SetDayNightModels...");
   SetDayNightModels_ptr(terrainDNCFile, unitDNCFile);
   SpyJassLog("[SetDayNightModels] OK [terrainDNCFile:%s, unitDNCFile:%s]\n",ReadJassStringNormal(terrainDNCFile), ReadJassStringNormal(unitDNCFile));
}
void _cdecl SetDefaultDifficulty_my(HGAMEDIFFICULTY g)
{
   funcname1 = "SetDefaultDifficulty";
   SpyJassLog(" Exec:SetDefaultDifficulty...");
   SetDefaultDifficulty_ptr(g);
   SpyJassLog("[SetDefaultDifficulty] OK [g:%s]\n",GetStrID(g).c_str( ));
}
void _cdecl SetDefendPlayer_my(BOOL arg1)
{
   funcname1 = "SetDefendPlayer";
   SpyJassLog(" Exec:SetDefendPlayer...");
   SetDefendPlayer_ptr(arg1);
   SpyJassLog("[SetDefendPlayer] OK [arg1:%s]\n",BoolToStr(arg1));
}
void _cdecl SetDestructableAnimation_my(HDESTRUCTABLE d, CJassString Animation)
{
   funcname1 = "SetDestructableAnimation";
   SpyJassLog(" Exec:SetDestructableAnimation...");
   SetDestructableAnimation_ptr(d, Animation);
   SpyJassLog("[SetDestructableAnimation] OK [d:%s, Animation:%s]\n",GetStrID(d).c_str( ), ReadJassStringNormal(Animation));
}
void _cdecl SetDestructableAnimationSpeed_my(HDESTRUCTABLE d, float *speedFactor)
{
   funcname1 = "SetDestructableAnimationSpeed";
   SpyJassLog(" Exec:SetDestructableAnimationSpeed...");
   SetDestructableAnimationSpeed_ptr(d, speedFactor);
   SpyJassLog("[SetDestructableAnimationSpeed] OK [d:%s, speedFactor:%.4g]\n",GetStrID(d).c_str( ), (*speedFactor));
}
void _cdecl SetDestructableInvulnerable_my(HDESTRUCTABLE d, BOOL flag)
{
   funcname1 = "SetDestructableInvulnerable";
   SpyJassLog(" Exec:SetDestructableInvulnerable...");
   SetDestructableInvulnerable_ptr(d, flag);
   SpyJassLog("[SetDestructableInvulnerable] OK [d:%s, flag:%s]\n",GetStrID(d).c_str( ), BoolToStr(flag));
}
void _cdecl SetDestructableLife_my(HDESTRUCTABLE d, float *life)
{
   funcname1 = "SetDestructableLife";
   SpyJassLog(" Exec:SetDestructableLife...");
   SetDestructableLife_ptr(d, life);
   SpyJassLog("[SetDestructableLife] OK [d:%s, life:%.4g]\n",GetStrID(d).c_str( ), (*life));
}
void _cdecl SetDestructableMaxLife_my(HDESTRUCTABLE d, float *max)
{
   funcname1 = "SetDestructableMaxLife";
   SpyJassLog(" Exec:SetDestructableMaxLife...");
   SetDestructableMaxLife_ptr(d, max);
   SpyJassLog("[SetDestructableMaxLife] OK [d:%s, max:%.4g]\n",GetStrID(d).c_str( ), (*max));
}
void _cdecl SetDestructableOccluderHeight_my(HDESTRUCTABLE d, float *height)
{
   funcname1 = "SetDestructableOccluderHeight";
   SpyJassLog(" Exec:SetDestructableOccluderHeight...");
   SetDestructableOccluderHeight_ptr(d, height);
   SpyJassLog("[SetDestructableOccluderHeight] OK [d:%s, height:%.4g]\n",GetStrID(d).c_str( ), (*height));
}
void _cdecl SetDoodadAnimation_my(float *x, float *y, float *radius, int doodadID, BOOL nearestOnly, CJassString animName, BOOL animRandom)
{
   funcname1 = "SetDoodadAnimation";
   SpyJassLog(" Exec:SetDoodadAnimation...");
   SetDoodadAnimation_ptr(x, y, radius, doodadID, nearestOnly, animName, animRandom);
   SpyJassLog("[SetDoodadAnimation] OK [x:%.4g, y:%.4g, radius:%.4g, doodadID:%s, nearestOnly:%s, animName:%s, animRandom:%s]\n",(*x), (*y), (*radius), GetStrID(doodadID).c_str( ), BoolToStr(nearestOnly), ReadJassStringNormal(animName), BoolToStr(animRandom));
}
void _cdecl SetDoodadAnimationRect_my(HRECT r, int doodadID, CJassString animName, BOOL animRandom)
{
   funcname1 = "SetDoodadAnimationRect";
   SpyJassLog(" Exec:SetDoodadAnimationRect...");
   SetDoodadAnimationRect_ptr(r, doodadID, animName, animRandom);
   SpyJassLog("[SetDoodadAnimationRect] OK [r:%s, doodadID:%s, animName:%s, animRandom:%s]\n",GetStrID(r).c_str( ), GetStrID(doodadID).c_str( ), ReadJassStringNormal(animName), BoolToStr(animRandom));
}
void _cdecl SetEdCinematicAvailable_my(int campaignNumber, BOOL available)
{
   funcname1 = "SetEdCinematicAvailable";
   SpyJassLog(" Exec:SetEdCinematicAvailable...");
   SetEdCinematicAvailable_ptr(campaignNumber, available);
   SpyJassLog("[SetEdCinematicAvailable] OK [campaignNumber:%s, available:%s]\n",GetStrID(campaignNumber).c_str( ), BoolToStr(available));
}
BOOL _cdecl SetExpansion_my(HUNIT arg1, int arg2)
{
   funcname1 = "SetExpansion";
   SpyJassLog(" Exec:SetExpansion[arg1:%s, arg2:%s]...",GetUnitHID(arg1).c_str( ), GetStrID(arg2).c_str( ));
   BOOL returnvalue; 
   returnvalue = SetExpansion_ptr(arg1, arg2);
   SpyJassLog("[SetExpansion] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl SetFloatGameState_my(HFGAMESTATE FloatGameState, float *value)
{
   funcname1 = "SetFloatGameState";
   SpyJassLog(" Exec:SetFloatGameState...");
   SetFloatGameState_ptr(FloatGameState, value);
   SpyJassLog("[SetFloatGameState] OK [FloatGameState:%s, value:%.4g]\n",GetStrID(FloatGameState).c_str( ), (*value));
}
void _cdecl SetFogStateRadius_my(HPLAYER forWhichPlayer, HFOGSTATE State, float *centerx, float *centerY, float *radius, BOOL useSharedVision)
{
   funcname1 = "SetFogStateRadius";
   SpyJassLog(" Exec:SetFogStateRadius...");
   SetFogStateRadius_ptr(forWhichPlayer, State, centerx, centerY, radius, useSharedVision);
   SpyJassLog("[SetFogStateRadius] OK [forWhichPlayer:%i, State:%s, centerx:%.4g, centerY:%.4g, radius:%.4g, useSharedVision:%s]\n",GetPlayerId_ptr(forWhichPlayer), GetStrID(State).c_str( ), (*centerx), (*centerY), (*radius), BoolToStr(useSharedVision));
}
void _cdecl SetFogStateRadiusLoc_my(HPLAYER forWhichPlayer, HFOGSTATE State, HLOCATION center, float *radius, BOOL useSharedVision)
{
   funcname1 = "SetFogStateRadiusLoc";
   SpyJassLog(" Exec:SetFogStateRadiusLoc...");
   SetFogStateRadiusLoc_ptr(forWhichPlayer, State, center, radius, useSharedVision);
   SpyJassLog("[SetFogStateRadiusLoc] OK [forWhichPlayer:%i, State:%s, center:%s, radius:%.4g, useSharedVision:%s]\n",GetPlayerId_ptr(forWhichPlayer), GetStrID(State).c_str( ), GetStrID(center).c_str( ), (*radius), BoolToStr(useSharedVision));
}
void _cdecl SetFogStateRect_my(HPLAYER forWhichPlayer, HFOGSTATE State, HRECT where, BOOL useSharedVision)
{
   funcname1 = "SetFogStateRect";
   SpyJassLog(" Exec:SetFogStateRect...");
   SetFogStateRect_ptr(forWhichPlayer, State, where, useSharedVision);
   SpyJassLog("[SetFogStateRect] OK [forWhichPlayer:%i, State:%s, where:%s, useSharedVision:%s]\n",GetPlayerId_ptr(forWhichPlayer), GetStrID(State).c_str( ), GetStrID(where).c_str( ), BoolToStr(useSharedVision));
}
void _cdecl SetGameDifficulty_my(HGAMEDIFFICULTY difficulty)
{
   funcname1 = "SetGameDifficulty";
   SpyJassLog(" Exec:SetGameDifficulty...");
   SetGameDifficulty_ptr(difficulty);
   SpyJassLog("[SetGameDifficulty] OK [difficulty:%s]\n",GetStrID(difficulty).c_str( ));
}
void _cdecl SetGamePlacement_my(HPLACEMENT PlacementType)
{
   funcname1 = "SetGamePlacement";
   SpyJassLog(" Exec:SetGamePlacement...");
   SetGamePlacement_ptr(PlacementType);
   SpyJassLog("[SetGamePlacement] OK [PlacementType:%s]\n",GetStrID(PlacementType).c_str( ));
}
void _cdecl SetGameSpeed_my(HGAMESPEED speed)
{
   funcname1 = "SetGameSpeed";
   SpyJassLog(" Exec:SetGameSpeed...");
   SetGameSpeed_ptr(speed);
   SpyJassLog("[SetGameSpeed] OK [speed:%s]\n",GetStrID(speed).c_str( ));
}
void _cdecl SetGameTypeSupported_my(HGAMETYPE GameType, BOOL value)
{
   funcname1 = "SetGameTypeSupported";
   SpyJassLog(" Exec:SetGameTypeSupported...");
   SetGameTypeSupported_ptr(GameType, value);
   SpyJassLog("[SetGameTypeSupported] OK [GameType:%s, value:%s]\n",GetStrID(GameType).c_str( ), BoolToStr(value));
}
void _cdecl SetGroupsFlee_my(BOOL arg1)
{
   funcname1 = "SetGroupsFlee";
   SpyJassLog(" Exec:SetGroupsFlee...");
   SetGroupsFlee_ptr(arg1);
   SpyJassLog("[SetGroupsFlee] OK [arg1:%s]\n",BoolToStr(arg1));
}
void _cdecl SetHeroAgi_my(HUNIT hero, int newAgi, BOOL permanent)
{
   funcname1 = "SetHeroAgi";
   SpyJassLog(" Exec:SetHeroAgi...");
   SetHeroAgi_ptr(hero, newAgi, permanent);
   SpyJassLog("[SetHeroAgi] OK [hero:%s, newAgi:%s, permanent:%s]\n",GetUnitHID(hero).c_str( ), GetStrID(newAgi).c_str( ), BoolToStr(permanent));
}
void _cdecl SetHeroInt_my(HUNIT hero, int newInt, BOOL permanent)
{
   funcname1 = "SetHeroInt";
   SpyJassLog(" Exec:SetHeroInt...");
   SetHeroInt_ptr(hero, newInt, permanent);
   SpyJassLog("[SetHeroInt] OK [hero:%s, newInt:%s, permanent:%s]\n",GetUnitHID(hero).c_str( ), GetStrID(newInt).c_str( ), BoolToStr(permanent));
}
void _cdecl SetHeroLevel_my(HUNIT hero, int level, BOOL showEyeCandy)
{
   funcname1 = "SetHeroLevel";
   SpyJassLog(" Exec:SetHeroLevel...");
   SetHeroLevel_ptr(hero, level, showEyeCandy);
   SpyJassLog("[SetHeroLevel] OK [hero:%s, level:%s, showEyeCandy:%s]\n",GetUnitHID(hero).c_str( ), GetStrID(level).c_str( ), BoolToStr(showEyeCandy));
}
void _cdecl SetHeroLevels_my(CODE arg1)
{
   funcname1 = "SetHeroLevels";
   SpyJassLog(" Exec:SetHeroLevels...");
   SetHeroLevels_ptr(arg1);
   SpyJassLog("[SetHeroLevels] OK [arg1:%s]\n",GetStrID(arg1).c_str( ));
}
void _cdecl SetHeroStr_my(HUNIT hero, int newStr, BOOL permanent)
{
   funcname1 = "SetHeroStr";
   SpyJassLog(" Exec:SetHeroStr...");
   SetHeroStr_ptr(hero, newStr, permanent);
   SpyJassLog("[SetHeroStr] OK [hero:%s, newStr:%s, permanent:%s]\n",GetUnitHID(hero).c_str( ), GetStrID(newStr).c_str( ), BoolToStr(permanent));
}
void _cdecl SetHeroXP_my(HUNIT hero, int newXpVal, BOOL showEyeCandy)
{
   funcname1 = "SetHeroXP";
   SpyJassLog(" Exec:SetHeroXP...");
   SetHeroXP_ptr(hero, newXpVal, showEyeCandy);
   SpyJassLog("[SetHeroXP] OK [hero:%s, newXpVal:%s, showEyeCandy:%s]\n",GetUnitHID(hero).c_str( ), GetStrID(newXpVal).c_str( ), BoolToStr(showEyeCandy));
}
void _cdecl SetHeroesBuyItems_my(BOOL arg1)
{
   funcname1 = "SetHeroesBuyItems";
   SpyJassLog(" Exec:SetHeroesBuyItems...");
   SetHeroesBuyItems_ptr(arg1);
   SpyJassLog("[SetHeroesBuyItems] OK [arg1:%s]\n",BoolToStr(arg1));
}
void _cdecl SetHeroesFlee_my(BOOL arg1)
{
   funcname1 = "SetHeroesFlee";
   SpyJassLog(" Exec:SetHeroesFlee...");
   SetHeroesFlee_ptr(arg1);
   SpyJassLog("[SetHeroesFlee] OK [arg1:%s]\n",BoolToStr(arg1));
}
void _cdecl SetHeroesTakeItems_my(BOOL arg1)
{
   funcname1 = "SetHeroesTakeItems";
   SpyJassLog(" Exec:SetHeroesTakeItems...");
   SetHeroesTakeItems_ptr(arg1);
   SpyJassLog("[SetHeroesTakeItems] OK [arg1:%s]\n",BoolToStr(arg1));
}
void _cdecl SetIgnoreInjured_my(BOOL arg1)
{
   funcname1 = "SetIgnoreInjured";
   SpyJassLog(" Exec:SetIgnoreInjured...");
   SetIgnoreInjured_ptr(arg1);
   SpyJassLog("[SetIgnoreInjured] OK [arg1:%s]\n",BoolToStr(arg1));
}
void _cdecl SetImageAboveWater_my(HIMAGE Image, BOOL flag, BOOL useWaterAlpha)
{
   funcname1 = "SetImageAboveWater";
   SpyJassLog(" Exec:SetImageAboveWater...");
   SetImageAboveWater_ptr(Image, flag, useWaterAlpha);
   SpyJassLog("[SetImageAboveWater] OK [Image:%s, flag:%s, useWaterAlpha:%s]\n",GetStrID(Image).c_str( ), BoolToStr(flag), BoolToStr(useWaterAlpha));
}
void _cdecl SetImageColor_my(HIMAGE Image, int red, int green, int blue, int alpha)
{
   funcname1 = "SetImageColor";
   SpyJassLog(" Exec:SetImageColor...");
   SetImageColor_ptr(Image, red, green, blue, alpha);
   SpyJassLog("[SetImageColor] OK [Image:%s, red:%s, green:%s, blue:%s, alpha:%s]\n",GetStrID(Image).c_str( ), GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), GetStrID(alpha).c_str( ));
}
void _cdecl SetImageConstantHeight_my(HIMAGE Image, BOOL flag, float *height)
{
   funcname1 = "SetImageConstantHeight";
   SpyJassLog(" Exec:SetImageConstantHeight...");
   SetImageConstantHeight_ptr(Image, flag, height);
   SpyJassLog("[SetImageConstantHeight] OK [Image:%s, flag:%s, height:%.4g]\n",GetStrID(Image).c_str( ), BoolToStr(flag), (*height));
}
void _cdecl SetImagePosition_my(HIMAGE Image, float *x, float *y, float *z)
{
   funcname1 = "SetImagePosition";
   SpyJassLog(" Exec:SetImagePosition...");
   SetImagePosition_ptr(Image, x, y, z);
   SpyJassLog("[SetImagePosition] OK [Image:%s, x:%.4g, y:%.4g, z:%.4g]\n",GetStrID(Image).c_str( ), (*x), (*y), (*z));
}
void _cdecl SetImageRender_my(HIMAGE Image, BOOL flag)
{
   funcname1 = "SetImageRender";
   SpyJassLog(" Exec:SetImageRender...");
   SetImageRender_ptr(Image, flag);
   SpyJassLog("[SetImageRender] OK [Image:%s, flag:%s]\n",GetStrID(Image).c_str( ), BoolToStr(flag));
}
void _cdecl SetImageRenderAlways_my(HIMAGE Image, BOOL flag)
{
   funcname1 = "SetImageRenderAlways";
   SpyJassLog(" Exec:SetImageRenderAlways...");
   SetImageRenderAlways_ptr(Image, flag);
   SpyJassLog("[SetImageRenderAlways] OK [Image:%s, flag:%s]\n",GetStrID(Image).c_str( ), BoolToStr(flag));
}
void _cdecl SetImageType_my(HIMAGE Image, int imageType)
{
   funcname1 = "SetImageType";
   SpyJassLog(" Exec:SetImageType...");
   SetImageType_ptr(Image, imageType);
   SpyJassLog("[SetImageType] OK [Image:%s, imageType:%s]\n",GetStrID(Image).c_str( ), GetStrID(imageType).c_str( ));
}
void _cdecl SetIntegerGameState_my(HIGAMESTATE IntegerGameState, int value)
{
   funcname1 = "SetIntegerGameState";
   SpyJassLog(" Exec:SetIntegerGameState...");
   SetIntegerGameState_ptr(IntegerGameState, value);
   SpyJassLog("[SetIntegerGameState] OK [IntegerGameState:%s, value:%s]\n",GetStrID(IntegerGameState).c_str( ), GetStrID(value).c_str( ));
}
void _cdecl SetIntroShotModel_my(CJassString introModelPath)
{
   funcname1 = "SetIntroShotModel";
   SpyJassLog(" Exec:SetIntroShotModel...");
   SetIntroShotModel_ptr(introModelPath);
   SpyJassLog("[SetIntroShotModel] OK [introModelPath:%s]\n",ReadJassStringNormal(introModelPath));
}
void _cdecl SetIntroShotText_my(CJassString introText)
{
   funcname1 = "SetIntroShotText";
   SpyJassLog(" Exec:SetIntroShotText...");
   SetIntroShotText_ptr(introText);
   SpyJassLog("[SetIntroShotText] OK [introText:%s]\n",ReadJassStringNormal(introText));
}
void _cdecl SetItemCharges_my(HITEM item, int charges)
{
   funcname1 = "SetItemCharges";
   SpyJassLog(" Exec:SetItemCharges...");
   SetItemCharges_ptr(item, charges);
   SpyJassLog("[SetItemCharges] OK [item:%s, charges:%s]\n",GetItemHID(item).c_str( ), GetStrID(charges).c_str( ));
}
void _cdecl SetItemDropID_my(HITEM item, int unitId)
{
   funcname1 = "SetItemDropID";
   SpyJassLog(" Exec:SetItemDropID...");
   SetItemDropID_ptr(item, unitId);
   SpyJassLog("[SetItemDropID] OK [item:%s, unitId:%s]\n",GetItemHID(item).c_str( ), GetStrID(unitId).c_str( ));
}
void _cdecl SetItemDropOnDeath_my(HITEM item, BOOL flag)
{
   funcname1 = "SetItemDropOnDeath";
   SpyJassLog(" Exec:SetItemDropOnDeath...");
   SetItemDropOnDeath_ptr(item, flag);
   SpyJassLog("[SetItemDropOnDeath] OK [item:%s, flag:%s]\n",GetItemHID(item).c_str( ), BoolToStr(flag));
}
void _cdecl SetItemDroppable_my(HITEM i, BOOL flag)
{
   funcname1 = "SetItemDroppable";
   SpyJassLog(" Exec:SetItemDroppable...");
   SetItemDroppable_ptr(i, flag);
   SpyJassLog("[SetItemDroppable] OK [i:%s, flag:%s]\n",GetItemHID(i).c_str( ), BoolToStr(flag));
}
void _cdecl SetItemInvulnerable_my(HITEM item, BOOL flag)
{
   funcname1 = "SetItemInvulnerable";
   SpyJassLog(" Exec:SetItemInvulnerable...");
   SetItemInvulnerable_ptr(item, flag);
   SpyJassLog("[SetItemInvulnerable] OK [item:%s, flag:%s]\n",GetItemHID(item).c_str( ), BoolToStr(flag));
}
void _cdecl SetItemPawnable_my(HITEM i, BOOL flag)
{
   funcname1 = "SetItemPawnable";
   SpyJassLog(" Exec:SetItemPawnable...");
   SetItemPawnable_ptr(i, flag);
   SpyJassLog("[SetItemPawnable] OK [i:%s, flag:%s]\n",GetItemHID(i).c_str( ), BoolToStr(flag));
}
void _cdecl SetItemPlayer_my(HITEM item, HPLAYER player, BOOL changeColor)
{
   funcname1 = "SetItemPlayer";
   SpyJassLog(" Exec:SetItemPlayer...");
   SetItemPlayer_ptr(item, player, changeColor);
   SpyJassLog("[SetItemPlayer] OK [item:%s, player:%i, changeColor:%s]\n",GetItemHID(item).c_str( ), GetPlayerId_ptr(player), BoolToStr(changeColor));
}
void _cdecl SetItemPosition_my(HITEM i, float *x, float *y)
{
   funcname1 = "SetItemPosition";
   SpyJassLog(" Exec:SetItemPosition...");
   SetItemPosition_ptr(i, x, y);
   SpyJassLog("[SetItemPosition] OK [i:%s, x:%.4g, y:%.4g]\n",GetItemHID(i).c_str( ), (*x), (*y));
}
void _cdecl SetItemTypeSlots_my(HUNIT unit, int slots)
{
   funcname1 = "SetItemTypeSlots";
   SpyJassLog(" Exec:SetItemTypeSlots...");
   SetItemTypeSlots_ptr(unit, slots);
   SpyJassLog("[SetItemTypeSlots] OK [unit:%s, slots:%s]\n",GetUnitHID(unit).c_str( ), GetStrID(slots).c_str( ));
}
void _cdecl SetItemUserData_my(HITEM item, int data)
{
   funcname1 = "SetItemUserData";
   SpyJassLog(" Exec:SetItemUserData...");
   SetItemUserData_ptr(item, data);
   SpyJassLog("[SetItemUserData] OK [item:%s, data:%s]\n",GetItemHID(item).c_str( ), GetStrID(data).c_str( ));
}
void _cdecl SetItemVisible_my(HITEM item, BOOL show)
{
   funcname1 = "SetItemVisible";
   SpyJassLog(" Exec:SetItemVisible...");
   SetItemVisible_ptr(item, show);
   SpyJassLog("[SetItemVisible] OK [item:%s, show:%s]\n",GetItemHID(item).c_str( ), BoolToStr(show));
}
BOOL _cdecl SetLightningColor_my(HLIGHTNING Bolt, float *r, float *g, float *b, float *a)
{
   funcname1 = "SetLightningColor";
   SpyJassLog(" Exec:SetLightningColor[Bolt:%s, r:%.4g, g:%.4g, b:%.4g, a:%.4g]...",GetStrID(Bolt).c_str( ), (*r), (*g), (*b), (*a));
   BOOL returnvalue; 
   returnvalue = SetLightningColor_ptr(Bolt, r, g, b, a);
   SpyJassLog("[SetLightningColor] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl SetMapDescription_my(CJassString description)
{
   funcname1 = "SetMapDescription";
   SpyJassLog(" Exec:SetMapDescription...");
   SetMapDescription_ptr(description);
   SpyJassLog("[SetMapDescription] OK [description:%s]\n",ReadJassStringNormal(description));
}
void _cdecl SetMapFlag_my(HMAPFLAG MapFlag, BOOL value)
{
   funcname1 = "SetMapFlag";
   SpyJassLog(" Exec:SetMapFlag...");
   SetMapFlag_ptr(MapFlag, value);
   SpyJassLog("[SetMapFlag] OK [MapFlag:%s, value:%s]\n",GetStrID(MapFlag).c_str( ), BoolToStr(value));
}
void _cdecl SetMapMusic_my(CJassString musicName, BOOL random, int index)
{
   funcname1 = "SetMapMusic";
   SpyJassLog(" Exec:SetMapMusic...");
   SetMapMusic_ptr(musicName, random, index);
   SpyJassLog("[SetMapMusic] OK [musicName:%s, random:%s, index:%s]\n",ReadJassStringNormal(musicName), BoolToStr(random), GetStrID(index).c_str( ));
}
void _cdecl SetMapName_my(CJassString name)
{
   funcname1 = "SetMapName";
   SpyJassLog(" Exec:SetMapName...");
   SetMapName_ptr(name);
   SpyJassLog("[SetMapName] OK [name:%s]\n",ReadJassStringNormal(name));
}
void _cdecl SetMeleeAI_my()
{
   funcname1 = "SetMeleeAI";
   SpyJassLog(" Exec:SetMeleeAI...");
   SetMeleeAI_ptr();
   SpyJassLog("[SetMeleeAI] OK []\n");
}
void _cdecl SetMissionAvailable_my(int campaignNumber, int missionNumber, BOOL available)
{
   funcname1 = "SetMissionAvailable";
   SpyJassLog(" Exec:SetMissionAvailable...");
   SetMissionAvailable_ptr(campaignNumber, missionNumber, available);
   SpyJassLog("[SetMissionAvailable] OK [campaignNumber:%s, missionNumber:%s, available:%s]\n",GetStrID(campaignNumber).c_str( ), GetStrID(missionNumber).c_str( ), BoolToStr(available));
}
void _cdecl SetMusicPlayPosition_my(int millisecs)
{
   funcname1 = "SetMusicPlayPosition";
   SpyJassLog(" Exec:SetMusicPlayPosition...");
   SetMusicPlayPosition_ptr(millisecs);
   SpyJassLog("[SetMusicPlayPosition] OK [millisecs:%s]\n",GetStrID(millisecs).c_str( ));
}
void _cdecl SetMusicVolume_my(int volume)
{
   funcname1 = "SetMusicVolume";
   SpyJassLog(" Exec:SetMusicVolume...");
   SetMusicVolume_ptr(volume);
   SpyJassLog("[SetMusicVolume] OK [volume:%s]\n",GetStrID(volume).c_str( ));
}
void _cdecl SetNewHeroes_my(BOOL arg1)
{
   funcname1 = "SetNewHeroes";
   SpyJassLog(" Exec:SetNewHeroes...");
   SetNewHeroes_ptr(arg1);
   SpyJassLog("[SetNewHeroes] OK [arg1:%s]\n",BoolToStr(arg1));
}
void _cdecl SetOpCinematicAvailable_my(int campaignNumber, BOOL available)
{
   funcname1 = "SetOpCinematicAvailable";
   SpyJassLog(" Exec:SetOpCinematicAvailable...");
   SetOpCinematicAvailable_ptr(campaignNumber, available);
   SpyJassLog("[SetOpCinematicAvailable] OK [campaignNumber:%s, available:%s]\n",GetStrID(campaignNumber).c_str( ), BoolToStr(available));
}
void _cdecl SetPeonsRepair_my(BOOL arg1)
{
   funcname1 = "SetPeonsRepair";
   SpyJassLog(" Exec:SetPeonsRepair...");
   SetPeonsRepair_ptr(arg1);
   SpyJassLog("[SetPeonsRepair] OK [arg1:%s]\n",BoolToStr(arg1));
}
void _cdecl SetPlayerAbilityAvailable_my(HPLAYER player, int abilid, BOOL avail)
{
   funcname1 = "SetPlayerAbilityAvailable";
   SpyJassLog(" Exec:SetPlayerAbilityAvailable...");
   SetPlayerAbilityAvailable_ptr(player, abilid, avail);
   SpyJassLog("[SetPlayerAbilityAvailable] OK [player:%i, abilid:%s, avail:%s]\n",GetPlayerId_ptr(player), GetStrID(abilid).c_str( ), BoolToStr(avail));
}
void _cdecl SetPlayerAlliance_my(HPLAYER sourcePlayer, HPLAYER otherPlayer, HALLIANCETYPE AllianceSetting, BOOL value)
{
   funcname1 = "SetPlayerAlliance";
   SpyJassLog(" Exec:SetPlayerAlliance...");
   SetPlayerAlliance_ptr(sourcePlayer, otherPlayer, AllianceSetting, value);
   SpyJassLog("[SetPlayerAlliance] OK [sourcePlayer:%i, otherPlayer:%i, AllianceSetting:%s, value:%s]\n",GetPlayerId_ptr(sourcePlayer), GetPlayerId_ptr(otherPlayer), GetStrID(AllianceSetting).c_str( ), BoolToStr(value));
}
void _cdecl SetPlayerColor_my(HPLAYER player, HPLAYERCOLOR color)
{
   funcname1 = "SetPlayerColor";
   SpyJassLog(" Exec:SetPlayerColor...");
   SetPlayerColor_ptr(player, color);
   SpyJassLog("[SetPlayerColor] OK [player:%i, color:%s]\n",GetPlayerId_ptr(player), GetStrID(color).c_str( ));
}
void _cdecl SetPlayerController_my(HPLAYER player, HMAPCONTROL controlType)
{
   funcname1 = "SetPlayerController";
   SpyJassLog(" Exec:SetPlayerController...");
   SetPlayerController_ptr(player, controlType);
   SpyJassLog("[SetPlayerController] OK [player:%i, controlType:%s]\n",GetPlayerId_ptr(player), GetStrID(controlType).c_str( ));
}
void _cdecl SetPlayerHandicap_my(HPLAYER player, float *handicap)
{
   funcname1 = "SetPlayerHandicap";
   SpyJassLog(" Exec:SetPlayerHandicap...");
   SetPlayerHandicap_ptr(player, handicap);
   SpyJassLog("[SetPlayerHandicap] OK [player:%i, handicap:%.4g]\n",GetPlayerId_ptr(player), (*handicap));
}
void _cdecl SetPlayerHandicapXP_my(HPLAYER player, float *handicap)
{
   funcname1 = "SetPlayerHandicapXP";
   SpyJassLog(" Exec:SetPlayerHandicapXP...");
   SetPlayerHandicapXP_ptr(player, handicap);
   SpyJassLog("[SetPlayerHandicapXP] OK [player:%i, handicap:%.4g]\n",GetPlayerId_ptr(player), (*handicap));
}
void _cdecl SetPlayerName_my(HPLAYER player, CJassString name)
{
   funcname1 = "SetPlayerName";
   SpyJassLog(" Exec:SetPlayerName...");
   SetPlayerName_ptr(player, name);
   SpyJassLog("[SetPlayerName] OK [player:%i, name:%s]\n",GetPlayerId_ptr(player), ReadJassStringNormal(name));
}
void _cdecl SetPlayerOnScoreScreen_my(HPLAYER player, BOOL flag)
{
   funcname1 = "SetPlayerOnScoreScreen";
   SpyJassLog(" Exec:SetPlayerOnScoreScreen...");
   SetPlayerOnScoreScreen_ptr(player, flag);
   SpyJassLog("[SetPlayerOnScoreScreen] OK [player:%i, flag:%s]\n",GetPlayerId_ptr(player), BoolToStr(flag));
}
void _cdecl SetPlayerRacePreference_my(HPLAYER player, HRACEPREFERENCE RacePreference)
{
   funcname1 = "SetPlayerRacePreference";
   SpyJassLog(" Exec:SetPlayerRacePreference...");
   SetPlayerRacePreference_ptr(player, RacePreference);
   SpyJassLog("[SetPlayerRacePreference] OK [player:%i, RacePreference:%s]\n",GetPlayerId_ptr(player), GetStrID(RacePreference).c_str( ));
}
void _cdecl SetPlayerRaceSelectable_my(HPLAYER player, BOOL value)
{
   funcname1 = "SetPlayerRaceSelectable";
   SpyJassLog(" Exec:SetPlayerRaceSelectable...");
   SetPlayerRaceSelectable_ptr(player, value);
   SpyJassLog("[SetPlayerRaceSelectable] OK [player:%i, value:%s]\n",GetPlayerId_ptr(player), BoolToStr(value));
}
void _cdecl SetPlayerStartLocation_my(HPLAYER player, int startLocIndex)
{
   funcname1 = "SetPlayerStartLocation";
   SpyJassLog(" Exec:SetPlayerStartLocation...");
   SetPlayerStartLocation_ptr(player, startLocIndex);
   SpyJassLog("[SetPlayerStartLocation] OK [player:%i, startLocIndex:%s]\n",GetPlayerId_ptr(player), GetStrID(startLocIndex).c_str( ));
}
void _cdecl SetPlayerState_my(HPLAYER player, HPLAYERSTATE PlayerState, int value)
{
   funcname1 = "SetPlayerState";
   SpyJassLog(" Exec:SetPlayerState...");
   SetPlayerState_ptr(player, PlayerState, value);
   SpyJassLog("[SetPlayerState] OK [player:%i, PlayerState:%s, value:%s]\n",GetPlayerId_ptr(player), GetStrID(PlayerState).c_str( ), GetStrID(value).c_str( ));
}
void _cdecl SetPlayerTaxRate_my(HPLAYER sourcePlayer, HPLAYER otherPlayer, HPLAYERSTATE Resource, int rate)
{
   funcname1 = "SetPlayerTaxRate";
   SpyJassLog(" Exec:SetPlayerTaxRate...");
   SetPlayerTaxRate_ptr(sourcePlayer, otherPlayer, Resource, rate);
   SpyJassLog("[SetPlayerTaxRate] OK [sourcePlayer:%i, otherPlayer:%i, Resource:%s, rate:%s]\n",GetPlayerId_ptr(sourcePlayer), GetPlayerId_ptr(otherPlayer), GetStrID(Resource).c_str( ), GetStrID(rate).c_str( ));
}
void _cdecl SetPlayerTeam_my(HPLAYER player, int Team)
{
   funcname1 = "SetPlayerTeam";
   SpyJassLog(" Exec:SetPlayerTeam...");
   SetPlayerTeam_ptr(player, Team);
   SpyJassLog("[SetPlayerTeam] OK [player:%i, Team:%s]\n",GetPlayerId_ptr(player), GetStrID(Team).c_str( ));
}
void _cdecl SetPlayerTechMaxAllowed_my(HPLAYER player, int techid, int maximum)
{
   funcname1 = "SetPlayerTechMaxAllowed";
   SpyJassLog(" Exec:SetPlayerTechMaxAllowed...");
   SetPlayerTechMaxAllowed_ptr(player, techid, maximum);
   SpyJassLog("[SetPlayerTechMaxAllowed] OK [player:%i, techid:%s, maximum:%s]\n",GetPlayerId_ptr(player), GetStrID(techid).c_str( ), GetStrID(maximum).c_str( ));
}
void _cdecl SetPlayerTechResearched_my(HPLAYER player, int techid, int setToLevel)
{
   funcname1 = "SetPlayerTechResearched";
   SpyJassLog(" Exec:SetPlayerTechResearched...");
   SetPlayerTechResearched_ptr(player, techid, setToLevel);
   SpyJassLog("[SetPlayerTechResearched] OK [player:%i, techid:%s, setToLevel:%s]\n",GetPlayerId_ptr(player), GetStrID(techid).c_str( ), GetStrID(setToLevel).c_str( ));
}
void _cdecl SetPlayerUnitsOwner_my(HPLAYER player, int newOwner)
{
   funcname1 = "SetPlayerUnitsOwner";
   SpyJassLog(" Exec:SetPlayerUnitsOwner...");
   SetPlayerUnitsOwner_ptr(player, newOwner);
   SpyJassLog("[SetPlayerUnitsOwner] OK [player:%i, newOwner:%s]\n",GetPlayerId_ptr(player), GetStrID(newOwner).c_str( ));
}
void _cdecl SetPlayers_my(int playercount)
{
   funcname1 = "SetPlayers";
   SpyJassLog(" Exec:SetPlayers...");
   SetPlayers_ptr(playercount);
   SpyJassLog("[SetPlayers] OK [playercount:%s]\n",GetStrID(playercount).c_str( ));
}
BOOL _cdecl SetProduce_my(int arg1, int arg2, int arg3)
{
   funcname1 = "SetProduce";
   SpyJassLog(" Exec:SetProduce[arg1:%s, arg2:%s, arg3:%s]...",GetStrID(arg1).c_str( ), GetStrID(arg2).c_str( ), GetStrID(arg3).c_str( ));
   BOOL returnvalue; 
   returnvalue = SetProduce_ptr(arg1, arg2, arg3);
   SpyJassLog("[SetProduce] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl SetRandomPaths_my(BOOL arg1)
{
   funcname1 = "SetRandomPaths";
   SpyJassLog(" Exec:SetRandomPaths...");
   SetRandomPaths_ptr(arg1);
   SpyJassLog("[SetRandomPaths] OK [arg1:%s]\n",BoolToStr(arg1));
}
void _cdecl SetRandomSeed_my(int seed)
{
   funcname1 = "SetRandomSeed";
   SpyJassLog(" Exec:SetRandomSeed...");
   SetRandomSeed_ptr(seed);
   SpyJassLog("[SetRandomSeed] OK [seed:%s]\n",GetStrID(seed).c_str( ));
}
void _cdecl SetRect_my(HRECT Rect, float *minx, float *miny, float *maxx, float *maxy)
{
   funcname1 = "SetRect";
   SpyJassLog(" Exec:SetRect...");
   SetRect_ptr(Rect, minx, miny, maxx, maxy);
   SpyJassLog("[SetRect] OK [Rect:%s, minx:%.4g, miny:%.4g, maxx:%.4g, maxy:%.4g]\n",GetStrID(Rect).c_str( ), (*minx), (*miny), (*maxx), (*maxy));
}
void _cdecl SetRectFromLoc_my(HRECT Rect, HLOCATION min, HLOCATION max)
{
   funcname1 = "SetRectFromLoc";
   SpyJassLog(" Exec:SetRectFromLoc...");
   SetRectFromLoc_ptr(Rect, min, max);
   SpyJassLog("[SetRectFromLoc] OK [Rect:%s, min:%s, max:%s]\n",GetStrID(Rect).c_str( ), GetStrID(min).c_str( ), GetStrID(max).c_str( ));
}
void _cdecl SetReplacementCount_my(int arg1)
{
   funcname1 = "SetReplacementCount";
   SpyJassLog(" Exec:SetReplacementCount...");
   SetReplacementCount_ptr(arg1);
   SpyJassLog("[SetReplacementCount] OK [arg1:%s]\n",GetStrID(arg1).c_str( ));
}
void _cdecl SetReservedLocalHeroButtons_my(int reserved)
{
   funcname1 = "SetReservedLocalHeroButtons";
   SpyJassLog(" Exec:SetReservedLocalHeroButtons...");
   SetReservedLocalHeroButtons_ptr(reserved);
   SpyJassLog("[SetReservedLocalHeroButtons] OK [reserved:%s]\n",GetStrID(reserved).c_str( ));
}
void _cdecl SetResourceAmount_my(HUNIT unit, int amount)
{
   funcname1 = "SetResourceAmount";
   SpyJassLog(" Exec:SetResourceAmount...");
   SetResourceAmount_ptr(unit, amount);
   SpyJassLog("[SetResourceAmount] OK [unit:%s, amount:%s]\n",GetUnitHID(unit).c_str( ), GetStrID(amount).c_str( ));
}
void _cdecl SetResourceDensity_my(HMAPDENSITY density)
{
   funcname1 = "SetResourceDensity";
   SpyJassLog(" Exec:SetResourceDensity...");
   SetResourceDensity_ptr(density);
   SpyJassLog("[SetResourceDensity] OK [density:%s]\n",GetStrID(density).c_str( ));
}
void _cdecl SetSkyModel_my(CJassString skyModelFile)
{
   funcname1 = "SetSkyModel";
   SpyJassLog(" Exec:SetSkyModel...");
   SetSkyModel_ptr(skyModelFile);
   SpyJassLog("[SetSkyModel] OK [skyModelFile:%s]\n",ReadJassStringNormal(skyModelFile));
}
void _cdecl SetSlowChopping_my(BOOL arg1)
{
   funcname1 = "SetSlowChopping";
   SpyJassLog(" Exec:SetSlowChopping...");
   SetSlowChopping_ptr(arg1);
   SpyJassLog("[SetSlowChopping] OK [arg1:%s]\n",BoolToStr(arg1));
}
void _cdecl SetSmartArtillery_my(BOOL arg1)
{
   funcname1 = "SetSmartArtillery";
   SpyJassLog(" Exec:SetSmartArtillery...");
   SetSmartArtillery_ptr(arg1);
   SpyJassLog("[SetSmartArtillery] OK [arg1:%s]\n",BoolToStr(arg1));
}
void _cdecl SetSoundChannel_my(HSOUND soundHandle, int channel)
{
   funcname1 = "SetSoundChannel";
   SpyJassLog(" Exec:SetSoundChannel...");
   SetSoundChannel_ptr(soundHandle, channel);
   SpyJassLog("[SetSoundChannel] OK [soundHandle:%s, channel:%s]\n",GetStrID(soundHandle).c_str( ), GetStrID(channel).c_str( ));
}
void _cdecl SetSoundConeAngles_my(HSOUND soundHandle, float *inside, float *outside, int outsideVolume)
{
   funcname1 = "SetSoundConeAngles";
   SpyJassLog(" Exec:SetSoundConeAngles...");
   SetSoundConeAngles_ptr(soundHandle, inside, outside, outsideVolume);
   SpyJassLog("[SetSoundConeAngles] OK [soundHandle:%s, inside:%.4g, outside:%.4g, outsideVolume:%s]\n",GetStrID(soundHandle).c_str( ), (*inside), (*outside), GetStrID(outsideVolume).c_str( ));
}
void _cdecl SetSoundConeOrientation_my(HSOUND soundHandle, float *x, float *y, float *z)
{
   funcname1 = "SetSoundConeOrientation";
   SpyJassLog(" Exec:SetSoundConeOrientation...");
   SetSoundConeOrientation_ptr(soundHandle, x, y, z);
   SpyJassLog("[SetSoundConeOrientation] OK [soundHandle:%s, x:%.4g, y:%.4g, z:%.4g]\n",GetStrID(soundHandle).c_str( ), (*x), (*y), (*z));
}
void _cdecl SetSoundDistanceCutoff_my(HSOUND soundHandle, float *cutoff)
{
   funcname1 = "SetSoundDistanceCutoff";
   SpyJassLog(" Exec:SetSoundDistanceCutoff...");
   SetSoundDistanceCutoff_ptr(soundHandle, cutoff);
   SpyJassLog("[SetSoundDistanceCutoff] OK [soundHandle:%s, cutoff:%.4g]\n",GetStrID(soundHandle).c_str( ), (*cutoff));
}
void _cdecl SetSoundDistances_my(HSOUND soundHandle, float *minDist, float *maxDist)
{
   funcname1 = "SetSoundDistances";
   SpyJassLog(" Exec:SetSoundDistances...");
   SetSoundDistances_ptr(soundHandle, minDist, maxDist);
   SpyJassLog("[SetSoundDistances] OK [soundHandle:%s, minDist:%.4g, maxDist:%.4g]\n",GetStrID(soundHandle).c_str( ), (*minDist), (*maxDist));
}
void _cdecl SetSoundDuration_my(HSOUND soundHandle, int duration)
{
   funcname1 = "SetSoundDuration";
   SpyJassLog(" Exec:SetSoundDuration...");
   SetSoundDuration_ptr(soundHandle, duration);
   SpyJassLog("[SetSoundDuration] OK [soundHandle:%s, duration:%s]\n",GetStrID(soundHandle).c_str( ), GetStrID(duration).c_str( ));
}
void _cdecl SetSoundParamsFromLabel_my(HSOUND soundHandle, CJassString soundLabel)
{
   funcname1 = "SetSoundParamsFromLabel";
   SpyJassLog(" Exec:SetSoundParamsFromLabel...");
   SetSoundParamsFromLabel_ptr(soundHandle, soundLabel);
   SpyJassLog("[SetSoundParamsFromLabel] OK [soundHandle:%s, soundLabel:%s]\n",GetStrID(soundHandle).c_str( ), ReadJassStringNormal(soundLabel));
}
void _cdecl SetSoundPitch_my(HSOUND soundHandle, float *pitch)
{
   funcname1 = "SetSoundPitch";
   SpyJassLog(" Exec:SetSoundPitch...");
   SetSoundPitch_ptr(soundHandle, pitch);
   SpyJassLog("[SetSoundPitch] OK [soundHandle:%s, pitch:%.4g]\n",GetStrID(soundHandle).c_str( ), (*pitch));
}
void _cdecl SetSoundPlayPosition_my(HSOUND soundHandle, int millisecs)
{
   funcname1 = "SetSoundPlayPosition";
   SpyJassLog(" Exec:SetSoundPlayPosition...");
   SetSoundPlayPosition_ptr(soundHandle, millisecs);
   SpyJassLog("[SetSoundPlayPosition] OK [soundHandle:%s, millisecs:%s]\n",GetStrID(soundHandle).c_str( ), GetStrID(millisecs).c_str( ));
}
void _cdecl SetSoundPosition_my(HSOUND soundHandle, float *x, float *y, float *z)
{
   funcname1 = "SetSoundPosition";
   SpyJassLog(" Exec:SetSoundPosition...");
   SetSoundPosition_ptr(soundHandle, x, y, z);
   SpyJassLog("[SetSoundPosition] OK [soundHandle:%s, x:%.4g, y:%.4g, z:%.4g]\n",GetStrID(soundHandle).c_str( ), (*x), (*y), (*z));
}
void _cdecl SetSoundVelocity_my(HSOUND soundHandle, float *x, float *y, float *z)
{
   funcname1 = "SetSoundVelocity";
   SpyJassLog(" Exec:SetSoundVelocity...");
   SetSoundVelocity_ptr(soundHandle, x, y, z);
   SpyJassLog("[SetSoundVelocity] OK [soundHandle:%s, x:%.4g, y:%.4g, z:%.4g]\n",GetStrID(soundHandle).c_str( ), (*x), (*y), (*z));
}
void _cdecl SetSoundVolume_my(HSOUND soundHandle, int volume)
{
   funcname1 = "SetSoundVolume";
   SpyJassLog(" Exec:SetSoundVolume...");
   SetSoundVolume_ptr(soundHandle, volume);
   SpyJassLog("[SetSoundVolume] OK [soundHandle:%s, volume:%s]\n",GetStrID(soundHandle).c_str( ), GetStrID(volume).c_str( ));
}
void _cdecl SetStackedSound_my(CJassString arg1, float *arg2, float *arg3)
{
   funcname1 = "SetStackedSound";
   SpyJassLog(" Exec:SetStackedSound...");
   SetStackedSound_ptr(arg1, arg2, arg3);
   SpyJassLog("[SetStackedSound] OK [arg1:%s, arg2:%.4g, arg3:%.4g]\n",ReadJassStringNormal(arg1), (*arg2), (*arg3));
}
void _cdecl SetStackedSoundRect_my(CJassString arg1, HRECT arg2)
{
   funcname1 = "SetStackedSoundRect";
   SpyJassLog(" Exec:SetStackedSoundRect...");
   SetStackedSoundRect_ptr(arg1, arg2);
   SpyJassLog("[SetStackedSoundRect] OK [arg1:%s, arg2:%s]\n",ReadJassStringNormal(arg1), GetStrID(arg2).c_str( ));
}
void _cdecl SetStagePoint_my(float *arg1, float *arg2)
{
   funcname1 = "SetStagePoint";
   SpyJassLog(" Exec:SetStagePoint...");
   SetStagePoint_ptr(arg1, arg2);
   SpyJassLog("[SetStagePoint] OK [arg1:%.4g, arg2:%.4g]\n",(*arg1), (*arg2));
}
void _cdecl SetStartLocPrio_my(int StartLoc, int prioSlotIndex, int otherStartLocIndex, HSTARTLOCPRIO priority)
{
   funcname1 = "SetStartLocPrio";
   SpyJassLog(" Exec:SetStartLocPrio...");
   SetStartLocPrio_ptr(StartLoc, prioSlotIndex, otherStartLocIndex, priority);
   SpyJassLog("[SetStartLocPrio] OK [StartLoc:%s, prioSlotIndex:%s, otherStartLocIndex:%s, priority:%s]\n",GetStrID(StartLoc).c_str( ), GetStrID(prioSlotIndex).c_str( ), GetStrID(otherStartLocIndex).c_str( ), GetStrID(priority).c_str( ));
}
void _cdecl SetStartLocPrioCount_my(int StartLoc, int prioSlotCount)
{
   funcname1 = "SetStartLocPrioCount";
   SpyJassLog(" Exec:SetStartLocPrioCount...");
   SetStartLocPrioCount_ptr(StartLoc, prioSlotCount);
   SpyJassLog("[SetStartLocPrioCount] OK [StartLoc:%s, prioSlotCount:%s]\n",GetStrID(StartLoc).c_str( ), GetStrID(prioSlotCount).c_str( ));
}
void _cdecl SetTargetHeroes_my(BOOL arg1)
{
   funcname1 = "SetTargetHeroes";
   SpyJassLog(" Exec:SetTargetHeroes...");
   SetTargetHeroes_ptr(arg1);
   SpyJassLog("[SetTargetHeroes] OK [arg1:%s]\n",BoolToStr(arg1));
}
void _cdecl SetTeams_my(int teamcount)
{
   funcname1 = "SetTeams";
   SpyJassLog(" Exec:SetTeams...");
   SetTeams_ptr(teamcount);
   SpyJassLog("[SetTeams] OK [teamcount:%s]\n",GetStrID(teamcount).c_str( ));
}
void _cdecl SetTerrainFog_my(float *a, float *b, float *c, float *d, float *e)
{
   funcname1 = "SetTerrainFog";
   SpyJassLog(" Exec:SetTerrainFog...");
   SetTerrainFog_ptr(a, b, c, d, e);
   SpyJassLog("[SetTerrainFog] OK [a:%.4g, b:%.4g, c:%.4g, d:%.4g, e:%.4g]\n",(*a), (*b), (*c), (*d), (*e));
}
void _cdecl SetTerrainFogEx_my(int style, float *zstart, float *zend, float *density, float *red, float *green, float *blue)
{
   funcname1 = "SetTerrainFogEx";
   SpyJassLog(" Exec:SetTerrainFogEx...");
   SetTerrainFogEx_ptr(style, zstart, zend, density, red, green, blue);
   SpyJassLog("[SetTerrainFogEx] OK [style:%s, zstart:%.4g, zend:%.4g, density:%.4g, red:%.4g, green:%.4g, blue:%.4g]\n",GetStrID(style).c_str( ), (*zstart), (*zend), (*density), (*red), (*green), (*blue));
}
void _cdecl SetTerrainPathable_my(float *x, float *y, HPATHINGTYPE t, BOOL flag)
{
   funcname1 = "SetTerrainPathable";
   SpyJassLog(" Exec:SetTerrainPathable...");
   SetTerrainPathable_ptr(x, y, t, flag);
   SpyJassLog("[SetTerrainPathable] OK [x:%.4g, y:%.4g, t:%s, flag:%s]\n",(*x), (*y), GetStrID(t).c_str( ), BoolToStr(flag));
}
void _cdecl SetTerrainType_my(float *x, float *y, int terrainType, int variation, int area, int shape)
{
   funcname1 = "SetTerrainType";
   SpyJassLog(" Exec:SetTerrainType...");
   SetTerrainType_ptr(x, y, terrainType, variation, area, shape);
   SpyJassLog("[SetTerrainType] OK [x:%.4g, y:%.4g, terrainType:%s, variation:%s, area:%s, shape:%s]\n",(*x), (*y), GetStrID(terrainType).c_str( ), GetStrID(variation).c_str( ), GetStrID(area).c_str( ), GetStrID(shape).c_str( ));
}
void _cdecl SetTextTagAge_my(HTEXTTAG t, float *age)
{
   funcname1 = "SetTextTagAge";
   SpyJassLog(" Exec:SetTextTagAge...");
   SetTextTagAge_ptr(t, age);
   SpyJassLog("[SetTextTagAge] OK [t:%s, age:%.4g]\n",GetStrID(t).c_str( ), (*age));
}
void _cdecl SetTextTagColor_my(HTEXTTAG t, int red, int green, int blue, int alpha)
{
   funcname1 = "SetTextTagColor";
   SpyJassLog(" Exec:SetTextTagColor...");
   SetTextTagColor_ptr(t, red, green, blue, alpha);
   SpyJassLog("[SetTextTagColor] OK [t:%s, red:%s, green:%s, blue:%s, alpha:%s]\n",GetStrID(t).c_str( ), GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), GetStrID(alpha).c_str( ));
}
void _cdecl SetTextTagFadepoint_my(HTEXTTAG t, float *fadepoint)
{
   funcname1 = "SetTextTagFadepoint";
   SpyJassLog(" Exec:SetTextTagFadepoint...");
   SetTextTagFadepoint_ptr(t, fadepoint);
   SpyJassLog("[SetTextTagFadepoint] OK [t:%s, fadepoint:%.4g]\n",GetStrID(t).c_str( ), (*fadepoint));
}
void _cdecl SetTextTagLifespan_my(HTEXTTAG t, float *lifespan)
{
   funcname1 = "SetTextTagLifespan";
   SpyJassLog(" Exec:SetTextTagLifespan...");
   SetTextTagLifespan_ptr(t, lifespan);
   SpyJassLog("[SetTextTagLifespan] OK [t:%s, lifespan:%.4g]\n",GetStrID(t).c_str( ), (*lifespan));
}
void _cdecl SetTextTagPermanent_my(HTEXTTAG t, BOOL flag)
{
   funcname1 = "SetTextTagPermanent";
   SpyJassLog(" Exec:SetTextTagPermanent...");
   SetTextTagPermanent_ptr(t, flag);
   SpyJassLog("[SetTextTagPermanent] OK [t:%s, flag:%s]\n",GetStrID(t).c_str( ), BoolToStr(flag));
}
void _cdecl SetTextTagPos_my(HTEXTTAG t, float *x, float *y, float *heightOffset)
{
   funcname1 = "SetTextTagPos";
   SpyJassLog(" Exec:SetTextTagPos...");
   SetTextTagPos_ptr(t, x, y, heightOffset);
   SpyJassLog("[SetTextTagPos] OK [t:%s, x:%.4g, y:%.4g, heightOffset:%.4g]\n",GetStrID(t).c_str( ), (*x), (*y), (*heightOffset));
}
void _cdecl SetTextTagPosUnit_my(HTEXTTAG t, HUNIT unit, float *heightOffset)
{
   funcname1 = "SetTextTagPosUnit";
   SpyJassLog(" Exec:SetTextTagPosUnit...");
   SetTextTagPosUnit_ptr(t, unit, heightOffset);
   SpyJassLog("[SetTextTagPosUnit] OK [t:%s, unit:%s, heightOffset:%.4g]\n",GetStrID(t).c_str( ), GetUnitHID(unit).c_str( ), (*heightOffset));
}
void _cdecl SetTextTagSuspended_my(HTEXTTAG t, BOOL flag)
{
   funcname1 = "SetTextTagSuspended";
   SpyJassLog(" Exec:SetTextTagSuspended...");
   SetTextTagSuspended_ptr(t, flag);
   SpyJassLog("[SetTextTagSuspended] OK [t:%s, flag:%s]\n",GetStrID(t).c_str( ), BoolToStr(flag));
}
void _cdecl SetTextTagText_my(HTEXTTAG t, CJassString s, float *height)
{
   funcname1 = "SetTextTagText";
   SpyJassLog(" Exec:SetTextTagText...");
   SetTextTagText_ptr(t, s, height);
   SpyJassLog("[SetTextTagText] OK [t:%s, s:%s, height:%.4g]\n",GetStrID(t).c_str( ), ReadJassStringNormal(s), (*height));
}
void _cdecl SetTextTagVelocity_my(HTEXTTAG t, float *xvel, float *yvel)
{
   funcname1 = "SetTextTagVelocity";
   SpyJassLog(" Exec:SetTextTagVelocity...");
   SetTextTagVelocity_ptr(t, xvel, yvel);
   SpyJassLog("[SetTextTagVelocity] OK [t:%s, xvel:%.4g, yvel:%.4g]\n",GetStrID(t).c_str( ), (*xvel), (*yvel));
}
void _cdecl SetTextTagVisibility_my(HTEXTTAG t, BOOL flag)
{
   funcname1 = "SetTextTagVisibility";
   SpyJassLog(" Exec:SetTextTagVisibility...");
   SetTextTagVisibility_ptr(t, flag);
   SpyJassLog("[SetTextTagVisibility] OK [t:%s, flag:%s]\n",GetStrID(t).c_str( ), BoolToStr(flag));
}
void _cdecl SetThematicMusicPlayPosition_my(int millisecs)
{
   funcname1 = "SetThematicMusicPlayPosition";
   SpyJassLog(" Exec:SetThematicMusicPlayPosition...");
   SetThematicMusicPlayPosition_ptr(millisecs);
   SpyJassLog("[SetThematicMusicPlayPosition] OK [millisecs:%s]\n",GetStrID(millisecs).c_str( ));
}
void _cdecl SetTimeOfDayScale_my(float *r)
{
   funcname1 = "SetTimeOfDayScale";
   SpyJassLog(" Exec:SetTimeOfDayScale...");
   SetTimeOfDayScale_ptr(r);
   SpyJassLog("[SetTimeOfDayScale] OK [r:%.4g]\n",(*r));
}
void _cdecl SetTutorialCleared_my(BOOL cleared)
{
   funcname1 = "SetTutorialCleared";
   SpyJassLog(" Exec:SetTutorialCleared...");
   SetTutorialCleared_ptr(cleared);
   SpyJassLog("[SetTutorialCleared] OK [cleared:%s]\n",BoolToStr(cleared));
}
void _cdecl SetUbersplatRender_my(HUBERSPLAT Splat, BOOL flag)
{
   funcname1 = "SetUbersplatRender";
   SpyJassLog(" Exec:SetUbersplatRender...");
   SetUbersplatRender_ptr(Splat, flag);
   SpyJassLog("[SetUbersplatRender] OK [Splat:%s, flag:%s]\n",GetStrID(Splat).c_str( ), BoolToStr(flag));
}
void _cdecl SetUbersplatRenderAlways_my(HUBERSPLAT Splat, BOOL flag)
{
   funcname1 = "SetUbersplatRenderAlways";
   SpyJassLog(" Exec:SetUbersplatRenderAlways...");
   SetUbersplatRenderAlways_ptr(Splat, flag);
   SpyJassLog("[SetUbersplatRenderAlways] OK [Splat:%s, flag:%s]\n",GetStrID(Splat).c_str( ), BoolToStr(flag));
}
int _cdecl SetUnitAbilityLevel_my(HUNIT unit, int abilcode, int level)
{
   funcname1 = "SetUnitAbilityLevel";
   SpyJassLog(" Exec:SetUnitAbilityLevel[unit:%s, abilcode:%s, level:%s]...",GetUnitHID(unit).c_str( ), GetStrID(abilcode).c_str( ), GetStrID(level).c_str( ));
   int returnvalue; 
   returnvalue = SetUnitAbilityLevel_ptr(unit, abilcode, level);
   SpyJassLog("[SetUnitAbilityLevel] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl SetUnitAcquireRange_my(HUNIT unit, float *newAcquireRange)
{
   funcname1 = "SetUnitAcquireRange";
   SpyJassLog(" Exec:SetUnitAcquireRange...");
   SetUnitAcquireRange_ptr(unit, newAcquireRange);
   SpyJassLog("[SetUnitAcquireRange] OK [unit:%s, newAcquireRange:%.4g]\n",GetUnitHID(unit).c_str( ), (*newAcquireRange));
}
void _cdecl SetUnitAnimation_my(HUNIT unit, CJassString Animation)
{
   funcname1 = "SetUnitAnimation";
   SpyJassLog(" Exec:SetUnitAnimation...");
   SetUnitAnimation_ptr(unit, Animation);
   SpyJassLog("[SetUnitAnimation] OK [unit:%s, Animation:%s]\n",GetUnitHID(unit).c_str( ), ReadJassStringNormal(Animation));
}
void _cdecl SetUnitAnimationByIndex_my(HUNIT unit, int Animation)
{
   funcname1 = "SetUnitAnimationByIndex";
   SpyJassLog(" Exec:SetUnitAnimationByIndex...");
   SetUnitAnimationByIndex_ptr(unit, Animation);
   SpyJassLog("[SetUnitAnimationByIndex] OK [unit:%s, Animation:%s]\n",GetUnitHID(unit).c_str( ), GetStrID(Animation).c_str( ));
}
void _cdecl SetUnitAnimationWithRarity_my(HUNIT unit, CJassString Animation, HRARITYCONTROL rarity)
{
   funcname1 = "SetUnitAnimationWithRarity";
   SpyJassLog(" Exec:SetUnitAnimationWithRarity...");
   SetUnitAnimationWithRarity_ptr(unit, Animation, rarity);
   SpyJassLog("[SetUnitAnimationWithRarity] OK [unit:%s, Animation:%s, rarity:%s]\n",GetUnitHID(unit).c_str( ), ReadJassStringNormal(Animation), GetStrID(rarity).c_str( ));
}
void _cdecl SetUnitBlendTime_my(HUNIT unit, float *blendTime)
{
   funcname1 = "SetUnitBlendTime";
   SpyJassLog(" Exec:SetUnitBlendTime...");
   SetUnitBlendTime_ptr(unit, blendTime);
   SpyJassLog("[SetUnitBlendTime] OK [unit:%s, blendTime:%.4g]\n",GetUnitHID(unit).c_str( ), (*blendTime));
}
void _cdecl SetUnitColor_my(HUNIT unit, HPLAYERCOLOR Color)
{
   funcname1 = "SetUnitColor";
   SpyJassLog(" Exec:SetUnitColor...");
   SetUnitColor_ptr(unit, Color);
   SpyJassLog("[SetUnitColor] OK [unit:%s, Color:%s]\n",GetUnitHID(unit).c_str( ), GetStrID(Color).c_str( ));
}
void _cdecl SetUnitCreepGuard_my(HUNIT unit, BOOL creepGuard)
{
   funcname1 = "SetUnitCreepGuard";
   SpyJassLog(" Exec:SetUnitCreepGuard...");
   SetUnitCreepGuard_ptr(unit, creepGuard);
   SpyJassLog("[SetUnitCreepGuard] OK [unit:%s, creepGuard:%s]\n",GetUnitHID(unit).c_str( ), BoolToStr(creepGuard));
}
void _cdecl SetUnitExploded_my(HUNIT unit, BOOL exploded)
{
   funcname1 = "SetUnitExploded";
   SpyJassLog(" Exec:SetUnitExploded...");
   SetUnitExploded_ptr(unit, exploded);
   SpyJassLog("[SetUnitExploded] OK [unit:%s, exploded:%s]\n",GetUnitHID(unit).c_str( ), BoolToStr(exploded));
}
void _cdecl SetUnitFacing_my(HUNIT unit, float *facingAngle)
{
   funcname1 = "SetUnitFacing";
   SpyJassLog(" Exec:SetUnitFacing...");
   SetUnitFacing_ptr(unit, facingAngle);
   SpyJassLog("[SetUnitFacing] OK [unit:%s, facingAngle:%.4g]\n",GetUnitHID(unit).c_str( ), (*facingAngle));
}
void _cdecl SetUnitFacingTimed_my(HUNIT unit, float *facingAngle, float *duration)
{
   funcname1 = "SetUnitFacingTimed";
   SpyJassLog(" Exec:SetUnitFacingTimed...");
   SetUnitFacingTimed_ptr(unit, facingAngle, duration);
   SpyJassLog("[SetUnitFacingTimed] OK [unit:%s, facingAngle:%.4g, duration:%.4g]\n",GetUnitHID(unit).c_str( ), (*facingAngle), (*duration));
}
void _cdecl SetUnitFlyHeight_my(HUNIT unit, float *newHeight, float *rate)
{
   funcname1 = "SetUnitFlyHeight";
   SpyJassLog(" Exec:SetUnitFlyHeight...");
   SetUnitFlyHeight_ptr(unit, newHeight, rate);
   SpyJassLog("[SetUnitFlyHeight] OK [unit:%s, newHeight:%.4g, rate:%.4g]\n",GetUnitHID(unit).c_str( ), (*newHeight), (*rate));
}
void _cdecl SetUnitFog_my(float *a, float *b, float *c, float *d, float *e)
{
   funcname1 = "SetUnitFog";
   SpyJassLog(" Exec:SetUnitFog...");
   SetUnitFog_ptr(a, b, c, d, e);
   SpyJassLog("[SetUnitFog] OK [a:%.4g, b:%.4g, c:%.4g, d:%.4g, e:%.4g]\n",(*a), (*b), (*c), (*d), (*e));
}
void _cdecl SetUnitInvulnerable_my(HUNIT unit, BOOL flag)
{
   funcname1 = "SetUnitInvulnerable";
   SpyJassLog(" Exec:SetUnitInvulnerable...");
   SetUnitInvulnerable_ptr(unit, flag);
   SpyJassLog("[SetUnitInvulnerable] OK [unit:%s, flag:%s]\n",GetUnitHID(unit).c_str( ), BoolToStr(flag));
}
void _cdecl SetUnitLookAt_my(HUNIT unit, CJassString Bone, HUNIT lookAtTarget, float *offsetX, float *offsetY, float *offsetZ)
{
   funcname1 = "SetUnitLookAt";
   SpyJassLog(" Exec:SetUnitLookAt...");
   SetUnitLookAt_ptr(unit, Bone, lookAtTarget, offsetX, offsetY, offsetZ);
   SpyJassLog("[SetUnitLookAt] OK [unit:%s, Bone:%s, lookAtTarget:%s, offsetX:%.4g, offsetY:%.4g, offsetZ:%.4g]\n",GetUnitHID(unit).c_str( ), ReadJassStringNormal(Bone), GetUnitHID(lookAtTarget).c_str( ), (*offsetX), (*offsetY), (*offsetZ));
}
void _cdecl SetUnitMoveSpeed_my(HUNIT unit, float *newSpeed)
{
   funcname1 = "SetUnitMoveSpeed";
   SpyJassLog(" Exec:SetUnitMoveSpeed...");
   SetUnitMoveSpeed_ptr(unit, newSpeed);
   SpyJassLog("[SetUnitMoveSpeed] OK [unit:%s, newSpeed:%.4g]\n",GetUnitHID(unit).c_str( ), (*newSpeed));
}
void _cdecl SetUnitOwner_my(HUNIT unit, HPLAYER player, BOOL changeColor)
{
   funcname1 = "SetUnitOwner";
   SpyJassLog(" Exec:SetUnitOwner...");
   SetUnitOwner_ptr(unit, player, changeColor);
   SpyJassLog("[SetUnitOwner] OK [unit:%s, player:%i, changeColor:%s]\n",GetUnitHID(unit).c_str( ), GetPlayerId_ptr(player), BoolToStr(changeColor));
}
void _cdecl SetUnitPathing_my(HUNIT unit, BOOL flag)
{
   funcname1 = "SetUnitPathing";
   SpyJassLog(" Exec:SetUnitPathing...");
   SetUnitPathing_ptr(unit, flag);
   SpyJassLog("[SetUnitPathing] OK [unit:%s, flag:%s]\n",GetUnitHID(unit).c_str( ), BoolToStr(flag));
}
void _cdecl SetUnitPosition_my(HUNIT unit, float *newX, float *newY)
{
   funcname1 = "SetUnitPosition";
   SpyJassLog(" Exec:SetUnitPosition...");
   SetUnitPosition_ptr(unit, newX, newY);
   SpyJassLog("[SetUnitPosition] OK [unit:%s, newX:%.4g, newY:%.4g]\n",GetUnitHID(unit).c_str( ), (*newX), (*newY));
}
void _cdecl SetUnitPositionLoc_my(HUNIT unit, HLOCATION Location)
{
   funcname1 = "SetUnitPositionLoc";
   SpyJassLog(" Exec:SetUnitPositionLoc...");
   SetUnitPositionLoc_ptr(unit, Location);
   SpyJassLog("[SetUnitPositionLoc] OK [unit:%s, Location:%s]\n",GetUnitHID(unit).c_str( ), GetStrID(Location).c_str( ));
}
void _cdecl SetUnitPropWindow_my(HUNIT unit, float *newPropWindowAngle)
{
   funcname1 = "SetUnitPropWindow";
   SpyJassLog(" Exec:SetUnitPropWindow...");
   SetUnitPropWindow_ptr(unit, newPropWindowAngle);
   SpyJassLog("[SetUnitPropWindow] OK [unit:%s, newPropWindowAngle:%.4g]\n",GetUnitHID(unit).c_str( ), (*newPropWindowAngle));
}
void _cdecl SetUnitRescuable_my(HUNIT unit, HPLAYER byWhichPlayer, BOOL flag)
{
   funcname1 = "SetUnitRescuable";
   SpyJassLog(" Exec:SetUnitRescuable...");
   SetUnitRescuable_ptr(unit, byWhichPlayer, flag);
   SpyJassLog("[SetUnitRescuable] OK [unit:%s, byWhichPlayer:%i, flag:%s]\n",GetUnitHID(unit).c_str( ), GetPlayerId_ptr(byWhichPlayer), BoolToStr(flag));
}
void _cdecl SetUnitRescueRange_my(HUNIT unit, float *range)
{
   funcname1 = "SetUnitRescueRange";
   SpyJassLog(" Exec:SetUnitRescueRange...");
   SetUnitRescueRange_ptr(unit, range);
   SpyJassLog("[SetUnitRescueRange] OK [unit:%s, range:%.4g]\n",GetUnitHID(unit).c_str( ), (*range));
}
void _cdecl SetUnitScale_my(HUNIT unit, float *scaleX, float *scaleY, float *scaleZ)
{
   funcname1 = "SetUnitScale";
   SpyJassLog(" Exec:SetUnitScale...");
   SetUnitScale_ptr(unit, scaleX, scaleY, scaleZ);
   SpyJassLog("[SetUnitScale] OK [unit:%s, scaleX:%.4g, scaleY:%.4g, scaleZ:%.4g]\n",GetUnitHID(unit).c_str( ), (*scaleX), (*scaleY), (*scaleZ));
}
void _cdecl SetUnitState_my(HUNIT unit, HUNITSTATE UnitState, float *newVal)
{
   funcname1 = "SetUnitState";
   SpyJassLog(" Exec:SetUnitState...");
   SetUnitState_ptr(unit, UnitState, newVal);
   SpyJassLog("[SetUnitState] OK [unit:%s, UnitState:%s, newVal:%.4g]\n",GetUnitHID(unit).c_str( ), GetStrID(UnitState).c_str( ), (*newVal));
}
void _cdecl SetUnitTimeScale_my(HUNIT unit, float *timeScale)
{
   funcname1 = "SetUnitTimeScale";
   SpyJassLog(" Exec:SetUnitTimeScale...");
   SetUnitTimeScale_ptr(unit, timeScale);
   SpyJassLog("[SetUnitTimeScale] OK [unit:%s, timeScale:%.4g]\n",GetUnitHID(unit).c_str( ), (*timeScale));
}
void _cdecl SetUnitTurnSpeed_my(HUNIT unit, float *newTurnSpeed)
{
   funcname1 = "SetUnitTurnSpeed";
   SpyJassLog(" Exec:SetUnitTurnSpeed...");
   SetUnitTurnSpeed_ptr(unit, newTurnSpeed);
   SpyJassLog("[SetUnitTurnSpeed] OK [unit:%s, newTurnSpeed:%.4g]\n",GetUnitHID(unit).c_str( ), (*newTurnSpeed));
}
void _cdecl SetUnitTypeSlots_my(HUNIT unit, int slots)
{
   funcname1 = "SetUnitTypeSlots";
   SpyJassLog(" Exec:SetUnitTypeSlots...");
   SetUnitTypeSlots_ptr(unit, slots);
   SpyJassLog("[SetUnitTypeSlots] OK [unit:%s, slots:%s]\n",GetUnitHID(unit).c_str( ), GetStrID(slots).c_str( ));
}
void _cdecl SetUnitUseFood_my(HUNIT unit, BOOL useFood)
{
   funcname1 = "SetUnitUseFood";
   SpyJassLog(" Exec:SetUnitUseFood...");
   SetUnitUseFood_ptr(unit, useFood);
   SpyJassLog("[SetUnitUseFood] OK [unit:%s, useFood:%s]\n",GetUnitHID(unit).c_str( ), BoolToStr(useFood));
}
void _cdecl SetUnitUserData_my(HUNIT unit, int data)
{
   funcname1 = "SetUnitUserData";
   SpyJassLog(" Exec:SetUnitUserData...");
   SetUnitUserData_ptr(unit, data);
   SpyJassLog("[SetUnitUserData] OK [unit:%s, data:%s]\n",GetUnitHID(unit).c_str( ), GetStrID(data).c_str( ));
}
void _cdecl SetUnitVertexColor_my(HUNIT unit, int red, int green, int blue, int alpha)
{
   funcname1 = "SetUnitVertexColor";
   SpyJassLog(" Exec:SetUnitVertexColor...");
   SetUnitVertexColor_ptr(unit, red, green, blue, alpha);
   SpyJassLog("[SetUnitVertexColor] OK [unit:%s, red:%s, green:%s, blue:%s, alpha:%s]\n",GetUnitHID(unit).c_str( ), GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), GetStrID(alpha).c_str( ));
}
void _cdecl SetUnitX_my(HUNIT unit, float *newX)
{
   funcname1 = "SetUnitX";
   SpyJassLog(" Exec:SetUnitX...");
   SetUnitX_ptr(unit, newX);
   SpyJassLog("[SetUnitX] OK [unit:%s, newX:%.4g]\n",GetUnitHID(unit).c_str( ), (*newX));
}
void _cdecl SetUnitY_my(HUNIT unit, float *newY)
{
   funcname1 = "SetUnitY";
   SpyJassLog(" Exec:SetUnitY...");
   SetUnitY_ptr(unit, newY);
   SpyJassLog("[SetUnitY] OK [unit:%s, newY:%.4g]\n",GetUnitHID(unit).c_str( ), (*newY));
}
void _cdecl SetUnitsFlee_my(BOOL arg1)
{
   funcname1 = "SetUnitsFlee";
   SpyJassLog(" Exec:SetUnitsFlee...");
   SetUnitsFlee_ptr(arg1);
   SpyJassLog("[SetUnitsFlee] OK [arg1:%s]\n",BoolToStr(arg1));
}
BOOL _cdecl SetUpgrade_my(int arg1)
{
   funcname1 = "SetUpgrade";
   SpyJassLog(" Exec:SetUpgrade[arg1:%s]...",GetStrID(arg1).c_str( ));
   BOOL returnvalue; 
   returnvalue = SetUpgrade_ptr(arg1);
   SpyJassLog("[SetUpgrade] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl SetWatchMegaTargets_my(BOOL arg1)
{
   funcname1 = "SetWatchMegaTargets";
   SpyJassLog(" Exec:SetWatchMegaTargets...");
   SetWatchMegaTargets_ptr(arg1);
   SpyJassLog("[SetWatchMegaTargets] OK [arg1:%s]\n",BoolToStr(arg1));
}
void _cdecl SetWaterBaseColor_my(int red, int green, int blue, int alpha)
{
   funcname1 = "SetWaterBaseColor";
   SpyJassLog(" Exec:SetWaterBaseColor...");
   SetWaterBaseColor_ptr(red, green, blue, alpha);
   SpyJassLog("[SetWaterBaseColor] OK [red:%s, green:%s, blue:%s, alpha:%s]\n",GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), GetStrID(alpha).c_str( ));
}
void _cdecl SetWaterDeforms_my(BOOL val)
{
   funcname1 = "SetWaterDeforms";
   SpyJassLog(" Exec:SetWaterDeforms...");
   SetWaterDeforms_ptr(val);
   SpyJassLog("[SetWaterDeforms] OK [val:%s]\n",BoolToStr(val));
}
void _cdecl SetWidgetLife_my(HWIDGET widget, float *newLife)
{
   funcname1 = "SetWidgetLife";
   SpyJassLog(" Exec:SetWidgetLife...");
   SetWidgetLife_ptr(widget, newLife);
   SpyJassLog("[SetWidgetLife] OK [widget:%s, newLife:%.4g]\n",GetStrID(widget).c_str( ), (*newLife));
}
void _cdecl ShiftTownSpot_my(float *arg1, float *arg2)
{
   funcname1 = "ShiftTownSpot";
   SpyJassLog(" Exec:ShiftTownSpot...");
   ShiftTownSpot_ptr(arg1, arg2);
   SpyJassLog("[ShiftTownSpot] OK [arg1:%.4g, arg2:%.4g]\n",(*arg1), (*arg2));
}
void _cdecl ShowDestructable_my(HDESTRUCTABLE d, BOOL flag)
{
   funcname1 = "ShowDestructable";
   SpyJassLog(" Exec:ShowDestructable...");
   ShowDestructable_ptr(d, flag);
   SpyJassLog("[ShowDestructable] OK [d:%s, flag:%s]\n",GetStrID(d).c_str( ), BoolToStr(flag));
}
void _cdecl ShowImage_my(HIMAGE Image, BOOL flag)
{
   funcname1 = "ShowImage";
   SpyJassLog(" Exec:ShowImage...");
   ShowImage_ptr(Image, flag);
   SpyJassLog("[ShowImage] OK [Image:%s, flag:%s]\n",GetStrID(Image).c_str( ), BoolToStr(flag));
}
void _cdecl ShowInterface_my(BOOL flag, float *fadeDuration)
{
   funcname1 = "ShowInterface";
   SpyJassLog(" Exec:ShowInterface...");
   ShowInterface_ptr(flag, fadeDuration);
   SpyJassLog("[ShowInterface] OK [flag:%s, fadeDuration:%.4g]\n",BoolToStr(flag), (*fadeDuration));
}
void _cdecl ShowUbersplat_my(HUBERSPLAT Splat, BOOL flag)
{
   funcname1 = "ShowUbersplat";
   SpyJassLog(" Exec:ShowUbersplat...");
   ShowUbersplat_ptr(Splat, flag);
   SpyJassLog("[ShowUbersplat] OK [Splat:%s, flag:%s]\n",GetStrID(Splat).c_str( ), BoolToStr(flag));
}
void _cdecl ShowUnit_my(HUNIT unit, BOOL show)
{
   funcname1 = "ShowUnit";
   SpyJassLog(" Exec:ShowUnit...");
   ShowUnit_ptr(unit, show);
   SpyJassLog("[ShowUnit] OK [unit:%s, show:%s]\n",GetUnitHID(unit).c_str( ), BoolToStr(show));
}
DWFP _cdecl Sin_my(float *radians)
{
   funcname1 = "Sin";
   SpyJassLog(" Exec:Sin[radians:%.4g]...",(*radians));
   DWFP returnvalue; 
   returnvalue = Sin_ptr(radians);
   SpyJassLog("[Sin] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
void _cdecl Sleep_my(float *arg1)
{
   funcname1 = "Sleep";
   SpyJassLog(" Exec:Sleep...");
   Sleep_ptr(arg1);
   SpyJassLog("[Sleep] OK [arg1:%.4g]\n",(*arg1));
}
DWFP _cdecl SquareRoot_my(float *x)
{
   funcname1 = "SquareRoot";
   SpyJassLog(" Exec:SquareRoot[x:%.4g]...",(*x));
   DWFP returnvalue; 
   returnvalue = SquareRoot_ptr(x);
   SpyJassLog("[SquareRoot] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
void _cdecl StartCampaignAI_my(HPLAYER num, CJassString script)
{
   funcname1 = "StartCampaignAI";
   SpyJassLog(" Exec:StartCampaignAI...");
   StartCampaignAI_ptr(num, script);
   SpyJassLog("[StartCampaignAI] OK [num:%i, script:%s]\n",GetPlayerId_ptr(num), ReadJassStringNormal(script));
}
void _cdecl StartGetEnemyBase_my()
{
   funcname1 = "StartGetEnemyBase";
   SpyJassLog(" Exec:StartGetEnemyBase...");
   StartGetEnemyBase_ptr();
   SpyJassLog("[StartGetEnemyBase] OK []\n");
}
void _cdecl StartMeleeAI_my(HPLAYER num, CJassString script)
{
   funcname1 = "StartMeleeAI";
   SpyJassLog(" Exec:StartMeleeAI...");
   StartMeleeAI_ptr(num, script);
   SpyJassLog("[StartMeleeAI] OK [num:%i, script:%s]\n",GetPlayerId_ptr(num), ReadJassStringNormal(script));
}
void _cdecl StartSound_my(HSOUND soundHandle)
{
   funcname1 = "StartSound";
   SpyJassLog(" Exec:StartSound...");
   StartSound_ptr(soundHandle);
   SpyJassLog("[StartSound] OK [soundHandle:%s]\n",GetStrID(soundHandle).c_str( ));
}
void _cdecl StartThread_my(CODE arg1)
{
   funcname1 = "StartThread";
   SpyJassLog(" Exec:StartThread...");
   StartThread_ptr(arg1);
   SpyJassLog("[StartThread] OK [arg1:%s]\n",GetStrID(arg1).c_str( ));
}
void _cdecl StopCamera_my()
{
   funcname1 = "StopCamera";
   SpyJassLog(" Exec:StopCamera...");
   StopCamera_ptr();
   SpyJassLog("[StopCamera] OK []\n");
}
void _cdecl StopGathering_my()
{
   funcname1 = "StopGathering";
   SpyJassLog(" Exec:StopGathering...");
   StopGathering_ptr();
   SpyJassLog("[StopGathering] OK []\n");
}
void _cdecl StopMusic_my(BOOL fadeOut)
{
   funcname1 = "StopMusic";
   SpyJassLog(" Exec:StopMusic...");
   StopMusic_ptr(fadeOut);
   SpyJassLog("[StopMusic] OK [fadeOut:%s]\n",BoolToStr(fadeOut));
}
void _cdecl StopSound_my(HSOUND soundHandle, BOOL killWhenDone, BOOL fadeOut)
{
   funcname1 = "StopSound";
   SpyJassLog(" Exec:StopSound...");
   StopSound_ptr(soundHandle, killWhenDone, fadeOut);
   SpyJassLog("[StopSound] OK [soundHandle:%s, killWhenDone:%s, fadeOut:%s]\n",GetStrID(soundHandle).c_str( ), BoolToStr(killWhenDone), BoolToStr(fadeOut));
}
void _cdecl StoreBoolean_my(HGAMECACHE cache, CJassString missionKey, CJassString key, BOOL value)
{
   funcname1 = "StoreBoolean";
   SpyJassLog(" Exec:StoreBoolean...");
   StoreBoolean_ptr(cache, missionKey, key, value);
   SpyJassLog("[StoreBoolean] OK [cache:%s, missionKey:%s, key:%s, value:%s]\n",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key), BoolToStr(value));
}
void _cdecl StoreInteger_my(HGAMECACHE cache, CJassString missionKey, CJassString key, int value)
{
   funcname1 = "StoreInteger";
   SpyJassLog(" Exec:StoreInteger...");
   StoreInteger_ptr(cache, missionKey, key, value);
   SpyJassLog("[StoreInteger] OK [cache:%s, missionKey:%s, key:%s, value:%s]\n",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key), GetStrID(value).c_str( ));
}
void _cdecl StoreReal_my(HGAMECACHE cache, CJassString missionKey, CJassString key, float *value)
{
   funcname1 = "StoreReal";
   SpyJassLog(" Exec:StoreReal...");
   StoreReal_ptr(cache, missionKey, key, value);
   SpyJassLog("[StoreReal] OK [cache:%s, missionKey:%s, key:%s, value:%.4g]\n",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key), (*value));
}
BOOL _cdecl StoreString_my(HGAMECACHE cache, CJassString missionKey, CJassString key, CJassString value)
{
   funcname1 = "StoreString";
   SpyJassLog(" Exec:StoreString[cache:%s, missionKey:%s, key:%s, value:%s]...",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key), ReadJassStringNormal(value));
   BOOL returnvalue; 
   returnvalue = StoreString_ptr(cache, missionKey, key, value);
   SpyJassLog("[StoreString] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl StoreUnit_my(HGAMECACHE cache, CJassString missionKey, CJassString key, HUNIT unit)
{
   funcname1 = "StoreUnit";
   SpyJassLog(" Exec:StoreUnit[cache:%s, missionKey:%s, key:%s, unit:%s]...",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key), GetUnitHID(unit).c_str( ));
   BOOL returnvalue; 
   returnvalue = StoreUnit_ptr(cache, missionKey, key, unit);
   SpyJassLog("[StoreUnit] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
CJassStringSID _cdecl StringCase_my(CJassString source, BOOL upper)
{
   funcname1 = "StringCase";
   SpyJassLog(" Exec:StringCase[source:%s, upper:%s]...",ReadJassStringNormal(source), BoolToStr(upper));
   CJassStringSID returnvalue; 
   returnvalue = StringCase_ptr(source, upper);
   SpyJassLog("[StringCase] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
int _cdecl StringHash_my(CJassString s)
{
   funcname1 = "StringHash";
   SpyJassLog(" Exec:StringHash[s:%s]...",ReadJassStringNormal(s));
   int returnvalue; 
   returnvalue = StringHash_ptr(s);
   SpyJassLog("[StringHash] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
int _cdecl StringLength_my(CJassString s)
{
   funcname1 = "StringLength";
   SpyJassLog(" Exec:StringLength[s:%s]...",ReadJassStringNormal(s));
   int returnvalue; 
   returnvalue = StringLength_ptr(s);
   SpyJassLog("[StringLength] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
CJassStringSID _cdecl SubString_my(CJassString source, int start, int end)
{
   funcname1 = "SubString";
   SpyJassLog(" Exec:SubString[source:%s, start:%s, end:%s]...",ReadJassStringNormal(source), GetStrID(start).c_str( ), GetStrID(end).c_str( ));
   CJassStringSID returnvalue; 
   returnvalue = SubString_ptr(source, start, end);
   SpyJassLog("[SubString] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
BOOL _cdecl SuicidePlayer_my(HPLAYER arg1, BOOL arg2)
{
   funcname1 = "SuicidePlayer";
   SpyJassLog(" Exec:SuicidePlayer[arg1:%i, arg2:%s]...",GetPlayerId_ptr(arg1), BoolToStr(arg2));
   BOOL returnvalue; 
   returnvalue = SuicidePlayer_ptr(arg1, arg2);
   SpyJassLog("[SuicidePlayer] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl SuicidePlayerUnits_my(HPLAYER arg1, BOOL arg2)
{
   funcname1 = "SuicidePlayerUnits";
   SpyJassLog(" Exec:SuicidePlayerUnits[arg1:%i, arg2:%s]...",GetPlayerId_ptr(arg1), BoolToStr(arg2));
   BOOL returnvalue; 
   returnvalue = SuicidePlayerUnits_ptr(arg1, arg2);
   SpyJassLog("[SuicidePlayerUnits] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl SuicideUnit_my(int arg1, int arg2)
{
   funcname1 = "SuicideUnit";
   SpyJassLog(" Exec:SuicideUnit...");
   SuicideUnit_ptr(arg1, arg2);
   SpyJassLog("[SuicideUnit] OK [arg1:%s, arg2:%s]\n",GetStrID(arg1).c_str( ), GetStrID(arg2).c_str( ));
}
void _cdecl SuicideUnitEx_my(int arg1, int arg2, int arg3)
{
   funcname1 = "SuicideUnitEx";
   SpyJassLog(" Exec:SuicideUnitEx...");
   SuicideUnitEx_ptr(arg1, arg2, arg3);
   SpyJassLog("[SuicideUnitEx] OK [arg1:%s, arg2:%s, arg3:%s]\n",GetStrID(arg1).c_str( ), GetStrID(arg2).c_str( ), GetStrID(arg3).c_str( ));
}
void _cdecl SuspendHeroXP_my(HUNIT hero, BOOL flag)
{
   funcname1 = "SuspendHeroXP";
   SpyJassLog(" Exec:SuspendHeroXP...");
   SuspendHeroXP_ptr(hero, flag);
   SpyJassLog("[SuspendHeroXP] OK [hero:%s, flag:%s]\n",GetUnitHID(hero).c_str( ), BoolToStr(flag));
}
void _cdecl SuspendTimeOfDay_my(BOOL b)
{
   funcname1 = "SuspendTimeOfDay";
   SpyJassLog(" Exec:SuspendTimeOfDay...");
   SuspendTimeOfDay_ptr(b);
   SpyJassLog("[SuspendTimeOfDay] OK [b:%s]\n",BoolToStr(b));
}
void _cdecl SyncSelections_my()
{
   funcname1 = "SyncSelections";
   SpyJassLog(" Exec:SyncSelections...");
   SyncSelections_ptr();
   SpyJassLog("[SyncSelections] OK []\n");
}
void _cdecl SyncStoredBoolean_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "SyncStoredBoolean";
   SpyJassLog(" Exec:SyncStoredBoolean...");
   SyncStoredBoolean_ptr(cache, missionKey, key);
   SpyJassLog("[SyncStoredBoolean] OK [cache:%s, missionKey:%s, key:%s]\n",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
}
void _cdecl SyncStoredInteger_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "SyncStoredInteger";
   SpyJassLog(" Exec:SyncStoredInteger...");
   SyncStoredInteger_ptr(cache, missionKey, key);
   SpyJassLog("[SyncStoredInteger] OK [cache:%s, missionKey:%s, key:%s]\n",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
}
void _cdecl SyncStoredReal_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "SyncStoredReal";
   SpyJassLog(" Exec:SyncStoredReal...");
   SyncStoredReal_ptr(cache, missionKey, key);
   SpyJassLog("[SyncStoredReal] OK [cache:%s, missionKey:%s, key:%s]\n",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
}
void _cdecl SyncStoredString_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "SyncStoredString";
   SpyJassLog(" Exec:SyncStoredString...");
   SyncStoredString_ptr(cache, missionKey, key);
   SpyJassLog("[SyncStoredString] OK [cache:%s, missionKey:%s, key:%s]\n",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
}
void _cdecl SyncStoredUnit_my(HGAMECACHE cache, CJassString missionKey, CJassString key)
{
   funcname1 = "SyncStoredUnit";
   SpyJassLog(" Exec:SyncStoredUnit...");
   SyncStoredUnit_ptr(cache, missionKey, key);
   SpyJassLog("[SyncStoredUnit] OK [cache:%s, missionKey:%s, key:%s]\n",GetStrID(cache).c_str( ), ReadJassStringNormal(missionKey), ReadJassStringNormal(key));
}
DWFP _cdecl Tan_my(float *radians)
{
   funcname1 = "Tan";
   SpyJassLog(" Exec:Tan[radians:%.4g]...",(*radians));
   DWFP returnvalue; 
   returnvalue = Tan_ptr(radians);
   SpyJassLog("[Tan] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
void _cdecl TeleportCaptain_my(float *arg1, float *arg2)
{
   funcname1 = "TeleportCaptain";
   SpyJassLog(" Exec:TeleportCaptain...");
   TeleportCaptain_ptr(arg1, arg2);
   SpyJassLog("[TeleportCaptain] OK [arg1:%.4g, arg2:%.4g]\n",(*arg1), (*arg2));
}
HTERRAINDEFORMATION _cdecl TerrainDeformCrater_my(float *x, float *y, float *radius, float *depth, int duration, BOOL permanent)
{
   funcname1 = "TerrainDeformCrater";
   SpyJassLog(" Exec:TerrainDeformCrater[x:%.4g, y:%.4g, radius:%.4g, depth:%.4g, duration:%s, permanent:%s]...",(*x), (*y), (*radius), (*depth), GetStrID(duration).c_str( ), BoolToStr(permanent));
   HTERRAINDEFORMATION returnvalue; 
   returnvalue = TerrainDeformCrater_ptr(x, y, radius, depth, duration, permanent);
   SpyJassLog("[TerrainDeformCrater] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTERRAINDEFORMATION _cdecl TerrainDeformRandom_my(float *x, float *y, float *radius, float *minDelta, float *maxDelta, int duration, int updateInterval)
{
   funcname1 = "TerrainDeformRandom";
   SpyJassLog(" Exec:TerrainDeformRandom[x:%.4g, y:%.4g, radius:%.4g, minDelta:%.4g, maxDelta:%.4g, duration:%s, updateInterval:%s]...",(*x), (*y), (*radius), (*minDelta), (*maxDelta), GetStrID(duration).c_str( ), GetStrID(updateInterval).c_str( ));
   HTERRAINDEFORMATION returnvalue; 
   returnvalue = TerrainDeformRandom_ptr(x, y, radius, minDelta, maxDelta, duration, updateInterval);
   SpyJassLog("[TerrainDeformRandom] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTERRAINDEFORMATION _cdecl TerrainDeformRipple_my(float *x, float *y, float *radius, float *depth, int duration, int count, float *spaceWaves, float *timeWaves, float *radiusStartPct, BOOL limitNeg)
{
   funcname1 = "TerrainDeformRipple";
   SpyJassLog(" Exec:TerrainDeformRipple[x:%.4g, y:%.4g, radius:%.4g, depth:%.4g, duration:%s, count:%s, spaceWaves:%.4g, timeWaves:%.4g, radiusStartPct:%.4g, limitNeg:%s]...",(*x), (*y), (*radius), (*depth), GetStrID(duration).c_str( ), GetStrID(count).c_str( ), (*spaceWaves), (*timeWaves), (*radiusStartPct), BoolToStr(limitNeg));
   HTERRAINDEFORMATION returnvalue; 
   returnvalue = TerrainDeformRipple_ptr(x, y, radius, depth, duration, count, spaceWaves, timeWaves, radiusStartPct, limitNeg);
   SpyJassLog("[TerrainDeformRipple] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl TerrainDeformStop_my(HTERRAINDEFORMATION deformation, int duration)
{
   funcname1 = "TerrainDeformStop";
   SpyJassLog(" Exec:TerrainDeformStop...");
   TerrainDeformStop_ptr(deformation, duration);
   SpyJassLog("[TerrainDeformStop] OK [deformation:%s, duration:%s]\n",GetStrID(deformation).c_str( ), GetStrID(duration).c_str( ));
}
void _cdecl TerrainDeformStopAll_my()
{
   funcname1 = "TerrainDeformStopAll";
   SpyJassLog(" Exec:TerrainDeformStopAll...");
   TerrainDeformStopAll_ptr();
   SpyJassLog("[TerrainDeformStopAll] OK []\n");
}
HTERRAINDEFORMATION _cdecl TerrainDeformWave_my(float *x, float *y, float *dirX, float *dirY, float *distance, float *speed, float *radius, float *depth, int trailTime, int count)
{
   funcname1 = "TerrainDeformWave";
   SpyJassLog(" Exec:TerrainDeformWave[x:%.4g, y:%.4g, dirX:%.4g, dirY:%.4g, distance:%.4g, speed:%.4g, radius:%.4g, depth:%.4g, trailTime:%s, count:%s]...",(*x), (*y), (*dirX), (*dirY), (*distance), (*speed), (*radius), (*depth), GetStrID(trailTime).c_str( ), GetStrID(count).c_str( ));
   HTERRAINDEFORMATION returnvalue; 
   returnvalue = TerrainDeformWave_ptr(x, y, dirX, dirY, distance, speed, radius, depth, trailTime, count);
   SpyJassLog("[TerrainDeformWave] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl TimerDialogDisplay_my(HTIMERDIALOG Dialog, BOOL display)
{
   funcname1 = "TimerDialogDisplay";
   SpyJassLog(" Exec:TimerDialogDisplay...");
   TimerDialogDisplay_ptr(Dialog, display);
   SpyJassLog("[TimerDialogDisplay] OK [Dialog:%s, display:%s]\n",GetStrID(Dialog).c_str( ), BoolToStr(display));
}
void _cdecl TimerDialogSetRealTimeRemaining_my(HTIMERDIALOG Dialog, float *timeRemaining)
{
   funcname1 = "TimerDialogSetRealTimeRemaining";
   SpyJassLog(" Exec:TimerDialogSetRealTimeRemaining...");
   TimerDialogSetRealTimeRemaining_ptr(Dialog, timeRemaining);
   SpyJassLog("[TimerDialogSetRealTimeRemaining] OK [Dialog:%s, timeRemaining:%.4g]\n",GetStrID(Dialog).c_str( ), (*timeRemaining));
}
void _cdecl TimerDialogSetSpeed_my(HTIMERDIALOG Dialog, float *speedMultFactor)
{
   funcname1 = "TimerDialogSetSpeed";
   SpyJassLog(" Exec:TimerDialogSetSpeed...");
   TimerDialogSetSpeed_ptr(Dialog, speedMultFactor);
   SpyJassLog("[TimerDialogSetSpeed] OK [Dialog:%s, speedMultFactor:%.4g]\n",GetStrID(Dialog).c_str( ), (*speedMultFactor));
}
void _cdecl TimerDialogSetTimeColor_my(HTIMERDIALOG Dialog, int red, int green, int blue, int alpha)
{
   funcname1 = "TimerDialogSetTimeColor";
   SpyJassLog(" Exec:TimerDialogSetTimeColor...");
   TimerDialogSetTimeColor_ptr(Dialog, red, green, blue, alpha);
   SpyJassLog("[TimerDialogSetTimeColor] OK [Dialog:%s, red:%s, green:%s, blue:%s, alpha:%s]\n",GetStrID(Dialog).c_str( ), GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), GetStrID(alpha).c_str( ));
}
void _cdecl TimerDialogSetTitle_my(HTIMERDIALOG Dialog, CJassString title)
{
   funcname1 = "TimerDialogSetTitle";
   SpyJassLog(" Exec:TimerDialogSetTitle...");
   TimerDialogSetTitle_ptr(Dialog, title);
   SpyJassLog("[TimerDialogSetTitle] OK [Dialog:%s, title:%s]\n",GetStrID(Dialog).c_str( ), ReadJassStringNormal(title));
}
void _cdecl TimerDialogSetTitleColor_my(HTIMERDIALOG Dialog, int red, int green, int blue, int alpha)
{
   funcname1 = "TimerDialogSetTitleColor";
   SpyJassLog(" Exec:TimerDialogSetTitleColor...");
   TimerDialogSetTitleColor_ptr(Dialog, red, green, blue, alpha);
   SpyJassLog("[TimerDialogSetTitleColor] OK [Dialog:%s, red:%s, green:%s, blue:%s, alpha:%s]\n",GetStrID(Dialog).c_str( ), GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), GetStrID(alpha).c_str( ));
}
DWFP _cdecl TimerGetElapsed_my(HTIMER Timer)
{
   funcname1 = "TimerGetElapsed";
   SpyJassLog(" Exec:TimerGetElapsed[Timer:%s]...",GetStrID(Timer).c_str( ));
   DWFP returnvalue; 
   returnvalue = TimerGetElapsed_ptr(Timer);
   SpyJassLog("[TimerGetElapsed] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl TimerGetRemaining_my(HTIMER Timer)
{
   funcname1 = "TimerGetRemaining";
   SpyJassLog(" Exec:TimerGetRemaining[Timer:%s]...",GetStrID(Timer).c_str( ));
   DWFP returnvalue; 
   returnvalue = TimerGetRemaining_ptr(Timer);
   SpyJassLog("[TimerGetRemaining] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl TimerGetTimeout_my(HTIMER Timer)
{
   funcname1 = "TimerGetTimeout";
   SpyJassLog(" Exec:TimerGetTimeout[Timer:%s]...",GetStrID(Timer).c_str( ));
   DWFP returnvalue; 
   returnvalue = TimerGetTimeout_ptr(Timer);
   SpyJassLog("[TimerGetTimeout] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
void _cdecl TimerStart_my(HTIMER Timer, float *timeout, BOOL periodic, CODE handlerFunc)
{
   funcname1 = "TimerStart";
   SpyJassLog(" Exec:TimerStart...");
   TimerStart_ptr(Timer, timeout, periodic, handlerFunc);
   SpyJassLog("[TimerStart] OK [Timer:%s, timeout:%.4g, periodic:%s, handlerFunc:%s]\n",GetStrID(Timer).c_str( ), (*timeout), BoolToStr(periodic), GetStrID(handlerFunc).c_str( ));
}
BOOL _cdecl TownHasHall_my(int arg1)
{
   funcname1 = "TownHasHall";
   SpyJassLog(" Exec:TownHasHall[arg1:%s]...",GetStrID(arg1).c_str( ));
   BOOL returnvalue; 
   returnvalue = TownHasHall_ptr(arg1);
   SpyJassLog("[TownHasHall] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl TownHasMine_my(int arg1)
{
   funcname1 = "TownHasMine";
   SpyJassLog(" Exec:TownHasMine[arg1:%s]...",GetStrID(arg1).c_str( ));
   BOOL returnvalue; 
   returnvalue = TownHasMine_ptr(arg1);
   SpyJassLog("[TownHasMine] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl TownThreatened_my()
{
   funcname1 = "TownThreatened";
   SpyJassLog(" Exec:TownThreatened[]...");
   BOOL returnvalue; 
   returnvalue = TownThreatened_ptr();
   SpyJassLog("[TownThreatened] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
int _cdecl TownWithMine_my()
{
   funcname1 = "TownWithMine";
   SpyJassLog(" Exec:TownWithMine[]...");
   int returnvalue; 
   returnvalue = TownWithMine_ptr();
   SpyJassLog("[TownWithMine] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTRIGGERACTION _cdecl TriggerAddAction_my(HTRIGGER Trigger, CODE actionFunc)
{
   funcname1 = "TriggerAddAction";
   SpyJassLog(" Exec:TriggerAddAction[Trigger:%s, actionFunc:%s]...",GetStrID(Trigger).c_str( ), GetStrID(actionFunc).c_str( ));
   HTRIGGERACTION returnvalue; 
   returnvalue = TriggerAddAction_ptr(Trigger, actionFunc);
   SpyJassLog("[TriggerAddAction] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HTRIGGERCONDITION _cdecl TriggerAddCondition_my(HTRIGGER Trigger, HBOOLEXPR condition)
{
   funcname1 = "TriggerAddCondition";
   SpyJassLog(" Exec:TriggerAddCondition[Trigger:%s, condition:%s]...",GetStrID(Trigger).c_str( ), GetStrID(condition).c_str( ));
   HTRIGGERCONDITION returnvalue; 
   returnvalue = TriggerAddCondition_ptr(Trigger, condition);
   SpyJassLog("[TriggerAddCondition] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl TriggerClearActions_my(HTRIGGER Trigger)
{
   funcname1 = "TriggerClearActions";
   SpyJassLog(" Exec:TriggerClearActions...");
   TriggerClearActions_ptr(Trigger);
   SpyJassLog("[TriggerClearActions] OK [Trigger:%s]\n",GetStrID(Trigger).c_str( ));
}
void _cdecl TriggerClearConditions_my(HTRIGGER Trigger)
{
   funcname1 = "TriggerClearConditions";
   SpyJassLog(" Exec:TriggerClearConditions...");
   TriggerClearConditions_ptr(Trigger);
   SpyJassLog("[TriggerClearConditions] OK [Trigger:%s]\n",GetStrID(Trigger).c_str( ));
}
BOOL _cdecl TriggerEvaluate_my(HTRIGGER Trigger)
{
   funcname1 = "TriggerEvaluate";
   SpyJassLog(" Exec:TriggerEvaluate[Trigger:%s]...",GetStrID(Trigger).c_str( ));
   BOOL returnvalue; 
   returnvalue = TriggerEvaluate_ptr(Trigger);
   SpyJassLog("[TriggerEvaluate] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl TriggerExecute_my(HTRIGGER Trigger)
{
   funcname1 = "TriggerExecute";
   SpyJassLog(" Exec:TriggerExecute...");
   TriggerExecute_ptr(Trigger);
   SpyJassLog("[TriggerExecute] OK [Trigger:%s]\n",GetStrID(Trigger).c_str( ));
}
void _cdecl TriggerExecuteWait_my(HTRIGGER Trigger)
{
   funcname1 = "TriggerExecuteWait";
   SpyJassLog(" Exec:TriggerExecuteWait...");
   TriggerExecuteWait_ptr(Trigger);
   SpyJassLog("[TriggerExecuteWait] OK [Trigger:%s]\n",GetStrID(Trigger).c_str( ));
}
HEVENT _cdecl TriggerRegisterDeathEvent_my(HTRIGGER Trigger, HWIDGET widget)
{
   funcname1 = "TriggerRegisterDeathEvent";
   SpyJassLog(" Exec:TriggerRegisterDeathEvent[Trigger:%s, widget:%s]...",GetStrID(Trigger).c_str( ), GetStrID(widget).c_str( ));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterDeathEvent_ptr(Trigger, widget);
   SpyJassLog("[TriggerRegisterDeathEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterDialogButtonEvent_my(HTRIGGER Trigger, HBUTTON Button)
{
   funcname1 = "TriggerRegisterDialogButtonEvent";
   SpyJassLog(" Exec:TriggerRegisterDialogButtonEvent[Trigger:%s, Button:%s]...",GetStrID(Trigger).c_str( ), GetStrID(Button).c_str( ));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterDialogButtonEvent_ptr(Trigger, Button);
   SpyJassLog("[TriggerRegisterDialogButtonEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterDialogEvent_my(HTRIGGER Trigger, HDIALOG Dialog)
{
   funcname1 = "TriggerRegisterDialogEvent";
   SpyJassLog(" Exec:TriggerRegisterDialogEvent[Trigger:%s, Dialog:%s]...",GetStrID(Trigger).c_str( ), GetStrID(Dialog).c_str( ));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterDialogEvent_ptr(Trigger, Dialog);
   SpyJassLog("[TriggerRegisterDialogEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterEnterRegion_my(HTRIGGER Trigger, HREGION Region, HBOOLEXPR filter)
{
   funcname1 = "TriggerRegisterEnterRegion";
   SpyJassLog(" Exec:TriggerRegisterEnterRegion[Trigger:%s, Region:%s, filter:%s]...",GetStrID(Trigger).c_str( ), GetStrID(Region).c_str( ), GetStrID(filter).c_str( ));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterEnterRegion_ptr(Trigger, Region, filter);
   SpyJassLog("[TriggerRegisterEnterRegion] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterFilterUnitEvent_my(HTRIGGER Trigger, HUNIT unit, HUNITEVENT Event, HBOOLEXPR filter)
{
   funcname1 = "TriggerRegisterFilterUnitEvent";
   SpyJassLog(" Exec:TriggerRegisterFilterUnitEvent[Trigger:%s, unit:%s, Event:%s, filter:%s]...",GetStrID(Trigger).c_str( ), GetUnitHID(unit).c_str( ), GetStrID(Event).c_str( ), GetStrID(filter).c_str( ));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterFilterUnitEvent_ptr(Trigger, unit, Event, filter);
   SpyJassLog("[TriggerRegisterFilterUnitEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterGameEvent_my(HTRIGGER Trigger, HGAMEEVENT GameEvent)
{
   funcname1 = "TriggerRegisterGameEvent";
   SpyJassLog(" Exec:TriggerRegisterGameEvent[Trigger:%s, GameEvent:%s]...",GetStrID(Trigger).c_str( ), GetStrID(GameEvent).c_str( ));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterGameEvent_ptr(Trigger, GameEvent);
   SpyJassLog("[TriggerRegisterGameEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterGameStateEvent_my(HTRIGGER Trigger, HGAMESTATE State, HLIMITOP opcode, float *limitval)
{
   funcname1 = "TriggerRegisterGameStateEvent";
   SpyJassLog(" Exec:TriggerRegisterGameStateEvent[Trigger:%s, State:%s, opcode:%s, limitval:%.4g]...",GetStrID(Trigger).c_str( ), GetStrID(State).c_str( ), GetStrID(opcode).c_str( ), (*limitval));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterGameStateEvent_ptr(Trigger, State, opcode, limitval);
   SpyJassLog("[TriggerRegisterGameStateEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterLeaveRegion_my(HTRIGGER Trigger, HREGION Region, HBOOLEXPR filter)
{
   funcname1 = "TriggerRegisterLeaveRegion";
   SpyJassLog(" Exec:TriggerRegisterLeaveRegion[Trigger:%s, Region:%s, filter:%s]...",GetStrID(Trigger).c_str( ), GetStrID(Region).c_str( ), GetStrID(filter).c_str( ));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterLeaveRegion_ptr(Trigger, Region, filter);
   SpyJassLog("[TriggerRegisterLeaveRegion] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterPlayerAllianceChange_my(HTRIGGER Trigger, HPLAYER player, HALLIANCETYPE Alliance)
{
   funcname1 = "TriggerRegisterPlayerAllianceChange";
   SpyJassLog(" Exec:TriggerRegisterPlayerAllianceChange[Trigger:%s, player:%i, Alliance:%s]...",GetStrID(Trigger).c_str( ), GetPlayerId_ptr(player), GetStrID(Alliance).c_str( ));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterPlayerAllianceChange_ptr(Trigger, player, Alliance);
   SpyJassLog("[TriggerRegisterPlayerAllianceChange] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterPlayerChatEvent_my(HTRIGGER Trigger, HPLAYER player, CJassString chatMessageToDetect, BOOL exactMatchOnly)
{
   funcname1 = "TriggerRegisterPlayerChatEvent";
   SpyJassLog(" Exec:TriggerRegisterPlayerChatEvent[Trigger:%s, player:%i, chatMessageToDetect:%s, exactMatchOnly:%s]...",GetStrID(Trigger).c_str( ), GetPlayerId_ptr(player), ReadJassStringNormal(chatMessageToDetect), BoolToStr(exactMatchOnly));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterPlayerChatEvent_ptr(Trigger, player, chatMessageToDetect, exactMatchOnly);
   SpyJassLog("[TriggerRegisterPlayerChatEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterPlayerEvent_my(HTRIGGER Trigger, HPLAYER player, HPLAYEREVENT PlayerEvent)
{
   funcname1 = "TriggerRegisterPlayerEvent";
   SpyJassLog(" Exec:TriggerRegisterPlayerEvent[Trigger:%s, player:%i, PlayerEvent:%s]...",GetStrID(Trigger).c_str( ), GetPlayerId_ptr(player), GetStrID(PlayerEvent).c_str( ));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterPlayerEvent_ptr(Trigger, player, PlayerEvent);
   SpyJassLog("[TriggerRegisterPlayerEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterPlayerStateEvent_my(HTRIGGER Trigger, HPLAYER player, HPLAYERSTATE State, HLIMITOP opcode, float *limitval)
{
   funcname1 = "TriggerRegisterPlayerStateEvent";
   SpyJassLog(" Exec:TriggerRegisterPlayerStateEvent[Trigger:%s, player:%i, State:%s, opcode:%s, limitval:%.4g]...",GetStrID(Trigger).c_str( ), GetPlayerId_ptr(player), GetStrID(State).c_str( ), GetStrID(opcode).c_str( ), (*limitval));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterPlayerStateEvent_ptr(Trigger, player, State, opcode, limitval);
   SpyJassLog("[TriggerRegisterPlayerStateEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterPlayerUnitEvent_my(HTRIGGER Trigger, HPLAYER player, HPLAYERUNITEVENT PlayerUnitEvent, HBOOLEXPR filter)
{
   funcname1 = "TriggerRegisterPlayerUnitEvent";
   SpyJassLog(" Exec:TriggerRegisterPlayerUnitEvent[Trigger:%s, player:%i, PlayerUnitEvent:%s, filter:%s]...",GetStrID(Trigger).c_str( ), GetPlayerId_ptr(player), GetStrID(PlayerUnitEvent).c_str( ), GetStrID(filter).c_str( ));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterPlayerUnitEvent_ptr(Trigger, player, PlayerUnitEvent, filter);
   SpyJassLog("[TriggerRegisterPlayerUnitEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterTimerEvent_my(HTRIGGER Trigger, float *timeout, BOOL periodic)
{
   funcname1 = "TriggerRegisterTimerEvent";
   SpyJassLog(" Exec:TriggerRegisterTimerEvent[Trigger:%s, timeout:%.4g, periodic:%s]...",GetStrID(Trigger).c_str( ), (*timeout), BoolToStr(periodic));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterTimerEvent_ptr(Trigger, timeout, periodic);
   SpyJassLog("[TriggerRegisterTimerEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterTimerExpireEvent_my(HTRIGGER Trigger, HTIMER t)
{
   funcname1 = "TriggerRegisterTimerExpireEvent";
   SpyJassLog(" Exec:TriggerRegisterTimerExpireEvent[Trigger:%s, t:%s]...",GetStrID(Trigger).c_str( ), GetStrID(t).c_str( ));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterTimerExpireEvent_ptr(Trigger, t);
   SpyJassLog("[TriggerRegisterTimerExpireEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterTrackableHitEvent_my(HTRIGGER Trigger, HTRACKABLE t)
{
   funcname1 = "TriggerRegisterTrackableHitEvent";
   SpyJassLog(" Exec:TriggerRegisterTrackableHitEvent[Trigger:%s, t:%s]...",GetStrID(Trigger).c_str( ), GetStrID(t).c_str( ));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterTrackableHitEvent_ptr(Trigger, t);
   SpyJassLog("[TriggerRegisterTrackableHitEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterTrackableTrackEvent_my(HTRIGGER Trigger, HTRACKABLE t)
{
   funcname1 = "TriggerRegisterTrackableTrackEvent";
   SpyJassLog(" Exec:TriggerRegisterTrackableTrackEvent[Trigger:%s, t:%s]...",GetStrID(Trigger).c_str( ), GetStrID(t).c_str( ));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterTrackableTrackEvent_ptr(Trigger, t);
   SpyJassLog("[TriggerRegisterTrackableTrackEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterUnitEvent_my(HTRIGGER Trigger, HUNIT unit, HUNITEVENT Event)
{
   funcname1 = "TriggerRegisterUnitEvent";
   SpyJassLog(" Exec:TriggerRegisterUnitEvent[Trigger:%s, unit:%s, Event:%s]...",GetStrID(Trigger).c_str( ), GetUnitHID(unit).c_str( ), GetStrID(Event).c_str( ));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterUnitEvent_ptr(Trigger, unit, Event);
   SpyJassLog("[TriggerRegisterUnitEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterUnitInRange_my(HTRIGGER Trigger, HUNIT unit, float *range, HBOOLEXPR filter)
{
   funcname1 = "TriggerRegisterUnitInRange";
   SpyJassLog(" Exec:TriggerRegisterUnitInRange[Trigger:%s, unit:%s, range:%.4g, filter:%s]...",GetStrID(Trigger).c_str( ), GetUnitHID(unit).c_str( ), (*range), GetStrID(filter).c_str( ));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterUnitInRange_ptr(Trigger, unit, range, filter);
   SpyJassLog("[TriggerRegisterUnitInRange] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterUnitStateEvent_my(HTRIGGER Trigger, HUNIT unit, HUNITSTATE State, HLIMITOP opcode, float *limitval)
{
   funcname1 = "TriggerRegisterUnitStateEvent";
   SpyJassLog(" Exec:TriggerRegisterUnitStateEvent[Trigger:%s, unit:%s, State:%s, opcode:%s, limitval:%.4g]...",GetStrID(Trigger).c_str( ), GetUnitHID(unit).c_str( ), GetStrID(State).c_str( ), GetStrID(opcode).c_str( ), (*limitval));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterUnitStateEvent_ptr(Trigger, unit, State, opcode, limitval);
   SpyJassLog("[TriggerRegisterUnitStateEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
HEVENT _cdecl TriggerRegisterVariableEvent_my(HTRIGGER Trigger, CJassString varName, HLIMITOP opcode, float *limitval)
{
   funcname1 = "TriggerRegisterVariableEvent";
   SpyJassLog(" Exec:TriggerRegisterVariableEvent[Trigger:%s, varName:%s, opcode:%s, limitval:%.4g]...",GetStrID(Trigger).c_str( ), ReadJassStringNormal(varName), GetStrID(opcode).c_str( ), (*limitval));
   HEVENT returnvalue; 
   returnvalue = TriggerRegisterVariableEvent_ptr(Trigger, varName, opcode, limitval);
   SpyJassLog("[TriggerRegisterVariableEvent] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
void _cdecl TriggerRemoveAction_my(HTRIGGER Trigger, HTRIGGERACTION Action)
{
   funcname1 = "TriggerRemoveAction";
   SpyJassLog(" Exec:TriggerRemoveAction...");
   TriggerRemoveAction_ptr(Trigger, Action);
   SpyJassLog("[TriggerRemoveAction] OK [Trigger:%s, Action:%s]\n",GetStrID(Trigger).c_str( ), GetStrID(Action).c_str( ));
}
void _cdecl TriggerRemoveCondition_my(HTRIGGER Trigger, HTRIGGERCONDITION Condition)
{
   funcname1 = "TriggerRemoveCondition";
   SpyJassLog(" Exec:TriggerRemoveCondition...");
   TriggerRemoveCondition_ptr(Trigger, Condition);
   SpyJassLog("[TriggerRemoveCondition] OK [Trigger:%s, Condition:%s]\n",GetStrID(Trigger).c_str( ), GetStrID(Condition).c_str( ));
}
void _cdecl TriggerSleepAction_my(float *timeout)
{
   funcname1 = "TriggerSleepAction";
   SpyJassLog(" Exec:TriggerSleepAction...");
   TriggerSleepAction_ptr(timeout);
   SpyJassLog("[TriggerSleepAction] OK [timeout:%.4g]\n",(*timeout));
}
void _cdecl TriggerSyncReady_my()
{
   funcname1 = "TriggerSyncReady";
   SpyJassLog(" Exec:TriggerSyncReady...");
   TriggerSyncReady_ptr();
   SpyJassLog("[TriggerSyncReady] OK []\n");
}
void _cdecl TriggerSyncStart_my()
{
   funcname1 = "TriggerSyncStart";
   SpyJassLog(" Exec:TriggerSyncStart...");
   TriggerSyncStart_ptr();
   SpyJassLog("[TriggerSyncStart] OK []\n");
}
void _cdecl TriggerWaitForSound_my(HSOUND s, float *offset)
{
   funcname1 = "TriggerWaitForSound";
   SpyJassLog(" Exec:TriggerWaitForSound...");
   TriggerWaitForSound_ptr(s, offset);
   SpyJassLog("[TriggerWaitForSound] OK [s:%s, offset:%.4g]\n",GetStrID(s).c_str( ), (*offset));
}
void _cdecl TriggerWaitOnSleeps_my(HTRIGGER Trigger, BOOL flag)
{
   funcname1 = "TriggerWaitOnSleeps";
   SpyJassLog(" Exec:TriggerWaitOnSleeps...");
   TriggerWaitOnSleeps_ptr(Trigger, flag);
   SpyJassLog("[TriggerWaitOnSleeps] OK [Trigger:%s, flag:%s]\n",GetStrID(Trigger).c_str( ), BoolToStr(flag));
}
BOOL _cdecl UnitAddAbility_my(HUNIT unit, int AbilID)
{
   funcname1 = "UnitAddAbility";
   SpyJassLog(" Exec:UnitAddAbility[unit:%s, AbilID:%s]...",GetUnitHID(unit).c_str( ), GetStrID(AbilID).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitAddAbility_ptr(unit, AbilID);
   SpyJassLog("[UnitAddAbility] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl UnitAddIndicator_my(HUNIT unit, int red, int green, int blue, int alpha)
{
   funcname1 = "UnitAddIndicator";
   SpyJassLog(" Exec:UnitAddIndicator...");
   UnitAddIndicator_ptr(unit, red, green, blue, alpha);
   SpyJassLog("[UnitAddIndicator] OK [unit:%s, red:%s, green:%s, blue:%s, alpha:%s]\n",GetUnitHID(unit).c_str( ), GetStrID(red).c_str( ), GetStrID(green).c_str( ), GetStrID(blue).c_str( ), GetStrID(alpha).c_str( ));
}
BOOL _cdecl UnitAddItem_my(HUNIT unit, HITEM item)
{
   funcname1 = "UnitAddItem";
   SpyJassLog(" Exec:UnitAddItem[unit:%s, item:%s]...",GetUnitHID(unit).c_str( ), GetItemHID(item).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitAddItem_ptr(unit, item);
   SpyJassLog("[UnitAddItem] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
HITEM _cdecl UnitAddItemById_my(HUNIT unit, int itemId)
{
   funcname1 = "UnitAddItemById";
   SpyJassLog(" Exec:UnitAddItemById[unit:%s, itemId:%s]...",GetUnitHID(unit).c_str( ), GetStrID(itemId).c_str( ));
   HITEM returnvalue; 
   returnvalue = UnitAddItemById_ptr(unit, itemId);
   SpyJassLog("[UnitAddItemById] OK [%s]\n",GetItemHID(returnvalue).c_str( ));
   return returnvalue;
}
BOOL _cdecl UnitAddItemToSlotById_my(HUNIT unit, int itemId, int itemSlot)
{
   funcname1 = "UnitAddItemToSlotById";
   SpyJassLog(" Exec:UnitAddItemToSlotById[unit:%s, itemId:%s, itemSlot:%s]...",GetUnitHID(unit).c_str( ), GetStrID(itemId).c_str( ), GetStrID(itemSlot).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitAddItemToSlotById_ptr(unit, itemId, itemSlot);
   SpyJassLog("[UnitAddItemToSlotById] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl UnitAddSleep_my(HUNIT unit, BOOL add)
{
   funcname1 = "UnitAddSleep";
   SpyJassLog(" Exec:UnitAddSleep...");
   UnitAddSleep_ptr(unit, add);
   SpyJassLog("[UnitAddSleep] OK [unit:%s, add:%s]\n",GetUnitHID(unit).c_str( ), BoolToStr(add));
}
void _cdecl UnitAddSleepPerm_my(HUNIT unit, BOOL add)
{
   funcname1 = "UnitAddSleepPerm";
   SpyJassLog(" Exec:UnitAddSleepPerm...");
   UnitAddSleepPerm_ptr(unit, add);
   SpyJassLog("[UnitAddSleepPerm] OK [unit:%s, add:%s]\n",GetUnitHID(unit).c_str( ), BoolToStr(add));
}
BOOL _cdecl UnitAddType_my(HUNIT unit, HUNITTYPE UnitType)
{
   funcname1 = "UnitAddType";
   SpyJassLog(" Exec:UnitAddType[unit:%s, UnitType:%s]...",GetUnitHID(unit).c_str( ), GetStrID(UnitType).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitAddType_ptr(unit, UnitType);
   SpyJassLog("[UnitAddType] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl UnitAlive_my(HUNIT arg1)
{
   funcname1 = "UnitAlive";
   SpyJassLog(" Exec:UnitAlive[arg1:%s]...",GetUnitHID(arg1).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitAlive_ptr(arg1);
   SpyJassLog("[UnitAlive] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl UnitApplyTimedLife_my(HUNIT unit, int buffId, float *duration)
{
   funcname1 = "UnitApplyTimedLife";
   SpyJassLog(" Exec:UnitApplyTimedLife...");
   UnitApplyTimedLife_ptr(unit, buffId, duration);
   SpyJassLog("[UnitApplyTimedLife] OK [unit:%s, buffId:%s, duration:%.4g]\n",GetUnitHID(unit).c_str( ), GetStrID(buffId).c_str( ), (*duration));
}
BOOL _cdecl UnitCanSleep_my(HUNIT unit)
{
   funcname1 = "UnitCanSleep";
   SpyJassLog(" Exec:UnitCanSleep[unit:%s]...",GetUnitHID(unit).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitCanSleep_ptr(unit);
   SpyJassLog("[UnitCanSleep] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl UnitCanSleepPerm_my(HUNIT unit)
{
   funcname1 = "UnitCanSleepPerm";
   SpyJassLog(" Exec:UnitCanSleepPerm[unit:%s]...",GetUnitHID(unit).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitCanSleepPerm_ptr(unit);
   SpyJassLog("[UnitCanSleepPerm] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
int _cdecl UnitCountBuffsEx_my(HUNIT unit, BOOL removePositive, BOOL removeNegative, BOOL magic, BOOL physical, BOOL timedLife, BOOL aura, BOOL autoDispel)
{
   funcname1 = "UnitCountBuffsEx";
   SpyJassLog(" Exec:UnitCountBuffsEx[unit:%s, removePositive:%s, removeNegative:%s, magic:%s, physical:%s, timedLife:%s, aura:%s, autoDispel:%s]...",GetUnitHID(unit).c_str( ), BoolToStr(removePositive), BoolToStr(removeNegative), BoolToStr(magic), BoolToStr(physical), BoolToStr(timedLife), BoolToStr(aura), BoolToStr(autoDispel));
   int returnvalue; 
   returnvalue = UnitCountBuffsEx_ptr(unit, removePositive, removeNegative, magic, physical, timedLife, aura, autoDispel);
   SpyJassLog("[UnitCountBuffsEx] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
BOOL _cdecl UnitDamagePoint_my(HUNIT unit, float *delay, float *radius, float *x, float *y, float *amount, BOOL attack, BOOL ranged, HATTACKTYPE attackType, HDAMAGETYPE damageType, HWEAPONTYPE weaponType)
{
   funcname1 = "UnitDamagePoint";
   SpyJassLog(" Exec:UnitDamagePoint[unit:%s, delay:%.4g, radius:%.4g, x:%.4g, y:%.4g, amount:%.4g, attack:%s, ranged:%s, attackType:%s, damageType:%s, weaponType:%s]...",GetUnitHID(unit).c_str( ), (*delay), (*radius), (*x), (*y), (*amount), BoolToStr(attack), BoolToStr(ranged), GetStrID(attackType).c_str( ), GetStrID(damageType).c_str( ), GetStrID(weaponType).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitDamagePoint_ptr(unit, delay, radius, x, y, amount, attack, ranged, attackType, damageType, weaponType);
   SpyJassLog("[UnitDamagePoint] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl UnitDamageTarget_my(HUNIT unit, HWIDGET target, float *amount, BOOL attack, BOOL ranged, HATTACKTYPE attackType, HDAMAGETYPE damageType, HWEAPONTYPE weaponType)
{
   funcname1 = "UnitDamageTarget";
   SpyJassLog(" Exec:UnitDamageTarget[unit:%s, target:%s, amount:%.4g, attack:%s, ranged:%s, attackType:%s, damageType:%s, weaponType:%s]...",GetUnitHID(unit).c_str( ), GetStrID(target).c_str( ), (*amount), BoolToStr(attack), BoolToStr(ranged), GetStrID(attackType).c_str( ), GetStrID(damageType).c_str( ), GetStrID(weaponType).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitDamageTarget_ptr(unit, target, amount, attack, ranged, attackType, damageType, weaponType);
   SpyJassLog("[UnitDamageTarget] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl UnitDropItemPoint_my(HUNIT unit, HITEM item, float *x, float *y)
{
   funcname1 = "UnitDropItemPoint";
   SpyJassLog(" Exec:UnitDropItemPoint[unit:%s, item:%s, x:%.4g, y:%.4g]...",GetUnitHID(unit).c_str( ), GetItemHID(item).c_str( ), (*x), (*y));
   BOOL returnvalue; 
   returnvalue = UnitDropItemPoint_ptr(unit, item, x, y);
   SpyJassLog("[UnitDropItemPoint] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl UnitDropItemSlot_my(HUNIT unit, HITEM item, int slot)
{
   funcname1 = "UnitDropItemSlot";
   SpyJassLog(" Exec:UnitDropItemSlot[unit:%s, item:%s, slot:%s]...",GetUnitHID(unit).c_str( ), GetItemHID(item).c_str( ), GetStrID(slot).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitDropItemSlot_ptr(unit, item, slot);
   SpyJassLog("[UnitDropItemSlot] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl UnitDropItemTarget_my(HUNIT unit, HITEM item, HWIDGET target)
{
   funcname1 = "UnitDropItemTarget";
   SpyJassLog(" Exec:UnitDropItemTarget[unit:%s, item:%s, target:%s]...",GetUnitHID(unit).c_str( ), GetItemHID(item).c_str( ), GetStrID(target).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitDropItemTarget_ptr(unit, item, target);
   SpyJassLog("[UnitDropItemTarget] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl UnitHasBuffsEx_my(HUNIT unit, BOOL removePositive, BOOL removeNegative, BOOL magic, BOOL physical, BOOL timedLife, BOOL aura, BOOL autoDispel)
{
   funcname1 = "UnitHasBuffsEx";
   SpyJassLog(" Exec:UnitHasBuffsEx[unit:%s, removePositive:%s, removeNegative:%s, magic:%s, physical:%s, timedLife:%s, aura:%s, autoDispel:%s]...",GetUnitHID(unit).c_str( ), BoolToStr(removePositive), BoolToStr(removeNegative), BoolToStr(magic), BoolToStr(physical), BoolToStr(timedLife), BoolToStr(aura), BoolToStr(autoDispel));
   BOOL returnvalue; 
   returnvalue = UnitHasBuffsEx_ptr(unit, removePositive, removeNegative, magic, physical, timedLife, aura, autoDispel);
   SpyJassLog("[UnitHasBuffsEx] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl UnitHasItem_my(HUNIT unit, HITEM item)
{
   funcname1 = "UnitHasItem";
   SpyJassLog(" Exec:UnitHasItem[unit:%s, item:%s]...",GetUnitHID(unit).c_str( ), GetItemHID(item).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitHasItem_ptr(unit, item);
   SpyJassLog("[UnitHasItem] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
int _cdecl UnitId_my(CJassString unitIdString)
{
   funcname1 = "UnitId";
   SpyJassLog(" Exec:UnitId[unitIdString:%s]...",ReadJassStringNormal(unitIdString));
   int returnvalue; 
   returnvalue = UnitId_ptr(unitIdString);
   SpyJassLog("[UnitId] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
CJassStringSID _cdecl UnitId2String_my(int unitId)
{
   funcname1 = "UnitId2String";
   SpyJassLog(" Exec:UnitId2String[unitId:%s]...",GetStrID(unitId).c_str( ));
   CJassStringSID returnvalue; 
   returnvalue = UnitId2String_ptr(unitId);
   SpyJassLog("[UnitId2String] OK [%s]\n",ReadJassSID(returnvalue));
   return returnvalue;
}
BOOL _cdecl UnitIgnoreAlarm_my(HUNIT unit, BOOL flag)
{
   funcname1 = "UnitIgnoreAlarm";
   SpyJassLog(" Exec:UnitIgnoreAlarm[unit:%s, flag:%s]...",GetUnitHID(unit).c_str( ), BoolToStr(flag));
   BOOL returnvalue; 
   returnvalue = UnitIgnoreAlarm_ptr(unit, flag);
   SpyJassLog("[UnitIgnoreAlarm] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl UnitIgnoreAlarmToggled_my(HUNIT unit)
{
   funcname1 = "UnitIgnoreAlarmToggled";
   SpyJassLog(" Exec:UnitIgnoreAlarmToggled[unit:%s]...",GetUnitHID(unit).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitIgnoreAlarmToggled_ptr(unit);
   SpyJassLog("[UnitIgnoreAlarmToggled] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
int _cdecl UnitInventorySize_my(HUNIT unit)
{
   funcname1 = "UnitInventorySize";
   SpyJassLog(" Exec:UnitInventorySize[unit:%s]...",GetUnitHID(unit).c_str( ));
   int returnvalue; 
   returnvalue = UnitInventorySize_ptr(unit);
   SpyJassLog("[UnitInventorySize] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
BOOL _cdecl UnitInvis_my(HUNIT arg1)
{
   funcname1 = "UnitInvis";
   SpyJassLog(" Exec:UnitInvis[arg1:%s]...",GetUnitHID(arg1).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitInvis_ptr(arg1);
   SpyJassLog("[UnitInvis] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl UnitIsSleeping_my(HUNIT unit)
{
   funcname1 = "UnitIsSleeping";
   SpyJassLog(" Exec:UnitIsSleeping[unit:%s]...",GetUnitHID(unit).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitIsSleeping_ptr(unit);
   SpyJassLog("[UnitIsSleeping] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
HITEM _cdecl UnitItemInSlot_my(HUNIT unit, int itemSlot)
{
   funcname1 = "UnitItemInSlot";
   SpyJassLog(" Exec:UnitItemInSlot[unit:%s, itemSlot:%s]...",GetUnitHID(unit).c_str( ), GetStrID(itemSlot).c_str( ));
   HITEM returnvalue; 
   returnvalue = UnitItemInSlot_ptr(unit, itemSlot);
   SpyJassLog("[UnitItemInSlot] OK [%s]\n",GetItemHID(returnvalue).c_str( ));
   return returnvalue;
}
BOOL _cdecl UnitMakeAbilityPermanent_my(HUNIT unit, BOOL permanent, int AbilID)
{
   funcname1 = "UnitMakeAbilityPermanent";
   SpyJassLog(" Exec:UnitMakeAbilityPermanent[unit:%s, permanent:%s, AbilID:%s]...",GetUnitHID(unit).c_str( ), BoolToStr(permanent), GetStrID(AbilID).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitMakeAbilityPermanent_ptr(unit, permanent, AbilID);
   SpyJassLog("[UnitMakeAbilityPermanent] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl UnitModifySkillPoints_my(HUNIT hero, int skillPointDelta)
{
   funcname1 = "UnitModifySkillPoints";
   SpyJassLog(" Exec:UnitModifySkillPoints[hero:%s, skillPointDelta:%s]...",GetUnitHID(hero).c_str( ), GetStrID(skillPointDelta).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitModifySkillPoints_ptr(hero, skillPointDelta);
   SpyJassLog("[UnitModifySkillPoints] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl UnitPauseTimedLife_my(HUNIT unit, BOOL flag)
{
   funcname1 = "UnitPauseTimedLife";
   SpyJassLog(" Exec:UnitPauseTimedLife...");
   UnitPauseTimedLife_ptr(unit, flag);
   SpyJassLog("[UnitPauseTimedLife] OK [unit:%s, flag:%s]\n",GetUnitHID(unit).c_str( ), BoolToStr(flag));
}
void _cdecl UnitPoolAddUnitType_my(HUNITPOOL Pool, int unitId, float *weight)
{
   funcname1 = "UnitPoolAddUnitType";
   SpyJassLog(" Exec:UnitPoolAddUnitType...");
   UnitPoolAddUnitType_ptr(Pool, unitId, weight);
   SpyJassLog("[UnitPoolAddUnitType] OK [Pool:%s, unitId:%s, weight:%.4g]\n",GetStrID(Pool).c_str( ), GetStrID(unitId).c_str( ), (*weight));
}
void _cdecl UnitPoolRemoveUnitType_my(HUNITPOOL Pool, int unitId)
{
   funcname1 = "UnitPoolRemoveUnitType";
   SpyJassLog(" Exec:UnitPoolRemoveUnitType...");
   UnitPoolRemoveUnitType_ptr(Pool, unitId);
   SpyJassLog("[UnitPoolRemoveUnitType] OK [Pool:%s, unitId:%s]\n",GetStrID(Pool).c_str( ), GetStrID(unitId).c_str( ));
}
BOOL _cdecl UnitRemoveAbility_my(HUNIT unit, int AbilID)
{
   funcname1 = "UnitRemoveAbility";
   SpyJassLog(" Exec:UnitRemoveAbility[unit:%s, AbilID:%s]...",GetUnitHID(unit).c_str( ), GetStrID(AbilID).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitRemoveAbility_ptr(unit, AbilID);
   SpyJassLog("[UnitRemoveAbility] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl UnitRemoveBuffs_my(HUNIT unit, BOOL removePositive, BOOL removeNegative)
{
   funcname1 = "UnitRemoveBuffs";
   SpyJassLog(" Exec:UnitRemoveBuffs...");
   UnitRemoveBuffs_ptr(unit, removePositive, removeNegative);
   SpyJassLog("[UnitRemoveBuffs] OK [unit:%s, removePositive:%s, removeNegative:%s]\n",GetUnitHID(unit).c_str( ), BoolToStr(removePositive), BoolToStr(removeNegative));
}
void _cdecl UnitRemoveBuffsEx_my(HUNIT unit, BOOL removePositive, BOOL removeNegative, BOOL magic, BOOL physical, BOOL timedLife, BOOL aura, BOOL autoDispel)
{
   funcname1 = "UnitRemoveBuffsEx";
   SpyJassLog(" Exec:UnitRemoveBuffsEx...");
   UnitRemoveBuffsEx_ptr(unit, removePositive, removeNegative, magic, physical, timedLife, aura, autoDispel);
   SpyJassLog("[UnitRemoveBuffsEx] OK [unit:%s, removePositive:%s, removeNegative:%s, magic:%s, physical:%s, timedLife:%s, aura:%s, autoDispel:%s]\n",GetUnitHID(unit).c_str( ), BoolToStr(removePositive), BoolToStr(removeNegative), BoolToStr(magic), BoolToStr(physical), BoolToStr(timedLife), BoolToStr(aura), BoolToStr(autoDispel));
}
void _cdecl UnitRemoveItem_my(HUNIT unit, HITEM item)
{
   funcname1 = "UnitRemoveItem";
   SpyJassLog(" Exec:UnitRemoveItem...");
   UnitRemoveItem_ptr(unit, item);
   SpyJassLog("[UnitRemoveItem] OK [unit:%s, item:%s]\n",GetUnitHID(unit).c_str( ), GetItemHID(item).c_str( ));
}
HITEM _cdecl UnitRemoveItemFromSlot_my(HUNIT unit, int itemSlot)
{
   funcname1 = "UnitRemoveItemFromSlot";
   SpyJassLog(" Exec:UnitRemoveItemFromSlot[unit:%s, itemSlot:%s]...",GetUnitHID(unit).c_str( ), GetStrID(itemSlot).c_str( ));
   HITEM returnvalue; 
   returnvalue = UnitRemoveItemFromSlot_ptr(unit, itemSlot);
   SpyJassLog("[UnitRemoveItemFromSlot] OK [%s]\n",GetItemHID(returnvalue).c_str( ));
   return returnvalue;
}
BOOL _cdecl UnitRemoveType_my(HUNIT unit, HUNITTYPE UnitType)
{
   funcname1 = "UnitRemoveType";
   SpyJassLog(" Exec:UnitRemoveType[unit:%s, UnitType:%s]...",GetUnitHID(unit).c_str( ), GetStrID(UnitType).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitRemoveType_ptr(unit, UnitType);
   SpyJassLog("[UnitRemoveType] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl UnitResetCooldown_my(HUNIT unit)
{
   funcname1 = "UnitResetCooldown";
   SpyJassLog(" Exec:UnitResetCooldown...");
   UnitResetCooldown_ptr(unit);
   SpyJassLog("[UnitResetCooldown] OK [unit:%s]\n",GetUnitHID(unit).c_str( ));
}
void _cdecl UnitSetConstructionProgress_my(HUNIT unit, int constructionPercentage)
{
   funcname1 = "UnitSetConstructionProgress";
   SpyJassLog(" Exec:UnitSetConstructionProgress...");
   UnitSetConstructionProgress_ptr(unit, constructionPercentage);
   SpyJassLog("[UnitSetConstructionProgress] OK [unit:%s, constructionPercentage:%s]\n",GetUnitHID(unit).c_str( ), GetStrID(constructionPercentage).c_str( ));
}
void _cdecl UnitSetUpgradeProgress_my(HUNIT unit, int upgradePercentage)
{
   funcname1 = "UnitSetUpgradeProgress";
   SpyJassLog(" Exec:UnitSetUpgradeProgress...");
   UnitSetUpgradeProgress_ptr(unit, upgradePercentage);
   SpyJassLog("[UnitSetUpgradeProgress] OK [unit:%s, upgradePercentage:%s]\n",GetUnitHID(unit).c_str( ), GetStrID(upgradePercentage).c_str( ));
}
void _cdecl UnitSetUsesAltIcon_my(HUNIT unit, BOOL flag)
{
   funcname1 = "UnitSetUsesAltIcon";
   SpyJassLog(" Exec:UnitSetUsesAltIcon...");
   UnitSetUsesAltIcon_ptr(unit, flag);
   SpyJassLog("[UnitSetUsesAltIcon] OK [unit:%s, flag:%s]\n",GetUnitHID(unit).c_str( ), BoolToStr(flag));
}
void _cdecl UnitShareVision_my(HUNIT unit, HPLAYER player, BOOL share)
{
   funcname1 = "UnitShareVision";
   SpyJassLog(" Exec:UnitShareVision...");
   UnitShareVision_ptr(unit, player, share);
   SpyJassLog("[UnitShareVision] OK [unit:%s, player:%i, share:%s]\n",GetUnitHID(unit).c_str( ), GetPlayerId_ptr(player), BoolToStr(share));
}
BOOL _cdecl UnitStripHeroLevel_my(HUNIT hero, int howManyLevels)
{
   funcname1 = "UnitStripHeroLevel";
   SpyJassLog(" Exec:UnitStripHeroLevel[hero:%s, howManyLevels:%s]...",GetUnitHID(hero).c_str( ), GetStrID(howManyLevels).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitStripHeroLevel_ptr(hero, howManyLevels);
   SpyJassLog("[UnitStripHeroLevel] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl UnitSuspendDecay_my(HUNIT unit, BOOL suspend)
{
   funcname1 = "UnitSuspendDecay";
   SpyJassLog(" Exec:UnitSuspendDecay...");
   UnitSuspendDecay_ptr(unit, suspend);
   SpyJassLog("[UnitSuspendDecay] OK [unit:%s, suspend:%s]\n",GetUnitHID(unit).c_str( ), BoolToStr(suspend));
}
BOOL _cdecl UnitUseItem_my(HUNIT unit, HITEM item)
{
   funcname1 = "UnitUseItem";
   SpyJassLog(" Exec:UnitUseItem[unit:%s, item:%s]...",GetUnitHID(unit).c_str( ), GetItemHID(item).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitUseItem_ptr(unit, item);
   SpyJassLog("[UnitUseItem] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl UnitUseItemPoint_my(HUNIT unit, HITEM item, float *x, float *y)
{
   funcname1 = "UnitUseItemPoint";
   SpyJassLog(" Exec:UnitUseItemPoint[unit:%s, item:%s, x:%.4g, y:%.4g]...",GetUnitHID(unit).c_str( ), GetItemHID(item).c_str( ), (*x), (*y));
   BOOL returnvalue; 
   returnvalue = UnitUseItemPoint_ptr(unit, item, x, y);
   SpyJassLog("[UnitUseItemPoint] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
BOOL _cdecl UnitUseItemTarget_my(HUNIT unit, HITEM item, HWIDGET target)
{
   funcname1 = "UnitUseItemTarget";
   SpyJassLog(" Exec:UnitUseItemTarget[unit:%s, item:%s, target:%s]...",GetUnitHID(unit).c_str( ), GetItemHID(item).c_str( ), GetStrID(target).c_str( ));
   BOOL returnvalue; 
   returnvalue = UnitUseItemTarget_ptr(unit, item, target);
   SpyJassLog("[UnitUseItemTarget] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl UnitWakeUp_my(HUNIT unit)
{
   funcname1 = "UnitWakeUp";
   SpyJassLog(" Exec:UnitWakeUp...");
   UnitWakeUp_ptr(unit);
   SpyJassLog("[UnitWakeUp] OK [unit:%s]\n",GetUnitHID(unit).c_str( ));
}
void _cdecl UnregisterStackedSound_my(HSOUND soundHandle, BOOL byPosition, float *rectwidth, float *rectheight)
{
   funcname1 = "UnregisterStackedSound";
   SpyJassLog(" Exec:UnregisterStackedSound...");
   UnregisterStackedSound_ptr(soundHandle, byPosition, rectwidth, rectheight);
   SpyJassLog("[UnregisterStackedSound] OK [soundHandle:%s, byPosition:%s, rectwidth:%.4g, rectheight:%.4g]\n",GetStrID(soundHandle).c_str( ), BoolToStr(byPosition), (*rectwidth), (*rectheight));
}
void _cdecl Unsummon_my(HUNIT arg1)
{
   funcname1 = "Unsummon";
   SpyJassLog(" Exec:Unsummon...");
   Unsummon_ptr(arg1);
   SpyJassLog("[Unsummon] OK [arg1:%s]\n",GetUnitHID(arg1).c_str( ));
}
BOOL _cdecl VersionCompatible_my(HVERSION Version)
{
   funcname1 = "VersionCompatible";
   SpyJassLog(" Exec:VersionCompatible[Version:%s]...",GetStrID(Version).c_str( ));
   BOOL returnvalue; 
   returnvalue = VersionCompatible_ptr(Version);
   SpyJassLog("[VersionCompatible] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
HVERSION _cdecl VersionGet_my()
{
   funcname1 = "VersionGet";
   SpyJassLog(" Exec:VersionGet[]...");
   HVERSION returnvalue; 
   returnvalue = VersionGet_ptr();
   SpyJassLog("[VersionGet] OK [%s]\n",GetStrID( returnvalue ).c_str( ));
   return returnvalue;
}
BOOL _cdecl VersionSupported_my(HVERSION Version)
{
   funcname1 = "VersionSupported";
   SpyJassLog(" Exec:VersionSupported[Version:%s]...",GetStrID(Version).c_str( ));
   BOOL returnvalue; 
   returnvalue = VersionSupported_ptr(Version);
   SpyJassLog("[VersionSupported] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl VolumeGroupReset_my()
{
   funcname1 = "VolumeGroupReset";
   SpyJassLog(" Exec:VolumeGroupReset...");
   VolumeGroupReset_ptr();
   SpyJassLog("[VolumeGroupReset] OK []\n");
}
void _cdecl VolumeGroupSetVolume_my(HVOLUMEGROUP vgroup, float *scale)
{
   funcname1 = "VolumeGroupSetVolume";
   SpyJassLog(" Exec:VolumeGroupSetVolume...");
   VolumeGroupSetVolume_ptr(vgroup, scale);
   SpyJassLog("[VolumeGroupSetVolume] OK [vgroup:%s, scale:%.4g]\n",GetStrID(vgroup).c_str( ), (*scale));
}
BOOL _cdecl WaitGetEnemyBase_my()
{
   funcname1 = "WaitGetEnemyBase";
   SpyJassLog(" Exec:WaitGetEnemyBase[]...");
   BOOL returnvalue; 
   returnvalue = WaitGetEnemyBase_ptr();
   SpyJassLog("[WaitGetEnemyBase] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl WaygateActivate_my(HUNIT waygate, BOOL activate)
{
   funcname1 = "WaygateActivate";
   SpyJassLog(" Exec:WaygateActivate...");
   WaygateActivate_ptr(waygate, activate);
   SpyJassLog("[WaygateActivate] OK [waygate:%s, activate:%s]\n",GetUnitHID(waygate).c_str( ), BoolToStr(activate));
}
DWFP _cdecl WaygateGetDestinationX_my(HUNIT waygate)
{
   funcname1 = "WaygateGetDestinationX";
   SpyJassLog(" Exec:WaygateGetDestinationX[waygate:%s]...",GetUnitHID(waygate).c_str( ));
   DWFP returnvalue; 
   returnvalue = WaygateGetDestinationX_ptr(waygate);
   SpyJassLog("[WaygateGetDestinationX] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
DWFP _cdecl WaygateGetDestinationY_my(HUNIT waygate)
{
   funcname1 = "WaygateGetDestinationY";
   SpyJassLog(" Exec:WaygateGetDestinationY[waygate:%s]...",GetUnitHID(waygate).c_str( ));
   DWFP returnvalue; 
   returnvalue = WaygateGetDestinationY_ptr(waygate);
   SpyJassLog("[WaygateGetDestinationY] OK [%.4g]\n",GetFloatFromDWFP(returnvalue));
   return returnvalue;
}
BOOL _cdecl WaygateIsActive_my(HUNIT waygate)
{
   funcname1 = "WaygateIsActive";
   SpyJassLog(" Exec:WaygateIsActive[waygate:%s]...",GetUnitHID(waygate).c_str( ));
   BOOL returnvalue; 
   returnvalue = WaygateIsActive_ptr(waygate);
   SpyJassLog("[WaygateIsActive] OK [%s]\n",BoolToStr(returnvalue));
   return returnvalue;
}
void _cdecl WaygateSetDestination_my(HUNIT waygate, float *x, float *y)
{
   funcname1 = "WaygateSetDestination";
   SpyJassLog(" Exec:WaygateSetDestination...");
   WaygateSetDestination_ptr(waygate, x, y);
   SpyJassLog("[WaygateSetDestination] OK [waygate:%s, x:%.4g, y:%.4g]\n",GetUnitHID(waygate).c_str( ), (*x), (*y));
}
