#pragma once
namespace NAMESPACE {
	namespace PeDecoderWrapper
	{
		using namespace System::Collections::Generic;
		[FlagsAttribute]
		[EditorAttribute(FlagsEditor<SectionCharacteristics>::typeid, UITypeEditor::typeid)]
		public enum class SectionCharacteristics :DWORD
		{
			TYPE_NO_PAD = IMAGE_SCN_TYPE_NO_PAD,
			CNT_CODE = IMAGE_SCN_CNT_CODE,
			CNT_INITIALIZED_DATA = IMAGE_SCN_CNT_INITIALIZED_DATA,
			CNT_UNINITIALIZED_DATA = IMAGE_SCN_CNT_UNINITIALIZED_DATA,
			LNK_OTHER = IMAGE_SCN_LNK_OTHER,
			LNK_INFO = IMAGE_SCN_LNK_INFO,
			LNK_REMOVE = IMAGE_SCN_LNK_REMOVE,
			LNK_COMDAT = IMAGE_SCN_LNK_COMDAT,
			NO_DEFER_SPEC_EXC = IMAGE_SCN_NO_DEFER_SPEC_EXC,
			GPREL = IMAGE_SCN_GPREL,
			MEM_FARDATA = IMAGE_SCN_MEM_FARDATA,
			MEM_PURGEABLE = IMAGE_SCN_MEM_PURGEABLE,
			MEM_16BIT = IMAGE_SCN_MEM_16BIT,
			MEM_LOCKED = IMAGE_SCN_MEM_LOCKED,
			MEM_PRELOAD = IMAGE_SCN_MEM_PRELOAD,
			ALIGN_1BYTES = IMAGE_SCN_ALIGN_1BYTES,
			ALIGN_2BYTES = IMAGE_SCN_ALIGN_2BYTES,
			ALIGN_4BYTES = IMAGE_SCN_ALIGN_4BYTES,
			ALIGN_8BYTES = IMAGE_SCN_ALIGN_8BYTES,
			ALIGN_16BYTES = IMAGE_SCN_ALIGN_16BYTES,
			ALIGN_32BYTES = IMAGE_SCN_ALIGN_32BYTES,
			ALIGN_64BYTES = IMAGE_SCN_ALIGN_64BYTES,
			ALIGN_128BYTES = IMAGE_SCN_ALIGN_128BYTES,
			ALIGN_256BYTES = IMAGE_SCN_ALIGN_256BYTES,
			ALIGN_512BYTES = IMAGE_SCN_ALIGN_512BYTES,
			ALIGN_1024BYTES = IMAGE_SCN_ALIGN_1024BYTES,
			ALIGN_2048BYTES = IMAGE_SCN_ALIGN_2048BYTES,
			ALIGN_4096BYTES = IMAGE_SCN_ALIGN_4096BYTES,
			ALIGN_8192BYTES = IMAGE_SCN_ALIGN_8192BYTES,
			ALIGN_MASK = IMAGE_SCN_ALIGN_MASK,
			LNK_NRELOC_OVFL = IMAGE_SCN_LNK_NRELOC_OVFL,
			MEM_DISCARDABLE = IMAGE_SCN_MEM_DISCARDABLE,
			MEM_NOT_CACHED = IMAGE_SCN_MEM_NOT_CACHED,
			MEM_NOT_PAGED = IMAGE_SCN_MEM_NOT_PAGED,
			MEM_SHARED = IMAGE_SCN_MEM_SHARED,
			MEM_EXECUTE = IMAGE_SCN_MEM_EXECUTE,
			MEM_READ = IMAGE_SCN_MEM_READ,
			MEM_WRITE = IMAGE_SCN_MEM_WRITE
		};

		//[StructLayout(LayoutKind::Explicit, /*Size = ,*/ CharSet = CharSet::Ansi)]
		//[FieldOffset(0)]
		//[MarshalAs(UnmanagedType::ByValArray, SizeConst = IMAGE_SIZEOF_SHORT_NAME)]
		//array<BYTE>^    Name;
		//[FieldOffset(8)]
		//DWORD   PhysicalAddress;
		//[FieldOffset(8)]
		//DWORD   VirtualSize;
		//[FieldOffset(12)]
		//DWORD   VirtualAddress;
		//[FieldOffset(16)]
		//DWORD   SizeOfRawData;
		//[FieldOffset(20)]
		//DWORD   PointerToRawData;
		//[FieldOffset(24)]
		//DWORD   PointerToRelocations;
		//[FieldOffset(28)]
		//DWORD   PointerToLinenumbers;
		//[FieldOffset(32)]
		//WORD    NumberOfRelocations;
		//[FieldOffset(34)]
		//WORD    NumberOfLinenumbers;
		//[FieldOffset(36)]
		//DWORD   Characteristics;
		ref class PeImage;

