#pragma once
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
#define ENUM_VALUE(name,hex) name##_##hex
		using namespace System::ComponentModel;


		[TypeConverter(EnumHexConverter::typeid)]
		public enum class  MachineType :WORD
		{
			UNKNOWN = IMAGE_FILE_MACHINE_UNKNOWN,
			I386 = IMAGE_FILE_MACHINE_I386,
			R3000 = IMAGE_FILE_MACHINE_R3000,
			R4000 = IMAGE_FILE_MACHINE_R4000,
			R10000 = IMAGE_FILE_MACHINE_R10000,
			WCEMIPSV2 = IMAGE_FILE_MACHINE_WCEMIPSV2,
			ALPHA = IMAGE_FILE_MACHINE_ALPHA,
			SH3 = IMAGE_FILE_MACHINE_SH3,
			SH3DSP = IMAGE_FILE_MACHINE_SH3DSP,
			SH3E = IMAGE_FILE_MACHINE_SH3E,
			SH4 = IMAGE_FILE_MACHINE_SH4,
			SH5 = IMAGE_FILE_MACHINE_SH5,
			ARM = IMAGE_FILE_MACHINE_ARM,
			THUMB = IMAGE_FILE_MACHINE_THUMB,
			ARMNT = IMAGE_FILE_MACHINE_ARMNT,
			AM33 = IMAGE_FILE_MACHINE_AM33,
			POWERPC = IMAGE_FILE_MACHINE_POWERPC,
			POWERPCFP = IMAGE_FILE_MACHINE_POWERPCFP,
			IA64 = IMAGE_FILE_MACHINE_IA64,
			MIPS16 = IMAGE_FILE_MACHINE_MIPS16,
			ALPHA64 = IMAGE_FILE_MACHINE_ALPHA64,
			MIPSFPU = IMAGE_FILE_MACHINE_MIPSFPU,
			MIPSFPU16 = IMAGE_FILE_MACHINE_MIPSFPU16,
			AXP64 = IMAGE_FILE_MACHINE_AXP64,
			TRICORE = IMAGE_FILE_MACHINE_TRICORE,
			CEF = IMAGE_FILE_MACHINE_CEF,
			EBC = IMAGE_FILE_MACHINE_EBC,
			AMD64 = IMAGE_FILE_MACHINE_AMD64,
			M32R = IMAGE_FILE_MACHINE_M32R,
			CEE = IMAGE_FILE_MACHINE_CEE
		};

		[FlagsAttribute]
		[EditorAttribute(FlagsEditor<CharacteristicsType>::typeid, UITypeEditor::typeid)]
		public enum class  CharacteristicsType :WORD
		{
			RELOCS_STRIPPED = IMAGE_FILE_RELOCS_STRIPPED,
			EXECUTABLE_IMAGE = IMAGE_FILE_EXECUTABLE_IMAGE,
			LINE_NUMS_STRIPPED = IMAGE_FILE_LINE_NUMS_STRIPPED,
			LOCAL_SYMS_STRIPPED = IMAGE_FILE_LOCAL_SYMS_STRIPPED,
			AGGRESIVE_WS_TRIM = IMAGE_FILE_AGGRESIVE_WS_TRIM,
			LARGE_ADDRESS_AWARE = IMAGE_FILE_LARGE_ADDRESS_AWARE,
			BYTES_REVERSED_LO = IMAGE_FILE_BYTES_REVERSED_LO,
			MACHINE_32BIT = IMAGE_FILE_32BIT_MACHINE,
			DEBUG_STRIPPED = IMAGE_FILE_DEBUG_STRIPPED,
			REMOVABLE_RUN_FROM_SWAP = IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP,
			NET_RUN_FROM_SWAP = IMAGE_FILE_NET_RUN_FROM_SWAP,
			SYSTEM = IMAGE_FILE_SYSTEM,
			DLL = IMAGE_FILE_DLL,
			UP_SYSTEM_ONLY = IMAGE_FILE_UP_SYSTEM_ONLY,
			BYTES_REVERSED_HI = IMAGE_FILE_BYTES_REVERSED_HI
		};

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
		public ref class FileHeaderWapper :
			public PeStructWapper<IMAGE_FILE_HEADER>
		{
			static array<String^>^ sortList;
			
		internal:
			// 通过 PeStructWapper 继承
			virtual PeStructWapperType & GetUnmanagedStruct() override;

		public:

			FileHeaderWapper(PeImage^ pe);
			virtual array<String^>^ GetSortList() override
			{
				if (FileHeaderWapper::sortList == nullptr)
				{
					FileHeaderWapper::sortList = gcnew array<String^>
					{
						"Machine",
							"NumberOfSections",
							"TimeDateStamp",
							"PointerToSymbolTable",
							"NumberOfSymbols",
							"SizeOfOptionalHeader",
							"Characteristics"
					};
				}
				return FileHeaderWapper::sortList;
			}
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
	}
}
