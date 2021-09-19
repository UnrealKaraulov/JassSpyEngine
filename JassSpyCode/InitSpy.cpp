#include "JassFuncs.h"
#include "IniReader.h"
struct JassStringData {
	DWORD vtable;
	DWORD refCount;
	DWORD dwUnk1;
	DWORD pUnk2;
	DWORD pUnk3;
	DWORD pUnk4;
	DWORD pUnk5;
	char *data;
};


struct CJassString {
	DWORD vtable;
	DWORD dw0;
	JassStringData *data;
	DWORD dw1;
};


void InitHackPart2(void);
void InitHack(void)
{

	DWORD GameDll = (DWORD) GetModuleHandle("Game.dll");
	CIniReader JassINI(".\\JassSpy.ini");


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AbilityId", FALSE))
	{
		GAME_AbilityIdorg = (GAME_AbilityId) ((DWORD) GameDll + 0x3BB5F0);
		MH_CreateHook(GAME_AbilityIdorg, &GAME_AbilityIdmy, reinterpret_cast<void**>(&GAME_AbilityIdold));
		MH_EnableHook(GAME_AbilityIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AbilityId2String", FALSE))
	{
		GAME_AbilityId2Stringorg = (GAME_AbilityId2String) ((DWORD) GameDll + 0x3BB620);
		MH_CreateHook(GAME_AbilityId2Stringorg, &GAME_AbilityId2Stringmy, reinterpret_cast<void**>(&GAME_AbilityId2Stringold));
		MH_EnableHook(GAME_AbilityId2Stringorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Acos", FALSE))
	{
		GAME_Acosorg = (GAME_Acos) ((DWORD) GameDll + 0x3B2AB0);
		MH_CreateHook(GAME_Acosorg, &GAME_Acosmy, reinterpret_cast<void**>(&GAME_Acosold));
		MH_EnableHook(GAME_Acosorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddAssault", FALSE))
	{
		GAME_AddAssaultorg = (GAME_AddAssault) ((DWORD) GameDll + 0x2DD9C0);
		MH_CreateHook(GAME_AddAssaultorg, &GAME_AddAssaultmy, reinterpret_cast<void**>(&GAME_AddAssaultold));
		MH_EnableHook(GAME_AddAssaultorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddDefenders", FALSE))
	{
		GAME_AddDefendersorg = (GAME_AddDefenders) ((DWORD) GameDll + 0x2DDA00);
		MH_CreateHook(GAME_AddDefendersorg, &GAME_AddDefendersmy, reinterpret_cast<void**>(&GAME_AddDefendersold));
		MH_EnableHook(GAME_AddDefendersorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddGuardPost", FALSE))
	{
		GAME_AddGuardPostorg = (GAME_AddGuardPost) ((DWORD) GameDll + 0x2DCE30);
		MH_CreateHook(GAME_AddGuardPostorg, &GAME_AddGuardPostmy, reinterpret_cast<void**>(&GAME_AddGuardPostold));
		MH_EnableHook(GAME_AddGuardPostorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddHeroXP", FALSE))
	{
		GAME_AddHeroXPorg = (GAME_AddHeroXP) ((DWORD) GameDll + 0x3C6CF0);
		MH_CreateHook(GAME_AddHeroXPorg, &GAME_AddHeroXPmy, reinterpret_cast<void**>(&GAME_AddHeroXPold));
		MH_EnableHook(GAME_AddHeroXPorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddIndicator", FALSE))
	{
		GAME_AddIndicatororg = (GAME_AddIndicator) ((DWORD) GameDll + 0x3C6C60);
		MH_CreateHook(GAME_AddIndicatororg, &GAME_AddIndicatormy, reinterpret_cast<void**>(&GAME_AddIndicatorold));
		MH_EnableHook(GAME_AddIndicatororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddItemToAllStock", FALSE))
	{
		GAME_AddItemToAllStockorg = (GAME_AddItemToAllStock) ((DWORD) GameDll + 0x3B3270);
		MH_CreateHook(GAME_AddItemToAllStockorg, &GAME_AddItemToAllStockmy, reinterpret_cast<void**>(&GAME_AddItemToAllStockold));
		MH_EnableHook(GAME_AddItemToAllStockorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddItemToStock", FALSE))
	{
		GAME_AddItemToStockorg = (GAME_AddItemToStock) ((DWORD) GameDll + 0x3C9350);
		MH_CreateHook(GAME_AddItemToStockorg, &GAME_AddItemToStockmy, reinterpret_cast<void**>(&GAME_AddItemToStockold));
		MH_EnableHook(GAME_AddItemToStockorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddLightning", FALSE))
	{
		GAME_AddLightningorg = (GAME_AddLightning) ((DWORD) GameDll + 0x3BCC20);
		MH_CreateHook(GAME_AddLightningorg, &GAME_AddLightningmy, reinterpret_cast<void**>(&GAME_AddLightningold));
		MH_EnableHook(GAME_AddLightningorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddLightningEx", FALSE))
	{
		GAME_AddLightningExorg = (GAME_AddLightningEx) ((DWORD) GameDll + 0x3BCB30);
		MH_CreateHook(GAME_AddLightningExorg, &GAME_AddLightningExmy, reinterpret_cast<void**>(&GAME_AddLightningExold));
		MH_EnableHook(GAME_AddLightningExorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddPlayerTechResearched", FALSE))
	{
		GAME_AddPlayerTechResearchedorg = (GAME_AddPlayerTechResearched) ((DWORD) GameDll + 0x3C96D0);
		MH_CreateHook(GAME_AddPlayerTechResearchedorg, &GAME_AddPlayerTechResearchedmy, reinterpret_cast<void**>(&GAME_AddPlayerTechResearchedold));
		MH_EnableHook(GAME_AddPlayerTechResearchedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddResourceAmount", FALSE))
	{
		GAME_AddResourceAmountorg = (GAME_AddResourceAmount) ((DWORD) GameDll + 0x3C7850);
		MH_CreateHook(GAME_AddResourceAmountorg, &GAME_AddResourceAmountmy, reinterpret_cast<void**>(&GAME_AddResourceAmountold));
		MH_EnableHook(GAME_AddResourceAmountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddSpecialEffect", FALSE))
	{
		GAME_AddSpecialEffectorg = (GAME_AddSpecialEffect) ((DWORD) GameDll + 0x3BCA90);
		MH_CreateHook(GAME_AddSpecialEffectorg, &GAME_AddSpecialEffectmy, reinterpret_cast<void**>(&GAME_AddSpecialEffectold));
		MH_EnableHook(GAME_AddSpecialEffectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddSpecialEffectLoc", FALSE))
	{
		GAME_AddSpecialEffectLocorg = (GAME_AddSpecialEffectLoc) ((DWORD) GameDll + 0x3CD260);
		MH_CreateHook(GAME_AddSpecialEffectLocorg, &GAME_AddSpecialEffectLocmy, reinterpret_cast<void**>(&GAME_AddSpecialEffectLocold));
		MH_EnableHook(GAME_AddSpecialEffectLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddSpecialEffectTarget", FALSE))
	{
		GAME_AddSpecialEffectTargetorg = (GAME_AddSpecialEffectTarget) ((DWORD) GameDll + 0x3CD2A0);
		MH_CreateHook(GAME_AddSpecialEffectTargetorg, &GAME_AddSpecialEffectTargetmy, reinterpret_cast<void**>(&GAME_AddSpecialEffectTargetold));
		MH_EnableHook(GAME_AddSpecialEffectTargetorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddSpellEffect", FALSE))
	{
		GAME_AddSpellEffectorg = (GAME_AddSpellEffect) ((DWORD) GameDll + 0x3BCB10);
		MH_CreateHook(GAME_AddSpellEffectorg, &GAME_AddSpellEffectmy, reinterpret_cast<void**>(&GAME_AddSpellEffectold));
		MH_EnableHook(GAME_AddSpellEffectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddSpellEffectById", FALSE))
	{
		GAME_AddSpellEffectByIdorg = (GAME_AddSpellEffectById) ((DWORD) GameDll + 0x3BCAE0);
		MH_CreateHook(GAME_AddSpellEffectByIdorg, &GAME_AddSpellEffectByIdmy, reinterpret_cast<void**>(&GAME_AddSpellEffectByIdold));
		MH_EnableHook(GAME_AddSpellEffectByIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddSpellEffectByIdLoc", FALSE))
	{
		GAME_AddSpellEffectByIdLocorg = (GAME_AddSpellEffectByIdLoc) ((DWORD) GameDll + 0x3CD2D0);
		MH_CreateHook(GAME_AddSpellEffectByIdLocorg, &GAME_AddSpellEffectByIdLocmy, reinterpret_cast<void**>(&GAME_AddSpellEffectByIdLocold));
		MH_EnableHook(GAME_AddSpellEffectByIdLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddSpellEffectLoc", FALSE))
	{
		GAME_AddSpellEffectLocorg = (GAME_AddSpellEffectLoc) ((DWORD) GameDll + 0x3CD320);
		MH_CreateHook(GAME_AddSpellEffectLocorg, &GAME_AddSpellEffectLocmy, reinterpret_cast<void**>(&GAME_AddSpellEffectLocold));
		MH_EnableHook(GAME_AddSpellEffectLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddSpellEffectTarget", FALSE))
	{
		GAME_AddSpellEffectTargetorg = (GAME_AddSpellEffectTarget) ((DWORD) GameDll + 0x3CD4A0);
		MH_CreateHook(GAME_AddSpellEffectTargetorg, &GAME_AddSpellEffectTargetmy, reinterpret_cast<void**>(&GAME_AddSpellEffectTargetold));
		MH_EnableHook(GAME_AddSpellEffectTargetorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddSpellEffectTargetById", FALSE))
	{
		GAME_AddSpellEffectTargetByIdorg = (GAME_AddSpellEffectTargetById) ((DWORD) GameDll + 0x3CD380);
		MH_CreateHook(GAME_AddSpellEffectTargetByIdorg, &GAME_AddSpellEffectTargetByIdmy, reinterpret_cast<void**>(&GAME_AddSpellEffectTargetByIdold));
		MH_EnableHook(GAME_AddSpellEffectTargetByIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddUnitAnimationProperties", FALSE))
	{
		GAME_AddUnitAnimationPropertiesorg = (GAME_AddUnitAnimationProperties) ((DWORD) GameDll + 0x3C6220);
		MH_CreateHook(GAME_AddUnitAnimationPropertiesorg, &GAME_AddUnitAnimationPropertiesmy, reinterpret_cast<void**>(&GAME_AddUnitAnimationPropertiesold));
		MH_EnableHook(GAME_AddUnitAnimationPropertiesorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddUnitToAllStock", FALSE))
	{
		GAME_AddUnitToAllStockorg = (GAME_AddUnitToAllStock) ((DWORD) GameDll + 0x3B3290);
		MH_CreateHook(GAME_AddUnitToAllStockorg, &GAME_AddUnitToAllStockmy, reinterpret_cast<void**>(&GAME_AddUnitToAllStockold));
		MH_EnableHook(GAME_AddUnitToAllStockorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddUnitToStock", FALSE))
	{
		GAME_AddUnitToStockorg = (GAME_AddUnitToStock) ((DWORD) GameDll + 0x3C93A0);
		MH_CreateHook(GAME_AddUnitToStockorg, &GAME_AddUnitToStockmy, reinterpret_cast<void**>(&GAME_AddUnitToStockold));
		MH_EnableHook(GAME_AddUnitToStockorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AddWeatherEffect", FALSE))
	{
		GAME_AddWeatherEffectorg = (GAME_AddWeatherEffect) ((DWORD) GameDll + 0x3CCFE0);
		MH_CreateHook(GAME_AddWeatherEffectorg, &GAME_AddWeatherEffectmy, reinterpret_cast<void**>(&GAME_AddWeatherEffectold));
		MH_EnableHook(GAME_AddWeatherEffectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AdjustCameraField", FALSE))
	{
		GAME_AdjustCameraFieldorg = (GAME_AdjustCameraField) ((DWORD) GameDll + 0x3B48F0);
		MH_CreateHook(GAME_AdjustCameraFieldorg, &GAME_AdjustCameraFieldmy, reinterpret_cast<void**>(&GAME_AdjustCameraFieldold));
		MH_EnableHook(GAME_AdjustCameraFieldorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_And", FALSE))
	{
		GAME_Andorg = (GAME_And) ((DWORD) GameDll + 0x3D05F0);
		MH_CreateHook(GAME_Andorg, &GAME_Andmy, reinterpret_cast<void**>(&GAME_Andold));
		MH_EnableHook(GAME_Andorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Asin", FALSE))
	{
		GAME_Asinorg = (GAME_Asin) ((DWORD) GameDll + 0x3B2A70);
		MH_CreateHook(GAME_Asinorg, &GAME_Asinmy, reinterpret_cast<void**>(&GAME_Asinold));
		MH_EnableHook(GAME_Asinorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Atan", FALSE))
	{
		GAME_Atanorg = (GAME_Atan) ((DWORD) GameDll + 0x3B2AF0);
		MH_CreateHook(GAME_Atanorg, &GAME_Atanmy, reinterpret_cast<void**>(&GAME_Atanold));
		MH_EnableHook(GAME_Atanorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Atan2", FALSE))
	{
		GAME_Atan2org = (GAME_Atan2) ((DWORD) GameDll + 0x3B2B10);
		MH_CreateHook(GAME_Atan2org, &GAME_Atan2my, reinterpret_cast<void**>(&GAME_Atan2old));
		MH_EnableHook(GAME_Atan2org);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AttachSoundToUnit", FALSE))
	{
		GAME_AttachSoundToUnitorg = (GAME_AttachSoundToUnit) ((DWORD) GameDll + 0x3CCE50);
		MH_CreateHook(GAME_AttachSoundToUnitorg, &GAME_AttachSoundToUnitmy, reinterpret_cast<void**>(&GAME_AttachSoundToUnitold));
		MH_EnableHook(GAME_AttachSoundToUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AttackMoveKill", FALSE))
	{
		GAME_AttackMoveKillorg = (GAME_AttackMoveKill) ((DWORD) GameDll + 0x2E0A40);
		MH_CreateHook(GAME_AttackMoveKillorg, &GAME_AttackMoveKillmy, reinterpret_cast<void**>(&GAME_AttackMoveKillold));
		MH_EnableHook(GAME_AttackMoveKillorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AttackMoveXY", FALSE))
	{
		GAME_AttackMoveXYorg = (GAME_AttackMoveXY) ((DWORD) GameDll + 0x2DDC10);
		MH_CreateHook(GAME_AttackMoveXYorg, &GAME_AttackMoveXYmy, reinterpret_cast<void**>(&GAME_AttackMoveXYold));
		MH_EnableHook(GAME_AttackMoveXYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CachePlayerHeroData", FALSE))
	{
		GAME_CachePlayerHeroDataorg = (GAME_CachePlayerHeroData) ((DWORD) GameDll + 0x3C9DE0);
		MH_CreateHook(GAME_CachePlayerHeroDataorg, &GAME_CachePlayerHeroDatamy, reinterpret_cast<void**>(&GAME_CachePlayerHeroDataold));
		MH_EnableHook(GAME_CachePlayerHeroDataorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CameraSetSmoothingFactor", FALSE))
	{
		GAME_CameraSetSmoothingFactororg = (GAME_CameraSetSmoothingFactor) ((DWORD) GameDll + 0x3B4BB0);
		MH_CreateHook(GAME_CameraSetSmoothingFactororg, &GAME_CameraSetSmoothingFactormy, reinterpret_cast<void**>(&GAME_CameraSetSmoothingFactorold));
		MH_EnableHook(GAME_CameraSetSmoothingFactororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CameraSetSourceNoise", FALSE))
	{
		GAME_CameraSetSourceNoiseorg = (GAME_CameraSetSourceNoise) ((DWORD) GameDll + 0x3B49E0);
		MH_CreateHook(GAME_CameraSetSourceNoiseorg, &GAME_CameraSetSourceNoisemy, reinterpret_cast<void**>(&GAME_CameraSetSourceNoiseold));
		MH_EnableHook(GAME_CameraSetSourceNoiseorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CameraSetSourceNoiseEx", FALSE))
	{
		GAME_CameraSetSourceNoiseExorg = (GAME_CameraSetSourceNoiseEx) ((DWORD) GameDll + 0x3B4B20);
		MH_CreateHook(GAME_CameraSetSourceNoiseExorg, &GAME_CameraSetSourceNoiseExmy, reinterpret_cast<void**>(&GAME_CameraSetSourceNoiseExold));
		MH_EnableHook(GAME_CameraSetSourceNoiseExorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CameraSetTargetNoise", FALSE))
	{
		GAME_CameraSetTargetNoiseorg = (GAME_CameraSetTargetNoise) ((DWORD) GameDll + 0x3B4930);
		MH_CreateHook(GAME_CameraSetTargetNoiseorg, &GAME_CameraSetTargetNoisemy, reinterpret_cast<void**>(&GAME_CameraSetTargetNoiseold));
		MH_EnableHook(GAME_CameraSetTargetNoiseorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CameraSetTargetNoiseEx", FALSE))
	{
		GAME_CameraSetTargetNoiseExorg = (GAME_CameraSetTargetNoiseEx) ((DWORD) GameDll + 0x3B4A70);
		MH_CreateHook(GAME_CameraSetTargetNoiseExorg, &GAME_CameraSetTargetNoiseExmy, reinterpret_cast<void**>(&GAME_CameraSetTargetNoiseExold));
		MH_EnableHook(GAME_CameraSetTargetNoiseExorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CameraSetupApply", FALSE))
	{
		GAME_CameraSetupApplyorg = (GAME_CameraSetupApply) ((DWORD) GameDll + 0x3CD900);
		MH_CreateHook(GAME_CameraSetupApplyorg, &GAME_CameraSetupApplymy, reinterpret_cast<void**>(&GAME_CameraSetupApplyold));
		MH_EnableHook(GAME_CameraSetupApplyorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CameraSetupApplyForceDuration", FALSE))
	{
		GAME_CameraSetupApplyForceDurationorg = (GAME_CameraSetupApplyForceDuration) ((DWORD) GameDll + 0x3CD960);
		MH_CreateHook(GAME_CameraSetupApplyForceDurationorg, &GAME_CameraSetupApplyForceDurationmy, reinterpret_cast<void**>(&GAME_CameraSetupApplyForceDurationold));
		MH_EnableHook(GAME_CameraSetupApplyForceDurationorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CameraSetupApplyForceDurationWithZ", FALSE))
	{
		GAME_CameraSetupApplyForceDurationWithZorg = (GAME_CameraSetupApplyForceDurationWithZ) ((DWORD) GameDll + 0x3CD990);
		MH_CreateHook(GAME_CameraSetupApplyForceDurationWithZorg, &GAME_CameraSetupApplyForceDurationWithZmy, reinterpret_cast<void**>(&GAME_CameraSetupApplyForceDurationWithZold));
		MH_EnableHook(GAME_CameraSetupApplyForceDurationWithZorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CameraSetupApplyWithZ", FALSE))
	{
		GAME_CameraSetupApplyWithZorg = (GAME_CameraSetupApplyWithZ) ((DWORD) GameDll + 0x3CD930);
		MH_CreateHook(GAME_CameraSetupApplyWithZorg, &GAME_CameraSetupApplyWithZmy, reinterpret_cast<void**>(&GAME_CameraSetupApplyWithZold));
		MH_EnableHook(GAME_CameraSetupApplyWithZorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CameraSetupGetDestPositionLoc", FALSE))
	{
		GAME_CameraSetupGetDestPositionLocorg = (GAME_CameraSetupGetDestPositionLoc) ((DWORD) GameDll + 0x3D3E40);
		MH_CreateHook(GAME_CameraSetupGetDestPositionLocorg, &GAME_CameraSetupGetDestPositionLocmy, reinterpret_cast<void**>(&GAME_CameraSetupGetDestPositionLocold));
		MH_EnableHook(GAME_CameraSetupGetDestPositionLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CameraSetupGetDestPositionX", FALSE))
	{
		GAME_CameraSetupGetDestPositionXorg = (GAME_CameraSetupGetDestPositionX) ((DWORD) GameDll + 0x3CD8C0);
		MH_CreateHook(GAME_CameraSetupGetDestPositionXorg, &GAME_CameraSetupGetDestPositionXmy, reinterpret_cast<void**>(&GAME_CameraSetupGetDestPositionXold));
		MH_EnableHook(GAME_CameraSetupGetDestPositionXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CameraSetupGetDestPositionY", FALSE))
	{
		GAME_CameraSetupGetDestPositionYorg = (GAME_CameraSetupGetDestPositionY) ((DWORD) GameDll + 0x3CD8E0);
		MH_CreateHook(GAME_CameraSetupGetDestPositionYorg, &GAME_CameraSetupGetDestPositionYmy, reinterpret_cast<void**>(&GAME_CameraSetupGetDestPositionYold));
		MH_EnableHook(GAME_CameraSetupGetDestPositionYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CameraSetupGetField", FALSE))
	{
		GAME_CameraSetupGetFieldorg = (GAME_CameraSetupGetField) ((DWORD) GameDll + 0x3CD830);
		MH_CreateHook(GAME_CameraSetupGetFieldorg, &GAME_CameraSetupGetFieldmy, reinterpret_cast<void**>(&GAME_CameraSetupGetFieldold));
		MH_EnableHook(GAME_CameraSetupGetFieldorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CameraSetupSetDestPosition", FALSE))
	{
		GAME_CameraSetupSetDestPositionorg = (GAME_CameraSetupSetDestPosition) ((DWORD) GameDll + 0x3CD870);
		MH_CreateHook(GAME_CameraSetupSetDestPositionorg, &GAME_CameraSetupSetDestPositionmy, reinterpret_cast<void**>(&GAME_CameraSetupSetDestPositionold));
		MH_EnableHook(GAME_CameraSetupSetDestPositionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CameraSetupSetField", FALSE))
	{
		GAME_CameraSetupSetFieldorg = (GAME_CameraSetupSetField) ((DWORD) GameDll + 0x3CD800);
		MH_CreateHook(GAME_CameraSetupSetFieldorg, &GAME_CameraSetupSetFieldmy, reinterpret_cast<void**>(&GAME_CameraSetupSetFieldold));
		MH_EnableHook(GAME_CameraSetupSetFieldorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CaptainAtGoal", FALSE))
	{
		GAME_CaptainAtGoalorg = (GAME_CaptainAtGoal) ((DWORD) GameDll + 0x2DD930);
		MH_CreateHook(GAME_CaptainAtGoalorg, &GAME_CaptainAtGoalmy, reinterpret_cast<void**>(&GAME_CaptainAtGoalold));
		MH_EnableHook(GAME_CaptainAtGoalorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CaptainAttack", FALSE))
	{
		GAME_CaptainAttackorg = (GAME_CaptainAttack) ((DWORD) GameDll + 0x2DD700);
		MH_CreateHook(GAME_CaptainAttackorg, &GAME_CaptainAttackmy, reinterpret_cast<void**>(&GAME_CaptainAttackold));
		MH_EnableHook(GAME_CaptainAttackorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CaptainGoHome", FALSE))
	{
		GAME_CaptainGoHomeorg = (GAME_CaptainGoHome) ((DWORD) GameDll + 0x2DD800);
		MH_CreateHook(GAME_CaptainGoHomeorg, &GAME_CaptainGoHomemy, reinterpret_cast<void**>(&GAME_CaptainGoHomeold));
		MH_EnableHook(GAME_CaptainGoHomeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CaptainGroupSize", FALSE))
	{
		GAME_CaptainGroupSizeorg = (GAME_CaptainGroupSize) ((DWORD) GameDll + 0x2DDB90);
		MH_CreateHook(GAME_CaptainGroupSizeorg, &GAME_CaptainGroupSizemy, reinterpret_cast<void**>(&GAME_CaptainGroupSizeold));
		MH_EnableHook(GAME_CaptainGroupSizeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CaptainInCombat", FALSE))
	{
		GAME_CaptainInCombatorg = (GAME_CaptainInCombat) ((DWORD) GameDll + 0x2DD8A0);
		MH_CreateHook(GAME_CaptainInCombatorg, &GAME_CaptainInCombatmy, reinterpret_cast<void**>(&GAME_CaptainInCombatold));
		MH_EnableHook(GAME_CaptainInCombatorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CaptainIsEmpty", FALSE))
	{
		GAME_CaptainIsEmptyorg = (GAME_CaptainIsEmpty) ((DWORD) GameDll + 0x2DDB50);
		MH_CreateHook(GAME_CaptainIsEmptyorg, &GAME_CaptainIsEmptymy, reinterpret_cast<void**>(&GAME_CaptainIsEmptyold));
		MH_EnableHook(GAME_CaptainIsEmptyorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CaptainIsFull", FALSE))
	{
		GAME_CaptainIsFullorg = (GAME_CaptainIsFull) ((DWORD) GameDll + 0x2DDB10);
		MH_CreateHook(GAME_CaptainIsFullorg, &GAME_CaptainIsFullmy, reinterpret_cast<void**>(&GAME_CaptainIsFullold));
		MH_EnableHook(GAME_CaptainIsFullorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CaptainIsHome", FALSE))
	{
		GAME_CaptainIsHomeorg = (GAME_CaptainIsHome) ((DWORD) GameDll + 0x2DD870);
		MH_CreateHook(GAME_CaptainIsHomeorg, &GAME_CaptainIsHomemy, reinterpret_cast<void**>(&GAME_CaptainIsHomeold));
		MH_EnableHook(GAME_CaptainIsHomeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CaptainReadiness", FALSE))
	{
		GAME_CaptainReadinessorg = (GAME_CaptainReadiness) ((DWORD) GameDll + 0x2DDA40);
		MH_CreateHook(GAME_CaptainReadinessorg, &GAME_CaptainReadinessmy, reinterpret_cast<void**>(&GAME_CaptainReadinessold));
		MH_EnableHook(GAME_CaptainReadinessorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CaptainReadinessHP", FALSE))
	{
		GAME_CaptainReadinessHPorg = (GAME_CaptainReadinessHP) ((DWORD) GameDll + 0x2DDA90);
		MH_CreateHook(GAME_CaptainReadinessHPorg, &GAME_CaptainReadinessHPmy, reinterpret_cast<void**>(&GAME_CaptainReadinessHPold));
		MH_EnableHook(GAME_CaptainReadinessHPorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CaptainReadinessMa", FALSE))
	{
		GAME_CaptainReadinessMaorg = (GAME_CaptainReadinessMa) ((DWORD) GameDll + 0x2DDAD0);
		MH_CreateHook(GAME_CaptainReadinessMaorg, &GAME_CaptainReadinessMamy, reinterpret_cast<void**>(&GAME_CaptainReadinessMaold));
		MH_EnableHook(GAME_CaptainReadinessMaorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CaptainRetreating", FALSE))
	{
		GAME_CaptainRetreatingorg = (GAME_CaptainRetreating) ((DWORD) GameDll + 0x2DD830);
		MH_CreateHook(GAME_CaptainRetreatingorg, &GAME_CaptainRetreatingmy, reinterpret_cast<void**>(&GAME_CaptainRetreatingold));
		MH_EnableHook(GAME_CaptainRetreatingorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CaptainVsPlayer", FALSE))
	{
		GAME_CaptainVsPlayerorg = (GAME_CaptainVsPlayer) ((DWORD) GameDll + 0x2E2C80);
		MH_CreateHook(GAME_CaptainVsPlayerorg, &GAME_CaptainVsPlayermy, reinterpret_cast<void**>(&GAME_CaptainVsPlayerold));
		MH_EnableHook(GAME_CaptainVsPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CaptainVsUnits", FALSE))
	{
		GAME_CaptainVsUnitsorg = (GAME_CaptainVsUnits) ((DWORD) GameDll + 0x2E2BF0);
		MH_CreateHook(GAME_CaptainVsUnitsorg, &GAME_CaptainVsUnitsmy, reinterpret_cast<void**>(&GAME_CaptainVsUnitsold));
		MH_EnableHook(GAME_CaptainVsUnitsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ChangeLevel", FALSE))
	{
		GAME_ChangeLevelorg = (GAME_ChangeLevel) ((DWORD) GameDll + 0x3BBC30);
		MH_CreateHook(GAME_ChangeLevelorg, &GAME_ChangeLevelmy, reinterpret_cast<void**>(&GAME_ChangeLevelold));
		MH_EnableHook(GAME_ChangeLevelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Cheat", FALSE))
	{
		GAME_Cheatorg = (GAME_Cheat) ((DWORD) GameDll + 0x3B3BC0);
		MH_CreateHook(GAME_Cheatorg, &GAME_Cheatmy, reinterpret_cast<void**>(&GAME_Cheatold));
		MH_EnableHook(GAME_Cheatorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ChooseRandomCreep", FALSE))
	{
		GAME_ChooseRandomCreeporg = (GAME_ChooseRandomCreep) ((DWORD) GameDll + 0x3B3660);
		MH_CreateHook(GAME_ChooseRandomCreeporg, &GAME_ChooseRandomCreepmy, reinterpret_cast<void**>(&GAME_ChooseRandomCreepold));
		MH_EnableHook(GAME_ChooseRandomCreeporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ChooseRandomItem", FALSE))
	{
		GAME_ChooseRandomItemorg = (GAME_ChooseRandomItem) ((DWORD) GameDll + 0x3B3690);
		MH_CreateHook(GAME_ChooseRandomItemorg, &GAME_ChooseRandomItemmy, reinterpret_cast<void**>(&GAME_ChooseRandomItemold));
		MH_EnableHook(GAME_ChooseRandomItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ChooseRandomItemEx", FALSE))
	{
		GAME_ChooseRandomItemExorg = (GAME_ChooseRandomItemEx) ((DWORD) GameDll + 0x3B36B0);
		MH_CreateHook(GAME_ChooseRandomItemExorg, &GAME_ChooseRandomItemExmy, reinterpret_cast<void**>(&GAME_ChooseRandomItemExold));
		MH_EnableHook(GAME_ChooseRandomItemExorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ChooseRandomNPBuilding", FALSE))
	{
		GAME_ChooseRandomNPBuildingorg = (GAME_ChooseRandomNPBuilding) ((DWORD) GameDll + 0x3B3680);
		MH_CreateHook(GAME_ChooseRandomNPBuildingorg, &GAME_ChooseRandomNPBuildingmy, reinterpret_cast<void**>(&GAME_ChooseRandomNPBuildingold));
		MH_EnableHook(GAME_ChooseRandomNPBuildingorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ClearCaptainTargets", FALSE))
	{
		GAME_ClearCaptainTargetsorg = (GAME_ClearCaptainTargets) ((DWORD) GameDll + 0x2DD6C0);
		MH_CreateHook(GAME_ClearCaptainTargetsorg, &GAME_ClearCaptainTargetsmy, reinterpret_cast<void**>(&GAME_ClearCaptainTargetsold));
		MH_EnableHook(GAME_ClearCaptainTargetsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ClearHarvestAI", FALSE))
	{
		GAME_ClearHarvestAIorg = (GAME_ClearHarvestAI) ((DWORD) GameDll + 0x2DD5B0);
		MH_CreateHook(GAME_ClearHarvestAIorg, &GAME_ClearHarvestAImy, reinterpret_cast<void**>(&GAME_ClearHarvestAIold));
		MH_EnableHook(GAME_ClearHarvestAIorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ClearMapMusic", FALSE))
	{
		GAME_ClearMapMusicorg = (GAME_ClearMapMusic) ((DWORD) GameDll + 0x3B3D20);
		MH_CreateHook(GAME_ClearMapMusicorg, &GAME_ClearMapMusicmy, reinterpret_cast<void**>(&GAME_ClearMapMusicold));
		MH_EnableHook(GAME_ClearMapMusicorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ClearSelection", FALSE))
	{
		GAME_ClearSelectionorg = (GAME_ClearSelection) ((DWORD) GameDll + 0x3BBAA0);
		MH_CreateHook(GAME_ClearSelectionorg, &GAME_ClearSelectionmy, reinterpret_cast<void**>(&GAME_ClearSelectionold));
		MH_EnableHook(GAME_ClearSelectionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ClearStackedSound", FALSE))
	{
		GAME_ClearStackedSoundorg = (GAME_ClearStackedSound) ((DWORD) GameDll + 0x3B3C80);
		MH_CreateHook(GAME_ClearStackedSoundorg, &GAME_ClearStackedSoundmy, reinterpret_cast<void**>(&GAME_ClearStackedSoundold));
		MH_EnableHook(GAME_ClearStackedSoundorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ClearStackedSoundRect", FALSE))
	{
		GAME_ClearStackedSoundRectorg = (GAME_ClearStackedSoundRect) ((DWORD) GameDll + 0x3CCB20);
		MH_CreateHook(GAME_ClearStackedSoundRectorg, &GAME_ClearStackedSoundRectmy, reinterpret_cast<void**>(&GAME_ClearStackedSoundRectold));
		MH_EnableHook(GAME_ClearStackedSoundRectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ClearTextMessages", FALSE))
	{
		GAME_ClearTextMessagesorg = (GAME_ClearTextMessages) ((DWORD) GameDll + 0x3B4E60);
		MH_CreateHook(GAME_ClearTextMessagesorg, &GAME_ClearTextMessagesmy, reinterpret_cast<void**>(&GAME_ClearTextMessagesold));
		MH_EnableHook(GAME_ClearTextMessagesorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CommandAI", FALSE))
	{
		GAME_CommandAIorg = (GAME_CommandAI) ((DWORD) GameDll + 0x3CB7A0);
		MH_CreateHook(GAME_CommandAIorg, &GAME_CommandAImy, reinterpret_cast<void**>(&GAME_CommandAIold));
		MH_EnableHook(GAME_CommandAIorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CommandsWaiting", FALSE))
	{
		GAME_CommandsWaitingorg = (GAME_CommandsWaiting) ((DWORD) GameDll + 0x2DCDD0);
		MH_CreateHook(GAME_CommandsWaitingorg, &GAME_CommandsWaitingmy, reinterpret_cast<void**>(&GAME_CommandsWaitingold));
		MH_EnableHook(GAME_CommandsWaitingorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Condition", FALSE))
	{
		GAME_Conditionorg = (GAME_Condition) ((DWORD) GameDll + 0x3BB0A0);
		MH_CreateHook(GAME_Conditionorg, &GAME_Conditionmy, reinterpret_cast<void**>(&GAME_Conditionold));
		MH_EnableHook(GAME_Conditionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertAIDifficulty", FALSE))
	{
		GAME_ConvertAIDifficultyorg = (GAME_ConvertAIDifficulty) ((DWORD) GameDll + 0x3B2690);
		MH_CreateHook(GAME_ConvertAIDifficultyorg, &GAME_ConvertAIDifficultymy, reinterpret_cast<void**>(&GAME_ConvertAIDifficultyold));
		MH_EnableHook(GAME_ConvertAIDifficultyorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertAllianceType", FALSE))
	{
		GAME_ConvertAllianceTypeorg = (GAME_ConvertAllianceType) ((DWORD) GameDll + 0x3B2610);
		MH_CreateHook(GAME_ConvertAllianceTypeorg, &GAME_ConvertAllianceTypemy, reinterpret_cast<void**>(&GAME_ConvertAllianceTypeold));
		MH_EnableHook(GAME_ConvertAllianceTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertAttackType", FALSE))
	{
		GAME_ConvertAttackTypeorg = (GAME_ConvertAttackType) ((DWORD) GameDll + 0x3B2870);
		MH_CreateHook(GAME_ConvertAttackTypeorg, &GAME_ConvertAttackTypemy, reinterpret_cast<void**>(&GAME_ConvertAttackTypeold));
		MH_EnableHook(GAME_ConvertAttackTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertBlendMode", FALSE))
	{
		GAME_ConvertBlendModeorg = (GAME_ConvertBlendMode) ((DWORD) GameDll + 0x3B2810);
		MH_CreateHook(GAME_ConvertBlendModeorg, &GAME_ConvertBlendModemy, reinterpret_cast<void**>(&GAME_ConvertBlendModeold));
		MH_EnableHook(GAME_ConvertBlendModeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertCameraField", FALSE))
	{
		GAME_ConvertCameraFieldorg = (GAME_ConvertCameraField) ((DWORD) GameDll + 0x3B27F0);
		MH_CreateHook(GAME_ConvertCameraFieldorg, &GAME_ConvertCameraFieldmy, reinterpret_cast<void**>(&GAME_ConvertCameraFieldold));
		MH_EnableHook(GAME_ConvertCameraFieldorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertDamageType", FALSE))
	{
		GAME_ConvertDamageTypeorg = (GAME_ConvertDamageType) ((DWORD) GameDll + 0x3B2880);
		MH_CreateHook(GAME_ConvertDamageTypeorg, &GAME_ConvertDamageTypemy, reinterpret_cast<void**>(&GAME_ConvertDamageTypeold));
		MH_EnableHook(GAME_ConvertDamageTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertDialogEvent", FALSE))
	{
		GAME_ConvertDialogEventorg = (GAME_ConvertDialogEvent) ((DWORD) GameDll + 0x3B26F0);
		MH_CreateHook(GAME_ConvertDialogEventorg, &GAME_ConvertDialogEventmy, reinterpret_cast<void**>(&GAME_ConvertDialogEventold));
		MH_EnableHook(GAME_ConvertDialogEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertEffectType", FALSE))
	{
		GAME_ConvertEffectTypeorg = (GAME_ConvertEffectType) ((DWORD) GameDll + 0x3B2840);
		MH_CreateHook(GAME_ConvertEffectTypeorg, &GAME_ConvertEffectTypemy, reinterpret_cast<void**>(&GAME_ConvertEffectTypeold));
		MH_EnableHook(GAME_ConvertEffectTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertFGameState", FALSE))
	{
		GAME_ConvertFGameStateorg = (GAME_ConvertFGameState) ((DWORD) GameDll + 0x3B2640);
		MH_CreateHook(GAME_ConvertFGameStateorg, &GAME_ConvertFGameStatemy, reinterpret_cast<void**>(&GAME_ConvertFGameStateold));
		MH_EnableHook(GAME_ConvertFGameStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertFogState", FALSE))
	{
		GAME_ConvertFogStateorg = (GAME_ConvertFogState) ((DWORD) GameDll + 0x3B2830);
		MH_CreateHook(GAME_ConvertFogStateorg, &GAME_ConvertFogStatemy, reinterpret_cast<void**>(&GAME_ConvertFogStateold));
		MH_EnableHook(GAME_ConvertFogStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertGameDifficulty", FALSE))
	{
		GAME_ConvertGameDifficultyorg = (GAME_ConvertGameDifficulty) ((DWORD) GameDll + 0x3B2750);
		MH_CreateHook(GAME_ConvertGameDifficultyorg, &GAME_ConvertGameDifficultymy, reinterpret_cast<void**>(&GAME_ConvertGameDifficultyold));
		MH_EnableHook(GAME_ConvertGameDifficultyorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertGameEvent", FALSE))
	{
		GAME_ConvertGameEventorg = (GAME_ConvertGameEvent) ((DWORD) GameDll + 0x3B26A0);
		MH_CreateHook(GAME_ConvertGameEventorg, &GAME_ConvertGameEventmy, reinterpret_cast<void**>(&GAME_ConvertGameEventold));
		MH_EnableHook(GAME_ConvertGameEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertGameSpeed", FALSE))
	{
		GAME_ConvertGameSpeedorg = (GAME_ConvertGameSpeed) ((DWORD) GameDll + 0x3B2720);
		MH_CreateHook(GAME_ConvertGameSpeedorg, &GAME_ConvertGameSpeedmy, reinterpret_cast<void**>(&GAME_ConvertGameSpeedold));
		MH_EnableHook(GAME_ConvertGameSpeedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertGameType", FALSE))
	{
		GAME_ConvertGameTypeorg = (GAME_ConvertGameType) ((DWORD) GameDll + 0x3B2760);
		MH_CreateHook(GAME_ConvertGameTypeorg, &GAME_ConvertGameTypemy, reinterpret_cast<void**>(&GAME_ConvertGameTypeold));
		MH_EnableHook(GAME_ConvertGameTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertIGameState", FALSE))
	{
		GAME_ConvertIGameStateorg = (GAME_ConvertIGameState) ((DWORD) GameDll + 0x3B2630);
		MH_CreateHook(GAME_ConvertIGameStateorg, &GAME_ConvertIGameStatemy, reinterpret_cast<void**>(&GAME_ConvertIGameStateold));
		MH_EnableHook(GAME_ConvertIGameStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertItemType", FALSE))
	{
		GAME_ConvertItemTypeorg = (GAME_ConvertItemType) ((DWORD) GameDll + 0x3B2860);
		MH_CreateHook(GAME_ConvertItemTypeorg, &GAME_ConvertItemTypemy, reinterpret_cast<void**>(&GAME_ConvertItemTypeold));
		MH_EnableHook(GAME_ConvertItemTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertLimitOp", FALSE))
	{
		GAME_ConvertLimitOporg = (GAME_ConvertLimitOp) ((DWORD) GameDll + 0x3B2700);
		MH_CreateHook(GAME_ConvertLimitOporg, &GAME_ConvertLimitOpmy, reinterpret_cast<void**>(&GAME_ConvertLimitOpold));
		MH_EnableHook(GAME_ConvertLimitOporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertMapControl", FALSE))
	{
		GAME_ConvertMapControlorg = (GAME_ConvertMapControl) ((DWORD) GameDll + 0x3B27B0);
		MH_CreateHook(GAME_ConvertMapControlorg, &GAME_ConvertMapControlmy, reinterpret_cast<void**>(&GAME_ConvertMapControlold));
		MH_EnableHook(GAME_ConvertMapControlorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertMapDensity", FALSE))
	{
		GAME_ConvertMapDensityorg = (GAME_ConvertMapDensity) ((DWORD) GameDll + 0x3B27A0);
		MH_CreateHook(GAME_ConvertMapDensityorg, &GAME_ConvertMapDensitymy, reinterpret_cast<void**>(&GAME_ConvertMapDensityold));
		MH_EnableHook(GAME_ConvertMapDensityorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertMapFlag", FALSE))
	{
		GAME_ConvertMapFlagorg = (GAME_ConvertMapFlag) ((DWORD) GameDll + 0x3B2770);
		MH_CreateHook(GAME_ConvertMapFlagorg, &GAME_ConvertMapFlagmy, reinterpret_cast<void**>(&GAME_ConvertMapFlagold));
		MH_EnableHook(GAME_ConvertMapFlagorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertMapSetting", FALSE))
	{
		GAME_ConvertMapSettingorg = (GAME_ConvertMapSetting) ((DWORD) GameDll + 0x3B2790);
		MH_CreateHook(GAME_ConvertMapSettingorg, &GAME_ConvertMapSettingmy, reinterpret_cast<void**>(&GAME_ConvertMapSettingold));
		MH_EnableHook(GAME_ConvertMapSettingorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertMapVisibility", FALSE))
	{
		GAME_ConvertMapVisibilityorg = (GAME_ConvertMapVisibility) ((DWORD) GameDll + 0x3B2780);
		MH_CreateHook(GAME_ConvertMapVisibilityorg, &GAME_ConvertMapVisibilitymy, reinterpret_cast<void**>(&GAME_ConvertMapVisibilityold));
		MH_EnableHook(GAME_ConvertMapVisibilityorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertPathingType", FALSE))
	{
		GAME_ConvertPathingTypeorg = (GAME_ConvertPathingType) ((DWORD) GameDll + 0x3B28B0);
		MH_CreateHook(GAME_ConvertPathingTypeorg, &GAME_ConvertPathingTypemy, reinterpret_cast<void**>(&GAME_ConvertPathingTypeold));
		MH_EnableHook(GAME_ConvertPathingTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertPlacement", FALSE))
	{
		GAME_ConvertPlacementorg = (GAME_ConvertPlacement) ((DWORD) GameDll + 0x3B2730);
		MH_CreateHook(GAME_ConvertPlacementorg, &GAME_ConvertPlacementmy, reinterpret_cast<void**>(&GAME_ConvertPlacementold));
		MH_EnableHook(GAME_ConvertPlacementorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertPlayerColor", FALSE))
	{
		GAME_ConvertPlayerColororg = (GAME_ConvertPlayerColor) ((DWORD) GameDll + 0x3B27C0);
		MH_CreateHook(GAME_ConvertPlayerColororg, &GAME_ConvertPlayerColormy, reinterpret_cast<void**>(&GAME_ConvertPlayerColorold));
		MH_EnableHook(GAME_ConvertPlayerColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertPlayerEvent", FALSE))
	{
		GAME_ConvertPlayerEventorg = (GAME_ConvertPlayerEvent) ((DWORD) GameDll + 0x3B26B0);
		MH_CreateHook(GAME_ConvertPlayerEventorg, &GAME_ConvertPlayerEventmy, reinterpret_cast<void**>(&GAME_ConvertPlayerEventold));
		MH_EnableHook(GAME_ConvertPlayerEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertPlayerGameResult", FALSE))
	{
		GAME_ConvertPlayerGameResultorg = (GAME_ConvertPlayerGameResult) ((DWORD) GameDll + 0x3B2670);
		MH_CreateHook(GAME_ConvertPlayerGameResultorg, &GAME_ConvertPlayerGameResultmy, reinterpret_cast<void**>(&GAME_ConvertPlayerGameResultold));
		MH_EnableHook(GAME_ConvertPlayerGameResultorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertPlayerScore", FALSE))
	{
		GAME_ConvertPlayerScoreorg = (GAME_ConvertPlayerScore) ((DWORD) GameDll + 0x3B2660);
		MH_CreateHook(GAME_ConvertPlayerScoreorg, &GAME_ConvertPlayerScoremy, reinterpret_cast<void**>(&GAME_ConvertPlayerScoreold));
		MH_EnableHook(GAME_ConvertPlayerScoreorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertPlayerSlotState", FALSE))
	{
		GAME_ConvertPlayerSlotStateorg = (GAME_ConvertPlayerSlotState) ((DWORD) GameDll + 0x3B27D0);
		MH_CreateHook(GAME_ConvertPlayerSlotStateorg, &GAME_ConvertPlayerSlotStatemy, reinterpret_cast<void**>(&GAME_ConvertPlayerSlotStateold));
		MH_EnableHook(GAME_ConvertPlayerSlotStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertPlayerState", FALSE))
	{
		GAME_ConvertPlayerStateorg = (GAME_ConvertPlayerState) ((DWORD) GameDll + 0x3B2650);
		MH_CreateHook(GAME_ConvertPlayerStateorg, &GAME_ConvertPlayerStatemy, reinterpret_cast<void**>(&GAME_ConvertPlayerStateold));
		MH_EnableHook(GAME_ConvertPlayerStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertPlayerUnitEvent", FALSE))
	{
		GAME_ConvertPlayerUnitEventorg = (GAME_ConvertPlayerUnitEvent) ((DWORD) GameDll + 0x3B26C0);
		MH_CreateHook(GAME_ConvertPlayerUnitEventorg, &GAME_ConvertPlayerUnitEventmy, reinterpret_cast<void**>(&GAME_ConvertPlayerUnitEventold));
		MH_EnableHook(GAME_ConvertPlayerUnitEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertRace", FALSE))
	{
		GAME_ConvertRaceorg = (GAME_ConvertRace) ((DWORD) GameDll + 0x3B2600);
		MH_CreateHook(GAME_ConvertRaceorg, &GAME_ConvertRacemy, reinterpret_cast<void**>(&GAME_ConvertRaceold));
		MH_EnableHook(GAME_ConvertRaceorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertRacePref", FALSE))
	{
		GAME_ConvertRacePreforg = (GAME_ConvertRacePref) ((DWORD) GameDll + 0x3B2620);
		MH_CreateHook(GAME_ConvertRacePreforg, &GAME_ConvertRacePrefmy, reinterpret_cast<void**>(&GAME_ConvertRacePrefold));
		MH_EnableHook(GAME_ConvertRacePreforg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertRarityControl", FALSE))
	{
		GAME_ConvertRarityControlorg = (GAME_ConvertRarityControl) ((DWORD) GameDll + 0x3B2800);
		MH_CreateHook(GAME_ConvertRarityControlorg, &GAME_ConvertRarityControlmy, reinterpret_cast<void**>(&GAME_ConvertRarityControlold));
		MH_EnableHook(GAME_ConvertRarityControlorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertSoundType", FALSE))
	{
		GAME_ConvertSoundTypeorg = (GAME_ConvertSoundType) ((DWORD) GameDll + 0x3B28A0);
		MH_CreateHook(GAME_ConvertSoundTypeorg, &GAME_ConvertSoundTypemy, reinterpret_cast<void**>(&GAME_ConvertSoundTypeold));
		MH_EnableHook(GAME_ConvertSoundTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertStartLocPrio", FALSE))
	{
		GAME_ConvertStartLocPrioorg = (GAME_ConvertStartLocPrio) ((DWORD) GameDll + 0x3B2740);
		MH_CreateHook(GAME_ConvertStartLocPrioorg, &GAME_ConvertStartLocPriomy, reinterpret_cast<void**>(&GAME_ConvertStartLocPrioold));
		MH_EnableHook(GAME_ConvertStartLocPrioorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertTexMapFlags", FALSE))
	{
		GAME_ConvertTexMapFlagsorg = (GAME_ConvertTexMapFlags) ((DWORD) GameDll + 0x3B2820);
		MH_CreateHook(GAME_ConvertTexMapFlagsorg, &GAME_ConvertTexMapFlagsmy, reinterpret_cast<void**>(&GAME_ConvertTexMapFlagsold));
		MH_EnableHook(GAME_ConvertTexMapFlagsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertUnitEvent", FALSE))
	{
		GAME_ConvertUnitEventorg = (GAME_ConvertUnitEvent) ((DWORD) GameDll + 0x3B26D0);
		MH_CreateHook(GAME_ConvertUnitEventorg, &GAME_ConvertUnitEventmy, reinterpret_cast<void**>(&GAME_ConvertUnitEventold));
		MH_EnableHook(GAME_ConvertUnitEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertUnitState", FALSE))
	{
		GAME_ConvertUnitStateorg = (GAME_ConvertUnitState) ((DWORD) GameDll + 0x3B2680);
		MH_CreateHook(GAME_ConvertUnitStateorg, &GAME_ConvertUnitStatemy, reinterpret_cast<void**>(&GAME_ConvertUnitStateold));
		MH_EnableHook(GAME_ConvertUnitStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertUnitType", FALSE))
	{
		GAME_ConvertUnitTypeorg = (GAME_ConvertUnitType) ((DWORD) GameDll + 0x3B2710);
		MH_CreateHook(GAME_ConvertUnitTypeorg, &GAME_ConvertUnitTypemy, reinterpret_cast<void**>(&GAME_ConvertUnitTypeold));
		MH_EnableHook(GAME_ConvertUnitTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertUnits", FALSE))
	{
		GAME_ConvertUnitsorg = (GAME_ConvertUnits) ((DWORD) GameDll + 0x2DD2E0);
		MH_CreateHook(GAME_ConvertUnitsorg, &GAME_ConvertUnitsmy, reinterpret_cast<void**>(&GAME_ConvertUnitsold));
		MH_EnableHook(GAME_ConvertUnitsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertVersion", FALSE))
	{
		GAME_ConvertVersionorg = (GAME_ConvertVersion) ((DWORD) GameDll + 0x3B2850);
		MH_CreateHook(GAME_ConvertVersionorg, &GAME_ConvertVersionmy, reinterpret_cast<void**>(&GAME_ConvertVersionold));
		MH_EnableHook(GAME_ConvertVersionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertVolumeGroup", FALSE))
	{
		GAME_ConvertVolumeGrouporg = (GAME_ConvertVolumeGroup) ((DWORD) GameDll + 0x3B27E0);
		MH_CreateHook(GAME_ConvertVolumeGrouporg, &GAME_ConvertVolumeGroupmy, reinterpret_cast<void**>(&GAME_ConvertVolumeGroupold));
		MH_EnableHook(GAME_ConvertVolumeGrouporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertWeaponType", FALSE))
	{
		GAME_ConvertWeaponTypeorg = (GAME_ConvertWeaponType) ((DWORD) GameDll + 0x3B2890);
		MH_CreateHook(GAME_ConvertWeaponTypeorg, &GAME_ConvertWeaponTypemy, reinterpret_cast<void**>(&GAME_ConvertWeaponTypeold));
		MH_EnableHook(GAME_ConvertWeaponTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ConvertWidgetEvent", FALSE))
	{
		GAME_ConvertWidgetEventorg = (GAME_ConvertWidgetEvent) ((DWORD) GameDll + 0x3B26E0);
		MH_CreateHook(GAME_ConvertWidgetEventorg, &GAME_ConvertWidgetEventmy, reinterpret_cast<void**>(&GAME_ConvertWidgetEventold));
		MH_EnableHook(GAME_ConvertWidgetEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CopySaveGame", FALSE))
	{
		GAME_CopySaveGameorg = (GAME_CopySaveGame) ((DWORD) GameDll + 0x3BC180);
		MH_CreateHook(GAME_CopySaveGameorg, &GAME_CopySaveGamemy, reinterpret_cast<void**>(&GAME_CopySaveGameold));
		MH_EnableHook(GAME_CopySaveGameorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Cos", FALSE))
	{
		GAME_Cosorg = (GAME_Cos) ((DWORD) GameDll + 0x3B2A30);
		MH_CreateHook(GAME_Cosorg, &GAME_Cosmy, reinterpret_cast<void**>(&GAME_Cosold));
		MH_EnableHook(GAME_Cosorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateBlightedGoldmine", FALSE))
	{
		GAME_CreateBlightedGoldmineorg = (GAME_CreateBlightedGoldmine) ((DWORD) GameDll + 0x3CD630);
		MH_CreateHook(GAME_CreateBlightedGoldmineorg, &GAME_CreateBlightedGoldminemy, reinterpret_cast<void**>(&GAME_CreateBlightedGoldmineold));
		MH_EnableHook(GAME_CreateBlightedGoldmineorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateCameraSetup", FALSE))
	{
		GAME_CreateCameraSetuporg = (GAME_CreateCameraSetup) ((DWORD) GameDll + 0x3D3D40);
		MH_CreateHook(GAME_CreateCameraSetuporg, &GAME_CreateCameraSetupmy, reinterpret_cast<void**>(&GAME_CreateCameraSetupold));
		MH_EnableHook(GAME_CreateCameraSetuporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateCaptains", FALSE))
	{
		GAME_CreateCaptainsorg = (GAME_CreateCaptains) ((DWORD) GameDll + 0x2DD960);
		MH_CreateHook(GAME_CreateCaptainsorg, &GAME_CreateCaptainsmy, reinterpret_cast<void**>(&GAME_CreateCaptainsold));
		MH_EnableHook(GAME_CreateCaptainsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateCorpse", FALSE))
	{
		GAME_CreateCorpseorg = (GAME_CreateCorpse) ((DWORD) GameDll + 0x3C5350);
		MH_CreateHook(GAME_CreateCorpseorg, &GAME_CreateCorpsemy, reinterpret_cast<void**>(&GAME_CreateCorpseold));
		MH_EnableHook(GAME_CreateCorpseorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateDeadDestructable", FALSE))
	{
		GAME_CreateDeadDestructableorg = (GAME_CreateDeadDestructable) ((DWORD) GameDll + 0x3BB840);
		MH_CreateHook(GAME_CreateDeadDestructableorg, &GAME_CreateDeadDestructablemy, reinterpret_cast<void**>(&GAME_CreateDeadDestructableold));
		MH_EnableHook(GAME_CreateDeadDestructableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateDeadDestructableZ", FALSE))
	{
		GAME_CreateDeadDestructableZorg = (GAME_CreateDeadDestructableZ) ((DWORD) GameDll + 0x3BB890);
		MH_CreateHook(GAME_CreateDeadDestructableZorg, &GAME_CreateDeadDestructableZmy, reinterpret_cast<void**>(&GAME_CreateDeadDestructableZold));
		MH_EnableHook(GAME_CreateDeadDestructableZorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateDefeatCondition", FALSE))
	{
		GAME_CreateDefeatConditionorg = (GAME_CreateDefeatCondition) ((DWORD) GameDll + 0x3BC9E0);
		MH_CreateHook(GAME_CreateDefeatConditionorg, &GAME_CreateDefeatConditionmy, reinterpret_cast<void**>(&GAME_CreateDefeatConditionold));
		MH_EnableHook(GAME_CreateDefeatConditionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateDestructable", FALSE))
	{
		GAME_CreateDestructableorg = (GAME_CreateDestructable) ((DWORD) GameDll + 0x3BB790);
		MH_CreateHook(GAME_CreateDestructableorg, &GAME_CreateDestructablemy, reinterpret_cast<void**>(&GAME_CreateDestructableold));
		MH_EnableHook(GAME_CreateDestructableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateDestructableZ", FALSE))
	{
		GAME_CreateDestructableZorg = (GAME_CreateDestructableZ) ((DWORD) GameDll + 0x3BB7E0);
		MH_CreateHook(GAME_CreateDestructableZorg, &GAME_CreateDestructableZmy, reinterpret_cast<void**>(&GAME_CreateDestructableZold));
		MH_EnableHook(GAME_CreateDestructableZorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateFogModifierRadius", FALSE))
	{
		GAME_CreateFogModifierRadiusorg = (GAME_CreateFogModifierRadius) ((DWORD) GameDll + 0x3D0F90);
		MH_CreateHook(GAME_CreateFogModifierRadiusorg, &GAME_CreateFogModifierRadiusmy, reinterpret_cast<void**>(&GAME_CreateFogModifierRadiusold));
		MH_EnableHook(GAME_CreateFogModifierRadiusorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateFogModifierRadiusLoc", FALSE))
	{
		GAME_CreateFogModifierRadiusLocorg = (GAME_CreateFogModifierRadiusLoc) ((DWORD) GameDll + 0x3D10F0);
		MH_CreateHook(GAME_CreateFogModifierRadiusLocorg, &GAME_CreateFogModifierRadiusLocmy, reinterpret_cast<void**>(&GAME_CreateFogModifierRadiusLocold));
		MH_EnableHook(GAME_CreateFogModifierRadiusLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateFogModifierRect", FALSE))
	{
		GAME_CreateFogModifierRectorg = (GAME_CreateFogModifierRect) ((DWORD) GameDll + 0x3D0E70);
		MH_CreateHook(GAME_CreateFogModifierRectorg, &GAME_CreateFogModifierRectmy, reinterpret_cast<void**>(&GAME_CreateFogModifierRectold));
		MH_EnableHook(GAME_CreateFogModifierRectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateForce", FALSE))
	{
		GAME_CreateForceorg = (GAME_CreateForce) ((DWORD) GameDll + 0x3D29F0);
		MH_CreateHook(GAME_CreateForceorg, &GAME_CreateForcemy, reinterpret_cast<void**>(&GAME_CreateForceold));
		MH_EnableHook(GAME_CreateForceorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateGroup", FALSE))
	{
		GAME_CreateGrouporg = (GAME_CreateGroup) ((DWORD) GameDll + 0x3D2900);
		MH_CreateHook(GAME_CreateGrouporg, &GAME_CreateGroupmy, reinterpret_cast<void**>(&GAME_CreateGroupold));
		MH_EnableHook(GAME_CreateGrouporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateImage", FALSE))
	{
		GAME_CreateImageorg = (GAME_CreateImage) ((DWORD) GameDll + 0x3B4320);
		MH_CreateHook(GAME_CreateImageorg, &GAME_CreateImagemy, reinterpret_cast<void**>(&GAME_CreateImageold));
		MH_EnableHook(GAME_CreateImageorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateItem", FALSE))
	{
		GAME_CreateItemorg = (GAME_CreateItem) ((DWORD) GameDll + 0x3BB9A0);
		MH_CreateHook(GAME_CreateItemorg, &GAME_CreateItemmy, reinterpret_cast<void**>(&GAME_CreateItemold));
		MH_EnableHook(GAME_CreateItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateItemPool", FALSE))
	{
		GAME_CreateItemPoolorg = (GAME_CreateItemPool) ((DWORD) GameDll + 0x3D2FC0);
		MH_CreateHook(GAME_CreateItemPoolorg, &GAME_CreateItemPoolmy, reinterpret_cast<void**>(&GAME_CreateItemPoolold));
		MH_EnableHook(GAME_CreateItemPoolorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateLeaderboard", FALSE))
	{
		GAME_CreateLeaderboardorg = (GAME_CreateLeaderboard) ((DWORD) GameDll + 0x3D35B0);
		MH_CreateHook(GAME_CreateLeaderboardorg, &GAME_CreateLeaderboardmy, reinterpret_cast<void**>(&GAME_CreateLeaderboardold));
		MH_EnableHook(GAME_CreateLeaderboardorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateMIDISound", FALSE))
	{
		GAME_CreateMIDISoundorg = (GAME_CreateMIDISound) ((DWORD) GameDll + 0x3D3C30);
		MH_CreateHook(GAME_CreateMIDISoundorg, &GAME_CreateMIDISoundmy, reinterpret_cast<void**>(&GAME_CreateMIDISoundold));
		MH_EnableHook(GAME_CreateMIDISoundorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateMultiboard", FALSE))
	{
		GAME_CreateMultiboardorg = (GAME_CreateMultiboard) ((DWORD) GameDll + 0x3D36B0);
		MH_CreateHook(GAME_CreateMultiboardorg, &GAME_CreateMultiboardmy, reinterpret_cast<void**>(&GAME_CreateMultiboardold));
		MH_EnableHook(GAME_CreateMultiboardorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateQuest", FALSE))
	{
		GAME_CreateQuestorg = (GAME_CreateQuest) ((DWORD) GameDll + 0x3BC970);
		MH_CreateHook(GAME_CreateQuestorg, &GAME_CreateQuestmy, reinterpret_cast<void**>(&GAME_CreateQuestold));
		MH_EnableHook(GAME_CreateQuestorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateRegion", FALSE))
	{
		GAME_CreateRegionorg = (GAME_CreateRegion) ((DWORD) GameDll + 0x3D0930);
		MH_CreateHook(GAME_CreateRegionorg, &GAME_CreateRegionmy, reinterpret_cast<void**>(&GAME_CreateRegionold));
		MH_EnableHook(GAME_CreateRegionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateSound", FALSE))
	{
		GAME_CreateSoundorg = (GAME_CreateSound) ((DWORD) GameDll + 0x3D38D0);
		MH_CreateHook(GAME_CreateSoundorg, &GAME_CreateSoundmy, reinterpret_cast<void**>(&GAME_CreateSoundold));
		MH_EnableHook(GAME_CreateSoundorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateSoundFilenameWithLabel", FALSE))
	{
		GAME_CreateSoundFilenameWithLabelorg = (GAME_CreateSoundFilenameWithLabel) ((DWORD) GameDll + 0x3D39F0);
		MH_CreateHook(GAME_CreateSoundFilenameWithLabelorg, &GAME_CreateSoundFilenameWithLabelmy, reinterpret_cast<void**>(&GAME_CreateSoundFilenameWithLabelold));
		MH_EnableHook(GAME_CreateSoundFilenameWithLabelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateSoundFromLabel", FALSE))
	{
		GAME_CreateSoundFromLabelorg = (GAME_CreateSoundFromLabel) ((DWORD) GameDll + 0x3D3B10);
		MH_CreateHook(GAME_CreateSoundFromLabelorg, &GAME_CreateSoundFromLabelmy, reinterpret_cast<void**>(&GAME_CreateSoundFromLabelold));
		MH_EnableHook(GAME_CreateSoundFromLabelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateTextTag", FALSE))
	{
		GAME_CreateTextTagorg = (GAME_CreateTextTag) ((DWORD) GameDll + 0x3BC580);
		MH_CreateHook(GAME_CreateTextTagorg, &GAME_CreateTextTagmy, reinterpret_cast<void**>(&GAME_CreateTextTagold));
		MH_EnableHook(GAME_CreateTextTagorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateTimer", FALSE))
	{
		GAME_CreateTimerorg = (GAME_CreateTimer) ((DWORD) GameDll + 0x3D0500);
		MH_CreateHook(GAME_CreateTimerorg, &GAME_CreateTimermy, reinterpret_cast<void**>(&GAME_CreateTimerold));
		MH_EnableHook(GAME_CreateTimerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateTimerDialog", FALSE))
	{
		GAME_CreateTimerDialogorg = (GAME_CreateTimerDialog) ((DWORD) GameDll + 0x3D34B0);
		MH_CreateHook(GAME_CreateTimerDialogorg, &GAME_CreateTimerDialogmy, reinterpret_cast<void**>(&GAME_CreateTimerDialogold));
		MH_EnableHook(GAME_CreateTimerDialogorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateTrackable", FALSE))
	{
		GAME_CreateTrackableorg = (GAME_CreateTrackable) ((DWORD) GameDll + 0x3D30B0);
		MH_CreateHook(GAME_CreateTrackableorg, &GAME_CreateTrackablemy, reinterpret_cast<void**>(&GAME_CreateTrackableold));
		MH_EnableHook(GAME_CreateTrackableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateTrigger", FALSE))
	{
		GAME_CreateTriggerorg = (GAME_CreateTrigger) ((DWORD) GameDll + 0x3D11F0);
		MH_CreateHook(GAME_CreateTriggerorg, &GAME_CreateTriggermy, reinterpret_cast<void**>(&GAME_CreateTriggerold));
		MH_EnableHook(GAME_CreateTriggerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateUbersplat", FALSE))
	{
		GAME_CreateUbersplatorg = (GAME_CreateUbersplat) ((DWORD) GameDll + 0x3B85F0);
		MH_CreateHook(GAME_CreateUbersplatorg, &GAME_CreateUbersplatmy, reinterpret_cast<void**>(&GAME_CreateUbersplatold));
		MH_EnableHook(GAME_CreateUbersplatorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateUnit", FALSE))
	{
		GAME_CreateUnitorg = (GAME_CreateUnit) ((DWORD) GameDll + 0x3C5230);
		MH_CreateHook(GAME_CreateUnitorg, &GAME_CreateUnitmy, reinterpret_cast<void**>(&GAME_CreateUnitold));
		MH_EnableHook(GAME_CreateUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateUnitAtLoc", FALSE))
	{
		GAME_CreateUnitAtLocorg = (GAME_CreateUnitAtLoc) ((DWORD) GameDll + 0x3C52D0);
		MH_CreateHook(GAME_CreateUnitAtLocorg, &GAME_CreateUnitAtLocmy, reinterpret_cast<void**>(&GAME_CreateUnitAtLocold));
		MH_EnableHook(GAME_CreateUnitAtLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateUnitAtLocByName", FALSE))
	{
		GAME_CreateUnitAtLocByNameorg = (GAME_CreateUnitAtLocByName) ((DWORD) GameDll + 0x3C5320);
		MH_CreateHook(GAME_CreateUnitAtLocByNameorg, &GAME_CreateUnitAtLocByNamemy, reinterpret_cast<void**>(&GAME_CreateUnitAtLocByNameold));
		MH_EnableHook(GAME_CreateUnitAtLocByNameorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateUnitByName", FALSE))
	{
		GAME_CreateUnitByNameorg = (GAME_CreateUnitByName) ((DWORD) GameDll + 0x3C52A0);
		MH_CreateHook(GAME_CreateUnitByNameorg, &GAME_CreateUnitByNamemy, reinterpret_cast<void**>(&GAME_CreateUnitByNameold));
		MH_EnableHook(GAME_CreateUnitByNameorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateUnitPool", FALSE))
	{
		GAME_CreateUnitPoolorg = (GAME_CreateUnitPool) ((DWORD) GameDll + 0x3D2ED0);
		MH_CreateHook(GAME_CreateUnitPoolorg, &GAME_CreateUnitPoolmy, reinterpret_cast<void**>(&GAME_CreateUnitPoolold));
		MH_EnableHook(GAME_CreateUnitPoolorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreepsOnMap", FALSE))
	{
		GAME_CreepsOnMaporg = (GAME_CreepsOnMap) ((DWORD) GameDll + 0x2DC0F0);
		MH_CreateHook(GAME_CreepsOnMaporg, &GAME_CreepsOnMapmy, reinterpret_cast<void**>(&GAME_CreepsOnMapold));
		MH_EnableHook(GAME_CreepsOnMaporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CripplePlayer", FALSE))
	{
		GAME_CripplePlayerorg = (GAME_CripplePlayer) ((DWORD) GameDll + 0x3C1310);
		MH_CreateHook(GAME_CripplePlayerorg, &GAME_CripplePlayermy, reinterpret_cast<void**>(&GAME_CripplePlayerold));
		MH_EnableHook(GAME_CripplePlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DebugBreak", FALSE))
	{
		GAME_DebugBreakorg = (GAME_DebugBreak) ((DWORD) GameDll + 0x2DC050);
		MH_CreateHook(GAME_DebugBreakorg, &GAME_DebugBreakmy, reinterpret_cast<void**>(&GAME_DebugBreakold));
		MH_EnableHook(GAME_DebugBreakorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DebugFI", FALSE))
	{
		GAME_DebugFIorg = (GAME_DebugFI) ((DWORD) GameDll + 0x2DC0B0);
		MH_CreateHook(GAME_DebugFIorg, &GAME_DebugFImy, reinterpret_cast<void**>(&GAME_DebugFIold));
		MH_EnableHook(GAME_DebugFIorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DebugS", FALSE))
	{
		GAME_DebugSorg = (GAME_DebugS) ((DWORD) GameDll + 0x2DC0A0);
		MH_CreateHook(GAME_DebugSorg, &GAME_DebugSmy, reinterpret_cast<void**>(&GAME_DebugSold));
		MH_EnableHook(GAME_DebugSorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DebugUnitID", FALSE))
	{
		GAME_DebugUnitIDorg = (GAME_DebugUnitID) ((DWORD) GameDll + 0x2DC0C0);
		MH_CreateHook(GAME_DebugUnitIDorg, &GAME_DebugUnitIDmy, reinterpret_cast<void**>(&GAME_DebugUnitIDold));
		MH_EnableHook(GAME_DebugUnitIDorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_FastError", FALSE))
	{
		GAME_FastErrororg = (GAME_FastError) ((DWORD) GameDll + 0x4CBF60);
		MH_CreateHook(GAME_FastErrororg, &GAME_FastErrormy, reinterpret_cast<void**>(&GAME_FastErrorold));
		MH_EnableHook(GAME_FastErrororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Ordinal578", FALSE))
	{
		GAME_Ordinal578org = (GAME_Ordinal578) ((DWORD) GameDll + 0x034150);
		MH_CreateHook(GAME_Ordinal578org, &GAME_Ordinal578my, reinterpret_cast<void**>(&GAME_Ordinal578old));
		MH_EnableHook(GAME_Ordinal578org);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Ordinal289", FALSE))
	{
		GAME_Ordinal289org = (GAME_Ordinal289) ((DWORD) GameDll + 0x0196E0);
		MH_CreateHook(GAME_Ordinal289org, &GAME_Ordinal289my, reinterpret_cast<void**>(&GAME_Ordinal289old));
		MH_EnableHook(GAME_Ordinal289org);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_sub_10006020", FALSE))
	{
		GAME_sub_10006020org = (GAME_sub_10006020) ((DWORD) GameDll + 0x6020);
		MH_CreateHook(GAME_sub_10006020org, &GAME_sub_10006020my, reinterpret_cast<void**>(&GAME_sub_10006020old));
		MH_EnableHook(GAME_sub_10006020org);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_reconnect1", FALSE))
	{
		GAME_reconnect1org = (GAME_reconnect1) ((DWORD) GameDll + 0x01C100);
		MH_CreateHook(GAME_reconnect1org, &GAME_reconnect1my, reinterpret_cast<void**>(&GAME_reconnect1old));
		MH_EnableHook(GAME_reconnect1org);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DllMainRECO", FALSE))
	{
		GAME_DllMainRECOorg = (GAME_DllMainRECO) ((DWORD) GameDll + 0x015480);
		MH_CreateHook(GAME_DllMainRECOorg, &GAME_DllMainRECOmy, reinterpret_cast<void**>(&GAME_DllMainRECOold));
		MH_EnableHook(GAME_DllMainRECOorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_sub_6F4CBF60", FALSE))
	{
		GAME_sub_6F4CBF60org = (GAME_sub_6F4CBF60) ((DWORD) GameDll + 0x4CBF60);
		MH_CreateHook(GAME_sub_6F4CBF60org, &GAME_sub_6F4CBF60my, reinterpret_cast<void**>(&GAME_sub_6F4CBF60old));
		MH_EnableHook(GAME_sub_6F4CBF60org);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_VersionGM", FALSE))
	{
		GAME_VersionGMorg = (GAME_VersionGM) ((DWORD) GameDll + 0x31F530);
		MH_CreateHook(GAME_VersionGMorg, &GAME_VersionGMmy, reinterpret_cast<void**>(&GAME_VersionGMold));
		MH_EnableHook(GAME_VersionGMorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateGameMessage", FALSE))
	{
		GAME_CreateGameMessageorg = (GAME_CreateGameMessage) ((DWORD) GameDll + 0x5C9650);
		MH_CreateHook(GAME_CreateGameMessageorg, &GAME_CreateGameMessagemy, reinterpret_cast<void**>(&GAME_CreateGameMessageold));
		MH_EnableHook(GAME_CreateGameMessageorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_BeforeSendMessage2", FALSE))
	{
		GAME_BeforeSendMessage2org = (GAME_BeforeSendMessage2) ((DWORD) GameDll + 0x53E610);
		MH_CreateHook(GAME_BeforeSendMessage2org, &GAME_BeforeSendMessage2my, reinterpret_cast<void**>(&GAME_BeforeSendMessage2old));
		MH_EnableHook(GAME_BeforeSendMessage2org);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_CreateGameDefaultBNETErrorMessage", FALSE))
	{
		GAME_CreateGameDefaultBNETErrorMessageorg = (GAME_CreateGameDefaultBNETErrorMessage) ((DWORD) GameDll + 0x5A7780);
		MH_CreateHook(GAME_CreateGameDefaultBNETErrorMessageorg, &GAME_CreateGameDefaultBNETErrorMessagemy, reinterpret_cast<void**>(&GAME_CreateGameDefaultBNETErrorMessageold));
		MH_EnableHook(GAME_CreateGameDefaultBNETErrorMessageorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_BeforeSendMessage", FALSE))
	{
		GAME_BeforeSendMessageorg = (GAME_BeforeSendMessage) ((DWORD) GameDll + 0x5A6DA0);
		MH_CreateHook(GAME_BeforeSendMessageorg, &GAME_BeforeSendMessagemy, reinterpret_cast<void**>(&GAME_BeforeSendMessageold));
		MH_EnableHook(GAME_BeforeSendMessageorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ShowGameMessage", FALSE))
	{
		GAME_ShowGameMessageorg = (GAME_ShowGameMessage) ((DWORD) GameDll + 0x55CEB0);
		MH_CreateHook(GAME_ShowGameMessageorg, &GAME_ShowGameMessagemy, reinterpret_cast<void**>(&GAME_ShowGameMessageold));
		MH_EnableHook(GAME_ShowGameMessageorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DecUnitAbilityLevel", FALSE))
	{
		GAME_DecUnitAbilityLevelorg = (GAME_DecUnitAbilityLevel) ((DWORD) GameDll + 0x3C70B0);
		MH_CreateHook(GAME_DecUnitAbilityLevelorg, &GAME_DecUnitAbilityLevelmy, reinterpret_cast<void**>(&GAME_DecUnitAbilityLevelold));
		MH_EnableHook(GAME_DecUnitAbilityLevelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DefeatConditionSetDescription", FALSE))
	{
		GAME_DefeatConditionSetDescriptionorg = (GAME_DefeatConditionSetDescription) ((DWORD) GameDll + 0x3CBE00);
		MH_CreateHook(GAME_DefeatConditionSetDescriptionorg, &GAME_DefeatConditionSetDescriptionmy, reinterpret_cast<void**>(&GAME_DefeatConditionSetDescriptionold));
		MH_EnableHook(GAME_DefeatConditionSetDescriptionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DefineStartLocation", FALSE))
	{
		GAME_DefineStartLocationorg = (GAME_DefineStartLocation) ((DWORD) GameDll + 0x3BAF70);
		MH_CreateHook(GAME_DefineStartLocationorg, &GAME_DefineStartLocationmy, reinterpret_cast<void**>(&GAME_DefineStartLocationold));
		MH_EnableHook(GAME_DefineStartLocationorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DefineStartLocationLoc", FALSE))
	{
		GAME_DefineStartLocationLocorg = (GAME_DefineStartLocationLoc) ((DWORD) GameDll + 0x3C0EA0);
		MH_CreateHook(GAME_DefineStartLocationLocorg, &GAME_DefineStartLocationLocmy, reinterpret_cast<void**>(&GAME_DefineStartLocationLocold));
		MH_EnableHook(GAME_DefineStartLocationLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Deg2Rad", FALSE))
	{
		GAME_Deg2Radorg = (GAME_Deg2Rad) ((DWORD) GameDll + 0x3B29D0);
		MH_CreateHook(GAME_Deg2Radorg, &GAME_Deg2Radmy, reinterpret_cast<void**>(&GAME_Deg2Radold));
		MH_EnableHook(GAME_Deg2Radorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyBOOLExpr", FALSE))
	{
		GAME_DestroyBOOLExprorg = (GAME_DestroyBOOLExpr) ((DWORD) GameDll + 0x3C14A0);
		MH_CreateHook(GAME_DestroyBOOLExprorg, &GAME_DestroyBOOLExprmy, reinterpret_cast<void**>(&GAME_DestroyBOOLExprold));
		MH_EnableHook(GAME_DestroyBOOLExprorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyCondition", FALSE))
	{
		GAME_DestroyConditionorg = (GAME_DestroyCondition) ((DWORD) GameDll + 0x3C1440);
		MH_CreateHook(GAME_DestroyConditionorg, &GAME_DestroyConditionmy, reinterpret_cast<void**>(&GAME_DestroyConditionold));
		MH_EnableHook(GAME_DestroyConditionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyDefeatCondition", FALSE))
	{
		GAME_DestroyDefeatConditionorg = (GAME_DestroyDefeatCondition) ((DWORD) GameDll + 0x3CBDB0);
		MH_CreateHook(GAME_DestroyDefeatConditionorg, &GAME_DestroyDefeatConditionmy, reinterpret_cast<void**>(&GAME_DestroyDefeatConditionold));
		MH_EnableHook(GAME_DestroyDefeatConditionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyEffect", FALSE))
	{
		GAME_DestroyEffectorg = (GAME_DestroyEffect) ((DWORD) GameDll + 0x3CD240);
		MH_CreateHook(GAME_DestroyEffectorg, &GAME_DestroyEffectmy, reinterpret_cast<void**>(&GAME_DestroyEffectold));
		MH_EnableHook(GAME_DestroyEffectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyFilter", FALSE))
	{
		GAME_DestroyFilterorg = (GAME_DestroyFilter) ((DWORD) GameDll + 0x3C1470);
		MH_CreateHook(GAME_DestroyFilterorg, &GAME_DestroyFiltermy, reinterpret_cast<void**>(&GAME_DestroyFilterold));
		MH_EnableHook(GAME_DestroyFilterorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyFogModifier", FALSE))
	{
		GAME_DestroyFogModifierorg = (GAME_DestroyFogModifier) ((DWORD) GameDll + 0x3C1BA0);
		MH_CreateHook(GAME_DestroyFogModifierorg, &GAME_DestroyFogModifiermy, reinterpret_cast<void**>(&GAME_DestroyFogModifierold));
		MH_EnableHook(GAME_DestroyFogModifierorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyForce", FALSE))
	{
		GAME_DestroyForceorg = (GAME_DestroyForce) ((DWORD) GameDll + 0x3C44C0);
		MH_CreateHook(GAME_DestroyForceorg, &GAME_DestroyForcemy, reinterpret_cast<void**>(&GAME_DestroyForceold));
		MH_EnableHook(GAME_DestroyForceorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DebugTerrainCONSOLE", FALSE))
	{
		GAME_DebugTerrainCONSOLEorg = (GAME_DebugTerrainCONSOLE) ((DWORD) GameDll + 0x763B20);
		MH_CreateHook(GAME_DebugTerrainCONSOLEorg, &GAME_DebugTerrainCONSOLEmy, reinterpret_cast<void**>(&GAME_DebugTerrainCONSOLEold));
		MH_EnableHook(GAME_DebugTerrainCONSOLEorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DebugTerrainFILE", FALSE))
	{
		GAME_DebugTerrainFILEorg = (GAME_DebugTerrainFILE) ((DWORD) GameDll + 0x763B50);
		MH_CreateHook(GAME_DebugTerrainFILEorg, &GAME_DebugTerrainFILEmy, reinterpret_cast<void**>(&GAME_DebugTerrainFILEold));
		MH_EnableHook(GAME_DebugTerrainFILEorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyGroup", FALSE))
	{
		GAME_DestroyGrouporg = (GAME_DestroyGroup) ((DWORD) GameDll + 0x3C3FA0);
		MH_CreateHook(GAME_DestroyGrouporg, &GAME_DestroyGroupmy, reinterpret_cast<void**>(&GAME_DestroyGroupold));
		MH_EnableHook(GAME_DestroyGrouporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyImage", FALSE))
	{
		GAME_DestroyImageorg = (GAME_DestroyImage) ((DWORD) GameDll + 0x3B43B0);
		MH_CreateHook(GAME_DestroyImageorg, &GAME_DestroyImagemy, reinterpret_cast<void**>(&GAME_DestroyImageold));
		MH_EnableHook(GAME_DestroyImageorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyItemPool", FALSE))
	{
		GAME_DestroyItemPoolorg = (GAME_DestroyItemPool) ((DWORD) GameDll + 0x3CB6A0);
		MH_CreateHook(GAME_DestroyItemPoolorg, &GAME_DestroyItemPoolmy, reinterpret_cast<void**>(&GAME_DestroyItemPoolold));
		MH_EnableHook(GAME_DestroyItemPoolorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyLeaderboard", FALSE))
	{
		GAME_DestroyLeaderboardorg = (GAME_DestroyLeaderboard) ((DWORD) GameDll + 0x3CBFD0);
		MH_CreateHook(GAME_DestroyLeaderboardorg, &GAME_DestroyLeaderboardmy, reinterpret_cast<void**>(&GAME_DestroyLeaderboardold));
		MH_EnableHook(GAME_DestroyLeaderboardorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyLightning", FALSE))
	{
		GAME_DestroyLightningorg = (GAME_DestroyLightning) ((DWORD) GameDll + 0x3B4150);
		MH_CreateHook(GAME_DestroyLightningorg, &GAME_DestroyLightningmy, reinterpret_cast<void**>(&GAME_DestroyLightningold));
		MH_EnableHook(GAME_DestroyLightningorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyMultiboard", FALSE))
	{
		GAME_DestroyMultiboardorg = (GAME_DestroyMultiboard) ((DWORD) GameDll + 0x3CC650);
		MH_CreateHook(GAME_DestroyMultiboardorg, &GAME_DestroyMultiboardmy, reinterpret_cast<void**>(&GAME_DestroyMultiboardold));
		MH_EnableHook(GAME_DestroyMultiboardorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyQuest", FALSE))
	{
		GAME_DestroyQuestorg = (GAME_DestroyQuest) ((DWORD) GameDll + 0x3CBB20);
		MH_CreateHook(GAME_DestroyQuestorg, &GAME_DestroyQuestmy, reinterpret_cast<void**>(&GAME_DestroyQuestold));
		MH_EnableHook(GAME_DestroyQuestorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyTextTag", FALSE))
	{
		GAME_DestroyTextTagorg = (GAME_DestroyTextTag) ((DWORD) GameDll + 0x3BC5A0);
		MH_CreateHook(GAME_DestroyTextTagorg, &GAME_DestroyTextTagmy, reinterpret_cast<void**>(&GAME_DestroyTextTagold));
		MH_EnableHook(GAME_DestroyTextTagorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyTimer", FALSE))
	{
		GAME_DestroyTimerorg = (GAME_DestroyTimer) ((DWORD) GameDll + 0x3C1350);
		MH_CreateHook(GAME_DestroyTimerorg, &GAME_DestroyTimermy, reinterpret_cast<void**>(&GAME_DestroyTimerold));
		MH_EnableHook(GAME_DestroyTimerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyTimerDialog", FALSE))
	{
		GAME_DestroyTimerDialogorg = (GAME_DestroyTimerDialog) ((DWORD) GameDll + 0x3CBE30);
		MH_CreateHook(GAME_DestroyTimerDialogorg, &GAME_DestroyTimerDialogmy, reinterpret_cast<void**>(&GAME_DestroyTimerDialogold));
		MH_EnableHook(GAME_DestroyTimerDialogorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyTrigger", FALSE))
	{
		GAME_DestroyTriggerorg = (GAME_DestroyTrigger) ((DWORD) GameDll + 0x3C1C00);
		MH_CreateHook(GAME_DestroyTriggerorg, &GAME_DestroyTriggermy, reinterpret_cast<void**>(&GAME_DestroyTriggerold));
		MH_EnableHook(GAME_DestroyTriggerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyUbersplat", FALSE))
	{
		GAME_DestroyUbersplatorg = (GAME_DestroyUbersplat) ((DWORD) GameDll + 0x3B44C0);
		MH_CreateHook(GAME_DestroyUbersplatorg, &GAME_DestroyUbersplatmy, reinterpret_cast<void**>(&GAME_DestroyUbersplatold));
		MH_EnableHook(GAME_DestroyUbersplatorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestroyUnitPool", FALSE))
	{
		GAME_DestroyUnitPoolorg = (GAME_DestroyUnitPool) ((DWORD) GameDll + 0x3CB5C0);
		MH_CreateHook(GAME_DestroyUnitPoolorg, &GAME_DestroyUnitPoolmy, reinterpret_cast<void**>(&GAME_DestroyUnitPoolold));
		MH_EnableHook(GAME_DestroyUnitPoolorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DestructableRestoreLife", FALSE))
	{
		GAME_DestructableRestoreLifeorg = (GAME_DestructableRestoreLife) ((DWORD) GameDll + 0x3C4870);
		MH_CreateHook(GAME_DestructableRestoreLifeorg, &GAME_DestructableRestoreLifemy, reinterpret_cast<void**>(&GAME_DestructableRestoreLifeold));
		MH_EnableHook(GAME_DestructableRestoreLifeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DialogAddButton", FALSE))
	{
		GAME_DialogAddButtonorg = (GAME_DialogAddButton) ((DWORD) GameDll + 0x3C9F90);
		MH_CreateHook(GAME_DialogAddButtonorg, &GAME_DialogAddButtonmy, reinterpret_cast<void**>(&GAME_DialogAddButtonold));
		MH_EnableHook(GAME_DialogAddButtonorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DialogAddQuitButton", FALSE))
	{
		GAME_DialogAddQuitButtonorg = (GAME_DialogAddQuitButton) ((DWORD) GameDll + 0x3C9FE0);
		MH_CreateHook(GAME_DialogAddQuitButtonorg, &GAME_DialogAddQuitButtonmy, reinterpret_cast<void**>(&GAME_DialogAddQuitButtonold));
		MH_EnableHook(GAME_DialogAddQuitButtonorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DialogClear", FALSE))
	{
		GAME_DialogClearorg = (GAME_DialogClear) ((DWORD) GameDll + 0x3C9F40);
		MH_CreateHook(GAME_DialogClearorg, &GAME_DialogClearmy, reinterpret_cast<void**>(&GAME_DialogClearold));
		MH_EnableHook(GAME_DialogClearorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DialogCreate", FALSE))
	{
		GAME_DialogCreateorg = (GAME_DialogCreate) ((DWORD) GameDll + 0x3D2BC0);
		MH_CreateHook(GAME_DialogCreateorg, &GAME_DialogCreatemy, reinterpret_cast<void**>(&GAME_DialogCreateold));
		MH_EnableHook(GAME_DialogCreateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DialogDestroy", FALSE))
	{
		GAME_DialogDestroyorg = (GAME_DialogDestroy) ((DWORD) GameDll + 0x3C9F00);
		MH_CreateHook(GAME_DialogDestroyorg, &GAME_DialogDestroymy, reinterpret_cast<void**>(&GAME_DialogDestroyold));
		MH_EnableHook(GAME_DialogDestroyorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DialogDisplay", FALSE))
	{
		GAME_DialogDisplayorg = (GAME_DialogDisplay) ((DWORD) GameDll + 0x3CA030);
		MH_CreateHook(GAME_DialogDisplayorg, &GAME_DialogDisplaymy, reinterpret_cast<void**>(&GAME_DialogDisplayold));
		MH_EnableHook(GAME_DialogDisplayorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DialogSetAsync", FALSE))
	{
		GAME_DialogSetAsyncorg = (GAME_DialogSetAsync) ((DWORD) GameDll + 0x3C9F20);
		MH_CreateHook(GAME_DialogSetAsyncorg, &GAME_DialogSetAsyncmy, reinterpret_cast<void**>(&GAME_DialogSetAsyncold));
		MH_EnableHook(GAME_DialogSetAsyncorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DialogSetMessage", FALSE))
	{
		GAME_DialogSetMessageorg = (GAME_DialogSetMessage) ((DWORD) GameDll + 0x3C9F60);
		MH_CreateHook(GAME_DialogSetMessageorg, &GAME_DialogSetMessagemy, reinterpret_cast<void**>(&GAME_DialogSetMessageold));
		MH_EnableHook(GAME_DialogSetMessageorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DisablePathing", FALSE))
	{
		GAME_DisablePathingorg = (GAME_DisablePathing) ((DWORD) GameDll + 0x2E06E0);
		MH_CreateHook(GAME_DisablePathingorg, &GAME_DisablePathingmy, reinterpret_cast<void**>(&GAME_DisablePathingold));
		MH_EnableHook(GAME_DisablePathingorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DisableRestartMission", FALSE))
	{
		GAME_DisableRestartMissionorg = (GAME_DisableRestartMission) ((DWORD) GameDll + 0x3B38C0);
		MH_CreateHook(GAME_DisableRestartMissionorg, &GAME_DisableRestartMissionmy, reinterpret_cast<void**>(&GAME_DisableRestartMissionold));
		MH_EnableHook(GAME_DisableRestartMissionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DisableTrigger", FALSE))
	{
		GAME_DisableTriggerorg = (GAME_DisableTrigger) ((DWORD) GameDll + 0x3C1C60);
		MH_CreateHook(GAME_DisableTriggerorg, &GAME_DisableTriggermy, reinterpret_cast<void**>(&GAME_DisableTriggerold));
		MH_EnableHook(GAME_DisableTriggerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DisplayCineFilter", FALSE))
	{
		GAME_DisplayCineFilterorg = (GAME_DisplayCineFilter) ((DWORD) GameDll + 0x3B5120);
		MH_CreateHook(GAME_DisplayCineFilterorg, &GAME_DisplayCineFiltermy, reinterpret_cast<void**>(&GAME_DisplayCineFilterold));
		MH_EnableHook(GAME_DisplayCineFilterorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DisplayLoadDialog", FALSE))
	{
		GAME_DisplayLoadDialogorg = (GAME_DisplayLoadDialog) ((DWORD) GameDll + 0x3B3A10);
		MH_CreateHook(GAME_DisplayLoadDialogorg, &GAME_DisplayLoadDialogmy, reinterpret_cast<void**>(&GAME_DisplayLoadDialogold));
		MH_EnableHook(GAME_DisplayLoadDialogorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DisplayText", FALSE))
	{
		GAME_DisplayTextorg = (GAME_DisplayText) ((DWORD) GameDll + 0x2DC060);
		MH_CreateHook(GAME_DisplayTextorg, &GAME_DisplayTextmy, reinterpret_cast<void**>(&GAME_DisplayTextold));
		MH_EnableHook(GAME_DisplayTextorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DisplayTextI", FALSE))
	{
		GAME_DisplayTextIorg = (GAME_DisplayTextI) ((DWORD) GameDll + 0x2DC070);
		MH_CreateHook(GAME_DisplayTextIorg, &GAME_DisplayTextImy, reinterpret_cast<void**>(&GAME_DisplayTextIold));
		MH_EnableHook(GAME_DisplayTextIorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DisplayTextII", FALSE))
	{
		GAME_DisplayTextIIorg = (GAME_DisplayTextII) ((DWORD) GameDll + 0x2DC080);
		MH_CreateHook(GAME_DisplayTextIIorg, &GAME_DisplayTextIImy, reinterpret_cast<void**>(&GAME_DisplayTextIIold));
		MH_EnableHook(GAME_DisplayTextIIorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DisplayTextIII", FALSE))
	{
		GAME_DisplayTextIIIorg = (GAME_DisplayTextIII) ((DWORD) GameDll + 0x2DC090);
		MH_CreateHook(GAME_DisplayTextIIIorg, &GAME_DisplayTextIIImy, reinterpret_cast<void**>(&GAME_DisplayTextIIIold));
		MH_EnableHook(GAME_DisplayTextIIIorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DisplayTextToPlayer", FALSE))
	{
		GAME_DisplayTextToPlayerorg = (GAME_DisplayTextToPlayer) ((DWORD) GameDll + 0x3CB900);
		MH_CreateHook(GAME_DisplayTextToPlayerorg, &GAME_DisplayTextToPlayermy, reinterpret_cast<void**>(&GAME_DisplayTextToPlayerold));
		MH_EnableHook(GAME_DisplayTextToPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DisplayTimedTextFromPlayer", FALSE))
	{
		GAME_DisplayTimedTextFromPlayerorg = (GAME_DisplayTimedTextFromPlayer) ((DWORD) GameDll + 0x3CBA30);
		MH_CreateHook(GAME_DisplayTimedTextFromPlayerorg, &GAME_DisplayTimedTextFromPlayermy, reinterpret_cast<void**>(&GAME_DisplayTimedTextFromPlayerold));
		MH_EnableHook(GAME_DisplayTimedTextFromPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DisplayTimedTextToPlayer", FALSE))
	{
		GAME_DisplayTimedTextToPlayerorg = (GAME_DisplayTimedTextToPlayer) ((DWORD) GameDll + 0x3CB9B0);
		MH_CreateHook(GAME_DisplayTimedTextToPlayerorg, &GAME_DisplayTimedTextToPlayermy, reinterpret_cast<void**>(&GAME_DisplayTimedTextToPlayerold));
		MH_EnableHook(GAME_DisplayTimedTextToPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DoAiScriptDebug", FALSE))
	{
		GAME_DoAiScriptDebugorg = (GAME_DoAiScriptDebug) ((DWORD) GameDll + 0x2DC0D0);
		MH_CreateHook(GAME_DoAiScriptDebugorg, &GAME_DoAiScriptDebugmy, reinterpret_cast<void**>(&GAME_DoAiScriptDebugold));
		MH_EnableHook(GAME_DoAiScriptDebugorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_DoNotSaveReplay", FALSE))
	{
		GAME_DoNotSaveReplayorg = (GAME_DoNotSaveReplay) ((DWORD) GameDll + 0x3B3550);
		MH_CreateHook(GAME_DoNotSaveReplayorg, &GAME_DoNotSaveReplaymy, reinterpret_cast<void**>(&GAME_DoNotSaveReplayold));
		MH_EnableHook(GAME_DoNotSaveReplayorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_EnableDragSelect", FALSE))
	{
		GAME_EnableDragSelectorg = (GAME_EnableDragSelect) ((DWORD) GameDll + 0x3B3B30);
		MH_CreateHook(GAME_EnableDragSelectorg, &GAME_EnableDragSelectmy, reinterpret_cast<void**>(&GAME_EnableDragSelectold));
		MH_EnableHook(GAME_EnableDragSelectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_EnableMinimapFilterButtons", FALSE))
	{
		GAME_EnableMinimapFilterButtonsorg = (GAME_EnableMinimapFilterButtons) ((DWORD) GameDll + 0x3B3AF0);
		MH_CreateHook(GAME_EnableMinimapFilterButtonsorg, &GAME_EnableMinimapFilterButtonsmy, reinterpret_cast<void**>(&GAME_EnableMinimapFilterButtonsold));
		MH_EnableHook(GAME_EnableMinimapFilterButtonsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_EnableOcclusion", FALSE))
	{
		GAME_EnableOcclusionorg = (GAME_EnableOcclusion) ((DWORD) GameDll + 0x3B3B90);
		MH_CreateHook(GAME_EnableOcclusionorg, &GAME_EnableOcclusionmy, reinterpret_cast<void**>(&GAME_EnableOcclusionold));
		MH_EnableHook(GAME_EnableOcclusionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_EnablePreSelect", FALSE))
	{
		GAME_EnablePreSelectorg = (GAME_EnablePreSelect) ((DWORD) GameDll + 0x3B3B50);
		MH_CreateHook(GAME_EnablePreSelectorg, &GAME_EnablePreSelectmy, reinterpret_cast<void**>(&GAME_EnablePreSelectold));
		MH_EnableHook(GAME_EnablePreSelectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_EnableSelect", FALSE))
	{
		GAME_EnableSelectorg = (GAME_EnableSelect) ((DWORD) GameDll + 0x3B3B70);
		MH_CreateHook(GAME_EnableSelectorg, &GAME_EnableSelectmy, reinterpret_cast<void**>(&GAME_EnableSelectold));
		MH_EnableHook(GAME_EnableSelectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_EnableTrigger", FALSE))
	{
		GAME_EnableTriggerorg = (GAME_EnableTrigger) ((DWORD) GameDll + 0x3C1C40);
		MH_CreateHook(GAME_EnableTriggerorg, &GAME_EnableTriggermy, reinterpret_cast<void**>(&GAME_EnableTriggerold));
		MH_EnableHook(GAME_EnableTriggerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_EnableUserControl", FALSE))
	{
		GAME_EnableUserControlorg = (GAME_EnableUserControl) ((DWORD) GameDll + 0x3B3880);
		MH_CreateHook(GAME_EnableUserControlorg, &GAME_EnableUserControlmy, reinterpret_cast<void**>(&GAME_EnableUserControlold));
		MH_EnableHook(GAME_EnableUserControlorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_EnableUserUI", FALSE))
	{
		GAME_EnableUserUIorg = (GAME_EnableUserUI) ((DWORD) GameDll + 0x3B38A0);
		MH_CreateHook(GAME_EnableUserUIorg, &GAME_EnableUserUImy, reinterpret_cast<void**>(&GAME_EnableUserUIold));
		MH_EnableHook(GAME_EnableUserUIorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_EnableWeatherEffect", FALSE))
	{
		GAME_EnableWeatherEffectorg = (GAME_EnableWeatherEffect) ((DWORD) GameDll + 0x3B3E80);
		MH_CreateHook(GAME_EnableWeatherEffectorg, &GAME_EnableWeatherEffectmy, reinterpret_cast<void**>(&GAME_EnableWeatherEffectold));
		MH_EnableHook(GAME_EnableWeatherEffectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_EnableWorldFogBoundary", FALSE))
	{
		GAME_EnableWorldFogBoundaryorg = (GAME_EnableWorldFogBoundary) ((DWORD) GameDll + 0x3B3BB0);
		MH_CreateHook(GAME_EnableWorldFogBoundaryorg, &GAME_EnableWorldFogBoundarymy, reinterpret_cast<void**>(&GAME_EnableWorldFogBoundaryold));
		MH_EnableHook(GAME_EnableWorldFogBoundaryorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_EndCinematicScene", FALSE))
	{
		GAME_EndCinematicSceneorg = (GAME_EndCinematicScene) ((DWORD) GameDll + 0x3B4E20);
		MH_CreateHook(GAME_EndCinematicSceneorg, &GAME_EndCinematicScenemy, reinterpret_cast<void**>(&GAME_EndCinematicSceneold));
		MH_EnableHook(GAME_EndCinematicSceneorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_EndGame", FALSE))
	{
		GAME_EndGameorg = (GAME_EndGame) ((DWORD) GameDll + 0x3BBBB0);
		MH_CreateHook(GAME_EndGameorg, &GAME_EndGamemy, reinterpret_cast<void**>(&GAME_EndGameold));
		MH_EnableHook(GAME_EndGameorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_EndThematicMusic", FALSE))
	{
		GAME_EndThematicMusicorg = (GAME_EndThematicMusic) ((DWORD) GameDll + 0x3B3DE0);
		MH_CreateHook(GAME_EndThematicMusicorg, &GAME_EndThematicMusicmy, reinterpret_cast<void**>(&GAME_EndThematicMusicold));
		MH_EnableHook(GAME_EndThematicMusicorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_EnumDestructablesInRect", FALSE))
	{
		GAME_EnumDestructablesInRectorg = (GAME_EnumDestructablesInRect) ((DWORD) GameDll + 0x3C4A90);
		MH_CreateHook(GAME_EnumDestructablesInRectorg, &GAME_EnumDestructablesInRectmy, reinterpret_cast<void**>(&GAME_EnumDestructablesInRectold));
		MH_EnableHook(GAME_EnumDestructablesInRectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_EnumItemsInRect", FALSE))
	{
		GAME_EnumItemsInRectorg = (GAME_EnumItemsInRect) ((DWORD) GameDll + 0x3C5110);
		MH_CreateHook(GAME_EnumItemsInRectorg, &GAME_EnumItemsInRectmy, reinterpret_cast<void**>(&GAME_EnumItemsInRectold));
		MH_EnableHook(GAME_EnumItemsInRectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ExecuteFunc", FALSE))
	{
		GAME_ExecuteFuncorg = (GAME_ExecuteFunc) ((DWORD) GameDll + 0x3D3F30);
		MH_CreateHook(GAME_ExecuteFuncorg, &GAME_ExecuteFuncmy, reinterpret_cast<void**>(&GAME_ExecuteFuncold));
		MH_EnableHook(GAME_ExecuteFuncorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_FillGuardPosts", FALSE))
	{
		GAME_FillGuardPostsorg = (GAME_FillGuardPosts) ((DWORD) GameDll + 0x2DCF80);
		MH_CreateHook(GAME_FillGuardPostsorg, &GAME_FillGuardPostsmy, reinterpret_cast<void**>(&GAME_FillGuardPostsold));
		MH_EnableHook(GAME_FillGuardPostsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Filter", FALSE))
	{
		GAME_Filterorg = (GAME_Filter) ((DWORD) GameDll + 0x3BB140);
		MH_CreateHook(GAME_Filterorg, &GAME_Filtermy, reinterpret_cast<void**>(&GAME_Filterold));
		MH_EnableHook(GAME_Filterorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_FinishUbersplat", FALSE))
	{
		GAME_FinishUbersplatorg = (GAME_FinishUbersplat) ((DWORD) GameDll + 0x3B44E0);
		MH_CreateHook(GAME_FinishUbersplatorg, &GAME_FinishUbersplatmy, reinterpret_cast<void**>(&GAME_FinishUbersplatold));
		MH_EnableHook(GAME_FinishUbersplatorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_FirstOfGroup", FALSE))
	{
		GAME_FirstOfGrouporg = (GAME_FirstOfGroup) ((DWORD) GameDll + 0x3C4460);
		MH_CreateHook(GAME_FirstOfGrouporg, &GAME_FirstOfGroupmy, reinterpret_cast<void**>(&GAME_FirstOfGroupold));
		MH_EnableHook(GAME_FirstOfGrouporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_FlashQuestDialogButton", FALSE))
	{
		GAME_FlashQuestDialogButtonorg = (GAME_FlashQuestDialogButton) ((DWORD) GameDll + 0x3BC920);
		MH_CreateHook(GAME_FlashQuestDialogButtonorg, &GAME_FlashQuestDialogButtonmy, reinterpret_cast<void**>(&GAME_FlashQuestDialogButtonold));
		MH_EnableHook(GAME_FlashQuestDialogButtonorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_FlushChildHashtable", FALSE))
	{
		GAME_FlushChildHashtableorg = (GAME_FlushChildHashtable) ((DWORD) GameDll + 0x3CB590);
		MH_CreateHook(GAME_FlushChildHashtableorg, &GAME_FlushChildHashtablemy, reinterpret_cast<void**>(&GAME_FlushChildHashtableold));
		MH_EnableHook(GAME_FlushChildHashtableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_FlushGameCache", FALSE))
	{
		GAME_FlushGameCacheorg = (GAME_FlushGameCache) ((DWORD) GameDll + 0x3CB200);
		MH_CreateHook(GAME_FlushGameCacheorg, &GAME_FlushGameCachemy, reinterpret_cast<void**>(&GAME_FlushGameCacheold));
		MH_EnableHook(GAME_FlushGameCacheorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_FlushParentHashtable", FALSE))
	{
		GAME_FlushParentHashtableorg = (GAME_FlushParentHashtable) ((DWORD) GameDll + 0x3CB550);
		MH_CreateHook(GAME_FlushParentHashtableorg, &GAME_FlushParentHashtablemy, reinterpret_cast<void**>(&GAME_FlushParentHashtableold));
		MH_EnableHook(GAME_FlushParentHashtableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_FlushStoredBOOLean", FALSE))
	{
		GAME_FlushStoredBOOLeanorg = (GAME_FlushStoredBOOLean) ((DWORD) GameDll + 0x3CB320);
		MH_CreateHook(GAME_FlushStoredBOOLeanorg, &GAME_FlushStoredBOOLeanmy, reinterpret_cast<void**>(&GAME_FlushStoredBOOLeanold));
		MH_EnableHook(GAME_FlushStoredBOOLeanorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_FlushStoredInteger", FALSE))
	{
		GAME_FlushStoredIntegerorg = (GAME_FlushStoredInteger) ((DWORD) GameDll + 0x3CB280);
		MH_CreateHook(GAME_FlushStoredIntegerorg, &GAME_FlushStoredIntegermy, reinterpret_cast<void**>(&GAME_FlushStoredIntegerold));
		MH_EnableHook(GAME_FlushStoredIntegerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_FlushStoredMission", FALSE))
	{
		GAME_FlushStoredMissionorg = (GAME_FlushStoredMission) ((DWORD) GameDll + 0x3CB240);
		MH_CreateHook(GAME_FlushStoredMissionorg, &GAME_FlushStoredMissionmy, reinterpret_cast<void**>(&GAME_FlushStoredMissionold));
		MH_EnableHook(GAME_FlushStoredMissionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_FlushStoredReal", FALSE))
	{
		GAME_FlushStoredRealorg = (GAME_FlushStoredReal) ((DWORD) GameDll + 0x3CB2D0);
		MH_CreateHook(GAME_FlushStoredRealorg, &GAME_FlushStoredRealmy, reinterpret_cast<void**>(&GAME_FlushStoredRealold));
		MH_EnableHook(GAME_FlushStoredRealorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_FlushStoredString", FALSE))
	{
		GAME_FlushStoredStringorg = (GAME_FlushStoredString) ((DWORD) GameDll + 0x3CB3C0);
		MH_CreateHook(GAME_FlushStoredStringorg, &GAME_FlushStoredStringmy, reinterpret_cast<void**>(&GAME_FlushStoredStringold));
		MH_EnableHook(GAME_FlushStoredStringorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_FlushStoredUnit", FALSE))
	{
		GAME_FlushStoredUnitorg = (GAME_FlushStoredUnit) ((DWORD) GameDll + 0x3CB370);
		MH_CreateHook(GAME_FlushStoredUnitorg, &GAME_FlushStoredUnitmy, reinterpret_cast<void**>(&GAME_FlushStoredUnitold));
		MH_EnableHook(GAME_FlushStoredUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_FogEnable", FALSE))
	{
		GAME_FogEnableorg = (GAME_FogEnable) ((DWORD) GameDll + 0x3BB1E0);
		MH_CreateHook(GAME_FogEnableorg, &GAME_FogEnablemy, reinterpret_cast<void**>(&GAME_FogEnableold));
		MH_EnableHook(GAME_FogEnableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_FogMaskEnable", FALSE))
	{
		GAME_FogMaskEnableorg = (GAME_FogMaskEnable) ((DWORD) GameDll + 0x3BB210);
		MH_CreateHook(GAME_FogMaskEnableorg, &GAME_FogMaskEnablemy, reinterpret_cast<void**>(&GAME_FogMaskEnableold));
		MH_EnableHook(GAME_FogMaskEnableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_FogModifierStart", FALSE))
	{
		GAME_FogModifierStartorg = (GAME_FogModifierStart) ((DWORD) GameDll + 0x3C1BC0);
		MH_CreateHook(GAME_FogModifierStartorg, &GAME_FogModifierStartmy, reinterpret_cast<void**>(&GAME_FogModifierStartold));
		MH_EnableHook(GAME_FogModifierStartorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_FogModifierStop", FALSE))
	{
		GAME_FogModifierStoporg = (GAME_FogModifierStop) ((DWORD) GameDll + 0x3C1BE0);
		MH_CreateHook(GAME_FogModifierStoporg, &GAME_FogModifierStopmy, reinterpret_cast<void**>(&GAME_FogModifierStopold));
		MH_EnableHook(GAME_FogModifierStoporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ForForce", FALSE))
	{
		GAME_ForForceorg = (GAME_ForForce) ((DWORD) GameDll + 0x3C4640);
		MH_CreateHook(GAME_ForForceorg, &GAME_ForForcemy, reinterpret_cast<void**>(&GAME_ForForceold));
		MH_EnableHook(GAME_ForForceorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ForGroup", FALSE))
	{
		GAME_ForGrouporg = (GAME_ForGroup) ((DWORD) GameDll + 0x3C44A0);
		MH_CreateHook(GAME_ForGrouporg, &GAME_ForGroupmy, reinterpret_cast<void**>(&GAME_ForGroupold));
		MH_EnableHook(GAME_ForGrouporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ForceAddPlayer", FALSE))
	{
		GAME_ForceAddPlayerorg = (GAME_ForceAddPlayer) ((DWORD) GameDll + 0x3C44E0);
		MH_CreateHook(GAME_ForceAddPlayerorg, &GAME_ForceAddPlayermy, reinterpret_cast<void**>(&GAME_ForceAddPlayerold));
		MH_EnableHook(GAME_ForceAddPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ForceCampaignSelectScreen", FALSE))
	{
		GAME_ForceCampaignSelectScreenorg = (GAME_ForceCampaignSelectScreen) ((DWORD) GameDll + 0x3BC400);
		MH_CreateHook(GAME_ForceCampaignSelectScreenorg, &GAME_ForceCampaignSelectScreenmy, reinterpret_cast<void**>(&GAME_ForceCampaignSelectScreenold));
		MH_EnableHook(GAME_ForceCampaignSelectScreenorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ForceCinematicSubtitles", FALSE))
	{
		GAME_ForceCinematicSubtitlesorg = (GAME_ForceCinematicSubtitles) ((DWORD) GameDll + 0x3B4E40);
		MH_CreateHook(GAME_ForceCinematicSubtitlesorg, &GAME_ForceCinematicSubtitlesmy, reinterpret_cast<void**>(&GAME_ForceCinematicSubtitlesold));
		MH_EnableHook(GAME_ForceCinematicSubtitlesorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ForceClear", FALSE))
	{
		GAME_ForceClearorg = (GAME_ForceClear) ((DWORD) GameDll + 0x3C4540);
		MH_CreateHook(GAME_ForceClearorg, &GAME_ForceClearmy, reinterpret_cast<void**>(&GAME_ForceClearold));
		MH_EnableHook(GAME_ForceClearorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ForceEnumAllies", FALSE))
	{
		GAME_ForceEnumAlliesorg = (GAME_ForceEnumAllies) ((DWORD) GameDll + 0x3C45C0);
		MH_CreateHook(GAME_ForceEnumAlliesorg, &GAME_ForceEnumAlliesmy, reinterpret_cast<void**>(&GAME_ForceEnumAlliesold));
		MH_EnableHook(GAME_ForceEnumAlliesorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ForceEnumEnemies", FALSE))
	{
		GAME_ForceEnumEnemiesorg = (GAME_ForceEnumEnemies) ((DWORD) GameDll + 0x3C4600);
		MH_CreateHook(GAME_ForceEnumEnemiesorg, &GAME_ForceEnumEnemiesmy, reinterpret_cast<void**>(&GAME_ForceEnumEnemiesold));
		MH_EnableHook(GAME_ForceEnumEnemiesorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ForceEnumPlayers", FALSE))
	{
		GAME_ForceEnumPlayersorg = (GAME_ForceEnumPlayers) ((DWORD) GameDll + 0x3C4560);
		MH_CreateHook(GAME_ForceEnumPlayersorg, &GAME_ForceEnumPlayersmy, reinterpret_cast<void**>(&GAME_ForceEnumPlayersold));
		MH_EnableHook(GAME_ForceEnumPlayersorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ForceEnumPlayersCounted", FALSE))
	{
		GAME_ForceEnumPlayersCountedorg = (GAME_ForceEnumPlayersCounted) ((DWORD) GameDll + 0x3C4590);
		MH_CreateHook(GAME_ForceEnumPlayersCountedorg, &GAME_ForceEnumPlayersCountedmy, reinterpret_cast<void**>(&GAME_ForceEnumPlayersCountedold));
		MH_EnableHook(GAME_ForceEnumPlayersCountedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ForcePlayerStartLocation", FALSE))
	{
		GAME_ForcePlayerStartLocationorg = (GAME_ForcePlayerStartLocation) ((DWORD) GameDll + 0x3C0FA0);
		MH_CreateHook(GAME_ForcePlayerStartLocationorg, &GAME_ForcePlayerStartLocationmy, reinterpret_cast<void**>(&GAME_ForcePlayerStartLocationold));
		MH_EnableHook(GAME_ForcePlayerStartLocationorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ForceQuestDialogUpdate", FALSE))
	{
		GAME_ForceQuestDialogUpdateorg = (GAME_ForceQuestDialogUpdate) ((DWORD) GameDll + 0x3B3BE0);
		MH_CreateHook(GAME_ForceQuestDialogUpdateorg, &GAME_ForceQuestDialogUpdatemy, reinterpret_cast<void**>(&GAME_ForceQuestDialogUpdateold));
		MH_EnableHook(GAME_ForceQuestDialogUpdateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ForceRemovePlayer", FALSE))
	{
		GAME_ForceRemovePlayerorg = (GAME_ForceRemovePlayer) ((DWORD) GameDll + 0x3C4510);
		MH_CreateHook(GAME_ForceRemovePlayerorg, &GAME_ForceRemovePlayermy, reinterpret_cast<void**>(&GAME_ForceRemovePlayerold));
		MH_EnableHook(GAME_ForceRemovePlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ForceUICancel", FALSE))
	{
		GAME_ForceUICancelorg = (GAME_ForceUICancel) ((DWORD) GameDll + 0x3B3990);
		MH_CreateHook(GAME_ForceUICancelorg, &GAME_ForceUICancelmy, reinterpret_cast<void**>(&GAME_ForceUICancelold));
		MH_EnableHook(GAME_ForceUICancelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ForceUIKey", FALSE))
	{
		GAME_ForceUIKeyorg = (GAME_ForceUIKey) ((DWORD) GameDll + 0x3B38E0);
		MH_CreateHook(GAME_ForceUIKeyorg, &GAME_ForceUIKeymy, reinterpret_cast<void**>(&GAME_ForceUIKeyold));
		MH_EnableHook(GAME_ForceUIKeyorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetAIDifficulty", FALSE))
	{
		GAME_GetAIDifficultyorg = (GAME_GetAIDifficulty) ((DWORD) GameDll + 0x3CB7E0);
		MH_CreateHook(GAME_GetAIDifficultyorg, &GAME_GetAIDifficultymy, reinterpret_cast<void**>(&GAME_GetAIDifficultyold));
		MH_EnableHook(GAME_GetAIDifficultyorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetAbilityEffect", FALSE))
	{
		GAME_GetAbilityEffectorg = (GAME_GetAbilityEffect) ((DWORD) GameDll + 0x3BCAB0);
		MH_CreateHook(GAME_GetAbilityEffectorg, &GAME_GetAbilityEffectmy, reinterpret_cast<void**>(&GAME_GetAbilityEffectold));
		MH_EnableHook(GAME_GetAbilityEffectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetAbilityEffectById", FALSE))
	{
		GAME_GetAbilityEffectByIdorg = (GAME_GetAbilityEffectById) ((DWORD) GameDll + 0x3BCE40);
		MH_CreateHook(GAME_GetAbilityEffectByIdorg, &GAME_GetAbilityEffectByIdmy, reinterpret_cast<void**>(&GAME_GetAbilityEffectByIdold));
		MH_EnableHook(GAME_GetAbilityEffectByIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetAbilitySound", FALSE))
	{
		GAME_GetAbilitySoundorg = (GAME_GetAbilitySound) ((DWORD) GameDll + 0x3BCE60);
		MH_CreateHook(GAME_GetAbilitySoundorg, &GAME_GetAbilitySoundmy, reinterpret_cast<void**>(&GAME_GetAbilitySoundold));
		MH_EnableHook(GAME_GetAbilitySoundorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetAbilitySoundById", FALSE))
	{
		GAME_GetAbilitySoundByIdorg = (GAME_GetAbilitySoundById) ((DWORD) GameDll + 0x3BCEA0);
		MH_CreateHook(GAME_GetAbilitySoundByIdorg, &GAME_GetAbilitySoundByIdmy, reinterpret_cast<void**>(&GAME_GetAbilitySoundByIdold));
		MH_EnableHook(GAME_GetAbilitySoundByIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetAiPlayer", FALSE))
	{
		GAME_GetAiPlayerorg = (GAME_GetAiPlayer) ((DWORD) GameDll + 0x2DCFE0);
		MH_CreateHook(GAME_GetAiPlayerorg, &GAME_GetAiPlayermy, reinterpret_cast<void**>(&GAME_GetAiPlayerold));
		MH_EnableHook(GAME_GetAiPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Ordinal266", FALSE))
	{
		GAME_Ordinal266org = (GAME_Ordinal266) ((DWORD) GameDll + 0x1D3B0);
		MH_CreateHook(GAME_Ordinal266org, &GAME_Ordinal266my, reinterpret_cast<void**>(&GAME_Ordinal266old));
		MH_EnableHook(GAME_Ordinal266org);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Ordinal293", FALSE))
	{
		GAME_Ordinal293org = (GAME_Ordinal293) ((DWORD) GameDll + 0x1D600);
		MH_CreateHook(GAME_Ordinal293org, &GAME_Ordinal293my, reinterpret_cast<void**>(&GAME_Ordinal293old));
		MH_EnableHook(GAME_Ordinal293org);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_AutoCast", FALSE))
	{
		GAME_AutoCastorg = (GAME_AutoCast) ((DWORD) GameDll + 0x26FA80);
		MH_CreateHook(GAME_AutoCastorg, &GAME_AutoCastmy, reinterpret_cast<void**>(&GAME_AutoCastold));
		MH_EnableHook(GAME_AutoCastorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_INIDEB", FALSE))
	{
		GAME_INIDEBorg = (GAME_INIDEB) ((DWORD) GameDll + 0x33600);
		MH_CreateHook(GAME_INIDEBorg, &GAME_INIDEBmy, reinterpret_cast<void**>(&GAME_INIDEBold));
		MH_EnableHook(GAME_INIDEBorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetAllianceTarget", FALSE))
	{
		GAME_GetAllianceTargetorg = (GAME_GetAllianceTarget) ((DWORD) GameDll + 0x2DD570);
		MH_CreateHook(GAME_GetAllianceTargetorg, &GAME_GetAllianceTargetmy, reinterpret_cast<void**>(&GAME_GetAllianceTargetold));
		MH_EnableHook(GAME_GetAllianceTargetorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetAllyColorFilterState", FALSE))
	{
		GAME_GetAllyColorFilterStateorg = (GAME_GetAllyColorFilterState) ((DWORD) GameDll + 0x3B3A50);
		MH_CreateHook(GAME_GetAllyColorFilterStateorg, &GAME_GetAllyColorFilterStatemy, reinterpret_cast<void**>(&GAME_GetAllyColorFilterStateold));
		MH_EnableHook(GAME_GetAllyColorFilterStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetAttacker", FALSE))
	{
		GAME_GetAttackerorg = (GAME_GetAttacker) ((DWORD) GameDll + 0x3C20F0);
		MH_CreateHook(GAME_GetAttackerorg, &GAME_GetAttackermy, reinterpret_cast<void**>(&GAME_GetAttackerold));
		MH_EnableHook(GAME_GetAttackerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetBuilding", FALSE))
	{
		GAME_GetBuildingorg = (GAME_GetBuilding) ((DWORD) GameDll + 0x2E2E80);
		MH_CreateHook(GAME_GetBuildingorg, &GAME_GetBuildingmy, reinterpret_cast<void**>(&GAME_GetBuildingold));
		MH_EnableHook(GAME_GetBuildingorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetBuyingUnit", FALSE))
	{
		GAME_GetBuyingUnitorg = (GAME_GetBuyingUnit) ((DWORD) GameDll + 0x3C27B0);
		MH_CreateHook(GAME_GetBuyingUnitorg, &GAME_GetBuyingUnitmy, reinterpret_cast<void**>(&GAME_GetBuyingUnitold));
		MH_EnableHook(GAME_GetBuyingUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCameraBoundMaxX", FALSE))
	{
		GAME_GetCameraBoundMaxXorg = (GAME_GetCameraBoundMaxX) ((DWORD) GameDll + 0x3B4C90);
		MH_CreateHook(GAME_GetCameraBoundMaxXorg, &GAME_GetCameraBoundMaxXmy, reinterpret_cast<void**>(&GAME_GetCameraBoundMaxXold));
		MH_EnableHook(GAME_GetCameraBoundMaxXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCameraBoundMaxY", FALSE))
	{
		GAME_GetCameraBoundMaxYorg = (GAME_GetCameraBoundMaxY) ((DWORD) GameDll + 0x3B4CB0);
		MH_CreateHook(GAME_GetCameraBoundMaxYorg, &GAME_GetCameraBoundMaxYmy, reinterpret_cast<void**>(&GAME_GetCameraBoundMaxYold));
		MH_EnableHook(GAME_GetCameraBoundMaxYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCameraBoundMinX", FALSE))
	{
		GAME_GetCameraBoundMinXorg = (GAME_GetCameraBoundMinX) ((DWORD) GameDll + 0x3B4C50);
		MH_CreateHook(GAME_GetCameraBoundMinXorg, &GAME_GetCameraBoundMinXmy, reinterpret_cast<void**>(&GAME_GetCameraBoundMinXold));
		MH_EnableHook(GAME_GetCameraBoundMinXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCameraBoundMinY", FALSE))
	{
		GAME_GetCameraBoundMinYorg = (GAME_GetCameraBoundMinY) ((DWORD) GameDll + 0x3B4C70);
		MH_CreateHook(GAME_GetCameraBoundMinYorg, &GAME_GetCameraBoundMinYmy, reinterpret_cast<void**>(&GAME_GetCameraBoundMinYold));
		MH_EnableHook(GAME_GetCameraBoundMinYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCameraEyePositionLoc", FALSE))
	{
		GAME_GetCameraEyePositionLocorg = (GAME_GetCameraEyePositionLoc) ((DWORD) GameDll + 0x3D3EE0);
		MH_CreateHook(GAME_GetCameraEyePositionLocorg, &GAME_GetCameraEyePositionLocmy, reinterpret_cast<void**>(&GAME_GetCameraEyePositionLocold));
		MH_EnableHook(GAME_GetCameraEyePositionLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCameraEyePositionX", FALSE))
	{
		GAME_GetCameraEyePositionXorg = (GAME_GetCameraEyePositionX) ((DWORD) GameDll + 0x3B4D90);
		MH_CreateHook(GAME_GetCameraEyePositionXorg, &GAME_GetCameraEyePositionXmy, reinterpret_cast<void**>(&GAME_GetCameraEyePositionXold));
		MH_EnableHook(GAME_GetCameraEyePositionXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCameraEyePositionY", FALSE))
	{
		GAME_GetCameraEyePositionYorg = (GAME_GetCameraEyePositionY) ((DWORD) GameDll + 0x3B4DC0);
		MH_CreateHook(GAME_GetCameraEyePositionYorg, &GAME_GetCameraEyePositionYmy, reinterpret_cast<void**>(&GAME_GetCameraEyePositionYold));
		MH_EnableHook(GAME_GetCameraEyePositionYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCameraEyePositionZ", FALSE))
	{
		GAME_GetCameraEyePositionZorg = (GAME_GetCameraEyePositionZ) ((DWORD) GameDll + 0x3B4DF0);
		MH_CreateHook(GAME_GetCameraEyePositionZorg, &GAME_GetCameraEyePositionZmy, reinterpret_cast<void**>(&GAME_GetCameraEyePositionZold));
		MH_EnableHook(GAME_GetCameraEyePositionZorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCameraField", FALSE))
	{
		GAME_GetCameraFieldorg = (GAME_GetCameraField) ((DWORD) GameDll + 0x3B4CD0);
		MH_CreateHook(GAME_GetCameraFieldorg, &GAME_GetCameraFieldmy, reinterpret_cast<void**>(&GAME_GetCameraFieldold));
		MH_EnableHook(GAME_GetCameraFieldorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCameraMargin", FALSE))
	{
		GAME_GetCameraMarginorg = (GAME_GetCameraMargin) ((DWORD) GameDll + 0x3B4BE0);
		MH_CreateHook(GAME_GetCameraMarginorg, &GAME_GetCameraMarginmy, reinterpret_cast<void**>(&GAME_GetCameraMarginold));
		MH_EnableHook(GAME_GetCameraMarginorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCameraTargetPositionLoc", FALSE))
	{
		GAME_GetCameraTargetPositionLocorg = (GAME_GetCameraTargetPositionLoc) ((DWORD) GameDll + 0x3D3E90);
		MH_CreateHook(GAME_GetCameraTargetPositionLocorg, &GAME_GetCameraTargetPositionLocmy, reinterpret_cast<void**>(&GAME_GetCameraTargetPositionLocold));
		MH_EnableHook(GAME_GetCameraTargetPositionLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCameraTargetPositionX", FALSE))
	{
		GAME_GetCameraTargetPositionXorg = (GAME_GetCameraTargetPositionX) ((DWORD) GameDll + 0x3B4D00);
		MH_CreateHook(GAME_GetCameraTargetPositionXorg, &GAME_GetCameraTargetPositionXmy, reinterpret_cast<void**>(&GAME_GetCameraTargetPositionXold));
		MH_EnableHook(GAME_GetCameraTargetPositionXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCameraTargetPositionY", FALSE))
	{
		GAME_GetCameraTargetPositionYorg = (GAME_GetCameraTargetPositionY) ((DWORD) GameDll + 0x3B4D30);
		MH_CreateHook(GAME_GetCameraTargetPositionYorg, &GAME_GetCameraTargetPositionYmy, reinterpret_cast<void**>(&GAME_GetCameraTargetPositionYold));
		MH_EnableHook(GAME_GetCameraTargetPositionYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCameraTargetPositionZ", FALSE))
	{
		GAME_GetCameraTargetPositionZorg = (GAME_GetCameraTargetPositionZ) ((DWORD) GameDll + 0x3B4D60);
		MH_CreateHook(GAME_GetCameraTargetPositionZorg, &GAME_GetCameraTargetPositionZmy, reinterpret_cast<void**>(&GAME_GetCameraTargetPositionZold));
		MH_EnableHook(GAME_GetCameraTargetPositionZorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCancelledStructure", FALSE))
	{
		GAME_GetCancelledStructureorg = (GAME_GetCancelledStructure) ((DWORD) GameDll + 0x3BB470);
		MH_CreateHook(GAME_GetCancelledStructureorg, &GAME_GetCancelledStructuremy, reinterpret_cast<void**>(&GAME_GetCancelledStructureold));
		MH_EnableHook(GAME_GetCancelledStructureorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetChangingUnit", FALSE))
	{
		GAME_GetChangingUnitorg = (GAME_GetChangingUnit) ((DWORD) GameDll + 0x3C2680);
		MH_CreateHook(GAME_GetChangingUnitorg, &GAME_GetChangingUnitmy, reinterpret_cast<void**>(&GAME_GetChangingUnitold));
		MH_EnableHook(GAME_GetChangingUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetChangingUnitPrevOwner", FALSE))
	{
		GAME_GetChangingUnitPrevOwnerorg = (GAME_GetChangingUnitPrevOwner) ((DWORD) GameDll + 0x3C26E0);
		MH_CreateHook(GAME_GetChangingUnitPrevOwnerorg, &GAME_GetChangingUnitPrevOwnermy, reinterpret_cast<void**>(&GAME_GetChangingUnitPrevOwnerold));
		MH_EnableHook(GAME_GetChangingUnitPrevOwnerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetClickedButton", FALSE))
	{
		GAME_GetClickedButtonorg = (GAME_GetClickedButton) ((DWORD) GameDll + 0x3C1DE0);
		MH_CreateHook(GAME_GetClickedButtonorg, &GAME_GetClickedButtonmy, reinterpret_cast<void**>(&GAME_GetClickedButtonold));
		MH_EnableHook(GAME_GetClickedButtonorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetClickedDialog", FALSE))
	{
		GAME_GetClickedDialogorg = (GAME_GetClickedDialog) ((DWORD) GameDll + 0x3C1E30);
		MH_CreateHook(GAME_GetClickedDialogorg, &GAME_GetClickedDialogmy, reinterpret_cast<void**>(&GAME_GetClickedDialogold));
		MH_EnableHook(GAME_GetClickedDialogorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetConstructedStructure", FALSE))
	{
		GAME_GetConstructedStructureorg = (GAME_GetConstructedStructure) ((DWORD) GameDll + 0x3BB490);
		MH_CreateHook(GAME_GetConstructedStructureorg, &GAME_GetConstructedStructuremy, reinterpret_cast<void**>(&GAME_GetConstructedStructureold));
		MH_EnableHook(GAME_GetConstructedStructureorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetConstructingStructure", FALSE))
	{
		GAME_GetConstructingStructureorg = (GAME_GetConstructingStructure) ((DWORD) GameDll + 0x3BB450);
		MH_CreateHook(GAME_GetConstructingStructureorg, &GAME_GetConstructingStructuremy, reinterpret_cast<void**>(&GAME_GetConstructingStructureold));
		MH_EnableHook(GAME_GetConstructingStructureorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCreatureDensity", FALSE))
	{
		GAME_GetCreatureDensityorg = (GAME_GetCreatureDensity) ((DWORD) GameDll + 0x3BAF60);
		MH_CreateHook(GAME_GetCreatureDensityorg, &GAME_GetCreatureDensitymy, reinterpret_cast<void**>(&GAME_GetCreatureDensityold));
		MH_EnableHook(GAME_GetCreatureDensityorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCreepCamp", FALSE))
	{
		GAME_GetCreepCamporg = (GAME_GetCreepCamp) ((DWORD) GameDll + 0x2E3D50);
		MH_CreateHook(GAME_GetCreepCamporg, &GAME_GetCreepCampmy, reinterpret_cast<void**>(&GAME_GetCreepCampold));
		MH_EnableHook(GAME_GetCreepCamporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCreepCampFilterState", FALSE))
	{
		GAME_GetCreepCampFilterStateorg = (GAME_GetCreepCampFilterState) ((DWORD) GameDll + 0x3B3AA0);
		MH_CreateHook(GAME_GetCreepCampFilterStateorg, &GAME_GetCreepCampFilterStatemy, reinterpret_cast<void**>(&GAME_GetCreepCampFilterStateold));
		MH_EnableHook(GAME_GetCreepCampFilterStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetCustomCampaignButtonVisible", FALSE))
	{
		GAME_GetCustomCampaignButtonVisibleorg = (GAME_GetCustomCampaignButtonVisible) ((DWORD) GameDll + 0x3B3530);
		MH_CreateHook(GAME_GetCustomCampaignButtonVisibleorg, &GAME_GetCustomCampaignButtonVisiblemy, reinterpret_cast<void**>(&GAME_GetCustomCampaignButtonVisibleold));
		MH_EnableHook(GAME_GetCustomCampaignButtonVisibleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetDecayingUnit", FALSE))
	{
		GAME_GetDecayingUnitorg = (GAME_GetDecayingUnit) ((DWORD) GameDll + 0x3BB430);
		MH_CreateHook(GAME_GetDecayingUnitorg, &GAME_GetDecayingUnitmy, reinterpret_cast<void**>(&GAME_GetDecayingUnitold));
		MH_EnableHook(GAME_GetDecayingUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetDefaultDifficulty", FALSE))
	{
		GAME_GetDefaultDifficultyorg = (GAME_GetDefaultDifficulty) ((DWORD) GameDll + 0x3B33A0);
		MH_CreateHook(GAME_GetDefaultDifficultyorg, &GAME_GetDefaultDifficultymy, reinterpret_cast<void**>(&GAME_GetDefaultDifficultyold));
		MH_EnableHook(GAME_GetDefaultDifficultyorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetDestructableLife", FALSE))
	{
		GAME_GetDestructableLifeorg = (GAME_GetDestructableLife) ((DWORD) GameDll + 0x3C4890);
		MH_CreateHook(GAME_GetDestructableLifeorg, &GAME_GetDestructableLifemy, reinterpret_cast<void**>(&GAME_GetDestructableLifeold));
		MH_EnableHook(GAME_GetDestructableLifeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetDestructableMaxLife", FALSE))
	{
		GAME_GetDestructableMaxLifeorg = (GAME_GetDestructableMaxLife) ((DWORD) GameDll + 0x3C4920);
		MH_CreateHook(GAME_GetDestructableMaxLifeorg, &GAME_GetDestructableMaxLifemy, reinterpret_cast<void**>(&GAME_GetDestructableMaxLifeold));
		MH_EnableHook(GAME_GetDestructableMaxLifeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetDestructableName", FALSE))
	{
		GAME_GetDestructableNameorg = (GAME_GetDestructableName) ((DWORD) GameDll + 0x3C4C10);
		MH_CreateHook(GAME_GetDestructableNameorg, &GAME_GetDestructableNamemy, reinterpret_cast<void**>(&GAME_GetDestructableNameold));
		MH_EnableHook(GAME_GetDestructableNameorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetDestructableOccluderHeight", FALSE))
	{
		GAME_GetDestructableOccluderHeightorg = (GAME_GetDestructableOccluderHeight) ((DWORD) GameDll + 0x3C4BB0);
		MH_CreateHook(GAME_GetDestructableOccluderHeightorg, &GAME_GetDestructableOccluderHeightmy, reinterpret_cast<void**>(&GAME_GetDestructableOccluderHeightold));
		MH_EnableHook(GAME_GetDestructableOccluderHeightorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetDestructableTypeId", FALSE))
	{
		GAME_GetDestructableTypeIdorg = (GAME_GetDestructableTypeId) ((DWORD) GameDll + 0x3C47B0);
		MH_CreateHook(GAME_GetDestructableTypeIdorg, &GAME_GetDestructableTypeIdmy, reinterpret_cast<void**>(&GAME_GetDestructableTypeIdold));
		MH_EnableHook(GAME_GetDestructableTypeIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetDestructableX", FALSE))
	{
		GAME_GetDestructableXorg = (GAME_GetDestructableX) ((DWORD) GameDll + 0x3C47D0);
		MH_CreateHook(GAME_GetDestructableXorg, &GAME_GetDestructableXmy, reinterpret_cast<void**>(&GAME_GetDestructableXold));
		MH_EnableHook(GAME_GetDestructableXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetDestructableY", FALSE))
	{
		GAME_GetDestructableYorg = (GAME_GetDestructableY) ((DWORD) GameDll + 0x3C4810);
		MH_CreateHook(GAME_GetDestructableYorg, &GAME_GetDestructableYmy, reinterpret_cast<void**>(&GAME_GetDestructableYold));
		MH_EnableHook(GAME_GetDestructableYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetDetectedUnit", FALSE))
	{
		GAME_GetDetectedUnitorg = (GAME_GetDetectedUnit) ((DWORD) GameDll + 0x3BB4B0);
		MH_CreateHook(GAME_GetDetectedUnitorg, &GAME_GetDetectedUnitmy, reinterpret_cast<void**>(&GAME_GetDetectedUnitold));
		MH_EnableHook(GAME_GetDetectedUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetDyingUnit", FALSE))
	{
		GAME_GetDyingUnitorg = (GAME_GetDyingUnit) ((DWORD) GameDll + 0x3BB410);
		MH_CreateHook(GAME_GetDyingUnitorg, &GAME_GetDyingUnitmy, reinterpret_cast<void**>(&GAME_GetDyingUnitold));
		MH_EnableHook(GAME_GetDyingUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetEnemyBase", FALSE))
	{
		GAME_GetEnemyBaseorg = (GAME_GetEnemyBase) ((DWORD) GameDll + 0x2DDD20);
		MH_CreateHook(GAME_GetEnemyBaseorg, &GAME_GetEnemyBasemy, reinterpret_cast<void**>(&GAME_GetEnemyBaseold));
		MH_EnableHook(GAME_GetEnemyBaseorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetEnemyExpansion", FALSE))
	{
		GAME_GetEnemyExpansionorg = (GAME_GetEnemyExpansion) ((DWORD) GameDll + 0x2DD4F0);
		MH_CreateHook(GAME_GetEnemyExpansionorg, &GAME_GetEnemyExpansionmy, reinterpret_cast<void**>(&GAME_GetEnemyExpansionold));
		MH_EnableHook(GAME_GetEnemyExpansionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetEnemyPower", FALSE))
	{
		GAME_GetEnemyPowerorg = (GAME_GetEnemyPower) ((DWORD) GameDll + 0x2DC150);
		MH_CreateHook(GAME_GetEnemyPowerorg, &GAME_GetEnemyPowermy, reinterpret_cast<void**>(&GAME_GetEnemyPowerold));
		MH_EnableHook(GAME_GetEnemyPowerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetEnteringUnit", FALSE))
	{
		GAME_GetEnteringUnitorg = (GAME_GetEnteringUnit) ((DWORD) GameDll + 0x3BB6D0);
		MH_CreateHook(GAME_GetEnteringUnitorg, &GAME_GetEnteringUnitmy, reinterpret_cast<void**>(&GAME_GetEnteringUnitold));
		MH_EnableHook(GAME_GetEnteringUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetEnumDestructable", FALSE))
	{
		GAME_GetEnumDestructableorg = (GAME_GetEnumDestructable) ((DWORD) GameDll + 0x3BB360);
		MH_CreateHook(GAME_GetEnumDestructableorg, &GAME_GetEnumDestructablemy, reinterpret_cast<void**>(&GAME_GetEnumDestructableold));
		MH_EnableHook(GAME_GetEnumDestructableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetEnumItem", FALSE))
	{
		GAME_GetEnumItemorg = (GAME_GetEnumItem) ((DWORD) GameDll + 0x3BB3A0);
		MH_CreateHook(GAME_GetEnumItemorg, &GAME_GetEnumItemmy, reinterpret_cast<void**>(&GAME_GetEnumItemold));
		MH_EnableHook(GAME_GetEnumItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetEnumPlayer", FALSE))
	{
		GAME_GetEnumPlayerorg = (GAME_GetEnumPlayer) ((DWORD) GameDll + 0x3BB320);
		MH_CreateHook(GAME_GetEnumPlayerorg, &GAME_GetEnumPlayermy, reinterpret_cast<void**>(&GAME_GetEnumPlayerold));
		MH_EnableHook(GAME_GetEnumPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetEnumUnit", FALSE))
	{
		GAME_GetEnumUnitorg = (GAME_GetEnumUnit) ((DWORD) GameDll + 0x3BB300);
		MH_CreateHook(GAME_GetEnumUnitorg, &GAME_GetEnumUnitmy, reinterpret_cast<void**>(&GAME_GetEnumUnitold));
		MH_EnableHook(GAME_GetEnumUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetEventDamage", FALSE))
	{
		GAME_GetEventDamageorg = (GAME_GetEventDamage) ((DWORD) GameDll + 0x3C3C40);
		MH_CreateHook(GAME_GetEventDamageorg, &GAME_GetEventDamagemy, reinterpret_cast<void**>(&GAME_GetEventDamageold));
		MH_EnableHook(GAME_GetEventDamageorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetEventDamageSource", FALSE))
	{
		GAME_GetEventDamageSourceorg = (GAME_GetEventDamageSource) ((DWORD) GameDll + 0x3C3C60);
		MH_CreateHook(GAME_GetEventDamageSourceorg, &GAME_GetEventDamageSourcemy, reinterpret_cast<void**>(&GAME_GetEventDamageSourceold));
		MH_EnableHook(GAME_GetEventDamageSourceorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetEventDetectingPlayer", FALSE))
	{
		GAME_GetEventDetectingPlayerorg = (GAME_GetEventDetectingPlayer) ((DWORD) GameDll + 0x3C3CB0);
		MH_CreateHook(GAME_GetEventDetectingPlayerorg, &GAME_GetEventDetectingPlayermy, reinterpret_cast<void**>(&GAME_GetEventDetectingPlayerold));
		MH_EnableHook(GAME_GetEventDetectingPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetEventGameState", FALSE))
	{
		GAME_GetEventGameStateorg = (GAME_GetEventGameState) ((DWORD) GameDll + 0x3C2020);
		MH_CreateHook(GAME_GetEventGameStateorg, &GAME_GetEventGameStatemy, reinterpret_cast<void**>(&GAME_GetEventGameStateold));
		MH_EnableHook(GAME_GetEventGameStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetEventPlayerChatString", FALSE))
	{
		GAME_GetEventPlayerChatStringorg = (GAME_GetEventPlayerChatString) ((DWORD) GameDll + 0x3C20B0);
		MH_CreateHook(GAME_GetEventPlayerChatStringorg, &GAME_GetEventPlayerChatStringmy, reinterpret_cast<void**>(&GAME_GetEventPlayerChatStringold));
		MH_EnableHook(GAME_GetEventPlayerChatStringorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetEventPlayerChatStringMatched", FALSE))
	{
		GAME_GetEventPlayerChatStringMatchedorg = (GAME_GetEventPlayerChatStringMatched) ((DWORD) GameDll + 0x3C2080);
		MH_CreateHook(GAME_GetEventPlayerChatStringMatchedorg, &GAME_GetEventPlayerChatStringMatchedmy, reinterpret_cast<void**>(&GAME_GetEventPlayerChatStringMatchedold));
		MH_EnableHook(GAME_GetEventPlayerChatStringMatchedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetEventPlayerState", FALSE))
	{
		GAME_GetEventPlayerStateorg = (GAME_GetEventPlayerState) ((DWORD) GameDll + 0x3C2050);
		MH_CreateHook(GAME_GetEventPlayerStateorg, &GAME_GetEventPlayerStatemy, reinterpret_cast<void**>(&GAME_GetEventPlayerStateold));
		MH_EnableHook(GAME_GetEventPlayerStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetEventTargetUnit", FALSE))
	{
		GAME_GetEventTargetUnitorg = (GAME_GetEventTargetUnit) ((DWORD) GameDll + 0x3C3D00);
		MH_CreateHook(GAME_GetEventTargetUnitorg, &GAME_GetEventTargetUnitmy, reinterpret_cast<void**>(&GAME_GetEventTargetUnitold));
		MH_EnableHook(GAME_GetEventTargetUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetEventUnitState", FALSE))
	{
		GAME_GetEventUnitStateorg = (GAME_GetEventUnitState) ((DWORD) GameDll + 0x3C3C10);
		MH_CreateHook(GAME_GetEventUnitStateorg, &GAME_GetEventUnitStatemy, reinterpret_cast<void**>(&GAME_GetEventUnitStateold));
		MH_EnableHook(GAME_GetEventUnitStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetExpansionFoe", FALSE))
	{
		GAME_GetExpansionFoeorg = (GAME_GetExpansionFoe) ((DWORD) GameDll + 0x2E2E40);
		MH_CreateHook(GAME_GetExpansionFoeorg, &GAME_GetExpansionFoemy, reinterpret_cast<void**>(&GAME_GetExpansionFoeold));
		MH_EnableHook(GAME_GetExpansionFoeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetExpansionPeon", FALSE))
	{
		GAME_GetExpansionPeonorg = (GAME_GetExpansionPeon) ((DWORD) GameDll + 0x2DD530);
		MH_CreateHook(GAME_GetExpansionPeonorg, &GAME_GetExpansionPeonmy, reinterpret_cast<void**>(&GAME_GetExpansionPeonold));
		MH_EnableHook(GAME_GetExpansionPeonorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetExpansionX", FALSE))
	{
		GAME_GetExpansionXorg = (GAME_GetExpansionX) ((DWORD) GameDll + 0x2E2DA0);
		MH_CreateHook(GAME_GetExpansionXorg, &GAME_GetExpansionXmy, reinterpret_cast<void**>(&GAME_GetExpansionXold));
		MH_EnableHook(GAME_GetExpansionXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetExpansionY", FALSE))
	{
		GAME_GetExpansionYorg = (GAME_GetExpansionY) ((DWORD) GameDll + 0x2E2DF0);
		MH_CreateHook(GAME_GetExpansionYorg, &GAME_GetExpansionYmy, reinterpret_cast<void**>(&GAME_GetExpansionYold));
		MH_EnableHook(GAME_GetExpansionYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetExpiredTimer", FALSE))
	{
		GAME_GetExpiredTimerorg = (GAME_GetExpiredTimer) ((DWORD) GameDll + 0x3C1D80);
		MH_CreateHook(GAME_GetExpiredTimerorg, &GAME_GetExpiredTimermy, reinterpret_cast<void**>(&GAME_GetExpiredTimerold));
		MH_EnableHook(GAME_GetExpiredTimerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetFilterDestructable", FALSE))
	{
		GAME_GetFilterDestructableorg = (GAME_GetFilterDestructable) ((DWORD) GameDll + 0x3BB380);
		MH_CreateHook(GAME_GetFilterDestructableorg, &GAME_GetFilterDestructablemy, reinterpret_cast<void**>(&GAME_GetFilterDestructableold));
		MH_EnableHook(GAME_GetFilterDestructableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetFilterItem", FALSE))
	{
		GAME_GetFilterItemorg = (GAME_GetFilterItem) ((DWORD) GameDll + 0x3BB3C0);
		MH_CreateHook(GAME_GetFilterItemorg, &GAME_GetFilterItemmy, reinterpret_cast<void**>(&GAME_GetFilterItemold));
		MH_EnableHook(GAME_GetFilterItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetFilterPlayer", FALSE))
	{
		GAME_GetFilterPlayerorg = (GAME_GetFilterPlayer) ((DWORD) GameDll + 0x3BB340);
		MH_CreateHook(GAME_GetFilterPlayerorg, &GAME_GetFilterPlayermy, reinterpret_cast<void**>(&GAME_GetFilterPlayerold));
		MH_EnableHook(GAME_GetFilterPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetFilterUnit", FALSE))
	{
		GAME_GetFilterUnitorg = (GAME_GetFilterUnit) ((DWORD) GameDll + 0x3BB2E0);
		MH_CreateHook(GAME_GetFilterUnitorg, &GAME_GetFilterUnitmy, reinterpret_cast<void**>(&GAME_GetFilterUnitold));
		MH_EnableHook(GAME_GetFilterUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetFloatGameState", FALSE))
	{
		GAME_GetFloatGameStateorg = (GAME_GetFloatGameState) ((DWORD) GameDll + 0x3BC310);
		MH_CreateHook(GAME_GetFloatGameStateorg, &GAME_GetFloatGameStatemy, reinterpret_cast<void**>(&GAME_GetFloatGameStateold));
		MH_EnableHook(GAME_GetFloatGameStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetFoodMade", FALSE))
	{
		GAME_GetFoodMadeorg = (GAME_GetFoodMade) ((DWORD) GameDll + 0x3B2E00);
		MH_CreateHook(GAME_GetFoodMadeorg, &GAME_GetFoodMademy, reinterpret_cast<void**>(&GAME_GetFoodMadeold));
		MH_EnableHook(GAME_GetFoodMadeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetFoodUsed", FALSE))
	{
		GAME_GetFoodUsedorg = (GAME_GetFoodUsed) ((DWORD) GameDll + 0x3B2E10);
		MH_CreateHook(GAME_GetFoodUsedorg, &GAME_GetFoodUsedmy, reinterpret_cast<void**>(&GAME_GetFoodUsedold));
		MH_EnableHook(GAME_GetFoodUsedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetGameDifficulty", FALSE))
	{
		GAME_GetGameDifficultyorg = (GAME_GetGameDifficulty) ((DWORD) GameDll + 0x3BAF20);
		MH_CreateHook(GAME_GetGameDifficultyorg, &GAME_GetGameDifficultymy, reinterpret_cast<void**>(&GAME_GetGameDifficultyold));
		MH_EnableHook(GAME_GetGameDifficultyorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetGamePlacement", FALSE))
	{
		GAME_GetGamePlacementorg = (GAME_GetGamePlacement) ((DWORD) GameDll + 0x3BAF00);
		MH_CreateHook(GAME_GetGamePlacementorg, &GAME_GetGamePlacementmy, reinterpret_cast<void**>(&GAME_GetGamePlacementold));
		MH_EnableHook(GAME_GetGamePlacementorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetGameSpeed", FALSE))
	{
		GAME_GetGameSpeedorg = (GAME_GetGameSpeed) ((DWORD) GameDll + 0x3BAEC0);
		MH_CreateHook(GAME_GetGameSpeedorg, &GAME_GetGameSpeedmy, reinterpret_cast<void**>(&GAME_GetGameSpeedold));
		MH_EnableHook(GAME_GetGameSpeedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetGameTypeSelected", FALSE))
	{
		GAME_GetGameTypeSelectedorg = (GAME_GetGameTypeSelected) ((DWORD) GameDll + 0x3BAE60);
		MH_CreateHook(GAME_GetGameTypeSelectedorg, &GAME_GetGameTypeSelectedmy, reinterpret_cast<void**>(&GAME_GetGameTypeSelectedold));
		MH_EnableHook(GAME_GetGameTypeSelectedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetGoldOwned", FALSE))
	{
		GAME_GetGoldOwnedorg = (GAME_GetGoldOwned) ((DWORD) GameDll + 0x2DE000);
		MH_CreateHook(GAME_GetGoldOwnedorg, &GAME_GetGoldOwnedmy, reinterpret_cast<void**>(&GAME_GetGoldOwnedold));
		MH_EnableHook(GAME_GetGoldOwnedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetHandleId", FALSE))
	{
		GAME_GetHandleIdorg = (GAME_GetHandleId) ((DWORD) GameDll + 0x3B2D00);
		MH_CreateHook(GAME_GetHandleIdorg, &GAME_GetHandleIdmy, reinterpret_cast<void**>(&GAME_GetHandleIdold));
		MH_EnableHook(GAME_GetHandleIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetHeroAgi", FALSE))
	{
		GAME_GetHeroAgiorg = (GAME_GetHeroAgi) ((DWORD) GameDll + 0x3C6850);
		MH_CreateHook(GAME_GetHeroAgiorg, &GAME_GetHeroAgimy, reinterpret_cast<void**>(&GAME_GetHeroAgiold));
		MH_EnableHook(GAME_GetHeroAgiorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetHeroId", FALSE))
	{
		GAME_GetHeroIdorg = (GAME_GetHeroId) ((DWORD) GameDll + 0x2DDF50);
		MH_CreateHook(GAME_GetHeroIdorg, &GAME_GetHeroIdmy, reinterpret_cast<void**>(&GAME_GetHeroIdold));
		MH_EnableHook(GAME_GetHeroIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetHeroInt", FALSE))
	{
		GAME_GetHeroIntorg = (GAME_GetHeroInt) ((DWORD) GameDll + 0x3C68C0);
		MH_CreateHook(GAME_GetHeroIntorg, &GAME_GetHeroIntmy, reinterpret_cast<void**>(&GAME_GetHeroIntold));
		MH_EnableHook(GAME_GetHeroIntorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetHeroLevel", FALSE))
	{
		GAME_GetHeroLevelorg = (GAME_GetHeroLevel) ((DWORD) GameDll + 0x3C6ED0);
		MH_CreateHook(GAME_GetHeroLevelorg, &GAME_GetHeroLevelmy, reinterpret_cast<void**>(&GAME_GetHeroLevelold));
		MH_EnableHook(GAME_GetHeroLevelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetHeroLevelAI", FALSE))
	{
		GAME_GetHeroLevelAIorg = (GAME_GetHeroLevelAI) ((DWORD) GameDll + 0x2DE0E0);
		MH_CreateHook(GAME_GetHeroLevelAIorg, &GAME_GetHeroLevelAImy, reinterpret_cast<void**>(&GAME_GetHeroLevelAIold));
		MH_EnableHook(GAME_GetHeroLevelAIorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetHeroProperName", FALSE))
	{
		GAME_GetHeroProperNameorg = (GAME_GetHeroProperName) ((DWORD) GameDll + 0x3C6FA0);
		MH_CreateHook(GAME_GetHeroProperNameorg, &GAME_GetHeroProperNamemy, reinterpret_cast<void**>(&GAME_GetHeroProperNameold));
		MH_EnableHook(GAME_GetHeroProperNameorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetHeroSkillPoints", FALSE))
	{
		GAME_GetHeroSkillPointsorg = (GAME_GetHeroSkillPoints) ((DWORD) GameDll + 0x3C6780);
		MH_CreateHook(GAME_GetHeroSkillPointsorg, &GAME_GetHeroSkillPointsmy, reinterpret_cast<void**>(&GAME_GetHeroSkillPointsold));
		MH_EnableHook(GAME_GetHeroSkillPointsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetHeroStr", FALSE))
	{
		GAME_GetHeroStrorg = (GAME_GetHeroStr) ((DWORD) GameDll + 0x3C67E0);
		MH_CreateHook(GAME_GetHeroStrorg, &GAME_GetHeroStrmy, reinterpret_cast<void**>(&GAME_GetHeroStrold));
		MH_EnableHook(GAME_GetHeroStrorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetHeroXP", FALSE))
	{
		GAME_GetHeroXPorg = (GAME_GetHeroXP) ((DWORD) GameDll + 0x3C6A10);
		MH_CreateHook(GAME_GetHeroXPorg, &GAME_GetHeroXPmy, reinterpret_cast<void**>(&GAME_GetHeroXPold));
		MH_EnableHook(GAME_GetHeroXPorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetIntegerGameState", FALSE))
	{
		GAME_GetIntegerGameStateorg = (GAME_GetIntegerGameState) ((DWORD) GameDll + 0x3BC380);
		MH_CreateHook(GAME_GetIntegerGameStateorg, &GAME_GetIntegerGameStatemy, reinterpret_cast<void**>(&GAME_GetIntegerGameStateold));
		MH_EnableHook(GAME_GetIntegerGameStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetIssuedOrderId", FALSE))
	{
		GAME_GetIssuedOrderIdorg = (GAME_GetIssuedOrderId) ((DWORD) GameDll + 0x3C2C80);
		MH_CreateHook(GAME_GetIssuedOrderIdorg, &GAME_GetIssuedOrderIdmy, reinterpret_cast<void**>(&GAME_GetIssuedOrderIdold));
		MH_EnableHook(GAME_GetIssuedOrderIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetItemCharges", FALSE))
	{
		GAME_GetItemChargesorg = (GAME_GetItemCharges) ((DWORD) GameDll + 0x3C5050);
		MH_CreateHook(GAME_GetItemChargesorg, &GAME_GetItemChargesmy, reinterpret_cast<void**>(&GAME_GetItemChargesold));
		MH_EnableHook(GAME_GetItemChargesorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetItemLevel", FALSE))
	{
		GAME_GetItemLevelorg = (GAME_GetItemLevel) ((DWORD) GameDll + 0x3C4E50);
		MH_CreateHook(GAME_GetItemLevelorg, &GAME_GetItemLevelmy, reinterpret_cast<void**>(&GAME_GetItemLevelold));
		MH_EnableHook(GAME_GetItemLevelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetItemName", FALSE))
	{
		GAME_GetItemNameorg = (GAME_GetItemName) ((DWORD) GameDll + 0x3C4E90);
		MH_CreateHook(GAME_GetItemNameorg, &GAME_GetItemNamemy, reinterpret_cast<void**>(&GAME_GetItemNameold));
		MH_EnableHook(GAME_GetItemNameorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetItemPlayer", FALSE))
	{
		GAME_GetItemPlayerorg = (GAME_GetItemPlayer) ((DWORD) GameDll + 0x3C4E10);
		MH_CreateHook(GAME_GetItemPlayerorg, &GAME_GetItemPlayermy, reinterpret_cast<void**>(&GAME_GetItemPlayerold));
		MH_EnableHook(GAME_GetItemPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetItemType", FALSE))
	{
		GAME_GetItemTypeorg = (GAME_GetItemType) ((DWORD) GameDll + 0x3C4E70);
		MH_CreateHook(GAME_GetItemTypeorg, &GAME_GetItemTypemy, reinterpret_cast<void**>(&GAME_GetItemTypeold));
		MH_EnableHook(GAME_GetItemTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetItemTypeId", FALSE))
	{
		GAME_GetItemTypeIdorg = (GAME_GetItemTypeId) ((DWORD) GameDll + 0x3C4C60);
		MH_CreateHook(GAME_GetItemTypeIdorg, &GAME_GetItemTypeIdmy, reinterpret_cast<void**>(&GAME_GetItemTypeIdold));
		MH_EnableHook(GAME_GetItemTypeIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetItemUserData", FALSE))
	{
		GAME_GetItemUserDataorg = (GAME_GetItemUserData) ((DWORD) GameDll + 0x3C50D0);
		MH_CreateHook(GAME_GetItemUserDataorg, &GAME_GetItemUserDatamy, reinterpret_cast<void**>(&GAME_GetItemUserDataold));
		MH_EnableHook(GAME_GetItemUserDataorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetItemX", FALSE))
	{
		GAME_GetItemXorg = (GAME_GetItemX) ((DWORD) GameDll + 0x3C4D90);
		MH_CreateHook(GAME_GetItemXorg, &GAME_GetItemXmy, reinterpret_cast<void**>(&GAME_GetItemXold));
		MH_EnableHook(GAME_GetItemXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetItemY", FALSE))
	{
		GAME_GetItemYorg = (GAME_GetItemY) ((DWORD) GameDll + 0x3C4DD0);
		MH_CreateHook(GAME_GetItemYorg, &GAME_GetItemYmy, reinterpret_cast<void**>(&GAME_GetItemYold));
		MH_EnableHook(GAME_GetItemYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetKillingUnit", FALSE))
	{
		GAME_GetKillingUnitorg = (GAME_GetKillingUnit) ((DWORD) GameDll + 0x3C23F0);
		MH_CreateHook(GAME_GetKillingUnitorg, &GAME_GetKillingUnitmy, reinterpret_cast<void**>(&GAME_GetKillingUnitold));
		MH_EnableHook(GAME_GetKillingUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetLastCommand", FALSE))
	{
		GAME_GetLastCommandorg = (GAME_GetLastCommand) ((DWORD) GameDll + 0x2E0450);
		MH_CreateHook(GAME_GetLastCommandorg, &GAME_GetLastCommandmy, reinterpret_cast<void**>(&GAME_GetLastCommandold));
		MH_EnableHook(GAME_GetLastCommandorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetLastData", FALSE))
	{
		GAME_GetLastDataorg = (GAME_GetLastData) ((DWORD) GameDll + 0x2E0490);
		MH_CreateHook(GAME_GetLastDataorg, &GAME_GetLastDatamy, reinterpret_cast<void**>(&GAME_GetLastDataold));
		MH_EnableHook(GAME_GetLastDataorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetLearnedSkill", FALSE))
	{
		GAME_GetLearnedSkillorg = (GAME_GetLearnedSkill) ((DWORD) GameDll + 0x3C2210);
		MH_CreateHook(GAME_GetLearnedSkillorg, &GAME_GetLearnedSkillmy, reinterpret_cast<void**>(&GAME_GetLearnedSkillold));
		MH_EnableHook(GAME_GetLearnedSkillorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetLearnedSkillLevel", FALSE))
	{
		GAME_GetLearnedSkillLevelorg = (GAME_GetLearnedSkillLevel) ((DWORD) GameDll + 0x3C2250);
		MH_CreateHook(GAME_GetLearnedSkillLevelorg, &GAME_GetLearnedSkillLevelmy, reinterpret_cast<void**>(&GAME_GetLearnedSkillLevelold));
		MH_EnableHook(GAME_GetLearnedSkillLevelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetLearningUnit", FALSE))
	{
		GAME_GetLearningUnitorg = (GAME_GetLearningUnit) ((DWORD) GameDll + 0x3C21B0);
		MH_CreateHook(GAME_GetLearningUnitorg, &GAME_GetLearningUnitmy, reinterpret_cast<void**>(&GAME_GetLearningUnitold));
		MH_EnableHook(GAME_GetLearningUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetLeavingUnit", FALSE))
	{
		GAME_GetLeavingUnitorg = (GAME_GetLeavingUnit) ((DWORD) GameDll + 0x3BB6F0);
		MH_CreateHook(GAME_GetLeavingUnitorg, &GAME_GetLeavingUnitmy, reinterpret_cast<void**>(&GAME_GetLeavingUnitold));
		MH_EnableHook(GAME_GetLeavingUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetLevelingUnit", FALSE))
	{
		GAME_GetLevelingUnitorg = (GAME_GetLevelingUnit) ((DWORD) GameDll + 0x3C2150);
		MH_CreateHook(GAME_GetLevelingUnitorg, &GAME_GetLevelingUnitmy, reinterpret_cast<void**>(&GAME_GetLevelingUnitold));
		MH_EnableHook(GAME_GetLevelingUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetLightningColorA", FALSE))
	{
		GAME_GetLightningColorAorg = (GAME_GetLightningColorA) ((DWORD) GameDll + 0x3B8310);
		MH_CreateHook(GAME_GetLightningColorAorg, &GAME_GetLightningColorAmy, reinterpret_cast<void**>(&GAME_GetLightningColorAold));
		MH_EnableHook(GAME_GetLightningColorAorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetLightningColorB", FALSE))
	{
		GAME_GetLightningColorBorg = (GAME_GetLightningColorB) ((DWORD) GameDll + 0x3B8430);
		MH_CreateHook(GAME_GetLightningColorBorg, &GAME_GetLightningColorBmy, reinterpret_cast<void**>(&GAME_GetLightningColorBold));
		MH_EnableHook(GAME_GetLightningColorBorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetLightningColorG", FALSE))
	{
		GAME_GetLightningColorGorg = (GAME_GetLightningColorG) ((DWORD) GameDll + 0x3B83D0);
		MH_CreateHook(GAME_GetLightningColorGorg, &GAME_GetLightningColorGmy, reinterpret_cast<void**>(&GAME_GetLightningColorGold));
		MH_EnableHook(GAME_GetLightningColorGorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetLightningColorR", FALSE))
	{
		GAME_GetLightningColorRorg = (GAME_GetLightningColorR) ((DWORD) GameDll + 0x3B8370);
		MH_CreateHook(GAME_GetLightningColorRorg, &GAME_GetLightningColorRmy, reinterpret_cast<void**>(&GAME_GetLightningColorRold));
		MH_EnableHook(GAME_GetLightningColorRorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetLoadedUnit", FALSE))
	{
		GAME_GetLoadedUnitorg = (GAME_GetLoadedUnit) ((DWORD) GameDll + 0x3C2A00);
		MH_CreateHook(GAME_GetLoadedUnitorg, &GAME_GetLoadedUnitmy, reinterpret_cast<void**>(&GAME_GetLoadedUnitold));
		MH_EnableHook(GAME_GetLoadedUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetLocalPlayer", FALSE))
	{
		GAME_GetLocalPlayerorg = (GAME_GetLocalPlayer) ((DWORD) GameDll + 0x3BBB60);
		MH_CreateHook(GAME_GetLocalPlayerorg, &GAME_GetLocalPlayermy, reinterpret_cast<void**>(&GAME_GetLocalPlayerold));
		MH_EnableHook(GAME_GetLocalPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetLocalizedHotkey", FALSE))
	{
		GAME_GetLocalizedHotkeyorg = (GAME_GetLocalizedHotkey) ((DWORD) GameDll + 0x3B2D80);
		MH_CreateHook(GAME_GetLocalizedHotkeyorg, &GAME_GetLocalizedHotkeymy, reinterpret_cast<void**>(&GAME_GetLocalizedHotkeyold));
		MH_EnableHook(GAME_GetLocalizedHotkeyorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetLocalizedString", FALSE))
	{
		GAME_GetLocalizedStringorg = (GAME_GetLocalizedString) ((DWORD) GameDll + 0x3BACF0);
		MH_CreateHook(GAME_GetLocalizedStringorg, &GAME_GetLocalizedStringmy, reinterpret_cast<void**>(&GAME_GetLocalizedStringold));
		MH_EnableHook(GAME_GetLocalizedStringorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetLocationX", FALSE))
	{
		GAME_GetLocationXorg = (GAME_GetLocationX) ((DWORD) GameDll + 0x3C0E10);
		MH_CreateHook(GAME_GetLocationXorg, &GAME_GetLocationXmy, reinterpret_cast<void**>(&GAME_GetLocationXold));
		MH_EnableHook(GAME_GetLocationXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetLocationY", FALSE))
	{
		GAME_GetLocationYorg = (GAME_GetLocationY) ((DWORD) GameDll + 0x3C0E30);
		MH_CreateHook(GAME_GetLocationYorg, &GAME_GetLocationYmy, reinterpret_cast<void**>(&GAME_GetLocationYold));
		MH_EnableHook(GAME_GetLocationYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetLocationZ", FALSE))
	{
		GAME_GetLocationZorg = (GAME_GetLocationZ) ((DWORD) GameDll + 0x3C0E50);
		MH_CreateHook(GAME_GetLocationZorg, &GAME_GetLocationZmy, reinterpret_cast<void**>(&GAME_GetLocationZold));
		MH_EnableHook(GAME_GetLocationZorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetManipulatedItem", FALSE))
	{
		GAME_GetManipulatedItemorg = (GAME_GetManipulatedItem) ((DWORD) GameDll + 0x3C2B00);
		MH_CreateHook(GAME_GetManipulatedItemorg, &GAME_GetManipulatedItemmy, reinterpret_cast<void**>(&GAME_GetManipulatedItemold));
		MH_EnableHook(GAME_GetManipulatedItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetManipulatingUnit", FALSE))
	{
		GAME_GetManipulatingUnitorg = (GAME_GetManipulatingUnit) ((DWORD) GameDll + 0x3C2A60);
		MH_CreateHook(GAME_GetManipulatingUnitorg, &GAME_GetManipulatingUnitmy, reinterpret_cast<void**>(&GAME_GetManipulatingUnitold));
		MH_EnableHook(GAME_GetManipulatingUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetMegaTarget", FALSE))
	{
		GAME_GetMegaTargetorg = (GAME_GetMegaTarget) ((DWORD) GameDll + 0x2DDD60);
		MH_CreateHook(GAME_GetMegaTargetorg, &GAME_GetMegaTargetmy, reinterpret_cast<void**>(&GAME_GetMegaTargetold));
		MH_EnableHook(GAME_GetMegaTargetorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetMinesOwned", FALSE))
	{
		GAME_GetMinesOwnedorg = (GAME_GetMinesOwned) ((DWORD) GameDll + 0x2DDFD0);
		MH_CreateHook(GAME_GetMinesOwnedorg, &GAME_GetMinesOwnedmy, reinterpret_cast<void**>(&GAME_GetMinesOwnedold));
		MH_EnableHook(GAME_GetMinesOwnedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetNextExpansion", FALSE))
	{
		GAME_GetNextExpansionorg = (GAME_GetNextExpansion) ((DWORD) GameDll + 0x2E2BC0);
		MH_CreateHook(GAME_GetNextExpansionorg, &GAME_GetNextExpansionmy, reinterpret_cast<void**>(&GAME_GetNextExpansionold));
		MH_EnableHook(GAME_GetNextExpansionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetObjectName", FALSE))
	{
		GAME_GetObjectNameorg = (GAME_GetObjectName) ((DWORD) GameDll + 0x3BB6B0);
		MH_CreateHook(GAME_GetObjectNameorg, &GAME_GetObjectNamemy, reinterpret_cast<void**>(&GAME_GetObjectNameold));
		MH_EnableHook(GAME_GetObjectNameorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetOrderPointLoc", FALSE))
	{
		GAME_GetOrderPointLocorg = (GAME_GetOrderPointLoc) ((DWORD) GameDll + 0x3D1FF0);
		MH_CreateHook(GAME_GetOrderPointLocorg, &GAME_GetOrderPointLocmy, reinterpret_cast<void**>(&GAME_GetOrderPointLocold));
		MH_EnableHook(GAME_GetOrderPointLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetOrderPointX", FALSE))
	{
		GAME_GetOrderPointXorg = (GAME_GetOrderPointX) ((DWORD) GameDll + 0x3C2D00);
		MH_CreateHook(GAME_GetOrderPointXorg, &GAME_GetOrderPointXmy, reinterpret_cast<void**>(&GAME_GetOrderPointXold));
		MH_EnableHook(GAME_GetOrderPointXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetOrderPointY", FALSE))
	{
		GAME_GetOrderPointYorg = (GAME_GetOrderPointY) ((DWORD) GameDll + 0x3C2D50);
		MH_CreateHook(GAME_GetOrderPointYorg, &GAME_GetOrderPointYmy, reinterpret_cast<void**>(&GAME_GetOrderPointYold));
		MH_EnableHook(GAME_GetOrderPointYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetOrderTarget", FALSE))
	{
		GAME_GetOrderTargetorg = (GAME_GetOrderTarget) ((DWORD) GameDll + 0x3C2DE0);
		MH_CreateHook(GAME_GetOrderTargetorg, &GAME_GetOrderTargetmy, reinterpret_cast<void**>(&GAME_GetOrderTargetold));
		MH_EnableHook(GAME_GetOrderTargetorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetOrderTargetDestructable", FALSE))
	{
		GAME_GetOrderTargetDestructableorg = (GAME_GetOrderTargetDestructable) ((DWORD) GameDll + 0x3C2F10);
		MH_CreateHook(GAME_GetOrderTargetDestructableorg, &GAME_GetOrderTargetDestructablemy, reinterpret_cast<void**>(&GAME_GetOrderTargetDestructableold));
		MH_EnableHook(GAME_GetOrderTargetDestructableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetOrderTargetItem", FALSE))
	{
		GAME_GetOrderTargetItemorg = (GAME_GetOrderTargetItem) ((DWORD) GameDll + 0x3C3040);
		MH_CreateHook(GAME_GetOrderTargetItemorg, &GAME_GetOrderTargetItemmy, reinterpret_cast<void**>(&GAME_GetOrderTargetItemold));
		MH_EnableHook(GAME_GetOrderTargetItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetOrderTargetUnit", FALSE))
	{
		GAME_GetOrderTargetUnitorg = (GAME_GetOrderTargetUnit) ((DWORD) GameDll + 0x3C3170);
		MH_CreateHook(GAME_GetOrderTargetUnitorg, &GAME_GetOrderTargetUnitmy, reinterpret_cast<void**>(&GAME_GetOrderTargetUnitold));
		MH_EnableHook(GAME_GetOrderTargetUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetOrderedUnit", FALSE))
	{
		GAME_GetOrderedUnitorg = (GAME_GetOrderedUnit) ((DWORD) GameDll + 0x3BB530);
		MH_CreateHook(GAME_GetOrderedUnitorg, &GAME_GetOrderedUnitmy, reinterpret_cast<void**>(&GAME_GetOrderedUnitold));
		MH_EnableHook(GAME_GetOrderedUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetOwningPlayer", FALSE))
	{
		GAME_GetOwningPlayerorg = (GAME_GetOwningPlayer) ((DWORD) GameDll + 0x3C8190);
		MH_CreateHook(GAME_GetOwningPlayerorg, &GAME_GetOwningPlayermy, reinterpret_cast<void**>(&GAME_GetOwningPlayerold));
		MH_EnableHook(GAME_GetOwningPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerAlliance", FALSE))
	{
		GAME_GetPlayerAllianceorg = (GAME_GetPlayerAlliance) ((DWORD) GameDll + 0x3C9D70);
		MH_CreateHook(GAME_GetPlayerAllianceorg, &GAME_GetPlayerAlliancemy, reinterpret_cast<void**>(&GAME_GetPlayerAllianceold));
		MH_EnableHook(GAME_GetPlayerAllianceorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerColor", FALSE))
	{
		GAME_GetPlayerColororg = (GAME_GetPlayerColor) ((DWORD) GameDll + 0x3C1240);
		MH_CreateHook(GAME_GetPlayerColororg, &GAME_GetPlayerColormy, reinterpret_cast<void**>(&GAME_GetPlayerColorold));
		MH_EnableHook(GAME_GetPlayerColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerController", FALSE))
	{
		GAME_GetPlayerControllerorg = (GAME_GetPlayerController) ((DWORD) GameDll + 0x3C12B0);
		MH_CreateHook(GAME_GetPlayerControllerorg, &GAME_GetPlayerControllermy, reinterpret_cast<void**>(&GAME_GetPlayerControllerold));
		MH_EnableHook(GAME_GetPlayerControllerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerHandicap", FALSE))
	{
		GAME_GetPlayerHandicaporg = (GAME_GetPlayerHandicap) ((DWORD) GameDll + 0x3C9E10);
		MH_CreateHook(GAME_GetPlayerHandicaporg, &GAME_GetPlayerHandicapmy, reinterpret_cast<void**>(&GAME_GetPlayerHandicapold));
		MH_EnableHook(GAME_GetPlayerHandicaporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerHandicapXP", FALSE))
	{
		GAME_GetPlayerHandicapXPorg = (GAME_GetPlayerHandicapXP) ((DWORD) GameDll + 0x3C9EC0);
		MH_CreateHook(GAME_GetPlayerHandicapXPorg, &GAME_GetPlayerHandicapXPmy, reinterpret_cast<void**>(&GAME_GetPlayerHandicapXPold));
		MH_EnableHook(GAME_GetPlayerHandicapXPorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerId", FALSE))
	{
		GAME_GetPlayerIdorg = (GAME_GetPlayerId) ((DWORD) GameDll + 0x3C9640);
		MH_CreateHook(GAME_GetPlayerIdorg, &GAME_GetPlayerIdmy, reinterpret_cast<void**>(&GAME_GetPlayerIdold));
		MH_EnableHook(GAME_GetPlayerIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerName", FALSE))
	{
		GAME_GetPlayerNameorg = (GAME_GetPlayerName) ((DWORD) GameDll + 0x3C0F60);
		MH_CreateHook(GAME_GetPlayerNameorg, &GAME_GetPlayerNamemy, reinterpret_cast<void**>(&GAME_GetPlayerNameold));
		MH_EnableHook(GAME_GetPlayerNameorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerRace", FALSE))
	{
		GAME_GetPlayerRaceorg = (GAME_GetPlayerRace) ((DWORD) GameDll + 0x3C9620);
		MH_CreateHook(GAME_GetPlayerRaceorg, &GAME_GetPlayerRacemy, reinterpret_cast<void**>(&GAME_GetPlayerRaceold));
		MH_EnableHook(GAME_GetPlayerRaceorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerScore", FALSE))
	{
		GAME_GetPlayerScoreorg = (GAME_GetPlayerScore) ((DWORD) GameDll + 0x3C9B70);
		MH_CreateHook(GAME_GetPlayerScoreorg, &GAME_GetPlayerScoremy, reinterpret_cast<void**>(&GAME_GetPlayerScoreold));
		MH_EnableHook(GAME_GetPlayerScoreorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerSelectable", FALSE))
	{
		GAME_GetPlayerSelectableorg = (GAME_GetPlayerSelectable) ((DWORD) GameDll + 0x3C1290);
		MH_CreateHook(GAME_GetPlayerSelectableorg, &GAME_GetPlayerSelectablemy, reinterpret_cast<void**>(&GAME_GetPlayerSelectableold));
		MH_EnableHook(GAME_GetPlayerSelectableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerSlotState", FALSE))
	{
		GAME_GetPlayerSlotStateorg = (GAME_GetPlayerSlotState) ((DWORD) GameDll + 0x3C12D0);
		MH_CreateHook(GAME_GetPlayerSlotStateorg, &GAME_GetPlayerSlotStatemy, reinterpret_cast<void**>(&GAME_GetPlayerSlotStateold));
		MH_EnableHook(GAME_GetPlayerSlotStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerStartLocation", FALSE))
	{
		GAME_GetPlayerStartLocationorg = (GAME_GetPlayerStartLocation) ((DWORD) GameDll + 0x3C0FD0);
		MH_CreateHook(GAME_GetPlayerStartLocationorg, &GAME_GetPlayerStartLocationmy, reinterpret_cast<void**>(&GAME_GetPlayerStartLocationold));
		MH_EnableHook(GAME_GetPlayerStartLocationorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerStartLocationX", FALSE))
	{
		GAME_GetPlayerStartLocationXorg = (GAME_GetPlayerStartLocationX) ((DWORD) GameDll + 0x3C0FF0);
		MH_CreateHook(GAME_GetPlayerStartLocationXorg, &GAME_GetPlayerStartLocationXmy, reinterpret_cast<void**>(&GAME_GetPlayerStartLocationXold));
		MH_EnableHook(GAME_GetPlayerStartLocationXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerStartLocationY", FALSE))
	{
		GAME_GetPlayerStartLocationYorg = (GAME_GetPlayerStartLocationY) ((DWORD) GameDll + 0x3C1020);
		MH_CreateHook(GAME_GetPlayerStartLocationYorg, &GAME_GetPlayerStartLocationYmy, reinterpret_cast<void**>(&GAME_GetPlayerStartLocationYold));
		MH_EnableHook(GAME_GetPlayerStartLocationYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerState", FALSE))
	{
		GAME_GetPlayerStateorg = (GAME_GetPlayerState) ((DWORD) GameDll + 0x3C9B00);
		MH_CreateHook(GAME_GetPlayerStateorg, &GAME_GetPlayerStatemy, reinterpret_cast<void**>(&GAME_GetPlayerStateold));
		MH_EnableHook(GAME_GetPlayerStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerStructureCount", FALSE))
	{
		GAME_GetPlayerStructureCountorg = (GAME_GetPlayerStructureCount) ((DWORD) GameDll + 0x3C98C0);
		MH_CreateHook(GAME_GetPlayerStructureCountorg, &GAME_GetPlayerStructureCountmy, reinterpret_cast<void**>(&GAME_GetPlayerStructureCountold));
		MH_EnableHook(GAME_GetPlayerStructureCountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerTaxRate", FALSE))
	{
		GAME_GetPlayerTaxRateorg = (GAME_GetPlayerTaxRate) ((DWORD) GameDll + 0x3C1150);
		MH_CreateHook(GAME_GetPlayerTaxRateorg, &GAME_GetPlayerTaxRatemy, reinterpret_cast<void**>(&GAME_GetPlayerTaxRateold));
		MH_EnableHook(GAME_GetPlayerTaxRateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerTeam", FALSE))
	{
		GAME_GetPlayerTeamorg = (GAME_GetPlayerTeam) ((DWORD) GameDll + 0x3C0F40);
		MH_CreateHook(GAME_GetPlayerTeamorg, &GAME_GetPlayerTeammy, reinterpret_cast<void**>(&GAME_GetPlayerTeamold));
		MH_EnableHook(GAME_GetPlayerTeamorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerTechCount", FALSE))
	{
		GAME_GetPlayerTechCountorg = (GAME_GetPlayerTechCount) ((DWORD) GameDll + 0x3C97A0);
		MH_CreateHook(GAME_GetPlayerTechCountorg, &GAME_GetPlayerTechCountmy, reinterpret_cast<void**>(&GAME_GetPlayerTechCountold));
		MH_EnableHook(GAME_GetPlayerTechCountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerTechMaxAllowed", FALSE))
	{
		GAME_GetPlayerTechMaxAllowedorg = (GAME_GetPlayerTechMaxAllowed) ((DWORD) GameDll + 0x3C9690);
		MH_CreateHook(GAME_GetPlayerTechMaxAllowedorg, &GAME_GetPlayerTechMaxAllowedmy, reinterpret_cast<void**>(&GAME_GetPlayerTechMaxAllowedold));
		MH_EnableHook(GAME_GetPlayerTechMaxAllowedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerTechResearched", FALSE))
	{
		GAME_GetPlayerTechResearchedorg = (GAME_GetPlayerTechResearched) ((DWORD) GameDll + 0x3C9770);
		MH_CreateHook(GAME_GetPlayerTechResearchedorg, &GAME_GetPlayerTechResearchedmy, reinterpret_cast<void**>(&GAME_GetPlayerTechResearchedold));
		MH_EnableHook(GAME_GetPlayerTechResearchedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerTypedUnitCount", FALSE))
	{
		GAME_GetPlayerTypedUnitCountorg = (GAME_GetPlayerTypedUnitCount) ((DWORD) GameDll + 0x3C9850);
		MH_CreateHook(GAME_GetPlayerTypedUnitCountorg, &GAME_GetPlayerTypedUnitCountmy, reinterpret_cast<void**>(&GAME_GetPlayerTypedUnitCountold));
		MH_EnableHook(GAME_GetPlayerTypedUnitCountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerUnitCount", FALSE))
	{
		GAME_GetPlayerUnitCountorg = (GAME_GetPlayerUnitCount) ((DWORD) GameDll + 0x3C9820);
		MH_CreateHook(GAME_GetPlayerUnitCountorg, &GAME_GetPlayerUnitCountmy, reinterpret_cast<void**>(&GAME_GetPlayerUnitCountold));
		MH_EnableHook(GAME_GetPlayerUnitCountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayerUnitTypeCount", FALSE))
	{
		GAME_GetPlayerUnitTypeCountorg = (GAME_GetPlayerUnitTypeCount) ((DWORD) GameDll + 0x2E2B60);
		MH_CreateHook(GAME_GetPlayerUnitTypeCountorg, &GAME_GetPlayerUnitTypeCountmy, reinterpret_cast<void**>(&GAME_GetPlayerUnitTypeCountold));
		MH_EnableHook(GAME_GetPlayerUnitTypeCountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetPlayers", FALSE))
	{
		GAME_GetPlayersorg = (GAME_GetPlayers) ((DWORD) GameDll + 0x3BAE00);
		MH_CreateHook(GAME_GetPlayersorg, &GAME_GetPlayersmy, reinterpret_cast<void**>(&GAME_GetPlayersold));
		MH_EnableHook(GAME_GetPlayersorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetRandomInt", FALSE))
	{
		GAME_GetRandomIntorg = (GAME_GetRandomInt) ((DWORD) GameDll + 0x3B3560);
		MH_CreateHook(GAME_GetRandomIntorg, &GAME_GetRandomIntmy, reinterpret_cast<void**>(&GAME_GetRandomIntold));
		MH_EnableHook(GAME_GetRandomIntorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetRandomReal", FALSE))
	{
		GAME_GetRandomRealorg = (GAME_GetRandomReal) ((DWORD) GameDll + 0x3B35A0);
		MH_CreateHook(GAME_GetRandomRealorg, &GAME_GetRandomRealmy, reinterpret_cast<void**>(&GAME_GetRandomRealold));
		MH_EnableHook(GAME_GetRandomRealorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetRectCenterX", FALSE))
	{
		GAME_GetRectCenterXorg = (GAME_GetRectCenterX) ((DWORD) GameDll + 0x3C18E0);
		MH_CreateHook(GAME_GetRectCenterXorg, &GAME_GetRectCenterXmy, reinterpret_cast<void**>(&GAME_GetRectCenterXold));
		MH_EnableHook(GAME_GetRectCenterXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetRectCenterY", FALSE))
	{
		GAME_GetRectCenterYorg = (GAME_GetRectCenterY) ((DWORD) GameDll + 0x3C1910);
		MH_CreateHook(GAME_GetRectCenterYorg, &GAME_GetRectCenterYmy, reinterpret_cast<void**>(&GAME_GetRectCenterYold));
		MH_EnableHook(GAME_GetRectCenterYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetRectMaxX", FALSE))
	{
		GAME_GetRectMaxXorg = (GAME_GetRectMaxX) ((DWORD) GameDll + 0x3C1980);
		MH_CreateHook(GAME_GetRectMaxXorg, &GAME_GetRectMaxXmy, reinterpret_cast<void**>(&GAME_GetRectMaxXold));
		MH_EnableHook(GAME_GetRectMaxXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetRectMaxY", FALSE))
	{
		GAME_GetRectMaxYorg = (GAME_GetRectMaxY) ((DWORD) GameDll + 0x3C19A0);
		MH_CreateHook(GAME_GetRectMaxYorg, &GAME_GetRectMaxYmy, reinterpret_cast<void**>(&GAME_GetRectMaxYold));
		MH_EnableHook(GAME_GetRectMaxYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetRectMinX", FALSE))
	{
		GAME_GetRectMinXorg = (GAME_GetRectMinX) ((DWORD) GameDll + 0x3C1940);
		MH_CreateHook(GAME_GetRectMinXorg, &GAME_GetRectMinXmy, reinterpret_cast<void**>(&GAME_GetRectMinXold));
		MH_EnableHook(GAME_GetRectMinXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetRectMinY", FALSE))
	{
		GAME_GetRectMinYorg = (GAME_GetRectMinY) ((DWORD) GameDll + 0x3C1960);
		MH_CreateHook(GAME_GetRectMinYorg, &GAME_GetRectMinYmy, reinterpret_cast<void**>(&GAME_GetRectMinYold));
		MH_EnableHook(GAME_GetRectMinYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetRescuer", FALSE))
	{
		GAME_GetRescuerorg = (GAME_GetRescuer) ((DWORD) GameDll + 0x3C2390);
		MH_CreateHook(GAME_GetRescuerorg, &GAME_GetRescuermy, reinterpret_cast<void**>(&GAME_GetRescuerold));
		MH_EnableHook(GAME_GetRescuerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetResearched", FALSE))
	{
		GAME_GetResearchedorg = (GAME_GetResearched) ((DWORD) GameDll + 0x3C2870);
		MH_CreateHook(GAME_GetResearchedorg, &GAME_GetResearchedmy, reinterpret_cast<void**>(&GAME_GetResearchedold));
		MH_EnableHook(GAME_GetResearchedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetResearchingUnit", FALSE))
	{
		GAME_GetResearchingUnitorg = (GAME_GetResearchingUnit) ((DWORD) GameDll + 0x3BB4D0);
		MH_CreateHook(GAME_GetResearchingUnitorg, &GAME_GetResearchingUnitmy, reinterpret_cast<void**>(&GAME_GetResearchingUnitold));
		MH_EnableHook(GAME_GetResearchingUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetResourceAmount", FALSE))
	{
		GAME_GetResourceAmountorg = (GAME_GetResourceAmount) ((DWORD) GameDll + 0x3C78B0);
		MH_CreateHook(GAME_GetResourceAmountorg, &GAME_GetResourceAmountmy, reinterpret_cast<void**>(&GAME_GetResourceAmountold));
		MH_EnableHook(GAME_GetResourceAmountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetResourceDensity", FALSE))
	{
		GAME_GetResourceDensityorg = (GAME_GetResourceDensity) ((DWORD) GameDll + 0x3BAF40);
		MH_CreateHook(GAME_GetResourceDensityorg, &GAME_GetResourceDensitymy, reinterpret_cast<void**>(&GAME_GetResourceDensityold));
		MH_EnableHook(GAME_GetResourceDensityorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetRevivableUnit", FALSE))
	{
		GAME_GetRevivableUnitorg = (GAME_GetRevivableUnit) ((DWORD) GameDll + 0x3C2290);
		MH_CreateHook(GAME_GetRevivableUnitorg, &GAME_GetRevivableUnitmy, reinterpret_cast<void**>(&GAME_GetRevivableUnitold));
		MH_EnableHook(GAME_GetRevivableUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetRevivingUnit", FALSE))
	{
		GAME_GetRevivingUnitorg = (GAME_GetRevivingUnit) ((DWORD) GameDll + 0x3C22F0);
		MH_CreateHook(GAME_GetRevivingUnitorg, &GAME_GetRevivingUnitmy, reinterpret_cast<void**>(&GAME_GetRevivingUnitold));
		MH_EnableHook(GAME_GetRevivingUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSaveBasicFilename", FALSE))
	{
		GAME_GetSaveBasicFilenameorg = (GAME_GetSaveBasicFilename) ((DWORD) GameDll + 0x3C1F80);
		MH_CreateHook(GAME_GetSaveBasicFilenameorg, &GAME_GetSaveBasicFilenamemy, reinterpret_cast<void**>(&GAME_GetSaveBasicFilenameold));
		MH_EnableHook(GAME_GetSaveBasicFilenameorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSellingUnit", FALSE))
	{
		GAME_GetSellingUnitorg = (GAME_GetSellingUnit) ((DWORD) GameDll + 0x3C2560);
		MH_CreateHook(GAME_GetSellingUnitorg, &GAME_GetSellingUnitmy, reinterpret_cast<void**>(&GAME_GetSellingUnitold));
		MH_EnableHook(GAME_GetSellingUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSoldItem", FALSE))
	{
		GAME_GetSoldItemorg = (GAME_GetSoldItem) ((DWORD) GameDll + 0x3C25F0);
		MH_CreateHook(GAME_GetSoldItemorg, &GAME_GetSoldItemmy, reinterpret_cast<void**>(&GAME_GetSoldItemold));
		MH_EnableHook(GAME_GetSoldItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSoldUnit", FALSE))
	{
		GAME_GetSoldUnitorg = (GAME_GetSoldUnit) ((DWORD) GameDll + 0x3C2750);
		MH_CreateHook(GAME_GetSoldUnitorg, &GAME_GetSoldUnitmy, reinterpret_cast<void**>(&GAME_GetSoldUnitold));
		MH_EnableHook(GAME_GetSoldUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSoundDuration", FALSE))
	{
		GAME_GetSoundDurationorg = (GAME_GetSoundDuration) ((DWORD) GameDll + 0x3CCF20);
		MH_CreateHook(GAME_GetSoundDurationorg, &GAME_GetSoundDurationmy, reinterpret_cast<void**>(&GAME_GetSoundDurationold));
		MH_EnableHook(GAME_GetSoundDurationorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSoundFileDuration", FALSE))
	{
		GAME_GetSoundFileDurationorg = (GAME_GetSoundFileDuration) ((DWORD) GameDll + 0x3B3E20);
		MH_CreateHook(GAME_GetSoundFileDurationorg, &GAME_GetSoundFileDurationmy, reinterpret_cast<void**>(&GAME_GetSoundFileDurationold));
		MH_EnableHook(GAME_GetSoundFileDurationorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSoundIsLoading", FALSE))
	{
		GAME_GetSoundIsLoadingorg = (GAME_GetSoundIsLoading) ((DWORD) GameDll + 0x3CCF60);
		MH_CreateHook(GAME_GetSoundIsLoadingorg, &GAME_GetSoundIsLoadingmy, reinterpret_cast<void**>(&GAME_GetSoundIsLoadingold));
		MH_EnableHook(GAME_GetSoundIsLoadingorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSoundIsPlaying", FALSE))
	{
		GAME_GetSoundIsPlayingorg = (GAME_GetSoundIsPlaying) ((DWORD) GameDll + 0x3CCF40);
		MH_CreateHook(GAME_GetSoundIsPlayingorg, &GAME_GetSoundIsPlayingmy, reinterpret_cast<void**>(&GAME_GetSoundIsPlayingold));
		MH_EnableHook(GAME_GetSoundIsPlayingorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSpellAbility", FALSE))
	{
		GAME_GetSpellAbilityorg = (GAME_GetSpellAbility) ((DWORD) GameDll + 0x3C3380);
		MH_CreateHook(GAME_GetSpellAbilityorg, &GAME_GetSpellAbilitymy, reinterpret_cast<void**>(&GAME_GetSpellAbilityold));
		MH_EnableHook(GAME_GetSpellAbilityorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSpellAbilityId", FALSE))
	{
		GAME_GetSpellAbilityIdorg = (GAME_GetSpellAbilityId) ((DWORD) GameDll + 0x3C32A0);
		MH_CreateHook(GAME_GetSpellAbilityIdorg, &GAME_GetSpellAbilityIdmy, reinterpret_cast<void**>(&GAME_GetSpellAbilityIdold));
		MH_EnableHook(GAME_GetSpellAbilityIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSpellAbilityUnit", FALSE))
	{
		GAME_GetSpellAbilityUnitorg = (GAME_GetSpellAbilityUnit) ((DWORD) GameDll + 0x3C3470);
		MH_CreateHook(GAME_GetSpellAbilityUnitorg, &GAME_GetSpellAbilityUnitmy, reinterpret_cast<void**>(&GAME_GetSpellAbilityUnitold));
		MH_EnableHook(GAME_GetSpellAbilityUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSpellTargetDestructable", FALSE))
	{
		GAME_GetSpellTargetDestructableorg = (GAME_GetSpellTargetDestructable) ((DWORD) GameDll + 0x3C3760);
		MH_CreateHook(GAME_GetSpellTargetDestructableorg, &GAME_GetSpellTargetDestructablemy, reinterpret_cast<void**>(&GAME_GetSpellTargetDestructableold));
		MH_EnableHook(GAME_GetSpellTargetDestructableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSpellTargetItem", FALSE))
	{
		GAME_GetSpellTargetItemorg = (GAME_GetSpellTargetItem) ((DWORD) GameDll + 0x3C38F0);
		MH_CreateHook(GAME_GetSpellTargetItemorg, &GAME_GetSpellTargetItemmy, reinterpret_cast<void**>(&GAME_GetSpellTargetItemold));
		MH_EnableHook(GAME_GetSpellTargetItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSpellTargetLoc", FALSE))
	{
		GAME_GetSpellTargetLocorg = (GAME_GetSpellTargetLoc) ((DWORD) GameDll + 0x3D2090);
		MH_CreateHook(GAME_GetSpellTargetLocorg, &GAME_GetSpellTargetLocmy, reinterpret_cast<void**>(&GAME_GetSpellTargetLocold));
		MH_EnableHook(GAME_GetSpellTargetLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSpellTargetUnit", FALSE))
	{
		GAME_GetSpellTargetUnitorg = (GAME_GetSpellTargetUnit) ((DWORD) GameDll + 0x3C3A80);
		MH_CreateHook(GAME_GetSpellTargetUnitorg, &GAME_GetSpellTargetUnitmy, reinterpret_cast<void**>(&GAME_GetSpellTargetUnitold));
		MH_EnableHook(GAME_GetSpellTargetUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSpellTargetX", FALSE))
	{
		GAME_GetSpellTargetXorg = (GAME_GetSpellTargetX) ((DWORD) GameDll + 0x3C3580);
		MH_CreateHook(GAME_GetSpellTargetXorg, &GAME_GetSpellTargetXmy, reinterpret_cast<void**>(&GAME_GetSpellTargetXold));
		MH_EnableHook(GAME_GetSpellTargetXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSpellTargetY", FALSE))
	{
		GAME_GetSpellTargetYorg = (GAME_GetSpellTargetY) ((DWORD) GameDll + 0x3C3670);
		MH_CreateHook(GAME_GetSpellTargetYorg, &GAME_GetSpellTargetYmy, reinterpret_cast<void**>(&GAME_GetSpellTargetYold));
		MH_EnableHook(GAME_GetSpellTargetYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetStartLocPrio", FALSE))
	{
		GAME_GetStartLocPrioorg = (GAME_GetStartLocPrio) ((DWORD) GameDll + 0x3BB030);
		MH_CreateHook(GAME_GetStartLocPrioorg, &GAME_GetStartLocPriomy, reinterpret_cast<void**>(&GAME_GetStartLocPrioold));
		MH_EnableHook(GAME_GetStartLocPrioorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetStartLocPrioSlot", FALSE))
	{
		GAME_GetStartLocPrioSlotorg = (GAME_GetStartLocPrioSlot) ((DWORD) GameDll + 0x3BB000);
		MH_CreateHook(GAME_GetStartLocPrioSlotorg, &GAME_GetStartLocPrioSlotmy, reinterpret_cast<void**>(&GAME_GetStartLocPrioSlotold));
		MH_EnableHook(GAME_GetStartLocPrioSlotorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetStartLocationLoc", FALSE))
	{
		GAME_GetStartLocationLocorg = (GAME_GetStartLocationLoc) ((DWORD) GameDll + 0x3D04B0);
		MH_CreateHook(GAME_GetStartLocationLocorg, &GAME_GetStartLocationLocmy, reinterpret_cast<void**>(&GAME_GetStartLocationLocold));
		MH_EnableHook(GAME_GetStartLocationLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetStartLocationX", FALSE))
	{
		GAME_GetStartLocationXorg = (GAME_GetStartLocationX) ((DWORD) GameDll + 0x3BB060);
		MH_CreateHook(GAME_GetStartLocationXorg, &GAME_GetStartLocationXmy, reinterpret_cast<void**>(&GAME_GetStartLocationXold));
		MH_EnableHook(GAME_GetStartLocationXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetStartLocationY", FALSE))
	{
		GAME_GetStartLocationYorg = (GAME_GetStartLocationY) ((DWORD) GameDll + 0x3BB080);
		MH_CreateHook(GAME_GetStartLocationYorg, &GAME_GetStartLocationYmy, reinterpret_cast<void**>(&GAME_GetStartLocationYold));
		MH_EnableHook(GAME_GetStartLocationYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetStoredBOOLean", FALSE))
	{
		GAME_GetStoredBOOLeanorg = (GAME_GetStoredBOOLean) ((DWORD) GameDll + 0x3CA920);
		MH_CreateHook(GAME_GetStoredBOOLeanorg, &GAME_GetStoredBOOLeanmy, reinterpret_cast<void**>(&GAME_GetStoredBOOLeanold));
		MH_EnableHook(GAME_GetStoredBOOLeanorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetStoredInteger", FALSE))
	{
		GAME_GetStoredIntegerorg = (GAME_GetStoredInteger) ((DWORD) GameDll + 0x3CA870);
		MH_CreateHook(GAME_GetStoredIntegerorg, &GAME_GetStoredIntegermy, reinterpret_cast<void**>(&GAME_GetStoredIntegerold));
		MH_EnableHook(GAME_GetStoredIntegerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetStoredReal", FALSE))
	{
		GAME_GetStoredRealorg = (GAME_GetStoredReal) ((DWORD) GameDll + 0x3CA8C0);
		MH_CreateHook(GAME_GetStoredRealorg, &GAME_GetStoredRealmy, reinterpret_cast<void**>(&GAME_GetStoredRealold));
		MH_EnableHook(GAME_GetStoredRealorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetStoredString", FALSE))
	{
		GAME_GetStoredStringorg = (GAME_GetStoredString) ((DWORD) GameDll + 0x3CAA40);
		MH_CreateHook(GAME_GetStoredStringorg, &GAME_GetStoredStringmy, reinterpret_cast<void**>(&GAME_GetStoredStringold));
		MH_EnableHook(GAME_GetStoredStringorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSummonedUnit", FALSE))
	{
		GAME_GetSummonedUnitorg = (GAME_GetSummonedUnit) ((DWORD) GameDll + 0x3C2950);
		MH_CreateHook(GAME_GetSummonedUnitorg, &GAME_GetSummonedUnitmy, reinterpret_cast<void**>(&GAME_GetSummonedUnitold));
		MH_EnableHook(GAME_GetSummonedUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetSummoningUnit", FALSE))
	{
		GAME_GetSummoningUnitorg = (GAME_GetSummoningUnit) ((DWORD) GameDll + 0x3C28F0);
		MH_CreateHook(GAME_GetSummoningUnitorg, &GAME_GetSummoningUnitmy, reinterpret_cast<void**>(&GAME_GetSummoningUnitold));
		MH_EnableHook(GAME_GetSummoningUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTeams", FALSE))
	{
		GAME_GetTeamsorg = (GAME_GetTeams) ((DWORD) GameDll + 0x3BADE0);
		MH_CreateHook(GAME_GetTeamsorg, &GAME_GetTeamsmy, reinterpret_cast<void**>(&GAME_GetTeamsold));
		MH_EnableHook(GAME_GetTeamsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTerrainCliffLevel", FALSE))
	{
		GAME_GetTerrainCliffLevelorg = (GAME_GetTerrainCliffLevel) ((DWORD) GameDll + 0x3B4190);
		MH_CreateHook(GAME_GetTerrainCliffLevelorg, &GAME_GetTerrainCliffLevelmy, reinterpret_cast<void**>(&GAME_GetTerrainCliffLevelold));
		MH_EnableHook(GAME_GetTerrainCliffLevelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTerrainType", FALSE))
	{
		GAME_GetTerrainTypeorg = (GAME_GetTerrainType) ((DWORD) GameDll + 0x3BCED0);
		MH_CreateHook(GAME_GetTerrainTypeorg, &GAME_GetTerrainTypemy, reinterpret_cast<void**>(&GAME_GetTerrainTypeold));
		MH_EnableHook(GAME_GetTerrainTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTerrainVariance", FALSE))
	{
		GAME_GetTerrainVarianceorg = (GAME_GetTerrainVariance) ((DWORD) GameDll + 0x3B4250);
		MH_CreateHook(GAME_GetTerrainVarianceorg, &GAME_GetTerrainVariancemy, reinterpret_cast<void**>(&GAME_GetTerrainVarianceold));
		MH_EnableHook(GAME_GetTerrainVarianceorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTimeOfDayScale", FALSE))
	{
		GAME_GetTimeOfDayScaleorg = (GAME_GetTimeOfDayScale) ((DWORD) GameDll + 0x3BC4B0);
		MH_CreateHook(GAME_GetTimeOfDayScaleorg, &GAME_GetTimeOfDayScalemy, reinterpret_cast<void**>(&GAME_GetTimeOfDayScaleold));
		MH_EnableHook(GAME_GetTimeOfDayScaleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTournamentFinishNowPlayer", FALSE))
	{
		GAME_GetTournamentFinishNowPlayerorg = (GAME_GetTournamentFinishNowPlayer) ((DWORD) GameDll + 0x3C1F00);
		MH_CreateHook(GAME_GetTournamentFinishNowPlayerorg, &GAME_GetTournamentFinishNowPlayermy, reinterpret_cast<void**>(&GAME_GetTournamentFinishNowPlayerold));
		MH_EnableHook(GAME_GetTournamentFinishNowPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTournamentFinishNowRule", FALSE))
	{
		GAME_GetTournamentFinishNowRuleorg = (GAME_GetTournamentFinishNowRule) ((DWORD) GameDll + 0x3C1ED0);
		MH_CreateHook(GAME_GetTournamentFinishNowRuleorg, &GAME_GetTournamentFinishNowRulemy, reinterpret_cast<void**>(&GAME_GetTournamentFinishNowRuleold));
		MH_EnableHook(GAME_GetTournamentFinishNowRuleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTournamentFinishSoonTimeRemaining", FALSE))
	{
		GAME_GetTournamentFinishSoonTimeRemainingorg = (GAME_GetTournamentFinishSoonTimeRemaining) ((DWORD) GameDll + 0x3C1EA0);
		MH_CreateHook(GAME_GetTournamentFinishSoonTimeRemainingorg, &GAME_GetTournamentFinishSoonTimeRemainingmy, reinterpret_cast<void**>(&GAME_GetTournamentFinishSoonTimeRemainingold));
		MH_EnableHook(GAME_GetTournamentFinishSoonTimeRemainingorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTournamentScore", FALSE))
	{
		GAME_GetTournamentScoreorg = (GAME_GetTournamentScore) ((DWORD) GameDll + 0x3C1F60);
		MH_CreateHook(GAME_GetTournamentScoreorg, &GAME_GetTournamentScoremy, reinterpret_cast<void**>(&GAME_GetTournamentScoreold));
		MH_EnableHook(GAME_GetTournamentScoreorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTownUnitCount", FALSE))
	{
		GAME_GetTownUnitCountorg = (GAME_GetTownUnitCount) ((DWORD) GameDll + 0x2DD0C0);
		MH_CreateHook(GAME_GetTownUnitCountorg, &GAME_GetTownUnitCountmy, reinterpret_cast<void**>(&GAME_GetTownUnitCountold));
		MH_EnableHook(GAME_GetTownUnitCountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTrainedUnit", FALSE))
	{
		GAME_GetTrainedUnitorg = (GAME_GetTrainedUnit) ((DWORD) GameDll + 0x3C2500);
		MH_CreateHook(GAME_GetTrainedUnitorg, &GAME_GetTrainedUnitmy, reinterpret_cast<void**>(&GAME_GetTrainedUnitold));
		MH_EnableHook(GAME_GetTrainedUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTrainedUnitType", FALSE))
	{
		GAME_GetTrainedUnitTypeorg = (GAME_GetTrainedUnitType) ((DWORD) GameDll + 0x3C2450);
		MH_CreateHook(GAME_GetTrainedUnitTypeorg, &GAME_GetTrainedUnitTypemy, reinterpret_cast<void**>(&GAME_GetTrainedUnitTypeold));
		MH_EnableHook(GAME_GetTrainedUnitTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTransportUnit", FALSE))
	{
		GAME_GetTransportUnitorg = (GAME_GetTransportUnit) ((DWORD) GameDll + 0x3C29A0);
		MH_CreateHook(GAME_GetTransportUnitorg, &GAME_GetTransportUnitmy, reinterpret_cast<void**>(&GAME_GetTransportUnitold));
		MH_EnableHook(GAME_GetTransportUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTriggerDestructable", FALSE))
	{
		GAME_GetTriggerDestructableorg = (GAME_GetTriggerDestructable) ((DWORD) GameDll + 0x3C1D20);
		MH_CreateHook(GAME_GetTriggerDestructableorg, &GAME_GetTriggerDestructablemy, reinterpret_cast<void**>(&GAME_GetTriggerDestructableold));
		MH_EnableHook(GAME_GetTriggerDestructableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTriggerEvalCount", FALSE))
	{
		GAME_GetTriggerEvalCountorg = (GAME_GetTriggerEvalCount) ((DWORD) GameDll + 0x3C1CE0);
		MH_CreateHook(GAME_GetTriggerEvalCountorg, &GAME_GetTriggerEvalCountmy, reinterpret_cast<void**>(&GAME_GetTriggerEvalCountold));
		MH_EnableHook(GAME_GetTriggerEvalCountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTriggerEventId", FALSE))
	{
		GAME_GetTriggerEventIdorg = (GAME_GetTriggerEventId) ((DWORD) GameDll + 0x3BB2C0);
		MH_CreateHook(GAME_GetTriggerEventIdorg, &GAME_GetTriggerEventIdmy, reinterpret_cast<void**>(&GAME_GetTriggerEventIdold));
		MH_EnableHook(GAME_GetTriggerEventIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTriggerExecCount", FALSE))
	{
		GAME_GetTriggerExecCountorg = (GAME_GetTriggerExecCount) ((DWORD) GameDll + 0x3C1D00);
		MH_CreateHook(GAME_GetTriggerExecCountorg, &GAME_GetTriggerExecCountmy, reinterpret_cast<void**>(&GAME_GetTriggerExecCountold));
		MH_EnableHook(GAME_GetTriggerExecCountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTriggerPlayer", FALSE))
	{
		GAME_GetTriggerPlayerorg = (GAME_GetTriggerPlayer) ((DWORD) GameDll + 0x3BB280);
		MH_CreateHook(GAME_GetTriggerPlayerorg, &GAME_GetTriggerPlayermy, reinterpret_cast<void**>(&GAME_GetTriggerPlayerold));
		MH_EnableHook(GAME_GetTriggerPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTriggerUnit", FALSE))
	{
		GAME_GetTriggerUnitorg = (GAME_GetTriggerUnit) ((DWORD) GameDll + 0x3BB240);
		MH_CreateHook(GAME_GetTriggerUnitorg, &GAME_GetTriggerUnitmy, reinterpret_cast<void**>(&GAME_GetTriggerUnitold));
		MH_EnableHook(GAME_GetTriggerUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTriggerWidget", FALSE))
	{
		GAME_GetTriggerWidgetorg = (GAME_GetTriggerWidget) ((DWORD) GameDll + 0x3BB260);
		MH_CreateHook(GAME_GetTriggerWidgetorg, &GAME_GetTriggerWidgetmy, reinterpret_cast<void**>(&GAME_GetTriggerWidgetold));
		MH_EnableHook(GAME_GetTriggerWidgetorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTriggeringRegion", FALSE))
	{
		GAME_GetTriggeringRegionorg = (GAME_GetTriggeringRegion) ((DWORD) GameDll + 0x3C3D50);
		MH_CreateHook(GAME_GetTriggeringRegionorg, &GAME_GetTriggeringRegionmy, reinterpret_cast<void**>(&GAME_GetTriggeringRegionold));
		MH_EnableHook(GAME_GetTriggeringRegionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTriggeringTrackable", FALSE))
	{
		GAME_GetTriggeringTrackableorg = (GAME_GetTriggeringTrackable) ((DWORD) GameDll + 0x3C3DA0);
		MH_CreateHook(GAME_GetTriggeringTrackableorg, &GAME_GetTriggeringTrackablemy, reinterpret_cast<void**>(&GAME_GetTriggeringTrackableold));
		MH_EnableHook(GAME_GetTriggeringTrackableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetTriggeringTrigger", FALSE))
	{
		GAME_GetTriggeringTriggerorg = (GAME_GetTriggeringTrigger) ((DWORD) GameDll + 0x3BB2A0);
		MH_CreateHook(GAME_GetTriggeringTriggerorg, &GAME_GetTriggeringTriggermy, reinterpret_cast<void**>(&GAME_GetTriggeringTriggerold));
		MH_EnableHook(GAME_GetTriggeringTriggerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitAbilityLevel", FALSE))
	{
		GAME_GetUnitAbilityLevelorg = (GAME_GetUnitAbilityLevel) ((DWORD) GameDll + 0x3C7290);
		MH_CreateHook(GAME_GetUnitAbilityLevelorg, &GAME_GetUnitAbilityLevelmy, reinterpret_cast<void**>(&GAME_GetUnitAbilityLevelold));
		MH_EnableHook(GAME_GetUnitAbilityLevelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitAcquireRange", FALSE))
	{
		GAME_GetUnitAcquireRangeorg = (GAME_GetUnitAcquireRange) ((DWORD) GameDll + 0x3C5D10);
		MH_CreateHook(GAME_GetUnitAcquireRangeorg, &GAME_GetUnitAcquireRangemy, reinterpret_cast<void**>(&GAME_GetUnitAcquireRangeold));
		MH_EnableHook(GAME_GetUnitAcquireRangeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitBuildTime", FALSE))
	{
		GAME_GetUnitBuildTimeorg = (GAME_GetUnitBuildTime) ((DWORD) GameDll + 0x2DD190);
		MH_CreateHook(GAME_GetUnitBuildTimeorg, &GAME_GetUnitBuildTimemy, reinterpret_cast<void**>(&GAME_GetUnitBuildTimeold));
		MH_EnableHook(GAME_GetUnitBuildTimeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitCount", FALSE))
	{
		GAME_GetUnitCountorg = (GAME_GetUnitCount) ((DWORD) GameDll + 0x2DD050);
		MH_CreateHook(GAME_GetUnitCountorg, &GAME_GetUnitCountmy, reinterpret_cast<void**>(&GAME_GetUnitCountold));
		MH_EnableHook(GAME_GetUnitCountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitCountDone", FALSE))
	{
		GAME_GetUnitCountDoneorg = (GAME_GetUnitCountDone) ((DWORD) GameDll + 0x2DD010);
		MH_CreateHook(GAME_GetUnitCountDoneorg, &GAME_GetUnitCountDonemy, reinterpret_cast<void**>(&GAME_GetUnitCountDoneold));
		MH_EnableHook(GAME_GetUnitCountDoneorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitCurrentOrder", FALSE))
	{
		GAME_GetUnitCurrentOrderorg = (GAME_GetUnitCurrentOrder) ((DWORD) GameDll + 0x3C7780);
		MH_CreateHook(GAME_GetUnitCurrentOrderorg, &GAME_GetUnitCurrentOrdermy, reinterpret_cast<void**>(&GAME_GetUnitCurrentOrderold));
		MH_EnableHook(GAME_GetUnitCurrentOrderorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitDefaultAcquireRange", FALSE))
	{
		GAME_GetUnitDefaultAcquireRangeorg = (GAME_GetUnitDefaultAcquireRange) ((DWORD) GameDll + 0x3C5DC0);
		MH_CreateHook(GAME_GetUnitDefaultAcquireRangeorg, &GAME_GetUnitDefaultAcquireRangemy, reinterpret_cast<void**>(&GAME_GetUnitDefaultAcquireRangeold));
		MH_EnableHook(GAME_GetUnitDefaultAcquireRangeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitDefaultFlyHeight", FALSE))
	{
		GAME_GetUnitDefaultFlyHeightorg = (GAME_GetUnitDefaultFlyHeight) ((DWORD) GameDll + 0x3C5E50);
		MH_CreateHook(GAME_GetUnitDefaultFlyHeightorg, &GAME_GetUnitDefaultFlyHeightmy, reinterpret_cast<void**>(&GAME_GetUnitDefaultFlyHeightold));
		MH_EnableHook(GAME_GetUnitDefaultFlyHeightorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitDefaultMoveSpeed", FALSE))
	{
		GAME_GetUnitDefaultMoveSpeedorg = (GAME_GetUnitDefaultMoveSpeed) ((DWORD) GameDll + 0x3C5870);
		MH_CreateHook(GAME_GetUnitDefaultMoveSpeedorg, &GAME_GetUnitDefaultMoveSpeedmy, reinterpret_cast<void**>(&GAME_GetUnitDefaultMoveSpeedold));
		MH_EnableHook(GAME_GetUnitDefaultMoveSpeedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitDefaultPropWindow", FALSE))
	{
		GAME_GetUnitDefaultPropWindoworg = (GAME_GetUnitDefaultPropWindow) ((DWORD) GameDll + 0x3C5E20);
		MH_CreateHook(GAME_GetUnitDefaultPropWindoworg, &GAME_GetUnitDefaultPropWindowmy, reinterpret_cast<void**>(&GAME_GetUnitDefaultPropWindowold));
		MH_EnableHook(GAME_GetUnitDefaultPropWindoworg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitDefaultTurnSpeed", FALSE))
	{
		GAME_GetUnitDefaultTurnSpeedorg = (GAME_GetUnitDefaultTurnSpeed) ((DWORD) GameDll + 0x3C5DF0);
		MH_CreateHook(GAME_GetUnitDefaultTurnSpeedorg, &GAME_GetUnitDefaultTurnSpeedmy, reinterpret_cast<void**>(&GAME_GetUnitDefaultTurnSpeedold));
		MH_EnableHook(GAME_GetUnitDefaultTurnSpeedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitFacing", FALSE))
	{
		GAME_GetUnitFacingorg = (GAME_GetUnitFacing) ((DWORD) GameDll + 0x3C5790);
		MH_CreateHook(GAME_GetUnitFacingorg, &GAME_GetUnitFacingmy, reinterpret_cast<void**>(&GAME_GetUnitFacingold));
		MH_EnableHook(GAME_GetUnitFacingorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitFlyHeight", FALSE))
	{
		GAME_GetUnitFlyHeightorg = (GAME_GetUnitFlyHeight) ((DWORD) GameDll + 0x3C5DA0);
		MH_CreateHook(GAME_GetUnitFlyHeightorg, &GAME_GetUnitFlyHeightmy, reinterpret_cast<void**>(&GAME_GetUnitFlyHeightold));
		MH_EnableHook(GAME_GetUnitFlyHeightorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitFoodMade", FALSE))
	{
		GAME_GetUnitFoodMadeorg = (GAME_GetUnitFoodMade) ((DWORD) GameDll + 0x3C5460);
		MH_CreateHook(GAME_GetUnitFoodMadeorg, &GAME_GetUnitFoodMademy, reinterpret_cast<void**>(&GAME_GetUnitFoodMadeold));
		MH_EnableHook(GAME_GetUnitFoodMadeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitFoodUsed", FALSE))
	{
		GAME_GetUnitFoodUsedorg = (GAME_GetUnitFoodUsed) ((DWORD) GameDll + 0x3C5440);
		MH_CreateHook(GAME_GetUnitFoodUsedorg, &GAME_GetUnitFoodUsedmy, reinterpret_cast<void**>(&GAME_GetUnitFoodUsedold));
		MH_EnableHook(GAME_GetUnitFoodUsedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitGoldCost", FALSE))
	{
		GAME_GetUnitGoldCostorg = (GAME_GetUnitGoldCost) ((DWORD) GameDll + 0x2DD1E0);
		MH_CreateHook(GAME_GetUnitGoldCostorg, &GAME_GetUnitGoldCostmy, reinterpret_cast<void**>(&GAME_GetUnitGoldCostold));
		MH_EnableHook(GAME_GetUnitGoldCostorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitLevel", FALSE))
	{
		GAME_GetUnitLevelorg = (GAME_GetUnitLevel) ((DWORD) GameDll + 0x3C6F30);
		MH_CreateHook(GAME_GetUnitLevelorg, &GAME_GetUnitLevelmy, reinterpret_cast<void**>(&GAME_GetUnitLevelold));
		MH_EnableHook(GAME_GetUnitLevelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitLoc", FALSE))
	{
		GAME_GetUnitLocorg = (GAME_GetUnitLoc) ((DWORD) GameDll + 0x3D2AE0);
		MH_CreateHook(GAME_GetUnitLocorg, &GAME_GetUnitLocmy, reinterpret_cast<void**>(&GAME_GetUnitLocold));
		MH_EnableHook(GAME_GetUnitLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitMoveSpeed", FALSE))
	{
		GAME_GetUnitMoveSpeedorg = (GAME_GetUnitMoveSpeed) ((DWORD) GameDll + 0x3C5810);
		MH_CreateHook(GAME_GetUnitMoveSpeedorg, &GAME_GetUnitMoveSpeedmy, reinterpret_cast<void**>(&GAME_GetUnitMoveSpeedold));
		MH_EnableHook(GAME_GetUnitMoveSpeedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitName", FALSE))
	{
		GAME_GetUnitNameorg = (GAME_GetUnitName) ((DWORD) GameDll + 0x3C5950);
		MH_CreateHook(GAME_GetUnitNameorg, &GAME_GetUnitNamemy, reinterpret_cast<void**>(&GAME_GetUnitNameold));
		MH_EnableHook(GAME_GetUnitNameorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitPointValue", FALSE))
	{
		GAME_GetUnitPointValueorg = (GAME_GetUnitPointValue) ((DWORD) GameDll + 0x3C5E80);
		MH_CreateHook(GAME_GetUnitPointValueorg, &GAME_GetUnitPointValuemy, reinterpret_cast<void**>(&GAME_GetUnitPointValueold));
		MH_EnableHook(GAME_GetUnitPointValueorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitPointValueByType", FALSE))
	{
		GAME_GetUnitPointValueByTypeorg = (GAME_GetUnitPointValueByType) ((DWORD) GameDll + 0x3B2E20);
		MH_CreateHook(GAME_GetUnitPointValueByTypeorg, &GAME_GetUnitPointValueByTypemy, reinterpret_cast<void**>(&GAME_GetUnitPointValueByTypeold));
		MH_EnableHook(GAME_GetUnitPointValueByTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitPropWindow", FALSE))
	{
		GAME_GetUnitPropWindoworg = (GAME_GetUnitPropWindow) ((DWORD) GameDll + 0x3C5D70);
		MH_CreateHook(GAME_GetUnitPropWindoworg, &GAME_GetUnitPropWindowmy, reinterpret_cast<void**>(&GAME_GetUnitPropWindowold));
		MH_EnableHook(GAME_GetUnitPropWindoworg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitRace", FALSE))
	{
		GAME_GetUnitRaceorg = (GAME_GetUnitRace) ((DWORD) GameDll + 0x3C5930);
		MH_CreateHook(GAME_GetUnitRaceorg, &GAME_GetUnitRacemy, reinterpret_cast<void**>(&GAME_GetUnitRaceold));
		MH_EnableHook(GAME_GetUnitRaceorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitRallyDestructable", FALSE))
	{
		GAME_GetUnitRallyDestructableorg = (GAME_GetUnitRallyDestructable) ((DWORD) GameDll + 0x3C5690);
		MH_CreateHook(GAME_GetUnitRallyDestructableorg, &GAME_GetUnitRallyDestructablemy, reinterpret_cast<void**>(&GAME_GetUnitRallyDestructableold));
		MH_EnableHook(GAME_GetUnitRallyDestructableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitRallyPoint", FALSE))
	{
		GAME_GetUnitRallyPointorg = (GAME_GetUnitRallyPoint) ((DWORD) GameDll + 0x3D2B40);
		MH_CreateHook(GAME_GetUnitRallyPointorg, &GAME_GetUnitRallyPointmy, reinterpret_cast<void**>(&GAME_GetUnitRallyPointold));
		MH_EnableHook(GAME_GetUnitRallyPointorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitRallyUnit", FALSE))
	{
		GAME_GetUnitRallyUnitorg = (GAME_GetUnitRallyUnit) ((DWORD) GameDll + 0x3C5590);
		MH_CreateHook(GAME_GetUnitRallyUnitorg, &GAME_GetUnitRallyUnitmy, reinterpret_cast<void**>(&GAME_GetUnitRallyUnitold));
		MH_EnableHook(GAME_GetUnitRallyUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitState", FALSE))
	{
		GAME_GetUnitStateorg = (GAME_GetUnitState) ((DWORD) GameDll + 0x3C5400);
		MH_CreateHook(GAME_GetUnitStateorg, &GAME_GetUnitStatemy, reinterpret_cast<void**>(&GAME_GetUnitStateold));
		MH_EnableHook(GAME_GetUnitStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitTurnSpeed", FALSE))
	{
		GAME_GetUnitTurnSpeedorg = (GAME_GetUnitTurnSpeed) ((DWORD) GameDll + 0x3C5D40);
		MH_CreateHook(GAME_GetUnitTurnSpeedorg, &GAME_GetUnitTurnSpeedmy, reinterpret_cast<void**>(&GAME_GetUnitTurnSpeedold));
		MH_EnableHook(GAME_GetUnitTurnSpeedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitTypeId", FALSE))
	{
		GAME_GetUnitTypeIdorg = (GAME_GetUnitTypeId) ((DWORD) GameDll + 0x3C5910);
		MH_CreateHook(GAME_GetUnitTypeIdorg, &GAME_GetUnitTypeIdmy, reinterpret_cast<void**>(&GAME_GetUnitTypeIdold));
		MH_EnableHook(GAME_GetUnitTypeIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitUserData", FALSE))
	{
		GAME_GetUnitUserDataorg = (GAME_GetUnitUserData) ((DWORD) GameDll + 0x3C94F0);
		MH_CreateHook(GAME_GetUnitUserDataorg, &GAME_GetUnitUserDatamy, reinterpret_cast<void**>(&GAME_GetUnitUserDataold));
		MH_EnableHook(GAME_GetUnitUserDataorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitWoodCost", FALSE))
	{
		GAME_GetUnitWoodCostorg = (GAME_GetUnitWoodCost) ((DWORD) GameDll + 0x2DD240);
		MH_CreateHook(GAME_GetUnitWoodCostorg, &GAME_GetUnitWoodCostmy, reinterpret_cast<void**>(&GAME_GetUnitWoodCostold));
		MH_EnableHook(GAME_GetUnitWoodCostorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitX", FALSE))
	{
		GAME_GetUnitXorg = (GAME_GetUnitX) ((DWORD) GameDll + 0x3C5510);
		MH_CreateHook(GAME_GetUnitXorg, &GAME_GetUnitXmy, reinterpret_cast<void**>(&GAME_GetUnitXold));
		MH_EnableHook(GAME_GetUnitXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUnitY", FALSE))
	{
		GAME_GetUnitYorg = (GAME_GetUnitY) ((DWORD) GameDll + 0x3C5550);
		MH_CreateHook(GAME_GetUnitYorg, &GAME_GetUnitYmy, reinterpret_cast<void**>(&GAME_GetUnitYold));
		MH_EnableHook(GAME_GetUnitYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUpgradeGoldCost", FALSE))
	{
		GAME_GetUpgradeGoldCostorg = (GAME_GetUpgradeGoldCost) ((DWORD) GameDll + 0x2DD2A0);
		MH_CreateHook(GAME_GetUpgradeGoldCostorg, &GAME_GetUpgradeGoldCostmy, reinterpret_cast<void**>(&GAME_GetUpgradeGoldCostold));
		MH_EnableHook(GAME_GetUpgradeGoldCostorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUpgradeLevel", FALSE))
	{
		GAME_GetUpgradeLevelorg = (GAME_GetUpgradeLevel) ((DWORD) GameDll + 0x2DD130);
		MH_CreateHook(GAME_GetUpgradeLevelorg, &GAME_GetUpgradeLevelmy, reinterpret_cast<void**>(&GAME_GetUpgradeLevelold));
		MH_EnableHook(GAME_GetUpgradeLevelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetUpgradeWoodCost", FALSE))
	{
		GAME_GetUpgradeWoodCostorg = (GAME_GetUpgradeWoodCost) ((DWORD) GameDll + 0x2DD2C0);
		MH_CreateHook(GAME_GetUpgradeWoodCostorg, &GAME_GetUpgradeWoodCostmy, reinterpret_cast<void**>(&GAME_GetUpgradeWoodCostold));
		MH_EnableHook(GAME_GetUpgradeWoodCostorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetWidgetLife", FALSE))
	{
		GAME_GetWidgetLifeorg = (GAME_GetWidgetLife) ((DWORD) GameDll + 0x3C4660);
		MH_CreateHook(GAME_GetWidgetLifeorg, &GAME_GetWidgetLifemy, reinterpret_cast<void**>(&GAME_GetWidgetLifeold));
		MH_EnableHook(GAME_GetWidgetLifeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetWidgetX", FALSE))
	{
		GAME_GetWidgetXorg = (GAME_GetWidgetX) ((DWORD) GameDll + 0x3C46B0);
		MH_CreateHook(GAME_GetWidgetXorg, &GAME_GetWidgetXmy, reinterpret_cast<void**>(&GAME_GetWidgetXold));
		MH_EnableHook(GAME_GetWidgetXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetWidgetY", FALSE))
	{
		GAME_GetWidgetYorg = (GAME_GetWidgetY) ((DWORD) GameDll + 0x3C46F0);
		MH_CreateHook(GAME_GetWidgetYorg, &GAME_GetWidgetYmy, reinterpret_cast<void**>(&GAME_GetWidgetYold));
		MH_EnableHook(GAME_GetWidgetYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetWinningPlayer", FALSE))
	{
		GAME_GetWinningPlayerorg = (GAME_GetWinningPlayer) ((DWORD) GameDll + 0x3BB3E0);
		MH_CreateHook(GAME_GetWinningPlayerorg, &GAME_GetWinningPlayermy, reinterpret_cast<void**>(&GAME_GetWinningPlayerold));
		MH_EnableHook(GAME_GetWinningPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GetWorldBounds", FALSE))
	{
		GAME_GetWorldBoundsorg = (GAME_GetWorldBounds) ((DWORD) GameDll + 0x3D0D60);
		MH_CreateHook(GAME_GetWorldBoundsorg, &GAME_GetWorldBoundsmy, reinterpret_cast<void**>(&GAME_GetWorldBoundsold));
		MH_EnableHook(GAME_GetWorldBoundsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupAddUnit", FALSE))
	{
		GAME_GroupAddUnitorg = (GAME_GroupAddUnit) ((DWORD) GameDll + 0x3C3FC0);
		MH_CreateHook(GAME_GroupAddUnitorg, &GAME_GroupAddUnitmy, reinterpret_cast<void**>(&GAME_GroupAddUnitold));
		MH_EnableHook(GAME_GroupAddUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupClear", FALSE))
	{
		GAME_GroupClearorg = (GAME_GroupClear) ((DWORD) GameDll + 0x3C4020);
		MH_CreateHook(GAME_GroupClearorg, &GAME_GroupClearmy, reinterpret_cast<void**>(&GAME_GroupClearold));
		MH_EnableHook(GAME_GroupClearorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupEnumUnitsInRange", FALSE))
	{
		GAME_GroupEnumUnitsInRangeorg = (GAME_GroupEnumUnitsInRange) ((DWORD) GameDll + 0x3C41A0);
		MH_CreateHook(GAME_GroupEnumUnitsInRangeorg, &GAME_GroupEnumUnitsInRangemy, reinterpret_cast<void**>(&GAME_GroupEnumUnitsInRangeold));
		MH_EnableHook(GAME_GroupEnumUnitsInRangeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupEnumUnitsInRangeCounted", FALSE))
	{
		GAME_GroupEnumUnitsInRangeCountedorg = (GAME_GroupEnumUnitsInRangeCounted) ((DWORD) GameDll + 0x3C4230);
		MH_CreateHook(GAME_GroupEnumUnitsInRangeCountedorg, &GAME_GroupEnumUnitsInRangeCountedmy, reinterpret_cast<void**>(&GAME_GroupEnumUnitsInRangeCountedold));
		MH_EnableHook(GAME_GroupEnumUnitsInRangeCountedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupEnumUnitsInRangeOfLoc", FALSE))
	{
		GAME_GroupEnumUnitsInRangeOfLocorg = (GAME_GroupEnumUnitsInRangeOfLoc) ((DWORD) GameDll + 0x3C41E0);
		MH_CreateHook(GAME_GroupEnumUnitsInRangeOfLocorg, &GAME_GroupEnumUnitsInRangeOfLocmy, reinterpret_cast<void**>(&GAME_GroupEnumUnitsInRangeOfLocold));
		MH_EnableHook(GAME_GroupEnumUnitsInRangeOfLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupEnumUnitsInRangeOfLocCounted", FALSE))
	{
		GAME_GroupEnumUnitsInRangeOfLocCountedorg = (GAME_GroupEnumUnitsInRangeOfLocCounted) ((DWORD) GameDll + 0x3C4270);
		MH_CreateHook(GAME_GroupEnumUnitsInRangeOfLocCountedorg, &GAME_GroupEnumUnitsInRangeOfLocCountedmy, reinterpret_cast<void**>(&GAME_GroupEnumUnitsInRangeOfLocCountedold));
		MH_EnableHook(GAME_GroupEnumUnitsInRangeOfLocCountedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupEnumUnitsInRect", FALSE))
	{
		GAME_GroupEnumUnitsInRectorg = (GAME_GroupEnumUnitsInRect) ((DWORD) GameDll + 0x3C40E0);
		MH_CreateHook(GAME_GroupEnumUnitsInRectorg, &GAME_GroupEnumUnitsInRectmy, reinterpret_cast<void**>(&GAME_GroupEnumUnitsInRectold));
		MH_EnableHook(GAME_GroupEnumUnitsInRectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupEnumUnitsInRectCounted", FALSE))
	{
		GAME_GroupEnumUnitsInRectCountedorg = (GAME_GroupEnumUnitsInRectCounted) ((DWORD) GameDll + 0x3C4140);
		MH_CreateHook(GAME_GroupEnumUnitsInRectCountedorg, &GAME_GroupEnumUnitsInRectCountedmy, reinterpret_cast<void**>(&GAME_GroupEnumUnitsInRectCountedold));
		MH_EnableHook(GAME_GroupEnumUnitsInRectCountedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupEnumUnitsOfPlayer", FALSE))
	{
		GAME_GroupEnumUnitsOfPlayerorg = (GAME_GroupEnumUnitsOfPlayer) ((DWORD) GameDll + 0x3C42C0);
		MH_CreateHook(GAME_GroupEnumUnitsOfPlayerorg, &GAME_GroupEnumUnitsOfPlayermy, reinterpret_cast<void**>(&GAME_GroupEnumUnitsOfPlayerold));
		MH_EnableHook(GAME_GroupEnumUnitsOfPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupEnumUnitsOfType", FALSE))
	{
		GAME_GroupEnumUnitsOfTypeorg = (GAME_GroupEnumUnitsOfType) ((DWORD) GameDll + 0x3C4040);
		MH_CreateHook(GAME_GroupEnumUnitsOfTypeorg, &GAME_GroupEnumUnitsOfTypemy, reinterpret_cast<void**>(&GAME_GroupEnumUnitsOfTypeold));
		MH_EnableHook(GAME_GroupEnumUnitsOfTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupEnumUnitsOfTypeCounted", FALSE))
	{
		GAME_GroupEnumUnitsOfTypeCountedorg = (GAME_GroupEnumUnitsOfTypeCounted) ((DWORD) GameDll + 0x3C4090);
		MH_CreateHook(GAME_GroupEnumUnitsOfTypeCountedorg, &GAME_GroupEnumUnitsOfTypeCountedmy, reinterpret_cast<void**>(&GAME_GroupEnumUnitsOfTypeCountedold));
		MH_EnableHook(GAME_GroupEnumUnitsOfTypeCountedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupEnumUnitsSelected", FALSE))
	{
		GAME_GroupEnumUnitsSelectedorg = (GAME_GroupEnumUnitsSelected) ((DWORD) GameDll + 0x3CE590);
		MH_CreateHook(GAME_GroupEnumUnitsSelectedorg, &GAME_GroupEnumUnitsSelectedmy, reinterpret_cast<void**>(&GAME_GroupEnumUnitsSelectedold));
		MH_EnableHook(GAME_GroupEnumUnitsSelectedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupImmediateOrder", FALSE))
	{
		GAME_GroupImmediateOrderorg = (GAME_GroupImmediateOrder) ((DWORD) GameDll + 0x3C4320);
		MH_CreateHook(GAME_GroupImmediateOrderorg, &GAME_GroupImmediateOrdermy, reinterpret_cast<void**>(&GAME_GroupImmediateOrderold));
		MH_EnableHook(GAME_GroupImmediateOrderorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupImmediateOrderById", FALSE))
	{
		GAME_GroupImmediateOrderByIdorg = (GAME_GroupImmediateOrderById) ((DWORD) GameDll + 0x3C4300);
		MH_CreateHook(GAME_GroupImmediateOrderByIdorg, &GAME_GroupImmediateOrderByIdmy, reinterpret_cast<void**>(&GAME_GroupImmediateOrderByIdold));
		MH_EnableHook(GAME_GroupImmediateOrderByIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupPointOrder", FALSE))
	{
		GAME_GroupPointOrderorg = (GAME_GroupPointOrder) ((DWORD) GameDll + 0x3C4370);
		MH_CreateHook(GAME_GroupPointOrderorg, &GAME_GroupPointOrdermy, reinterpret_cast<void**>(&GAME_GroupPointOrderold));
		MH_EnableHook(GAME_GroupPointOrderorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupPointOrderById", FALSE))
	{
		GAME_GroupPointOrderByIdorg = (GAME_GroupPointOrderById) ((DWORD) GameDll + 0x3C4340);
		MH_CreateHook(GAME_GroupPointOrderByIdorg, &GAME_GroupPointOrderByIdmy, reinterpret_cast<void**>(&GAME_GroupPointOrderByIdold));
		MH_EnableHook(GAME_GroupPointOrderByIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupPointOrderByIdLoc", FALSE))
	{
		GAME_GroupPointOrderByIdLocorg = (GAME_GroupPointOrderByIdLoc) ((DWORD) GameDll + 0x3C4390);
		MH_CreateHook(GAME_GroupPointOrderByIdLocorg, &GAME_GroupPointOrderByIdLocmy, reinterpret_cast<void**>(&GAME_GroupPointOrderByIdLocold));
		MH_EnableHook(GAME_GroupPointOrderByIdLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupPointOrderLoc", FALSE))
	{
		GAME_GroupPointOrderLocorg = (GAME_GroupPointOrderLoc) ((DWORD) GameDll + 0x3C43E0);
		MH_CreateHook(GAME_GroupPointOrderLocorg, &GAME_GroupPointOrderLocmy, reinterpret_cast<void**>(&GAME_GroupPointOrderLocold));
		MH_EnableHook(GAME_GroupPointOrderLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupRemoveUnit", FALSE))
	{
		GAME_GroupRemoveUnitorg = (GAME_GroupRemoveUnit) ((DWORD) GameDll + 0x3C3FF0);
		MH_CreateHook(GAME_GroupRemoveUnitorg, &GAME_GroupRemoveUnitmy, reinterpret_cast<void**>(&GAME_GroupRemoveUnitold));
		MH_EnableHook(GAME_GroupRemoveUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupTargetOrder", FALSE))
	{
		GAME_GroupTargetOrderorg = (GAME_GroupTargetOrder) ((DWORD) GameDll + 0x3C4440);
		MH_CreateHook(GAME_GroupTargetOrderorg, &GAME_GroupTargetOrdermy, reinterpret_cast<void**>(&GAME_GroupTargetOrderold));
		MH_EnableHook(GAME_GroupTargetOrderorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupTargetOrderById", FALSE))
	{
		GAME_GroupTargetOrderByIdorg = (GAME_GroupTargetOrderById) ((DWORD) GameDll + 0x3C4400);
		MH_CreateHook(GAME_GroupTargetOrderByIdorg, &GAME_GroupTargetOrderByIdmy, reinterpret_cast<void**>(&GAME_GroupTargetOrderByIdold));
		MH_EnableHook(GAME_GroupTargetOrderByIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_GroupTimedLife", FALSE))
	{
		GAME_GroupTimedLifeorg = (GAME_GroupTimedLife) ((DWORD) GameDll + 0x2E2D60);
		MH_CreateHook(GAME_GroupTimedLifeorg, &GAME_GroupTimedLifemy, reinterpret_cast<void**>(&GAME_GroupTimedLifeold));
		MH_EnableHook(GAME_GroupTimedLifeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_HarvestGold", FALSE))
	{
		GAME_HarvestGoldorg = (GAME_HarvestGold) ((DWORD) GameDll + 0x2DD5E0);
		MH_CreateHook(GAME_HarvestGoldorg, &GAME_HarvestGoldmy, reinterpret_cast<void**>(&GAME_HarvestGoldold));
		MH_EnableHook(GAME_HarvestGoldorg);
		Sleep(1);
	}

	InitHackPart2();
}

void InitHackPart2(void)
{

	DWORD GameDll = (DWORD) GetModuleHandle("Game.dll");
	CIniReader JassINI(".\\JassSpy.ini");



	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_HarvestWood", FALSE))
	{
		GAME_HarvestWoodorg = (GAME_HarvestWood) ((DWORD) GameDll + 0x2DD630);
		MH_CreateHook(GAME_HarvestWoodorg, &GAME_HarvestWoodmy, reinterpret_cast<void**>(&GAME_HarvestWoodold));
		MH_EnableHook(GAME_HarvestWoodorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_HaveSavedBOOLean", FALSE))
	{
		GAME_HaveSavedBOOLeanorg = (GAME_HaveSavedBOOLean) ((DWORD) GameDll + 0x3CB140);
		MH_CreateHook(GAME_HaveSavedBOOLeanorg, &GAME_HaveSavedBOOLeanmy, reinterpret_cast<void**>(&GAME_HaveSavedBOOLeanold));
		MH_EnableHook(GAME_HaveSavedBOOLeanorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_HaveSavedHandle", FALSE))
	{
		GAME_HaveSavedHandleorg = (GAME_HaveSavedHandle) ((DWORD) GameDll + 0x3CB1C0);
		MH_CreateHook(GAME_HaveSavedHandleorg, &GAME_HaveSavedHandlemy, reinterpret_cast<void**>(&GAME_HaveSavedHandleold));
		MH_EnableHook(GAME_HaveSavedHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_HaveSavedInteger", FALSE))
	{
		GAME_HaveSavedIntegerorg = (GAME_HaveSavedInteger) ((DWORD) GameDll + 0x3CB0C0);
		MH_CreateHook(GAME_HaveSavedIntegerorg, &GAME_HaveSavedIntegermy, reinterpret_cast<void**>(&GAME_HaveSavedIntegerold));
		MH_EnableHook(GAME_HaveSavedIntegerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_HaveSavedReal", FALSE))
	{
		GAME_HaveSavedRealorg = (GAME_HaveSavedReal) ((DWORD) GameDll + 0x3CB100);
		MH_CreateHook(GAME_HaveSavedRealorg, &GAME_HaveSavedRealmy, reinterpret_cast<void**>(&GAME_HaveSavedRealold));
		MH_EnableHook(GAME_HaveSavedRealorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_HaveSavedString", FALSE))
	{
		GAME_HaveSavedStringorg = (GAME_HaveSavedString) ((DWORD) GameDll + 0x3CB180);
		MH_CreateHook(GAME_HaveSavedStringorg, &GAME_HaveSavedStringmy, reinterpret_cast<void**>(&GAME_HaveSavedStringold));
		MH_EnableHook(GAME_HaveSavedStringorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_HaveStoredBOOLean", FALSE))
	{
		GAME_HaveStoredBOOLeanorg = (GAME_HaveStoredBOOLean) ((DWORD) GameDll + 0x3CAFD0);
		MH_CreateHook(GAME_HaveStoredBOOLeanorg, &GAME_HaveStoredBOOLeanmy, reinterpret_cast<void**>(&GAME_HaveStoredBOOLeanold));
		MH_EnableHook(GAME_HaveStoredBOOLeanorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_HaveStoredInteger", FALSE))
	{
		GAME_HaveStoredIntegerorg = (GAME_HaveStoredInteger) ((DWORD) GameDll + 0x3CAF30);
		MH_CreateHook(GAME_HaveStoredIntegerorg, &GAME_HaveStoredIntegermy, reinterpret_cast<void**>(&GAME_HaveStoredIntegerold));
		MH_EnableHook(GAME_HaveStoredIntegerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_HaveStoredReal", FALSE))
	{
		GAME_HaveStoredRealorg = (GAME_HaveStoredReal) ((DWORD) GameDll + 0x3CAF80);
		MH_CreateHook(GAME_HaveStoredRealorg, &GAME_HaveStoredRealmy, reinterpret_cast<void**>(&GAME_HaveStoredRealold));
		MH_EnableHook(GAME_HaveStoredRealorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_HaveStoredString", FALSE))
	{
		GAME_HaveStoredStringorg = (GAME_HaveStoredString) ((DWORD) GameDll + 0x3CB070);
		MH_CreateHook(GAME_HaveStoredStringorg, &GAME_HaveStoredStringmy, reinterpret_cast<void**>(&GAME_HaveStoredStringold));
		MH_EnableHook(GAME_HaveStoredStringorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_HaveStoredUnit", FALSE))
	{
		GAME_HaveStoredUnitorg = (GAME_HaveStoredUnit) ((DWORD) GameDll + 0x3CB020);
		MH_CreateHook(GAME_HaveStoredUnitorg, &GAME_HaveStoredUnitmy, reinterpret_cast<void**>(&GAME_HaveStoredUnitold));
		MH_EnableHook(GAME_HaveStoredUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_I2R", FALSE))
	{
		GAME_I2Rorg = (GAME_I2R) ((DWORD) GameDll + 0x3B2CC0);
		MH_CreateHook(GAME_I2Rorg, &GAME_I2Rmy, reinterpret_cast<void**>(&GAME_I2Rold));
		MH_EnableHook(GAME_I2Rorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_I2S", FALSE))
	{
		GAME_I2Sorg = (GAME_I2S) ((DWORD) GameDll + 0x3BAAA0);
		MH_CreateHook(GAME_I2Sorg, &GAME_I2Smy, reinterpret_cast<void**>(&GAME_I2Sold));
		MH_EnableHook(GAME_I2Sorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IgnoredUnits", FALSE))
	{
		GAME_IgnoredUnitsorg = (GAME_IgnoredUnits) ((DWORD) GameDll + 0x2DCE80);
		MH_CreateHook(GAME_IgnoredUnitsorg, &GAME_IgnoredUnitsmy, reinterpret_cast<void**>(&GAME_IgnoredUnitsold));
		MH_EnableHook(GAME_IgnoredUnitsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IncUnitAbilityLevel", FALSE))
	{
		GAME_IncUnitAbilityLevelorg = (GAME_IncUnitAbilityLevel) ((DWORD) GameDll + 0x3C7130);
		MH_CreateHook(GAME_IncUnitAbilityLevelorg, &GAME_IncUnitAbilityLevelmy, reinterpret_cast<void**>(&GAME_IncUnitAbilityLevelold));
		MH_EnableHook(GAME_IncUnitAbilityLevelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_InitAssault", FALSE))
	{
		GAME_InitAssaultorg = (GAME_InitAssault) ((DWORD) GameDll + 0x2DD990);
		MH_CreateHook(GAME_InitAssaultorg, &GAME_InitAssaultmy, reinterpret_cast<void**>(&GAME_InitAssaultold));
		MH_EnableHook(GAME_InitAssaultorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_InitGameCache", FALSE))
	{
		GAME_InitGameCacheorg = (GAME_InitGameCache) ((DWORD) GameDll + 0x3D2CC0);
		MH_CreateHook(GAME_InitGameCacheorg, &GAME_InitGameCachemy, reinterpret_cast<void**>(&GAME_InitGameCacheold));
		MH_EnableHook(GAME_InitGameCacheorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_InitHashtable", FALSE))
	{
		GAME_InitHashtableorg = (GAME_InitHashtable) ((DWORD) GameDll + 0x3D2DF0);
		MH_CreateHook(GAME_InitHashtableorg, &GAME_InitHashtablemy, reinterpret_cast<void**>(&GAME_InitHashtableold));
		MH_EnableHook(GAME_InitHashtableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsCineFilterDisplayed", FALSE))
	{
		GAME_IsCineFilterDisplayedorg = (GAME_IsCineFilterDisplayed) ((DWORD) GameDll + 0x3B5150);
		MH_CreateHook(GAME_IsCineFilterDisplayedorg, &GAME_IsCineFilterDisplayedmy, reinterpret_cast<void**>(&GAME_IsCineFilterDisplayedold));
		MH_EnableHook(GAME_IsCineFilterDisplayedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsDestructableInvulnerable", FALSE))
	{
		GAME_IsDestructableInvulnerableorg = (GAME_IsDestructableInvulnerable) ((DWORD) GameDll + 0x3C4790);
		MH_CreateHook(GAME_IsDestructableInvulnerableorg, &GAME_IsDestructableInvulnerablemy, reinterpret_cast<void**>(&GAME_IsDestructableInvulnerableold));
		MH_EnableHook(GAME_IsDestructableInvulnerableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsFogEnabled", FALSE))
	{
		GAME_IsFogEnabledorg = (GAME_IsFogEnabled) ((DWORD) GameDll + 0x3BB200);
		MH_CreateHook(GAME_IsFogEnabledorg, &GAME_IsFogEnabledmy, reinterpret_cast<void**>(&GAME_IsFogEnabledold));
		MH_EnableHook(GAME_IsFogEnabledorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsFogMaskEnabled", FALSE))
	{
		GAME_IsFogMaskEnabledorg = (GAME_IsFogMaskEnabled) ((DWORD) GameDll + 0x3BB230);
		MH_CreateHook(GAME_IsFogMaskEnabledorg, &GAME_IsFogMaskEnabledmy, reinterpret_cast<void**>(&GAME_IsFogMaskEnabledold));
		MH_EnableHook(GAME_IsFogMaskEnabledorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsFoggedToPlayer", FALSE))
	{
		GAME_IsFoggedToPlayerorg = (GAME_IsFoggedToPlayer) ((DWORD) GameDll + 0x3C9980);
		MH_CreateHook(GAME_IsFoggedToPlayerorg, &GAME_IsFoggedToPlayermy, reinterpret_cast<void**>(&GAME_IsFoggedToPlayerold));
		MH_EnableHook(GAME_IsFoggedToPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsGameTypeSupported", FALSE))
	{
		GAME_IsGameTypeSupportedorg = (GAME_IsGameTypeSupported) ((DWORD) GameDll + 0x3BAE40);
		MH_CreateHook(GAME_IsGameTypeSupportedorg, &GAME_IsGameTypeSupportedmy, reinterpret_cast<void**>(&GAME_IsGameTypeSupportedold));
		MH_EnableHook(GAME_IsGameTypeSupportedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsHeroUnitId", FALSE))
	{
		GAME_IsHeroUnitIdorg = (GAME_IsHeroUnitId) ((DWORD) GameDll + 0x3B2E90);
		MH_CreateHook(GAME_IsHeroUnitIdorg, &GAME_IsHeroUnitIdmy, reinterpret_cast<void**>(&GAME_IsHeroUnitIdold));
		MH_EnableHook(GAME_IsHeroUnitIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsItemIdPawnable", FALSE))
	{
		GAME_IsItemIdPawnableorg = (GAME_IsItemIdPawnable) ((DWORD) GameDll + 0x3B2DF0);
		MH_CreateHook(GAME_IsItemIdPawnableorg, &GAME_IsItemIdPawnablemy, reinterpret_cast<void**>(&GAME_IsItemIdPawnableold));
		MH_EnableHook(GAME_IsItemIdPawnableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsItemIdPowerup", FALSE))
	{
		GAME_IsItemIdPoweruporg = (GAME_IsItemIdPowerup) ((DWORD) GameDll + 0x3B2DD0);
		MH_CreateHook(GAME_IsItemIdPoweruporg, &GAME_IsItemIdPowerupmy, reinterpret_cast<void**>(&GAME_IsItemIdPowerupold));
		MH_EnableHook(GAME_IsItemIdPoweruporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsItemIdSellable", FALSE))
	{
		GAME_IsItemIdSellableorg = (GAME_IsItemIdSellable) ((DWORD) GameDll + 0x3B2DE0);
		MH_CreateHook(GAME_IsItemIdSellableorg, &GAME_IsItemIdSellablemy, reinterpret_cast<void**>(&GAME_IsItemIdSellableold));
		MH_EnableHook(GAME_IsItemIdSellableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsItemInvulnerable", FALSE))
	{
		GAME_IsItemInvulnerableorg = (GAME_IsItemInvulnerable) ((DWORD) GameDll + 0x3C4F00);
		MH_CreateHook(GAME_IsItemInvulnerableorg, &GAME_IsItemInvulnerablemy, reinterpret_cast<void**>(&GAME_IsItemInvulnerableold));
		MH_EnableHook(GAME_IsItemInvulnerableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsItemOwned", FALSE))
	{
		GAME_IsItemOwnedorg = (GAME_IsItemOwned) ((DWORD) GameDll + 0x3C4F90);
		MH_CreateHook(GAME_IsItemOwnedorg, &GAME_IsItemOwnedmy, reinterpret_cast<void**>(&GAME_IsItemOwnedold));
		MH_EnableHook(GAME_IsItemOwnedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsItemPawnable", FALSE))
	{
		GAME_IsItemPawnableorg = (GAME_IsItemPawnable) ((DWORD) GameDll + 0x3C5010);
		MH_CreateHook(GAME_IsItemPawnableorg, &GAME_IsItemPawnablemy, reinterpret_cast<void**>(&GAME_IsItemPawnableold));
		MH_EnableHook(GAME_IsItemPawnableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsItemPowerup", FALSE))
	{
		GAME_IsItemPoweruporg = (GAME_IsItemPowerup) ((DWORD) GameDll + 0x3C4FD0);
		MH_CreateHook(GAME_IsItemPoweruporg, &GAME_IsItemPowerupmy, reinterpret_cast<void**>(&GAME_IsItemPowerupold));
		MH_EnableHook(GAME_IsItemPoweruporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsItemSellable", FALSE))
	{
		GAME_IsItemSellableorg = (GAME_IsItemSellable) ((DWORD) GameDll + 0x3C4FF0);
		MH_CreateHook(GAME_IsItemSellableorg, &GAME_IsItemSellablemy, reinterpret_cast<void**>(&GAME_IsItemSellableold));
		MH_EnableHook(GAME_IsItemSellableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsItemVisible", FALSE))
	{
		GAME_IsItemVisibleorg = (GAME_IsItemVisible) ((DWORD) GameDll + 0x3C4F70);
		MH_CreateHook(GAME_IsItemVisibleorg, &GAME_IsItemVisiblemy, reinterpret_cast<void**>(&GAME_IsItemVisibleold));
		MH_EnableHook(GAME_IsItemVisibleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsLeaderboardDisplayed", FALSE))
	{
		GAME_IsLeaderboardDisplayedorg = (GAME_IsLeaderboardDisplayed) ((DWORD) GameDll + 0x3CC220);
		MH_CreateHook(GAME_IsLeaderboardDisplayedorg, &GAME_IsLeaderboardDisplayedmy, reinterpret_cast<void**>(&GAME_IsLeaderboardDisplayedold));
		MH_EnableHook(GAME_IsLeaderboardDisplayedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsLocationFoggedToPlayer", FALSE))
	{
		GAME_IsLocationFoggedToPlayerorg = (GAME_IsLocationFoggedToPlayer) ((DWORD) GameDll + 0x3C99D0);
		MH_CreateHook(GAME_IsLocationFoggedToPlayerorg, &GAME_IsLocationFoggedToPlayermy, reinterpret_cast<void**>(&GAME_IsLocationFoggedToPlayerold));
		MH_EnableHook(GAME_IsLocationFoggedToPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsLocationInRegion", FALSE))
	{
		GAME_IsLocationInRegionorg = (GAME_IsLocationInRegion) ((DWORD) GameDll + 0x3C16B0);
		MH_CreateHook(GAME_IsLocationInRegionorg, &GAME_IsLocationInRegionmy, reinterpret_cast<void**>(&GAME_IsLocationInRegionold));
		MH_EnableHook(GAME_IsLocationInRegionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsLocationMaskedToPlayer", FALSE))
	{
		GAME_IsLocationMaskedToPlayerorg = (GAME_IsLocationMaskedToPlayer) ((DWORD) GameDll + 0x3C9A60);
		MH_CreateHook(GAME_IsLocationMaskedToPlayerorg, &GAME_IsLocationMaskedToPlayermy, reinterpret_cast<void**>(&GAME_IsLocationMaskedToPlayerold));
		MH_EnableHook(GAME_IsLocationMaskedToPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsLocationVisibleToPlayer", FALSE))
	{
		GAME_IsLocationVisibleToPlayerorg = (GAME_IsLocationVisibleToPlayer) ((DWORD) GameDll + 0x3C9940);
		MH_CreateHook(GAME_IsLocationVisibleToPlayerorg, &GAME_IsLocationVisibleToPlayermy, reinterpret_cast<void**>(&GAME_IsLocationVisibleToPlayerold));
		MH_EnableHook(GAME_IsLocationVisibleToPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsMapFlagSet", FALSE))
	{
		GAME_IsMapFlagSetorg = (GAME_IsMapFlagSet) ((DWORD) GameDll + 0x3BAEA0);
		MH_CreateHook(GAME_IsMapFlagSetorg, &GAME_IsMapFlagSetmy, reinterpret_cast<void**>(&GAME_IsMapFlagSetold));
		MH_EnableHook(GAME_IsMapFlagSetorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsMaskedToPlayer", FALSE))
	{
		GAME_IsMaskedToPlayerorg = (GAME_IsMaskedToPlayer) ((DWORD) GameDll + 0x3C9A10);
		MH_CreateHook(GAME_IsMaskedToPlayerorg, &GAME_IsMaskedToPlayermy, reinterpret_cast<void**>(&GAME_IsMaskedToPlayerold));
		MH_EnableHook(GAME_IsMaskedToPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsMultiboardDisplayed", FALSE))
	{
		GAME_IsMultiboardDisplayedorg = (GAME_IsMultiboardDisplayed) ((DWORD) GameDll + 0x3CC690);
		MH_CreateHook(GAME_IsMultiboardDisplayedorg, &GAME_IsMultiboardDisplayedmy, reinterpret_cast<void**>(&GAME_IsMultiboardDisplayedold));
		MH_EnableHook(GAME_IsMultiboardDisplayedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsMultiboardMinimized", FALSE))
	{
		GAME_IsMultiboardMinimizedorg = (GAME_IsMultiboardMinimized) ((DWORD) GameDll + 0x3CC6D0);
		MH_CreateHook(GAME_IsMultiboardMinimizedorg, &GAME_IsMultiboardMinimizedmy, reinterpret_cast<void**>(&GAME_IsMultiboardMinimizedold));
		MH_EnableHook(GAME_IsMultiboardMinimizedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsNoDefeatCheat", FALSE))
	{
		GAME_IsNoDefeatCheatorg = (GAME_IsNoDefeatCheat) ((DWORD) GameDll + 0x3BC8F0);
		MH_CreateHook(GAME_IsNoDefeatCheatorg, &GAME_IsNoDefeatCheatmy, reinterpret_cast<void**>(&GAME_IsNoDefeatCheatold));
		MH_EnableHook(GAME_IsNoDefeatCheatorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsNoVictoryCheat", FALSE))
	{
		GAME_IsNoVictoryCheatorg = (GAME_IsNoVictoryCheat) ((DWORD) GameDll + 0x3BC8C0);
		MH_CreateHook(GAME_IsNoVictoryCheatorg, &GAME_IsNoVictoryCheatmy, reinterpret_cast<void**>(&GAME_IsNoVictoryCheatold));
		MH_EnableHook(GAME_IsNoVictoryCheatorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsPlayerAlly", FALSE))
	{
		GAME_IsPlayerAllyorg = (GAME_IsPlayerAlly) ((DWORD) GameDll + 0x3C9530);
		MH_CreateHook(GAME_IsPlayerAllyorg, &GAME_IsPlayerAllymy, reinterpret_cast<void**>(&GAME_IsPlayerAllyold));
		MH_EnableHook(GAME_IsPlayerAllyorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsPlayerEnemy", FALSE))
	{
		GAME_IsPlayerEnemyorg = (GAME_IsPlayerEnemy) ((DWORD) GameDll + 0x3C9580);
		MH_CreateHook(GAME_IsPlayerEnemyorg, &GAME_IsPlayerEnemymy, reinterpret_cast<void**>(&GAME_IsPlayerEnemyold));
		MH_EnableHook(GAME_IsPlayerEnemyorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsPlayerInForce", FALSE))
	{
		GAME_IsPlayerInForceorg = (GAME_IsPlayerInForce) ((DWORD) GameDll + 0x3C95D0);
		MH_CreateHook(GAME_IsPlayerInForceorg, &GAME_IsPlayerInForcemy, reinterpret_cast<void**>(&GAME_IsPlayerInForceold));
		MH_EnableHook(GAME_IsPlayerInForceorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsPlayerObserver", FALSE))
	{
		GAME_IsPlayerObserverorg = (GAME_IsPlayerObserver) ((DWORD) GameDll + 0x3C9600);
		MH_CreateHook(GAME_IsPlayerObserverorg, &GAME_IsPlayerObservermy, reinterpret_cast<void**>(&GAME_IsPlayerObserverold));
		MH_EnableHook(GAME_IsPlayerObserverorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsPlayerRacePrefSet", FALSE))
	{
		GAME_IsPlayerRacePrefSetorg = (GAME_IsPlayerRacePrefSet) ((DWORD) GameDll + 0x3C1260);
		MH_CreateHook(GAME_IsPlayerRacePrefSetorg, &GAME_IsPlayerRacePrefSetmy, reinterpret_cast<void**>(&GAME_IsPlayerRacePrefSetold));
		MH_EnableHook(GAME_IsPlayerRacePrefSetorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsPointBlighted", FALSE))
	{
		GAME_IsPointBlightedorg = (GAME_IsPointBlighted) ((DWORD) GameDll + 0x3B4550);
		MH_CreateHook(GAME_IsPointBlightedorg, &GAME_IsPointBlightedmy, reinterpret_cast<void**>(&GAME_IsPointBlightedold));
		MH_EnableHook(GAME_IsPointBlightedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsPointInRegion", FALSE))
	{
		GAME_IsPointInRegionorg = (GAME_IsPointInRegion) ((DWORD) GameDll + 0x3C1690);
		MH_CreateHook(GAME_IsPointInRegionorg, &GAME_IsPointInRegionmy, reinterpret_cast<void**>(&GAME_IsPointInRegionold));
		MH_EnableHook(GAME_IsPointInRegionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsQuestCompleted", FALSE))
	{
		GAME_IsQuestCompletedorg = (GAME_IsQuestCompleted) ((DWORD) GameDll + 0x3CBCC0);
		MH_CreateHook(GAME_IsQuestCompletedorg, &GAME_IsQuestCompletedmy, reinterpret_cast<void**>(&GAME_IsQuestCompletedold));
		MH_EnableHook(GAME_IsQuestCompletedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsQuestDiscovered", FALSE))
	{
		GAME_IsQuestDiscoveredorg = (GAME_IsQuestDiscovered) ((DWORD) GameDll + 0x3CBCE0);
		MH_CreateHook(GAME_IsQuestDiscoveredorg, &GAME_IsQuestDiscoveredmy, reinterpret_cast<void**>(&GAME_IsQuestDiscoveredold));
		MH_EnableHook(GAME_IsQuestDiscoveredorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsQuestEnabled", FALSE))
	{
		GAME_IsQuestEnabledorg = (GAME_IsQuestEnabled) ((DWORD) GameDll + 0x3CBD20);
		MH_CreateHook(GAME_IsQuestEnabledorg, &GAME_IsQuestEnabledmy, reinterpret_cast<void**>(&GAME_IsQuestEnabledold));
		MH_EnableHook(GAME_IsQuestEnabledorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsQuestFailed", FALSE))
	{
		GAME_IsQuestFailedorg = (GAME_IsQuestFailed) ((DWORD) GameDll + 0x3CBD00);
		MH_CreateHook(GAME_IsQuestFailedorg, &GAME_IsQuestFailedmy, reinterpret_cast<void**>(&GAME_IsQuestFailedold));
		MH_EnableHook(GAME_IsQuestFailedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsQuestItemCompleted", FALSE))
	{
		GAME_IsQuestItemCompletedorg = (GAME_IsQuestItemCompleted) ((DWORD) GameDll + 0x3CBD90);
		MH_CreateHook(GAME_IsQuestItemCompletedorg, &GAME_IsQuestItemCompletedmy, reinterpret_cast<void**>(&GAME_IsQuestItemCompletedold));
		MH_EnableHook(GAME_IsQuestItemCompletedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsQuestRequired", FALSE))
	{
		GAME_IsQuestRequiredorg = (GAME_IsQuestRequired) ((DWORD) GameDll + 0x3CBCA0);
		MH_CreateHook(GAME_IsQuestRequiredorg, &GAME_IsQuestRequiredmy, reinterpret_cast<void**>(&GAME_IsQuestRequiredold));
		MH_EnableHook(GAME_IsQuestRequiredorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsSuspendedXP", FALSE))
	{
		GAME_IsSuspendedXPorg = (GAME_IsSuspendedXP) ((DWORD) GameDll + 0x3C6E70);
		MH_CreateHook(GAME_IsSuspendedXPorg, &GAME_IsSuspendedXPmy, reinterpret_cast<void**>(&GAME_IsSuspendedXPold));
		MH_EnableHook(GAME_IsSuspendedXPorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsTerrainPathable", FALSE))
	{
		GAME_IsTerrainPathableorg = (GAME_IsTerrainPathable) ((DWORD) GameDll + 0x3B42D0);
		MH_CreateHook(GAME_IsTerrainPathableorg, &GAME_IsTerrainPathablemy, reinterpret_cast<void**>(&GAME_IsTerrainPathableold));
		MH_EnableHook(GAME_IsTerrainPathableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsTimerDialogDisplayed", FALSE))
	{
		GAME_IsTimerDialogDisplayedorg = (GAME_IsTimerDialogDisplayed) ((DWORD) GameDll + 0x3CBF70);
		MH_CreateHook(GAME_IsTimerDialogDisplayedorg, &GAME_IsTimerDialogDisplayedmy, reinterpret_cast<void**>(&GAME_IsTimerDialogDisplayedold));
		MH_EnableHook(GAME_IsTimerDialogDisplayedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsTowered", FALSE))
	{
		GAME_IsToweredorg = (GAME_IsTowered) ((DWORD) GameDll + 0x2E0950);
		MH_CreateHook(GAME_IsToweredorg, &GAME_IsToweredmy, reinterpret_cast<void**>(&GAME_IsToweredold));
		MH_EnableHook(GAME_IsToweredorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsTriggerEnabled", FALSE))
	{
		GAME_IsTriggerEnabledorg = (GAME_IsTriggerEnabled) ((DWORD) GameDll + 0x3C1C80);
		MH_CreateHook(GAME_IsTriggerEnabledorg, &GAME_IsTriggerEnabledmy, reinterpret_cast<void**>(&GAME_IsTriggerEnabledold));
		MH_EnableHook(GAME_IsTriggerEnabledorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsTriggerWaitOnSleeps", FALSE))
	{
		GAME_IsTriggerWaitOnSleepsorg = (GAME_IsTriggerWaitOnSleeps) ((DWORD) GameDll + 0x3C1CC0);
		MH_CreateHook(GAME_IsTriggerWaitOnSleepsorg, &GAME_IsTriggerWaitOnSleepsmy, reinterpret_cast<void**>(&GAME_IsTriggerWaitOnSleepsold));
		MH_EnableHook(GAME_IsTriggerWaitOnSleepsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnit", FALSE))
	{
		GAME_IsUnitorg = (GAME_IsUnit) ((DWORD) GameDll + 0x3C8020);
		MH_CreateHook(GAME_IsUnitorg, &GAME_IsUnitmy, reinterpret_cast<void**>(&GAME_IsUnitold));
		MH_EnableHook(GAME_IsUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitAlly", FALSE))
	{
		GAME_IsUnitAllyorg = (GAME_IsUnitAlly) ((DWORD) GameDll + 0x3C7A70);
		MH_CreateHook(GAME_IsUnitAllyorg, &GAME_IsUnitAllymy, reinterpret_cast<void**>(&GAME_IsUnitAllyold));
		MH_EnableHook(GAME_IsUnitAllyorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitDetected", FALSE))
	{
		GAME_IsUnitDetectedorg = (GAME_IsUnitDetected) ((DWORD) GameDll + 0x3C7C80);
		MH_CreateHook(GAME_IsUnitDetectedorg, &GAME_IsUnitDetectedmy, reinterpret_cast<void**>(&GAME_IsUnitDetectedold));
		MH_EnableHook(GAME_IsUnitDetectedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitEnemy", FALSE))
	{
		GAME_IsUnitEnemyorg = (GAME_IsUnitEnemy) ((DWORD) GameDll + 0x3C7AD0);
		MH_CreateHook(GAME_IsUnitEnemyorg, &GAME_IsUnitEnemymy, reinterpret_cast<void**>(&GAME_IsUnitEnemyold));
		MH_EnableHook(GAME_IsUnitEnemyorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitFogged", FALSE))
	{
		GAME_IsUnitFoggedorg = (GAME_IsUnitFogged) ((DWORD) GameDll + 0x3C7D00);
		MH_CreateHook(GAME_IsUnitFoggedorg, &GAME_IsUnitFoggedmy, reinterpret_cast<void**>(&GAME_IsUnitFoggedold));
		MH_EnableHook(GAME_IsUnitFoggedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitHidden", FALSE))
	{
		GAME_IsUnitHiddenorg = (GAME_IsUnitHidden) ((DWORD) GameDll + 0x3C7B30);
		MH_CreateHook(GAME_IsUnitHiddenorg, &GAME_IsUnitHiddenmy, reinterpret_cast<void**>(&GAME_IsUnitHiddenold));
		MH_EnableHook(GAME_IsUnitHiddenorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitIdType", FALSE))
	{
		GAME_IsUnitIdTypeorg = (GAME_IsUnitIdType) ((DWORD) GameDll + 0x3B7F60);
		MH_CreateHook(GAME_IsUnitIdTypeorg, &GAME_IsUnitIdTypemy, reinterpret_cast<void**>(&GAME_IsUnitIdTypeold));
		MH_EnableHook(GAME_IsUnitIdTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitIllusion", FALSE))
	{
		GAME_IsUnitIllusionorg = (GAME_IsUnitIllusion) ((DWORD) GameDll + 0x3C7B50);
		MH_CreateHook(GAME_IsUnitIllusionorg, &GAME_IsUnitIllusionmy, reinterpret_cast<void**>(&GAME_IsUnitIllusionold));
		MH_EnableHook(GAME_IsUnitIllusionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitInForce", FALSE))
	{
		GAME_IsUnitInForceorg = (GAME_IsUnitInForce) ((DWORD) GameDll + 0x3C79C0);
		MH_CreateHook(GAME_IsUnitInForceorg, &GAME_IsUnitInForcemy, reinterpret_cast<void**>(&GAME_IsUnitInForceold));
		MH_EnableHook(GAME_IsUnitInForceorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitInGroup", FALSE))
	{
		GAME_IsUnitInGrouporg = (GAME_IsUnitInGroup) ((DWORD) GameDll + 0x3C7A00);
		MH_CreateHook(GAME_IsUnitInGrouporg, &GAME_IsUnitInGroupmy, reinterpret_cast<void**>(&GAME_IsUnitInGroupold));
		MH_EnableHook(GAME_IsUnitInGrouporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitInRange", FALSE))
	{
		GAME_IsUnitInRangeorg = (GAME_IsUnitInRange) ((DWORD) GameDll + 0x3C8090);
		MH_CreateHook(GAME_IsUnitInRangeorg, &GAME_IsUnitInRangemy, reinterpret_cast<void**>(&GAME_IsUnitInRangeold));
		MH_EnableHook(GAME_IsUnitInRangeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitInRangeLoc", FALSE))
	{
		GAME_IsUnitInRangeLocorg = (GAME_IsUnitInRangeLoc) ((DWORD) GameDll + 0x3C8140);
		MH_CreateHook(GAME_IsUnitInRangeLocorg, &GAME_IsUnitInRangeLocmy, reinterpret_cast<void**>(&GAME_IsUnitInRangeLocold));
		MH_EnableHook(GAME_IsUnitInRangeLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitInRangeXY", FALSE))
	{
		GAME_IsUnitInRangeXYorg = (GAME_IsUnitInRangeXY) ((DWORD) GameDll + 0x3C80E0);
		MH_CreateHook(GAME_IsUnitInRangeXYorg, &GAME_IsUnitInRangeXYmy, reinterpret_cast<void**>(&GAME_IsUnitInRangeXYold));
		MH_EnableHook(GAME_IsUnitInRangeXYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitInRegion", FALSE))
	{
		GAME_IsUnitInRegionorg = (GAME_IsUnitInRegion) ((DWORD) GameDll + 0x3C1660);
		MH_CreateHook(GAME_IsUnitInRegionorg, &GAME_IsUnitInRegionmy, reinterpret_cast<void**>(&GAME_IsUnitInRegionold));
		MH_EnableHook(GAME_IsUnitInRegionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitInTransport", FALSE))
	{
		GAME_IsUnitInTransportorg = (GAME_IsUnitInTransport) ((DWORD) GameDll + 0x3C7B70);
		MH_CreateHook(GAME_IsUnitInTransportorg, &GAME_IsUnitInTransportmy, reinterpret_cast<void**>(&GAME_IsUnitInTransportold));
		MH_EnableHook(GAME_IsUnitInTransportorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitInvisible", FALSE))
	{
		GAME_IsUnitInvisibleorg = (GAME_IsUnitInvisible) ((DWORD) GameDll + 0x3C7CC0);
		MH_CreateHook(GAME_IsUnitInvisibleorg, &GAME_IsUnitInvisiblemy, reinterpret_cast<void**>(&GAME_IsUnitInvisibleold));
		MH_EnableHook(GAME_IsUnitInvisibleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitLoaded", FALSE))
	{
		GAME_IsUnitLoadedorg = (GAME_IsUnitLoaded) ((DWORD) GameDll + 0x3C7BA0);
		MH_CreateHook(GAME_IsUnitLoadedorg, &GAME_IsUnitLoadedmy, reinterpret_cast<void**>(&GAME_IsUnitLoadedold));
		MH_EnableHook(GAME_IsUnitLoadedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitMasked", FALSE))
	{
		GAME_IsUnitMaskedorg = (GAME_IsUnitMasked) ((DWORD) GameDll + 0x3C7D80);
		MH_CreateHook(GAME_IsUnitMaskedorg, &GAME_IsUnitMaskedmy, reinterpret_cast<void**>(&GAME_IsUnitMaskedold));
		MH_EnableHook(GAME_IsUnitMaskedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitOwnedByPlayer", FALSE))
	{
		GAME_IsUnitOwnedByPlayerorg = (GAME_IsUnitOwnedByPlayer) ((DWORD) GameDll + 0x3C7A30);
		MH_CreateHook(GAME_IsUnitOwnedByPlayerorg, &GAME_IsUnitOwnedByPlayermy, reinterpret_cast<void**>(&GAME_IsUnitOwnedByPlayerold));
		MH_EnableHook(GAME_IsUnitOwnedByPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitPaused", FALSE))
	{
		GAME_IsUnitPausedorg = (GAME_IsUnitPaused) ((DWORD) GameDll + 0x3C73A0);
		MH_CreateHook(GAME_IsUnitPausedorg, &GAME_IsUnitPausedmy, reinterpret_cast<void**>(&GAME_IsUnitPausedold));
		MH_EnableHook(GAME_IsUnitPausedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitRace", FALSE))
	{
		GAME_IsUnitRaceorg = (GAME_IsUnitRace) ((DWORD) GameDll + 0x3C7E60);
		MH_CreateHook(GAME_IsUnitRaceorg, &GAME_IsUnitRacemy, reinterpret_cast<void**>(&GAME_IsUnitRaceold));
		MH_EnableHook(GAME_IsUnitRaceorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitSelected", FALSE))
	{
		GAME_IsUnitSelectedorg = (GAME_IsUnitSelected) ((DWORD) GameDll + 0x3C7E00);
		MH_CreateHook(GAME_IsUnitSelectedorg, &GAME_IsUnitSelectedmy, reinterpret_cast<void**>(&GAME_IsUnitSelectedold));
		MH_EnableHook(GAME_IsUnitSelectedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitType", FALSE))
	{
		GAME_IsUnitTypeorg = (GAME_IsUnitType) ((DWORD) GameDll + 0x3C7E90);
		MH_CreateHook(GAME_IsUnitTypeorg, &GAME_IsUnitTypemy, reinterpret_cast<void**>(&GAME_IsUnitTypeold));
		MH_EnableHook(GAME_IsUnitTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsUnitVisible", FALSE))
	{
		GAME_IsUnitVisibleorg = (GAME_IsUnitVisible) ((DWORD) GameDll + 0x3C7AF0);
		MH_CreateHook(GAME_IsUnitVisibleorg, &GAME_IsUnitVisiblemy, reinterpret_cast<void**>(&GAME_IsUnitVisibleold));
		MH_EnableHook(GAME_IsUnitVisibleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IsVisibleToPlayer", FALSE))
	{
		GAME_IsVisibleToPlayerorg = (GAME_IsVisibleToPlayer) ((DWORD) GameDll + 0x3C98F0);
		MH_CreateHook(GAME_IsVisibleToPlayerorg, &GAME_IsVisibleToPlayermy, reinterpret_cast<void**>(&GAME_IsVisibleToPlayerold));
		MH_EnableHook(GAME_IsVisibleToPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssueBuildOrder", FALSE))
	{
		GAME_IssueBuildOrderorg = (GAME_IssueBuildOrder) ((DWORD) GameDll + 0x3C8E80);
		MH_CreateHook(GAME_IssueBuildOrderorg, &GAME_IssueBuildOrdermy, reinterpret_cast<void**>(&GAME_IssueBuildOrderold));
		MH_EnableHook(GAME_IssueBuildOrderorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssueBuildOrderById", FALSE))
	{
		GAME_IssueBuildOrderByIdorg = (GAME_IssueBuildOrderById) ((DWORD) GameDll + 0x3C8BE0);
		MH_CreateHook(GAME_IssueBuildOrderByIdorg, &GAME_IssueBuildOrderByIdmy, reinterpret_cast<void**>(&GAME_IssueBuildOrderByIdold));
		MH_EnableHook(GAME_IssueBuildOrderByIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssueImmediateOrder", FALSE))
	{
		GAME_IssueImmediateOrderorg = (GAME_IssueImmediateOrder) ((DWORD) GameDll + 0x3C8D80);
		MH_CreateHook(GAME_IssueImmediateOrderorg, &GAME_IssueImmediateOrdermy, reinterpret_cast<void**>(&GAME_IssueImmediateOrderold));
		MH_EnableHook(GAME_IssueImmediateOrderorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssueImmediateOrderById", FALSE))
	{
		GAME_IssueImmediateOrderByIdorg = (GAME_IssueImmediateOrderById) ((DWORD) GameDll + 0x3C8900);
		MH_CreateHook(GAME_IssueImmediateOrderByIdorg, &GAME_IssueImmediateOrderByIdmy, reinterpret_cast<void**>(&GAME_IssueImmediateOrderByIdold));
		MH_EnableHook(GAME_IssueImmediateOrderByIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssueInstantPointOrder", FALSE))
	{
		GAME_IssueInstantPointOrderorg = (GAME_IssueInstantPointOrder) ((DWORD) GameDll + 0x3C8E40);
		MH_CreateHook(GAME_IssueInstantPointOrderorg, &GAME_IssueInstantPointOrdermy, reinterpret_cast<void**>(&GAME_IssueInstantPointOrderold));
		MH_EnableHook(GAME_IssueInstantPointOrderorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssueInstantPointOrderById", FALSE))
	{
		GAME_IssueInstantPointOrderByIdorg = (GAME_IssueInstantPointOrderById) ((DWORD) GameDll + 0x3C8A20);
		MH_CreateHook(GAME_IssueInstantPointOrderByIdorg, &GAME_IssueInstantPointOrderByIdmy, reinterpret_cast<void**>(&GAME_IssueInstantPointOrderByIdold));
		MH_EnableHook(GAME_IssueInstantPointOrderByIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssueInstantTargetOrder", FALSE))
	{
		GAME_IssueInstantTargetOrderorg = (GAME_IssueInstantTargetOrder) ((DWORD) GameDll + 0x3C8E60);
		MH_CreateHook(GAME_IssueInstantTargetOrderorg, &GAME_IssueInstantTargetOrdermy, reinterpret_cast<void**>(&GAME_IssueInstantTargetOrderold));
		MH_EnableHook(GAME_IssueInstantTargetOrderorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssueInstantTargetOrderById", FALSE))
	{
		GAME_IssueInstantTargetOrderByIdorg = (GAME_IssueInstantTargetOrderById) ((DWORD) GameDll + 0x3C8AB0);
		MH_CreateHook(GAME_IssueInstantTargetOrderByIdorg, &GAME_IssueInstantTargetOrderByIdmy, reinterpret_cast<void**>(&GAME_IssueInstantTargetOrderByIdold));
		MH_EnableHook(GAME_IssueInstantTargetOrderByIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssueNeutralImmediateOrder", FALSE))
	{
		GAME_IssueNeutralImmediateOrderorg = (GAME_IssueNeutralImmediateOrder) ((DWORD) GameDll + 0x3C8EA0);
		MH_CreateHook(GAME_IssueNeutralImmediateOrderorg, &GAME_IssueNeutralImmediateOrdermy, reinterpret_cast<void**>(&GAME_IssueNeutralImmediateOrderold));
		MH_EnableHook(GAME_IssueNeutralImmediateOrderorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssueNeutralImmediateOrderById", FALSE))
	{
		GAME_IssueNeutralImmediateOrderByIdorg = (GAME_IssueNeutralImmediateOrderById) ((DWORD) GameDll + 0x3C8CA0);
		MH_CreateHook(GAME_IssueNeutralImmediateOrderByIdorg, &GAME_IssueNeutralImmediateOrderByIdmy, reinterpret_cast<void**>(&GAME_IssueNeutralImmediateOrderByIdold));
		MH_EnableHook(GAME_IssueNeutralImmediateOrderByIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssueNeutralPointOrder", FALSE))
	{
		GAME_IssueNeutralPointOrderorg = (GAME_IssueNeutralPointOrder) ((DWORD) GameDll + 0x3C8EC0);
		MH_CreateHook(GAME_IssueNeutralPointOrderorg, &GAME_IssueNeutralPointOrdermy, reinterpret_cast<void**>(&GAME_IssueNeutralPointOrderold));
		MH_EnableHook(GAME_IssueNeutralPointOrderorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssueNeutralPointOrderById", FALSE))
	{
		GAME_IssueNeutralPointOrderByIdorg = (GAME_IssueNeutralPointOrderById) ((DWORD) GameDll + 0x3C8CE0);
		MH_CreateHook(GAME_IssueNeutralPointOrderByIdorg, &GAME_IssueNeutralPointOrderByIdmy, reinterpret_cast<void**>(&GAME_IssueNeutralPointOrderByIdold));
		MH_EnableHook(GAME_IssueNeutralPointOrderByIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssueNeutralTargetOrder", FALSE))
	{
		GAME_IssueNeutralTargetOrderorg = (GAME_IssueNeutralTargetOrder) ((DWORD) GameDll + 0x3C8EE0);
		MH_CreateHook(GAME_IssueNeutralTargetOrderorg, &GAME_IssueNeutralTargetOrdermy, reinterpret_cast<void**>(&GAME_IssueNeutralTargetOrderold));
		MH_EnableHook(GAME_IssueNeutralTargetOrderorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssueNeutralTargetOrderById", FALSE))
	{
		GAME_IssueNeutralTargetOrderByIdorg = (GAME_IssueNeutralTargetOrderById) ((DWORD) GameDll + 0x3C8D30);
		MH_CreateHook(GAME_IssueNeutralTargetOrderByIdorg, &GAME_IssueNeutralTargetOrderByIdmy, reinterpret_cast<void**>(&GAME_IssueNeutralTargetOrderByIdold));
		MH_EnableHook(GAME_IssueNeutralTargetOrderByIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssuePointOrder", FALSE))
	{
		GAME_IssuePointOrderorg = (GAME_IssuePointOrder) ((DWORD) GameDll + 0x3C8DA0);
		MH_CreateHook(GAME_IssuePointOrderorg, &GAME_IssuePointOrdermy, reinterpret_cast<void**>(&GAME_IssuePointOrderold));
		MH_EnableHook(GAME_IssuePointOrderorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssuePointOrderById", FALSE))
	{
		GAME_IssuePointOrderByIdorg = (GAME_IssuePointOrderById) ((DWORD) GameDll + 0x3C8940);
		MH_CreateHook(GAME_IssuePointOrderByIdorg, &GAME_IssuePointOrderByIdmy, reinterpret_cast<void**>(&GAME_IssuePointOrderByIdold));
		MH_EnableHook(GAME_IssuePointOrderByIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssuePointOrderByIdLoc", FALSE))
	{
		GAME_IssuePointOrderByIdLocorg = (GAME_IssuePointOrderByIdLoc) ((DWORD) GameDll + 0x3C8980);
		MH_CreateHook(GAME_IssuePointOrderByIdLocorg, &GAME_IssuePointOrderByIdLocmy, reinterpret_cast<void**>(&GAME_IssuePointOrderByIdLocold));
		MH_EnableHook(GAME_IssuePointOrderByIdLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssuePointOrderLoc", FALSE))
	{
		GAME_IssuePointOrderLocorg = (GAME_IssuePointOrderLoc) ((DWORD) GameDll + 0x3C8DC0);
		MH_CreateHook(GAME_IssuePointOrderLocorg, &GAME_IssuePointOrderLocmy, reinterpret_cast<void**>(&GAME_IssuePointOrderLocold));
		MH_EnableHook(GAME_IssuePointOrderLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssueTargetOrder", FALSE))
	{
		GAME_IssueTargetOrderorg = (GAME_IssueTargetOrder) ((DWORD) GameDll + 0x3C8E20);
		MH_CreateHook(GAME_IssueTargetOrderorg, &GAME_IssueTargetOrdermy, reinterpret_cast<void**>(&GAME_IssueTargetOrderold));
		MH_EnableHook(GAME_IssueTargetOrderorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_IssueTargetOrderById", FALSE))
	{
		GAME_IssueTargetOrderByIdorg = (GAME_IssueTargetOrderById) ((DWORD) GameDll + 0x3C89D0);
		MH_CreateHook(GAME_IssueTargetOrderByIdorg, &GAME_IssueTargetOrderByIdmy, reinterpret_cast<void**>(&GAME_IssueTargetOrderByIdold));
		MH_EnableHook(GAME_IssueTargetOrderByIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ItemPoolAddItemType", FALSE))
	{
		GAME_ItemPoolAddItemTypeorg = (GAME_ItemPoolAddItemType) ((DWORD) GameDll + 0x3CB6C0);
		MH_CreateHook(GAME_ItemPoolAddItemTypeorg, &GAME_ItemPoolAddItemTypemy, reinterpret_cast<void**>(&GAME_ItemPoolAddItemTypeold));
		MH_EnableHook(GAME_ItemPoolAddItemTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ItemPoolRemoveItemType", FALSE))
	{
		GAME_ItemPoolRemoveItemTypeorg = (GAME_ItemPoolRemoveItemType) ((DWORD) GameDll + 0x3CB6E0);
		MH_CreateHook(GAME_ItemPoolRemoveItemTypeorg, &GAME_ItemPoolRemoveItemTypemy, reinterpret_cast<void**>(&GAME_ItemPoolRemoveItemTypeold));
		MH_EnableHook(GAME_ItemPoolRemoveItemTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_KillDestructable", FALSE))
	{
		GAME_KillDestructableorg = (GAME_KillDestructable) ((DWORD) GameDll + 0x3C4750);
		MH_CreateHook(GAME_KillDestructableorg, &GAME_KillDestructablemy, reinterpret_cast<void**>(&GAME_KillDestructableold));
		MH_EnableHook(GAME_KillDestructableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_KillSoundWhenDone", FALSE))
	{
		GAME_KillSoundWhenDoneorg = (GAME_KillSoundWhenDone) ((DWORD) GameDll + 0x3CCED0);
		MH_CreateHook(GAME_KillSoundWhenDoneorg, &GAME_KillSoundWhenDonemy, reinterpret_cast<void**>(&GAME_KillSoundWhenDoneold));
		MH_EnableHook(GAME_KillSoundWhenDoneorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_KillUnit", FALSE))
	{
		GAME_KillUnitorg = (GAME_KillUnit) ((DWORD) GameDll + 0x3C8040);
		MH_CreateHook(GAME_KillUnitorg, &GAME_KillUnitmy, reinterpret_cast<void**>(&GAME_KillUnitold));
		MH_EnableHook(GAME_KillUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardAddItem", FALSE))
	{
		GAME_LeaderboardAddItemorg = (GAME_LeaderboardAddItem) ((DWORD) GameDll + 0x3CC060);
		MH_CreateHook(GAME_LeaderboardAddItemorg, &GAME_LeaderboardAddItemmy, reinterpret_cast<void**>(&GAME_LeaderboardAddItemold));
		MH_EnableHook(GAME_LeaderboardAddItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardClear", FALSE))
	{
		GAME_LeaderboardClearorg = (GAME_LeaderboardClear) ((DWORD) GameDll + 0x3CC1B0);
		MH_CreateHook(GAME_LeaderboardClearorg, &GAME_LeaderboardClearmy, reinterpret_cast<void**>(&GAME_LeaderboardClearold));
		MH_EnableHook(GAME_LeaderboardClearorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardDisplay", FALSE))
	{
		GAME_LeaderboardDisplayorg = (GAME_LeaderboardDisplay) ((DWORD) GameDll + 0x3CC1D0);
		MH_CreateHook(GAME_LeaderboardDisplayorg, &GAME_LeaderboardDisplaymy, reinterpret_cast<void**>(&GAME_LeaderboardDisplayold));
		MH_EnableHook(GAME_LeaderboardDisplayorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardGetItemCount", FALSE))
	{
		GAME_LeaderboardGetItemCountorg = (GAME_LeaderboardGetItemCount) ((DWORD) GameDll + 0x3CC000);
		MH_CreateHook(GAME_LeaderboardGetItemCountorg, &GAME_LeaderboardGetItemCountmy, reinterpret_cast<void**>(&GAME_LeaderboardGetItemCountold));
		MH_EnableHook(GAME_LeaderboardGetItemCountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardGetLabelText", FALSE))
	{
		GAME_LeaderboardGetLabelTextorg = (GAME_LeaderboardGetLabelText) ((DWORD) GameDll + 0x3CC2F0);
		MH_CreateHook(GAME_LeaderboardGetLabelTextorg, &GAME_LeaderboardGetLabelTextmy, reinterpret_cast<void**>(&GAME_LeaderboardGetLabelTextold));
		MH_EnableHook(GAME_LeaderboardGetLabelTextorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardGetPlayerIndex", FALSE))
	{
		GAME_LeaderboardGetPlayerIndexorg = (GAME_LeaderboardGetPlayerIndex) ((DWORD) GameDll + 0x3CC2A0);
		MH_CreateHook(GAME_LeaderboardGetPlayerIndexorg, &GAME_LeaderboardGetPlayerIndexmy, reinterpret_cast<void**>(&GAME_LeaderboardGetPlayerIndexold));
		MH_EnableHook(GAME_LeaderboardGetPlayerIndexorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardHasPlayerItem", FALSE))
	{
		GAME_LeaderboardHasPlayerItemorg = (GAME_LeaderboardHasPlayerItem) ((DWORD) GameDll + 0x3CC250);
		MH_CreateHook(GAME_LeaderboardHasPlayerItemorg, &GAME_LeaderboardHasPlayerItemmy, reinterpret_cast<void**>(&GAME_LeaderboardHasPlayerItemold));
		MH_EnableHook(GAME_LeaderboardHasPlayerItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardRemoveItem", FALSE))
	{
		GAME_LeaderboardRemoveItemorg = (GAME_LeaderboardRemoveItem) ((DWORD) GameDll + 0x3CC0B0);
		MH_CreateHook(GAME_LeaderboardRemoveItemorg, &GAME_LeaderboardRemoveItemmy, reinterpret_cast<void**>(&GAME_LeaderboardRemoveItemold));
		MH_EnableHook(GAME_LeaderboardRemoveItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardRemovePlayerItem", FALSE))
	{
		GAME_LeaderboardRemovePlayerItemorg = (GAME_LeaderboardRemovePlayerItem) ((DWORD) GameDll + 0x3CC0E0);
		MH_CreateHook(GAME_LeaderboardRemovePlayerItemorg, &GAME_LeaderboardRemovePlayerItemmy, reinterpret_cast<void**>(&GAME_LeaderboardRemovePlayerItemold));
		MH_EnableHook(GAME_LeaderboardRemovePlayerItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardSetItemLabel", FALSE))
	{
		GAME_LeaderboardSetItemLabelorg = (GAME_LeaderboardSetItemLabel) ((DWORD) GameDll + 0x3CC520);
		MH_CreateHook(GAME_LeaderboardSetItemLabelorg, &GAME_LeaderboardSetItemLabelmy, reinterpret_cast<void**>(&GAME_LeaderboardSetItemLabelold));
		MH_EnableHook(GAME_LeaderboardSetItemLabelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardSetItemLabelColor", FALSE))
	{
		GAME_LeaderboardSetItemLabelColororg = (GAME_LeaderboardSetItemLabelColor) ((DWORD) GameDll + 0x3CC5B0);
		MH_CreateHook(GAME_LeaderboardSetItemLabelColororg, &GAME_LeaderboardSetItemLabelColormy, reinterpret_cast<void**>(&GAME_LeaderboardSetItemLabelColorold));
		MH_EnableHook(GAME_LeaderboardSetItemLabelColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardSetItemStyle", FALSE))
	{
		GAME_LeaderboardSetItemStyleorg = (GAME_LeaderboardSetItemStyle) ((DWORD) GameDll + 0x3CC560);
		MH_CreateHook(GAME_LeaderboardSetItemStyleorg, &GAME_LeaderboardSetItemStylemy, reinterpret_cast<void**>(&GAME_LeaderboardSetItemStyleold));
		MH_EnableHook(GAME_LeaderboardSetItemStyleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardSetItemValue", FALSE))
	{
		GAME_LeaderboardSetItemValueorg = (GAME_LeaderboardSetItemValue) ((DWORD) GameDll + 0x3CC4F0);
		MH_CreateHook(GAME_LeaderboardSetItemValueorg, &GAME_LeaderboardSetItemValuemy, reinterpret_cast<void**>(&GAME_LeaderboardSetItemValueold));
		MH_EnableHook(GAME_LeaderboardSetItemValueorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardSetItemValueColor", FALSE))
	{
		GAME_LeaderboardSetItemValueColororg = (GAME_LeaderboardSetItemValueColor) ((DWORD) GameDll + 0x3CC600);
		MH_CreateHook(GAME_LeaderboardSetItemValueColororg, &GAME_LeaderboardSetItemValueColormy, reinterpret_cast<void**>(&GAME_LeaderboardSetItemValueColorold));
		MH_EnableHook(GAME_LeaderboardSetItemValueColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardSetLabel", FALSE))
	{
		GAME_LeaderboardSetLabelorg = (GAME_LeaderboardSetLabel) ((DWORD) GameDll + 0x3CC3D0);
		MH_CreateHook(GAME_LeaderboardSetLabelorg, &GAME_LeaderboardSetLabelmy, reinterpret_cast<void**>(&GAME_LeaderboardSetLabelold));
		MH_EnableHook(GAME_LeaderboardSetLabelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardSetLabelColor", FALSE))
	{
		GAME_LeaderboardSetLabelColororg = (GAME_LeaderboardSetLabelColor) ((DWORD) GameDll + 0x3CC400);
		MH_CreateHook(GAME_LeaderboardSetLabelColororg, &GAME_LeaderboardSetLabelColormy, reinterpret_cast<void**>(&GAME_LeaderboardSetLabelColorold));
		MH_EnableHook(GAME_LeaderboardSetLabelColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardSetSizeByItemCount", FALSE))
	{
		GAME_LeaderboardSetSizeByItemCountorg = (GAME_LeaderboardSetSizeByItemCount) ((DWORD) GameDll + 0x3CC030);
		MH_CreateHook(GAME_LeaderboardSetSizeByItemCountorg, &GAME_LeaderboardSetSizeByItemCountmy, reinterpret_cast<void**>(&GAME_LeaderboardSetSizeByItemCountold));
		MH_EnableHook(GAME_LeaderboardSetSizeByItemCountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardSetStyle", FALSE))
	{
		GAME_LeaderboardSetStyleorg = (GAME_LeaderboardSetStyle) ((DWORD) GameDll + 0x3CC4A0);
		MH_CreateHook(GAME_LeaderboardSetStyleorg, &GAME_LeaderboardSetStylemy, reinterpret_cast<void**>(&GAME_LeaderboardSetStyleold));
		MH_EnableHook(GAME_LeaderboardSetStyleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardSetValueColor", FALSE))
	{
		GAME_LeaderboardSetValueColororg = (GAME_LeaderboardSetValueColor) ((DWORD) GameDll + 0x3CC450);
		MH_CreateHook(GAME_LeaderboardSetValueColororg, &GAME_LeaderboardSetValueColormy, reinterpret_cast<void**>(&GAME_LeaderboardSetValueColorold));
		MH_EnableHook(GAME_LeaderboardSetValueColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardSortItemsByLabel", FALSE))
	{
		GAME_LeaderboardSortItemsByLabelorg = (GAME_LeaderboardSortItemsByLabel) ((DWORD) GameDll + 0x3CC180);
		MH_CreateHook(GAME_LeaderboardSortItemsByLabelorg, &GAME_LeaderboardSortItemsByLabelmy, reinterpret_cast<void**>(&GAME_LeaderboardSortItemsByLabelold));
		MH_EnableHook(GAME_LeaderboardSortItemsByLabelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardSortItemsByPlayer", FALSE))
	{
		GAME_LeaderboardSortItemsByPlayerorg = (GAME_LeaderboardSortItemsByPlayer) ((DWORD) GameDll + 0x3CC150);
		MH_CreateHook(GAME_LeaderboardSortItemsByPlayerorg, &GAME_LeaderboardSortItemsByPlayermy, reinterpret_cast<void**>(&GAME_LeaderboardSortItemsByPlayerold));
		MH_EnableHook(GAME_LeaderboardSortItemsByPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LeaderboardSortItemsByValue", FALSE))
	{
		GAME_LeaderboardSortItemsByValueorg = (GAME_LeaderboardSortItemsByValue) ((DWORD) GameDll + 0x3CC120);
		MH_CreateHook(GAME_LeaderboardSortItemsByValueorg, &GAME_LeaderboardSortItemsByValuemy, reinterpret_cast<void**>(&GAME_LeaderboardSortItemsByValueold));
		MH_EnableHook(GAME_LeaderboardSortItemsByValueorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadAbilityHandle", FALSE))
	{
		GAME_LoadAbilityHandleorg = (GAME_LoadAbilityHandle) ((DWORD) GameDll + 0x3CEA60);
		MH_CreateHook(GAME_LoadAbilityHandleorg, &GAME_LoadAbilityHandlemy, reinterpret_cast<void**>(&GAME_LoadAbilityHandleold));
		MH_EnableHook(GAME_LoadAbilityHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadBOOLean", FALSE))
	{
		GAME_LoadBOOLeanorg = (GAME_LoadBOOLean) ((DWORD) GameDll + 0x3CAB10);
		MH_CreateHook(GAME_LoadBOOLeanorg, &GAME_LoadBOOLeanmy, reinterpret_cast<void**>(&GAME_LoadBOOLeanold));
		MH_EnableHook(GAME_LoadBOOLeanorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadBOOLeanExprHandle", FALSE))
	{
		GAME_LoadBOOLeanExprHandleorg = (GAME_LoadBOOLeanExprHandle) ((DWORD) GameDll + 0x3CAD70);
		MH_CreateHook(GAME_LoadBOOLeanExprHandleorg, &GAME_LoadBOOLeanExprHandlemy, reinterpret_cast<void**>(&GAME_LoadBOOLeanExprHandleold));
		MH_EnableHook(GAME_LoadBOOLeanExprHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadButtonHandle", FALSE))
	{
		GAME_LoadButtonHandleorg = (GAME_LoadButtonHandle) ((DWORD) GameDll + 0x3CADD0);
		MH_CreateHook(GAME_LoadButtonHandleorg, &GAME_LoadButtonHandlemy, reinterpret_cast<void**>(&GAME_LoadButtonHandleold));
		MH_EnableHook(GAME_LoadButtonHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadDefeatConditionHandle", FALSE))
	{
		GAME_LoadDefeatConditionHandleorg = (GAME_LoadDefeatConditionHandle) ((DWORD) GameDll + 0x3CEB20);
		MH_CreateHook(GAME_LoadDefeatConditionHandleorg, &GAME_LoadDefeatConditionHandlemy, reinterpret_cast<void**>(&GAME_LoadDefeatConditionHandleold));
		MH_EnableHook(GAME_LoadDefeatConditionHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadDestructableHandle", FALSE))
	{
		GAME_LoadDestructableHandleorg = (GAME_LoadDestructableHandle) ((DWORD) GameDll + 0x3CABD0);
		MH_CreateHook(GAME_LoadDestructableHandleorg, &GAME_LoadDestructableHandlemy, reinterpret_cast<void**>(&GAME_LoadDestructableHandleold));
		MH_EnableHook(GAME_LoadDestructableHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadDialogHandle", FALSE))
	{
		GAME_LoadDialogHandleorg = (GAME_LoadDialogHandle) ((DWORD) GameDll + 0x3CADB0);
		MH_CreateHook(GAME_LoadDialogHandleorg, &GAME_LoadDialogHandlemy, reinterpret_cast<void**>(&GAME_LoadDialogHandleold));
		MH_EnableHook(GAME_LoadDialogHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadEffectHandle", FALSE))
	{
		GAME_LoadEffectHandleorg = (GAME_LoadEffectHandle) ((DWORD) GameDll + 0x3CEA80);
		MH_CreateHook(GAME_LoadEffectHandleorg, &GAME_LoadEffectHandlemy, reinterpret_cast<void**>(&GAME_LoadEffectHandleold));
		MH_EnableHook(GAME_LoadEffectHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadFogModifierHandle", FALSE))
	{
		GAME_LoadFogModifierHandleorg = (GAME_LoadFogModifierHandle) ((DWORD) GameDll + 0x3CAEF0);
		MH_CreateHook(GAME_LoadFogModifierHandleorg, &GAME_LoadFogModifierHandlemy, reinterpret_cast<void**>(&GAME_LoadFogModifierHandleold));
		MH_EnableHook(GAME_LoadFogModifierHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadFogStateHandle", FALSE))
	{
		GAME_LoadFogStateHandleorg = (GAME_LoadFogStateHandle) ((DWORD) GameDll + 0x3CAED0);
		MH_CreateHook(GAME_LoadFogStateHandleorg, &GAME_LoadFogStateHandlemy, reinterpret_cast<void**>(&GAME_LoadFogStateHandleold));
		MH_EnableHook(GAME_LoadFogStateHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadForceHandle", FALSE))
	{
		GAME_LoadForceHandleorg = (GAME_LoadForceHandle) ((DWORD) GameDll + 0x3CACF0);
		MH_CreateHook(GAME_LoadForceHandleorg, &GAME_LoadForceHandlemy, reinterpret_cast<void**>(&GAME_LoadForceHandleold));
		MH_EnableHook(GAME_LoadForceHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadGame", FALSE))
	{
		GAME_LoadGameorg = (GAME_LoadGame) ((DWORD) GameDll + 0x3BBE60);
		MH_CreateHook(GAME_LoadGameorg, &GAME_LoadGamemy, reinterpret_cast<void**>(&GAME_LoadGameold));
		MH_EnableHook(GAME_LoadGameorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadGroupHandle", FALSE))
	{
		GAME_LoadGroupHandleorg = (GAME_LoadGroupHandle) ((DWORD) GameDll + 0x3CAD10);
		MH_CreateHook(GAME_LoadGroupHandleorg, &GAME_LoadGroupHandlemy, reinterpret_cast<void**>(&GAME_LoadGroupHandleold));
		MH_EnableHook(GAME_LoadGroupHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadHashtableHandle", FALSE))
	{
		GAME_LoadHashtableHandleorg = (GAME_LoadHashtableHandle) ((DWORD) GameDll + 0x3CAF10);
		MH_CreateHook(GAME_LoadHashtableHandleorg, &GAME_LoadHashtableHandlemy, reinterpret_cast<void**>(&GAME_LoadHashtableHandleold));
		MH_EnableHook(GAME_LoadHashtableHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadImageHandle", FALSE))
	{
		GAME_LoadImageHandleorg = (GAME_LoadImageHandle) ((DWORD) GameDll + 0x3CAE90);
		MH_CreateHook(GAME_LoadImageHandleorg, &GAME_LoadImageHandlemy, reinterpret_cast<void**>(&GAME_LoadImageHandleold));
		MH_EnableHook(GAME_LoadImageHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadInteger", FALSE))
	{
		GAME_LoadIntegerorg = (GAME_LoadInteger) ((DWORD) GameDll + 0x3CAA90);
		MH_CreateHook(GAME_LoadIntegerorg, &GAME_LoadIntegermy, reinterpret_cast<void**>(&GAME_LoadIntegerold));
		MH_EnableHook(GAME_LoadIntegerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadItemHandle", FALSE))
	{
		GAME_LoadItemHandleorg = (GAME_LoadItemHandle) ((DWORD) GameDll + 0x3CABF0);
		MH_CreateHook(GAME_LoadItemHandleorg, &GAME_LoadItemHandlemy, reinterpret_cast<void**>(&GAME_LoadItemHandleold));
		MH_EnableHook(GAME_LoadItemHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadItemPoolHandle", FALSE))
	{
		GAME_LoadItemPoolHandleorg = (GAME_LoadItemPoolHandle) ((DWORD) GameDll + 0x3CEAC0);
		MH_CreateHook(GAME_LoadItemPoolHandleorg, &GAME_LoadItemPoolHandlemy, reinterpret_cast<void**>(&GAME_LoadItemPoolHandleold));
		MH_EnableHook(GAME_LoadItemPoolHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadLeaderboardHandle", FALSE))
	{
		GAME_LoadLeaderboardHandleorg = (GAME_LoadLeaderboardHandle) ((DWORD) GameDll + 0x3CEB60);
		MH_CreateHook(GAME_LoadLeaderboardHandleorg, &GAME_LoadLeaderboardHandlemy, reinterpret_cast<void**>(&GAME_LoadLeaderboardHandleold));
		MH_EnableHook(GAME_LoadLeaderboardHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadLightningHandle", FALSE))
	{
		GAME_LoadLightningHandleorg = (GAME_LoadLightningHandle) ((DWORD) GameDll + 0x3CAE70);
		MH_CreateHook(GAME_LoadLightningHandleorg, &GAME_LoadLightningHandlemy, reinterpret_cast<void**>(&GAME_LoadLightningHandleold));
		MH_EnableHook(GAME_LoadLightningHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadLocationHandle", FALSE))
	{
		GAME_LoadLocationHandleorg = (GAME_LoadLocationHandle) ((DWORD) GameDll + 0x3CAD30);
		MH_CreateHook(GAME_LoadLocationHandleorg, &GAME_LoadLocationHandlemy, reinterpret_cast<void**>(&GAME_LoadLocationHandleold));
		MH_EnableHook(GAME_LoadLocationHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadMultiboardHandle", FALSE))
	{
		GAME_LoadMultiboardHandleorg = (GAME_LoadMultiboardHandle) ((DWORD) GameDll + 0x3CEB80);
		MH_CreateHook(GAME_LoadMultiboardHandleorg, &GAME_LoadMultiboardHandlemy, reinterpret_cast<void**>(&GAME_LoadMultiboardHandleold));
		MH_EnableHook(GAME_LoadMultiboardHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadMultiboardItemHandle", FALSE))
	{
		GAME_LoadMultiboardItemHandleorg = (GAME_LoadMultiboardItemHandle) ((DWORD) GameDll + 0x3CEBA0);
		MH_CreateHook(GAME_LoadMultiboardItemHandleorg, &GAME_LoadMultiboardItemHandlemy, reinterpret_cast<void**>(&GAME_LoadMultiboardItemHandleold));
		MH_EnableHook(GAME_LoadMultiboardItemHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadPlayerHandle", FALSE))
	{
		GAME_LoadPlayerHandleorg = (GAME_LoadPlayerHandle) ((DWORD) GameDll + 0x3CAB90);
		MH_CreateHook(GAME_LoadPlayerHandleorg, &GAME_LoadPlayerHandlemy, reinterpret_cast<void**>(&GAME_LoadPlayerHandleold));
		MH_EnableHook(GAME_LoadPlayerHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadQuestHandle", FALSE))
	{
		GAME_LoadQuestHandleorg = (GAME_LoadQuestHandle) ((DWORD) GameDll + 0x3CEAE0);
		MH_CreateHook(GAME_LoadQuestHandleorg, &GAME_LoadQuestHandlemy, reinterpret_cast<void**>(&GAME_LoadQuestHandleold));
		MH_EnableHook(GAME_LoadQuestHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadQuestItemHandle", FALSE))
	{
		GAME_LoadQuestItemHandleorg = (GAME_LoadQuestItemHandle) ((DWORD) GameDll + 0x3CEB00);
		MH_CreateHook(GAME_LoadQuestItemHandleorg, &GAME_LoadQuestItemHandlemy, reinterpret_cast<void**>(&GAME_LoadQuestItemHandleold));
		MH_EnableHook(GAME_LoadQuestItemHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadReal", FALSE))
	{
		GAME_LoadRealorg = (GAME_LoadReal) ((DWORD) GameDll + 0x3CAAD0);
		MH_CreateHook(GAME_LoadRealorg, &GAME_LoadRealmy, reinterpret_cast<void**>(&GAME_LoadRealold));
		MH_EnableHook(GAME_LoadRealorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadRectHandle", FALSE))
	{
		GAME_LoadRectHandleorg = (GAME_LoadRectHandle) ((DWORD) GameDll + 0x3CAD50);
		MH_CreateHook(GAME_LoadRectHandleorg, &GAME_LoadRectHandlemy, reinterpret_cast<void**>(&GAME_LoadRectHandleold));
		MH_EnableHook(GAME_LoadRectHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadRegionHandle", FALSE))
	{
		GAME_LoadRegionHandleorg = (GAME_LoadRegionHandle) ((DWORD) GameDll + 0x3CAC50);
		MH_CreateHook(GAME_LoadRegionHandleorg, &GAME_LoadRegionHandlemy, reinterpret_cast<void**>(&GAME_LoadRegionHandleold));
		MH_EnableHook(GAME_LoadRegionHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadSoundHandle", FALSE))
	{
		GAME_LoadSoundHandleorg = (GAME_LoadSoundHandle) ((DWORD) GameDll + 0x3CAD90);
		MH_CreateHook(GAME_LoadSoundHandleorg, &GAME_LoadSoundHandlemy, reinterpret_cast<void**>(&GAME_LoadSoundHandleold));
		MH_EnableHook(GAME_LoadSoundHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadStr", FALSE))
	{
		GAME_LoadStrorg = (GAME_LoadStr) ((DWORD) GameDll + 0x3CAB50);
		MH_CreateHook(GAME_LoadStrorg, &GAME_LoadStrmy, reinterpret_cast<void**>(&GAME_LoadStrold));
		MH_EnableHook(GAME_LoadStrorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadTextTagHandle", FALSE))
	{
		GAME_LoadTextTagHandleorg = (GAME_LoadTextTagHandle) ((DWORD) GameDll + 0x3CAE50);
		MH_CreateHook(GAME_LoadTextTagHandleorg, &GAME_LoadTextTagHandlemy, reinterpret_cast<void**>(&GAME_LoadTextTagHandleold));
		MH_EnableHook(GAME_LoadTextTagHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadTimerDialogHandle", FALSE))
	{
		GAME_LoadTimerDialogHandleorg = (GAME_LoadTimerDialogHandle) ((DWORD) GameDll + 0x3CEB40);
		MH_CreateHook(GAME_LoadTimerDialogHandleorg, &GAME_LoadTimerDialogHandlemy, reinterpret_cast<void**>(&GAME_LoadTimerDialogHandleold));
		MH_EnableHook(GAME_LoadTimerDialogHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadTimerHandle", FALSE))
	{
		GAME_LoadTimerHandleorg = (GAME_LoadTimerHandle) ((DWORD) GameDll + 0x3CAC30);
		MH_CreateHook(GAME_LoadTimerHandleorg, &GAME_LoadTimerHandlemy, reinterpret_cast<void**>(&GAME_LoadTimerHandleold));
		MH_EnableHook(GAME_LoadTimerHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadTrackableHandle", FALSE))
	{
		GAME_LoadTrackableHandleorg = (GAME_LoadTrackableHandle) ((DWORD) GameDll + 0x3CEBC0);
		MH_CreateHook(GAME_LoadTrackableHandleorg, &GAME_LoadTrackableHandlemy, reinterpret_cast<void**>(&GAME_LoadTrackableHandleold));
		MH_EnableHook(GAME_LoadTrackableHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadTriggerActionHandle", FALSE))
	{
		GAME_LoadTriggerActionHandleorg = (GAME_LoadTriggerActionHandle) ((DWORD) GameDll + 0x3CACB0);
		MH_CreateHook(GAME_LoadTriggerActionHandleorg, &GAME_LoadTriggerActionHandlemy, reinterpret_cast<void**>(&GAME_LoadTriggerActionHandleold));
		MH_EnableHook(GAME_LoadTriggerActionHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadTriggerConditionHandle", FALSE))
	{
		GAME_LoadTriggerConditionHandleorg = (GAME_LoadTriggerConditionHandle) ((DWORD) GameDll + 0x3CAC90);
		MH_CreateHook(GAME_LoadTriggerConditionHandleorg, &GAME_LoadTriggerConditionHandlemy, reinterpret_cast<void**>(&GAME_LoadTriggerConditionHandleold));
		MH_EnableHook(GAME_LoadTriggerConditionHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadTriggerEventHandle", FALSE))
	{
		GAME_LoadTriggerEventHandleorg = (GAME_LoadTriggerEventHandle) ((DWORD) GameDll + 0x3CACD0);
		MH_CreateHook(GAME_LoadTriggerEventHandleorg, &GAME_LoadTriggerEventHandlemy, reinterpret_cast<void**>(&GAME_LoadTriggerEventHandleold));
		MH_EnableHook(GAME_LoadTriggerEventHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadTriggerHandle", FALSE))
	{
		GAME_LoadTriggerHandleorg = (GAME_LoadTriggerHandle) ((DWORD) GameDll + 0x3CAC70);
		MH_CreateHook(GAME_LoadTriggerHandleorg, &GAME_LoadTriggerHandlemy, reinterpret_cast<void**>(&GAME_LoadTriggerHandleold));
		MH_EnableHook(GAME_LoadTriggerHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadUbersplatHandle", FALSE))
	{
		GAME_LoadUbersplatHandleorg = (GAME_LoadUbersplatHandle) ((DWORD) GameDll + 0x3CAEB0);
		MH_CreateHook(GAME_LoadUbersplatHandleorg, &GAME_LoadUbersplatHandlemy, reinterpret_cast<void**>(&GAME_LoadUbersplatHandleold));
		MH_EnableHook(GAME_LoadUbersplatHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadUnitHandle", FALSE))
	{
		GAME_LoadUnitHandleorg = (GAME_LoadUnitHandle) ((DWORD) GameDll + 0x3CAC10);
		MH_CreateHook(GAME_LoadUnitHandleorg, &GAME_LoadUnitHandlemy, reinterpret_cast<void**>(&GAME_LoadUnitHandleold));
		MH_EnableHook(GAME_LoadUnitHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadUnitPoolHandle", FALSE))
	{
		GAME_LoadUnitPoolHandleorg = (GAME_LoadUnitPoolHandle) ((DWORD) GameDll + 0x3CEAA0);
		MH_CreateHook(GAME_LoadUnitPoolHandleorg, &GAME_LoadUnitPoolHandlemy, reinterpret_cast<void**>(&GAME_LoadUnitPoolHandleold));
		MH_EnableHook(GAME_LoadUnitPoolHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadWidgetHandle", FALSE))
	{
		GAME_LoadWidgetHandleorg = (GAME_LoadWidgetHandle) ((DWORD) GameDll + 0x3CABB0);
		MH_CreateHook(GAME_LoadWidgetHandleorg, &GAME_LoadWidgetHandlemy, reinterpret_cast<void**>(&GAME_LoadWidgetHandleold));
		MH_EnableHook(GAME_LoadWidgetHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_LoadZepWave", FALSE))
	{
		GAME_LoadZepWaveorg = (GAME_LoadZepWave) ((DWORD) GameDll + 0x2DDC50);
		MH_CreateHook(GAME_LoadZepWaveorg, &GAME_LoadZepWavemy, reinterpret_cast<void**>(&GAME_LoadZepWaveold));
		MH_EnableHook(GAME_LoadZepWaveorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Location", FALSE))
	{
		GAME_Locationorg = (GAME_Location) ((DWORD) GameDll + 0x3D03B0);
		MH_CreateHook(GAME_Locationorg, &GAME_Locationmy, reinterpret_cast<void**>(&GAME_Locationold));
		MH_EnableHook(GAME_Locationorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MeleeDifficulty", FALSE))
	{
		GAME_MeleeDifficultyorg = (GAME_MeleeDifficulty) ((DWORD) GameDll + 0x2E0500);
		MH_CreateHook(GAME_MeleeDifficultyorg, &GAME_MeleeDifficultymy, reinterpret_cast<void**>(&GAME_MeleeDifficultyold));
		MH_EnableHook(GAME_MeleeDifficultyorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MergeUnits", FALSE))
	{
		GAME_MergeUnitsorg = (GAME_MergeUnits) ((DWORD) GameDll + 0x2DD320);
		MH_CreateHook(GAME_MergeUnitsorg, &GAME_MergeUnitsmy, reinterpret_cast<void**>(&GAME_MergeUnitsold));
		MH_EnableHook(GAME_MergeUnitsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MoveLightning", FALSE))
	{
		GAME_MoveLightningorg = (GAME_MoveLightning) ((DWORD) GameDll + 0x3BCDA0);
		MH_CreateHook(GAME_MoveLightningorg, &GAME_MoveLightningmy, reinterpret_cast<void**>(&GAME_MoveLightningold));
		MH_EnableHook(GAME_MoveLightningorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MoveLightningEx", FALSE))
	{
		GAME_MoveLightningExorg = (GAME_MoveLightningEx) ((DWORD) GameDll + 0x3BCCC0);
		MH_CreateHook(GAME_MoveLightningExorg, &GAME_MoveLightningExmy, reinterpret_cast<void**>(&GAME_MoveLightningExold));
		MH_EnableHook(GAME_MoveLightningExorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MoveLocation", FALSE))
	{
		GAME_MoveLocationorg = (GAME_MoveLocation) ((DWORD) GameDll + 0x3C0DF0);
		MH_CreateHook(GAME_MoveLocationorg, &GAME_MoveLocationmy, reinterpret_cast<void**>(&GAME_MoveLocationold));
		MH_EnableHook(GAME_MoveLocationorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MoveRectTo", FALSE))
	{
		GAME_MoveRectToorg = (GAME_MoveRectTo) ((DWORD) GameDll + 0x3C19C0);
		MH_CreateHook(GAME_MoveRectToorg, &GAME_MoveRectTomy, reinterpret_cast<void**>(&GAME_MoveRectToold));
		MH_EnableHook(GAME_MoveRectToorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MoveRectToLoc", FALSE))
	{
		GAME_MoveRectToLocorg = (GAME_MoveRectToLoc) ((DWORD) GameDll + 0x3C19F0);
		MH_CreateHook(GAME_MoveRectToLocorg, &GAME_MoveRectToLocmy, reinterpret_cast<void**>(&GAME_MoveRectToLocold));
		MH_EnableHook(GAME_MoveRectToLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardClear", FALSE))
	{
		GAME_MultiboardClearorg = (GAME_MultiboardClear) ((DWORD) GameDll + 0x3CC6F0);
		MH_CreateHook(GAME_MultiboardClearorg, &GAME_MultiboardClearmy, reinterpret_cast<void**>(&GAME_MultiboardClearold));
		MH_EnableHook(GAME_MultiboardClearorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardDisplay", FALSE))
	{
		GAME_MultiboardDisplayorg = (GAME_MultiboardDisplay) ((DWORD) GameDll + 0x3CC670);
		MH_CreateHook(GAME_MultiboardDisplayorg, &GAME_MultiboardDisplaymy, reinterpret_cast<void**>(&GAME_MultiboardDisplayold));
		MH_EnableHook(GAME_MultiboardDisplayorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardGetColumnCount", FALSE))
	{
		GAME_MultiboardGetColumnCountorg = (GAME_MultiboardGetColumnCount) ((DWORD) GameDll + 0x3CC7D0);
		MH_CreateHook(GAME_MultiboardGetColumnCountorg, &GAME_MultiboardGetColumnCountmy, reinterpret_cast<void**>(&GAME_MultiboardGetColumnCountold));
		MH_EnableHook(GAME_MultiboardGetColumnCountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardGetItem", FALSE))
	{
		GAME_MultiboardGetItemorg = (GAME_MultiboardGetItem) ((DWORD) GameDll + 0x3D37B0);
		MH_CreateHook(GAME_MultiboardGetItemorg, &GAME_MultiboardGetItemmy, reinterpret_cast<void**>(&GAME_MultiboardGetItemold));
		MH_EnableHook(GAME_MultiboardGetItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardGetRowCount", FALSE))
	{
		GAME_MultiboardGetRowCountorg = (GAME_MultiboardGetRowCount) ((DWORD) GameDll + 0x3CC7B0);
		MH_CreateHook(GAME_MultiboardGetRowCountorg, &GAME_MultiboardGetRowCountmy, reinterpret_cast<void**>(&GAME_MultiboardGetRowCountold));
		MH_EnableHook(GAME_MultiboardGetRowCountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardGetTitleText", FALSE))
	{
		GAME_MultiboardGetTitleTextorg = (GAME_MultiboardGetTitleText) ((DWORD) GameDll + 0x3CC750);
		MH_CreateHook(GAME_MultiboardGetTitleTextorg, &GAME_MultiboardGetTitleTextmy, reinterpret_cast<void**>(&GAME_MultiboardGetTitleTextold));
		MH_EnableHook(GAME_MultiboardGetTitleTextorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardMinimize", FALSE))
	{
		GAME_MultiboardMinimizeorg = (GAME_MultiboardMinimize) ((DWORD) GameDll + 0x3CC6B0);
		MH_CreateHook(GAME_MultiboardMinimizeorg, &GAME_MultiboardMinimizemy, reinterpret_cast<void**>(&GAME_MultiboardMinimizeold));
		MH_EnableHook(GAME_MultiboardMinimizeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardReleaseItem", FALSE))
	{
		GAME_MultiboardReleaseItemorg = (GAME_MultiboardReleaseItem) ((DWORD) GameDll + 0x3CC950);
		MH_CreateHook(GAME_MultiboardReleaseItemorg, &GAME_MultiboardReleaseItemmy, reinterpret_cast<void**>(&GAME_MultiboardReleaseItemold));
		MH_EnableHook(GAME_MultiboardReleaseItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardSetColumnCount", FALSE))
	{
		GAME_MultiboardSetColumnCountorg = (GAME_MultiboardSetColumnCount) ((DWORD) GameDll + 0x3CC7F0);
		MH_CreateHook(GAME_MultiboardSetColumnCountorg, &GAME_MultiboardSetColumnCountmy, reinterpret_cast<void**>(&GAME_MultiboardSetColumnCountold));
		MH_EnableHook(GAME_MultiboardSetColumnCountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardSetItemIcon", FALSE))
	{
		GAME_MultiboardSetItemIconorg = (GAME_MultiboardSetItemIcon) ((DWORD) GameDll + 0x3CCA20);
		MH_CreateHook(GAME_MultiboardSetItemIconorg, &GAME_MultiboardSetItemIconmy, reinterpret_cast<void**>(&GAME_MultiboardSetItemIconold));
		MH_EnableHook(GAME_MultiboardSetItemIconorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardSetItemStyle", FALSE))
	{
		GAME_MultiboardSetItemStyleorg = (GAME_MultiboardSetItemStyle) ((DWORD) GameDll + 0x3CC970);
		MH_CreateHook(GAME_MultiboardSetItemStyleorg, &GAME_MultiboardSetItemStylemy, reinterpret_cast<void**>(&GAME_MultiboardSetItemStyleold));
		MH_EnableHook(GAME_MultiboardSetItemStyleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardSetItemValue", FALSE))
	{
		GAME_MultiboardSetItemValueorg = (GAME_MultiboardSetItemValue) ((DWORD) GameDll + 0x3CC990);
		MH_CreateHook(GAME_MultiboardSetItemValueorg, &GAME_MultiboardSetItemValuemy, reinterpret_cast<void**>(&GAME_MultiboardSetItemValueold));
		MH_EnableHook(GAME_MultiboardSetItemValueorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardSetItemValueColor", FALSE))
	{
		GAME_MultiboardSetItemValueColororg = (GAME_MultiboardSetItemValueColor) ((DWORD) GameDll + 0x3CC9C0);
		MH_CreateHook(GAME_MultiboardSetItemValueColororg, &GAME_MultiboardSetItemValueColormy, reinterpret_cast<void**>(&GAME_MultiboardSetItemValueColorold));
		MH_EnableHook(GAME_MultiboardSetItemValueColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardSetItemWidth", FALSE))
	{
		GAME_MultiboardSetItemWidthorg = (GAME_MultiboardSetItemWidth) ((DWORD) GameDll + 0x3CCA00);
		MH_CreateHook(GAME_MultiboardSetItemWidthorg, &GAME_MultiboardSetItemWidthmy, reinterpret_cast<void**>(&GAME_MultiboardSetItemWidthold));
		MH_EnableHook(GAME_MultiboardSetItemWidthorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardSetItemsIcon", FALSE))
	{
		GAME_MultiboardSetItemsIconorg = (GAME_MultiboardSetItemsIcon) ((DWORD) GameDll + 0x3CC920);
		MH_CreateHook(GAME_MultiboardSetItemsIconorg, &GAME_MultiboardSetItemsIconmy, reinterpret_cast<void**>(&GAME_MultiboardSetItemsIconold));
		MH_EnableHook(GAME_MultiboardSetItemsIconorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardSetItemsStyle", FALSE))
	{
		GAME_MultiboardSetItemsStyleorg = (GAME_MultiboardSetItemsStyle) ((DWORD) GameDll + 0x3CC830);
		MH_CreateHook(GAME_MultiboardSetItemsStyleorg, &GAME_MultiboardSetItemsStylemy, reinterpret_cast<void**>(&GAME_MultiboardSetItemsStyleold));
		MH_EnableHook(GAME_MultiboardSetItemsStyleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardSetItemsValue", FALSE))
	{
		GAME_MultiboardSetItemsValueorg = (GAME_MultiboardSetItemsValue) ((DWORD) GameDll + 0x3CC870);
		MH_CreateHook(GAME_MultiboardSetItemsValueorg, &GAME_MultiboardSetItemsValuemy, reinterpret_cast<void**>(&GAME_MultiboardSetItemsValueold));
		MH_EnableHook(GAME_MultiboardSetItemsValueorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardSetItemsValueColor", FALSE))
	{
		GAME_MultiboardSetItemsValueColororg = (GAME_MultiboardSetItemsValueColor) ((DWORD) GameDll + 0x3CC8A0);
		MH_CreateHook(GAME_MultiboardSetItemsValueColororg, &GAME_MultiboardSetItemsValueColormy, reinterpret_cast<void**>(&GAME_MultiboardSetItemsValueColorold));
		MH_EnableHook(GAME_MultiboardSetItemsValueColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardSetItemsWidth", FALSE))
	{
		GAME_MultiboardSetItemsWidthorg = (GAME_MultiboardSetItemsWidth) ((DWORD) GameDll + 0x3CC8F0);
		MH_CreateHook(GAME_MultiboardSetItemsWidthorg, &GAME_MultiboardSetItemsWidthmy, reinterpret_cast<void**>(&GAME_MultiboardSetItemsWidthold));
		MH_EnableHook(GAME_MultiboardSetItemsWidthorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardSetRowCount", FALSE))
	{
		GAME_MultiboardSetRowCountorg = (GAME_MultiboardSetRowCount) ((DWORD) GameDll + 0x3CC810);
		MH_CreateHook(GAME_MultiboardSetRowCountorg, &GAME_MultiboardSetRowCountmy, reinterpret_cast<void**>(&GAME_MultiboardSetRowCountold));
		MH_EnableHook(GAME_MultiboardSetRowCountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardSetTitleText", FALSE))
	{
		GAME_MultiboardSetTitleTextorg = (GAME_MultiboardSetTitleText) ((DWORD) GameDll + 0x3CC720);
		MH_CreateHook(GAME_MultiboardSetTitleTextorg, &GAME_MultiboardSetTitleTextmy, reinterpret_cast<void**>(&GAME_MultiboardSetTitleTextold));
		MH_EnableHook(GAME_MultiboardSetTitleTextorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardSetTitleTextColor", FALSE))
	{
		GAME_MultiboardSetTitleTextColororg = (GAME_MultiboardSetTitleTextColor) ((DWORD) GameDll + 0x3CC770);
		MH_CreateHook(GAME_MultiboardSetTitleTextColororg, &GAME_MultiboardSetTitleTextColormy, reinterpret_cast<void**>(&GAME_MultiboardSetTitleTextColorold));
		MH_EnableHook(GAME_MultiboardSetTitleTextColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_MultiboardSuppressDisplay", FALSE))
	{
		GAME_MultiboardSuppressDisplayorg = (GAME_MultiboardSuppressDisplay) ((DWORD) GameDll + 0x3B3C00);
		MH_CreateHook(GAME_MultiboardSuppressDisplayorg, &GAME_MultiboardSuppressDisplaymy, reinterpret_cast<void**>(&GAME_MultiboardSuppressDisplayold));
		MH_EnableHook(GAME_MultiboardSuppressDisplayorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_NewSoundEnvironment", FALSE))
	{
		GAME_NewSoundEnvironmentorg = (GAME_NewSoundEnvironment) ((DWORD) GameDll + 0x3B3E60);
		MH_CreateHook(GAME_NewSoundEnvironmentorg, &GAME_NewSoundEnvironmentmy, reinterpret_cast<void**>(&GAME_NewSoundEnvironmentold));
		MH_EnableHook(GAME_NewSoundEnvironmentorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Not", FALSE))
	{
		GAME_Notorg = (GAME_Not) ((DWORD) GameDll + 0x3D0830);
		MH_CreateHook(GAME_Notorg, &GAME_Notmy, reinterpret_cast<void**>(&GAME_Notold));
		MH_EnableHook(GAME_Notorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Or", FALSE))
	{
		GAME_Ororg = (GAME_Or) ((DWORD) GameDll + 0x3D0710);
		MH_CreateHook(GAME_Ororg, &GAME_Ormy, reinterpret_cast<void**>(&GAME_Orold));
		MH_EnableHook(GAME_Ororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_OrderId", FALSE))
	{
		GAME_OrderIdorg = (GAME_OrderId) ((DWORD) GameDll + 0x3BB590);
		MH_CreateHook(GAME_OrderIdorg, &GAME_OrderIdmy, reinterpret_cast<void**>(&GAME_OrderIdold));
		MH_EnableHook(GAME_OrderIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_OrderId2String", FALSE))
	{
		GAME_OrderId2Stringorg = (GAME_OrderId2String) ((DWORD) GameDll + 0x3BB5C0);
		MH_CreateHook(GAME_OrderId2Stringorg, &GAME_OrderId2Stringmy, reinterpret_cast<void**>(&GAME_OrderId2Stringold));
		MH_EnableHook(GAME_OrderId2Stringorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PanCameraTo", FALSE))
	{
		GAME_PanCameraToorg = (GAME_PanCameraTo) ((DWORD) GameDll + 0x3B4700);
		MH_CreateHook(GAME_PanCameraToorg, &GAME_PanCameraTomy, reinterpret_cast<void**>(&GAME_PanCameraToold));
		MH_EnableHook(GAME_PanCameraToorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PanCameraToTimed", FALSE))
	{
		GAME_PanCameraToTimedorg = (GAME_PanCameraToTimed) ((DWORD) GameDll + 0x3B4740);
		MH_CreateHook(GAME_PanCameraToTimedorg, &GAME_PanCameraToTimedmy, reinterpret_cast<void**>(&GAME_PanCameraToTimedold));
		MH_EnableHook(GAME_PanCameraToTimedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PanCameraToTimedWithZ", FALSE))
	{
		GAME_PanCameraToTimedWithZorg = (GAME_PanCameraToTimedWithZ) ((DWORD) GameDll + 0x3B47D0);
		MH_CreateHook(GAME_PanCameraToTimedWithZorg, &GAME_PanCameraToTimedWithZmy, reinterpret_cast<void**>(&GAME_PanCameraToTimedWithZold));
		MH_EnableHook(GAME_PanCameraToTimedWithZorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PanCameraToWithZ", FALSE))
	{
		GAME_PanCameraToWithZorg = (GAME_PanCameraToWithZ) ((DWORD) GameDll + 0x3B4790);
		MH_CreateHook(GAME_PanCameraToWithZorg, &GAME_PanCameraToWithZmy, reinterpret_cast<void**>(&GAME_PanCameraToWithZold));
		MH_EnableHook(GAME_PanCameraToWithZorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PauseCompAI", FALSE))
	{
		GAME_PauseCompAIorg = (GAME_PauseCompAI) ((DWORD) GameDll + 0x3CB7C0);
		MH_CreateHook(GAME_PauseCompAIorg, &GAME_PauseCompAImy, reinterpret_cast<void**>(&GAME_PauseCompAIold));
		MH_EnableHook(GAME_PauseCompAIorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PauseGame", FALSE))
	{
		GAME_PauseGameorg = (GAME_PauseGame) ((DWORD) GameDll + 0x3BC4D0);
		MH_CreateHook(GAME_PauseGameorg, &GAME_PauseGamemy, reinterpret_cast<void**>(&GAME_PauseGameold));
		MH_EnableHook(GAME_PauseGameorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PauseTimer", FALSE))
	{
		GAME_PauseTimerorg = (GAME_PauseTimer) ((DWORD) GameDll + 0x3C1400);
		MH_CreateHook(GAME_PauseTimerorg, &GAME_PauseTimermy, reinterpret_cast<void**>(&GAME_PauseTimerold));
		MH_EnableHook(GAME_PauseTimerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PauseUnit", FALSE))
	{
		GAME_PauseUnitorg = (GAME_PauseUnit) ((DWORD) GameDll + 0x3C7340);
		MH_CreateHook(GAME_PauseUnitorg, &GAME_PauseUnitmy, reinterpret_cast<void**>(&GAME_PauseUnitold));
		MH_EnableHook(GAME_PauseUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PingMinimap", FALSE))
	{
		GAME_PingMinimaporg = (GAME_PingMinimap) ((DWORD) GameDll + 0x3B4650);
		MH_CreateHook(GAME_PingMinimaporg, &GAME_PingMinimapmy, reinterpret_cast<void**>(&GAME_PingMinimapold));
		MH_EnableHook(GAME_PingMinimaporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PingMinimapEx", FALSE))
	{
		GAME_PingMinimapExorg = (GAME_PingMinimapEx) ((DWORD) GameDll + 0x3B8660);
		MH_CreateHook(GAME_PingMinimapExorg, &GAME_PingMinimapExmy, reinterpret_cast<void**>(&GAME_PingMinimapExold));
		MH_EnableHook(GAME_PingMinimapExorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PlaceRandomItem", FALSE))
	{
		GAME_PlaceRandomItemorg = (GAME_PlaceRandomItem) ((DWORD) GameDll + 0x3CB700);
		MH_CreateHook(GAME_PlaceRandomItemorg, &GAME_PlaceRandomItemmy, reinterpret_cast<void**>(&GAME_PlaceRandomItemold));
		MH_EnableHook(GAME_PlaceRandomItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PlaceRandomUnit", FALSE))
	{
		GAME_PlaceRandomUnitorg = (GAME_PlaceRandomUnit) ((DWORD) GameDll + 0x3CB620);
		MH_CreateHook(GAME_PlaceRandomUnitorg, &GAME_PlaceRandomUnitmy, reinterpret_cast<void**>(&GAME_PlaceRandomUnitold));
		MH_EnableHook(GAME_PlaceRandomUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PlayCinematic", FALSE))
	{
		GAME_PlayCinematicorg = (GAME_PlayCinematic) ((DWORD) GameDll + 0x3BC520);
		MH_CreateHook(GAME_PlayCinematicorg, &GAME_PlayCinematicmy, reinterpret_cast<void**>(&GAME_PlayCinematicold));
		MH_EnableHook(GAME_PlayCinematicorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PlayModelCinematic", FALSE))
	{
		GAME_PlayModelCinematicorg = (GAME_PlayModelCinematic) ((DWORD) GameDll + 0x3BC500);
		MH_CreateHook(GAME_PlayModelCinematicorg, &GAME_PlayModelCinematicmy, reinterpret_cast<void**>(&GAME_PlayModelCinematicold));
		MH_EnableHook(GAME_PlayModelCinematicorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PlayMusic", FALSE))
	{
		GAME_PlayMusicorg = (GAME_PlayMusic) ((DWORD) GameDll + 0x3B3D30);
		MH_CreateHook(GAME_PlayMusicorg, &GAME_PlayMusicmy, reinterpret_cast<void**>(&GAME_PlayMusicold));
		MH_EnableHook(GAME_PlayMusicorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PlayMusicEx", FALSE))
	{
		GAME_PlayMusicExorg = (GAME_PlayMusicEx) ((DWORD) GameDll + 0x3B3D50);
		MH_CreateHook(GAME_PlayMusicExorg, &GAME_PlayMusicExmy, reinterpret_cast<void**>(&GAME_PlayMusicExold));
		MH_EnableHook(GAME_PlayMusicExorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PlayThematicMusic", FALSE))
	{
		GAME_PlayThematicMusicorg = (GAME_PlayThematicMusic) ((DWORD) GameDll + 0x3B3DA0);
		MH_CreateHook(GAME_PlayThematicMusicorg, &GAME_PlayThematicMusicmy, reinterpret_cast<void**>(&GAME_PlayThematicMusicold));
		MH_EnableHook(GAME_PlayThematicMusicorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PlayThematicMusicEx", FALSE))
	{
		GAME_PlayThematicMusicExorg = (GAME_PlayThematicMusicEx) ((DWORD) GameDll + 0x3B3DC0);
		MH_CreateHook(GAME_PlayThematicMusicExorg, &GAME_PlayThematicMusicExmy, reinterpret_cast<void**>(&GAME_PlayThematicMusicExold));
		MH_EnableHook(GAME_PlayThematicMusicExorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Player", FALSE))
	{
		GAME_Playerorg = (GAME_Player) ((DWORD) GameDll + 0x3BBB30);
		MH_CreateHook(GAME_Playerorg, &GAME_Playermy, reinterpret_cast<void**>(&GAME_Playerold));
		MH_EnableHook(GAME_Playerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PlayerGetLeaderboard", FALSE))
	{
		GAME_PlayerGetLeaderboardorg = (GAME_PlayerGetLeaderboard) ((DWORD) GameDll + 0x3CC380);
		MH_CreateHook(GAME_PlayerGetLeaderboardorg, &GAME_PlayerGetLeaderboardmy, reinterpret_cast<void**>(&GAME_PlayerGetLeaderboardold));
		MH_EnableHook(GAME_PlayerGetLeaderboardorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PlayerSetLeaderboard", FALSE))
	{
		GAME_PlayerSetLeaderboardorg = (GAME_PlayerSetLeaderboard) ((DWORD) GameDll + 0x3CC340);
		MH_CreateHook(GAME_PlayerSetLeaderboardorg, &GAME_PlayerSetLeaderboardmy, reinterpret_cast<void**>(&GAME_PlayerSetLeaderboardold));
		MH_EnableHook(GAME_PlayerSetLeaderboardorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PopLastCommand", FALSE))
	{
		GAME_PopLastCommandorg = (GAME_PopLastCommand) ((DWORD) GameDll + 0x2E04D0);
		MH_CreateHook(GAME_PopLastCommandorg, &GAME_PopLastCommandmy, reinterpret_cast<void**>(&GAME_PopLastCommandold));
		MH_EnableHook(GAME_PopLastCommandorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Pow", FALSE))
	{
		GAME_Poworg = (GAME_Pow) ((DWORD) GameDll + 0x3B2C00);
		MH_CreateHook(GAME_Poworg, &GAME_Powmy, reinterpret_cast<void**>(&GAME_Powold));
		MH_EnableHook(GAME_Poworg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Preload", FALSE))
	{
		GAME_Preloadorg = (GAME_Preload) ((DWORD) GameDll + 0x3B5170);
		MH_CreateHook(GAME_Preloadorg, &GAME_Preloadmy, reinterpret_cast<void**>(&GAME_Preloadold));
		MH_EnableHook(GAME_Preloadorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PreloadEnd", FALSE))
	{
		GAME_PreloadEndorg = (GAME_PreloadEnd) ((DWORD) GameDll + 0x3B5190);
		MH_CreateHook(GAME_PreloadEndorg, &GAME_PreloadEndmy, reinterpret_cast<void**>(&GAME_PreloadEndold));
		MH_EnableHook(GAME_PreloadEndorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PreloadEndEx", FALSE))
	{
		GAME_PreloadEndExorg = (GAME_PreloadEndEx) ((DWORD) GameDll + 0x3B5220);
		MH_CreateHook(GAME_PreloadEndExorg, &GAME_PreloadEndExmy, reinterpret_cast<void**>(&GAME_PreloadEndExold));
		MH_EnableHook(GAME_PreloadEndExorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PreloadGenClear", FALSE))
	{
		GAME_PreloadGenClearorg = (GAME_PreloadGenClear) ((DWORD) GameDll + 0x3B52B0);
		MH_CreateHook(GAME_PreloadGenClearorg, &GAME_PreloadGenClearmy, reinterpret_cast<void**>(&GAME_PreloadGenClearold));
		MH_EnableHook(GAME_PreloadGenClearorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PreloadGenEnd", FALSE))
	{
		GAME_PreloadGenEndorg = (GAME_PreloadGenEnd) ((DWORD) GameDll + 0x3B52D0);
		MH_CreateHook(GAME_PreloadGenEndorg, &GAME_PreloadGenEndmy, reinterpret_cast<void**>(&GAME_PreloadGenEndold));
		MH_EnableHook(GAME_PreloadGenEndorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PreloadGenStart", FALSE))
	{
		GAME_PreloadGenStartorg = (GAME_PreloadGenStart) ((DWORD) GameDll + 0x3B5290);
		MH_CreateHook(GAME_PreloadGenStartorg, &GAME_PreloadGenStartmy, reinterpret_cast<void**>(&GAME_PreloadGenStartold));
		MH_EnableHook(GAME_PreloadGenStartorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PreloadRefresh", FALSE))
	{
		GAME_PreloadRefreshorg = (GAME_PreloadRefresh) ((DWORD) GameDll + 0x3B5210);
		MH_CreateHook(GAME_PreloadRefreshorg, &GAME_PreloadRefreshmy, reinterpret_cast<void**>(&GAME_PreloadRefreshold));
		MH_EnableHook(GAME_PreloadRefreshorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PreloadStart", FALSE))
	{
		GAME_PreloadStartorg = (GAME_PreloadStart) ((DWORD) GameDll + 0x3B51F0);
		MH_CreateHook(GAME_PreloadStartorg, &GAME_PreloadStartmy, reinterpret_cast<void**>(&GAME_PreloadStartold));
		MH_EnableHook(GAME_PreloadStartorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Preloader", FALSE))
	{
		GAME_Preloaderorg = (GAME_Preloader) ((DWORD) GameDll + 0x3B5310);
		MH_CreateHook(GAME_Preloaderorg, &GAME_Preloadermy, reinterpret_cast<void**>(&GAME_Preloaderold));
		MH_EnableHook(GAME_Preloaderorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_PurchaseZeppelin", FALSE))
	{
		GAME_PurchaseZeppelinorg = (GAME_PurchaseZeppelin) ((DWORD) GameDll + 0x2DD410);
		MH_CreateHook(GAME_PurchaseZeppelinorg, &GAME_PurchaseZeppelinmy, reinterpret_cast<void**>(&GAME_PurchaseZeppelinold));
		MH_EnableHook(GAME_PurchaseZeppelinorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_QuestCreateItem", FALSE))
	{
		GAME_QuestCreateItemorg = (GAME_QuestCreateItem) ((DWORD) GameDll + 0x3D3380);
		MH_CreateHook(GAME_QuestCreateItemorg, &GAME_QuestCreateItemmy, reinterpret_cast<void**>(&GAME_QuestCreateItemold));
		MH_EnableHook(GAME_QuestCreateItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_QuestItemSetCompleted", FALSE))
	{
		GAME_QuestItemSetCompletedorg = (GAME_QuestItemSetCompleted) ((DWORD) GameDll + 0x3CBD70);
		MH_CreateHook(GAME_QuestItemSetCompletedorg, &GAME_QuestItemSetCompletedmy, reinterpret_cast<void**>(&GAME_QuestItemSetCompletedold));
		MH_EnableHook(GAME_QuestItemSetCompletedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_QuestItemSetDescription", FALSE))
	{
		GAME_QuestItemSetDescriptionorg = (GAME_QuestItemSetDescription) ((DWORD) GameDll + 0x3CBD40);
		MH_CreateHook(GAME_QuestItemSetDescriptionorg, &GAME_QuestItemSetDescriptionmy, reinterpret_cast<void**>(&GAME_QuestItemSetDescriptionold));
		MH_EnableHook(GAME_QuestItemSetDescriptionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_QuestSetCompleted", FALSE))
	{
		GAME_QuestSetCompletedorg = (GAME_QuestSetCompleted) ((DWORD) GameDll + 0x3CBC20);
		MH_CreateHook(GAME_QuestSetCompletedorg, &GAME_QuestSetCompletedmy, reinterpret_cast<void**>(&GAME_QuestSetCompletedold));
		MH_EnableHook(GAME_QuestSetCompletedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_QuestSetDescription", FALSE))
	{
		GAME_QuestSetDescriptionorg = (GAME_QuestSetDescription) ((DWORD) GameDll + 0x3CBBA0);
		MH_CreateHook(GAME_QuestSetDescriptionorg, &GAME_QuestSetDescriptionmy, reinterpret_cast<void**>(&GAME_QuestSetDescriptionold));
		MH_EnableHook(GAME_QuestSetDescriptionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_QuestSetDiscovered", FALSE))
	{
		GAME_QuestSetDiscoveredorg = (GAME_QuestSetDiscovered) ((DWORD) GameDll + 0x3CBC60);
		MH_CreateHook(GAME_QuestSetDiscoveredorg, &GAME_QuestSetDiscoveredmy, reinterpret_cast<void**>(&GAME_QuestSetDiscoveredold));
		MH_EnableHook(GAME_QuestSetDiscoveredorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_QuestSetEnabled", FALSE))
	{
		GAME_QuestSetEnabledorg = (GAME_QuestSetEnabled) ((DWORD) GameDll + 0x3CBC80);
		MH_CreateHook(GAME_QuestSetEnabledorg, &GAME_QuestSetEnabledmy, reinterpret_cast<void**>(&GAME_QuestSetEnabledold));
		MH_EnableHook(GAME_QuestSetEnabledorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_QuestSetFailed", FALSE))
	{
		GAME_QuestSetFailedorg = (GAME_QuestSetFailed) ((DWORD) GameDll + 0x3CBC40);
		MH_CreateHook(GAME_QuestSetFailedorg, &GAME_QuestSetFailedmy, reinterpret_cast<void**>(&GAME_QuestSetFailedold));
		MH_EnableHook(GAME_QuestSetFailedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_QuestSetIconPath", FALSE))
	{
		GAME_QuestSetIconPathorg = (GAME_QuestSetIconPath) ((DWORD) GameDll + 0x3CBBD0);
		MH_CreateHook(GAME_QuestSetIconPathorg, &GAME_QuestSetIconPathmy, reinterpret_cast<void**>(&GAME_QuestSetIconPathold));
		MH_EnableHook(GAME_QuestSetIconPathorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_QuestSetRequired", FALSE))
	{
		GAME_QuestSetRequiredorg = (GAME_QuestSetRequired) ((DWORD) GameDll + 0x3CBC00);
		MH_CreateHook(GAME_QuestSetRequiredorg, &GAME_QuestSetRequiredmy, reinterpret_cast<void**>(&GAME_QuestSetRequiredold));
		MH_EnableHook(GAME_QuestSetRequiredorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_QuestSetTitle", FALSE))
	{
		GAME_QuestSetTitleorg = (GAME_QuestSetTitle) ((DWORD) GameDll + 0x3CBB70);
		MH_CreateHook(GAME_QuestSetTitleorg, &GAME_QuestSetTitlemy, reinterpret_cast<void**>(&GAME_QuestSetTitleold));
		MH_EnableHook(GAME_QuestSetTitleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_QueueDestructableAnimation", FALSE))
	{
		GAME_QueueDestructableAnimationorg = (GAME_QueueDestructableAnimation) ((DWORD) GameDll + 0x3C4A00);
		MH_CreateHook(GAME_QueueDestructableAnimationorg, &GAME_QueueDestructableAnimationmy, reinterpret_cast<void**>(&GAME_QueueDestructableAnimationold));
		MH_EnableHook(GAME_QueueDestructableAnimationorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_QueueUnitAnimation", FALSE))
	{
		GAME_QueueUnitAnimationorg = (GAME_QueueUnitAnimation) ((DWORD) GameDll + 0x3C6180);
		MH_CreateHook(GAME_QueueUnitAnimationorg, &GAME_QueueUnitAnimationmy, reinterpret_cast<void**>(&GAME_QueueUnitAnimationold));
		MH_EnableHook(GAME_QueueUnitAnimationorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_R2I", FALSE))
	{
		GAME_R2Iorg = (GAME_R2I) ((DWORD) GameDll + 0x3B2CE0);
		MH_CreateHook(GAME_R2Iorg, &GAME_R2Imy, reinterpret_cast<void**>(&GAME_R2Iold));
		MH_EnableHook(GAME_R2Iorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_R2S", FALSE))
	{
		GAME_R2Sorg = (GAME_R2S) ((DWORD) GameDll + 0x3BAAF0);
		MH_CreateHook(GAME_R2Sorg, &GAME_R2Smy, reinterpret_cast<void**>(&GAME_R2Sold));
		MH_EnableHook(GAME_R2Sorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_R2SW", FALSE))
	{
		GAME_R2SWorg = (GAME_R2SW) ((DWORD) GameDll + 0x3BAB40);
		MH_CreateHook(GAME_R2SWorg, &GAME_R2SWmy, reinterpret_cast<void**>(&GAME_R2SWold));
		MH_EnableHook(GAME_R2SWorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Rad2Deg", FALSE))
	{
		GAME_Rad2Degorg = (GAME_Rad2Deg) ((DWORD) GameDll + 0x3B29F0);
		MH_CreateHook(GAME_Rad2Degorg, &GAME_Rad2Degmy, reinterpret_cast<void**>(&GAME_Rad2Degold));
		MH_EnableHook(GAME_Rad2Degorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Rect", FALSE))
	{
		GAME_Rectorg = (GAME_Rect) ((DWORD) GameDll + 0x3D0A20);
		MH_CreateHook(GAME_Rectorg, &GAME_Rectmy, reinterpret_cast<void**>(&GAME_Rectold));
		MH_EnableHook(GAME_Rectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RectFromLoc", FALSE))
	{
		GAME_RectFromLocorg = (GAME_RectFromLoc) ((DWORD) GameDll + 0x3D0BD0);
		MH_CreateHook(GAME_RectFromLocorg, &GAME_RectFromLocmy, reinterpret_cast<void**>(&GAME_RectFromLocold));
		MH_EnableHook(GAME_RectFromLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RecycleGuardPosition", FALSE))
	{
		GAME_RecycleGuardPositionorg = (GAME_RecycleGuardPosition) ((DWORD) GameDll + 0x3CB800);
		MH_CreateHook(GAME_RecycleGuardPositionorg, &GAME_RecycleGuardPositionmy, reinterpret_cast<void**>(&GAME_RecycleGuardPositionold));
		MH_EnableHook(GAME_RecycleGuardPositionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RegionAddCell", FALSE))
	{
		GAME_RegionAddCellorg = (GAME_RegionAddCell) ((DWORD) GameDll + 0x3C1580);
		MH_CreateHook(GAME_RegionAddCellorg, &GAME_RegionAddCellmy, reinterpret_cast<void**>(&GAME_RegionAddCellold));
		MH_EnableHook(GAME_RegionAddCellorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RegionAddCellAtLoc", FALSE))
	{
		GAME_RegionAddCellAtLocorg = (GAME_RegionAddCellAtLoc) ((DWORD) GameDll + 0x3C15B0);
		MH_CreateHook(GAME_RegionAddCellAtLocorg, &GAME_RegionAddCellAtLocmy, reinterpret_cast<void**>(&GAME_RegionAddCellAtLocold));
		MH_EnableHook(GAME_RegionAddCellAtLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RegionAddRect", FALSE))
	{
		GAME_RegionAddRectorg = (GAME_RegionAddRect) ((DWORD) GameDll + 0x3C14E0);
		MH_CreateHook(GAME_RegionAddRectorg, &GAME_RegionAddRectmy, reinterpret_cast<void**>(&GAME_RegionAddRectold));
		MH_EnableHook(GAME_RegionAddRectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RegionClearCell", FALSE))
	{
		GAME_RegionClearCellorg = (GAME_RegionClearCell) ((DWORD) GameDll + 0x3C15F0);
		MH_CreateHook(GAME_RegionClearCellorg, &GAME_RegionClearCellmy, reinterpret_cast<void**>(&GAME_RegionClearCellold));
		MH_EnableHook(GAME_RegionClearCellorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RegionClearCellAtLoc", FALSE))
	{
		GAME_RegionClearCellAtLocorg = (GAME_RegionClearCellAtLoc) ((DWORD) GameDll + 0x3C1620);
		MH_CreateHook(GAME_RegionClearCellAtLocorg, &GAME_RegionClearCellAtLocmy, reinterpret_cast<void**>(&GAME_RegionClearCellAtLocold));
		MH_EnableHook(GAME_RegionClearCellAtLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RegionClearRect", FALSE))
	{
		GAME_RegionClearRectorg = (GAME_RegionClearRect) ((DWORD) GameDll + 0x3C1530);
		MH_CreateHook(GAME_RegionClearRectorg, &GAME_RegionClearRectmy, reinterpret_cast<void**>(&GAME_RegionClearRectold));
		MH_EnableHook(GAME_RegionClearRectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RegisterStackedSound", FALSE))
	{
		GAME_RegisterStackedSoundorg = (GAME_RegisterStackedSound) ((DWORD) GameDll + 0x3CCF80);
		MH_CreateHook(GAME_RegisterStackedSoundorg, &GAME_RegisterStackedSoundmy, reinterpret_cast<void**>(&GAME_RegisterStackedSoundold));
		MH_EnableHook(GAME_RegisterStackedSoundorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ReloadGame", FALSE))
	{
		GAME_ReloadGameorg = (GAME_ReloadGame) ((DWORD) GameDll + 0x3BBBE0);
		MH_CreateHook(GAME_ReloadGameorg, &GAME_ReloadGamemy, reinterpret_cast<void**>(&GAME_ReloadGameold));
		MH_EnableHook(GAME_ReloadGameorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ReloadGameCachesFromDisk", FALSE))
	{
		GAME_ReloadGameCachesFromDiskorg = (GAME_ReloadGameCachesFromDisk) ((DWORD) GameDll + 0x3BC430);
		MH_CreateHook(GAME_ReloadGameCachesFromDiskorg, &GAME_ReloadGameCachesFromDiskmy, reinterpret_cast<void**>(&GAME_ReloadGameCachesFromDiskold));
		MH_EnableHook(GAME_ReloadGameCachesFromDiskorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveAllGuardPositions", FALSE))
	{
		GAME_RemoveAllGuardPositionsorg = (GAME_RemoveAllGuardPositions) ((DWORD) GameDll + 0x3CB840);
		MH_CreateHook(GAME_RemoveAllGuardPositionsorg, &GAME_RemoveAllGuardPositionsmy, reinterpret_cast<void**>(&GAME_RemoveAllGuardPositionsold));
		MH_EnableHook(GAME_RemoveAllGuardPositionsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveDestructable", FALSE))
	{
		GAME_RemoveDestructableorg = (GAME_RemoveDestructable) ((DWORD) GameDll + 0x3C4730);
		MH_CreateHook(GAME_RemoveDestructableorg, &GAME_RemoveDestructablemy, reinterpret_cast<void**>(&GAME_RemoveDestructableold));
		MH_EnableHook(GAME_RemoveDestructableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveGuardPosition", FALSE))
	{
		GAME_RemoveGuardPositionorg = (GAME_RemoveGuardPosition) ((DWORD) GameDll + 0x3CB820);
		MH_CreateHook(GAME_RemoveGuardPositionorg, &GAME_RemoveGuardPositionmy, reinterpret_cast<void**>(&GAME_RemoveGuardPositionold));
		MH_EnableHook(GAME_RemoveGuardPositionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveInjuries", FALSE))
	{
		GAME_RemoveInjuriesorg = (GAME_RemoveInjuries) ((DWORD) GameDll + 0x2DDDA0);
		MH_CreateHook(GAME_RemoveInjuriesorg, &GAME_RemoveInjuriesmy, reinterpret_cast<void**>(&GAME_RemoveInjuriesold));
		MH_EnableHook(GAME_RemoveInjuriesorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveItem", FALSE))
	{
		GAME_RemoveItemorg = (GAME_RemoveItem) ((DWORD) GameDll + 0x3C4C30);
		MH_CreateHook(GAME_RemoveItemorg, &GAME_RemoveItemmy, reinterpret_cast<void**>(&GAME_RemoveItemold));
		MH_EnableHook(GAME_RemoveItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveItemFromAllStock", FALSE))
	{
		GAME_RemoveItemFromAllStockorg = (GAME_RemoveItemFromAllStock) ((DWORD) GameDll + 0x3B32B0);
		MH_CreateHook(GAME_RemoveItemFromAllStockorg, &GAME_RemoveItemFromAllStockmy, reinterpret_cast<void**>(&GAME_RemoveItemFromAllStockold));
		MH_EnableHook(GAME_RemoveItemFromAllStockorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveItemFromStock", FALSE))
	{
		GAME_RemoveItemFromStockorg = (GAME_RemoveItemFromStock) ((DWORD) GameDll + 0x3C93F0);
		MH_CreateHook(GAME_RemoveItemFromStockorg, &GAME_RemoveItemFromStockmy, reinterpret_cast<void**>(&GAME_RemoveItemFromStockold));
		MH_EnableHook(GAME_RemoveItemFromStockorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveLocation", FALSE))
	{
		GAME_RemoveLocationorg = (GAME_RemoveLocation) ((DWORD) GameDll + 0x3C0DD0);
		MH_CreateHook(GAME_RemoveLocationorg, &GAME_RemoveLocationmy, reinterpret_cast<void**>(&GAME_RemoveLocationold));
		MH_EnableHook(GAME_RemoveLocationorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemovePlayer", FALSE))
	{
		GAME_RemovePlayerorg = (GAME_RemovePlayer) ((DWORD) GameDll + 0x3C9DC0);
		MH_CreateHook(GAME_RemovePlayerorg, &GAME_RemovePlayermy, reinterpret_cast<void**>(&GAME_RemovePlayerold));
		MH_EnableHook(GAME_RemovePlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveRect", FALSE))
	{
		GAME_RemoveRectorg = (GAME_RemoveRect) ((DWORD) GameDll + 0x3C16F0);
		MH_CreateHook(GAME_RemoveRectorg, &GAME_RemoveRectmy, reinterpret_cast<void**>(&GAME_RemoveRectold));
		MH_EnableHook(GAME_RemoveRectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveRegion", FALSE))
	{
		GAME_RemoveRegionorg = (GAME_RemoveRegion) ((DWORD) GameDll + 0x3C14C0);
		MH_CreateHook(GAME_RemoveRegionorg, &GAME_RemoveRegionmy, reinterpret_cast<void**>(&GAME_RemoveRegionold));
		MH_EnableHook(GAME_RemoveRegionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveSaveDirectory", FALSE))
	{
		GAME_RemoveSaveDirectoryorg = (GAME_RemoveSaveDirectory) ((DWORD) GameDll + 0x3BC070);
		MH_CreateHook(GAME_RemoveSaveDirectoryorg, &GAME_RemoveSaveDirectorymy, reinterpret_cast<void**>(&GAME_RemoveSaveDirectoryold));
		MH_EnableHook(GAME_RemoveSaveDirectoryorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveSavedBOOLean", FALSE))
	{
		GAME_RemoveSavedBOOLeanorg = (GAME_RemoveSavedBOOLean) ((DWORD) GameDll + 0x3CB490);
		MH_CreateHook(GAME_RemoveSavedBOOLeanorg, &GAME_RemoveSavedBOOLeanmy, reinterpret_cast<void**>(&GAME_RemoveSavedBOOLeanold));
		MH_EnableHook(GAME_RemoveSavedBOOLeanorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveSavedHandle", FALSE))
	{
		GAME_RemoveSavedHandleorg = (GAME_RemoveSavedHandle) ((DWORD) GameDll + 0x3CB510);
		MH_CreateHook(GAME_RemoveSavedHandleorg, &GAME_RemoveSavedHandlemy, reinterpret_cast<void**>(&GAME_RemoveSavedHandleold));
		MH_EnableHook(GAME_RemoveSavedHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveSavedInteger", FALSE))
	{
		GAME_RemoveSavedIntegerorg = (GAME_RemoveSavedInteger) ((DWORD) GameDll + 0x3CB410);
		MH_CreateHook(GAME_RemoveSavedIntegerorg, &GAME_RemoveSavedIntegermy, reinterpret_cast<void**>(&GAME_RemoveSavedIntegerold));
		MH_EnableHook(GAME_RemoveSavedIntegerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveSavedReal", FALSE))
	{
		GAME_RemoveSavedRealorg = (GAME_RemoveSavedReal) ((DWORD) GameDll + 0x3CB450);
		MH_CreateHook(GAME_RemoveSavedRealorg, &GAME_RemoveSavedRealmy, reinterpret_cast<void**>(&GAME_RemoveSavedRealold));
		MH_EnableHook(GAME_RemoveSavedRealorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveSavedString", FALSE))
	{
		GAME_RemoveSavedStringorg = (GAME_RemoveSavedString) ((DWORD) GameDll + 0x3CB4D0);
		MH_CreateHook(GAME_RemoveSavedStringorg, &GAME_RemoveSavedStringmy, reinterpret_cast<void**>(&GAME_RemoveSavedStringold));
		MH_EnableHook(GAME_RemoveSavedStringorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveSiege", FALSE))
	{
		GAME_RemoveSiegeorg = (GAME_RemoveSiege) ((DWORD) GameDll + 0x2DDE00);
		MH_CreateHook(GAME_RemoveSiegeorg, &GAME_RemoveSiegemy, reinterpret_cast<void**>(&GAME_RemoveSiegeold));
		MH_EnableHook(GAME_RemoveSiegeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveUnit", FALSE))
	{
		GAME_RemoveUnitorg = (GAME_RemoveUnit) ((DWORD) GameDll + 0x3C8060);
		MH_CreateHook(GAME_RemoveUnitorg, &GAME_RemoveUnitmy, reinterpret_cast<void**>(&GAME_RemoveUnitold));
		MH_EnableHook(GAME_RemoveUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveUnitFromAllStock", FALSE))
	{
		GAME_RemoveUnitFromAllStockorg = (GAME_RemoveUnitFromAllStock) ((DWORD) GameDll + 0x3B32C0);
		MH_CreateHook(GAME_RemoveUnitFromAllStockorg, &GAME_RemoveUnitFromAllStockmy, reinterpret_cast<void**>(&GAME_RemoveUnitFromAllStockold));
		MH_EnableHook(GAME_RemoveUnitFromAllStockorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveUnitFromStock", FALSE))
	{
		GAME_RemoveUnitFromStockorg = (GAME_RemoveUnitFromStock) ((DWORD) GameDll + 0x3C9430);
		MH_CreateHook(GAME_RemoveUnitFromStockorg, &GAME_RemoveUnitFromStockmy, reinterpret_cast<void**>(&GAME_RemoveUnitFromStockold));
		MH_EnableHook(GAME_RemoveUnitFromStockorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RemoveWeatherEffect", FALSE))
	{
		GAME_RemoveWeatherEffectorg = (GAME_RemoveWeatherEffect) ((DWORD) GameDll + 0x3B3E70);
		MH_CreateHook(GAME_RemoveWeatherEffectorg, &GAME_RemoveWeatherEffectmy, reinterpret_cast<void**>(&GAME_RemoveWeatherEffectold));
		MH_EnableHook(GAME_RemoveWeatherEffectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RenameSaveDirectory", FALSE))
	{
		GAME_RenameSaveDirectoryorg = (GAME_RenameSaveDirectory) ((DWORD) GameDll + 0x3BBFB0);
		MH_CreateHook(GAME_RenameSaveDirectoryorg, &GAME_RenameSaveDirectorymy, reinterpret_cast<void**>(&GAME_RenameSaveDirectoryold));
		MH_EnableHook(GAME_RenameSaveDirectoryorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ResetCaptainLocs", FALSE))
	{
		GAME_ResetCaptainLocsorg = (GAME_ResetCaptainLocs) ((DWORD) GameDll + 0x2DD780);
		MH_CreateHook(GAME_ResetCaptainLocsorg, &GAME_ResetCaptainLocsmy, reinterpret_cast<void**>(&GAME_ResetCaptainLocsold));
		MH_EnableHook(GAME_ResetCaptainLocsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ResetTerrainFog", FALSE))
	{
		GAME_ResetTerrainFogorg = (GAME_ResetTerrainFog) ((DWORD) GameDll + 0x3B3860);
		MH_CreateHook(GAME_ResetTerrainFogorg, &GAME_ResetTerrainFogmy, reinterpret_cast<void**>(&GAME_ResetTerrainFogold));
		MH_EnableHook(GAME_ResetTerrainFogorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ResetToGameCamera", FALSE))
	{
		GAME_ResetToGameCameraorg = (GAME_ResetToGameCamera) ((DWORD) GameDll + 0x3B46B0);
		MH_CreateHook(GAME_ResetToGameCameraorg, &GAME_ResetToGameCameramy, reinterpret_cast<void**>(&GAME_ResetToGameCameraold));
		MH_EnableHook(GAME_ResetToGameCameraorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ResetTrigger", FALSE))
	{
		GAME_ResetTriggerorg = (GAME_ResetTrigger) ((DWORD) GameDll + 0x3C1C20);
		MH_CreateHook(GAME_ResetTriggerorg, &GAME_ResetTriggermy, reinterpret_cast<void**>(&GAME_ResetTriggerold));
		MH_EnableHook(GAME_ResetTriggerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ResetUbersplat", FALSE))
	{
		GAME_ResetUbersplatorg = (GAME_ResetUbersplat) ((DWORD) GameDll + 0x3B44D0);
		MH_CreateHook(GAME_ResetUbersplatorg, &GAME_ResetUbersplatmy, reinterpret_cast<void**>(&GAME_ResetUbersplatold));
		MH_EnableHook(GAME_ResetUbersplatorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ResetUnitLookAt", FALSE))
	{
		GAME_ResetUnitLookAtorg = (GAME_ResetUnitLookAt) ((DWORD) GameDll + 0x3C65F0);
		MH_CreateHook(GAME_ResetUnitLookAtorg, &GAME_ResetUnitLookAtmy, reinterpret_cast<void**>(&GAME_ResetUnitLookAtold));
		MH_EnableHook(GAME_ResetUnitLookAtorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RestartGame", FALSE))
	{
		GAME_RestartGameorg = (GAME_RestartGame) ((DWORD) GameDll + 0x3BBC00);
		MH_CreateHook(GAME_RestartGameorg, &GAME_RestartGamemy, reinterpret_cast<void**>(&GAME_RestartGameold));
		MH_EnableHook(GAME_RestartGameorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_RestoreUnit", FALSE))
	{
		GAME_RestoreUnitorg = (GAME_RestoreUnit) ((DWORD) GameDll + 0x3CA970);
		MH_CreateHook(GAME_RestoreUnitorg, &GAME_RestoreUnitmy, reinterpret_cast<void**>(&GAME_RestoreUnitold));
		MH_EnableHook(GAME_RestoreUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ResumeMusic", FALSE))
	{
		GAME_ResumeMusicorg = (GAME_ResumeMusic) ((DWORD) GameDll + 0x3B3D90);
		MH_CreateHook(GAME_ResumeMusicorg, &GAME_ResumeMusicmy, reinterpret_cast<void**>(&GAME_ResumeMusicold));
		MH_EnableHook(GAME_ResumeMusicorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ResumeTimer", FALSE))
	{
		GAME_ResumeTimerorg = (GAME_ResumeTimer) ((DWORD) GameDll + 0x3C1420);
		MH_CreateHook(GAME_ResumeTimerorg, &GAME_ResumeTimermy, reinterpret_cast<void**>(&GAME_ResumeTimerold));
		MH_EnableHook(GAME_ResumeTimerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ReturnGuardPosts", FALSE))
	{
		GAME_ReturnGuardPostsorg = (GAME_ReturnGuardPosts) ((DWORD) GameDll + 0x2DCFB0);
		MH_CreateHook(GAME_ReturnGuardPostsorg, &GAME_ReturnGuardPostsmy, reinterpret_cast<void**>(&GAME_ReturnGuardPostsold));
		MH_EnableHook(GAME_ReturnGuardPostsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ReviveHero", FALSE))
	{
		GAME_ReviveHeroorg = (GAME_ReviveHero) ((DWORD) GameDll + 0x3C6AF0);
		MH_CreateHook(GAME_ReviveHeroorg, &GAME_ReviveHeromy, reinterpret_cast<void**>(&GAME_ReviveHeroold));
		MH_EnableHook(GAME_ReviveHeroorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ReviveHeroLoc", FALSE))
	{
		GAME_ReviveHeroLocorg = (GAME_ReviveHeroLoc) ((DWORD) GameDll + 0x3C6B80);
		MH_CreateHook(GAME_ReviveHeroLocorg, &GAME_ReviveHeroLocmy, reinterpret_cast<void**>(&GAME_ReviveHeroLocold));
		MH_EnableHook(GAME_ReviveHeroLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_S2I", FALSE))
	{
		GAME_S2Iorg = (GAME_S2I) ((DWORD) GameDll + 0x3B2D10);
		MH_CreateHook(GAME_S2Iorg, &GAME_S2Imy, reinterpret_cast<void**>(&GAME_S2Iold));
		MH_EnableHook(GAME_S2Iorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_S2R", FALSE))
	{
		GAME_S2Rorg = (GAME_S2R) ((DWORD) GameDll + 0x3B2D50);
		MH_CreateHook(GAME_S2Rorg, &GAME_S2Rmy, reinterpret_cast<void**>(&GAME_S2Rold));
		MH_EnableHook(GAME_S2Rorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveAbilityHandle", FALSE))
	{
		GAME_SaveAbilityHandleorg = (GAME_SaveAbilityHandle) ((DWORD) GameDll + 0x3CE8C0);
		MH_CreateHook(GAME_SaveAbilityHandleorg, &GAME_SaveAbilityHandlemy, reinterpret_cast<void**>(&GAME_SaveAbilityHandleold));
		MH_EnableHook(GAME_SaveAbilityHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveAgentHandle", FALSE))
	{
		GAME_SaveAgentHandleorg = (GAME_SaveAgentHandle) ((DWORD) GameDll + 0x3CEA40);
		MH_CreateHook(GAME_SaveAgentHandleorg, &GAME_SaveAgentHandlemy, reinterpret_cast<void**>(&GAME_SaveAgentHandleold));
		MH_EnableHook(GAME_SaveAgentHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveBOOLean", FALSE))
	{
		GAME_SaveBOOLeanorg = (GAME_SaveBOOLean) ((DWORD) GameDll + 0x3CA280);
		MH_CreateHook(GAME_SaveBOOLeanorg, &GAME_SaveBOOLeanmy, reinterpret_cast<void**>(&GAME_SaveBOOLeanold));
		MH_EnableHook(GAME_SaveBOOLeanorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveBOOLeanExprHandle", FALSE))
	{
		GAME_SaveBOOLeanExprHandleorg = (GAME_SaveBOOLeanExprHandle) ((DWORD) GameDll + 0x3CA4E0);
		MH_CreateHook(GAME_SaveBOOLeanExprHandleorg, &GAME_SaveBOOLeanExprHandlemy, reinterpret_cast<void**>(&GAME_SaveBOOLeanExprHandleold));
		MH_EnableHook(GAME_SaveBOOLeanExprHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveButtonHandle", FALSE))
	{
		GAME_SaveButtonHandleorg = (GAME_SaveButtonHandle) ((DWORD) GameDll + 0x3CA540);
		MH_CreateHook(GAME_SaveButtonHandleorg, &GAME_SaveButtonHandlemy, reinterpret_cast<void**>(&GAME_SaveButtonHandleold));
		MH_EnableHook(GAME_SaveButtonHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveDefeatConditionHandle", FALSE))
	{
		GAME_SaveDefeatConditionHandleorg = (GAME_SaveDefeatConditionHandle) ((DWORD) GameDll + 0x3CE980);
		MH_CreateHook(GAME_SaveDefeatConditionHandleorg, &GAME_SaveDefeatConditionHandlemy, reinterpret_cast<void**>(&GAME_SaveDefeatConditionHandleold));
		MH_EnableHook(GAME_SaveDefeatConditionHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveDestructableHandle", FALSE))
	{
		GAME_SaveDestructableHandleorg = (GAME_SaveDestructableHandle) ((DWORD) GameDll + 0x3CA340);
		MH_CreateHook(GAME_SaveDestructableHandleorg, &GAME_SaveDestructableHandlemy, reinterpret_cast<void**>(&GAME_SaveDestructableHandleold));
		MH_EnableHook(GAME_SaveDestructableHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveDialogHandle", FALSE))
	{
		GAME_SaveDialogHandleorg = (GAME_SaveDialogHandle) ((DWORD) GameDll + 0x3CA520);
		MH_CreateHook(GAME_SaveDialogHandleorg, &GAME_SaveDialogHandlemy, reinterpret_cast<void**>(&GAME_SaveDialogHandleold));
		MH_EnableHook(GAME_SaveDialogHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveEffectHandle", FALSE))
	{
		GAME_SaveEffectHandleorg = (GAME_SaveEffectHandle) ((DWORD) GameDll + 0x3CE8E0);
		MH_CreateHook(GAME_SaveEffectHandleorg, &GAME_SaveEffectHandlemy, reinterpret_cast<void**>(&GAME_SaveEffectHandleold));
		MH_EnableHook(GAME_SaveEffectHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveFogModifierHandle", FALSE))
	{
		GAME_SaveFogModifierHandleorg = (GAME_SaveFogModifierHandle) ((DWORD) GameDll + 0x3CA640);
		MH_CreateHook(GAME_SaveFogModifierHandleorg, &GAME_SaveFogModifierHandlemy, reinterpret_cast<void**>(&GAME_SaveFogModifierHandleold));
		MH_EnableHook(GAME_SaveFogModifierHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveFogStateHandle", FALSE))
	{
		GAME_SaveFogStateHandleorg = (GAME_SaveFogStateHandle) ((DWORD) GameDll + 0x3CA620);
		MH_CreateHook(GAME_SaveFogStateHandleorg, &GAME_SaveFogStateHandlemy, reinterpret_cast<void**>(&GAME_SaveFogStateHandleold));
		MH_EnableHook(GAME_SaveFogStateHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveForceHandle", FALSE))
	{
		GAME_SaveForceHandleorg = (GAME_SaveForceHandle) ((DWORD) GameDll + 0x3CA460);
		MH_CreateHook(GAME_SaveForceHandleorg, &GAME_SaveForceHandlemy, reinterpret_cast<void**>(&GAME_SaveForceHandleold));
		MH_EnableHook(GAME_SaveForceHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveGame", FALSE))
	{
		GAME_SaveGameorg = (GAME_SaveGame) ((DWORD) GameDll + 0x3BBEE0);
		MH_CreateHook(GAME_SaveGameorg, &GAME_SaveGamemy, reinterpret_cast<void**>(&GAME_SaveGameold));
		MH_EnableHook(GAME_SaveGameorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveGameCache", FALSE))
	{
		GAME_SaveGameCacheorg = (GAME_SaveGameCache) ((DWORD) GameDll + 0x3CA080);
		MH_CreateHook(GAME_SaveGameCacheorg, &GAME_SaveGameCachemy, reinterpret_cast<void**>(&GAME_SaveGameCacheold));
		MH_EnableHook(GAME_SaveGameCacheorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveGameExists", FALSE))
	{
		GAME_SaveGameExistsorg = (GAME_SaveGameExists) ((DWORD) GameDll + 0x3BC100);
		MH_CreateHook(GAME_SaveGameExistsorg, &GAME_SaveGameExistsmy, reinterpret_cast<void**>(&GAME_SaveGameExistsold));
		MH_EnableHook(GAME_SaveGameExistsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveGroupHandle", FALSE))
	{
		GAME_SaveGroupHandleorg = (GAME_SaveGroupHandle) ((DWORD) GameDll + 0x3CA480);
		MH_CreateHook(GAME_SaveGroupHandleorg, &GAME_SaveGroupHandlemy, reinterpret_cast<void**>(&GAME_SaveGroupHandleold));
		MH_EnableHook(GAME_SaveGroupHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveHashtableHandle", FALSE))
	{
		GAME_SaveHashtableHandleorg = (GAME_SaveHashtableHandle) ((DWORD) GameDll + 0x3CA660);
		MH_CreateHook(GAME_SaveHashtableHandleorg, &GAME_SaveHashtableHandlemy, reinterpret_cast<void**>(&GAME_SaveHashtableHandleold));
		MH_EnableHook(GAME_SaveHashtableHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveImageHandle", FALSE))
	{
		GAME_SaveImageHandleorg = (GAME_SaveImageHandle) ((DWORD) GameDll + 0x3CA5E0);
		MH_CreateHook(GAME_SaveImageHandleorg, &GAME_SaveImageHandlemy, reinterpret_cast<void**>(&GAME_SaveImageHandleold));
		MH_EnableHook(GAME_SaveImageHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveInteger", FALSE))
	{
		GAME_SaveIntegerorg = (GAME_SaveInteger) ((DWORD) GameDll + 0x3CA200);
		MH_CreateHook(GAME_SaveIntegerorg, &GAME_SaveIntegermy, reinterpret_cast<void**>(&GAME_SaveIntegerold));
		MH_EnableHook(GAME_SaveIntegerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveItemHandle", FALSE))
	{
		GAME_SaveItemHandleorg = (GAME_SaveItemHandle) ((DWORD) GameDll + 0x3CA360);
		MH_CreateHook(GAME_SaveItemHandleorg, &GAME_SaveItemHandlemy, reinterpret_cast<void**>(&GAME_SaveItemHandleold));
		MH_EnableHook(GAME_SaveItemHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveItemPoolHandle", FALSE))
	{
		GAME_SaveItemPoolHandleorg = (GAME_SaveItemPoolHandle) ((DWORD) GameDll + 0x3CE920);
		MH_CreateHook(GAME_SaveItemPoolHandleorg, &GAME_SaveItemPoolHandlemy, reinterpret_cast<void**>(&GAME_SaveItemPoolHandleold));
		MH_EnableHook(GAME_SaveItemPoolHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveLeaderboardHandle", FALSE))
	{
		GAME_SaveLeaderboardHandleorg = (GAME_SaveLeaderboardHandle) ((DWORD) GameDll + 0x3CE9C0);
		MH_CreateHook(GAME_SaveLeaderboardHandleorg, &GAME_SaveLeaderboardHandlemy, reinterpret_cast<void**>(&GAME_SaveLeaderboardHandleold));
		MH_EnableHook(GAME_SaveLeaderboardHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveLightningHandle", FALSE))
	{
		GAME_SaveLightningHandleorg = (GAME_SaveLightningHandle) ((DWORD) GameDll + 0x3CA5C0);
		MH_CreateHook(GAME_SaveLightningHandleorg, &GAME_SaveLightningHandlemy, reinterpret_cast<void**>(&GAME_SaveLightningHandleold));
		MH_EnableHook(GAME_SaveLightningHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveLocationHandle", FALSE))
	{
		GAME_SaveLocationHandleorg = (GAME_SaveLocationHandle) ((DWORD) GameDll + 0x3CA4A0);
		MH_CreateHook(GAME_SaveLocationHandleorg, &GAME_SaveLocationHandlemy, reinterpret_cast<void**>(&GAME_SaveLocationHandleold));
		MH_EnableHook(GAME_SaveLocationHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveMultiboardHandle", FALSE))
	{
		GAME_SaveMultiboardHandleorg = (GAME_SaveMultiboardHandle) ((DWORD) GameDll + 0x3CE9E0);
		MH_CreateHook(GAME_SaveMultiboardHandleorg, &GAME_SaveMultiboardHandlemy, reinterpret_cast<void**>(&GAME_SaveMultiboardHandleold));
		MH_EnableHook(GAME_SaveMultiboardHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveMultiboardItemHandle", FALSE))
	{
		GAME_SaveMultiboardItemHandleorg = (GAME_SaveMultiboardItemHandle) ((DWORD) GameDll + 0x3CEA00);
		MH_CreateHook(GAME_SaveMultiboardItemHandleorg, &GAME_SaveMultiboardItemHandlemy, reinterpret_cast<void**>(&GAME_SaveMultiboardItemHandleold));
		MH_EnableHook(GAME_SaveMultiboardItemHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SavePlayerHandle", FALSE))
	{
		GAME_SavePlayerHandleorg = (GAME_SavePlayerHandle) ((DWORD) GameDll + 0x3CA300);
		MH_CreateHook(GAME_SavePlayerHandleorg, &GAME_SavePlayerHandlemy, reinterpret_cast<void**>(&GAME_SavePlayerHandleold));
		MH_EnableHook(GAME_SavePlayerHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveQuestHandle", FALSE))
	{
		GAME_SaveQuestHandleorg = (GAME_SaveQuestHandle) ((DWORD) GameDll + 0x3CE940);
		MH_CreateHook(GAME_SaveQuestHandleorg, &GAME_SaveQuestHandlemy, reinterpret_cast<void**>(&GAME_SaveQuestHandleold));
		MH_EnableHook(GAME_SaveQuestHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveQuestItemHandle", FALSE))
	{
		GAME_SaveQuestItemHandleorg = (GAME_SaveQuestItemHandle) ((DWORD) GameDll + 0x3CE960);
		MH_CreateHook(GAME_SaveQuestItemHandleorg, &GAME_SaveQuestItemHandlemy, reinterpret_cast<void**>(&GAME_SaveQuestItemHandleold));
		MH_EnableHook(GAME_SaveQuestItemHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveReal", FALSE))
	{
		GAME_SaveRealorg = (GAME_SaveReal) ((DWORD) GameDll + 0x3CA240);
		MH_CreateHook(GAME_SaveRealorg, &GAME_SaveRealmy, reinterpret_cast<void**>(&GAME_SaveRealold));
		MH_EnableHook(GAME_SaveRealorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveRectHandle", FALSE))
	{
		GAME_SaveRectHandleorg = (GAME_SaveRectHandle) ((DWORD) GameDll + 0x3CA4C0);
		MH_CreateHook(GAME_SaveRectHandleorg, &GAME_SaveRectHandlemy, reinterpret_cast<void**>(&GAME_SaveRectHandleold));
		MH_EnableHook(GAME_SaveRectHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveRegionHandle", FALSE))
	{
		GAME_SaveRegionHandleorg = (GAME_SaveRegionHandle) ((DWORD) GameDll + 0x3CA3C0);
		MH_CreateHook(GAME_SaveRegionHandleorg, &GAME_SaveRegionHandlemy, reinterpret_cast<void**>(&GAME_SaveRegionHandleold));
		MH_EnableHook(GAME_SaveRegionHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveSoundHandle", FALSE))
	{
		GAME_SaveSoundHandleorg = (GAME_SaveSoundHandle) ((DWORD) GameDll + 0x3CA500);
		MH_CreateHook(GAME_SaveSoundHandleorg, &GAME_SaveSoundHandlemy, reinterpret_cast<void**>(&GAME_SaveSoundHandleold));
		MH_EnableHook(GAME_SaveSoundHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveStr", FALSE))
	{
		GAME_SaveStrorg = (GAME_SaveStr) ((DWORD) GameDll + 0x3CA2C0);
		MH_CreateHook(GAME_SaveStrorg, &GAME_SaveStrmy, reinterpret_cast<void**>(&GAME_SaveStrold));
		MH_EnableHook(GAME_SaveStrorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveTextTagHandle", FALSE))
	{
		GAME_SaveTextTagHandleorg = (GAME_SaveTextTagHandle) ((DWORD) GameDll + 0x3CA5A0);
		MH_CreateHook(GAME_SaveTextTagHandleorg, &GAME_SaveTextTagHandlemy, reinterpret_cast<void**>(&GAME_SaveTextTagHandleold));
		MH_EnableHook(GAME_SaveTextTagHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveTimerDialogHandle", FALSE))
	{
		GAME_SaveTimerDialogHandleorg = (GAME_SaveTimerDialogHandle) ((DWORD) GameDll + 0x3CE9A0);
		MH_CreateHook(GAME_SaveTimerDialogHandleorg, &GAME_SaveTimerDialogHandlemy, reinterpret_cast<void**>(&GAME_SaveTimerDialogHandleold));
		MH_EnableHook(GAME_SaveTimerDialogHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveTimerHandle", FALSE))
	{
		GAME_SaveTimerHandleorg = (GAME_SaveTimerHandle) ((DWORD) GameDll + 0x3CA3A0);
		MH_CreateHook(GAME_SaveTimerHandleorg, &GAME_SaveTimerHandlemy, reinterpret_cast<void**>(&GAME_SaveTimerHandleold));
		MH_EnableHook(GAME_SaveTimerHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveTrackableHandle", FALSE))
	{
		GAME_SaveTrackableHandleorg = (GAME_SaveTrackableHandle) ((DWORD) GameDll + 0x3CEA20);
		MH_CreateHook(GAME_SaveTrackableHandleorg, &GAME_SaveTrackableHandlemy, reinterpret_cast<void**>(&GAME_SaveTrackableHandleold));
		MH_EnableHook(GAME_SaveTrackableHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveTriggerActionHandle", FALSE))
	{
		GAME_SaveTriggerActionHandleorg = (GAME_SaveTriggerActionHandle) ((DWORD) GameDll + 0x3CA420);
		MH_CreateHook(GAME_SaveTriggerActionHandleorg, &GAME_SaveTriggerActionHandlemy, reinterpret_cast<void**>(&GAME_SaveTriggerActionHandleold));
		MH_EnableHook(GAME_SaveTriggerActionHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveTriggerConditionHandle", FALSE))
	{
		GAME_SaveTriggerConditionHandleorg = (GAME_SaveTriggerConditionHandle) ((DWORD) GameDll + 0x3CA400);
		MH_CreateHook(GAME_SaveTriggerConditionHandleorg, &GAME_SaveTriggerConditionHandlemy, reinterpret_cast<void**>(&GAME_SaveTriggerConditionHandleold));
		MH_EnableHook(GAME_SaveTriggerConditionHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveTriggerEventHandle", FALSE))
	{
		GAME_SaveTriggerEventHandleorg = (GAME_SaveTriggerEventHandle) ((DWORD) GameDll + 0x3CA440);
		MH_CreateHook(GAME_SaveTriggerEventHandleorg, &GAME_SaveTriggerEventHandlemy, reinterpret_cast<void**>(&GAME_SaveTriggerEventHandleold));
		MH_EnableHook(GAME_SaveTriggerEventHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveTriggerHandle", FALSE))
	{
		GAME_SaveTriggerHandleorg = (GAME_SaveTriggerHandle) ((DWORD) GameDll + 0x3CA3E0);
		MH_CreateHook(GAME_SaveTriggerHandleorg, &GAME_SaveTriggerHandlemy, reinterpret_cast<void**>(&GAME_SaveTriggerHandleold));
		MH_EnableHook(GAME_SaveTriggerHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveUbersplatHandle", FALSE))
	{
		GAME_SaveUbersplatHandleorg = (GAME_SaveUbersplatHandle) ((DWORD) GameDll + 0x3CA600);
		MH_CreateHook(GAME_SaveUbersplatHandleorg, &GAME_SaveUbersplatHandlemy, reinterpret_cast<void**>(&GAME_SaveUbersplatHandleold));
		MH_EnableHook(GAME_SaveUbersplatHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveUnitHandle", FALSE))
	{
		GAME_SaveUnitHandleorg = (GAME_SaveUnitHandle) ((DWORD) GameDll + 0x3CA380);
		MH_CreateHook(GAME_SaveUnitHandleorg, &GAME_SaveUnitHandlemy, reinterpret_cast<void**>(&GAME_SaveUnitHandleold));
		MH_EnableHook(GAME_SaveUnitHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveUnitPoolHandle", FALSE))
	{
		GAME_SaveUnitPoolHandleorg = (GAME_SaveUnitPoolHandle) ((DWORD) GameDll + 0x3CE900);
		MH_CreateHook(GAME_SaveUnitPoolHandleorg, &GAME_SaveUnitPoolHandlemy, reinterpret_cast<void**>(&GAME_SaveUnitPoolHandleold));
		MH_EnableHook(GAME_SaveUnitPoolHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SaveWidgetHandle", FALSE))
	{
		GAME_SaveWidgetHandleorg = (GAME_SaveWidgetHandle) ((DWORD) GameDll + 0x3CA320);
		MH_CreateHook(GAME_SaveWidgetHandleorg, &GAME_SaveWidgetHandlemy, reinterpret_cast<void**>(&GAME_SaveWidgetHandleold));
		MH_EnableHook(GAME_SaveWidgetHandleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SelectHeroSkill", FALSE))
	{
		GAME_SelectHeroSkillorg = (GAME_SelectHeroSkill) ((DWORD) GameDll + 0x3C7050);
		MH_CreateHook(GAME_SelectHeroSkillorg, &GAME_SelectHeroSkillmy, reinterpret_cast<void**>(&GAME_SelectHeroSkillold));
		MH_EnableHook(GAME_SelectHeroSkillorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SelectUnit", FALSE))
	{
		GAME_SelectUnitorg = (GAME_SelectUnit) ((DWORD) GameDll + 0x3C7910);
		MH_CreateHook(GAME_SelectUnitorg, &GAME_SelectUnitmy, reinterpret_cast<void**>(&GAME_SelectUnitold));
		MH_EnableHook(GAME_SelectUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetAllItemTypeSlots", FALSE))
	{
		GAME_SetAllItemTypeSlotsorg = (GAME_SetAllItemTypeSlots) ((DWORD) GameDll + 0x3B32D0);
		MH_CreateHook(GAME_SetAllItemTypeSlotsorg, &GAME_SetAllItemTypeSlotsmy, reinterpret_cast<void**>(&GAME_SetAllItemTypeSlotsold));
		MH_EnableHook(GAME_SetAllItemTypeSlotsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetAllUnitTypeSlots", FALSE))
	{
		GAME_SetAllUnitTypeSlotsorg = (GAME_SetAllUnitTypeSlots) ((DWORD) GameDll + 0x3B32E0);
		MH_CreateHook(GAME_SetAllUnitTypeSlotsorg, &GAME_SetAllUnitTypeSlotsmy, reinterpret_cast<void**>(&GAME_SetAllUnitTypeSlotsold));
		MH_EnableHook(GAME_SetAllUnitTypeSlotsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetAllianceTarget", FALSE))
	{
		GAME_SetAllianceTargetorg = (GAME_SetAllianceTarget) ((DWORD) GameDll + 0x2E0630);
		MH_CreateHook(GAME_SetAllianceTargetorg, &GAME_SetAllianceTargetmy, reinterpret_cast<void**>(&GAME_SetAllianceTargetold));
		MH_EnableHook(GAME_SetAllianceTargetorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetAllyColorFilterState", FALSE))
	{
		GAME_SetAllyColorFilterStateorg = (GAME_SetAllyColorFilterState) ((DWORD) GameDll + 0x3B3A70);
		MH_CreateHook(GAME_SetAllyColorFilterStateorg, &GAME_SetAllyColorFilterStatemy, reinterpret_cast<void**>(&GAME_SetAllyColorFilterStateold));
		MH_EnableHook(GAME_SetAllyColorFilterStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetAltMinimapIcon", FALSE))
	{
		GAME_SetAltMinimapIconorg = (GAME_SetAltMinimapIcon) ((DWORD) GameDll + 0x3BC540);
		MH_CreateHook(GAME_SetAltMinimapIconorg, &GAME_SetAltMinimapIconmy, reinterpret_cast<void**>(&GAME_SetAltMinimapIconold));
		MH_EnableHook(GAME_SetAltMinimapIconorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetAmphibious", FALSE))
	{
		GAME_SetAmphibiousorg = (GAME_SetAmphibious) ((DWORD) GameDll + 0x2E0720);
		MH_CreateHook(GAME_SetAmphibiousorg, &GAME_SetAmphibiousmy, reinterpret_cast<void**>(&GAME_SetAmphibiousold));
		MH_EnableHook(GAME_SetAmphibiousorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetBlight", FALSE))
	{
		GAME_SetBlightorg = (GAME_SetBlight) ((DWORD) GameDll + 0x3CD4C0);
		MH_CreateHook(GAME_SetBlightorg, &GAME_SetBlightmy, reinterpret_cast<void**>(&GAME_SetBlightold));
		MH_EnableHook(GAME_SetBlightorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetBlightLoc", FALSE))
	{
		GAME_SetBlightLocorg = (GAME_SetBlightLoc) ((DWORD) GameDll + 0x3CD5D0);
		MH_CreateHook(GAME_SetBlightLocorg, &GAME_SetBlightLocmy, reinterpret_cast<void**>(&GAME_SetBlightLocold));
		MH_EnableHook(GAME_SetBlightLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetBlightPoint", FALSE))
	{
		GAME_SetBlightPointorg = (GAME_SetBlightPoint) ((DWORD) GameDll + 0x3CD580);
		MH_CreateHook(GAME_SetBlightPointorg, &GAME_SetBlightPointmy, reinterpret_cast<void**>(&GAME_SetBlightPointold));
		MH_EnableHook(GAME_SetBlightPointorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetBlightRect", FALSE))
	{
		GAME_SetBlightRectorg = (GAME_SetBlightRect) ((DWORD) GameDll + 0x3CD520);
		MH_CreateHook(GAME_SetBlightRectorg, &GAME_SetBlightRectmy, reinterpret_cast<void**>(&GAME_SetBlightRectold));
		MH_EnableHook(GAME_SetBlightRectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCameraBounds", FALSE))
	{
		GAME_SetCameraBoundsorg = (GAME_SetCameraBounds) ((DWORD) GameDll + 0x3B86F0);
		MH_CreateHook(GAME_SetCameraBoundsorg, &GAME_SetCameraBoundsmy, reinterpret_cast<void**>(&GAME_SetCameraBoundsold));
		MH_EnableHook(GAME_SetCameraBoundsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCameraField", FALSE))
	{
		GAME_SetCameraFieldorg = (GAME_SetCameraField) ((DWORD) GameDll + 0x3B48B0);
		MH_CreateHook(GAME_SetCameraFieldorg, &GAME_SetCameraFieldmy, reinterpret_cast<void**>(&GAME_SetCameraFieldold));
		MH_EnableHook(GAME_SetCameraFieldorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCameraOrientController", FALSE))
	{
		GAME_SetCameraOrientControllerorg = (GAME_SetCameraOrientController) ((DWORD) GameDll + 0x3CD7B0);
		MH_CreateHook(GAME_SetCameraOrientControllerorg, &GAME_SetCameraOrientControllermy, reinterpret_cast<void**>(&GAME_SetCameraOrientControllerold));
		MH_EnableHook(GAME_SetCameraOrientControllerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCameraPosition", FALSE))
	{
		GAME_SetCameraPositionorg = (GAME_SetCameraPosition) ((DWORD) GameDll + 0x3B45D0);
		MH_CreateHook(GAME_SetCameraPositionorg, &GAME_SetCameraPositionmy, reinterpret_cast<void**>(&GAME_SetCameraPositionold));
		MH_EnableHook(GAME_SetCameraPositionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCameraQuickPosition", FALSE))
	{
		GAME_SetCameraQuickPositionorg = (GAME_SetCameraQuickPosition) ((DWORD) GameDll + 0x3B4610);
		MH_CreateHook(GAME_SetCameraQuickPositionorg, &GAME_SetCameraQuickPositionmy, reinterpret_cast<void**>(&GAME_SetCameraQuickPositionold));
		MH_EnableHook(GAME_SetCameraQuickPositionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCameraRotateMode", FALSE))
	{
		GAME_SetCameraRotateModeorg = (GAME_SetCameraRotateMode) ((DWORD) GameDll + 0x3B4850);
		MH_CreateHook(GAME_SetCameraRotateModeorg, &GAME_SetCameraRotateModemy, reinterpret_cast<void**>(&GAME_SetCameraRotateModeold));
		MH_EnableHook(GAME_SetCameraRotateModeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCameraTargetController", FALSE))
	{
		GAME_SetCameraTargetControllerorg = (GAME_SetCameraTargetController) ((DWORD) GameDll + 0x3CD760);
		MH_CreateHook(GAME_SetCameraTargetControllerorg, &GAME_SetCameraTargetControllermy, reinterpret_cast<void**>(&GAME_SetCameraTargetControllerold));
		MH_EnableHook(GAME_SetCameraTargetControllerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCampaignAI", FALSE))
	{
		GAME_SetCampaignAIorg = (GAME_SetCampaignAI) ((DWORD) GameDll + 0x2DDEA0);
		MH_CreateHook(GAME_SetCampaignAIorg, &GAME_SetCampaignAImy, reinterpret_cast<void**>(&GAME_SetCampaignAIold));
		MH_EnableHook(GAME_SetCampaignAIorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCampaignAvailable", FALSE))
	{
		GAME_SetCampaignAvailableorg = (GAME_SetCampaignAvailable) ((DWORD) GameDll + 0x3B3370);
		MH_CreateHook(GAME_SetCampaignAvailableorg, &GAME_SetCampaignAvailablemy, reinterpret_cast<void**>(&GAME_SetCampaignAvailableold));
		MH_EnableHook(GAME_SetCampaignAvailableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCampaignMenuRace", FALSE))
	{
		GAME_SetCampaignMenuRaceorg = (GAME_SetCampaignMenuRace) ((DWORD) GameDll + 0x3BC3D0);
		MH_CreateHook(GAME_SetCampaignMenuRaceorg, &GAME_SetCampaignMenuRacemy, reinterpret_cast<void**>(&GAME_SetCampaignMenuRaceold));
		MH_EnableHook(GAME_SetCampaignMenuRaceorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCampaignMenuRaceEx", FALSE))
	{
		GAME_SetCampaignMenuRaceExorg = (GAME_SetCampaignMenuRaceEx) ((DWORD) GameDll + 0x3BC3B0);
		MH_CreateHook(GAME_SetCampaignMenuRaceExorg, &GAME_SetCampaignMenuRaceExmy, reinterpret_cast<void**>(&GAME_SetCampaignMenuRaceExold));
		MH_EnableHook(GAME_SetCampaignMenuRaceExorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCaptainChanges", FALSE))
	{
		GAME_SetCaptainChangesorg = (GAME_SetCaptainChanges) ((DWORD) GameDll + 0x2E2D20);
		MH_CreateHook(GAME_SetCaptainChangesorg, &GAME_SetCaptainChangesmy, reinterpret_cast<void**>(&GAME_SetCaptainChangesold));
		MH_EnableHook(GAME_SetCaptainChangesorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCaptainHome", FALSE))
	{
		GAME_SetCaptainHomeorg = (GAME_SetCaptainHome) ((DWORD) GameDll + 0x2DD7B0);
		MH_CreateHook(GAME_SetCaptainHomeorg, &GAME_SetCaptainHomemy, reinterpret_cast<void**>(&GAME_SetCaptainHomeold));
		MH_EnableHook(GAME_SetCaptainHomeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCineFilterBlendMode", FALSE))
	{
		GAME_SetCineFilterBlendModeorg = (GAME_SetCineFilterBlendMode) ((DWORD) GameDll + 0x3B4EB0);
		MH_CreateHook(GAME_SetCineFilterBlendModeorg, &GAME_SetCineFilterBlendModemy, reinterpret_cast<void**>(&GAME_SetCineFilterBlendModeold));
		MH_EnableHook(GAME_SetCineFilterBlendModeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCineFilterDuration", FALSE))
	{
		GAME_SetCineFilterDurationorg = (GAME_SetCineFilterDuration) ((DWORD) GameDll + 0x3B5100);
		MH_CreateHook(GAME_SetCineFilterDurationorg, &GAME_SetCineFilterDurationmy, reinterpret_cast<void**>(&GAME_SetCineFilterDurationold));
		MH_EnableHook(GAME_SetCineFilterDurationorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCineFilterEndColor", FALSE))
	{
		GAME_SetCineFilterEndColororg = (GAME_SetCineFilterEndColor) ((DWORD) GameDll + 0x3CECD0);
		MH_CreateHook(GAME_SetCineFilterEndColororg, &GAME_SetCineFilterEndColormy, reinterpret_cast<void**>(&GAME_SetCineFilterEndColorold));
		MH_EnableHook(GAME_SetCineFilterEndColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCineFilterEndUV", FALSE))
	{
		GAME_SetCineFilterEndUVorg = (GAME_SetCineFilterEndUV) ((DWORD) GameDll + 0x3B5020);
		MH_CreateHook(GAME_SetCineFilterEndUVorg, &GAME_SetCineFilterEndUVmy, reinterpret_cast<void**>(&GAME_SetCineFilterEndUVold));
		MH_EnableHook(GAME_SetCineFilterEndUVorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCineFilterStartColor", FALSE))
	{
		GAME_SetCineFilterStartColororg = (GAME_SetCineFilterStartColor) ((DWORD) GameDll + 0x3CEBE0);
		MH_CreateHook(GAME_SetCineFilterStartColororg, &GAME_SetCineFilterStartColormy, reinterpret_cast<void**>(&GAME_SetCineFilterStartColorold));
		MH_EnableHook(GAME_SetCineFilterStartColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCineFilterStartUV", FALSE))
	{
		GAME_SetCineFilterStartUVorg = (GAME_SetCineFilterStartUV) ((DWORD) GameDll + 0x3B4F40);
		MH_CreateHook(GAME_SetCineFilterStartUVorg, &GAME_SetCineFilterStartUVmy, reinterpret_cast<void**>(&GAME_SetCineFilterStartUVold));
		MH_EnableHook(GAME_SetCineFilterStartUVorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCineFilterTexMapFlags", FALSE))
	{
		GAME_SetCineFilterTexMapFlagsorg = (GAME_SetCineFilterTexMapFlags) ((DWORD) GameDll + 0x3B4EF0);
		MH_CreateHook(GAME_SetCineFilterTexMapFlagsorg, &GAME_SetCineFilterTexMapFlagsmy, reinterpret_cast<void**>(&GAME_SetCineFilterTexMapFlagsold));
		MH_EnableHook(GAME_SetCineFilterTexMapFlagsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCineFilterTexture", FALSE))
	{
		GAME_SetCineFilterTextureorg = (GAME_SetCineFilterTexture) ((DWORD) GameDll + 0x3B4E80);
		MH_CreateHook(GAME_SetCineFilterTextureorg, &GAME_SetCineFilterTexturemy, reinterpret_cast<void**>(&GAME_SetCineFilterTextureold));
		MH_EnableHook(GAME_SetCineFilterTextureorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCinematicCamera", FALSE))
	{
		GAME_SetCinematicCameraorg = (GAME_SetCinematicCamera) ((DWORD) GameDll + 0x3B4820);
		MH_CreateHook(GAME_SetCinematicCameraorg, &GAME_SetCinematicCameramy, reinterpret_cast<void**>(&GAME_SetCinematicCameraold));
		MH_EnableHook(GAME_SetCinematicCameraorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCinematicScene", FALSE))
	{
		GAME_SetCinematicSceneorg = (GAME_SetCinematicScene) ((DWORD) GameDll + 0x3BCF80);
		MH_CreateHook(GAME_SetCinematicSceneorg, &GAME_SetCinematicScenemy, reinterpret_cast<void**>(&GAME_SetCinematicSceneold));
		MH_EnableHook(GAME_SetCinematicSceneorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCreatureDensity", FALSE))
	{
		GAME_SetCreatureDensityorg = (GAME_SetCreatureDensity) ((DWORD) GameDll + 0x3BAF50);
		MH_CreateHook(GAME_SetCreatureDensityorg, &GAME_SetCreatureDensitymy, reinterpret_cast<void**>(&GAME_SetCreatureDensityold));
		MH_EnableHook(GAME_SetCreatureDensityorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCreepCampFilterState", FALSE))
	{
		GAME_SetCreepCampFilterStateorg = (GAME_SetCreepCampFilterState) ((DWORD) GameDll + 0x3B3AC0);
		MH_CreateHook(GAME_SetCreepCampFilterStateorg, &GAME_SetCreepCampFilterStatemy, reinterpret_cast<void**>(&GAME_SetCreepCampFilterStateold));
		MH_EnableHook(GAME_SetCreepCampFilterStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetCustomCampaignButtonVisible", FALSE))
	{
		GAME_SetCustomCampaignButtonVisibleorg = (GAME_SetCustomCampaignButtonVisible) ((DWORD) GameDll + 0x3B3510);
		MH_CreateHook(GAME_SetCustomCampaignButtonVisibleorg, &GAME_SetCustomCampaignButtonVisiblemy, reinterpret_cast<void**>(&GAME_SetCustomCampaignButtonVisibleold));
		MH_EnableHook(GAME_SetCustomCampaignButtonVisibleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetDayNightModels", FALSE))
	{
		GAME_SetDayNightModelsorg = (GAME_SetDayNightModels) ((DWORD) GameDll + 0x3B3790);
		MH_CreateHook(GAME_SetDayNightModelsorg, &GAME_SetDayNightModelsmy, reinterpret_cast<void**>(&GAME_SetDayNightModelsold));
		MH_EnableHook(GAME_SetDayNightModelsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetDefaultDifficulty", FALSE))
	{
		GAME_SetDefaultDifficultyorg = (GAME_SetDefaultDifficulty) ((DWORD) GameDll + 0x3B33D0);
		MH_CreateHook(GAME_SetDefaultDifficultyorg, &GAME_SetDefaultDifficultymy, reinterpret_cast<void**>(&GAME_SetDefaultDifficultyold));
		MH_EnableHook(GAME_SetDefaultDifficultyorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetDefendPlayer", FALSE))
	{
		GAME_SetDefendPlayerorg = (GAME_SetDefendPlayer) ((DWORD) GameDll + 0x2E30E0);
		MH_CreateHook(GAME_SetDefendPlayerorg, &GAME_SetDefendPlayermy, reinterpret_cast<void**>(&GAME_SetDefendPlayerold));
		MH_EnableHook(GAME_SetDefendPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetDestructableAnimation", FALSE))
	{
		GAME_SetDestructableAnimationorg = (GAME_SetDestructableAnimation) ((DWORD) GameDll + 0x3C4A20);
		MH_CreateHook(GAME_SetDestructableAnimationorg, &GAME_SetDestructableAnimationmy, reinterpret_cast<void**>(&GAME_SetDestructableAnimationold));
		MH_EnableHook(GAME_SetDestructableAnimationorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetDestructableAnimationSpeed", FALSE))
	{
		GAME_SetDestructableAnimationSpeedorg = (GAME_SetDestructableAnimationSpeed) ((DWORD) GameDll + 0x3C4A40);
		MH_CreateHook(GAME_SetDestructableAnimationSpeedorg, &GAME_SetDestructableAnimationSpeedmy, reinterpret_cast<void**>(&GAME_SetDestructableAnimationSpeedold));
		MH_EnableHook(GAME_SetDestructableAnimationSpeedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetDestructableInvulnerable", FALSE))
	{
		GAME_SetDestructableInvulnerableorg = (GAME_SetDestructableInvulnerable) ((DWORD) GameDll + 0x3C4770);
		MH_CreateHook(GAME_SetDestructableInvulnerableorg, &GAME_SetDestructableInvulnerablemy, reinterpret_cast<void**>(&GAME_SetDestructableInvulnerableold));
		MH_EnableHook(GAME_SetDestructableInvulnerableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetDestructableLife", FALSE))
	{
		GAME_SetDestructableLifeorg = (GAME_SetDestructableLife) ((DWORD) GameDll + 0x3C4850);
		MH_CreateHook(GAME_SetDestructableLifeorg, &GAME_SetDestructableLifemy, reinterpret_cast<void**>(&GAME_SetDestructableLifeold));
		MH_EnableHook(GAME_SetDestructableLifeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetDestructableMaxLife", FALSE))
	{
		GAME_SetDestructableMaxLifeorg = (GAME_SetDestructableMaxLife) ((DWORD) GameDll + 0x3C48D0);
		MH_CreateHook(GAME_SetDestructableMaxLifeorg, &GAME_SetDestructableMaxLifemy, reinterpret_cast<void**>(&GAME_SetDestructableMaxLifeold));
		MH_EnableHook(GAME_SetDestructableMaxLifeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetDestructableOccluderHeight", FALSE))
	{
		GAME_SetDestructableOccluderHeightorg = (GAME_SetDestructableOccluderHeight) ((DWORD) GameDll + 0x3C4BD0);
		MH_CreateHook(GAME_SetDestructableOccluderHeightorg, &GAME_SetDestructableOccluderHeightmy, reinterpret_cast<void**>(&GAME_SetDestructableOccluderHeightold));
		MH_EnableHook(GAME_SetDestructableOccluderHeightorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetDoodadAnimation", FALSE))
	{
		GAME_SetDoodadAnimationorg = (GAME_SetDoodadAnimation) ((DWORD) GameDll + 0x3B4570);
		MH_CreateHook(GAME_SetDoodadAnimationorg, &GAME_SetDoodadAnimationmy, reinterpret_cast<void**>(&GAME_SetDoodadAnimationold));
		MH_EnableHook(GAME_SetDoodadAnimationorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetDoodadAnimationRect", FALSE))
	{
		GAME_SetDoodadAnimationRectorg = (GAME_SetDoodadAnimationRect) ((DWORD) GameDll + 0x3CD6F0);
		MH_CreateHook(GAME_SetDoodadAnimationRectorg, &GAME_SetDoodadAnimationRectmy, reinterpret_cast<void**>(&GAME_SetDoodadAnimationRectold));
		MH_EnableHook(GAME_SetDoodadAnimationRectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetEdCinematicAvailable", FALSE))
	{
		GAME_SetEdCinematicAvailableorg = (GAME_SetEdCinematicAvailable) ((DWORD) GameDll + 0x3B3460);
		MH_CreateHook(GAME_SetEdCinematicAvailableorg, &GAME_SetEdCinematicAvailablemy, reinterpret_cast<void**>(&GAME_SetEdCinematicAvailableold));
		MH_EnableHook(GAME_SetEdCinematicAvailableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetExpansion", FALSE))
	{
		GAME_SetExpansionorg = (GAME_SetExpansion) ((DWORD) GameDll + 0x2E0570);
		MH_CreateHook(GAME_SetExpansionorg, &GAME_SetExpansionmy, reinterpret_cast<void**>(&GAME_SetExpansionold));
		MH_EnableHook(GAME_SetExpansionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetFloatGameState", FALSE))
	{
		GAME_SetFloatGameStateorg = (GAME_SetFloatGameState) ((DWORD) GameDll + 0x3BC2E0);
		MH_CreateHook(GAME_SetFloatGameStateorg, &GAME_SetFloatGameStatemy, reinterpret_cast<void**>(&GAME_SetFloatGameStateold));
		MH_EnableHook(GAME_SetFloatGameStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetFogStateRadius", FALSE))
	{
		GAME_SetFogStateRadiusorg = (GAME_SetFogStateRadius) ((DWORD) GameDll + 0x3C1AB0);
		MH_CreateHook(GAME_SetFogStateRadiusorg, &GAME_SetFogStateRadiusmy, reinterpret_cast<void**>(&GAME_SetFogStateRadiusold));
		MH_EnableHook(GAME_SetFogStateRadiusorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetFogStateRadiusLoc", FALSE))
	{
		GAME_SetFogStateRadiusLocorg = (GAME_SetFogStateRadiusLoc) ((DWORD) GameDll + 0x3C1B20);
		MH_CreateHook(GAME_SetFogStateRadiusLocorg, &GAME_SetFogStateRadiusLocmy, reinterpret_cast<void**>(&GAME_SetFogStateRadiusLocold));
		MH_EnableHook(GAME_SetFogStateRadiusLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetFogStateRect", FALSE))
	{
		GAME_SetFogStateRectorg = (GAME_SetFogStateRect) ((DWORD) GameDll + 0x3C1A30);
		MH_CreateHook(GAME_SetFogStateRectorg, &GAME_SetFogStateRectmy, reinterpret_cast<void**>(&GAME_SetFogStateRectold));
		MH_EnableHook(GAME_SetFogStateRectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetGameDifficulty", FALSE))
	{
		GAME_SetGameDifficultyorg = (GAME_SetGameDifficulty) ((DWORD) GameDll + 0x3BAF10);
		MH_CreateHook(GAME_SetGameDifficultyorg, &GAME_SetGameDifficultymy, reinterpret_cast<void**>(&GAME_SetGameDifficultyold));
		MH_EnableHook(GAME_SetGameDifficultyorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetGamePlacement", FALSE))
	{
		GAME_SetGamePlacementorg = (GAME_SetGamePlacement) ((DWORD) GameDll + 0x3BAEF0);
		MH_CreateHook(GAME_SetGamePlacementorg, &GAME_SetGamePlacementmy, reinterpret_cast<void**>(&GAME_SetGamePlacementold));
		MH_EnableHook(GAME_SetGamePlacementorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetGameSpeed", FALSE))
	{
		GAME_SetGameSpeedorg = (GAME_SetGameSpeed) ((DWORD) GameDll + 0x3BAED0);
		MH_CreateHook(GAME_SetGameSpeedorg, &GAME_SetGameSpeedmy, reinterpret_cast<void**>(&GAME_SetGameSpeedold));
		MH_EnableHook(GAME_SetGameSpeedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetGameTypeSupported", FALSE))
	{
		GAME_SetGameTypeSupportedorg = (GAME_SetGameTypeSupported) ((DWORD) GameDll + 0x3BAE10);
		MH_CreateHook(GAME_SetGameTypeSupportedorg, &GAME_SetGameTypeSupportedmy, reinterpret_cast<void**>(&GAME_SetGameTypeSupportedold));
		MH_EnableHook(GAME_SetGameTypeSupportedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetGroupsFlee", FALSE))
	{
		GAME_SetGroupsFleeorg = (GAME_SetGroupsFlee) ((DWORD) GameDll + 0x2E32A0);
		MH_CreateHook(GAME_SetGroupsFleeorg, &GAME_SetGroupsFleemy, reinterpret_cast<void**>(&GAME_SetGroupsFleeold));
		MH_EnableHook(GAME_SetGroupsFleeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetHeroAgi", FALSE))
	{
		GAME_SetHeroAgiorg = (GAME_SetHeroAgi) ((DWORD) GameDll + 0x3C66A0);
		MH_CreateHook(GAME_SetHeroAgiorg, &GAME_SetHeroAgimy, reinterpret_cast<void**>(&GAME_SetHeroAgiold));
		MH_EnableHook(GAME_SetHeroAgiorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetHeroInt", FALSE))
	{
		GAME_SetHeroIntorg = (GAME_SetHeroInt) ((DWORD) GameDll + 0x3C6710);
		MH_CreateHook(GAME_SetHeroIntorg, &GAME_SetHeroIntmy, reinterpret_cast<void**>(&GAME_SetHeroIntold));
		MH_EnableHook(GAME_SetHeroIntorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetHeroLevel", FALSE))
	{
		GAME_SetHeroLevelorg = (GAME_SetHeroLevel) ((DWORD) GameDll + 0x3C6D70);
		MH_CreateHook(GAME_SetHeroLevelorg, &GAME_SetHeroLevelmy, reinterpret_cast<void**>(&GAME_SetHeroLevelold));
		MH_EnableHook(GAME_SetHeroLevelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetHeroLevels", FALSE))
	{
		GAME_SetHeroLevelsorg = (GAME_SetHeroLevels) ((DWORD) GameDll + 0x2E0B00);
		MH_CreateHook(GAME_SetHeroLevelsorg, &GAME_SetHeroLevelsmy, reinterpret_cast<void**>(&GAME_SetHeroLevelsold));
		MH_EnableHook(GAME_SetHeroLevelsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetHeroStr", FALSE))
	{
		GAME_SetHeroStrorg = (GAME_SetHeroStr) ((DWORD) GameDll + 0x3C6630);
		MH_CreateHook(GAME_SetHeroStrorg, &GAME_SetHeroStrmy, reinterpret_cast<void**>(&GAME_SetHeroStrold));
		MH_EnableHook(GAME_SetHeroStrorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetHeroXP", FALSE))
	{
		GAME_SetHeroXPorg = (GAME_SetHeroXP) ((DWORD) GameDll + 0x3C6A70);
		MH_CreateHook(GAME_SetHeroXPorg, &GAME_SetHeroXPmy, reinterpret_cast<void**>(&GAME_SetHeroXPold));
		MH_EnableHook(GAME_SetHeroXPorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetHeroesBuyItems", FALSE))
	{
		GAME_SetHeroesBuyItemsorg = (GAME_SetHeroesBuyItems) ((DWORD) GameDll + 0x2E3160);
		MH_CreateHook(GAME_SetHeroesBuyItemsorg, &GAME_SetHeroesBuyItemsmy, reinterpret_cast<void**>(&GAME_SetHeroesBuyItemsold));
		MH_EnableHook(GAME_SetHeroesBuyItemsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetHeroesFlee", FALSE))
	{
		GAME_SetHeroesFleeorg = (GAME_SetHeroesFlee) ((DWORD) GameDll + 0x2E3120);
		MH_CreateHook(GAME_SetHeroesFleeorg, &GAME_SetHeroesFleemy, reinterpret_cast<void**>(&GAME_SetHeroesFleeold));
		MH_EnableHook(GAME_SetHeroesFleeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetHeroesTakeItems", FALSE))
	{
		GAME_SetHeroesTakeItemsorg = (GAME_SetHeroesTakeItems) ((DWORD) GameDll + 0x2E3220);
		MH_CreateHook(GAME_SetHeroesTakeItemsorg, &GAME_SetHeroesTakeItemsmy, reinterpret_cast<void**>(&GAME_SetHeroesTakeItemsold));
		MH_EnableHook(GAME_SetHeroesTakeItemsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetIgnoreInjured", FALSE))
	{
		GAME_SetIgnoreInjuredorg = (GAME_SetIgnoreInjured) ((DWORD) GameDll + 0x2E31E0);
		MH_CreateHook(GAME_SetIgnoreInjuredorg, &GAME_SetIgnoreInjuredmy, reinterpret_cast<void**>(&GAME_SetIgnoreInjuredold));
		MH_EnableHook(GAME_SetIgnoreInjuredorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetImageAboveWater", FALSE))
	{
		GAME_SetImageAboveWaterorg = (GAME_SetImageAboveWater) ((DWORD) GameDll + 0x3B4480);
		MH_CreateHook(GAME_SetImageAboveWaterorg, &GAME_SetImageAboveWatermy, reinterpret_cast<void**>(&GAME_SetImageAboveWaterold));
		MH_EnableHook(GAME_SetImageAboveWaterorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetImageColor", FALSE))
	{
		GAME_SetImageColororg = (GAME_SetImageColor) ((DWORD) GameDll + 0x3B85B0);
		MH_CreateHook(GAME_SetImageColororg, &GAME_SetImageColormy, reinterpret_cast<void**>(&GAME_SetImageColorold));
		MH_EnableHook(GAME_SetImageColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetImageConstantHeight", FALSE))
	{
		GAME_SetImageConstantHeightorg = (GAME_SetImageConstantHeight) ((DWORD) GameDll + 0x3B43E0);
		MH_CreateHook(GAME_SetImageConstantHeightorg, &GAME_SetImageConstantHeightmy, reinterpret_cast<void**>(&GAME_SetImageConstantHeightold));
		MH_EnableHook(GAME_SetImageConstantHeightorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetImagePosition", FALSE))
	{
		GAME_SetImagePositionorg = (GAME_SetImagePosition) ((DWORD) GameDll + 0x3B4400);
		MH_CreateHook(GAME_SetImagePositionorg, &GAME_SetImagePositionmy, reinterpret_cast<void**>(&GAME_SetImagePositionold));
		MH_EnableHook(GAME_SetImagePositionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetImageRender", FALSE))
	{
		GAME_SetImageRenderorg = (GAME_SetImageRender) ((DWORD) GameDll + 0x3B4440);
		MH_CreateHook(GAME_SetImageRenderorg, &GAME_SetImageRendermy, reinterpret_cast<void**>(&GAME_SetImageRenderold));
		MH_EnableHook(GAME_SetImageRenderorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetImageRenderAlways", FALSE))
	{
		GAME_SetImageRenderAlwaysorg = (GAME_SetImageRenderAlways) ((DWORD) GameDll + 0x3B4460);
		MH_CreateHook(GAME_SetImageRenderAlwaysorg, &GAME_SetImageRenderAlwaysmy, reinterpret_cast<void**>(&GAME_SetImageRenderAlwaysold));
		MH_EnableHook(GAME_SetImageRenderAlwaysorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetImageType", FALSE))
	{
		GAME_SetImageTypeorg = (GAME_SetImageType) ((DWORD) GameDll + 0x3B44A0);
		MH_CreateHook(GAME_SetImageTypeorg, &GAME_SetImageTypemy, reinterpret_cast<void**>(&GAME_SetImageTypeold));
		MH_EnableHook(GAME_SetImageTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetIntegerGameState", FALSE))
	{
		GAME_SetIntegerGameStateorg = (GAME_SetIntegerGameState) ((DWORD) GameDll + 0x3BC350);
		MH_CreateHook(GAME_SetIntegerGameStateorg, &GAME_SetIntegerGameStatemy, reinterpret_cast<void**>(&GAME_SetIntegerGameStateold));
		MH_EnableHook(GAME_SetIntegerGameStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetIntroShotModel", FALSE))
	{
		GAME_SetIntroShotModelorg = (GAME_SetIntroShotModel) ((DWORD) GameDll + 0x3BC8A0);
		MH_CreateHook(GAME_SetIntroShotModelorg, &GAME_SetIntroShotModelmy, reinterpret_cast<void**>(&GAME_SetIntroShotModelold));
		MH_EnableHook(GAME_SetIntroShotModelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetIntroShotText", FALSE))
	{
		GAME_SetIntroShotTextorg = (GAME_SetIntroShotText) ((DWORD) GameDll + 0x3BC880);
		MH_CreateHook(GAME_SetIntroShotTextorg, &GAME_SetIntroShotTextmy, reinterpret_cast<void**>(&GAME_SetIntroShotTextold));
		MH_EnableHook(GAME_SetIntroShotTextorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetItemCharges", FALSE))
	{
		GAME_SetItemChargesorg = (GAME_SetItemCharges) ((DWORD) GameDll + 0x3C5070);
		MH_CreateHook(GAME_SetItemChargesorg, &GAME_SetItemChargesmy, reinterpret_cast<void**>(&GAME_SetItemChargesold));
		MH_EnableHook(GAME_SetItemChargesorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetItemDropID", FALSE))
	{
		GAME_SetItemDropIDorg = (GAME_SetItemDropID) ((DWORD) GameDll + 0x3C5030);
		MH_CreateHook(GAME_SetItemDropIDorg, &GAME_SetItemDropIDmy, reinterpret_cast<void**>(&GAME_SetItemDropIDold));
		MH_EnableHook(GAME_SetItemDropIDorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetItemDropOnDeath", FALSE))
	{
		GAME_SetItemDropOnDeathorg = (GAME_SetItemDropOnDeath) ((DWORD) GameDll + 0x3C4D00);
		MH_CreateHook(GAME_SetItemDropOnDeathorg, &GAME_SetItemDropOnDeathmy, reinterpret_cast<void**>(&GAME_SetItemDropOnDeathold));
		MH_EnableHook(GAME_SetItemDropOnDeathorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetItemDroppable", FALSE))
	{
		GAME_SetItemDroppableorg = (GAME_SetItemDroppable) ((DWORD) GameDll + 0x3C4D30);
		MH_CreateHook(GAME_SetItemDroppableorg, &GAME_SetItemDroppablemy, reinterpret_cast<void**>(&GAME_SetItemDroppableold));
		MH_EnableHook(GAME_SetItemDroppableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetItemInvulnerable", FALSE))
	{
		GAME_SetItemInvulnerableorg = (GAME_SetItemInvulnerable) ((DWORD) GameDll + 0x3C4EE0);
		MH_CreateHook(GAME_SetItemInvulnerableorg, &GAME_SetItemInvulnerablemy, reinterpret_cast<void**>(&GAME_SetItemInvulnerableold));
		MH_EnableHook(GAME_SetItemInvulnerableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetItemPawnable", FALSE))
	{
		GAME_SetItemPawnableorg = (GAME_SetItemPawnable) ((DWORD) GameDll + 0x3C4D60);
		MH_CreateHook(GAME_SetItemPawnableorg, &GAME_SetItemPawnablemy, reinterpret_cast<void**>(&GAME_SetItemPawnableold));
		MH_EnableHook(GAME_SetItemPawnableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetItemPlayer", FALSE))
	{
		GAME_SetItemPlayerorg = (GAME_SetItemPlayer) ((DWORD) GameDll + 0x3C4EB0);
		MH_CreateHook(GAME_SetItemPlayerorg, &GAME_SetItemPlayermy, reinterpret_cast<void**>(&GAME_SetItemPlayerold));
		MH_EnableHook(GAME_SetItemPlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetItemPosition", FALSE))
	{
		GAME_SetItemPositionorg = (GAME_SetItemPosition) ((DWORD) GameDll + 0x3C4C80);
		MH_CreateHook(GAME_SetItemPositionorg, &GAME_SetItemPositionmy, reinterpret_cast<void**>(&GAME_SetItemPositionold));
		MH_EnableHook(GAME_SetItemPositionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetItemTypeSlots", FALSE))
	{
		GAME_SetItemTypeSlotsorg = (GAME_SetItemTypeSlots) ((DWORD) GameDll + 0x3C9470);
		MH_CreateHook(GAME_SetItemTypeSlotsorg, &GAME_SetItemTypeSlotsmy, reinterpret_cast<void**>(&GAME_SetItemTypeSlotsold));
		MH_EnableHook(GAME_SetItemTypeSlotsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetItemUserData", FALSE))
	{
		GAME_SetItemUserDataorg = (GAME_SetItemUserData) ((DWORD) GameDll + 0x3C50F0);
		MH_CreateHook(GAME_SetItemUserDataorg, &GAME_SetItemUserDatamy, reinterpret_cast<void**>(&GAME_SetItemUserDataold));
		MH_EnableHook(GAME_SetItemUserDataorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetItemVisible", FALSE))
	{
		GAME_SetItemVisibleorg = (GAME_SetItemVisible) ((DWORD) GameDll + 0x3C4F20);
		MH_CreateHook(GAME_SetItemVisibleorg, &GAME_SetItemVisiblemy, reinterpret_cast<void**>(&GAME_SetItemVisibleold));
		MH_EnableHook(GAME_SetItemVisibleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetLightningColor", FALSE))
	{
		GAME_SetLightningColororg = (GAME_SetLightningColor) ((DWORD) GameDll + 0x3B8490);
		MH_CreateHook(GAME_SetLightningColororg, &GAME_SetLightningColormy, reinterpret_cast<void**>(&GAME_SetLightningColorold));
		MH_EnableHook(GAME_SetLightningColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetMapDescription", FALSE))
	{
		GAME_SetMapDescriptionorg = (GAME_SetMapDescription) ((DWORD) GameDll + 0x3BADC0);
		MH_CreateHook(GAME_SetMapDescriptionorg, &GAME_SetMapDescriptionmy, reinterpret_cast<void**>(&GAME_SetMapDescriptionold));
		MH_EnableHook(GAME_SetMapDescriptionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetMapFlag", FALSE))
	{
		GAME_SetMapFlagorg = (GAME_SetMapFlag) ((DWORD) GameDll + 0x3BAE70);
		MH_CreateHook(GAME_SetMapFlagorg, &GAME_SetMapFlagmy, reinterpret_cast<void**>(&GAME_SetMapFlagold));
		MH_EnableHook(GAME_SetMapFlagorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetMapMusic", FALSE))
	{
		GAME_SetMapMusicorg = (GAME_SetMapMusic) ((DWORD) GameDll + 0x3B3CE0);
		MH_CreateHook(GAME_SetMapMusicorg, &GAME_SetMapMusicmy, reinterpret_cast<void**>(&GAME_SetMapMusicold));
		MH_EnableHook(GAME_SetMapMusicorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetMapName", FALSE))
	{
		GAME_SetMapNameorg = (GAME_SetMapName) ((DWORD) GameDll + 0x3BADA0);
		MH_CreateHook(GAME_SetMapNameorg, &GAME_SetMapNamemy, reinterpret_cast<void**>(&GAME_SetMapNameold));
		MH_EnableHook(GAME_SetMapNameorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetMeleeAI", FALSE))
	{
		GAME_SetMeleeAIorg = (GAME_SetMeleeAI) ((DWORD) GameDll + 0x2DDEE0);
		MH_CreateHook(GAME_SetMeleeAIorg, &GAME_SetMeleeAImy, reinterpret_cast<void**>(&GAME_SetMeleeAIold));
		MH_EnableHook(GAME_SetMeleeAIorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetMissionAvailable", FALSE))
	{
		GAME_SetMissionAvailableorg = (GAME_SetMissionAvailable) ((DWORD) GameDll + 0x3B3340);
		MH_CreateHook(GAME_SetMissionAvailableorg, &GAME_SetMissionAvailablemy, reinterpret_cast<void**>(&GAME_SetMissionAvailableold));
		MH_EnableHook(GAME_SetMissionAvailableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetMusicPlayPosition", FALSE))
	{
		GAME_SetMusicPlayPositionorg = (GAME_SetMusicPlayPosition) ((DWORD) GameDll + 0x3B3E00);
		MH_CreateHook(GAME_SetMusicPlayPositionorg, &GAME_SetMusicPlayPositionmy, reinterpret_cast<void**>(&GAME_SetMusicPlayPositionold));
		MH_EnableHook(GAME_SetMusicPlayPositionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetMusicVolume", FALSE))
	{
		GAME_SetMusicVolumeorg = (GAME_SetMusicVolume) ((DWORD) GameDll + 0x3B3DF0);
		MH_CreateHook(GAME_SetMusicVolumeorg, &GAME_SetMusicVolumemy, reinterpret_cast<void**>(&GAME_SetMusicVolumeold));
		MH_EnableHook(GAME_SetMusicVolumeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetNewHeroes", FALSE))
	{
		GAME_SetNewHeroesorg = (GAME_SetNewHeroes) ((DWORD) GameDll + 0x2E3020);
		MH_CreateHook(GAME_SetNewHeroesorg, &GAME_SetNewHeroesmy, reinterpret_cast<void**>(&GAME_SetNewHeroesold));
		MH_EnableHook(GAME_SetNewHeroesorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetOpCinematicAvailable", FALSE))
	{
		GAME_SetOpCinematicAvailableorg = (GAME_SetOpCinematicAvailable) ((DWORD) GameDll + 0x3B3400);
		MH_CreateHook(GAME_SetOpCinematicAvailableorg, &GAME_SetOpCinematicAvailablemy, reinterpret_cast<void**>(&GAME_SetOpCinematicAvailableold));
		MH_EnableHook(GAME_SetOpCinematicAvailableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPeonsRepair", FALSE))
	{
		GAME_SetPeonsRepairorg = (GAME_SetPeonsRepair) ((DWORD) GameDll + 0x2E3060);
		MH_CreateHook(GAME_SetPeonsRepairorg, &GAME_SetPeonsRepairmy, reinterpret_cast<void**>(&GAME_SetPeonsRepairold));
		MH_EnableHook(GAME_SetPeonsRepairorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPlayerAbilityAvailable", FALSE))
	{
		GAME_SetPlayerAbilityAvailableorg = (GAME_SetPlayerAbilityAvailable) ((DWORD) GameDll + 0x3C97D0);
		MH_CreateHook(GAME_SetPlayerAbilityAvailableorg, &GAME_SetPlayerAbilityAvailablemy, reinterpret_cast<void**>(&GAME_SetPlayerAbilityAvailableold));
		MH_EnableHook(GAME_SetPlayerAbilityAvailableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPlayerAlliance", FALSE))
	{
		GAME_SetPlayerAllianceorg = (GAME_SetPlayerAlliance) ((DWORD) GameDll + 0x3C1050);
		MH_CreateHook(GAME_SetPlayerAllianceorg, &GAME_SetPlayerAlliancemy, reinterpret_cast<void**>(&GAME_SetPlayerAllianceold));
		MH_EnableHook(GAME_SetPlayerAllianceorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPlayerColor", FALSE))
	{
		GAME_SetPlayerColororg = (GAME_SetPlayerColor) ((DWORD) GameDll + 0x3C1220);
		MH_CreateHook(GAME_SetPlayerColororg, &GAME_SetPlayerColormy, reinterpret_cast<void**>(&GAME_SetPlayerColorold));
		MH_EnableHook(GAME_SetPlayerColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPlayerController", FALSE))
	{
		GAME_SetPlayerControllerorg = (GAME_SetPlayerController) ((DWORD) GameDll + 0x3C1200);
		MH_CreateHook(GAME_SetPlayerControllerorg, &GAME_SetPlayerControllermy, reinterpret_cast<void**>(&GAME_SetPlayerControllerold));
		MH_EnableHook(GAME_SetPlayerControllerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPlayerHandicap", FALSE))
	{
		GAME_SetPlayerHandicaporg = (GAME_SetPlayerHandicap) ((DWORD) GameDll + 0x3C9E30);
		MH_CreateHook(GAME_SetPlayerHandicaporg, &GAME_SetPlayerHandicapmy, reinterpret_cast<void**>(&GAME_SetPlayerHandicapold));
		MH_EnableHook(GAME_SetPlayerHandicaporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPlayerHandicapXP", FALSE))
	{
		GAME_SetPlayerHandicapXPorg = (GAME_SetPlayerHandicapXP) ((DWORD) GameDll + 0x3C9EE0);
		MH_CreateHook(GAME_SetPlayerHandicapXPorg, &GAME_SetPlayerHandicapXPmy, reinterpret_cast<void**>(&GAME_SetPlayerHandicapXPold));
		MH_EnableHook(GAME_SetPlayerHandicapXPorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPlayerName", FALSE))
	{
		GAME_SetPlayerNameorg = (GAME_SetPlayerName) ((DWORD) GameDll + 0x3C0F10);
		MH_CreateHook(GAME_SetPlayerNameorg, &GAME_SetPlayerNamemy, reinterpret_cast<void**>(&GAME_SetPlayerNameold));
		MH_EnableHook(GAME_SetPlayerNameorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPlayerOnScoreScreen", FALSE))
	{
		GAME_SetPlayerOnScoreScreenorg = (GAME_SetPlayerOnScoreScreen) ((DWORD) GameDll + 0x3C9800);
		MH_CreateHook(GAME_SetPlayerOnScoreScreenorg, &GAME_SetPlayerOnScoreScreenmy, reinterpret_cast<void**>(&GAME_SetPlayerOnScoreScreenold));
		MH_EnableHook(GAME_SetPlayerOnScoreScreenorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPlayerRacePreference", FALSE))
	{
		GAME_SetPlayerRacePreferenceorg = (GAME_SetPlayerRacePreference) ((DWORD) GameDll + 0x3C11A0);
		MH_CreateHook(GAME_SetPlayerRacePreferenceorg, &GAME_SetPlayerRacePreferencemy, reinterpret_cast<void**>(&GAME_SetPlayerRacePreferenceold));
		MH_EnableHook(GAME_SetPlayerRacePreferenceorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPlayerRaceSelectable", FALSE))
	{
		GAME_SetPlayerRaceSelectableorg = (GAME_SetPlayerRaceSelectable) ((DWORD) GameDll + 0x3C11D0);
		MH_CreateHook(GAME_SetPlayerRaceSelectableorg, &GAME_SetPlayerRaceSelectablemy, reinterpret_cast<void**>(&GAME_SetPlayerRaceSelectableold));
		MH_EnableHook(GAME_SetPlayerRaceSelectableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPlayerStartLocation", FALSE))
	{
		GAME_SetPlayerStartLocationorg = (GAME_SetPlayerStartLocation) ((DWORD) GameDll + 0x3C0F80);
		MH_CreateHook(GAME_SetPlayerStartLocationorg, &GAME_SetPlayerStartLocationmy, reinterpret_cast<void**>(&GAME_SetPlayerStartLocationold));
		MH_EnableHook(GAME_SetPlayerStartLocationorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPlayerState", FALSE))
	{
		GAME_SetPlayerStateorg = (GAME_SetPlayerState) ((DWORD) GameDll + 0x3C9AA0);
		MH_CreateHook(GAME_SetPlayerStateorg, &GAME_SetPlayerStatemy, reinterpret_cast<void**>(&GAME_SetPlayerStateold));
		MH_EnableHook(GAME_SetPlayerStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPlayerTaxRate", FALSE))
	{
		GAME_SetPlayerTaxRateorg = (GAME_SetPlayerTaxRate) ((DWORD) GameDll + 0x3C10E0);
		MH_CreateHook(GAME_SetPlayerTaxRateorg, &GAME_SetPlayerTaxRatemy, reinterpret_cast<void**>(&GAME_SetPlayerTaxRateold));
		MH_EnableHook(GAME_SetPlayerTaxRateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPlayerTeam", FALSE))
	{
		GAME_SetPlayerTeamorg = (GAME_SetPlayerTeam) ((DWORD) GameDll + 0x3C0EE0);
		MH_CreateHook(GAME_SetPlayerTeamorg, &GAME_SetPlayerTeammy, reinterpret_cast<void**>(&GAME_SetPlayerTeamold));
		MH_EnableHook(GAME_SetPlayerTeamorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPlayerTechMaxAllowed", FALSE))
	{
		GAME_SetPlayerTechMaxAllowedorg = (GAME_SetPlayerTechMaxAllowed) ((DWORD) GameDll + 0x3C9660);
		MH_CreateHook(GAME_SetPlayerTechMaxAllowedorg, &GAME_SetPlayerTechMaxAllowedmy, reinterpret_cast<void**>(&GAME_SetPlayerTechMaxAllowedold));
		MH_EnableHook(GAME_SetPlayerTechMaxAllowedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPlayerTechResearched", FALSE))
	{
		GAME_SetPlayerTechResearchedorg = (GAME_SetPlayerTechResearched) ((DWORD) GameDll + 0x3C9730);
		MH_CreateHook(GAME_SetPlayerTechResearchedorg, &GAME_SetPlayerTechResearchedmy, reinterpret_cast<void**>(&GAME_SetPlayerTechResearchedold));
		MH_EnableHook(GAME_SetPlayerTechResearchedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPlayerUnitsOwner", FALSE))
	{
		GAME_SetPlayerUnitsOwnerorg = (GAME_SetPlayerUnitsOwner) ((DWORD) GameDll + 0x3C12F0);
		MH_CreateHook(GAME_SetPlayerUnitsOwnerorg, &GAME_SetPlayerUnitsOwnermy, reinterpret_cast<void**>(&GAME_SetPlayerUnitsOwnerold));
		MH_EnableHook(GAME_SetPlayerUnitsOwnerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetPlayers", FALSE))
	{
		GAME_SetPlayersorg = (GAME_SetPlayers) ((DWORD) GameDll + 0x3BADF0);
		MH_CreateHook(GAME_SetPlayersorg, &GAME_SetPlayersmy, reinterpret_cast<void**>(&GAME_SetPlayersold));
		MH_EnableHook(GAME_SetPlayersorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetProduce", FALSE))
	{
		GAME_SetProduceorg = (GAME_SetProduce) ((DWORD) GameDll + 0x2DD450);
		MH_CreateHook(GAME_SetProduceorg, &GAME_SetProducemy, reinterpret_cast<void**>(&GAME_SetProduceold));
		MH_EnableHook(GAME_SetProduceorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetRandomPaths", FALSE))
	{
		GAME_SetRandomPathsorg = (GAME_SetRandomPaths) ((DWORD) GameDll + 0x2E30A0);
		MH_CreateHook(GAME_SetRandomPathsorg, &GAME_SetRandomPathsmy, reinterpret_cast<void**>(&GAME_SetRandomPathsold));
		MH_EnableHook(GAME_SetRandomPathsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetRandomSeed", FALSE))
	{
		GAME_SetRandomSeedorg = (GAME_SetRandomSeed) ((DWORD) GameDll + 0x3B36D0);
		MH_CreateHook(GAME_SetRandomSeedorg, &GAME_SetRandomSeedmy, reinterpret_cast<void**>(&GAME_SetRandomSeedold));
		MH_EnableHook(GAME_SetRandomSeedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetRect", FALSE))
	{
		GAME_SetRectorg = (GAME_SetRect) ((DWORD) GameDll + 0x3C1710);
		MH_CreateHook(GAME_SetRectorg, &GAME_SetRectmy, reinterpret_cast<void**>(&GAME_SetRectold));
		MH_EnableHook(GAME_SetRectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetRectFromLoc", FALSE))
	{
		GAME_SetRectFromLocorg = (GAME_SetRectFromLoc) ((DWORD) GameDll + 0x3C17F0);
		MH_CreateHook(GAME_SetRectFromLocorg, &GAME_SetRectFromLocmy, reinterpret_cast<void**>(&GAME_SetRectFromLocold));
		MH_EnableHook(GAME_SetRectFromLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetReplacementCount", FALSE))
	{
		GAME_SetReplacementCountorg = (GAME_SetReplacementCount) ((DWORD) GameDll + 0x2E0B30);
		MH_CreateHook(GAME_SetReplacementCountorg, &GAME_SetReplacementCountmy, reinterpret_cast<void**>(&GAME_SetReplacementCountold));
		MH_EnableHook(GAME_SetReplacementCountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetReservedLocalHeroButtons", FALSE))
	{
		GAME_SetReservedLocalHeroButtonsorg = (GAME_SetReservedLocalHeroButtons) ((DWORD) GameDll + 0x3B3A30);
		MH_CreateHook(GAME_SetReservedLocalHeroButtonsorg, &GAME_SetReservedLocalHeroButtonsmy, reinterpret_cast<void**>(&GAME_SetReservedLocalHeroButtonsold));
		MH_EnableHook(GAME_SetReservedLocalHeroButtonsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetResourceAmount", FALSE))
	{
		GAME_SetResourceAmountorg = (GAME_SetResourceAmount) ((DWORD) GameDll + 0x3C77F0);
		MH_CreateHook(GAME_SetResourceAmountorg, &GAME_SetResourceAmountmy, reinterpret_cast<void**>(&GAME_SetResourceAmountold));
		MH_EnableHook(GAME_SetResourceAmountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetResourceDensity", FALSE))
	{
		GAME_SetResourceDensityorg = (GAME_SetResourceDensity) ((DWORD) GameDll + 0x3BAF30);
		MH_CreateHook(GAME_SetResourceDensityorg, &GAME_SetResourceDensitymy, reinterpret_cast<void**>(&GAME_SetResourceDensityold));
		MH_EnableHook(GAME_SetResourceDensityorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetSkyModel", FALSE))
	{
		GAME_SetSkyModelorg = (GAME_SetSkyModel) ((DWORD) GameDll + 0x3B37D0);
		MH_CreateHook(GAME_SetSkyModelorg, &GAME_SetSkyModelmy, reinterpret_cast<void**>(&GAME_SetSkyModelold));
		MH_EnableHook(GAME_SetSkyModelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetSlowChopping", FALSE))
	{
		GAME_SetSlowChoppingorg = (GAME_SetSlowChopping) ((DWORD) GameDll + 0x2E32E0);
		MH_CreateHook(GAME_SetSlowChoppingorg, &GAME_SetSlowChoppingmy, reinterpret_cast<void**>(&GAME_SetSlowChoppingold));
		MH_EnableHook(GAME_SetSlowChoppingorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetSmartArtillery", FALSE))
	{
		GAME_SetSmartArtilleryorg = (GAME_SetSmartArtillery) ((DWORD) GameDll + 0x2DDF10);
		MH_CreateHook(GAME_SetSmartArtilleryorg, &GAME_SetSmartArtillerymy, reinterpret_cast<void**>(&GAME_SetSmartArtilleryold));
		MH_EnableHook(GAME_SetSmartArtilleryorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetSoundChannel", FALSE))
	{
		GAME_SetSoundChannelorg = (GAME_SetSoundChannel) ((DWORD) GameDll + 0x3CCC20);
		MH_CreateHook(GAME_SetSoundChannelorg, &GAME_SetSoundChannelmy, reinterpret_cast<void**>(&GAME_SetSoundChannelold));
		MH_EnableHook(GAME_SetSoundChannelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetSoundConeAngles", FALSE))
	{
		GAME_SetSoundConeAnglesorg = (GAME_SetSoundConeAngles) ((DWORD) GameDll + 0x3CCCF0);
		MH_CreateHook(GAME_SetSoundConeAnglesorg, &GAME_SetSoundConeAnglesmy, reinterpret_cast<void**>(&GAME_SetSoundConeAnglesold));
		MH_EnableHook(GAME_SetSoundConeAnglesorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetSoundConeOrientation", FALSE))
	{
		GAME_SetSoundConeOrientationorg = (GAME_SetSoundConeOrientation) ((DWORD) GameDll + 0x3CCD30);
		MH_CreateHook(GAME_SetSoundConeOrientationorg, &GAME_SetSoundConeOrientationmy, reinterpret_cast<void**>(&GAME_SetSoundConeOrientationold));
		MH_EnableHook(GAME_SetSoundConeOrientationorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetSoundDistanceCutoff", FALSE))
	{
		GAME_SetSoundDistanceCutofforg = (GAME_SetSoundDistanceCutoff) ((DWORD) GameDll + 0x3CCCD0);
		MH_CreateHook(GAME_SetSoundDistanceCutofforg, &GAME_SetSoundDistanceCutoffmy, reinterpret_cast<void**>(&GAME_SetSoundDistanceCutoffold));
		MH_EnableHook(GAME_SetSoundDistanceCutofforg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetSoundDistances", FALSE))
	{
		GAME_SetSoundDistancesorg = (GAME_SetSoundDistances) ((DWORD) GameDll + 0x3CCCA0);
		MH_CreateHook(GAME_SetSoundDistancesorg, &GAME_SetSoundDistancesmy, reinterpret_cast<void**>(&GAME_SetSoundDistancesold));
		MH_EnableHook(GAME_SetSoundDistancesorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetSoundDuration", FALSE))
	{
		GAME_SetSoundDurationorg = (GAME_SetSoundDuration) ((DWORD) GameDll + 0x3CCEF0);
		MH_CreateHook(GAME_SetSoundDurationorg, &GAME_SetSoundDurationmy, reinterpret_cast<void**>(&GAME_SetSoundDurationold));
		MH_EnableHook(GAME_SetSoundDurationorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetSoundParamsFromLabel", FALSE))
	{
		GAME_SetSoundParamsFromLabelorg = (GAME_SetSoundParamsFromLabel) ((DWORD) GameDll + 0x3CCBF0);
		MH_CreateHook(GAME_SetSoundParamsFromLabelorg, &GAME_SetSoundParamsFromLabelmy, reinterpret_cast<void**>(&GAME_SetSoundParamsFromLabelold));
		MH_EnableHook(GAME_SetSoundParamsFromLabelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetSoundPitch", FALSE))
	{
		GAME_SetSoundPitchorg = (GAME_SetSoundPitch) ((DWORD) GameDll + 0x3CCC60);
		MH_CreateHook(GAME_SetSoundPitchorg, &GAME_SetSoundPitchmy, reinterpret_cast<void**>(&GAME_SetSoundPitchold));
		MH_EnableHook(GAME_SetSoundPitchorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetSoundPlayPosition", FALSE))
	{
		GAME_SetSoundPlayPositionorg = (GAME_SetSoundPlayPosition) ((DWORD) GameDll + 0x3CCC80);
		MH_CreateHook(GAME_SetSoundPlayPositionorg, &GAME_SetSoundPlayPositionmy, reinterpret_cast<void**>(&GAME_SetSoundPlayPositionold));
		MH_EnableHook(GAME_SetSoundPlayPositionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetSoundPosition", FALSE))
	{
		GAME_SetSoundPositionorg = (GAME_SetSoundPosition) ((DWORD) GameDll + 0x3CCD90);
		MH_CreateHook(GAME_SetSoundPositionorg, &GAME_SetSoundPositionmy, reinterpret_cast<void**>(&GAME_SetSoundPositionold));
		MH_EnableHook(GAME_SetSoundPositionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetSoundVelocity", FALSE))
	{
		GAME_SetSoundVelocityorg = (GAME_SetSoundVelocity) ((DWORD) GameDll + 0x3CCDF0);
		MH_CreateHook(GAME_SetSoundVelocityorg, &GAME_SetSoundVelocitymy, reinterpret_cast<void**>(&GAME_SetSoundVelocityold));
		MH_EnableHook(GAME_SetSoundVelocityorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetSoundVolume", FALSE))
	{
		GAME_SetSoundVolumeorg = (GAME_SetSoundVolume) ((DWORD) GameDll + 0x3CCC40);
		MH_CreateHook(GAME_SetSoundVolumeorg, &GAME_SetSoundVolumemy, reinterpret_cast<void**>(&GAME_SetSoundVolumeold));
		MH_EnableHook(GAME_SetSoundVolumeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetStackedSound", FALSE))
	{
		GAME_SetStackedSoundorg = (GAME_SetStackedSound) ((DWORD) GameDll + 0x3B3C20);
		MH_CreateHook(GAME_SetStackedSoundorg, &GAME_SetStackedSoundmy, reinterpret_cast<void**>(&GAME_SetStackedSoundold));
		MH_EnableHook(GAME_SetStackedSoundorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetStackedSoundRect", FALSE))
	{
		GAME_SetStackedSoundRectorg = (GAME_SetStackedSoundRect) ((DWORD) GameDll + 0x3CCA50);
		MH_CreateHook(GAME_SetStackedSoundRectorg, &GAME_SetStackedSoundRectmy, reinterpret_cast<void**>(&GAME_SetStackedSoundRectold));
		MH_EnableHook(GAME_SetStackedSoundRectorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetStagePoint", FALSE))
	{
		GAME_SetStagePointorg = (GAME_SetStagePoint) ((DWORD) GameDll + 0x2DDBD0);
		MH_CreateHook(GAME_SetStagePointorg, &GAME_SetStagePointmy, reinterpret_cast<void**>(&GAME_SetStagePointold));
		MH_EnableHook(GAME_SetStagePointorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetStartLocPrio", FALSE))
	{
		GAME_SetStartLocPrioorg = (GAME_SetStartLocPrio) ((DWORD) GameDll + 0x3BAFC0);
		MH_CreateHook(GAME_SetStartLocPrioorg, &GAME_SetStartLocPriomy, reinterpret_cast<void**>(&GAME_SetStartLocPrioold));
		MH_EnableHook(GAME_SetStartLocPrioorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetStartLocPrioCount", FALSE))
	{
		GAME_SetStartLocPrioCountorg = (GAME_SetStartLocPrioCount) ((DWORD) GameDll + 0x3BAF90);
		MH_CreateHook(GAME_SetStartLocPrioCountorg, &GAME_SetStartLocPrioCountmy, reinterpret_cast<void**>(&GAME_SetStartLocPrioCountold));
		MH_EnableHook(GAME_SetStartLocPrioCountorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTargetHeroes", FALSE))
	{
		GAME_SetTargetHeroesorg = (GAME_SetTargetHeroes) ((DWORD) GameDll + 0x2DDE60);
		MH_CreateHook(GAME_SetTargetHeroesorg, &GAME_SetTargetHeroesmy, reinterpret_cast<void**>(&GAME_SetTargetHeroesold));
		MH_EnableHook(GAME_SetTargetHeroesorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTeams", FALSE))
	{
		GAME_SetTeamsorg = (GAME_SetTeams) ((DWORD) GameDll + 0x3D4000);
		MH_CreateHook(GAME_SetTeamsorg, &GAME_SetTeamsmy, reinterpret_cast<void**>(&GAME_SetTeamsold));
		MH_EnableHook(GAME_SetTeamsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTerrainFog", FALSE))
	{
		GAME_SetTerrainFogorg = (GAME_SetTerrainFog) ((DWORD) GameDll + 0x3B3840);
		MH_CreateHook(GAME_SetTerrainFogorg, &GAME_SetTerrainFogmy, reinterpret_cast<void**>(&GAME_SetTerrainFogold));
		MH_EnableHook(GAME_SetTerrainFogorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTerrainFogEx", FALSE))
	{
		GAME_SetTerrainFogExorg = (GAME_SetTerrainFogEx) ((DWORD) GameDll + 0x3B81B0);
		MH_CreateHook(GAME_SetTerrainFogExorg, &GAME_SetTerrainFogExmy, reinterpret_cast<void**>(&GAME_SetTerrainFogExold));
		MH_EnableHook(GAME_SetTerrainFogExorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTerrainPathable", FALSE))
	{
		GAME_SetTerrainPathableorg = (GAME_SetTerrainPathable) ((DWORD) GameDll + 0x3B42F0);
		MH_CreateHook(GAME_SetTerrainPathableorg, &GAME_SetTerrainPathablemy, reinterpret_cast<void**>(&GAME_SetTerrainPathableold));
		MH_EnableHook(GAME_SetTerrainPathableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTerrainType", FALSE))
	{
		GAME_SetTerrainTypeorg = (GAME_SetTerrainType) ((DWORD) GameDll + 0x3BCF20);
		MH_CreateHook(GAME_SetTerrainTypeorg, &GAME_SetTerrainTypemy, reinterpret_cast<void**>(&GAME_SetTerrainTypeold));
		MH_EnableHook(GAME_SetTerrainTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTextTagAge", FALSE))
	{
		GAME_SetTextTagAgeorg = (GAME_SetTextTagAge) ((DWORD) GameDll + 0x3BC7F0);
		MH_CreateHook(GAME_SetTextTagAgeorg, &GAME_SetTextTagAgemy, reinterpret_cast<void**>(&GAME_SetTextTagAgeold));
		MH_EnableHook(GAME_SetTextTagAgeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTextTagColor", FALSE))
	{
		GAME_SetTextTagColororg = (GAME_SetTextTagColor) ((DWORD) GameDll + 0x3BC6A0);
		MH_CreateHook(GAME_SetTextTagColororg, &GAME_SetTextTagColormy, reinterpret_cast<void**>(&GAME_SetTextTagColorold));
		MH_EnableHook(GAME_SetTextTagColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTextTagFadepoint", FALSE))
	{
		GAME_SetTextTagFadepointorg = (GAME_SetTextTagFadepoint) ((DWORD) GameDll + 0x3BC850);
		MH_CreateHook(GAME_SetTextTagFadepointorg, &GAME_SetTextTagFadepointmy, reinterpret_cast<void**>(&GAME_SetTextTagFadepointold));
		MH_EnableHook(GAME_SetTextTagFadepointorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTextTagLifespan", FALSE))
	{
		GAME_SetTextTagLifespanorg = (GAME_SetTextTagLifespan) ((DWORD) GameDll + 0x3BC820);
		MH_CreateHook(GAME_SetTextTagLifespanorg, &GAME_SetTextTagLifespanmy, reinterpret_cast<void**>(&GAME_SetTextTagLifespanold));
		MH_EnableHook(GAME_SetTextTagLifespanorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTextTagPermanent", FALSE))
	{
		GAME_SetTextTagPermanentorg = (GAME_SetTextTagPermanent) ((DWORD) GameDll + 0x3BC7C0);
		MH_CreateHook(GAME_SetTextTagPermanentorg, &GAME_SetTextTagPermanentmy, reinterpret_cast<void**>(&GAME_SetTextTagPermanentold));
		MH_EnableHook(GAME_SetTextTagPermanentorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTextTagPos", FALSE))
	{
		GAME_SetTextTagPosorg = (GAME_SetTextTagPos) ((DWORD) GameDll + 0x3BC610);
		MH_CreateHook(GAME_SetTextTagPosorg, &GAME_SetTextTagPosmy, reinterpret_cast<void**>(&GAME_SetTextTagPosold));
		MH_EnableHook(GAME_SetTextTagPosorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTextTagPosUnit", FALSE))
	{
		GAME_SetTextTagPosUnitorg = (GAME_SetTextTagPosUnit) ((DWORD) GameDll + 0x3CB890);
		MH_CreateHook(GAME_SetTextTagPosUnitorg, &GAME_SetTextTagPosUnitmy, reinterpret_cast<void**>(&GAME_SetTextTagPosUnitold));
		MH_EnableHook(GAME_SetTextTagPosUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTextTagSuspended", FALSE))
	{
		GAME_SetTextTagSuspendedorg = (GAME_SetTextTagSuspended) ((DWORD) GameDll + 0x3BC790);
		MH_CreateHook(GAME_SetTextTagSuspendedorg, &GAME_SetTextTagSuspendedmy, reinterpret_cast<void**>(&GAME_SetTextTagSuspendedold));
		MH_EnableHook(GAME_SetTextTagSuspendedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTextTagText", FALSE))
	{
		GAME_SetTextTagTextorg = (GAME_SetTextTagText) ((DWORD) GameDll + 0x3BC5D0);
		MH_CreateHook(GAME_SetTextTagTextorg, &GAME_SetTextTagTextmy, reinterpret_cast<void**>(&GAME_SetTextTagTextold));
		MH_EnableHook(GAME_SetTextTagTextorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTextTagVelocity", FALSE))
	{
		GAME_SetTextTagVelocityorg = (GAME_SetTextTagVelocity) ((DWORD) GameDll + 0x3BC700);
		MH_CreateHook(GAME_SetTextTagVelocityorg, &GAME_SetTextTagVelocitymy, reinterpret_cast<void**>(&GAME_SetTextTagVelocityold));
		MH_EnableHook(GAME_SetTextTagVelocityorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTextTagVisibility", FALSE))
	{
		GAME_SetTextTagVisibilityorg = (GAME_SetTextTagVisibility) ((DWORD) GameDll + 0x3BC760);
		MH_CreateHook(GAME_SetTextTagVisibilityorg, &GAME_SetTextTagVisibilitymy, reinterpret_cast<void**>(&GAME_SetTextTagVisibilityold));
		MH_EnableHook(GAME_SetTextTagVisibilityorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetThematicMusicPlayPosition", FALSE))
	{
		GAME_SetThematicMusicPlayPositionorg = (GAME_SetThematicMusicPlayPosition) ((DWORD) GameDll + 0x3B3E10);
		MH_CreateHook(GAME_SetThematicMusicPlayPositionorg, &GAME_SetThematicMusicPlayPositionmy, reinterpret_cast<void**>(&GAME_SetThematicMusicPlayPositionold));
		MH_EnableHook(GAME_SetThematicMusicPlayPositionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTimeOfDayScale", FALSE))
	{
		GAME_SetTimeOfDayScaleorg = (GAME_SetTimeOfDayScale) ((DWORD) GameDll + 0x3BC490);
		MH_CreateHook(GAME_SetTimeOfDayScaleorg, &GAME_SetTimeOfDayScalemy, reinterpret_cast<void**>(&GAME_SetTimeOfDayScaleold));
		MH_EnableHook(GAME_SetTimeOfDayScaleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetTutorialCleared", FALSE))
	{
		GAME_SetTutorialClearedorg = (GAME_SetTutorialCleared) ((DWORD) GameDll + 0x3B3430);
		MH_CreateHook(GAME_SetTutorialClearedorg, &GAME_SetTutorialClearedmy, reinterpret_cast<void**>(&GAME_SetTutorialClearedold));
		MH_EnableHook(GAME_SetTutorialClearedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUbersplatRender", FALSE))
	{
		GAME_SetUbersplatRenderorg = (GAME_SetUbersplatRender) ((DWORD) GameDll + 0x3B4510);
		MH_CreateHook(GAME_SetUbersplatRenderorg, &GAME_SetUbersplatRendermy, reinterpret_cast<void**>(&GAME_SetUbersplatRenderold));
		MH_EnableHook(GAME_SetUbersplatRenderorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUbersplatRenderAlways", FALSE))
	{
		GAME_SetUbersplatRenderAlwaysorg = (GAME_SetUbersplatRenderAlways) ((DWORD) GameDll + 0x3B4530);
		MH_CreateHook(GAME_SetUbersplatRenderAlwaysorg, &GAME_SetUbersplatRenderAlwaysmy, reinterpret_cast<void**>(&GAME_SetUbersplatRenderAlwaysold));
		MH_EnableHook(GAME_SetUbersplatRenderAlwaysorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitAbilityLevel", FALSE))
	{
		GAME_SetUnitAbilityLevelorg = (GAME_SetUnitAbilityLevel) ((DWORD) GameDll + 0x3C71B0);
		MH_CreateHook(GAME_SetUnitAbilityLevelorg, &GAME_SetUnitAbilityLevelmy, reinterpret_cast<void**>(&GAME_SetUnitAbilityLevelold));
		MH_EnableHook(GAME_SetUnitAbilityLevelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitAcquireRange", FALSE))
	{
		GAME_SetUnitAcquireRangeorg = (GAME_SetUnitAcquireRange) ((DWORD) GameDll + 0x3C5CF0);
		MH_CreateHook(GAME_SetUnitAcquireRangeorg, &GAME_SetUnitAcquireRangemy, reinterpret_cast<void**>(&GAME_SetUnitAcquireRangeold));
		MH_EnableHook(GAME_SetUnitAcquireRangeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitAnimation", FALSE))
	{
		GAME_SetUnitAnimationorg = (GAME_SetUnitAnimation) ((DWORD) GameDll + 0x3C61A0);
		MH_CreateHook(GAME_SetUnitAnimationorg, &GAME_SetUnitAnimationmy, reinterpret_cast<void**>(&GAME_SetUnitAnimationold));
		MH_EnableHook(GAME_SetUnitAnimationorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitAnimationByIndex", FALSE))
	{
		GAME_SetUnitAnimationByIndexorg = (GAME_SetUnitAnimationByIndex) ((DWORD) GameDll + 0x3C61F0);
		MH_CreateHook(GAME_SetUnitAnimationByIndexorg, &GAME_SetUnitAnimationByIndexmy, reinterpret_cast<void**>(&GAME_SetUnitAnimationByIndexold));
		MH_EnableHook(GAME_SetUnitAnimationByIndexorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitAnimationWithRarity", FALSE))
	{
		GAME_SetUnitAnimationWithRarityorg = (GAME_SetUnitAnimationWithRarity) ((DWORD) GameDll + 0x3C61C0);
		MH_CreateHook(GAME_SetUnitAnimationWithRarityorg, &GAME_SetUnitAnimationWithRaritymy, reinterpret_cast<void**>(&GAME_SetUnitAnimationWithRarityold));
		MH_EnableHook(GAME_SetUnitAnimationWithRarityorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitBlendTime", FALSE))
	{
		GAME_SetUnitBlendTimeorg = (GAME_SetUnitBlendTime) ((DWORD) GameDll + 0x3C6320);
		MH_CreateHook(GAME_SetUnitBlendTimeorg, &GAME_SetUnitBlendTimemy, reinterpret_cast<void**>(&GAME_SetUnitBlendTimeold));
		MH_EnableHook(GAME_SetUnitBlendTimeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitColor", FALSE))
	{
		GAME_SetUnitColororg = (GAME_SetUnitColor) ((DWORD) GameDll + 0x3C5F60);
		MH_CreateHook(GAME_SetUnitColororg, &GAME_SetUnitColormy, reinterpret_cast<void**>(&GAME_SetUnitColorold));
		MH_EnableHook(GAME_SetUnitColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitCreepGuard", FALSE))
	{
		GAME_SetUnitCreepGuardorg = (GAME_SetUnitCreepGuard) ((DWORD) GameDll + 0x3C5480);
		MH_CreateHook(GAME_SetUnitCreepGuardorg, &GAME_SetUnitCreepGuardmy, reinterpret_cast<void**>(&GAME_SetUnitCreepGuardold));
		MH_EnableHook(GAME_SetUnitCreepGuardorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitExploded", FALSE))
	{
		GAME_SetUnitExplodedorg = (GAME_SetUnitExploded) ((DWORD) GameDll + 0x3CE6D0);
		MH_CreateHook(GAME_SetUnitExplodedorg, &GAME_SetUnitExplodedmy, reinterpret_cast<void**>(&GAME_SetUnitExplodedold));
		MH_EnableHook(GAME_SetUnitExplodedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitFacing", FALSE))
	{
		GAME_SetUnitFacingorg = (GAME_SetUnitFacing) ((DWORD) GameDll + 0x3C5AF0);
		MH_CreateHook(GAME_SetUnitFacingorg, &GAME_SetUnitFacingmy, reinterpret_cast<void**>(&GAME_SetUnitFacingold));
		MH_EnableHook(GAME_SetUnitFacingorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitFacingTimed", FALSE))
	{
		GAME_SetUnitFacingTimedorg = (GAME_SetUnitFacingTimed) ((DWORD) GameDll + 0x3C5B30);
		MH_CreateHook(GAME_SetUnitFacingTimedorg, &GAME_SetUnitFacingTimedmy, reinterpret_cast<void**>(&GAME_SetUnitFacingTimedold));
		MH_EnableHook(GAME_SetUnitFacingTimedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitFlyHeight", FALSE))
	{
		GAME_SetUnitFlyHeightorg = (GAME_SetUnitFlyHeight) ((DWORD) GameDll + 0x3C5C60);
		MH_CreateHook(GAME_SetUnitFlyHeightorg, &GAME_SetUnitFlyHeightmy, reinterpret_cast<void**>(&GAME_SetUnitFlyHeightold));
		MH_EnableHook(GAME_SetUnitFlyHeightorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitFog", FALSE))
	{
		GAME_SetUnitFogorg = (GAME_SetUnitFog) ((DWORD) GameDll + 0x3B3850);
		MH_CreateHook(GAME_SetUnitFogorg, &GAME_SetUnitFogmy, reinterpret_cast<void**>(&GAME_SetUnitFogold));
		MH_EnableHook(GAME_SetUnitFogorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitInvulnerable", FALSE))
	{
		GAME_SetUnitInvulnerableorg = (GAME_SetUnitInvulnerable) ((DWORD) GameDll + 0x3C72F0);
		MH_CreateHook(GAME_SetUnitInvulnerableorg, &GAME_SetUnitInvulnerablemy, reinterpret_cast<void**>(&GAME_SetUnitInvulnerableold));
		MH_EnableHook(GAME_SetUnitInvulnerableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitLookAt", FALSE))
	{
		GAME_SetUnitLookAtorg = (GAME_SetUnitLookAt) ((DWORD) GameDll + 0x3C64C0);
		MH_CreateHook(GAME_SetUnitLookAtorg, &GAME_SetUnitLookAtmy, reinterpret_cast<void**>(&GAME_SetUnitLookAtold));
		MH_EnableHook(GAME_SetUnitLookAtorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitMoveSpeed", FALSE))
	{
		GAME_SetUnitMoveSpeedorg = (GAME_SetUnitMoveSpeed) ((DWORD) GameDll + 0x3C5C40);
		MH_CreateHook(GAME_SetUnitMoveSpeedorg, &GAME_SetUnitMoveSpeedmy, reinterpret_cast<void**>(&GAME_SetUnitMoveSpeedold));
		MH_EnableHook(GAME_SetUnitMoveSpeedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitOwner", FALSE))
	{
		GAME_SetUnitOwnerorg = (GAME_SetUnitOwner) ((DWORD) GameDll + 0x3C5ED0);
		MH_CreateHook(GAME_SetUnitOwnerorg, &GAME_SetUnitOwnermy, reinterpret_cast<void**>(&GAME_SetUnitOwnerold));
		MH_EnableHook(GAME_SetUnitOwnerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitPathing", FALSE))
	{
		GAME_SetUnitPathingorg = (GAME_SetUnitPathing) ((DWORD) GameDll + 0x3C5FA0);
		MH_CreateHook(GAME_SetUnitPathingorg, &GAME_SetUnitPathingmy, reinterpret_cast<void**>(&GAME_SetUnitPathingold));
		MH_EnableHook(GAME_SetUnitPathingorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitPosition", FALSE))
	{
		GAME_SetUnitPositionorg = (GAME_SetUnitPosition) ((DWORD) GameDll + 0x3C5A50);
		MH_CreateHook(GAME_SetUnitPositionorg, &GAME_SetUnitPositionmy, reinterpret_cast<void**>(&GAME_SetUnitPositionold));
		MH_EnableHook(GAME_SetUnitPositionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitPositionLoc", FALSE))
	{
		GAME_SetUnitPositionLocorg = (GAME_SetUnitPositionLoc) ((DWORD) GameDll + 0x3C5AB0);
		MH_CreateHook(GAME_SetUnitPositionLocorg, &GAME_SetUnitPositionLocmy, reinterpret_cast<void**>(&GAME_SetUnitPositionLocold));
		MH_EnableHook(GAME_SetUnitPositionLocorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitPropWindow", FALSE))
	{
		GAME_SetUnitPropWindoworg = (GAME_SetUnitPropWindow) ((DWORD) GameDll + 0x3C5CD0);
		MH_CreateHook(GAME_SetUnitPropWindoworg, &GAME_SetUnitPropWindowmy, reinterpret_cast<void**>(&GAME_SetUnitPropWindowold));
		MH_EnableHook(GAME_SetUnitPropWindoworg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitRescuable", FALSE))
	{
		GAME_SetUnitRescuableorg = (GAME_SetUnitRescuable) ((DWORD) GameDll + 0x3C5F10);
		MH_CreateHook(GAME_SetUnitRescuableorg, &GAME_SetUnitRescuablemy, reinterpret_cast<void**>(&GAME_SetUnitRescuableold));
		MH_EnableHook(GAME_SetUnitRescuableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitRescueRange", FALSE))
	{
		GAME_SetUnitRescueRangeorg = (GAME_SetUnitRescueRange) ((DWORD) GameDll + 0x3C5F40);
		MH_CreateHook(GAME_SetUnitRescueRangeorg, &GAME_SetUnitRescueRangemy, reinterpret_cast<void**>(&GAME_SetUnitRescueRangeold));
		MH_EnableHook(GAME_SetUnitRescueRangeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitScale", FALSE))
	{
		GAME_SetUnitScaleorg = (GAME_SetUnitScale) ((DWORD) GameDll + 0x3C62D0);
		MH_CreateHook(GAME_SetUnitScaleorg, &GAME_SetUnitScalemy, reinterpret_cast<void**>(&GAME_SetUnitScaleold));
		MH_EnableHook(GAME_SetUnitScaleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitState", FALSE))
	{
		GAME_SetUnitStateorg = (GAME_SetUnitState) ((DWORD) GameDll + 0x3C5EA0);
		MH_CreateHook(GAME_SetUnitStateorg, &GAME_SetUnitStatemy, reinterpret_cast<void**>(&GAME_SetUnitStateold));
		MH_EnableHook(GAME_SetUnitStateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitTimeScale", FALSE))
	{
		GAME_SetUnitTimeScaleorg = (GAME_SetUnitTimeScale) ((DWORD) GameDll + 0x3C6300);
		MH_CreateHook(GAME_SetUnitTimeScaleorg, &GAME_SetUnitTimeScalemy, reinterpret_cast<void**>(&GAME_SetUnitTimeScaleold));
		MH_EnableHook(GAME_SetUnitTimeScaleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitTurnSpeed", FALSE))
	{
		GAME_SetUnitTurnSpeedorg = (GAME_SetUnitTurnSpeed) ((DWORD) GameDll + 0x3C5CB0);
		MH_CreateHook(GAME_SetUnitTurnSpeedorg, &GAME_SetUnitTurnSpeedmy, reinterpret_cast<void**>(&GAME_SetUnitTurnSpeedold));
		MH_EnableHook(GAME_SetUnitTurnSpeedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitTypeSlots", FALSE))
	{
		GAME_SetUnitTypeSlotsorg = (GAME_SetUnitTypeSlots) ((DWORD) GameDll + 0x3C94B0);
		MH_CreateHook(GAME_SetUnitTypeSlotsorg, &GAME_SetUnitTypeSlotsmy, reinterpret_cast<void**>(&GAME_SetUnitTypeSlotsold));
		MH_EnableHook(GAME_SetUnitTypeSlotsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitUseFood", FALSE))
	{
		GAME_SetUnitUseFoodorg = (GAME_SetUnitUseFood) ((DWORD) GameDll + 0x3C54A0);
		MH_CreateHook(GAME_SetUnitUseFoodorg, &GAME_SetUnitUseFoodmy, reinterpret_cast<void**>(&GAME_SetUnitUseFoodold));
		MH_EnableHook(GAME_SetUnitUseFoodorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitUserData", FALSE))
	{
		GAME_SetUnitUserDataorg = (GAME_SetUnitUserData) ((DWORD) GameDll + 0x3C9510);
		MH_CreateHook(GAME_SetUnitUserDataorg, &GAME_SetUnitUserDatamy, reinterpret_cast<void**>(&GAME_SetUnitUserDataold));
		MH_EnableHook(GAME_SetUnitUserDataorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitVertexColor", FALSE))
	{
		GAME_SetUnitVertexColororg = (GAME_SetUnitVertexColor) ((DWORD) GameDll + 0x3C6340);
		MH_CreateHook(GAME_SetUnitVertexColororg, &GAME_SetUnitVertexColormy, reinterpret_cast<void**>(&GAME_SetUnitVertexColorold));
		MH_EnableHook(GAME_SetUnitVertexColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitX", FALSE))
	{
		GAME_SetUnitXorg = (GAME_SetUnitX) ((DWORD) GameDll + 0x3C5970);
		MH_CreateHook(GAME_SetUnitXorg, &GAME_SetUnitXmy, reinterpret_cast<void**>(&GAME_SetUnitXold));
		MH_EnableHook(GAME_SetUnitXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitY", FALSE))
	{
		GAME_SetUnitYorg = (GAME_SetUnitY) ((DWORD) GameDll + 0x3C59E0);
		MH_CreateHook(GAME_SetUnitYorg, &GAME_SetUnitYmy, reinterpret_cast<void**>(&GAME_SetUnitYold));
		MH_EnableHook(GAME_SetUnitYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUnitsFlee", FALSE))
	{
		GAME_SetUnitsFleeorg = (GAME_SetUnitsFlee) ((DWORD) GameDll + 0x2E3260);
		MH_CreateHook(GAME_SetUnitsFleeorg, &GAME_SetUnitsFleemy, reinterpret_cast<void**>(&GAME_SetUnitsFleeold));
		MH_EnableHook(GAME_SetUnitsFleeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetUpgrade", FALSE))
	{
		GAME_SetUpgradeorg = (GAME_SetUpgrade) ((DWORD) GameDll + 0x2DD4B0);
		MH_CreateHook(GAME_SetUpgradeorg, &GAME_SetUpgrademy, reinterpret_cast<void**>(&GAME_SetUpgradeold));
		MH_EnableHook(GAME_SetUpgradeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetWatchMegaTargets", FALSE))
	{
		GAME_SetWatchMegaTargetsorg = (GAME_SetWatchMegaTargets) ((DWORD) GameDll + 0x2E31A0);
		MH_CreateHook(GAME_SetWatchMegaTargetsorg, &GAME_SetWatchMegaTargetsmy, reinterpret_cast<void**>(&GAME_SetWatchMegaTargetsold));
		MH_EnableHook(GAME_SetWatchMegaTargetsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetWaterBaseColor", FALSE))
	{
		GAME_SetWaterBaseColororg = (GAME_SetWaterBaseColor) ((DWORD) GameDll + 0x3B8580);
		MH_CreateHook(GAME_SetWaterBaseColororg, &GAME_SetWaterBaseColormy, reinterpret_cast<void**>(&GAME_SetWaterBaseColorold));
		MH_EnableHook(GAME_SetWaterBaseColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetWaterDeforms", FALSE))
	{
		GAME_SetWaterDeformsorg = (GAME_SetWaterDeforms) ((DWORD) GameDll + 0x3B4240);
		MH_CreateHook(GAME_SetWaterDeformsorg, &GAME_SetWaterDeformsmy, reinterpret_cast<void**>(&GAME_SetWaterDeformsold));
		MH_EnableHook(GAME_SetWaterDeformsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SetWidgetLife", FALSE))
	{
		GAME_SetWidgetLifeorg = (GAME_SetWidgetLife) ((DWORD) GameDll + 0x3C4690);
		MH_CreateHook(GAME_SetWidgetLifeorg, &GAME_SetWidgetLifemy, reinterpret_cast<void**>(&GAME_SetWidgetLifeold));
		MH_EnableHook(GAME_SetWidgetLifeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ShiftTownSpot", FALSE))
	{
		GAME_ShiftTownSpotorg = (GAME_ShiftTownSpot) ((DWORD) GameDll + 0x2DD740);
		MH_CreateHook(GAME_ShiftTownSpotorg, &GAME_ShiftTownSpotmy, reinterpret_cast<void**>(&GAME_ShiftTownSpotold));
		MH_EnableHook(GAME_ShiftTownSpotorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ShowDestructable", FALSE))
	{
		GAME_ShowDestructableorg = (GAME_ShowDestructable) ((DWORD) GameDll + 0x3C4A60);
		MH_CreateHook(GAME_ShowDestructableorg, &GAME_ShowDestructablemy, reinterpret_cast<void**>(&GAME_ShowDestructableold));
		MH_EnableHook(GAME_ShowDestructableorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ShowImage", FALSE))
	{
		GAME_ShowImageorg = (GAME_ShowImage) ((DWORD) GameDll + 0x3B43C0);
		MH_CreateHook(GAME_ShowImageorg, &GAME_ShowImagemy, reinterpret_cast<void**>(&GAME_ShowImageold));
		MH_EnableHook(GAME_ShowImageorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ShowInterface", FALSE))
	{
		GAME_ShowInterfaceorg = (GAME_ShowInterface) ((DWORD) GameDll + 0x3B3810);
		MH_CreateHook(GAME_ShowInterfaceorg, &GAME_ShowInterfacemy, reinterpret_cast<void**>(&GAME_ShowInterfaceold));
		MH_EnableHook(GAME_ShowInterfaceorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ShowUbersplat", FALSE))
	{
		GAME_ShowUbersplatorg = (GAME_ShowUbersplat) ((DWORD) GameDll + 0x3B44F0);
		MH_CreateHook(GAME_ShowUbersplatorg, &GAME_ShowUbersplatmy, reinterpret_cast<void**>(&GAME_ShowUbersplatold));
		MH_EnableHook(GAME_ShowUbersplatorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_ShowUnit", FALSE))
	{
		GAME_ShowUnitorg = (GAME_ShowUnit) ((DWORD) GameDll + 0x3CE730);
		MH_CreateHook(GAME_ShowUnitorg, &GAME_ShowUnitmy, reinterpret_cast<void**>(&GAME_ShowUnitold));
		MH_EnableHook(GAME_ShowUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Sin", FALSE))
	{
		GAME_Sinorg = (GAME_Sin) ((DWORD) GameDll + 0x3B2A10);
		MH_CreateHook(GAME_Sinorg, &GAME_Sinmy, reinterpret_cast<void**>(&GAME_Sinold));
		MH_EnableHook(GAME_Sinorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Sleep", FALSE))
	{
		GAME_Sleeporg = (GAME_Sleep) ((DWORD) GameDll + 0x2DE380);
		MH_CreateHook(GAME_Sleeporg, &GAME_Sleepmy, reinterpret_cast<void**>(&GAME_Sleepold));
		MH_EnableHook(GAME_Sleeporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SquareRoot", FALSE))
	{
		GAME_SquareRootorg = (GAME_SquareRoot) ((DWORD) GameDll + 0x3B2BA0);
		MH_CreateHook(GAME_SquareRootorg, &GAME_SquareRootmy, reinterpret_cast<void**>(&GAME_SquareRootold));
		MH_EnableHook(GAME_SquareRootorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_StartCampaignAI", FALSE))
	{
		GAME_StartCampaignAIorg = (GAME_StartCampaignAI) ((DWORD) GameDll + 0x3CB770);
		MH_CreateHook(GAME_StartCampaignAIorg, &GAME_StartCampaignAImy, reinterpret_cast<void**>(&GAME_StartCampaignAIold));
		MH_EnableHook(GAME_StartCampaignAIorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_StartGetEnemyBase", FALSE))
	{
		GAME_StartGetEnemyBaseorg = (GAME_StartGetEnemyBase) ((DWORD) GameDll + 0x2DDCC0);
		MH_CreateHook(GAME_StartGetEnemyBaseorg, &GAME_StartGetEnemyBasemy, reinterpret_cast<void**>(&GAME_StartGetEnemyBaseold));
		MH_EnableHook(GAME_StartGetEnemyBaseorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_StartMeleeAI", FALSE))
	{
		GAME_StartMeleeAIorg = (GAME_StartMeleeAI) ((DWORD) GameDll + 0x3CB740);
		MH_CreateHook(GAME_StartMeleeAIorg, &GAME_StartMeleeAImy, reinterpret_cast<void**>(&GAME_StartMeleeAIold));
		MH_EnableHook(GAME_StartMeleeAIorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_StartSound", FALSE))
	{
		GAME_StartSoundorg = (GAME_StartSound) ((DWORD) GameDll + 0x3CCE80);
		MH_CreateHook(GAME_StartSoundorg, &GAME_StartSoundmy, reinterpret_cast<void**>(&GAME_StartSoundold));
		MH_EnableHook(GAME_StartSoundorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_StartThread", FALSE))
	{
		GAME_StartThreadorg = (GAME_StartThread) ((DWORD) GameDll + 0x2DE2A0);
		MH_CreateHook(GAME_StartThreadorg, &GAME_StartThreadmy, reinterpret_cast<void**>(&GAME_StartThreadold));
		MH_EnableHook(GAME_StartThreadorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_StopCamera", FALSE))
	{
		GAME_StopCameraorg = (GAME_StopCamera) ((DWORD) GameDll + 0x3B46E0);
		MH_CreateHook(GAME_StopCameraorg, &GAME_StopCameramy, reinterpret_cast<void**>(&GAME_StopCameraold));
		MH_EnableHook(GAME_StopCameraorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_StopGathering", FALSE))
	{
		GAME_StopGatheringorg = (GAME_StopGathering) ((DWORD) GameDll + 0x2DCE00);
		MH_CreateHook(GAME_StopGatheringorg, &GAME_StopGatheringmy, reinterpret_cast<void**>(&GAME_StopGatheringold));
		MH_EnableHook(GAME_StopGatheringorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_StopMusic", FALSE))
	{
		GAME_StopMusicorg = (GAME_StopMusic) ((DWORD) GameDll + 0x3B3D80);
		MH_CreateHook(GAME_StopMusicorg, &GAME_StopMusicmy, reinterpret_cast<void**>(&GAME_StopMusicold));
		MH_EnableHook(GAME_StopMusicorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_StopSound", FALSE))
	{
		GAME_StopSoundorg = (GAME_StopSound) ((DWORD) GameDll + 0x3CCEB0);
		MH_CreateHook(GAME_StopSoundorg, &GAME_StopSoundmy, reinterpret_cast<void**>(&GAME_StopSoundold));
		MH_EnableHook(GAME_StopSoundorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_StoreBOOLean", FALSE))
	{
		GAME_StoreBOOLeanorg = (GAME_StoreBOOLean) ((DWORD) GameDll + 0x3CA140);
		MH_CreateHook(GAME_StoreBOOLeanorg, &GAME_StoreBOOLeanmy, reinterpret_cast<void**>(&GAME_StoreBOOLeanold));
		MH_EnableHook(GAME_StoreBOOLeanorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_StoreInteger", FALSE))
	{
		GAME_StoreIntegerorg = (GAME_StoreInteger) ((DWORD) GameDll + 0x3CA0A0);
		MH_CreateHook(GAME_StoreIntegerorg, &GAME_StoreIntegermy, reinterpret_cast<void**>(&GAME_StoreIntegerold));
		MH_EnableHook(GAME_StoreIntegerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_StoreReal", FALSE))
	{
		GAME_StoreRealorg = (GAME_StoreReal) ((DWORD) GameDll + 0x3CA0F0);
		MH_CreateHook(GAME_StoreRealorg, &GAME_StoreRealmy, reinterpret_cast<void**>(&GAME_StoreRealold));
		MH_EnableHook(GAME_StoreRealorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_StoreString", FALSE))
	{
		GAME_StoreStringorg = (GAME_StoreString) ((DWORD) GameDll + 0x3CA680);
		MH_CreateHook(GAME_StoreStringorg, &GAME_StoreStringmy, reinterpret_cast<void**>(&GAME_StoreStringold));
		MH_EnableHook(GAME_StoreStringorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_StoreUnit", FALSE))
	{
		GAME_StoreUnitorg = (GAME_StoreUnit) ((DWORD) GameDll + 0x3CA1A0);
		MH_CreateHook(GAME_StoreUnitorg, &GAME_StoreUnitmy, reinterpret_cast<void**>(&GAME_StoreUnitold));
		MH_EnableHook(GAME_StoreUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_StringCase", FALSE))
	{
		GAME_StringCaseorg = (GAME_StringCase) ((DWORD) GameDll + 0x3BAC40);
		MH_CreateHook(GAME_StringCaseorg, &GAME_StringCasemy, reinterpret_cast<void**>(&GAME_StringCaseold));
		MH_EnableHook(GAME_StringCaseorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_StringHash", FALSE))
	{
		GAME_StringHashorg = (GAME_StringHash) ((DWORD) GameDll + 0x3B2D30);
		MH_CreateHook(GAME_StringHashorg, &GAME_StringHashmy, reinterpret_cast<void**>(&GAME_StringHashold));
		MH_EnableHook(GAME_StringHashorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_StringLength", FALSE))
	{
		GAME_StringLengthorg = (GAME_StringLength) ((DWORD) GameDll + 0x3BAC20);
		MH_CreateHook(GAME_StringLengthorg, &GAME_StringLengthmy, reinterpret_cast<void**>(&GAME_StringLengthold));
		MH_EnableHook(GAME_StringLengthorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SubString", FALSE))
	{
		GAME_SubStringorg = (GAME_SubString) ((DWORD) GameDll + 0x3BABA0);
		MH_CreateHook(GAME_SubStringorg, &GAME_SubStringmy, reinterpret_cast<void**>(&GAME_SubStringold));
		MH_EnableHook(GAME_SubStringorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SuicidePlayer", FALSE))
	{
		GAME_SuicidePlayerorg = (GAME_SuicidePlayer) ((DWORD) GameDll + 0x2E2F00);
		MH_CreateHook(GAME_SuicidePlayerorg, &GAME_SuicidePlayermy, reinterpret_cast<void**>(&GAME_SuicidePlayerold));
		MH_EnableHook(GAME_SuicidePlayerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SuicidePlayerUnits", FALSE))
	{
		GAME_SuicidePlayerUnitsorg = (GAME_SuicidePlayerUnits) ((DWORD) GameDll + 0x2E2F90);
		MH_CreateHook(GAME_SuicidePlayerUnitsorg, &GAME_SuicidePlayerUnitsmy, reinterpret_cast<void**>(&GAME_SuicidePlayerUnitsold));
		MH_EnableHook(GAME_SuicidePlayerUnitsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SuicideUnit", FALSE))
	{
		GAME_SuicideUnitorg = (GAME_SuicideUnit) ((DWORD) GameDll + 0x2DE330);
		MH_CreateHook(GAME_SuicideUnitorg, &GAME_SuicideUnitmy, reinterpret_cast<void**>(&GAME_SuicideUnitold));
		MH_EnableHook(GAME_SuicideUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SuicideUnitEx", FALSE))
	{
		GAME_SuicideUnitExorg = (GAME_SuicideUnitEx) ((DWORD) GameDll + 0x2DE2E0);
		MH_CreateHook(GAME_SuicideUnitExorg, &GAME_SuicideUnitExmy, reinterpret_cast<void**>(&GAME_SuicideUnitExold));
		MH_EnableHook(GAME_SuicideUnitExorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SuspendHeroXP", FALSE))
	{
		GAME_SuspendHeroXPorg = (GAME_SuspendHeroXP) ((DWORD) GameDll + 0x3C6E10);
		MH_CreateHook(GAME_SuspendHeroXPorg, &GAME_SuspendHeroXPmy, reinterpret_cast<void**>(&GAME_SuspendHeroXPold));
		MH_EnableHook(GAME_SuspendHeroXPorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SuspendTimeOfDay", FALSE))
	{
		GAME_SuspendTimeOfDayorg = (GAME_SuspendTimeOfDay) ((DWORD) GameDll + 0x3BC460);
		MH_CreateHook(GAME_SuspendTimeOfDayorg, &GAME_SuspendTimeOfDaymy, reinterpret_cast<void**>(&GAME_SuspendTimeOfDayold));
		MH_EnableHook(GAME_SuspendTimeOfDayorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SyncSelections", FALSE))
	{
		GAME_SyncSelectionsorg = (GAME_SyncSelections) ((DWORD) GameDll + 0x3BB740);
		MH_CreateHook(GAME_SyncSelectionsorg, &GAME_SyncSelectionsmy, reinterpret_cast<void**>(&GAME_SyncSelectionsold));
		MH_EnableHook(GAME_SyncSelectionsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SyncStoredBOOLean", FALSE))
	{
		GAME_SyncStoredBOOLeanorg = (GAME_SyncStoredBOOLean) ((DWORD) GameDll + 0x3CA780);
		MH_CreateHook(GAME_SyncStoredBOOLeanorg, &GAME_SyncStoredBOOLeanmy, reinterpret_cast<void**>(&GAME_SyncStoredBOOLeanold));
		MH_EnableHook(GAME_SyncStoredBOOLeanorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SyncStoredInteger", FALSE))
	{
		GAME_SyncStoredIntegerorg = (GAME_SyncStoredInteger) ((DWORD) GameDll + 0x3CA6E0);
		MH_CreateHook(GAME_SyncStoredIntegerorg, &GAME_SyncStoredIntegermy, reinterpret_cast<void**>(&GAME_SyncStoredIntegerold));
		MH_EnableHook(GAME_SyncStoredIntegerorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SyncStoredReal", FALSE))
	{
		GAME_SyncStoredRealorg = (GAME_SyncStoredReal) ((DWORD) GameDll + 0x3CA730);
		MH_CreateHook(GAME_SyncStoredRealorg, &GAME_SyncStoredRealmy, reinterpret_cast<void**>(&GAME_SyncStoredRealold));
		MH_EnableHook(GAME_SyncStoredRealorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SyncStoredString", FALSE))
	{
		GAME_SyncStoredStringorg = (GAME_SyncStoredString) ((DWORD) GameDll + 0x3CA820);
		MH_CreateHook(GAME_SyncStoredStringorg, &GAME_SyncStoredStringmy, reinterpret_cast<void**>(&GAME_SyncStoredStringold));
		MH_EnableHook(GAME_SyncStoredStringorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_SyncStoredUnit", FALSE))
	{
		GAME_SyncStoredUnitorg = (GAME_SyncStoredUnit) ((DWORD) GameDll + 0x3CA7D0);
		MH_CreateHook(GAME_SyncStoredUnitorg, &GAME_SyncStoredUnitmy, reinterpret_cast<void**>(&GAME_SyncStoredUnitold));
		MH_EnableHook(GAME_SyncStoredUnitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Tan", FALSE))
	{
		GAME_Tanorg = (GAME_Tan) ((DWORD) GameDll + 0x3B2A50);
		MH_CreateHook(GAME_Tanorg, &GAME_Tanmy, reinterpret_cast<void**>(&GAME_Tanold));
		MH_EnableHook(GAME_Tanorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TeleportCaptain", FALSE))
	{
		GAME_TeleportCaptainorg = (GAME_TeleportCaptain) ((DWORD) GameDll + 0x2DD680);
		MH_CreateHook(GAME_TeleportCaptainorg, &GAME_TeleportCaptainmy, reinterpret_cast<void**>(&GAME_TeleportCaptainold));
		MH_EnableHook(GAME_TeleportCaptainorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TerrainDeformCrater", FALSE))
	{
		GAME_TerrainDeformCraterorg = (GAME_TerrainDeformCrater) ((DWORD) GameDll + 0x3B3E90);
		MH_CreateHook(GAME_TerrainDeformCraterorg, &GAME_TerrainDeformCratermy, reinterpret_cast<void**>(&GAME_TerrainDeformCraterold));
		MH_EnableHook(GAME_TerrainDeformCraterorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TerrainDeformRandom", FALSE))
	{
		GAME_TerrainDeformRandomorg = (GAME_TerrainDeformRandom) ((DWORD) GameDll + 0x3B4040);
		MH_CreateHook(GAME_TerrainDeformRandomorg, &GAME_TerrainDeformRandommy, reinterpret_cast<void**>(&GAME_TerrainDeformRandomold));
		MH_EnableHook(GAME_TerrainDeformRandomorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TerrainDeformRipple", FALSE))
	{
		GAME_TerrainDeformRippleorg = (GAME_TerrainDeformRipple) ((DWORD) GameDll + 0x3B3F00);
		MH_CreateHook(GAME_TerrainDeformRippleorg, &GAME_TerrainDeformRipplemy, reinterpret_cast<void**>(&GAME_TerrainDeformRippleold));
		MH_EnableHook(GAME_TerrainDeformRippleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TerrainDeformStop", FALSE))
	{
		GAME_TerrainDeformStoporg = (GAME_TerrainDeformStop) ((DWORD) GameDll + 0x3B40B0);
		MH_CreateHook(GAME_TerrainDeformStoporg, &GAME_TerrainDeformStopmy, reinterpret_cast<void**>(&GAME_TerrainDeformStopold));
		MH_EnableHook(GAME_TerrainDeformStoporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TerrainDeformStopAll", FALSE))
	{
		GAME_TerrainDeformStopAllorg = (GAME_TerrainDeformStopAll) ((DWORD) GameDll + 0x3B40C0);
		MH_CreateHook(GAME_TerrainDeformStopAllorg, &GAME_TerrainDeformStopAllmy, reinterpret_cast<void**>(&GAME_TerrainDeformStopAllold));
		MH_EnableHook(GAME_TerrainDeformStopAllorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TerrainDeformWave", FALSE))
	{
		GAME_TerrainDeformWaveorg = (GAME_TerrainDeformWave) ((DWORD) GameDll + 0x3B3FA0);
		MH_CreateHook(GAME_TerrainDeformWaveorg, &GAME_TerrainDeformWavemy, reinterpret_cast<void**>(&GAME_TerrainDeformWaveold));
		MH_EnableHook(GAME_TerrainDeformWaveorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TimerDialogDisplay", FALSE))
	{
		GAME_TimerDialogDisplayorg = (GAME_TimerDialogDisplay) ((DWORD) GameDll + 0x3CBF50);
		MH_CreateHook(GAME_TimerDialogDisplayorg, &GAME_TimerDialogDisplaymy, reinterpret_cast<void**>(&GAME_TimerDialogDisplayold));
		MH_EnableHook(GAME_TimerDialogDisplayorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TimerDialogSetRealTimeRemaining", FALSE))
	{
		GAME_TimerDialogSetRealTimeRemainingorg = (GAME_TimerDialogSetRealTimeRemaining) ((DWORD) GameDll + 0x3CBFA0);
		MH_CreateHook(GAME_TimerDialogSetRealTimeRemainingorg, &GAME_TimerDialogSetRealTimeRemainingmy, reinterpret_cast<void**>(&GAME_TimerDialogSetRealTimeRemainingold));
		MH_EnableHook(GAME_TimerDialogSetRealTimeRemainingorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TimerDialogSetSpeed", FALSE))
	{
		GAME_TimerDialogSetSpeedorg = (GAME_TimerDialogSetSpeed) ((DWORD) GameDll + 0x3CBF20);
		MH_CreateHook(GAME_TimerDialogSetSpeedorg, &GAME_TimerDialogSetSpeedmy, reinterpret_cast<void**>(&GAME_TimerDialogSetSpeedold));
		MH_EnableHook(GAME_TimerDialogSetSpeedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TimerDialogSetTimeColor", FALSE))
	{
		GAME_TimerDialogSetTimeColororg = (GAME_TimerDialogSetTimeColor) ((DWORD) GameDll + 0x3CBED0);
		MH_CreateHook(GAME_TimerDialogSetTimeColororg, &GAME_TimerDialogSetTimeColormy, reinterpret_cast<void**>(&GAME_TimerDialogSetTimeColorold));
		MH_EnableHook(GAME_TimerDialogSetTimeColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TimerDialogSetTitle", FALSE))
	{
		GAME_TimerDialogSetTitleorg = (GAME_TimerDialogSetTitle) ((DWORD) GameDll + 0x3CBE50);
		MH_CreateHook(GAME_TimerDialogSetTitleorg, &GAME_TimerDialogSetTitlemy, reinterpret_cast<void**>(&GAME_TimerDialogSetTitleold));
		MH_EnableHook(GAME_TimerDialogSetTitleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TimerDialogSetTitleColor", FALSE))
	{
		GAME_TimerDialogSetTitleColororg = (GAME_TimerDialogSetTitleColor) ((DWORD) GameDll + 0x3CBE80);
		MH_CreateHook(GAME_TimerDialogSetTitleColororg, &GAME_TimerDialogSetTitleColormy, reinterpret_cast<void**>(&GAME_TimerDialogSetTitleColorold));
		MH_EnableHook(GAME_TimerDialogSetTitleColororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TimerGetElapsed", FALSE))
	{
		GAME_TimerGetElapsedorg = (GAME_TimerGetElapsed) ((DWORD) GameDll + 0x3C13A0);
		MH_CreateHook(GAME_TimerGetElapsedorg, &GAME_TimerGetElapsedmy, reinterpret_cast<void**>(&GAME_TimerGetElapsedold));
		MH_EnableHook(GAME_TimerGetElapsedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TimerGetRemaining", FALSE))
	{
		GAME_TimerGetRemainingorg = (GAME_TimerGetRemaining) ((DWORD) GameDll + 0x3C13C0);
		MH_CreateHook(GAME_TimerGetRemainingorg, &GAME_TimerGetRemainingmy, reinterpret_cast<void**>(&GAME_TimerGetRemainingold));
		MH_EnableHook(GAME_TimerGetRemainingorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TimerGetTimeout", FALSE))
	{
		GAME_TimerGetTimeoutorg = (GAME_TimerGetTimeout) ((DWORD) GameDll + 0x3C13E0);
		MH_CreateHook(GAME_TimerGetTimeoutorg, &GAME_TimerGetTimeoutmy, reinterpret_cast<void**>(&GAME_TimerGetTimeoutold));
		MH_EnableHook(GAME_TimerGetTimeoutorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TimerStart", FALSE))
	{
		GAME_TimerStartorg = (GAME_TimerStart) ((DWORD) GameDll + 0x3C1370);
		MH_CreateHook(GAME_TimerStartorg, &GAME_TimerStartmy, reinterpret_cast<void**>(&GAME_TimerStartold));
		MH_EnableHook(GAME_TimerStartorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TownHasHall", FALSE))
	{
		GAME_TownHasHallorg = (GAME_TownHasHall) ((DWORD) GameDll + 0x2DE0A0);
		MH_CreateHook(GAME_TownHasHallorg, &GAME_TownHasHallmy, reinterpret_cast<void**>(&GAME_TownHasHallold));
		MH_EnableHook(GAME_TownHasHallorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TownHasMine", FALSE))
	{
		GAME_TownHasMineorg = (GAME_TownHasMine) ((DWORD) GameDll + 0x2DE060);
		MH_CreateHook(GAME_TownHasMineorg, &GAME_TownHasMinemy, reinterpret_cast<void**>(&GAME_TownHasMineold));
		MH_EnableHook(GAME_TownHasMineorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TownThreatened", FALSE))
	{
		GAME_TownThreatenedorg = (GAME_TownThreatened) ((DWORD) GameDll + 0x2DD8E0);
		MH_CreateHook(GAME_TownThreatenedorg, &GAME_TownThreatenedmy, reinterpret_cast<void**>(&GAME_TownThreatenedold));
		MH_EnableHook(GAME_TownThreatenedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TownWithMine", FALSE))
	{
		GAME_TownWithMineorg = (GAME_TownWithMine) ((DWORD) GameDll + 0x2DE030);
		MH_CreateHook(GAME_TownWithMineorg, &GAME_TownWithMinemy, reinterpret_cast<void**>(&GAME_TownWithMineold));
		MH_EnableHook(GAME_TownWithMineorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerAddAction", FALSE))
	{
		GAME_TriggerAddActionorg = (GAME_TriggerAddAction) ((DWORD) GameDll + 0x3C3E90);
		MH_CreateHook(GAME_TriggerAddActionorg, &GAME_TriggerAddActionmy, reinterpret_cast<void**>(&GAME_TriggerAddActionold));
		MH_EnableHook(GAME_TriggerAddActionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerAddCondition", FALSE))
	{
		GAME_TriggerAddConditionorg = (GAME_TriggerAddCondition) ((DWORD) GameDll + 0x3C3DF0);
		MH_CreateHook(GAME_TriggerAddConditionorg, &GAME_TriggerAddConditionmy, reinterpret_cast<void**>(&GAME_TriggerAddConditionold));
		MH_EnableHook(GAME_TriggerAddConditionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerClearActions", FALSE))
	{
		GAME_TriggerClearActionsorg = (GAME_TriggerClearActions) ((DWORD) GameDll + 0x3C3F00);
		MH_CreateHook(GAME_TriggerClearActionsorg, &GAME_TriggerClearActionsmy, reinterpret_cast<void**>(&GAME_TriggerClearActionsold));
		MH_EnableHook(GAME_TriggerClearActionsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerClearConditions", FALSE))
	{
		GAME_TriggerClearConditionsorg = (GAME_TriggerClearConditions) ((DWORD) GameDll + 0x3C3E70);
		MH_CreateHook(GAME_TriggerClearConditionsorg, &GAME_TriggerClearConditionsmy, reinterpret_cast<void**>(&GAME_TriggerClearConditionsold));
		MH_EnableHook(GAME_TriggerClearConditionsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerEvaluate", FALSE))
	{
		GAME_TriggerEvaluateorg = (GAME_TriggerEvaluate) ((DWORD) GameDll + 0x3C3F80);
		MH_CreateHook(GAME_TriggerEvaluateorg, &GAME_TriggerEvaluatemy, reinterpret_cast<void**>(&GAME_TriggerEvaluateold));
		MH_EnableHook(GAME_TriggerEvaluateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerExecute", FALSE))
	{
		GAME_TriggerExecuteorg = (GAME_TriggerExecute) ((DWORD) GameDll + 0x3C3F40);
		MH_CreateHook(GAME_TriggerExecuteorg, &GAME_TriggerExecutemy, reinterpret_cast<void**>(&GAME_TriggerExecuteold));
		MH_EnableHook(GAME_TriggerExecuteorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerExecuteWait", FALSE))
	{
		GAME_TriggerExecuteWaitorg = (GAME_TriggerExecuteWait) ((DWORD) GameDll + 0x3C3F60);
		MH_CreateHook(GAME_TriggerExecuteWaitorg, &GAME_TriggerExecuteWaitmy, reinterpret_cast<void**>(&GAME_TriggerExecuteWaitold));
		MH_EnableHook(GAME_TriggerExecuteWaitorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterDeathEvent", FALSE))
	{
		GAME_TriggerRegisterDeathEventorg = (GAME_TriggerRegisterDeathEvent) ((DWORD) GameDll + 0x3D22C0);
		MH_CreateHook(GAME_TriggerRegisterDeathEventorg, &GAME_TriggerRegisterDeathEventmy, reinterpret_cast<void**>(&GAME_TriggerRegisterDeathEventold));
		MH_EnableHook(GAME_TriggerRegisterDeathEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterDialogButtonEvent", FALSE))
	{
		GAME_TriggerRegisterDialogButtonEventorg = (GAME_TriggerRegisterDialogButtonEvent) ((DWORD) GameDll + 0x3D1880);
		MH_CreateHook(GAME_TriggerRegisterDialogButtonEventorg, &GAME_TriggerRegisterDialogButtonEventmy, reinterpret_cast<void**>(&GAME_TriggerRegisterDialogButtonEventold));
		MH_EnableHook(GAME_TriggerRegisterDialogButtonEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterDialogEvent", FALSE))
	{
		GAME_TriggerRegisterDialogEventorg = (GAME_TriggerRegisterDialogEvent) ((DWORD) GameDll + 0x3D17A0);
		MH_CreateHook(GAME_TriggerRegisterDialogEventorg, &GAME_TriggerRegisterDialogEventmy, reinterpret_cast<void**>(&GAME_TriggerRegisterDialogEventold));
		MH_EnableHook(GAME_TriggerRegisterDialogEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterEnterRegion", FALSE))
	{
		GAME_TriggerRegisterEnterRegionorg = (GAME_TriggerRegisterEnterRegion) ((DWORD) GameDll + 0x3D2700);
		MH_CreateHook(GAME_TriggerRegisterEnterRegionorg, &GAME_TriggerRegisterEnterRegionmy, reinterpret_cast<void**>(&GAME_TriggerRegisterEnterRegionold));
		MH_EnableHook(GAME_TriggerRegisterEnterRegionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterFilterUnitEvent", FALSE))
	{
		GAME_TriggerRegisterFilterUnitEventorg = (GAME_TriggerRegisterFilterUnitEvent) ((DWORD) GameDll + 0x3D24D0);
		MH_CreateHook(GAME_TriggerRegisterFilterUnitEventorg, &GAME_TriggerRegisterFilterUnitEventmy, reinterpret_cast<void**>(&GAME_TriggerRegisterFilterUnitEventold));
		MH_EnableHook(GAME_TriggerRegisterFilterUnitEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterGameEvent", FALSE))
	{
		GAME_TriggerRegisterGameEventorg = (GAME_TriggerRegisterGameEvent) ((DWORD) GameDll + 0x3D1960);
		MH_CreateHook(GAME_TriggerRegisterGameEventorg, &GAME_TriggerRegisterGameEventmy, reinterpret_cast<void**>(&GAME_TriggerRegisterGameEventold));
		MH_EnableHook(GAME_TriggerRegisterGameEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterGameStateEvent", FALSE))
	{
		GAME_TriggerRegisterGameStateEventorg = (GAME_TriggerRegisterGameStateEvent) ((DWORD) GameDll + 0x3D1630);
		MH_CreateHook(GAME_TriggerRegisterGameStateEventorg, &GAME_TriggerRegisterGameStateEventmy, reinterpret_cast<void**>(&GAME_TriggerRegisterGameStateEventold));
		MH_EnableHook(GAME_TriggerRegisterGameStateEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterLeaveRegion", FALSE))
	{
		GAME_TriggerRegisterLeaveRegionorg = (GAME_TriggerRegisterLeaveRegion) ((DWORD) GameDll + 0x3D2800);
		MH_CreateHook(GAME_TriggerRegisterLeaveRegionorg, &GAME_TriggerRegisterLeaveRegionmy, reinterpret_cast<void**>(&GAME_TriggerRegisterLeaveRegionold));
		MH_EnableHook(GAME_TriggerRegisterLeaveRegionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterPlayerAllianceChange", FALSE))
	{
		GAME_TriggerRegisterPlayerAllianceChangeorg = (GAME_TriggerRegisterPlayerAllianceChange) ((DWORD) GameDll + 0x3D1BA0);
		MH_CreateHook(GAME_TriggerRegisterPlayerAllianceChangeorg, &GAME_TriggerRegisterPlayerAllianceChangemy, reinterpret_cast<void**>(&GAME_TriggerRegisterPlayerAllianceChangeold));
		MH_EnableHook(GAME_TriggerRegisterPlayerAllianceChangeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterPlayerChatEvent", FALSE))
	{
		GAME_TriggerRegisterPlayerChatEventorg = (GAME_TriggerRegisterPlayerChatEvent) ((DWORD) GameDll + 0x3D1EF0);
		MH_CreateHook(GAME_TriggerRegisterPlayerChatEventorg, &GAME_TriggerRegisterPlayerChatEventmy, reinterpret_cast<void**>(&GAME_TriggerRegisterPlayerChatEventold));
		MH_EnableHook(GAME_TriggerRegisterPlayerChatEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterPlayerEvent", FALSE))
	{
		GAME_TriggerRegisterPlayerEventorg = (GAME_TriggerRegisterPlayerEvent) ((DWORD) GameDll + 0x3D1C90);
		MH_CreateHook(GAME_TriggerRegisterPlayerEventorg, &GAME_TriggerRegisterPlayerEventmy, reinterpret_cast<void**>(&GAME_TriggerRegisterPlayerEventold));
		MH_EnableHook(GAME_TriggerRegisterPlayerEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterPlayerStateEvent", FALSE))
	{
		GAME_TriggerRegisterPlayerStateEventorg = (GAME_TriggerRegisterPlayerStateEvent) ((DWORD) GameDll + 0x3D1A60);
		MH_CreateHook(GAME_TriggerRegisterPlayerStateEventorg, &GAME_TriggerRegisterPlayerStateEventmy, reinterpret_cast<void**>(&GAME_TriggerRegisterPlayerStateEventold));
		MH_EnableHook(GAME_TriggerRegisterPlayerStateEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterPlayerUnitEvent", FALSE))
	{
		GAME_TriggerRegisterPlayerUnitEventorg = (GAME_TriggerRegisterPlayerUnitEvent) ((DWORD) GameDll + 0x3D1DD0);
		MH_CreateHook(GAME_TriggerRegisterPlayerUnitEventorg, &GAME_TriggerRegisterPlayerUnitEventmy, reinterpret_cast<void**>(&GAME_TriggerRegisterPlayerUnitEventold));
		MH_EnableHook(GAME_TriggerRegisterPlayerUnitEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterTimerEvent", FALSE))
	{
		GAME_TriggerRegisterTimerEventorg = (GAME_TriggerRegisterTimerEvent) ((DWORD) GameDll + 0x3D1420);
		MH_CreateHook(GAME_TriggerRegisterTimerEventorg, &GAME_TriggerRegisterTimerEventmy, reinterpret_cast<void**>(&GAME_TriggerRegisterTimerEventold));
		MH_EnableHook(GAME_TriggerRegisterTimerEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterTimerExpireEvent", FALSE))
	{
		GAME_TriggerRegisterTimerExpireEventorg = (GAME_TriggerRegisterTimerExpireEvent) ((DWORD) GameDll + 0x3D1550);
		MH_CreateHook(GAME_TriggerRegisterTimerExpireEventorg, &GAME_TriggerRegisterTimerExpireEventmy, reinterpret_cast<void**>(&GAME_TriggerRegisterTimerExpireEventold));
		MH_EnableHook(GAME_TriggerRegisterTimerExpireEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterTrackableHitEvent", FALSE))
	{
		GAME_TriggerRegisterTrackableHitEventorg = (GAME_TriggerRegisterTrackableHitEvent) ((DWORD) GameDll + 0x3D31C0);
		MH_CreateHook(GAME_TriggerRegisterTrackableHitEventorg, &GAME_TriggerRegisterTrackableHitEventmy, reinterpret_cast<void**>(&GAME_TriggerRegisterTrackableHitEventold));
		MH_EnableHook(GAME_TriggerRegisterTrackableHitEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterTrackableTrackEvent", FALSE))
	{
		GAME_TriggerRegisterTrackableTrackEventorg = (GAME_TriggerRegisterTrackableTrackEvent) ((DWORD) GameDll + 0x3D32A0);
		MH_CreateHook(GAME_TriggerRegisterTrackableTrackEventorg, &GAME_TriggerRegisterTrackableTrackEventmy, reinterpret_cast<void**>(&GAME_TriggerRegisterTrackableTrackEventold));
		MH_EnableHook(GAME_TriggerRegisterTrackableTrackEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterUnitEvent", FALSE))
	{
		GAME_TriggerRegisterUnitEventorg = (GAME_TriggerRegisterUnitEvent) ((DWORD) GameDll + 0x3D23B0);
		MH_CreateHook(GAME_TriggerRegisterUnitEventorg, &GAME_TriggerRegisterUnitEventmy, reinterpret_cast<void**>(&GAME_TriggerRegisterUnitEventold));
		MH_EnableHook(GAME_TriggerRegisterUnitEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterUnitInRange", FALSE))
	{
		GAME_TriggerRegisterUnitInRangeorg = (GAME_TriggerRegisterUnitInRange) ((DWORD) GameDll + 0x3D25F0);
		MH_CreateHook(GAME_TriggerRegisterUnitInRangeorg, &GAME_TriggerRegisterUnitInRangemy, reinterpret_cast<void**>(&GAME_TriggerRegisterUnitInRangeold));
		MH_EnableHook(GAME_TriggerRegisterUnitInRangeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterUnitStateEvent", FALSE))
	{
		GAME_TriggerRegisterUnitStateEventorg = (GAME_TriggerRegisterUnitStateEvent) ((DWORD) GameDll + 0x3D21B0);
		MH_CreateHook(GAME_TriggerRegisterUnitStateEventorg, &GAME_TriggerRegisterUnitStateEventmy, reinterpret_cast<void**>(&GAME_TriggerRegisterUnitStateEventold));
		MH_EnableHook(GAME_TriggerRegisterUnitStateEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRegisterVariableEvent", FALSE))
	{
		GAME_TriggerRegisterVariableEventorg = (GAME_TriggerRegisterVariableEvent) ((DWORD) GameDll + 0x3D12E0);
		MH_CreateHook(GAME_TriggerRegisterVariableEventorg, &GAME_TriggerRegisterVariableEventmy, reinterpret_cast<void**>(&GAME_TriggerRegisterVariableEventold));
		MH_EnableHook(GAME_TriggerRegisterVariableEventorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRemoveAction", FALSE))
	{
		GAME_TriggerRemoveActionorg = (GAME_TriggerRemoveAction) ((DWORD) GameDll + 0x3C3ED0);
		MH_CreateHook(GAME_TriggerRemoveActionorg, &GAME_TriggerRemoveActionmy, reinterpret_cast<void**>(&GAME_TriggerRemoveActionold));
		MH_EnableHook(GAME_TriggerRemoveActionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerRemoveCondition", FALSE))
	{
		GAME_TriggerRemoveConditionorg = (GAME_TriggerRemoveCondition) ((DWORD) GameDll + 0x3C3E40);
		MH_CreateHook(GAME_TriggerRemoveConditionorg, &GAME_TriggerRemoveConditionmy, reinterpret_cast<void**>(&GAME_TriggerRemoveConditionold));
		MH_EnableHook(GAME_TriggerRemoveConditionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerSleepAction", FALSE))
	{
		GAME_TriggerSleepActionorg = (GAME_TriggerSleepAction) ((DWORD) GameDll + 0x3B2DB0);
		MH_CreateHook(GAME_TriggerSleepActionorg, &GAME_TriggerSleepActionmy, reinterpret_cast<void**>(&GAME_TriggerSleepActionold));
		MH_EnableHook(GAME_TriggerSleepActionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerSyncReady", FALSE))
	{
		GAME_TriggerSyncReadyorg = (GAME_TriggerSyncReady) ((DWORD) GameDll + 0x3BB710);
		MH_CreateHook(GAME_TriggerSyncReadyorg, &GAME_TriggerSyncReadymy, reinterpret_cast<void**>(&GAME_TriggerSyncReadyold));
		MH_EnableHook(GAME_TriggerSyncReadyorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerSyncStart", FALSE))
	{
		GAME_TriggerSyncStartorg = (GAME_TriggerSyncStart) ((DWORD) GameDll + 0x3B2DC0);
		MH_CreateHook(GAME_TriggerSyncStartorg, &GAME_TriggerSyncStartmy, reinterpret_cast<void**>(&GAME_TriggerSyncStartold));
		MH_EnableHook(GAME_TriggerSyncStartorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerWaitForSound", FALSE))
	{
		GAME_TriggerWaitForSoundorg = (GAME_TriggerWaitForSound) ((DWORD) GameDll + 0x3C3F20);
		MH_CreateHook(GAME_TriggerWaitForSoundorg, &GAME_TriggerWaitForSoundmy, reinterpret_cast<void**>(&GAME_TriggerWaitForSoundold));
		MH_EnableHook(GAME_TriggerWaitForSoundorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_TriggerWaitOnSleeps", FALSE))
	{
		GAME_TriggerWaitOnSleepsorg = (GAME_TriggerWaitOnSleeps) ((DWORD) GameDll + 0x3C1CA0);
		MH_CreateHook(GAME_TriggerWaitOnSleepsorg, &GAME_TriggerWaitOnSleepsmy, reinterpret_cast<void**>(&GAME_TriggerWaitOnSleepsold));
		MH_EnableHook(GAME_TriggerWaitOnSleepsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitAddAbility", FALSE))
	{
		GAME_UnitAddAbilityorg = (GAME_UnitAddAbility) ((DWORD) GameDll + 0x3C82A0);
		MH_CreateHook(GAME_UnitAddAbilityorg, &GAME_UnitAddAbilitymy, reinterpret_cast<void**>(&GAME_UnitAddAbilityold));
		MH_EnableHook(GAME_UnitAddAbilityorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitAddIndicator", FALSE))
	{
		GAME_UnitAddIndicatororg = (GAME_UnitAddIndicator) ((DWORD) GameDll + 0x3C6BD0);
		MH_CreateHook(GAME_UnitAddIndicatororg, &GAME_UnitAddIndicatormy, reinterpret_cast<void**>(&GAME_UnitAddIndicatorold));
		MH_EnableHook(GAME_UnitAddIndicatororg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitAddItem", FALSE))
	{
		GAME_UnitAddItemorg = (GAME_UnitAddItem) ((DWORD) GameDll + 0x3C73F0);
		MH_CreateHook(GAME_UnitAddItemorg, &GAME_UnitAddItemmy, reinterpret_cast<void**>(&GAME_UnitAddItemold));
		MH_EnableHook(GAME_UnitAddItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitAddItemById", FALSE))
	{
		GAME_UnitAddItemByIdorg = (GAME_UnitAddItemById) ((DWORD) GameDll + 0x3C74F0);
		MH_CreateHook(GAME_UnitAddItemByIdorg, &GAME_UnitAddItemByIdmy, reinterpret_cast<void**>(&GAME_UnitAddItemByIdold));
		MH_EnableHook(GAME_UnitAddItemByIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitAddItemToSlotById", FALSE))
	{
		GAME_UnitAddItemToSlotByIdorg = (GAME_UnitAddItemToSlotById) ((DWORD) GameDll + 0x3C75B0);
		MH_CreateHook(GAME_UnitAddItemToSlotByIdorg, &GAME_UnitAddItemToSlotByIdmy, reinterpret_cast<void**>(&GAME_UnitAddItemToSlotByIdold));
		MH_EnableHook(GAME_UnitAddItemToSlotByIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitAddSleep", FALSE))
	{
		GAME_UnitAddSleeporg = (GAME_UnitAddSleep) ((DWORD) GameDll + 0x3C8450);
		MH_CreateHook(GAME_UnitAddSleeporg, &GAME_UnitAddSleepmy, reinterpret_cast<void**>(&GAME_UnitAddSleepold));
		MH_EnableHook(GAME_UnitAddSleeporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitAddSleepPerm", FALSE))
	{
		GAME_UnitAddSleepPermorg = (GAME_UnitAddSleepPerm) ((DWORD) GameDll + 0x3C84D0);
		MH_CreateHook(GAME_UnitAddSleepPermorg, &GAME_UnitAddSleepPermmy, reinterpret_cast<void**>(&GAME_UnitAddSleepPermold));
		MH_EnableHook(GAME_UnitAddSleepPermorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitAddType", FALSE))
	{
		GAME_UnitAddTypeorg = (GAME_UnitAddType) ((DWORD) GameDll + 0x3C7BC0);
		MH_CreateHook(GAME_UnitAddTypeorg, &GAME_UnitAddTypemy, reinterpret_cast<void**>(&GAME_UnitAddTypeold));
		MH_EnableHook(GAME_UnitAddTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitAlive", FALSE))
	{
		GAME_UnitAliveorg = (GAME_UnitAlive) ((DWORD) GameDll + 0x2E0760);
		MH_CreateHook(GAME_UnitAliveorg, &GAME_UnitAlivemy, reinterpret_cast<void**>(&GAME_UnitAliveold));
		MH_EnableHook(GAME_UnitAliveorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitApplyTimedLife", FALSE))
	{
		GAME_UnitApplyTimedLifeorg = (GAME_UnitApplyTimedLife) ((DWORD) GameDll + 0x3C85D0);
		MH_CreateHook(GAME_UnitApplyTimedLifeorg, &GAME_UnitApplyTimedLifemy, reinterpret_cast<void**>(&GAME_UnitApplyTimedLifeold));
		MH_EnableHook(GAME_UnitApplyTimedLifeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitCanSleep", FALSE))
	{
		GAME_UnitCanSleeporg = (GAME_UnitCanSleep) ((DWORD) GameDll + 0x3C84A0);
		MH_CreateHook(GAME_UnitCanSleeporg, &GAME_UnitCanSleepmy, reinterpret_cast<void**>(&GAME_UnitCanSleepold));
		MH_EnableHook(GAME_UnitCanSleeporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitCanSleepPerm", FALSE))
	{
		GAME_UnitCanSleepPermorg = (GAME_UnitCanSleepPerm) ((DWORD) GameDll + 0x3C8520);
		MH_CreateHook(GAME_UnitCanSleepPermorg, &GAME_UnitCanSleepPermmy, reinterpret_cast<void**>(&GAME_UnitCanSleepPermold));
		MH_EnableHook(GAME_UnitCanSleepPermorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitCountBuffsEx", FALSE))
	{
		GAME_UnitCountBuffsExorg = (GAME_UnitCountBuffsEx) ((DWORD) GameDll + 0x3C83A0);
		MH_CreateHook(GAME_UnitCountBuffsExorg, &GAME_UnitCountBuffsExmy, reinterpret_cast<void**>(&GAME_UnitCountBuffsExold));
		MH_EnableHook(GAME_UnitCountBuffsExorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitDamagePoint", FALSE))
	{
		GAME_UnitDamagePointorg = (GAME_UnitDamagePoint) ((DWORD) GameDll + 0x3C8770);
		MH_CreateHook(GAME_UnitDamagePointorg, &GAME_UnitDamagePointmy, reinterpret_cast<void**>(&GAME_UnitDamagePointold));
		MH_EnableHook(GAME_UnitDamagePointorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitDamageTarget", FALSE))
	{
		GAME_UnitDamageTargetorg = (GAME_UnitDamageTarget) ((DWORD) GameDll + 0x3C8850);
		MH_CreateHook(GAME_UnitDamageTargetorg, &GAME_UnitDamageTargetmy, reinterpret_cast<void**>(&GAME_UnitDamageTargetold));
		MH_EnableHook(GAME_UnitDamageTargetorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitDropItemPoint", FALSE))
	{
		GAME_UnitDropItemPointorg = (GAME_UnitDropItemPoint) ((DWORD) GameDll + 0x3C8F30);
		MH_CreateHook(GAME_UnitDropItemPointorg, &GAME_UnitDropItemPointmy, reinterpret_cast<void**>(&GAME_UnitDropItemPointold));
		MH_EnableHook(GAME_UnitDropItemPointorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitDropItemSlot", FALSE))
	{
		GAME_UnitDropItemSlotorg = (GAME_UnitDropItemSlot) ((DWORD) GameDll + 0x3C9010);
		MH_CreateHook(GAME_UnitDropItemSlotorg, &GAME_UnitDropItemSlotmy, reinterpret_cast<void**>(&GAME_UnitDropItemSlotold));
		MH_EnableHook(GAME_UnitDropItemSlotorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitDropItemTarget", FALSE))
	{
		GAME_UnitDropItemTargetorg = (GAME_UnitDropItemTarget) ((DWORD) GameDll + 0x3C8FA0);
		MH_CreateHook(GAME_UnitDropItemTargetorg, &GAME_UnitDropItemTargetmy, reinterpret_cast<void**>(&GAME_UnitDropItemTargetold));
		MH_EnableHook(GAME_UnitDropItemTargetorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitHasBuffsEx", FALSE))
	{
		GAME_UnitHasBuffsExorg = (GAME_UnitHasBuffsEx) ((DWORD) GameDll + 0x3C8360);
		MH_CreateHook(GAME_UnitHasBuffsExorg, &GAME_UnitHasBuffsExmy, reinterpret_cast<void**>(&GAME_UnitHasBuffsExold));
		MH_EnableHook(GAME_UnitHasBuffsExorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitHasItem", FALSE))
	{
		GAME_UnitHasItemorg = (GAME_UnitHasItem) ((DWORD) GameDll + 0x3C76F0);
		MH_CreateHook(GAME_UnitHasItemorg, &GAME_UnitHasItemmy, reinterpret_cast<void**>(&GAME_UnitHasItemold));
		MH_EnableHook(GAME_UnitHasItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitId", FALSE))
	{
		GAME_UnitIdorg = (GAME_UnitId) ((DWORD) GameDll + 0x3BB650);
		MH_CreateHook(GAME_UnitIdorg, &GAME_UnitIdmy, reinterpret_cast<void**>(&GAME_UnitIdold));
		MH_EnableHook(GAME_UnitIdorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitId2String", FALSE))
	{
		GAME_UnitId2Stringorg = (GAME_UnitId2String) ((DWORD) GameDll + 0x3BB680);
		MH_CreateHook(GAME_UnitId2Stringorg, &GAME_UnitId2Stringmy, reinterpret_cast<void**>(&GAME_UnitId2Stringold));
		MH_EnableHook(GAME_UnitId2Stringorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitIgnoreAlarm", FALSE))
	{
		GAME_UnitIgnoreAlarmorg = (GAME_UnitIgnoreAlarm) ((DWORD) GameDll + 0x3C8640);
		MH_CreateHook(GAME_UnitIgnoreAlarmorg, &GAME_UnitIgnoreAlarmmy, reinterpret_cast<void**>(&GAME_UnitIgnoreAlarmold));
		MH_EnableHook(GAME_UnitIgnoreAlarmorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitIgnoreAlarmToggled", FALSE))
	{
		GAME_UnitIgnoreAlarmToggledorg = (GAME_UnitIgnoreAlarmToggled) ((DWORD) GameDll + 0x3C8690);
		MH_CreateHook(GAME_UnitIgnoreAlarmToggledorg, &GAME_UnitIgnoreAlarmToggledmy, reinterpret_cast<void**>(&GAME_UnitIgnoreAlarmToggledold));
		MH_EnableHook(GAME_UnitIgnoreAlarmToggledorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitInventorySize", FALSE))
	{
		GAME_UnitInventorySizeorg = (GAME_UnitInventorySize) ((DWORD) GameDll + 0x3C8F00);
		MH_CreateHook(GAME_UnitInventorySizeorg, &GAME_UnitInventorySizemy, reinterpret_cast<void**>(&GAME_UnitInventorySizeold));
		MH_EnableHook(GAME_UnitInventorySizeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitInvis", FALSE))
	{
		GAME_UnitInvisorg = (GAME_UnitInvis) ((DWORD) GameDll + 0x2E07C0);
		MH_CreateHook(GAME_UnitInvisorg, &GAME_UnitInvismy, reinterpret_cast<void**>(&GAME_UnitInvisold));
		MH_EnableHook(GAME_UnitInvisorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitIsSleeping", FALSE))
	{
		GAME_UnitIsSleepingorg = (GAME_UnitIsSleeping) ((DWORD) GameDll + 0x3C8550);
		MH_CreateHook(GAME_UnitIsSleepingorg, &GAME_UnitIsSleepingmy, reinterpret_cast<void**>(&GAME_UnitIsSleepingold));
		MH_EnableHook(GAME_UnitIsSleepingorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitItemInSlot", FALSE))
	{
		GAME_UnitItemInSlotorg = (GAME_UnitItemInSlot) ((DWORD) GameDll + 0x3C7730);
		MH_CreateHook(GAME_UnitItemInSlotorg, &GAME_UnitItemInSlotmy, reinterpret_cast<void**>(&GAME_UnitItemInSlotold));
		MH_EnableHook(GAME_UnitItemInSlotorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitMakeAbilityPermanent", FALSE))
	{
		GAME_UnitMakeAbilityPermanentorg = (GAME_UnitMakeAbilityPermanent) ((DWORD) GameDll + 0x3C8250);
		MH_CreateHook(GAME_UnitMakeAbilityPermanentorg, &GAME_UnitMakeAbilityPermanentmy, reinterpret_cast<void**>(&GAME_UnitMakeAbilityPermanentold));
		MH_EnableHook(GAME_UnitMakeAbilityPermanentorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitModifySkillPoints", FALSE))
	{
		GAME_UnitModifySkillPointsorg = (GAME_UnitModifySkillPoints) ((DWORD) GameDll + 0x3C69A0);
		MH_CreateHook(GAME_UnitModifySkillPointsorg, &GAME_UnitModifySkillPointsmy, reinterpret_cast<void**>(&GAME_UnitModifySkillPointsold));
		MH_EnableHook(GAME_UnitModifySkillPointsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitPauseTimedLife", FALSE))
	{
		GAME_UnitPauseTimedLifeorg = (GAME_UnitPauseTimedLife) ((DWORD) GameDll + 0x3C8750);
		MH_CreateHook(GAME_UnitPauseTimedLifeorg, &GAME_UnitPauseTimedLifemy, reinterpret_cast<void**>(&GAME_UnitPauseTimedLifeold));
		MH_EnableHook(GAME_UnitPauseTimedLifeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitPoolAddUnitType", FALSE))
	{
		GAME_UnitPoolAddUnitTypeorg = (GAME_UnitPoolAddUnitType) ((DWORD) GameDll + 0x3CB5E0);
		MH_CreateHook(GAME_UnitPoolAddUnitTypeorg, &GAME_UnitPoolAddUnitTypemy, reinterpret_cast<void**>(&GAME_UnitPoolAddUnitTypeold));
		MH_EnableHook(GAME_UnitPoolAddUnitTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitPoolRemoveUnitType", FALSE))
	{
		GAME_UnitPoolRemoveUnitTypeorg = (GAME_UnitPoolRemoveUnitType) ((DWORD) GameDll + 0x3CB600);
		MH_CreateHook(GAME_UnitPoolRemoveUnitTypeorg, &GAME_UnitPoolRemoveUnitTypemy, reinterpret_cast<void**>(&GAME_UnitPoolRemoveUnitTypeold));
		MH_EnableHook(GAME_UnitPoolRemoveUnitTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitRemoveAbility", FALSE))
	{
		GAME_UnitRemoveAbilityorg = (GAME_UnitRemoveAbility) ((DWORD) GameDll + 0x3C8310);
		MH_CreateHook(GAME_UnitRemoveAbilityorg, &GAME_UnitRemoveAbilitymy, reinterpret_cast<void**>(&GAME_UnitRemoveAbilityold));
		MH_EnableHook(GAME_UnitRemoveAbilityorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitRemoveBuffs", FALSE))
	{
		GAME_UnitRemoveBuffsorg = (GAME_UnitRemoveBuffs) ((DWORD) GameDll + 0x3C83E0);
		MH_CreateHook(GAME_UnitRemoveBuffsorg, &GAME_UnitRemoveBuffsmy, reinterpret_cast<void**>(&GAME_UnitRemoveBuffsold));
		MH_EnableHook(GAME_UnitRemoveBuffsorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitRemoveBuffsEx", FALSE))
	{
		GAME_UnitRemoveBuffsExorg = (GAME_UnitRemoveBuffsEx) ((DWORD) GameDll + 0x3C8410);
		MH_CreateHook(GAME_UnitRemoveBuffsExorg, &GAME_UnitRemoveBuffsExmy, reinterpret_cast<void**>(&GAME_UnitRemoveBuffsExold));
		MH_EnableHook(GAME_UnitRemoveBuffsExorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitRemoveItem", FALSE))
	{
		GAME_UnitRemoveItemorg = (GAME_UnitRemoveItem) ((DWORD) GameDll + 0x3C7660);
		MH_CreateHook(GAME_UnitRemoveItemorg, &GAME_UnitRemoveItemmy, reinterpret_cast<void**>(&GAME_UnitRemoveItemold));
		MH_EnableHook(GAME_UnitRemoveItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitRemoveItemFromSlot", FALSE))
	{
		GAME_UnitRemoveItemFromSlotorg = (GAME_UnitRemoveItemFromSlot) ((DWORD) GameDll + 0x3C76A0);
		MH_CreateHook(GAME_UnitRemoveItemFromSlotorg, &GAME_UnitRemoveItemFromSlotmy, reinterpret_cast<void**>(&GAME_UnitRemoveItemFromSlotold));
		MH_EnableHook(GAME_UnitRemoveItemFromSlotorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitRemoveType", FALSE))
	{
		GAME_UnitRemoveTypeorg = (GAME_UnitRemoveType) ((DWORD) GameDll + 0x3C7C20);
		MH_CreateHook(GAME_UnitRemoveTypeorg, &GAME_UnitRemoveTypemy, reinterpret_cast<void**>(&GAME_UnitRemoveTypeold));
		MH_EnableHook(GAME_UnitRemoveTypeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitResetCooldown", FALSE))
	{
		GAME_UnitResetCooldownorg = (GAME_UnitResetCooldown) ((DWORD) GameDll + 0x3C86D0);
		MH_CreateHook(GAME_UnitResetCooldownorg, &GAME_UnitResetCooldownmy, reinterpret_cast<void**>(&GAME_UnitResetCooldownold));
		MH_EnableHook(GAME_UnitResetCooldownorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitSetConstructionProgress", FALSE))
	{
		GAME_UnitSetConstructionProgressorg = (GAME_UnitSetConstructionProgress) ((DWORD) GameDll + 0x3C86F0);
		MH_CreateHook(GAME_UnitSetConstructionProgressorg, &GAME_UnitSetConstructionProgressmy, reinterpret_cast<void**>(&GAME_UnitSetConstructionProgressold));
		MH_EnableHook(GAME_UnitSetConstructionProgressorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitSetUpgradeProgress", FALSE))
	{
		GAME_UnitSetUpgradeProgressorg = (GAME_UnitSetUpgradeProgress) ((DWORD) GameDll + 0x3C8720);
		MH_CreateHook(GAME_UnitSetUpgradeProgressorg, &GAME_UnitSetUpgradeProgressmy, reinterpret_cast<void**>(&GAME_UnitSetUpgradeProgressold));
		MH_EnableHook(GAME_UnitSetUpgradeProgressorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitSetUsesAltIcon", FALSE))
	{
		GAME_UnitSetUsesAltIconorg = (GAME_UnitSetUsesAltIcon) ((DWORD) GameDll + 0x3CB860);
		MH_CreateHook(GAME_UnitSetUsesAltIconorg, &GAME_UnitSetUsesAltIconmy, reinterpret_cast<void**>(&GAME_UnitSetUsesAltIconold));
		MH_EnableHook(GAME_UnitSetUsesAltIconorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitShareVision", FALSE))
	{
		GAME_UnitShareVisionorg = (GAME_UnitShareVision) ((DWORD) GameDll + 0x3C81C0);
		MH_CreateHook(GAME_UnitShareVisionorg, &GAME_UnitShareVisionmy, reinterpret_cast<void**>(&GAME_UnitShareVisionold));
		MH_EnableHook(GAME_UnitShareVisionorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitStripHeroLevel", FALSE))
	{
		GAME_UnitStripHeroLevelorg = (GAME_UnitStripHeroLevel) ((DWORD) GameDll + 0x3C6930);
		MH_CreateHook(GAME_UnitStripHeroLevelorg, &GAME_UnitStripHeroLevelmy, reinterpret_cast<void**>(&GAME_UnitStripHeroLevelold));
		MH_EnableHook(GAME_UnitStripHeroLevelorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitSuspendDecay", FALSE))
	{
		GAME_UnitSuspendDecayorg = (GAME_UnitSuspendDecay) ((DWORD) GameDll + 0x3C81F0);
		MH_CreateHook(GAME_UnitSuspendDecayorg, &GAME_UnitSuspendDecaymy, reinterpret_cast<void**>(&GAME_UnitSuspendDecayold));
		MH_EnableHook(GAME_UnitSuspendDecayorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitUseItem", FALSE))
	{
		GAME_UnitUseItemorg = (GAME_UnitUseItem) ((DWORD) GameDll + 0x3C9090);
		MH_CreateHook(GAME_UnitUseItemorg, &GAME_UnitUseItemmy, reinterpret_cast<void**>(&GAME_UnitUseItemold));
		MH_EnableHook(GAME_UnitUseItemorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitUseItemPoint", FALSE))
	{
		GAME_UnitUseItemPointorg = (GAME_UnitUseItemPoint) ((DWORD) GameDll + 0x3C9100);
		MH_CreateHook(GAME_UnitUseItemPointorg, &GAME_UnitUseItemPointmy, reinterpret_cast<void**>(&GAME_UnitUseItemPointold));
		MH_EnableHook(GAME_UnitUseItemPointorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitUseItemTarget", FALSE))
	{
		GAME_UnitUseItemTargetorg = (GAME_UnitUseItemTarget) ((DWORD) GameDll + 0x3C9170);
		MH_CreateHook(GAME_UnitUseItemTargetorg, &GAME_UnitUseItemTargetmy, reinterpret_cast<void**>(&GAME_UnitUseItemTargetold));
		MH_EnableHook(GAME_UnitUseItemTargetorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnitWakeUp", FALSE))
	{
		GAME_UnitWakeUporg = (GAME_UnitWakeUp) ((DWORD) GameDll + 0x3C8590);
		MH_CreateHook(GAME_UnitWakeUporg, &GAME_UnitWakeUpmy, reinterpret_cast<void**>(&GAME_UnitWakeUpold));
		MH_EnableHook(GAME_UnitWakeUporg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_UnregisterStackedSound", FALSE))
	{
		GAME_UnregisterStackedSoundorg = (GAME_UnregisterStackedSound) ((DWORD) GameDll + 0x3CCFB0);
		MH_CreateHook(GAME_UnregisterStackedSoundorg, &GAME_UnregisterStackedSoundmy, reinterpret_cast<void**>(&GAME_UnregisterStackedSoundold));
		MH_EnableHook(GAME_UnregisterStackedSoundorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_Unsummon", FALSE))
	{
		GAME_Unsummonorg = (GAME_Unsummon) ((DWORD) GameDll + 0x2E08A0);
		MH_CreateHook(GAME_Unsummonorg, &GAME_Unsummonmy, reinterpret_cast<void**>(&GAME_Unsummonold));
		MH_EnableHook(GAME_Unsummonorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_VersionCompatible", FALSE))
	{
		GAME_VersionCompatibleorg = (GAME_VersionCompatible) ((DWORD) GameDll + 0x3B3300);
		MH_CreateHook(GAME_VersionCompatibleorg, &GAME_VersionCompatiblemy, reinterpret_cast<void**>(&GAME_VersionCompatibleold));
		MH_EnableHook(GAME_VersionCompatibleorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_VersionGet", FALSE))
	{
		GAME_VersionGetorg = (GAME_VersionGet) ((DWORD) GameDll + 0x3B32F0);
		MH_CreateHook(GAME_VersionGetorg, &GAME_VersionGetmy, reinterpret_cast<void**>(&GAME_VersionGetold));
		MH_EnableHook(GAME_VersionGetorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_VersionSupported", FALSE))
	{
		GAME_VersionSupportedorg = (GAME_VersionSupported) ((DWORD) GameDll + 0x3B3310);
		MH_CreateHook(GAME_VersionSupportedorg, &GAME_VersionSupportedmy, reinterpret_cast<void**>(&GAME_VersionSupportedold));
		MH_EnableHook(GAME_VersionSupportedorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_VolumeGroupReset", FALSE))
	{
		GAME_VolumeGroupResetorg = (GAME_VolumeGroupReset) ((DWORD) GameDll + 0x3B3E50);
		MH_CreateHook(GAME_VolumeGroupResetorg, &GAME_VolumeGroupResetmy, reinterpret_cast<void**>(&GAME_VolumeGroupResetold));
		MH_EnableHook(GAME_VolumeGroupResetorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_VolumeGroupSetVolume", FALSE))
	{
		GAME_VolumeGroupSetVolumeorg = (GAME_VolumeGroupSetVolume) ((DWORD) GameDll + 0x3B3E30);
		MH_CreateHook(GAME_VolumeGroupSetVolumeorg, &GAME_VolumeGroupSetVolumemy, reinterpret_cast<void**>(&GAME_VolumeGroupSetVolumeold));
		MH_EnableHook(GAME_VolumeGroupSetVolumeorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_WaitGetEnemyBase", FALSE))
	{
		GAME_WaitGetEnemyBaseorg = (GAME_WaitGetEnemyBase) ((DWORD) GameDll + 0x2DDCF0);
		MH_CreateHook(GAME_WaitGetEnemyBaseorg, &GAME_WaitGetEnemyBasemy, reinterpret_cast<void**>(&GAME_WaitGetEnemyBaseold));
		MH_EnableHook(GAME_WaitGetEnemyBaseorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_WaygateActivate", FALSE))
	{
		GAME_WaygateActivateorg = (GAME_WaygateActivate) ((DWORD) GameDll + 0x3C92D0);
		MH_CreateHook(GAME_WaygateActivateorg, &GAME_WaygateActivatemy, reinterpret_cast<void**>(&GAME_WaygateActivateold));
		MH_EnableHook(GAME_WaygateActivateorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_WaygateGetDestinationX", FALSE))
	{
		GAME_WaygateGetDestinationXorg = (GAME_WaygateGetDestinationX) ((DWORD) GameDll + 0x3C91F0);
		MH_CreateHook(GAME_WaygateGetDestinationXorg, &GAME_WaygateGetDestinationXmy, reinterpret_cast<void**>(&GAME_WaygateGetDestinationXold));
		MH_EnableHook(GAME_WaygateGetDestinationXorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_WaygateGetDestinationY", FALSE))
	{
		GAME_WaygateGetDestinationYorg = (GAME_WaygateGetDestinationY) ((DWORD) GameDll + 0x3C9240);
		MH_CreateHook(GAME_WaygateGetDestinationYorg, &GAME_WaygateGetDestinationYmy, reinterpret_cast<void**>(&GAME_WaygateGetDestinationYold));
		MH_EnableHook(GAME_WaygateGetDestinationYorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_WaygateIsActive", FALSE))
	{
		GAME_WaygateIsActiveorg = (GAME_WaygateIsActive) ((DWORD) GameDll + 0x3C9310);
		MH_CreateHook(GAME_WaygateIsActiveorg, &GAME_WaygateIsActivemy, reinterpret_cast<void**>(&GAME_WaygateIsActiveold));
		MH_EnableHook(GAME_WaygateIsActiveorg);
		Sleep(1);
	}


	if (JassINI.ReadBOOLean("JASS_SPY_BY_ABSOL_D3SCENE", "GAME_WaygateSetDestination", FALSE))
	{
		GAME_WaygateSetDestinationorg = (GAME_WaygateSetDestination) ((DWORD) GameDll + 0x3C9290);
		MH_CreateHook(GAME_WaygateSetDestinationorg, &GAME_WaygateSetDestinationmy, reinterpret_cast<void**>(&GAME_WaygateSetDestinationold));
		MH_EnableHook(GAME_WaygateSetDestinationorg);
		Sleep(1);
	}



	}