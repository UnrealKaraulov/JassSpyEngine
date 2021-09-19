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

        struct _funcaddr
        {
            public string funcname;
            public string funcaddr;
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


        static List<FuncStruct> JassNativeFunctions = new List<FuncStruct>();

        static List<argstruct> TypedefList = new List<argstruct>();

        static List<PrintGetType> PrintTypeList = new List<PrintGetType>();

        static string DefaultPrintType = "%s";

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


        static void Main(string[] args)
        {
            string RegexFuncInfo = @"^\s*(\w+.*?)__cdecl\s*(\w+)\((.*?\))$";
            string RegexFuncArgs = @"(\w+)([\s|\*]+\w+)\W\s*";
            string RegexFuncAddr = @"^\s*add\s+eax\s*,\s*(\w+)";
            string[] CJassData = File.ReadAllLines("CJass.cpp");
            List<_funcaddr> funcaddrlist = new List<_funcaddr>();

            if (File.Exists("Functions.txt"))
            {
                Console.WriteLine("Found Functions.txt file. Read function address from this file...");
                string[] FunctionsListAddr = File.ReadAllLines("Functions.txt");

                Console.WriteLine("Functions.txt lenght:" + FunctionsListAddr.Length);
                //"Deg2Rad" located at 0x1DF360 with parameters "(R)R"
                string GetFuncNameAndAddr = @"""(\w+)""\s.*?(0x\w+)";
                int loadedaddress = 0;
                Match GetFuncAddress = null;
                foreach (string s in FunctionsListAddr)
                {
                    if ((GetFuncAddress = Regex.Match(s, GetFuncNameAndAddr)).Success)
                    {
                        loadedaddress++;
                        _funcaddr tmpstr = new _funcaddr();
                        tmpstr.funcaddr = GetFuncAddress.Groups[2].Value;
                        tmpstr.funcname = GetFuncAddress.Groups[1].Value;
                        funcaddrlist.Add(tmpstr);
                    }
                }

                Console.WriteLine("Load:" + loadedaddress + " addr count.");
            }


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

                    bool FoundNewAddr = false;
                    foreach (var s in funcaddrlist)
                    {
                        if (s.funcname == NewFunction.FuncName)
                        {
                            NewFunction.FuncAddr = s.funcaddr;
                            FoundNewAddr = true;
                            break;
                        }
                    }


                    if (!FoundNewAddr)
                    {
                        Console.WriteLine("Error! Func addr for " + NewFunction.FuncName + " not found!");
                        Console.ReadLine();
                    }

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
            DefaultTypeList.VarType = "DWFP";
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
            DefaultTypeList.readtype = "GetPlayerId_ptr({0})";
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
            DefaultVars.argname = "DWFP";
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
            WriteToJassDefineHeader("union DWFP");
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
            WriteToJassNativesHook("#include \"MinHook.h\"");

            WriteToJassNativesHeaderInitialzier("#include \"JassNativesHeader.h\"");

            WriteToJassNativesHook("#pragma comment(lib, \"libMinHook.x86.lib\")");

            string[] exceptionhandlerdata = File.ReadAllLines("ExceptionHandler.txt");
            foreach (string str in exceptionhandlerdata)
                WriteToJassNativesHook(str);


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
            WriteToJassNativesHooked("	va_list args;\n va_start( args , format );\n vfprintf_s( logfile , format , args );\n va_end( args );\n /*fflush( logfile );*/");
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

            WriteToJassNativesHooked("float GetFloatFromDWFP( DWFP val )");
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
            WriteToJassNativesHooked("        stringstream s; s << unitid; s << \"(\" << GetStrID( GetUnitTypeId_ptr(unitid) ) << \")\";");
            WriteToJassNativesHooked("    return s.str( );");
            WriteToJassNativesHooked("}");

            WriteToJassNativesHooked("string GetItemHID( int itemid )");
            WriteToJassNativesHooked("{");
            WriteToJassNativesHooked("   if ( itemid == 0 ) return \"null\";");
            WriteToJassNativesHooked("        stringstream s; s << itemid; s << \"(\" << GetStrID( GetItemTypeId_ptr( itemid ) ) << \")\";");
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

            WriteToJassConfig("[JASS_DEBUG_ENGINE_BY_ABSOL]");

            for (int i = 0; i < JassNativeFunctions.Count; i++)
            {
                WriteToJassNativesHeader("extern " + JassNativeFunctions[i].FuncName +
                    "_FUNC " + JassNativeFunctions[i].FuncName + "_org;");
                WriteToJassNativesHeader("extern " + JassNativeFunctions[i].FuncName +
                    "_FUNC " + JassNativeFunctions[i].FuncName + "_ptr;");

                WriteToJassNativesHeaderInitialzier(JassNativeFunctions[i].FuncName +
                    "_FUNC " + JassNativeFunctions[i].FuncName + "_org = nullptr;");
                WriteToJassNativesHeaderInitialzier(JassNativeFunctions[i].FuncName +
                    "_FUNC " + JassNativeFunctions[i].FuncName + "_ptr = nullptr;");


                WriteToJassNativesHook("void " + JassNativeFunctions[i].FuncName + "_init ( )");
                WriteToJassNativesHook("{");
                //       WriteToJassNativesHook( "   if (JassINI.ReadBOOLean(\"JASS_DEBUG_ENGINE_BY_ABSOL\", \"" + JassNativeFunctions [ i ].FuncName + "\", FALSE))" );

                WriteToJassConfig(JassNativeFunctions[i].FuncName + "=yes");

                //     WriteToJassNativesHook( "   {" );
                WriteToJassNativesHook("      " + JassNativeFunctions[i].FuncName +
                    "_org = (" + JassNativeFunctions[i].FuncName + "_FUNC) ( GameDll + " + JassNativeFunctions[i].FuncAddr + " );");
                WriteToJassNativesHook("      MH_CreateHook(" + JassNativeFunctions[i].FuncName + "_org" +
                    ", &" + JassNativeFunctions[i].FuncName + "_my" +
                    ", reinterpret_cast<void**>(&" + JassNativeFunctions[i].FuncName + "_ptr" + "));");
                WriteToJassNativesHook("      MH_EnableHook(" + JassNativeFunctions[i].FuncName + "_org" + ");");
                //  WriteToJassNativesHook( "   }" );
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

                HookedFuncName += ")";
                WriteToJassNativesHeader("extern " + HookedFuncName + ";");
                WriteToJassNativesHooked(HookedFuncName);
                WriteToJassNativesHooked("{");
                WriteToJassNativesHooked("   funcname1 = \"" + JassNativeFunctions[i].FuncName + "\";");
                string WritePrintText, WritePrintArgs, CallFunctionString
                    , CurrentPrintType, CurrentPrintName;
                if (JassNativeFunctions[i].FuncType == "void")
                {
                    WriteToJassNativesHooked("   SpyJassLog(\" Exec:" +
                   JassNativeFunctions[i].FuncName + "...\");");

                    WritePrintText = "[" + JassNativeFunctions[i].FuncName + "] OK [";
                    WritePrintArgs = "";
                    CallFunctionString = JassNativeFunctions[i].FuncName + "_ptr(";

                    bool needremove = false;

                    foreach (argstruct FuncArg in JassNativeFunctions[i].FuncArgs)
                    {
                        CallFunctionString += FuncArg.argname.Replace("*", "") + ", ";


                        CurrentPrintType = DefaultPrintType;
                        CurrentPrintName = "GetStrID(" + FuncArg.argname + ").c_str( )";

                        foreach (PrintGetType printgettype in PrintTypeList)
                        {
                            if (FuncArg.argtype == printgettype.VarType)
                            {
                                CurrentPrintType = printgettype.PrintType;
                                CurrentPrintName = string.Format(printgettype.readtype, FuncArg.argname);
                                break;
                            }
                        }

                        WritePrintText += FuncArg.argname + ":" + CurrentPrintType + ", ";
                        WritePrintArgs += CurrentPrintName + ", ";
                        needremove = true;
                    }
                    if (needremove)
                    {
                        WritePrintText = WritePrintText.Remove(WritePrintText.Length - 2, 2) + "]";
                        WritePrintArgs = WritePrintArgs.Remove(WritePrintArgs.Length - 2, 2);

                        CallFunctionString = CallFunctionString.Remove(
                            CallFunctionString.Length - 2, 2);
                        CallFunctionString += ");";

                        WriteToJassNativesHooked("   " + CallFunctionString);
                        WriteToJassNativesHooked("   SpyJassLog(\"" +
                            WritePrintText.Replace("*", "") + "\\n\"," + WritePrintArgs + ");");

                    }
                    else
                    {
                        WritePrintText = WritePrintText + "]";
                        CallFunctionString += ");";

                        WriteToJassNativesHooked("   " + CallFunctionString);
                        WriteToJassNativesHooked("   SpyJassLog(\"" +
                            WritePrintText.Replace("*", "") + "\\n\");");

                    }
                }
                else
                {

                    WritePrintText = "[";
                    WritePrintArgs = "";

                    CallFunctionString = JassNativeFunctions[i].FuncType +
                        " returnvalue; \n   returnvalue = " + JassNativeFunctions[i].FuncName + "_ptr(";

                    bool needremove = false;

                    foreach (argstruct FuncArg in JassNativeFunctions[i].FuncArgs)
                    {
                        CallFunctionString += FuncArg.argname.Replace("*", "") + ", ";
                        CurrentPrintType = DefaultPrintType;
                        CurrentPrintName = "GetStrID(" + FuncArg.argname + ").c_str( )";

                        foreach (PrintGetType printgettype in PrintTypeList)
                        {
                            if (FuncArg.argtype == printgettype.VarType)
                            {
                                CurrentPrintType = printgettype.PrintType;
                                CurrentPrintName = string.Format(printgettype.readtype, FuncArg.argname);
                                break;
                            }
                        }

                        WritePrintText += FuncArg.argname + ":" + CurrentPrintType + ", ";

                        WritePrintArgs += CurrentPrintName + ", ";

                        needremove = true;
                    }
                    if (needremove)
                    {
                        WritePrintText = WritePrintText.Remove(WritePrintText.Length - 2, 2) + "]";
                        WritePrintArgs = WritePrintArgs.Remove(WritePrintArgs.Length - 2, 2);

                        CallFunctionString = CallFunctionString.Remove(
                            CallFunctionString.Length - 2, 2);
                        CallFunctionString += ");";

                        WriteToJassNativesHooked("   SpyJassLog(\" Exec:" +
                  JassNativeFunctions[i].FuncName +
                           WritePrintText.Replace("*", "") + "...\"," + WritePrintArgs + ");");

                        WriteToJassNativesHooked("   " + CallFunctionString);


                    }
                    else
                    {
                        WritePrintText = WritePrintText + "]";
                        CallFunctionString += ");";

                        WriteToJassNativesHooked("   SpyJassLog(\" Exec:" +
                   JassNativeFunctions[i].FuncName +
                      WritePrintText.Replace("*", "") + "...\");");

                        WriteToJassNativesHooked("   " + CallFunctionString);

                    }

                    string retprintstring = "[" + JassNativeFunctions[i].FuncName + "] OK ["; ;

                    CurrentPrintType = DefaultPrintType;
                    CurrentPrintName = "GetStrID( returnvalue ).c_str( )";

                    foreach (PrintGetType printgettype in PrintTypeList)
                    {
                        if (JassNativeFunctions[i].FuncType == printgettype.VarType)
                        {
                            CurrentPrintType = printgettype.PrintType;
                            CurrentPrintName = string.Format(printgettype.readtype, "returnvalue");
                            break;
                        }
                    }

                    WriteToJassNativesHooked("   SpyJassLog(\"" + retprintstring +
                   CurrentPrintType + "]\\n\"," + CurrentPrintName + ");");

                    WriteToJassNativesHooked("   return returnvalue;");
                }

                WriteToJassNativesHooked("}");
            }
            /*
                        for ( int i = 0 ; i < JassNativeFunctions.Count ; i++ )
                        {


                        }
                        */

            WriteToJassNativesHook("typedef int(__fastcall *LookupNative)(LPSTR,int unknown);");
            WriteToJassNativesHook("LookupNative LookupNative_org = NULL;");
            WriteToJassNativesHook("LookupNative LookupNative_ptr = NULL;");

            WriteToJassNativesHook("int __fastcall LookupNative_my(LPSTR str,int unknown)");
            WriteToJassNativesHook("{");
            WriteToJassNativesHook("   funcname2 = str;");
            WriteToJassNativesHook("   return LookupNative_ptr(str,unknown);");
            WriteToJassNativesHook("}");


            WriteToJassNativesHook("void Initializer( )");
            WriteToJassNativesHook("{");
            WriteToJassNativesHook("   LookupNative_org = (LookupNative) (GameDll + 0x44EA00);");
            WriteToJassNativesHook("   MH_CreateHook(LookupNative_org, &LookupNative_my, reinterpret_cast<void**>(&LookupNative_ptr));");
            WriteToJassNativesHook("   MH_EnableHook(LookupNative_org);");

            for (int i = 0; i < JassNativeFunctions.Count; i++)
            {
                WriteToJassNativesHook("  if ( reader.GetBoolean( \"JASS_DEBUG_ENGINE_BY_ABSOL\", \"" + JassNativeFunctions[i].FuncName + "\" , false ) )");
                WriteToJassNativesHook("      " + JassNativeFunctions[i].FuncName + "_init ( );");
            }
            WriteToJassNativesHook("}");



            /*
typedef int(__fastcall *LookupNative_)(LPSTR);
LookupNative_ fLookupNative = NULL;
             */

            WriteToJassNativesHook("BOOL APIENTRY DllMain( HINSTANCE hDLL , DWORD reason , LPVOID reserved )");
            WriteToJassNativesHook("{");
            WriteToJassNativesHook("	switch ( reason )");
            WriteToJassNativesHook("	{");
            WriteToJassNativesHook("		case DLL_PROCESS_ATTACH:");
            WriteToJassNativesHook("			logfile = _fsopen( \"JassSpy.txt\" , \"w\" , _SH_DENYWR );");
            WriteToJassNativesHook("			if ( reader.ParseError( ) < 0 )");
            WriteToJassNativesHook("			{");
            WriteToJassNativesHook("				MessageBox( 0 , \"Can't load \'JassConfig.ini\'\\n\" , \"ERROR LOAD CONFIG\" , MB_OK );");
            WriteToJassNativesHook("				return FALSE;");
            WriteToJassNativesHook("			}");
            WriteToJassNativesHook("			fprintf_s( logfile , \".......UnrealJassSpy for Warcraft 1.26a......\\n\" );");
            WriteToJassNativesHook("			setvbuf( logfile , NULL , _IOLBF , 128 );");
            WriteToJassNativesHook("			MH_Initialize( );");
            WriteToJassNativesHook("			Initializer( );");
            WriteToJassNativesHook("			AddVectoredExceptionHandler(1, TopLevelExceptionHandler);");
            // WriteToJassNativesHook( "			SetUnhandledExceptionFilter( TopLevelExceptionHandler );" );
            WriteToJassNativesHook("		break;");
            WriteToJassNativesHook("		case DLL_PROCESS_DETACH:");
            WriteToJassNativesHook("			MH_Uninitialize( );");
            WriteToJassNativesHook("		break;");
            WriteToJassNativesHook("	}");
            WriteToJassNativesHook("	return TRUE;");
            WriteToJassNativesHook("}");

        }
    }
}
