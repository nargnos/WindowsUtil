// 为了添加用于解析的数据,这个工程有点乱
// 里面包含了编写过程中写的一些测试,很杂
// 现在运行后会解析出自身pe的信息,因为之前是一条条测试的,整体混合就很乱,有时间再整理

#include "stdafx.h"
#include <Windows.h>
#include <WinBase.h>
#include <iostream>
#include <fstream>
#include <iomanip>

#include <PeImage.h>
#include <Process\LazyLoad\LazyLoadSystemApi.h>
#include <Process\OverwriteWinApi\OverwriteWinApi.h>
#include <Process\Hook\IatHook.h>
#include <Process\Hook\ApiHook.h>
#include <Process\Hook\EatHook.h>
#include <Process\Hook\DelayLoadHook.h>
#include <PE\DelayLoad\DelayLoad.h>

//#include <Asm\OpcodeReader.h>
#pragma comment(lib,"Shlwapi.lib")

using namespace std;
using namespace PE;

ofstream of;
const int maxSpace = 50;
const int minSpace = 2;
int space = minSpace;

__declspec(thread) int a = 0;


#define OUTPUT_FILENAME ".//output.txt"
#define SHOW_FILE system("start " OUTPUT_FILENAME);

#define DISPLAY_DES of//cout
#define TO_RIGHT space+=2;if(space>maxSpace){space=maxSpace;}{
#define TO_LEFT }space-=2;if(space<minSpace){space=minSpace;}
#define DISPLAY_STRUCT_HEX(structVal, name) DISPLAY_DES <<setw(space)<<""<<setw(maxSpace-space)<< #name <<" - 0x"<< hex<< structVal->name << endl
#define DISPLAY_STRUCT_HEX2(structVal, name) DISPLAY_DES <<setw(space)<<""<<setw(maxSpace-space)<< #name <<" - 0x"<< hex<< structVal.name << endl
#define DISPLAY_STRUCT_POINTER_HEX(structVal, name) DISPLAY_DES<<setw(space)<<""<<setw(maxSpace-space)<< #name <<" - 0x"<< hex<< &structVal->name << endl

#define DISPLAY_HEX(name,val) DISPLAY_DES <<setw(space)<<""<<setw(maxSpace-space)<<name <<" - 0x"<< hex << val<< endl
#define DISPLAY_MSG(msg) DISPLAY_DES <<setw(space)<<""<<msg<< endl
#define DISPLAY_PAUSE DISPLAY_DES << "-- MORE --" << endl;system("pause");


#pragma region 导入表测试数据
bool __stdcall HookBeep(DWORD val1, DWORD val2)
{
	DISPLAY_DES << "Hook Success. Params: " << val1 << " " << val2 << endl;
	return true;
}
#pragma endregion
#pragma region 导出表测试数据
#define ExportFunc __declspec(dllexport)

ExportFunc PCHAR  A()
{
	a++;
	return "A - Success";
}
extern "C"
ExportFunc PCHAR B()
{
	a++;
	return "B - Success";
}
class MyClass
{
public:
	ExportFunc MyClass(){}
	ExportFunc ~MyClass(){}

private:
	ExportFunc void C()
	{
	}
	ExportFunc  void __stdcall D()
	{
		MessageBoxA(0, 0, 0, 0);
	}
};
#pragma endregion



ExportFunc void PrintDosHeader(PIMAGE_DOS_HEADER dosHeader)
{

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

}

