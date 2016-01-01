#include "..\..\stdafx.h"
#include "ExportWapper.h"
#include "..\PeImage.h"
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		inline array<String^>^ ExportWapper::GetSortList()
		{
			if (ExportWapper::sortList == nullptr)
			{
				ExportWapper::sortList = gcnew array<String^>
				{
					"Characteristics",
						"TimeDateStamp",
						"MajorVersion",
						"MinorVersion",
						"Name",
						"Base",
						"NumberOfFunctions",
						"NumberOfNames",
						"AddressOfFunctions",
						"AddressOfNames",
						"AddressOfNameOrdinals",
						"Functions"
				};
			}
			return ExportWapper::sortList;
		}
		inline ExportWapper::PeStructWapperType & ExportWapper::GetUnmanagedStruct()
		{
			return pe->GetPeDecoder()->GetExport;
		}
		inline ExportWapper::ExportWapper(PeImage ^ pe) :PeStructWapperBase(pe)
		{
			SetDescription(IntPtr(GetUnmanagedStruct()->GetValue()), GetPeBase(), sizeof(IMAGE_EXPORT_DIRECTORY));

		}
		inline void ExportFuncArrayWapper::InitArrayList()
		{
			list = gcnew System::Collections::Generic::List<IElementName^>();
			
			// 读func 取index和值，带有name list和name
			// 读name ord，取到下标func的list或name写值
			 //添加 ExportFuncWapper 加完了要再设置ord
			auto funcTable = GetUnmanagedStruct()->FuncTable();
			auto numberOfFunctions = *GetUnmanagedStruct()->NumberOfFunctions();
			for (int i = 0; i < numberOfFunctions; i++)
			{
				list->Add(gcnew ExportFuncWapper(i, IntPtr(&funcTable[i]), pe));
			}
			auto numberOfNames = *GetUnmanagedStruct()->NumberOfNames();
			auto nameTable = GetUnmanagedStruct()->NameTable();;
			auto nameOrdinalTable = GetUnmanagedStruct()->OrdinalTable();
			for (int i = 0; i < numberOfNames; i++)
			{
				auto tmpNameRva = &nameTable[i];
				auto tmpOrdinal = &nameOrdinalTable[i];
				auto tmpFunc = safe_cast<ExportFuncWapper^>(list[*tmpOrdinal]);
				tmpFunc->AddName(gcnew ExportNameWapper(IntPtr(tmpNameRva),IntPtr(tmpOrdinal),  pe));
			}

			
		}
		inline ExportFuncArrayWapper::PeStructWapperType & ExportFuncArrayWapper::GetUnmanagedStruct()
		{
			return pe->GetPeDecoder()->GetExport;
		}
		inline ExportFuncArrayWapper::ExportFuncArrayWapper(PeImage ^ pe) :PeStructWapperBase(pe)
		{
			SetDescription(IntPtr::Zero, pe->BaseAddress, 0);
		}
		System::Collections::Generic::IList<IElementName^>^ ExportFuncArrayWapper::GetElements()
		{
			if (list == nullptr)
			{
				InitArrayList();
			}
			return list;
		}
		array<String^>^ ExportFuncArrayWapper::GetSortList()
		{
			return nullptr;
		}
		inline ExportFuncWapper::ExportFuncWapper(int index, IntPtr addr, PeImage ^ pe)
			:pe(pe), index(index)
		{
			this->SetDescription(addr, pe->BaseAddress, 0);
		}
		String ^ ExportFuncWapper::GetName()
		{
			if (Name)
			{
				return Name->String;
			}
			auto names = Names;
			if (names!=nullptr)
			{
				return names->GetDescription();
			}
			return Ordinal.ToString();
		}

		inline array<String^>^ ExportFuncWapper::GetSortList()
		{
			if (ExportFuncWapper::sortList == nullptr)
			{
				ExportFuncWapper::sortList = gcnew array<String^>
				{
					"Ordinal",
						"FuncRVA",
						"NameOrdinal",
						"NameRVA",
						"Name",
						"Names",
				};
			}
			return ExportFuncWapper::sortList;
		}

		inline List<String^>^ ExportFuncWapper::GetHidePropList()
		{
			auto result = gcnew List<String^>;
			if (!Names)
			{
				result->Add("Names");
			}

			if (!Name)
			{
				result->Add("Name");
				result->Add("NameOrdinal");
				result->Add("NameRVA");
			}
			return result;
		}

		inline void ExportFuncWapper::AddName(ExportNameWapper ^ name)
		{
			if (names == nullptr)
			{
				names = gcnew List<ExportNameWapper^>();
			}
			names->Add(name);
		}
	
		inline ExportNameArrayWapper::ExportNameArrayWapper(List<ExportNameWapper^>^ nameWappers)
		{
			// 不支持协变只能转换了
			names = gcnew List<IElementName^>();
			for each (auto var in nameWappers)
			{
				names->Add(var);
			}
		}

		System::Collections::Generic::IList<IElementName^>^ ExportNameArrayWapper::GetElements()
		{
			return names;
		}
		array<String^>^ ExportNameArrayWapper::GetSortList()
		{
			return nullptr;
		}
		inline PVOID ExportNameWapper::GetNamePtr()
		{
			return pe->GetPeDecoder()->GetRvaData(*(PDWORD)nameRva.ToPointer());
		}
		inline ExportNameWapper::ExportNameWapper(IntPtr nameRva, IntPtr nameOrdinal, PeImage ^ pe)
			:nameRva(nameRva), nameOrdinal(nameOrdinal),pe(pe)
		{
			SetDescription(nameRva, pe->BaseAddress, 0);
		}

		// 通过 IElementName 继承

		inline String ^ ExportNameWapper::GetName() {
			return Name->String;
		}
		array<String^>^ ExportNameWapper::GetSortList()
		{
			return nullptr;
		}
	}
}