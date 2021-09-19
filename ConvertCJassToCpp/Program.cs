using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.IO;

namespace ConvertCJassToJassSpy
{
    class Program
    {
        struct argstruct
        {
            public string argtype;
            public string argname;
        }

        struct FuncStruct
        {
            public string FuncName;
            public string FuncType;
            public argstruct[] FuncArgs;
            public string FuncAddr;
        }

        struct PrintGetType
        {
            public string VarType;
            public string PrintType;
            public string readtype;
        }


        struct TypedefData
        {
            public string OldName;
            public string ReplacedName;
        }


        struct FunctionStructure
        {
            string FuncNameAndArgs;
            string[] VarCode;
            string[] Code;
        }

        struct TypedefStruct
        {
            string OldString;
            string NewString;
        }

        struct VariablesStruct
        {
            string vartype;
            string varname;
            string varvalue;
        }



        static List<FuncStruct> JassNativeFunctions = new List<FuncStruct>();

        static List<argstruct> TypedefList = new List<argstruct>();

        static List<PrintGetType> PrintTypeList = new List<PrintGetType>();

        static void WriteToJassNativesHeader(string str)
        {
            if (!File.Exists(".\\JassNativesHeader.h"))
            {
                File.Create(".\\JassNativesHeader.h").Close();
            }

            File.AppendAllText(".\\JassNativesHeader.h", str + "\n");
        }

        static void WriteToJassNativesHeaderInitialzier(string str)
        {
            if (!File.Exists(".\\JassNativesHeader.cpp"))
            {
                File.Create(".\\JassNativesHeader.cpp").Close();
            }

            File.AppendAllText(".\\JassNativesHeader.cpp", str + "\n");
        }

        static void WriteToJassNativesHooked(string str)
        {
            if (!File.Exists(".\\JassNativesHooked.cpp"))
            {
                File.Create(".\\JassNativesHooked.cpp").Close();
            }

            File.AppendAllText(".\\JassNativesHooked.cpp", str + "\n");
        }

        static void WriteToJassDefineHeader(string str)
        {
            if (!File.Exists(".\\JassDefineHeader.h"))
            {
                File.Create(".\\JassDefineHeader.h").Close();
            }

            File.AppendAllText(".\\JassDefineHeader.h", str + "\n");
        }

        static void WriteToJassNativesHook(string str)
        {
            if (!File.Exists(".\\JassNativesHook.cpp"))
            {
                File.Create(".\\JassNativesHook.cpp").Close();
            }

            File.AppendAllText(".\\JassNativesHook.cpp", str + "\n");
        }

        static void WriteToJassConfig(string str)
        {
            if (!File.Exists(".\\JassConfig.ini"))
            {
                File.Create(".\\JassConfig.ini").Close();
            }

            File.AppendAllText(".\\JassConfig.ini", str + "\n");
        }

        static void WriteToCommonCode(string str)
        {
            if (!File.Exists(".\\common.cpp"))
            {
                File.Create(".\\common.cpp").Close();
            }

            File.AppendAllText(".\\common.cpp", str + "\n");
        }
        static void WriteToCommonHeader(string str)
        {
            if (!File.Exists(".\\common.h"))
            {
                File.Create(".\\common.h").Close();
            }

            File.AppendAllText(".\\common.h", str + "\n");
        }

        static void WriteToBlizzardCode(string str)
        {
            if (!File.Exists(".\\blizzard.cpp"))
            {
                File.Create(".\\blizzard.cpp").Close();
            }

            File.AppendAllText(".\\blizzard.cpp", str + "\n");
        }
        static void WriteToBlizzardHeader(string str)
        {
            if (!File.Exists(".\\blizzard.h"))
            {
                File.Create(".\\blizzard.h").Close();
            }

            File.AppendAllText(".\\blizzard.h", str + "\n");
        }
        static void WriteToMainCode(string str)
        {
            if (!File.Exists(".\\war3map.cpp"))
            {
                File.Create(".\\war3map.cpp").Close();
            }

            File.AppendAllText(".\\war3map.cpp", str + "\n");
        }