ExportFunc void PrintNtHeader32(PIMAGE_NT_HEADERS32 ntHeader)
{
	DISPLAY_STRUCT_HEX(ntHeader, Signature);
	DISPLAY_STRUCT_POINTER_HEX(ntHeader, FileHeader);
}
void PrintNtHeader64(PIMAGE_NT_HEADERS64 ntHeader)
{
	DISPLAY_STRUCT_HEX(ntHeader, Signature);
	DISPLAY_STRUCT_POINTER_HEX(ntHeader, FileHeader);
}
ExportFunc void PrintFileHeader(PIMAGE_FILE_HEADER fileHeader)
{
	DISPLAY_STRUCT_HEX(fileHeader, Machine);
	DISPLAY_STRUCT_HEX(fileHeader, NumberOfSections);
	DISPLAY_STRUCT_HEX(fileHeader, TimeDateStamp);
	DISPLAY_STRUCT_HEX(fileHeader, PointerToSymbolTable);
	DISPLAY_STRUCT_HEX(fileHeader, NumberOfSymbols);
	DISPLAY_STRUCT_HEX(fileHeader, SizeOfOptionalHeader);
	DISPLAY_STRUCT_HEX(fileHeader, Characteristics);
}
ExportFunc void PrintOptionalHeader32(PIMAGE_OPTIONAL_HEADER32 optionalHeader)
{
	DISPLAY_STRUCT_HEX(optionalHeader, Magic);
	DISPLAY_STRUCT_HEX(optionalHeader, MajorLinkerVersion);
	DISPLAY_STRUCT_HEX(optionalHeader, MinorLinkerVersion);
	DISPLAY_STRUCT_HEX(optionalHeader, SizeOfCode);
	DISPLAY_STRUCT_HEX(optionalHeader, SizeOfInitializedData);
	DISPLAY_STRUCT_HEX(optionalHeader, SizeOfUninitializedData);
	DISPLAY_STRUCT_HEX(optionalHeader, AddressOfEntryPoint);
	DISPLAY_STRUCT_HEX(optionalHeader, BaseOfCode);
	DISPLAY_STRUCT_HEX(optionalHeader, BaseOfData);
	DISPLAY_STRUCT_HEX(optionalHeader, ImageBase);
	DISPLAY_STRUCT_HEX(optionalHeader, SectionAlignment);
	DISPLAY_STRUCT_HEX(optionalHeader, FileAlignment);
	DISPLAY_STRUCT_HEX(optionalHeader, MajorOperatingSystemVersion);
	DISPLAY_STRUCT_HEX(optionalHeader, MinorOperatingSystemVersion);
	DISPLAY_STRUCT_HEX(optionalHeader, MajorImageVersion);
	DISPLAY_STRUCT_HEX(optionalHeader, MinorImageVersion);
	DISPLAY_STRUCT_HEX(optionalHeader, MajorSubsystemVersion);
	DISPLAY_STRUCT_HEX(optionalHeader, MinorSubsystemVersion);
	DISPLAY_STRUCT_HEX(optionalHeader, Win32VersionValue);
	DISPLAY_STRUCT_HEX(optionalHeader, SizeOfImage);
	DISPLAY_STRUCT_HEX(optionalHeader, SizeOfHeaders);
	DISPLAY_STRUCT_HEX(optionalHeader, CheckSum);
	DISPLAY_STRUCT_HEX(optionalHeader, Subsystem);
	DISPLAY_STRUCT_HEX(optionalHeader, DllCharacteristics);
	DISPLAY_STRUCT_HEX(optionalHeader, SizeOfStackReserve);
	DISPLAY_STRUCT_HEX(optionalHeader, SizeOfStackCommit);
	DISPLAY_STRUCT_HEX(optionalHeader, SizeOfHeapReserve);
	DISPLAY_STRUCT_HEX(optionalHeader, SizeOfHeapCommit);
	DISPLAY_STRUCT_HEX(optionalHeader, LoaderFlags);
	DISPLAY_STRUCT_HEX(optionalHeader, NumberOfRvaAndSizes);
	DISPLAY_STRUCT_HEX(optionalHeader, DataDirectory);
}
ExportFunc void PrintOptionalHeader64(PIMAGE_OPTIONAL_HEADER64 optionalHeader)
{
	DISPLAY_STRUCT_HEX(optionalHeader, Magic);
	DISPLAY_STRUCT_HEX(optionalHeader, MajorLinkerVersion);
	DISPLAY_STRUCT_HEX(optionalHeader, MinorLinkerVersion);
	DISPLAY_STRUCT_HEX(optionalHeader, SizeOfCode);
	DISPLAY_STRUCT_HEX(optionalHeader, SizeOfInitializedData);
	DISPLAY_STRUCT_HEX(optionalHeader, SizeOfUninitializedData);
	DISPLAY_STRUCT_HEX(optionalHeader, AddressOfEntryPoint);
	DISPLAY_STRUCT_HEX(optionalHeader, BaseOfCode);
	//DISPLAY_STRUCT_HEX(optionalHeader, BaseOfData);
	DISPLAY_STRUCT_HEX(optionalHeader, ImageBase);
	DISPLAY_STRUCT_HEX(optionalHeader, SectionAlignment);
	DISPLAY_STRUCT_HEX(optionalHeader, FileAlignment);
	DISPLAY_STRUCT_HEX(optionalHeader, MajorOperatingSystemVersion);
	DISPLAY_STRUCT_HEX(optionalHeader, MinorOperatingSystemVersion);
	DISPLAY_STRUCT_HEX(optionalHeader, MajorImageVersion);
	DISPLAY_STRUCT_HEX(optionalHeader, MinorImageVersion);
	DISPLAY_STRUCT_HEX(optionalHeader, MajorSubsystemVersion);
	DISPLAY_STRUCT_HEX(optionalHeader, MinorSubsystemVersion);
	DISPLAY_STRUCT_HEX(optionalHeader, Win32VersionValue);
	DISPLAY_STRUCT_HEX(optionalHeader, SizeOfImage);
	DISPLAY_STRUCT_HEX(optionalHeader, SizeOfHeaders);
	DISPLAY_STRUCT_HEX(optionalHeader, CheckSum);
	DISPLAY_STRUCT_HEX(optionalHeader, Subsystem);
	DISPLAY_STRUCT_HEX(optionalHeader, DllCharacteristics);
	DISPLAY_STRUCT_HEX(optionalHeader, SizeOfStackReserve);
	DISPLAY_STRUCT_HEX(optionalHeader, SizeOfStackCommit);
	DISPLAY_STRUCT_HEX(optionalHeader, SizeOfHeapReserve);
	DISPLAY_STRUCT_HEX(optionalHeader, SizeOfHeapCommit);
	DISPLAY_STRUCT_HEX(optionalHeader, LoaderFlags);
	DISPLAY_STRUCT_HEX(optionalHeader, NumberOfRvaAndSizes);
	DISPLAY_STRUCT_HEX(optionalHeader, DataDirectory);
}
ExportFunc void PrintDataDirectory(PIMAGE_DATA_DIRECTORY dataDirectory, DWORD numberOfRvaAndSizes)
{
	for (DWORD i = 0; i < numberOfRvaAndSizes; i++)
	{
		auto dataDir = dataDirectory++;
#define CASE_DISPLAY_DATA_DIR(name) case name:\
			 DISPLAY_HEX(#name, dataDir);\
			TO_RIGHT;\
			DISPLAY_STRUCT_HEX(dataDir,VirtualAddress);\
			DISPLAY_STRUCT_HEX(dataDir,Size);\
			TO_LEFT;\
			break;
		switch (i)
		{
			CASE_DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_EXPORT);	
			CASE_DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_IMPORT);
			CASE_DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_RESOURCE);
			CASE_DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_EXCEPTION);
			CASE_DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_SECURITY);
			CASE_DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_BASERELOC);
			CASE_DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_DEBUG);
			CASE_DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_ARCHITECTURE);
			CASE_DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_GLOBALPTR);
			CASE_DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_TLS);
			CASE_DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG);
			CASE_DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT);
			CASE_DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_IAT);
			CASE_DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT);
			CASE_DISPLAY_DATA_DIR(IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR);
		default:
			break;
		}
	}
}

