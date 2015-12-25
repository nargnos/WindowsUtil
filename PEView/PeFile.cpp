#include "stdafx.h"
#include "PeFile.h"

namespace PEView
{
#define _ADD_TABLE(fieldName,structName,tableName)\
			tableName##->Add(\
			gcnew _PeData(#fieldName,\
			((INT_PTR)&structName##->##fieldName-(INT_PTR)peDecoder->GetBase()),\
			 sizeof(structName##->##fieldName),\
			 structName##->##fieldName))


#define _ADD_TABLE_ARRAY(fieldName,structName,tableName)\
			for (int i = 0; i < sizeof(structName##->##fieldName) / sizeof(structName##->##fieldName[0]); i++)\
			{\
				tableName##->Add(gcnew _PeData(#fieldName +"[" + i + "]",\
					((INT_PTR)&structName##->##fieldName[i] - (INT_PTR)peDecoder->GetBase()),\
					sizeof(structName##->##fieldName[i]),\
					structName##->##fieldName[i]));\
			}
	std::shared_ptr<PE::PeDecoder> peDecoder;
	List<_ExeInfo^>^ PeFile::GetExeInfoData()
	{
		auto result = gcnew List<_ExeInfo^>();
		result->Add(gcnew _ExeInfo("Path", exePath));
		result->Add(gcnew _ExeInfo("File Type", ""));
		result->Add(gcnew _ExeInfo("File Info", ""));
		result->Add(gcnew _ExeInfo("File Size", fileInfo->Length+" Byte"));
		result->Add(gcnew _ExeInfo("PE Size",""));
		
		result->Add(gcnew _ExeInfo("Created", fileInfo->CreationTime.ToString()));
		result->Add(gcnew _ExeInfo("Modified", fileInfo->LastWriteTime.ToString()));
		result->Add(gcnew _ExeInfo("Accessed", fileInfo->LastAccessTime.ToString()));

		
		result->Add(gcnew _ExeInfo("MD5", ""));// md5 需要用托管数组,打算做到插件里
		
		result->Add(gcnew _ExeInfo("SHA-1", ""));
		result->Add(gcnew _ExeInfo("Company Name", ""));
		result->Add(gcnew _ExeInfo("File Description", ""));
		result->Add(gcnew _ExeInfo("File Version", ""));
		result->Add(gcnew _ExeInfo("Internal Name", ""));
		result->Add(gcnew _ExeInfo("Original File Name", ""));
		result->Add(gcnew _ExeInfo("Product Name", ""));

		return result;
	}
	List<_PeData^>^ PeFile::GetDosHeaderData()
	{
		// FIX: 非ref的结构体类型不知道怎么反射字段名(用GetFields(Reflection::BindingFlags::NonPublic| Reflection::BindingFlags::Instance)反射不出结果),
		// 现在只能一个个填
		auto result = gcnew List<_PeData^>();
		auto tmpDosHeader = peDecoder->GetDosHeader()->GetValue();

		_ADD_TABLE(e_magic, tmpDosHeader, result);
		_ADD_TABLE(e_cblp, tmpDosHeader, result);
		_ADD_TABLE(e_cp, tmpDosHeader, result);
		_ADD_TABLE(e_crlc, tmpDosHeader, result);
		_ADD_TABLE(e_cparhdr, tmpDosHeader, result);
		_ADD_TABLE(e_minalloc, tmpDosHeader, result);
		_ADD_TABLE(e_maxalloc, tmpDosHeader, result);
		_ADD_TABLE(e_ss, tmpDosHeader, result);
		_ADD_TABLE(e_sp, tmpDosHeader, result);
		_ADD_TABLE(e_csum, tmpDosHeader, result);
		_ADD_TABLE(e_ip, tmpDosHeader, result);
		_ADD_TABLE(e_cs, tmpDosHeader, result);
		_ADD_TABLE(e_lfarlc, tmpDosHeader, result);
		_ADD_TABLE(e_ovno, tmpDosHeader, result);
		_ADD_TABLE_ARRAY(e_res, tmpDosHeader, result);
		_ADD_TABLE(e_oemid, tmpDosHeader, result);
		_ADD_TABLE(e_oeminfo, tmpDosHeader, result);
		_ADD_TABLE_ARRAY(e_res2, tmpDosHeader, result);
		_ADD_TABLE(e_lfanew, tmpDosHeader, result);

		return result;
	}
	List<_PeData^>^ PeFile::GetNtHeaderData()
	{
		auto tmpNtHeader = peDecoder->GetNtHeader()->GetNtHeader32();
		auto result = gcnew List<_PeData^>();
		_ADD_TABLE(Signature, tmpNtHeader, result);
		return result;
	}
	List<_PeData^>^ PeFile::GetFileHeaderData()
	{
		auto result = gcnew List<_PeData^>();
		PIMAGE_FILE_HEADER tmpFileHeader;
		if (peDecoder->HasNtHeader32())
		{
			tmpFileHeader = &peDecoder->GetNtHeader()->GetNtHeader32()->FileHeader;
		}
		else
		{
			tmpFileHeader = &peDecoder->GetNtHeader()->GetNtHeader64()->FileHeader;
		}
		_ADD_TABLE(Machine, tmpFileHeader, result);
		_ADD_TABLE(NumberOfSections, tmpFileHeader, result);
		_ADD_TABLE(TimeDateStamp, tmpFileHeader, result);
		_ADD_TABLE(PointerToSymbolTable, tmpFileHeader, result);
		_ADD_TABLE(NumberOfSymbols, tmpFileHeader, result);
		_ADD_TABLE(SizeOfOptionalHeader, tmpFileHeader, result);
		_ADD_TABLE(Characteristics, tmpFileHeader, result);
		return result;
	}
	List<_PeData^>^ PeFile::GetOptionalHeaderData()
	{
		auto result = gcnew List<_PeData^>();
		if (peDecoder->HasNtHeader32())
		{
			auto tmpOh = &peDecoder->GetNtHeader()->GetNtHeader32()->OptionalHeader;
			_ADD_TABLE(Magic, tmpOh, result);
			_ADD_TABLE(MajorLinkerVersion, tmpOh, result);
			_ADD_TABLE(MinorLinkerVersion, tmpOh, result);
			_ADD_TABLE(SizeOfCode, tmpOh, result);
			_ADD_TABLE(SizeOfInitializedData, tmpOh, result);
			_ADD_TABLE(SizeOfUninitializedData, tmpOh, result);
			_ADD_TABLE(AddressOfEntryPoint, tmpOh, result);
			_ADD_TABLE(BaseOfCode, tmpOh, result);
			_ADD_TABLE(BaseOfData, tmpOh, result);

			_ADD_TABLE(ImageBase, tmpOh, result);
			_ADD_TABLE(SectionAlignment, tmpOh, result);
			_ADD_TABLE(FileAlignment, tmpOh, result);
			_ADD_TABLE(MajorOperatingSystemVersion, tmpOh, result);
			_ADD_TABLE(MinorOperatingSystemVersion, tmpOh, result);
			_ADD_TABLE(MajorImageVersion, tmpOh, result);
			_ADD_TABLE(MinorImageVersion, tmpOh, result);
			_ADD_TABLE(MajorSubsystemVersion, tmpOh, result);
			_ADD_TABLE(MinorSubsystemVersion, tmpOh, result);
			_ADD_TABLE(Win32VersionValue, tmpOh, result);
			_ADD_TABLE(SizeOfImage, tmpOh, result);
			_ADD_TABLE(SizeOfHeaders, tmpOh, result);
			_ADD_TABLE(CheckSum, tmpOh, result);
			_ADD_TABLE(Subsystem, tmpOh, result);
			_ADD_TABLE(DllCharacteristics, tmpOh, result);
			_ADD_TABLE(SizeOfStackReserve, tmpOh, result);
			_ADD_TABLE(SizeOfStackCommit, tmpOh, result);
			_ADD_TABLE(SizeOfHeapReserve, tmpOh, result);
			_ADD_TABLE(SizeOfHeapCommit, tmpOh, result);
			_ADD_TABLE(LoaderFlags, tmpOh, result);
			_ADD_TABLE(NumberOfRvaAndSizes, tmpOh, result);
		}
		else
		{
			auto tmpOh = &peDecoder->GetNtHeader()->GetNtHeader64()->OptionalHeader;
			_ADD_TABLE(Magic, tmpOh, result);
			_ADD_TABLE(MajorLinkerVersion, tmpOh, result);
			_ADD_TABLE(MinorLinkerVersion, tmpOh, result);
			_ADD_TABLE(SizeOfCode, tmpOh, result);
			_ADD_TABLE(SizeOfInitializedData, tmpOh, result);
			_ADD_TABLE(SizeOfUninitializedData, tmpOh, result);
			_ADD_TABLE(AddressOfEntryPoint, tmpOh, result);
			_ADD_TABLE(BaseOfCode, tmpOh, result);
			_ADD_TABLE(ImageBase, tmpOh, result);
			_ADD_TABLE(SectionAlignment, tmpOh, result);
			_ADD_TABLE(FileAlignment, tmpOh, result);
			_ADD_TABLE(MajorOperatingSystemVersion, tmpOh, result);
			_ADD_TABLE(MinorOperatingSystemVersion, tmpOh, result);
			_ADD_TABLE(MajorImageVersion, tmpOh, result);
			_ADD_TABLE(MinorImageVersion, tmpOh, result);
			_ADD_TABLE(MajorSubsystemVersion, tmpOh, result);
			_ADD_TABLE(MinorSubsystemVersion, tmpOh, result);
			_ADD_TABLE(Win32VersionValue, tmpOh, result);
			_ADD_TABLE(SizeOfImage, tmpOh, result);
			_ADD_TABLE(SizeOfHeaders, tmpOh, result);
			_ADD_TABLE(CheckSum, tmpOh, result);
			_ADD_TABLE(Subsystem, tmpOh, result);
			_ADD_TABLE(DllCharacteristics, tmpOh, result);
			_ADD_TABLE(SizeOfStackReserve, tmpOh, result);
			_ADD_TABLE(SizeOfStackCommit, tmpOh, result);
			_ADD_TABLE(SizeOfHeapReserve, tmpOh, result);
			_ADD_TABLE(SizeOfHeapCommit, tmpOh, result);
			_ADD_TABLE(LoaderFlags, tmpOh, result);
			_ADD_TABLE(NumberOfRvaAndSizes, tmpOh, result);
		}
		return result;
	}
	String^ PeFile::GetDataDirectoriesFieldName(int index,bool isRvaAddress)
	{
		auto sb = gcnew System::Text::StringBuilder();
#define CASE_DIRECTORY_ENTRY(index) \
		case index:\
		sb->Append(#index);\
		break;
		sb->Append(isRvaAddress ? "[RVA]  " : "[Size] ");
		switch (index)
		{
			CASE_DIRECTORY_ENTRY(IMAGE_DIRECTORY_ENTRY_EXPORT);
			CASE_DIRECTORY_ENTRY(IMAGE_DIRECTORY_ENTRY_IMPORT);
			CASE_DIRECTORY_ENTRY(IMAGE_DIRECTORY_ENTRY_RESOURCE);
			CASE_DIRECTORY_ENTRY(IMAGE_DIRECTORY_ENTRY_EXCEPTION);
			CASE_DIRECTORY_ENTRY(IMAGE_DIRECTORY_ENTRY_SECURITY);
			CASE_DIRECTORY_ENTRY(IMAGE_DIRECTORY_ENTRY_BASERELOC);
			CASE_DIRECTORY_ENTRY(IMAGE_DIRECTORY_ENTRY_DEBUG);
			CASE_DIRECTORY_ENTRY(IMAGE_DIRECTORY_ENTRY_ARCHITECTURE);
			CASE_DIRECTORY_ENTRY(IMAGE_DIRECTORY_ENTRY_GLOBALPTR);
			CASE_DIRECTORY_ENTRY(IMAGE_DIRECTORY_ENTRY_TLS);
			CASE_DIRECTORY_ENTRY(IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG);
			CASE_DIRECTORY_ENTRY(IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT);
			CASE_DIRECTORY_ENTRY(IMAGE_DIRECTORY_ENTRY_IAT);
			CASE_DIRECTORY_ENTRY(IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT);
			CASE_DIRECTORY_ENTRY(IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR);
		default:
			break;
		}
		
		return sb->ToString();
	}
	List<_PeData^>^ PeFile::GetDataDirectoriesData()
	{
		auto result = gcnew List<_PeData^>();
		auto count = peDecoder->HasNtHeader32() ?
			peDecoder->GetNtHeader()->GetNtHeader32()->OptionalHeader.NumberOfRvaAndSizes :
			peDecoder->GetNtHeader()->GetNtHeader64()->OptionalHeader.NumberOfRvaAndSizes;
		for (int i = 0; i < count && i<= IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR; i++)
		{
			auto tmpDataDirectory = peDecoder->GetDataDirectory(i);
			if (!tmpDataDirectory)
			{
				continue;
			}
			auto tmpFiledName = GetDataDirectoriesFieldName(i, true);
			auto tmpOffset = (INT_PTR)&tmpDataDirectory->VirtualAddress - (INT_PTR)peDecoder->GetBase();
			auto tmpSize = sizeof(tmpDataDirectory->VirtualAddress);
			
			// rva
			auto tmpPeData = gcnew _PeData(tmpFiledName, tmpOffset, tmpSize,tmpDataDirectory->VirtualAddress);
			result->Add(tmpPeData);

			// size
			tmpFiledName = GetDataDirectoriesFieldName(i, false);
			tmpOffset = (INT_PTR)&tmpDataDirectory->Size - (INT_PTR)peDecoder->GetBase();
			tmpSize = sizeof(tmpDataDirectory->Size);
			tmpPeData = gcnew _PeData(tmpFiledName, tmpOffset, tmpSize, tmpDataDirectory->Size);

			result->Add(tmpPeData);
		}

		return result;
	}
	List<_SectionData^>^ PeFile::GetSectionData()
	{
		auto sr = peDecoder->GetSection()->CreateIterator();
		auto result = gcnew List<_SectionData^>();
		while (sr->Next())
		{
			result->Add(gcnew _SectionData(peDecoder->GetBase(), sr->Current()));
		}
		return result;
	}
	PeFile::PeFile()
	{
	}

	inline PeFile::~PeFile() { CloseFile(); }

	void PeFile::OpenFile(System::String ^ filePath,bool isReadOnly)
	{
		CloseFile();
		this->isReadOnly = isReadOnly;

		FileStream fs(filePath, FileMode::Open, isReadOnly ? FileAccess::Read : FileAccess::ReadWrite);

		auto mapObj = CreateFileMappingW(fs.Handle.ToPointer(), NULL, isReadOnly? PAGE_READONLY :PAGE_READWRITE, 0, fs.Length, NULL);
		if (mapObj)
		{
			pePtr = gcnew IntPtr(MapViewOfFile(mapObj, isReadOnly ? FILE_MAP_READ: FILE_MAP_ALL_ACCESS, 0, 0, fs.Length));
			CloseHandle(mapObj);
		}
		else
		{
			fs.Close();
			throw gcnew Exception("不能创建映射对象");
		}

		fileInfo = gcnew System::IO::FileInfo(filePath);
		mapSize = fs.Length;
		fs.Close();

		if (pePtr)
		{
			if (!peDecoder)
			{
				peDecoder = std::make_shared<PE::PeDecoder>();
			}
			
			if (!peDecoder->LoadPEImage(pePtr->ToPointer(), false))
			{
				// 载入失败
				UnmapViewOfFile(pePtr->ToPointer());
				pePtr = IntPtr::Zero;
				throw gcnew Exception("不能以PE结构载入此文件");
			}

		}
		else
		{
			throw gcnew Exception("不能映射文件");
		}
		exePath = filePath;
		Opened();
	}
	void PeFile::CloseFile()
	{
		if (pePtr)
		{
			UnmapViewOfFile(pePtr->ToPointer());
			pePtr = IntPtr::Zero;
		}
		exePath = String::Empty;
		Closed();
		Reset();
	}
}