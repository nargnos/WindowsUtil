#pragma once
#include "..\..\stdafx.h"
#include <PE\Import\Import.h>
namespace NAMESPACE {
	namespace PeDecoderWrapper
	{
		ref class PeImage;
		// 函数名称
		[TypeConverter(ShowPropertiesConverter::typeid)]
		public ref class ImportThunkWrapper :
			public PeStructDescription,
			public IElementName,
			public IPropertiesFilter
		{
			static array<String^>^ sortList;
			PVOID originalThunk;
			PVOID thunk;
			PeImage ^ pe;
			IntPtr GetBase()
			{
				return pe->BaseAddress;
			}
			bool is32;
			PIMAGE_IMPORT_BY_NAME GetNameStruct()
			{
				if (is32)
				{
					auto ot = reinterpret_cast<PIMAGE_THUNK_DATA32>(originalThunk);
					if (PE::IsSnapByOrdinal(ot))
					{
						return nullptr;
					}
					return PE::GetNameStruct(pe->GetPeDecoder(), ot);
				}
				else
				{
					auto ot = reinterpret_cast<PIMAGE_THUNK_DATA64>(originalThunk);
					if (PE::IsSnapByOrdinal(ot))
					{
						return nullptr;
					}
					return PE::GetNameStruct(pe->GetPeDecoder(), ot);
				}
				return nullptr;
			}
		public:
			virtual array<String^>^ GetSortList() override
			{
				if (ImportThunkWrapper::sortList == nullptr)
				{
					ImportThunkWrapper::sortList = gcnew array<String^>
					{
						"Name",
							"Hint",
							"Ordinal32",
							"Ordinal64",
							"OriginalThunk32",
							"Thunk32",
							"OriginalThunk64",
							"Thunk64",
					};
				}
				return ImportThunkWrapper::sortList;
			}
			virtual List<String^>^ GetHidePropList()
			{
				auto result = gcnew List<String^>;
				if (!OriginalThunk32)
				{
					result->Add("OriginalThunk32");
				}
				if (!Thunk32)
				{
					result->Add("Thunk32");
				}
				if (!Ordinal32)
				{
					result->Add("Ordinal32");
				}
				if (!OriginalThunk64)
				{
					result->Add("OriginalThunk64");
				}
				if (!Thunk64)
				{
					result->Add("Thunk64");
				}
				if (!Ordinal64)
				{
					result->Add("Ordinal64");
				}
				if (!Hint)
				{
					result->Add("Hint");
				}
				if (!Name)
				{
					result->Add("Name");
				}
				return result;
			}
			virtual String ^ GetName()
			{
				auto name = Name;
				if (name != nullptr)
				{
					return name->String;
				}
				else
				{
					return is32 ? Ordinal32.ToString() : Ordinal64.ToString();
				}
			}

			ImportThunkWrapper(PIMAGE_THUNK_DATA32 othunk, PIMAGE_THUNK_DATA32 thunk, PeImage ^ pe)
				:originalThunk(othunk), thunk(thunk), pe(pe)
			{
				is32 = pe->HasNtHeader32;
			}
			ImportThunkWrapper(PIMAGE_THUNK_DATA64 othunk, PIMAGE_THUNK_DATA64 thunk, PeImage ^ pe)
				: originalThunk(othunk), thunk(thunk), pe(pe)
			{
				is32 = !pe->HasNtHeader32;
			}
			
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
		public ref class ImportThunkArrayWrapper :
			public IWrapperArray,
			public PeStructDescription
		{
			
			List<IElementName^>^ list;
			void InitArrayList()
			{
				list = gcnew List<IElementName^>();
				auto thunk = new PE::ImportThunkIterator(descriptor, pe->GetPeDecoder());
				if (pe->HasNtHeader32)
				{
					while (thunk->Next())
					{
						list->Add(gcnew ImportThunkWrapper(thunk->CurrentOriginalThunk32(), thunk->CurrentThunk32(), pe));
					}
				}
				else
				{
					while (thunk->Next())
					{
						list->Add(gcnew ImportThunkWrapper(thunk->CurrentOriginalThunk64(), thunk->CurrentThunk64(), pe));
					}
				}
			}
			PIMAGE_IMPORT_DESCRIPTOR descriptor;
			PeImage^ pe;
		public:
			ImportThunkArrayWrapper(PIMAGE_IMPORT_DESCRIPTOR descriptor, PeImage^ pe) :descriptor(descriptor), pe(pe)
			{
				this->SetDescription(IntPtr(descriptor), pe->BaseAddress, GetElements()->Count);
			}
			virtual System::Collections::Generic::IList<IElementName^>^ ImportThunkArrayWrapper::GetElements() override
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
			virtual array<String^>^ GetSortList() override
			{
				return nullptr;
			}
		};

		// dll名称
		[TypeConverter(ShowPropertiesConverter::typeid)]
		public ref class ImportDescriptorWrapper :
			public PeStructDescription,
			public IElementName
		{
			static array<String^>^ sortList;
			PeImage ^ pe;

			PIMAGE_IMPORT_DESCRIPTOR GetPointer()
			{
				return (PIMAGE_IMPORT_DESCRIPTOR)addr.ToPointer();
			}
			PE::PeDecoder* GetPeDecoder()
			{
				return pe->GetPeDecoder();
			}
		public:
			virtual String ^ GetName()
			{
				return Name->String;
			}
			virtual array<String^>^ GetSortList() override
			{
				if (ImportDescriptorWrapper::sortList == nullptr)
				{
					ImportDescriptorWrapper::sortList = gcnew array<String^>
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
				return ImportDescriptorWrapper::sortList;
			}

			ImportDescriptorWrapper(IntPtr addr, PeImage^ pe) :pe(pe)
			{
				SetDescription(addr, pe->BaseAddress, 0);
			}

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
			property ImportThunkArrayWrapper^ Functions
			{
				ImportThunkArrayWrapper^ get()
				{
					return gcnew ImportThunkArrayWrapper(GetPointer(), pe);
				}
			}
			
		};


		// dll名称
		[TypeConverter(PeStructArrayConverter::typeid)]
		public ref class ImportDescriptorArrayWrapper :
			public PeStructWrapper<PE::PeDecoder::LazyInstance<PE::ImportDirectory>>,
			public IWrapperArray
		{
			List<IElementName^>^ list;
			void InitArrayList()
			{
				list = gcnew List<IElementName^>();
				auto it = GetUnmanagedStruct()->CreateIterator();

				while (it->Next())
				{
					list->Add(gcnew ImportDescriptorWrapper(IntPtr(it->Current()), pe));
				}
			}
		public:
			ImportDescriptorArrayWrapper(PeImage^ pe) :PeStructWrapperBase(pe)
			{
				this->SetDescription(IntPtr(GetUnmanagedStruct()->DirectoryEntryToData()), pe->BaseAddress, 0);
			}


			virtual array<String^>^ GetSortList() override
			{
				return nullptr;
			}
			virtual PeStructWrapperType & GetUnmanagedStruct() override
			{
				return pe->GetPeDecoder()->GetImport;
			}
			virtual System::Collections::Generic::IList<IElementName^>^ GetElements()
			{
				if (list == nullptr)
				{
					InitArrayList();
				}
				return list;
			}

		};
	}
}