ExportFunc void PrintSection(PeDecoder& pe)
{
	Section::SectionReader sr(pe);
	while (sr.Next())
	{
		auto tmpSection = sr.Current();
		DISPLAY_HEX(tmpSection->Name, tmpSection);
		TO_RIGHT;
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
		TO_LEFT;
	}
}

ExportFunc void PrintExport(PeDecoder& pe)
{
	auto export = pe.GetImageExport();
	DISPLAY_STRUCT_HEX(export, Characteristics);
	DISPLAY_STRUCT_HEX(export, TimeDateStamp);
	DISPLAY_STRUCT_HEX(export, MajorVersion);
	DISPLAY_STRUCT_HEX(export, MinorVersion);
	//DISPLAY_STRUCT_HEX(export, Name);

	DISPLAY_HEX("Name", export->Name << " [" << (PCHAR)pe.GetRvaData(export->Name) << "]");
	DISPLAY_STRUCT_HEX(export, Base);
	DISPLAY_STRUCT_HEX(export, NumberOfFunctions);
	DISPLAY_STRUCT_HEX(export, NumberOfNames);
	DISPLAY_STRUCT_HEX(export, AddressOfFunctions);
	DISPLAY_STRUCT_HEX(export, AddressOfNames);
	DISPLAY_STRUCT_HEX(export, AddressOfNameOrdinals);
	TO_RIGHT;
	Export::ExportReader er(pe);
	while (er.Next())
	{
		DISPLAY_HEX("Ordinals", *er.CurrentNameOrdinals());
		TO_RIGHT;
		auto nameRva = er.CurrentNameRva();
		if (nameRva)
		{
			auto name = (PCHAR)pe.GetRvaData(*nameRva);
			DISPLAY_MSG("Name [" << name << "]");

			// 附加测试 - 运行读取到的导出函数	
			if (strcmp(name, "B") == 0 || strcmp(name, "?A@@YAPADXZ") == 0)
			{
				auto function = (PCHAR(*)())pe.GetRvaData(*er.CurrentFuncRva());
				DISPLAY_MSG("=== Call Function === [" << function() << "]");
			}

			// 附加测试结束

			DISPLAY_HEX("NameRva", *nameRva);

		}

		DISPLAY_HEX("FuncRva", *er.CurrentFuncRva());
		TO_LEFT;
	}
	TO_LEFT;
}