		[TypeConverter(ShowPropertiesConverter::typeid)]
		public ref class SectionHeaderWrapper :
			public PeStructDescription,
			public IElementName
		{
			PIMAGE_SECTION_HEADER GetPointer()
			{
				return (PIMAGE_SECTION_HEADER)addr.ToPointer();
			}
			static array<String^>^ sortList;
		public:
			virtual array<String^>^ GetSortList() override
			{
				if (SectionHeaderWrapper::sortList == nullptr)
				{
					SectionHeaderWrapper::sortList = gcnew array<String^>
					{
						"Name",
							"PhysicalAddress",
							"VirtualSize",
							"VirtualAddress",
							"SizeOfRawData",
							"PointerToRawData",
							"PointerToRelocations",
							"PointerToLinenumbers",
							"NumberOfRelocations",
							"NumberOfLinenumbers",
							"Characteristics"
					};
				}
				return SectionHeaderWrapper::sortList;
			}
			SectionHeaderWrapper(IntPtr addr, IntPtr base)
			{
				SetDescription(addr,base, sizeof(IMAGE_SECTION_HEADER));
			}
			
			property UnmanagedString^ Name//[IMAGE_SIZEOF_SHORT_NAME]
			{
				UnmanagedString^ get()
				{
					return gcnew UnmanagedString(IntPtr(&GetPointer()->Name),base,IMAGE_SIZEOF_SHORT_NAME);
				}
				
			};
			property UnmanagedValue<DWORD>^ VirtualSize
			{
				UnmanagedValue<DWORD>^ get()
				{
					if (addr == IntPtr::Zero)
					{
						return nullptr;
					}
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetPointer()->Misc.VirtualSize),base);
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
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetPointer()->VirtualAddress), base);

				}
			}
			property UnmanagedValue<DWORD>^ SizeOfRawData
			{
				UnmanagedValue<DWORD>^ get()
				{
					if (addr == IntPtr::Zero)
					{
						return nullptr;
					}
					return gcnew UnmanagedValue<DWORD>(IntPtr(&(GetPointer()->SizeOfRawData)), base);

				}
			}
			property UnmanagedValue<DWORD>^ PointerToRawData
			{
				UnmanagedValue<DWORD>^ get()
				{
					if (addr == IntPtr::Zero)
					{
						return nullptr;
					}
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetPointer()->PointerToRawData), base);

				}
			}
			property UnmanagedValue<DWORD>^ PointerToRelocations
			{
				UnmanagedValue<DWORD>^ get()
				{
					if (addr == IntPtr::Zero)
					{
						return nullptr;
					}
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetPointer()->PointerToRelocations), base);

				}
			}
			property UnmanagedValue<DWORD>^ PointerToLinenumbers
			{
				UnmanagedValue<DWORD>^ get()
				{
					if (addr == IntPtr::Zero)
					{
						return nullptr;
					}
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetPointer()->PointerToLinenumbers), base);

				}
			}
			property UnmanagedValue<WORD>^  NumberOfRelocations
			{
				UnmanagedValue<WORD>^ get()
				{
					if (addr == IntPtr::Zero)
					{
						return nullptr;
					}
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetPointer()->NumberOfRelocations), base);

				}
			}
			property UnmanagedValue<WORD>^  NumberOfLinenumbers
			{
				UnmanagedValue<WORD>^ get()
				{
					if (addr == IntPtr::Zero)
					{
						return nullptr;
					}
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetPointer()->NumberOfLinenumbers), base);

				}
			}
			property UnmanagedEnum<SectionCharacteristics>^ Characteristics
			{
				UnmanagedEnum<SectionCharacteristics>^ get()
				{
					if (addr == IntPtr::Zero)
					{
						return nullptr;
					}
					return gcnew UnmanagedEnum<SectionCharacteristics>(IntPtr(&GetPointer()->Characteristics), base);

				}
			}


			// 通过 IElementName 继承
			virtual String ^ GetName()
			{
				return Name->String;
			}

};

		[TypeConverter(PeStructArrayConverter::typeid)]
		ref class SectionHeaderArrayWrapper :
			public PeStructWrapper<PE::PeDecoder::LazyInstance<PE::SectionHeaders>>,
			public IWrapperArray
		{
			List<IElementName^>^ list;
			void InitArrayList()
			{

				list = gcnew List<IElementName^>(numberOfSections); // 
				auto iter = GetUnmanagedStruct()->CreateIterator();
				while (iter->Next())
				{
					list->Add(gcnew SectionHeaderWrapper(IntPtr(iter->Current()), pe->BaseAddress));
				}
			}
			int numberOfSections;
		public:

			SectionHeaderArrayWrapper(PeImage^ pe) :PeStructWrapperBase(pe)
			{
				list = nullptr;
				numberOfSections = pe->GetPeDecoder()->GetNtHeader->GetNtHeader32()->FileHeader.NumberOfSections;

				PVOID sectionAddr = NULL;
				if (pe->HasNtHeader32)
				{
					sectionAddr = IMAGE_FIRST_SECTION((PIMAGE_NT_HEADERS32)(&pe->GetPeDecoder()->GetNtHeader->GetNtHeader32()->Signature));
				}
				else
				{
					sectionAddr = IMAGE_FIRST_SECTION((PIMAGE_NT_HEADERS64)(&pe->GetPeDecoder()->GetNtHeader->GetNtHeader64()->Signature));
				}
				SetDescription(IntPtr(sectionAddr), GetPeBase(), sizeof(IMAGE_SECTION_HEADER)*numberOfSections);

			}
			virtual array<String^>^ GetSortList() override
			{
				return nullptr;
			}
			virtual PeStructWrapperType & GetUnmanagedStruct() override
			{
				return pe->GetPeDecoder()->GetSection;
			}
		
			// 通过 IWrapperArray 继承
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