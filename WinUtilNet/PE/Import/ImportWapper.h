#pragma once
#include "..\..\stdafx.h"
#include <PE\Import\Import.h>
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		ref class PeImage;
		// 函数名称
		[TypeConverter(ShowPropertiesConverter::typeid)]
		public ref class ImportThunkWapper :
			public PeStructDescription,
			public IElementName,
			public IPropertiesFilter
		{
			static array<String^>^ sortList;
			PVOID originalThunk;
			PVOID thunk;
			PeImage ^ pe;
			IntPtr GetBase();
			bool is32;
			PIMAGE_IMPORT_BY_NAME GetNameStruct();
		public:
			virtual array<String^>^ GetSortList() override;
			virtual List<String^>^ GetHidePropList();
			virtual String ^ GetName();

			ImportThunkWapper(PIMAGE_THUNK_DATA32 othunk, PIMAGE_THUNK_DATA32 thunk, PeImage ^ pe);
			ImportThunkWapper(PIMAGE_THUNK_DATA64 othunk, PIMAGE_THUNK_DATA64 thunk, PeImage ^ pe);
			
			property UnmanagedValue<DWORD>^   Thunk32
			{
				UnmanagedValue<DWORD>^ get()
				{
					if (!is32)
					{
						return nullptr;
					}
					return gcnew UnmanagedValue<DWORD>(IntPtr(thunk), GetBase());
				}
			}
			
			property UnmanagedValue<ULONGLONG>^   Thunk64
			{
				UnmanagedValue<ULONGLONG>^ get()
				{
					if (is32)
					{
						return nullptr;
					}
					return gcnew UnmanagedValue<ULONGLONG>(IntPtr(thunk), GetBase());
				}
			}

			
			property UnmanagedValue<DWORD>^   OriginalThunk32
			{
				UnmanagedValue<DWORD>^ get()
				{
					if (!is32)
					{
						return nullptr;
					}
					return gcnew UnmanagedValue<DWORD>(IntPtr(originalThunk), GetBase());
				}
			}
			
			property UnmanagedValue<ULONGLONG>^   OriginalThunk64
			{
				UnmanagedValue<ULONGLONG>^ get()
				{
					if (is32)
					{
						return nullptr;
					}
					return gcnew UnmanagedValue<ULONGLONG>(IntPtr(originalThunk), GetBase());
				}
			}

			[TypeConverter(ValueConverter::typeid)]
			property DWORD   Ordinal32
			{
				DWORD get()
				{
					auto ot = reinterpret_cast<PIMAGE_THUNK_DATA32>(originalThunk);
					if (!is32 || !PE::IsSnapByOrdinal(ot))
					{
						return 0;
					}
					return PE::GetOrdinal(ot);
				}
			}

			[TypeConverter(ValueConverter::typeid)]
			property ULONGLONG   Ordinal64
			{
				ULONGLONG get()
				{
					auto ot = reinterpret_cast<PIMAGE_THUNK_DATA64>(originalThunk);
					if (is32 || !PE::IsSnapByOrdinal(ot))
					{
						return 0;
					}
					return PE::GetOrdinal(ot);
				}
			}


			property UnmanagedValue<WORD>^   Hint
			{
				UnmanagedValue<WORD>^ get()
				{
					auto result = GetNameStruct();
					if (!result)
					{
						return nullptr;
					}
					return gcnew UnmanagedValue<WORD>(IntPtr(&result->Hint), GetBase());
				}
			}
			property UnmanagedString^   Name
			{
				UnmanagedString^ get()
				{
					auto result = GetNameStruct();
					if (!result)
					{
						return nullptr;
					}
					return gcnew UnmanagedString(IntPtr(result->Name), GetBase(), 0);
				}
			}

			
		};
		// 存储函数名称
		[TypeConverter(PeStructArrayConverter::typeid)]
		public ref class ImportThunkArrayWapper :
			public IWapperArray,
			public PeStructDescription
		{
			
			List<IElementName^>^ list;
			void InitArrayList();
			PIMAGE_IMPORT_DESCRIPTOR descriptor;
			PeImage^ pe;
		public:
			ImportThunkArrayWapper(PIMAGE_IMPORT_DESCRIPTOR descriptor, PeImage^ pe);
			virtual System::Collections::Generic::IList<IElementName^>^ ImportThunkArrayWapper::GetElements() override;
			virtual String ^ GetDescription() override;
			virtual array<String^>^ GetSortList() override;
		};

		// dll名称
		[TypeConverter(ShowPropertiesConverter::typeid)]
		public ref class ImportDescriptorWapper :
			public PeStructDescription,
			public IElementName
		{
			static array<String^>^ sortList;
			PeImage ^ pe;

			PIMAGE_IMPORT_DESCRIPTOR GetPointer();
			PE::PeDecoder* GetPeDecoder();
		public:
			virtual String ^ GetName();
			virtual array<String^>^ GetSortList() override;

			ImportDescriptorWapper(IntPtr addr, PeImage^ pe);

			property UnmanagedString^   Name
			{
				UnmanagedString^ get()
				{
					return gcnew UnmanagedString(IntPtr(PE::GetDescriptorName(GetPeDecoder(), GetPointer())), base, 0);
				}
			}
			property UnmanagedValue<DWORD>^   OriginalFirstThunk
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetPointer()->OriginalFirstThunk), base);
				}
			}
			property UnmanagedDateTimeValue<DWORD>^   TimeDateStamp
			{
				UnmanagedDateTimeValue<DWORD>^ get()
				{
					return gcnew UnmanagedDateTimeValue<DWORD>(IntPtr(&GetPointer()->TimeDateStamp), base);
				}
			}
			property UnmanagedValue<DWORD>^   ForwarderChain
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetPointer()->ForwarderChain), base);
				}
			}
			property UnmanagedValue<DWORD>^   NameRVA
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetPointer()->Name), base);
				}
			}
			property UnmanagedValue<DWORD>^   FirstThunk
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetPointer()->FirstThunk), base);
				}
			}
			property ImportThunkArrayWapper^ Functions
			{
				ImportThunkArrayWapper^ get()
				{
					return gcnew ImportThunkArrayWapper(GetPointer(), pe);
				}
			}
			
		};


		// dll名称
		[TypeConverter(PeStructArrayConverter::typeid)]
		public ref class ImportDescriptorArrayWapper :
			public PeStructWapper<PE::PeDecoder::LazyInstance<PE::ImportDirectory>>,
			public IWapperArray
		{
			List<IElementName^>^ list;
			void InitArrayList();
		public:
			ImportDescriptorArrayWapper(PeImage^ pe);


			virtual array<String^>^ GetSortList() override;
			virtual PeStructWapperType & GetUnmanagedStruct() override;
			virtual System::Collections::Generic::IList<IElementName^>^ GetElements();

		};
	}
}