void PrintImport(PeDecoder& pe)
{
	Import::ImportDescriptorReader idr(pe);
	Import::ImportThunkReader itr;
	while (idr.Next())
	{
		auto tmpDr = idr.Current();
		DISPLAY_MSG(Import::GetDescriptorName(pe, tmpDr) << " [OFT: 0x" << tmpDr->OriginalFirstThunk << "] [FT: 0x" << tmpDr->FirstThunk << "]");
		itr.Init(pe, tmpDr);
		TO_RIGHT;
		while (itr.Next())
		{
			auto tmpThunk = itr.CurrentOriginalThunk32();
			if (!Import::IsSnapByOrdinal(tmpThunk))
			{
				auto tmpName = Import::GetNameStruct(pe, tmpThunk);

				DISPLAY_MSG(tmpName->Name);
				TO_RIGHT;
				DISPLAY_HEX("OFT", tmpThunk->u1.AddressOfData);
				DISPLAY_HEX("FT", itr.CurrentThunk32()->u1.AddressOfData);
				DISPLAY_HEX("Hint", tmpName->Hint);
				TO_LEFT;
				// 附加测试 iat hook - Beep
				if (pe.IsMapped())
				{
					if (strcmp((char*)tmpName->Name, "Beep") == 0)
					{
						auto hookAddr = itr.CurrentThunk32();
						DWORD oldProtect;
						Process::Overwrite::_VirtualProtect((LPVOID)hookAddr, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &oldProtect);
						*(PDWORD)hookAddr = (DWORD)HookBeep;
						Process::Overwrite::_VirtualProtect((LPVOID)hookAddr, sizeof(DWORD), oldProtect, NULL);
						DISPLAY_HEX("New - FT", itr.CurrentThunk32()->u1.AddressOfData);
						DISPLAY_MSG(endl);
						DISPLAY_MSG("[Run Iat Hook Function]");
						Beep(0x1b8, 1000);
						DISPLAY_MSG("[Run Iat Hook Function]");
						Beep(0xdc, 1000);
						DISPLAY_MSG(endl);

					}

				}
				// 附加测试结束
			}
			else
			{
				auto tmpOrdinal = Import::GetOrdinal(tmpThunk);
				DISPLAY_MSG("Ordinal: " << tmpOrdinal);
				TO_RIGHT;
				DISPLAY_HEX("OFT", tmpThunk->u1.AddressOfData);
				DISPLAY_HEX("FT", itr.CurrentThunk32());
				TO_LEFT;
			}
		}
		TO_LEFT;

	}
}

