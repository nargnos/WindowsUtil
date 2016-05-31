#pragma once
#include "PeStructDescription.h"
#include "UnmanagedValue.h"
namespace PeImageClr
{
	[TypeConverter(ShowPropertiesConverter::typeid)]
	public ref class DataDirectoryWrapper :
		public PeStructDescription
	{
		static array<String^>^ sortList;
	public:
		DataDirectoryWrapper(IntPtr addr, IntPtr basePtr);
		~DataDirectoryWrapper();

		virtual array<String^>^ GetSortList() override;
		property UnmanagedValue<DWORD>^ Size
		{
			UnmanagedValue<DWORD>^ get()
			{
				if (addr == IntPtr::Zero)
				{
					return nullptr;
				}
				return gcnew UnmanagedValue<DWORD>(IntPtr(&((PIMAGE_DATA_DIRECTORY)addr.ToPointer())->Size), base);
			}
		}
		property UnmanagedValue<DWORD>^ VirtualAddress
		{
			UnmanagedValue<DWORD>^ get()
			{
				if (addr == IntPtr::Zero)
				{
					return nullptr;
				}
				return gcnew UnmanagedValue<DWORD>(IntPtr(&((PIMAGE_DATA_DIRECTORY)addr.ToPointer())->VirtualAddress), base);
			}
		}
	};
}  // namespace PeImageClr
