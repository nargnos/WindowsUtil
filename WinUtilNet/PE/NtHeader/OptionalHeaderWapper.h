#pragma once
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		public interface class IOptionalHeaderWapper
		{

		};
		public  ref  class OptionalHeaderSort
		{
			static array<String^>^ sortList;
			OptionalHeaderSort() {};
		public:
			static array<String^>^ GetSortList()
			{
				if (OptionalHeaderSort::sortList == nullptr)
				{
					OptionalHeaderSort::sortList = gcnew array<String^>
					{
						"Magic",
							"MajorLinkerVersion",
							"MinorLinkerVersion",
							"SizeOfCode",
							"SizeOfInitializedData",
							"SizeOfUninitializedData",
							"AddressOfEntryPoint",
							"BaseOfCode",
							"BaseOfData",
							"ImageBase",
							"SectionAlignment",
							"FileAlignment",
							"MajorOperatingSystemVersion",
							"MinorOperatingSystemVersion",
							"MajorImageVersion",
							"MinorImageVersion",
							"MajorSubsystemVersion",
							"MinorSubsystemVersion",
							"Win32VersionValue",
							"SizeOfImage",
							"SizeOfHeaders",
							"CheckSum",
							"Subsystem",
							"DllCharacteristics",
							"SizeOfStackReserve",
							"SizeOfStackCommit",
							"SizeOfHeapReserve",
							"SizeOfHeapCommit",
							"LoaderFlags",
							"NumberOfRvaAndSizes"
					};
				}
				return OptionalHeaderSort::sortList;
			}
		};
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


		[TypeConverter(ShowPropertiesConverter::typeid)]
		public ref class DataDirectoryWapper :
			public PeStructDescription
		{
			static array<String^>^ sortList;
		public:
			DataDirectoryWapper(IntPtr addr,IntPtr basePtr)//:PeStructDescription()
			{
				SetDescription(addr, basePtr, sizeof(IMAGE_DATA_DIRECTORY));
			}
			~DataDirectoryWapper()
			{
			}

			virtual array<String^>^ GetSortList() override
			{
				if (DataDirectoryWapper::sortList == nullptr)
				{
					DataDirectoryWapper::sortList = gcnew array<String^>
					{
						"Offset",
							"VirtualAddress",
							"Size"
					};
				}
				return DataDirectoryWapper::sortList;
			}
			property UnmanagedValue<DWORD>^ Size
			{
				UnmanagedValue<DWORD>^ get()
				{
					if (addr == IntPtr::Zero)
					{
						return nullptr;
					}
					return gcnew UnmanagedValue<DWORD>(IntPtr(&((PIMAGE_DATA_DIRECTORY)addr.ToPointer())->Size),base);
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
					return gcnew UnmanagedValue<DWORD>(IntPtr(&((PIMAGE_DATA_DIRECTORY)addr.ToPointer())->VirtualAddress), base);
				}
			}
		};

		[TypeConverter(ShowPropertiesConverter::typeid)]
		public ref class DataDirectoriesWapper :
			public PeStructDescription
		{
			static array<String^>^ sortList;
		public:
			virtual array<String^>^ GetSortList() override
			{
				if (DataDirectoriesWapper::sortList == nullptr)
				{
					DataDirectoriesWapper::sortList = gcnew array<String^>
					{
						"ExportEntry",
							"ImportEntry",
							"ResourceEntry",
							"ExceptionEntry",
							"SecurityEntry",
							"BaserelocEntry",
							"DebugEntry",
							"ArchitectureEntry",
							"GlobalptrEntry",
							"TlsEntry",
							"LoadConfigEntry",
							"BoundImportEntry",
							"IatEntry",
							"DelayImportEntry",
							"ComDescriptorEntry"
					};
				}
				return DataDirectoriesWapper::sortList;
			}
			DataDirectoriesWapper(PIMAGE_DATA_DIRECTORY entry,IntPtr basePtr, int size)
			{
				SetDescription(IntPtr(entry), basePtr, size*sizeof(IMAGE_DATA_DIRECTORY));
			}
			inline IntPtr GetDirectoryPointer(int index)
			{
				return IntPtr(&((PIMAGE_DATA_DIRECTORY)addr.ToPointer())[(int)index]);
			}
			~DataDirectoriesWapper()
			{
			}
			property DataDirectoryWapper^ ExportEntry
			{
				DataDirectoryWapper^ get()
				{
					if (IMAGE_DIRECTORY_ENTRY_EXPORT >= structSize)
					{
						return nullptr;
					}
					return gcnew DataDirectoryWapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_EXPORT), base);
				}
			}
			property DataDirectoryWapper^ ImportEntry
			{
				DataDirectoryWapper^ get()
				{
					if (IMAGE_DIRECTORY_ENTRY_IMPORT >= structSize)
					{
						return nullptr;
					}
					return gcnew DataDirectoryWapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_IMPORT), base);
				}
			}
			property DataDirectoryWapper^ ResourceEntry
			{
				DataDirectoryWapper^ get()
				{
					if (IMAGE_DIRECTORY_ENTRY_RESOURCE >= structSize)
					{
						return nullptr;
					}
					return gcnew DataDirectoryWapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_RESOURCE), base);
				}
			}
			property DataDirectoryWapper^ ExceptionEntry
			{
				DataDirectoryWapper^ get()
				{
					if (IMAGE_DIRECTORY_ENTRY_EXCEPTION >= structSize)
					{
						return nullptr;
					}
					return gcnew DataDirectoryWapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_EXCEPTION), base);
				}
			}
			property DataDirectoryWapper^ SecurityEntry
			{
				DataDirectoryWapper^ get()
				{
					if (IMAGE_DIRECTORY_ENTRY_SECURITY >= structSize)
					{
						return nullptr;
					}
					return gcnew DataDirectoryWapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_SECURITY), base);
				}
			}
			property DataDirectoryWapper^ BaserelocEntry
			{
				DataDirectoryWapper^ get()
				{
					if (IMAGE_DIRECTORY_ENTRY_BASERELOC >= structSize)
					{
						return nullptr;
					}
					return gcnew DataDirectoryWapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_BASERELOC), base);
				}
			}
			property DataDirectoryWapper^ DebugEntry
			{
				DataDirectoryWapper^ get()
				{
					if (IMAGE_DIRECTORY_ENTRY_DEBUG >= structSize)
					{
						return nullptr;
					}
					return gcnew DataDirectoryWapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_DEBUG), base);
				}
			}
			property DataDirectoryWapper^ ArchitectureEntry
			{
				DataDirectoryWapper^ get()
				{
					if (IMAGE_DIRECTORY_ENTRY_ARCHITECTURE >= structSize)
					{
						return nullptr;
					}
					return gcnew DataDirectoryWapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_ARCHITECTURE), base);
				}
			}
			property DataDirectoryWapper^ GlobalptrEntry
			{
				DataDirectoryWapper^ get()
				{
					if (IMAGE_DIRECTORY_ENTRY_GLOBALPTR >= structSize)
					{
						return nullptr;
					}
					return gcnew DataDirectoryWapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_GLOBALPTR), base);
				}
			}
			property DataDirectoryWapper^ TlsEntry
			{
				DataDirectoryWapper^ get()
				{
					if (IMAGE_DIRECTORY_ENTRY_TLS >= structSize)
					{
						return nullptr;
					}
					return gcnew DataDirectoryWapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_TLS), base);
				}
			}
			property DataDirectoryWapper^ LoadConfigEntry
			{
				DataDirectoryWapper^ get()
				{
					if (IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG >= structSize)
					{
						return nullptr;
					}
					return gcnew DataDirectoryWapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG), base);
				}
			}
			property DataDirectoryWapper^ BoundImportEntry
			{
				DataDirectoryWapper^ get()
				{
					if (IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT >= structSize)
					{
						return nullptr;
					}
					return gcnew DataDirectoryWapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT), base);
				}
			}
			property DataDirectoryWapper^ IatEntry
			{
				DataDirectoryWapper^ get()
				{
					if (IMAGE_DIRECTORY_ENTRY_IAT >= structSize)
					{
						return nullptr;
					}
					return gcnew DataDirectoryWapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_IAT), base);
				}
			}
			property DataDirectoryWapper^ DelayImportEntry
			{
				DataDirectoryWapper^ get()
				{
					if (IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT >= structSize)
					{
						return nullptr;
					}
					return gcnew DataDirectoryWapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT), base);
				}
			}
			property DataDirectoryWapper^ ComDescriptorEntry
			{
				DataDirectoryWapper^ get()
				{
					if (IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR >= structSize)
					{
						return nullptr;
					}
					return gcnew DataDirectoryWapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR), base);
				}
			}

		};


		// TODO: 在界面上判断是否32，绑定对应结构到按钮事件就行了
		// 非托管资源的地址不一样，所以只能分成2个类,不能合并
		[TypeConverter(ShowPropertiesConverter::typeid)]
		public ref class OptionalHeaderWapper32 :
			public PeStructWapper<IMAGE_OPTIONAL_HEADER32>,
			public IOptionalHeaderWapper
		{
		internal:
			// 通过 PeStructWapper 继承
			virtual PeStructWapperType & GetUnmanagedStruct() override;
		public:
			OptionalHeaderWapper32(PeImage^ pe);
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
			/*property OptionalMagic Magic
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
			};*/
			property UnmanagedValue<BYTE>^ MajorLinkerVersion
			{
				UnmanagedValue<BYTE>^ get()
				{
					return gcnew UnmanagedValue<BYTE>(IntPtr(&GetUnmanagedStruct().MajorLinkerVersion), GetPeBase());
				}
			};
			property UnmanagedValue<BYTE>^ MinorLinkerVersion
			{
				UnmanagedValue<BYTE>^ get()
				{
					return gcnew UnmanagedValue<BYTE>(IntPtr(&GetUnmanagedStruct().MinorLinkerVersion), GetPeBase());
				}
			};
			property UnmanagedValue<DWORD>^ SizeOfCode
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfCode), GetPeBase());
				}
			};
			property UnmanagedValue<DWORD>^ SizeOfInitializedData
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfInitializedData), GetPeBase());
				}
			};
			property UnmanagedValue<DWORD>^ SizeOfUninitializedData
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfUninitializedData), GetPeBase());
				}
			};
			property UnmanagedValue<DWORD>^ AddressOfEntryPoint
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().AddressOfEntryPoint), GetPeBase());
				}
			};
			property UnmanagedValue<DWORD>^ BaseOfCode
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().BaseOfCode), GetPeBase());
				}
			};
			property UnmanagedValue<DWORD>^ BaseOfData
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().BaseOfData), GetPeBase());
				}
			};
			property UnmanagedValue<DWORD>^ ImageBase
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().ImageBase), GetPeBase());
				}
			};
			property UnmanagedValue<DWORD>^ SectionAlignment
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SectionAlignment), GetPeBase());
				}
			};
			property UnmanagedValue<DWORD>^ FileAlignment
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().FileAlignment), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ MajorOperatingSystemVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MajorOperatingSystemVersion), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ MinorOperatingSystemVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MinorOperatingSystemVersion), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ MajorImageVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MajorImageVersion), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ MinorImageVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MinorImageVersion), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ MajorSubsystemVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MajorSubsystemVersion), GetPeBase());
				}
			};
			property UnmanagedValue<WORD>^ MinorSubsystemVersion
			{
				UnmanagedValue<WORD>^ get()
				{
					return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().MinorSubsystemVersion), GetPeBase());
				}
			};
			property UnmanagedValue<DWORD>^ Win32VersionValue
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().Win32VersionValue), GetPeBase());
				}
			};
			property UnmanagedValue<DWORD>^ SizeOfImage
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfImage), GetPeBase());
				}
			};
			property UnmanagedValue<DWORD>^ SizeOfHeaders
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfHeaders), GetPeBase());
				}
			};
			property UnmanagedValue<DWORD>^ CheckSum
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().CheckSum), GetPeBase());
				}
			};
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
			property UnmanagedValue<DWORD>^ SizeOfStackReserve
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfStackReserve), GetPeBase());
				}
			};
			property UnmanagedValue<DWORD>^ SizeOfStackCommit
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfStackCommit), GetPeBase());
				}
			};
			property UnmanagedValue<DWORD>^ SizeOfHeapReserve
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfHeapReserve), GetPeBase());
				}
			};
			property UnmanagedValue<DWORD>^ SizeOfHeapCommit
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().SizeOfHeapCommit), GetPeBase());
				}
			};
			property UnmanagedValue<DWORD>^ LoaderFlags
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().LoaderFlags), GetPeBase());
				}
			};
			property UnmanagedValue<DWORD>^ NumberOfRvaAndSizes
			{
				UnmanagedValue<DWORD>^ get()
				{
					return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().NumberOfRvaAndSizes), GetPeBase());
				}
			};
			[DisplayNameAttribute("Data Directories")]
			property DataDirectoriesWapper^ DataDirectories
			{
				DataDirectoriesWapper^ get()
				{
					return gcnew DataDirectoriesWapper(GetUnmanagedStruct().DataDirectory, GetPeBase(), GetUnmanagedStruct().NumberOfRvaAndSizes);
				}
			};

		};

		[TypeConverter(ShowPropertiesConverter::typeid)]
		public ref class OptionalHeaderWapper64 :
			public PeStructWapper<IMAGE_OPTIONAL_HEADER64>,
			public IOptionalHeaderWapper
		{
		internal:
			virtual PeStructWapperType & GetUnmanagedStruct() override;

		public:
			OptionalHeaderWapper64(PeImage^ pe);
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
			property DataDirectoriesWapper^ DataDirectories
			{
				DataDirectoriesWapper^ get()
				{
					return gcnew DataDirectoriesWapper(GetUnmanagedStruct().DataDirectory, GetPeBase(), GetUnmanagedStruct().NumberOfRvaAndSizes);
				}
			};

		};


	}
}