        static void Main(string[] args)
        {
            string RegexFuncInfo = @"^\s*(\w+.*?)__cdecl\s*(\w+)\((.*?\))$";
            string RegexFuncArgs = @"(\w+)([\s|\*]+\w+)\W\s*";
            string RegexFuncAddr = @"^\s*add\s+eax\s*,\s*(\w+)";
            string[] CJassData = File.ReadAllLines("CJass.cpp");

            int index = 0;

            if (File.Exists(".\\JassNativesHeader.h"))
            {
                File.Delete(".\\JassNativesHeader.h");
            }
            if (File.Exists(".\\JassDefineHeader.h"))
            {
                File.Delete(".\\JassDefineHeader.h");
            }

            if (File.Exists(".\\JassNativesHooked.cpp"))
            {
                File.Delete(".\\JassNativesHooked.cpp");
            }

            if (File.Exists(".\\JassNativesHook.cpp"))
            {
                File.Delete(".\\JassNativesHook.cpp");
            }

            if (File.Exists(".\\JassConfig.ini"))
            {
                File.Delete(".\\JassConfig.ini");
            }

            if (File.Exists(".\\JassNativesHeader.cpp"))
            {
                File.Delete(".\\JassNativesHeader.cpp");
            }


            while (index < CJassData.Length)
            {
                Match GetFuncInfo = Regex.Match(CJassData[index], RegexFuncInfo);
                if (GetFuncInfo.Success)
                {
                    string FuncType = GetFuncInfo.Groups[1].Value.Trim();
                    string FuncName = GetFuncInfo.Groups[2].Value.Trim();
                    string argsstring = GetFuncInfo.Groups[3].Value.Trim();

                    List<argstruct> FuncArgs = new List<argstruct>();

                    foreach (Match GetFuncArgs in Regex.Matches(argsstring, RegexFuncArgs))
                    {
                        if (!GetFuncArgs.Success && argsstring != ")")
                        {
                            Console.WriteLine("ERROR:" + argsstring);
                            Console.ReadLine();
                        }


                        int argscount = GetFuncArgs.Groups.Count / 2;
                        for (int i = 0; i < argscount; i++)
                        {
                            argstruct tmparg = new argstruct();
                            tmparg.argname =
                                GetFuncArgs.Groups[i + 2].Value.Trim().Replace(",", "").Trim();
                            tmparg.argtype =
                                GetFuncArgs.Groups[i + 1].Value.Trim().Replace(",", "").Trim();
                            FuncArgs.Add(tmparg);
                        }
                    }

                    Match GetFuncAddress = null;
                    while (!(GetFuncAddress =
                        Regex.Match(CJassData[index], RegexFuncAddr)).Success)
                    {
                        index++;
                    }

                    FuncStruct NewFunction = new FuncStruct();
                    NewFunction.FuncAddr = GetFuncAddress.Groups[1].Value;
                    NewFunction.FuncArgs = FuncArgs.ToArray();
                    NewFunction.FuncName = FuncName.Trim();
                    NewFunction.FuncType = FuncType.Trim();
                    JassNativeFunctions.Add(NewFunction);

                }
                index++;
            }

            PrintGetType DefaultTypeList = new PrintGetType();
            DefaultTypeList.VarType = "float";
            DefaultTypeList.PrintType = "%.4g";
            DefaultTypeList.readtype = "({0})";
            PrintTypeList.Add(DefaultTypeList);
            DefaultTypeList.VarType = "float";
            DefaultTypeList.PrintType = "%.4g";
            DefaultTypeList.readtype = "GetFloatFromDWFP({0})";
            PrintTypeList.Add(DefaultTypeList);
            DefaultTypeList.VarType = "CJassString";
            DefaultTypeList.PrintType = "%s";
            DefaultTypeList.readtype = "ReadJassStringNormal({0})";
            PrintTypeList.Add(DefaultTypeList);
            DefaultTypeList.VarType = "CJassStringSID";
            DefaultTypeList.PrintType = "%s";
            DefaultTypeList.readtype = "ReadJassSID({0})";
            PrintTypeList.Add(DefaultTypeList);
            DefaultTypeList.VarType = "BOOL";
            DefaultTypeList.PrintType = "%s";
            DefaultTypeList.readtype = "BoolToStr({0})";
            PrintTypeList.Add(DefaultTypeList);
            DefaultTypeList.VarType = "HPLAYER";
            DefaultTypeList.PrintType = "%i";
            DefaultTypeList.readtype = "GetPlayerId/*_native*/({0})";
            PrintTypeList.Add(DefaultTypeList);
            DefaultTypeList.VarType = "HUNIT";
            DefaultTypeList.PrintType = "%s";
            DefaultTypeList.readtype = "GetUnitHID({0}).c_str( )";
            PrintTypeList.Add(DefaultTypeList);
            DefaultTypeList.VarType = "HITEM";
            DefaultTypeList.PrintType = "%s";
            DefaultTypeList.readtype = "GetItemHID({0}).c_str( )";
            PrintTypeList.Add(DefaultTypeList);

            argstruct DefaultVars = new argstruct();
            DefaultVars.argname = "float";
            DefaultVars.argtype = "//";
            TypedefList.Add(DefaultVars);
            DefaultVars.argname = "float *";
            DefaultVars.argtype = "//";
            TypedefList.Add(DefaultVars);
            DefaultVars.argname = "int";
            DefaultVars.argtype = "//";
            TypedefList.Add(DefaultVars);
            DefaultVars.argname = "BOOL";
            DefaultVars.argtype = "//";
            TypedefList.Add(DefaultVars);
            DefaultVars.argname = "void";
            DefaultVars.argtype = "//";
            TypedefList.Add(DefaultVars);
            DefaultVars.argname = "float";
            DefaultVars.argtype = "//";
            TypedefList.Add(DefaultVars);

            for (int i = 0; i < JassNativeFunctions.Count; i++)
            {
                bool needadd = true;
                foreach (argstruct str in TypedefList)
                {
                    if (str.argname == JassNativeFunctions[i].FuncType)
                    {
                        needadd = false;
                        break;
                    }
                }

                if (needadd)
                {
                    argstruct temp = new argstruct();
                    temp.argname = JassNativeFunctions[i].FuncType;
                    temp.argtype = "typedef int ";
                    TypedefList.Add(temp);
                }
            }

            for (int i = 0; i < JassNativeFunctions.Count; i++)
            {
                foreach (argstruct FuncArg in JassNativeFunctions[i].FuncArgs)
                {
                    bool needadd = true;
                    foreach (argstruct str in TypedefList)
                    {
                        if (str.argname == FuncArg.argtype)
                        {
                            needadd = false;
                            break;
                        }
                    }
                    if (needadd)
                    {
                        argstruct temp = new argstruct();
                        temp.argname = FuncArg.argtype;
                        temp.argtype = "typedef int ";
                        TypedefList.Add(temp);
                    }
                }
            }

            WriteToJassDefineHeader("#pragma once");
            WriteToJassDefineHeader("union float");
            WriteToJassDefineHeader("{");
            WriteToJassDefineHeader("unsigned int dw;");
            WriteToJassDefineHeader("float fl;");
            WriteToJassDefineHeader("};");

            foreach (argstruct str in TypedefList)
            {
                WriteToJassDefineHeader(str.argtype + str.argname + ";");
            }

            WriteToJassNativesHeader("#pragma once");
            WriteToJassNativesHeader("#include <Windows.h>");
            WriteToJassNativesHeader("#include <stdio.h>");
            WriteToJassNativesHeader("#include \"JassDefineHeader.h\"");

            WriteToJassNativesHook("#include <Windows.h>");
            WriteToJassNativesHook("#include <string>");
            WriteToJassNativesHook("#include \"JassDefineHeader.h\"");
            WriteToJassNativesHook("#include \"JassNativesHeader.h\"");
            WriteToJassNativesHook("#include \"INIReader.h\"");
            //   WriteToJassNativesHook( "#include \"MinHook.h\"" );

            WriteToJassNativesHeaderInitialzier("#include \"JassNativesHeader.h\"");

            // WriteToJassNativesHook( "#pragma comment(lib, \"libMinHook.x86.lib\")" );

            /*   string [ ] exceptionhandlerdata = File.ReadAllLines( "ExceptionHandler.txt" );
               foreach ( string str in exceptionhandlerdata )
                   WriteToJassNativesHook( str );

               */
            WriteToJassNativesHook("static int GameDll = (int) GetModuleHandle(\"Game.dll\");");
            //INIReader reader( \"../JassConfig.ini\" );
            WriteToJassNativesHook("INIReader reader( \"./JassConfig.ini\" );");

            WriteToJassNativesHooked("#include <Windows.h>");
            WriteToJassNativesHooked("#include <time.h>");
            WriteToJassNativesHooked("#include <sstream>");
            WriteToJassNativesHooked("#include <string>");
            WriteToJassNativesHooked("#include \"JassNativesHeader.h\"");
            WriteToJassNativesHooked("using namespace std;");
            WriteToJassNativesHooked("static int GameDll = (int) GetModuleHandle( \"Game.dll\");");

            WriteToJassNativesHooked("FILE * logfile;");
            WriteToJassNativesHeader("extern FILE * logfile;");

            WriteToJassNativesHooked("char * funcname1 = \"NULLNAME\";");
            WriteToJassNativesHeader("extern char * funcname1;");
            WriteToJassNativesHooked("char * funcname2 = \"NULLNAME\";");
            WriteToJassNativesHeader("extern char * funcname2;");

            WriteToJassNativesHooked("void SpyJassLog( const char * format , ... )");
            WriteToJassNativesHooked("{");
            WriteToJassNativesHooked("	/*char buffer[ 256 ]; va_list args; va_start( args , format );");
            WriteToJassNativesHooked("	vsprintf_s( buffer , 256 , format , args ); va_end( args );");
            WriteToJassNativesHooked("	int lentowrite = strlen( buffer );");
            WriteToJassNativesHooked("	fwrite( &buffer , lentowrite , 1 , logfile ); fflush( logfile );*/");
            WriteToJassNativesHooked("	va_list args; va_start( args , format ); vfprintf_s( logfile , format , args ); va_end( args ); /*fflush( logfile );*/");
            WriteToJassNativesHooked("}");

            WriteToJassNativesHooked("string GetStrID( int id )");
            WriteToJassNativesHooked("{");
            WriteToJassNativesHooked("    char buff[ 7 ];");
            WriteToJassNativesHooked("    char buff2[ 4 ];");
            WriteToJassNativesHooked("    CopyMemory( buff2 , &id , 4 );");
            WriteToJassNativesHooked("    buff[ 0 ] = \'\\'\';");
            WriteToJassNativesHooked("    buff[ 1 ] = buff2[ 3 ];");
            WriteToJassNativesHooked("    buff[ 2 ] = buff2[ 2 ];");
            WriteToJassNativesHooked("	   buff[ 3 ] = buff2[ 1 ];");
            WriteToJassNativesHooked("    buff[ 4 ] = buff2[ 0 ];");
            WriteToJassNativesHooked("    buff[ 5 ] = \'\\'\';");
            WriteToJassNativesHooked("    buff[ 6 ] = \'\\0\';");
            WriteToJassNativesHooked("    bool needreturnid = true;");
            WriteToJassNativesHooked("    for ( int i = 1; i < 5; i++ )");
            WriteToJassNativesHooked("    {");
            WriteToJassNativesHooked("        if ( !isalnum( buff[ i ] ) )");
            WriteToJassNativesHooked("        {");
            WriteToJassNativesHooked("            needreturnid = false;");
            WriteToJassNativesHooked("            break;");
            WriteToJassNativesHooked("        }");
            WriteToJassNativesHooked("    }");
            WriteToJassNativesHooked("    if ( needreturnid )");
            WriteToJassNativesHooked("      return string( buff );");
            WriteToJassNativesHooked("    return to_string( id );");
            WriteToJassNativesHooked("}");

            WriteToJassNativesHooked("const char * BoolToStr( BOOL boolean )");
            WriteToJassNativesHooked("{");
            WriteToJassNativesHooked("    return boolean ? \"true\" : \"false\";");
            WriteToJassNativesHooked("}");

            WriteToJassNativesHooked("float GetFloatFromDWFP( float val )");
            WriteToJassNativesHooked("{");
            WriteToJassNativesHooked("    return val.fl;");
            WriteToJassNativesHooked("}");

            WriteToJassNativesHooked("char * ReadJassStringNormal( int JASSSTRING )");
            WriteToJassNativesHooked("{");
            WriteToJassNativesHooked("    if ( JASSSTRING == NULL || JASSSTRING >= INT_MAX ) { return \" \"; }");
            WriteToJassNativesHooked("    int offset1 = *( int* ) ( ( int ) JASSSTRING + 8 );");
            WriteToJassNativesHooked("    if ( offset1 == NULL || offset1 >= INT_MAX ) { return \" \"; }");
            WriteToJassNativesHooked("    int offset2 = *( int * ) ( ( *( int* ) ( ( int ) JASSSTRING + 8 ) ) + 0x1C );");
            WriteToJassNativesHooked("    if ( offset2 == NULL || offset2 >= INT_MAX ) { return \" \"; }");
            WriteToJassNativesHooked("    return *( char ** ) ( ( *( int* ) ( ( int ) JASSSTRING + 8 ) ) + 0x1C );");
            WriteToJassNativesHooked("}");

            WriteToJassNativesHooked("char * ReadJassSID(int JSID)");
            WriteToJassNativesHooked("{");
            WriteToJassNativesHooked("    int Convert = GameDll + 0x459640; int GetCurrentJassEnvironment = GameDll + 0x44B2E0;");
            WriteToJassNativesHooked("    char * cRet = NULL;");
            WriteToJassNativesHooked("    __asm");
            WriteToJassNativesHooked("    {");
            WriteToJassNativesHooked("        push JSID;");
            WriteToJassNativesHooked("        mov ecx, 1;");
            WriteToJassNativesHooked("        call GetCurrentJassEnvironment;");
            WriteToJassNativesHooked("        mov ecx, eax;");
            WriteToJassNativesHooked("        call Convert;");
            WriteToJassNativesHooked("        mov ecx,dword ptr ds:[eax+0x08];");
            WriteToJassNativesHooked("        mov eax,dword ptr ds:[ecx+0x1C];");
            WriteToJassNativesHooked("        mov cRet, eax;");
            WriteToJassNativesHooked("    }");
            WriteToJassNativesHooked("    return cRet;");
            WriteToJassNativesHooked("}");

            WriteToJassNativesHooked("string GetUnitHID( int unitid )");
            WriteToJassNativesHooked("{");
            WriteToJassNativesHooked("   if ( unitid == 0 ) return \"null\";");
            WriteToJassNativesHooked("        stringstream s; s << unitid; s << \"(\" << GetStrID( GetUnitTypeId/*_native*/(unitid) ) << \")\";");
            WriteToJassNativesHooked("    return s.str( );");
            WriteToJassNativesHooked("}");

            WriteToJassNativesHooked("string GetItemHID( int itemid )");
            WriteToJassNativesHooked("{");
            WriteToJassNativesHooked("   if ( itemid == 0 ) return \"null\";");
            WriteToJassNativesHooked("        stringstream s; s << itemid; s << \"(\" << GetStrID( GetItemTypeId/*_native*/( itemid ) ) << \")\";");
            WriteToJassNativesHooked("    return s.str( );");
            WriteToJassNativesHooked("}");




            for (int i = 0; i < JassNativeFunctions.Count; i++)
            {
                string ToAdd = "typedef " + JassNativeFunctions[i].FuncType +
                    " ( __cdecl * " + JassNativeFunctions[i].FuncName + "_FUNC) (";
                bool IsFirst = false;
                foreach (argstruct FuncArg in JassNativeFunctions[i].FuncArgs)
                {
                    if (!IsFirst)
                    {
                        IsFirst = true;
                        ToAdd += FuncArg.argtype + " ";
                        ToAdd += FuncArg.argname;
                    }
                    else
                    {
                        ToAdd += ", " + FuncArg.argtype + " ";
                        ToAdd += FuncArg.argname;
                    }
                }
                ToAdd += ");";
                WriteToJassNativesHeader(ToAdd);
            }

            //  WriteToJassConfig( "[JASS_DEBUG_ENGINE_BY_ABSOL]" );

            for (int i = 0; i < JassNativeFunctions.Count; i++)
            {
                WriteToJassNativesHeader("extern " + JassNativeFunctions[i].FuncName +
                    "_FUNC " + JassNativeFunctions[i].FuncName + "/*_native*/;");

                WriteToJassNativesHeaderInitialzier(JassNativeFunctions[i].FuncName +
                    "_FUNC " + JassNativeFunctions[i].FuncName + "/*_native*/ = nullptr;");

                WriteToJassNativesHook("void " + JassNativeFunctions[i].FuncName + "_init ( )");
                WriteToJassNativesHook("{");
                WriteToJassNativesHook("      " + JassNativeFunctions[i].FuncName +
                    "/*_native*/ = (" + JassNativeFunctions[i].FuncName + "_FUNC) ( GameDll + " + JassNativeFunctions[i].FuncAddr + " );");
                WriteToJassNativesHook("}");

                string HookedFuncName = JassNativeFunctions[i].FuncType + " _cdecl "
                    + JassNativeFunctions[i].FuncName + "_my(";

                bool IsFirst = false;
                foreach (argstruct FuncArg in JassNativeFunctions[i].FuncArgs)
                {
                    if (!IsFirst)
                    {
                        IsFirst = true;
                        HookedFuncName += FuncArg.argtype + " ";
                        HookedFuncName += FuncArg.argname;
                    }
                    else
                    {
                        HookedFuncName += ", " + FuncArg.argtype + " ";
                        HookedFuncName += FuncArg.argname;
                    }
                }



            }
            WriteToJassNativesHook(" typedef int(__fastcall *LookupNative)(LPSTR);");
            WriteToJassNativesHook(" LookupNative LookupNative/*_native*/ = NULL;");

            WriteToJassNativesHook("__declspec(dllexport) void Initializer( )");
            WriteToJassNativesHook("{");
            WriteToJassNativesHook("   LookupNative/*_native*/ = (LookupNative) (GameDll + 0x44EA00);");

            for (int i = 0; i < JassNativeFunctions.Count; i++)
            {
                WriteToJassNativesHook("      " + JassNativeFunctions[i].FuncName + "_init ( );");
            }
            WriteToJassNativesHook("}");


            WriteToJassNativesHook("BOOL APIENTRY DllMain( HINSTANCE hDLL , DWORD reason , LPVOID reserved )");
            WriteToJassNativesHook("{");
            WriteToJassNativesHook("	switch ( reason )");
            WriteToJassNativesHook("	{");
            WriteToJassNativesHook("		case DLL_PROCESS_ATTACH:");
            WriteToJassNativesHook("		break;");
            WriteToJassNativesHook("		case DLL_PROCESS_DETACH:");
            WriteToJassNativesHook("		break;");
            WriteToJassNativesHook("	}");
            WriteToJassNativesHook("	return TRUE;");
            WriteToJassNativesHook("}");


            Console.WriteLine("Enter path to dir with war3map.j,blizzard.j,common.j");
            string jassscriptspath = Console.ReadLine();
            string[] blizzard_j_data = File.ReadAllLines(jassscriptspath + "blizzard.j");
            string[] common_j_data = File.ReadAllLines(jassscriptspath + "common.j");
            string[] war3map_j_data = File.ReadAllLines(jassscriptspath + "war3map.j");




            string regex_get_globals = @"\s*globals";
            string regex_get_endglobals = @"\s*endglobals";

            string regex_get_constantdata = @"\s*constant\s+(.*?)\s+(.*?)\s+=\s*(.*)";
            string regex_get_nonconstantdata = @"\s*(.*?)\s+(.*?)\s+=\s*(.*)";

          
            for (int i = 0; i < common_j_data.Length; i++)
            {
                if (common_j_data.Length > 0)
                {

                    if (Regex.Match(common_j_data[i], regex_get_globals).Success)
                    {
                        if (common_j_data.Length > 0)
                        {

                            for (; i < common_j_data.Length; i++)
                            {
                                Match ConstantData = Regex.Match(common_j_data[i], regex_get_constantdata);

                                if (ConstantData.Success)
                                {
                                    WriteToCommonHeader("#define " + ConstantData.Groups[2] + " " + ConstantData.Groups[3]);
                                }
                               /* else
                                {
                                    Match NonConstantData = Regex.Match(common_j_data[i], regex_get_nonconstantdata);

                                    if (NonConstantData.Success)
                                    {

                                    }
                                }*/

                                if (Regex.Match(common_j_data[i], regex_get_endglobals).Success)
                                {
                                    Console.WriteLine(common_j_data[i]);
                                    break;
                                }
                            }

                        }
                    }
                }
            }

            Console.WriteLine("end2");
            string ConvertJass1 = @"\s*function\s+(.*?)\s+takes\s+(.*?)\s+returns\s+(.*)";
            string ConvertCpp1 = @" $3 $1( $2 ) {";

            string ConvertJass2 = @"\s*endfunction";
            string ConvertCpp2 = @"}";

            string ConvertJass3 = @"(\s*)elseif\s*(.*?)then";
            string ConvertCpp3 = "$1}\n$1 else if ($2) {";

            string ConvertJass4 = @"(\s*)if\s*(.*?)\s*then";
            string ConvertCpp4 = @"$1 if ($2) {";

        
            string ConvertJass5 = @"(\s*)else";
            string ConvertCpp5 = "$1}\n$1else {\n$1";

            string ConvertJass6 = @"(\s*)endif";
            string ConvertCpp6 = "$1}";

            string ConvertJass7 = @"(\s*)call\s+(.*)";
            string ConvertCpp7 = "$1 $2;";

            string ConvertJass8 = @"(\s*)set\s+(.*)";
            string ConvertCpp8 = "$1 $2;";

            string ConvertJass9 = @"(\s*)local\s+(.*)";
            string ConvertCpp9 = "$1 $2;";


            string ConvertJass10 = @"(\s*)return\s+(.*)";
            string ConvertCpp10 = "$1 return $2;";



            for (int i = 0; i < blizzard_j_data.Length; i++)
            {
                string oldstr = blizzard_j_data[i];
                if (oldstr == blizzard_j_data[i] && blizzard_j_data[i].IndexOf("function") > -1)
                    blizzard_j_data[i] = Regex.Replace(blizzard_j_data[i], ConvertJass1, ConvertCpp1);
                if (oldstr == blizzard_j_data[i] && blizzard_j_data[i].IndexOf("endfunction") > -1)
                    blizzard_j_data[i] = Regex.Replace(blizzard_j_data[i], ConvertJass2, ConvertCpp2);
                if (oldstr == blizzard_j_data[i] && blizzard_j_data[i].IndexOf("then") > -1)
                    blizzard_j_data[i] = Regex.Replace(blizzard_j_data[i], ConvertJass3, ConvertCpp3);
                if (oldstr == blizzard_j_data[i] && blizzard_j_data[i].IndexOf("then") > -1)
                    blizzard_j_data[i] = Regex.Replace(blizzard_j_data[i], ConvertJass4, ConvertCpp4);
                if (oldstr == blizzard_j_data[i] && blizzard_j_data[i].IndexOf("else") > -1)
                    blizzard_j_data[i] = Regex.Replace(blizzard_j_data[i], ConvertJass5, ConvertCpp5);
                if (oldstr == blizzard_j_data[i] && blizzard_j_data[i].IndexOf("endif") > -1)
                    blizzard_j_data[i] = Regex.Replace(blizzard_j_data[i], ConvertJass6, ConvertCpp6);
                if (oldstr == blizzard_j_data[i] && blizzard_j_data[i].IndexOf("call") > -1)
                    blizzard_j_data[i] = Regex.Replace(blizzard_j_data[i], ConvertJass7, ConvertCpp7);
                if (oldstr == blizzard_j_data[i] && blizzard_j_data[i].IndexOf("set") > -1)
                    blizzard_j_data[i] = Regex.Replace(blizzard_j_data[i], ConvertJass8, ConvertCpp8);
                if (oldstr == blizzard_j_data[i] && blizzard_j_data[i].IndexOf("local") > -1)
                    blizzard_j_data[i] = Regex.Replace(blizzard_j_data[i], ConvertJass9, ConvertCpp9);
                if (oldstr == blizzard_j_data[i] && blizzard_j_data[i].IndexOf("return") > -1)
                    blizzard_j_data[i] = Regex.Replace(blizzard_j_data[i], ConvertJass10, ConvertCpp10);


                if (blizzard_j_data[i].IndexOf("if") > -1 ||
                    blizzard_j_data[i].IndexOf("return") > -1)
                {
                    blizzard_j_data[i] = Regex.Replace(blizzard_j_data[i], @"(\W)or(\W)", @"$1||$2");
                    blizzard_j_data[i] = Regex.Replace(blizzard_j_data[i], @"(\W)and(\W)", @"$1&&$2");
                }
            }

            List<string> OutBLizzardData = new List<string>();

            for (int i = 0; i < blizzard_j_data.Length; i++)
            {
                if (!Regex.Match(blizzard_j_data[i], @"^\s*$").Success)
                {
                    OutBLizzardData.Add(blizzard_j_data[i]);
                }

            }

            File.WriteAllLines(".\\testblizzard.cpp", OutBLizzardData.ToArray( ));

        }
    }
}
