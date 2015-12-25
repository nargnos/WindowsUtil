#pragma once
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		public interface class IOptionalHeaderWapper
		{};
		[TypeConverter(EnumHexConverter::typeid)]
		public enum class OptionalMagic :WORD
		{
			[BrowsableAttribute(false)]
			UNKNOWN = 0,
			NT_HDR32 = IMAGE_NT_OPTIONAL_HDR32_MAGIC,
			NT_HDR64 = IMAGE_NT_OPTIONAL_HDR64_MAGIC,
			ROM_HDR = IMAGE_ROM_OPTIONAL_HDR_MAGIC
		};
		[TypeConverter(EnumHexConverter::typeid)]
		public enum class SubsystemValues :WORD
		{
			UNKNOWN = IMAGE_SUBSYSTEM_UNKNOWN,
			NATIVE = IMAGE_SUBSYSTEM_NATIVE,
			WINDOWS_GUI = IMAGE_SUBSYSTEM_WINDOWS_GUI,
			WINDOWS_CUI = IMAGE_SUBSYSTEM_WINDOWS_CUI,
			OS2_CUI = IMAGE_SUBSYSTEM_OS2_CUI,
			POSIX_CUI = IMAGE_SUBSYSTEM_POSIX_CUI,
			NATIVE_WINDOWS = IMAGE_SUBSYSTEM_NATIVE_WINDOWS,
			WINDOWS_CE_GUI = IMAGE_SUBSYSTEM_WINDOWS_CE_GUI,
			EFI_APPLICATION = IMAGE_SUBSYSTEM_EFI_APPLICATION,
			EFI_BOOT_SERVICE_DRIVER = IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER,
			EFI_RUNTIME_DRIVER = IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER,
			EFI_ROM = IMAGE_SUBSYSTEM_EFI_ROM,
			XBOX = IMAGE_SUBSYSTEM_XBOX,
			WINDOWS_BOOT_APPLICATION = IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION
		};

		[FlagsAttribute]
		[EditorAttribute(FlagsEditor<DllCharacteristicsEntries>::typeid, UITypeEditor::typeid)]
		public enum class DllCharacteristicsEntries :WORD
		{
			HIGH_ENTROPY_VA = IMAGE_DLLCHARACTERISTICS_HIGH_ENTROPY_VA,
			DYNAMIC_BASE = IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE,
			FORCE_INTEGRITY = IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY,
			NX_COMPAT = IMAGE_DLLCHARACTERISTICS_NX_COMPAT,
			NO_ISOLATION = IMAGE_DLLCHARACTERISTICS_NO_ISOLATION,
			NO_SEH = IMAGE_DLLCHARACTERISTICS_NO_SEH,
			NO_BIND = IMAGE_DLLCHARACTERISTICS_NO_BIND,
			APPCONTAINER = IMAGE_DLLCHARACTERISTICS_APPCONTAINER,
			WDM_DRIVER = IMAGE_DLLCHARACTERISTICS_WDM_DRIVER,
			GUARD_CF = IMAGE_DLLCHARACTERISTICS_GUARD_CF,
			TERMINAL_SERVER_AWARE = IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE
		};
		// TODO: 在界面上判断是否32，绑定对应结构到按钮事件就行了
		// 非托管资源的地址不一样，所以只能分成2个类
		[TypeConverter(OptionalHeaderConverter::typeid)]
		public ref class OptionalHeaderWapper32 :
			public PeStructWapper<IMAGE_OPTIONAL_HEADER32>,
			public IOptionalHeaderWapper
		{
		internal:
			// 通过 PeStructWapper 继承
			virtual PeStructWapperType & GetUnmanagedStruct() override;
		public:
			OptionalHeaderWapper32(PeImage^ pe) :PeStructWapperBase(pe)
			{

			}
			property OptionalMagic Magic
			{
				OptionalMagic get()
				{
					auto value = GetUnmanagedStruct().Magic;
					if (Enum::IsDefined(OptionalMagic::typeid, value))
					{
						return safe_cast<OptionalMagic>(value);
					}
					return OptionalMagic::UNKNOWN;
				}
				void set(OptionalMagic value)
				{
					GetUnmanagedStruct().Magic = (WORD)value;
				}
			};
			property UnmanagedValue<BYTE>^ MajorLinkerVersion
			{
				UnmanagedValue<BYTE>^ get()
				{
					return gcnew UnmanagedValue<BYTE>(IntPtr(&GetUnmanagedStruct().MajorLinkerVersion));
				}
			};
			property UnmanagedValue<BYTE>^ MinorLinkerVersion
			{
				UnmanagedValue<BYTE>^ get()
				{
					return gcnew UnmanagedValue<BYTE>(IntPtr(&GetUnmanagedStruct().MinorLinkerVersion));
				}
			};
			property UnmanagedValue<DWORD>^ SizeOfCode
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfCode));
				}
			};
			property UnmanagedValue<DWORD>^ SizeOfInitializedData
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfInitializedData));
				}
			};
			property UnmanagedValue<DWORD>^ SizeOfUninitializedData
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfUninitializedData));
				}
			};
			property UnmanagedValue<DWORD>^ AddressOfEntryPoint
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().AddressOfEntryPoint));
				}
			};
			property UnmanagedValue<DWORD>^ BaseOfCode
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().BaseOfCode));
				}
			};
			property UnmanagedValue<DWORD>^ BaseOfData
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().BaseOfData));
				}
			};
			property UnmanagedValue<DWORD>^ ImageBase
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().ImageBase));
				}
			};
			property UnmanagedValue<DWORD>^ SectionAlignment
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SectionAlignment));
				}
			};
			property UnmanagedValue<DWORD>^ FileAlignment
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().FileAlignment));
				}
			};
			property UnmanagedValue<WORD>^ MajorOperatingSystemVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MajorOperatingSystemVersion));
				}
			};
			property UnmanagedValue<WORD>^ MinorOperatingSystemVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MinorOperatingSystemVersion));
				}
			};
			property UnmanagedValue<WORD>^ MajorImageVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MajorImageVersion));
				}
			};
			property UnmanagedValue<WORD>^ MinorImageVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MinorImageVersion));
				}
			};
			property UnmanagedValue<WORD>^ MajorSubsystemVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MajorSubsystemVersion));
				}
			};
			property UnmanagedValue<WORD>^ MinorSubsystemVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MinorSubsystemVersion));
				}
			};
			property UnmanagedValue<DWORD>^ Win32VersionValue
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().Win32VersionValue));
				}
			};
			property UnmanagedValue<DWORD>^ SizeOfImage
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfImage));
				}
			};
			property UnmanagedValue<DWORD>^ SizeOfHeaders
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfHeaders));
				}
			};
			property UnmanagedValue<DWORD>^ CheckSum
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().CheckSum));
				}
			};
			property SubsystemValues Subsystem
			{
				SubsystemValues get()
				{
					return safe_cast<SubsystemValues>(GetUnmanagedStruct().Subsystem);
				}
				void set(SubsystemValues value)
				{
					GetUnmanagedStruct().Subsystem = (WORD)value;
				}
			};
			property DllCharacteristicsEntries DllCharacteristics
			{
				DllCharacteristicsEntries get()
				{
					return safe_cast<DllCharacteristicsEntries>(GetUnmanagedStruct().DllCharacteristics);
				}
				void set(DllCharacteristicsEntries value)
				{
					GetUnmanagedStruct().DllCharacteristics = (WORD)value;
				}

			};
			property UnmanagedValue<DWORD>^ SizeOfStackReserve
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfStackReserve));
				}
			};
			property UnmanagedValue<DWORD>^ SizeOfStackCommit
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfStackCommit));
				}
			};
			property UnmanagedValue<DWORD>^ SizeOfHeapReserve
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfHeapReserve));
				}
			};
			property UnmanagedValue<DWORD>^ SizeOfHeapCommit
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfHeapCommit));
				}
			};
			property UnmanagedValue<DWORD>^ LoaderFlags
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().LoaderFlags));
				}
			};
			property UnmanagedValue<DWORD>^ NumberOfRvaAndSizes
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().NumberOfRvaAndSizes));
				}
			};

		};

		[TypeConverter(OptionalHeaderConverter::typeid)]
		public ref class OptionalHeaderWapper64 :
			public PeStructWapper<IMAGE_OPTIONAL_HEADER64>,
			public IOptionalHeaderWapper
		{
		internal:
			// 通过 PeStructWapper 继承
			virtual PeStructWapperType & GetUnmanagedStruct() override;

		public:
			OptionalHeaderWapper64(PeImage^ pe) :PeStructWapperBase(pe)
			{}
			property OptionalMagic Magic
			{
				OptionalMagic get()
				{
					auto value = GetUnmanagedStruct().Magic;
					if (Enum::IsDefined(OptionalMagic::typeid, value))
					{
						return safe_cast<OptionalMagic>(value);
					}
					return OptionalMagic::UNKNOWN;
				}
				void set(OptionalMagic value)
				{
					GetUnmanagedStruct().Magic = (WORD)value;
				}
			}
			property UnmanagedValue<BYTE>^ MajorLinkerVersion
			{
				UnmanagedValue<BYTE>^ get()
				{
					return gcnew UnmanagedValue<BYTE>(IntPtr(&GetUnmanagedStruct().MajorLinkerVersion));
				}
			}
			property UnmanagedValue<BYTE>^ MinorLinkerVersion
			{
				UnmanagedValue<BYTE>^ get()
				{
					return gcnew UnmanagedValue<BYTE>(IntPtr(&GetUnmanagedStruct().MinorLinkerVersion));
				}
			}
			property UnmanagedValue<DWORD>^ SizeOfCode
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfCode));
				}
			}
			property UnmanagedValue<DWORD>^ SizeOfInitializedData
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfInitializedData));
				}
			}
			property UnmanagedValue<DWORD>^ SizeOfUninitializedData
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfUninitializedData));
				}
			}
			property UnmanagedValue<DWORD>^ AddressOfEntryPoint
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().AddressOfEntryPoint));
				}
			}
			property UnmanagedValue<DWORD>^ BaseOfCode
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().BaseOfCode));
				}
			}
			property UnmanagedValue<ULONGLONG>^ ImageBase
			{
				UnmanagedValue<ULONGLONG>^ get()
				{
					return gcnew UnmanagedValue<ULONGLONG>(IntPtr(&GetUnmanagedStruct().ImageBase));
				}
			}
			property UnmanagedValue<DWORD>^ SectionAlignment
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SectionAlignment));
				}
			}
			property UnmanagedValue<DWORD>^ FileAlignment
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().FileAlignment));
				}
			}
			property UnmanagedValue<WORD>^ MajorOperatingSystemVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MajorOperatingSystemVersion));
				}
			}
			property UnmanagedValue<WORD>^ MinorOperatingSystemVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MinorOperatingSystemVersion));
				}
			}
			property UnmanagedValue<WORD>^ MajorImageVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MajorImageVersion));
				}
			}
			property UnmanagedValue<WORD>^ MinorImageVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MinorImageVersion));
				}
			}
			property UnmanagedValue<WORD>^ MajorSubsystemVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MajorSubsystemVersion));
				}
			}
			property UnmanagedValue<WORD>^ MinorSubsystemVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MinorSubsystemVersion));
				}
			}
			property UnmanagedValue<DWORD>^ Win32VersionValue
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().Win32VersionValue));
				}
			}
			property UnmanagedValue<DWORD>^ SizeOfImage
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfImage));
				}
			}
			property UnmanagedValue<DWORD>^ SizeOfHeaders
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfHeaders));
				}
			}
			property UnmanagedValue<DWORD>^ CheckSum
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().CheckSum));
				}
			}
			property SubsystemValues Subsystem
			{
				SubsystemValues get()
				{
					return safe_cast<SubsystemValues>(GetUnmanagedStruct().Subsystem);
				}
				void set(SubsystemValues value)
				{
					GetUnmanagedStruct().Subsystem = (WORD)value;
				}
			}
			property DllCharacteristicsEntries DllCharacteristics
			{
				DllCharacteristicsEntries get()
				{
					return safe_cast<DllCharacteristicsEntries>(GetUnmanagedStruct().DllCharacteristics);
				}
				void set(DllCharacteristicsEntries value)
				{
					GetUnmanagedStruct().DllCharacteristics = (WORD)value;
				}
			}
			property UnmanagedValue<ULONGLONG>^ SizeOfStackReserve
			{
				UnmanagedValue<ULONGLONG>^ get()
				{
					return gcnew UnmanagedValue<ULONGLONG>(IntPtr(&GetUnmanagedStruct().SizeOfStackReserve));
				}
			}
			property UnmanagedValue<ULONGLONG>^ SizeOfStackCommit
			{
				UnmanagedValue<ULONGLONG>^ get()
				{
					return gcnew UnmanagedValue<ULONGLONG>(IntPtr(&GetUnmanagedStruct().SizeOfStackCommit));
				}
			}
			property UnmanagedValue<ULONGLONG>^ SizeOfHeapReserve
			{
				UnmanagedValue<ULONGLONG>^ get()
				{
					return gcnew UnmanagedValue<ULONGLONG>(IntPtr(&GetUnmanagedStruct().SizeOfHeapReserve));
				}
			}
			property UnmanagedValue<ULONGLONG>^ SizeOfHeapCommit
			{
				UnmanagedValue<ULONGLONG>^ get()
				{
					return gcnew UnmanagedValue<ULONGLONG>(IntPtr(&GetUnmanagedStruct().SizeOfHeapCommit));
				}
			}
			property UnmanagedValue<DWORD>^ LoaderFlags
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().LoaderFlags));
				}
			}
			property UnmanagedValue<DWORD>^ NumberOfRvaAndSizes
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().NumberOfRvaAndSizes));
				}
			}
		};


	}
}