void PrintImport64(PeDecoder& pe)
{
	Import::ImportDescriptorReader idr(pe);
	Import::ImportThunkReader itr;
	while (idr.Next())
	{
		auto tmpDr = idr.Current();
		DISPLAY_MSG(Import::GetDescriptorName(pe, tmpDr) << " [OFT: 0x" << tmpDr->OriginalFirstThunk << "] [FT: 0x" << tmpDr->FirstThunk << "]");
		itr.Init(pe, tmpDr);
		TO_RIGHT;
		while (itr.Next())
		{
			auto tmpThunk = itr.CurrentOriginalThunk64();
			if (!Import::IsSnapByOrdinal(tmpThunk))
			{
				auto tmpName = Import::GetNameStruct(pe, tmpThunk);

				DISPLAY_MSG(tmpName->Name);
				TO_RIGHT;
				DISPLAY_HEX("OFT", tmpThunk->u1.AddressOfData);
				DISPLAY_HEX("FT", itr.CurrentThunk64()->u1.AddressOfData);
				DISPLAY_HEX("Hint", tmpName->Hint);
				TO_LEFT;
				// 附加测试 iat hook - Beep
				if (pe.IsMapped())
				{
					if (strcmp((char*)tmpName->Name, "Beep") == 0)
					{
						auto hookAddr = itr.CurrentThunk64();
						DWORD oldProtect;
						Process::Overwrite::_VirtualProtect((LPVOID)hookAddr, sizeof(DWORDLONG), PAGE_EXECUTE_READWRITE, &oldProtect);
						*(PDWORDLONG)hookAddr = (DWORDLONG)HookBeep;
						Process::Overwrite::_VirtualProtect((LPVOID)hookAddr, sizeof(DWORDLONG), oldProtect, NULL);
						DISPLAY_HEX("New - FT", itr.CurrentThunk64()->u1.AddressOfData);
						DISPLAY_MSG(endl);
						DISPLAY_MSG("[Run Iat Hook Function]");
						Beep(0x1b8, 1000);
						DISPLAY_MSG("[Run Iat Hook Function]");
						Beep(0xdc, 1000);
						DISPLAY_MSG(endl);
						
					}

				}
				// 附加测试结束
			}
			else
			{
				auto tmpOrdinal = Import::GetOrdinal(tmpThunk);
				DISPLAY_MSG("Ordinal: " << tmpOrdinal);
				TO_RIGHT;
				DISPLAY_HEX("OFT", tmpThunk->u1.AddressOfData);
				DISPLAY_HEX("FT", itr.CurrentThunk64());
				TO_LEFT;
			}
		}
		TO_LEFT;

	}
}

bool PrintResourceEntryNameOrId(LPCSTR str,PIMAGE_RESOURCE_DIRECTORY root, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry)
{
	bool result = false;
	if (entry->NameIsString)
	{
		auto name = Resource::LocateEntryName(root, entry);
		auto tmpNameLen = name->Length + 1;
		PSTR tmpName = new CHAR[tmpNameLen];
		memset(tmpName, 0, sizeof(CHAR)*(tmpNameLen));
		WideCharToMultiByte(0, 0, (LPCWCH)name->NameString, name->Length, tmpName, tmpNameLen, NULL, NULL);
		DISPLAY_MSG(str<<" Name: " << tmpName);

		// 附加测试
		if (strcmp(tmpName,"DATA") == 0)
		{
			result = true;
		}
		// 附加测试结束

		delete[] tmpName;
	}
	else
	{
		DISPLAY_MSG(str<<" ID: " << dec << entry->Id);
	}
	return result;
}
void PrintResource(PeDecoder& pe)
{
	auto res = pe.GetImageResource();
	Resource::ResourceDirectoryReader resRoot(res);
	while (resRoot.NextTypeDirectoryEntry())
	{
		// 资源类型
		PrintResourceEntryNameOrId("Group",res, resRoot.CurrentTypeDirectoryEntry());
		TO_RIGHT;
		// 资源名
		while (resRoot.NextResourceNameDirectoryEntry())
		{
			bool isNameData = false; // 附加测试
			if (PrintResourceEntryNameOrId("Resource", res, resRoot.CurrentResourceNameDirectoryEntry()))
			{
				// 附加测试
				isNameData = true;
				// 附加测试结束
			}
			// 资源语言
			
			TO_RIGHT;
			while (resRoot.NextLanguageDirectoryEntry())
			{
				PrintResourceEntryNameOrId("Language", res, resRoot.CurrentLanguageDirectoryEntry());
				TO_RIGHT;
				auto tmpData = resRoot.CurrentResourceDataEntry();
				DISPLAY_MSG("Resource Size: 0x" <<hex<< tmpData->Size);
				auto dataAddr = pe.GetRvaData(tmpData->OffsetToData);
				DISPLAY_MSG("Resource Address: 0x" << dataAddr);
				// 附加测试
				if (isNameData)
				{
					DISPLAY_MSG("Get Resource: " << (LPCSTR)dataAddr);
				}
				// 附加测试结束
				TO_LEFT;
			}
		TO_LEFT;
		}	
		
		TO_LEFT;
	}

}

