#pragma once
#include <Windows.h>
#include <WinBase.h>
#include "PeStructWrapper.h"
#include "UnmanagedValue.h"
#include "UnmanagedEnum.h"
#include "MachineType.h"
#include "UnmanagedDateTimeValue.h"
#include "CharacteristicsType.h"
namespace PeImageClr
{
	using namespace System::ComponentModel;

	// FIX: 直接这样取值拿不到偏移地址, 想到方法了再替换，如果用取得头指针再自己计算偏移需要人工成本太大
	// 
	/*[StructLayout(LayoutKind::Sequential, Size = sizeof(IMAGE_FILE_HEADER))]
	public value struct FileHeader
	{
	MachineType    Machine;
	WORD    NumberOfSections;
	DWORD   TimeDateStamp;
	DWORD   PointerToSymbolTable;
	DWORD   NumberOfSymbols;
	WORD    SizeOfOptionalHeader;
	CharacteristicsType    Characteristics;
	};*/

	[TypeConverter(ShowPropertiesConverter::typeid)]
	public ref class FileHeaderWrapper :
		public PeStructWrapper<IMAGE_FILE_HEADER>
	{
		static array<String^>^ sortList;

	internal:
		// 通过 PeStructWrapper 继承
		virtual PeStructWrapperType & GetUnmanagedStruct() override;

	public:

		FileHeaderWrapper(PeImage^ pe);
		virtual array<String^>^ GetSortList() override;
		property UnmanagedEnum<MachineType>^ Machine
		{
			UnmanagedEnum<MachineType>^ get()
			{
				return gcnew UnmanagedEnum<MachineType>(IntPtr(&GetUnmanagedStruct().Machine), GetPeBase());
			}
		};

		property UnmanagedValue<WORD>^    NumberOfSections
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().NumberOfSections), GetPeBase());
			}
		};
		property UnmanagedDateTimeValue<DWORD>^   TimeDateStamp
		{
			UnmanagedDateTimeValue<DWORD>^ get()
			{
				return gcnew UnmanagedDateTimeValue<DWORD>(IntPtr(&GetUnmanagedStruct().TimeDateStamp), GetPeBase());
			}
		};
		property UnmanagedValue<DWORD>^   PointerToSymbolTable
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().PointerToSymbolTable), GetPeBase());
			}
		};
		property UnmanagedValue<DWORD>^   NumberOfSymbols
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().NumberOfSymbols), GetPeBase());
			}
		};
		property UnmanagedValue<WORD>^    SizeOfOptionalHeader
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().SizeOfOptionalHeader), GetPeBase());
			}
		};


		property UnmanagedEnum<CharacteristicsType>^ Characteristics
		{
			UnmanagedEnum<CharacteristicsType>^ get()
			{
				return gcnew UnmanagedEnum<CharacteristicsType>(IntPtr(&GetUnmanagedStruct().Characteristics), GetPeBase());
			}
		};
	};
}  // namespace PeImageClr
