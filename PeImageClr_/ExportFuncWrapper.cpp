#include "stdafx.h"
#include "ExportFuncWrapper.h"
#include "PeImage.h"
namespace PeImageClr
{
	 void ExportFuncWrapper::AddName(ExportNameWrapper ^ name)
	{
		if (names == nullptr)
		{
			names = gcnew List<ExportNameWrapper^>();
		}
		names->Add(name);
	}
	 String ^ ExportFuncWrapper::GetName()
	{
		if (Name)
		{
			return Name->String;
		}
		auto names = Names;
		if (names != nullptr)
		{
			return names->GetDescription();
		}
		return Ordinal.ToString();
	}
	 array<String^>^ ExportFuncWrapper::GetSortList()
	{
		if (ExportFuncWrapper::sortList == nullptr)
		{
			ExportFuncWrapper::sortList = gcnew array<String^>
			{
				"Ordinal",
					"FuncRVA",
					"NameOrdinal",
					"NameRVA",
					"Name",
					"Names",
			};
		}
		return ExportFuncWrapper::sortList;
	}
	 List<String^>^ ExportFuncWrapper::GetHidePropList()
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
	 ExportFuncWrapper::ExportFuncWrapper(int index, IntPtr addr, PeImage ^ pe)
		:pe(pe), index(index)
	{
		this->SetDescription(addr, pe->BaseAddress, 0);
	}
	 String ^ ExportFuncWrapper::GetDescription()
	{
		if (addr == IntPtr::Zero)
		{
			return String::Empty;
		}
		return String::Format("[{0:X8}]", FuncRVA->Value);
	}
}  // namespace PeImageClr