void PrintReloc(PeDecoder& pe)
{
	Reloc::BaseRelocationReader brr(pe);
	Reloc::TypeOffsetReader tmpTor;
	DWORD count = 0;
	while (brr.Next())
	{
		DISPLAY_MSG("[" << dec << count++ << "]");
		TO_RIGHT;
		auto tmpReloc = brr.Current();
		DISPLAY_STRUCT_HEX(tmpReloc, VirtualAddress);
		DISPLAY_STRUCT_HEX(tmpReloc, SizeOfBlock);
		TO_RIGHT;
		tmpTor.Init(tmpReloc);
		while (tmpTor.Next())
		{
			LPSTR tmpType;
#define CASE_SET_STR(caseVal, var) case caseVal: var = #caseVal;break;
			switch (tmpTor.CurrentType())
			{
				CASE_SET_STR(IMAGE_REL_BASED_ABSOLUTE, tmpType);
				CASE_SET_STR(IMAGE_REL_BASED_HIGH, tmpType);
				CASE_SET_STR(IMAGE_REL_BASED_LOW, tmpType);
				CASE_SET_STR(IMAGE_REL_BASED_HIGHLOW, tmpType);
				CASE_SET_STR(IMAGE_REL_BASED_HIGHADJ, tmpType);
				//CASE_SET_STR(IMAGE_REL_BASED_MACHINE_SPECIFIC_5, tmpType);
				//CASE_SET_STR(IMAGE_REL_BASED_RESERVED, tmpType);
				//CASE_SET_STR(IMAGE_REL_BASED_MACHINE_SPECIFIC_7, tmpType);
				//CASE_SET_STR(IMAGE_REL_BASED_MACHINE_SPECIFIC_8, tmpType);
				//CASE_SET_STR(IMAGE_REL_BASED_MACHINE_SPECIFIC_9, tmpType);
				CASE_SET_STR(IMAGE_REL_BASED_DIR64, tmpType);
			default:
				tmpType = "Unknown";
				break;
			}
			DISPLAY_MSG("0x" << *tmpTor.Current() << "  RVA: 0x" << tmpTor.CurrentRelocRva() << "   Type: " << tmpType);
		}
		TO_LEFT;
		TO_LEFT;
	}
}

void PrintDelay(PeDecoder& pe)
{
	PE::DelayLoad::DelayLoadDescriptorReader ddr(pe);
	PE::DelayLoad::DelayLoadThunkReader dtr;
	while (ddr.Next())
	{
		auto curDdr = ddr.Current();
		auto dllName = PE::DelayLoad::GetDelayloadDllName(pe, curDdr);
		DISPLAY_MSG(dllName);
		TO_RIGHT;
		dtr.Init(pe, curDdr);
		while (dtr.Next())
		{
			auto curNameTable = (PIMAGE_THUNK_DATA32)dtr.CurrentNameTable();
			if (!PE::Import::IsSnapByOrdinal(curNameTable))
			{
				auto funcName = (PIMAGE_IMPORT_BY_NAME)pe.GetRvaData(*(HANDLE_PTR*)curNameTable);
				DISPLAY_MSG("Name - "<<(PCHAR)funcName->Name);
			}
			else
			{
				auto curOrd = PE::Import::GetOrdinal(curNameTable);
				DISPLAY_MSG("Ordinal - "<<curOrd);
			}
		}
		TO_LEFT;
	}
}

