#pragma once
#include "IElementName.h"
#include "PeStructDescription.h"
#include "IPropertiesFilter.h"
#include "UnmanagedValue.h"
#include "UnmanagedString.h"
#include "ExportNameArrayWrapper.h"
#include "ExportNameWrapper.h"
namespace PeImageClr
{
	ref class ExportNameWrapper;
	ref class PeImage;
	// 导出表函数，因为存在多个名字同时指向一个函数地址的情况，所以包含导出表函数名或函数名数组
	public ref class ExportFuncWrapper :
		public IElementName,
		public PeStructDescription,
		public IPropertiesFilter
	{
		PeImage^ pe;
		int index;
		List<ExportNameWrapper^>^ names;
		static array<String^>^ sortList;
	internal:
		void AddName(ExportNameWrapper^ name);
	public:
		virtual String ^ GetName() override;
		virtual array<String^>^ GetSortList() override;
		virtual List<String^>^ GetHidePropList() override;
		ExportFuncWrapper(int index, IntPtr addr, PeImage^ pe);
		virtual String ^ GetDescription() override;
#pragma region 属性
		property int Ordinal
		{
			int get()
			{
				return index;
			}
		}
		[DescriptionAttribute("Function RVA")]
		property UnmanagedValue<DWORD>^ FuncRVA
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(addr, base);
			}
		}


		property UnmanagedValue<DWORD>^ NameRVA
		{
			UnmanagedValue<DWORD>^ get()
			{
				if (names == nullptr)
				{
					return nullptr;
				}
				if (names->Count != 1)
				{
					return nullptr;
				}
				return names[0]->NameRVA;
			}
		}
		property UnmanagedValue<WORD>^ NameOrdinal
		{
			UnmanagedValue<WORD>^ get()
			{
				if (names == nullptr)
				{
					return nullptr;
				}
				if (names->Count != 1)
				{
					return nullptr;
				}
				return names[0]->NameOrdinal;
			}
		}
		property UnmanagedString^ Name
		{
			UnmanagedString^ get()
			{
				if (names == nullptr)
				{
					return nullptr;
				}
				if (names->Count != 1)
				{
					return nullptr;
				}
				return names[0]->Name;//
			}
		}
		property ExportNameArrayWrapper^ Names
		{
			ExportNameArrayWrapper^ get()
			{
				if (names == nullptr)
				{
					return nullptr;
				}
				if (names->Count == 1)
				{
					return nullptr;
				}
				return gcnew ExportNameArrayWrapper(names);
			}
		}
#pragma endregion
	};

}  // namespace PeImageClr
