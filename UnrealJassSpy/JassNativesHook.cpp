#include <Windows.h>
#include <string>
#include "JassDefineHeader.h"
#include "JassNativesHeader.h"
#include "INIReader.h"
#include "MinHook.h"
#pragma comment(lib, "libMinHook.x86.lib")
#include <iostream>
#include <sstream>
#include <fstream>
#include <dbghelp.h>
#pragma comment(lib,"Dbghelp.lib")

class SymInit
{
public:
	SymInit( void ) : process_( GetCurrentProcess( ) )
	{
		SymInitialize( process_ , 0 , TRUE );

		DWORD options = SymGetOptions( );
		options |= SYMOPT_LOAD_LINES;
		SymSetOptions( options );
	}
	~SymInit( )
	{
		SymCleanup( process_ );
	}
private:
	HANDLE process_;
	SymInit( const SymInit & );
	SymInit & operator=( const SymInit & );
};

std::string get_module_path( HMODULE module = 0 )
{
	char path_name[ MAX_PATH ] = { };
	DWORD size = GetModuleFileNameA( module , path_name , MAX_PATH );
	return std::string( path_name , size );
}

void write_module_name( std::ostream & os , HANDLE process , DWORD64 program_counter )
{
	DWORD64 module_base = SymGetModuleBase64( process , program_counter );
	if ( module_base )
	{
		std::string module_name = get_module_path( reinterpret_cast< HMODULE >( module_base ) );
		if ( !module_name.empty( ) )
			os << module_name << "|";
		else
			os << "Unknown module|";
	}
	else
	{
		os << "Unknown module|";
	}
}

void write_function_name( std::ostream & os , HANDLE process , DWORD64 program_counter )
{
	SYMBOL_INFO_PACKAGE sym = { sizeof( sym ) };
	sym.si.MaxNameLen = MAX_SYM_NAME;
	if ( SymFromAddr( process , program_counter , 0 , &sym.si ) )
	{
		os << sym.si.Name << "()";
	}
	else
	{
		os << "Unknown function";
	}
}

void write_file_and_line( std::ostream & os , HANDLE process , DWORD64 program_counter )
{
	IMAGEHLP_LINE64 ih_line = { sizeof( IMAGEHLP_LINE64 ) };
	DWORD dummy = 0;
	if ( SymGetLineFromAddr64( process , program_counter , &dummy , &ih_line ) )
	{
		os << "|" << ih_line.FileName
			<< ":" << ih_line.LineNumber;
	}
}

void generate_stack_trace( std::ostream & os , CONTEXT ctx , int skip )
{
	STACKFRAME64 sf = { };
	sf.AddrPC.Offset = ctx.Eip;
	sf.AddrPC.Mode = AddrModeFlat;
	sf.AddrStack.Offset = ctx.Esp;
	sf.AddrStack.Mode = AddrModeFlat;
	sf.AddrFrame.Offset = ctx.Ebp;
	sf.AddrFrame.Mode = AddrModeFlat;

	HANDLE process = GetCurrentProcess( );
	HANDLE thread = GetCurrentThread( );

	os << std::uppercase;
	for ( ;; )
	{
		SetLastError( 0 );
		BOOL stack_walk_ok = StackWalk64( IMAGE_FILE_MACHINE_I386 , process , thread , &sf ,
										  &ctx , 0 , &SymFunctionTableAccess64 ,
										  &SymGetModuleBase64 , 0 );
		if ( !stack_walk_ok || !sf.AddrFrame.Offset ) return;

		if ( skip )
		{
			--skip;
		}
		else
		{
			// write the address
			os << std::hex << reinterpret_cast< void * >( sf.AddrPC.Offset ) << "|" << std::dec;

			write_module_name( os , process , sf.AddrPC.Offset );
			write_function_name( os , process , sf.AddrPC.Offset );
			write_file_and_line( os , process , sf.AddrPC.Offset );

			os << "\n";
		}
	}
}
struct UntypedException
{
	UntypedException( const EXCEPTION_RECORD & er )
	: exception_object( reinterpret_cast< void * >( er.ExceptionInformation[ 1 ] ) ) ,
	type_array( reinterpret_cast< _ThrowInfo * >( er.ExceptionInformation[ 2 ] )->pCatchableTypeArray )
	{ }
	void * exception_object;
	_CatchableTypeArray * type_array;
};
void * exception_cast_worker( const UntypedException & e , const type_info & ti )
{
	for ( int i = 0; i < e.type_array->nCatchableTypes; ++i )
	{
		_CatchableType & type_i = *e.type_array->arrayOfCatchableTypes[ i ];
		const std::type_info & ti_i = *reinterpret_cast< std::type_info * >( type_i.pType );
		if ( ti_i == ti )
		{
			char * base_address = reinterpret_cast< char * >( e.exception_object );
			base_address += type_i.thisDisplacement.mdisp;
			return base_address;
		}
	}
	return 0;
}

void get_exception_types( std::ostream & os , const UntypedException & e )
{
	for ( int i = 0; i < e.type_array->nCatchableTypes; ++i )
	{
		_CatchableType & type_i = *e.type_array->arrayOfCatchableTypes[ i ];
		const std::type_info & ti_i = *reinterpret_cast< std::type_info * >( type_i.pType );
		os << ti_i.name( ) << "\n";
	}
}

template <typename T>
T * exception_cast( const UntypedException & e )
{
	const std::type_info & ti = typeid( T );
	return reinterpret_cast< T * >( exception_cast_worker( e , ti ) );
}

DWORD do_filter( EXCEPTION_POINTERS * eps , std::string & buffer )
{
	std::stringstream sstr;
	const EXCEPTION_RECORD & er = *eps->ExceptionRecord;
	int skip = 0;
	sstr << "	JassSpy Exception Handler v0.1   \n\n";
	sstr << "   Search next jass function:" << funcname2 << "\n";
	sstr << "      Latest called function:" << funcname1 << "\n";
	switch ( er.ExceptionCode )
	{
		case 0xE06D7363: { // C++ exception
							 UntypedException ue( er );
							 if ( std::exception * e = exception_cast< std::exception >( ue ) )
							 {
								 const std::type_info & ti = typeid( *e );
								 sstr << ti.name( ) << ":" << e->what( );
							 }
							 else
							 {
								 sstr << "Unknown C++ exception thrown.\n";
								 get_exception_types( sstr , ue );
							 }
							 skip = 2; // skip RaiseException and _CxxThrowException
		} break;
		case EXCEPTION_ACCESS_VIOLATION: {
											 sstr << "Access violation. Illegal "
												 << ( er.ExceptionInformation[ 0 ] ? "write" : "read" )
												 << " by "
												 << er.ExceptionAddress
												 << " at "
												 << reinterpret_cast< void * >( er.ExceptionInformation[ 1 ] );
		} break;
		default: {
					 sstr << "SEH exception thrown. Exception code: "
						 << std::hex << std::uppercase << er.ExceptionCode
						 << " at "
						 << er.ExceptionAddress;
		}
	}
	sstr << "\n\nStack Trace:\n";
	generate_stack_trace( sstr , *eps->ContextRecord , skip );
	buffer = sstr.str( );

	return EXCEPTION_EXECUTE_HANDLER;
}

DWORD filter( EXCEPTION_POINTERS * eps , std::string & buffer )
{
	__try
	{
		return do_filter( eps , buffer );
	}
	__except ( EXCEPTION_EXECUTE_HANDLER )
	{
		return EXCEPTION_CONTINUE_SEARCH;
	}
}

void save_buffer( const std::string & buffer )
{
	std::ofstream ofs( "err_log.txt" );
	if ( ofs ) ofs << buffer;
}

LONG WINAPI TopLevelExceptionHandler( PEXCEPTION_POINTERS pExceptionInfo )
{
	fflush( logfile );
	std::string buffer;
	filter( pExceptionInfo , buffer );
	if ( !buffer.empty( ) )
	{
		save_buffer( buffer );
		MessageBoxA( 0 , buffer.c_str( ) , "Abnormal Termination" , MB_OK );
	}
	return EXCEPTION_CONTINUE_SEARCH;
}
static int GameDll = (int) GetModuleHandle("Game.dll");
INIReader reader( "./JassConfig.ini" );
void AbilityId_init ( )
{
      AbilityId_org = (AbilityId_FUNC) ( GameDll + 0x1D9B60 );
      MH_CreateHook(AbilityId_org, &AbilityId_my, reinterpret_cast<void**>(&AbilityId_ptr));
      MH_EnableHook(AbilityId_org);
}
void AbilityId2String_init ( )
{
      AbilityId2String_org = (AbilityId2String_FUNC) ( GameDll + 0x1D9B30 );
      MH_CreateHook(AbilityId2String_org, &AbilityId2String_my, reinterpret_cast<void**>(&AbilityId2String_ptr));
      MH_EnableHook(AbilityId2String_org);
}
void Acos_init ( )
{
      Acos_org = (Acos_FUNC) ( GameDll + 0x1D9B90 );
      MH_CreateHook(Acos_org, &Acos_my, reinterpret_cast<void**>(&Acos_ptr));
      MH_EnableHook(Acos_org);
}
void AddAssault_init ( )
{
      AddAssault_org = (AddAssault_FUNC) ( GameDll + 0x88C8B0 );
      MH_CreateHook(AddAssault_org, &AddAssault_my, reinterpret_cast<void**>(&AddAssault_ptr));
      MH_EnableHook(AddAssault_org);
}
void AddDefenders_init ( )
{
      AddDefenders_org = (AddDefenders_FUNC) ( GameDll + 0x88CAD0 );
      MH_CreateHook(AddDefenders_org, &AddDefenders_my, reinterpret_cast<void**>(&AddDefenders_ptr));
      MH_EnableHook(AddDefenders_org);
}
void AddGuardPost_init ( )
{
      AddGuardPost_org = (AddGuardPost_FUNC) ( GameDll + 0x88CB40 );
      MH_CreateHook(AddGuardPost_org, &AddGuardPost_my, reinterpret_cast<void**>(&AddGuardPost_ptr));
      MH_EnableHook(AddGuardPost_org);
}
void AddHeroXP_init ( )
{
      AddHeroXP_org = (AddHeroXP_FUNC) ( GameDll + 0x1D9DA0 );
      MH_CreateHook(AddHeroXP_org, &AddHeroXP_my, reinterpret_cast<void**>(&AddHeroXP_ptr));
      MH_EnableHook(AddHeroXP_org);
}
void AddIndicator_init ( )
{
      AddIndicator_org = (AddIndicator_FUNC) ( GameDll + 0x1D9E10 );
      MH_CreateHook(AddIndicator_org, &AddIndicator_my, reinterpret_cast<void**>(&AddIndicator_ptr));
      MH_EnableHook(AddIndicator_org);
}
void AddItemToAllStock_init ( )
{
      AddItemToAllStock_org = (AddItemToAllStock_FUNC) ( GameDll + 0x1D9FB0 );
      MH_CreateHook(AddItemToAllStock_org, &AddItemToAllStock_my, reinterpret_cast<void**>(&AddItemToAllStock_ptr));
      MH_EnableHook(AddItemToAllStock_org);
}
void AddItemToStock_init ( )
{
      AddItemToStock_org = (AddItemToStock_FUNC) ( GameDll + 0x1D9FD0 );
      MH_CreateHook(AddItemToStock_org, &AddItemToStock_my, reinterpret_cast<void**>(&AddItemToStock_ptr));
      MH_EnableHook(AddItemToStock_org);
}
void AddLightning_init ( )
{
      AddLightning_org = (AddLightning_FUNC) ( GameDll + 0x1DA010 );
      MH_CreateHook(AddLightning_org, &AddLightning_my, reinterpret_cast<void**>(&AddLightning_ptr));
      MH_EnableHook(AddLightning_org);
}
void AddLightningEx_init ( )
{
      AddLightningEx_org = (AddLightningEx_FUNC) ( GameDll + 0x1DA090 );
      MH_CreateHook(AddLightningEx_org, &AddLightningEx_my, reinterpret_cast<void**>(&AddLightningEx_ptr));
      MH_EnableHook(AddLightningEx_org);
}
void AddPlayerTechResearched_init ( )
{
      AddPlayerTechResearched_org = (AddPlayerTechResearched_FUNC) ( GameDll + 0x1DA190 );
      MH_CreateHook(AddPlayerTechResearched_org, &AddPlayerTechResearched_my, reinterpret_cast<void**>(&AddPlayerTechResearched_ptr));
      MH_EnableHook(AddPlayerTechResearched_org);
}
void AddResourceAmount_init ( )
{
      AddResourceAmount_org = (AddResourceAmount_FUNC) ( GameDll + 0x1DA1F0 );
      MH_CreateHook(AddResourceAmount_org, &AddResourceAmount_my, reinterpret_cast<void**>(&AddResourceAmount_ptr));
      MH_EnableHook(AddResourceAmount_org);
}
void AddSpecialEffect_init ( )
{
      AddSpecialEffect_org = (AddSpecialEffect_FUNC) ( GameDll + 0x1DA240 );
      MH_CreateHook(AddSpecialEffect_org, &AddSpecialEffect_my, reinterpret_cast<void**>(&AddSpecialEffect_ptr));
      MH_EnableHook(AddSpecialEffect_org);
}
void AddSpecialEffectLoc_init ( )
{
      AddSpecialEffectLoc_org = (AddSpecialEffectLoc_FUNC) ( GameDll + 0x1DA260 );
      MH_CreateHook(AddSpecialEffectLoc_org, &AddSpecialEffectLoc_my, reinterpret_cast<void**>(&AddSpecialEffectLoc_ptr));
      MH_EnableHook(AddSpecialEffectLoc_org);
}
void AddSpecialEffectTarget_init ( )
{
      AddSpecialEffectTarget_org = (AddSpecialEffectTarget_FUNC) ( GameDll + 0x1DA2A0 );
      MH_CreateHook(AddSpecialEffectTarget_org, &AddSpecialEffectTarget_my, reinterpret_cast<void**>(&AddSpecialEffectTarget_ptr));
      MH_EnableHook(AddSpecialEffectTarget_org);
}
void AddSpellEffect_init ( )
{
      AddSpellEffect_org = (AddSpellEffect_FUNC) ( GameDll + 0x1DA2D0 );
      MH_CreateHook(AddSpellEffect_org, &AddSpellEffect_my, reinterpret_cast<void**>(&AddSpellEffect_ptr));
      MH_EnableHook(AddSpellEffect_org);
}
void AddSpellEffectById_init ( )
{
      AddSpellEffectById_org = (AddSpellEffectById_FUNC) ( GameDll + 0x1DA2F0 );
      MH_CreateHook(AddSpellEffectById_org, &AddSpellEffectById_my, reinterpret_cast<void**>(&AddSpellEffectById_ptr));
      MH_EnableHook(AddSpellEffectById_org);
}
void AddSpellEffectByIdLoc_init ( )
{
      AddSpellEffectByIdLoc_org = (AddSpellEffectByIdLoc_FUNC) ( GameDll + 0x1DA320 );
      MH_CreateHook(AddSpellEffectByIdLoc_org, &AddSpellEffectByIdLoc_my, reinterpret_cast<void**>(&AddSpellEffectByIdLoc_ptr));
      MH_EnableHook(AddSpellEffectByIdLoc_org);
}
void AddSpellEffectLoc_init ( )
{
      AddSpellEffectLoc_org = (AddSpellEffectLoc_FUNC) ( GameDll + 0x1DA360 );
      MH_CreateHook(AddSpellEffectLoc_org, &AddSpellEffectLoc_my, reinterpret_cast<void**>(&AddSpellEffectLoc_ptr));
      MH_EnableHook(AddSpellEffectLoc_org);
}
void AddSpellEffectTarget_init ( )
{
      AddSpellEffectTarget_org = (AddSpellEffectTarget_FUNC) ( GameDll + 0x1DA3C0 );
      MH_CreateHook(AddSpellEffectTarget_org, &AddSpellEffectTarget_my, reinterpret_cast<void**>(&AddSpellEffectTarget_ptr));
      MH_EnableHook(AddSpellEffectTarget_org);
}
void AddSpellEffectTargetById_init ( )
{
      AddSpellEffectTargetById_org = (AddSpellEffectTargetById_FUNC) ( GameDll + 0x1DA3E0 );
      MH_CreateHook(AddSpellEffectTargetById_org, &AddSpellEffectTargetById_my, reinterpret_cast<void**>(&AddSpellEffectTargetById_ptr));
      MH_EnableHook(AddSpellEffectTargetById_org);
}
void AddUnitAnimationProperties_init ( )
{
      AddUnitAnimationProperties_org = (AddUnitAnimationProperties_FUNC) ( GameDll + 0x1DA540 );
      MH_CreateHook(AddUnitAnimationProperties_org, &AddUnitAnimationProperties_my, reinterpret_cast<void**>(&AddUnitAnimationProperties_ptr));
      MH_EnableHook(AddUnitAnimationProperties_org);
}
void AddUnitToAllStock_init ( )
{
      AddUnitToAllStock_org = (AddUnitToAllStock_FUNC) ( GameDll + 0x1DA5F0 );
      MH_CreateHook(AddUnitToAllStock_org, &AddUnitToAllStock_my, reinterpret_cast<void**>(&AddUnitToAllStock_ptr));
      MH_EnableHook(AddUnitToAllStock_org);
}
void AddUnitToStock_init ( )
{
      AddUnitToStock_org = (AddUnitToStock_FUNC) ( GameDll + 0x1DA610 );
      MH_CreateHook(AddUnitToStock_org, &AddUnitToStock_my, reinterpret_cast<void**>(&AddUnitToStock_ptr));
      MH_EnableHook(AddUnitToStock_org);
}
void AddWeatherEffect_init ( )
{
      AddWeatherEffect_org = (AddWeatherEffect_FUNC) ( GameDll + 0x1DA650 );
      MH_CreateHook(AddWeatherEffect_org, &AddWeatherEffect_my, reinterpret_cast<void**>(&AddWeatherEffect_ptr));
      MH_EnableHook(AddWeatherEffect_org);
}
void AdjustCameraField_init ( )
{
      AdjustCameraField_org = (AdjustCameraField_FUNC) ( GameDll + 0x1DA6C0 );
      MH_CreateHook(AdjustCameraField_org, &AdjustCameraField_my, reinterpret_cast<void**>(&AdjustCameraField_ptr));
      MH_EnableHook(AdjustCameraField_org);
}
void And_init ( )
{
      And_org = (And_FUNC) ( GameDll + 0x1DA700 );
      MH_CreateHook(And_org, &And_my, reinterpret_cast<void**>(&And_ptr));
      MH_EnableHook(And_org);
}
void Asin_init ( )
{
      Asin_org = (Asin_FUNC) ( GameDll + 0x1DA810 );
      MH_CreateHook(Asin_org, &Asin_my, reinterpret_cast<void**>(&Asin_ptr));
      MH_EnableHook(Asin_org);
}
void Atan_init ( )
{
      Atan_org = (Atan_FUNC) ( GameDll + 0x1DA8D0 );
      MH_CreateHook(Atan_org, &Atan_my, reinterpret_cast<void**>(&Atan_ptr));
      MH_EnableHook(Atan_org);
}
void Atan2_init ( )
{
      Atan2_org = (Atan2_FUNC) ( GameDll + 0x1DA850 );
      MH_CreateHook(Atan2_org, &Atan2_my, reinterpret_cast<void**>(&Atan2_ptr));
      MH_EnableHook(Atan2_org);
}
void AttachSoundToUnit_init ( )
{
      AttachSoundToUnit_org = (AttachSoundToUnit_FUNC) ( GameDll + 0x1DA8F0 );
      MH_CreateHook(AttachSoundToUnit_org, &AttachSoundToUnit_my, reinterpret_cast<void**>(&AttachSoundToUnit_ptr));
      MH_EnableHook(AttachSoundToUnit_org);
}
void AttackMoveKill_init ( )
{
      AttackMoveKill_org = (AttackMoveKill_FUNC) ( GameDll + 0x88CF10 );
      MH_CreateHook(AttackMoveKill_org, &AttackMoveKill_my, reinterpret_cast<void**>(&AttackMoveKill_ptr));
      MH_EnableHook(AttackMoveKill_org);
}
void AttackMoveXY_init ( )
{
      AttackMoveXY_org = (AttackMoveXY_FUNC) ( GameDll + 0x88CFE0 );
      MH_CreateHook(AttackMoveXY_org, &AttackMoveXY_my, reinterpret_cast<void**>(&AttackMoveXY_ptr));
      MH_EnableHook(AttackMoveXY_org);
}
void CachePlayerHeroData_init ( )
{
      CachePlayerHeroData_org = (CachePlayerHeroData_FUNC) ( GameDll + 0x1DA970 );
      MH_CreateHook(CachePlayerHeroData_org, &CachePlayerHeroData_my, reinterpret_cast<void**>(&CachePlayerHeroData_ptr));
      MH_EnableHook(CachePlayerHeroData_org);
}
void CameraSetSmoothingFactor_init ( )
{
      CameraSetSmoothingFactor_org = (CameraSetSmoothingFactor_FUNC) ( GameDll + 0x1DAA60 );
      MH_CreateHook(CameraSetSmoothingFactor_org, &CameraSetSmoothingFactor_my, reinterpret_cast<void**>(&CameraSetSmoothingFactor_ptr));
      MH_EnableHook(CameraSetSmoothingFactor_org);
}
void CameraSetSourceNoise_init ( )
{
      CameraSetSourceNoise_org = (CameraSetSourceNoise_FUNC) ( GameDll + 0x1DAA90 );
      MH_CreateHook(CameraSetSourceNoise_org, &CameraSetSourceNoise_my, reinterpret_cast<void**>(&CameraSetSourceNoise_ptr));
      MH_EnableHook(CameraSetSourceNoise_org);
}
void CameraSetSourceNoiseEx_init ( )
{
      CameraSetSourceNoiseEx_org = (CameraSetSourceNoiseEx_FUNC) ( GameDll + 0x1DAB30 );
      MH_CreateHook(CameraSetSourceNoiseEx_org, &CameraSetSourceNoiseEx_my, reinterpret_cast<void**>(&CameraSetSourceNoiseEx_ptr));
      MH_EnableHook(CameraSetSourceNoiseEx_org);
}
void CameraSetTargetNoise_init ( )
{
      CameraSetTargetNoise_org = (CameraSetTargetNoise_FUNC) ( GameDll + 0x1DABD0 );
      MH_CreateHook(CameraSetTargetNoise_org, &CameraSetTargetNoise_my, reinterpret_cast<void**>(&CameraSetTargetNoise_ptr));
      MH_EnableHook(CameraSetTargetNoise_org);
}
void CameraSetTargetNoiseEx_init ( )
{
      CameraSetTargetNoiseEx_org = (CameraSetTargetNoiseEx_FUNC) ( GameDll + 0x1DAC80 );
      MH_CreateHook(CameraSetTargetNoiseEx_org, &CameraSetTargetNoiseEx_my, reinterpret_cast<void**>(&CameraSetTargetNoiseEx_ptr));
      MH_EnableHook(CameraSetTargetNoiseEx_org);
}
void CameraSetupApply_init ( )
{
      CameraSetupApply_org = (CameraSetupApply_FUNC) ( GameDll + 0x1DAD30 );
      MH_CreateHook(CameraSetupApply_org, &CameraSetupApply_my, reinterpret_cast<void**>(&CameraSetupApply_ptr));
      MH_EnableHook(CameraSetupApply_org);
}
void CameraSetupApplyForceDuration_init ( )
{
      CameraSetupApplyForceDuration_org = (CameraSetupApplyForceDuration_FUNC) ( GameDll + 0x1DAD60 );
      MH_CreateHook(CameraSetupApplyForceDuration_org, &CameraSetupApplyForceDuration_my, reinterpret_cast<void**>(&CameraSetupApplyForceDuration_ptr));
      MH_EnableHook(CameraSetupApplyForceDuration_org);
}
void CameraSetupApplyForceDurationWithZ_init ( )
{
      CameraSetupApplyForceDurationWithZ_org = (CameraSetupApplyForceDurationWithZ_FUNC) ( GameDll + 0x1DAD90 );
      MH_CreateHook(CameraSetupApplyForceDurationWithZ_org, &CameraSetupApplyForceDurationWithZ_my, reinterpret_cast<void**>(&CameraSetupApplyForceDurationWithZ_ptr));
      MH_EnableHook(CameraSetupApplyForceDurationWithZ_org);
}
void CameraSetupApplyWithZ_init ( )
{
      CameraSetupApplyWithZ_org = (CameraSetupApplyWithZ_FUNC) ( GameDll + 0x1DADC0 );
      MH_CreateHook(CameraSetupApplyWithZ_org, &CameraSetupApplyWithZ_my, reinterpret_cast<void**>(&CameraSetupApplyWithZ_ptr));
      MH_EnableHook(CameraSetupApplyWithZ_org);
}
void CameraSetupGetDestPositionLoc_init ( )
{
      CameraSetupGetDestPositionLoc_org = (CameraSetupGetDestPositionLoc_FUNC) ( GameDll + 0x1DADF0 );
      MH_CreateHook(CameraSetupGetDestPositionLoc_org, &CameraSetupGetDestPositionLoc_my, reinterpret_cast<void**>(&CameraSetupGetDestPositionLoc_ptr));
      MH_EnableHook(CameraSetupGetDestPositionLoc_org);
}
void CameraSetupGetDestPositionX_init ( )
{
      CameraSetupGetDestPositionX_org = (CameraSetupGetDestPositionX_FUNC) ( GameDll + 0x1DAE40 );
      MH_CreateHook(CameraSetupGetDestPositionX_org, &CameraSetupGetDestPositionX_my, reinterpret_cast<void**>(&CameraSetupGetDestPositionX_ptr));
      MH_EnableHook(CameraSetupGetDestPositionX_org);
}
void CameraSetupGetDestPositionY_init ( )
{
      CameraSetupGetDestPositionY_org = (CameraSetupGetDestPositionY_FUNC) ( GameDll + 0x1DAE70 );
      MH_CreateHook(CameraSetupGetDestPositionY_org, &CameraSetupGetDestPositionY_my, reinterpret_cast<void**>(&CameraSetupGetDestPositionY_ptr));
      MH_EnableHook(CameraSetupGetDestPositionY_org);
}
void CameraSetupGetField_init ( )
{
      CameraSetupGetField_org = (CameraSetupGetField_FUNC) ( GameDll + 0x1DAE90 );
      MH_CreateHook(CameraSetupGetField_org, &CameraSetupGetField_my, reinterpret_cast<void**>(&CameraSetupGetField_ptr));
      MH_EnableHook(CameraSetupGetField_org);
}
void CameraSetupSetDestPosition_init ( )
{
      CameraSetupSetDestPosition_org = (CameraSetupSetDestPosition_FUNC) ( GameDll + 0x1DAED0 );
      MH_CreateHook(CameraSetupSetDestPosition_org, &CameraSetupSetDestPosition_my, reinterpret_cast<void**>(&CameraSetupSetDestPosition_ptr));
      MH_EnableHook(CameraSetupSetDestPosition_org);
}
void CameraSetupSetField_init ( )
{
      CameraSetupSetField_org = (CameraSetupSetField_FUNC) ( GameDll + 0x1DAF20 );
      MH_CreateHook(CameraSetupSetField_org, &CameraSetupSetField_my, reinterpret_cast<void**>(&CameraSetupSetField_ptr));
      MH_EnableHook(CameraSetupSetField_org);
}
void CaptainAtGoal_init ( )
{
      CaptainAtGoal_org = (CaptainAtGoal_FUNC) ( GameDll + 0x88D7C0 );
      MH_CreateHook(CaptainAtGoal_org, &CaptainAtGoal_my, reinterpret_cast<void**>(&CaptainAtGoal_ptr));
      MH_EnableHook(CaptainAtGoal_org);
}
void CaptainAttack_init ( )
{
      CaptainAttack_org = (CaptainAttack_FUNC) ( GameDll + 0x88D7F0 );
      MH_CreateHook(CaptainAttack_org, &CaptainAttack_my, reinterpret_cast<void**>(&CaptainAttack_ptr));
      MH_EnableHook(CaptainAttack_org);
}
void CaptainGoHome_init ( )
{
      CaptainGoHome_org = (CaptainGoHome_FUNC) ( GameDll + 0x88D830 );
      MH_CreateHook(CaptainGoHome_org, &CaptainGoHome_my, reinterpret_cast<void**>(&CaptainGoHome_ptr));
      MH_EnableHook(CaptainGoHome_org);
}
void CaptainGroupSize_init ( )
{
      CaptainGroupSize_org = (CaptainGroupSize_FUNC) ( GameDll + 0x88D860 );
      MH_CreateHook(CaptainGroupSize_org, &CaptainGroupSize_my, reinterpret_cast<void**>(&CaptainGroupSize_ptr));
      MH_EnableHook(CaptainGroupSize_org);
}
void CaptainInCombat_init ( )
{
      CaptainInCombat_org = (CaptainInCombat_FUNC) ( GameDll + 0x88D8A0 );
      MH_CreateHook(CaptainInCombat_org, &CaptainInCombat_my, reinterpret_cast<void**>(&CaptainInCombat_ptr));
      MH_EnableHook(CaptainInCombat_org);
}
void CaptainIsEmpty_init ( )
{
      CaptainIsEmpty_org = (CaptainIsEmpty_FUNC) ( GameDll + 0x88D8E0 );
      MH_CreateHook(CaptainIsEmpty_org, &CaptainIsEmpty_my, reinterpret_cast<void**>(&CaptainIsEmpty_ptr));
      MH_EnableHook(CaptainIsEmpty_org);
}
void CaptainIsFull_init ( )
{
      CaptainIsFull_org = (CaptainIsFull_FUNC) ( GameDll + 0x88D920 );
      MH_CreateHook(CaptainIsFull_org, &CaptainIsFull_my, reinterpret_cast<void**>(&CaptainIsFull_ptr));
      MH_EnableHook(CaptainIsFull_org);
}
void CaptainIsHome_init ( )
{
      CaptainIsHome_org = (CaptainIsHome_FUNC) ( GameDll + 0x88D960 );
      MH_CreateHook(CaptainIsHome_org, &CaptainIsHome_my, reinterpret_cast<void**>(&CaptainIsHome_ptr));
      MH_EnableHook(CaptainIsHome_org);
}
void CaptainReadiness_init ( )
{
      CaptainReadiness_org = (CaptainReadiness_FUNC) ( GameDll + 0x88D990 );
      MH_CreateHook(CaptainReadiness_org, &CaptainReadiness_my, reinterpret_cast<void**>(&CaptainReadiness_ptr));
      MH_EnableHook(CaptainReadiness_org);
}
void CaptainReadinessHP_init ( )
{
      CaptainReadinessHP_org = (CaptainReadinessHP_FUNC) ( GameDll + 0x88D9D0 );
      MH_CreateHook(CaptainReadinessHP_org, &CaptainReadinessHP_my, reinterpret_cast<void**>(&CaptainReadinessHP_ptr));
      MH_EnableHook(CaptainReadinessHP_org);
}
void CaptainReadinessMa_init ( )
{
      CaptainReadinessMa_org = (CaptainReadinessMa_FUNC) ( GameDll + 0x88DA10 );
      MH_CreateHook(CaptainReadinessMa_org, &CaptainReadinessMa_my, reinterpret_cast<void**>(&CaptainReadinessMa_ptr));
      MH_EnableHook(CaptainReadinessMa_org);
}
void CaptainRetreating_init ( )
{
      CaptainRetreating_org = (CaptainRetreating_FUNC) ( GameDll + 0x88DA50 );
      MH_CreateHook(CaptainRetreating_org, &CaptainRetreating_my, reinterpret_cast<void**>(&CaptainRetreating_ptr));
      MH_EnableHook(CaptainRetreating_org);
}
void CaptainVsPlayer_init ( )
{
      CaptainVsPlayer_org = (CaptainVsPlayer_FUNC) ( GameDll + 0x88DA90 );
      MH_CreateHook(CaptainVsPlayer_org, &CaptainVsPlayer_my, reinterpret_cast<void**>(&CaptainVsPlayer_ptr));
      MH_EnableHook(CaptainVsPlayer_org);
}
void CaptainVsUnits_init ( )
{
      CaptainVsUnits_org = (CaptainVsUnits_FUNC) ( GameDll + 0x88DB20 );
      MH_CreateHook(CaptainVsUnits_org, &CaptainVsUnits_my, reinterpret_cast<void**>(&CaptainVsUnits_ptr));
      MH_EnableHook(CaptainVsUnits_org);
}
void ChangeLevel_init ( )
{
      ChangeLevel_org = (ChangeLevel_FUNC) ( GameDll + 0x1DAFA0 );
      MH_CreateHook(ChangeLevel_org, &ChangeLevel_my, reinterpret_cast<void**>(&ChangeLevel_ptr));
      MH_EnableHook(ChangeLevel_org);
}
void Cheat_init ( )
{
      Cheat_org = (Cheat_FUNC) ( GameDll + 0x1DAFE0 );
      MH_CreateHook(Cheat_org, &Cheat_my, reinterpret_cast<void**>(&Cheat_ptr));
      MH_EnableHook(Cheat_org);
}
void ChooseRandomCreep_init ( )
{
      ChooseRandomCreep_org = (ChooseRandomCreep_FUNC) ( GameDll + 0x1DB0A0 );
      MH_CreateHook(ChooseRandomCreep_org, &ChooseRandomCreep_my, reinterpret_cast<void**>(&ChooseRandomCreep_ptr));
      MH_EnableHook(ChooseRandomCreep_org);
}
void ChooseRandomItem_init ( )
{
      ChooseRandomItem_org = (ChooseRandomItem_FUNC) ( GameDll + 0x1DB0C0 );
      MH_CreateHook(ChooseRandomItem_org, &ChooseRandomItem_my, reinterpret_cast<void**>(&ChooseRandomItem_ptr));
      MH_EnableHook(ChooseRandomItem_org);
}
void ChooseRandomItemEx_init ( )
{
      ChooseRandomItemEx_org = (ChooseRandomItemEx_FUNC) ( GameDll + 0x1DB0E0 );
      MH_CreateHook(ChooseRandomItemEx_org, &ChooseRandomItemEx_my, reinterpret_cast<void**>(&ChooseRandomItemEx_ptr));
      MH_EnableHook(ChooseRandomItemEx_org);
}
void ChooseRandomNPBuilding_init ( )
{
      ChooseRandomNPBuilding_org = (ChooseRandomNPBuilding_FUNC) ( GameDll + 0x1DB100 );
      MH_CreateHook(ChooseRandomNPBuilding_org, &ChooseRandomNPBuilding_my, reinterpret_cast<void**>(&ChooseRandomNPBuilding_ptr));
      MH_EnableHook(ChooseRandomNPBuilding_org);
}
void ClearCaptainTargets_init ( )
{
      ClearCaptainTargets_org = (ClearCaptainTargets_FUNC) ( GameDll + 0x88DD80 );
      MH_CreateHook(ClearCaptainTargets_org, &ClearCaptainTargets_my, reinterpret_cast<void**>(&ClearCaptainTargets_ptr));
      MH_EnableHook(ClearCaptainTargets_org);
}
void ClearHarvestAI_init ( )
{
      ClearHarvestAI_org = (ClearHarvestAI_FUNC) ( GameDll + 0x88DDE0 );
      MH_CreateHook(ClearHarvestAI_org, &ClearHarvestAI_my, reinterpret_cast<void**>(&ClearHarvestAI_ptr));
      MH_EnableHook(ClearHarvestAI_org);
}
void ClearMapMusic_init ( )
{
      ClearMapMusic_org = (ClearMapMusic_FUNC) ( GameDll + 0x1DB220 );
      MH_CreateHook(ClearMapMusic_org, &ClearMapMusic_my, reinterpret_cast<void**>(&ClearMapMusic_ptr));
      MH_EnableHook(ClearMapMusic_org);
}
void ClearSelection_init ( )
{
      ClearSelection_org = (ClearSelection_FUNC) ( GameDll + 0x1DB310 );
      MH_CreateHook(ClearSelection_org, &ClearSelection_my, reinterpret_cast<void**>(&ClearSelection_ptr));
      MH_EnableHook(ClearSelection_org);
}
void ClearStackedSound_init ( )
{
      ClearStackedSound_org = (ClearStackedSound_FUNC) ( GameDll + 0x1DB3A0 );
      MH_CreateHook(ClearStackedSound_org, &ClearStackedSound_my, reinterpret_cast<void**>(&ClearStackedSound_ptr));
      MH_EnableHook(ClearStackedSound_org);
}
void ClearStackedSoundRect_init ( )
{
      ClearStackedSoundRect_org = (ClearStackedSoundRect_FUNC) ( GameDll + 0x1DB3F0 );
      MH_CreateHook(ClearStackedSoundRect_org, &ClearStackedSoundRect_my, reinterpret_cast<void**>(&ClearStackedSoundRect_ptr));
      MH_EnableHook(ClearStackedSoundRect_org);
}
void ClearTextMessages_init ( )
{
      ClearTextMessages_org = (ClearTextMessages_FUNC) ( GameDll + 0x1DB520 );
      MH_CreateHook(ClearTextMessages_org, &ClearTextMessages_my, reinterpret_cast<void**>(&ClearTextMessages_ptr));
      MH_EnableHook(ClearTextMessages_org);
}
void CommandAI_init ( )
{
      CommandAI_org = (CommandAI_FUNC) ( GameDll + 0x1DB550 );
      MH_CreateHook(CommandAI_org, &CommandAI_my, reinterpret_cast<void**>(&CommandAI_ptr));
      MH_EnableHook(CommandAI_org);
}
void CommandsWaiting_init ( )
{
      CommandsWaiting_org = (CommandsWaiting_FUNC) ( GameDll + 0x88E100 );
      MH_CreateHook(CommandsWaiting_org, &CommandsWaiting_my, reinterpret_cast<void**>(&CommandsWaiting_ptr));
      MH_EnableHook(CommandsWaiting_org);
}
void Condition_init ( )
{
      Condition_org = (Condition_FUNC) ( GameDll + 0x1DB5C0 );
      MH_CreateHook(Condition_org, &Condition_my, reinterpret_cast<void**>(&Condition_ptr));
      MH_EnableHook(Condition_org);
}
void ConvertAIDifficulty_init ( )
{
      ConvertAIDifficulty_org = (ConvertAIDifficulty_FUNC) ( GameDll + 0x1DB6D0 );
      MH_CreateHook(ConvertAIDifficulty_org, &ConvertAIDifficulty_my, reinterpret_cast<void**>(&ConvertAIDifficulty_ptr));
      MH_EnableHook(ConvertAIDifficulty_org);
}
void ConvertAllianceType_init ( )
{
      ConvertAllianceType_org = (ConvertAllianceType_FUNC) ( GameDll + 0x1DB6E0 );
      MH_CreateHook(ConvertAllianceType_org, &ConvertAllianceType_my, reinterpret_cast<void**>(&ConvertAllianceType_ptr));
      MH_EnableHook(ConvertAllianceType_org);
}
void ConvertAttackType_init ( )
{
      ConvertAttackType_org = (ConvertAttackType_FUNC) ( GameDll + 0x1DB6F0 );
      MH_CreateHook(ConvertAttackType_org, &ConvertAttackType_my, reinterpret_cast<void**>(&ConvertAttackType_ptr));
      MH_EnableHook(ConvertAttackType_org);
}
void ConvertBlendMode_init ( )
{
      ConvertBlendMode_org = (ConvertBlendMode_FUNC) ( GameDll + 0x1DB700 );
      MH_CreateHook(ConvertBlendMode_org, &ConvertBlendMode_my, reinterpret_cast<void**>(&ConvertBlendMode_ptr));
      MH_EnableHook(ConvertBlendMode_org);
}
void ConvertCameraField_init ( )
{
      ConvertCameraField_org = (ConvertCameraField_FUNC) ( GameDll + 0x1DB710 );
      MH_CreateHook(ConvertCameraField_org, &ConvertCameraField_my, reinterpret_cast<void**>(&ConvertCameraField_ptr));
      MH_EnableHook(ConvertCameraField_org);
}
void ConvertDamageType_init ( )
{
      ConvertDamageType_org = (ConvertDamageType_FUNC) ( GameDll + 0x1DB720 );
      MH_CreateHook(ConvertDamageType_org, &ConvertDamageType_my, reinterpret_cast<void**>(&ConvertDamageType_ptr));
      MH_EnableHook(ConvertDamageType_org);
}
void ConvertDialogEvent_init ( )
{
      ConvertDialogEvent_org = (ConvertDialogEvent_FUNC) ( GameDll + 0x1DB730 );
      MH_CreateHook(ConvertDialogEvent_org, &ConvertDialogEvent_my, reinterpret_cast<void**>(&ConvertDialogEvent_ptr));
      MH_EnableHook(ConvertDialogEvent_org);
}
void ConvertEffectType_init ( )
{
      ConvertEffectType_org = (ConvertEffectType_FUNC) ( GameDll + 0x1DB740 );
      MH_CreateHook(ConvertEffectType_org, &ConvertEffectType_my, reinterpret_cast<void**>(&ConvertEffectType_ptr));
      MH_EnableHook(ConvertEffectType_org);
}
void ConvertFGameState_init ( )
{
      ConvertFGameState_org = (ConvertFGameState_FUNC) ( GameDll + 0x1DB750 );
      MH_CreateHook(ConvertFGameState_org, &ConvertFGameState_my, reinterpret_cast<void**>(&ConvertFGameState_ptr));
      MH_EnableHook(ConvertFGameState_org);
}
void ConvertFogState_init ( )
{
      ConvertFogState_org = (ConvertFogState_FUNC) ( GameDll + 0x1DB760 );
      MH_CreateHook(ConvertFogState_org, &ConvertFogState_my, reinterpret_cast<void**>(&ConvertFogState_ptr));
      MH_EnableHook(ConvertFogState_org);
}
void ConvertGameDifficulty_init ( )
{
      ConvertGameDifficulty_org = (ConvertGameDifficulty_FUNC) ( GameDll + 0x1DB770 );
      MH_CreateHook(ConvertGameDifficulty_org, &ConvertGameDifficulty_my, reinterpret_cast<void**>(&ConvertGameDifficulty_ptr));
      MH_EnableHook(ConvertGameDifficulty_org);
}
void ConvertGameEvent_init ( )
{
      ConvertGameEvent_org = (ConvertGameEvent_FUNC) ( GameDll + 0x1DB780 );
      MH_CreateHook(ConvertGameEvent_org, &ConvertGameEvent_my, reinterpret_cast<void**>(&ConvertGameEvent_ptr));
      MH_EnableHook(ConvertGameEvent_org);
}
void ConvertGameSpeed_init ( )
{
      ConvertGameSpeed_org = (ConvertGameSpeed_FUNC) ( GameDll + 0x1DB790 );
      MH_CreateHook(ConvertGameSpeed_org, &ConvertGameSpeed_my, reinterpret_cast<void**>(&ConvertGameSpeed_ptr));
      MH_EnableHook(ConvertGameSpeed_org);
}
void ConvertGameType_init ( )
{
      ConvertGameType_org = (ConvertGameType_FUNC) ( GameDll + 0x1DB7A0 );
      MH_CreateHook(ConvertGameType_org, &ConvertGameType_my, reinterpret_cast<void**>(&ConvertGameType_ptr));
      MH_EnableHook(ConvertGameType_org);
}
void ConvertIGameState_init ( )
{
      ConvertIGameState_org = (ConvertIGameState_FUNC) ( GameDll + 0x1DB7B0 );
      MH_CreateHook(ConvertIGameState_org, &ConvertIGameState_my, reinterpret_cast<void**>(&ConvertIGameState_ptr));
      MH_EnableHook(ConvertIGameState_org);
}
void ConvertItemType_init ( )
{
      ConvertItemType_org = (ConvertItemType_FUNC) ( GameDll + 0x1DB7C0 );
      MH_CreateHook(ConvertItemType_org, &ConvertItemType_my, reinterpret_cast<void**>(&ConvertItemType_ptr));
      MH_EnableHook(ConvertItemType_org);
}
void ConvertLimitOp_init ( )
{
      ConvertLimitOp_org = (ConvertLimitOp_FUNC) ( GameDll + 0x1DB7D0 );
      MH_CreateHook(ConvertLimitOp_org, &ConvertLimitOp_my, reinterpret_cast<void**>(&ConvertLimitOp_ptr));
      MH_EnableHook(ConvertLimitOp_org);
}
void ConvertMapControl_init ( )
{
      ConvertMapControl_org = (ConvertMapControl_FUNC) ( GameDll + 0x1DB7E0 );
      MH_CreateHook(ConvertMapControl_org, &ConvertMapControl_my, reinterpret_cast<void**>(&ConvertMapControl_ptr));
      MH_EnableHook(ConvertMapControl_org);
}
void ConvertMapDensity_init ( )
{
      ConvertMapDensity_org = (ConvertMapDensity_FUNC) ( GameDll + 0x1DB7F0 );
      MH_CreateHook(ConvertMapDensity_org, &ConvertMapDensity_my, reinterpret_cast<void**>(&ConvertMapDensity_ptr));
      MH_EnableHook(ConvertMapDensity_org);
}
void ConvertMapFlag_init ( )
{
      ConvertMapFlag_org = (ConvertMapFlag_FUNC) ( GameDll + 0x1DB800 );
      MH_CreateHook(ConvertMapFlag_org, &ConvertMapFlag_my, reinterpret_cast<void**>(&ConvertMapFlag_ptr));
      MH_EnableHook(ConvertMapFlag_org);
}
void ConvertMapSetting_init ( )
{
      ConvertMapSetting_org = (ConvertMapSetting_FUNC) ( GameDll + 0x1DB810 );
      MH_CreateHook(ConvertMapSetting_org, &ConvertMapSetting_my, reinterpret_cast<void**>(&ConvertMapSetting_ptr));
      MH_EnableHook(ConvertMapSetting_org);
}
void ConvertMapVisibility_init ( )
{
      ConvertMapVisibility_org = (ConvertMapVisibility_FUNC) ( GameDll + 0x1DB820 );
      MH_CreateHook(ConvertMapVisibility_org, &ConvertMapVisibility_my, reinterpret_cast<void**>(&ConvertMapVisibility_ptr));
      MH_EnableHook(ConvertMapVisibility_org);
}
void ConvertPathingType_init ( )
{
      ConvertPathingType_org = (ConvertPathingType_FUNC) ( GameDll + 0x1DB830 );
      MH_CreateHook(ConvertPathingType_org, &ConvertPathingType_my, reinterpret_cast<void**>(&ConvertPathingType_ptr));
      MH_EnableHook(ConvertPathingType_org);
}
void ConvertPlacement_init ( )
{
      ConvertPlacement_org = (ConvertPlacement_FUNC) ( GameDll + 0x1DB840 );
      MH_CreateHook(ConvertPlacement_org, &ConvertPlacement_my, reinterpret_cast<void**>(&ConvertPlacement_ptr));
      MH_EnableHook(ConvertPlacement_org);
}
void ConvertPlayerColor_init ( )
{
      ConvertPlayerColor_org = (ConvertPlayerColor_FUNC) ( GameDll + 0x1DB850 );
      MH_CreateHook(ConvertPlayerColor_org, &ConvertPlayerColor_my, reinterpret_cast<void**>(&ConvertPlayerColor_ptr));
      MH_EnableHook(ConvertPlayerColor_org);
}
void ConvertPlayerEvent_init ( )
{
      ConvertPlayerEvent_org = (ConvertPlayerEvent_FUNC) ( GameDll + 0x1DB860 );
      MH_CreateHook(ConvertPlayerEvent_org, &ConvertPlayerEvent_my, reinterpret_cast<void**>(&ConvertPlayerEvent_ptr));
      MH_EnableHook(ConvertPlayerEvent_org);
}
void ConvertPlayerGameResult_init ( )
{
      ConvertPlayerGameResult_org = (ConvertPlayerGameResult_FUNC) ( GameDll + 0x1DB870 );
      MH_CreateHook(ConvertPlayerGameResult_org, &ConvertPlayerGameResult_my, reinterpret_cast<void**>(&ConvertPlayerGameResult_ptr));
      MH_EnableHook(ConvertPlayerGameResult_org);
}
void ConvertPlayerScore_init ( )
{
      ConvertPlayerScore_org = (ConvertPlayerScore_FUNC) ( GameDll + 0x1DB880 );
      MH_CreateHook(ConvertPlayerScore_org, &ConvertPlayerScore_my, reinterpret_cast<void**>(&ConvertPlayerScore_ptr));
      MH_EnableHook(ConvertPlayerScore_org);
}
void ConvertPlayerSlotState_init ( )
{
      ConvertPlayerSlotState_org = (ConvertPlayerSlotState_FUNC) ( GameDll + 0x1DB890 );
      MH_CreateHook(ConvertPlayerSlotState_org, &ConvertPlayerSlotState_my, reinterpret_cast<void**>(&ConvertPlayerSlotState_ptr));
      MH_EnableHook(ConvertPlayerSlotState_org);
}
void ConvertPlayerState_init ( )
{
      ConvertPlayerState_org = (ConvertPlayerState_FUNC) ( GameDll + 0x1DB8A0 );
      MH_CreateHook(ConvertPlayerState_org, &ConvertPlayerState_my, reinterpret_cast<void**>(&ConvertPlayerState_ptr));
      MH_EnableHook(ConvertPlayerState_org);
}
void ConvertPlayerUnitEvent_init ( )
{
      ConvertPlayerUnitEvent_org = (ConvertPlayerUnitEvent_FUNC) ( GameDll + 0x1DB8B0 );
      MH_CreateHook(ConvertPlayerUnitEvent_org, &ConvertPlayerUnitEvent_my, reinterpret_cast<void**>(&ConvertPlayerUnitEvent_ptr));
      MH_EnableHook(ConvertPlayerUnitEvent_org);
}
void ConvertRace_init ( )
{
      ConvertRace_org = (ConvertRace_FUNC) ( GameDll + 0x1DB8C0 );
      MH_CreateHook(ConvertRace_org, &ConvertRace_my, reinterpret_cast<void**>(&ConvertRace_ptr));
      MH_EnableHook(ConvertRace_org);
}
void ConvertRacePref_init ( )
{
      ConvertRacePref_org = (ConvertRacePref_FUNC) ( GameDll + 0x1DB8D0 );
      MH_CreateHook(ConvertRacePref_org, &ConvertRacePref_my, reinterpret_cast<void**>(&ConvertRacePref_ptr));
      MH_EnableHook(ConvertRacePref_org);
}
void ConvertRarityControl_init ( )
{
      ConvertRarityControl_org = (ConvertRarityControl_FUNC) ( GameDll + 0x1DB8F0 );
      MH_CreateHook(ConvertRarityControl_org, &ConvertRarityControl_my, reinterpret_cast<void**>(&ConvertRarityControl_ptr));
      MH_EnableHook(ConvertRarityControl_org);
}
void ConvertSoundType_init ( )
{
      ConvertSoundType_org = (ConvertSoundType_FUNC) ( GameDll + 0x1DB900 );
      MH_CreateHook(ConvertSoundType_org, &ConvertSoundType_my, reinterpret_cast<void**>(&ConvertSoundType_ptr));
      MH_EnableHook(ConvertSoundType_org);
}
void ConvertStartLocPrio_init ( )
{
      ConvertStartLocPrio_org = (ConvertStartLocPrio_FUNC) ( GameDll + 0x1DB910 );
      MH_CreateHook(ConvertStartLocPrio_org, &ConvertStartLocPrio_my, reinterpret_cast<void**>(&ConvertStartLocPrio_ptr));
      MH_EnableHook(ConvertStartLocPrio_org);
}
void ConvertTexMapFlags_init ( )
{
      ConvertTexMapFlags_org = (ConvertTexMapFlags_FUNC) ( GameDll + 0x1DB920 );
      MH_CreateHook(ConvertTexMapFlags_org, &ConvertTexMapFlags_my, reinterpret_cast<void**>(&ConvertTexMapFlags_ptr));
      MH_EnableHook(ConvertTexMapFlags_org);
}
void ConvertUnitEvent_init ( )
{
      ConvertUnitEvent_org = (ConvertUnitEvent_FUNC) ( GameDll + 0x1DB980 );
      MH_CreateHook(ConvertUnitEvent_org, &ConvertUnitEvent_my, reinterpret_cast<void**>(&ConvertUnitEvent_ptr));
      MH_EnableHook(ConvertUnitEvent_org);
}
void ConvertUnitState_init ( )
{
      ConvertUnitState_org = (ConvertUnitState_FUNC) ( GameDll + 0x1DB990 );
      MH_CreateHook(ConvertUnitState_org, &ConvertUnitState_my, reinterpret_cast<void**>(&ConvertUnitState_ptr));
      MH_EnableHook(ConvertUnitState_org);
}
void ConvertUnitType_init ( )
{
      ConvertUnitType_org = (ConvertUnitType_FUNC) ( GameDll + 0x1DB9A0 );
      MH_CreateHook(ConvertUnitType_org, &ConvertUnitType_my, reinterpret_cast<void**>(&ConvertUnitType_ptr));
      MH_EnableHook(ConvertUnitType_org);
}
void ConvertUnits_init ( )
{
      ConvertUnits_org = (ConvertUnits_FUNC) ( GameDll + 0x88E350 );
      MH_CreateHook(ConvertUnits_org, &ConvertUnits_my, reinterpret_cast<void**>(&ConvertUnits_ptr));
      MH_EnableHook(ConvertUnits_org);
}
void ConvertVersion_init ( )
{
      ConvertVersion_org = (ConvertVersion_FUNC) ( GameDll + 0x1DB9B0 );
      MH_CreateHook(ConvertVersion_org, &ConvertVersion_my, reinterpret_cast<void**>(&ConvertVersion_ptr));
      MH_EnableHook(ConvertVersion_org);
}
void ConvertVolumeGroup_init ( )
{
      ConvertVolumeGroup_org = (ConvertVolumeGroup_FUNC) ( GameDll + 0x1DB9C0 );
      MH_CreateHook(ConvertVolumeGroup_org, &ConvertVolumeGroup_my, reinterpret_cast<void**>(&ConvertVolumeGroup_ptr));
      MH_EnableHook(ConvertVolumeGroup_org);
}
void ConvertWeaponType_init ( )
{
      ConvertWeaponType_org = (ConvertWeaponType_FUNC) ( GameDll + 0x1DB9D0 );
      MH_CreateHook(ConvertWeaponType_org, &ConvertWeaponType_my, reinterpret_cast<void**>(&ConvertWeaponType_ptr));
      MH_EnableHook(ConvertWeaponType_org);
}
void ConvertWidgetEvent_init ( )
{
      ConvertWidgetEvent_org = (ConvertWidgetEvent_FUNC) ( GameDll + 0x1DB9E0 );
      MH_CreateHook(ConvertWidgetEvent_org, &ConvertWidgetEvent_my, reinterpret_cast<void**>(&ConvertWidgetEvent_ptr));
      MH_EnableHook(ConvertWidgetEvent_org);
}
void CopySaveGame_init ( )
{
      CopySaveGame_org = (CopySaveGame_FUNC) ( GameDll + 0x1DB9F0 );
      MH_CreateHook(CopySaveGame_org, &CopySaveGame_my, reinterpret_cast<void**>(&CopySaveGame_ptr));
      MH_EnableHook(CopySaveGame_org);
}
void Cos_init ( )
{
      Cos_org = (Cos_FUNC) ( GameDll + 0x1DBB40 );
      MH_CreateHook(Cos_org, &Cos_my, reinterpret_cast<void**>(&Cos_ptr));
      MH_EnableHook(Cos_org);
}
void CreateBlightedGoldmine_init ( )
{
      CreateBlightedGoldmine_org = (CreateBlightedGoldmine_FUNC) ( GameDll + 0x1DD900 );
      MH_CreateHook(CreateBlightedGoldmine_org, &CreateBlightedGoldmine_my, reinterpret_cast<void**>(&CreateBlightedGoldmine_ptr));
      MH_EnableHook(CreateBlightedGoldmine_org);
}
void CreateCameraSetup_init ( )
{
      CreateCameraSetup_org = (CreateCameraSetup_FUNC) ( GameDll + 0x1DD9C0 );
      MH_CreateHook(CreateCameraSetup_org, &CreateCameraSetup_my, reinterpret_cast<void**>(&CreateCameraSetup_ptr));
      MH_EnableHook(CreateCameraSetup_org);
}
void CreateCaptains_init ( )
{
      CreateCaptains_org = (CreateCaptains_FUNC) ( GameDll + 0x88E530 );
      MH_CreateHook(CreateCaptains_org, &CreateCaptains_my, reinterpret_cast<void**>(&CreateCaptains_ptr));
      MH_EnableHook(CreateCaptains_org);
}
void CreateCorpse_init ( )
{
      CreateCorpse_org = (CreateCorpse_FUNC) ( GameDll + 0x1DDAB0 );
      MH_CreateHook(CreateCorpse_org, &CreateCorpse_my, reinterpret_cast<void**>(&CreateCorpse_ptr));
      MH_EnableHook(CreateCorpse_org);
}
void CreateDeadDestructable_init ( )
{
      CreateDeadDestructable_org = (CreateDeadDestructable_FUNC) ( GameDll + 0x1DDB60 );
      MH_CreateHook(CreateDeadDestructable_org, &CreateDeadDestructable_my, reinterpret_cast<void**>(&CreateDeadDestructable_ptr));
      MH_EnableHook(CreateDeadDestructable_org);
}
void CreateDeadDestructableZ_init ( )
{
      CreateDeadDestructableZ_org = (CreateDeadDestructableZ_FUNC) ( GameDll + 0x1DDBB0 );
      MH_CreateHook(CreateDeadDestructableZ_org, &CreateDeadDestructableZ_my, reinterpret_cast<void**>(&CreateDeadDestructableZ_ptr));
      MH_EnableHook(CreateDeadDestructableZ_org);
}
void CreateDefeatCondition_init ( )
{
      CreateDefeatCondition_org = (CreateDefeatCondition_FUNC) ( GameDll + 0x1DDC00 );
      MH_CreateHook(CreateDefeatCondition_org, &CreateDefeatCondition_my, reinterpret_cast<void**>(&CreateDefeatCondition_ptr));
      MH_EnableHook(CreateDefeatCondition_org);
}
void CreateDestructable_init ( )
{
      CreateDestructable_org = (CreateDestructable_FUNC) ( GameDll + 0x1DDC50 );
      MH_CreateHook(CreateDestructable_org, &CreateDestructable_my, reinterpret_cast<void**>(&CreateDestructable_ptr));
      MH_EnableHook(CreateDestructable_org);
}
void CreateDestructableZ_init ( )
{
      CreateDestructableZ_org = (CreateDestructableZ_FUNC) ( GameDll + 0x1DDCA0 );
      MH_CreateHook(CreateDestructableZ_org, &CreateDestructableZ_my, reinterpret_cast<void**>(&CreateDestructableZ_ptr));
      MH_EnableHook(CreateDestructableZ_org);
}
void CreateFogModifierRadius_init ( )
{
      CreateFogModifierRadius_org = (CreateFogModifierRadius_FUNC) ( GameDll + 0x1DDCF0 );
      MH_CreateHook(CreateFogModifierRadius_org, &CreateFogModifierRadius_my, reinterpret_cast<void**>(&CreateFogModifierRadius_ptr));
      MH_EnableHook(CreateFogModifierRadius_org);
}
void CreateFogModifierRadiusLoc_init ( )
{
      CreateFogModifierRadiusLoc_org = (CreateFogModifierRadiusLoc_FUNC) ( GameDll + 0x1DDDD0 );
      MH_CreateHook(CreateFogModifierRadiusLoc_org, &CreateFogModifierRadiusLoc_my, reinterpret_cast<void**>(&CreateFogModifierRadiusLoc_ptr));
      MH_EnableHook(CreateFogModifierRadiusLoc_org);
}
void CreateFogModifierRect_init ( )
{
      CreateFogModifierRect_org = (CreateFogModifierRect_FUNC) ( GameDll + 0x1DDEB0 );
      MH_CreateHook(CreateFogModifierRect_org, &CreateFogModifierRect_my, reinterpret_cast<void**>(&CreateFogModifierRect_ptr));
      MH_EnableHook(CreateFogModifierRect_org);
}
void CreateForce_init ( )
{
      CreateForce_org = (CreateForce_FUNC) ( GameDll + 0x1DDFA0 );
      MH_CreateHook(CreateForce_org, &CreateForce_my, reinterpret_cast<void**>(&CreateForce_ptr));
      MH_EnableHook(CreateForce_org);
}
void CreateGroup_init ( )
{
      CreateGroup_org = (CreateGroup_FUNC) ( GameDll + 0x1DE080 );
      MH_CreateHook(CreateGroup_org, &CreateGroup_my, reinterpret_cast<void**>(&CreateGroup_ptr));
      MH_EnableHook(CreateGroup_org);
}
void CreateImage_init ( )
{
      CreateImage_org = (CreateImage_FUNC) ( GameDll + 0x1DE160 );
      MH_CreateHook(CreateImage_org, &CreateImage_my, reinterpret_cast<void**>(&CreateImage_ptr));
      MH_EnableHook(CreateImage_org);
}
void CreateItem_init ( )
{
      CreateItem_org = (CreateItem_FUNC) ( GameDll + 0x1DE200 );
      MH_CreateHook(CreateItem_org, &CreateItem_my, reinterpret_cast<void**>(&CreateItem_ptr));
      MH_EnableHook(CreateItem_org);
}
void CreateItemPool_init ( )
{
      CreateItemPool_org = (CreateItemPool_FUNC) ( GameDll + 0x1DE230 );
      MH_CreateHook(CreateItemPool_org, &CreateItemPool_my, reinterpret_cast<void**>(&CreateItemPool_ptr));
      MH_EnableHook(CreateItemPool_org);
}
void CreateLeaderboard_init ( )
{
      CreateLeaderboard_org = (CreateLeaderboard_FUNC) ( GameDll + 0x1DE310 );
      MH_CreateHook(CreateLeaderboard_org, &CreateLeaderboard_my, reinterpret_cast<void**>(&CreateLeaderboard_ptr));
      MH_EnableHook(CreateLeaderboard_org);
}
void CreateMIDISound_init ( )
{
      CreateMIDISound_org = (CreateMIDISound_FUNC) ( GameDll + 0x1DE400 );
      MH_CreateHook(CreateMIDISound_org, &CreateMIDISound_my, reinterpret_cast<void**>(&CreateMIDISound_ptr));
      MH_EnableHook(CreateMIDISound_org);
}
void CreateMultiboard_init ( )
{
      CreateMultiboard_org = (CreateMultiboard_FUNC) ( GameDll + 0x1DE500 );
      MH_CreateHook(CreateMultiboard_org, &CreateMultiboard_my, reinterpret_cast<void**>(&CreateMultiboard_ptr));
      MH_EnableHook(CreateMultiboard_org);
}
void CreateQuest_init ( )
{
      CreateQuest_org = (CreateQuest_FUNC) ( GameDll + 0x1DE5F0 );
      MH_CreateHook(CreateQuest_org, &CreateQuest_my, reinterpret_cast<void**>(&CreateQuest_ptr));
      MH_EnableHook(CreateQuest_org);
}
void CreateRegion_init ( )
{
      CreateRegion_org = (CreateRegion_FUNC) ( GameDll + 0x1DE660 );
      MH_CreateHook(CreateRegion_org, &CreateRegion_my, reinterpret_cast<void**>(&CreateRegion_ptr));
      MH_EnableHook(CreateRegion_org);
}
void CreateSound_init ( )
{
      CreateSound_org = (CreateSound_FUNC) ( GameDll + 0x1DE740 );
      MH_CreateHook(CreateSound_org, &CreateSound_my, reinterpret_cast<void**>(&CreateSound_ptr));
      MH_EnableHook(CreateSound_org);
}
void CreateSoundFilenameWithLabel_init ( )
{
      CreateSoundFilenameWithLabel_org = (CreateSoundFilenameWithLabel_FUNC) ( GameDll + 0x1DE860 );
      MH_CreateHook(CreateSoundFilenameWithLabel_org, &CreateSoundFilenameWithLabel_my, reinterpret_cast<void**>(&CreateSoundFilenameWithLabel_ptr));
      MH_EnableHook(CreateSoundFilenameWithLabel_org);
}
void CreateSoundFromLabel_init ( )
{
      CreateSoundFromLabel_org = (CreateSoundFromLabel_FUNC) ( GameDll + 0x1DE980 );
      MH_CreateHook(CreateSoundFromLabel_org, &CreateSoundFromLabel_my, reinterpret_cast<void**>(&CreateSoundFromLabel_ptr));
      MH_EnableHook(CreateSoundFromLabel_org);
}
void CreateTextTag_init ( )
{
      CreateTextTag_org = (CreateTextTag_FUNC) ( GameDll + 0x1DEA90 );
      MH_CreateHook(CreateTextTag_org, &CreateTextTag_my, reinterpret_cast<void**>(&CreateTextTag_ptr));
      MH_EnableHook(CreateTextTag_org);
}
void CreateTimer_init ( )
{
      CreateTimer_org = (CreateTimer_FUNC) ( GameDll + 0x1DEAB0 );
      MH_CreateHook(CreateTimer_org, &CreateTimer_my, reinterpret_cast<void**>(&CreateTimer_ptr));
      MH_EnableHook(CreateTimer_org);
}
void CreateTimerDialog_init ( )
{
      CreateTimerDialog_org = (CreateTimerDialog_FUNC) ( GameDll + 0x1DEB90 );
      MH_CreateHook(CreateTimerDialog_org, &CreateTimerDialog_my, reinterpret_cast<void**>(&CreateTimerDialog_ptr));
      MH_EnableHook(CreateTimerDialog_org);
}
void CreateTrackable_init ( )
{
      CreateTrackable_org = (CreateTrackable_FUNC) ( GameDll + 0x1DEC90 );
      MH_CreateHook(CreateTrackable_org, &CreateTrackable_my, reinterpret_cast<void**>(&CreateTrackable_ptr));
      MH_EnableHook(CreateTrackable_org);
}
void CreateTrigger_init ( )
{
      CreateTrigger_org = (CreateTrigger_FUNC) ( GameDll + 0x1DEDA0 );
      MH_CreateHook(CreateTrigger_org, &CreateTrigger_my, reinterpret_cast<void**>(&CreateTrigger_ptr));
      MH_EnableHook(CreateTrigger_org);
}
void CreateUbersplat_init ( )
{
      CreateUbersplat_org = (CreateUbersplat_FUNC) ( GameDll + 0x1DEE80 );
      MH_CreateHook(CreateUbersplat_org, &CreateUbersplat_my, reinterpret_cast<void**>(&CreateUbersplat_ptr));
      MH_EnableHook(CreateUbersplat_org);
}
void CreateUnit_init ( )
{
      CreateUnit_org = (CreateUnit_FUNC) ( GameDll + 0x1DEEF0 );
      MH_CreateHook(CreateUnit_org, &CreateUnit_my, reinterpret_cast<void**>(&CreateUnit_ptr));
      MH_EnableHook(CreateUnit_org);
}
void CreateUnitAtLoc_init ( )
{
      CreateUnitAtLoc_org = (CreateUnitAtLoc_FUNC) ( GameDll + 0x1DEF50 );
      MH_CreateHook(CreateUnitAtLoc_org, &CreateUnitAtLoc_my, reinterpret_cast<void**>(&CreateUnitAtLoc_ptr));
      MH_EnableHook(CreateUnitAtLoc_org);
}
void CreateUnitAtLocByName_init ( )
{
      CreateUnitAtLocByName_org = (CreateUnitAtLocByName_FUNC) ( GameDll + 0x1DEFA0 );
      MH_CreateHook(CreateUnitAtLocByName_org, &CreateUnitAtLocByName_my, reinterpret_cast<void**>(&CreateUnitAtLocByName_ptr));
      MH_EnableHook(CreateUnitAtLocByName_org);
}
void CreateUnitByName_init ( )
{
      CreateUnitByName_org = (CreateUnitByName_FUNC) ( GameDll + 0x1DEFD0 );
      MH_CreateHook(CreateUnitByName_org, &CreateUnitByName_my, reinterpret_cast<void**>(&CreateUnitByName_ptr));
      MH_EnableHook(CreateUnitByName_org);
}
void CreateUnitPool_init ( )
{
      CreateUnitPool_org = (CreateUnitPool_FUNC) ( GameDll + 0x1DF000 );
      MH_CreateHook(CreateUnitPool_org, &CreateUnitPool_my, reinterpret_cast<void**>(&CreateUnitPool_ptr));
      MH_EnableHook(CreateUnitPool_org);
}
void CreepsOnMap_init ( )
{
      CreepsOnMap_org = (CreepsOnMap_FUNC) ( GameDll + 0x88E580 );
      MH_CreateHook(CreepsOnMap_org, &CreepsOnMap_my, reinterpret_cast<void**>(&CreepsOnMap_ptr));
      MH_EnableHook(CreepsOnMap_org);
}
void CripplePlayer_init ( )
{
      CripplePlayer_org = (CripplePlayer_FUNC) ( GameDll + 0x1DF100 );
      MH_CreateHook(CripplePlayer_org, &CripplePlayer_my, reinterpret_cast<void**>(&CripplePlayer_ptr));
      MH_EnableHook(CripplePlayer_org);
}
void DebugBreak_init ( )
{
      DebugBreak_org = (DebugBreak_FUNC) ( GameDll + 0x88E5B0 );
      MH_CreateHook(DebugBreak_org, &DebugBreak_my, reinterpret_cast<void**>(&DebugBreak_ptr));
      MH_EnableHook(DebugBreak_org);
}
void DebugFI_init ( )
{
      DebugFI_org = (DebugFI_FUNC) ( GameDll + 0x88E5C0 );
      MH_CreateHook(DebugFI_org, &DebugFI_my, reinterpret_cast<void**>(&DebugFI_ptr));
      MH_EnableHook(DebugFI_org);
}
void DebugS_init ( )
{
      DebugS_org = (DebugS_FUNC) ( GameDll + 0x88E5D0 );
      MH_CreateHook(DebugS_org, &DebugS_my, reinterpret_cast<void**>(&DebugS_ptr));
      MH_EnableHook(DebugS_org);
}
void DebugUnitID_init ( )
{
      DebugUnitID_org = (DebugUnitID_FUNC) ( GameDll + 0x88E5E0 );
      MH_CreateHook(DebugUnitID_org, &DebugUnitID_my, reinterpret_cast<void**>(&DebugUnitID_ptr));
      MH_EnableHook(DebugUnitID_org);
}
void DecUnitAbilityLevel_init ( )
{
      DecUnitAbilityLevel_org = (DecUnitAbilityLevel_FUNC) ( GameDll + 0x1DF1B0 );
      MH_CreateHook(DecUnitAbilityLevel_org, &DecUnitAbilityLevel_my, reinterpret_cast<void**>(&DecUnitAbilityLevel_ptr));
      MH_EnableHook(DecUnitAbilityLevel_org);
}
void DefeatConditionSetDescription_init ( )
{
      DefeatConditionSetDescription_org = (DefeatConditionSetDescription_FUNC) ( GameDll + 0x1DF2D0 );
      MH_CreateHook(DefeatConditionSetDescription_org, &DefeatConditionSetDescription_my, reinterpret_cast<void**>(&DefeatConditionSetDescription_ptr));
      MH_EnableHook(DefeatConditionSetDescription_org);
}
void DefineStartLocation_init ( )
{
      DefineStartLocation_org = (DefineStartLocation_FUNC) ( GameDll + 0x1DF300 );
      MH_CreateHook(DefineStartLocation_org, &DefineStartLocation_my, reinterpret_cast<void**>(&DefineStartLocation_ptr));
      MH_EnableHook(DefineStartLocation_org);
}
void DefineStartLocationLoc_init ( )
{
      DefineStartLocationLoc_org = (DefineStartLocationLoc_FUNC) ( GameDll + 0x1DF320 );
      MH_CreateHook(DefineStartLocationLoc_org, &DefineStartLocationLoc_my, reinterpret_cast<void**>(&DefineStartLocationLoc_ptr));
      MH_EnableHook(DefineStartLocationLoc_org);
}
void Deg2Rad_init ( )
{
      Deg2Rad_org = (Deg2Rad_FUNC) ( GameDll + 0x1DF360 );
      MH_CreateHook(Deg2Rad_org, &Deg2Rad_my, reinterpret_cast<void**>(&Deg2Rad_ptr));
      MH_EnableHook(Deg2Rad_org);
}
void DestroyBoolExpr_init ( )
{
      DestroyBoolExpr_org = (DestroyBoolExpr_FUNC) ( GameDll + 0x1DF510 );
      MH_CreateHook(DestroyBoolExpr_org, &DestroyBoolExpr_my, reinterpret_cast<void**>(&DestroyBoolExpr_ptr));
      MH_EnableHook(DestroyBoolExpr_org);
}
void DestroyCondition_init ( )
{
      DestroyCondition_org = (DestroyCondition_FUNC) ( GameDll + 0x1DF530 );
      MH_CreateHook(DestroyCondition_org, &DestroyCondition_my, reinterpret_cast<void**>(&DestroyCondition_ptr));
      MH_EnableHook(DestroyCondition_org);
}
void DestroyDefeatCondition_init ( )
{
      DestroyDefeatCondition_org = (DestroyDefeatCondition_FUNC) ( GameDll + 0x1DF560 );
      MH_CreateHook(DestroyDefeatCondition_org, &DestroyDefeatCondition_my, reinterpret_cast<void**>(&DestroyDefeatCondition_ptr));
      MH_EnableHook(DestroyDefeatCondition_org);
}
void DestroyEffect_init ( )
{
      DestroyEffect_org = (DestroyEffect_FUNC) ( GameDll + 0x1DF5B0 );
      MH_CreateHook(DestroyEffect_org, &DestroyEffect_my, reinterpret_cast<void**>(&DestroyEffect_ptr));
      MH_EnableHook(DestroyEffect_org);
}
void DestroyFilter_init ( )
{
      DestroyFilter_org = (DestroyFilter_FUNC) ( GameDll + 0x1DF5D0 );
      MH_CreateHook(DestroyFilter_org, &DestroyFilter_my, reinterpret_cast<void**>(&DestroyFilter_ptr));
      MH_EnableHook(DestroyFilter_org);
}
void DestroyFogModifier_init ( )
{
      DestroyFogModifier_org = (DestroyFogModifier_FUNC) ( GameDll + 0x1DF600 );
      MH_CreateHook(DestroyFogModifier_org, &DestroyFogModifier_my, reinterpret_cast<void**>(&DestroyFogModifier_ptr));
      MH_EnableHook(DestroyFogModifier_org);
}
void DestroyForce_init ( )
{
      DestroyForce_org = (DestroyForce_FUNC) ( GameDll + 0x1DF620 );
      MH_CreateHook(DestroyForce_org, &DestroyForce_my, reinterpret_cast<void**>(&DestroyForce_ptr));
      MH_EnableHook(DestroyForce_org);
}
void DestroyGroup_init ( )
{
      DestroyGroup_org = (DestroyGroup_FUNC) ( GameDll + 0x1DF640 );
      MH_CreateHook(DestroyGroup_org, &DestroyGroup_my, reinterpret_cast<void**>(&DestroyGroup_ptr));
      MH_EnableHook(DestroyGroup_org);
}
void DestroyImage_init ( )
{
      DestroyImage_org = (DestroyImage_FUNC) ( GameDll + 0x1DF660 );
      MH_CreateHook(DestroyImage_org, &DestroyImage_my, reinterpret_cast<void**>(&DestroyImage_ptr));
      MH_EnableHook(DestroyImage_org);
}
void DestroyItemPool_init ( )
{
      DestroyItemPool_org = (DestroyItemPool_FUNC) ( GameDll + 0x1DF680 );
      MH_CreateHook(DestroyItemPool_org, &DestroyItemPool_my, reinterpret_cast<void**>(&DestroyItemPool_ptr));
      MH_EnableHook(DestroyItemPool_org);
}
void DestroyLeaderboard_init ( )
{
      DestroyLeaderboard_org = (DestroyLeaderboard_FUNC) ( GameDll + 0x1DF6A0 );
      MH_CreateHook(DestroyLeaderboard_org, &DestroyLeaderboard_my, reinterpret_cast<void**>(&DestroyLeaderboard_ptr));
      MH_EnableHook(DestroyLeaderboard_org);
}
void DestroyLightning_init ( )
{
      DestroyLightning_org = (DestroyLightning_FUNC) ( GameDll + 0x1DF6D0 );
      MH_CreateHook(DestroyLightning_org, &DestroyLightning_my, reinterpret_cast<void**>(&DestroyLightning_ptr));
      MH_EnableHook(DestroyLightning_org);
}
void DestroyMultiboard_init ( )
{
      DestroyMultiboard_org = (DestroyMultiboard_FUNC) ( GameDll + 0x1DF6F0 );
      MH_CreateHook(DestroyMultiboard_org, &DestroyMultiboard_my, reinterpret_cast<void**>(&DestroyMultiboard_ptr));
      MH_EnableHook(DestroyMultiboard_org);
}
void DestroyQuest_init ( )
{
      DestroyQuest_org = (DestroyQuest_FUNC) ( GameDll + 0x1DF710 );
      MH_CreateHook(DestroyQuest_org, &DestroyQuest_my, reinterpret_cast<void**>(&DestroyQuest_ptr));
      MH_EnableHook(DestroyQuest_org);
}
void DestroyTextTag_init ( )
{
      DestroyTextTag_org = (DestroyTextTag_FUNC) ( GameDll + 0x1DF760 );
      MH_CreateHook(DestroyTextTag_org, &DestroyTextTag_my, reinterpret_cast<void**>(&DestroyTextTag_ptr));
      MH_EnableHook(DestroyTextTag_org);
}
void DestroyTimer_init ( )
{
      DestroyTimer_org = (DestroyTimer_FUNC) ( GameDll + 0x1DF790 );
      MH_CreateHook(DestroyTimer_org, &DestroyTimer_my, reinterpret_cast<void**>(&DestroyTimer_ptr));
      MH_EnableHook(DestroyTimer_org);
}
void DestroyTimerDialog_init ( )
{
      DestroyTimerDialog_org = (DestroyTimerDialog_FUNC) ( GameDll + 0x1DF7B0 );
      MH_CreateHook(DestroyTimerDialog_org, &DestroyTimerDialog_my, reinterpret_cast<void**>(&DestroyTimerDialog_ptr));
      MH_EnableHook(DestroyTimerDialog_org);
}
void DestroyTrigger_init ( )
{
      DestroyTrigger_org = (DestroyTrigger_FUNC) ( GameDll + 0x1DF7D0 );
      MH_CreateHook(DestroyTrigger_org, &DestroyTrigger_my, reinterpret_cast<void**>(&DestroyTrigger_ptr));
      MH_EnableHook(DestroyTrigger_org);
}
void DestroyUbersplat_init ( )
{
      DestroyUbersplat_org = (DestroyUbersplat_FUNC) ( GameDll + 0x1DF7F0 );
      MH_CreateHook(DestroyUbersplat_org, &DestroyUbersplat_my, reinterpret_cast<void**>(&DestroyUbersplat_ptr));
      MH_EnableHook(DestroyUbersplat_org);
}
void DestroyUnitPool_init ( )
{
      DestroyUnitPool_org = (DestroyUnitPool_FUNC) ( GameDll + 0x1DF810 );
      MH_CreateHook(DestroyUnitPool_org, &DestroyUnitPool_my, reinterpret_cast<void**>(&DestroyUnitPool_ptr));
      MH_EnableHook(DestroyUnitPool_org);
}
void DestructableRestoreLife_init ( )
{
      DestructableRestoreLife_org = (DestructableRestoreLife_FUNC) ( GameDll + 0x1DF980 );
      MH_CreateHook(DestructableRestoreLife_org, &DestructableRestoreLife_my, reinterpret_cast<void**>(&DestructableRestoreLife_ptr));
      MH_EnableHook(DestructableRestoreLife_org);
}
void DialogAddButton_init ( )
{
      DialogAddButton_org = (DialogAddButton_FUNC) ( GameDll + 0x1DF9A0 );
      MH_CreateHook(DialogAddButton_org, &DialogAddButton_my, reinterpret_cast<void**>(&DialogAddButton_ptr));
      MH_EnableHook(DialogAddButton_org);
}
void DialogAddQuitButton_init ( )
{
      DialogAddQuitButton_org = (DialogAddQuitButton_FUNC) ( GameDll + 0x1DF9F0 );
      MH_CreateHook(DialogAddQuitButton_org, &DialogAddQuitButton_my, reinterpret_cast<void**>(&DialogAddQuitButton_ptr));
      MH_EnableHook(DialogAddQuitButton_org);
}
void DialogClear_init ( )
{
      DialogClear_org = (DialogClear_FUNC) ( GameDll + 0x1DFA40 );
      MH_CreateHook(DialogClear_org, &DialogClear_my, reinterpret_cast<void**>(&DialogClear_ptr));
      MH_EnableHook(DialogClear_org);
}
void DialogCreate_init ( )
{
      DialogCreate_org = (DialogCreate_FUNC) ( GameDll + 0x1DFA60 );
      MH_CreateHook(DialogCreate_org, &DialogCreate_my, reinterpret_cast<void**>(&DialogCreate_ptr));
      MH_EnableHook(DialogCreate_org);
}
void DialogDestroy_init ( )
{
      DialogDestroy_org = (DialogDestroy_FUNC) ( GameDll + 0x1DFB50 );
      MH_CreateHook(DialogDestroy_org, &DialogDestroy_my, reinterpret_cast<void**>(&DialogDestroy_ptr));
      MH_EnableHook(DialogDestroy_org);
}
void DialogDisplay_init ( )
{
      DialogDisplay_org = (DialogDisplay_FUNC) ( GameDll + 0x1DFB70 );
      MH_CreateHook(DialogDisplay_org, &DialogDisplay_my, reinterpret_cast<void**>(&DialogDisplay_ptr));
      MH_EnableHook(DialogDisplay_org);
}
void DialogSetAsync_init ( )
{
      DialogSetAsync_org = (DialogSetAsync_FUNC) ( GameDll + 0x1DFBC0 );
      MH_CreateHook(DialogSetAsync_org, &DialogSetAsync_my, reinterpret_cast<void**>(&DialogSetAsync_ptr));
      MH_EnableHook(DialogSetAsync_org);
}
void DialogSetMessage_init ( )
{
      DialogSetMessage_org = (DialogSetMessage_FUNC) ( GameDll + 0x1DFBE0 );
      MH_CreateHook(DialogSetMessage_org, &DialogSetMessage_my, reinterpret_cast<void**>(&DialogSetMessage_ptr));
      MH_EnableHook(DialogSetMessage_org);
}
void DisablePathing_init ( )
{
      DisablePathing_org = (DisablePathing_FUNC) ( GameDll + 0x88E730 );
      MH_CreateHook(DisablePathing_org, &DisablePathing_my, reinterpret_cast<void**>(&DisablePathing_ptr));
      MH_EnableHook(DisablePathing_org);
}
void DisableRestartMission_init ( )
{
      DisableRestartMission_org = (DisableRestartMission_FUNC) ( GameDll + 0x1DFC30 );
      MH_CreateHook(DisableRestartMission_org, &DisableRestartMission_my, reinterpret_cast<void**>(&DisableRestartMission_ptr));
      MH_EnableHook(DisableRestartMission_org);
}
void DisableTrigger_init ( )
{
      DisableTrigger_org = (DisableTrigger_FUNC) ( GameDll + 0x1DFC50 );
      MH_CreateHook(DisableTrigger_org, &DisableTrigger_my, reinterpret_cast<void**>(&DisableTrigger_ptr));
      MH_EnableHook(DisableTrigger_org);
}
void DisplayCineFilter_init ( )
{
      DisplayCineFilter_org = (DisplayCineFilter_FUNC) ( GameDll + 0x1DFC90 );
      MH_CreateHook(DisplayCineFilter_org, &DisplayCineFilter_my, reinterpret_cast<void**>(&DisplayCineFilter_ptr));
      MH_EnableHook(DisplayCineFilter_org);
}
void DisplayLoadDialog_init ( )
{
      DisplayLoadDialog_org = (DisplayLoadDialog_FUNC) ( GameDll + 0x1DFCC0 );
      MH_CreateHook(DisplayLoadDialog_org, &DisplayLoadDialog_my, reinterpret_cast<void**>(&DisplayLoadDialog_ptr));
      MH_EnableHook(DisplayLoadDialog_org);
}
void DisplayText_init ( )
{
      DisplayText_org = (DisplayText_FUNC) ( GameDll + 0x88E780 );
      MH_CreateHook(DisplayText_org, &DisplayText_my, reinterpret_cast<void**>(&DisplayText_ptr));
      MH_EnableHook(DisplayText_org);
}
void DisplayTextI_init ( )
{
      DisplayTextI_org = (DisplayTextI_FUNC) ( GameDll + 0x88E790 );
      MH_CreateHook(DisplayTextI_org, &DisplayTextI_my, reinterpret_cast<void**>(&DisplayTextI_ptr));
      MH_EnableHook(DisplayTextI_org);
}
void DisplayTextII_init ( )
{
      DisplayTextII_org = (DisplayTextII_FUNC) ( GameDll + 0x88E7A0 );
      MH_CreateHook(DisplayTextII_org, &DisplayTextII_my, reinterpret_cast<void**>(&DisplayTextII_ptr));
      MH_EnableHook(DisplayTextII_org);
}
void DisplayTextIII_init ( )
{
      DisplayTextIII_org = (DisplayTextIII_FUNC) ( GameDll + 0x88E7B0 );
      MH_CreateHook(DisplayTextIII_org, &DisplayTextIII_my, reinterpret_cast<void**>(&DisplayTextIII_ptr));
      MH_EnableHook(DisplayTextIII_org);
}
void DisplayTextToPlayer_init ( )
{
      DisplayTextToPlayer_org = (DisplayTextToPlayer_FUNC) ( GameDll + 0x1DFCE0 );
      MH_CreateHook(DisplayTextToPlayer_org, &DisplayTextToPlayer_my, reinterpret_cast<void**>(&DisplayTextToPlayer_ptr));
      MH_EnableHook(DisplayTextToPlayer_org);
}
void DisplayTimedTextFromPlayer_init ( )
{
      DisplayTimedTextFromPlayer_org = (DisplayTimedTextFromPlayer_FUNC) ( GameDll + 0x1DFD90 );
      MH_CreateHook(DisplayTimedTextFromPlayer_org, &DisplayTimedTextFromPlayer_my, reinterpret_cast<void**>(&DisplayTimedTextFromPlayer_ptr));
      MH_EnableHook(DisplayTimedTextFromPlayer_org);
}
void DisplayTimedTextToPlayer_init ( )
{
      DisplayTimedTextToPlayer_org = (DisplayTimedTextToPlayer_FUNC) ( GameDll + 0x1DFE70 );
      MH_CreateHook(DisplayTimedTextToPlayer_org, &DisplayTimedTextToPlayer_my, reinterpret_cast<void**>(&DisplayTimedTextToPlayer_ptr));
      MH_EnableHook(DisplayTimedTextToPlayer_org);
}
void DoAiScriptDebug_init ( )
{
      DoAiScriptDebug_org = (DoAiScriptDebug_FUNC) ( GameDll + 0x88E7C0 );
      MH_CreateHook(DoAiScriptDebug_org, &DoAiScriptDebug_my, reinterpret_cast<void**>(&DoAiScriptDebug_ptr));
      MH_EnableHook(DoAiScriptDebug_org);
}
void DoNotSaveReplay_init ( )
{
      DoNotSaveReplay_org = (DoNotSaveReplay_FUNC) ( GameDll + 0x1DFEE0 );
      MH_CreateHook(DoNotSaveReplay_org, &DoNotSaveReplay_my, reinterpret_cast<void**>(&DoNotSaveReplay_ptr));
      MH_EnableHook(DoNotSaveReplay_org);
}
void EnableDragSelect_init ( )
{
      EnableDragSelect_org = (EnableDragSelect_FUNC) ( GameDll + 0x1DFF40 );
      MH_CreateHook(EnableDragSelect_org, &EnableDragSelect_my, reinterpret_cast<void**>(&EnableDragSelect_ptr));
      MH_EnableHook(EnableDragSelect_org);
}
void EnableMinimapFilterButtons_init ( )
{
      EnableMinimapFilterButtons_org = (EnableMinimapFilterButtons_FUNC) ( GameDll + 0x1DFF60 );
      MH_CreateHook(EnableMinimapFilterButtons_org, &EnableMinimapFilterButtons_my, reinterpret_cast<void**>(&EnableMinimapFilterButtons_ptr));
      MH_EnableHook(EnableMinimapFilterButtons_org);
}
void EnableOcclusion_init ( )
{
      EnableOcclusion_org = (EnableOcclusion_FUNC) ( GameDll + 0x1DFFA0 );
      MH_CreateHook(EnableOcclusion_org, &EnableOcclusion_my, reinterpret_cast<void**>(&EnableOcclusion_ptr));
      MH_EnableHook(EnableOcclusion_org);
}
void EnablePreSelect_init ( )
{
      EnablePreSelect_org = (EnablePreSelect_FUNC) ( GameDll + 0x1DFFD0 );
      MH_CreateHook(EnablePreSelect_org, &EnablePreSelect_my, reinterpret_cast<void**>(&EnablePreSelect_ptr));
      MH_EnableHook(EnablePreSelect_org);
}
void EnableSelect_init ( )
{
      EnableSelect_org = (EnableSelect_FUNC) ( GameDll + 0x1DFFF0 );
      MH_CreateHook(EnableSelect_org, &EnableSelect_my, reinterpret_cast<void**>(&EnableSelect_ptr));
      MH_EnableHook(EnableSelect_org);
}
void EnableTrigger_init ( )
{
      EnableTrigger_org = (EnableTrigger_FUNC) ( GameDll + 0x1E0010 );
      MH_CreateHook(EnableTrigger_org, &EnableTrigger_my, reinterpret_cast<void**>(&EnableTrigger_ptr));
      MH_EnableHook(EnableTrigger_org);
}
void EnableUserControl_init ( )
{
      EnableUserControl_org = (EnableUserControl_FUNC) ( GameDll + 0x1E0030 );
      MH_CreateHook(EnableUserControl_org, &EnableUserControl_my, reinterpret_cast<void**>(&EnableUserControl_ptr));
      MH_EnableHook(EnableUserControl_org);
}
void EnableUserUI_init ( )
{
      EnableUserUI_org = (EnableUserUI_FUNC) ( GameDll + 0x1E0060 );
      MH_CreateHook(EnableUserUI_org, &EnableUserUI_my, reinterpret_cast<void**>(&EnableUserUI_ptr));
      MH_EnableHook(EnableUserUI_org);
}
void EnableWeatherEffect_init ( )
{
      EnableWeatherEffect_org = (EnableWeatherEffect_FUNC) ( GameDll + 0x1E0090 );
      MH_CreateHook(EnableWeatherEffect_org, &EnableWeatherEffect_my, reinterpret_cast<void**>(&EnableWeatherEffect_ptr));
      MH_EnableHook(EnableWeatherEffect_org);
}
void EnableWorldFogBoundary_init ( )
{
      EnableWorldFogBoundary_org = (EnableWorldFogBoundary_FUNC) ( GameDll + 0x1E00A0 );
      MH_CreateHook(EnableWorldFogBoundary_org, &EnableWorldFogBoundary_my, reinterpret_cast<void**>(&EnableWorldFogBoundary_ptr));
      MH_EnableHook(EnableWorldFogBoundary_org);
}
void EndCinematicScene_init ( )
{
      EndCinematicScene_org = (EndCinematicScene_FUNC) ( GameDll + 0x1E00E0 );
      MH_CreateHook(EndCinematicScene_org, &EndCinematicScene_my, reinterpret_cast<void**>(&EndCinematicScene_ptr));
      MH_EnableHook(EndCinematicScene_org);
}
void EndGame_init ( )
{
      EndGame_org = (EndGame_FUNC) ( GameDll + 0x1E0100 );
      MH_CreateHook(EndGame_org, &EndGame_my, reinterpret_cast<void**>(&EndGame_ptr));
      MH_EnableHook(EndGame_org);
}
void EndThematicMusic_init ( )
{
      EndThematicMusic_org = (EndThematicMusic_FUNC) ( GameDll + 0x1E0130 );
      MH_CreateHook(EndThematicMusic_org, &EndThematicMusic_my, reinterpret_cast<void**>(&EndThematicMusic_ptr));
      MH_EnableHook(EndThematicMusic_org);
}
void EnumDestructablesInRect_init ( )
{
      EnumDestructablesInRect_org = (EnumDestructablesInRect_FUNC) ( GameDll + 0x1E0140 );
      MH_CreateHook(EnumDestructablesInRect_org, &EnumDestructablesInRect_my, reinterpret_cast<void**>(&EnumDestructablesInRect_ptr));
      MH_EnableHook(EnumDestructablesInRect_org);
}
void EnumItemsInRect_init ( )
{
      EnumItemsInRect_org = (EnumItemsInRect_FUNC) ( GameDll + 0x1E0230 );
      MH_CreateHook(EnumItemsInRect_org, &EnumItemsInRect_my, reinterpret_cast<void**>(&EnumItemsInRect_ptr));
      MH_EnableHook(EnumItemsInRect_org);
}
void ExecuteFunc_init ( )
{
      ExecuteFunc_org = (ExecuteFunc_FUNC) ( GameDll + 0x1E0650 );
      MH_CreateHook(ExecuteFunc_org, &ExecuteFunc_my, reinterpret_cast<void**>(&ExecuteFunc_ptr));
      MH_EnableHook(ExecuteFunc_org);
}
void FillGuardPosts_init ( )
{
      FillGuardPosts_org = (FillGuardPosts_FUNC) ( GameDll + 0x88EA50 );
      MH_CreateHook(FillGuardPosts_org, &FillGuardPosts_my, reinterpret_cast<void**>(&FillGuardPosts_ptr));
      MH_EnableHook(FillGuardPosts_org);
}
void Filter_init ( )
{
      Filter_org = (Filter_FUNC) ( GameDll + 0x1E0720 );
      MH_CreateHook(Filter_org, &Filter_my, reinterpret_cast<void**>(&Filter_ptr));
      MH_EnableHook(Filter_org);
}
void FinishUbersplat_init ( )
{
      FinishUbersplat_org = (FinishUbersplat_FUNC) ( GameDll + 0x1E0830 );
      MH_CreateHook(FinishUbersplat_org, &FinishUbersplat_my, reinterpret_cast<void**>(&FinishUbersplat_ptr));
      MH_EnableHook(FinishUbersplat_org);
}
void FirstOfGroup_init ( )
{
      FirstOfGroup_org = (FirstOfGroup_FUNC) ( GameDll + 0x1E0850 );
      MH_CreateHook(FirstOfGroup_org, &FirstOfGroup_my, reinterpret_cast<void**>(&FirstOfGroup_ptr));
      MH_EnableHook(FirstOfGroup_org);
}
void FlashQuestDialogButton_init ( )
{
      FlashQuestDialogButton_org = (FlashQuestDialogButton_FUNC) ( GameDll + 0x1E08A0 );
      MH_CreateHook(FlashQuestDialogButton_org, &FlashQuestDialogButton_my, reinterpret_cast<void**>(&FlashQuestDialogButton_ptr));
      MH_EnableHook(FlashQuestDialogButton_org);
}
void FlushChildHashtable_init ( )
{
      FlushChildHashtable_org = (FlushChildHashtable_FUNC) ( GameDll + 0x1E08F0 );
      MH_CreateHook(FlushChildHashtable_org, &FlushChildHashtable_my, reinterpret_cast<void**>(&FlushChildHashtable_ptr));
      MH_EnableHook(FlushChildHashtable_org);
}
void FlushGameCache_init ( )
{
      FlushGameCache_org = (FlushGameCache_FUNC) ( GameDll + 0x1E0920 );
      MH_CreateHook(FlushGameCache_org, &FlushGameCache_my, reinterpret_cast<void**>(&FlushGameCache_ptr));
      MH_EnableHook(FlushGameCache_org);
}
void FlushParentHashtable_init ( )
{
      FlushParentHashtable_org = (FlushParentHashtable_FUNC) ( GameDll + 0x1E0960 );
      MH_CreateHook(FlushParentHashtable_org, &FlushParentHashtable_my, reinterpret_cast<void**>(&FlushParentHashtable_ptr));
      MH_EnableHook(FlushParentHashtable_org);
}
void FlushStoredBoolean_init ( )
{
      FlushStoredBoolean_org = (FlushStoredBoolean_FUNC) ( GameDll + 0x1E09A0 );
      MH_CreateHook(FlushStoredBoolean_org, &FlushStoredBoolean_my, reinterpret_cast<void**>(&FlushStoredBoolean_ptr));
      MH_EnableHook(FlushStoredBoolean_org);
}
void FlushStoredInteger_init ( )
{
      FlushStoredInteger_org = (FlushStoredInteger_FUNC) ( GameDll + 0x1E09F0 );
      MH_CreateHook(FlushStoredInteger_org, &FlushStoredInteger_my, reinterpret_cast<void**>(&FlushStoredInteger_ptr));
      MH_EnableHook(FlushStoredInteger_org);
}
void FlushStoredMission_init ( )
{
      FlushStoredMission_org = (FlushStoredMission_FUNC) ( GameDll + 0x1E0A40 );
      MH_CreateHook(FlushStoredMission_org, &FlushStoredMission_my, reinterpret_cast<void**>(&FlushStoredMission_ptr));
      MH_EnableHook(FlushStoredMission_org);
}
void FlushStoredReal_init ( )
{
      FlushStoredReal_org = (FlushStoredReal_FUNC) ( GameDll + 0x1E0A80 );
      MH_CreateHook(FlushStoredReal_org, &FlushStoredReal_my, reinterpret_cast<void**>(&FlushStoredReal_ptr));
      MH_EnableHook(FlushStoredReal_org);
}
void FlushStoredString_init ( )
{
      FlushStoredString_org = (FlushStoredString_FUNC) ( GameDll + 0x1E0AD0 );
      MH_CreateHook(FlushStoredString_org, &FlushStoredString_my, reinterpret_cast<void**>(&FlushStoredString_ptr));
      MH_EnableHook(FlushStoredString_org);
}
void FlushStoredUnit_init ( )
{
      FlushStoredUnit_org = (FlushStoredUnit_FUNC) ( GameDll + 0x1E0B20 );
      MH_CreateHook(FlushStoredUnit_org, &FlushStoredUnit_my, reinterpret_cast<void**>(&FlushStoredUnit_ptr));
      MH_EnableHook(FlushStoredUnit_org);
}
void FogEnable_init ( )
{
      FogEnable_org = (FogEnable_FUNC) ( GameDll + 0x1E0B70 );
      MH_CreateHook(FogEnable_org, &FogEnable_my, reinterpret_cast<void**>(&FogEnable_ptr));
      MH_EnableHook(FogEnable_org);
}
void FogMaskEnable_init ( )
{
      FogMaskEnable_org = (FogMaskEnable_FUNC) ( GameDll + 0x1E0BA0 );
      MH_CreateHook(FogMaskEnable_org, &FogMaskEnable_my, reinterpret_cast<void**>(&FogMaskEnable_ptr));
      MH_EnableHook(FogMaskEnable_org);
}
void FogModifierStart_init ( )
{
      FogModifierStart_org = (FogModifierStart_FUNC) ( GameDll + 0x1E0BC0 );
      MH_CreateHook(FogModifierStart_org, &FogModifierStart_my, reinterpret_cast<void**>(&FogModifierStart_ptr));
      MH_EnableHook(FogModifierStart_org);
}
void FogModifierStop_init ( )
{
      FogModifierStop_org = (FogModifierStop_FUNC) ( GameDll + 0x1E0BE0 );
      MH_CreateHook(FogModifierStop_org, &FogModifierStop_my, reinterpret_cast<void**>(&FogModifierStop_ptr));
      MH_EnableHook(FogModifierStop_org);
}
void ForForce_init ( )
{
      ForForce_org = (ForForce_FUNC) ( GameDll + 0x1E0C30 );
      MH_CreateHook(ForForce_org, &ForForce_my, reinterpret_cast<void**>(&ForForce_ptr));
      MH_EnableHook(ForForce_org);
}
void ForGroup_init ( )
{
      ForGroup_org = (ForGroup_FUNC) ( GameDll + 0x1E0C50 );
      MH_CreateHook(ForGroup_org, &ForGroup_my, reinterpret_cast<void**>(&ForGroup_ptr));
      MH_EnableHook(ForGroup_org);
}
void ForceAddPlayer_init ( )
{
      ForceAddPlayer_org = (ForceAddPlayer_FUNC) ( GameDll + 0x1E0C70 );
      MH_CreateHook(ForceAddPlayer_org, &ForceAddPlayer_my, reinterpret_cast<void**>(&ForceAddPlayer_ptr));
      MH_EnableHook(ForceAddPlayer_org);
}
void ForceCampaignSelectScreen_init ( )
{
      ForceCampaignSelectScreen_org = (ForceCampaignSelectScreen_FUNC) ( GameDll + 0x1E0CA0 );
      MH_CreateHook(ForceCampaignSelectScreen_org, &ForceCampaignSelectScreen_my, reinterpret_cast<void**>(&ForceCampaignSelectScreen_ptr));
      MH_EnableHook(ForceCampaignSelectScreen_org);
}
void ForceCinematicSubtitles_init ( )
{
      ForceCinematicSubtitles_org = (ForceCinematicSubtitles_FUNC) ( GameDll + 0x1E0CD0 );
      MH_CreateHook(ForceCinematicSubtitles_org, &ForceCinematicSubtitles_my, reinterpret_cast<void**>(&ForceCinematicSubtitles_ptr));
      MH_EnableHook(ForceCinematicSubtitles_org);
}
void ForceClear_init ( )
{
      ForceClear_org = (ForceClear_FUNC) ( GameDll + 0x1E0CF0 );
      MH_CreateHook(ForceClear_org, &ForceClear_my, reinterpret_cast<void**>(&ForceClear_ptr));
      MH_EnableHook(ForceClear_org);
}
void ForceEnumAllies_init ( )
{
      ForceEnumAllies_org = (ForceEnumAllies_FUNC) ( GameDll + 0x1E0D10 );
      MH_CreateHook(ForceEnumAllies_org, &ForceEnumAllies_my, reinterpret_cast<void**>(&ForceEnumAllies_ptr));
      MH_EnableHook(ForceEnumAllies_org);
}
void ForceEnumEnemies_init ( )
{
      ForceEnumEnemies_org = (ForceEnumEnemies_FUNC) ( GameDll + 0x1E0D50 );
      MH_CreateHook(ForceEnumEnemies_org, &ForceEnumEnemies_my, reinterpret_cast<void**>(&ForceEnumEnemies_ptr));
      MH_EnableHook(ForceEnumEnemies_org);
}
void ForceEnumPlayers_init ( )
{
      ForceEnumPlayers_org = (ForceEnumPlayers_FUNC) ( GameDll + 0x1E0D90 );
      MH_CreateHook(ForceEnumPlayers_org, &ForceEnumPlayers_my, reinterpret_cast<void**>(&ForceEnumPlayers_ptr));
      MH_EnableHook(ForceEnumPlayers_org);
}
void ForceEnumPlayersCounted_init ( )
{
      ForceEnumPlayersCounted_org = (ForceEnumPlayersCounted_FUNC) ( GameDll + 0x1E0DC0 );
      MH_CreateHook(ForceEnumPlayersCounted_org, &ForceEnumPlayersCounted_my, reinterpret_cast<void**>(&ForceEnumPlayersCounted_ptr));
      MH_EnableHook(ForceEnumPlayersCounted_org);
}
void ForcePlayerStartLocation_init ( )
{
      ForcePlayerStartLocation_org = (ForcePlayerStartLocation_FUNC) ( GameDll + 0x1E0DF0 );
      MH_CreateHook(ForcePlayerStartLocation_org, &ForcePlayerStartLocation_my, reinterpret_cast<void**>(&ForcePlayerStartLocation_ptr));
      MH_EnableHook(ForcePlayerStartLocation_org);
}
void ForceQuestDialogUpdate_init ( )
{
      ForceQuestDialogUpdate_org = (ForceQuestDialogUpdate_FUNC) ( GameDll + 0x1E0E20 );
      MH_CreateHook(ForceQuestDialogUpdate_org, &ForceQuestDialogUpdate_my, reinterpret_cast<void**>(&ForceQuestDialogUpdate_ptr));
      MH_EnableHook(ForceQuestDialogUpdate_org);
}
void ForceRemovePlayer_init ( )
{
      ForceRemovePlayer_org = (ForceRemovePlayer_FUNC) ( GameDll + 0x1E0E50 );
      MH_CreateHook(ForceRemovePlayer_org, &ForceRemovePlayer_my, reinterpret_cast<void**>(&ForceRemovePlayer_ptr));
      MH_EnableHook(ForceRemovePlayer_org);
}
void ForceUICancel_init ( )
{
      ForceUICancel_org = (ForceUICancel_FUNC) ( GameDll + 0x1E0E80 );
      MH_CreateHook(ForceUICancel_org, &ForceUICancel_my, reinterpret_cast<void**>(&ForceUICancel_ptr));
      MH_EnableHook(ForceUICancel_org);
}
void ForceUIKey_init ( )
{
      ForceUIKey_org = (ForceUIKey_FUNC) ( GameDll + 0x1E0F00 );
      MH_CreateHook(ForceUIKey_org, &ForceUIKey_my, reinterpret_cast<void**>(&ForceUIKey_ptr));
      MH_EnableHook(ForceUIKey_org);
}
void GetAIDifficulty_init ( )
{
      GetAIDifficulty_org = (GetAIDifficulty_FUNC) ( GameDll + 0x1E1500 );
      MH_CreateHook(GetAIDifficulty_org, &GetAIDifficulty_my, reinterpret_cast<void**>(&GetAIDifficulty_ptr));
      MH_EnableHook(GetAIDifficulty_org);
}
void GetAbilityEffect_init ( )
{
      GetAbilityEffect_org = (GetAbilityEffect_FUNC) ( GameDll + 0x1E15A0 );
      MH_CreateHook(GetAbilityEffect_org, &GetAbilityEffect_my, reinterpret_cast<void**>(&GetAbilityEffect_ptr));
      MH_EnableHook(GetAbilityEffect_org);
}
void GetAbilityEffectById_init ( )
{
      GetAbilityEffectById_org = (GetAbilityEffectById_FUNC) ( GameDll + 0x1E15D0 );
      MH_CreateHook(GetAbilityEffectById_org, &GetAbilityEffectById_my, reinterpret_cast<void**>(&GetAbilityEffectById_ptr));
      MH_EnableHook(GetAbilityEffectById_org);
}
void GetAbilitySound_init ( )
{
      GetAbilitySound_org = (GetAbilitySound_FUNC) ( GameDll + 0x1E15F0 );
      MH_CreateHook(GetAbilitySound_org, &GetAbilitySound_my, reinterpret_cast<void**>(&GetAbilitySound_ptr));
      MH_EnableHook(GetAbilitySound_org);
}
void GetAbilitySoundById_init ( )
{
      GetAbilitySoundById_org = (GetAbilitySoundById_FUNC) ( GameDll + 0x1E1630 );
      MH_CreateHook(GetAbilitySoundById_org, &GetAbilitySoundById_my, reinterpret_cast<void**>(&GetAbilitySoundById_ptr));
      MH_EnableHook(GetAbilitySoundById_org);
}
void GetAiPlayer_init ( )
{
      GetAiPlayer_org = (GetAiPlayer_FUNC) ( GameDll + 0x88F280 );
      MH_CreateHook(GetAiPlayer_org, &GetAiPlayer_my, reinterpret_cast<void**>(&GetAiPlayer_ptr));
      MH_EnableHook(GetAiPlayer_org);
}
void GetAllianceTarget_init ( )
{
      GetAllianceTarget_org = (GetAllianceTarget_FUNC) ( GameDll + 0x88F2B0 );
      MH_CreateHook(GetAllianceTarget_org, &GetAllianceTarget_my, reinterpret_cast<void**>(&GetAllianceTarget_ptr));
      MH_EnableHook(GetAllianceTarget_org);
}
void GetAllyColorFilterState_init ( )
{
      GetAllyColorFilterState_org = (GetAllyColorFilterState_FUNC) ( GameDll + 0x1E1680 );
      MH_CreateHook(GetAllyColorFilterState_org, &GetAllyColorFilterState_my, reinterpret_cast<void**>(&GetAllyColorFilterState_ptr));
      MH_EnableHook(GetAllyColorFilterState_org);
}
void GetAttacker_init ( )
{
      GetAttacker_org = (GetAttacker_FUNC) ( GameDll + 0x1E16B0 );
      MH_CreateHook(GetAttacker_org, &GetAttacker_my, reinterpret_cast<void**>(&GetAttacker_ptr));
      MH_EnableHook(GetAttacker_org);
}
void GetBuilding_init ( )
{
      GetBuilding_org = (GetBuilding_FUNC) ( GameDll + 0x88F420 );
      MH_CreateHook(GetBuilding_org, &GetBuilding_my, reinterpret_cast<void**>(&GetBuilding_ptr));
      MH_EnableHook(GetBuilding_org);
}
void GetBuyingUnit_init ( )
{
      GetBuyingUnit_org = (GetBuyingUnit_FUNC) ( GameDll + 0x1E1730 );
      MH_CreateHook(GetBuyingUnit_org, &GetBuyingUnit_my, reinterpret_cast<void**>(&GetBuyingUnit_ptr));
      MH_EnableHook(GetBuyingUnit_org);
}
void GetCameraBoundMaxX_init ( )
{
      GetCameraBoundMaxX_org = (GetCameraBoundMaxX_FUNC) ( GameDll + 0x1E1810 );
      MH_CreateHook(GetCameraBoundMaxX_org, &GetCameraBoundMaxX_my, reinterpret_cast<void**>(&GetCameraBoundMaxX_ptr));
      MH_EnableHook(GetCameraBoundMaxX_org);
}
void GetCameraBoundMaxY_init ( )
{
      GetCameraBoundMaxY_org = (GetCameraBoundMaxY_FUNC) ( GameDll + 0x1E1840 );
      MH_CreateHook(GetCameraBoundMaxY_org, &GetCameraBoundMaxY_my, reinterpret_cast<void**>(&GetCameraBoundMaxY_ptr));
      MH_EnableHook(GetCameraBoundMaxY_org);
}
void GetCameraBoundMinX_init ( )
{
      GetCameraBoundMinX_org = (GetCameraBoundMinX_FUNC) ( GameDll + 0x1E1870 );
      MH_CreateHook(GetCameraBoundMinX_org, &GetCameraBoundMinX_my, reinterpret_cast<void**>(&GetCameraBoundMinX_ptr));
      MH_EnableHook(GetCameraBoundMinX_org);
}
void GetCameraBoundMinY_init ( )
{
      GetCameraBoundMinY_org = (GetCameraBoundMinY_FUNC) ( GameDll + 0x1E18A0 );
      MH_CreateHook(GetCameraBoundMinY_org, &GetCameraBoundMinY_my, reinterpret_cast<void**>(&GetCameraBoundMinY_ptr));
      MH_EnableHook(GetCameraBoundMinY_org);
}
void GetCameraEyePositionLoc_init ( )
{
      GetCameraEyePositionLoc_org = (GetCameraEyePositionLoc_FUNC) ( GameDll + 0x1E18E0 );
      MH_CreateHook(GetCameraEyePositionLoc_org, &GetCameraEyePositionLoc_my, reinterpret_cast<void**>(&GetCameraEyePositionLoc_ptr));
      MH_EnableHook(GetCameraEyePositionLoc_org);
}
void GetCameraEyePositionX_init ( )
{
      GetCameraEyePositionX_org = (GetCameraEyePositionX_FUNC) ( GameDll + 0x1E1930 );
      MH_CreateHook(GetCameraEyePositionX_org, &GetCameraEyePositionX_my, reinterpret_cast<void**>(&GetCameraEyePositionX_ptr));
      MH_EnableHook(GetCameraEyePositionX_org);
}
void GetCameraEyePositionY_init ( )
{
      GetCameraEyePositionY_org = (GetCameraEyePositionY_FUNC) ( GameDll + 0x1E1970 );
      MH_CreateHook(GetCameraEyePositionY_org, &GetCameraEyePositionY_my, reinterpret_cast<void**>(&GetCameraEyePositionY_ptr));
      MH_EnableHook(GetCameraEyePositionY_org);
}
void GetCameraEyePositionZ_init ( )
{
      GetCameraEyePositionZ_org = (GetCameraEyePositionZ_FUNC) ( GameDll + 0x1E19B0 );
      MH_CreateHook(GetCameraEyePositionZ_org, &GetCameraEyePositionZ_my, reinterpret_cast<void**>(&GetCameraEyePositionZ_ptr));
      MH_EnableHook(GetCameraEyePositionZ_org);
}
void GetCameraField_init ( )
{
      GetCameraField_org = (GetCameraField_FUNC) ( GameDll + 0x1E19F0 );
      MH_CreateHook(GetCameraField_org, &GetCameraField_my, reinterpret_cast<void**>(&GetCameraField_ptr));
      MH_EnableHook(GetCameraField_org);
}
void GetCameraMargin_init ( )
{
      GetCameraMargin_org = (GetCameraMargin_FUNC) ( GameDll + 0x1E1A20 );
      MH_CreateHook(GetCameraMargin_org, &GetCameraMargin_my, reinterpret_cast<void**>(&GetCameraMargin_ptr));
      MH_EnableHook(GetCameraMargin_org);
}
void GetCameraTargetPositionLoc_init ( )
{
      GetCameraTargetPositionLoc_org = (GetCameraTargetPositionLoc_FUNC) ( GameDll + 0x1E1A90 );
      MH_CreateHook(GetCameraTargetPositionLoc_org, &GetCameraTargetPositionLoc_my, reinterpret_cast<void**>(&GetCameraTargetPositionLoc_ptr));
      MH_EnableHook(GetCameraTargetPositionLoc_org);
}
void GetCameraTargetPositionX_init ( )
{
      GetCameraTargetPositionX_org = (GetCameraTargetPositionX_FUNC) ( GameDll + 0x1E1AE0 );
      MH_CreateHook(GetCameraTargetPositionX_org, &GetCameraTargetPositionX_my, reinterpret_cast<void**>(&GetCameraTargetPositionX_ptr));
      MH_EnableHook(GetCameraTargetPositionX_org);
}
void GetCameraTargetPositionY_init ( )
{
      GetCameraTargetPositionY_org = (GetCameraTargetPositionY_FUNC) ( GameDll + 0x1E1B20 );
      MH_CreateHook(GetCameraTargetPositionY_org, &GetCameraTargetPositionY_my, reinterpret_cast<void**>(&GetCameraTargetPositionY_ptr));
      MH_EnableHook(GetCameraTargetPositionY_org);
}
void GetCameraTargetPositionZ_init ( )
{
      GetCameraTargetPositionZ_org = (GetCameraTargetPositionZ_FUNC) ( GameDll + 0x1E1B60 );
      MH_CreateHook(GetCameraTargetPositionZ_org, &GetCameraTargetPositionZ_my, reinterpret_cast<void**>(&GetCameraTargetPositionZ_ptr));
      MH_EnableHook(GetCameraTargetPositionZ_org);
}
void GetCancelledStructure_init ( )
{
      GetCancelledStructure_org = (GetCancelledStructure_FUNC) ( GameDll + 0x1E1BA0 );
      MH_CreateHook(GetCancelledStructure_org, &GetCancelledStructure_my, reinterpret_cast<void**>(&GetCancelledStructure_ptr));
      MH_EnableHook(GetCancelledStructure_org);
}
void GetChangingUnit_init ( )
{
      GetChangingUnit_org = (GetChangingUnit_FUNC) ( GameDll + 0x1E1BC0 );
      MH_CreateHook(GetChangingUnit_org, &GetChangingUnit_my, reinterpret_cast<void**>(&GetChangingUnit_ptr));
      MH_EnableHook(GetChangingUnit_org);
}
void GetChangingUnitPrevOwner_init ( )
{
      GetChangingUnitPrevOwner_org = (GetChangingUnitPrevOwner_FUNC) ( GameDll + 0x1E1C40 );
      MH_CreateHook(GetChangingUnitPrevOwner_org, &GetChangingUnitPrevOwner_my, reinterpret_cast<void**>(&GetChangingUnitPrevOwner_ptr));
      MH_EnableHook(GetChangingUnitPrevOwner_org);
}
void GetClickedButton_init ( )
{
      GetClickedButton_org = (GetClickedButton_FUNC) ( GameDll + 0x1E1CD0 );
      MH_CreateHook(GetClickedButton_org, &GetClickedButton_my, reinterpret_cast<void**>(&GetClickedButton_ptr));
      MH_EnableHook(GetClickedButton_org);
}
void GetClickedDialog_init ( )
{
      GetClickedDialog_org = (GetClickedDialog_FUNC) ( GameDll + 0x1E1D20 );
      MH_CreateHook(GetClickedDialog_org, &GetClickedDialog_my, reinterpret_cast<void**>(&GetClickedDialog_ptr));
      MH_EnableHook(GetClickedDialog_org);
}
void GetConstructedStructure_init ( )
{
      GetConstructedStructure_org = (GetConstructedStructure_FUNC) ( GameDll + 0x1E1D90 );
      MH_CreateHook(GetConstructedStructure_org, &GetConstructedStructure_my, reinterpret_cast<void**>(&GetConstructedStructure_ptr));
      MH_EnableHook(GetConstructedStructure_org);
}
void GetConstructingStructure_init ( )
{
      GetConstructingStructure_org = (GetConstructingStructure_FUNC) ( GameDll + 0x1E1DB0 );
      MH_CreateHook(GetConstructingStructure_org, &GetConstructingStructure_my, reinterpret_cast<void**>(&GetConstructingStructure_ptr));
      MH_EnableHook(GetConstructingStructure_org);
}
void GetCreatureDensity_init ( )
{
      GetCreatureDensity_org = (GetCreatureDensity_FUNC) ( GameDll + 0x1E1E60 );
      MH_CreateHook(GetCreatureDensity_org, &GetCreatureDensity_my, reinterpret_cast<void**>(&GetCreatureDensity_ptr));
      MH_EnableHook(GetCreatureDensity_org);
}
void GetCreepCamp_init ( )
{
      GetCreepCamp_org = (GetCreepCamp_FUNC) ( GameDll + 0x88FAD0 );
      MH_CreateHook(GetCreepCamp_org, &GetCreepCamp_my, reinterpret_cast<void**>(&GetCreepCamp_ptr));
      MH_EnableHook(GetCreepCamp_org);
}
void GetCreepCampFilterState_init ( )
{
      GetCreepCampFilterState_org = (GetCreepCampFilterState_FUNC) ( GameDll + 0x1E1E70 );
      MH_CreateHook(GetCreepCampFilterState_org, &GetCreepCampFilterState_my, reinterpret_cast<void**>(&GetCreepCampFilterState_ptr));
      MH_EnableHook(GetCreepCampFilterState_org);
}
void GetCustomCampaignButtonVisible_init ( )
{
      GetCustomCampaignButtonVisible_org = (GetCustomCampaignButtonVisible_FUNC) ( GameDll + 0x1E1EA0 );
      MH_CreateHook(GetCustomCampaignButtonVisible_org, &GetCustomCampaignButtonVisible_my, reinterpret_cast<void**>(&GetCustomCampaignButtonVisible_ptr));
      MH_EnableHook(GetCustomCampaignButtonVisible_org);
}
void GetDecayingUnit_init ( )
{
      GetDecayingUnit_org = (GetDecayingUnit_FUNC) ( GameDll + 0x1E1ED0 );
      MH_CreateHook(GetDecayingUnit_org, &GetDecayingUnit_my, reinterpret_cast<void**>(&GetDecayingUnit_ptr));
      MH_EnableHook(GetDecayingUnit_org);
}
void GetDefaultDifficulty_init ( )
{
      GetDefaultDifficulty_org = (GetDefaultDifficulty_FUNC) ( GameDll + 0x1E1F10 );
      MH_CreateHook(GetDefaultDifficulty_org, &GetDefaultDifficulty_my, reinterpret_cast<void**>(&GetDefaultDifficulty_ptr));
      MH_EnableHook(GetDefaultDifficulty_org);
}
void GetDestructableLife_init ( )
{
      GetDestructableLife_org = (GetDestructableLife_FUNC) ( GameDll + 0x1E1F70 );
      MH_CreateHook(GetDestructableLife_org, &GetDestructableLife_my, reinterpret_cast<void**>(&GetDestructableLife_ptr));
      MH_EnableHook(GetDestructableLife_org);
}
void GetDestructableMaxLife_init ( )
{
      GetDestructableMaxLife_org = (GetDestructableMaxLife_FUNC) ( GameDll + 0x1E1FB0 );
      MH_CreateHook(GetDestructableMaxLife_org, &GetDestructableMaxLife_my, reinterpret_cast<void**>(&GetDestructableMaxLife_ptr));
      MH_EnableHook(GetDestructableMaxLife_org);
}
void GetDestructableName_init ( )
{
      GetDestructableName_org = (GetDestructableName_FUNC) ( GameDll + 0x1E1FE0 );
      MH_CreateHook(GetDestructableName_org, &GetDestructableName_my, reinterpret_cast<void**>(&GetDestructableName_ptr));
      MH_EnableHook(GetDestructableName_org);
}
void GetDestructableOccluderHeight_init ( )
{
      GetDestructableOccluderHeight_org = (GetDestructableOccluderHeight_FUNC) ( GameDll + 0x1E2010 );
      MH_CreateHook(GetDestructableOccluderHeight_org, &GetDestructableOccluderHeight_my, reinterpret_cast<void**>(&GetDestructableOccluderHeight_ptr));
      MH_EnableHook(GetDestructableOccluderHeight_org);
}
void GetDestructableTypeId_init ( )
{
      GetDestructableTypeId_org = (GetDestructableTypeId_FUNC) ( GameDll + 0x1E2030 );
      MH_CreateHook(GetDestructableTypeId_org, &GetDestructableTypeId_my, reinterpret_cast<void**>(&GetDestructableTypeId_ptr));
      MH_EnableHook(GetDestructableTypeId_org);
}
void GetDestructableX_init ( )
{
      GetDestructableX_org = (GetDestructableX_FUNC) ( GameDll + 0x1E2050 );
      MH_CreateHook(GetDestructableX_org, &GetDestructableX_my, reinterpret_cast<void**>(&GetDestructableX_ptr));
      MH_EnableHook(GetDestructableX_org);
}
void GetDestructableY_init ( )
{
      GetDestructableY_org = (GetDestructableY_FUNC) ( GameDll + 0x1E2090 );
      MH_CreateHook(GetDestructableY_org, &GetDestructableY_my, reinterpret_cast<void**>(&GetDestructableY_ptr));
      MH_EnableHook(GetDestructableY_org);
}
void GetDetectedUnit_init ( )
{
      GetDetectedUnit_org = (GetDetectedUnit_FUNC) ( GameDll + 0x1E20D0 );
      MH_CreateHook(GetDetectedUnit_org, &GetDetectedUnit_my, reinterpret_cast<void**>(&GetDetectedUnit_ptr));
      MH_EnableHook(GetDetectedUnit_org);
}
void GetDyingUnit_init ( )
{
      GetDyingUnit_org = (GetDyingUnit_FUNC) ( GameDll + 0x1E2110 );
      MH_CreateHook(GetDyingUnit_org, &GetDyingUnit_my, reinterpret_cast<void**>(&GetDyingUnit_ptr));
      MH_EnableHook(GetDyingUnit_org);
}
void GetEnemyBase_init ( )
{
      GetEnemyBase_org = (GetEnemyBase_FUNC) ( GameDll + 0x88FB10 );
      MH_CreateHook(GetEnemyBase_org, &GetEnemyBase_my, reinterpret_cast<void**>(&GetEnemyBase_ptr));
      MH_EnableHook(GetEnemyBase_org);
}
void GetEnemyExpansion_init ( )
{
      GetEnemyExpansion_org = (GetEnemyExpansion_FUNC) ( GameDll + 0x88FB50 );
      MH_CreateHook(GetEnemyExpansion_org, &GetEnemyExpansion_my, reinterpret_cast<void**>(&GetEnemyExpansion_ptr));
      MH_EnableHook(GetEnemyExpansion_org);
}
void GetEnemyPower_init ( )
{
      GetEnemyPower_org = (GetEnemyPower_FUNC) ( GameDll + 0x88FB90 );
      MH_CreateHook(GetEnemyPower_org, &GetEnemyPower_my, reinterpret_cast<void**>(&GetEnemyPower_ptr));
      MH_EnableHook(GetEnemyPower_org);
}
void GetEnteringUnit_init ( )
{
      GetEnteringUnit_org = (GetEnteringUnit_FUNC) ( GameDll + 0x1E2130 );
      MH_CreateHook(GetEnteringUnit_org, &GetEnteringUnit_my, reinterpret_cast<void**>(&GetEnteringUnit_ptr));
      MH_EnableHook(GetEnteringUnit_org);
}
void GetEnumDestructable_init ( )
{
      GetEnumDestructable_org = (GetEnumDestructable_FUNC) ( GameDll + 0x1E2150 );
      MH_CreateHook(GetEnumDestructable_org, &GetEnumDestructable_my, reinterpret_cast<void**>(&GetEnumDestructable_ptr));
      MH_EnableHook(GetEnumDestructable_org);
}
void GetEnumItem_init ( )
{
      GetEnumItem_org = (GetEnumItem_FUNC) ( GameDll + 0x1E2170 );
      MH_CreateHook(GetEnumItem_org, &GetEnumItem_my, reinterpret_cast<void**>(&GetEnumItem_ptr));
      MH_EnableHook(GetEnumItem_org);
}
void GetEnumPlayer_init ( )
{
      GetEnumPlayer_org = (GetEnumPlayer_FUNC) ( GameDll + 0x1E2190 );
      MH_CreateHook(GetEnumPlayer_org, &GetEnumPlayer_my, reinterpret_cast<void**>(&GetEnumPlayer_ptr));
      MH_EnableHook(GetEnumPlayer_org);
}
void GetEnumUnit_init ( )
{
      GetEnumUnit_org = (GetEnumUnit_FUNC) ( GameDll + 0x1E21B0 );
      MH_CreateHook(GetEnumUnit_org, &GetEnumUnit_my, reinterpret_cast<void**>(&GetEnumUnit_ptr));
      MH_EnableHook(GetEnumUnit_org);
}
void GetEventDamage_init ( )
{
      GetEventDamage_org = (GetEventDamage_FUNC) ( GameDll + 0x1E21D0 );
      MH_CreateHook(GetEventDamage_org, &GetEventDamage_my, reinterpret_cast<void**>(&GetEventDamage_ptr));
      MH_EnableHook(GetEventDamage_org);
}
void GetEventDamageSource_init ( )
{
      GetEventDamageSource_org = (GetEventDamageSource_FUNC) ( GameDll + 0x1E21F0 );
      MH_CreateHook(GetEventDamageSource_org, &GetEventDamageSource_my, reinterpret_cast<void**>(&GetEventDamageSource_ptr));
      MH_EnableHook(GetEventDamageSource_org);
}
void GetEventDetectingPlayer_init ( )
{
      GetEventDetectingPlayer_org = (GetEventDetectingPlayer_FUNC) ( GameDll + 0x1E2260 );
      MH_CreateHook(GetEventDetectingPlayer_org, &GetEventDetectingPlayer_my, reinterpret_cast<void**>(&GetEventDetectingPlayer_ptr));
      MH_EnableHook(GetEventDetectingPlayer_org);
}
void GetEventGameState_init ( )
{
      GetEventGameState_org = (GetEventGameState_FUNC) ( GameDll + 0x1E22B0 );
      MH_CreateHook(GetEventGameState_org, &GetEventGameState_my, reinterpret_cast<void**>(&GetEventGameState_ptr));
      MH_EnableHook(GetEventGameState_org);
}
void GetEventPlayerChatString_init ( )
{
      GetEventPlayerChatString_org = (GetEventPlayerChatString_FUNC) ( GameDll + 0x1E22E0 );
      MH_CreateHook(GetEventPlayerChatString_org, &GetEventPlayerChatString_my, reinterpret_cast<void**>(&GetEventPlayerChatString_ptr));
      MH_EnableHook(GetEventPlayerChatString_org);
}
void GetEventPlayerChatStringMatched_init ( )
{
      GetEventPlayerChatStringMatched_org = (GetEventPlayerChatStringMatched_FUNC) ( GameDll + 0x1E2320 );
      MH_CreateHook(GetEventPlayerChatStringMatched_org, &GetEventPlayerChatStringMatched_my, reinterpret_cast<void**>(&GetEventPlayerChatStringMatched_ptr));
      MH_EnableHook(GetEventPlayerChatStringMatched_org);
}
void GetEventPlayerState_init ( )
{
      GetEventPlayerState_org = (GetEventPlayerState_FUNC) ( GameDll + 0x1E2350 );
      MH_CreateHook(GetEventPlayerState_org, &GetEventPlayerState_my, reinterpret_cast<void**>(&GetEventPlayerState_ptr));
      MH_EnableHook(GetEventPlayerState_org);
}
void GetEventTargetUnit_init ( )
{
      GetEventTargetUnit_org = (GetEventTargetUnit_FUNC) ( GameDll + 0x1E2380 );
      MH_CreateHook(GetEventTargetUnit_org, &GetEventTargetUnit_my, reinterpret_cast<void**>(&GetEventTargetUnit_ptr));
      MH_EnableHook(GetEventTargetUnit_org);
}
void GetEventUnitState_init ( )
{
      GetEventUnitState_org = (GetEventUnitState_FUNC) ( GameDll + 0x1E23D0 );
      MH_CreateHook(GetEventUnitState_org, &GetEventUnitState_my, reinterpret_cast<void**>(&GetEventUnitState_ptr));
      MH_EnableHook(GetEventUnitState_org);
}
void GetExpansionFoe_init ( )
{
      GetExpansionFoe_org = (GetExpansionFoe_FUNC) ( GameDll + 0x88FBA0 );
      MH_CreateHook(GetExpansionFoe_org, &GetExpansionFoe_my, reinterpret_cast<void**>(&GetExpansionFoe_ptr));
      MH_EnableHook(GetExpansionFoe_org);
}
void GetExpansionPeon_init ( )
{
      GetExpansionPeon_org = (GetExpansionPeon_FUNC) ( GameDll + 0x88FC50 );
      MH_CreateHook(GetExpansionPeon_org, &GetExpansionPeon_my, reinterpret_cast<void**>(&GetExpansionPeon_ptr));
      MH_EnableHook(GetExpansionPeon_org);
}
void GetExpansionX_init ( )
{
      GetExpansionX_org = (GetExpansionX_FUNC) ( GameDll + 0x88FC90 );
      MH_CreateHook(GetExpansionX_org, &GetExpansionX_my, reinterpret_cast<void**>(&GetExpansionX_ptr));
      MH_EnableHook(GetExpansionX_org);
}
void GetExpansionY_init ( )
{
      GetExpansionY_org = (GetExpansionY_FUNC) ( GameDll + 0x88FD10 );
      MH_CreateHook(GetExpansionY_org, &GetExpansionY_my, reinterpret_cast<void**>(&GetExpansionY_ptr));
      MH_EnableHook(GetExpansionY_org);
}
void GetExpiredTimer_init ( )
{
      GetExpiredTimer_org = (GetExpiredTimer_FUNC) ( GameDll + 0x1E2410 );
      MH_CreateHook(GetExpiredTimer_org, &GetExpiredTimer_my, reinterpret_cast<void**>(&GetExpiredTimer_ptr));
      MH_EnableHook(GetExpiredTimer_org);
}
void GetFilterDestructable_init ( )
{
      GetFilterDestructable_org = (GetFilterDestructable_FUNC) ( GameDll + 0x1E2470 );
      MH_CreateHook(GetFilterDestructable_org, &GetFilterDestructable_my, reinterpret_cast<void**>(&GetFilterDestructable_ptr));
      MH_EnableHook(GetFilterDestructable_org);
}
void GetFilterItem_init ( )
{
      GetFilterItem_org = (GetFilterItem_FUNC) ( GameDll + 0x1E2490 );
      MH_CreateHook(GetFilterItem_org, &GetFilterItem_my, reinterpret_cast<void**>(&GetFilterItem_ptr));
      MH_EnableHook(GetFilterItem_org);
}
void GetFilterPlayer_init ( )
{
      GetFilterPlayer_org = (GetFilterPlayer_FUNC) ( GameDll + 0x1E24B0 );
      MH_CreateHook(GetFilterPlayer_org, &GetFilterPlayer_my, reinterpret_cast<void**>(&GetFilterPlayer_ptr));
      MH_EnableHook(GetFilterPlayer_org);
}
void GetFilterUnit_init ( )
{
      GetFilterUnit_org = (GetFilterUnit_FUNC) ( GameDll + 0x1E24D0 );
      MH_CreateHook(GetFilterUnit_org, &GetFilterUnit_my, reinterpret_cast<void**>(&GetFilterUnit_ptr));
      MH_EnableHook(GetFilterUnit_org);
}
void GetFloatGameState_init ( )
{
      GetFloatGameState_org = (GetFloatGameState_FUNC) ( GameDll + 0x1E2500 );
      MH_CreateHook(GetFloatGameState_org, &GetFloatGameState_my, reinterpret_cast<void**>(&GetFloatGameState_ptr));
      MH_EnableHook(GetFloatGameState_org);
}
void GetFoodMade_init ( )
{
      GetFoodMade_org = (GetFoodMade_FUNC) ( GameDll + 0x1E2560 );
      MH_CreateHook(GetFoodMade_org, &GetFoodMade_my, reinterpret_cast<void**>(&GetFoodMade_ptr));
      MH_EnableHook(GetFoodMade_org);
}
void GetFoodUsed_init ( )
{
      GetFoodUsed_org = (GetFoodUsed_FUNC) ( GameDll + 0x1E2570 );
      MH_CreateHook(GetFoodUsed_org, &GetFoodUsed_my, reinterpret_cast<void**>(&GetFoodUsed_ptr));
      MH_EnableHook(GetFoodUsed_org);
}
void GetGameDifficulty_init ( )
{
      GetGameDifficulty_org = (GetGameDifficulty_FUNC) ( GameDll + 0x1E2760 );
      MH_CreateHook(GetGameDifficulty_org, &GetGameDifficulty_my, reinterpret_cast<void**>(&GetGameDifficulty_ptr));
      MH_EnableHook(GetGameDifficulty_org);
}
void GetGamePlacement_init ( )
{
      GetGamePlacement_org = (GetGamePlacement_FUNC) ( GameDll + 0x1E2770 );
      MH_CreateHook(GetGamePlacement_org, &GetGamePlacement_my, reinterpret_cast<void**>(&GetGamePlacement_ptr));
      MH_EnableHook(GetGamePlacement_org);
}
void GetGameSpeed_init ( )
{
      GetGameSpeed_org = (GetGameSpeed_FUNC) ( GameDll + 0x1E2780 );
      MH_CreateHook(GetGameSpeed_org, &GetGameSpeed_my, reinterpret_cast<void**>(&GetGameSpeed_ptr));
      MH_EnableHook(GetGameSpeed_org);
}
void GetGameTypeSelected_init ( )
{
      GetGameTypeSelected_org = (GetGameTypeSelected_FUNC) ( GameDll + 0x1E2790 );
      MH_CreateHook(GetGameTypeSelected_org, &GetGameTypeSelected_my, reinterpret_cast<void**>(&GetGameTypeSelected_ptr));
      MH_EnableHook(GetGameTypeSelected_org);
}
void GetGoldOwned_init ( )
{
      GetGoldOwned_org = (GetGoldOwned_FUNC) ( GameDll + 0x88FDA0 );
      MH_CreateHook(GetGoldOwned_org, &GetGoldOwned_my, reinterpret_cast<void**>(&GetGoldOwned_ptr));
      MH_EnableHook(GetGoldOwned_org);
}
void GetHandleId_init ( )
{
      GetHandleId_org = (GetHandleId_FUNC) ( GameDll + 0x1E27A0 );
      MH_CreateHook(GetHandleId_org, &GetHandleId_my, reinterpret_cast<void**>(&GetHandleId_ptr));
      MH_EnableHook(GetHandleId_org);
}
void GetHeroAgi_init ( )
{
      GetHeroAgi_org = (GetHeroAgi_FUNC) ( GameDll + 0x1E27B0 );
      MH_CreateHook(GetHeroAgi_org, &GetHeroAgi_my, reinterpret_cast<void**>(&GetHeroAgi_ptr));
      MH_EnableHook(GetHeroAgi_org);
}
void GetHeroId_init ( )
{
      GetHeroId_org = (GetHeroId_FUNC) ( GameDll + 0x88FDD0 );
      MH_CreateHook(GetHeroId_org, &GetHeroId_my, reinterpret_cast<void**>(&GetHeroId_ptr));
      MH_EnableHook(GetHeroId_org);
}
void GetHeroInt_init ( )
{
      GetHeroInt_org = (GetHeroInt_FUNC) ( GameDll + 0x1E2810 );
      MH_CreateHook(GetHeroInt_org, &GetHeroInt_my, reinterpret_cast<void**>(&GetHeroInt_ptr));
      MH_EnableHook(GetHeroInt_org);
}
void GetHeroLevel_init ( )
{
      GetHeroLevel_org = (GetHeroLevel_FUNC) ( GameDll + 0x1E2870 );
      MH_CreateHook(GetHeroLevel_org, &GetHeroLevel_my, reinterpret_cast<void**>(&GetHeroLevel_ptr));
      MH_EnableHook(GetHeroLevel_org);
}
void GetHeroLevelAI_init ( )
{
      GetHeroLevelAI_org = (GetHeroLevelAI_FUNC) ( GameDll + 0x88FE50 );
      MH_CreateHook(GetHeroLevelAI_org, &GetHeroLevelAI_my, reinterpret_cast<void**>(&GetHeroLevelAI_ptr));
      MH_EnableHook(GetHeroLevelAI_org);
}
void GetHeroProperName_init ( )
{
      GetHeroProperName_org = (GetHeroProperName_FUNC) ( GameDll + 0x1E28D0 );
      MH_CreateHook(GetHeroProperName_org, &GetHeroProperName_my, reinterpret_cast<void**>(&GetHeroProperName_ptr));
      MH_EnableHook(GetHeroProperName_org);
}
void GetHeroSkillPoints_init ( )
{
      GetHeroSkillPoints_org = (GetHeroSkillPoints_FUNC) ( GameDll + 0x1E2970 );
      MH_CreateHook(GetHeroSkillPoints_org, &GetHeroSkillPoints_my, reinterpret_cast<void**>(&GetHeroSkillPoints_ptr));
      MH_EnableHook(GetHeroSkillPoints_org);
}
void GetHeroStr_init ( )
{
      GetHeroStr_org = (GetHeroStr_FUNC) ( GameDll + 0x1E29D0 );
      MH_CreateHook(GetHeroStr_org, &GetHeroStr_my, reinterpret_cast<void**>(&GetHeroStr_ptr));
      MH_EnableHook(GetHeroStr_org);
}
void GetHeroXP_init ( )
{
      GetHeroXP_org = (GetHeroXP_FUNC) ( GameDll + 0x1E2A30 );
      MH_CreateHook(GetHeroXP_org, &GetHeroXP_my, reinterpret_cast<void**>(&GetHeroXP_ptr));
      MH_EnableHook(GetHeroXP_org);
}
void GetIntegerGameState_init ( )
{
      GetIntegerGameState_org = (GetIntegerGameState_FUNC) ( GameDll + 0x1E2B30 );
      MH_CreateHook(GetIntegerGameState_org, &GetIntegerGameState_my, reinterpret_cast<void**>(&GetIntegerGameState_ptr));
      MH_EnableHook(GetIntegerGameState_org);
}
void GetIssuedOrderId_init ( )
{
      GetIssuedOrderId_org = (GetIssuedOrderId_FUNC) ( GameDll + 0x1E2B60 );
      MH_CreateHook(GetIssuedOrderId_org, &GetIssuedOrderId_my, reinterpret_cast<void**>(&GetIssuedOrderId_ptr));
      MH_EnableHook(GetIssuedOrderId_org);
}
void GetItemCharges_init ( )
{
      GetItemCharges_org = (GetItemCharges_FUNC) ( GameDll + 0x1E2BE0 );
      MH_CreateHook(GetItemCharges_org, &GetItemCharges_my, reinterpret_cast<void**>(&GetItemCharges_ptr));
      MH_EnableHook(GetItemCharges_org);
}
void GetItemLevel_init ( )
{
      GetItemLevel_org = (GetItemLevel_FUNC) ( GameDll + 0x1E2C00 );
      MH_CreateHook(GetItemLevel_org, &GetItemLevel_my, reinterpret_cast<void**>(&GetItemLevel_ptr));
      MH_EnableHook(GetItemLevel_org);
}
void GetItemName_init ( )
{
      GetItemName_org = (GetItemName_FUNC) ( GameDll + 0x1E2C20 );
      MH_CreateHook(GetItemName_org, &GetItemName_my, reinterpret_cast<void**>(&GetItemName_ptr));
      MH_EnableHook(GetItemName_org);
}
void GetItemPlayer_init ( )
{
      GetItemPlayer_org = (GetItemPlayer_FUNC) ( GameDll + 0x1E2C50 );
      MH_CreateHook(GetItemPlayer_org, &GetItemPlayer_my, reinterpret_cast<void**>(&GetItemPlayer_ptr));
      MH_EnableHook(GetItemPlayer_org);
}
void GetItemType_init ( )
{
      GetItemType_org = (GetItemType_FUNC) ( GameDll + 0x1E2CA0 );
      MH_CreateHook(GetItemType_org, &GetItemType_my, reinterpret_cast<void**>(&GetItemType_ptr));
      MH_EnableHook(GetItemType_org);
}
void GetItemTypeId_init ( )
{
      GetItemTypeId_org = (GetItemTypeId_FUNC) ( GameDll + 0x1E2CC0 );
      MH_CreateHook(GetItemTypeId_org, &GetItemTypeId_my, reinterpret_cast<void**>(&GetItemTypeId_ptr));
      MH_EnableHook(GetItemTypeId_org);
}
void GetItemUserData_init ( )
{
      GetItemUserData_org = (GetItemUserData_FUNC) ( GameDll + 0x1E2CE0 );
      MH_CreateHook(GetItemUserData_org, &GetItemUserData_my, reinterpret_cast<void**>(&GetItemUserData_ptr));
      MH_EnableHook(GetItemUserData_org);
}
void GetItemX_init ( )
{
      GetItemX_org = (GetItemX_FUNC) ( GameDll + 0x1E2D00 );
      MH_CreateHook(GetItemX_org, &GetItemX_my, reinterpret_cast<void**>(&GetItemX_ptr));
      MH_EnableHook(GetItemX_org);
}
void GetItemY_init ( )
{
      GetItemY_org = (GetItemY_FUNC) ( GameDll + 0x1E2D40 );
      MH_CreateHook(GetItemY_org, &GetItemY_my, reinterpret_cast<void**>(&GetItemY_ptr));
      MH_EnableHook(GetItemY_org);
}
void GetKillingUnit_init ( )
{
      GetKillingUnit_org = (GetKillingUnit_FUNC) ( GameDll + 0x1E2DC0 );
      MH_CreateHook(GetKillingUnit_org, &GetKillingUnit_my, reinterpret_cast<void**>(&GetKillingUnit_ptr));
      MH_EnableHook(GetKillingUnit_org);
}
void GetLastCommand_init ( )
{
      GetLastCommand_org = (GetLastCommand_FUNC) ( GameDll + 0x88FEC0 );
      MH_CreateHook(GetLastCommand_org, &GetLastCommand_my, reinterpret_cast<void**>(&GetLastCommand_ptr));
      MH_EnableHook(GetLastCommand_org);
}
void GetLastData_init ( )
{
      GetLastData_org = (GetLastData_FUNC) ( GameDll + 0x88FF00 );
      MH_CreateHook(GetLastData_org, &GetLastData_my, reinterpret_cast<void**>(&GetLastData_ptr));
      MH_EnableHook(GetLastData_org);
}
void GetLearnedSkill_init ( )
{
      GetLearnedSkill_org = (GetLearnedSkill_FUNC) ( GameDll + 0x1E2E30 );
      MH_CreateHook(GetLearnedSkill_org, &GetLearnedSkill_my, reinterpret_cast<void**>(&GetLearnedSkill_ptr));
      MH_EnableHook(GetLearnedSkill_org);
}
void GetLearnedSkillLevel_init ( )
{
      GetLearnedSkillLevel_org = (GetLearnedSkillLevel_FUNC) ( GameDll + 0x1E2E70 );
      MH_CreateHook(GetLearnedSkillLevel_org, &GetLearnedSkillLevel_my, reinterpret_cast<void**>(&GetLearnedSkillLevel_ptr));
      MH_EnableHook(GetLearnedSkillLevel_org);
}
void GetLearningUnit_init ( )
{
      GetLearningUnit_org = (GetLearningUnit_FUNC) ( GameDll + 0x1E2EB0 );
      MH_CreateHook(GetLearningUnit_org, &GetLearningUnit_my, reinterpret_cast<void**>(&GetLearningUnit_ptr));
      MH_EnableHook(GetLearningUnit_org);
}
void GetLeavingUnit_init ( )
{
      GetLeavingUnit_org = (GetLeavingUnit_FUNC) ( GameDll + 0x1E2F10 );
      MH_CreateHook(GetLeavingUnit_org, &GetLeavingUnit_my, reinterpret_cast<void**>(&GetLeavingUnit_ptr));
      MH_EnableHook(GetLeavingUnit_org);
}
void GetLevelingUnit_init ( )
{
      GetLevelingUnit_org = (GetLevelingUnit_FUNC) ( GameDll + 0x1E2F50 );
      MH_CreateHook(GetLevelingUnit_org, &GetLevelingUnit_my, reinterpret_cast<void**>(&GetLevelingUnit_ptr));
      MH_EnableHook(GetLevelingUnit_org);
}
void GetLightningColorA_init ( )
{
      GetLightningColorA_org = (GetLightningColorA_FUNC) ( GameDll + 0x1E2FB0 );
      MH_CreateHook(GetLightningColorA_org, &GetLightningColorA_my, reinterpret_cast<void**>(&GetLightningColorA_ptr));
      MH_EnableHook(GetLightningColorA_org);
}
void GetLightningColorB_init ( )
{
      GetLightningColorB_org = (GetLightningColorB_FUNC) ( GameDll + 0x1E3000 );
      MH_CreateHook(GetLightningColorB_org, &GetLightningColorB_my, reinterpret_cast<void**>(&GetLightningColorB_ptr));
      MH_EnableHook(GetLightningColorB_org);
}
void GetLightningColorG_init ( )
{
      GetLightningColorG_org = (GetLightningColorG_FUNC) ( GameDll + 0x1E3050 );
      MH_CreateHook(GetLightningColorG_org, &GetLightningColorG_my, reinterpret_cast<void**>(&GetLightningColorG_ptr));
      MH_EnableHook(GetLightningColorG_org);
}
void GetLightningColorR_init ( )
{
      GetLightningColorR_org = (GetLightningColorR_FUNC) ( GameDll + 0x1E30A0 );
      MH_CreateHook(GetLightningColorR_org, &GetLightningColorR_my, reinterpret_cast<void**>(&GetLightningColorR_ptr));
      MH_EnableHook(GetLightningColorR_org);
}
void GetLoadedUnit_init ( )
{
      GetLoadedUnit_org = (GetLoadedUnit_FUNC) ( GameDll + 0x1E30F0 );
      MH_CreateHook(GetLoadedUnit_org, &GetLoadedUnit_my, reinterpret_cast<void**>(&GetLoadedUnit_ptr));
      MH_EnableHook(GetLoadedUnit_org);
}
void GetLocalPlayer_init ( )
{
      GetLocalPlayer_org = (GetLocalPlayer_FUNC) ( GameDll + 0x1E3150 );
      MH_CreateHook(GetLocalPlayer_org, &GetLocalPlayer_my, reinterpret_cast<void**>(&GetLocalPlayer_ptr));
      MH_EnableHook(GetLocalPlayer_org);
}
void GetLocalizedHotkey_init ( )
{
      GetLocalizedHotkey_org = (GetLocalizedHotkey_FUNC) ( GameDll + 0x1E31A0 );
      MH_CreateHook(GetLocalizedHotkey_org, &GetLocalizedHotkey_my, reinterpret_cast<void**>(&GetLocalizedHotkey_ptr));
      MH_EnableHook(GetLocalizedHotkey_org);
}
void GetLocalizedString_init ( )
{
      GetLocalizedString_org = (GetLocalizedString_FUNC) ( GameDll + 0x1E31D0 );
      MH_CreateHook(GetLocalizedString_org, &GetLocalizedString_my, reinterpret_cast<void**>(&GetLocalizedString_ptr));
      MH_EnableHook(GetLocalizedString_org);
}
void GetLocationX_init ( )
{
      GetLocationX_org = (GetLocationX_FUNC) ( GameDll + 0x1E3240 );
      MH_CreateHook(GetLocationX_org, &GetLocationX_my, reinterpret_cast<void**>(&GetLocationX_ptr));
      MH_EnableHook(GetLocationX_org);
}
void GetLocationY_init ( )
{
      GetLocationY_org = (GetLocationY_FUNC) ( GameDll + 0x1E3260 );
      MH_CreateHook(GetLocationY_org, &GetLocationY_my, reinterpret_cast<void**>(&GetLocationY_ptr));
      MH_EnableHook(GetLocationY_org);
}
void GetLocationZ_init ( )
{
      GetLocationZ_org = (GetLocationZ_FUNC) ( GameDll + 0x1E3280 );
      MH_CreateHook(GetLocationZ_org, &GetLocationZ_my, reinterpret_cast<void**>(&GetLocationZ_ptr));
      MH_EnableHook(GetLocationZ_org);
}
void GetManipulatedItem_init ( )
{
      GetManipulatedItem_org = (GetManipulatedItem_FUNC) ( GameDll + 0x1E32E0 );
      MH_CreateHook(GetManipulatedItem_org, &GetManipulatedItem_my, reinterpret_cast<void**>(&GetManipulatedItem_ptr));
      MH_EnableHook(GetManipulatedItem_org);
}
void GetManipulatingUnit_init ( )
{
      GetManipulatingUnit_org = (GetManipulatingUnit_FUNC) ( GameDll + 0x1E3380 );
      MH_CreateHook(GetManipulatingUnit_org, &GetManipulatingUnit_my, reinterpret_cast<void**>(&GetManipulatingUnit_ptr));
      MH_EnableHook(GetManipulatingUnit_org);
}
void GetMegaTarget_init ( )
{
      GetMegaTarget_org = (GetMegaTarget_FUNC) ( GameDll + 0x890050 );
      MH_CreateHook(GetMegaTarget_org, &GetMegaTarget_my, reinterpret_cast<void**>(&GetMegaTarget_ptr));
      MH_EnableHook(GetMegaTarget_org);
}
void GetMinesOwned_init ( )
{
      GetMinesOwned_org = (GetMinesOwned_FUNC) ( GameDll + 0x890090 );
      MH_CreateHook(GetMinesOwned_org, &GetMinesOwned_my, reinterpret_cast<void**>(&GetMinesOwned_ptr));
      MH_EnableHook(GetMinesOwned_org);
}
void GetNextExpansion_init ( )
{
      GetNextExpansion_org = (GetNextExpansion_FUNC) ( GameDll + 0x8900E0 );
      MH_CreateHook(GetNextExpansion_org, &GetNextExpansion_my, reinterpret_cast<void**>(&GetNextExpansion_ptr));
      MH_EnableHook(GetNextExpansion_org);
}
void GetObjectName_init ( )
{
      GetObjectName_org = (GetObjectName_FUNC) ( GameDll + 0x1E34A0 );
      MH_CreateHook(GetObjectName_org, &GetObjectName_my, reinterpret_cast<void**>(&GetObjectName_ptr));
      MH_EnableHook(GetObjectName_org);
}
void GetOrderPointLoc_init ( )
{
      GetOrderPointLoc_org = (GetOrderPointLoc_FUNC) ( GameDll + 0x1E3520 );
      MH_CreateHook(GetOrderPointLoc_org, &GetOrderPointLoc_my, reinterpret_cast<void**>(&GetOrderPointLoc_ptr));
      MH_EnableHook(GetOrderPointLoc_org);
}
void GetOrderPointX_init ( )
{
      GetOrderPointX_org = (GetOrderPointX_FUNC) ( GameDll + 0x1E35C0 );
      MH_CreateHook(GetOrderPointX_org, &GetOrderPointX_my, reinterpret_cast<void**>(&GetOrderPointX_ptr));
      MH_EnableHook(GetOrderPointX_org);
}
void GetOrderPointY_init ( )
{
      GetOrderPointY_org = (GetOrderPointY_FUNC) ( GameDll + 0x1E3610 );
      MH_CreateHook(GetOrderPointY_org, &GetOrderPointY_my, reinterpret_cast<void**>(&GetOrderPointY_ptr));
      MH_EnableHook(GetOrderPointY_org);
}
void GetOrderTarget_init ( )
{
      GetOrderTarget_org = (GetOrderTarget_FUNC) ( GameDll + 0x1E3660 );
      MH_CreateHook(GetOrderTarget_org, &GetOrderTarget_my, reinterpret_cast<void**>(&GetOrderTarget_ptr));
      MH_EnableHook(GetOrderTarget_org);
}
void GetOrderTargetDestructable_init ( )
{
      GetOrderTargetDestructable_org = (GetOrderTargetDestructable_FUNC) ( GameDll + 0x1E37C0 );
      MH_CreateHook(GetOrderTargetDestructable_org, &GetOrderTargetDestructable_my, reinterpret_cast<void**>(&GetOrderTargetDestructable_ptr));
      MH_EnableHook(GetOrderTargetDestructable_org);
}
void GetOrderTargetItem_init ( )
{
      GetOrderTargetItem_org = (GetOrderTargetItem_FUNC) ( GameDll + 0x1E38E0 );
      MH_CreateHook(GetOrderTargetItem_org, &GetOrderTargetItem_my, reinterpret_cast<void**>(&GetOrderTargetItem_ptr));
      MH_EnableHook(GetOrderTargetItem_org);
}
void GetOrderTargetUnit_init ( )
{
      GetOrderTargetUnit_org = (GetOrderTargetUnit_FUNC) ( GameDll + 0x1E3A00 );
      MH_CreateHook(GetOrderTargetUnit_org, &GetOrderTargetUnit_my, reinterpret_cast<void**>(&GetOrderTargetUnit_ptr));
      MH_EnableHook(GetOrderTargetUnit_org);
}
void GetOrderedUnit_init ( )
{
      GetOrderedUnit_org = (GetOrderedUnit_FUNC) ( GameDll + 0x1E3B20 );
      MH_CreateHook(GetOrderedUnit_org, &GetOrderedUnit_my, reinterpret_cast<void**>(&GetOrderedUnit_ptr));
      MH_EnableHook(GetOrderedUnit_org);
}
void GetOwningPlayer_init ( )
{
      GetOwningPlayer_org = (GetOwningPlayer_FUNC) ( GameDll + 0x1E3BA0 );
      MH_CreateHook(GetOwningPlayer_org, &GetOwningPlayer_my, reinterpret_cast<void**>(&GetOwningPlayer_ptr));
      MH_EnableHook(GetOwningPlayer_org);
}
void GetPlayerAlliance_init ( )
{
      GetPlayerAlliance_org = (GetPlayerAlliance_FUNC) ( GameDll + 0x1E3C50 );
      MH_CreateHook(GetPlayerAlliance_org, &GetPlayerAlliance_my, reinterpret_cast<void**>(&GetPlayerAlliance_ptr));
      MH_EnableHook(GetPlayerAlliance_org);
}
void GetPlayerColor_init ( )
{
      GetPlayerColor_org = (GetPlayerColor_FUNC) ( GameDll + 0x1E3CA0 );
      MH_CreateHook(GetPlayerColor_org, &GetPlayerColor_my, reinterpret_cast<void**>(&GetPlayerColor_ptr));
      MH_EnableHook(GetPlayerColor_org);
}
void GetPlayerController_init ( )
{
      GetPlayerController_org = (GetPlayerController_FUNC) ( GameDll + 0x1E3CC0 );
      MH_CreateHook(GetPlayerController_org, &GetPlayerController_my, reinterpret_cast<void**>(&GetPlayerController_ptr));
      MH_EnableHook(GetPlayerController_org);
}
void GetPlayerHandicap_init ( )
{
      GetPlayerHandicap_org = (GetPlayerHandicap_FUNC) ( GameDll + 0x1E3CE0 );
      MH_CreateHook(GetPlayerHandicap_org, &GetPlayerHandicap_my, reinterpret_cast<void**>(&GetPlayerHandicap_ptr));
      MH_EnableHook(GetPlayerHandicap_org);
}
void GetPlayerHandicapXP_init ( )
{
      GetPlayerHandicapXP_org = (GetPlayerHandicapXP_FUNC) ( GameDll + 0x1E3D00 );
      MH_CreateHook(GetPlayerHandicapXP_org, &GetPlayerHandicapXP_my, reinterpret_cast<void**>(&GetPlayerHandicapXP_ptr));
      MH_EnableHook(GetPlayerHandicapXP_org);
}
void GetPlayerId_init ( )
{
      GetPlayerId_org = (GetPlayerId_FUNC) ( GameDll + 0x1E3D20 );
      MH_CreateHook(GetPlayerId_org, &GetPlayerId_my, reinterpret_cast<void**>(&GetPlayerId_ptr));
      MH_EnableHook(GetPlayerId_org);
}
void GetPlayerName_init ( )
{
      GetPlayerName_org = (GetPlayerName_FUNC) ( GameDll + 0x1E3D40 );
      MH_CreateHook(GetPlayerName_org, &GetPlayerName_my, reinterpret_cast<void**>(&GetPlayerName_ptr));
      MH_EnableHook(GetPlayerName_org);
}
void GetPlayerRace_init ( )
{
      GetPlayerRace_org = (GetPlayerRace_FUNC) ( GameDll + 0x1E3D70 );
      MH_CreateHook(GetPlayerRace_org, &GetPlayerRace_my, reinterpret_cast<void**>(&GetPlayerRace_ptr));
      MH_EnableHook(GetPlayerRace_org);
}
void GetPlayerScore_init ( )
{
      GetPlayerScore_org = (GetPlayerScore_FUNC) ( GameDll + 0x1E3D90 );
      MH_CreateHook(GetPlayerScore_org, &GetPlayerScore_my, reinterpret_cast<void**>(&GetPlayerScore_ptr));
      MH_EnableHook(GetPlayerScore_org);
}
void GetPlayerSelectable_init ( )
{
      GetPlayerSelectable_org = (GetPlayerSelectable_FUNC) ( GameDll + 0x1E3FC0 );
      MH_CreateHook(GetPlayerSelectable_org, &GetPlayerSelectable_my, reinterpret_cast<void**>(&GetPlayerSelectable_ptr));
      MH_EnableHook(GetPlayerSelectable_org);
}
void GetPlayerSlotState_init ( )
{
      GetPlayerSlotState_org = (GetPlayerSlotState_FUNC) ( GameDll + 0x1E3FE0 );
      MH_CreateHook(GetPlayerSlotState_org, &GetPlayerSlotState_my, reinterpret_cast<void**>(&GetPlayerSlotState_ptr));
      MH_EnableHook(GetPlayerSlotState_org);
}
void GetPlayerStartLocation_init ( )
{
      GetPlayerStartLocation_org = (GetPlayerStartLocation_FUNC) ( GameDll + 0x1E4000 );
      MH_CreateHook(GetPlayerStartLocation_org, &GetPlayerStartLocation_my, reinterpret_cast<void**>(&GetPlayerStartLocation_ptr));
      MH_EnableHook(GetPlayerStartLocation_org);
}
void GetPlayerStartLocationX_init ( )
{
      GetPlayerStartLocationX_org = (GetPlayerStartLocationX_FUNC) ( GameDll + 0x1E4020 );
      MH_CreateHook(GetPlayerStartLocationX_org, &GetPlayerStartLocationX_my, reinterpret_cast<void**>(&GetPlayerStartLocationX_ptr));
      MH_EnableHook(GetPlayerStartLocationX_org);
}
void GetPlayerStartLocationY_init ( )
{
      GetPlayerStartLocationY_org = (GetPlayerStartLocationY_FUNC) ( GameDll + 0x1E4050 );
      MH_CreateHook(GetPlayerStartLocationY_org, &GetPlayerStartLocationY_my, reinterpret_cast<void**>(&GetPlayerStartLocationY_ptr));
      MH_EnableHook(GetPlayerStartLocationY_org);
}
void GetPlayerState_init ( )
{
      GetPlayerState_org = (GetPlayerState_FUNC) ( GameDll + 0x1E4080 );
      MH_CreateHook(GetPlayerState_org, &GetPlayerState_my, reinterpret_cast<void**>(&GetPlayerState_ptr));
      MH_EnableHook(GetPlayerState_org);
}
void GetPlayerStructureCount_init ( )
{
      GetPlayerStructureCount_org = (GetPlayerStructureCount_FUNC) ( GameDll + 0x1E40E0 );
      MH_CreateHook(GetPlayerStructureCount_org, &GetPlayerStructureCount_my, reinterpret_cast<void**>(&GetPlayerStructureCount_ptr));
      MH_EnableHook(GetPlayerStructureCount_org);
}
void GetPlayerTaxRate_init ( )
{
      GetPlayerTaxRate_org = (GetPlayerTaxRate_FUNC) ( GameDll + 0x1E4110 );
      MH_CreateHook(GetPlayerTaxRate_org, &GetPlayerTaxRate_my, reinterpret_cast<void**>(&GetPlayerTaxRate_ptr));
      MH_EnableHook(GetPlayerTaxRate_org);
}
void GetPlayerTeam_init ( )
{
      GetPlayerTeam_org = (GetPlayerTeam_FUNC) ( GameDll + 0x1E4160 );
      MH_CreateHook(GetPlayerTeam_org, &GetPlayerTeam_my, reinterpret_cast<void**>(&GetPlayerTeam_ptr));
      MH_EnableHook(GetPlayerTeam_org);
}
void GetPlayerTechCount_init ( )
{
      GetPlayerTechCount_org = (GetPlayerTechCount_FUNC) ( GameDll + 0x1E4190 );
      MH_CreateHook(GetPlayerTechCount_org, &GetPlayerTechCount_my, reinterpret_cast<void**>(&GetPlayerTechCount_ptr));
      MH_EnableHook(GetPlayerTechCount_org);
}
void GetPlayerTechMaxAllowed_init ( )
{
      GetPlayerTechMaxAllowed_org = (GetPlayerTechMaxAllowed_FUNC) ( GameDll + 0x1E41C0 );
      MH_CreateHook(GetPlayerTechMaxAllowed_org, &GetPlayerTechMaxAllowed_my, reinterpret_cast<void**>(&GetPlayerTechMaxAllowed_ptr));
      MH_EnableHook(GetPlayerTechMaxAllowed_org);
}
void GetPlayerTechResearched_init ( )
{
      GetPlayerTechResearched_org = (GetPlayerTechResearched_FUNC) ( GameDll + 0x1E4200 );
      MH_CreateHook(GetPlayerTechResearched_org, &GetPlayerTechResearched_my, reinterpret_cast<void**>(&GetPlayerTechResearched_ptr));
      MH_EnableHook(GetPlayerTechResearched_org);
}
void GetPlayerTypedUnitCount_init ( )
{
      GetPlayerTypedUnitCount_org = (GetPlayerTypedUnitCount_FUNC) ( GameDll + 0x1E4230 );
      MH_CreateHook(GetPlayerTypedUnitCount_org, &GetPlayerTypedUnitCount_my, reinterpret_cast<void**>(&GetPlayerTypedUnitCount_ptr));
      MH_EnableHook(GetPlayerTypedUnitCount_org);
}
void GetPlayerUnitCount_init ( )
{
      GetPlayerUnitCount_org = (GetPlayerUnitCount_FUNC) ( GameDll + 0x1E42A0 );
      MH_CreateHook(GetPlayerUnitCount_org, &GetPlayerUnitCount_my, reinterpret_cast<void**>(&GetPlayerUnitCount_ptr));
      MH_EnableHook(GetPlayerUnitCount_org);
}
void GetPlayerUnitTypeCount_init ( )
{
      GetPlayerUnitTypeCount_org = (GetPlayerUnitTypeCount_FUNC) ( GameDll + 0x8905D0 );
      MH_CreateHook(GetPlayerUnitTypeCount_org, &GetPlayerUnitTypeCount_my, reinterpret_cast<void**>(&GetPlayerUnitTypeCount_ptr));
      MH_EnableHook(GetPlayerUnitTypeCount_org);
}
void GetPlayers_init ( )
{
      GetPlayers_org = (GetPlayers_FUNC) ( GameDll + 0x1E4350 );
      MH_CreateHook(GetPlayers_org, &GetPlayers_my, reinterpret_cast<void**>(&GetPlayers_ptr));
      MH_EnableHook(GetPlayers_org);
}
void GetRandomInt_init ( )
{
      GetRandomInt_org = (GetRandomInt_FUNC) ( GameDll + 0x1E43E0 );
      MH_CreateHook(GetRandomInt_org, &GetRandomInt_my, reinterpret_cast<void**>(&GetRandomInt_ptr));
      MH_EnableHook(GetRandomInt_org);
}
void GetRandomReal_init ( )
{
      GetRandomReal_org = (GetRandomReal_FUNC) ( GameDll + 0x1E4420 );
      MH_CreateHook(GetRandomReal_org, &GetRandomReal_my, reinterpret_cast<void**>(&GetRandomReal_ptr));
      MH_EnableHook(GetRandomReal_org);
}
void GetRectCenterX_init ( )
{
      GetRectCenterX_org = (GetRectCenterX_FUNC) ( GameDll + 0x1E44D0 );
      MH_CreateHook(GetRectCenterX_org, &GetRectCenterX_my, reinterpret_cast<void**>(&GetRectCenterX_ptr));
      MH_EnableHook(GetRectCenterX_org);
}
void GetRectCenterY_init ( )
{
      GetRectCenterY_org = (GetRectCenterY_FUNC) ( GameDll + 0x1E4530 );
      MH_CreateHook(GetRectCenterY_org, &GetRectCenterY_my, reinterpret_cast<void**>(&GetRectCenterY_ptr));
      MH_EnableHook(GetRectCenterY_org);
}
void GetRectMaxX_init ( )
{
      GetRectMaxX_org = (GetRectMaxX_FUNC) ( GameDll + 0x1E4590 );
      MH_CreateHook(GetRectMaxX_org, &GetRectMaxX_my, reinterpret_cast<void**>(&GetRectMaxX_ptr));
      MH_EnableHook(GetRectMaxX_org);
}
void GetRectMaxY_init ( )
{
      GetRectMaxY_org = (GetRectMaxY_FUNC) ( GameDll + 0x1E45B0 );
      MH_CreateHook(GetRectMaxY_org, &GetRectMaxY_my, reinterpret_cast<void**>(&GetRectMaxY_ptr));
      MH_EnableHook(GetRectMaxY_org);
}
void GetRectMinX_init ( )
{
      GetRectMinX_org = (GetRectMinX_FUNC) ( GameDll + 0x1E45D0 );
      MH_CreateHook(GetRectMinX_org, &GetRectMinX_my, reinterpret_cast<void**>(&GetRectMinX_ptr));
      MH_EnableHook(GetRectMinX_org);
}
void GetRectMinY_init ( )
{
      GetRectMinY_org = (GetRectMinY_FUNC) ( GameDll + 0x1E45F0 );
      MH_CreateHook(GetRectMinY_org, &GetRectMinY_my, reinterpret_cast<void**>(&GetRectMinY_ptr));
      MH_EnableHook(GetRectMinY_org);
}
void GetRescuer_init ( )
{
      GetRescuer_org = (GetRescuer_FUNC) ( GameDll + 0x1E4630 );
      MH_CreateHook(GetRescuer_org, &GetRescuer_my, reinterpret_cast<void**>(&GetRescuer_ptr));
      MH_EnableHook(GetRescuer_org);
}
void GetResearched_init ( )
{
      GetResearched_org = (GetResearched_FUNC) ( GameDll + 0x1E46B0 );
      MH_CreateHook(GetResearched_org, &GetResearched_my, reinterpret_cast<void**>(&GetResearched_ptr));
      MH_EnableHook(GetResearched_org);
}
void GetResearchingUnit_init ( )
{
      GetResearchingUnit_org = (GetResearchingUnit_FUNC) ( GameDll + 0x1E4750 );
      MH_CreateHook(GetResearchingUnit_org, &GetResearchingUnit_my, reinterpret_cast<void**>(&GetResearchingUnit_ptr));
      MH_EnableHook(GetResearchingUnit_org);
}
void GetResourceAmount_init ( )
{
      GetResourceAmount_org = (GetResourceAmount_FUNC) ( GameDll + 0x1E47B0 );
      MH_CreateHook(GetResourceAmount_org, &GetResourceAmount_my, reinterpret_cast<void**>(&GetResourceAmount_ptr));
      MH_EnableHook(GetResourceAmount_org);
}
void GetResourceDensity_init ( )
{
      GetResourceDensity_org = (GetResourceDensity_FUNC) ( GameDll + 0x1E4800 );
      MH_CreateHook(GetResourceDensity_org, &GetResourceDensity_my, reinterpret_cast<void**>(&GetResourceDensity_ptr));
      MH_EnableHook(GetResourceDensity_org);
}
void GetRevivableUnit_init ( )
{
      GetRevivableUnit_org = (GetRevivableUnit_FUNC) ( GameDll + 0x1E4810 );
      MH_CreateHook(GetRevivableUnit_org, &GetRevivableUnit_my, reinterpret_cast<void**>(&GetRevivableUnit_ptr));
      MH_EnableHook(GetRevivableUnit_org);
}
void GetRevivingUnit_init ( )
{
      GetRevivingUnit_org = (GetRevivingUnit_FUNC) ( GameDll + 0x1E4870 );
      MH_CreateHook(GetRevivingUnit_org, &GetRevivingUnit_my, reinterpret_cast<void**>(&GetRevivingUnit_ptr));
      MH_EnableHook(GetRevivingUnit_org);
}
void GetSaveBasicFilename_init ( )
{
      GetSaveBasicFilename_org = (GetSaveBasicFilename_FUNC) ( GameDll + 0x1E4920 );
      MH_CreateHook(GetSaveBasicFilename_org, &GetSaveBasicFilename_my, reinterpret_cast<void**>(&GetSaveBasicFilename_ptr));
      MH_EnableHook(GetSaveBasicFilename_org);
}
void GetSellingUnit_init ( )
{
      GetSellingUnit_org = (GetSellingUnit_FUNC) ( GameDll + 0x1E49B0 );
      MH_CreateHook(GetSellingUnit_org, &GetSellingUnit_my, reinterpret_cast<void**>(&GetSellingUnit_ptr));
      MH_EnableHook(GetSellingUnit_org);
}
void GetSoldItem_init ( )
{
      GetSoldItem_org = (GetSoldItem_FUNC) ( GameDll + 0x1E4AD0 );
      MH_CreateHook(GetSoldItem_org, &GetSoldItem_my, reinterpret_cast<void**>(&GetSoldItem_ptr));
      MH_EnableHook(GetSoldItem_org);
}
void GetSoldUnit_init ( )
{
      GetSoldUnit_org = (GetSoldUnit_FUNC) ( GameDll + 0x1E4B60 );
      MH_CreateHook(GetSoldUnit_org, &GetSoldUnit_my, reinterpret_cast<void**>(&GetSoldUnit_ptr));
      MH_EnableHook(GetSoldUnit_org);
}
void GetSoundDuration_init ( )
{
      GetSoundDuration_org = (GetSoundDuration_FUNC) ( GameDll + 0x1E4BE0 );
      MH_CreateHook(GetSoundDuration_org, &GetSoundDuration_my, reinterpret_cast<void**>(&GetSoundDuration_ptr));
      MH_EnableHook(GetSoundDuration_org);
}
void GetSoundFileDuration_init ( )
{
      GetSoundFileDuration_org = (GetSoundFileDuration_FUNC) ( GameDll + 0x1E4C00 );
      MH_CreateHook(GetSoundFileDuration_org, &GetSoundFileDuration_my, reinterpret_cast<void**>(&GetSoundFileDuration_ptr));
      MH_EnableHook(GetSoundFileDuration_org);
}
void GetSoundIsLoading_init ( )
{
      GetSoundIsLoading_org = (GetSoundIsLoading_FUNC) ( GameDll + 0x1E4C20 );
      MH_CreateHook(GetSoundIsLoading_org, &GetSoundIsLoading_my, reinterpret_cast<void**>(&GetSoundIsLoading_ptr));
      MH_EnableHook(GetSoundIsLoading_org);
}
void GetSoundIsPlaying_init ( )
{
      GetSoundIsPlaying_org = (GetSoundIsPlaying_FUNC) ( GameDll + 0x1E4C40 );
      MH_CreateHook(GetSoundIsPlaying_org, &GetSoundIsPlaying_my, reinterpret_cast<void**>(&GetSoundIsPlaying_ptr));
      MH_EnableHook(GetSoundIsPlaying_org);
}
void GetSpellAbility_init ( )
{
      GetSpellAbility_org = (GetSpellAbility_FUNC) ( GameDll + 0x1E4C80 );
      MH_CreateHook(GetSpellAbility_org, &GetSpellAbility_my, reinterpret_cast<void**>(&GetSpellAbility_ptr));
      MH_EnableHook(GetSpellAbility_org);
}
void GetSpellAbilityId_init ( )
{
      GetSpellAbilityId_org = (GetSpellAbilityId_FUNC) ( GameDll + 0x1E4DD0 );
      MH_CreateHook(GetSpellAbilityId_org, &GetSpellAbilityId_my, reinterpret_cast<void**>(&GetSpellAbilityId_ptr));
      MH_EnableHook(GetSpellAbilityId_org);
}
void GetSpellAbilityUnit_init ( )
{
      GetSpellAbilityUnit_org = (GetSpellAbilityUnit_FUNC) ( GameDll + 0x1E4E40 );
      MH_CreateHook(GetSpellAbilityUnit_org, &GetSpellAbilityUnit_my, reinterpret_cast<void**>(&GetSpellAbilityUnit_ptr));
      MH_EnableHook(GetSpellAbilityUnit_org);
}
void GetSpellTargetDestructable_init ( )
{
      GetSpellTargetDestructable_org = (GetSpellTargetDestructable_FUNC) ( GameDll + 0x1E4F60 );
      MH_CreateHook(GetSpellTargetDestructable_org, &GetSpellTargetDestructable_my, reinterpret_cast<void**>(&GetSpellTargetDestructable_ptr));
      MH_EnableHook(GetSpellTargetDestructable_org);
}
void GetSpellTargetItem_init ( )
{
      GetSpellTargetItem_org = (GetSpellTargetItem_FUNC) ( GameDll + 0x1E5090 );
      MH_CreateHook(GetSpellTargetItem_org, &GetSpellTargetItem_my, reinterpret_cast<void**>(&GetSpellTargetItem_ptr));
      MH_EnableHook(GetSpellTargetItem_org);
}
void GetSpellTargetLoc_init ( )
{
      GetSpellTargetLoc_org = (GetSpellTargetLoc_FUNC) ( GameDll + 0x1E51C0 );
      MH_CreateHook(GetSpellTargetLoc_org, &GetSpellTargetLoc_my, reinterpret_cast<void**>(&GetSpellTargetLoc_ptr));
      MH_EnableHook(GetSpellTargetLoc_org);
}
void GetSpellTargetUnit_init ( )
{
      GetSpellTargetUnit_org = (GetSpellTargetUnit_FUNC) ( GameDll + 0x1E52B0 );
      MH_CreateHook(GetSpellTargetUnit_org, &GetSpellTargetUnit_my, reinterpret_cast<void**>(&GetSpellTargetUnit_ptr));
      MH_EnableHook(GetSpellTargetUnit_org);
}
void GetSpellTargetX_init ( )
{
      GetSpellTargetX_org = (GetSpellTargetX_FUNC) ( GameDll + 0x1E53E0 );
      MH_CreateHook(GetSpellTargetX_org, &GetSpellTargetX_my, reinterpret_cast<void**>(&GetSpellTargetX_ptr));
      MH_EnableHook(GetSpellTargetX_org);
}
void GetSpellTargetY_init ( )
{
      GetSpellTargetY_org = (GetSpellTargetY_FUNC) ( GameDll + 0x1E54C0 );
      MH_CreateHook(GetSpellTargetY_org, &GetSpellTargetY_my, reinterpret_cast<void**>(&GetSpellTargetY_ptr));
      MH_EnableHook(GetSpellTargetY_org);
}
void GetStartLocPrio_init ( )
{
      GetStartLocPrio_org = (GetStartLocPrio_FUNC) ( GameDll + 0x1E55A0 );
      MH_CreateHook(GetStartLocPrio_org, &GetStartLocPrio_my, reinterpret_cast<void**>(&GetStartLocPrio_ptr));
      MH_EnableHook(GetStartLocPrio_org);
}
void GetStartLocPrioSlot_init ( )
{
      GetStartLocPrioSlot_org = (GetStartLocPrioSlot_FUNC) ( GameDll + 0x1E55D0 );
      MH_CreateHook(GetStartLocPrioSlot_org, &GetStartLocPrioSlot_my, reinterpret_cast<void**>(&GetStartLocPrioSlot_ptr));
      MH_EnableHook(GetStartLocPrioSlot_org);
}
void GetStartLocationLoc_init ( )
{
      GetStartLocationLoc_org = (GetStartLocationLoc_FUNC) ( GameDll + 0x1E5600 );
      MH_CreateHook(GetStartLocationLoc_org, &GetStartLocationLoc_my, reinterpret_cast<void**>(&GetStartLocationLoc_ptr));
      MH_EnableHook(GetStartLocationLoc_org);
}
void GetStartLocationX_init ( )
{
      GetStartLocationX_org = (GetStartLocationX_FUNC) ( GameDll + 0x1E5650 );
      MH_CreateHook(GetStartLocationX_org, &GetStartLocationX_my, reinterpret_cast<void**>(&GetStartLocationX_ptr));
      MH_EnableHook(GetStartLocationX_org);
}
void GetStartLocationY_init ( )
{
      GetStartLocationY_org = (GetStartLocationY_FUNC) ( GameDll + 0x1E5670 );
      MH_CreateHook(GetStartLocationY_org, &GetStartLocationY_my, reinterpret_cast<void**>(&GetStartLocationY_ptr));
      MH_EnableHook(GetStartLocationY_org);
}
void GetStoredBoolean_init ( )
{
      GetStoredBoolean_org = (GetStoredBoolean_FUNC) ( GameDll + 0x1E56C0 );
      MH_CreateHook(GetStoredBoolean_org, &GetStoredBoolean_my, reinterpret_cast<void**>(&GetStoredBoolean_ptr));
      MH_EnableHook(GetStoredBoolean_org);
}
void GetStoredInteger_init ( )
{
      GetStoredInteger_org = (GetStoredInteger_FUNC) ( GameDll + 0x1E5710 );
      MH_CreateHook(GetStoredInteger_org, &GetStoredInteger_my, reinterpret_cast<void**>(&GetStoredInteger_ptr));
      MH_EnableHook(GetStoredInteger_org);
}
void GetStoredReal_init ( )
{
      GetStoredReal_org = (GetStoredReal_FUNC) ( GameDll + 0x1E5760 );
      MH_CreateHook(GetStoredReal_org, &GetStoredReal_my, reinterpret_cast<void**>(&GetStoredReal_ptr));
      MH_EnableHook(GetStoredReal_org);
}
void GetStoredString_init ( )
{
      GetStoredString_org = (GetStoredString_FUNC) ( GameDll + 0x1E57C0 );
      MH_CreateHook(GetStoredString_org, &GetStoredString_my, reinterpret_cast<void**>(&GetStoredString_ptr));
      MH_EnableHook(GetStoredString_org);
}
void GetSummonedUnit_init ( )
{
      GetSummonedUnit_org = (GetSummonedUnit_FUNC) ( GameDll + 0x1E5820 );
      MH_CreateHook(GetSummonedUnit_org, &GetSummonedUnit_my, reinterpret_cast<void**>(&GetSummonedUnit_ptr));
      MH_EnableHook(GetSummonedUnit_org);
}
void GetSummoningUnit_init ( )
{
      GetSummoningUnit_org = (GetSummoningUnit_FUNC) ( GameDll + 0x1E58A0 );
      MH_CreateHook(GetSummoningUnit_org, &GetSummoningUnit_my, reinterpret_cast<void**>(&GetSummoningUnit_ptr));
      MH_EnableHook(GetSummoningUnit_org);
}
void GetTeams_init ( )
{
      GetTeams_org = (GetTeams_FUNC) ( GameDll + 0x1E5910 );
      MH_CreateHook(GetTeams_org, &GetTeams_my, reinterpret_cast<void**>(&GetTeams_ptr));
      MH_EnableHook(GetTeams_org);
}
void GetTerrainCliffLevel_init ( )
{
      GetTerrainCliffLevel_org = (GetTerrainCliffLevel_FUNC) ( GameDll + 0x1E5920 );
      MH_CreateHook(GetTerrainCliffLevel_org, &GetTerrainCliffLevel_my, reinterpret_cast<void**>(&GetTerrainCliffLevel_ptr));
      MH_EnableHook(GetTerrainCliffLevel_org);
}
void GetTerrainType_init ( )
{
      GetTerrainType_org = (GetTerrainType_FUNC) ( GameDll + 0x1E59C0 );
      MH_CreateHook(GetTerrainType_org, &GetTerrainType_my, reinterpret_cast<void**>(&GetTerrainType_ptr));
      MH_EnableHook(GetTerrainType_org);
}
void GetTerrainVariance_init ( )
{
      GetTerrainVariance_org = (GetTerrainVariance_FUNC) ( GameDll + 0x1E5A10 );
      MH_CreateHook(GetTerrainVariance_org, &GetTerrainVariance_my, reinterpret_cast<void**>(&GetTerrainVariance_ptr));
      MH_EnableHook(GetTerrainVariance_org);
}
void GetTimeOfDayScale_init ( )
{
      GetTimeOfDayScale_org = (GetTimeOfDayScale_FUNC) ( GameDll + 0x1E5A50 );
      MH_CreateHook(GetTimeOfDayScale_org, &GetTimeOfDayScale_my, reinterpret_cast<void**>(&GetTimeOfDayScale_ptr));
      MH_EnableHook(GetTimeOfDayScale_org);
}
void GetTournamentFinishNowPlayer_init ( )
{
      GetTournamentFinishNowPlayer_org = (GetTournamentFinishNowPlayer_FUNC) ( GameDll + 0x1E5A80 );
      MH_CreateHook(GetTournamentFinishNowPlayer_org, &GetTournamentFinishNowPlayer_my, reinterpret_cast<void**>(&GetTournamentFinishNowPlayer_ptr));
      MH_EnableHook(GetTournamentFinishNowPlayer_org);
}
void GetTournamentFinishNowRule_init ( )
{
      GetTournamentFinishNowRule_org = (GetTournamentFinishNowRule_FUNC) ( GameDll + 0x1E5AE0 );
      MH_CreateHook(GetTournamentFinishNowRule_org, &GetTournamentFinishNowRule_my, reinterpret_cast<void**>(&GetTournamentFinishNowRule_ptr));
      MH_EnableHook(GetTournamentFinishNowRule_org);
}
void GetTournamentFinishSoonTimeRemaining_init ( )
{
      GetTournamentFinishSoonTimeRemaining_org = (GetTournamentFinishSoonTimeRemaining_FUNC) ( GameDll + 0x1E5B10 );
      MH_CreateHook(GetTournamentFinishSoonTimeRemaining_org, &GetTournamentFinishSoonTimeRemaining_my, reinterpret_cast<void**>(&GetTournamentFinishSoonTimeRemaining_ptr));
      MH_EnableHook(GetTournamentFinishSoonTimeRemaining_org);
}
void GetTournamentScore_init ( )
{
      GetTournamentScore_org = (GetTournamentScore_FUNC) ( GameDll + 0x1E5B40 );
      MH_CreateHook(GetTournamentScore_org, &GetTournamentScore_my, reinterpret_cast<void**>(&GetTournamentScore_ptr));
      MH_EnableHook(GetTournamentScore_org);
}
void GetTownUnitCount_init ( )
{
      GetTownUnitCount_org = (GetTownUnitCount_FUNC) ( GameDll + 0x890680 );
      MH_CreateHook(GetTownUnitCount_org, &GetTownUnitCount_my, reinterpret_cast<void**>(&GetTownUnitCount_ptr));
      MH_EnableHook(GetTownUnitCount_org);
}
void GetTrainedUnit_init ( )
{
      GetTrainedUnit_org = (GetTrainedUnit_FUNC) ( GameDll + 0x1E5B70 );
      MH_CreateHook(GetTrainedUnit_org, &GetTrainedUnit_my, reinterpret_cast<void**>(&GetTrainedUnit_ptr));
      MH_EnableHook(GetTrainedUnit_org);
}
void GetTrainedUnitType_init ( )
{
      GetTrainedUnitType_org = (GetTrainedUnitType_FUNC) ( GameDll + 0x1E5BF0 );
      MH_CreateHook(GetTrainedUnitType_org, &GetTrainedUnitType_my, reinterpret_cast<void**>(&GetTrainedUnitType_ptr));
      MH_EnableHook(GetTrainedUnitType_org);
}
void GetTransportUnit_init ( )
{
      GetTransportUnit_org = (GetTransportUnit_FUNC) ( GameDll + 0x1E5CB0 );
      MH_CreateHook(GetTransportUnit_org, &GetTransportUnit_my, reinterpret_cast<void**>(&GetTransportUnit_ptr));
      MH_EnableHook(GetTransportUnit_org);
}
void GetTriggerDestructable_init ( )
{
      GetTriggerDestructable_org = (GetTriggerDestructable_FUNC) ( GameDll + 0x1E5D30 );
      MH_CreateHook(GetTriggerDestructable_org, &GetTriggerDestructable_my, reinterpret_cast<void**>(&GetTriggerDestructable_ptr));
      MH_EnableHook(GetTriggerDestructable_org);
}
void GetTriggerEvalCount_init ( )
{
      GetTriggerEvalCount_org = (GetTriggerEvalCount_FUNC) ( GameDll + 0x1E5D50 );
      MH_CreateHook(GetTriggerEvalCount_org, &GetTriggerEvalCount_my, reinterpret_cast<void**>(&GetTriggerEvalCount_ptr));
      MH_EnableHook(GetTriggerEvalCount_org);
}
void GetTriggerEventId_init ( )
{
      GetTriggerEventId_org = (GetTriggerEventId_FUNC) ( GameDll + 0x1E5D90 );
      MH_CreateHook(GetTriggerEventId_org, &GetTriggerEventId_my, reinterpret_cast<void**>(&GetTriggerEventId_ptr));
      MH_EnableHook(GetTriggerEventId_org);
}
void GetTriggerExecCount_init ( )
{
      GetTriggerExecCount_org = (GetTriggerExecCount_FUNC) ( GameDll + 0x1E5DD0 );
      MH_CreateHook(GetTriggerExecCount_org, &GetTriggerExecCount_my, reinterpret_cast<void**>(&GetTriggerExecCount_ptr));
      MH_EnableHook(GetTriggerExecCount_org);
}
void GetTriggerPlayer_init ( )
{
      GetTriggerPlayer_org = (GetTriggerPlayer_FUNC) ( GameDll + 0x1E5DF0 );
      MH_CreateHook(GetTriggerPlayer_org, &GetTriggerPlayer_my, reinterpret_cast<void**>(&GetTriggerPlayer_ptr));
      MH_EnableHook(GetTriggerPlayer_org);
}
void GetTriggerUnit_init ( )
{
      GetTriggerUnit_org = (GetTriggerUnit_FUNC) ( GameDll + 0x1E5E10 );
      MH_CreateHook(GetTriggerUnit_org, &GetTriggerUnit_my, reinterpret_cast<void**>(&GetTriggerUnit_ptr));
      MH_EnableHook(GetTriggerUnit_org);
}
void GetTriggerWidget_init ( )
{
      GetTriggerWidget_org = (GetTriggerWidget_FUNC) ( GameDll + 0x1E5E30 );
      MH_CreateHook(GetTriggerWidget_org, &GetTriggerWidget_my, reinterpret_cast<void**>(&GetTriggerWidget_ptr));
      MH_EnableHook(GetTriggerWidget_org);
}
void GetTriggeringRegion_init ( )
{
      GetTriggeringRegion_org = (GetTriggeringRegion_FUNC) ( GameDll + 0x1E5E50 );
      MH_CreateHook(GetTriggeringRegion_org, &GetTriggeringRegion_my, reinterpret_cast<void**>(&GetTriggeringRegion_ptr));
      MH_EnableHook(GetTriggeringRegion_org);
}
void GetTriggeringTrackable_init ( )
{
      GetTriggeringTrackable_org = (GetTriggeringTrackable_FUNC) ( GameDll + 0x1E5E90 );
      MH_CreateHook(GetTriggeringTrackable_org, &GetTriggeringTrackable_my, reinterpret_cast<void**>(&GetTriggeringTrackable_ptr));
      MH_EnableHook(GetTriggeringTrackable_org);
}
void GetTriggeringTrigger_init ( )
{
      GetTriggeringTrigger_org = (GetTriggeringTrigger_FUNC) ( GameDll + 0x1E5ED0 );
      MH_CreateHook(GetTriggeringTrigger_org, &GetTriggeringTrigger_my, reinterpret_cast<void**>(&GetTriggeringTrigger_ptr));
      MH_EnableHook(GetTriggeringTrigger_org);
}
void GetUnitAbilityLevel_init ( )
{
      GetUnitAbilityLevel_org = (GetUnitAbilityLevel_FUNC) ( GameDll + 0x1E5EF0 );
      MH_CreateHook(GetUnitAbilityLevel_org, &GetUnitAbilityLevel_my, reinterpret_cast<void**>(&GetUnitAbilityLevel_ptr));
      MH_EnableHook(GetUnitAbilityLevel_org);
}
void GetUnitAcquireRange_init ( )
{
      GetUnitAcquireRange_org = (GetUnitAcquireRange_FUNC) ( GameDll + 0x1E5F50 );
      MH_CreateHook(GetUnitAcquireRange_org, &GetUnitAcquireRange_my, reinterpret_cast<void**>(&GetUnitAcquireRange_ptr));
      MH_EnableHook(GetUnitAcquireRange_org);
}
void GetUnitBuildTime_init ( )
{
      GetUnitBuildTime_org = (GetUnitBuildTime_FUNC) ( GameDll + 0x890700 );
      MH_CreateHook(GetUnitBuildTime_org, &GetUnitBuildTime_my, reinterpret_cast<void**>(&GetUnitBuildTime_ptr));
      MH_EnableHook(GetUnitBuildTime_org);
}
void GetUnitCount_init ( )
{
      GetUnitCount_org = (GetUnitCount_FUNC) ( GameDll + 0x890750 );
      MH_CreateHook(GetUnitCount_org, &GetUnitCount_my, reinterpret_cast<void**>(&GetUnitCount_ptr));
      MH_EnableHook(GetUnitCount_org);
}
void GetUnitCountDone_init ( )
{
      GetUnitCountDone_org = (GetUnitCountDone_FUNC) ( GameDll + 0x8907C0 );
      MH_CreateHook(GetUnitCountDone_org, &GetUnitCountDone_my, reinterpret_cast<void**>(&GetUnitCountDone_ptr));
      MH_EnableHook(GetUnitCountDone_org);
}
void GetUnitCurrentOrder_init ( )
{
      GetUnitCurrentOrder_org = (GetUnitCurrentOrder_FUNC) ( GameDll + 0x1E5F80 );
      MH_CreateHook(GetUnitCurrentOrder_org, &GetUnitCurrentOrder_my, reinterpret_cast<void**>(&GetUnitCurrentOrder_ptr));
      MH_EnableHook(GetUnitCurrentOrder_org);
}
void GetUnitDefaultAcquireRange_init ( )
{
      GetUnitDefaultAcquireRange_org = (GetUnitDefaultAcquireRange_FUNC) ( GameDll + 0x1E5FE0 );
      MH_CreateHook(GetUnitDefaultAcquireRange_org, &GetUnitDefaultAcquireRange_my, reinterpret_cast<void**>(&GetUnitDefaultAcquireRange_ptr));
      MH_EnableHook(GetUnitDefaultAcquireRange_org);
}
void GetUnitDefaultFlyHeight_init ( )
{
      GetUnitDefaultFlyHeight_org = (GetUnitDefaultFlyHeight_FUNC) ( GameDll + 0x1E6010 );
      MH_CreateHook(GetUnitDefaultFlyHeight_org, &GetUnitDefaultFlyHeight_my, reinterpret_cast<void**>(&GetUnitDefaultFlyHeight_ptr));
      MH_EnableHook(GetUnitDefaultFlyHeight_org);
}
void GetUnitDefaultMoveSpeed_init ( )
{
      GetUnitDefaultMoveSpeed_org = (GetUnitDefaultMoveSpeed_FUNC) ( GameDll + 0x1E6040 );
      MH_CreateHook(GetUnitDefaultMoveSpeed_org, &GetUnitDefaultMoveSpeed_my, reinterpret_cast<void**>(&GetUnitDefaultMoveSpeed_ptr));
      MH_EnableHook(GetUnitDefaultMoveSpeed_org);
}
void GetUnitDefaultPropWindow_init ( )
{
      GetUnitDefaultPropWindow_org = (GetUnitDefaultPropWindow_FUNC) ( GameDll + 0x1E60D0 );
      MH_CreateHook(GetUnitDefaultPropWindow_org, &GetUnitDefaultPropWindow_my, reinterpret_cast<void**>(&GetUnitDefaultPropWindow_ptr));
      MH_EnableHook(GetUnitDefaultPropWindow_org);
}
void GetUnitDefaultTurnSpeed_init ( )
{
      GetUnitDefaultTurnSpeed_org = (GetUnitDefaultTurnSpeed_FUNC) ( GameDll + 0x1E6100 );
      MH_CreateHook(GetUnitDefaultTurnSpeed_org, &GetUnitDefaultTurnSpeed_my, reinterpret_cast<void**>(&GetUnitDefaultTurnSpeed_ptr));
      MH_EnableHook(GetUnitDefaultTurnSpeed_org);
}
void GetUnitFacing_init ( )
{
      GetUnitFacing_org = (GetUnitFacing_FUNC) ( GameDll + 0x1E6130 );
      MH_CreateHook(GetUnitFacing_org, &GetUnitFacing_my, reinterpret_cast<void**>(&GetUnitFacing_ptr));
      MH_EnableHook(GetUnitFacing_org);
}
void GetUnitFlyHeight_init ( )
{
      GetUnitFlyHeight_org = (GetUnitFlyHeight_FUNC) ( GameDll + 0x1E61A0 );
      MH_CreateHook(GetUnitFlyHeight_org, &GetUnitFlyHeight_my, reinterpret_cast<void**>(&GetUnitFlyHeight_ptr));
      MH_EnableHook(GetUnitFlyHeight_org);
}
void GetUnitFoodMade_init ( )
{
      GetUnitFoodMade_org = (GetUnitFoodMade_FUNC) ( GameDll + 0x1E61C0 );
      MH_CreateHook(GetUnitFoodMade_org, &GetUnitFoodMade_my, reinterpret_cast<void**>(&GetUnitFoodMade_ptr));
      MH_EnableHook(GetUnitFoodMade_org);
}
void GetUnitFoodUsed_init ( )
{
      GetUnitFoodUsed_org = (GetUnitFoodUsed_FUNC) ( GameDll + 0x1E61E0 );
      MH_CreateHook(GetUnitFoodUsed_org, &GetUnitFoodUsed_my, reinterpret_cast<void**>(&GetUnitFoodUsed_ptr));
      MH_EnableHook(GetUnitFoodUsed_org);
}
void GetUnitGoldCost_init ( )
{
      GetUnitGoldCost_org = (GetUnitGoldCost_FUNC) ( GameDll + 0x890800 );
      MH_CreateHook(GetUnitGoldCost_org, &GetUnitGoldCost_my, reinterpret_cast<void**>(&GetUnitGoldCost_ptr));
      MH_EnableHook(GetUnitGoldCost_org);
}
void GetUnitLevel_init ( )
{
      GetUnitLevel_org = (GetUnitLevel_FUNC) ( GameDll + 0x1E6210 );
      MH_CreateHook(GetUnitLevel_org, &GetUnitLevel_my, reinterpret_cast<void**>(&GetUnitLevel_ptr));
      MH_EnableHook(GetUnitLevel_org);
}
void GetUnitLoc_init ( )
{
      GetUnitLoc_org = (GetUnitLoc_FUNC) ( GameDll + 0x1E6280 );
      MH_CreateHook(GetUnitLoc_org, &GetUnitLoc_my, reinterpret_cast<void**>(&GetUnitLoc_ptr));
      MH_EnableHook(GetUnitLoc_org);
}
void GetUnitMoveSpeed_init ( )
{
      GetUnitMoveSpeed_org = (GetUnitMoveSpeed_FUNC) ( GameDll + 0x1E62E0 );
      MH_CreateHook(GetUnitMoveSpeed_org, &GetUnitMoveSpeed_my, reinterpret_cast<void**>(&GetUnitMoveSpeed_ptr));
      MH_EnableHook(GetUnitMoveSpeed_org);
}
void GetUnitName_init ( )
{
      GetUnitName_org = (GetUnitName_FUNC) ( GameDll + 0x1E6340 );
      MH_CreateHook(GetUnitName_org, &GetUnitName_my, reinterpret_cast<void**>(&GetUnitName_ptr));
      MH_EnableHook(GetUnitName_org);
}
void GetUnitPointValue_init ( )
{
      GetUnitPointValue_org = (GetUnitPointValue_FUNC) ( GameDll + 0x1E6370 );
      MH_CreateHook(GetUnitPointValue_org, &GetUnitPointValue_my, reinterpret_cast<void**>(&GetUnitPointValue_ptr));
      MH_EnableHook(GetUnitPointValue_org);
}
void GetUnitPointValueByType_init ( )
{
      GetUnitPointValueByType_org = (GetUnitPointValueByType_FUNC) ( GameDll + 0x1E6390 );
      MH_CreateHook(GetUnitPointValueByType_org, &GetUnitPointValueByType_my, reinterpret_cast<void**>(&GetUnitPointValueByType_ptr));
      MH_EnableHook(GetUnitPointValueByType_org);
}
void GetUnitPropWindow_init ( )
{
      GetUnitPropWindow_org = (GetUnitPropWindow_FUNC) ( GameDll + 0x1E63A0 );
      MH_CreateHook(GetUnitPropWindow_org, &GetUnitPropWindow_my, reinterpret_cast<void**>(&GetUnitPropWindow_ptr));
      MH_EnableHook(GetUnitPropWindow_org);
}
void GetUnitRace_init ( )
{
      GetUnitRace_org = (GetUnitRace_FUNC) ( GameDll + 0x1E63D0 );
      MH_CreateHook(GetUnitRace_org, &GetUnitRace_my, reinterpret_cast<void**>(&GetUnitRace_ptr));
      MH_EnableHook(GetUnitRace_org);
}
void GetUnitRallyDestructable_init ( )
{
      GetUnitRallyDestructable_org = (GetUnitRallyDestructable_FUNC) ( GameDll + 0x1E63F0 );
      MH_CreateHook(GetUnitRallyDestructable_org, &GetUnitRallyDestructable_my, reinterpret_cast<void**>(&GetUnitRallyDestructable_ptr));
      MH_EnableHook(GetUnitRallyDestructable_org);
}
void GetUnitRallyPoint_init ( )
{
      GetUnitRallyPoint_org = (GetUnitRallyPoint_FUNC) ( GameDll + 0x1E64C0 );
      MH_CreateHook(GetUnitRallyPoint_org, &GetUnitRallyPoint_my, reinterpret_cast<void**>(&GetUnitRallyPoint_ptr));
      MH_EnableHook(GetUnitRallyPoint_org);
}
void GetUnitRallyUnit_init ( )
{
      GetUnitRallyUnit_org = (GetUnitRallyUnit_FUNC) ( GameDll + 0x1E6530 );
      MH_CreateHook(GetUnitRallyUnit_org, &GetUnitRallyUnit_my, reinterpret_cast<void**>(&GetUnitRallyUnit_ptr));
      MH_EnableHook(GetUnitRallyUnit_org);
}
void GetUnitState_init ( )
{
      GetUnitState_org = (GetUnitState_FUNC) ( GameDll + 0x1E6600 );
      MH_CreateHook(GetUnitState_org, &GetUnitState_my, reinterpret_cast<void**>(&GetUnitState_ptr));
      MH_EnableHook(GetUnitState_org);
}
void GetUnitTurnSpeed_init ( )
{
      GetUnitTurnSpeed_org = (GetUnitTurnSpeed_FUNC) ( GameDll + 0x1E6640 );
      MH_CreateHook(GetUnitTurnSpeed_org, &GetUnitTurnSpeed_my, reinterpret_cast<void**>(&GetUnitTurnSpeed_ptr));
      MH_EnableHook(GetUnitTurnSpeed_org);
}
void GetUnitTypeId_init ( )
{
      GetUnitTypeId_org = (GetUnitTypeId_FUNC) ( GameDll + 0x1E6670 );
      MH_CreateHook(GetUnitTypeId_org, &GetUnitTypeId_my, reinterpret_cast<void**>(&GetUnitTypeId_ptr));
      MH_EnableHook(GetUnitTypeId_org);
}
void GetUnitUserData_init ( )
{
      GetUnitUserData_org = (GetUnitUserData_FUNC) ( GameDll + 0x1E6690 );
      MH_CreateHook(GetUnitUserData_org, &GetUnitUserData_my, reinterpret_cast<void**>(&GetUnitUserData_ptr));
      MH_EnableHook(GetUnitUserData_org);
}
void GetUnitWoodCost_init ( )
{
      GetUnitWoodCost_org = (GetUnitWoodCost_FUNC) ( GameDll + 0x890860 );
      MH_CreateHook(GetUnitWoodCost_org, &GetUnitWoodCost_my, reinterpret_cast<void**>(&GetUnitWoodCost_ptr));
      MH_EnableHook(GetUnitWoodCost_org);
}
void GetUnitX_init ( )
{
      GetUnitX_org = (GetUnitX_FUNC) ( GameDll + 0x1E66B0 );
      MH_CreateHook(GetUnitX_org, &GetUnitX_my, reinterpret_cast<void**>(&GetUnitX_ptr));
      MH_EnableHook(GetUnitX_org);
}
void GetUnitY_init ( )
{
      GetUnitY_org = (GetUnitY_FUNC) ( GameDll + 0x1E66F0 );
      MH_CreateHook(GetUnitY_org, &GetUnitY_my, reinterpret_cast<void**>(&GetUnitY_ptr));
      MH_EnableHook(GetUnitY_org);
}
void GetUpgradeGoldCost_init ( )
{
      GetUpgradeGoldCost_org = (GetUpgradeGoldCost_FUNC) ( GameDll + 0x8908C0 );
      MH_CreateHook(GetUpgradeGoldCost_org, &GetUpgradeGoldCost_my, reinterpret_cast<void**>(&GetUpgradeGoldCost_ptr));
      MH_EnableHook(GetUpgradeGoldCost_org);
}
void GetUpgradeLevel_init ( )
{
      GetUpgradeLevel_org = (GetUpgradeLevel_FUNC) ( GameDll + 0x8908E0 );
      MH_CreateHook(GetUpgradeLevel_org, &GetUpgradeLevel_my, reinterpret_cast<void**>(&GetUpgradeLevel_ptr));
      MH_EnableHook(GetUpgradeLevel_org);
}
void GetUpgradeWoodCost_init ( )
{
      GetUpgradeWoodCost_org = (GetUpgradeWoodCost_FUNC) ( GameDll + 0x890940 );
      MH_CreateHook(GetUpgradeWoodCost_org, &GetUpgradeWoodCost_my, reinterpret_cast<void**>(&GetUpgradeWoodCost_ptr));
      MH_EnableHook(GetUpgradeWoodCost_org);
}
void GetWidgetLife_init ( )
{
      GetWidgetLife_org = (GetWidgetLife_FUNC) ( GameDll + 0x1E6730 );
      MH_CreateHook(GetWidgetLife_org, &GetWidgetLife_my, reinterpret_cast<void**>(&GetWidgetLife_ptr));
      MH_EnableHook(GetWidgetLife_org);
}
void GetWidgetX_init ( )
{
      GetWidgetX_org = (GetWidgetX_FUNC) ( GameDll + 0x1E6760 );
      MH_CreateHook(GetWidgetX_org, &GetWidgetX_my, reinterpret_cast<void**>(&GetWidgetX_ptr));
      MH_EnableHook(GetWidgetX_org);
}
void GetWidgetY_init ( )
{
      GetWidgetY_org = (GetWidgetY_FUNC) ( GameDll + 0x1E67A0 );
      MH_CreateHook(GetWidgetY_org, &GetWidgetY_my, reinterpret_cast<void**>(&GetWidgetY_ptr));
      MH_EnableHook(GetWidgetY_org);
}
void GetWinningPlayer_init ( )
{
      GetWinningPlayer_org = (GetWinningPlayer_FUNC) ( GameDll + 0x1E67E0 );
      MH_CreateHook(GetWinningPlayer_org, &GetWinningPlayer_my, reinterpret_cast<void**>(&GetWinningPlayer_ptr));
      MH_EnableHook(GetWinningPlayer_org);
}
void GetWorldBounds_init ( )
{
      GetWorldBounds_org = (GetWorldBounds_FUNC) ( GameDll + 0x1E6810 );
      MH_CreateHook(GetWorldBounds_org, &GetWorldBounds_my, reinterpret_cast<void**>(&GetWorldBounds_ptr));
      MH_EnableHook(GetWorldBounds_org);
}
void GroupAddUnit_init ( )
{
      GroupAddUnit_org = (GroupAddUnit_FUNC) ( GameDll + 0x1E6910 );
      MH_CreateHook(GroupAddUnit_org, &GroupAddUnit_my, reinterpret_cast<void**>(&GroupAddUnit_ptr));
      MH_EnableHook(GroupAddUnit_org);
}
void GroupClear_init ( )
{
      GroupClear_org = (GroupClear_FUNC) ( GameDll + 0x1E6940 );
      MH_CreateHook(GroupClear_org, &GroupClear_my, reinterpret_cast<void**>(&GroupClear_ptr));
      MH_EnableHook(GroupClear_org);
}
void GroupEnumUnitsInRange_init ( )
{
      GroupEnumUnitsInRange_org = (GroupEnumUnitsInRange_FUNC) ( GameDll + 0x1E6960 );
      MH_CreateHook(GroupEnumUnitsInRange_org, &GroupEnumUnitsInRange_my, reinterpret_cast<void**>(&GroupEnumUnitsInRange_ptr));
      MH_EnableHook(GroupEnumUnitsInRange_org);
}
void GroupEnumUnitsInRangeCounted_init ( )
{
      GroupEnumUnitsInRangeCounted_org = (GroupEnumUnitsInRangeCounted_FUNC) ( GameDll + 0x1E6990 );
      MH_CreateHook(GroupEnumUnitsInRangeCounted_org, &GroupEnumUnitsInRangeCounted_my, reinterpret_cast<void**>(&GroupEnumUnitsInRangeCounted_ptr));
      MH_EnableHook(GroupEnumUnitsInRangeCounted_org);
}
void GroupEnumUnitsInRangeOfLoc_init ( )
{
      GroupEnumUnitsInRangeOfLoc_org = (GroupEnumUnitsInRangeOfLoc_FUNC) ( GameDll + 0x1E69D0 );
      MH_CreateHook(GroupEnumUnitsInRangeOfLoc_org, &GroupEnumUnitsInRangeOfLoc_my, reinterpret_cast<void**>(&GroupEnumUnitsInRangeOfLoc_ptr));
      MH_EnableHook(GroupEnumUnitsInRangeOfLoc_org);
}
void GroupEnumUnitsInRangeOfLocCounted_init ( )
{
      GroupEnumUnitsInRangeOfLocCounted_org = (GroupEnumUnitsInRangeOfLocCounted_FUNC) ( GameDll + 0x1E6A10 );
      MH_CreateHook(GroupEnumUnitsInRangeOfLocCounted_org, &GroupEnumUnitsInRangeOfLocCounted_my, reinterpret_cast<void**>(&GroupEnumUnitsInRangeOfLocCounted_ptr));
      MH_EnableHook(GroupEnumUnitsInRangeOfLocCounted_org);
}
void GroupEnumUnitsInRect_init ( )
{
      GroupEnumUnitsInRect_org = (GroupEnumUnitsInRect_FUNC) ( GameDll + 0x1E6A50 );
      MH_CreateHook(GroupEnumUnitsInRect_org, &GroupEnumUnitsInRect_my, reinterpret_cast<void**>(&GroupEnumUnitsInRect_ptr));
      MH_EnableHook(GroupEnumUnitsInRect_org);
}
void GroupEnumUnitsInRectCounted_init ( )
{
      GroupEnumUnitsInRectCounted_org = (GroupEnumUnitsInRectCounted_FUNC) ( GameDll + 0x1E6AB0 );
      MH_CreateHook(GroupEnumUnitsInRectCounted_org, &GroupEnumUnitsInRectCounted_my, reinterpret_cast<void**>(&GroupEnumUnitsInRectCounted_ptr));
      MH_EnableHook(GroupEnumUnitsInRectCounted_org);
}
void GroupEnumUnitsOfPlayer_init ( )
{
      GroupEnumUnitsOfPlayer_org = (GroupEnumUnitsOfPlayer_FUNC) ( GameDll + 0x1E6B10 );
      MH_CreateHook(GroupEnumUnitsOfPlayer_org, &GroupEnumUnitsOfPlayer_my, reinterpret_cast<void**>(&GroupEnumUnitsOfPlayer_ptr));
      MH_EnableHook(GroupEnumUnitsOfPlayer_org);
}
void GroupEnumUnitsOfType_init ( )
{
      GroupEnumUnitsOfType_org = (GroupEnumUnitsOfType_FUNC) ( GameDll + 0x1E6B50 );
      MH_CreateHook(GroupEnumUnitsOfType_org, &GroupEnumUnitsOfType_my, reinterpret_cast<void**>(&GroupEnumUnitsOfType_ptr));
      MH_EnableHook(GroupEnumUnitsOfType_org);
}
void GroupEnumUnitsOfTypeCounted_init ( )
{
      GroupEnumUnitsOfTypeCounted_org = (GroupEnumUnitsOfTypeCounted_FUNC) ( GameDll + 0x1E6BA0 );
      MH_CreateHook(GroupEnumUnitsOfTypeCounted_org, &GroupEnumUnitsOfTypeCounted_my, reinterpret_cast<void**>(&GroupEnumUnitsOfTypeCounted_ptr));
      MH_EnableHook(GroupEnumUnitsOfTypeCounted_org);
}
void GroupEnumUnitsSelected_init ( )
{
      GroupEnumUnitsSelected_org = (GroupEnumUnitsSelected_FUNC) ( GameDll + 0x1E6BF0 );
      MH_CreateHook(GroupEnumUnitsSelected_org, &GroupEnumUnitsSelected_my, reinterpret_cast<void**>(&GroupEnumUnitsSelected_ptr));
      MH_EnableHook(GroupEnumUnitsSelected_org);
}
void GroupImmediateOrder_init ( )
{
      GroupImmediateOrder_org = (GroupImmediateOrder_FUNC) ( GameDll + 0x1E6D40 );
      MH_CreateHook(GroupImmediateOrder_org, &GroupImmediateOrder_my, reinterpret_cast<void**>(&GroupImmediateOrder_ptr));
      MH_EnableHook(GroupImmediateOrder_org);
}
void GroupImmediateOrderById_init ( )
{
      GroupImmediateOrderById_org = (GroupImmediateOrderById_FUNC) ( GameDll + 0x1E6D60 );
      MH_CreateHook(GroupImmediateOrderById_org, &GroupImmediateOrderById_my, reinterpret_cast<void**>(&GroupImmediateOrderById_ptr));
      MH_EnableHook(GroupImmediateOrderById_org);
}
void GroupPointOrder_init ( )
{
      GroupPointOrder_org = (GroupPointOrder_FUNC) ( GameDll + 0x1E6D80 );
      MH_CreateHook(GroupPointOrder_org, &GroupPointOrder_my, reinterpret_cast<void**>(&GroupPointOrder_ptr));
      MH_EnableHook(GroupPointOrder_org);
}
void GroupPointOrderById_init ( )
{
      GroupPointOrderById_org = (GroupPointOrderById_FUNC) ( GameDll + 0x1E6DA0 );
      MH_CreateHook(GroupPointOrderById_org, &GroupPointOrderById_my, reinterpret_cast<void**>(&GroupPointOrderById_ptr));
      MH_EnableHook(GroupPointOrderById_org);
}
void GroupPointOrderByIdLoc_init ( )
{
      GroupPointOrderByIdLoc_org = (GroupPointOrderByIdLoc_FUNC) ( GameDll + 0x1E6DD0 );
      MH_CreateHook(GroupPointOrderByIdLoc_org, &GroupPointOrderByIdLoc_my, reinterpret_cast<void**>(&GroupPointOrderByIdLoc_ptr));
      MH_EnableHook(GroupPointOrderByIdLoc_org);
}
void GroupPointOrderLoc_init ( )
{
      GroupPointOrderLoc_org = (GroupPointOrderLoc_FUNC) ( GameDll + 0x1E6E10 );
      MH_CreateHook(GroupPointOrderLoc_org, &GroupPointOrderLoc_my, reinterpret_cast<void**>(&GroupPointOrderLoc_ptr));
      MH_EnableHook(GroupPointOrderLoc_org);
}
void GroupRemoveUnit_init ( )
{
      GroupRemoveUnit_org = (GroupRemoveUnit_FUNC) ( GameDll + 0x1E6E30 );
      MH_CreateHook(GroupRemoveUnit_org, &GroupRemoveUnit_my, reinterpret_cast<void**>(&GroupRemoveUnit_ptr));
      MH_EnableHook(GroupRemoveUnit_org);
}
void GroupTargetOrder_init ( )
{
      GroupTargetOrder_org = (GroupTargetOrder_FUNC) ( GameDll + 0x1E6E60 );
      MH_CreateHook(GroupTargetOrder_org, &GroupTargetOrder_my, reinterpret_cast<void**>(&GroupTargetOrder_ptr));
      MH_EnableHook(GroupTargetOrder_org);
}
void GroupTargetOrderById_init ( )
{
      GroupTargetOrderById_org = (GroupTargetOrderById_FUNC) ( GameDll + 0x1E6E80 );
      MH_CreateHook(GroupTargetOrderById_org, &GroupTargetOrderById_my, reinterpret_cast<void**>(&GroupTargetOrderById_ptr));
      MH_EnableHook(GroupTargetOrderById_org);
}
void GroupTimedLife_init ( )
{
      GroupTimedLife_org = (GroupTimedLife_FUNC) ( GameDll + 0x890A90 );
      MH_CreateHook(GroupTimedLife_org, &GroupTimedLife_my, reinterpret_cast<void**>(&GroupTimedLife_ptr));
      MH_EnableHook(GroupTimedLife_org);
}
void HarvestGold_init ( )
{
      HarvestGold_org = (HarvestGold_FUNC) ( GameDll + 0x890CB0 );
      MH_CreateHook(HarvestGold_org, &HarvestGold_my, reinterpret_cast<void**>(&HarvestGold_ptr));
      MH_EnableHook(HarvestGold_org);
}
void HarvestWood_init ( )
{
      HarvestWood_org = (HarvestWood_FUNC) ( GameDll + 0x890D20 );
      MH_CreateHook(HarvestWood_org, &HarvestWood_my, reinterpret_cast<void**>(&HarvestWood_ptr));
      MH_EnableHook(HarvestWood_org);
}
void HaveSavedBoolean_init ( )
{
      HaveSavedBoolean_org = (HaveSavedBoolean_FUNC) ( GameDll + 0x1E6F60 );
      MH_CreateHook(HaveSavedBoolean_org, &HaveSavedBoolean_my, reinterpret_cast<void**>(&HaveSavedBoolean_ptr));
      MH_EnableHook(HaveSavedBoolean_org);
}
void HaveSavedHandle_init ( )
{
      HaveSavedHandle_org = (HaveSavedHandle_FUNC) ( GameDll + 0x1E6FA0 );
      MH_CreateHook(HaveSavedHandle_org, &HaveSavedHandle_my, reinterpret_cast<void**>(&HaveSavedHandle_ptr));
      MH_EnableHook(HaveSavedHandle_org);
}
void HaveSavedInteger_init ( )
{
      HaveSavedInteger_org = (HaveSavedInteger_FUNC) ( GameDll + 0x1E6FE0 );
      MH_CreateHook(HaveSavedInteger_org, &HaveSavedInteger_my, reinterpret_cast<void**>(&HaveSavedInteger_ptr));
      MH_EnableHook(HaveSavedInteger_org);
}
void HaveSavedReal_init ( )
{
      HaveSavedReal_org = (HaveSavedReal_FUNC) ( GameDll + 0x1E7020 );
      MH_CreateHook(HaveSavedReal_org, &HaveSavedReal_my, reinterpret_cast<void**>(&HaveSavedReal_ptr));
      MH_EnableHook(HaveSavedReal_org);
}
void HaveSavedString_init ( )
{
      HaveSavedString_org = (HaveSavedString_FUNC) ( GameDll + 0x1E7060 );
      MH_CreateHook(HaveSavedString_org, &HaveSavedString_my, reinterpret_cast<void**>(&HaveSavedString_ptr));
      MH_EnableHook(HaveSavedString_org);
}
void HaveStoredBoolean_init ( )
{
      HaveStoredBoolean_org = (HaveStoredBoolean_FUNC) ( GameDll + 0x1E70A0 );
      MH_CreateHook(HaveStoredBoolean_org, &HaveStoredBoolean_my, reinterpret_cast<void**>(&HaveStoredBoolean_ptr));
      MH_EnableHook(HaveStoredBoolean_org);
}
void HaveStoredInteger_init ( )
{
      HaveStoredInteger_org = (HaveStoredInteger_FUNC) ( GameDll + 0x1E70F0 );
      MH_CreateHook(HaveStoredInteger_org, &HaveStoredInteger_my, reinterpret_cast<void**>(&HaveStoredInteger_ptr));
      MH_EnableHook(HaveStoredInteger_org);
}
void HaveStoredReal_init ( )
{
      HaveStoredReal_org = (HaveStoredReal_FUNC) ( GameDll + 0x1E7140 );
      MH_CreateHook(HaveStoredReal_org, &HaveStoredReal_my, reinterpret_cast<void**>(&HaveStoredReal_ptr));
      MH_EnableHook(HaveStoredReal_org);
}
void HaveStoredString_init ( )
{
      HaveStoredString_org = (HaveStoredString_FUNC) ( GameDll + 0x1E7190 );
      MH_CreateHook(HaveStoredString_org, &HaveStoredString_my, reinterpret_cast<void**>(&HaveStoredString_ptr));
      MH_EnableHook(HaveStoredString_org);
}
void HaveStoredUnit_init ( )
{
      HaveStoredUnit_org = (HaveStoredUnit_FUNC) ( GameDll + 0x1E71E0 );
      MH_CreateHook(HaveStoredUnit_org, &HaveStoredUnit_my, reinterpret_cast<void**>(&HaveStoredUnit_ptr));
      MH_EnableHook(HaveStoredUnit_org);
}
void I2R_init ( )
{
      I2R_org = (I2R_FUNC) ( GameDll + 0x1E7230 );
      MH_CreateHook(I2R_org, &I2R_my, reinterpret_cast<void**>(&I2R_ptr));
      MH_EnableHook(I2R_org);
}
void I2S_init ( )
{
      I2S_org = (I2S_FUNC) ( GameDll + 0x1E7250 );
      MH_CreateHook(I2S_org, &I2S_my, reinterpret_cast<void**>(&I2S_ptr));
      MH_EnableHook(I2S_org);
}
void IgnoredUnits_init ( )
{
      IgnoredUnits_org = (IgnoredUnits_FUNC) ( GameDll + 0x890FB0 );
      MH_CreateHook(IgnoredUnits_org, &IgnoredUnits_my, reinterpret_cast<void**>(&IgnoredUnits_ptr));
      MH_EnableHook(IgnoredUnits_org);
}
void IncUnitAbilityLevel_init ( )
{
      IncUnitAbilityLevel_org = (IncUnitAbilityLevel_FUNC) ( GameDll + 0x1E7340 );
      MH_CreateHook(IncUnitAbilityLevel_org, &IncUnitAbilityLevel_my, reinterpret_cast<void**>(&IncUnitAbilityLevel_ptr));
      MH_EnableHook(IncUnitAbilityLevel_org);
}
void InitAssault_init ( )
{
      InitAssault_org = (InitAssault_FUNC) ( GameDll + 0x890FF0 );
      MH_CreateHook(InitAssault_org, &InitAssault_my, reinterpret_cast<void**>(&InitAssault_ptr));
      MH_EnableHook(InitAssault_org);
}
void InitGameCache_init ( )
{
      InitGameCache_org = (InitGameCache_FUNC) ( GameDll + 0x1E73C0 );
      MH_CreateHook(InitGameCache_org, &InitGameCache_my, reinterpret_cast<void**>(&InitGameCache_ptr));
      MH_EnableHook(InitGameCache_org);
}
void InitHashtable_init ( )
{
      InitHashtable_org = (InitHashtable_FUNC) ( GameDll + 0x1E74D0 );
      MH_CreateHook(InitHashtable_org, &InitHashtable_my, reinterpret_cast<void**>(&InitHashtable_ptr));
      MH_EnableHook(InitHashtable_org);
}
void IsCineFilterDisplayed_init ( )
{
      IsCineFilterDisplayed_org = (IsCineFilterDisplayed_FUNC) ( GameDll + 0x1E7820 );
      MH_CreateHook(IsCineFilterDisplayed_org, &IsCineFilterDisplayed_my, reinterpret_cast<void**>(&IsCineFilterDisplayed_ptr));
      MH_EnableHook(IsCineFilterDisplayed_org);
}
void IsDestructableInvulnerable_init ( )
{
      IsDestructableInvulnerable_org = (IsDestructableInvulnerable_FUNC) ( GameDll + 0x1E7870 );
      MH_CreateHook(IsDestructableInvulnerable_org, &IsDestructableInvulnerable_my, reinterpret_cast<void**>(&IsDestructableInvulnerable_ptr));
      MH_EnableHook(IsDestructableInvulnerable_org);
}
void IsFogEnabled_init ( )
{
      IsFogEnabled_org = (IsFogEnabled_FUNC) ( GameDll + 0x1E7960 );
      MH_CreateHook(IsFogEnabled_org, &IsFogEnabled_my, reinterpret_cast<void**>(&IsFogEnabled_ptr));
      MH_EnableHook(IsFogEnabled_org);
}
void IsFogMaskEnabled_init ( )
{
      IsFogMaskEnabled_org = (IsFogMaskEnabled_FUNC) ( GameDll + 0x1E7970 );
      MH_CreateHook(IsFogMaskEnabled_org, &IsFogMaskEnabled_my, reinterpret_cast<void**>(&IsFogMaskEnabled_ptr));
      MH_EnableHook(IsFogMaskEnabled_org);
}
void IsFoggedToPlayer_init ( )
{
      IsFoggedToPlayer_org = (IsFoggedToPlayer_FUNC) ( GameDll + 0x1E7A10 );
      MH_CreateHook(IsFoggedToPlayer_org, &IsFoggedToPlayer_my, reinterpret_cast<void**>(&IsFoggedToPlayer_ptr));
      MH_EnableHook(IsFoggedToPlayer_org);
}
void IsGameTypeSupported_init ( )
{
      IsGameTypeSupported_org = (IsGameTypeSupported_FUNC) ( GameDll + 0x1E7AA0 );
      MH_CreateHook(IsGameTypeSupported_org, &IsGameTypeSupported_my, reinterpret_cast<void**>(&IsGameTypeSupported_ptr));
      MH_EnableHook(IsGameTypeSupported_org);
}
void IsHeroUnitId_init ( )
{
      IsHeroUnitId_org = (IsHeroUnitId_FUNC) ( GameDll + 0x1E7B50 );
      MH_CreateHook(IsHeroUnitId_org, &IsHeroUnitId_my, reinterpret_cast<void**>(&IsHeroUnitId_ptr));
      MH_EnableHook(IsHeroUnitId_org);
}
void IsItemIdPawnable_init ( )
{
      IsItemIdPawnable_org = (IsItemIdPawnable_FUNC) ( GameDll + 0x1E7BE0 );
      MH_CreateHook(IsItemIdPawnable_org, &IsItemIdPawnable_my, reinterpret_cast<void**>(&IsItemIdPawnable_ptr));
      MH_EnableHook(IsItemIdPawnable_org);
}
void IsItemIdPowerup_init ( )
{
      IsItemIdPowerup_org = (IsItemIdPowerup_FUNC) ( GameDll + 0x1E7BF0 );
      MH_CreateHook(IsItemIdPowerup_org, &IsItemIdPowerup_my, reinterpret_cast<void**>(&IsItemIdPowerup_ptr));
      MH_EnableHook(IsItemIdPowerup_org);
}
void IsItemIdSellable_init ( )
{
      IsItemIdSellable_org = (IsItemIdSellable_FUNC) ( GameDll + 0x1E7C00 );
      MH_CreateHook(IsItemIdSellable_org, &IsItemIdSellable_my, reinterpret_cast<void**>(&IsItemIdSellable_ptr));
      MH_EnableHook(IsItemIdSellable_org);
}
void IsItemInvulnerable_init ( )
{
      IsItemInvulnerable_org = (IsItemInvulnerable_FUNC) ( GameDll + 0x1E7C10 );
      MH_CreateHook(IsItemInvulnerable_org, &IsItemInvulnerable_my, reinterpret_cast<void**>(&IsItemInvulnerable_ptr));
      MH_EnableHook(IsItemInvulnerable_org);
}
void IsItemOwned_init ( )
{
      IsItemOwned_org = (IsItemOwned_FUNC) ( GameDll + 0x1E7C30 );
      MH_CreateHook(IsItemOwned_org, &IsItemOwned_my, reinterpret_cast<void**>(&IsItemOwned_ptr));
      MH_EnableHook(IsItemOwned_org);
}
void IsItemPawnable_init ( )
{
      IsItemPawnable_org = (IsItemPawnable_FUNC) ( GameDll + 0x1E7C70 );
      MH_CreateHook(IsItemPawnable_org, &IsItemPawnable_my, reinterpret_cast<void**>(&IsItemPawnable_ptr));
      MH_EnableHook(IsItemPawnable_org);
}
void IsItemPowerup_init ( )
{
      IsItemPowerup_org = (IsItemPowerup_FUNC) ( GameDll + 0x1E7C90 );
      MH_CreateHook(IsItemPowerup_org, &IsItemPowerup_my, reinterpret_cast<void**>(&IsItemPowerup_ptr));
      MH_EnableHook(IsItemPowerup_org);
}
void IsItemSellable_init ( )
{
      IsItemSellable_org = (IsItemSellable_FUNC) ( GameDll + 0x1E7CB0 );
      MH_CreateHook(IsItemSellable_org, &IsItemSellable_my, reinterpret_cast<void**>(&IsItemSellable_ptr));
      MH_EnableHook(IsItemSellable_org);
}
void IsItemVisible_init ( )
{
      IsItemVisible_org = (IsItemVisible_FUNC) ( GameDll + 0x1E7CD0 );
      MH_CreateHook(IsItemVisible_org, &IsItemVisible_my, reinterpret_cast<void**>(&IsItemVisible_ptr));
      MH_EnableHook(IsItemVisible_org);
}
void IsLeaderboardDisplayed_init ( )
{
      IsLeaderboardDisplayed_org = (IsLeaderboardDisplayed_FUNC) ( GameDll + 0x1E7CF0 );
      MH_CreateHook(IsLeaderboardDisplayed_org, &IsLeaderboardDisplayed_my, reinterpret_cast<void**>(&IsLeaderboardDisplayed_ptr));
      MH_EnableHook(IsLeaderboardDisplayed_org);
}
void IsLocationFoggedToPlayer_init ( )
{
      IsLocationFoggedToPlayer_org = (IsLocationFoggedToPlayer_FUNC) ( GameDll + 0x1E7D20 );
      MH_CreateHook(IsLocationFoggedToPlayer_org, &IsLocationFoggedToPlayer_my, reinterpret_cast<void**>(&IsLocationFoggedToPlayer_ptr));
      MH_EnableHook(IsLocationFoggedToPlayer_org);
}
void IsLocationInRegion_init ( )
{
      IsLocationInRegion_org = (IsLocationInRegion_FUNC) ( GameDll + 0x1E7D60 );
      MH_CreateHook(IsLocationInRegion_org, &IsLocationInRegion_my, reinterpret_cast<void**>(&IsLocationInRegion_ptr));
      MH_EnableHook(IsLocationInRegion_org);
}
void IsLocationMaskedToPlayer_init ( )
{
      IsLocationMaskedToPlayer_org = (IsLocationMaskedToPlayer_FUNC) ( GameDll + 0x1E7DA0 );
      MH_CreateHook(IsLocationMaskedToPlayer_org, &IsLocationMaskedToPlayer_my, reinterpret_cast<void**>(&IsLocationMaskedToPlayer_ptr));
      MH_EnableHook(IsLocationMaskedToPlayer_org);
}
void IsLocationVisibleToPlayer_init ( )
{
      IsLocationVisibleToPlayer_org = (IsLocationVisibleToPlayer_FUNC) ( GameDll + 0x1E7DE0 );
      MH_CreateHook(IsLocationVisibleToPlayer_org, &IsLocationVisibleToPlayer_my, reinterpret_cast<void**>(&IsLocationVisibleToPlayer_ptr));
      MH_EnableHook(IsLocationVisibleToPlayer_org);
}
void IsMapFlagSet_init ( )
{
      IsMapFlagSet_org = (IsMapFlagSet_FUNC) ( GameDll + 0x1E7E50 );
      MH_CreateHook(IsMapFlagSet_org, &IsMapFlagSet_my, reinterpret_cast<void**>(&IsMapFlagSet_ptr));
      MH_EnableHook(IsMapFlagSet_org);
}
void IsMaskedToPlayer_init ( )
{
      IsMaskedToPlayer_org = (IsMaskedToPlayer_FUNC) ( GameDll + 0x1E7EF0 );
      MH_CreateHook(IsMaskedToPlayer_org, &IsMaskedToPlayer_my, reinterpret_cast<void**>(&IsMaskedToPlayer_ptr));
      MH_EnableHook(IsMaskedToPlayer_org);
}
void IsMultiboardDisplayed_init ( )
{
      IsMultiboardDisplayed_org = (IsMultiboardDisplayed_FUNC) ( GameDll + 0x1E7F70 );
      MH_CreateHook(IsMultiboardDisplayed_org, &IsMultiboardDisplayed_my, reinterpret_cast<void**>(&IsMultiboardDisplayed_ptr));
      MH_EnableHook(IsMultiboardDisplayed_org);
}
void IsMultiboardMinimized_init ( )
{
      IsMultiboardMinimized_org = (IsMultiboardMinimized_FUNC) ( GameDll + 0x1E7F90 );
      MH_CreateHook(IsMultiboardMinimized_org, &IsMultiboardMinimized_my, reinterpret_cast<void**>(&IsMultiboardMinimized_ptr));
      MH_EnableHook(IsMultiboardMinimized_org);
}
void IsNoDefeatCheat_init ( )
{
      IsNoDefeatCheat_org = (IsNoDefeatCheat_FUNC) ( GameDll + 0x1E7FB0 );
      MH_CreateHook(IsNoDefeatCheat_org, &IsNoDefeatCheat_my, reinterpret_cast<void**>(&IsNoDefeatCheat_ptr));
      MH_EnableHook(IsNoDefeatCheat_org);
}
void IsNoVictoryCheat_init ( )
{
      IsNoVictoryCheat_org = (IsNoVictoryCheat_FUNC) ( GameDll + 0x1E7FE0 );
      MH_CreateHook(IsNoVictoryCheat_org, &IsNoVictoryCheat_my, reinterpret_cast<void**>(&IsNoVictoryCheat_ptr));
      MH_EnableHook(IsNoVictoryCheat_org);
}
void IsPlayerAlly_init ( )
{
      IsPlayerAlly_org = (IsPlayerAlly_FUNC) ( GameDll + 0x1E8040 );
      MH_CreateHook(IsPlayerAlly_org, &IsPlayerAlly_my, reinterpret_cast<void**>(&IsPlayerAlly_ptr));
      MH_EnableHook(IsPlayerAlly_org);
}
void IsPlayerEnemy_init ( )
{
      IsPlayerEnemy_org = (IsPlayerEnemy_FUNC) ( GameDll + 0x1E8090 );
      MH_CreateHook(IsPlayerEnemy_org, &IsPlayerEnemy_my, reinterpret_cast<void**>(&IsPlayerEnemy_ptr));
      MH_EnableHook(IsPlayerEnemy_org);
}
void IsPlayerInForce_init ( )
{
      IsPlayerInForce_org = (IsPlayerInForce_FUNC) ( GameDll + 0x1E8140 );
      MH_CreateHook(IsPlayerInForce_org, &IsPlayerInForce_my, reinterpret_cast<void**>(&IsPlayerInForce_ptr));
      MH_EnableHook(IsPlayerInForce_org);
}
void IsPlayerObserver_init ( )
{
      IsPlayerObserver_org = (IsPlayerObserver_FUNC) ( GameDll + 0x1E8170 );
      MH_CreateHook(IsPlayerObserver_org, &IsPlayerObserver_my, reinterpret_cast<void**>(&IsPlayerObserver_ptr));
      MH_EnableHook(IsPlayerObserver_org);
}
void IsPlayerRacePrefSet_init ( )
{
      IsPlayerRacePrefSet_org = (IsPlayerRacePrefSet_FUNC) ( GameDll + 0x1E8190 );
      MH_CreateHook(IsPlayerRacePrefSet_org, &IsPlayerRacePrefSet_my, reinterpret_cast<void**>(&IsPlayerRacePrefSet_ptr));
      MH_EnableHook(IsPlayerRacePrefSet_org);
}
void IsPointBlighted_init ( )
{
      IsPointBlighted_org = (IsPointBlighted_FUNC) ( GameDll + 0x1E8250 );
      MH_CreateHook(IsPointBlighted_org, &IsPointBlighted_my, reinterpret_cast<void**>(&IsPointBlighted_ptr));
      MH_EnableHook(IsPointBlighted_org);
}
void IsPointInRegion_init ( )
{
      IsPointInRegion_org = (IsPointInRegion_FUNC) ( GameDll + 0x1E8270 );
      MH_CreateHook(IsPointInRegion_org, &IsPointInRegion_my, reinterpret_cast<void**>(&IsPointInRegion_ptr));
      MH_EnableHook(IsPointInRegion_org);
}
void IsQuestCompleted_init ( )
{
      IsQuestCompleted_org = (IsQuestCompleted_FUNC) ( GameDll + 0x1E8290 );
      MH_CreateHook(IsQuestCompleted_org, &IsQuestCompleted_my, reinterpret_cast<void**>(&IsQuestCompleted_ptr));
      MH_EnableHook(IsQuestCompleted_org);
}
void IsQuestDiscovered_init ( )
{
      IsQuestDiscovered_org = (IsQuestDiscovered_FUNC) ( GameDll + 0x1E82B0 );
      MH_CreateHook(IsQuestDiscovered_org, &IsQuestDiscovered_my, reinterpret_cast<void**>(&IsQuestDiscovered_ptr));
      MH_EnableHook(IsQuestDiscovered_org);
}
void IsQuestEnabled_init ( )
{
      IsQuestEnabled_org = (IsQuestEnabled_FUNC) ( GameDll + 0x1E82D0 );
      MH_CreateHook(IsQuestEnabled_org, &IsQuestEnabled_my, reinterpret_cast<void**>(&IsQuestEnabled_ptr));
      MH_EnableHook(IsQuestEnabled_org);
}
void IsQuestFailed_init ( )
{
      IsQuestFailed_org = (IsQuestFailed_FUNC) ( GameDll + 0x1E82F0 );
      MH_CreateHook(IsQuestFailed_org, &IsQuestFailed_my, reinterpret_cast<void**>(&IsQuestFailed_ptr));
      MH_EnableHook(IsQuestFailed_org);
}
void IsQuestItemCompleted_init ( )
{
      IsQuestItemCompleted_org = (IsQuestItemCompleted_FUNC) ( GameDll + 0x1E8310 );
      MH_CreateHook(IsQuestItemCompleted_org, &IsQuestItemCompleted_my, reinterpret_cast<void**>(&IsQuestItemCompleted_ptr));
      MH_EnableHook(IsQuestItemCompleted_org);
}
void IsQuestRequired_init ( )
{
      IsQuestRequired_org = (IsQuestRequired_FUNC) ( GameDll + 0x1E8330 );
      MH_CreateHook(IsQuestRequired_org, &IsQuestRequired_my, reinterpret_cast<void**>(&IsQuestRequired_ptr));
      MH_EnableHook(IsQuestRequired_org);
}
void IsSuspendedXP_init ( )
{
      IsSuspendedXP_org = (IsSuspendedXP_FUNC) ( GameDll + 0x1E83E0 );
      MH_CreateHook(IsSuspendedXP_org, &IsSuspendedXP_my, reinterpret_cast<void**>(&IsSuspendedXP_ptr));
      MH_EnableHook(IsSuspendedXP_org);
}
void IsTerrainPathable_init ( )
{
      IsTerrainPathable_org = (IsTerrainPathable_FUNC) ( GameDll + 0x1E8440 );
      MH_CreateHook(IsTerrainPathable_org, &IsTerrainPathable_my, reinterpret_cast<void**>(&IsTerrainPathable_ptr));
      MH_EnableHook(IsTerrainPathable_org);
}
void IsTimerDialogDisplayed_init ( )
{
      IsTimerDialogDisplayed_org = (IsTimerDialogDisplayed_FUNC) ( GameDll + 0x1E8470 );
      MH_CreateHook(IsTimerDialogDisplayed_org, &IsTimerDialogDisplayed_my, reinterpret_cast<void**>(&IsTimerDialogDisplayed_ptr));
      MH_EnableHook(IsTimerDialogDisplayed_org);
}
void IsTowered_init ( )
{
      IsTowered_org = (IsTowered_FUNC) ( GameDll + 0x8912E0 );
      MH_CreateHook(IsTowered_org, &IsTowered_my, reinterpret_cast<void**>(&IsTowered_ptr));
      MH_EnableHook(IsTowered_org);
}
void IsTriggerEnabled_init ( )
{
      IsTriggerEnabled_org = (IsTriggerEnabled_FUNC) ( GameDll + 0x1E84B0 );
      MH_CreateHook(IsTriggerEnabled_org, &IsTriggerEnabled_my, reinterpret_cast<void**>(&IsTriggerEnabled_ptr));
      MH_EnableHook(IsTriggerEnabled_org);
}
void IsTriggerWaitOnSleeps_init ( )
{
      IsTriggerWaitOnSleeps_org = (IsTriggerWaitOnSleeps_FUNC) ( GameDll + 0x1E84D0 );
      MH_CreateHook(IsTriggerWaitOnSleeps_org, &IsTriggerWaitOnSleeps_my, reinterpret_cast<void**>(&IsTriggerWaitOnSleeps_ptr));
      MH_EnableHook(IsTriggerWaitOnSleeps_org);
}
void IsUnit_init ( )
{
      IsUnit_org = (IsUnit_FUNC) ( GameDll + 0x1E84F0 );
      MH_CreateHook(IsUnit_org, &IsUnit_my, reinterpret_cast<void**>(&IsUnit_ptr));
      MH_EnableHook(IsUnit_org);
}
void IsUnitAlly_init ( )
{
      IsUnitAlly_org = (IsUnitAlly_FUNC) ( GameDll + 0x1E8520 );
      MH_CreateHook(IsUnitAlly_org, &IsUnitAlly_my, reinterpret_cast<void**>(&IsUnitAlly_ptr));
      MH_EnableHook(IsUnitAlly_org);
}
void IsUnitDetected_init ( )
{
      IsUnitDetected_org = (IsUnitDetected_FUNC) ( GameDll + 0x1E8580 );
      MH_CreateHook(IsUnitDetected_org, &IsUnitDetected_my, reinterpret_cast<void**>(&IsUnitDetected_ptr));
      MH_EnableHook(IsUnitDetected_org);
}
void IsUnitEnemy_init ( )
{
      IsUnitEnemy_org = (IsUnitEnemy_FUNC) ( GameDll + 0x1E85C0 );
      MH_CreateHook(IsUnitEnemy_org, &IsUnitEnemy_my, reinterpret_cast<void**>(&IsUnitEnemy_ptr));
      MH_EnableHook(IsUnitEnemy_org);
}
void IsUnitFogged_init ( )
{
      IsUnitFogged_org = (IsUnitFogged_FUNC) ( GameDll + 0x1E8640 );
      MH_CreateHook(IsUnitFogged_org, &IsUnitFogged_my, reinterpret_cast<void**>(&IsUnitFogged_ptr));
      MH_EnableHook(IsUnitFogged_org);
}
void IsUnitHidden_init ( )
{
      IsUnitHidden_org = (IsUnitHidden_FUNC) ( GameDll + 0x1E86C0 );
      MH_CreateHook(IsUnitHidden_org, &IsUnitHidden_my, reinterpret_cast<void**>(&IsUnitHidden_ptr));
      MH_EnableHook(IsUnitHidden_org);
}
void IsUnitIdType_init ( )
{
      IsUnitIdType_org = (IsUnitIdType_FUNC) ( GameDll + 0x1E86E0 );
      MH_CreateHook(IsUnitIdType_org, &IsUnitIdType_my, reinterpret_cast<void**>(&IsUnitIdType_ptr));
      MH_EnableHook(IsUnitIdType_org);
}
void IsUnitIllusion_init ( )
{
      IsUnitIllusion_org = (IsUnitIllusion_FUNC) ( GameDll + 0x1E88C0 );
      MH_CreateHook(IsUnitIllusion_org, &IsUnitIllusion_my, reinterpret_cast<void**>(&IsUnitIllusion_ptr));
      MH_EnableHook(IsUnitIllusion_org);
}
void IsUnitInForce_init ( )
{
      IsUnitInForce_org = (IsUnitInForce_FUNC) ( GameDll + 0x1E88E0 );
      MH_CreateHook(IsUnitInForce_org, &IsUnitInForce_my, reinterpret_cast<void**>(&IsUnitInForce_ptr));
      MH_EnableHook(IsUnitInForce_org);
}
void IsUnitInGroup_init ( )
{
      IsUnitInGroup_org = (IsUnitInGroup_FUNC) ( GameDll + 0x1E8920 );
      MH_CreateHook(IsUnitInGroup_org, &IsUnitInGroup_my, reinterpret_cast<void**>(&IsUnitInGroup_ptr));
      MH_EnableHook(IsUnitInGroup_org);
}
void IsUnitInRange_init ( )
{
      IsUnitInRange_org = (IsUnitInRange_FUNC) ( GameDll + 0x1E8950 );
      MH_CreateHook(IsUnitInRange_org, &IsUnitInRange_my, reinterpret_cast<void**>(&IsUnitInRange_ptr));
      MH_EnableHook(IsUnitInRange_org);
}
void IsUnitInRangeLoc_init ( )
{
      IsUnitInRangeLoc_org = (IsUnitInRangeLoc_FUNC) ( GameDll + 0x1E89A0 );
      MH_CreateHook(IsUnitInRangeLoc_org, &IsUnitInRangeLoc_my, reinterpret_cast<void**>(&IsUnitInRangeLoc_ptr));
      MH_EnableHook(IsUnitInRangeLoc_org);
}
void IsUnitInRangeXY_init ( )
{
      IsUnitInRangeXY_org = (IsUnitInRangeXY_FUNC) ( GameDll + 0x1E89E0 );
      MH_CreateHook(IsUnitInRangeXY_org, &IsUnitInRangeXY_my, reinterpret_cast<void**>(&IsUnitInRangeXY_ptr));
      MH_EnableHook(IsUnitInRangeXY_org);
}
void IsUnitInRegion_init ( )
{
      IsUnitInRegion_org = (IsUnitInRegion_FUNC) ( GameDll + 0x1E8A30 );
      MH_CreateHook(IsUnitInRegion_org, &IsUnitInRegion_my, reinterpret_cast<void**>(&IsUnitInRegion_ptr));
      MH_EnableHook(IsUnitInRegion_org);
}
void IsUnitInTransport_init ( )
{
      IsUnitInTransport_org = (IsUnitInTransport_FUNC) ( GameDll + 0x1E8A70 );
      MH_CreateHook(IsUnitInTransport_org, &IsUnitInTransport_my, reinterpret_cast<void**>(&IsUnitInTransport_ptr));
      MH_EnableHook(IsUnitInTransport_org);
}
void IsUnitInvisible_init ( )
{
      IsUnitInvisible_org = (IsUnitInvisible_FUNC) ( GameDll + 0x1E8AA0 );
      MH_CreateHook(IsUnitInvisible_org, &IsUnitInvisible_my, reinterpret_cast<void**>(&IsUnitInvisible_ptr));
      MH_EnableHook(IsUnitInvisible_org);
}
void IsUnitLoaded_init ( )
{
      IsUnitLoaded_org = (IsUnitLoaded_FUNC) ( GameDll + 0x1E8AE0 );
      MH_CreateHook(IsUnitLoaded_org, &IsUnitLoaded_my, reinterpret_cast<void**>(&IsUnitLoaded_ptr));
      MH_EnableHook(IsUnitLoaded_org);
}
void IsUnitMasked_init ( )
{
      IsUnitMasked_org = (IsUnitMasked_FUNC) ( GameDll + 0x1E8B00 );
      MH_CreateHook(IsUnitMasked_org, &IsUnitMasked_my, reinterpret_cast<void**>(&IsUnitMasked_ptr));
      MH_EnableHook(IsUnitMasked_org);
}
void IsUnitOwnedByPlayer_init ( )
{
      IsUnitOwnedByPlayer_org = (IsUnitOwnedByPlayer_FUNC) ( GameDll + 0x1E8B80 );
      MH_CreateHook(IsUnitOwnedByPlayer_org, &IsUnitOwnedByPlayer_my, reinterpret_cast<void**>(&IsUnitOwnedByPlayer_ptr));
      MH_EnableHook(IsUnitOwnedByPlayer_org);
}
void IsUnitPaused_init ( )
{
      IsUnitPaused_org = (IsUnitPaused_FUNC) ( GameDll + 0x1E8BC0 );
      MH_CreateHook(IsUnitPaused_org, &IsUnitPaused_my, reinterpret_cast<void**>(&IsUnitPaused_ptr));
      MH_EnableHook(IsUnitPaused_org);
}
void IsUnitRace_init ( )
{
      IsUnitRace_org = (IsUnitRace_FUNC) ( GameDll + 0x1E8C10 );
      MH_CreateHook(IsUnitRace_org, &IsUnitRace_my, reinterpret_cast<void**>(&IsUnitRace_ptr));
      MH_EnableHook(IsUnitRace_org);
}
void IsUnitSelected_init ( )
{
      IsUnitSelected_org = (IsUnitSelected_FUNC) ( GameDll + 0x1E8C40 );
      MH_CreateHook(IsUnitSelected_org, &IsUnitSelected_my, reinterpret_cast<void**>(&IsUnitSelected_ptr));
      MH_EnableHook(IsUnitSelected_org);
}
void IsUnitType_init ( )
{
      IsUnitType_org = (IsUnitType_FUNC) ( GameDll + 0x1E8CC0 );
      MH_CreateHook(IsUnitType_org, &IsUnitType_my, reinterpret_cast<void**>(&IsUnitType_ptr));
      MH_EnableHook(IsUnitType_org);
}
void IsUnitVisible_init ( )
{
      IsUnitVisible_org = (IsUnitVisible_FUNC) ( GameDll + 0x1E8E80 );
      MH_CreateHook(IsUnitVisible_org, &IsUnitVisible_my, reinterpret_cast<void**>(&IsUnitVisible_ptr));
      MH_EnableHook(IsUnitVisible_org);
}
void IsVisibleToPlayer_init ( )
{
      IsVisibleToPlayer_org = (IsVisibleToPlayer_FUNC) ( GameDll + 0x1E8F50 );
      MH_CreateHook(IsVisibleToPlayer_org, &IsVisibleToPlayer_my, reinterpret_cast<void**>(&IsVisibleToPlayer_ptr));
      MH_EnableHook(IsVisibleToPlayer_org);
}
void IssueBuildOrder_init ( )
{
      IssueBuildOrder_org = (IssueBuildOrder_FUNC) ( GameDll + 0x1E8FB0 );
      MH_CreateHook(IssueBuildOrder_org, &IssueBuildOrder_my, reinterpret_cast<void**>(&IssueBuildOrder_ptr));
      MH_EnableHook(IssueBuildOrder_org);
}
void IssueBuildOrderById_init ( )
{
      IssueBuildOrderById_org = (IssueBuildOrderById_FUNC) ( GameDll + 0x1E8FD0 );
      MH_CreateHook(IssueBuildOrderById_org, &IssueBuildOrderById_my, reinterpret_cast<void**>(&IssueBuildOrderById_ptr));
      MH_EnableHook(IssueBuildOrderById_org);
}
void IssueImmediateOrder_init ( )
{
      IssueImmediateOrder_org = (IssueImmediateOrder_FUNC) ( GameDll + 0x1E9080 );
      MH_CreateHook(IssueImmediateOrder_org, &IssueImmediateOrder_my, reinterpret_cast<void**>(&IssueImmediateOrder_ptr));
      MH_EnableHook(IssueImmediateOrder_org);
}
void IssueImmediateOrderById_init ( )
{
      IssueImmediateOrderById_org = (IssueImmediateOrderById_FUNC) ( GameDll + 0x1E90A0 );
      MH_CreateHook(IssueImmediateOrderById_org, &IssueImmediateOrderById_my, reinterpret_cast<void**>(&IssueImmediateOrderById_ptr));
      MH_EnableHook(IssueImmediateOrderById_org);
}
void IssueInstantPointOrder_init ( )
{
      IssueInstantPointOrder_org = (IssueInstantPointOrder_FUNC) ( GameDll + 0x1E9120 );
      MH_CreateHook(IssueInstantPointOrder_org, &IssueInstantPointOrder_my, reinterpret_cast<void**>(&IssueInstantPointOrder_ptr));
      MH_EnableHook(IssueInstantPointOrder_org);
}
void IssueInstantPointOrderById_init ( )
{
      IssueInstantPointOrderById_org = (IssueInstantPointOrderById_FUNC) ( GameDll + 0x1E9140 );
      MH_CreateHook(IssueInstantPointOrderById_org, &IssueInstantPointOrderById_my, reinterpret_cast<void**>(&IssueInstantPointOrderById_ptr));
      MH_EnableHook(IssueInstantPointOrderById_org);
}
void IssueInstantTargetOrder_init ( )
{
      IssueInstantTargetOrder_org = (IssueInstantTargetOrder_FUNC) ( GameDll + 0x1E91D0 );
      MH_CreateHook(IssueInstantTargetOrder_org, &IssueInstantTargetOrder_my, reinterpret_cast<void**>(&IssueInstantTargetOrder_ptr));
      MH_EnableHook(IssueInstantTargetOrder_org);
}
void IssueInstantTargetOrderById_init ( )
{
      IssueInstantTargetOrderById_org = (IssueInstantTargetOrderById_FUNC) ( GameDll + 0x1E91F0 );
      MH_CreateHook(IssueInstantTargetOrderById_org, &IssueInstantTargetOrderById_my, reinterpret_cast<void**>(&IssueInstantTargetOrderById_ptr));
      MH_EnableHook(IssueInstantTargetOrderById_org);
}
void IssueNeutralImmediateOrder_init ( )
{
      IssueNeutralImmediateOrder_org = (IssueNeutralImmediateOrder_FUNC) ( GameDll + 0x1E9310 );
      MH_CreateHook(IssueNeutralImmediateOrder_org, &IssueNeutralImmediateOrder_my, reinterpret_cast<void**>(&IssueNeutralImmediateOrder_ptr));
      MH_EnableHook(IssueNeutralImmediateOrder_org);
}
void IssueNeutralImmediateOrderById_init ( )
{
      IssueNeutralImmediateOrderById_org = (IssueNeutralImmediateOrderById_FUNC) ( GameDll + 0x1E9330 );
      MH_CreateHook(IssueNeutralImmediateOrderById_org, &IssueNeutralImmediateOrderById_my, reinterpret_cast<void**>(&IssueNeutralImmediateOrderById_ptr));
      MH_EnableHook(IssueNeutralImmediateOrderById_org);
}
void IssueNeutralPointOrder_init ( )
{
      IssueNeutralPointOrder_org = (IssueNeutralPointOrder_FUNC) ( GameDll + 0x1E9370 );
      MH_CreateHook(IssueNeutralPointOrder_org, &IssueNeutralPointOrder_my, reinterpret_cast<void**>(&IssueNeutralPointOrder_ptr));
      MH_EnableHook(IssueNeutralPointOrder_org);
}
void IssueNeutralPointOrderById_init ( )
{
      IssueNeutralPointOrderById_org = (IssueNeutralPointOrderById_FUNC) ( GameDll + 0x1E9390 );
      MH_CreateHook(IssueNeutralPointOrderById_org, &IssueNeutralPointOrderById_my, reinterpret_cast<void**>(&IssueNeutralPointOrderById_ptr));
      MH_EnableHook(IssueNeutralPointOrderById_org);
}
void IssueNeutralTargetOrder_init ( )
{
      IssueNeutralTargetOrder_org = (IssueNeutralTargetOrder_FUNC) ( GameDll + 0x1E93E0 );
      MH_CreateHook(IssueNeutralTargetOrder_org, &IssueNeutralTargetOrder_my, reinterpret_cast<void**>(&IssueNeutralTargetOrder_ptr));
      MH_EnableHook(IssueNeutralTargetOrder_org);
}
void IssueNeutralTargetOrderById_init ( )
{
      IssueNeutralTargetOrderById_org = (IssueNeutralTargetOrderById_FUNC) ( GameDll + 0x1E9400 );
      MH_CreateHook(IssueNeutralTargetOrderById_org, &IssueNeutralTargetOrderById_my, reinterpret_cast<void**>(&IssueNeutralTargetOrderById_ptr));
      MH_EnableHook(IssueNeutralTargetOrderById_org);
}
void IssuePointOrder_init ( )
{
      IssuePointOrder_org = (IssuePointOrder_FUNC) ( GameDll + 0x1E9450 );
      MH_CreateHook(IssuePointOrder_org, &IssuePointOrder_my, reinterpret_cast<void**>(&IssuePointOrder_ptr));
      MH_EnableHook(IssuePointOrder_org);
}
void IssuePointOrderById_init ( )
{
      IssuePointOrderById_org = (IssuePointOrderById_FUNC) ( GameDll + 0x1E9470 );
      MH_CreateHook(IssuePointOrderById_org, &IssuePointOrderById_my, reinterpret_cast<void**>(&IssuePointOrderById_ptr));
      MH_EnableHook(IssuePointOrderById_org);
}
void IssuePointOrderByIdLoc_init ( )
{
      IssuePointOrderByIdLoc_org = (IssuePointOrderByIdLoc_FUNC) ( GameDll + 0x1E9610 );
      MH_CreateHook(IssuePointOrderByIdLoc_org, &IssuePointOrderByIdLoc_my, reinterpret_cast<void**>(&IssuePointOrderByIdLoc_ptr));
      MH_EnableHook(IssuePointOrderByIdLoc_org);
}
void IssuePointOrderLoc_init ( )
{
      IssuePointOrderLoc_org = (IssuePointOrderLoc_FUNC) ( GameDll + 0x1E9650 );
      MH_CreateHook(IssuePointOrderLoc_org, &IssuePointOrderLoc_my, reinterpret_cast<void**>(&IssuePointOrderLoc_ptr));
      MH_EnableHook(IssuePointOrderLoc_org);
}
void IssueTargetOrder_init ( )
{
      IssueTargetOrder_org = (IssueTargetOrder_FUNC) ( GameDll + 0x1E96A0 );
      MH_CreateHook(IssueTargetOrder_org, &IssueTargetOrder_my, reinterpret_cast<void**>(&IssueTargetOrder_ptr));
      MH_EnableHook(IssueTargetOrder_org);
}
void IssueTargetOrderById_init ( )
{
      IssueTargetOrderById_org = (IssueTargetOrderById_FUNC) ( GameDll + 0x1E96C0 );
      MH_CreateHook(IssueTargetOrderById_org, &IssueTargetOrderById_my, reinterpret_cast<void**>(&IssueTargetOrderById_ptr));
      MH_EnableHook(IssueTargetOrderById_org);
}
void ItemPoolAddItemType_init ( )
{
      ItemPoolAddItemType_org = (ItemPoolAddItemType_FUNC) ( GameDll + 0x1E9980 );
      MH_CreateHook(ItemPoolAddItemType_org, &ItemPoolAddItemType_my, reinterpret_cast<void**>(&ItemPoolAddItemType_ptr));
      MH_EnableHook(ItemPoolAddItemType_org);
}
void ItemPoolRemoveItemType_init ( )
{
      ItemPoolRemoveItemType_org = (ItemPoolRemoveItemType_FUNC) ( GameDll + 0x1E99A0 );
      MH_CreateHook(ItemPoolRemoveItemType_org, &ItemPoolRemoveItemType_my, reinterpret_cast<void**>(&ItemPoolRemoveItemType_ptr));
      MH_EnableHook(ItemPoolRemoveItemType_org);
}
void KillDestructable_init ( )
{
      KillDestructable_org = (KillDestructable_FUNC) ( GameDll + 0x1EFC90 );
      MH_CreateHook(KillDestructable_org, &KillDestructable_my, reinterpret_cast<void**>(&KillDestructable_ptr));
      MH_EnableHook(KillDestructable_org);
}
void KillSoundWhenDone_init ( )
{
      KillSoundWhenDone_org = (KillSoundWhenDone_FUNC) ( GameDll + 0x1EFCB0 );
      MH_CreateHook(KillSoundWhenDone_org, &KillSoundWhenDone_my, reinterpret_cast<void**>(&KillSoundWhenDone_ptr));
      MH_EnableHook(KillSoundWhenDone_org);
}
void KillUnit_init ( )
{
      KillUnit_org = (KillUnit_FUNC) ( GameDll + 0x1EFCD0 );
      MH_CreateHook(KillUnit_org, &KillUnit_my, reinterpret_cast<void**>(&KillUnit_ptr));
      MH_EnableHook(KillUnit_org);
}
void LeaderboardAddItem_init ( )
{
      LeaderboardAddItem_org = (LeaderboardAddItem_FUNC) ( GameDll + 0x1EFCF0 );
      MH_CreateHook(LeaderboardAddItem_org, &LeaderboardAddItem_my, reinterpret_cast<void**>(&LeaderboardAddItem_ptr));
      MH_EnableHook(LeaderboardAddItem_org);
}
void LeaderboardClear_init ( )
{
      LeaderboardClear_org = (LeaderboardClear_FUNC) ( GameDll + 0x1EFD40 );
      MH_CreateHook(LeaderboardClear_org, &LeaderboardClear_my, reinterpret_cast<void**>(&LeaderboardClear_ptr));
      MH_EnableHook(LeaderboardClear_org);
}
void LeaderboardDisplay_init ( )
{
      LeaderboardDisplay_org = (LeaderboardDisplay_FUNC) ( GameDll + 0x1EFD70 );
      MH_CreateHook(LeaderboardDisplay_org, &LeaderboardDisplay_my, reinterpret_cast<void**>(&LeaderboardDisplay_ptr));
      MH_EnableHook(LeaderboardDisplay_org);
}
void LeaderboardGetItemCount_init ( )
{
      LeaderboardGetItemCount_org = (LeaderboardGetItemCount_FUNC) ( GameDll + 0x1EFDC0 );
      MH_CreateHook(LeaderboardGetItemCount_org, &LeaderboardGetItemCount_my, reinterpret_cast<void**>(&LeaderboardGetItemCount_ptr));
      MH_EnableHook(LeaderboardGetItemCount_org);
}
void LeaderboardGetLabelText_init ( )
{
      LeaderboardGetLabelText_org = (LeaderboardGetLabelText_FUNC) ( GameDll + 0x1EFDF0 );
      MH_CreateHook(LeaderboardGetLabelText_org, &LeaderboardGetLabelText_my, reinterpret_cast<void**>(&LeaderboardGetLabelText_ptr));
      MH_EnableHook(LeaderboardGetLabelText_org);
}
void LeaderboardGetPlayerIndex_init ( )
{
      LeaderboardGetPlayerIndex_org = (LeaderboardGetPlayerIndex_FUNC) ( GameDll + 0x1EFE40 );
      MH_CreateHook(LeaderboardGetPlayerIndex_org, &LeaderboardGetPlayerIndex_my, reinterpret_cast<void**>(&LeaderboardGetPlayerIndex_ptr));
      MH_EnableHook(LeaderboardGetPlayerIndex_org);
}
void LeaderboardHasPlayerItem_init ( )
{
      LeaderboardHasPlayerItem_org = (LeaderboardHasPlayerItem_FUNC) ( GameDll + 0x1EFE90 );
      MH_CreateHook(LeaderboardHasPlayerItem_org, &LeaderboardHasPlayerItem_my, reinterpret_cast<void**>(&LeaderboardHasPlayerItem_ptr));
      MH_EnableHook(LeaderboardHasPlayerItem_org);
}
void LeaderboardRemoveItem_init ( )
{
      LeaderboardRemoveItem_org = (LeaderboardRemoveItem_FUNC) ( GameDll + 0x1EFEE0 );
      MH_CreateHook(LeaderboardRemoveItem_org, &LeaderboardRemoveItem_my, reinterpret_cast<void**>(&LeaderboardRemoveItem_ptr));
      MH_EnableHook(LeaderboardRemoveItem_org);
}
void LeaderboardRemovePlayerItem_init ( )
{
      LeaderboardRemovePlayerItem_org = (LeaderboardRemovePlayerItem_FUNC) ( GameDll + 0x1EFF10 );
      MH_CreateHook(LeaderboardRemovePlayerItem_org, &LeaderboardRemovePlayerItem_my, reinterpret_cast<void**>(&LeaderboardRemovePlayerItem_ptr));
      MH_EnableHook(LeaderboardRemovePlayerItem_org);
}
void LeaderboardSetItemLabel_init ( )
{
      LeaderboardSetItemLabel_org = (LeaderboardSetItemLabel_FUNC) ( GameDll + 0x1EFF50 );
      MH_CreateHook(LeaderboardSetItemLabel_org, &LeaderboardSetItemLabel_my, reinterpret_cast<void**>(&LeaderboardSetItemLabel_ptr));
      MH_EnableHook(LeaderboardSetItemLabel_org);
}
void LeaderboardSetItemLabelColor_init ( )
{
      LeaderboardSetItemLabelColor_org = (LeaderboardSetItemLabelColor_FUNC) ( GameDll + 0x1EFF90 );
      MH_CreateHook(LeaderboardSetItemLabelColor_org, &LeaderboardSetItemLabelColor_my, reinterpret_cast<void**>(&LeaderboardSetItemLabelColor_ptr));
      MH_EnableHook(LeaderboardSetItemLabelColor_org);
}
void LeaderboardSetItemStyle_init ( )
{
      LeaderboardSetItemStyle_org = (LeaderboardSetItemStyle_FUNC) ( GameDll + 0x1EFFF0 );
      MH_CreateHook(LeaderboardSetItemStyle_org, &LeaderboardSetItemStyle_my, reinterpret_cast<void**>(&LeaderboardSetItemStyle_ptr));
      MH_EnableHook(LeaderboardSetItemStyle_org);
}
void LeaderboardSetItemValue_init ( )
{
      LeaderboardSetItemValue_org = (LeaderboardSetItemValue_FUNC) ( GameDll + 0x1F0040 );
      MH_CreateHook(LeaderboardSetItemValue_org, &LeaderboardSetItemValue_my, reinterpret_cast<void**>(&LeaderboardSetItemValue_ptr));
      MH_EnableHook(LeaderboardSetItemValue_org);
}
void LeaderboardSetItemValueColor_init ( )
{
      LeaderboardSetItemValueColor_org = (LeaderboardSetItemValueColor_FUNC) ( GameDll + 0x1F0070 );
      MH_CreateHook(LeaderboardSetItemValueColor_org, &LeaderboardSetItemValueColor_my, reinterpret_cast<void**>(&LeaderboardSetItemValueColor_ptr));
      MH_EnableHook(LeaderboardSetItemValueColor_org);
}
void LeaderboardSetLabel_init ( )
{
      LeaderboardSetLabel_org = (LeaderboardSetLabel_FUNC) ( GameDll + 0x1F00D0 );
      MH_CreateHook(LeaderboardSetLabel_org, &LeaderboardSetLabel_my, reinterpret_cast<void**>(&LeaderboardSetLabel_ptr));
      MH_EnableHook(LeaderboardSetLabel_org);
}
void LeaderboardSetLabelColor_init ( )
{
      LeaderboardSetLabelColor_org = (LeaderboardSetLabelColor_FUNC) ( GameDll + 0x1F0100 );
      MH_CreateHook(LeaderboardSetLabelColor_org, &LeaderboardSetLabelColor_my, reinterpret_cast<void**>(&LeaderboardSetLabelColor_ptr));
      MH_EnableHook(LeaderboardSetLabelColor_org);
}
void LeaderboardSetSizeByItemCount_init ( )
{
      LeaderboardSetSizeByItemCount_org = (LeaderboardSetSizeByItemCount_FUNC) ( GameDll + 0x1F0160 );
      MH_CreateHook(LeaderboardSetSizeByItemCount_org, &LeaderboardSetSizeByItemCount_my, reinterpret_cast<void**>(&LeaderboardSetSizeByItemCount_ptr));
      MH_EnableHook(LeaderboardSetSizeByItemCount_org);
}
void LeaderboardSetStyle_init ( )
{
      LeaderboardSetStyle_org = (LeaderboardSetStyle_FUNC) ( GameDll + 0x1F0190 );
      MH_CreateHook(LeaderboardSetStyle_org, &LeaderboardSetStyle_my, reinterpret_cast<void**>(&LeaderboardSetStyle_ptr));
      MH_EnableHook(LeaderboardSetStyle_org);
}
void LeaderboardSetValueColor_init ( )
{
      LeaderboardSetValueColor_org = (LeaderboardSetValueColor_FUNC) ( GameDll + 0x1F01E0 );
      MH_CreateHook(LeaderboardSetValueColor_org, &LeaderboardSetValueColor_my, reinterpret_cast<void**>(&LeaderboardSetValueColor_ptr));
      MH_EnableHook(LeaderboardSetValueColor_org);
}
void LeaderboardSortItemsByLabel_init ( )
{
      LeaderboardSortItemsByLabel_org = (LeaderboardSortItemsByLabel_FUNC) ( GameDll + 0x1F0240 );
      MH_CreateHook(LeaderboardSortItemsByLabel_org, &LeaderboardSortItemsByLabel_my, reinterpret_cast<void**>(&LeaderboardSortItemsByLabel_ptr));
      MH_EnableHook(LeaderboardSortItemsByLabel_org);
}
void LeaderboardSortItemsByPlayer_init ( )
{
      LeaderboardSortItemsByPlayer_org = (LeaderboardSortItemsByPlayer_FUNC) ( GameDll + 0x1F0270 );
      MH_CreateHook(LeaderboardSortItemsByPlayer_org, &LeaderboardSortItemsByPlayer_my, reinterpret_cast<void**>(&LeaderboardSortItemsByPlayer_ptr));
      MH_EnableHook(LeaderboardSortItemsByPlayer_org);
}
void LeaderboardSortItemsByValue_init ( )
{
      LeaderboardSortItemsByValue_org = (LeaderboardSortItemsByValue_FUNC) ( GameDll + 0x1F02A0 );
      MH_CreateHook(LeaderboardSortItemsByValue_org, &LeaderboardSortItemsByValue_my, reinterpret_cast<void**>(&LeaderboardSortItemsByValue_ptr));
      MH_EnableHook(LeaderboardSortItemsByValue_org);
}
void LoadAbilityHandle_init ( )
{
      LoadAbilityHandle_org = (LoadAbilityHandle_FUNC) ( GameDll + 0x1F04B0 );
      MH_CreateHook(LoadAbilityHandle_org, &LoadAbilityHandle_my, reinterpret_cast<void**>(&LoadAbilityHandle_ptr));
      MH_EnableHook(LoadAbilityHandle_org);
}
void LoadBoolean_init ( )
{
      LoadBoolean_org = (LoadBoolean_FUNC) ( GameDll + 0x1F04D0 );
      MH_CreateHook(LoadBoolean_org, &LoadBoolean_my, reinterpret_cast<void**>(&LoadBoolean_ptr));
      MH_EnableHook(LoadBoolean_org);
}
void LoadBooleanExprHandle_init ( )
{
      LoadBooleanExprHandle_org = (LoadBooleanExprHandle_FUNC) ( GameDll + 0x1F0510 );
      MH_CreateHook(LoadBooleanExprHandle_org, &LoadBooleanExprHandle_my, reinterpret_cast<void**>(&LoadBooleanExprHandle_ptr));
      MH_EnableHook(LoadBooleanExprHandle_org);
}
void LoadButtonHandle_init ( )
{
      LoadButtonHandle_org = (LoadButtonHandle_FUNC) ( GameDll + 0x1F0530 );
      MH_CreateHook(LoadButtonHandle_org, &LoadButtonHandle_my, reinterpret_cast<void**>(&LoadButtonHandle_ptr));
      MH_EnableHook(LoadButtonHandle_org);
}
void LoadDefeatConditionHandle_init ( )
{
      LoadDefeatConditionHandle_org = (LoadDefeatConditionHandle_FUNC) ( GameDll + 0x1F0550 );
      MH_CreateHook(LoadDefeatConditionHandle_org, &LoadDefeatConditionHandle_my, reinterpret_cast<void**>(&LoadDefeatConditionHandle_ptr));
      MH_EnableHook(LoadDefeatConditionHandle_org);
}
void LoadDestructableHandle_init ( )
{
      LoadDestructableHandle_org = (LoadDestructableHandle_FUNC) ( GameDll + 0x1F0570 );
      MH_CreateHook(LoadDestructableHandle_org, &LoadDestructableHandle_my, reinterpret_cast<void**>(&LoadDestructableHandle_ptr));
      MH_EnableHook(LoadDestructableHandle_org);
}
void LoadDialogHandle_init ( )
{
      LoadDialogHandle_org = (LoadDialogHandle_FUNC) ( GameDll + 0x1F0590 );
      MH_CreateHook(LoadDialogHandle_org, &LoadDialogHandle_my, reinterpret_cast<void**>(&LoadDialogHandle_ptr));
      MH_EnableHook(LoadDialogHandle_org);
}
void LoadEffectHandle_init ( )
{
      LoadEffectHandle_org = (LoadEffectHandle_FUNC) ( GameDll + 0x1F05B0 );
      MH_CreateHook(LoadEffectHandle_org, &LoadEffectHandle_my, reinterpret_cast<void**>(&LoadEffectHandle_ptr));
      MH_EnableHook(LoadEffectHandle_org);
}
void LoadFogModifierHandle_init ( )
{
      LoadFogModifierHandle_org = (LoadFogModifierHandle_FUNC) ( GameDll + 0x1F05D0 );
      MH_CreateHook(LoadFogModifierHandle_org, &LoadFogModifierHandle_my, reinterpret_cast<void**>(&LoadFogModifierHandle_ptr));
      MH_EnableHook(LoadFogModifierHandle_org);
}
void LoadFogStateHandle_init ( )
{
      LoadFogStateHandle_org = (LoadFogStateHandle_FUNC) ( GameDll + 0x1F05F0 );
      MH_CreateHook(LoadFogStateHandle_org, &LoadFogStateHandle_my, reinterpret_cast<void**>(&LoadFogStateHandle_ptr));
      MH_EnableHook(LoadFogStateHandle_org);
}
void LoadForceHandle_init ( )
{
      LoadForceHandle_org = (LoadForceHandle_FUNC) ( GameDll + 0x1F0610 );
      MH_CreateHook(LoadForceHandle_org, &LoadForceHandle_my, reinterpret_cast<void**>(&LoadForceHandle_ptr));
      MH_EnableHook(LoadForceHandle_org);
}
void LoadGame_init ( )
{
      LoadGame_org = (LoadGame_FUNC) ( GameDll + 0x1F0630 );
      MH_CreateHook(LoadGame_org, &LoadGame_my, reinterpret_cast<void**>(&LoadGame_ptr));
      MH_EnableHook(LoadGame_org);
}
void LoadGroupHandle_init ( )
{
      LoadGroupHandle_org = (LoadGroupHandle_FUNC) ( GameDll + 0x1F06B0 );
      MH_CreateHook(LoadGroupHandle_org, &LoadGroupHandle_my, reinterpret_cast<void**>(&LoadGroupHandle_ptr));
      MH_EnableHook(LoadGroupHandle_org);
}
void LoadHashtableHandle_init ( )
{
      LoadHashtableHandle_org = (LoadHashtableHandle_FUNC) ( GameDll + 0x1F06D0 );
      MH_CreateHook(LoadHashtableHandle_org, &LoadHashtableHandle_my, reinterpret_cast<void**>(&LoadHashtableHandle_ptr));
      MH_EnableHook(LoadHashtableHandle_org);
}
void LoadImageHandle_init ( )
{
      LoadImageHandle_org = (LoadImageHandle_FUNC) ( GameDll + 0x1F06F0 );
      MH_CreateHook(LoadImageHandle_org, &LoadImageHandle_my, reinterpret_cast<void**>(&LoadImageHandle_ptr));
      MH_EnableHook(LoadImageHandle_org);
}
void LoadInteger_init ( )
{
      LoadInteger_org = (LoadInteger_FUNC) ( GameDll + 0x1F0710 );
      MH_CreateHook(LoadInteger_org, &LoadInteger_my, reinterpret_cast<void**>(&LoadInteger_ptr));
      MH_EnableHook(LoadInteger_org);
}
void LoadItemHandle_init ( )
{
      LoadItemHandle_org = (LoadItemHandle_FUNC) ( GameDll + 0x1F0750 );
      MH_CreateHook(LoadItemHandle_org, &LoadItemHandle_my, reinterpret_cast<void**>(&LoadItemHandle_ptr));
      MH_EnableHook(LoadItemHandle_org);
}
void LoadItemPoolHandle_init ( )
{
      LoadItemPoolHandle_org = (LoadItemPoolHandle_FUNC) ( GameDll + 0x1F0770 );
      MH_CreateHook(LoadItemPoolHandle_org, &LoadItemPoolHandle_my, reinterpret_cast<void**>(&LoadItemPoolHandle_ptr));
      MH_EnableHook(LoadItemPoolHandle_org);
}
void LoadLeaderboardHandle_init ( )
{
      LoadLeaderboardHandle_org = (LoadLeaderboardHandle_FUNC) ( GameDll + 0x1F0790 );
      MH_CreateHook(LoadLeaderboardHandle_org, &LoadLeaderboardHandle_my, reinterpret_cast<void**>(&LoadLeaderboardHandle_ptr));
      MH_EnableHook(LoadLeaderboardHandle_org);
}
void LoadLightningHandle_init ( )
{
      LoadLightningHandle_org = (LoadLightningHandle_FUNC) ( GameDll + 0x1F07B0 );
      MH_CreateHook(LoadLightningHandle_org, &LoadLightningHandle_my, reinterpret_cast<void**>(&LoadLightningHandle_ptr));
      MH_EnableHook(LoadLightningHandle_org);
}
void LoadLocationHandle_init ( )
{
      LoadLocationHandle_org = (LoadLocationHandle_FUNC) ( GameDll + 0x1F07D0 );
      MH_CreateHook(LoadLocationHandle_org, &LoadLocationHandle_my, reinterpret_cast<void**>(&LoadLocationHandle_ptr));
      MH_EnableHook(LoadLocationHandle_org);
}
void LoadMultiboardHandle_init ( )
{
      LoadMultiboardHandle_org = (LoadMultiboardHandle_FUNC) ( GameDll + 0x1F07F0 );
      MH_CreateHook(LoadMultiboardHandle_org, &LoadMultiboardHandle_my, reinterpret_cast<void**>(&LoadMultiboardHandle_ptr));
      MH_EnableHook(LoadMultiboardHandle_org);
}
void LoadMultiboardItemHandle_init ( )
{
      LoadMultiboardItemHandle_org = (LoadMultiboardItemHandle_FUNC) ( GameDll + 0x1F0810 );
      MH_CreateHook(LoadMultiboardItemHandle_org, &LoadMultiboardItemHandle_my, reinterpret_cast<void**>(&LoadMultiboardItemHandle_ptr));
      MH_EnableHook(LoadMultiboardItemHandle_org);
}
void LoadPlayerHandle_init ( )
{
      LoadPlayerHandle_org = (LoadPlayerHandle_FUNC) ( GameDll + 0x1F0830 );
      MH_CreateHook(LoadPlayerHandle_org, &LoadPlayerHandle_my, reinterpret_cast<void**>(&LoadPlayerHandle_ptr));
      MH_EnableHook(LoadPlayerHandle_org);
}
void LoadQuestHandle_init ( )
{
      LoadQuestHandle_org = (LoadQuestHandle_FUNC) ( GameDll + 0x1F0850 );
      MH_CreateHook(LoadQuestHandle_org, &LoadQuestHandle_my, reinterpret_cast<void**>(&LoadQuestHandle_ptr));
      MH_EnableHook(LoadQuestHandle_org);
}
void LoadQuestItemHandle_init ( )
{
      LoadQuestItemHandle_org = (LoadQuestItemHandle_FUNC) ( GameDll + 0x1F0870 );
      MH_CreateHook(LoadQuestItemHandle_org, &LoadQuestItemHandle_my, reinterpret_cast<void**>(&LoadQuestItemHandle_ptr));
      MH_EnableHook(LoadQuestItemHandle_org);
}
void LoadReal_init ( )
{
      LoadReal_org = (LoadReal_FUNC) ( GameDll + 0x1F0890 );
      MH_CreateHook(LoadReal_org, &LoadReal_my, reinterpret_cast<void**>(&LoadReal_ptr));
      MH_EnableHook(LoadReal_org);
}
void LoadRectHandle_init ( )
{
      LoadRectHandle_org = (LoadRectHandle_FUNC) ( GameDll + 0x1F08D0 );
      MH_CreateHook(LoadRectHandle_org, &LoadRectHandle_my, reinterpret_cast<void**>(&LoadRectHandle_ptr));
      MH_EnableHook(LoadRectHandle_org);
}
void LoadRegionHandle_init ( )
{
      LoadRegionHandle_org = (LoadRegionHandle_FUNC) ( GameDll + 0x1F08F0 );
      MH_CreateHook(LoadRegionHandle_org, &LoadRegionHandle_my, reinterpret_cast<void**>(&LoadRegionHandle_ptr));
      MH_EnableHook(LoadRegionHandle_org);
}
void LoadSoundHandle_init ( )
{
      LoadSoundHandle_org = (LoadSoundHandle_FUNC) ( GameDll + 0x1F0A30 );
      MH_CreateHook(LoadSoundHandle_org, &LoadSoundHandle_my, reinterpret_cast<void**>(&LoadSoundHandle_ptr));
      MH_EnableHook(LoadSoundHandle_org);
}
void LoadStr_init ( )
{
      LoadStr_org = (LoadStr_FUNC) ( GameDll + 0x1F0A50 );
      MH_CreateHook(LoadStr_org, &LoadStr_my, reinterpret_cast<void**>(&LoadStr_ptr));
      MH_EnableHook(LoadStr_org);
}
void LoadTextTagHandle_init ( )
{
      LoadTextTagHandle_org = (LoadTextTagHandle_FUNC) ( GameDll + 0x1F0A90 );
      MH_CreateHook(LoadTextTagHandle_org, &LoadTextTagHandle_my, reinterpret_cast<void**>(&LoadTextTagHandle_ptr));
      MH_EnableHook(LoadTextTagHandle_org);
}
void LoadTimerDialogHandle_init ( )
{
      LoadTimerDialogHandle_org = (LoadTimerDialogHandle_FUNC) ( GameDll + 0x1F0AB0 );
      MH_CreateHook(LoadTimerDialogHandle_org, &LoadTimerDialogHandle_my, reinterpret_cast<void**>(&LoadTimerDialogHandle_ptr));
      MH_EnableHook(LoadTimerDialogHandle_org);
}
void LoadTimerHandle_init ( )
{
      LoadTimerHandle_org = (LoadTimerHandle_FUNC) ( GameDll + 0x1F0AD0 );
      MH_CreateHook(LoadTimerHandle_org, &LoadTimerHandle_my, reinterpret_cast<void**>(&LoadTimerHandle_ptr));
      MH_EnableHook(LoadTimerHandle_org);
}
void LoadTrackableHandle_init ( )
{
      LoadTrackableHandle_org = (LoadTrackableHandle_FUNC) ( GameDll + 0x1F0AF0 );
      MH_CreateHook(LoadTrackableHandle_org, &LoadTrackableHandle_my, reinterpret_cast<void**>(&LoadTrackableHandle_ptr));
      MH_EnableHook(LoadTrackableHandle_org);
}
void LoadTriggerActionHandle_init ( )
{
      LoadTriggerActionHandle_org = (LoadTriggerActionHandle_FUNC) ( GameDll + 0x1F0B10 );
      MH_CreateHook(LoadTriggerActionHandle_org, &LoadTriggerActionHandle_my, reinterpret_cast<void**>(&LoadTriggerActionHandle_ptr));
      MH_EnableHook(LoadTriggerActionHandle_org);
}
void LoadTriggerConditionHandle_init ( )
{
      LoadTriggerConditionHandle_org = (LoadTriggerConditionHandle_FUNC) ( GameDll + 0x1F0B30 );
      MH_CreateHook(LoadTriggerConditionHandle_org, &LoadTriggerConditionHandle_my, reinterpret_cast<void**>(&LoadTriggerConditionHandle_ptr));
      MH_EnableHook(LoadTriggerConditionHandle_org);
}
void LoadTriggerEventHandle_init ( )
{
      LoadTriggerEventHandle_org = (LoadTriggerEventHandle_FUNC) ( GameDll + 0x1F0B50 );
      MH_CreateHook(LoadTriggerEventHandle_org, &LoadTriggerEventHandle_my, reinterpret_cast<void**>(&LoadTriggerEventHandle_ptr));
      MH_EnableHook(LoadTriggerEventHandle_org);
}
void LoadTriggerHandle_init ( )
{
      LoadTriggerHandle_org = (LoadTriggerHandle_FUNC) ( GameDll + 0x1F0B70 );
      MH_CreateHook(LoadTriggerHandle_org, &LoadTriggerHandle_my, reinterpret_cast<void**>(&LoadTriggerHandle_ptr));
      MH_EnableHook(LoadTriggerHandle_org);
}
void LoadUbersplatHandle_init ( )
{
      LoadUbersplatHandle_org = (LoadUbersplatHandle_FUNC) ( GameDll + 0x1F0B90 );
      MH_CreateHook(LoadUbersplatHandle_org, &LoadUbersplatHandle_my, reinterpret_cast<void**>(&LoadUbersplatHandle_ptr));
      MH_EnableHook(LoadUbersplatHandle_org);
}
void LoadUnitHandle_init ( )
{
      LoadUnitHandle_org = (LoadUnitHandle_FUNC) ( GameDll + 0x1F0BB0 );
      MH_CreateHook(LoadUnitHandle_org, &LoadUnitHandle_my, reinterpret_cast<void**>(&LoadUnitHandle_ptr));
      MH_EnableHook(LoadUnitHandle_org);
}
void LoadUnitPoolHandle_init ( )
{
      LoadUnitPoolHandle_org = (LoadUnitPoolHandle_FUNC) ( GameDll + 0x1F0BD0 );
      MH_CreateHook(LoadUnitPoolHandle_org, &LoadUnitPoolHandle_my, reinterpret_cast<void**>(&LoadUnitPoolHandle_ptr));
      MH_EnableHook(LoadUnitPoolHandle_org);
}
void LoadWidgetHandle_init ( )
{
      LoadWidgetHandle_org = (LoadWidgetHandle_FUNC) ( GameDll + 0x1F0BF0 );
      MH_CreateHook(LoadWidgetHandle_org, &LoadWidgetHandle_my, reinterpret_cast<void**>(&LoadWidgetHandle_ptr));
      MH_EnableHook(LoadWidgetHandle_org);
}
void LoadZepWave_init ( )
{
      LoadZepWave_org = (LoadZepWave_FUNC) ( GameDll + 0x8917C0 );
      MH_CreateHook(LoadZepWave_org, &LoadZepWave_my, reinterpret_cast<void**>(&LoadZepWave_ptr));
      MH_EnableHook(LoadZepWave_org);
}
void Location_init ( )
{
      Location_org = (Location_FUNC) ( GameDll + 0x1F0C10 );
      MH_CreateHook(Location_org, &Location_my, reinterpret_cast<void**>(&Location_ptr));
      MH_EnableHook(Location_org);
}
void MeleeDifficulty_init ( )
{
      MeleeDifficulty_org = (MeleeDifficulty_FUNC) ( GameDll + 0x891E70 );
      MH_CreateHook(MeleeDifficulty_org, &MeleeDifficulty_my, reinterpret_cast<void**>(&MeleeDifficulty_ptr));
      MH_EnableHook(MeleeDifficulty_org);
}
void MergeUnits_init ( )
{
      MergeUnits_org = (MergeUnits_FUNC) ( GameDll + 0x891F20 );
      MH_CreateHook(MergeUnits_org, &MergeUnits_my, reinterpret_cast<void**>(&MergeUnits_ptr));
      MH_EnableHook(MergeUnits_org);
}
void MoveLightning_init ( )
{
      MoveLightning_org = (MoveLightning_FUNC) ( GameDll + 0x1F0D60 );
      MH_CreateHook(MoveLightning_org, &MoveLightning_my, reinterpret_cast<void**>(&MoveLightning_ptr));
      MH_EnableHook(MoveLightning_org);
}
void MoveLightningEx_init ( )
{
      MoveLightningEx_org = (MoveLightningEx_FUNC) ( GameDll + 0x1F0DE0 );
      MH_CreateHook(MoveLightningEx_org, &MoveLightningEx_my, reinterpret_cast<void**>(&MoveLightningEx_ptr));
      MH_EnableHook(MoveLightningEx_org);
}
void MoveLocation_init ( )
{
      MoveLocation_org = (MoveLocation_FUNC) ( GameDll + 0x1F0EC0 );
      MH_CreateHook(MoveLocation_org, &MoveLocation_my, reinterpret_cast<void**>(&MoveLocation_ptr));
      MH_EnableHook(MoveLocation_org);
}
void MoveRectTo_init ( )
{
      MoveRectTo_org = (MoveRectTo_FUNC) ( GameDll + 0x1F0EF0 );
      MH_CreateHook(MoveRectTo_org, &MoveRectTo_my, reinterpret_cast<void**>(&MoveRectTo_ptr));
      MH_EnableHook(MoveRectTo_org);
}
void MoveRectToLoc_init ( )
{
      MoveRectToLoc_org = (MoveRectToLoc_FUNC) ( GameDll + 0x1F0F20 );
      MH_CreateHook(MoveRectToLoc_org, &MoveRectToLoc_my, reinterpret_cast<void**>(&MoveRectToLoc_ptr));
      MH_EnableHook(MoveRectToLoc_org);
}
void MultiboardClear_init ( )
{
      MultiboardClear_org = (MultiboardClear_FUNC) ( GameDll + 0x1F1030 );
      MH_CreateHook(MultiboardClear_org, &MultiboardClear_my, reinterpret_cast<void**>(&MultiboardClear_ptr));
      MH_EnableHook(MultiboardClear_org);
}
void MultiboardDisplay_init ( )
{
      MultiboardDisplay_org = (MultiboardDisplay_FUNC) ( GameDll + 0x1F1060 );
      MH_CreateHook(MultiboardDisplay_org, &MultiboardDisplay_my, reinterpret_cast<void**>(&MultiboardDisplay_ptr));
      MH_EnableHook(MultiboardDisplay_org);
}
void MultiboardGetColumnCount_init ( )
{
      MultiboardGetColumnCount_org = (MultiboardGetColumnCount_FUNC) ( GameDll + 0x1F1080 );
      MH_CreateHook(MultiboardGetColumnCount_org, &MultiboardGetColumnCount_my, reinterpret_cast<void**>(&MultiboardGetColumnCount_ptr));
      MH_EnableHook(MultiboardGetColumnCount_org);
}
void MultiboardGetItem_init ( )
{
      MultiboardGetItem_org = (MultiboardGetItem_FUNC) ( GameDll + 0x1F10A0 );
      MH_CreateHook(MultiboardGetItem_org, &MultiboardGetItem_my, reinterpret_cast<void**>(&MultiboardGetItem_ptr));
      MH_EnableHook(MultiboardGetItem_org);
}
void MultiboardGetRowCount_init ( )
{
      MultiboardGetRowCount_org = (MultiboardGetRowCount_FUNC) ( GameDll + 0x1F1160 );
      MH_CreateHook(MultiboardGetRowCount_org, &MultiboardGetRowCount_my, reinterpret_cast<void**>(&MultiboardGetRowCount_ptr));
      MH_EnableHook(MultiboardGetRowCount_org);
}
void MultiboardGetTitleText_init ( )
{
      MultiboardGetTitleText_org = (MultiboardGetTitleText_FUNC) ( GameDll + 0x1F1180 );
      MH_CreateHook(MultiboardGetTitleText_org, &MultiboardGetTitleText_my, reinterpret_cast<void**>(&MultiboardGetTitleText_ptr));
      MH_EnableHook(MultiboardGetTitleText_org);
}
void MultiboardMinimize_init ( )
{
      MultiboardMinimize_org = (MultiboardMinimize_FUNC) ( GameDll + 0x1F11A0 );
      MH_CreateHook(MultiboardMinimize_org, &MultiboardMinimize_my, reinterpret_cast<void**>(&MultiboardMinimize_ptr));
      MH_EnableHook(MultiboardMinimize_org);
}
void MultiboardReleaseItem_init ( )
{
      MultiboardReleaseItem_org = (MultiboardReleaseItem_FUNC) ( GameDll + 0x1F11C0 );
      MH_CreateHook(MultiboardReleaseItem_org, &MultiboardReleaseItem_my, reinterpret_cast<void**>(&MultiboardReleaseItem_ptr));
      MH_EnableHook(MultiboardReleaseItem_org);
}
void MultiboardSetColumnCount_init ( )
{
      MultiboardSetColumnCount_org = (MultiboardSetColumnCount_FUNC) ( GameDll + 0x1F11E0 );
      MH_CreateHook(MultiboardSetColumnCount_org, &MultiboardSetColumnCount_my, reinterpret_cast<void**>(&MultiboardSetColumnCount_ptr));
      MH_EnableHook(MultiboardSetColumnCount_org);
}
void MultiboardSetItemIcon_init ( )
{
      MultiboardSetItemIcon_org = (MultiboardSetItemIcon_FUNC) ( GameDll + 0x1F1200 );
      MH_CreateHook(MultiboardSetItemIcon_org, &MultiboardSetItemIcon_my, reinterpret_cast<void**>(&MultiboardSetItemIcon_ptr));
      MH_EnableHook(MultiboardSetItemIcon_org);
}
void MultiboardSetItemStyle_init ( )
{
      MultiboardSetItemStyle_org = (MultiboardSetItemStyle_FUNC) ( GameDll + 0x1F1230 );
      MH_CreateHook(MultiboardSetItemStyle_org, &MultiboardSetItemStyle_my, reinterpret_cast<void**>(&MultiboardSetItemStyle_ptr));
      MH_EnableHook(MultiboardSetItemStyle_org);
}
void MultiboardSetItemValue_init ( )
{
      MultiboardSetItemValue_org = (MultiboardSetItemValue_FUNC) ( GameDll + 0x1F1250 );
      MH_CreateHook(MultiboardSetItemValue_org, &MultiboardSetItemValue_my, reinterpret_cast<void**>(&MultiboardSetItemValue_ptr));
      MH_EnableHook(MultiboardSetItemValue_org);
}
void MultiboardSetItemValueColor_init ( )
{
      MultiboardSetItemValueColor_org = (MultiboardSetItemValueColor_FUNC) ( GameDll + 0x1F1280 );
      MH_CreateHook(MultiboardSetItemValueColor_org, &MultiboardSetItemValueColor_my, reinterpret_cast<void**>(&MultiboardSetItemValueColor_ptr));
      MH_EnableHook(MultiboardSetItemValueColor_org);
}
void MultiboardSetItemWidth_init ( )
{
      MultiboardSetItemWidth_org = (MultiboardSetItemWidth_FUNC) ( GameDll + 0x1F12D0 );
      MH_CreateHook(MultiboardSetItemWidth_org, &MultiboardSetItemWidth_my, reinterpret_cast<void**>(&MultiboardSetItemWidth_ptr));
      MH_EnableHook(MultiboardSetItemWidth_org);
}
void MultiboardSetItemsIcon_init ( )
{
      MultiboardSetItemsIcon_org = (MultiboardSetItemsIcon_FUNC) ( GameDll + 0x1F1300 );
      MH_CreateHook(MultiboardSetItemsIcon_org, &MultiboardSetItemsIcon_my, reinterpret_cast<void**>(&MultiboardSetItemsIcon_ptr));
      MH_EnableHook(MultiboardSetItemsIcon_org);
}
void MultiboardSetItemsStyle_init ( )
{
      MultiboardSetItemsStyle_org = (MultiboardSetItemsStyle_FUNC) ( GameDll + 0x1F1330 );
      MH_CreateHook(MultiboardSetItemsStyle_org, &MultiboardSetItemsStyle_my, reinterpret_cast<void**>(&MultiboardSetItemsStyle_ptr));
      MH_EnableHook(MultiboardSetItemsStyle_org);
}
void MultiboardSetItemsValue_init ( )
{
      MultiboardSetItemsValue_org = (MultiboardSetItemsValue_FUNC) ( GameDll + 0x1F1370 );
      MH_CreateHook(MultiboardSetItemsValue_org, &MultiboardSetItemsValue_my, reinterpret_cast<void**>(&MultiboardSetItemsValue_ptr));
      MH_EnableHook(MultiboardSetItemsValue_org);
}
void MultiboardSetItemsValueColor_init ( )
{
      MultiboardSetItemsValueColor_org = (MultiboardSetItemsValueColor_FUNC) ( GameDll + 0x1F13A0 );
      MH_CreateHook(MultiboardSetItemsValueColor_org, &MultiboardSetItemsValueColor_my, reinterpret_cast<void**>(&MultiboardSetItemsValueColor_ptr));
      MH_EnableHook(MultiboardSetItemsValueColor_org);
}
void MultiboardSetItemsWidth_init ( )
{
      MultiboardSetItemsWidth_org = (MultiboardSetItemsWidth_FUNC) ( GameDll + 0x1F1400 );
      MH_CreateHook(MultiboardSetItemsWidth_org, &MultiboardSetItemsWidth_my, reinterpret_cast<void**>(&MultiboardSetItemsWidth_ptr));
      MH_EnableHook(MultiboardSetItemsWidth_org);
}
void MultiboardSetRowCount_init ( )
{
      MultiboardSetRowCount_org = (MultiboardSetRowCount_FUNC) ( GameDll + 0x1F1430 );
      MH_CreateHook(MultiboardSetRowCount_org, &MultiboardSetRowCount_my, reinterpret_cast<void**>(&MultiboardSetRowCount_ptr));
      MH_EnableHook(MultiboardSetRowCount_org);
}
void MultiboardSetTitleText_init ( )
{
      MultiboardSetTitleText_org = (MultiboardSetTitleText_FUNC) ( GameDll + 0x1F1450 );
      MH_CreateHook(MultiboardSetTitleText_org, &MultiboardSetTitleText_my, reinterpret_cast<void**>(&MultiboardSetTitleText_ptr));
      MH_EnableHook(MultiboardSetTitleText_org);
}
void MultiboardSetTitleTextColor_init ( )
{
      MultiboardSetTitleTextColor_org = (MultiboardSetTitleTextColor_FUNC) ( GameDll + 0x1F1480 );
      MH_CreateHook(MultiboardSetTitleTextColor_org, &MultiboardSetTitleTextColor_my, reinterpret_cast<void**>(&MultiboardSetTitleTextColor_ptr));
      MH_EnableHook(MultiboardSetTitleTextColor_org);
}
void MultiboardSuppressDisplay_init ( )
{
      MultiboardSuppressDisplay_org = (MultiboardSuppressDisplay_FUNC) ( GameDll + 0x1F14D0 );
      MH_CreateHook(MultiboardSuppressDisplay_org, &MultiboardSuppressDisplay_my, reinterpret_cast<void**>(&MultiboardSuppressDisplay_ptr));
      MH_EnableHook(MultiboardSuppressDisplay_org);
}
void NewSoundEnvironment_init ( )
{
      NewSoundEnvironment_org = (NewSoundEnvironment_FUNC) ( GameDll + 0x1F15B0 );
      MH_CreateHook(NewSoundEnvironment_org, &NewSoundEnvironment_my, reinterpret_cast<void**>(&NewSoundEnvironment_ptr));
      MH_EnableHook(NewSoundEnvironment_org);
}
void Not_init ( )
{
      Not_org = (Not_FUNC) ( GameDll + 0x1F1600 );
      MH_CreateHook(Not_org, &Not_my, reinterpret_cast<void**>(&Not_ptr));
      MH_EnableHook(Not_org);
}
void Or_init ( )
{
      Or_org = (Or_FUNC) ( GameDll + 0x1F17A0 );
      MH_CreateHook(Or_org, &Or_my, reinterpret_cast<void**>(&Or_ptr));
      MH_EnableHook(Or_org);
}
void OrderId_init ( )
{
      OrderId_org = (OrderId_FUNC) ( GameDll + 0x1F18D0 );
      MH_CreateHook(OrderId_org, &OrderId_my, reinterpret_cast<void**>(&OrderId_ptr));
      MH_EnableHook(OrderId_org);
}
void OrderId2String_init ( )
{
      OrderId2String_org = (OrderId2String_FUNC) ( GameDll + 0x1F18A0 );
      MH_CreateHook(OrderId2String_org, &OrderId2String_my, reinterpret_cast<void**>(&OrderId2String_ptr));
      MH_EnableHook(OrderId2String_org);
}
void PanCameraTo_init ( )
{
      PanCameraTo_org = (PanCameraTo_FUNC) ( GameDll + 0x1F1950 );
      MH_CreateHook(PanCameraTo_org, &PanCameraTo_my, reinterpret_cast<void**>(&PanCameraTo_ptr));
      MH_EnableHook(PanCameraTo_org);
}
void PanCameraToTimed_init ( )
{
      PanCameraToTimed_org = (PanCameraToTimed_FUNC) ( GameDll + 0x1F19A0 );
      MH_CreateHook(PanCameraToTimed_org, &PanCameraToTimed_my, reinterpret_cast<void**>(&PanCameraToTimed_ptr));
      MH_EnableHook(PanCameraToTimed_org);
}
void PanCameraToTimedWithZ_init ( )
{
      PanCameraToTimedWithZ_org = (PanCameraToTimedWithZ_FUNC) ( GameDll + 0x1F1A00 );
      MH_CreateHook(PanCameraToTimedWithZ_org, &PanCameraToTimedWithZ_my, reinterpret_cast<void**>(&PanCameraToTimedWithZ_ptr));
      MH_EnableHook(PanCameraToTimedWithZ_org);
}
void PanCameraToWithZ_init ( )
{
      PanCameraToWithZ_org = (PanCameraToWithZ_FUNC) ( GameDll + 0x1F1A60 );
      MH_CreateHook(PanCameraToWithZ_org, &PanCameraToWithZ_my, reinterpret_cast<void**>(&PanCameraToWithZ_ptr));
      MH_EnableHook(PanCameraToWithZ_org);
}
void PauseCompAI_init ( )
{
      PauseCompAI_org = (PauseCompAI_FUNC) ( GameDll + 0x1F1AB0 );
      MH_CreateHook(PauseCompAI_org, &PauseCompAI_my, reinterpret_cast<void**>(&PauseCompAI_ptr));
      MH_EnableHook(PauseCompAI_org);
}
void PauseGame_init ( )
{
      PauseGame_org = (PauseGame_FUNC) ( GameDll + 0x1F1AD0 );
      MH_CreateHook(PauseGame_org, &PauseGame_my, reinterpret_cast<void**>(&PauseGame_ptr));
      MH_EnableHook(PauseGame_org);
}
void PauseTimer_init ( )
{
      PauseTimer_org = (PauseTimer_FUNC) ( GameDll + 0x1F1B00 );
      MH_CreateHook(PauseTimer_org, &PauseTimer_my, reinterpret_cast<void**>(&PauseTimer_ptr));
      MH_EnableHook(PauseTimer_org);
}
void PauseUnit_init ( )
{
      PauseUnit_org = (PauseUnit_FUNC) ( GameDll + 0x1F1B20 );
      MH_CreateHook(PauseUnit_org, &PauseUnit_my, reinterpret_cast<void**>(&PauseUnit_ptr));
      MH_EnableHook(PauseUnit_org);
}
void PingMinimap_init ( )
{
      PingMinimap_org = (PingMinimap_FUNC) ( GameDll + 0x1F1BD0 );
      MH_CreateHook(PingMinimap_org, &PingMinimap_my, reinterpret_cast<void**>(&PingMinimap_ptr));
      MH_EnableHook(PingMinimap_org);
}
void PingMinimapEx_init ( )
{
      PingMinimapEx_org = (PingMinimapEx_FUNC) ( GameDll + 0x1F1C30 );
      MH_CreateHook(PingMinimapEx_org, &PingMinimapEx_my, reinterpret_cast<void**>(&PingMinimapEx_ptr));
      MH_EnableHook(PingMinimapEx_org);
}
void PlaceRandomItem_init ( )
{
      PlaceRandomItem_org = (PlaceRandomItem_FUNC) ( GameDll + 0x1F1CC0 );
      MH_CreateHook(PlaceRandomItem_org, &PlaceRandomItem_my, reinterpret_cast<void**>(&PlaceRandomItem_ptr));
      MH_EnableHook(PlaceRandomItem_org);
}
void PlaceRandomUnit_init ( )
{
      PlaceRandomUnit_org = (PlaceRandomUnit_FUNC) ( GameDll + 0x1F1D00 );
      MH_CreateHook(PlaceRandomUnit_org, &PlaceRandomUnit_my, reinterpret_cast<void**>(&PlaceRandomUnit_ptr));
      MH_EnableHook(PlaceRandomUnit_org);
}
void PlayCinematic_init ( )
{
      PlayCinematic_org = (PlayCinematic_FUNC) ( GameDll + 0x1F1D90 );
      MH_CreateHook(PlayCinematic_org, &PlayCinematic_my, reinterpret_cast<void**>(&PlayCinematic_ptr));
      MH_EnableHook(PlayCinematic_org);
}
void PlayModelCinematic_init ( )
{
      PlayModelCinematic_org = (PlayModelCinematic_FUNC) ( GameDll + 0x1F1DB0 );
      MH_CreateHook(PlayModelCinematic_org, &PlayModelCinematic_my, reinterpret_cast<void**>(&PlayModelCinematic_ptr));
      MH_EnableHook(PlayModelCinematic_org);
}
void PlayMusic_init ( )
{
      PlayMusic_org = (PlayMusic_FUNC) ( GameDll + 0x1F1DD0 );
      MH_CreateHook(PlayMusic_org, &PlayMusic_my, reinterpret_cast<void**>(&PlayMusic_ptr));
      MH_EnableHook(PlayMusic_org);
}
void PlayMusicEx_init ( )
{
      PlayMusicEx_org = (PlayMusicEx_FUNC) ( GameDll + 0x1F1E00 );
      MH_CreateHook(PlayMusicEx_org, &PlayMusicEx_my, reinterpret_cast<void**>(&PlayMusicEx_ptr));
      MH_EnableHook(PlayMusicEx_org);
}
void PlayThematicMusic_init ( )
{
      PlayThematicMusic_org = (PlayThematicMusic_FUNC) ( GameDll + 0x1F1E30 );
      MH_CreateHook(PlayThematicMusic_org, &PlayThematicMusic_my, reinterpret_cast<void**>(&PlayThematicMusic_ptr));
      MH_EnableHook(PlayThematicMusic_org);
}
void PlayThematicMusicEx_init ( )
{
      PlayThematicMusicEx_org = (PlayThematicMusicEx_FUNC) ( GameDll + 0x1F1E50 );
      MH_CreateHook(PlayThematicMusicEx_org, &PlayThematicMusicEx_my, reinterpret_cast<void**>(&PlayThematicMusicEx_ptr));
      MH_EnableHook(PlayThematicMusicEx_org);
}
void Player_init ( )
{
      Player_org = (Player_FUNC) ( GameDll + 0x1F1E70 );
      MH_CreateHook(Player_org, &Player_my, reinterpret_cast<void**>(&Player_ptr));
      MH_EnableHook(Player_org);
}
void PlayerGetLeaderboard_init ( )
{
      PlayerGetLeaderboard_org = (PlayerGetLeaderboard_FUNC) ( GameDll + 0x1F1EA0 );
      MH_CreateHook(PlayerGetLeaderboard_org, &PlayerGetLeaderboard_my, reinterpret_cast<void**>(&PlayerGetLeaderboard_ptr));
      MH_EnableHook(PlayerGetLeaderboard_org);
}
void PlayerSetLeaderboard_init ( )
{
      PlayerSetLeaderboard_org = (PlayerSetLeaderboard_FUNC) ( GameDll + 0x1F1F00 );
      MH_CreateHook(PlayerSetLeaderboard_org, &PlayerSetLeaderboard_my, reinterpret_cast<void**>(&PlayerSetLeaderboard_ptr));
      MH_EnableHook(PlayerSetLeaderboard_org);
}
void PopLastCommand_init ( )
{
      PopLastCommand_org = (PopLastCommand_FUNC) ( GameDll + 0x8928A0 );
      MH_CreateHook(PopLastCommand_org, &PopLastCommand_my, reinterpret_cast<void**>(&PopLastCommand_ptr));
      MH_EnableHook(PopLastCommand_org);
}
void Pow_init ( )
{
      Pow_org = (Pow_FUNC) ( GameDll + 0x1F1F70 );
      MH_CreateHook(Pow_org, &Pow_my, reinterpret_cast<void**>(&Pow_ptr));
      MH_EnableHook(Pow_org);
}
void Preload_init ( )
{
      Preload_org = (Preload_FUNC) ( GameDll + 0x1F2020 );
      MH_CreateHook(Preload_org, &Preload_my, reinterpret_cast<void**>(&Preload_ptr));
      MH_EnableHook(Preload_org);
}
void PreloadEnd_init ( )
{
      PreloadEnd_org = (PreloadEnd_FUNC) ( GameDll + 0x1F2050 );
      MH_CreateHook(PreloadEnd_org, &PreloadEnd_my, reinterpret_cast<void**>(&PreloadEnd_ptr));
      MH_EnableHook(PreloadEnd_org);
}
void PreloadEndEx_init ( )
{
      PreloadEndEx_org = (PreloadEndEx_FUNC) ( GameDll + 0x1F20A0 );
      MH_CreateHook(PreloadEndEx_org, &PreloadEndEx_my, reinterpret_cast<void**>(&PreloadEndEx_ptr));
      MH_EnableHook(PreloadEndEx_org);
}
void PreloadGenClear_init ( )
{
      PreloadGenClear_org = (PreloadGenClear_FUNC) ( GameDll + 0x1F20F0 );
      MH_CreateHook(PreloadGenClear_org, &PreloadGenClear_my, reinterpret_cast<void**>(&PreloadGenClear_ptr));
      MH_EnableHook(PreloadGenClear_org);
}
void PreloadGenEnd_init ( )
{
      PreloadGenEnd_org = (PreloadGenEnd_FUNC) ( GameDll + 0x1F2110 );
      MH_CreateHook(PreloadGenEnd_org, &PreloadGenEnd_my, reinterpret_cast<void**>(&PreloadGenEnd_ptr));
      MH_EnableHook(PreloadGenEnd_org);
}
void PreloadGenStart_init ( )
{
      PreloadGenStart_org = (PreloadGenStart_FUNC) ( GameDll + 0x1F2140 );
      MH_CreateHook(PreloadGenStart_org, &PreloadGenStart_my, reinterpret_cast<void**>(&PreloadGenStart_ptr));
      MH_EnableHook(PreloadGenStart_org);
}
void PreloadRefresh_init ( )
{
      PreloadRefresh_org = (PreloadRefresh_FUNC) ( GameDll + 0x1F2160 );
      MH_CreateHook(PreloadRefresh_org, &PreloadRefresh_my, reinterpret_cast<void**>(&PreloadRefresh_ptr));
      MH_EnableHook(PreloadRefresh_org);
}
void PreloadStart_init ( )
{
      PreloadStart_org = (PreloadStart_FUNC) ( GameDll + 0x1F2170 );
      MH_CreateHook(PreloadStart_org, &PreloadStart_my, reinterpret_cast<void**>(&PreloadStart_ptr));
      MH_EnableHook(PreloadStart_org);
}
void Preloader_init ( )
{
      Preloader_org = (Preloader_FUNC) ( GameDll + 0x1F2190 );
      MH_CreateHook(Preloader_org, &Preloader_my, reinterpret_cast<void**>(&Preloader_ptr));
      MH_EnableHook(Preloader_org);
}
void PurchaseZeppelin_init ( )
{
      PurchaseZeppelin_org = (PurchaseZeppelin_FUNC) ( GameDll + 0x892930 );
      MH_CreateHook(PurchaseZeppelin_org, &PurchaseZeppelin_my, reinterpret_cast<void**>(&PurchaseZeppelin_ptr));
      MH_EnableHook(PurchaseZeppelin_org);
}
void QuestCreateItem_init ( )
{
      QuestCreateItem_org = (QuestCreateItem_FUNC) ( GameDll + 0x1F2420 );
      MH_CreateHook(QuestCreateItem_org, &QuestCreateItem_my, reinterpret_cast<void**>(&QuestCreateItem_ptr));
      MH_EnableHook(QuestCreateItem_org);
}
void QuestItemSetCompleted_init ( )
{
      QuestItemSetCompleted_org = (QuestItemSetCompleted_FUNC) ( GameDll + 0x1F24D0 );
      MH_CreateHook(QuestItemSetCompleted_org, &QuestItemSetCompleted_my, reinterpret_cast<void**>(&QuestItemSetCompleted_ptr));
      MH_EnableHook(QuestItemSetCompleted_org);
}
void QuestItemSetDescription_init ( )
{
      QuestItemSetDescription_org = (QuestItemSetDescription_FUNC) ( GameDll + 0x1F2500 );
      MH_CreateHook(QuestItemSetDescription_org, &QuestItemSetDescription_my, reinterpret_cast<void**>(&QuestItemSetDescription_ptr));
      MH_EnableHook(QuestItemSetDescription_org);
}
void QuestSetCompleted_init ( )
{
      QuestSetCompleted_org = (QuestSetCompleted_FUNC) ( GameDll + 0x1F2550 );
      MH_CreateHook(QuestSetCompleted_org, &QuestSetCompleted_my, reinterpret_cast<void**>(&QuestSetCompleted_ptr));
      MH_EnableHook(QuestSetCompleted_org);
}
void QuestSetDescription_init ( )
{
      QuestSetDescription_org = (QuestSetDescription_FUNC) ( GameDll + 0x1F2580 );
      MH_CreateHook(QuestSetDescription_org, &QuestSetDescription_my, reinterpret_cast<void**>(&QuestSetDescription_ptr));
      MH_EnableHook(QuestSetDescription_org);
}
void QuestSetDiscovered_init ( )
{
      QuestSetDiscovered_org = (QuestSetDiscovered_FUNC) ( GameDll + 0x1F25B0 );
      MH_CreateHook(QuestSetDiscovered_org, &QuestSetDiscovered_my, reinterpret_cast<void**>(&QuestSetDiscovered_ptr));
      MH_EnableHook(QuestSetDiscovered_org);
}
void QuestSetEnabled_init ( )
{
      QuestSetEnabled_org = (QuestSetEnabled_FUNC) ( GameDll + 0x1F25E0 );
      MH_CreateHook(QuestSetEnabled_org, &QuestSetEnabled_my, reinterpret_cast<void**>(&QuestSetEnabled_ptr));
      MH_EnableHook(QuestSetEnabled_org);
}
void QuestSetFailed_init ( )
{
      QuestSetFailed_org = (QuestSetFailed_FUNC) ( GameDll + 0x1F2610 );
      MH_CreateHook(QuestSetFailed_org, &QuestSetFailed_my, reinterpret_cast<void**>(&QuestSetFailed_ptr));
      MH_EnableHook(QuestSetFailed_org);
}
void QuestSetIconPath_init ( )
{
      QuestSetIconPath_org = (QuestSetIconPath_FUNC) ( GameDll + 0x1F2640 );
      MH_CreateHook(QuestSetIconPath_org, &QuestSetIconPath_my, reinterpret_cast<void**>(&QuestSetIconPath_ptr));
      MH_EnableHook(QuestSetIconPath_org);
}
void QuestSetRequired_init ( )
{
      QuestSetRequired_org = (QuestSetRequired_FUNC) ( GameDll + 0x1F2670 );
      MH_CreateHook(QuestSetRequired_org, &QuestSetRequired_my, reinterpret_cast<void**>(&QuestSetRequired_ptr));
      MH_EnableHook(QuestSetRequired_org);
}
void QuestSetTitle_init ( )
{
      QuestSetTitle_org = (QuestSetTitle_FUNC) ( GameDll + 0x1F26A0 );
      MH_CreateHook(QuestSetTitle_org, &QuestSetTitle_my, reinterpret_cast<void**>(&QuestSetTitle_ptr));
      MH_EnableHook(QuestSetTitle_org);
}
void QueueDestructableAnimation_init ( )
{
      QueueDestructableAnimation_org = (QueueDestructableAnimation_FUNC) ( GameDll + 0x1F26D0 );
      MH_CreateHook(QueueDestructableAnimation_org, &QueueDestructableAnimation_my, reinterpret_cast<void**>(&QueueDestructableAnimation_ptr));
      MH_EnableHook(QueueDestructableAnimation_org);
}
void QueueUnitAnimation_init ( )
{
      QueueUnitAnimation_org = (QueueUnitAnimation_FUNC) ( GameDll + 0x1F26F0 );
      MH_CreateHook(QueueUnitAnimation_org, &QueueUnitAnimation_my, reinterpret_cast<void**>(&QueueUnitAnimation_ptr));
      MH_EnableHook(QueueUnitAnimation_org);
}
void R2I_init ( )
{
      R2I_org = (R2I_FUNC) ( GameDll + 0x1F2710 );
      MH_CreateHook(R2I_org, &R2I_my, reinterpret_cast<void**>(&R2I_ptr));
      MH_EnableHook(R2I_org);
}
void R2S_init ( )
{
      R2S_org = (R2S_FUNC) ( GameDll + 0x1F2720 );
      MH_CreateHook(R2S_org, &R2S_my, reinterpret_cast<void**>(&R2S_ptr));
      MH_EnableHook(R2S_org);
}
void R2SW_init ( )
{
      R2SW_org = (R2SW_FUNC) ( GameDll + 0x1F2760 );
      MH_CreateHook(R2SW_org, &R2SW_my, reinterpret_cast<void**>(&R2SW_ptr));
      MH_EnableHook(R2SW_org);
}
void Rad2Deg_init ( )
{
      Rad2Deg_org = (Rad2Deg_FUNC) ( GameDll + 0x1F27F0 );
      MH_CreateHook(Rad2Deg_org, &Rad2Deg_my, reinterpret_cast<void**>(&Rad2Deg_ptr));
      MH_EnableHook(Rad2Deg_org);
}
void Rect_init ( )
{
      Rect_org = (Rect_FUNC) ( GameDll + 0x1EF590 );
      MH_CreateHook(Rect_org, &Rect_my, reinterpret_cast<void**>(&Rect_ptr));
      MH_EnableHook(Rect_org);
}
void RectFromLoc_init ( )
{
      RectFromLoc_org = (RectFromLoc_FUNC) ( GameDll + 0x1F2820 );
      MH_CreateHook(RectFromLoc_org, &RectFromLoc_my, reinterpret_cast<void**>(&RectFromLoc_ptr));
      MH_EnableHook(RectFromLoc_org);
}
void RecycleGuardPosition_init ( )
{
      RecycleGuardPosition_org = (RecycleGuardPosition_FUNC) ( GameDll + 0x1F2980 );
      MH_CreateHook(RecycleGuardPosition_org, &RecycleGuardPosition_my, reinterpret_cast<void**>(&RecycleGuardPosition_ptr));
      MH_EnableHook(RecycleGuardPosition_org);
}
void RegionAddCell_init ( )
{
      RegionAddCell_org = (RegionAddCell_FUNC) ( GameDll + 0x1F29A0 );
      MH_CreateHook(RegionAddCell_org, &RegionAddCell_my, reinterpret_cast<void**>(&RegionAddCell_ptr));
      MH_EnableHook(RegionAddCell_org);
}
void RegionAddCellAtLoc_init ( )
{
      RegionAddCellAtLoc_org = (RegionAddCellAtLoc_FUNC) ( GameDll + 0x1F29C0 );
      MH_CreateHook(RegionAddCellAtLoc_org, &RegionAddCellAtLoc_my, reinterpret_cast<void**>(&RegionAddCellAtLoc_ptr));
      MH_EnableHook(RegionAddCellAtLoc_org);
}
void RegionAddRect_init ( )
{
      RegionAddRect_org = (RegionAddRect_FUNC) ( GameDll + 0x1F2A00 );
      MH_CreateHook(RegionAddRect_org, &RegionAddRect_my, reinterpret_cast<void**>(&RegionAddRect_ptr));
      MH_EnableHook(RegionAddRect_org);
}
void RegionClearCell_init ( )
{
      RegionClearCell_org = (RegionClearCell_FUNC) ( GameDll + 0x1F2A50 );
      MH_CreateHook(RegionClearCell_org, &RegionClearCell_my, reinterpret_cast<void**>(&RegionClearCell_ptr));
      MH_EnableHook(RegionClearCell_org);
}
void RegionClearCellAtLoc_init ( )
{
      RegionClearCellAtLoc_org = (RegionClearCellAtLoc_FUNC) ( GameDll + 0x1F2A70 );
      MH_CreateHook(RegionClearCellAtLoc_org, &RegionClearCellAtLoc_my, reinterpret_cast<void**>(&RegionClearCellAtLoc_ptr));
      MH_EnableHook(RegionClearCellAtLoc_org);
}
void RegionClearRect_init ( )
{
      RegionClearRect_org = (RegionClearRect_FUNC) ( GameDll + 0x1F2AB0 );
      MH_CreateHook(RegionClearRect_org, &RegionClearRect_my, reinterpret_cast<void**>(&RegionClearRect_ptr));
      MH_EnableHook(RegionClearRect_org);
}
void RegisterStackedSound_init ( )
{
      RegisterStackedSound_org = (RegisterStackedSound_FUNC) ( GameDll + 0x1F2BE0 );
      MH_CreateHook(RegisterStackedSound_org, &RegisterStackedSound_my, reinterpret_cast<void**>(&RegisterStackedSound_ptr));
      MH_EnableHook(RegisterStackedSound_org);
}
void ReloadGame_init ( )
{
      ReloadGame_org = (ReloadGame_FUNC) ( GameDll + 0x1F2C20 );
      MH_CreateHook(ReloadGame_org, &ReloadGame_my, reinterpret_cast<void**>(&ReloadGame_ptr));
      MH_EnableHook(ReloadGame_org);
}
void ReloadGameCachesFromDisk_init ( )
{
      ReloadGameCachesFromDisk_org = (ReloadGameCachesFromDisk_FUNC) ( GameDll + 0x1F2C40 );
      MH_CreateHook(ReloadGameCachesFromDisk_org, &ReloadGameCachesFromDisk_my, reinterpret_cast<void**>(&ReloadGameCachesFromDisk_ptr));
      MH_EnableHook(ReloadGameCachesFromDisk_org);
}
void RemoveAllGuardPositions_init ( )
{
      RemoveAllGuardPositions_org = (RemoveAllGuardPositions_FUNC) ( GameDll + 0x1F2C80 );
      MH_CreateHook(RemoveAllGuardPositions_org, &RemoveAllGuardPositions_my, reinterpret_cast<void**>(&RemoveAllGuardPositions_ptr));
      MH_EnableHook(RemoveAllGuardPositions_org);
}
void RemoveDestructable_init ( )
{
      RemoveDestructable_org = (RemoveDestructable_FUNC) ( GameDll + 0x1F2CC0 );
      MH_CreateHook(RemoveDestructable_org, &RemoveDestructable_my, reinterpret_cast<void**>(&RemoveDestructable_ptr));
      MH_EnableHook(RemoveDestructable_org);
}
void RemoveGuardPosition_init ( )
{
      RemoveGuardPosition_org = (RemoveGuardPosition_FUNC) ( GameDll + 0x1F2CE0 );
      MH_CreateHook(RemoveGuardPosition_org, &RemoveGuardPosition_my, reinterpret_cast<void**>(&RemoveGuardPosition_ptr));
      MH_EnableHook(RemoveGuardPosition_org);
}
void RemoveInjuries_init ( )
{
      RemoveInjuries_org = (RemoveInjuries_FUNC) ( GameDll + 0x893880 );
      MH_CreateHook(RemoveInjuries_org, &RemoveInjuries_my, reinterpret_cast<void**>(&RemoveInjuries_ptr));
      MH_EnableHook(RemoveInjuries_org);
}
void RemoveItem_init ( )
{
      RemoveItem_org = (RemoveItem_FUNC) ( GameDll + 0x1F2D00 );
      MH_CreateHook(RemoveItem_org, &RemoveItem_my, reinterpret_cast<void**>(&RemoveItem_ptr));
      MH_EnableHook(RemoveItem_org);
}
void RemoveItemFromAllStock_init ( )
{
      RemoveItemFromAllStock_org = (RemoveItemFromAllStock_FUNC) ( GameDll + 0x1F2D30 );
      MH_CreateHook(RemoveItemFromAllStock_org, &RemoveItemFromAllStock_my, reinterpret_cast<void**>(&RemoveItemFromAllStock_ptr));
      MH_EnableHook(RemoveItemFromAllStock_org);
}
void RemoveItemFromStock_init ( )
{
      RemoveItemFromStock_org = (RemoveItemFromStock_FUNC) ( GameDll + 0x1F2D40 );
      MH_CreateHook(RemoveItemFromStock_org, &RemoveItemFromStock_my, reinterpret_cast<void**>(&RemoveItemFromStock_ptr));
      MH_EnableHook(RemoveItemFromStock_org);
}
void RemoveLocation_init ( )
{
      RemoveLocation_org = (RemoveLocation_FUNC) ( GameDll + 0x1F2D80 );
      MH_CreateHook(RemoveLocation_org, &RemoveLocation_my, reinterpret_cast<void**>(&RemoveLocation_ptr));
      MH_EnableHook(RemoveLocation_org);
}
void RemovePlayer_init ( )
{
      RemovePlayer_org = (RemovePlayer_FUNC) ( GameDll + 0x1F2DB0 );
      MH_CreateHook(RemovePlayer_org, &RemovePlayer_my, reinterpret_cast<void**>(&RemovePlayer_ptr));
      MH_EnableHook(RemovePlayer_org);
}
void RemoveRect_init ( )
{
      RemoveRect_org = (RemoveRect_FUNC) ( GameDll + 0x1F2DD0 );
      MH_CreateHook(RemoveRect_org, &RemoveRect_my, reinterpret_cast<void**>(&RemoveRect_ptr));
      MH_EnableHook(RemoveRect_org);
}
void RemoveRegion_init ( )
{
      RemoveRegion_org = (RemoveRegion_FUNC) ( GameDll + 0x1F2DF0 );
      MH_CreateHook(RemoveRegion_org, &RemoveRegion_my, reinterpret_cast<void**>(&RemoveRegion_ptr));
      MH_EnableHook(RemoveRegion_org);
}
void RemoveSaveDirectory_init ( )
{
      RemoveSaveDirectory_org = (RemoveSaveDirectory_FUNC) ( GameDll + 0x1F2E10 );
      MH_CreateHook(RemoveSaveDirectory_org, &RemoveSaveDirectory_my, reinterpret_cast<void**>(&RemoveSaveDirectory_ptr));
      MH_EnableHook(RemoveSaveDirectory_org);
}
void RemoveSavedBoolean_init ( )
{
      RemoveSavedBoolean_org = (RemoveSavedBoolean_FUNC) ( GameDll + 0x1F2E90 );
      MH_CreateHook(RemoveSavedBoolean_org, &RemoveSavedBoolean_my, reinterpret_cast<void**>(&RemoveSavedBoolean_ptr));
      MH_EnableHook(RemoveSavedBoolean_org);
}
void RemoveSavedHandle_init ( )
{
      RemoveSavedHandle_org = (RemoveSavedHandle_FUNC) ( GameDll + 0x1F2EC0 );
      MH_CreateHook(RemoveSavedHandle_org, &RemoveSavedHandle_my, reinterpret_cast<void**>(&RemoveSavedHandle_ptr));
      MH_EnableHook(RemoveSavedHandle_org);
}
void RemoveSavedInteger_init ( )
{
      RemoveSavedInteger_org = (RemoveSavedInteger_FUNC) ( GameDll + 0x1F2EF0 );
      MH_CreateHook(RemoveSavedInteger_org, &RemoveSavedInteger_my, reinterpret_cast<void**>(&RemoveSavedInteger_ptr));
      MH_EnableHook(RemoveSavedInteger_org);
}
void RemoveSavedReal_init ( )
{
      RemoveSavedReal_org = (RemoveSavedReal_FUNC) ( GameDll + 0x1F2F20 );
      MH_CreateHook(RemoveSavedReal_org, &RemoveSavedReal_my, reinterpret_cast<void**>(&RemoveSavedReal_ptr));
      MH_EnableHook(RemoveSavedReal_org);
}
void RemoveSavedString_init ( )
{
      RemoveSavedString_org = (RemoveSavedString_FUNC) ( GameDll + 0x1F2F50 );
      MH_CreateHook(RemoveSavedString_org, &RemoveSavedString_my, reinterpret_cast<void**>(&RemoveSavedString_ptr));
      MH_EnableHook(RemoveSavedString_org);
}
void RemoveSiege_init ( )
{
      RemoveSiege_org = (RemoveSiege_FUNC) ( GameDll + 0x893960 );
      MH_CreateHook(RemoveSiege_org, &RemoveSiege_my, reinterpret_cast<void**>(&RemoveSiege_ptr));
      MH_EnableHook(RemoveSiege_org);
}
void RemoveUnit_init ( )
{
      RemoveUnit_org = (RemoveUnit_FUNC) ( GameDll + 0x1F2F80 );
      MH_CreateHook(RemoveUnit_org, &RemoveUnit_my, reinterpret_cast<void**>(&RemoveUnit_ptr));
      MH_EnableHook(RemoveUnit_org);
}
void RemoveUnitFromAllStock_init ( )
{
      RemoveUnitFromAllStock_org = (RemoveUnitFromAllStock_FUNC) ( GameDll + 0x1F2FB0 );
      MH_CreateHook(RemoveUnitFromAllStock_org, &RemoveUnitFromAllStock_my, reinterpret_cast<void**>(&RemoveUnitFromAllStock_ptr));
      MH_EnableHook(RemoveUnitFromAllStock_org);
}
void RemoveUnitFromStock_init ( )
{
      RemoveUnitFromStock_org = (RemoveUnitFromStock_FUNC) ( GameDll + 0x1F2FC0 );
      MH_CreateHook(RemoveUnitFromStock_org, &RemoveUnitFromStock_my, reinterpret_cast<void**>(&RemoveUnitFromStock_ptr));
      MH_EnableHook(RemoveUnitFromStock_org);
}
void RemoveWeatherEffect_init ( )
{
      RemoveWeatherEffect_org = (RemoveWeatherEffect_FUNC) ( GameDll + 0x1F3000 );
      MH_CreateHook(RemoveWeatherEffect_org, &RemoveWeatherEffect_my, reinterpret_cast<void**>(&RemoveWeatherEffect_ptr));
      MH_EnableHook(RemoveWeatherEffect_org);
}
void RenameSaveDirectory_init ( )
{
      RenameSaveDirectory_org = (RenameSaveDirectory_FUNC) ( GameDll + 0x1F3010 );
      MH_CreateHook(RenameSaveDirectory_org, &RenameSaveDirectory_my, reinterpret_cast<void**>(&RenameSaveDirectory_ptr));
      MH_EnableHook(RenameSaveDirectory_org);
}
void ResetCaptainLocs_init ( )
{
      ResetCaptainLocs_org = (ResetCaptainLocs_FUNC) ( GameDll + 0x893D60 );
      MH_CreateHook(ResetCaptainLocs_org, &ResetCaptainLocs_my, reinterpret_cast<void**>(&ResetCaptainLocs_ptr));
      MH_EnableHook(ResetCaptainLocs_org);
}
void ResetTerrainFog_init ( )
{
      ResetTerrainFog_org = (ResetTerrainFog_FUNC) ( GameDll + 0x1F30F0 );
      MH_CreateHook(ResetTerrainFog_org, &ResetTerrainFog_my, reinterpret_cast<void**>(&ResetTerrainFog_ptr));
      MH_EnableHook(ResetTerrainFog_org);
}
void ResetToGameCamera_init ( )
{
      ResetToGameCamera_org = (ResetToGameCamera_FUNC) ( GameDll + 0x1F3110 );
      MH_CreateHook(ResetToGameCamera_org, &ResetToGameCamera_my, reinterpret_cast<void**>(&ResetToGameCamera_ptr));
      MH_EnableHook(ResetToGameCamera_org);
}
void ResetTrigger_init ( )
{
      ResetTrigger_org = (ResetTrigger_FUNC) ( GameDll + 0x1F3140 );
      MH_CreateHook(ResetTrigger_org, &ResetTrigger_my, reinterpret_cast<void**>(&ResetTrigger_ptr));
      MH_EnableHook(ResetTrigger_org);
}
void ResetUbersplat_init ( )
{
      ResetUbersplat_org = (ResetUbersplat_FUNC) ( GameDll + 0x1F3160 );
      MH_CreateHook(ResetUbersplat_org, &ResetUbersplat_my, reinterpret_cast<void**>(&ResetUbersplat_ptr));
      MH_EnableHook(ResetUbersplat_org);
}
void ResetUnitLookAt_init ( )
{
      ResetUnitLookAt_org = (ResetUnitLookAt_FUNC) ( GameDll + 0x1F3180 );
      MH_CreateHook(ResetUnitLookAt_org, &ResetUnitLookAt_my, reinterpret_cast<void**>(&ResetUnitLookAt_ptr));
      MH_EnableHook(ResetUnitLookAt_org);
}
void RestartGame_init ( )
{
      RestartGame_org = (RestartGame_FUNC) ( GameDll + 0x1F31E0 );
      MH_CreateHook(RestartGame_org, &RestartGame_my, reinterpret_cast<void**>(&RestartGame_ptr));
      MH_EnableHook(RestartGame_org);
}
void RestoreUnit_init ( )
{
      RestoreUnit_org = (RestoreUnit_FUNC) ( GameDll + 0x1F3210 );
      MH_CreateHook(RestoreUnit_org, &RestoreUnit_my, reinterpret_cast<void**>(&RestoreUnit_ptr));
      MH_EnableHook(RestoreUnit_org);
}
void ResumeMusic_init ( )
{
      ResumeMusic_org = (ResumeMusic_FUNC) ( GameDll + 0x1F32D0 );
      MH_CreateHook(ResumeMusic_org, &ResumeMusic_my, reinterpret_cast<void**>(&ResumeMusic_ptr));
      MH_EnableHook(ResumeMusic_org);
}
void ResumeTimer_init ( )
{
      ResumeTimer_org = (ResumeTimer_FUNC) ( GameDll + 0x1F32E0 );
      MH_CreateHook(ResumeTimer_org, &ResumeTimer_my, reinterpret_cast<void**>(&ResumeTimer_ptr));
      MH_EnableHook(ResumeTimer_org);
}
void ReturnGuardPosts_init ( )
{
      ReturnGuardPosts_org = (ReturnGuardPosts_FUNC) ( GameDll + 0x893DA0 );
      MH_CreateHook(ReturnGuardPosts_org, &ReturnGuardPosts_my, reinterpret_cast<void**>(&ReturnGuardPosts_ptr));
      MH_EnableHook(ReturnGuardPosts_org);
}
void ReviveHero_init ( )
{
      ReviveHero_org = (ReviveHero_FUNC) ( GameDll + 0x1F3300 );
      MH_CreateHook(ReviveHero_org, &ReviveHero_my, reinterpret_cast<void**>(&ReviveHero_ptr));
      MH_EnableHook(ReviveHero_org);
}
void ReviveHeroLoc_init ( )
{
      ReviveHeroLoc_org = (ReviveHeroLoc_FUNC) ( GameDll + 0x1F3380 );
      MH_CreateHook(ReviveHeroLoc_org, &ReviveHeroLoc_my, reinterpret_cast<void**>(&ReviveHeroLoc_ptr));
      MH_EnableHook(ReviveHeroLoc_org);
}
void S2I_init ( )
{
      S2I_org = (S2I_FUNC) ( GameDll + 0x1F33C0 );
      MH_CreateHook(S2I_org, &S2I_my, reinterpret_cast<void**>(&S2I_ptr));
      MH_EnableHook(S2I_org);
}
void S2R_init ( )
{
      S2R_org = (S2R_FUNC) ( GameDll + 0x1F33F0 );
      MH_CreateHook(S2R_org, &S2R_my, reinterpret_cast<void**>(&S2R_ptr));
      MH_EnableHook(S2R_org);
}
void SaveAbilityHandle_init ( )
{
      SaveAbilityHandle_org = (SaveAbilityHandle_FUNC) ( GameDll + 0x1F3530 );
      MH_CreateHook(SaveAbilityHandle_org, &SaveAbilityHandle_my, reinterpret_cast<void**>(&SaveAbilityHandle_ptr));
      MH_EnableHook(SaveAbilityHandle_org);
}
void SaveAgentHandle_init ( )
{
      SaveAgentHandle_org = (SaveAgentHandle_FUNC) ( GameDll + 0x1F3550 );
      MH_CreateHook(SaveAgentHandle_org, &SaveAgentHandle_my, reinterpret_cast<void**>(&SaveAgentHandle_ptr));
      MH_EnableHook(SaveAgentHandle_org);
}
void SaveBoolean_init ( )
{
      SaveBoolean_org = (SaveBoolean_FUNC) ( GameDll + 0x1F3570 );
      MH_CreateHook(SaveBoolean_org, &SaveBoolean_my, reinterpret_cast<void**>(&SaveBoolean_ptr));
      MH_EnableHook(SaveBoolean_org);
}
void SaveBooleanExprHandle_init ( )
{
      SaveBooleanExprHandle_org = (SaveBooleanExprHandle_FUNC) ( GameDll + 0x1F35B0 );
      MH_CreateHook(SaveBooleanExprHandle_org, &SaveBooleanExprHandle_my, reinterpret_cast<void**>(&SaveBooleanExprHandle_ptr));
      MH_EnableHook(SaveBooleanExprHandle_org);
}
void SaveButtonHandle_init ( )
{
      SaveButtonHandle_org = (SaveButtonHandle_FUNC) ( GameDll + 0x1F35D0 );
      MH_CreateHook(SaveButtonHandle_org, &SaveButtonHandle_my, reinterpret_cast<void**>(&SaveButtonHandle_ptr));
      MH_EnableHook(SaveButtonHandle_org);
}
void SaveDefeatConditionHandle_init ( )
{
      SaveDefeatConditionHandle_org = (SaveDefeatConditionHandle_FUNC) ( GameDll + 0x1F35F0 );
      MH_CreateHook(SaveDefeatConditionHandle_org, &SaveDefeatConditionHandle_my, reinterpret_cast<void**>(&SaveDefeatConditionHandle_ptr));
      MH_EnableHook(SaveDefeatConditionHandle_org);
}
void SaveDestructableHandle_init ( )
{
      SaveDestructableHandle_org = (SaveDestructableHandle_FUNC) ( GameDll + 0x1F3610 );
      MH_CreateHook(SaveDestructableHandle_org, &SaveDestructableHandle_my, reinterpret_cast<void**>(&SaveDestructableHandle_ptr));
      MH_EnableHook(SaveDestructableHandle_org);
}
void SaveDialogHandle_init ( )
{
      SaveDialogHandle_org = (SaveDialogHandle_FUNC) ( GameDll + 0x1F3630 );
      MH_CreateHook(SaveDialogHandle_org, &SaveDialogHandle_my, reinterpret_cast<void**>(&SaveDialogHandle_ptr));
      MH_EnableHook(SaveDialogHandle_org);
}
void SaveEffectHandle_init ( )
{
      SaveEffectHandle_org = (SaveEffectHandle_FUNC) ( GameDll + 0x1F3650 );
      MH_CreateHook(SaveEffectHandle_org, &SaveEffectHandle_my, reinterpret_cast<void**>(&SaveEffectHandle_ptr));
      MH_EnableHook(SaveEffectHandle_org);
}
void SaveFogModifierHandle_init ( )
{
      SaveFogModifierHandle_org = (SaveFogModifierHandle_FUNC) ( GameDll + 0x1F3670 );
      MH_CreateHook(SaveFogModifierHandle_org, &SaveFogModifierHandle_my, reinterpret_cast<void**>(&SaveFogModifierHandle_ptr));
      MH_EnableHook(SaveFogModifierHandle_org);
}
void SaveFogStateHandle_init ( )
{
      SaveFogStateHandle_org = (SaveFogStateHandle_FUNC) ( GameDll + 0x1F3690 );
      MH_CreateHook(SaveFogStateHandle_org, &SaveFogStateHandle_my, reinterpret_cast<void**>(&SaveFogStateHandle_ptr));
      MH_EnableHook(SaveFogStateHandle_org);
}
void SaveForceHandle_init ( )
{
      SaveForceHandle_org = (SaveForceHandle_FUNC) ( GameDll + 0x1F36B0 );
      MH_CreateHook(SaveForceHandle_org, &SaveForceHandle_my, reinterpret_cast<void**>(&SaveForceHandle_ptr));
      MH_EnableHook(SaveForceHandle_org);
}
void SaveGame_init ( )
{
      SaveGame_org = (SaveGame_FUNC) ( GameDll + 0x1F36D0 );
      MH_CreateHook(SaveGame_org, &SaveGame_my, reinterpret_cast<void**>(&SaveGame_ptr));
      MH_EnableHook(SaveGame_org);
}
void SaveGameCache_init ( )
{
      SaveGameCache_org = (SaveGameCache_FUNC) ( GameDll + 0x1F3790 );
      MH_CreateHook(SaveGameCache_org, &SaveGameCache_my, reinterpret_cast<void**>(&SaveGameCache_ptr));
      MH_EnableHook(SaveGameCache_org);
}
void SaveGameExists_init ( )
{
      SaveGameExists_org = (SaveGameExists_FUNC) ( GameDll + 0x1F37C0 );
      MH_CreateHook(SaveGameExists_org, &SaveGameExists_my, reinterpret_cast<void**>(&SaveGameExists_ptr));
      MH_EnableHook(SaveGameExists_org);
}
void SaveGroupHandle_init ( )
{
      SaveGroupHandle_org = (SaveGroupHandle_FUNC) ( GameDll + 0x1F3830 );
      MH_CreateHook(SaveGroupHandle_org, &SaveGroupHandle_my, reinterpret_cast<void**>(&SaveGroupHandle_ptr));
      MH_EnableHook(SaveGroupHandle_org);
}
void SaveHashtableHandle_init ( )
{
      SaveHashtableHandle_org = (SaveHashtableHandle_FUNC) ( GameDll + 0x1F3850 );
      MH_CreateHook(SaveHashtableHandle_org, &SaveHashtableHandle_my, reinterpret_cast<void**>(&SaveHashtableHandle_ptr));
      MH_EnableHook(SaveHashtableHandle_org);
}
void SaveImageHandle_init ( )
{
      SaveImageHandle_org = (SaveImageHandle_FUNC) ( GameDll + 0x1F3870 );
      MH_CreateHook(SaveImageHandle_org, &SaveImageHandle_my, reinterpret_cast<void**>(&SaveImageHandle_ptr));
      MH_EnableHook(SaveImageHandle_org);
}
void SaveInteger_init ( )
{
      SaveInteger_org = (SaveInteger_FUNC) ( GameDll + 0x1F3890 );
      MH_CreateHook(SaveInteger_org, &SaveInteger_my, reinterpret_cast<void**>(&SaveInteger_ptr));
      MH_EnableHook(SaveInteger_org);
}
void SaveItemHandle_init ( )
{
      SaveItemHandle_org = (SaveItemHandle_FUNC) ( GameDll + 0x1F38D0 );
      MH_CreateHook(SaveItemHandle_org, &SaveItemHandle_my, reinterpret_cast<void**>(&SaveItemHandle_ptr));
      MH_EnableHook(SaveItemHandle_org);
}
void SaveItemPoolHandle_init ( )
{
      SaveItemPoolHandle_org = (SaveItemPoolHandle_FUNC) ( GameDll + 0x1F38F0 );
      MH_CreateHook(SaveItemPoolHandle_org, &SaveItemPoolHandle_my, reinterpret_cast<void**>(&SaveItemPoolHandle_ptr));
      MH_EnableHook(SaveItemPoolHandle_org);
}
void SaveLeaderboardHandle_init ( )
{
      SaveLeaderboardHandle_org = (SaveLeaderboardHandle_FUNC) ( GameDll + 0x1F3910 );
      MH_CreateHook(SaveLeaderboardHandle_org, &SaveLeaderboardHandle_my, reinterpret_cast<void**>(&SaveLeaderboardHandle_ptr));
      MH_EnableHook(SaveLeaderboardHandle_org);
}
void SaveLightningHandle_init ( )
{
      SaveLightningHandle_org = (SaveLightningHandle_FUNC) ( GameDll + 0x1F3930 );
      MH_CreateHook(SaveLightningHandle_org, &SaveLightningHandle_my, reinterpret_cast<void**>(&SaveLightningHandle_ptr));
      MH_EnableHook(SaveLightningHandle_org);
}
void SaveLocationHandle_init ( )
{
      SaveLocationHandle_org = (SaveLocationHandle_FUNC) ( GameDll + 0x1F3950 );
      MH_CreateHook(SaveLocationHandle_org, &SaveLocationHandle_my, reinterpret_cast<void**>(&SaveLocationHandle_ptr));
      MH_EnableHook(SaveLocationHandle_org);
}
void SaveMultiboardHandle_init ( )
{
      SaveMultiboardHandle_org = (SaveMultiboardHandle_FUNC) ( GameDll + 0x1F3970 );
      MH_CreateHook(SaveMultiboardHandle_org, &SaveMultiboardHandle_my, reinterpret_cast<void**>(&SaveMultiboardHandle_ptr));
      MH_EnableHook(SaveMultiboardHandle_org);
}
void SaveMultiboardItemHandle_init ( )
{
      SaveMultiboardItemHandle_org = (SaveMultiboardItemHandle_FUNC) ( GameDll + 0x1F3990 );
      MH_CreateHook(SaveMultiboardItemHandle_org, &SaveMultiboardItemHandle_my, reinterpret_cast<void**>(&SaveMultiboardItemHandle_ptr));
      MH_EnableHook(SaveMultiboardItemHandle_org);
}
void SavePlayerHandle_init ( )
{
      SavePlayerHandle_org = (SavePlayerHandle_FUNC) ( GameDll + 0x1F39B0 );
      MH_CreateHook(SavePlayerHandle_org, &SavePlayerHandle_my, reinterpret_cast<void**>(&SavePlayerHandle_ptr));
      MH_EnableHook(SavePlayerHandle_org);
}
void SaveQuestHandle_init ( )
{
      SaveQuestHandle_org = (SaveQuestHandle_FUNC) ( GameDll + 0x1F39D0 );
      MH_CreateHook(SaveQuestHandle_org, &SaveQuestHandle_my, reinterpret_cast<void**>(&SaveQuestHandle_ptr));
      MH_EnableHook(SaveQuestHandle_org);
}
void SaveQuestItemHandle_init ( )
{
      SaveQuestItemHandle_org = (SaveQuestItemHandle_FUNC) ( GameDll + 0x1F39F0 );
      MH_CreateHook(SaveQuestItemHandle_org, &SaveQuestItemHandle_my, reinterpret_cast<void**>(&SaveQuestItemHandle_ptr));
      MH_EnableHook(SaveQuestItemHandle_org);
}
void SaveReal_init ( )
{
      SaveReal_org = (SaveReal_FUNC) ( GameDll + 0x1F3A10 );
      MH_CreateHook(SaveReal_org, &SaveReal_my, reinterpret_cast<void**>(&SaveReal_ptr));
      MH_EnableHook(SaveReal_org);
}
void SaveRectHandle_init ( )
{
      SaveRectHandle_org = (SaveRectHandle_FUNC) ( GameDll + 0x1F3A50 );
      MH_CreateHook(SaveRectHandle_org, &SaveRectHandle_my, reinterpret_cast<void**>(&SaveRectHandle_ptr));
      MH_EnableHook(SaveRectHandle_org);
}
void SaveRegionHandle_init ( )
{
      SaveRegionHandle_org = (SaveRegionHandle_FUNC) ( GameDll + 0x1F3A70 );
      MH_CreateHook(SaveRegionHandle_org, &SaveRegionHandle_my, reinterpret_cast<void**>(&SaveRegionHandle_ptr));
      MH_EnableHook(SaveRegionHandle_org);
}
void SaveSoundHandle_init ( )
{
      SaveSoundHandle_org = (SaveSoundHandle_FUNC) ( GameDll + 0x1F3AD0 );
      MH_CreateHook(SaveSoundHandle_org, &SaveSoundHandle_my, reinterpret_cast<void**>(&SaveSoundHandle_ptr));
      MH_EnableHook(SaveSoundHandle_org);
}
void SaveStr_init ( )
{
      SaveStr_org = (SaveStr_FUNC) ( GameDll + 0x1F3AF0 );
      MH_CreateHook(SaveStr_org, &SaveStr_my, reinterpret_cast<void**>(&SaveStr_ptr));
      MH_EnableHook(SaveStr_org);
}
void SaveTextTagHandle_init ( )
{
      SaveTextTagHandle_org = (SaveTextTagHandle_FUNC) ( GameDll + 0x1F3B30 );
      MH_CreateHook(SaveTextTagHandle_org, &SaveTextTagHandle_my, reinterpret_cast<void**>(&SaveTextTagHandle_ptr));
      MH_EnableHook(SaveTextTagHandle_org);
}
void SaveTimerDialogHandle_init ( )
{
      SaveTimerDialogHandle_org = (SaveTimerDialogHandle_FUNC) ( GameDll + 0x1F3B50 );
      MH_CreateHook(SaveTimerDialogHandle_org, &SaveTimerDialogHandle_my, reinterpret_cast<void**>(&SaveTimerDialogHandle_ptr));
      MH_EnableHook(SaveTimerDialogHandle_org);
}
void SaveTimerHandle_init ( )
{
      SaveTimerHandle_org = (SaveTimerHandle_FUNC) ( GameDll + 0x1F3B70 );
      MH_CreateHook(SaveTimerHandle_org, &SaveTimerHandle_my, reinterpret_cast<void**>(&SaveTimerHandle_ptr));
      MH_EnableHook(SaveTimerHandle_org);
}
void SaveTrackableHandle_init ( )
{
      SaveTrackableHandle_org = (SaveTrackableHandle_FUNC) ( GameDll + 0x1F3B90 );
      MH_CreateHook(SaveTrackableHandle_org, &SaveTrackableHandle_my, reinterpret_cast<void**>(&SaveTrackableHandle_ptr));
      MH_EnableHook(SaveTrackableHandle_org);
}
void SaveTriggerActionHandle_init ( )
{
      SaveTriggerActionHandle_org = (SaveTriggerActionHandle_FUNC) ( GameDll + 0x1F3BB0 );
      MH_CreateHook(SaveTriggerActionHandle_org, &SaveTriggerActionHandle_my, reinterpret_cast<void**>(&SaveTriggerActionHandle_ptr));
      MH_EnableHook(SaveTriggerActionHandle_org);
}
void SaveTriggerConditionHandle_init ( )
{
      SaveTriggerConditionHandle_org = (SaveTriggerConditionHandle_FUNC) ( GameDll + 0x1F3BD0 );
      MH_CreateHook(SaveTriggerConditionHandle_org, &SaveTriggerConditionHandle_my, reinterpret_cast<void**>(&SaveTriggerConditionHandle_ptr));
      MH_EnableHook(SaveTriggerConditionHandle_org);
}
void SaveTriggerEventHandle_init ( )
{
      SaveTriggerEventHandle_org = (SaveTriggerEventHandle_FUNC) ( GameDll + 0x1F3BF0 );
      MH_CreateHook(SaveTriggerEventHandle_org, &SaveTriggerEventHandle_my, reinterpret_cast<void**>(&SaveTriggerEventHandle_ptr));
      MH_EnableHook(SaveTriggerEventHandle_org);
}
void SaveTriggerHandle_init ( )
{
      SaveTriggerHandle_org = (SaveTriggerHandle_FUNC) ( GameDll + 0x1F3C10 );
      MH_CreateHook(SaveTriggerHandle_org, &SaveTriggerHandle_my, reinterpret_cast<void**>(&SaveTriggerHandle_ptr));
      MH_EnableHook(SaveTriggerHandle_org);
}
void SaveUbersplatHandle_init ( )
{
      SaveUbersplatHandle_org = (SaveUbersplatHandle_FUNC) ( GameDll + 0x1F3C30 );
      MH_CreateHook(SaveUbersplatHandle_org, &SaveUbersplatHandle_my, reinterpret_cast<void**>(&SaveUbersplatHandle_ptr));
      MH_EnableHook(SaveUbersplatHandle_org);
}
void SaveUnitHandle_init ( )
{
      SaveUnitHandle_org = (SaveUnitHandle_FUNC) ( GameDll + 0x1F3C50 );
      MH_CreateHook(SaveUnitHandle_org, &SaveUnitHandle_my, reinterpret_cast<void**>(&SaveUnitHandle_ptr));
      MH_EnableHook(SaveUnitHandle_org);
}
void SaveUnitPoolHandle_init ( )
{
      SaveUnitPoolHandle_org = (SaveUnitPoolHandle_FUNC) ( GameDll + 0x1F3C70 );
      MH_CreateHook(SaveUnitPoolHandle_org, &SaveUnitPoolHandle_my, reinterpret_cast<void**>(&SaveUnitPoolHandle_ptr));
      MH_EnableHook(SaveUnitPoolHandle_org);
}
void SaveWidgetHandle_init ( )
{
      SaveWidgetHandle_org = (SaveWidgetHandle_FUNC) ( GameDll + 0x1F3C90 );
      MH_CreateHook(SaveWidgetHandle_org, &SaveWidgetHandle_my, reinterpret_cast<void**>(&SaveWidgetHandle_ptr));
      MH_EnableHook(SaveWidgetHandle_org);
}
void SelectHeroSkill_init ( )
{
      SelectHeroSkill_org = (SelectHeroSkill_FUNC) ( GameDll + 0x1F3CB0 );
      MH_CreateHook(SelectHeroSkill_org, &SelectHeroSkill_my, reinterpret_cast<void**>(&SelectHeroSkill_ptr));
      MH_EnableHook(SelectHeroSkill_org);
}
void SelectUnit_init ( )
{
      SelectUnit_org = (SelectUnit_FUNC) ( GameDll + 0x1F3D10 );
      MH_CreateHook(SelectUnit_org, &SelectUnit_my, reinterpret_cast<void**>(&SelectUnit_ptr));
      MH_EnableHook(SelectUnit_org);
}
void SetAllItemTypeSlots_init ( )
{
      SetAllItemTypeSlots_org = (SetAllItemTypeSlots_FUNC) ( GameDll + 0x1F3E60 );
      MH_CreateHook(SetAllItemTypeSlots_org, &SetAllItemTypeSlots_my, reinterpret_cast<void**>(&SetAllItemTypeSlots_ptr));
      MH_EnableHook(SetAllItemTypeSlots_org);
}
void SetAllUnitTypeSlots_init ( )
{
      SetAllUnitTypeSlots_org = (SetAllUnitTypeSlots_FUNC) ( GameDll + 0x1F3E70 );
      MH_CreateHook(SetAllUnitTypeSlots_org, &SetAllUnitTypeSlots_my, reinterpret_cast<void**>(&SetAllUnitTypeSlots_ptr));
      MH_EnableHook(SetAllUnitTypeSlots_org);
}
void SetAllianceTarget_init ( )
{
      SetAllianceTarget_org = (SetAllianceTarget_FUNC) ( GameDll + 0x894140 );
      MH_CreateHook(SetAllianceTarget_org, &SetAllianceTarget_my, reinterpret_cast<void**>(&SetAllianceTarget_ptr));
      MH_EnableHook(SetAllianceTarget_org);
}
void SetAllyColorFilterState_init ( )
{
      SetAllyColorFilterState_org = (SetAllyColorFilterState_FUNC) ( GameDll + 0x1F3E80 );
      MH_CreateHook(SetAllyColorFilterState_org, &SetAllyColorFilterState_my, reinterpret_cast<void**>(&SetAllyColorFilterState_ptr));
      MH_EnableHook(SetAllyColorFilterState_org);
}
void SetAltMinimapIcon_init ( )
{
      SetAltMinimapIcon_org = (SetAltMinimapIcon_FUNC) ( GameDll + 0x1F3EB0 );
      MH_CreateHook(SetAltMinimapIcon_org, &SetAltMinimapIcon_my, reinterpret_cast<void**>(&SetAltMinimapIcon_ptr));
      MH_EnableHook(SetAltMinimapIcon_org);
}
void SetAmphibious_init ( )
{
      SetAmphibious_org = (SetAmphibious_FUNC) ( GameDll + 0x894200 );
      MH_CreateHook(SetAmphibious_org, &SetAmphibious_my, reinterpret_cast<void**>(&SetAmphibious_ptr));
      MH_EnableHook(SetAmphibious_org);
}
void SetBlight_init ( )
{
      SetBlight_org = (SetBlight_FUNC) ( GameDll + 0x1F3F20 );
      MH_CreateHook(SetBlight_org, &SetBlight_my, reinterpret_cast<void**>(&SetBlight_ptr));
      MH_EnableHook(SetBlight_org);
}
void SetBlightLoc_init ( )
{
      SetBlightLoc_org = (SetBlightLoc_FUNC) ( GameDll + 0x1F3F80 );
      MH_CreateHook(SetBlightLoc_org, &SetBlightLoc_my, reinterpret_cast<void**>(&SetBlightLoc_ptr));
      MH_EnableHook(SetBlightLoc_org);
}
void SetBlightPoint_init ( )
{
      SetBlightPoint_org = (SetBlightPoint_FUNC) ( GameDll + 0x1F3FE0 );
      MH_CreateHook(SetBlightPoint_org, &SetBlightPoint_my, reinterpret_cast<void**>(&SetBlightPoint_ptr));
      MH_EnableHook(SetBlightPoint_org);
}
void SetBlightRect_init ( )
{
      SetBlightRect_org = (SetBlightRect_FUNC) ( GameDll + 0x1F4030 );
      MH_CreateHook(SetBlightRect_org, &SetBlightRect_my, reinterpret_cast<void**>(&SetBlightRect_ptr));
      MH_EnableHook(SetBlightRect_org);
}
void SetCameraBounds_init ( )
{
      SetCameraBounds_org = (SetCameraBounds_FUNC) ( GameDll + 0x1F4090 );
      MH_CreateHook(SetCameraBounds_org, &SetCameraBounds_my, reinterpret_cast<void**>(&SetCameraBounds_ptr));
      MH_EnableHook(SetCameraBounds_org);
}
void SetCameraField_init ( )
{
      SetCameraField_org = (SetCameraField_FUNC) ( GameDll + 0x1F4170 );
      MH_CreateHook(SetCameraField_org, &SetCameraField_my, reinterpret_cast<void**>(&SetCameraField_ptr));
      MH_EnableHook(SetCameraField_org);
}
void SetCameraOrientController_init ( )
{
      SetCameraOrientController_org = (SetCameraOrientController_FUNC) ( GameDll + 0x1F41B0 );
      MH_CreateHook(SetCameraOrientController_org, &SetCameraOrientController_my, reinterpret_cast<void**>(&SetCameraOrientController_ptr));
      MH_EnableHook(SetCameraOrientController_org);
}
void SetCameraPosition_init ( )
{
      SetCameraPosition_org = (SetCameraPosition_FUNC) ( GameDll + 0x1F4200 );
      MH_CreateHook(SetCameraPosition_org, &SetCameraPosition_my, reinterpret_cast<void**>(&SetCameraPosition_ptr));
      MH_EnableHook(SetCameraPosition_org);
}
void SetCameraQuickPosition_init ( )
{
      SetCameraQuickPosition_org = (SetCameraQuickPosition_FUNC) ( GameDll + 0x1F4250 );
      MH_CreateHook(SetCameraQuickPosition_org, &SetCameraQuickPosition_my, reinterpret_cast<void**>(&SetCameraQuickPosition_ptr));
      MH_EnableHook(SetCameraQuickPosition_org);
}
void SetCameraRotateMode_init ( )
{
      SetCameraRotateMode_org = (SetCameraRotateMode_FUNC) ( GameDll + 0x1F4290 );
      MH_CreateHook(SetCameraRotateMode_org, &SetCameraRotateMode_my, reinterpret_cast<void**>(&SetCameraRotateMode_ptr));
      MH_EnableHook(SetCameraRotateMode_org);
}
void SetCameraTargetController_init ( )
{
      SetCameraTargetController_org = (SetCameraTargetController_FUNC) ( GameDll + 0x1F42F0 );
      MH_CreateHook(SetCameraTargetController_org, &SetCameraTargetController_my, reinterpret_cast<void**>(&SetCameraTargetController_ptr));
      MH_EnableHook(SetCameraTargetController_org);
}
void SetCampaignAI_init ( )
{
      SetCampaignAI_org = (SetCampaignAI_FUNC) ( GameDll + 0x894260 );
      MH_CreateHook(SetCampaignAI_org, &SetCampaignAI_my, reinterpret_cast<void**>(&SetCampaignAI_ptr));
      MH_EnableHook(SetCampaignAI_org);
}
void SetCampaignAvailable_init ( )
{
      SetCampaignAvailable_org = (SetCampaignAvailable_FUNC) ( GameDll + 0x1F4350 );
      MH_CreateHook(SetCampaignAvailable_org, &SetCampaignAvailable_my, reinterpret_cast<void**>(&SetCampaignAvailable_ptr));
      MH_EnableHook(SetCampaignAvailable_org);
}
void SetCampaignMenuRace_init ( )
{
      SetCampaignMenuRace_org = (SetCampaignMenuRace_FUNC) ( GameDll + 0x1F4380 );
      MH_CreateHook(SetCampaignMenuRace_org, &SetCampaignMenuRace_my, reinterpret_cast<void**>(&SetCampaignMenuRace_ptr));
      MH_EnableHook(SetCampaignMenuRace_org);
}
void SetCampaignMenuRaceEx_init ( )
{
      SetCampaignMenuRaceEx_org = (SetCampaignMenuRaceEx_FUNC) ( GameDll + 0x1F43B0 );
      MH_CreateHook(SetCampaignMenuRaceEx_org, &SetCampaignMenuRaceEx_my, reinterpret_cast<void**>(&SetCampaignMenuRaceEx_ptr));
      MH_EnableHook(SetCampaignMenuRaceEx_org);
}
void SetCaptainChanges_init ( )
{
      SetCaptainChanges_org = (SetCaptainChanges_FUNC) ( GameDll + 0x8942A0 );
      MH_CreateHook(SetCaptainChanges_org, &SetCaptainChanges_my, reinterpret_cast<void**>(&SetCaptainChanges_ptr));
      MH_EnableHook(SetCaptainChanges_org);
}
void SetCaptainHome_init ( )
{
      SetCaptainHome_org = (SetCaptainHome_FUNC) ( GameDll + 0x894310 );
      MH_CreateHook(SetCaptainHome_org, &SetCaptainHome_my, reinterpret_cast<void**>(&SetCaptainHome_ptr));
      MH_EnableHook(SetCaptainHome_org);
}
void SetCineFilterBlendMode_init ( )
{
      SetCineFilterBlendMode_org = (SetCineFilterBlendMode_FUNC) ( GameDll + 0x1F43D0 );
      MH_CreateHook(SetCineFilterBlendMode_org, &SetCineFilterBlendMode_my, reinterpret_cast<void**>(&SetCineFilterBlendMode_ptr));
      MH_EnableHook(SetCineFilterBlendMode_org);
}
void SetCineFilterDuration_init ( )
{
      SetCineFilterDuration_org = (SetCineFilterDuration_FUNC) ( GameDll + 0x1F4470 );
      MH_CreateHook(SetCineFilterDuration_org, &SetCineFilterDuration_my, reinterpret_cast<void**>(&SetCineFilterDuration_ptr));
      MH_EnableHook(SetCineFilterDuration_org);
}
void SetCineFilterEndColor_init ( )
{
      SetCineFilterEndColor_org = (SetCineFilterEndColor_FUNC) ( GameDll + 0x1F4490 );
      MH_CreateHook(SetCineFilterEndColor_org, &SetCineFilterEndColor_my, reinterpret_cast<void**>(&SetCineFilterEndColor_ptr));
      MH_EnableHook(SetCineFilterEndColor_org);
}
void SetCineFilterEndUV_init ( )
{
      SetCineFilterEndUV_org = (SetCineFilterEndUV_FUNC) ( GameDll + 0x1F4590 );
      MH_CreateHook(SetCineFilterEndUV_org, &SetCineFilterEndUV_my, reinterpret_cast<void**>(&SetCineFilterEndUV_ptr));
      MH_EnableHook(SetCineFilterEndUV_org);
}
void SetCineFilterStartColor_init ( )
{
      SetCineFilterStartColor_org = (SetCineFilterStartColor_FUNC) ( GameDll + 0x1F4620 );
      MH_CreateHook(SetCineFilterStartColor_org, &SetCineFilterStartColor_my, reinterpret_cast<void**>(&SetCineFilterStartColor_ptr));
      MH_EnableHook(SetCineFilterStartColor_org);
}
void SetCineFilterStartUV_init ( )
{
      SetCineFilterStartUV_org = (SetCineFilterStartUV_FUNC) ( GameDll + 0x1F4720 );
      MH_CreateHook(SetCineFilterStartUV_org, &SetCineFilterStartUV_my, reinterpret_cast<void**>(&SetCineFilterStartUV_ptr));
      MH_EnableHook(SetCineFilterStartUV_org);
}
void SetCineFilterTexMapFlags_init ( )
{
      SetCineFilterTexMapFlags_org = (SetCineFilterTexMapFlags_FUNC) ( GameDll + 0x1F47B0 );
      MH_CreateHook(SetCineFilterTexMapFlags_org, &SetCineFilterTexMapFlags_my, reinterpret_cast<void**>(&SetCineFilterTexMapFlags_ptr));
      MH_EnableHook(SetCineFilterTexMapFlags_org);
}
void SetCineFilterTexture_init ( )
{
      SetCineFilterTexture_org = (SetCineFilterTexture_FUNC) ( GameDll + 0x1F47F0 );
      MH_CreateHook(SetCineFilterTexture_org, &SetCineFilterTexture_my, reinterpret_cast<void**>(&SetCineFilterTexture_ptr));
      MH_EnableHook(SetCineFilterTexture_org);
}
void SetCinematicCamera_init ( )
{
      SetCinematicCamera_org = (SetCinematicCamera_FUNC) ( GameDll + 0x1F4820 );
      MH_CreateHook(SetCinematicCamera_org, &SetCinematicCamera_my, reinterpret_cast<void**>(&SetCinematicCamera_ptr));
      MH_EnableHook(SetCinematicCamera_org);
}
void SetCinematicScene_init ( )
{
      SetCinematicScene_org = (SetCinematicScene_FUNC) ( GameDll + 0x1F4860 );
      MH_CreateHook(SetCinematicScene_org, &SetCinematicScene_my, reinterpret_cast<void**>(&SetCinematicScene_ptr));
      MH_EnableHook(SetCinematicScene_org);
}
void SetCreatureDensity_init ( )
{
      SetCreatureDensity_org = (SetCreatureDensity_FUNC) ( GameDll + 0x1F48C0 );
      MH_CreateHook(SetCreatureDensity_org, &SetCreatureDensity_my, reinterpret_cast<void**>(&SetCreatureDensity_ptr));
      MH_EnableHook(SetCreatureDensity_org);
}
void SetCreepCampFilterState_init ( )
{
      SetCreepCampFilterState_org = (SetCreepCampFilterState_FUNC) ( GameDll + 0x1F48E0 );
      MH_CreateHook(SetCreepCampFilterState_org, &SetCreepCampFilterState_my, reinterpret_cast<void**>(&SetCreepCampFilterState_ptr));
      MH_EnableHook(SetCreepCampFilterState_org);
}
void SetCustomCampaignButtonVisible_init ( )
{
      SetCustomCampaignButtonVisible_org = (SetCustomCampaignButtonVisible_FUNC) ( GameDll + 0x1F4920 );
      MH_CreateHook(SetCustomCampaignButtonVisible_org, &SetCustomCampaignButtonVisible_my, reinterpret_cast<void**>(&SetCustomCampaignButtonVisible_ptr));
      MH_EnableHook(SetCustomCampaignButtonVisible_org);
}
void SetDayNightModels_init ( )
{
      SetDayNightModels_org = (SetDayNightModels_FUNC) ( GameDll + 0x1F4940 );
      MH_CreateHook(SetDayNightModels_org, &SetDayNightModels_my, reinterpret_cast<void**>(&SetDayNightModels_ptr));
      MH_EnableHook(SetDayNightModels_org);
}
void SetDefaultDifficulty_init ( )
{
      SetDefaultDifficulty_org = (SetDefaultDifficulty_FUNC) ( GameDll + 0x1F4980 );
      MH_CreateHook(SetDefaultDifficulty_org, &SetDefaultDifficulty_my, reinterpret_cast<void**>(&SetDefaultDifficulty_ptr));
      MH_EnableHook(SetDefaultDifficulty_org);
}
void SetDefendPlayer_init ( )
{
      SetDefendPlayer_org = (SetDefendPlayer_FUNC) ( GameDll + 0x894360 );
      MH_CreateHook(SetDefendPlayer_org, &SetDefendPlayer_my, reinterpret_cast<void**>(&SetDefendPlayer_ptr));
      MH_EnableHook(SetDefendPlayer_org);
}
void SetDestructableAnimation_init ( )
{
      SetDestructableAnimation_org = (SetDestructableAnimation_FUNC) ( GameDll + 0x1F4A10 );
      MH_CreateHook(SetDestructableAnimation_org, &SetDestructableAnimation_my, reinterpret_cast<void**>(&SetDestructableAnimation_ptr));
      MH_EnableHook(SetDestructableAnimation_org);
}
void SetDestructableAnimationSpeed_init ( )
{
      SetDestructableAnimationSpeed_org = (SetDestructableAnimationSpeed_FUNC) ( GameDll + 0x1F4AD0 );
      MH_CreateHook(SetDestructableAnimationSpeed_org, &SetDestructableAnimationSpeed_my, reinterpret_cast<void**>(&SetDestructableAnimationSpeed_ptr));
      MH_EnableHook(SetDestructableAnimationSpeed_org);
}
void SetDestructableInvulnerable_init ( )
{
      SetDestructableInvulnerable_org = (SetDestructableInvulnerable_FUNC) ( GameDll + 0x1F4B00 );
      MH_CreateHook(SetDestructableInvulnerable_org, &SetDestructableInvulnerable_my, reinterpret_cast<void**>(&SetDestructableInvulnerable_ptr));
      MH_EnableHook(SetDestructableInvulnerable_org);
}
void SetDestructableLife_init ( )
{
      SetDestructableLife_org = (SetDestructableLife_FUNC) ( GameDll + 0x1F4B20 );
      MH_CreateHook(SetDestructableLife_org, &SetDestructableLife_my, reinterpret_cast<void**>(&SetDestructableLife_ptr));
      MH_EnableHook(SetDestructableLife_org);
}
void SetDestructableMaxLife_init ( )
{
      SetDestructableMaxLife_org = (SetDestructableMaxLife_FUNC) ( GameDll + 0x1F4B40 );
      MH_CreateHook(SetDestructableMaxLife_org, &SetDestructableMaxLife_my, reinterpret_cast<void**>(&SetDestructableMaxLife_ptr));
      MH_EnableHook(SetDestructableMaxLife_org);
}
void SetDestructableOccluderHeight_init ( )
{
      SetDestructableOccluderHeight_org = (SetDestructableOccluderHeight_FUNC) ( GameDll + 0x1F4B90 );
      MH_CreateHook(SetDestructableOccluderHeight_org, &SetDestructableOccluderHeight_my, reinterpret_cast<void**>(&SetDestructableOccluderHeight_ptr));
      MH_EnableHook(SetDestructableOccluderHeight_org);
}
void SetDoodadAnimation_init ( )
{
      SetDoodadAnimation_org = (SetDoodadAnimation_FUNC) ( GameDll + 0x1F4BE0 );
      MH_CreateHook(SetDoodadAnimation_org, &SetDoodadAnimation_my, reinterpret_cast<void**>(&SetDoodadAnimation_ptr));
      MH_EnableHook(SetDoodadAnimation_org);
}
void SetDoodadAnimationRect_init ( )
{
      SetDoodadAnimationRect_org = (SetDoodadAnimationRect_FUNC) ( GameDll + 0x1F4C40 );
      MH_CreateHook(SetDoodadAnimationRect_org, &SetDoodadAnimationRect_my, reinterpret_cast<void**>(&SetDoodadAnimationRect_ptr));
      MH_EnableHook(SetDoodadAnimationRect_org);
}
void SetEdCinematicAvailable_init ( )
{
      SetEdCinematicAvailable_org = (SetEdCinematicAvailable_FUNC) ( GameDll + 0x1F4CE0 );
      MH_CreateHook(SetEdCinematicAvailable_org, &SetEdCinematicAvailable_my, reinterpret_cast<void**>(&SetEdCinematicAvailable_ptr));
      MH_EnableHook(SetEdCinematicAvailable_org);
}
void SetExpansion_init ( )
{
      SetExpansion_org = (SetExpansion_FUNC) ( GameDll + 0x8943D0 );
      MH_CreateHook(SetExpansion_org, &SetExpansion_my, reinterpret_cast<void**>(&SetExpansion_ptr));
      MH_EnableHook(SetExpansion_org);
}
void SetFloatGameState_init ( )
{
      SetFloatGameState_org = (SetFloatGameState_FUNC) ( GameDll + 0x1F4DA0 );
      MH_CreateHook(SetFloatGameState_org, &SetFloatGameState_my, reinterpret_cast<void**>(&SetFloatGameState_ptr));
      MH_EnableHook(SetFloatGameState_org);
}
void SetFogStateRadius_init ( )
{
      SetFogStateRadius_org = (SetFogStateRadius_FUNC) ( GameDll + 0x1F54D0 );
      MH_CreateHook(SetFogStateRadius_org, &SetFogStateRadius_my, reinterpret_cast<void**>(&SetFogStateRadius_ptr));
      MH_EnableHook(SetFogStateRadius_org);
}
void SetFogStateRadiusLoc_init ( )
{
      SetFogStateRadiusLoc_org = (SetFogStateRadiusLoc_FUNC) ( GameDll + 0x1F5530 );
      MH_CreateHook(SetFogStateRadiusLoc_org, &SetFogStateRadiusLoc_my, reinterpret_cast<void**>(&SetFogStateRadiusLoc_ptr));
      MH_EnableHook(SetFogStateRadiusLoc_org);
}
void SetFogStateRect_init ( )
{
      SetFogStateRect_org = (SetFogStateRect_FUNC) ( GameDll + 0x1F55A0 );
      MH_CreateHook(SetFogStateRect_org, &SetFogStateRect_my, reinterpret_cast<void**>(&SetFogStateRect_ptr));
      MH_EnableHook(SetFogStateRect_org);
}
void SetGameDifficulty_init ( )
{
      SetGameDifficulty_org = (SetGameDifficulty_FUNC) ( GameDll + 0x1F5680 );
      MH_CreateHook(SetGameDifficulty_org, &SetGameDifficulty_my, reinterpret_cast<void**>(&SetGameDifficulty_ptr));
      MH_EnableHook(SetGameDifficulty_org);
}
void SetGamePlacement_init ( )
{
      SetGamePlacement_org = (SetGamePlacement_FUNC) ( GameDll + 0x1F56A0 );
      MH_CreateHook(SetGamePlacement_org, &SetGamePlacement_my, reinterpret_cast<void**>(&SetGamePlacement_ptr));
      MH_EnableHook(SetGamePlacement_org);
}
void SetGameSpeed_init ( )
{
      SetGameSpeed_org = (SetGameSpeed_FUNC) ( GameDll + 0x1F56C0 );
      MH_CreateHook(SetGameSpeed_org, &SetGameSpeed_my, reinterpret_cast<void**>(&SetGameSpeed_ptr));
      MH_EnableHook(SetGameSpeed_org);
}
void SetGameTypeSupported_init ( )
{
      SetGameTypeSupported_org = (SetGameTypeSupported_FUNC) ( GameDll + 0x1F56E0 );
      MH_CreateHook(SetGameTypeSupported_org, &SetGameTypeSupported_my, reinterpret_cast<void**>(&SetGameTypeSupported_ptr));
      MH_EnableHook(SetGameTypeSupported_org);
}
void SetGroupsFlee_init ( )
{
      SetGroupsFlee_org = (SetGroupsFlee_FUNC) ( GameDll + 0x894510 );
      MH_CreateHook(SetGroupsFlee_org, &SetGroupsFlee_my, reinterpret_cast<void**>(&SetGroupsFlee_ptr));
      MH_EnableHook(SetGroupsFlee_org);
}
void SetHeroAgi_init ( )
{
      SetHeroAgi_org = (SetHeroAgi_FUNC) ( GameDll + 0x1F5720 );
      MH_CreateHook(SetHeroAgi_org, &SetHeroAgi_my, reinterpret_cast<void**>(&SetHeroAgi_ptr));
      MH_EnableHook(SetHeroAgi_org);
}
void SetHeroInt_init ( )
{
      SetHeroInt_org = (SetHeroInt_FUNC) ( GameDll + 0x1F5780 );
      MH_CreateHook(SetHeroInt_org, &SetHeroInt_my, reinterpret_cast<void**>(&SetHeroInt_ptr));
      MH_EnableHook(SetHeroInt_org);
}
void SetHeroLevel_init ( )
{
      SetHeroLevel_org = (SetHeroLevel_FUNC) ( GameDll + 0x1F57E0 );
      MH_CreateHook(SetHeroLevel_org, &SetHeroLevel_my, reinterpret_cast<void**>(&SetHeroLevel_ptr));
      MH_EnableHook(SetHeroLevel_org);
}
void SetHeroLevels_init ( )
{
      SetHeroLevels_org = (SetHeroLevels_FUNC) ( GameDll + 0x894660 );
      MH_CreateHook(SetHeroLevels_org, &SetHeroLevels_my, reinterpret_cast<void**>(&SetHeroLevels_ptr));
      MH_EnableHook(SetHeroLevels_org);
}
void SetHeroStr_init ( )
{
      SetHeroStr_org = (SetHeroStr_FUNC) ( GameDll + 0x1F5890 );
      MH_CreateHook(SetHeroStr_org, &SetHeroStr_my, reinterpret_cast<void**>(&SetHeroStr_ptr));
      MH_EnableHook(SetHeroStr_org);
}
void SetHeroXP_init ( )
{
      SetHeroXP_org = (SetHeroXP_FUNC) ( GameDll + 0x1F58F0 );
      MH_CreateHook(SetHeroXP_org, &SetHeroXP_my, reinterpret_cast<void**>(&SetHeroXP_ptr));
      MH_EnableHook(SetHeroXP_org);
}
void SetHeroesBuyItems_init ( )
{
      SetHeroesBuyItems_org = (SetHeroesBuyItems_FUNC) ( GameDll + 0x8946D0 );
      MH_CreateHook(SetHeroesBuyItems_org, &SetHeroesBuyItems_my, reinterpret_cast<void**>(&SetHeroesBuyItems_ptr));
      MH_EnableHook(SetHeroesBuyItems_org);
}
void SetHeroesFlee_init ( )
{
      SetHeroesFlee_org = (SetHeroesFlee_FUNC) ( GameDll + 0x894710 );
      MH_CreateHook(SetHeroesFlee_org, &SetHeroesFlee_my, reinterpret_cast<void**>(&SetHeroesFlee_ptr));
      MH_EnableHook(SetHeroesFlee_org);
}
void SetHeroesTakeItems_init ( )
{
      SetHeroesTakeItems_org = (SetHeroesTakeItems_FUNC) ( GameDll + 0x8947A0 );
      MH_CreateHook(SetHeroesTakeItems_org, &SetHeroesTakeItems_my, reinterpret_cast<void**>(&SetHeroesTakeItems_ptr));
      MH_EnableHook(SetHeroesTakeItems_org);
}
void SetIgnoreInjured_init ( )
{
      SetIgnoreInjured_org = (SetIgnoreInjured_FUNC) ( GameDll + 0x8947E0 );
      MH_CreateHook(SetIgnoreInjured_org, &SetIgnoreInjured_my, reinterpret_cast<void**>(&SetIgnoreInjured_ptr));
      MH_EnableHook(SetIgnoreInjured_org);
}
void SetImageAboveWater_init ( )
{
      SetImageAboveWater_org = (SetImageAboveWater_FUNC) ( GameDll + 0x1F5990 );
      MH_CreateHook(SetImageAboveWater_org, &SetImageAboveWater_my, reinterpret_cast<void**>(&SetImageAboveWater_ptr));
      MH_EnableHook(SetImageAboveWater_org);
}
void SetImageColor_init ( )
{
      SetImageColor_org = (SetImageColor_FUNC) ( GameDll + 0x1F59B0 );
      MH_CreateHook(SetImageColor_org, &SetImageColor_my, reinterpret_cast<void**>(&SetImageColor_ptr));
      MH_EnableHook(SetImageColor_org);
}
void SetImageConstantHeight_init ( )
{
      SetImageConstantHeight_org = (SetImageConstantHeight_FUNC) ( GameDll + 0x1F59F0 );
      MH_CreateHook(SetImageConstantHeight_org, &SetImageConstantHeight_my, reinterpret_cast<void**>(&SetImageConstantHeight_ptr));
      MH_EnableHook(SetImageConstantHeight_org);
}
void SetImagePosition_init ( )
{
      SetImagePosition_org = (SetImagePosition_FUNC) ( GameDll + 0x1F5A20 );
      MH_CreateHook(SetImagePosition_org, &SetImagePosition_my, reinterpret_cast<void**>(&SetImagePosition_ptr));
      MH_EnableHook(SetImagePosition_org);
}
void SetImageRender_init ( )
{
      SetImageRender_org = (SetImageRender_FUNC) ( GameDll + 0x1F5A60 );
      MH_CreateHook(SetImageRender_org, &SetImageRender_my, reinterpret_cast<void**>(&SetImageRender_ptr));
      MH_EnableHook(SetImageRender_org);
}
void SetImageRenderAlways_init ( )
{
      SetImageRenderAlways_org = (SetImageRenderAlways_FUNC) ( GameDll + 0x1F5A80 );
      MH_CreateHook(SetImageRenderAlways_org, &SetImageRenderAlways_my, reinterpret_cast<void**>(&SetImageRenderAlways_ptr));
      MH_EnableHook(SetImageRenderAlways_org);
}
void SetImageType_init ( )
{
      SetImageType_org = (SetImageType_FUNC) ( GameDll + 0x1F5AA0 );
      MH_CreateHook(SetImageType_org, &SetImageType_my, reinterpret_cast<void**>(&SetImageType_ptr));
      MH_EnableHook(SetImageType_org);
}
void SetIntegerGameState_init ( )
{
      SetIntegerGameState_org = (SetIntegerGameState_FUNC) ( GameDll + 0x1F5AC0 );
      MH_CreateHook(SetIntegerGameState_org, &SetIntegerGameState_my, reinterpret_cast<void**>(&SetIntegerGameState_ptr));
      MH_EnableHook(SetIntegerGameState_org);
}
void SetIntroShotModel_init ( )
{
      SetIntroShotModel_org = (SetIntroShotModel_FUNC) ( GameDll + 0x1F5B00 );
      MH_CreateHook(SetIntroShotModel_org, &SetIntroShotModel_my, reinterpret_cast<void**>(&SetIntroShotModel_ptr));
      MH_EnableHook(SetIntroShotModel_org);
}
void SetIntroShotText_init ( )
{
      SetIntroShotText_org = (SetIntroShotText_FUNC) ( GameDll + 0x1F5B20 );
      MH_CreateHook(SetIntroShotText_org, &SetIntroShotText_my, reinterpret_cast<void**>(&SetIntroShotText_ptr));
      MH_EnableHook(SetIntroShotText_org);
}
void SetItemCharges_init ( )
{
      SetItemCharges_org = (SetItemCharges_FUNC) ( GameDll + 0x1F5B50 );
      MH_CreateHook(SetItemCharges_org, &SetItemCharges_my, reinterpret_cast<void**>(&SetItemCharges_ptr));
      MH_EnableHook(SetItemCharges_org);
}
void SetItemDropID_init ( )
{
      SetItemDropID_org = (SetItemDropID_FUNC) ( GameDll + 0x1F5BB0 );
      MH_CreateHook(SetItemDropID_org, &SetItemDropID_my, reinterpret_cast<void**>(&SetItemDropID_ptr));
      MH_EnableHook(SetItemDropID_org);
}
void SetItemDropOnDeath_init ( )
{
      SetItemDropOnDeath_org = (SetItemDropOnDeath_FUNC) ( GameDll + 0x1F5BD0 );
      MH_CreateHook(SetItemDropOnDeath_org, &SetItemDropOnDeath_my, reinterpret_cast<void**>(&SetItemDropOnDeath_ptr));
      MH_EnableHook(SetItemDropOnDeath_org);
}
void SetItemDroppable_init ( )
{
      SetItemDroppable_org = (SetItemDroppable_FUNC) ( GameDll + 0x1F5C00 );
      MH_CreateHook(SetItemDroppable_org, &SetItemDroppable_my, reinterpret_cast<void**>(&SetItemDroppable_ptr));
      MH_EnableHook(SetItemDroppable_org);
}
void SetItemInvulnerable_init ( )
{
      SetItemInvulnerable_org = (SetItemInvulnerable_FUNC) ( GameDll + 0x1F5C30 );
      MH_CreateHook(SetItemInvulnerable_org, &SetItemInvulnerable_my, reinterpret_cast<void**>(&SetItemInvulnerable_ptr));
      MH_EnableHook(SetItemInvulnerable_org);
}
void SetItemPawnable_init ( )
{
      SetItemPawnable_org = (SetItemPawnable_FUNC) ( GameDll + 0x1F5C50 );
      MH_CreateHook(SetItemPawnable_org, &SetItemPawnable_my, reinterpret_cast<void**>(&SetItemPawnable_ptr));
      MH_EnableHook(SetItemPawnable_org);
}
void SetItemPlayer_init ( )
{
      SetItemPlayer_org = (SetItemPlayer_FUNC) ( GameDll + 0x1F5C80 );
      MH_CreateHook(SetItemPlayer_org, &SetItemPlayer_my, reinterpret_cast<void**>(&SetItemPlayer_ptr));
      MH_EnableHook(SetItemPlayer_org);
}
void SetItemPosition_init ( )
{
      SetItemPosition_org = (SetItemPosition_FUNC) ( GameDll + 0x1F5CB0 );
      MH_CreateHook(SetItemPosition_org, &SetItemPosition_my, reinterpret_cast<void**>(&SetItemPosition_ptr));
      MH_EnableHook(SetItemPosition_org);
}
void SetItemTypeSlots_init ( )
{
      SetItemTypeSlots_org = (SetItemTypeSlots_FUNC) ( GameDll + 0x1F5D30 );
      MH_CreateHook(SetItemTypeSlots_org, &SetItemTypeSlots_my, reinterpret_cast<void**>(&SetItemTypeSlots_ptr));
      MH_EnableHook(SetItemTypeSlots_org);
}
void SetItemUserData_init ( )
{
      SetItemUserData_org = (SetItemUserData_FUNC) ( GameDll + 0x1F5D70 );
      MH_CreateHook(SetItemUserData_org, &SetItemUserData_my, reinterpret_cast<void**>(&SetItemUserData_ptr));
      MH_EnableHook(SetItemUserData_org);
}
void SetItemVisible_init ( )
{
      SetItemVisible_org = (SetItemVisible_FUNC) ( GameDll + 0x1F5D90 );
      MH_CreateHook(SetItemVisible_org, &SetItemVisible_my, reinterpret_cast<void**>(&SetItemVisible_ptr));
      MH_EnableHook(SetItemVisible_org);
}
void SetLightningColor_init ( )
{
      SetLightningColor_org = (SetLightningColor_FUNC) ( GameDll + 0x1F5E00 );
      MH_CreateHook(SetLightningColor_org, &SetLightningColor_my, reinterpret_cast<void**>(&SetLightningColor_ptr));
      MH_EnableHook(SetLightningColor_org);
}
void SetMapDescription_init ( )
{
      SetMapDescription_org = (SetMapDescription_FUNC) ( GameDll + 0x1F5E90 );
      MH_CreateHook(SetMapDescription_org, &SetMapDescription_my, reinterpret_cast<void**>(&SetMapDescription_ptr));
      MH_EnableHook(SetMapDescription_org);
}
void SetMapFlag_init ( )
{
      SetMapFlag_org = (SetMapFlag_FUNC) ( GameDll + 0x1F5EC0 );
      MH_CreateHook(SetMapFlag_org, &SetMapFlag_my, reinterpret_cast<void**>(&SetMapFlag_ptr));
      MH_EnableHook(SetMapFlag_org);
}
void SetMapMusic_init ( )
{
      SetMapMusic_org = (SetMapMusic_FUNC) ( GameDll + 0x1F5EF0 );
      MH_CreateHook(SetMapMusic_org, &SetMapMusic_my, reinterpret_cast<void**>(&SetMapMusic_ptr));
      MH_EnableHook(SetMapMusic_org);
}
void SetMapName_init ( )
{
      SetMapName_org = (SetMapName_FUNC) ( GameDll + 0x1F5F20 );
      MH_CreateHook(SetMapName_org, &SetMapName_my, reinterpret_cast<void**>(&SetMapName_ptr));
      MH_EnableHook(SetMapName_org);
}
void SetMeleeAI_init ( )
{
      SetMeleeAI_org = (SetMeleeAI_FUNC) ( GameDll + 0x894850 );
      MH_CreateHook(SetMeleeAI_org, &SetMeleeAI_my, reinterpret_cast<void**>(&SetMeleeAI_ptr));
      MH_EnableHook(SetMeleeAI_org);
}
void SetMissionAvailable_init ( )
{
      SetMissionAvailable_org = (SetMissionAvailable_FUNC) ( GameDll + 0x1F5F50 );
      MH_CreateHook(SetMissionAvailable_org, &SetMissionAvailable_my, reinterpret_cast<void**>(&SetMissionAvailable_ptr));
      MH_EnableHook(SetMissionAvailable_org);
}
void SetMusicPlayPosition_init ( )
{
      SetMusicPlayPosition_org = (SetMusicPlayPosition_FUNC) ( GameDll + 0x1F5F80 );
      MH_CreateHook(SetMusicPlayPosition_org, &SetMusicPlayPosition_my, reinterpret_cast<void**>(&SetMusicPlayPosition_ptr));
      MH_EnableHook(SetMusicPlayPosition_org);
}
void SetMusicVolume_init ( )
{
      SetMusicVolume_org = (SetMusicVolume_FUNC) ( GameDll + 0x1F5F90 );
      MH_CreateHook(SetMusicVolume_org, &SetMusicVolume_my, reinterpret_cast<void**>(&SetMusicVolume_ptr));
      MH_EnableHook(SetMusicVolume_org);
}
void SetNewHeroes_init ( )
{
      SetNewHeroes_org = (SetNewHeroes_FUNC) ( GameDll + 0x894880 );
      MH_CreateHook(SetNewHeroes_org, &SetNewHeroes_my, reinterpret_cast<void**>(&SetNewHeroes_ptr));
      MH_EnableHook(SetNewHeroes_org);
}
void SetOpCinematicAvailable_init ( )
{
      SetOpCinematicAvailable_org = (SetOpCinematicAvailable_FUNC) ( GameDll + 0x1F5FD0 );
      MH_CreateHook(SetOpCinematicAvailable_org, &SetOpCinematicAvailable_my, reinterpret_cast<void**>(&SetOpCinematicAvailable_ptr));
      MH_EnableHook(SetOpCinematicAvailable_org);
}
void SetPeonsRepair_init ( )
{
      SetPeonsRepair_org = (SetPeonsRepair_FUNC) ( GameDll + 0x8948E0 );
      MH_CreateHook(SetPeonsRepair_org, &SetPeonsRepair_my, reinterpret_cast<void**>(&SetPeonsRepair_ptr));
      MH_EnableHook(SetPeonsRepair_org);
}
void SetPlayerAbilityAvailable_init ( )
{
      SetPlayerAbilityAvailable_org = (SetPlayerAbilityAvailable_FUNC) ( GameDll + 0x1F6000 );
      MH_CreateHook(SetPlayerAbilityAvailable_org, &SetPlayerAbilityAvailable_my, reinterpret_cast<void**>(&SetPlayerAbilityAvailable_ptr));
      MH_EnableHook(SetPlayerAbilityAvailable_org);
}
void SetPlayerAlliance_init ( )
{
      SetPlayerAlliance_org = (SetPlayerAlliance_FUNC) ( GameDll + 0x1F6030 );
      MH_CreateHook(SetPlayerAlliance_org, &SetPlayerAlliance_my, reinterpret_cast<void**>(&SetPlayerAlliance_ptr));
      MH_EnableHook(SetPlayerAlliance_org);
}
void SetPlayerColor_init ( )
{
      SetPlayerColor_org = (SetPlayerColor_FUNC) ( GameDll + 0x1F60D0 );
      MH_CreateHook(SetPlayerColor_org, &SetPlayerColor_my, reinterpret_cast<void**>(&SetPlayerColor_ptr));
      MH_EnableHook(SetPlayerColor_org);
}
void SetPlayerController_init ( )
{
      SetPlayerController_org = (SetPlayerController_FUNC) ( GameDll + 0x1F60F0 );
      MH_CreateHook(SetPlayerController_org, &SetPlayerController_my, reinterpret_cast<void**>(&SetPlayerController_ptr));
      MH_EnableHook(SetPlayerController_org);
}
void SetPlayerHandicap_init ( )
{
      SetPlayerHandicap_org = (SetPlayerHandicap_FUNC) ( GameDll + 0x1F6120 );
      MH_CreateHook(SetPlayerHandicap_org, &SetPlayerHandicap_my, reinterpret_cast<void**>(&SetPlayerHandicap_ptr));
      MH_EnableHook(SetPlayerHandicap_org);
}
void SetPlayerHandicapXP_init ( )
{
      SetPlayerHandicapXP_org = (SetPlayerHandicapXP_FUNC) ( GameDll + 0x1F61E0 );
      MH_CreateHook(SetPlayerHandicapXP_org, &SetPlayerHandicapXP_my, reinterpret_cast<void**>(&SetPlayerHandicapXP_ptr));
      MH_EnableHook(SetPlayerHandicapXP_org);
}
void SetPlayerName_init ( )
{
      SetPlayerName_org = (SetPlayerName_FUNC) ( GameDll + 0x1F6240 );
      MH_CreateHook(SetPlayerName_org, &SetPlayerName_my, reinterpret_cast<void**>(&SetPlayerName_ptr));
      MH_EnableHook(SetPlayerName_org);
}
void SetPlayerOnScoreScreen_init ( )
{
      SetPlayerOnScoreScreen_org = (SetPlayerOnScoreScreen_FUNC) ( GameDll + 0x1F6280 );
      MH_CreateHook(SetPlayerOnScoreScreen_org, &SetPlayerOnScoreScreen_my, reinterpret_cast<void**>(&SetPlayerOnScoreScreen_ptr));
      MH_EnableHook(SetPlayerOnScoreScreen_org);
}
void SetPlayerRacePreference_init ( )
{
      SetPlayerRacePreference_org = (SetPlayerRacePreference_FUNC) ( GameDll + 0x1F62A0 );
      MH_CreateHook(SetPlayerRacePreference_org, &SetPlayerRacePreference_my, reinterpret_cast<void**>(&SetPlayerRacePreference_ptr));
      MH_EnableHook(SetPlayerRacePreference_org);
}
void SetPlayerRaceSelectable_init ( )
{
      SetPlayerRaceSelectable_org = (SetPlayerRaceSelectable_FUNC) ( GameDll + 0x1F62D0 );
      MH_CreateHook(SetPlayerRaceSelectable_org, &SetPlayerRaceSelectable_my, reinterpret_cast<void**>(&SetPlayerRaceSelectable_ptr));
      MH_EnableHook(SetPlayerRaceSelectable_org);
}
void SetPlayerStartLocation_init ( )
{
      SetPlayerStartLocation_org = (SetPlayerStartLocation_FUNC) ( GameDll + 0x1F6300 );
      MH_CreateHook(SetPlayerStartLocation_org, &SetPlayerStartLocation_my, reinterpret_cast<void**>(&SetPlayerStartLocation_ptr));
      MH_EnableHook(SetPlayerStartLocation_org);
}
void SetPlayerState_init ( )
{
      SetPlayerState_org = (SetPlayerState_FUNC) ( GameDll + 0x1F6320 );
      MH_CreateHook(SetPlayerState_org, &SetPlayerState_my, reinterpret_cast<void**>(&SetPlayerState_ptr));
      MH_EnableHook(SetPlayerState_org);
}
void SetPlayerTaxRate_init ( )
{
      SetPlayerTaxRate_org = (SetPlayerTaxRate_FUNC) ( GameDll + 0x1F6380 );
      MH_CreateHook(SetPlayerTaxRate_org, &SetPlayerTaxRate_my, reinterpret_cast<void**>(&SetPlayerTaxRate_ptr));
      MH_EnableHook(SetPlayerTaxRate_org);
}
void SetPlayerTeam_init ( )
{
      SetPlayerTeam_org = (SetPlayerTeam_FUNC) ( GameDll + 0x1F63E0 );
      MH_CreateHook(SetPlayerTeam_org, &SetPlayerTeam_my, reinterpret_cast<void**>(&SetPlayerTeam_ptr));
      MH_EnableHook(SetPlayerTeam_org);
}
void SetPlayerTechMaxAllowed_init ( )
{
      SetPlayerTechMaxAllowed_org = (SetPlayerTechMaxAllowed_FUNC) ( GameDll + 0x1F6410 );
      MH_CreateHook(SetPlayerTechMaxAllowed_org, &SetPlayerTechMaxAllowed_my, reinterpret_cast<void**>(&SetPlayerTechMaxAllowed_ptr));
      MH_EnableHook(SetPlayerTechMaxAllowed_org);
}
void SetPlayerTechResearched_init ( )
{
      SetPlayerTechResearched_org = (SetPlayerTechResearched_FUNC) ( GameDll + 0x1F6440 );
      MH_CreateHook(SetPlayerTechResearched_org, &SetPlayerTechResearched_my, reinterpret_cast<void**>(&SetPlayerTechResearched_ptr));
      MH_EnableHook(SetPlayerTechResearched_org);
}
void SetPlayerUnitsOwner_init ( )
{
      SetPlayerUnitsOwner_org = (SetPlayerUnitsOwner_FUNC) ( GameDll + 0x1F6480 );
      MH_CreateHook(SetPlayerUnitsOwner_org, &SetPlayerUnitsOwner_my, reinterpret_cast<void**>(&SetPlayerUnitsOwner_ptr));
      MH_EnableHook(SetPlayerUnitsOwner_org);
}
void SetPlayers_init ( )
{
      SetPlayers_org = (SetPlayers_FUNC) ( GameDll + 0x1F64A0 );
      MH_CreateHook(SetPlayers_org, &SetPlayers_my, reinterpret_cast<void**>(&SetPlayers_ptr));
      MH_EnableHook(SetPlayers_org);
}
void SetProduce_init ( )
{
      SetProduce_org = (SetProduce_FUNC) ( GameDll + 0x894950 );
      MH_CreateHook(SetProduce_org, &SetProduce_my, reinterpret_cast<void**>(&SetProduce_ptr));
      MH_EnableHook(SetProduce_org);
}
void SetRandomPaths_init ( )
{
      SetRandomPaths_org = (SetRandomPaths_FUNC) ( GameDll + 0x8949B0 );
      MH_CreateHook(SetRandomPaths_org, &SetRandomPaths_my, reinterpret_cast<void**>(&SetRandomPaths_ptr));
      MH_EnableHook(SetRandomPaths_org);
}
void SetRandomSeed_init ( )
{
      SetRandomSeed_org = (SetRandomSeed_FUNC) ( GameDll + 0x1F64B0 );
      MH_CreateHook(SetRandomSeed_org, &SetRandomSeed_my, reinterpret_cast<void**>(&SetRandomSeed_ptr));
      MH_EnableHook(SetRandomSeed_org);
}
void SetRect_init ( )
{
      SetRect_org = (SetRect_FUNC) ( GameDll + 0x1EF750 );
      MH_CreateHook(SetRect_org, &SetRect_my, reinterpret_cast<void**>(&SetRect_ptr));
      MH_EnableHook(SetRect_org);
}
void SetRectFromLoc_init ( )
{
      SetRectFromLoc_org = (SetRectFromLoc_FUNC) ( GameDll + 0x1F64E0 );
      MH_CreateHook(SetRectFromLoc_org, &SetRectFromLoc_my, reinterpret_cast<void**>(&SetRectFromLoc_ptr));
      MH_EnableHook(SetRectFromLoc_org);
}
void SetReplacementCount_init ( )
{
      SetReplacementCount_org = (SetReplacementCount_FUNC) ( GameDll + 0x894A30 );
      MH_CreateHook(SetReplacementCount_org, &SetReplacementCount_my, reinterpret_cast<void**>(&SetReplacementCount_ptr));
      MH_EnableHook(SetReplacementCount_org);
}
void SetReservedLocalHeroButtons_init ( )
{
      SetReservedLocalHeroButtons_org = (SetReservedLocalHeroButtons_FUNC) ( GameDll + 0x1F65C0 );
      MH_CreateHook(SetReservedLocalHeroButtons_org, &SetReservedLocalHeroButtons_my, reinterpret_cast<void**>(&SetReservedLocalHeroButtons_ptr));
      MH_EnableHook(SetReservedLocalHeroButtons_org);
}
void SetResourceAmount_init ( )
{
      SetResourceAmount_org = (SetResourceAmount_FUNC) ( GameDll + 0x1F65E0 );
      MH_CreateHook(SetResourceAmount_org, &SetResourceAmount_my, reinterpret_cast<void**>(&SetResourceAmount_ptr));
      MH_EnableHook(SetResourceAmount_org);
}
void SetResourceDensity_init ( )
{
      SetResourceDensity_org = (SetResourceDensity_FUNC) ( GameDll + 0x1F6630 );
      MH_CreateHook(SetResourceDensity_org, &SetResourceDensity_my, reinterpret_cast<void**>(&SetResourceDensity_ptr));
      MH_EnableHook(SetResourceDensity_org);
}
void SetSkyModel_init ( )
{
      SetSkyModel_org = (SetSkyModel_FUNC) ( GameDll + 0x1F6650 );
      MH_CreateHook(SetSkyModel_org, &SetSkyModel_my, reinterpret_cast<void**>(&SetSkyModel_ptr));
      MH_EnableHook(SetSkyModel_org);
}
void SetSlowChopping_init ( )
{
      SetSlowChopping_org = (SetSlowChopping_FUNC) ( GameDll + 0x894A70 );
      MH_CreateHook(SetSlowChopping_org, &SetSlowChopping_my, reinterpret_cast<void**>(&SetSlowChopping_ptr));
      MH_EnableHook(SetSlowChopping_org);
}
void SetSmartArtillery_init ( )
{
      SetSmartArtillery_org = (SetSmartArtillery_FUNC) ( GameDll + 0x894AD0 );
      MH_CreateHook(SetSmartArtillery_org, &SetSmartArtillery_my, reinterpret_cast<void**>(&SetSmartArtillery_ptr));
      MH_EnableHook(SetSmartArtillery_org);
}
void SetSoundChannel_init ( )
{
      SetSoundChannel_org = (SetSoundChannel_FUNC) ( GameDll + 0x1F6690 );
      MH_CreateHook(SetSoundChannel_org, &SetSoundChannel_my, reinterpret_cast<void**>(&SetSoundChannel_ptr));
      MH_EnableHook(SetSoundChannel_org);
}
void SetSoundConeAngles_init ( )
{
      SetSoundConeAngles_org = (SetSoundConeAngles_FUNC) ( GameDll + 0x1F66B0 );
      MH_CreateHook(SetSoundConeAngles_org, &SetSoundConeAngles_my, reinterpret_cast<void**>(&SetSoundConeAngles_ptr));
      MH_EnableHook(SetSoundConeAngles_org);
}
void SetSoundConeOrientation_init ( )
{
      SetSoundConeOrientation_org = (SetSoundConeOrientation_FUNC) ( GameDll + 0x1F6700 );
      MH_CreateHook(SetSoundConeOrientation_org, &SetSoundConeOrientation_my, reinterpret_cast<void**>(&SetSoundConeOrientation_ptr));
      MH_EnableHook(SetSoundConeOrientation_org);
}
void SetSoundDistanceCutoff_init ( )
{
      SetSoundDistanceCutoff_org = (SetSoundDistanceCutoff_FUNC) ( GameDll + 0x1F6760 );
      MH_CreateHook(SetSoundDistanceCutoff_org, &SetSoundDistanceCutoff_my, reinterpret_cast<void**>(&SetSoundDistanceCutoff_ptr));
      MH_EnableHook(SetSoundDistanceCutoff_org);
}
void SetSoundDistances_init ( )
{
      SetSoundDistances_org = (SetSoundDistances_FUNC) ( GameDll + 0x1F6790 );
      MH_CreateHook(SetSoundDistances_org, &SetSoundDistances_my, reinterpret_cast<void**>(&SetSoundDistances_ptr));
      MH_EnableHook(SetSoundDistances_org);
}
void SetSoundDuration_init ( )
{
      SetSoundDuration_org = (SetSoundDuration_FUNC) ( GameDll + 0x1F67D0 );
      MH_CreateHook(SetSoundDuration_org, &SetSoundDuration_my, reinterpret_cast<void**>(&SetSoundDuration_ptr));
      MH_EnableHook(SetSoundDuration_org);
}
void SetSoundParamsFromLabel_init ( )
{
      SetSoundParamsFromLabel_org = (SetSoundParamsFromLabel_FUNC) ( GameDll + 0x1F6800 );
      MH_CreateHook(SetSoundParamsFromLabel_org, &SetSoundParamsFromLabel_my, reinterpret_cast<void**>(&SetSoundParamsFromLabel_ptr));
      MH_EnableHook(SetSoundParamsFromLabel_org);
}
void SetSoundPitch_init ( )
{
      SetSoundPitch_org = (SetSoundPitch_FUNC) ( GameDll + 0x1F6830 );
      MH_CreateHook(SetSoundPitch_org, &SetSoundPitch_my, reinterpret_cast<void**>(&SetSoundPitch_ptr));
      MH_EnableHook(SetSoundPitch_org);
}
void SetSoundPlayPosition_init ( )
{
      SetSoundPlayPosition_org = (SetSoundPlayPosition_FUNC) ( GameDll + 0x1F6860 );
      MH_CreateHook(SetSoundPlayPosition_org, &SetSoundPlayPosition_my, reinterpret_cast<void**>(&SetSoundPlayPosition_ptr));
      MH_EnableHook(SetSoundPlayPosition_org);
}
void SetSoundPosition_init ( )
{
      SetSoundPosition_org = (SetSoundPosition_FUNC) ( GameDll + 0x1F6880 );
      MH_CreateHook(SetSoundPosition_org, &SetSoundPosition_my, reinterpret_cast<void**>(&SetSoundPosition_ptr));
      MH_EnableHook(SetSoundPosition_org);
}
void SetSoundVelocity_init ( )
{
      SetSoundVelocity_org = (SetSoundVelocity_FUNC) ( GameDll + 0x1F68E0 );
      MH_CreateHook(SetSoundVelocity_org, &SetSoundVelocity_my, reinterpret_cast<void**>(&SetSoundVelocity_ptr));
      MH_EnableHook(SetSoundVelocity_org);
}
void SetSoundVolume_init ( )
{
      SetSoundVolume_org = (SetSoundVolume_FUNC) ( GameDll + 0x1F6940 );
      MH_CreateHook(SetSoundVolume_org, &SetSoundVolume_my, reinterpret_cast<void**>(&SetSoundVolume_ptr));
      MH_EnableHook(SetSoundVolume_org);
}
void SetStackedSound_init ( )
{
      SetStackedSound_org = (SetStackedSound_FUNC) ( GameDll + 0x1F6960 );
      MH_CreateHook(SetStackedSound_org, &SetStackedSound_my, reinterpret_cast<void**>(&SetStackedSound_ptr));
      MH_EnableHook(SetStackedSound_org);
}
void SetStackedSoundRect_init ( )
{
      SetStackedSoundRect_org = (SetStackedSoundRect_FUNC) ( GameDll + 0x1F69C0 );
      MH_CreateHook(SetStackedSoundRect_org, &SetStackedSoundRect_my, reinterpret_cast<void**>(&SetStackedSoundRect_ptr));
      MH_EnableHook(SetStackedSoundRect_org);
}
void SetStagePoint_init ( )
{
      SetStagePoint_org = (SetStagePoint_FUNC) ( GameDll + 0x894B10 );
      MH_CreateHook(SetStagePoint_org, &SetStagePoint_my, reinterpret_cast<void**>(&SetStagePoint_ptr));
      MH_EnableHook(SetStagePoint_org);
}
void SetStartLocPrio_init ( )
{
      SetStartLocPrio_org = (SetStartLocPrio_FUNC) ( GameDll + 0x1F6B00 );
      MH_CreateHook(SetStartLocPrio_org, &SetStartLocPrio_my, reinterpret_cast<void**>(&SetStartLocPrio_ptr));
      MH_EnableHook(SetStartLocPrio_org);
}
void SetStartLocPrioCount_init ( )
{
      SetStartLocPrioCount_org = (SetStartLocPrioCount_FUNC) ( GameDll + 0x1F6B40 );
      MH_CreateHook(SetStartLocPrioCount_org, &SetStartLocPrioCount_my, reinterpret_cast<void**>(&SetStartLocPrioCount_ptr));
      MH_EnableHook(SetStartLocPrioCount_org);
}
void SetTargetHeroes_init ( )
{
      SetTargetHeroes_org = (SetTargetHeroes_FUNC) ( GameDll + 0x894B50 );
      MH_CreateHook(SetTargetHeroes_org, &SetTargetHeroes_my, reinterpret_cast<void**>(&SetTargetHeroes_ptr));
      MH_EnableHook(SetTargetHeroes_org);
}
void SetTeams_init ( )
{
      SetTeams_org = (SetTeams_FUNC) ( GameDll + 0x1F6B70 );
      MH_CreateHook(SetTeams_org, &SetTeams_my, reinterpret_cast<void**>(&SetTeams_ptr));
      MH_EnableHook(SetTeams_org);
}
void SetTerrainFog_init ( )
{
      SetTerrainFog_org = (SetTerrainFog_FUNC) ( GameDll + 0x1F6BA0 );
      MH_CreateHook(SetTerrainFog_org, &SetTerrainFog_my, reinterpret_cast<void**>(&SetTerrainFog_ptr));
      MH_EnableHook(SetTerrainFog_org);
}
void SetTerrainFogEx_init ( )
{
      SetTerrainFogEx_org = (SetTerrainFogEx_FUNC) ( GameDll + 0x1F6BB0 );
      MH_CreateHook(SetTerrainFogEx_org, &SetTerrainFogEx_my, reinterpret_cast<void**>(&SetTerrainFogEx_ptr));
      MH_EnableHook(SetTerrainFogEx_org);
}
void SetTerrainPathable_init ( )
{
      SetTerrainPathable_org = (SetTerrainPathable_FUNC) ( GameDll + 0x1F6C60 );
      MH_CreateHook(SetTerrainPathable_org, &SetTerrainPathable_my, reinterpret_cast<void**>(&SetTerrainPathable_ptr));
      MH_EnableHook(SetTerrainPathable_org);
}
void SetTerrainType_init ( )
{
      SetTerrainType_org = (SetTerrainType_FUNC) ( GameDll + 0x1F6C90 );
      MH_CreateHook(SetTerrainType_org, &SetTerrainType_my, reinterpret_cast<void**>(&SetTerrainType_ptr));
      MH_EnableHook(SetTerrainType_org);
}
void SetTextTagAge_init ( )
{
      SetTextTagAge_org = (SetTextTagAge_FUNC) ( GameDll + 0x1F6CF0 );
      MH_CreateHook(SetTextTagAge_org, &SetTextTagAge_my, reinterpret_cast<void**>(&SetTextTagAge_ptr));
      MH_EnableHook(SetTextTagAge_org);
}
void SetTextTagColor_init ( )
{
      SetTextTagColor_org = (SetTextTagColor_FUNC) ( GameDll + 0x1F6D30 );
      MH_CreateHook(SetTextTagColor_org, &SetTextTagColor_my, reinterpret_cast<void**>(&SetTextTagColor_ptr));
      MH_EnableHook(SetTextTagColor_org);
}
void SetTextTagFadepoint_init ( )
{
      SetTextTagFadepoint_org = (SetTextTagFadepoint_FUNC) ( GameDll + 0x1F6D80 );
      MH_CreateHook(SetTextTagFadepoint_org, &SetTextTagFadepoint_my, reinterpret_cast<void**>(&SetTextTagFadepoint_ptr));
      MH_EnableHook(SetTextTagFadepoint_org);
}
void SetTextTagLifespan_init ( )
{
      SetTextTagLifespan_org = (SetTextTagLifespan_FUNC) ( GameDll + 0x1F6DC0 );
      MH_CreateHook(SetTextTagLifespan_org, &SetTextTagLifespan_my, reinterpret_cast<void**>(&SetTextTagLifespan_ptr));
      MH_EnableHook(SetTextTagLifespan_org);
}
void SetTextTagPermanent_init ( )
{
      SetTextTagPermanent_org = (SetTextTagPermanent_FUNC) ( GameDll + 0x1F6E00 );
      MH_CreateHook(SetTextTagPermanent_org, &SetTextTagPermanent_my, reinterpret_cast<void**>(&SetTextTagPermanent_ptr));
      MH_EnableHook(SetTextTagPermanent_org);
}
void SetTextTagPos_init ( )
{
      SetTextTagPos_org = (SetTextTagPos_FUNC) ( GameDll + 0x1F6E30 );
      MH_CreateHook(SetTextTagPos_org, &SetTextTagPos_my, reinterpret_cast<void**>(&SetTextTagPos_ptr));
      MH_EnableHook(SetTextTagPos_org);
}
void SetTextTagPosUnit_init ( )
{
      SetTextTagPosUnit_org = (SetTextTagPosUnit_FUNC) ( GameDll + 0x1F6ED0 );
      MH_CreateHook(SetTextTagPosUnit_org, &SetTextTagPosUnit_my, reinterpret_cast<void**>(&SetTextTagPosUnit_ptr));
      MH_EnableHook(SetTextTagPosUnit_org);
}
void SetTextTagSuspended_init ( )
{
      SetTextTagSuspended_org = (SetTextTagSuspended_FUNC) ( GameDll + 0x1F6F40 );
      MH_CreateHook(SetTextTagSuspended_org, &SetTextTagSuspended_my, reinterpret_cast<void**>(&SetTextTagSuspended_ptr));
      MH_EnableHook(SetTextTagSuspended_org);
}
void SetTextTagText_init ( )
{
      SetTextTagText_org = (SetTextTagText_FUNC) ( GameDll + 0x1F6F70 );
      MH_CreateHook(SetTextTagText_org, &SetTextTagText_my, reinterpret_cast<void**>(&SetTextTagText_ptr));
      MH_EnableHook(SetTextTagText_org);
}
void SetTextTagVelocity_init ( )
{
      SetTextTagVelocity_org = (SetTextTagVelocity_FUNC) ( GameDll + 0x1F6FC0 );
      MH_CreateHook(SetTextTagVelocity_org, &SetTextTagVelocity_my, reinterpret_cast<void**>(&SetTextTagVelocity_ptr));
      MH_EnableHook(SetTextTagVelocity_org);
}
void SetTextTagVisibility_init ( )
{
      SetTextTagVisibility_org = (SetTextTagVisibility_FUNC) ( GameDll + 0x1F7020 );
      MH_CreateHook(SetTextTagVisibility_org, &SetTextTagVisibility_my, reinterpret_cast<void**>(&SetTextTagVisibility_ptr));
      MH_EnableHook(SetTextTagVisibility_org);
}
void SetThematicMusicPlayPosition_init ( )
{
      SetThematicMusicPlayPosition_org = (SetThematicMusicPlayPosition_FUNC) ( GameDll + 0x1F7050 );
      MH_CreateHook(SetThematicMusicPlayPosition_org, &SetThematicMusicPlayPosition_my, reinterpret_cast<void**>(&SetThematicMusicPlayPosition_ptr));
      MH_EnableHook(SetThematicMusicPlayPosition_org);
}
void SetTimeOfDayScale_init ( )
{
      SetTimeOfDayScale_org = (SetTimeOfDayScale_FUNC) ( GameDll + 0x1F7060 );
      MH_CreateHook(SetTimeOfDayScale_org, &SetTimeOfDayScale_my, reinterpret_cast<void**>(&SetTimeOfDayScale_ptr));
      MH_EnableHook(SetTimeOfDayScale_org);
}
void SetTutorialCleared_init ( )
{
      SetTutorialCleared_org = (SetTutorialCleared_FUNC) ( GameDll + 0x1F70D0 );
      MH_CreateHook(SetTutorialCleared_org, &SetTutorialCleared_my, reinterpret_cast<void**>(&SetTutorialCleared_ptr));
      MH_EnableHook(SetTutorialCleared_org);
}
void SetUbersplatRender_init ( )
{
      SetUbersplatRender_org = (SetUbersplatRender_FUNC) ( GameDll + 0x1F7100 );
      MH_CreateHook(SetUbersplatRender_org, &SetUbersplatRender_my, reinterpret_cast<void**>(&SetUbersplatRender_ptr));
      MH_EnableHook(SetUbersplatRender_org);
}
void SetUbersplatRenderAlways_init ( )
{
      SetUbersplatRenderAlways_org = (SetUbersplatRenderAlways_FUNC) ( GameDll + 0x1F7120 );
      MH_CreateHook(SetUbersplatRenderAlways_org, &SetUbersplatRenderAlways_my, reinterpret_cast<void**>(&SetUbersplatRenderAlways_ptr));
      MH_EnableHook(SetUbersplatRenderAlways_org);
}
void SetUnitAbilityLevel_init ( )
{
      SetUnitAbilityLevel_org = (SetUnitAbilityLevel_FUNC) ( GameDll + 0x1F7140 );
      MH_CreateHook(SetUnitAbilityLevel_org, &SetUnitAbilityLevel_my, reinterpret_cast<void**>(&SetUnitAbilityLevel_ptr));
      MH_EnableHook(SetUnitAbilityLevel_org);
}
void SetUnitAcquireRange_init ( )
{
      SetUnitAcquireRange_org = (SetUnitAcquireRange_FUNC) ( GameDll + 0x1F7210 );
      MH_CreateHook(SetUnitAcquireRange_org, &SetUnitAcquireRange_my, reinterpret_cast<void**>(&SetUnitAcquireRange_ptr));
      MH_EnableHook(SetUnitAcquireRange_org);
}
void SetUnitAnimation_init ( )
{
      SetUnitAnimation_org = (SetUnitAnimation_FUNC) ( GameDll + 0x1F7230 );
      MH_CreateHook(SetUnitAnimation_org, &SetUnitAnimation_my, reinterpret_cast<void**>(&SetUnitAnimation_ptr));
      MH_EnableHook(SetUnitAnimation_org);
}
void SetUnitAnimationByIndex_init ( )
{
      SetUnitAnimationByIndex_org = (SetUnitAnimationByIndex_FUNC) ( GameDll + 0x1F7250 );
      MH_CreateHook(SetUnitAnimationByIndex_org, &SetUnitAnimationByIndex_my, reinterpret_cast<void**>(&SetUnitAnimationByIndex_ptr));
      MH_EnableHook(SetUnitAnimationByIndex_org);
}
void SetUnitAnimationWithRarity_init ( )
{
      SetUnitAnimationWithRarity_org = (SetUnitAnimationWithRarity_FUNC) ( GameDll + 0x1F73C0 );
      MH_CreateHook(SetUnitAnimationWithRarity_org, &SetUnitAnimationWithRarity_my, reinterpret_cast<void**>(&SetUnitAnimationWithRarity_ptr));
      MH_EnableHook(SetUnitAnimationWithRarity_org);
}
void SetUnitBlendTime_init ( )
{
      SetUnitBlendTime_org = (SetUnitBlendTime_FUNC) ( GameDll + 0x1F73E0 );
      MH_CreateHook(SetUnitBlendTime_org, &SetUnitBlendTime_my, reinterpret_cast<void**>(&SetUnitBlendTime_ptr));
      MH_EnableHook(SetUnitBlendTime_org);
}
void SetUnitColor_init ( )
{
      SetUnitColor_org = (SetUnitColor_FUNC) ( GameDll + 0x1F7410 );
      MH_CreateHook(SetUnitColor_org, &SetUnitColor_my, reinterpret_cast<void**>(&SetUnitColor_ptr));
      MH_EnableHook(SetUnitColor_org);
}
void SetUnitCreepGuard_init ( )
{
      SetUnitCreepGuard_org = (SetUnitCreepGuard_FUNC) ( GameDll + 0x1F7450 );
      MH_CreateHook(SetUnitCreepGuard_org, &SetUnitCreepGuard_my, reinterpret_cast<void**>(&SetUnitCreepGuard_ptr));
      MH_EnableHook(SetUnitCreepGuard_org);
}
void SetUnitExploded_init ( )
{
      SetUnitExploded_org = (SetUnitExploded_FUNC) ( GameDll + 0x1F7480 );
      MH_CreateHook(SetUnitExploded_org, &SetUnitExploded_my, reinterpret_cast<void**>(&SetUnitExploded_ptr));
      MH_EnableHook(SetUnitExploded_org);
}
void SetUnitFacing_init ( )
{
      SetUnitFacing_org = (SetUnitFacing_FUNC) ( GameDll + 0x1F74E0 );
      MH_CreateHook(SetUnitFacing_org, &SetUnitFacing_my, reinterpret_cast<void**>(&SetUnitFacing_ptr));
      MH_EnableHook(SetUnitFacing_org);
}
void SetUnitFacingTimed_init ( )
{
      SetUnitFacingTimed_org = (SetUnitFacingTimed_FUNC) ( GameDll + 0x1F7520 );
      MH_CreateHook(SetUnitFacingTimed_org, &SetUnitFacingTimed_my, reinterpret_cast<void**>(&SetUnitFacingTimed_ptr));
      MH_EnableHook(SetUnitFacingTimed_org);
}
void SetUnitFlyHeight_init ( )
{
      SetUnitFlyHeight_org = (SetUnitFlyHeight_FUNC) ( GameDll + 0x1F7630 );
      MH_CreateHook(SetUnitFlyHeight_org, &SetUnitFlyHeight_my, reinterpret_cast<void**>(&SetUnitFlyHeight_ptr));
      MH_EnableHook(SetUnitFlyHeight_org);
}
void SetUnitFog_init ( )
{
      SetUnitFog_org = (SetUnitFog_FUNC) ( GameDll + 0x1F7680 );
      MH_CreateHook(SetUnitFog_org, &SetUnitFog_my, reinterpret_cast<void**>(&SetUnitFog_ptr));
      MH_EnableHook(SetUnitFog_org);
}
void SetUnitInvulnerable_init ( )
{
      SetUnitInvulnerable_org = (SetUnitInvulnerable_FUNC) ( GameDll + 0x1F7690 );
      MH_CreateHook(SetUnitInvulnerable_org, &SetUnitInvulnerable_my, reinterpret_cast<void**>(&SetUnitInvulnerable_ptr));
      MH_EnableHook(SetUnitInvulnerable_org);
}
void SetUnitLookAt_init ( )
{
      SetUnitLookAt_org = (SetUnitLookAt_FUNC) ( GameDll + 0x1F76E0 );
      MH_CreateHook(SetUnitLookAt_org, &SetUnitLookAt_my, reinterpret_cast<void**>(&SetUnitLookAt_ptr));
      MH_EnableHook(SetUnitLookAt_org);
}
void SetUnitMoveSpeed_init ( )
{
      SetUnitMoveSpeed_org = (SetUnitMoveSpeed_FUNC) ( GameDll + 0x1F7850 );
      MH_CreateHook(SetUnitMoveSpeed_org, &SetUnitMoveSpeed_my, reinterpret_cast<void**>(&SetUnitMoveSpeed_ptr));
      MH_EnableHook(SetUnitMoveSpeed_org);
}
void SetUnitOwner_init ( )
{
      SetUnitOwner_org = (SetUnitOwner_FUNC) ( GameDll + 0x1F7870 );
      MH_CreateHook(SetUnitOwner_org, &SetUnitOwner_my, reinterpret_cast<void**>(&SetUnitOwner_ptr));
      MH_EnableHook(SetUnitOwner_org);
}
void SetUnitPathing_init ( )
{
      SetUnitPathing_org = (SetUnitPathing_FUNC) ( GameDll + 0x1F78B0 );
      MH_CreateHook(SetUnitPathing_org, &SetUnitPathing_my, reinterpret_cast<void**>(&SetUnitPathing_ptr));
      MH_EnableHook(SetUnitPathing_org);
}
void SetUnitPosition_init ( )
{
      SetUnitPosition_org = (SetUnitPosition_FUNC) ( GameDll + 0x1F7930 );
      MH_CreateHook(SetUnitPosition_org, &SetUnitPosition_my, reinterpret_cast<void**>(&SetUnitPosition_ptr));
      MH_EnableHook(SetUnitPosition_org);
}
void SetUnitPositionLoc_init ( )
{
      SetUnitPositionLoc_org = (SetUnitPositionLoc_FUNC) ( GameDll + 0x1F7990 );
      MH_CreateHook(SetUnitPositionLoc_org, &SetUnitPositionLoc_my, reinterpret_cast<void**>(&SetUnitPositionLoc_ptr));
      MH_EnableHook(SetUnitPositionLoc_org);
}
void SetUnitPropWindow_init ( )
{
      SetUnitPropWindow_org = (SetUnitPropWindow_FUNC) ( GameDll + 0x1F79D0 );
      MH_CreateHook(SetUnitPropWindow_org, &SetUnitPropWindow_my, reinterpret_cast<void**>(&SetUnitPropWindow_ptr));
      MH_EnableHook(SetUnitPropWindow_org);
}
void SetUnitRescuable_init ( )
{
      SetUnitRescuable_org = (SetUnitRescuable_FUNC) ( GameDll + 0x1F79F0 );
      MH_CreateHook(SetUnitRescuable_org, &SetUnitRescuable_my, reinterpret_cast<void**>(&SetUnitRescuable_ptr));
      MH_EnableHook(SetUnitRescuable_org);
}
void SetUnitRescueRange_init ( )
{
      SetUnitRescueRange_org = (SetUnitRescueRange_FUNC) ( GameDll + 0x1F7A20 );
      MH_CreateHook(SetUnitRescueRange_org, &SetUnitRescueRange_my, reinterpret_cast<void**>(&SetUnitRescueRange_ptr));
      MH_EnableHook(SetUnitRescueRange_org);
}
void SetUnitScale_init ( )
{
      SetUnitScale_org = (SetUnitScale_FUNC) ( GameDll + 0x1F7A40 );
      MH_CreateHook(SetUnitScale_org, &SetUnitScale_my, reinterpret_cast<void**>(&SetUnitScale_ptr));
      MH_EnableHook(SetUnitScale_org);
}
void SetUnitState_init ( )
{
      SetUnitState_org = (SetUnitState_FUNC) ( GameDll + 0x1F7A80 );
      MH_CreateHook(SetUnitState_org, &SetUnitState_my, reinterpret_cast<void**>(&SetUnitState_ptr));
      MH_EnableHook(SetUnitState_org);
}
void SetUnitTimeScale_init ( )
{
      SetUnitTimeScale_org = (SetUnitTimeScale_FUNC) ( GameDll + 0x1F7AB0 );
      MH_CreateHook(SetUnitTimeScale_org, &SetUnitTimeScale_my, reinterpret_cast<void**>(&SetUnitTimeScale_ptr));
      MH_EnableHook(SetUnitTimeScale_org);
}
void SetUnitTurnSpeed_init ( )
{
      SetUnitTurnSpeed_org = (SetUnitTurnSpeed_FUNC) ( GameDll + 0x1F7AE0 );
      MH_CreateHook(SetUnitTurnSpeed_org, &SetUnitTurnSpeed_my, reinterpret_cast<void**>(&SetUnitTurnSpeed_ptr));
      MH_EnableHook(SetUnitTurnSpeed_org);
}
void SetUnitTypeSlots_init ( )
{
      SetUnitTypeSlots_org = (SetUnitTypeSlots_FUNC) ( GameDll + 0x1F7B00 );
      MH_CreateHook(SetUnitTypeSlots_org, &SetUnitTypeSlots_my, reinterpret_cast<void**>(&SetUnitTypeSlots_ptr));
      MH_EnableHook(SetUnitTypeSlots_org);
}
void SetUnitUseFood_init ( )
{
      SetUnitUseFood_org = (SetUnitUseFood_FUNC) ( GameDll + 0x1F7B40 );
      MH_CreateHook(SetUnitUseFood_org, &SetUnitUseFood_my, reinterpret_cast<void**>(&SetUnitUseFood_ptr));
      MH_EnableHook(SetUnitUseFood_org);
}
void SetUnitUserData_init ( )
{
      SetUnitUserData_org = (SetUnitUserData_FUNC) ( GameDll + 0x1F7BB0 );
      MH_CreateHook(SetUnitUserData_org, &SetUnitUserData_my, reinterpret_cast<void**>(&SetUnitUserData_ptr));
      MH_EnableHook(SetUnitUserData_org);
}
void SetUnitVertexColor_init ( )
{
      SetUnitVertexColor_org = (SetUnitVertexColor_FUNC) ( GameDll + 0x1F7BD0 );
      MH_CreateHook(SetUnitVertexColor_org, &SetUnitVertexColor_my, reinterpret_cast<void**>(&SetUnitVertexColor_ptr));
      MH_EnableHook(SetUnitVertexColor_org);
}
void SetUnitX_init ( )
{
      SetUnitX_org = (SetUnitX_FUNC) ( GameDll + 0x1F7C70 );
      MH_CreateHook(SetUnitX_org, &SetUnitX_my, reinterpret_cast<void**>(&SetUnitX_ptr));
      MH_EnableHook(SetUnitX_org);
}
void SetUnitY_init ( )
{
      SetUnitY_org = (SetUnitY_FUNC) ( GameDll + 0x1F7CD0 );
      MH_CreateHook(SetUnitY_org, &SetUnitY_my, reinterpret_cast<void**>(&SetUnitY_ptr));
      MH_EnableHook(SetUnitY_org);
}
void SetUnitsFlee_init ( )
{
      SetUnitsFlee_org = (SetUnitsFlee_FUNC) ( GameDll + 0x894C70 );
      MH_CreateHook(SetUnitsFlee_org, &SetUnitsFlee_my, reinterpret_cast<void**>(&SetUnitsFlee_ptr));
      MH_EnableHook(SetUnitsFlee_org);
}
void SetUpgrade_init ( )
{
      SetUpgrade_org = (SetUpgrade_FUNC) ( GameDll + 0x894CD0 );
      MH_CreateHook(SetUpgrade_org, &SetUpgrade_my, reinterpret_cast<void**>(&SetUpgrade_ptr));
      MH_EnableHook(SetUpgrade_org);
}
void SetWatchMegaTargets_init ( )
{
      SetWatchMegaTargets_org = (SetWatchMegaTargets_FUNC) ( GameDll + 0x894D10 );
      MH_CreateHook(SetWatchMegaTargets_org, &SetWatchMegaTargets_my, reinterpret_cast<void**>(&SetWatchMegaTargets_ptr));
      MH_EnableHook(SetWatchMegaTargets_org);
}
void SetWaterBaseColor_init ( )
{
      SetWaterBaseColor_org = (SetWaterBaseColor_FUNC) ( GameDll + 0x1F7D60 );
      MH_CreateHook(SetWaterBaseColor_org, &SetWaterBaseColor_my, reinterpret_cast<void**>(&SetWaterBaseColor_ptr));
      MH_EnableHook(SetWaterBaseColor_org);
}
void SetWaterDeforms_init ( )
{
      SetWaterDeforms_org = (SetWaterDeforms_FUNC) ( GameDll + 0x1F7DA0 );
      MH_CreateHook(SetWaterDeforms_org, &SetWaterDeforms_my, reinterpret_cast<void**>(&SetWaterDeforms_ptr));
      MH_EnableHook(SetWaterDeforms_org);
}
void SetWidgetLife_init ( )
{
      SetWidgetLife_org = (SetWidgetLife_FUNC) ( GameDll + 0x1F7DB0 );
      MH_CreateHook(SetWidgetLife_org, &SetWidgetLife_my, reinterpret_cast<void**>(&SetWidgetLife_ptr));
      MH_EnableHook(SetWidgetLife_org);
}
void ShiftTownSpot_init ( )
{
      ShiftTownSpot_org = (ShiftTownSpot_FUNC) ( GameDll + 0x894FB0 );
      MH_CreateHook(ShiftTownSpot_org, &ShiftTownSpot_my, reinterpret_cast<void**>(&ShiftTownSpot_ptr));
      MH_EnableHook(ShiftTownSpot_org);
}
void ShowDestructable_init ( )
{
      ShowDestructable_org = (ShowDestructable_FUNC) ( GameDll + 0x1F7DD0 );
      MH_CreateHook(ShowDestructable_org, &ShowDestructable_my, reinterpret_cast<void**>(&ShowDestructable_ptr));
      MH_EnableHook(ShowDestructable_org);
}
void ShowImage_init ( )
{
      ShowImage_org = (ShowImage_FUNC) ( GameDll + 0x1F7E00 );
      MH_CreateHook(ShowImage_org, &ShowImage_my, reinterpret_cast<void**>(&ShowImage_ptr));
      MH_EnableHook(ShowImage_org);
}
void ShowInterface_init ( )
{
      ShowInterface_org = (ShowInterface_FUNC) ( GameDll + 0x1F7E20 );
      MH_CreateHook(ShowInterface_org, &ShowInterface_my, reinterpret_cast<void**>(&ShowInterface_ptr));
      MH_EnableHook(ShowInterface_org);
}
void ShowUbersplat_init ( )
{
      ShowUbersplat_org = (ShowUbersplat_FUNC) ( GameDll + 0x1F7E50 );
      MH_CreateHook(ShowUbersplat_org, &ShowUbersplat_my, reinterpret_cast<void**>(&ShowUbersplat_ptr));
      MH_EnableHook(ShowUbersplat_org);
}
void ShowUnit_init ( )
{
      ShowUnit_org = (ShowUnit_FUNC) ( GameDll + 0x1F7E70 );
      MH_CreateHook(ShowUnit_org, &ShowUnit_my, reinterpret_cast<void**>(&ShowUnit_ptr));
      MH_EnableHook(ShowUnit_org);
}
void Sin_init ( )
{
      Sin_org = (Sin_FUNC) ( GameDll + 0x1F8070 );
      MH_CreateHook(Sin_org, &Sin_my, reinterpret_cast<void**>(&Sin_ptr));
      MH_EnableHook(Sin_org);
}
void Sleep_init ( )
{
      Sleep_org = (Sleep_FUNC) ( GameDll + 0x894FF0 );
      MH_CreateHook(Sleep_org, &Sleep_my, reinterpret_cast<void**>(&Sleep_ptr));
      MH_EnableHook(Sleep_org);
}
void SquareRoot_init ( )
{
      SquareRoot_org = (SquareRoot_FUNC) ( GameDll + 0x1F80A0 );
      MH_CreateHook(SquareRoot_org, &SquareRoot_my, reinterpret_cast<void**>(&SquareRoot_ptr));
      MH_EnableHook(SquareRoot_org);
}
void StartCampaignAI_init ( )
{
      StartCampaignAI_org = (StartCampaignAI_FUNC) ( GameDll + 0x1F8100 );
      MH_CreateHook(StartCampaignAI_org, &StartCampaignAI_my, reinterpret_cast<void**>(&StartCampaignAI_ptr));
      MH_EnableHook(StartCampaignAI_org);
}
void StartGetEnemyBase_init ( )
{
      StartGetEnemyBase_org = (StartGetEnemyBase_FUNC) ( GameDll + 0x895080 );
      MH_CreateHook(StartGetEnemyBase_org, &StartGetEnemyBase_my, reinterpret_cast<void**>(&StartGetEnemyBase_ptr));
      MH_EnableHook(StartGetEnemyBase_org);
}
void StartMeleeAI_init ( )
{
      StartMeleeAI_org = (StartMeleeAI_FUNC) ( GameDll + 0x1F8150 );
      MH_CreateHook(StartMeleeAI_org, &StartMeleeAI_my, reinterpret_cast<void**>(&StartMeleeAI_ptr));
      MH_EnableHook(StartMeleeAI_org);
}
void StartSound_init ( )
{
      StartSound_org = (StartSound_FUNC) ( GameDll + 0x1F8180 );
      MH_CreateHook(StartSound_org, &StartSound_my, reinterpret_cast<void**>(&StartSound_ptr));
      MH_EnableHook(StartSound_org);
}
void StartThread_init ( )
{
      StartThread_org = (StartThread_FUNC) ( GameDll + 0x8950B0 );
      MH_CreateHook(StartThread_org, &StartThread_my, reinterpret_cast<void**>(&StartThread_ptr));
      MH_EnableHook(StartThread_org);
}
void StopCamera_init ( )
{
      StopCamera_org = (StopCamera_FUNC) ( GameDll + 0x1F81D0 );
      MH_CreateHook(StopCamera_org, &StopCamera_my, reinterpret_cast<void**>(&StopCamera_ptr));
      MH_EnableHook(StopCamera_org);
}
void StopGathering_init ( )
{
      StopGathering_org = (StopGathering_FUNC) ( GameDll + 0x8951A0 );
      MH_CreateHook(StopGathering_org, &StopGathering_my, reinterpret_cast<void**>(&StopGathering_ptr));
      MH_EnableHook(StopGathering_org);
}
void StopMusic_init ( )
{
      StopMusic_org = (StopMusic_FUNC) ( GameDll + 0x1F81F0 );
      MH_CreateHook(StopMusic_org, &StopMusic_my, reinterpret_cast<void**>(&StopMusic_ptr));
      MH_EnableHook(StopMusic_org);
}
void StopSound_init ( )
{
      StopSound_org = (StopSound_FUNC) ( GameDll + 0x1F8200 );
      MH_CreateHook(StopSound_org, &StopSound_my, reinterpret_cast<void**>(&StopSound_ptr));
      MH_EnableHook(StopSound_org);
}
void StoreBoolean_init ( )
{
      StoreBoolean_org = (StoreBoolean_FUNC) ( GameDll + 0x1F8220 );
      MH_CreateHook(StoreBoolean_org, &StoreBoolean_my, reinterpret_cast<void**>(&StoreBoolean_ptr));
      MH_EnableHook(StoreBoolean_org);
}
void StoreInteger_init ( )
{
      StoreInteger_org = (StoreInteger_FUNC) ( GameDll + 0x1F8280 );
      MH_CreateHook(StoreInteger_org, &StoreInteger_my, reinterpret_cast<void**>(&StoreInteger_ptr));
      MH_EnableHook(StoreInteger_org);
}
void StoreReal_init ( )
{
      StoreReal_org = (StoreReal_FUNC) ( GameDll + 0x1F82D0 );
      MH_CreateHook(StoreReal_org, &StoreReal_my, reinterpret_cast<void**>(&StoreReal_ptr));
      MH_EnableHook(StoreReal_org);
}
void StoreString_init ( )
{
      StoreString_org = (StoreString_FUNC) ( GameDll + 0x1F8320 );
      MH_CreateHook(StoreString_org, &StoreString_my, reinterpret_cast<void**>(&StoreString_ptr));
      MH_EnableHook(StoreString_org);
}
void StoreUnit_init ( )
{
      StoreUnit_org = (StoreUnit_FUNC) ( GameDll + 0x1F8380 );
      MH_CreateHook(StoreUnit_org, &StoreUnit_my, reinterpret_cast<void**>(&StoreUnit_ptr));
      MH_EnableHook(StoreUnit_org);
}
void StringCase_init ( )
{
      StringCase_org = (StringCase_FUNC) ( GameDll + 0x1F83E0 );
      MH_CreateHook(StringCase_org, &StringCase_my, reinterpret_cast<void**>(&StringCase_ptr));
      MH_EnableHook(StringCase_org);
}
void StringHash_init ( )
{
      StringHash_org = (StringHash_FUNC) ( GameDll + 0x1F8470 );
      MH_CreateHook(StringHash_org, &StringHash_my, reinterpret_cast<void**>(&StringHash_ptr));
      MH_EnableHook(StringHash_org);
}
void StringLength_init ( )
{
      StringLength_org = (StringLength_FUNC) ( GameDll + 0x1F8490 );
      MH_CreateHook(StringLength_org, &StringLength_my, reinterpret_cast<void**>(&StringLength_ptr));
      MH_EnableHook(StringLength_org);
}
void SubString_init ( )
{
      SubString_org = (SubString_FUNC) ( GameDll + 0x1F8770 );
      MH_CreateHook(SubString_org, &SubString_my, reinterpret_cast<void**>(&SubString_ptr));
      MH_EnableHook(SubString_org);
}
void SuicidePlayer_init ( )
{
      SuicidePlayer_org = (SuicidePlayer_FUNC) ( GameDll + 0x8951D0 );
      MH_CreateHook(SuicidePlayer_org, &SuicidePlayer_my, reinterpret_cast<void**>(&SuicidePlayer_ptr));
      MH_EnableHook(SuicidePlayer_org);
}
void SuicidePlayerUnits_init ( )
{
      SuicidePlayerUnits_org = (SuicidePlayerUnits_FUNC) ( GameDll + 0x895260 );
      MH_CreateHook(SuicidePlayerUnits_org, &SuicidePlayerUnits_my, reinterpret_cast<void**>(&SuicidePlayerUnits_ptr));
      MH_EnableHook(SuicidePlayerUnits_org);
}
void SuicideUnit_init ( )
{
      SuicideUnit_org = (SuicideUnit_FUNC) ( GameDll + 0x8952F0 );
      MH_CreateHook(SuicideUnit_org, &SuicideUnit_my, reinterpret_cast<void**>(&SuicideUnit_ptr));
      MH_EnableHook(SuicideUnit_org);
}
void SuicideUnitEx_init ( )
{
      SuicideUnitEx_org = (SuicideUnitEx_FUNC) ( GameDll + 0x895340 );
      MH_CreateHook(SuicideUnitEx_org, &SuicideUnitEx_my, reinterpret_cast<void**>(&SuicideUnitEx_ptr));
      MH_EnableHook(SuicideUnitEx_org);
}
void SuspendHeroXP_init ( )
{
      SuspendHeroXP_org = (SuspendHeroXP_FUNC) ( GameDll + 0x1F8810 );
      MH_CreateHook(SuspendHeroXP_org, &SuspendHeroXP_my, reinterpret_cast<void**>(&SuspendHeroXP_ptr));
      MH_EnableHook(SuspendHeroXP_org);
}
void SuspendTimeOfDay_init ( )
{
      SuspendTimeOfDay_org = (SuspendTimeOfDay_FUNC) ( GameDll + 0x1F8870 );
      MH_CreateHook(SuspendTimeOfDay_org, &SuspendTimeOfDay_my, reinterpret_cast<void**>(&SuspendTimeOfDay_ptr));
      MH_EnableHook(SuspendTimeOfDay_org);
}
void SyncSelections_init ( )
{
      SyncSelections_org = (SyncSelections_FUNC) ( GameDll + 0x1F88A0 );
      MH_CreateHook(SyncSelections_org, &SyncSelections_my, reinterpret_cast<void**>(&SyncSelections_ptr));
      MH_EnableHook(SyncSelections_org);
}
void SyncStoredBoolean_init ( )
{
      SyncStoredBoolean_org = (SyncStoredBoolean_FUNC) ( GameDll + 0x1F88E0 );
      MH_CreateHook(SyncStoredBoolean_org, &SyncStoredBoolean_my, reinterpret_cast<void**>(&SyncStoredBoolean_ptr));
      MH_EnableHook(SyncStoredBoolean_org);
}
void SyncStoredInteger_init ( )
{
      SyncStoredInteger_org = (SyncStoredInteger_FUNC) ( GameDll + 0x1F8940 );
      MH_CreateHook(SyncStoredInteger_org, &SyncStoredInteger_my, reinterpret_cast<void**>(&SyncStoredInteger_ptr));
      MH_EnableHook(SyncStoredInteger_org);
}
void SyncStoredReal_init ( )
{
      SyncStoredReal_org = (SyncStoredReal_FUNC) ( GameDll + 0x1F89A0 );
      MH_CreateHook(SyncStoredReal_org, &SyncStoredReal_my, reinterpret_cast<void**>(&SyncStoredReal_ptr));
      MH_EnableHook(SyncStoredReal_org);
}
void SyncStoredString_init ( )
{
      SyncStoredString_org = (SyncStoredString_FUNC) ( GameDll + 0x1F8A00 );
      MH_CreateHook(SyncStoredString_org, &SyncStoredString_my, reinterpret_cast<void**>(&SyncStoredString_ptr));
      MH_EnableHook(SyncStoredString_org);
}
void SyncStoredUnit_init ( )
{
      SyncStoredUnit_org = (SyncStoredUnit_FUNC) ( GameDll + 0x1F8A60 );
      MH_CreateHook(SyncStoredUnit_org, &SyncStoredUnit_my, reinterpret_cast<void**>(&SyncStoredUnit_ptr));
      MH_EnableHook(SyncStoredUnit_org);
}
void Tan_init ( )
{
      Tan_org = (Tan_FUNC) ( GameDll + 0x1F8AC0 );
      MH_CreateHook(Tan_org, &Tan_my, reinterpret_cast<void**>(&Tan_ptr));
      MH_EnableHook(Tan_org);
}
void TeleportCaptain_init ( )
{
      TeleportCaptain_org = (TeleportCaptain_FUNC) ( GameDll + 0x895390 );
      MH_CreateHook(TeleportCaptain_org, &TeleportCaptain_my, reinterpret_cast<void**>(&TeleportCaptain_ptr));
      MH_EnableHook(TeleportCaptain_org);
}
void TerrainDeformCrater_init ( )
{
      TerrainDeformCrater_org = (TerrainDeformCrater_FUNC) ( GameDll + 0x1F8B00 );
      MH_CreateHook(TerrainDeformCrater_org, &TerrainDeformCrater_my, reinterpret_cast<void**>(&TerrainDeformCrater_ptr));
      MH_EnableHook(TerrainDeformCrater_org);
}
void TerrainDeformRandom_init ( )
{
      TerrainDeformRandom_org = (TerrainDeformRandom_FUNC) ( GameDll + 0x1F8B60 );
      MH_CreateHook(TerrainDeformRandom_org, &TerrainDeformRandom_my, reinterpret_cast<void**>(&TerrainDeformRandom_ptr));
      MH_EnableHook(TerrainDeformRandom_org);
}
void TerrainDeformRipple_init ( )
{
      TerrainDeformRipple_org = (TerrainDeformRipple_FUNC) ( GameDll + 0x1F8BC0 );
      MH_CreateHook(TerrainDeformRipple_org, &TerrainDeformRipple_my, reinterpret_cast<void**>(&TerrainDeformRipple_ptr));
      MH_EnableHook(TerrainDeformRipple_org);
}
void TerrainDeformStop_init ( )
{
      TerrainDeformStop_org = (TerrainDeformStop_FUNC) ( GameDll + 0x1F8C40 );
      MH_CreateHook(TerrainDeformStop_org, &TerrainDeformStop_my, reinterpret_cast<void**>(&TerrainDeformStop_ptr));
      MH_EnableHook(TerrainDeformStop_org);
}
void TerrainDeformStopAll_init ( )
{
      TerrainDeformStopAll_org = (TerrainDeformStopAll_FUNC) ( GameDll + 0x1F8C50 );
      MH_CreateHook(TerrainDeformStopAll_org, &TerrainDeformStopAll_my, reinterpret_cast<void**>(&TerrainDeformStopAll_ptr));
      MH_EnableHook(TerrainDeformStopAll_org);
}
void TerrainDeformWave_init ( )
{
      TerrainDeformWave_org = (TerrainDeformWave_FUNC) ( GameDll + 0x1F8C60 );
      MH_CreateHook(TerrainDeformWave_org, &TerrainDeformWave_my, reinterpret_cast<void**>(&TerrainDeformWave_ptr));
      MH_EnableHook(TerrainDeformWave_org);
}
void TimerDialogDisplay_init ( )
{
      TimerDialogDisplay_org = (TimerDialogDisplay_FUNC) ( GameDll + 0x1F8DE0 );
      MH_CreateHook(TimerDialogDisplay_org, &TimerDialogDisplay_my, reinterpret_cast<void**>(&TimerDialogDisplay_ptr));
      MH_EnableHook(TimerDialogDisplay_org);
}
void TimerDialogSetRealTimeRemaining_init ( )
{
      TimerDialogSetRealTimeRemaining_org = (TimerDialogSetRealTimeRemaining_FUNC) ( GameDll + 0x1F8E00 );
      MH_CreateHook(TimerDialogSetRealTimeRemaining_org, &TimerDialogSetRealTimeRemaining_my, reinterpret_cast<void**>(&TimerDialogSetRealTimeRemaining_ptr));
      MH_EnableHook(TimerDialogSetRealTimeRemaining_org);
}
void TimerDialogSetSpeed_init ( )
{
      TimerDialogSetSpeed_org = (TimerDialogSetSpeed_FUNC) ( GameDll + 0x1F8E30 );
      MH_CreateHook(TimerDialogSetSpeed_org, &TimerDialogSetSpeed_my, reinterpret_cast<void**>(&TimerDialogSetSpeed_ptr));
      MH_EnableHook(TimerDialogSetSpeed_org);
}
void TimerDialogSetTimeColor_init ( )
{
      TimerDialogSetTimeColor_org = (TimerDialogSetTimeColor_FUNC) ( GameDll + 0x1F8E60 );
      MH_CreateHook(TimerDialogSetTimeColor_org, &TimerDialogSetTimeColor_my, reinterpret_cast<void**>(&TimerDialogSetTimeColor_ptr));
      MH_EnableHook(TimerDialogSetTimeColor_org);
}
void TimerDialogSetTitle_init ( )
{
      TimerDialogSetTitle_org = (TimerDialogSetTitle_FUNC) ( GameDll + 0x1F8EC0 );
      MH_CreateHook(TimerDialogSetTitle_org, &TimerDialogSetTitle_my, reinterpret_cast<void**>(&TimerDialogSetTitle_ptr));
      MH_EnableHook(TimerDialogSetTitle_org);
}
void TimerDialogSetTitleColor_init ( )
{
      TimerDialogSetTitleColor_org = (TimerDialogSetTitleColor_FUNC) ( GameDll + 0x1F8EF0 );
      MH_CreateHook(TimerDialogSetTitleColor_org, &TimerDialogSetTitleColor_my, reinterpret_cast<void**>(&TimerDialogSetTitleColor_ptr));
      MH_EnableHook(TimerDialogSetTitleColor_org);
}
void TimerGetElapsed_init ( )
{
      TimerGetElapsed_org = (TimerGetElapsed_FUNC) ( GameDll + 0x1F8F50 );
      MH_CreateHook(TimerGetElapsed_org, &TimerGetElapsed_my, reinterpret_cast<void**>(&TimerGetElapsed_ptr));
      MH_EnableHook(TimerGetElapsed_org);
}
void TimerGetRemaining_init ( )
{
      TimerGetRemaining_org = (TimerGetRemaining_FUNC) ( GameDll + 0x1F8F80 );
      MH_CreateHook(TimerGetRemaining_org, &TimerGetRemaining_my, reinterpret_cast<void**>(&TimerGetRemaining_ptr));
      MH_EnableHook(TimerGetRemaining_org);
}
void TimerGetTimeout_init ( )
{
      TimerGetTimeout_org = (TimerGetTimeout_FUNC) ( GameDll + 0x1F8FB0 );
      MH_CreateHook(TimerGetTimeout_org, &TimerGetTimeout_my, reinterpret_cast<void**>(&TimerGetTimeout_ptr));
      MH_EnableHook(TimerGetTimeout_org);
}
void TimerStart_init ( )
{
      TimerStart_org = (TimerStart_FUNC) ( GameDll + 0x1F8FE0 );
      MH_CreateHook(TimerStart_org, &TimerStart_my, reinterpret_cast<void**>(&TimerStart_ptr));
      MH_EnableHook(TimerStart_org);
}
void TownHasHall_init ( )
{
      TownHasHall_org = (TownHasHall_FUNC) ( GameDll + 0x895690 );
      MH_CreateHook(TownHasHall_org, &TownHasHall_my, reinterpret_cast<void**>(&TownHasHall_ptr));
      MH_EnableHook(TownHasHall_org);
}
void TownHasMine_init ( )
{
      TownHasMine_org = (TownHasMine_FUNC) ( GameDll + 0x8956D0 );
      MH_CreateHook(TownHasMine_org, &TownHasMine_my, reinterpret_cast<void**>(&TownHasMine_ptr));
      MH_EnableHook(TownHasMine_org);
}
void TownThreatened_init ( )
{
      TownThreatened_org = (TownThreatened_FUNC) ( GameDll + 0x895710 );
      MH_CreateHook(TownThreatened_org, &TownThreatened_my, reinterpret_cast<void**>(&TownThreatened_ptr));
      MH_EnableHook(TownThreatened_org);
}
void TownWithMine_init ( )
{
      TownWithMine_org = (TownWithMine_FUNC) ( GameDll + 0x895760 );
      MH_CreateHook(TownWithMine_org, &TownWithMine_my, reinterpret_cast<void**>(&TownWithMine_ptr));
      MH_EnableHook(TownWithMine_org);
}
void TriggerAddAction_init ( )
{
      TriggerAddAction_org = (TriggerAddAction_FUNC) ( GameDll + 0x1F9010 );
      MH_CreateHook(TriggerAddAction_org, &TriggerAddAction_my, reinterpret_cast<void**>(&TriggerAddAction_ptr));
      MH_EnableHook(TriggerAddAction_org);
}
void TriggerAddCondition_init ( )
{
      TriggerAddCondition_org = (TriggerAddCondition_FUNC) ( GameDll + 0x1F9050 );
      MH_CreateHook(TriggerAddCondition_org, &TriggerAddCondition_my, reinterpret_cast<void**>(&TriggerAddCondition_ptr));
      MH_EnableHook(TriggerAddCondition_org);
}
void TriggerClearActions_init ( )
{
      TriggerClearActions_org = (TriggerClearActions_FUNC) ( GameDll + 0x1F90A0 );
      MH_CreateHook(TriggerClearActions_org, &TriggerClearActions_my, reinterpret_cast<void**>(&TriggerClearActions_ptr));
      MH_EnableHook(TriggerClearActions_org);
}
void TriggerClearConditions_init ( )
{
      TriggerClearConditions_org = (TriggerClearConditions_FUNC) ( GameDll + 0x1F90C0 );
      MH_CreateHook(TriggerClearConditions_org, &TriggerClearConditions_my, reinterpret_cast<void**>(&TriggerClearConditions_ptr));
      MH_EnableHook(TriggerClearConditions_org);
}
void TriggerEvaluate_init ( )
{
      TriggerEvaluate_org = (TriggerEvaluate_FUNC) ( GameDll + 0x1F90E0 );
      MH_CreateHook(TriggerEvaluate_org, &TriggerEvaluate_my, reinterpret_cast<void**>(&TriggerEvaluate_ptr));
      MH_EnableHook(TriggerEvaluate_org);
}
void TriggerExecute_init ( )
{
      TriggerExecute_org = (TriggerExecute_FUNC) ( GameDll + 0x1F9100 );
      MH_CreateHook(TriggerExecute_org, &TriggerExecute_my, reinterpret_cast<void**>(&TriggerExecute_ptr));
      MH_EnableHook(TriggerExecute_org);
}
void TriggerExecuteWait_init ( )
{
      TriggerExecuteWait_org = (TriggerExecuteWait_FUNC) ( GameDll + 0x1F9120 );
      MH_CreateHook(TriggerExecuteWait_org, &TriggerExecuteWait_my, reinterpret_cast<void**>(&TriggerExecuteWait_ptr));
      MH_EnableHook(TriggerExecuteWait_org);
}
void TriggerRegisterDeathEvent_init ( )
{
      TriggerRegisterDeathEvent_org = (TriggerRegisterDeathEvent_FUNC) ( GameDll + 0x1F9140 );
      MH_CreateHook(TriggerRegisterDeathEvent_org, &TriggerRegisterDeathEvent_my, reinterpret_cast<void**>(&TriggerRegisterDeathEvent_ptr));
      MH_EnableHook(TriggerRegisterDeathEvent_org);
}
void TriggerRegisterDialogButtonEvent_init ( )
{
      TriggerRegisterDialogButtonEvent_org = (TriggerRegisterDialogButtonEvent_FUNC) ( GameDll + 0x1F9210 );
      MH_CreateHook(TriggerRegisterDialogButtonEvent_org, &TriggerRegisterDialogButtonEvent_my, reinterpret_cast<void**>(&TriggerRegisterDialogButtonEvent_ptr));
      MH_EnableHook(TriggerRegisterDialogButtonEvent_org);
}
void TriggerRegisterDialogEvent_init ( )
{
      TriggerRegisterDialogEvent_org = (TriggerRegisterDialogEvent_FUNC) ( GameDll + 0x1F92D0 );
      MH_CreateHook(TriggerRegisterDialogEvent_org, &TriggerRegisterDialogEvent_my, reinterpret_cast<void**>(&TriggerRegisterDialogEvent_ptr));
      MH_EnableHook(TriggerRegisterDialogEvent_org);
}
void TriggerRegisterEnterRegion_init ( )
{
      TriggerRegisterEnterRegion_org = (TriggerRegisterEnterRegion_FUNC) ( GameDll + 0x1F9390 );
      MH_CreateHook(TriggerRegisterEnterRegion_org, &TriggerRegisterEnterRegion_my, reinterpret_cast<void**>(&TriggerRegisterEnterRegion_ptr));
      MH_EnableHook(TriggerRegisterEnterRegion_org);
}
void TriggerRegisterFilterUnitEvent_init ( )
{
      TriggerRegisterFilterUnitEvent_org = (TriggerRegisterFilterUnitEvent_FUNC) ( GameDll + 0x1F9470 );
      MH_CreateHook(TriggerRegisterFilterUnitEvent_org, &TriggerRegisterFilterUnitEvent_my, reinterpret_cast<void**>(&TriggerRegisterFilterUnitEvent_ptr));
      MH_EnableHook(TriggerRegisterFilterUnitEvent_org);
}
void TriggerRegisterGameEvent_init ( )
{
      TriggerRegisterGameEvent_org = (TriggerRegisterGameEvent_FUNC) ( GameDll + 0x1F9570 );
      MH_CreateHook(TriggerRegisterGameEvent_org, &TriggerRegisterGameEvent_my, reinterpret_cast<void**>(&TriggerRegisterGameEvent_ptr));
      MH_EnableHook(TriggerRegisterGameEvent_org);
}
void TriggerRegisterGameStateEvent_init ( )
{
      TriggerRegisterGameStateEvent_org = (TriggerRegisterGameStateEvent_FUNC) ( GameDll + 0x1F9650 );
      MH_CreateHook(TriggerRegisterGameStateEvent_org, &TriggerRegisterGameStateEvent_my, reinterpret_cast<void**>(&TriggerRegisterGameStateEvent_ptr));
      MH_EnableHook(TriggerRegisterGameStateEvent_org);
}
void TriggerRegisterLeaveRegion_init ( )
{
      TriggerRegisterLeaveRegion_org = (TriggerRegisterLeaveRegion_FUNC) ( GameDll + 0x1F97A0 );
      MH_CreateHook(TriggerRegisterLeaveRegion_org, &TriggerRegisterLeaveRegion_my, reinterpret_cast<void**>(&TriggerRegisterLeaveRegion_ptr));
      MH_EnableHook(TriggerRegisterLeaveRegion_org);
}
void TriggerRegisterPlayerAllianceChange_init ( )
{
      TriggerRegisterPlayerAllianceChange_org = (TriggerRegisterPlayerAllianceChange_FUNC) ( GameDll + 0x1F9880 );
      MH_CreateHook(TriggerRegisterPlayerAllianceChange_org, &TriggerRegisterPlayerAllianceChange_my, reinterpret_cast<void**>(&TriggerRegisterPlayerAllianceChange_ptr));
      MH_EnableHook(TriggerRegisterPlayerAllianceChange_org);
}
void TriggerRegisterPlayerChatEvent_init ( )
{
      TriggerRegisterPlayerChatEvent_org = (TriggerRegisterPlayerChatEvent_FUNC) ( GameDll + 0x1F9950 );
      MH_CreateHook(TriggerRegisterPlayerChatEvent_org, &TriggerRegisterPlayerChatEvent_my, reinterpret_cast<void**>(&TriggerRegisterPlayerChatEvent_ptr));
      MH_EnableHook(TriggerRegisterPlayerChatEvent_org);
}
void TriggerRegisterPlayerEvent_init ( )
{
      TriggerRegisterPlayerEvent_org = (TriggerRegisterPlayerEvent_FUNC) ( GameDll + 0x1F9A20 );
      MH_CreateHook(TriggerRegisterPlayerEvent_org, &TriggerRegisterPlayerEvent_my, reinterpret_cast<void**>(&TriggerRegisterPlayerEvent_ptr));
      MH_EnableHook(TriggerRegisterPlayerEvent_org);
}
void TriggerRegisterPlayerStateEvent_init ( )
{
      TriggerRegisterPlayerStateEvent_org = (TriggerRegisterPlayerStateEvent_FUNC) ( GameDll + 0x1F9B40 );
      MH_CreateHook(TriggerRegisterPlayerStateEvent_org, &TriggerRegisterPlayerStateEvent_my, reinterpret_cast<void**>(&TriggerRegisterPlayerStateEvent_ptr));
      MH_EnableHook(TriggerRegisterPlayerStateEvent_org);
}
void TriggerRegisterPlayerUnitEvent_init ( )
{
      TriggerRegisterPlayerUnitEvent_org = (TriggerRegisterPlayerUnitEvent_FUNC) ( GameDll + 0x1F9C60 );
      MH_CreateHook(TriggerRegisterPlayerUnitEvent_org, &TriggerRegisterPlayerUnitEvent_my, reinterpret_cast<void**>(&TriggerRegisterPlayerUnitEvent_ptr));
      MH_EnableHook(TriggerRegisterPlayerUnitEvent_org);
}
void TriggerRegisterTimerEvent_init ( )
{
      TriggerRegisterTimerEvent_org = (TriggerRegisterTimerEvent_FUNC) ( GameDll + 0x1F9D60 );
      MH_CreateHook(TriggerRegisterTimerEvent_org, &TriggerRegisterTimerEvent_my, reinterpret_cast<void**>(&TriggerRegisterTimerEvent_ptr));
      MH_EnableHook(TriggerRegisterTimerEvent_org);
}
void TriggerRegisterTimerExpireEvent_init ( )
{
      TriggerRegisterTimerExpireEvent_org = (TriggerRegisterTimerExpireEvent_FUNC) ( GameDll + 0x1F9E20 );
      MH_CreateHook(TriggerRegisterTimerExpireEvent_org, &TriggerRegisterTimerExpireEvent_my, reinterpret_cast<void**>(&TriggerRegisterTimerExpireEvent_ptr));
      MH_EnableHook(TriggerRegisterTimerExpireEvent_org);
}
void TriggerRegisterTrackableHitEvent_init ( )
{
      TriggerRegisterTrackableHitEvent_org = (TriggerRegisterTrackableHitEvent_FUNC) ( GameDll + 0x1F9EE0 );
      MH_CreateHook(TriggerRegisterTrackableHitEvent_org, &TriggerRegisterTrackableHitEvent_my, reinterpret_cast<void**>(&TriggerRegisterTrackableHitEvent_ptr));
      MH_EnableHook(TriggerRegisterTrackableHitEvent_org);
}
void TriggerRegisterTrackableTrackEvent_init ( )
{
      TriggerRegisterTrackableTrackEvent_org = (TriggerRegisterTrackableTrackEvent_FUNC) ( GameDll + 0x1F9FA0 );
      MH_CreateHook(TriggerRegisterTrackableTrackEvent_org, &TriggerRegisterTrackableTrackEvent_my, reinterpret_cast<void**>(&TriggerRegisterTrackableTrackEvent_ptr));
      MH_EnableHook(TriggerRegisterTrackableTrackEvent_org);
}
void TriggerRegisterUnitEvent_init ( )
{
      TriggerRegisterUnitEvent_org = (TriggerRegisterUnitEvent_FUNC) ( GameDll + 0x1FA060 );
      MH_CreateHook(TriggerRegisterUnitEvent_org, &TriggerRegisterUnitEvent_my, reinterpret_cast<void**>(&TriggerRegisterUnitEvent_ptr));
      MH_EnableHook(TriggerRegisterUnitEvent_org);
}
void TriggerRegisterUnitInRange_init ( )
{
      TriggerRegisterUnitInRange_org = (TriggerRegisterUnitInRange_FUNC) ( GameDll + 0x1FA170 );
      MH_CreateHook(TriggerRegisterUnitInRange_org, &TriggerRegisterUnitInRange_my, reinterpret_cast<void**>(&TriggerRegisterUnitInRange_ptr));
      MH_EnableHook(TriggerRegisterUnitInRange_org);
}
void TriggerRegisterUnitStateEvent_init ( )
{
      TriggerRegisterUnitStateEvent_org = (TriggerRegisterUnitStateEvent_FUNC) ( GameDll + 0x1FA260 );
      MH_CreateHook(TriggerRegisterUnitStateEvent_org, &TriggerRegisterUnitStateEvent_my, reinterpret_cast<void**>(&TriggerRegisterUnitStateEvent_ptr));
      MH_EnableHook(TriggerRegisterUnitStateEvent_org);
}
void TriggerRegisterVariableEvent_init ( )
{
      TriggerRegisterVariableEvent_org = (TriggerRegisterVariableEvent_FUNC) ( GameDll + 0x1FA350 );
      MH_CreateHook(TriggerRegisterVariableEvent_org, &TriggerRegisterVariableEvent_my, reinterpret_cast<void**>(&TriggerRegisterVariableEvent_ptr));
      MH_EnableHook(TriggerRegisterVariableEvent_org);
}
void TriggerRemoveAction_init ( )
{
      TriggerRemoveAction_org = (TriggerRemoveAction_FUNC) ( GameDll + 0x1FA420 );
      MH_CreateHook(TriggerRemoveAction_org, &TriggerRemoveAction_my, reinterpret_cast<void**>(&TriggerRemoveAction_ptr));
      MH_EnableHook(TriggerRemoveAction_org);
}
void TriggerRemoveCondition_init ( )
{
      TriggerRemoveCondition_org = (TriggerRemoveCondition_FUNC) ( GameDll + 0x1FA450 );
      MH_CreateHook(TriggerRemoveCondition_org, &TriggerRemoveCondition_my, reinterpret_cast<void**>(&TriggerRemoveCondition_ptr));
      MH_EnableHook(TriggerRemoveCondition_org);
}
void TriggerSleepAction_init ( )
{
      TriggerSleepAction_org = (TriggerSleepAction_FUNC) ( GameDll + 0x1FA480 );
      MH_CreateHook(TriggerSleepAction_org, &TriggerSleepAction_my, reinterpret_cast<void**>(&TriggerSleepAction_ptr));
      MH_EnableHook(TriggerSleepAction_org);
}
void TriggerSyncReady_init ( )
{
      TriggerSyncReady_org = (TriggerSyncReady_FUNC) ( GameDll + 0x1FA490 );
      MH_CreateHook(TriggerSyncReady_org, &TriggerSyncReady_my, reinterpret_cast<void**>(&TriggerSyncReady_ptr));
      MH_EnableHook(TriggerSyncReady_org);
}
void TriggerSyncStart_init ( )
{
      TriggerSyncStart_org = (TriggerSyncStart_FUNC) ( GameDll + 0x1FA4C0 );
      MH_CreateHook(TriggerSyncStart_org, &TriggerSyncStart_my, reinterpret_cast<void**>(&TriggerSyncStart_ptr));
      MH_EnableHook(TriggerSyncStart_org);
}
void TriggerWaitForSound_init ( )
{
      TriggerWaitForSound_org = (TriggerWaitForSound_FUNC) ( GameDll + 0x1FA4D0 );
      MH_CreateHook(TriggerWaitForSound_org, &TriggerWaitForSound_my, reinterpret_cast<void**>(&TriggerWaitForSound_ptr));
      MH_EnableHook(TriggerWaitForSound_org);
}
void TriggerWaitOnSleeps_init ( )
{
      TriggerWaitOnSleeps_org = (TriggerWaitOnSleeps_FUNC) ( GameDll + 0x1FA4F0 );
      MH_CreateHook(TriggerWaitOnSleeps_org, &TriggerWaitOnSleeps_my, reinterpret_cast<void**>(&TriggerWaitOnSleeps_ptr));
      MH_EnableHook(TriggerWaitOnSleeps_org);
}
void UnitAddAbility_init ( )
{
      UnitAddAbility_org = (UnitAddAbility_FUNC) ( GameDll + 0x1FA510 );
      MH_CreateHook(UnitAddAbility_org, &UnitAddAbility_my, reinterpret_cast<void**>(&UnitAddAbility_ptr));
      MH_EnableHook(UnitAddAbility_org);
}
void UnitAddIndicator_init ( )
{
      UnitAddIndicator_org = (UnitAddIndicator_FUNC) ( GameDll + 0x1FA580 );
      MH_CreateHook(UnitAddIndicator_org, &UnitAddIndicator_my, reinterpret_cast<void**>(&UnitAddIndicator_ptr));
      MH_EnableHook(UnitAddIndicator_org);
}
void UnitAddItem_init ( )
{
      UnitAddItem_org = (UnitAddItem_FUNC) ( GameDll + 0x1FA610 );
      MH_CreateHook(UnitAddItem_org, &UnitAddItem_my, reinterpret_cast<void**>(&UnitAddItem_ptr));
      MH_EnableHook(UnitAddItem_org);
}
void UnitAddItemById_init ( )
{
      UnitAddItemById_org = (UnitAddItemById_FUNC) ( GameDll + 0x1FA700 );
      MH_CreateHook(UnitAddItemById_org, &UnitAddItemById_my, reinterpret_cast<void**>(&UnitAddItemById_ptr));
      MH_EnableHook(UnitAddItemById_org);
}
void UnitAddItemToSlotById_init ( )
{
      UnitAddItemToSlotById_org = (UnitAddItemToSlotById_FUNC) ( GameDll + 0x1FA7B0 );
      MH_CreateHook(UnitAddItemToSlotById_org, &UnitAddItemToSlotById_my, reinterpret_cast<void**>(&UnitAddItemToSlotById_ptr));
      MH_EnableHook(UnitAddItemToSlotById_org);
}
void UnitAddSleep_init ( )
{
      UnitAddSleep_org = (UnitAddSleep_FUNC) ( GameDll + 0x1FA850 );
      MH_CreateHook(UnitAddSleep_org, &UnitAddSleep_my, reinterpret_cast<void**>(&UnitAddSleep_ptr));
      MH_EnableHook(UnitAddSleep_org);
}
void UnitAddSleepPerm_init ( )
{
      UnitAddSleepPerm_org = (UnitAddSleepPerm_FUNC) ( GameDll + 0x1FA8A0 );
      MH_CreateHook(UnitAddSleepPerm_org, &UnitAddSleepPerm_my, reinterpret_cast<void**>(&UnitAddSleepPerm_ptr));
      MH_EnableHook(UnitAddSleepPerm_org);
}
void UnitAddType_init ( )
{
      UnitAddType_org = (UnitAddType_FUNC) ( GameDll + 0x1FA8F0 );
      MH_CreateHook(UnitAddType_org, &UnitAddType_my, reinterpret_cast<void**>(&UnitAddType_ptr));
      MH_EnableHook(UnitAddType_org);
}
void UnitAlive_init ( )
{
      UnitAlive_org = (UnitAlive_FUNC) ( GameDll + 0x8958D0 );
      MH_CreateHook(UnitAlive_org, &UnitAlive_my, reinterpret_cast<void**>(&UnitAlive_ptr));
      MH_EnableHook(UnitAlive_org);
}
void UnitApplyTimedLife_init ( )
{
      UnitApplyTimedLife_org = (UnitApplyTimedLife_FUNC) ( GameDll + 0x1FA950 );
      MH_CreateHook(UnitApplyTimedLife_org, &UnitApplyTimedLife_my, reinterpret_cast<void**>(&UnitApplyTimedLife_ptr));
      MH_EnableHook(UnitApplyTimedLife_org);
}
void UnitCanSleep_init ( )
{
      UnitCanSleep_org = (UnitCanSleep_FUNC) ( GameDll + 0x1FA9C0 );
      MH_CreateHook(UnitCanSleep_org, &UnitCanSleep_my, reinterpret_cast<void**>(&UnitCanSleep_ptr));
      MH_EnableHook(UnitCanSleep_org);
}
void UnitCanSleepPerm_init ( )
{
      UnitCanSleepPerm_org = (UnitCanSleepPerm_FUNC) ( GameDll + 0x1FAA00 );
      MH_CreateHook(UnitCanSleepPerm_org, &UnitCanSleepPerm_my, reinterpret_cast<void**>(&UnitCanSleepPerm_ptr));
      MH_EnableHook(UnitCanSleepPerm_org);
}
void UnitCountBuffsEx_init ( )
{
      UnitCountBuffsEx_org = (UnitCountBuffsEx_FUNC) ( GameDll + 0x1FAA40 );
      MH_CreateHook(UnitCountBuffsEx_org, &UnitCountBuffsEx_my, reinterpret_cast<void**>(&UnitCountBuffsEx_ptr));
      MH_EnableHook(UnitCountBuffsEx_org);
}
void UnitDamagePoint_init ( )
{
      UnitDamagePoint_org = (UnitDamagePoint_FUNC) ( GameDll + 0x1FAA80 );
      MH_CreateHook(UnitDamagePoint_org, &UnitDamagePoint_my, reinterpret_cast<void**>(&UnitDamagePoint_ptr));
      MH_EnableHook(UnitDamagePoint_org);
}
void UnitDamageTarget_init ( )
{
      UnitDamageTarget_org = (UnitDamageTarget_FUNC) ( GameDll + 0x1FAB70 );
      MH_CreateHook(UnitDamageTarget_org, &UnitDamageTarget_my, reinterpret_cast<void**>(&UnitDamageTarget_ptr));
      MH_EnableHook(UnitDamageTarget_org);
}
void UnitDropItemPoint_init ( )
{
      UnitDropItemPoint_org = (UnitDropItemPoint_FUNC) ( GameDll + 0x1FAC20 );
      MH_CreateHook(UnitDropItemPoint_org, &UnitDropItemPoint_my, reinterpret_cast<void**>(&UnitDropItemPoint_ptr));
      MH_EnableHook(UnitDropItemPoint_org);
}
void UnitDropItemSlot_init ( )
{
      UnitDropItemSlot_org = (UnitDropItemSlot_FUNC) ( GameDll + 0x1FAC80 );
      MH_CreateHook(UnitDropItemSlot_org, &UnitDropItemSlot_my, reinterpret_cast<void**>(&UnitDropItemSlot_ptr));
      MH_EnableHook(UnitDropItemSlot_org);
}
void UnitDropItemTarget_init ( )
{
      UnitDropItemTarget_org = (UnitDropItemTarget_FUNC) ( GameDll + 0x1FACF0 );
      MH_CreateHook(UnitDropItemTarget_org, &UnitDropItemTarget_my, reinterpret_cast<void**>(&UnitDropItemTarget_ptr));
      MH_EnableHook(UnitDropItemTarget_org);
}
void UnitHasBuffsEx_init ( )
{
      UnitHasBuffsEx_org = (UnitHasBuffsEx_FUNC) ( GameDll + 0x1FAD50 );
      MH_CreateHook(UnitHasBuffsEx_org, &UnitHasBuffsEx_my, reinterpret_cast<void**>(&UnitHasBuffsEx_ptr));
      MH_EnableHook(UnitHasBuffsEx_org);
}
void UnitHasItem_init ( )
{
      UnitHasItem_org = (UnitHasItem_FUNC) ( GameDll + 0x1FAD90 );
      MH_CreateHook(UnitHasItem_org, &UnitHasItem_my, reinterpret_cast<void**>(&UnitHasItem_ptr));
      MH_EnableHook(UnitHasItem_org);
}
void UnitId_init ( )
{
      UnitId_org = (UnitId_FUNC) ( GameDll + 0x1FAE10 );
      MH_CreateHook(UnitId_org, &UnitId_my, reinterpret_cast<void**>(&UnitId_ptr));
      MH_EnableHook(UnitId_org);
}
void UnitId2String_init ( )
{
      UnitId2String_org = (UnitId2String_FUNC) ( GameDll + 0x1FADE0 );
      MH_CreateHook(UnitId2String_org, &UnitId2String_my, reinterpret_cast<void**>(&UnitId2String_ptr));
      MH_EnableHook(UnitId2String_org);
}
void UnitIgnoreAlarm_init ( )
{
      UnitIgnoreAlarm_org = (UnitIgnoreAlarm_FUNC) ( GameDll + 0x1FAE40 );
      MH_CreateHook(UnitIgnoreAlarm_org, &UnitIgnoreAlarm_my, reinterpret_cast<void**>(&UnitIgnoreAlarm_ptr));
      MH_EnableHook(UnitIgnoreAlarm_org);
}
void UnitIgnoreAlarmToggled_init ( )
{
      UnitIgnoreAlarmToggled_org = (UnitIgnoreAlarmToggled_FUNC) ( GameDll + 0x1FAEA0 );
      MH_CreateHook(UnitIgnoreAlarmToggled_org, &UnitIgnoreAlarmToggled_my, reinterpret_cast<void**>(&UnitIgnoreAlarmToggled_ptr));
      MH_EnableHook(UnitIgnoreAlarmToggled_org);
}
void UnitInventorySize_init ( )
{
      UnitInventorySize_org = (UnitInventorySize_FUNC) ( GameDll + 0x1FAEE0 );
      MH_CreateHook(UnitInventorySize_org, &UnitInventorySize_my, reinterpret_cast<void**>(&UnitInventorySize_ptr));
      MH_EnableHook(UnitInventorySize_org);
}
void UnitInvis_init ( )
{
      UnitInvis_org = (UnitInvis_FUNC) ( GameDll + 0x895930 );
      MH_CreateHook(UnitInvis_org, &UnitInvis_my, reinterpret_cast<void**>(&UnitInvis_ptr));
      MH_EnableHook(UnitInvis_org);
}
void UnitIsSleeping_init ( )
{
      UnitIsSleeping_org = (UnitIsSleeping_FUNC) ( GameDll + 0x1FAF10 );
      MH_CreateHook(UnitIsSleeping_org, &UnitIsSleeping_my, reinterpret_cast<void**>(&UnitIsSleeping_ptr));
      MH_EnableHook(UnitIsSleeping_org);
}
void UnitItemInSlot_init ( )
{
      UnitItemInSlot_org = (UnitItemInSlot_FUNC) ( GameDll + 0x1FAF50 );
      MH_CreateHook(UnitItemInSlot_org, &UnitItemInSlot_my, reinterpret_cast<void**>(&UnitItemInSlot_ptr));
      MH_EnableHook(UnitItemInSlot_org);
}
void UnitMakeAbilityPermanent_init ( )
{
      UnitMakeAbilityPermanent_org = (UnitMakeAbilityPermanent_FUNC) ( GameDll + 0x1FAFA0 );
      MH_CreateHook(UnitMakeAbilityPermanent_org, &UnitMakeAbilityPermanent_my, reinterpret_cast<void**>(&UnitMakeAbilityPermanent_ptr));
      MH_EnableHook(UnitMakeAbilityPermanent_org);
}
void UnitModifySkillPoints_init ( )
{
      UnitModifySkillPoints_org = (UnitModifySkillPoints_FUNC) ( GameDll + 0x1FAFF0 );
      MH_CreateHook(UnitModifySkillPoints_org, &UnitModifySkillPoints_my, reinterpret_cast<void**>(&UnitModifySkillPoints_ptr));
      MH_EnableHook(UnitModifySkillPoints_org);
}
void UnitPauseTimedLife_init ( )
{
      UnitPauseTimedLife_org = (UnitPauseTimedLife_FUNC) ( GameDll + 0x1FB050 );
      MH_CreateHook(UnitPauseTimedLife_org, &UnitPauseTimedLife_my, reinterpret_cast<void**>(&UnitPauseTimedLife_ptr));
      MH_EnableHook(UnitPauseTimedLife_org);
}
void UnitPoolAddUnitType_init ( )
{
      UnitPoolAddUnitType_org = (UnitPoolAddUnitType_FUNC) ( GameDll + 0x1FB070 );
      MH_CreateHook(UnitPoolAddUnitType_org, &UnitPoolAddUnitType_my, reinterpret_cast<void**>(&UnitPoolAddUnitType_ptr));
      MH_EnableHook(UnitPoolAddUnitType_org);
}
void UnitPoolRemoveUnitType_init ( )
{
      UnitPoolRemoveUnitType_org = (UnitPoolRemoveUnitType_FUNC) ( GameDll + 0x1FB090 );
      MH_CreateHook(UnitPoolRemoveUnitType_org, &UnitPoolRemoveUnitType_my, reinterpret_cast<void**>(&UnitPoolRemoveUnitType_ptr));
      MH_EnableHook(UnitPoolRemoveUnitType_org);
}
void UnitRemoveAbility_init ( )
{
      UnitRemoveAbility_org = (UnitRemoveAbility_FUNC) ( GameDll + 0x1FB0B0 );
      MH_CreateHook(UnitRemoveAbility_org, &UnitRemoveAbility_my, reinterpret_cast<void**>(&UnitRemoveAbility_ptr));
      MH_EnableHook(UnitRemoveAbility_org);
}
void UnitRemoveBuffs_init ( )
{
      UnitRemoveBuffs_org = (UnitRemoveBuffs_FUNC) ( GameDll + 0x1FB100 );
      MH_CreateHook(UnitRemoveBuffs_org, &UnitRemoveBuffs_my, reinterpret_cast<void**>(&UnitRemoveBuffs_ptr));
      MH_EnableHook(UnitRemoveBuffs_org);
}
void UnitRemoveBuffsEx_init ( )
{
      UnitRemoveBuffsEx_org = (UnitRemoveBuffsEx_FUNC) ( GameDll + 0x1FB130 );
      MH_CreateHook(UnitRemoveBuffsEx_org, &UnitRemoveBuffsEx_my, reinterpret_cast<void**>(&UnitRemoveBuffsEx_ptr));
      MH_EnableHook(UnitRemoveBuffsEx_org);
}
void UnitRemoveItem_init ( )
{
      UnitRemoveItem_org = (UnitRemoveItem_FUNC) ( GameDll + 0x1FB170 );
      MH_CreateHook(UnitRemoveItem_org, &UnitRemoveItem_my, reinterpret_cast<void**>(&UnitRemoveItem_ptr));
      MH_EnableHook(UnitRemoveItem_org);
}
void UnitRemoveItemFromSlot_init ( )
{
      UnitRemoveItemFromSlot_org = (UnitRemoveItemFromSlot_FUNC) ( GameDll + 0x1FB1B0 );
      MH_CreateHook(UnitRemoveItemFromSlot_org, &UnitRemoveItemFromSlot_my, reinterpret_cast<void**>(&UnitRemoveItemFromSlot_ptr));
      MH_EnableHook(UnitRemoveItemFromSlot_org);
}
void UnitRemoveType_init ( )
{
      UnitRemoveType_org = (UnitRemoveType_FUNC) ( GameDll + 0x1FB210 );
      MH_CreateHook(UnitRemoveType_org, &UnitRemoveType_my, reinterpret_cast<void**>(&UnitRemoveType_ptr));
      MH_EnableHook(UnitRemoveType_org);
}
void UnitResetCooldown_init ( )
{
      UnitResetCooldown_org = (UnitResetCooldown_FUNC) ( GameDll + 0x1FB270 );
      MH_CreateHook(UnitResetCooldown_org, &UnitResetCooldown_my, reinterpret_cast<void**>(&UnitResetCooldown_ptr));
      MH_EnableHook(UnitResetCooldown_org);
}
void UnitSetConstructionProgress_init ( )
{
      UnitSetConstructionProgress_org = (UnitSetConstructionProgress_FUNC) ( GameDll + 0x1FB290 );
      MH_CreateHook(UnitSetConstructionProgress_org, &UnitSetConstructionProgress_my, reinterpret_cast<void**>(&UnitSetConstructionProgress_ptr));
      MH_EnableHook(UnitSetConstructionProgress_org);
}
void UnitSetUpgradeProgress_init ( )
{
      UnitSetUpgradeProgress_org = (UnitSetUpgradeProgress_FUNC) ( GameDll + 0x1FB2D0 );
      MH_CreateHook(UnitSetUpgradeProgress_org, &UnitSetUpgradeProgress_my, reinterpret_cast<void**>(&UnitSetUpgradeProgress_ptr));
      MH_EnableHook(UnitSetUpgradeProgress_org);
}
void UnitSetUsesAltIcon_init ( )
{
      UnitSetUsesAltIcon_org = (UnitSetUsesAltIcon_FUNC) ( GameDll + 0x1FB310 );
      MH_CreateHook(UnitSetUsesAltIcon_org, &UnitSetUsesAltIcon_my, reinterpret_cast<void**>(&UnitSetUsesAltIcon_ptr));
      MH_EnableHook(UnitSetUsesAltIcon_org);
}
void UnitShareVision_init ( )
{
      UnitShareVision_org = (UnitShareVision_FUNC) ( GameDll + 0x1FB340 );
      MH_CreateHook(UnitShareVision_org, &UnitShareVision_my, reinterpret_cast<void**>(&UnitShareVision_ptr));
      MH_EnableHook(UnitShareVision_org);
}
void UnitStripHeroLevel_init ( )
{
      UnitStripHeroLevel_org = (UnitStripHeroLevel_FUNC) ( GameDll + 0x1FB370 );
      MH_CreateHook(UnitStripHeroLevel_org, &UnitStripHeroLevel_my, reinterpret_cast<void**>(&UnitStripHeroLevel_ptr));
      MH_EnableHook(UnitStripHeroLevel_org);
}
void UnitSuspendDecay_init ( )
{
      UnitSuspendDecay_org = (UnitSuspendDecay_FUNC) ( GameDll + 0x1FB3D0 );
      MH_CreateHook(UnitSuspendDecay_org, &UnitSuspendDecay_my, reinterpret_cast<void**>(&UnitSuspendDecay_ptr));
      MH_EnableHook(UnitSuspendDecay_org);
}
void UnitUseItem_init ( )
{
      UnitUseItem_org = (UnitUseItem_FUNC) ( GameDll + 0x1FB430 );
      MH_CreateHook(UnitUseItem_org, &UnitUseItem_my, reinterpret_cast<void**>(&UnitUseItem_ptr));
      MH_EnableHook(UnitUseItem_org);
}
void UnitUseItemPoint_init ( )
{
      UnitUseItemPoint_org = (UnitUseItemPoint_FUNC) ( GameDll + 0x1FB4A0 );
      MH_CreateHook(UnitUseItemPoint_org, &UnitUseItemPoint_my, reinterpret_cast<void**>(&UnitUseItemPoint_ptr));
      MH_EnableHook(UnitUseItemPoint_org);
}
void UnitUseItemTarget_init ( )
{
      UnitUseItemTarget_org = (UnitUseItemTarget_FUNC) ( GameDll + 0x1FB510 );
      MH_CreateHook(UnitUseItemTarget_org, &UnitUseItemTarget_my, reinterpret_cast<void**>(&UnitUseItemTarget_ptr));
      MH_EnableHook(UnitUseItemTarget_org);
}
void UnitWakeUp_init ( )
{
      UnitWakeUp_org = (UnitWakeUp_FUNC) ( GameDll + 0x1FB590 );
      MH_CreateHook(UnitWakeUp_org, &UnitWakeUp_my, reinterpret_cast<void**>(&UnitWakeUp_ptr));
      MH_EnableHook(UnitWakeUp_org);
}
void UnregisterStackedSound_init ( )
{
      UnregisterStackedSound_org = (UnregisterStackedSound_FUNC) ( GameDll + 0x1FB680 );
      MH_CreateHook(UnregisterStackedSound_org, &UnregisterStackedSound_my, reinterpret_cast<void**>(&UnregisterStackedSound_ptr));
      MH_EnableHook(UnregisterStackedSound_org);
}
void Unsummon_init ( )
{
      Unsummon_org = (Unsummon_FUNC) ( GameDll + 0x895B20 );
      MH_CreateHook(Unsummon_org, &Unsummon_my, reinterpret_cast<void**>(&Unsummon_ptr));
      MH_EnableHook(Unsummon_org);
}
void VersionCompatible_init ( )
{
      VersionCompatible_org = (VersionCompatible_FUNC) ( GameDll + 0x1FB6C0 );
      MH_CreateHook(VersionCompatible_org, &VersionCompatible_my, reinterpret_cast<void**>(&VersionCompatible_ptr));
      MH_EnableHook(VersionCompatible_org);
}
void VersionGet_init ( )
{
      VersionGet_org = (VersionGet_FUNC) ( GameDll + 0x1FB6D0 );
      MH_CreateHook(VersionGet_org, &VersionGet_my, reinterpret_cast<void**>(&VersionGet_ptr));
      MH_EnableHook(VersionGet_org);
}
void VersionSupported_init ( )
{
      VersionSupported_org = (VersionSupported_FUNC) ( GameDll + 0x1FB6E0 );
      MH_CreateHook(VersionSupported_org, &VersionSupported_my, reinterpret_cast<void**>(&VersionSupported_ptr));
      MH_EnableHook(VersionSupported_org);
}
void VolumeGroupReset_init ( )
{
      VolumeGroupReset_org = (VolumeGroupReset_FUNC) ( GameDll + 0x1FB6F0 );
      MH_CreateHook(VolumeGroupReset_org, &VolumeGroupReset_my, reinterpret_cast<void**>(&VolumeGroupReset_ptr));
      MH_EnableHook(VolumeGroupReset_org);
}
void VolumeGroupSetVolume_init ( )
{
      VolumeGroupSetVolume_org = (VolumeGroupSetVolume_FUNC) ( GameDll + 0x1FB700 );
      MH_CreateHook(VolumeGroupSetVolume_org, &VolumeGroupSetVolume_my, reinterpret_cast<void**>(&VolumeGroupSetVolume_ptr));
      MH_EnableHook(VolumeGroupSetVolume_org);
}
void WaitGetEnemyBase_init ( )
{
      WaitGetEnemyBase_org = (WaitGetEnemyBase_FUNC) ( GameDll + 0x895BE0 );
      MH_CreateHook(WaitGetEnemyBase_org, &WaitGetEnemyBase_my, reinterpret_cast<void**>(&WaitGetEnemyBase_ptr));
      MH_EnableHook(WaitGetEnemyBase_org);
}
void WaygateActivate_init ( )
{
      WaygateActivate_org = (WaygateActivate_FUNC) ( GameDll + 0x1FB750 );
      MH_CreateHook(WaygateActivate_org, &WaygateActivate_my, reinterpret_cast<void**>(&WaygateActivate_ptr));
      MH_EnableHook(WaygateActivate_org);
}
void WaygateGetDestinationX_init ( )
{
      WaygateGetDestinationX_org = (WaygateGetDestinationX_FUNC) ( GameDll + 0x1FB790 );
      MH_CreateHook(WaygateGetDestinationX_org, &WaygateGetDestinationX_my, reinterpret_cast<void**>(&WaygateGetDestinationX_ptr));
      MH_EnableHook(WaygateGetDestinationX_org);
}
void WaygateGetDestinationY_init ( )
{
      WaygateGetDestinationY_org = (WaygateGetDestinationY_FUNC) ( GameDll + 0x1FB7E0 );
      MH_CreateHook(WaygateGetDestinationY_org, &WaygateGetDestinationY_my, reinterpret_cast<void**>(&WaygateGetDestinationY_ptr));
      MH_EnableHook(WaygateGetDestinationY_org);
}
void WaygateIsActive_init ( )
{
      WaygateIsActive_org = (WaygateIsActive_FUNC) ( GameDll + 0x1FB830 );
      MH_CreateHook(WaygateIsActive_org, &WaygateIsActive_my, reinterpret_cast<void**>(&WaygateIsActive_ptr));
      MH_EnableHook(WaygateIsActive_org);
}
void WaygateSetDestination_init ( )
{
      WaygateSetDestination_org = (WaygateSetDestination_FUNC) ( GameDll + 0x1FB870 );
      MH_CreateHook(WaygateSetDestination_org, &WaygateSetDestination_my, reinterpret_cast<void**>(&WaygateSetDestination_ptr));
      MH_EnableHook(WaygateSetDestination_org);
}
typedef int(__fastcall *LookupNative)(LPSTR,int unknown);
LookupNative LookupNative_org = NULL;
LookupNative LookupNative_ptr = NULL;
int __fastcall LookupNative_my(LPSTR str,int unknown)
{
   funcname2 = str;
   return LookupNative_ptr(str,unknown);
}
void Initializer( )
{
   LookupNative_org = (LookupNative) (GameDll + 0x7E2FE0 );
   MH_CreateHook(LookupNative_org, &LookupNative_my, reinterpret_cast<void**>(&LookupNative_ptr));
   MH_EnableHook(LookupNative_org);
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AbilityId" , false ) )
      AbilityId_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AbilityId2String" , false ) )
      AbilityId2String_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Acos" , false ) )
      Acos_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddAssault" , false ) )
      AddAssault_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddDefenders" , false ) )
      AddDefenders_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddGuardPost" , false ) )
      AddGuardPost_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddHeroXP" , false ) )
      AddHeroXP_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddIndicator" , false ) )
      AddIndicator_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddItemToAllStock" , false ) )
      AddItemToAllStock_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddItemToStock" , false ) )
      AddItemToStock_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddLightning" , false ) )
      AddLightning_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddLightningEx" , false ) )
      AddLightningEx_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddPlayerTechResearched" , false ) )
      AddPlayerTechResearched_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddResourceAmount" , false ) )
      AddResourceAmount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddSpecialEffect" , false ) )
      AddSpecialEffect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddSpecialEffectLoc" , false ) )
      AddSpecialEffectLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddSpecialEffectTarget" , false ) )
      AddSpecialEffectTarget_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddSpellEffect" , false ) )
      AddSpellEffect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddSpellEffectById" , false ) )
      AddSpellEffectById_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddSpellEffectByIdLoc" , false ) )
      AddSpellEffectByIdLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddSpellEffectLoc" , false ) )
      AddSpellEffectLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddSpellEffectTarget" , false ) )
      AddSpellEffectTarget_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddSpellEffectTargetById" , false ) )
      AddSpellEffectTargetById_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddUnitAnimationProperties" , false ) )
      AddUnitAnimationProperties_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddUnitToAllStock" , false ) )
      AddUnitToAllStock_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddUnitToStock" , false ) )
      AddUnitToStock_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AddWeatherEffect" , false ) )
      AddWeatherEffect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AdjustCameraField" , false ) )
      AdjustCameraField_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "And" , false ) )
      And_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Asin" , false ) )
      Asin_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Atan" , false ) )
      Atan_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Atan2" , false ) )
      Atan2_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AttachSoundToUnit" , false ) )
      AttachSoundToUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AttackMoveKill" , false ) )
      AttackMoveKill_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "AttackMoveXY" , false ) )
      AttackMoveXY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CachePlayerHeroData" , false ) )
      CachePlayerHeroData_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CameraSetSmoothingFactor" , false ) )
      CameraSetSmoothingFactor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CameraSetSourceNoise" , false ) )
      CameraSetSourceNoise_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CameraSetSourceNoiseEx" , false ) )
      CameraSetSourceNoiseEx_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CameraSetTargetNoise" , false ) )
      CameraSetTargetNoise_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CameraSetTargetNoiseEx" , false ) )
      CameraSetTargetNoiseEx_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CameraSetupApply" , false ) )
      CameraSetupApply_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CameraSetupApplyForceDuration" , false ) )
      CameraSetupApplyForceDuration_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CameraSetupApplyForceDurationWithZ" , false ) )
      CameraSetupApplyForceDurationWithZ_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CameraSetupApplyWithZ" , false ) )
      CameraSetupApplyWithZ_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CameraSetupGetDestPositionLoc" , false ) )
      CameraSetupGetDestPositionLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CameraSetupGetDestPositionX" , false ) )
      CameraSetupGetDestPositionX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CameraSetupGetDestPositionY" , false ) )
      CameraSetupGetDestPositionY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CameraSetupGetField" , false ) )
      CameraSetupGetField_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CameraSetupSetDestPosition" , false ) )
      CameraSetupSetDestPosition_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CameraSetupSetField" , false ) )
      CameraSetupSetField_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CaptainAtGoal" , false ) )
      CaptainAtGoal_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CaptainAttack" , false ) )
      CaptainAttack_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CaptainGoHome" , false ) )
      CaptainGoHome_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CaptainGroupSize" , false ) )
      CaptainGroupSize_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CaptainInCombat" , false ) )
      CaptainInCombat_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CaptainIsEmpty" , false ) )
      CaptainIsEmpty_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CaptainIsFull" , false ) )
      CaptainIsFull_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CaptainIsHome" , false ) )
      CaptainIsHome_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CaptainReadiness" , false ) )
      CaptainReadiness_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CaptainReadinessHP" , false ) )
      CaptainReadinessHP_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CaptainReadinessMa" , false ) )
      CaptainReadinessMa_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CaptainRetreating" , false ) )
      CaptainRetreating_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CaptainVsPlayer" , false ) )
      CaptainVsPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CaptainVsUnits" , false ) )
      CaptainVsUnits_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ChangeLevel" , false ) )
      ChangeLevel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Cheat" , false ) )
      Cheat_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ChooseRandomCreep" , false ) )
      ChooseRandomCreep_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ChooseRandomItem" , false ) )
      ChooseRandomItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ChooseRandomItemEx" , false ) )
      ChooseRandomItemEx_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ChooseRandomNPBuilding" , false ) )
      ChooseRandomNPBuilding_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ClearCaptainTargets" , false ) )
      ClearCaptainTargets_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ClearHarvestAI" , false ) )
      ClearHarvestAI_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ClearMapMusic" , false ) )
      ClearMapMusic_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ClearSelection" , false ) )
      ClearSelection_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ClearStackedSound" , false ) )
      ClearStackedSound_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ClearStackedSoundRect" , false ) )
      ClearStackedSoundRect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ClearTextMessages" , false ) )
      ClearTextMessages_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CommandAI" , false ) )
      CommandAI_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CommandsWaiting" , false ) )
      CommandsWaiting_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Condition" , false ) )
      Condition_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertAIDifficulty" , false ) )
      ConvertAIDifficulty_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertAllianceType" , false ) )
      ConvertAllianceType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertAttackType" , false ) )
      ConvertAttackType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertBlendMode" , false ) )
      ConvertBlendMode_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertCameraField" , false ) )
      ConvertCameraField_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertDamageType" , false ) )
      ConvertDamageType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertDialogEvent" , false ) )
      ConvertDialogEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertEffectType" , false ) )
      ConvertEffectType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertFGameState" , false ) )
      ConvertFGameState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertFogState" , false ) )
      ConvertFogState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertGameDifficulty" , false ) )
      ConvertGameDifficulty_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertGameEvent" , false ) )
      ConvertGameEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertGameSpeed" , false ) )
      ConvertGameSpeed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertGameType" , false ) )
      ConvertGameType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertIGameState" , false ) )
      ConvertIGameState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertItemType" , false ) )
      ConvertItemType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertLimitOp" , false ) )
      ConvertLimitOp_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertMapControl" , false ) )
      ConvertMapControl_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertMapDensity" , false ) )
      ConvertMapDensity_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertMapFlag" , false ) )
      ConvertMapFlag_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertMapSetting" , false ) )
      ConvertMapSetting_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertMapVisibility" , false ) )
      ConvertMapVisibility_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertPathingType" , false ) )
      ConvertPathingType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertPlacement" , false ) )
      ConvertPlacement_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertPlayerColor" , false ) )
      ConvertPlayerColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertPlayerEvent" , false ) )
      ConvertPlayerEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertPlayerGameResult" , false ) )
      ConvertPlayerGameResult_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertPlayerScore" , false ) )
      ConvertPlayerScore_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertPlayerSlotState" , false ) )
      ConvertPlayerSlotState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertPlayerState" , false ) )
      ConvertPlayerState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertPlayerUnitEvent" , false ) )
      ConvertPlayerUnitEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertRace" , false ) )
      ConvertRace_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertRacePref" , false ) )
      ConvertRacePref_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertRarityControl" , false ) )
      ConvertRarityControl_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertSoundType" , false ) )
      ConvertSoundType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertStartLocPrio" , false ) )
      ConvertStartLocPrio_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertTexMapFlags" , false ) )
      ConvertTexMapFlags_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertUnitEvent" , false ) )
      ConvertUnitEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertUnitState" , false ) )
      ConvertUnitState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertUnitType" , false ) )
      ConvertUnitType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertUnits" , false ) )
      ConvertUnits_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertVersion" , false ) )
      ConvertVersion_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertVolumeGroup" , false ) )
      ConvertVolumeGroup_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertWeaponType" , false ) )
      ConvertWeaponType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ConvertWidgetEvent" , false ) )
      ConvertWidgetEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CopySaveGame" , false ) )
      CopySaveGame_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Cos" , false ) )
      Cos_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateBlightedGoldmine" , false ) )
      CreateBlightedGoldmine_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateCameraSetup" , false ) )
      CreateCameraSetup_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateCaptains" , false ) )
      CreateCaptains_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateCorpse" , false ) )
      CreateCorpse_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateDeadDestructable" , false ) )
      CreateDeadDestructable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateDeadDestructableZ" , false ) )
      CreateDeadDestructableZ_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateDefeatCondition" , false ) )
      CreateDefeatCondition_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateDestructable" , false ) )
      CreateDestructable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateDestructableZ" , false ) )
      CreateDestructableZ_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateFogModifierRadius" , false ) )
      CreateFogModifierRadius_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateFogModifierRadiusLoc" , false ) )
      CreateFogModifierRadiusLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateFogModifierRect" , false ) )
      CreateFogModifierRect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateForce" , false ) )
      CreateForce_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateGroup" , false ) )
      CreateGroup_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateImage" , false ) )
      CreateImage_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateItem" , false ) )
      CreateItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateItemPool" , false ) )
      CreateItemPool_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateLeaderboard" , false ) )
      CreateLeaderboard_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateMIDISound" , false ) )
      CreateMIDISound_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateMultiboard" , false ) )
      CreateMultiboard_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateQuest" , false ) )
      CreateQuest_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateRegion" , false ) )
      CreateRegion_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateSound" , false ) )
      CreateSound_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateSoundFilenameWithLabel" , false ) )
      CreateSoundFilenameWithLabel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateSoundFromLabel" , false ) )
      CreateSoundFromLabel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateTextTag" , false ) )
      CreateTextTag_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateTimer" , false ) )
      CreateTimer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateTimerDialog" , false ) )
      CreateTimerDialog_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateTrackable" , false ) )
      CreateTrackable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateTrigger" , false ) )
      CreateTrigger_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateUbersplat" , false ) )
      CreateUbersplat_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateUnit" , false ) )
      CreateUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateUnitAtLoc" , false ) )
      CreateUnitAtLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateUnitAtLocByName" , false ) )
      CreateUnitAtLocByName_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateUnitByName" , false ) )
      CreateUnitByName_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreateUnitPool" , false ) )
      CreateUnitPool_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CreepsOnMap" , false ) )
      CreepsOnMap_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "CripplePlayer" , false ) )
      CripplePlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DebugBreak" , false ) )
      DebugBreak_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DebugFI" , false ) )
      DebugFI_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DebugS" , false ) )
      DebugS_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DebugUnitID" , false ) )
      DebugUnitID_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DecUnitAbilityLevel" , false ) )
      DecUnitAbilityLevel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DefeatConditionSetDescription" , false ) )
      DefeatConditionSetDescription_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DefineStartLocation" , false ) )
      DefineStartLocation_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DefineStartLocationLoc" , false ) )
      DefineStartLocationLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Deg2Rad" , false ) )
      Deg2Rad_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyBoolExpr" , false ) )
      DestroyBoolExpr_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyCondition" , false ) )
      DestroyCondition_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyDefeatCondition" , false ) )
      DestroyDefeatCondition_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyEffect" , false ) )
      DestroyEffect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyFilter" , false ) )
      DestroyFilter_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyFogModifier" , false ) )
      DestroyFogModifier_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyForce" , false ) )
      DestroyForce_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyGroup" , false ) )
      DestroyGroup_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyImage" , false ) )
      DestroyImage_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyItemPool" , false ) )
      DestroyItemPool_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyLeaderboard" , false ) )
      DestroyLeaderboard_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyLightning" , false ) )
      DestroyLightning_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyMultiboard" , false ) )
      DestroyMultiboard_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyQuest" , false ) )
      DestroyQuest_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyTextTag" , false ) )
      DestroyTextTag_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyTimer" , false ) )
      DestroyTimer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyTimerDialog" , false ) )
      DestroyTimerDialog_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyTrigger" , false ) )
      DestroyTrigger_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyUbersplat" , false ) )
      DestroyUbersplat_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestroyUnitPool" , false ) )
      DestroyUnitPool_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DestructableRestoreLife" , false ) )
      DestructableRestoreLife_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DialogAddButton" , false ) )
      DialogAddButton_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DialogAddQuitButton" , false ) )
      DialogAddQuitButton_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DialogClear" , false ) )
      DialogClear_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DialogCreate" , false ) )
      DialogCreate_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DialogDestroy" , false ) )
      DialogDestroy_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DialogDisplay" , false ) )
      DialogDisplay_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DialogSetAsync" , false ) )
      DialogSetAsync_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DialogSetMessage" , false ) )
      DialogSetMessage_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DisablePathing" , false ) )
      DisablePathing_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DisableRestartMission" , false ) )
      DisableRestartMission_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DisableTrigger" , false ) )
      DisableTrigger_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DisplayCineFilter" , false ) )
      DisplayCineFilter_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DisplayLoadDialog" , false ) )
      DisplayLoadDialog_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DisplayText" , false ) )
      DisplayText_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DisplayTextI" , false ) )
      DisplayTextI_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DisplayTextII" , false ) )
      DisplayTextII_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DisplayTextIII" , false ) )
      DisplayTextIII_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DisplayTextToPlayer" , false ) )
      DisplayTextToPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DisplayTimedTextFromPlayer" , false ) )
      DisplayTimedTextFromPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DisplayTimedTextToPlayer" , false ) )
      DisplayTimedTextToPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DoAiScriptDebug" , false ) )
      DoAiScriptDebug_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "DoNotSaveReplay" , false ) )
      DoNotSaveReplay_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "EnableDragSelect" , false ) )
      EnableDragSelect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "EnableMinimapFilterButtons" , false ) )
      EnableMinimapFilterButtons_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "EnableOcclusion" , false ) )
      EnableOcclusion_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "EnablePreSelect" , false ) )
      EnablePreSelect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "EnableSelect" , false ) )
      EnableSelect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "EnableTrigger" , false ) )
      EnableTrigger_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "EnableUserControl" , false ) )
      EnableUserControl_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "EnableUserUI" , false ) )
      EnableUserUI_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "EnableWeatherEffect" , false ) )
      EnableWeatherEffect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "EnableWorldFogBoundary" , false ) )
      EnableWorldFogBoundary_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "EndCinematicScene" , false ) )
      EndCinematicScene_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "EndGame" , false ) )
      EndGame_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "EndThematicMusic" , false ) )
      EndThematicMusic_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "EnumDestructablesInRect" , false ) )
      EnumDestructablesInRect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "EnumItemsInRect" , false ) )
      EnumItemsInRect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ExecuteFunc" , false ) )
      ExecuteFunc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "FillGuardPosts" , false ) )
      FillGuardPosts_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Filter" , false ) )
      Filter_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "FinishUbersplat" , false ) )
      FinishUbersplat_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "FirstOfGroup" , false ) )
      FirstOfGroup_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "FlashQuestDialogButton" , false ) )
      FlashQuestDialogButton_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "FlushChildHashtable" , false ) )
      FlushChildHashtable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "FlushGameCache" , false ) )
      FlushGameCache_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "FlushParentHashtable" , false ) )
      FlushParentHashtable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "FlushStoredBoolean" , false ) )
      FlushStoredBoolean_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "FlushStoredInteger" , false ) )
      FlushStoredInteger_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "FlushStoredMission" , false ) )
      FlushStoredMission_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "FlushStoredReal" , false ) )
      FlushStoredReal_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "FlushStoredString" , false ) )
      FlushStoredString_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "FlushStoredUnit" , false ) )
      FlushStoredUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "FogEnable" , false ) )
      FogEnable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "FogMaskEnable" , false ) )
      FogMaskEnable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "FogModifierStart" , false ) )
      FogModifierStart_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "FogModifierStop" , false ) )
      FogModifierStop_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ForForce" , false ) )
      ForForce_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ForGroup" , false ) )
      ForGroup_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ForceAddPlayer" , false ) )
      ForceAddPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ForceCampaignSelectScreen" , false ) )
      ForceCampaignSelectScreen_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ForceCinematicSubtitles" , false ) )
      ForceCinematicSubtitles_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ForceClear" , false ) )
      ForceClear_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ForceEnumAllies" , false ) )
      ForceEnumAllies_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ForceEnumEnemies" , false ) )
      ForceEnumEnemies_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ForceEnumPlayers" , false ) )
      ForceEnumPlayers_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ForceEnumPlayersCounted" , false ) )
      ForceEnumPlayersCounted_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ForcePlayerStartLocation" , false ) )
      ForcePlayerStartLocation_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ForceQuestDialogUpdate" , false ) )
      ForceQuestDialogUpdate_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ForceRemovePlayer" , false ) )
      ForceRemovePlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ForceUICancel" , false ) )
      ForceUICancel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ForceUIKey" , false ) )
      ForceUIKey_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetAIDifficulty" , false ) )
      GetAIDifficulty_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetAbilityEffect" , false ) )
      GetAbilityEffect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetAbilityEffectById" , false ) )
      GetAbilityEffectById_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetAbilitySound" , false ) )
      GetAbilitySound_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetAbilitySoundById" , false ) )
      GetAbilitySoundById_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetAiPlayer" , false ) )
      GetAiPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetAllianceTarget" , false ) )
      GetAllianceTarget_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetAllyColorFilterState" , false ) )
      GetAllyColorFilterState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetAttacker" , false ) )
      GetAttacker_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetBuilding" , false ) )
      GetBuilding_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetBuyingUnit" , false ) )
      GetBuyingUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCameraBoundMaxX" , false ) )
      GetCameraBoundMaxX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCameraBoundMaxY" , false ) )
      GetCameraBoundMaxY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCameraBoundMinX" , false ) )
      GetCameraBoundMinX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCameraBoundMinY" , false ) )
      GetCameraBoundMinY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCameraEyePositionLoc" , false ) )
      GetCameraEyePositionLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCameraEyePositionX" , false ) )
      GetCameraEyePositionX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCameraEyePositionY" , false ) )
      GetCameraEyePositionY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCameraEyePositionZ" , false ) )
      GetCameraEyePositionZ_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCameraField" , false ) )
      GetCameraField_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCameraMargin" , false ) )
      GetCameraMargin_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCameraTargetPositionLoc" , false ) )
      GetCameraTargetPositionLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCameraTargetPositionX" , false ) )
      GetCameraTargetPositionX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCameraTargetPositionY" , false ) )
      GetCameraTargetPositionY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCameraTargetPositionZ" , false ) )
      GetCameraTargetPositionZ_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCancelledStructure" , false ) )
      GetCancelledStructure_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetChangingUnit" , false ) )
      GetChangingUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetChangingUnitPrevOwner" , false ) )
      GetChangingUnitPrevOwner_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetClickedButton" , false ) )
      GetClickedButton_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetClickedDialog" , false ) )
      GetClickedDialog_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetConstructedStructure" , false ) )
      GetConstructedStructure_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetConstructingStructure" , false ) )
      GetConstructingStructure_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCreatureDensity" , false ) )
      GetCreatureDensity_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCreepCamp" , false ) )
      GetCreepCamp_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCreepCampFilterState" , false ) )
      GetCreepCampFilterState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetCustomCampaignButtonVisible" , false ) )
      GetCustomCampaignButtonVisible_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetDecayingUnit" , false ) )
      GetDecayingUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetDefaultDifficulty" , false ) )
      GetDefaultDifficulty_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetDestructableLife" , false ) )
      GetDestructableLife_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetDestructableMaxLife" , false ) )
      GetDestructableMaxLife_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetDestructableName" , false ) )
      GetDestructableName_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetDestructableOccluderHeight" , false ) )
      GetDestructableOccluderHeight_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetDestructableTypeId" , false ) )
      GetDestructableTypeId_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetDestructableX" , false ) )
      GetDestructableX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetDestructableY" , false ) )
      GetDestructableY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetDetectedUnit" , false ) )
      GetDetectedUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetDyingUnit" , false ) )
      GetDyingUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetEnemyBase" , false ) )
      GetEnemyBase_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetEnemyExpansion" , false ) )
      GetEnemyExpansion_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetEnemyPower" , false ) )
      GetEnemyPower_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetEnteringUnit" , false ) )
      GetEnteringUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetEnumDestructable" , false ) )
      GetEnumDestructable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetEnumItem" , false ) )
      GetEnumItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetEnumPlayer" , false ) )
      GetEnumPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetEnumUnit" , false ) )
      GetEnumUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetEventDamage" , false ) )
      GetEventDamage_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetEventDamageSource" , false ) )
      GetEventDamageSource_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetEventDetectingPlayer" , false ) )
      GetEventDetectingPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetEventGameState" , false ) )
      GetEventGameState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetEventPlayerChatString" , false ) )
      GetEventPlayerChatString_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetEventPlayerChatStringMatched" , false ) )
      GetEventPlayerChatStringMatched_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetEventPlayerState" , false ) )
      GetEventPlayerState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetEventTargetUnit" , false ) )
      GetEventTargetUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetEventUnitState" , false ) )
      GetEventUnitState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetExpansionFoe" , false ) )
      GetExpansionFoe_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetExpansionPeon" , false ) )
      GetExpansionPeon_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetExpansionX" , false ) )
      GetExpansionX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetExpansionY" , false ) )
      GetExpansionY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetExpiredTimer" , false ) )
      GetExpiredTimer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetFilterDestructable" , false ) )
      GetFilterDestructable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetFilterItem" , false ) )
      GetFilterItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetFilterPlayer" , false ) )
      GetFilterPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetFilterUnit" , false ) )
      GetFilterUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetFloatGameState" , false ) )
      GetFloatGameState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetFoodMade" , false ) )
      GetFoodMade_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetFoodUsed" , false ) )
      GetFoodUsed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetGameDifficulty" , false ) )
      GetGameDifficulty_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetGamePlacement" , false ) )
      GetGamePlacement_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetGameSpeed" , false ) )
      GetGameSpeed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetGameTypeSelected" , false ) )
      GetGameTypeSelected_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetGoldOwned" , false ) )
      GetGoldOwned_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetHandleId" , false ) )
      GetHandleId_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetHeroAgi" , false ) )
      GetHeroAgi_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetHeroId" , false ) )
      GetHeroId_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetHeroInt" , false ) )
      GetHeroInt_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetHeroLevel" , false ) )
      GetHeroLevel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetHeroLevelAI" , false ) )
      GetHeroLevelAI_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetHeroProperName" , false ) )
      GetHeroProperName_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetHeroSkillPoints" , false ) )
      GetHeroSkillPoints_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetHeroStr" , false ) )
      GetHeroStr_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetHeroXP" , false ) )
      GetHeroXP_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetIntegerGameState" , false ) )
      GetIntegerGameState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetIssuedOrderId" , false ) )
      GetIssuedOrderId_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetItemCharges" , false ) )
      GetItemCharges_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetItemLevel" , false ) )
      GetItemLevel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetItemName" , false ) )
      GetItemName_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetItemPlayer" , false ) )
      GetItemPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetItemType" , false ) )
      GetItemType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetItemTypeId" , false ) )
      GetItemTypeId_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetItemUserData" , false ) )
      GetItemUserData_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetItemX" , false ) )
      GetItemX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetItemY" , false ) )
      GetItemY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetKillingUnit" , false ) )
      GetKillingUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetLastCommand" , false ) )
      GetLastCommand_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetLastData" , false ) )
      GetLastData_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetLearnedSkill" , false ) )
      GetLearnedSkill_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetLearnedSkillLevel" , false ) )
      GetLearnedSkillLevel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetLearningUnit" , false ) )
      GetLearningUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetLeavingUnit" , false ) )
      GetLeavingUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetLevelingUnit" , false ) )
      GetLevelingUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetLightningColorA" , false ) )
      GetLightningColorA_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetLightningColorB" , false ) )
      GetLightningColorB_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetLightningColorG" , false ) )
      GetLightningColorG_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetLightningColorR" , false ) )
      GetLightningColorR_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetLoadedUnit" , false ) )
      GetLoadedUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetLocalPlayer" , false ) )
      GetLocalPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetLocalizedHotkey" , false ) )
      GetLocalizedHotkey_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetLocalizedString" , false ) )
      GetLocalizedString_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetLocationX" , false ) )
      GetLocationX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetLocationY" , false ) )
      GetLocationY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetLocationZ" , false ) )
      GetLocationZ_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetManipulatedItem" , false ) )
      GetManipulatedItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetManipulatingUnit" , false ) )
      GetManipulatingUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetMegaTarget" , false ) )
      GetMegaTarget_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetMinesOwned" , false ) )
      GetMinesOwned_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetNextExpansion" , false ) )
      GetNextExpansion_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetObjectName" , false ) )
      GetObjectName_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetOrderPointLoc" , false ) )
      GetOrderPointLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetOrderPointX" , false ) )
      GetOrderPointX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetOrderPointY" , false ) )
      GetOrderPointY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetOrderTarget" , false ) )
      GetOrderTarget_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetOrderTargetDestructable" , false ) )
      GetOrderTargetDestructable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetOrderTargetItem" , false ) )
      GetOrderTargetItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetOrderTargetUnit" , false ) )
      GetOrderTargetUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetOrderedUnit" , false ) )
      GetOrderedUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetOwningPlayer" , false ) )
      GetOwningPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerAlliance" , false ) )
      GetPlayerAlliance_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerColor" , false ) )
      GetPlayerColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerController" , false ) )
      GetPlayerController_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerHandicap" , false ) )
      GetPlayerHandicap_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerHandicapXP" , false ) )
      GetPlayerHandicapXP_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerId" , false ) )
      GetPlayerId_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerName" , false ) )
      GetPlayerName_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerRace" , false ) )
      GetPlayerRace_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerScore" , false ) )
      GetPlayerScore_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerSelectable" , false ) )
      GetPlayerSelectable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerSlotState" , false ) )
      GetPlayerSlotState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerStartLocation" , false ) )
      GetPlayerStartLocation_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerStartLocationX" , false ) )
      GetPlayerStartLocationX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerStartLocationY" , false ) )
      GetPlayerStartLocationY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerState" , false ) )
      GetPlayerState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerStructureCount" , false ) )
      GetPlayerStructureCount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerTaxRate" , false ) )
      GetPlayerTaxRate_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerTeam" , false ) )
      GetPlayerTeam_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerTechCount" , false ) )
      GetPlayerTechCount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerTechMaxAllowed" , false ) )
      GetPlayerTechMaxAllowed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerTechResearched" , false ) )
      GetPlayerTechResearched_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerTypedUnitCount" , false ) )
      GetPlayerTypedUnitCount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerUnitCount" , false ) )
      GetPlayerUnitCount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayerUnitTypeCount" , false ) )
      GetPlayerUnitTypeCount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetPlayers" , false ) )
      GetPlayers_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetRandomInt" , false ) )
      GetRandomInt_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetRandomReal" , false ) )
      GetRandomReal_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetRectCenterX" , false ) )
      GetRectCenterX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetRectCenterY" , false ) )
      GetRectCenterY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetRectMaxX" , false ) )
      GetRectMaxX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetRectMaxY" , false ) )
      GetRectMaxY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetRectMinX" , false ) )
      GetRectMinX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetRectMinY" , false ) )
      GetRectMinY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetRescuer" , false ) )
      GetRescuer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetResearched" , false ) )
      GetResearched_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetResearchingUnit" , false ) )
      GetResearchingUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetResourceAmount" , false ) )
      GetResourceAmount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetResourceDensity" , false ) )
      GetResourceDensity_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetRevivableUnit" , false ) )
      GetRevivableUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetRevivingUnit" , false ) )
      GetRevivingUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSaveBasicFilename" , false ) )
      GetSaveBasicFilename_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSellingUnit" , false ) )
      GetSellingUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSoldItem" , false ) )
      GetSoldItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSoldUnit" , false ) )
      GetSoldUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSoundDuration" , false ) )
      GetSoundDuration_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSoundFileDuration" , false ) )
      GetSoundFileDuration_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSoundIsLoading" , false ) )
      GetSoundIsLoading_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSoundIsPlaying" , false ) )
      GetSoundIsPlaying_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSpellAbility" , false ) )
      GetSpellAbility_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSpellAbilityId" , false ) )
      GetSpellAbilityId_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSpellAbilityUnit" , false ) )
      GetSpellAbilityUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSpellTargetDestructable" , false ) )
      GetSpellTargetDestructable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSpellTargetItem" , false ) )
      GetSpellTargetItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSpellTargetLoc" , false ) )
      GetSpellTargetLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSpellTargetUnit" , false ) )
      GetSpellTargetUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSpellTargetX" , false ) )
      GetSpellTargetX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSpellTargetY" , false ) )
      GetSpellTargetY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetStartLocPrio" , false ) )
      GetStartLocPrio_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetStartLocPrioSlot" , false ) )
      GetStartLocPrioSlot_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetStartLocationLoc" , false ) )
      GetStartLocationLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetStartLocationX" , false ) )
      GetStartLocationX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetStartLocationY" , false ) )
      GetStartLocationY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetStoredBoolean" , false ) )
      GetStoredBoolean_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetStoredInteger" , false ) )
      GetStoredInteger_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetStoredReal" , false ) )
      GetStoredReal_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetStoredString" , false ) )
      GetStoredString_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSummonedUnit" , false ) )
      GetSummonedUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetSummoningUnit" , false ) )
      GetSummoningUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTeams" , false ) )
      GetTeams_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTerrainCliffLevel" , false ) )
      GetTerrainCliffLevel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTerrainType" , false ) )
      GetTerrainType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTerrainVariance" , false ) )
      GetTerrainVariance_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTimeOfDayScale" , false ) )
      GetTimeOfDayScale_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTournamentFinishNowPlayer" , false ) )
      GetTournamentFinishNowPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTournamentFinishNowRule" , false ) )
      GetTournamentFinishNowRule_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTournamentFinishSoonTimeRemaining" , false ) )
      GetTournamentFinishSoonTimeRemaining_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTournamentScore" , false ) )
      GetTournamentScore_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTownUnitCount" , false ) )
      GetTownUnitCount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTrainedUnit" , false ) )
      GetTrainedUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTrainedUnitType" , false ) )
      GetTrainedUnitType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTransportUnit" , false ) )
      GetTransportUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTriggerDestructable" , false ) )
      GetTriggerDestructable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTriggerEvalCount" , false ) )
      GetTriggerEvalCount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTriggerEventId" , false ) )
      GetTriggerEventId_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTriggerExecCount" , false ) )
      GetTriggerExecCount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTriggerPlayer" , false ) )
      GetTriggerPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTriggerUnit" , false ) )
      GetTriggerUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTriggerWidget" , false ) )
      GetTriggerWidget_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTriggeringRegion" , false ) )
      GetTriggeringRegion_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTriggeringTrackable" , false ) )
      GetTriggeringTrackable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetTriggeringTrigger" , false ) )
      GetTriggeringTrigger_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitAbilityLevel" , false ) )
      GetUnitAbilityLevel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitAcquireRange" , false ) )
      GetUnitAcquireRange_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitBuildTime" , false ) )
      GetUnitBuildTime_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitCount" , false ) )
      GetUnitCount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitCountDone" , false ) )
      GetUnitCountDone_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitCurrentOrder" , false ) )
      GetUnitCurrentOrder_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitDefaultAcquireRange" , false ) )
      GetUnitDefaultAcquireRange_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitDefaultFlyHeight" , false ) )
      GetUnitDefaultFlyHeight_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitDefaultMoveSpeed" , false ) )
      GetUnitDefaultMoveSpeed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitDefaultPropWindow" , false ) )
      GetUnitDefaultPropWindow_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitDefaultTurnSpeed" , false ) )
      GetUnitDefaultTurnSpeed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitFacing" , false ) )
      GetUnitFacing_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitFlyHeight" , false ) )
      GetUnitFlyHeight_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitFoodMade" , false ) )
      GetUnitFoodMade_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitFoodUsed" , false ) )
      GetUnitFoodUsed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitGoldCost" , false ) )
      GetUnitGoldCost_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitLevel" , false ) )
      GetUnitLevel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitLoc" , false ) )
      GetUnitLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitMoveSpeed" , false ) )
      GetUnitMoveSpeed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitName" , false ) )
      GetUnitName_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitPointValue" , false ) )
      GetUnitPointValue_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitPointValueByType" , false ) )
      GetUnitPointValueByType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitPropWindow" , false ) )
      GetUnitPropWindow_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitRace" , false ) )
      GetUnitRace_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitRallyDestructable" , false ) )
      GetUnitRallyDestructable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitRallyPoint" , false ) )
      GetUnitRallyPoint_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitRallyUnit" , false ) )
      GetUnitRallyUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitState" , false ) )
      GetUnitState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitTurnSpeed" , false ) )
      GetUnitTurnSpeed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitTypeId" , false ) )
      GetUnitTypeId_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitUserData" , false ) )
      GetUnitUserData_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitWoodCost" , false ) )
      GetUnitWoodCost_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitX" , false ) )
      GetUnitX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUnitY" , false ) )
      GetUnitY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUpgradeGoldCost" , false ) )
      GetUpgradeGoldCost_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUpgradeLevel" , false ) )
      GetUpgradeLevel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetUpgradeWoodCost" , false ) )
      GetUpgradeWoodCost_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetWidgetLife" , false ) )
      GetWidgetLife_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetWidgetX" , false ) )
      GetWidgetX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetWidgetY" , false ) )
      GetWidgetY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetWinningPlayer" , false ) )
      GetWinningPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GetWorldBounds" , false ) )
      GetWorldBounds_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupAddUnit" , false ) )
      GroupAddUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupClear" , false ) )
      GroupClear_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupEnumUnitsInRange" , false ) )
      GroupEnumUnitsInRange_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupEnumUnitsInRangeCounted" , false ) )
      GroupEnumUnitsInRangeCounted_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupEnumUnitsInRangeOfLoc" , false ) )
      GroupEnumUnitsInRangeOfLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupEnumUnitsInRangeOfLocCounted" , false ) )
      GroupEnumUnitsInRangeOfLocCounted_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupEnumUnitsInRect" , false ) )
      GroupEnumUnitsInRect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupEnumUnitsInRectCounted" , false ) )
      GroupEnumUnitsInRectCounted_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupEnumUnitsOfPlayer" , false ) )
      GroupEnumUnitsOfPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupEnumUnitsOfType" , false ) )
      GroupEnumUnitsOfType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupEnumUnitsOfTypeCounted" , false ) )
      GroupEnumUnitsOfTypeCounted_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupEnumUnitsSelected" , false ) )
      GroupEnumUnitsSelected_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupImmediateOrder" , false ) )
      GroupImmediateOrder_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupImmediateOrderById" , false ) )
      GroupImmediateOrderById_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupPointOrder" , false ) )
      GroupPointOrder_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupPointOrderById" , false ) )
      GroupPointOrderById_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupPointOrderByIdLoc" , false ) )
      GroupPointOrderByIdLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupPointOrderLoc" , false ) )
      GroupPointOrderLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupRemoveUnit" , false ) )
      GroupRemoveUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupTargetOrder" , false ) )
      GroupTargetOrder_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupTargetOrderById" , false ) )
      GroupTargetOrderById_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "GroupTimedLife" , false ) )
      GroupTimedLife_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "HarvestGold" , false ) )
      HarvestGold_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "HarvestWood" , false ) )
      HarvestWood_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "HaveSavedBoolean" , false ) )
      HaveSavedBoolean_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "HaveSavedHandle" , false ) )
      HaveSavedHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "HaveSavedInteger" , false ) )
      HaveSavedInteger_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "HaveSavedReal" , false ) )
      HaveSavedReal_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "HaveSavedString" , false ) )
      HaveSavedString_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "HaveStoredBoolean" , false ) )
      HaveStoredBoolean_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "HaveStoredInteger" , false ) )
      HaveStoredInteger_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "HaveStoredReal" , false ) )
      HaveStoredReal_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "HaveStoredString" , false ) )
      HaveStoredString_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "HaveStoredUnit" , false ) )
      HaveStoredUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "I2R" , false ) )
      I2R_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "I2S" , false ) )
      I2S_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IgnoredUnits" , false ) )
      IgnoredUnits_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IncUnitAbilityLevel" , false ) )
      IncUnitAbilityLevel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "InitAssault" , false ) )
      InitAssault_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "InitGameCache" , false ) )
      InitGameCache_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "InitHashtable" , false ) )
      InitHashtable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsCineFilterDisplayed" , false ) )
      IsCineFilterDisplayed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsDestructableInvulnerable" , false ) )
      IsDestructableInvulnerable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsFogEnabled" , false ) )
      IsFogEnabled_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsFogMaskEnabled" , false ) )
      IsFogMaskEnabled_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsFoggedToPlayer" , false ) )
      IsFoggedToPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsGameTypeSupported" , false ) )
      IsGameTypeSupported_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsHeroUnitId" , false ) )
      IsHeroUnitId_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsItemIdPawnable" , false ) )
      IsItemIdPawnable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsItemIdPowerup" , false ) )
      IsItemIdPowerup_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsItemIdSellable" , false ) )
      IsItemIdSellable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsItemInvulnerable" , false ) )
      IsItemInvulnerable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsItemOwned" , false ) )
      IsItemOwned_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsItemPawnable" , false ) )
      IsItemPawnable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsItemPowerup" , false ) )
      IsItemPowerup_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsItemSellable" , false ) )
      IsItemSellable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsItemVisible" , false ) )
      IsItemVisible_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsLeaderboardDisplayed" , false ) )
      IsLeaderboardDisplayed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsLocationFoggedToPlayer" , false ) )
      IsLocationFoggedToPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsLocationInRegion" , false ) )
      IsLocationInRegion_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsLocationMaskedToPlayer" , false ) )
      IsLocationMaskedToPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsLocationVisibleToPlayer" , false ) )
      IsLocationVisibleToPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsMapFlagSet" , false ) )
      IsMapFlagSet_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsMaskedToPlayer" , false ) )
      IsMaskedToPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsMultiboardDisplayed" , false ) )
      IsMultiboardDisplayed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsMultiboardMinimized" , false ) )
      IsMultiboardMinimized_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsNoDefeatCheat" , false ) )
      IsNoDefeatCheat_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsNoVictoryCheat" , false ) )
      IsNoVictoryCheat_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsPlayerAlly" , false ) )
      IsPlayerAlly_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsPlayerEnemy" , false ) )
      IsPlayerEnemy_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsPlayerInForce" , false ) )
      IsPlayerInForce_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsPlayerObserver" , false ) )
      IsPlayerObserver_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsPlayerRacePrefSet" , false ) )
      IsPlayerRacePrefSet_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsPointBlighted" , false ) )
      IsPointBlighted_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsPointInRegion" , false ) )
      IsPointInRegion_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsQuestCompleted" , false ) )
      IsQuestCompleted_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsQuestDiscovered" , false ) )
      IsQuestDiscovered_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsQuestEnabled" , false ) )
      IsQuestEnabled_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsQuestFailed" , false ) )
      IsQuestFailed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsQuestItemCompleted" , false ) )
      IsQuestItemCompleted_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsQuestRequired" , false ) )
      IsQuestRequired_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsSuspendedXP" , false ) )
      IsSuspendedXP_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsTerrainPathable" , false ) )
      IsTerrainPathable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsTimerDialogDisplayed" , false ) )
      IsTimerDialogDisplayed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsTowered" , false ) )
      IsTowered_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsTriggerEnabled" , false ) )
      IsTriggerEnabled_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsTriggerWaitOnSleeps" , false ) )
      IsTriggerWaitOnSleeps_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnit" , false ) )
      IsUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitAlly" , false ) )
      IsUnitAlly_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitDetected" , false ) )
      IsUnitDetected_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitEnemy" , false ) )
      IsUnitEnemy_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitFogged" , false ) )
      IsUnitFogged_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitHidden" , false ) )
      IsUnitHidden_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitIdType" , false ) )
      IsUnitIdType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitIllusion" , false ) )
      IsUnitIllusion_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitInForce" , false ) )
      IsUnitInForce_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitInGroup" , false ) )
      IsUnitInGroup_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitInRange" , false ) )
      IsUnitInRange_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitInRangeLoc" , false ) )
      IsUnitInRangeLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitInRangeXY" , false ) )
      IsUnitInRangeXY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitInRegion" , false ) )
      IsUnitInRegion_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitInTransport" , false ) )
      IsUnitInTransport_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitInvisible" , false ) )
      IsUnitInvisible_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitLoaded" , false ) )
      IsUnitLoaded_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitMasked" , false ) )
      IsUnitMasked_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitOwnedByPlayer" , false ) )
      IsUnitOwnedByPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitPaused" , false ) )
      IsUnitPaused_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitRace" , false ) )
      IsUnitRace_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitSelected" , false ) )
      IsUnitSelected_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitType" , false ) )
      IsUnitType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsUnitVisible" , false ) )
      IsUnitVisible_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IsVisibleToPlayer" , false ) )
      IsVisibleToPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssueBuildOrder" , false ) )
      IssueBuildOrder_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssueBuildOrderById" , false ) )
      IssueBuildOrderById_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssueImmediateOrder" , false ) )
      IssueImmediateOrder_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssueImmediateOrderById" , false ) )
      IssueImmediateOrderById_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssueInstantPointOrder" , false ) )
      IssueInstantPointOrder_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssueInstantPointOrderById" , false ) )
      IssueInstantPointOrderById_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssueInstantTargetOrder" , false ) )
      IssueInstantTargetOrder_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssueInstantTargetOrderById" , false ) )
      IssueInstantTargetOrderById_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssueNeutralImmediateOrder" , false ) )
      IssueNeutralImmediateOrder_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssueNeutralImmediateOrderById" , false ) )
      IssueNeutralImmediateOrderById_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssueNeutralPointOrder" , false ) )
      IssueNeutralPointOrder_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssueNeutralPointOrderById" , false ) )
      IssueNeutralPointOrderById_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssueNeutralTargetOrder" , false ) )
      IssueNeutralTargetOrder_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssueNeutralTargetOrderById" , false ) )
      IssueNeutralTargetOrderById_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssuePointOrder" , false ) )
      IssuePointOrder_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssuePointOrderById" , false ) )
      IssuePointOrderById_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssuePointOrderByIdLoc" , false ) )
      IssuePointOrderByIdLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssuePointOrderLoc" , false ) )
      IssuePointOrderLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssueTargetOrder" , false ) )
      IssueTargetOrder_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "IssueTargetOrderById" , false ) )
      IssueTargetOrderById_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ItemPoolAddItemType" , false ) )
      ItemPoolAddItemType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ItemPoolRemoveItemType" , false ) )
      ItemPoolRemoveItemType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "KillDestructable" , false ) )
      KillDestructable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "KillSoundWhenDone" , false ) )
      KillSoundWhenDone_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "KillUnit" , false ) )
      KillUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardAddItem" , false ) )
      LeaderboardAddItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardClear" , false ) )
      LeaderboardClear_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardDisplay" , false ) )
      LeaderboardDisplay_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardGetItemCount" , false ) )
      LeaderboardGetItemCount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardGetLabelText" , false ) )
      LeaderboardGetLabelText_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardGetPlayerIndex" , false ) )
      LeaderboardGetPlayerIndex_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardHasPlayerItem" , false ) )
      LeaderboardHasPlayerItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardRemoveItem" , false ) )
      LeaderboardRemoveItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardRemovePlayerItem" , false ) )
      LeaderboardRemovePlayerItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardSetItemLabel" , false ) )
      LeaderboardSetItemLabel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardSetItemLabelColor" , false ) )
      LeaderboardSetItemLabelColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardSetItemStyle" , false ) )
      LeaderboardSetItemStyle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardSetItemValue" , false ) )
      LeaderboardSetItemValue_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardSetItemValueColor" , false ) )
      LeaderboardSetItemValueColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardSetLabel" , false ) )
      LeaderboardSetLabel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardSetLabelColor" , false ) )
      LeaderboardSetLabelColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardSetSizeByItemCount" , false ) )
      LeaderboardSetSizeByItemCount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardSetStyle" , false ) )
      LeaderboardSetStyle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardSetValueColor" , false ) )
      LeaderboardSetValueColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardSortItemsByLabel" , false ) )
      LeaderboardSortItemsByLabel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardSortItemsByPlayer" , false ) )
      LeaderboardSortItemsByPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LeaderboardSortItemsByValue" , false ) )
      LeaderboardSortItemsByValue_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadAbilityHandle" , false ) )
      LoadAbilityHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadBoolean" , false ) )
      LoadBoolean_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadBooleanExprHandle" , false ) )
      LoadBooleanExprHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadButtonHandle" , false ) )
      LoadButtonHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadDefeatConditionHandle" , false ) )
      LoadDefeatConditionHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadDestructableHandle" , false ) )
      LoadDestructableHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadDialogHandle" , false ) )
      LoadDialogHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadEffectHandle" , false ) )
      LoadEffectHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadFogModifierHandle" , false ) )
      LoadFogModifierHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadFogStateHandle" , false ) )
      LoadFogStateHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadForceHandle" , false ) )
      LoadForceHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadGame" , false ) )
      LoadGame_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadGroupHandle" , false ) )
      LoadGroupHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadHashtableHandle" , false ) )
      LoadHashtableHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadImageHandle" , false ) )
      LoadImageHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadInteger" , false ) )
      LoadInteger_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadItemHandle" , false ) )
      LoadItemHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadItemPoolHandle" , false ) )
      LoadItemPoolHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadLeaderboardHandle" , false ) )
      LoadLeaderboardHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadLightningHandle" , false ) )
      LoadLightningHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadLocationHandle" , false ) )
      LoadLocationHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadMultiboardHandle" , false ) )
      LoadMultiboardHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadMultiboardItemHandle" , false ) )
      LoadMultiboardItemHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadPlayerHandle" , false ) )
      LoadPlayerHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadQuestHandle" , false ) )
      LoadQuestHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadQuestItemHandle" , false ) )
      LoadQuestItemHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadReal" , false ) )
      LoadReal_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadRectHandle" , false ) )
      LoadRectHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadRegionHandle" , false ) )
      LoadRegionHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadSoundHandle" , false ) )
      LoadSoundHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadStr" , false ) )
      LoadStr_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadTextTagHandle" , false ) )
      LoadTextTagHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadTimerDialogHandle" , false ) )
      LoadTimerDialogHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadTimerHandle" , false ) )
      LoadTimerHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadTrackableHandle" , false ) )
      LoadTrackableHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadTriggerActionHandle" , false ) )
      LoadTriggerActionHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadTriggerConditionHandle" , false ) )
      LoadTriggerConditionHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadTriggerEventHandle" , false ) )
      LoadTriggerEventHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadTriggerHandle" , false ) )
      LoadTriggerHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadUbersplatHandle" , false ) )
      LoadUbersplatHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadUnitHandle" , false ) )
      LoadUnitHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadUnitPoolHandle" , false ) )
      LoadUnitPoolHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadWidgetHandle" , false ) )
      LoadWidgetHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "LoadZepWave" , false ) )
      LoadZepWave_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Location" , false ) )
      Location_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MeleeDifficulty" , false ) )
      MeleeDifficulty_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MergeUnits" , false ) )
      MergeUnits_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MoveLightning" , false ) )
      MoveLightning_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MoveLightningEx" , false ) )
      MoveLightningEx_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MoveLocation" , false ) )
      MoveLocation_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MoveRectTo" , false ) )
      MoveRectTo_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MoveRectToLoc" , false ) )
      MoveRectToLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardClear" , false ) )
      MultiboardClear_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardDisplay" , false ) )
      MultiboardDisplay_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardGetColumnCount" , false ) )
      MultiboardGetColumnCount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardGetItem" , false ) )
      MultiboardGetItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardGetRowCount" , false ) )
      MultiboardGetRowCount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardGetTitleText" , false ) )
      MultiboardGetTitleText_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardMinimize" , false ) )
      MultiboardMinimize_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardReleaseItem" , false ) )
      MultiboardReleaseItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardSetColumnCount" , false ) )
      MultiboardSetColumnCount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardSetItemIcon" , false ) )
      MultiboardSetItemIcon_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardSetItemStyle" , false ) )
      MultiboardSetItemStyle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardSetItemValue" , false ) )
      MultiboardSetItemValue_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardSetItemValueColor" , false ) )
      MultiboardSetItemValueColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardSetItemWidth" , false ) )
      MultiboardSetItemWidth_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardSetItemsIcon" , false ) )
      MultiboardSetItemsIcon_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardSetItemsStyle" , false ) )
      MultiboardSetItemsStyle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardSetItemsValue" , false ) )
      MultiboardSetItemsValue_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardSetItemsValueColor" , false ) )
      MultiboardSetItemsValueColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardSetItemsWidth" , false ) )
      MultiboardSetItemsWidth_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardSetRowCount" , false ) )
      MultiboardSetRowCount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardSetTitleText" , false ) )
      MultiboardSetTitleText_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardSetTitleTextColor" , false ) )
      MultiboardSetTitleTextColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "MultiboardSuppressDisplay" , false ) )
      MultiboardSuppressDisplay_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "NewSoundEnvironment" , false ) )
      NewSoundEnvironment_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Not" , false ) )
      Not_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Or" , false ) )
      Or_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "OrderId" , false ) )
      OrderId_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "OrderId2String" , false ) )
      OrderId2String_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PanCameraTo" , false ) )
      PanCameraTo_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PanCameraToTimed" , false ) )
      PanCameraToTimed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PanCameraToTimedWithZ" , false ) )
      PanCameraToTimedWithZ_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PanCameraToWithZ" , false ) )
      PanCameraToWithZ_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PauseCompAI" , false ) )
      PauseCompAI_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PauseGame" , false ) )
      PauseGame_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PauseTimer" , false ) )
      PauseTimer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PauseUnit" , false ) )
      PauseUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PingMinimap" , false ) )
      PingMinimap_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PingMinimapEx" , false ) )
      PingMinimapEx_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PlaceRandomItem" , false ) )
      PlaceRandomItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PlaceRandomUnit" , false ) )
      PlaceRandomUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PlayCinematic" , false ) )
      PlayCinematic_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PlayModelCinematic" , false ) )
      PlayModelCinematic_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PlayMusic" , false ) )
      PlayMusic_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PlayMusicEx" , false ) )
      PlayMusicEx_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PlayThematicMusic" , false ) )
      PlayThematicMusic_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PlayThematicMusicEx" , false ) )
      PlayThematicMusicEx_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Player" , false ) )
      Player_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PlayerGetLeaderboard" , false ) )
      PlayerGetLeaderboard_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PlayerSetLeaderboard" , false ) )
      PlayerSetLeaderboard_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PopLastCommand" , false ) )
      PopLastCommand_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Pow" , false ) )
      Pow_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Preload" , false ) )
      Preload_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PreloadEnd" , false ) )
      PreloadEnd_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PreloadEndEx" , false ) )
      PreloadEndEx_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PreloadGenClear" , false ) )
      PreloadGenClear_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PreloadGenEnd" , false ) )
      PreloadGenEnd_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PreloadGenStart" , false ) )
      PreloadGenStart_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PreloadRefresh" , false ) )
      PreloadRefresh_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PreloadStart" , false ) )
      PreloadStart_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Preloader" , false ) )
      Preloader_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "PurchaseZeppelin" , false ) )
      PurchaseZeppelin_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "QuestCreateItem" , false ) )
      QuestCreateItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "QuestItemSetCompleted" , false ) )
      QuestItemSetCompleted_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "QuestItemSetDescription" , false ) )
      QuestItemSetDescription_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "QuestSetCompleted" , false ) )
      QuestSetCompleted_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "QuestSetDescription" , false ) )
      QuestSetDescription_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "QuestSetDiscovered" , false ) )
      QuestSetDiscovered_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "QuestSetEnabled" , false ) )
      QuestSetEnabled_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "QuestSetFailed" , false ) )
      QuestSetFailed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "QuestSetIconPath" , false ) )
      QuestSetIconPath_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "QuestSetRequired" , false ) )
      QuestSetRequired_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "QuestSetTitle" , false ) )
      QuestSetTitle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "QueueDestructableAnimation" , false ) )
      QueueDestructableAnimation_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "QueueUnitAnimation" , false ) )
      QueueUnitAnimation_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "R2I" , false ) )
      R2I_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "R2S" , false ) )
      R2S_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "R2SW" , false ) )
      R2SW_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Rad2Deg" , false ) )
      Rad2Deg_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Rect" , false ) )
      Rect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RectFromLoc" , false ) )
      RectFromLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RecycleGuardPosition" , false ) )
      RecycleGuardPosition_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RegionAddCell" , false ) )
      RegionAddCell_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RegionAddCellAtLoc" , false ) )
      RegionAddCellAtLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RegionAddRect" , false ) )
      RegionAddRect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RegionClearCell" , false ) )
      RegionClearCell_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RegionClearCellAtLoc" , false ) )
      RegionClearCellAtLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RegionClearRect" , false ) )
      RegionClearRect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RegisterStackedSound" , false ) )
      RegisterStackedSound_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ReloadGame" , false ) )
      ReloadGame_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ReloadGameCachesFromDisk" , false ) )
      ReloadGameCachesFromDisk_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveAllGuardPositions" , false ) )
      RemoveAllGuardPositions_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveDestructable" , false ) )
      RemoveDestructable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveGuardPosition" , false ) )
      RemoveGuardPosition_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveInjuries" , false ) )
      RemoveInjuries_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveItem" , false ) )
      RemoveItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveItemFromAllStock" , false ) )
      RemoveItemFromAllStock_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveItemFromStock" , false ) )
      RemoveItemFromStock_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveLocation" , false ) )
      RemoveLocation_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemovePlayer" , false ) )
      RemovePlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveRect" , false ) )
      RemoveRect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveRegion" , false ) )
      RemoveRegion_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveSaveDirectory" , false ) )
      RemoveSaveDirectory_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveSavedBoolean" , false ) )
      RemoveSavedBoolean_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveSavedHandle" , false ) )
      RemoveSavedHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveSavedInteger" , false ) )
      RemoveSavedInteger_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveSavedReal" , false ) )
      RemoveSavedReal_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveSavedString" , false ) )
      RemoveSavedString_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveSiege" , false ) )
      RemoveSiege_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveUnit" , false ) )
      RemoveUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveUnitFromAllStock" , false ) )
      RemoveUnitFromAllStock_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveUnitFromStock" , false ) )
      RemoveUnitFromStock_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RemoveWeatherEffect" , false ) )
      RemoveWeatherEffect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RenameSaveDirectory" , false ) )
      RenameSaveDirectory_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ResetCaptainLocs" , false ) )
      ResetCaptainLocs_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ResetTerrainFog" , false ) )
      ResetTerrainFog_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ResetToGameCamera" , false ) )
      ResetToGameCamera_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ResetTrigger" , false ) )
      ResetTrigger_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ResetUbersplat" , false ) )
      ResetUbersplat_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ResetUnitLookAt" , false ) )
      ResetUnitLookAt_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RestartGame" , false ) )
      RestartGame_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "RestoreUnit" , false ) )
      RestoreUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ResumeMusic" , false ) )
      ResumeMusic_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ResumeTimer" , false ) )
      ResumeTimer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ReturnGuardPosts" , false ) )
      ReturnGuardPosts_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ReviveHero" , false ) )
      ReviveHero_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ReviveHeroLoc" , false ) )
      ReviveHeroLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "S2I" , false ) )
      S2I_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "S2R" , false ) )
      S2R_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveAbilityHandle" , false ) )
      SaveAbilityHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveAgentHandle" , false ) )
      SaveAgentHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveBoolean" , false ) )
      SaveBoolean_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveBooleanExprHandle" , false ) )
      SaveBooleanExprHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveButtonHandle" , false ) )
      SaveButtonHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveDefeatConditionHandle" , false ) )
      SaveDefeatConditionHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveDestructableHandle" , false ) )
      SaveDestructableHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveDialogHandle" , false ) )
      SaveDialogHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveEffectHandle" , false ) )
      SaveEffectHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveFogModifierHandle" , false ) )
      SaveFogModifierHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveFogStateHandle" , false ) )
      SaveFogStateHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveForceHandle" , false ) )
      SaveForceHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveGame" , false ) )
      SaveGame_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveGameCache" , false ) )
      SaveGameCache_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveGameExists" , false ) )
      SaveGameExists_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveGroupHandle" , false ) )
      SaveGroupHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveHashtableHandle" , false ) )
      SaveHashtableHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveImageHandle" , false ) )
      SaveImageHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveInteger" , false ) )
      SaveInteger_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveItemHandle" , false ) )
      SaveItemHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveItemPoolHandle" , false ) )
      SaveItemPoolHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveLeaderboardHandle" , false ) )
      SaveLeaderboardHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveLightningHandle" , false ) )
      SaveLightningHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveLocationHandle" , false ) )
      SaveLocationHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveMultiboardHandle" , false ) )
      SaveMultiboardHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveMultiboardItemHandle" , false ) )
      SaveMultiboardItemHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SavePlayerHandle" , false ) )
      SavePlayerHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveQuestHandle" , false ) )
      SaveQuestHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveQuestItemHandle" , false ) )
      SaveQuestItemHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveReal" , false ) )
      SaveReal_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveRectHandle" , false ) )
      SaveRectHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveRegionHandle" , false ) )
      SaveRegionHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveSoundHandle" , false ) )
      SaveSoundHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveStr" , false ) )
      SaveStr_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveTextTagHandle" , false ) )
      SaveTextTagHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveTimerDialogHandle" , false ) )
      SaveTimerDialogHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveTimerHandle" , false ) )
      SaveTimerHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveTrackableHandle" , false ) )
      SaveTrackableHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveTriggerActionHandle" , false ) )
      SaveTriggerActionHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveTriggerConditionHandle" , false ) )
      SaveTriggerConditionHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveTriggerEventHandle" , false ) )
      SaveTriggerEventHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveTriggerHandle" , false ) )
      SaveTriggerHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveUbersplatHandle" , false ) )
      SaveUbersplatHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveUnitHandle" , false ) )
      SaveUnitHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveUnitPoolHandle" , false ) )
      SaveUnitPoolHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SaveWidgetHandle" , false ) )
      SaveWidgetHandle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SelectHeroSkill" , false ) )
      SelectHeroSkill_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SelectUnit" , false ) )
      SelectUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetAllItemTypeSlots" , false ) )
      SetAllItemTypeSlots_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetAllUnitTypeSlots" , false ) )
      SetAllUnitTypeSlots_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetAllianceTarget" , false ) )
      SetAllianceTarget_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetAllyColorFilterState" , false ) )
      SetAllyColorFilterState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetAltMinimapIcon" , false ) )
      SetAltMinimapIcon_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetAmphibious" , false ) )
      SetAmphibious_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetBlight" , false ) )
      SetBlight_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetBlightLoc" , false ) )
      SetBlightLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetBlightPoint" , false ) )
      SetBlightPoint_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetBlightRect" , false ) )
      SetBlightRect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCameraBounds" , false ) )
      SetCameraBounds_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCameraField" , false ) )
      SetCameraField_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCameraOrientController" , false ) )
      SetCameraOrientController_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCameraPosition" , false ) )
      SetCameraPosition_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCameraQuickPosition" , false ) )
      SetCameraQuickPosition_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCameraRotateMode" , false ) )
      SetCameraRotateMode_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCameraTargetController" , false ) )
      SetCameraTargetController_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCampaignAI" , false ) )
      SetCampaignAI_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCampaignAvailable" , false ) )
      SetCampaignAvailable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCampaignMenuRace" , false ) )
      SetCampaignMenuRace_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCampaignMenuRaceEx" , false ) )
      SetCampaignMenuRaceEx_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCaptainChanges" , false ) )
      SetCaptainChanges_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCaptainHome" , false ) )
      SetCaptainHome_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCineFilterBlendMode" , false ) )
      SetCineFilterBlendMode_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCineFilterDuration" , false ) )
      SetCineFilterDuration_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCineFilterEndColor" , false ) )
      SetCineFilterEndColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCineFilterEndUV" , false ) )
      SetCineFilterEndUV_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCineFilterStartColor" , false ) )
      SetCineFilterStartColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCineFilterStartUV" , false ) )
      SetCineFilterStartUV_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCineFilterTexMapFlags" , false ) )
      SetCineFilterTexMapFlags_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCineFilterTexture" , false ) )
      SetCineFilterTexture_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCinematicCamera" , false ) )
      SetCinematicCamera_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCinematicScene" , false ) )
      SetCinematicScene_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCreatureDensity" , false ) )
      SetCreatureDensity_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCreepCampFilterState" , false ) )
      SetCreepCampFilterState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetCustomCampaignButtonVisible" , false ) )
      SetCustomCampaignButtonVisible_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetDayNightModels" , false ) )
      SetDayNightModels_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetDefaultDifficulty" , false ) )
      SetDefaultDifficulty_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetDefendPlayer" , false ) )
      SetDefendPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetDestructableAnimation" , false ) )
      SetDestructableAnimation_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetDestructableAnimationSpeed" , false ) )
      SetDestructableAnimationSpeed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetDestructableInvulnerable" , false ) )
      SetDestructableInvulnerable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetDestructableLife" , false ) )
      SetDestructableLife_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetDestructableMaxLife" , false ) )
      SetDestructableMaxLife_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetDestructableOccluderHeight" , false ) )
      SetDestructableOccluderHeight_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetDoodadAnimation" , false ) )
      SetDoodadAnimation_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetDoodadAnimationRect" , false ) )
      SetDoodadAnimationRect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetEdCinematicAvailable" , false ) )
      SetEdCinematicAvailable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetExpansion" , false ) )
      SetExpansion_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetFloatGameState" , false ) )
      SetFloatGameState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetFogStateRadius" , false ) )
      SetFogStateRadius_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetFogStateRadiusLoc" , false ) )
      SetFogStateRadiusLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetFogStateRect" , false ) )
      SetFogStateRect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetGameDifficulty" , false ) )
      SetGameDifficulty_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetGamePlacement" , false ) )
      SetGamePlacement_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetGameSpeed" , false ) )
      SetGameSpeed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetGameTypeSupported" , false ) )
      SetGameTypeSupported_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetGroupsFlee" , false ) )
      SetGroupsFlee_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetHeroAgi" , false ) )
      SetHeroAgi_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetHeroInt" , false ) )
      SetHeroInt_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetHeroLevel" , false ) )
      SetHeroLevel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetHeroLevels" , false ) )
      SetHeroLevels_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetHeroStr" , false ) )
      SetHeroStr_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetHeroXP" , false ) )
      SetHeroXP_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetHeroesBuyItems" , false ) )
      SetHeroesBuyItems_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetHeroesFlee" , false ) )
      SetHeroesFlee_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetHeroesTakeItems" , false ) )
      SetHeroesTakeItems_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetIgnoreInjured" , false ) )
      SetIgnoreInjured_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetImageAboveWater" , false ) )
      SetImageAboveWater_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetImageColor" , false ) )
      SetImageColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetImageConstantHeight" , false ) )
      SetImageConstantHeight_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetImagePosition" , false ) )
      SetImagePosition_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetImageRender" , false ) )
      SetImageRender_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetImageRenderAlways" , false ) )
      SetImageRenderAlways_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetImageType" , false ) )
      SetImageType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetIntegerGameState" , false ) )
      SetIntegerGameState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetIntroShotModel" , false ) )
      SetIntroShotModel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetIntroShotText" , false ) )
      SetIntroShotText_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetItemCharges" , false ) )
      SetItemCharges_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetItemDropID" , false ) )
      SetItemDropID_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetItemDropOnDeath" , false ) )
      SetItemDropOnDeath_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetItemDroppable" , false ) )
      SetItemDroppable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetItemInvulnerable" , false ) )
      SetItemInvulnerable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetItemPawnable" , false ) )
      SetItemPawnable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetItemPlayer" , false ) )
      SetItemPlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetItemPosition" , false ) )
      SetItemPosition_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetItemTypeSlots" , false ) )
      SetItemTypeSlots_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetItemUserData" , false ) )
      SetItemUserData_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetItemVisible" , false ) )
      SetItemVisible_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetLightningColor" , false ) )
      SetLightningColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetMapDescription" , false ) )
      SetMapDescription_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetMapFlag" , false ) )
      SetMapFlag_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetMapMusic" , false ) )
      SetMapMusic_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetMapName" , false ) )
      SetMapName_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetMeleeAI" , false ) )
      SetMeleeAI_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetMissionAvailable" , false ) )
      SetMissionAvailable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetMusicPlayPosition" , false ) )
      SetMusicPlayPosition_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetMusicVolume" , false ) )
      SetMusicVolume_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetNewHeroes" , false ) )
      SetNewHeroes_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetOpCinematicAvailable" , false ) )
      SetOpCinematicAvailable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPeonsRepair" , false ) )
      SetPeonsRepair_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPlayerAbilityAvailable" , false ) )
      SetPlayerAbilityAvailable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPlayerAlliance" , false ) )
      SetPlayerAlliance_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPlayerColor" , false ) )
      SetPlayerColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPlayerController" , false ) )
      SetPlayerController_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPlayerHandicap" , false ) )
      SetPlayerHandicap_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPlayerHandicapXP" , false ) )
      SetPlayerHandicapXP_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPlayerName" , false ) )
      SetPlayerName_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPlayerOnScoreScreen" , false ) )
      SetPlayerOnScoreScreen_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPlayerRacePreference" , false ) )
      SetPlayerRacePreference_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPlayerRaceSelectable" , false ) )
      SetPlayerRaceSelectable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPlayerStartLocation" , false ) )
      SetPlayerStartLocation_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPlayerState" , false ) )
      SetPlayerState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPlayerTaxRate" , false ) )
      SetPlayerTaxRate_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPlayerTeam" , false ) )
      SetPlayerTeam_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPlayerTechMaxAllowed" , false ) )
      SetPlayerTechMaxAllowed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPlayerTechResearched" , false ) )
      SetPlayerTechResearched_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPlayerUnitsOwner" , false ) )
      SetPlayerUnitsOwner_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetPlayers" , false ) )
      SetPlayers_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetProduce" , false ) )
      SetProduce_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetRandomPaths" , false ) )
      SetRandomPaths_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetRandomSeed" , false ) )
      SetRandomSeed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetRect" , false ) )
      SetRect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetRectFromLoc" , false ) )
      SetRectFromLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetReplacementCount" , false ) )
      SetReplacementCount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetReservedLocalHeroButtons" , false ) )
      SetReservedLocalHeroButtons_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetResourceAmount" , false ) )
      SetResourceAmount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetResourceDensity" , false ) )
      SetResourceDensity_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetSkyModel" , false ) )
      SetSkyModel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetSlowChopping" , false ) )
      SetSlowChopping_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetSmartArtillery" , false ) )
      SetSmartArtillery_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetSoundChannel" , false ) )
      SetSoundChannel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetSoundConeAngles" , false ) )
      SetSoundConeAngles_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetSoundConeOrientation" , false ) )
      SetSoundConeOrientation_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetSoundDistanceCutoff" , false ) )
      SetSoundDistanceCutoff_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetSoundDistances" , false ) )
      SetSoundDistances_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetSoundDuration" , false ) )
      SetSoundDuration_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetSoundParamsFromLabel" , false ) )
      SetSoundParamsFromLabel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetSoundPitch" , false ) )
      SetSoundPitch_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetSoundPlayPosition" , false ) )
      SetSoundPlayPosition_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetSoundPosition" , false ) )
      SetSoundPosition_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetSoundVelocity" , false ) )
      SetSoundVelocity_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetSoundVolume" , false ) )
      SetSoundVolume_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetStackedSound" , false ) )
      SetStackedSound_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetStackedSoundRect" , false ) )
      SetStackedSoundRect_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetStagePoint" , false ) )
      SetStagePoint_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetStartLocPrio" , false ) )
      SetStartLocPrio_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetStartLocPrioCount" , false ) )
      SetStartLocPrioCount_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTargetHeroes" , false ) )
      SetTargetHeroes_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTeams" , false ) )
      SetTeams_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTerrainFog" , false ) )
      SetTerrainFog_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTerrainFogEx" , false ) )
      SetTerrainFogEx_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTerrainPathable" , false ) )
      SetTerrainPathable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTerrainType" , false ) )
      SetTerrainType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTextTagAge" , false ) )
      SetTextTagAge_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTextTagColor" , false ) )
      SetTextTagColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTextTagFadepoint" , false ) )
      SetTextTagFadepoint_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTextTagLifespan" , false ) )
      SetTextTagLifespan_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTextTagPermanent" , false ) )
      SetTextTagPermanent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTextTagPos" , false ) )
      SetTextTagPos_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTextTagPosUnit" , false ) )
      SetTextTagPosUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTextTagSuspended" , false ) )
      SetTextTagSuspended_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTextTagText" , false ) )
      SetTextTagText_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTextTagVelocity" , false ) )
      SetTextTagVelocity_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTextTagVisibility" , false ) )
      SetTextTagVisibility_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetThematicMusicPlayPosition" , false ) )
      SetThematicMusicPlayPosition_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTimeOfDayScale" , false ) )
      SetTimeOfDayScale_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetTutorialCleared" , false ) )
      SetTutorialCleared_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUbersplatRender" , false ) )
      SetUbersplatRender_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUbersplatRenderAlways" , false ) )
      SetUbersplatRenderAlways_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitAbilityLevel" , false ) )
      SetUnitAbilityLevel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitAcquireRange" , false ) )
      SetUnitAcquireRange_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitAnimation" , false ) )
      SetUnitAnimation_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitAnimationByIndex" , false ) )
      SetUnitAnimationByIndex_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitAnimationWithRarity" , false ) )
      SetUnitAnimationWithRarity_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitBlendTime" , false ) )
      SetUnitBlendTime_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitColor" , false ) )
      SetUnitColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitCreepGuard" , false ) )
      SetUnitCreepGuard_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitExploded" , false ) )
      SetUnitExploded_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitFacing" , false ) )
      SetUnitFacing_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitFacingTimed" , false ) )
      SetUnitFacingTimed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitFlyHeight" , false ) )
      SetUnitFlyHeight_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitFog" , false ) )
      SetUnitFog_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitInvulnerable" , false ) )
      SetUnitInvulnerable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitLookAt" , false ) )
      SetUnitLookAt_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitMoveSpeed" , false ) )
      SetUnitMoveSpeed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitOwner" , false ) )
      SetUnitOwner_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitPathing" , false ) )
      SetUnitPathing_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitPosition" , false ) )
      SetUnitPosition_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitPositionLoc" , false ) )
      SetUnitPositionLoc_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitPropWindow" , false ) )
      SetUnitPropWindow_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitRescuable" , false ) )
      SetUnitRescuable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitRescueRange" , false ) )
      SetUnitRescueRange_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitScale" , false ) )
      SetUnitScale_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitState" , false ) )
      SetUnitState_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitTimeScale" , false ) )
      SetUnitTimeScale_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitTurnSpeed" , false ) )
      SetUnitTurnSpeed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitTypeSlots" , false ) )
      SetUnitTypeSlots_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitUseFood" , false ) )
      SetUnitUseFood_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitUserData" , false ) )
      SetUnitUserData_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitVertexColor" , false ) )
      SetUnitVertexColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitX" , false ) )
      SetUnitX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitY" , false ) )
      SetUnitY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUnitsFlee" , false ) )
      SetUnitsFlee_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetUpgrade" , false ) )
      SetUpgrade_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetWatchMegaTargets" , false ) )
      SetWatchMegaTargets_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetWaterBaseColor" , false ) )
      SetWaterBaseColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetWaterDeforms" , false ) )
      SetWaterDeforms_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SetWidgetLife" , false ) )
      SetWidgetLife_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ShiftTownSpot" , false ) )
      ShiftTownSpot_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ShowDestructable" , false ) )
      ShowDestructable_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ShowImage" , false ) )
      ShowImage_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ShowInterface" , false ) )
      ShowInterface_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ShowUbersplat" , false ) )
      ShowUbersplat_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "ShowUnit" , false ) )
      ShowUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Sin" , false ) )
      Sin_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Sleep" , false ) )
      Sleep_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SquareRoot" , false ) )
      SquareRoot_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "StartCampaignAI" , false ) )
      StartCampaignAI_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "StartGetEnemyBase" , false ) )
      StartGetEnemyBase_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "StartMeleeAI" , false ) )
      StartMeleeAI_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "StartSound" , false ) )
      StartSound_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "StartThread" , false ) )
      StartThread_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "StopCamera" , false ) )
      StopCamera_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "StopGathering" , false ) )
      StopGathering_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "StopMusic" , false ) )
      StopMusic_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "StopSound" , false ) )
      StopSound_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "StoreBoolean" , false ) )
      StoreBoolean_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "StoreInteger" , false ) )
      StoreInteger_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "StoreReal" , false ) )
      StoreReal_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "StoreString" , false ) )
      StoreString_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "StoreUnit" , false ) )
      StoreUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "StringCase" , false ) )
      StringCase_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "StringHash" , false ) )
      StringHash_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "StringLength" , false ) )
      StringLength_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SubString" , false ) )
      SubString_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SuicidePlayer" , false ) )
      SuicidePlayer_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SuicidePlayerUnits" , false ) )
      SuicidePlayerUnits_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SuicideUnit" , false ) )
      SuicideUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SuicideUnitEx" , false ) )
      SuicideUnitEx_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SuspendHeroXP" , false ) )
      SuspendHeroXP_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SuspendTimeOfDay" , false ) )
      SuspendTimeOfDay_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SyncSelections" , false ) )
      SyncSelections_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SyncStoredBoolean" , false ) )
      SyncStoredBoolean_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SyncStoredInteger" , false ) )
      SyncStoredInteger_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SyncStoredReal" , false ) )
      SyncStoredReal_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SyncStoredString" , false ) )
      SyncStoredString_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "SyncStoredUnit" , false ) )
      SyncStoredUnit_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Tan" , false ) )
      Tan_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TeleportCaptain" , false ) )
      TeleportCaptain_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TerrainDeformCrater" , false ) )
      TerrainDeformCrater_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TerrainDeformRandom" , false ) )
      TerrainDeformRandom_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TerrainDeformRipple" , false ) )
      TerrainDeformRipple_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TerrainDeformStop" , false ) )
      TerrainDeformStop_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TerrainDeformStopAll" , false ) )
      TerrainDeformStopAll_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TerrainDeformWave" , false ) )
      TerrainDeformWave_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TimerDialogDisplay" , false ) )
      TimerDialogDisplay_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TimerDialogSetRealTimeRemaining" , false ) )
      TimerDialogSetRealTimeRemaining_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TimerDialogSetSpeed" , false ) )
      TimerDialogSetSpeed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TimerDialogSetTimeColor" , false ) )
      TimerDialogSetTimeColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TimerDialogSetTitle" , false ) )
      TimerDialogSetTitle_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TimerDialogSetTitleColor" , false ) )
      TimerDialogSetTitleColor_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TimerGetElapsed" , false ) )
      TimerGetElapsed_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TimerGetRemaining" , false ) )
      TimerGetRemaining_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TimerGetTimeout" , false ) )
      TimerGetTimeout_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TimerStart" , false ) )
      TimerStart_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TownHasHall" , false ) )
      TownHasHall_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TownHasMine" , false ) )
      TownHasMine_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TownThreatened" , false ) )
      TownThreatened_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TownWithMine" , false ) )
      TownWithMine_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerAddAction" , false ) )
      TriggerAddAction_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerAddCondition" , false ) )
      TriggerAddCondition_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerClearActions" , false ) )
      TriggerClearActions_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerClearConditions" , false ) )
      TriggerClearConditions_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerEvaluate" , false ) )
      TriggerEvaluate_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerExecute" , false ) )
      TriggerExecute_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerExecuteWait" , false ) )
      TriggerExecuteWait_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterDeathEvent" , false ) )
      TriggerRegisterDeathEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterDialogButtonEvent" , false ) )
      TriggerRegisterDialogButtonEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterDialogEvent" , false ) )
      TriggerRegisterDialogEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterEnterRegion" , false ) )
      TriggerRegisterEnterRegion_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterFilterUnitEvent" , false ) )
      TriggerRegisterFilterUnitEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterGameEvent" , false ) )
      TriggerRegisterGameEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterGameStateEvent" , false ) )
      TriggerRegisterGameStateEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterLeaveRegion" , false ) )
      TriggerRegisterLeaveRegion_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterPlayerAllianceChange" , false ) )
      TriggerRegisterPlayerAllianceChange_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterPlayerChatEvent" , false ) )
      TriggerRegisterPlayerChatEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterPlayerEvent" , false ) )
      TriggerRegisterPlayerEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterPlayerStateEvent" , false ) )
      TriggerRegisterPlayerStateEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterPlayerUnitEvent" , false ) )
      TriggerRegisterPlayerUnitEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterTimerEvent" , false ) )
      TriggerRegisterTimerEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterTimerExpireEvent" , false ) )
      TriggerRegisterTimerExpireEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterTrackableHitEvent" , false ) )
      TriggerRegisterTrackableHitEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterTrackableTrackEvent" , false ) )
      TriggerRegisterTrackableTrackEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterUnitEvent" , false ) )
      TriggerRegisterUnitEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterUnitInRange" , false ) )
      TriggerRegisterUnitInRange_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterUnitStateEvent" , false ) )
      TriggerRegisterUnitStateEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRegisterVariableEvent" , false ) )
      TriggerRegisterVariableEvent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRemoveAction" , false ) )
      TriggerRemoveAction_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerRemoveCondition" , false ) )
      TriggerRemoveCondition_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerSleepAction" , false ) )
      TriggerSleepAction_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerSyncReady" , false ) )
      TriggerSyncReady_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerSyncStart" , false ) )
      TriggerSyncStart_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerWaitForSound" , false ) )
      TriggerWaitForSound_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "TriggerWaitOnSleeps" , false ) )
      TriggerWaitOnSleeps_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitAddAbility" , false ) )
      UnitAddAbility_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitAddIndicator" , false ) )
      UnitAddIndicator_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitAddItem" , false ) )
      UnitAddItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitAddItemById" , false ) )
      UnitAddItemById_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitAddItemToSlotById" , false ) )
      UnitAddItemToSlotById_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitAddSleep" , false ) )
      UnitAddSleep_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitAddSleepPerm" , false ) )
      UnitAddSleepPerm_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitAddType" , false ) )
      UnitAddType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitAlive" , false ) )
      UnitAlive_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitApplyTimedLife" , false ) )
      UnitApplyTimedLife_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitCanSleep" , false ) )
      UnitCanSleep_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitCanSleepPerm" , false ) )
      UnitCanSleepPerm_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitCountBuffsEx" , false ) )
      UnitCountBuffsEx_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitDamagePoint" , false ) )
      UnitDamagePoint_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitDamageTarget" , false ) )
      UnitDamageTarget_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitDropItemPoint" , false ) )
      UnitDropItemPoint_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitDropItemSlot" , false ) )
      UnitDropItemSlot_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitDropItemTarget" , false ) )
      UnitDropItemTarget_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitHasBuffsEx" , false ) )
      UnitHasBuffsEx_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitHasItem" , false ) )
      UnitHasItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitId" , false ) )
      UnitId_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitId2String" , false ) )
      UnitId2String_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitIgnoreAlarm" , false ) )
      UnitIgnoreAlarm_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitIgnoreAlarmToggled" , false ) )
      UnitIgnoreAlarmToggled_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitInventorySize" , false ) )
      UnitInventorySize_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitInvis" , false ) )
      UnitInvis_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitIsSleeping" , false ) )
      UnitIsSleeping_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitItemInSlot" , false ) )
      UnitItemInSlot_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitMakeAbilityPermanent" , false ) )
      UnitMakeAbilityPermanent_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitModifySkillPoints" , false ) )
      UnitModifySkillPoints_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitPauseTimedLife" , false ) )
      UnitPauseTimedLife_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitPoolAddUnitType" , false ) )
      UnitPoolAddUnitType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitPoolRemoveUnitType" , false ) )
      UnitPoolRemoveUnitType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitRemoveAbility" , false ) )
      UnitRemoveAbility_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitRemoveBuffs" , false ) )
      UnitRemoveBuffs_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitRemoveBuffsEx" , false ) )
      UnitRemoveBuffsEx_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitRemoveItem" , false ) )
      UnitRemoveItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitRemoveItemFromSlot" , false ) )
      UnitRemoveItemFromSlot_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitRemoveType" , false ) )
      UnitRemoveType_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitResetCooldown" , false ) )
      UnitResetCooldown_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitSetConstructionProgress" , false ) )
      UnitSetConstructionProgress_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitSetUpgradeProgress" , false ) )
      UnitSetUpgradeProgress_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitSetUsesAltIcon" , false ) )
      UnitSetUsesAltIcon_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitShareVision" , false ) )
      UnitShareVision_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitStripHeroLevel" , false ) )
      UnitStripHeroLevel_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitSuspendDecay" , false ) )
      UnitSuspendDecay_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitUseItem" , false ) )
      UnitUseItem_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitUseItemPoint" , false ) )
      UnitUseItemPoint_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitUseItemTarget" , false ) )
      UnitUseItemTarget_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnitWakeUp" , false ) )
      UnitWakeUp_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "UnregisterStackedSound" , false ) )
      UnregisterStackedSound_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "Unsummon" , false ) )
      Unsummon_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "VersionCompatible" , false ) )
      VersionCompatible_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "VersionGet" , false ) )
      VersionGet_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "VersionSupported" , false ) )
      VersionSupported_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "VolumeGroupReset" , false ) )
      VolumeGroupReset_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "VolumeGroupSetVolume" , false ) )
      VolumeGroupSetVolume_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "WaitGetEnemyBase" , false ) )
      WaitGetEnemyBase_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "WaygateActivate" , false ) )
      WaygateActivate_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "WaygateGetDestinationX" , false ) )
      WaygateGetDestinationX_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "WaygateGetDestinationY" , false ) )
      WaygateGetDestinationY_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "WaygateIsActive" , false ) )
      WaygateIsActive_init ( );
  if ( reader.GetBoolean( "JASS_DEBUG_ENGINE_BY_ABSOL", "WaygateSetDestination" , false ) )
      WaygateSetDestination_init ( );
}
BOOL APIENTRY DllMain( HINSTANCE hDLL , DWORD reason , LPVOID reserved )
{
	switch ( reason )
	{
		case DLL_PROCESS_ATTACH:
			logfile = _fsopen( "JassSpy.txt" , "w" , _SH_DENYWR );
			if ( reader.ParseError( ) < 0 )
			{
				MessageBox( 0 , "Can't load 'JassConfig.ini'\n" , "ERROR LOAD CONFIG" , MB_OK );
				return FALSE;
			}
			fprintf_s( logfile , ".......UnrealJassSpy for Warcraft 1.26a......\n" );
			setvbuf( logfile , NULL , _IOLBF , 128 );
			MH_Initialize( );
			Initializer( );
			AddVectoredExceptionHandler(1, TopLevelExceptionHandler);
		break;
		case DLL_PROCESS_DETACH:
			MH_Uninitialize( );
		break;
	}
	return TRUE;
}
