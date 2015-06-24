// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
//#include "../LazyLoad/LazyLoad.h"
#include "../WindowsUtil/EnvironmentBlock.h"
#include "../WindowsUtil/PeImage.h"
using namespace std;


void TestPeDecoder()
{
	const int maxSpace = 50;
	const int minSpace = 2;
	int space = minSpace;
	
#define TO_RIGHT space+=2;if(space>maxSpace){space=maxSpace;}{
#define TO_LEFT }space-=2;if(space<minSpace){space=minSpace;}
#define DISPLAY_STRUCT_HEX(structVal, name) cout <<setw(space)<<""<<setw(maxSpace-space)<< #name <<" - 0x"<< hex<< structVal->name << endl
#define DISPLAY_STRUCT_HEX2(structVal, name) cout <<setw(space)<<""<<setw(maxSpace-space)<< #name <<" - 0x"<< hex<< structVal.name << endl
#define DISPLAY_STRUCT_POINTER_HEX(structVal, name) cout<<setw(space)<<""<<setw(maxSpace-space)<< #name <<" - 0x"<< hex<< &structVal->name << endl

#define DISPLAY_HEX(name,val) cout <<setw(space)<<""<<setw(maxSpace-space)<<name <<" - 0x"<< hex << val<< endl
#define DISPLAY_MSG(msg) cout <<setw(space)<<""<<msg<< endl

	cout.setf(ios::left | ios::boolalpha);

	// pe解析器测试, 只做测试怎么简单怎么编
	PE::PeDecoder pe(GetModuleHandleA(NULL), true);
	if (pe.IsPE())
	{
		// dosHeader
		auto dosHeader = pe.DosHeader();		
		DISPLAY_HEX("[Dos Header]", dosHeader);		
		TO_RIGHT
			DISPLAY_STRUCT_HEX(dosHeader, e_magic);
			DISPLAY_STRUCT_HEX(dosHeader, e_cblp);
			DISPLAY_STRUCT_HEX(dosHeader, e_cp);
			DISPLAY_STRUCT_HEX(dosHeader, e_crlc);
			DISPLAY_STRUCT_HEX(dosHeader, e_cparhdr);
			DISPLAY_STRUCT_HEX(dosHeader, e_minalloc);
			DISPLAY_STRUCT_HEX(dosHeader, e_maxalloc);
			DISPLAY_STRUCT_HEX(dosHeader, e_ss);
			DISPLAY_STRUCT_HEX(dosHeader, e_sp);
			DISPLAY_STRUCT_HEX(dosHeader, e_csum);
			DISPLAY_STRUCT_HEX(dosHeader, e_ip);
			DISPLAY_STRUCT_HEX(dosHeader, e_cs);
			DISPLAY_STRUCT_HEX(dosHeader, e_lfarlc);
			DISPLAY_STRUCT_HEX(dosHeader, e_ovno);
			DISPLAY_STRUCT_HEX(dosHeader, e_res); // 输出数组指针
			DISPLAY_STRUCT_HEX(dosHeader, e_oemid);
			DISPLAY_STRUCT_HEX(dosHeader, e_oeminfo);
			DISPLAY_STRUCT_HEX(dosHeader, e_res2); // 输出数组指针
			DISPLAY_STRUCT_HEX(dosHeader, e_lfanew);
		TO_LEFT
		cout << endl;
		if (pe.HasNtHeader32())
		{
			auto ntHeader = pe.NtHeader32();
			//cout << "[Is 32 PE]" << endl;
			// ntHeader
			DISPLAY_HEX("[NtHeader 32]",ntHeader);
			TO_RIGHT
				DISPLAY_STRUCT_HEX(ntHeader, Signature); 			
				DISPLAY_STRUCT_POINTER_HEX(ntHeader, FileHeader);
				// FileHeader
				TO_RIGHT
					auto fileHeader = ntHeader->FileHeader;
					DISPLAY_STRUCT_HEX2(fileHeader, Machine);
					DISPLAY_STRUCT_HEX2(fileHeader, NumberOfSections);
					DISPLAY_STRUCT_HEX2(fileHeader, TimeDateStamp);
					DISPLAY_STRUCT_HEX2(fileHeader, PointerToSymbolTable);
					DISPLAY_STRUCT_HEX2(fileHeader, NumberOfSymbols);
					DISPLAY_STRUCT_HEX2(fileHeader, SizeOfOptionalHeader);
					DISPLAY_STRUCT_HEX2(fileHeader, Characteristics);
				TO_LEFT

				// OptionalHeader
				DISPLAY_STRUCT_POINTER_HEX(ntHeader, OptionalHeader);
				auto optionalHeader = ntHeader->OptionalHeader;	
				TO_RIGHT							
					DISPLAY_STRUCT_HEX2(optionalHeader, Magic);
					DISPLAY_STRUCT_HEX2(optionalHeader, MajorLinkerVersion);
					DISPLAY_STRUCT_HEX2(optionalHeader, MinorLinkerVersion);
					DISPLAY_STRUCT_HEX2(optionalHeader, SizeOfCode);
					DISPLAY_STRUCT_HEX2(optionalHeader, SizeOfInitializedData);
					DISPLAY_STRUCT_HEX2(optionalHeader, SizeOfUninitializedData);
					DISPLAY_STRUCT_HEX2(optionalHeader, AddressOfEntryPoint);
					DISPLAY_STRUCT_HEX2(optionalHeader, BaseOfCode);
					DISPLAY_STRUCT_HEX2(optionalHeader, BaseOfData);
					DISPLAY_STRUCT_HEX2(optionalHeader, ImageBase);
					DISPLAY_STRUCT_HEX2(optionalHeader, SectionAlignment);
					DISPLAY_STRUCT_HEX2(optionalHeader, FileAlignment);
					DISPLAY_STRUCT_HEX2(optionalHeader, MajorOperatingSystemVersion);
					DISPLAY_STRUCT_HEX2(optionalHeader, MinorOperatingSystemVersion);
					DISPLAY_STRUCT_HEX2(optionalHeader, MajorImageVersion);
					DISPLAY_STRUCT_HEX2(optionalHeader, MinorImageVersion);
					DISPLAY_STRUCT_HEX2(optionalHeader, MajorSubsystemVersion);
					DISPLAY_STRUCT_HEX2(optionalHeader, MinorSubsystemVersion);
					DISPLAY_STRUCT_HEX2(optionalHeader, Win32VersionValue);
					DISPLAY_STRUCT_HEX2(optionalHeader, SizeOfImage);
					DISPLAY_STRUCT_HEX2(optionalHeader, SizeOfHeaders);
					DISPLAY_STRUCT_HEX2(optionalHeader, CheckSum);
					DISPLAY_STRUCT_HEX2(optionalHeader, Subsystem);
					DISPLAY_STRUCT_HEX2(optionalHeader, DllCharacteristics);
					DISPLAY_STRUCT_HEX2(optionalHeader, SizeOfStackReserve);
					DISPLAY_STRUCT_HEX2(optionalHeader, SizeOfStackCommit);
					DISPLAY_STRUCT_HEX2(optionalHeader, SizeOfHeapReserve);
					DISPLAY_STRUCT_HEX2(optionalHeader, SizeOfHeapCommit);
					DISPLAY_STRUCT_HEX2(optionalHeader, LoaderFlags);
					DISPLAY_STRUCT_HEX2(optionalHeader, NumberOfRvaAndSizes);
					DISPLAY_STRUCT_HEX2(optionalHeader, DataDirectory);

					// 数据目录
					TO_RIGHT						
						auto dataDirectory = optionalHeader.DataDirectory;
						for (int i = 0; i < optionalHeader.NumberOfRvaAndSizes; i++)
						{
							auto dataDir = dataDirectory++;
	#define DISPLAY_DATA_DIR(name) DISPLAY_HEX(#name, dataDir);\
			TO_RIGHT\
			DISPLAY_STRUCT_HEX(dataDir,VirtualAddress);\
			DISPLAY_STRUCT_HEX(dataDir,Size);\
			TO_LEFT							
							switch (i)
							{
							case IMAGE_DIRECTORY_ENTRY_EXPORT:
								DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_EXPORT);
								break;
							case IMAGE_DIRECTORY_ENTRY_IMPORT:
								DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_IMPORT);
								break;
							case IMAGE_DIRECTORY_ENTRY_RESOURCE:
								DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_RESOURCE);
								break;
							case IMAGE_DIRECTORY_ENTRY_EXCEPTION:
								DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_EXCEPTION);
								break;
							case IMAGE_DIRECTORY_ENTRY_SECURITY:
								DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_SECURITY);
								break;
							case IMAGE_DIRECTORY_ENTRY_BASERELOC:
								DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_BASERELOC);
								break;
							case IMAGE_DIRECTORY_ENTRY_DEBUG:
								DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_DEBUG);
								break;
							case IMAGE_DIRECTORY_ENTRY_ARCHITECTURE:
								DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_ARCHITECTURE);
								break;
							case IMAGE_DIRECTORY_ENTRY_GLOBALPTR:
								DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_GLOBALPTR);
								break;
							case IMAGE_DIRECTORY_ENTRY_TLS:
								DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_TLS);
								break;
							case IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG:
								DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG);
								break;
							case IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT:
								DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT);
								break;
							case IMAGE_DIRECTORY_ENTRY_IAT:
								DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_IAT);
								break;
							case IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT:
								DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT);
								break;
							case IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR:
								DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR);
								break;
							default:
								break;
							}						
						}
						TO_LEFT
					// end dataDirectory
					TO_LEFT
				// end optionalHeader
				TO_LEFT
				// end ntheader
				cout << endl;
				DISPLAY_MSG("[Section]");
				PE::SectionReader sr(pe);
				while (sr.Next())
				{
					auto tmpSection = sr.Current();
					DISPLAY_HEX(tmpSection->Name, tmpSection);
					TO_RIGHT						
						DISPLAY_STRUCT_HEX(tmpSection, Misc.PhysicalAddress);
						DISPLAY_STRUCT_HEX(tmpSection, Misc.VirtualSize);
						DISPLAY_STRUCT_HEX(tmpSection, VirtualAddress); // 节位置rva
						DISPLAY_STRUCT_HEX(tmpSection, SizeOfRawData);
						DISPLAY_STRUCT_HEX(tmpSection, PointerToRawData); // 文件位置偏移量
						DISPLAY_STRUCT_HEX(tmpSection, PointerToRelocations);
						DISPLAY_STRUCT_HEX(tmpSection, PointerToLinenumbers);
						DISPLAY_STRUCT_HEX(tmpSection, NumberOfRelocations);
						DISPLAY_STRUCT_HEX(tmpSection, NumberOfLinenumbers);
						DISPLAY_STRUCT_HEX(tmpSection, Characteristics);
					TO_LEFT
				}
				cout << endl;
				DISPLAY_MSG("[Export]");
				TO_RIGHT
					auto export = pe.GetImageExport();
					DISPLAY_STRUCT_HEX(export, Characteristics);
					DISPLAY_STRUCT_HEX(export, TimeDateStamp);
					DISPLAY_STRUCT_HEX(export, MajorVersion);
					DISPLAY_STRUCT_HEX(export, MinorVersion);
					//DISPLAY_STRUCT_HEX(export, Name);
					
					DISPLAY_HEX("Name", export->Name<< " ["<<(PCHAR)pe.GetRvaData(export->Name)<<"]");
					DISPLAY_STRUCT_HEX(export, Base);
					DISPLAY_STRUCT_HEX(export, NumberOfFunctions);
					DISPLAY_STRUCT_HEX(export, NumberOfNames);
					DISPLAY_STRUCT_HEX(export, AddressOfFunctions);
					DISPLAY_STRUCT_HEX(export, AddressOfNames);
					DISPLAY_STRUCT_HEX(export, AddressOfNameOrdinals);
					TO_RIGHT
						PE::ExportReader er(pe);
						while (er.Next())
						{
							DISPLAY_HEX("Ordinals", *er.CurrentNameOrdinals());
							TO_RIGHT
							auto nameRva = er.CurrentNameRva();
							if (nameRva)
							{
								auto name = (PCHAR)pe.GetRvaData(*nameRva);
								DISPLAY_MSG("Name ["<<name<<"]");

								// 附加测试 - 运行读取到的导出函数	
								if (strcmp(name, "B") == 0 || strcmp(name, "?A@@YAPADXZ") == 0)
								{
									auto function = (PCHAR(*)())pe.GetRvaData(*er.CurrentFuncRva());
									DISPLAY_MSG("=== Call Function === ["<<function()<<"]");
								}
								
								// 附加测试结束

								DISPLAY_HEX("NameRva", *nameRva);
								
							}
					
							DISPLAY_HEX("FuncRva", *er.CurrentFuncRva());
							TO_LEFT
						}
					TO_LEFT
					// TODO: 导入表

				TO_LEFT
		}
		else
		{
			auto ntHeader = pe.NtHeader64();
			DISPLAY_HEX("NtHeader64",ntHeader);
			DISPLAY_STRUCT_HEX(ntHeader, Signature);
			DISPLAY_STRUCT_POINTER_HEX(ntHeader, FileHeader);
			DISPLAY_STRUCT_POINTER_HEX(ntHeader, OptionalHeader);
		}




	}
	else
	{
		cout << "Not a PE" << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{

	//_asm pushad
	//InitLazyLoad();
	////InitLazyLoad();
	//Lazy_MessageBoxA(0, 0, 0, 0);
	//MessageBoxA(0, 0, 0, 0);
	//auto x = Peb::FindLoadedModuleHandle(L"ntdll.dll");

	TestPeDecoder();

	system("pause");
	return 0;
}
#pragma region 导出表测试数据
#define Export __declspec(dllexport)

Export PCHAR  A()
{
	return "A - Success";
}
extern "C"
Export PCHAR B()
{
	return "B - Success";
}
class MyClass
{
public:
	Export MyClass(){}
	Export ~MyClass(){}

private:
	Export void C(){}
};
#pragma endregion