// pe解析器测试, 只做测试怎么简单怎么编
void TestPeDecoder()
{
	of.open(OUTPUT_FILENAME, ios::out| ios::trunc);

	DISPLAY_DES.setf(ios::left | ios::boolalpha);

	PE::PeDecoder pe;
	
	if (pe.LoadPEImage(GetModuleHandleA(NULL), true))
	{
		auto dosHeader = pe.DosHeader();
		DISPLAY_HEX("[Dos Header]", dosHeader);
		TO_RIGHT;
		PrintDosHeader(dosHeader);
		TO_LEFT;
		cout << endl;


		if (pe.HasNtHeader32())
		{
			auto ntHeader = pe.NtHeader32();
			//cout << "[Is 32 PE]" << endl;

			DISPLAY_HEX("[NtHeader 32]", ntHeader);
			TO_RIGHT;// ntheader
			PrintNtHeader32(ntHeader);
			TO_RIGHT; // FileHeader
			auto fileHeader = ntHeader->FileHeader;
			PrintFileHeader(&fileHeader);
			TO_LEFT;// end FileHeader
			DISPLAY_STRUCT_POINTER_HEX(ntHeader, OptionalHeader);
			auto optionalHeader = ntHeader->OptionalHeader;
			TO_RIGHT;// optionalHeader
			PrintOptionalHeader32(&optionalHeader);

			TO_RIGHT;// dataDirectory
			auto dataDirectory = optionalHeader.DataDirectory;
			PrintDataDirectory(dataDirectory, optionalHeader.NumberOfRvaAndSizes);
			TO_LEFT;// end dataDirectory


			TO_LEFT;// end optionalHeader

			TO_LEFT;// end ntheader

			cout << endl;

			// Section
			DISPLAY_MSG("[Section]");
			PrintSection(pe);
			cout << endl;
			// Export
			DISPLAY_MSG("[Export]");
			TO_RIGHT;
			PrintExport(pe);
			cout << endl;
			// Import
			// 导入表					
			DISPLAY_MSG("[Import]");
			TO_RIGHT;
			PrintImport(pe);
			TO_LEFT;

			cout << endl;
			// Resource
			// 资源目录
			DISPLAY_MSG("[Resource]");
			PrintResource(pe);

			// exception
			// TODO:exception directory
			// security
			// TODO:security

			cout << endl;
			// relocation
			// relocation
			DISPLAY_MSG("[BaseRelocation]");
			PrintReloc(pe);

			cout << endl;
			// debug
			// TODO:debug
			// architecture
			// TODO:architecture
			// reserved
			// TODO:reserved
			// tls
			// TODO:tls
			// config
			// TODO:config
			// bound import
			// TODO:bound import
			// iat
			// TODO: iat
			// delay import
			DISPLAY_MSG("[DelayImport]");
			PrintDelay(pe);
		
			// meta
			// TODO: meta


			TO_LEFT;
		}
		else
		{
			// 64位
			auto ntHeader = pe.NtHeader64();
			DISPLAY_HEX("[NtHeader 64]", ntHeader);
			TO_RIGHT;// ntheader
			PrintNtHeader64(ntHeader);
			TO_RIGHT; // FileHeader
			auto fileHeader = ntHeader->FileHeader;
			PrintFileHeader(&fileHeader);
			TO_LEFT;// end FileHeader
			DISPLAY_STRUCT_POINTER_HEX(ntHeader, OptionalHeader);
			auto optionalHeader = ntHeader->OptionalHeader;
			TO_RIGHT;// optionalHeader
			PrintOptionalHeader64(&optionalHeader);
			TO_RIGHT;// dataDirectory
			auto dataDirectory = optionalHeader.DataDirectory;
			PrintDataDirectory(dataDirectory, optionalHeader.NumberOfRvaAndSizes);
			TO_LEFT;// end dataDirectory
			TO_LEFT;// end optionalHeader
			TO_LEFT;// end ntheader
			cout << endl;
			// Section
			DISPLAY_MSG("[Section]");
			PrintSection(pe);
			cout << endl;
			// Export
			DISPLAY_MSG("[Export]");
			TO_RIGHT;
			PrintExport(pe);
			cout << endl;
			// Import
			// 导入表					
			DISPLAY_MSG("[Import]");
			TO_RIGHT;
			PrintImport64(pe);
			TO_LEFT;

			cout << endl;
			// Resource
			// 资源目录
			DISPLAY_MSG("[Resource]");
			PrintResource(pe); 
			TO_LEFT;
		}




	}
	else
	{
		cout << "Not a PE" << endl;
	}
	of.close();
	SHOW_FILE;
	Beep(261, 1000);
}
void TestLazyLoad()
{
using namespace Process::LazyLoad;
	/*LazyLoad::_LdrLoadDll(0, 0, 0, 0);
	if (!LazyLoad::_LoadLibraryA("aaa"))
	{
		cout << "FAILD" << endl;
	}
	if (!LazyLoad::_LoadLibraryA("bbb"))
	{
		cout << "FAILD" << endl;
	}*/
	//
	//LazyLoad::__LoadLibraryA("");
	//auto ii = NtCurrentTeb();



	/*auto x =_OpenProcess(PROCESS_ALL_ACCESS, FALSE, 12328);
	UINT8 buff[100]="HelloWorld!";
	DWORD size;
	auto k = _VirtualAllocEx(x, NULL, 100, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	_WriteProcessMemory(x, k, buff, 100, &size);
	UINT8 buff2[100];
	_ReadProcessMemory(x, k, buff2, 100, &size);
	auto dd = GetLastError();
	_MessageBoxA(0, "Hi", "HelloWorld!", 0);*/
}
LPCSTR hookSuccess = "成功";
int(WINAPI*realMboxAddr)(HWND, LPCSTR, LPCSTR, UINT);
int WINAPI HookMBoxIAT(HWND hwnd, LPCSTR text, LPCSTR caption, UINT type)
{
	cout << "IAT Hook - TEXT:" << text << " CAPTION:" << caption << endl;
	return realMboxAddr(hwnd, "IAT HOOK", hookSuccess, type);
}
int WINAPI HookMBoxEAT(HWND hwnd, LPCSTR text, LPCSTR caption, UINT type)
{
	cout << "EAT Hook - TEXT:" << text << " CAPTION:" << caption << endl;
	return realMboxAddr(hwnd, "EAT HOOK", hookSuccess, type);
}
#ifndef _WIN64
__declspec(naked) void HookAsm()
{
	_asm pushad
	cout << "内联汇编的hook函数" << endl;
	_asm
	{
		popad
		pop eax
		pop ebx
		pop ecx
		pop ecx
		push STRaddr
		push hookSuccess
		push ebx
		push eax
		jmp realMboxAddr
STRaddr:
		_emit 'H'
		_emit 'o'
		_emit 'o'
		_emit 'k'
		_emit 'e'
		_emit 'd'
		_emit 0

	}

}
#endif
int (WINAPI*oldShellMessageBoxA)(
	_In_opt_ HINSTANCE hAppInst,
	_In_opt_ HWND hWnd,
	_In_ LPCSTR lpcText,
	_In_opt_ LPCSTR lpcTitle,
	_In_ UINT fuStyle, ...);
