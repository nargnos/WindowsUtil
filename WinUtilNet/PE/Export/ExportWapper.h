#pragma once
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		using namespace System::Collections::Generic;
		ref class PeImage;

		public ref class ExportNameWapper :
			public IElementName,
			public PeStructDescription
		{
			IntPtr nameRva;
			IntPtr nameOrdinal;
			PeImage^ pe;
			PVOID GetNamePtr();
		public:
			ExportNameWapper(IntPtr nameRva, IntPtr nameOrdinal, PeImage^ pe);
			virtual String ^ GetName();

			virtual array<String^>^ GetSortList() override;
			property UnmanagedValue<DWORD>^ NameRVA
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(nameRva, base);
				}
			}
			property UnmanagedValue<WORD>^ NameOrdinal
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(nameOrdinal, base);
				}
			}
			property UnmanagedString^ Name
			{
				UnmanagedString^ get()
				{
					return gcnew UnmanagedString(IntPtr(GetNamePtr()), base, 0);//
				}
			}
		};
		[TypeConverter(PeStructArrayConverter::typeid)]
		public ref class ExportNameArrayWapper :
			public IWapperArray,
			public PeStructDescription
		{
			System::Collections::Generic::IList<IElementName^>^ names;
		public:
			ExportNameArrayWapper(List<ExportNameWapper^>^ nameWappers);
			virtual System::Collections::Generic::IList<IElementName^>^ GetElements();

			virtual array<String^>^ GetSortList() override;

		};

		// 导出表函数，因为存在多个名字同时指向一个函数地址的情况，所以包含导出表函数名或函数名数组
		public ref class ExportFuncWapper :
			public IElementName,
			public PeStructDescription,
			public IPropertiesFilter
		{
			PeImage^ pe;
			int index;
			List<ExportNameWapper^>^ names;
			static array<String^>^ sortList;
		internal:
			void AddName(ExportNameWapper^ name);
		public:
			virtual String ^ GetName() override;
			virtual array<String^>^ GetSortList() override;
			virtual List<String^>^ GetHidePropList() override;
			ExportFuncWapper(int index, IntPtr addr, PeImage^ pe);
			virtual String ^ GetDescription() override
			{
				if (addr == IntPtr::Zero)
				{
					return String::Empty;
				}
				return String::Format("[{0:X8}]", FuncRVA->Value); 
			}
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
			property ExportNameArrayWapper^ Names
			{
				ExportNameArrayWapper^ get()
				{
					if (names == nullptr)
					{
						return nullptr;
					}
					if (names->Count == 1)
					{
						return nullptr;
					}
					return gcnew ExportNameArrayWapper(names);
				}
			}
#pragma endregion
		};

		// 导出表函数数组， 读导出表包括无名函数，解析用
		[TypeConverter(PeStructArrayConverter::typeid)]
		public ref class ExportFuncArrayWapper :
			public IWapperArray,
			public PeStructWapper<PE::PeDecoder::LazyInstance<PE::ExportDirectory>>
		{
			System::Collections::Generic::IList<IElementName^>^ list;
			void InitArrayList();
		public:
			virtual PeStructWapperType & GetUnmanagedStruct() override;
			virtual array<String^>^ GetSortList() override;
			virtual System::Collections::Generic::IList<IElementName^>^ GetElements() override;

			ExportFuncArrayWapper(PeImage^ pe);
			virtual String ^ GetDescription() override
			{
				if (GetElements()==nullptr)
				{
					return String::Empty;
				}
				return String::Format("(Count: {0})", GetElements()->Count);
			}
		};


		// 导出表头，可取到导出表函数数组
		public ref class ExportWapper :
			public PeStructWapper<PE::PeDecoder::LazyInstance<PE::ExportDirectory>>
		{
			static array<String^>^ sortList;
			int numberOfSections;
		public:
			virtual array<String^>^ GetSortList() override;
			virtual PeStructWapperType & GetUnmanagedStruct() override;
			ExportWapper(PeImage^ pe);

#pragma region 属性
			property UnmanagedValue<DWORD>^   Characteristics
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->Characteristics), GetPeBase());
				}
			}
			property UnmanagedDateTimeValue<DWORD>^   TimeDateStamp
			{
				UnmanagedDateTimeValue<DWORD>^ get()
				{
					return gcnew UnmanagedDateTimeValue<DWORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->TimeDateStamp), GetPeBase());
				}
			}
			property UnmanagedValue<WORD>^    MajorVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->MajorVersion), GetPeBase());
				}
			}
			property UnmanagedValue<WORD>^    MinorVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->MinorVersion), GetPeBase());
				}
			}
			property UnmanagedValue<DWORD>^   Name
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->Name), GetPeBase());
				}
			}
			property UnmanagedValue<DWORD>^   Base
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->Base), GetPeBase());
				}
			}
			property UnmanagedValue<DWORD>^   NumberOfFunctions
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->NumberOfFunctions), GetPeBase());
				}
			}
			property UnmanagedValue<DWORD>^   NumberOfNames
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->NumberOfNames), GetPeBase());
				}
			}
			property UnmanagedValue<DWORD>^   AddressOfFunctions
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->AddressOfFunctions), GetPeBase());
				}
			}
			property UnmanagedValue<DWORD>^   AddressOfNames
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->AddressOfNames), GetPeBase());
				}
			}
			property UnmanagedValue<DWORD>^   AddressOfNameOrdinals
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct()->GetValue()->AddressOfNameOrdinals), GetPeBase());
				}
			}
			property ExportFuncArrayWapper^   Functions
			{
				ExportFuncArrayWapper^ get()
				{
					return gcnew ExportFuncArrayWapper(pe);
				}
			}
#pragma endregion
		};
	}
}
