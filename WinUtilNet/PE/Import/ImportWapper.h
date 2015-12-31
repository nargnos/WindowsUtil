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
			// 通过 PeStructDescription 继承
			virtual array<String^>^ GetSortList() override;

			// 通过 IElementName 继承
			virtual String ^ GetName();

			ImportThunkWapper(PIMAGE_THUNK_DATA32 othunk, PIMAGE_THUNK_DATA32 thunk, PeImage ^ pe);
			ImportThunkWapper(PIMAGE_THUNK_DATA64 othunk, PIMAGE_THUNK_DATA64 thunk, PeImage ^ pe);
			[DescriptionAttribute("Thunk")]
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
			[DescriptionAttribute("Thunk")]
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

			[DescriptionAttribute("Original Thunk")]
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
			[DescriptionAttribute("Original Thunk")]
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

			[DescriptionAttribute("Ordinal")]
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

			[DescriptionAttribute("Ordinal")]
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


			// 通过 IPropertiesFilter 继承
			virtual List<String^>^ GetHidePropList();

		};
		// 存储函数名称
		[TypeConverter(PeStructArrayConverter::typeid)]
		public ref class ImportThunkArrayWapper :
			public IWapperArray,
			public PeStructDescription
		{
			
			List<Object^>^ list;
			void InitArrayList();
			PIMAGE_IMPORT_DESCRIPTOR descriptor;
			PeImage^ pe;
		public:
			ImportThunkArrayWapper(PIMAGE_IMPORT_DESCRIPTOR descriptor, PeImage^ pe);
			virtual System::Collections::Generic::IList<Object^>^ ImportThunkArrayWapper::GetElements() override
			{
				if (list == nullptr)
				{
					InitArrayList();
				}
				return list;
			}
			virtual String ^ GetDescription() override
			{
				if (addr == IntPtr::Zero)
				{
					return String::Empty;
				}
				auto offset = Offset.ToString("X" + 2 * IntPtr::Size);
				if (structSize == 0)
				{
					return String::Format("[{0}]", offset);
				}
				return String::Format("[{0} (Count: {1})]", offset, structSize);
			}
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

			PIMAGE_IMPORT_DESCRIPTOR GetPointer()
			{
				return (PIMAGE_IMPORT_DESCRIPTOR)addr.ToPointer();
			}
			PE::PeDecoder* GetPeDecoder();
		public:
			virtual array<String^>^ GetSortList() override
			{
				if (ImportDescriptorWapper::sortList == nullptr)
				{
					ImportDescriptorWapper::sortList = gcnew array<String^>
					{
						"Name",
							"OriginalFirstThunk",
							"TimeDateStamp",
							"ForwarderChain",
							"NameRVA",
							"FirstThunk",
							"Functions"
					};
				}
				return ImportDescriptorWapper::sortList;
			}

			ImportDescriptorWapper(IntPtr addr, PeImage^ pe);

			property UnmanagedString^   Name
			{
				UnmanagedString^ get()
				{
					return gcnew UnmanagedString(IntPtr(PE::GetDescriptorName(*GetPeDecoder(), GetPointer())), base, 0);
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
			


			virtual String ^ GetName();

		};


		// dll名称
		[TypeConverter(PeStructArrayConverter::typeid)]
		public ref class ImportDescriptorArrayWapper :
			public PeStructWapper<PE::PeDecoder::PeStructInstance<PE::ImportDirectory>>,
			public IWapperArray
		{
			List<Object^>^ list;
			void InitArrayList()
			{
				list = gcnew List<Object^>();
				auto it = GetUnmanagedStruct()->CreateIterator();

				while (it->Next())
				{
					list->Add(gcnew ImportDescriptorWapper(IntPtr(it->Current()), pe));
				}
			}
		public:
			ImportDescriptorArrayWapper(PeImage^ pe);


			virtual array<String^>^ GetSortList() override
			{
				return nullptr;
			}
			virtual PeStructWapperType & GetUnmanagedStruct() override;
			virtual System::Collections::Generic::IList<Object^>^ GetElements();

		};
	}
}