int WINAPI HookShellMessageBoxA(
	_In_opt_ HINSTANCE hAppInst,
	_In_opt_ HWND hWnd,
	_In_ LPCSTR lpcText,
	_In_opt_ LPCSTR lpcTitle,
	_In_ UINT fuStyle, ...)
{
	cout << "延迟导入表Hook" << endl;
	
	return oldShellMessageBoxA(hAppInst, hWnd, "延迟导入表Hooked", hookSuccess, fuStyle);;
}
void TestHook()
{
	ShellMessageBoxW(0, 0, L"测试hook", L"hook", MB_ICONINFORMATION, "开始测试Hook,这个函数是延迟导入表导入的,好像用的是序数");
	realMboxAddr = (int(WINAPI*)(HWND, LPCSTR, LPCSTR, UINT))Process::LazyLoad::_GetProcAddressEx(L"user32.dll", "MessageBoxA");
	
	Process::Hook::HookIat("MessageBoxA", HookMBoxIAT);
	
	MessageBoxA(0, "hook", "hook", 0); // hooked 输出
	
	realMboxAddr(0, "iat hook不能影响这个", "realAddress", 0);

#ifndef _WIN64
	// 使用另一种hook函数
	Process::Hook::HookIat("MessageBoxA", HookAsm);
	MessageBoxA(0, "hook", "hook", 0); // hooked 输出
#endif

	Process::Hook::HookEat(L"user32.dll", "MessageBoxA", HookMBoxEAT);
	auto hookEatAddress = (int(WINAPI*)(HWND, LPCSTR, LPCSTR, UINT))GetProcAddress(LoadLibraryA("user32.dll"), "MessageBoxA"); // hookEat后取到的都是hook地址
	realMboxAddr(0, "eat hook不能影响这个", "realAddress", 0);
	hookEatAddress(0, "hook", "hook", 0); // hooked 输出



	Process::Hook::HookDelayLoad("SHLWAPI.dll", "ShellMessageBoxA", HookShellMessageBoxA, (PVOID*)&oldShellMessageBoxA);
	ShellMessageBoxA(0, 0, "测试 延迟载入 hook", "hook", MB_ICONINFORMATION);
	SHGetLocalizedName(NULL, NULL, NULL, NULL); // 用来扩展延迟导入表项的, 无视


}
CHAR* fasf = "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH";
typedef struct UUUF
{

	CHAR uuu;
	CHAR ff;
	
}GdA;// = { 'k',2 };
GdA k[] = { {'h'},{'u',3} };


int _tmain(int argc, _TCHAR* argv[])
{

	// 测试pe解析
	TestPeDecoder();
	// 测试延迟载入
	//TestLazyLoad();
	// 测试Hook
	///TestHook();
	return 0;
}
