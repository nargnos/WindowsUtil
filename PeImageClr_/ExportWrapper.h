#pragma once
namespace PeImageClr
{	// 导出表头，可取到导出表函数数组
	public ref class ExportWrapper :
		public PeStructWrapper<PE::PeDecoder::LazyInstance<PE::ExportDirectory>>
	{
		static array<String^>^ sortList;
		int numberOfSections;
	public:
		virtual array<String^>^ GetSortList() override
		{
			if (ExportWrapper::sortList == nullptr)
			{
				ExportWrapper::sortList = gcnew array<String^>
				{
					"Characteristics",
						"TimeDateStamp",
						"MajorVersion",
						"MinorVersion",
						"Name",
						"Base",
						"NumberOfFunctions",
						"NumberOfNames",
						"AddressOfFunctions",
						"AddressOfNames",
						"AddressOfNameOrdinals",
						"Functions"
				};
			}
			return ExportWrapper::sortList;
		}
		virtual PeStructWrapperType & GetUnmanagedStruct() override
		{
			return pe->GetPeDecoder()->GetExport;
		}
		ExportWrapper(PeImage^ pe) :PeStructWrapperBase(pe)
		{
			SetDescription(IntPtr(GetUnmanagedStruct()->GetValue()), GetPeBase(), sizeof(IMAGE_EXPORT_DIRECTORY));

		}

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
		property ExportFuncArrayWrapper^   Functions
		{
			ExportFuncArrayWrapper^ get()
			{
				return gcnew ExportFuncArrayWrapper(pe);
			}
		}
#pragma endregion
	};
}  // namespace PeImageClr
