#pragma once
namespace PeImageClr
{
	[TypeConverter(ShowPropertiesConverter::typeid)]
	public ref class OptionalHeaderWrapper64 :
		public PeStructWrapper<IMAGE_OPTIONAL_HEADER64>,
		public IOptionalHeaderWrapper
	{
	internal:
		virtual PeStructWrapperType & GetUnmanagedStruct() override
		{
			return pe->GetPeDecoder()->GetNtHeader->GetNtHeader64()->OptionalHeader;
		}

	public:
		OptionalHeaderWrapper64(PeImage^ pe) :PeStructWrapperBase(pe)
		{
			SetDescription(IntPtr(&pe->GetPeDecoder()->GetNtHeader->GetNtHeader64()->OptionalHeader), GetPeBase(), sizeof(IMAGE_OPTIONAL_HEADER64));
		}
		virtual array<String^>^ GetSortList() override
		{
			return OptionalHeaderSort::GetSortList();
		}
		property UnmanagedEnum<OptionalMagic>^ Magic
		{
			UnmanagedEnum<OptionalMagic>^ get()
			{
				return gcnew UnmanagedEnum<OptionalMagic>(IntPtr(&GetUnmanagedStruct().Magic), GetPeBase());
			}
		};
		property UnmanagedValue<BYTE>^ MajorLinkerVersion
		{
			UnmanagedValue<BYTE>^ get()
			{
				return gcnew UnmanagedValue<BYTE>(IntPtr(&GetUnmanagedStruct().MajorLinkerVersion), GetPeBase());
			}
		}
		property UnmanagedValue<BYTE>^ MinorLinkerVersion
		{
			UnmanagedValue<BYTE>^ get()
			{
				return gcnew UnmanagedValue<BYTE>(IntPtr(&GetUnmanagedStruct().MinorLinkerVersion), GetPeBase());
			}
		}
		property UnmanagedValue<DWORD>^ SizeOfCode
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfCode), GetPeBase());
			}
		}
		property UnmanagedValue<DWORD>^ SizeOfInitializedData
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfInitializedData), GetPeBase());
			}
		}
		property UnmanagedValue<DWORD>^ SizeOfUninitializedData
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfUninitializedData), GetPeBase());
			}
		}
		property UnmanagedValue<DWORD>^ AddressOfEntryPoint
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().AddressOfEntryPoint), GetPeBase());
			}
		}
		property UnmanagedValue<DWORD>^ BaseOfCode
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().BaseOfCode), GetPeBase());
			}
		}
		property UnmanagedValue<ULONGLONG>^ ImageBase
		{
			UnmanagedValue<ULONGLONG>^ get()
			{
				return gcnew UnmanagedValue<ULONGLONG>(IntPtr(&GetUnmanagedStruct().ImageBase), GetPeBase());
			}
		}
		property UnmanagedValue<DWORD>^ SectionAlignment
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SectionAlignment), GetPeBase());
			}
		}
		property UnmanagedValue<DWORD>^ FileAlignment
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().FileAlignment), GetPeBase());
			}
		}
		property UnmanagedValue<WORD>^ MajorOperatingSystemVersion
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MajorOperatingSystemVersion), GetPeBase());
			}
		}
		property UnmanagedValue<WORD>^ MinorOperatingSystemVersion
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MinorOperatingSystemVersion), GetPeBase());
			}
		}
		property UnmanagedValue<WORD>^ MajorImageVersion
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MajorImageVersion), GetPeBase());
			}
		}
		property UnmanagedValue<WORD>^ MinorImageVersion
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MinorImageVersion), GetPeBase());
			}
		}
		property UnmanagedValue<WORD>^ MajorSubsystemVersion
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MajorSubsystemVersion), GetPeBase());
			}
		}
		property UnmanagedValue<WORD>^ MinorSubsystemVersion
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MinorSubsystemVersion), GetPeBase());
			}
		}
		property UnmanagedValue<DWORD>^ Win32VersionValue
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().Win32VersionValue), GetPeBase());
			}
		}
		property UnmanagedValue<DWORD>^ SizeOfImage
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfImage), GetPeBase());
			}
		}
		property UnmanagedValue<DWORD>^ SizeOfHeaders
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfHeaders), GetPeBase());
			}
		}
		property UnmanagedValue<DWORD>^ CheckSum
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().CheckSum), GetPeBase());
			}
		}
		property UnmanagedEnum<SubsystemValues>^ Subsystem
		{
			UnmanagedEnum<SubsystemValues>^ get()
			{
				return gcnew UnmanagedEnum<SubsystemValues>(IntPtr(&GetUnmanagedStruct().Subsystem), GetPeBase());
			}
		};

		property UnmanagedEnum<DllCharacteristicsEntries>^ DllCharacteristics
		{
			UnmanagedEnum<DllCharacteristicsEntries>^ get()
			{
				return gcnew UnmanagedEnum<DllCharacteristicsEntries>(IntPtr(&GetUnmanagedStruct().DllCharacteristics), GetPeBase());
			}
		};
		property UnmanagedValue<ULONGLONG>^ SizeOfStackReserve
		{
			UnmanagedValue<ULONGLONG>^ get()
			{
				return gcnew UnmanagedValue<ULONGLONG>(IntPtr(&GetUnmanagedStruct().SizeOfStackReserve), GetPeBase());
			}
		}
		property UnmanagedValue<ULONGLONG>^ SizeOfStackCommit
		{
			UnmanagedValue<ULONGLONG>^ get()
			{
				return gcnew UnmanagedValue<ULONGLONG>(IntPtr(&GetUnmanagedStruct().SizeOfStackCommit), GetPeBase());
			}
		}
		property UnmanagedValue<ULONGLONG>^ SizeOfHeapReserve
		{
			UnmanagedValue<ULONGLONG>^ get()
			{
				return gcnew UnmanagedValue<ULONGLONG>(IntPtr(&GetUnmanagedStruct().SizeOfHeapReserve), GetPeBase());
			}
		}
		property UnmanagedValue<ULONGLONG>^ SizeOfHeapCommit
		{
			UnmanagedValue<ULONGLONG>^ get()
			{
				return gcnew UnmanagedValue<ULONGLONG>(IntPtr(&GetUnmanagedStruct().SizeOfHeapCommit), GetPeBase());
			}
		}
		property UnmanagedValue<DWORD>^ LoaderFlags
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().LoaderFlags), GetPeBase());
			}
		}
		property UnmanagedValue<DWORD>^ NumberOfRvaAndSizes
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().NumberOfRvaAndSizes), GetPeBase());
			}
		}
		[DisplayNameAttribute("Data Directories")]
		property DataDirectoriesWrapper^ DataDirectories
		{
			DataDirectoriesWrapper^ get()
			{
				return gcnew DataDirectoriesWrapper(GetUnmanagedStruct().DataDirectory, GetPeBase(), GetUnmanagedStruct().NumberOfRvaAndSizes);
			}
		};

	};

}  // namespace PeImageClr
