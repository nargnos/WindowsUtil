#pragma once
namespace PeImageClr
{
	[TypeConverter(ShowPropertiesConverter::typeid)]
	public ref class DataDirectoriesWrapper :
		public PeStructDescription
	{
		static array<String^>^ sortList;
	public:
		virtual array<String^>^ GetSortList() override
		{
			if (DataDirectoriesWrapper::sortList == nullptr)
			{
				DataDirectoriesWrapper::sortList = gcnew array<String^>
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
			return DataDirectoriesWrapper::sortList;
		}
		DataDirectoriesWrapper(PIMAGE_DATA_DIRECTORY entry, IntPtr basePtr, int size)
		{
			SetDescription(IntPtr(entry), basePtr, size * sizeof(IMAGE_DATA_DIRECTORY));
		}
		inline IntPtr GetDirectoryPointer(int index)
		{
			return IntPtr(&((PIMAGE_DATA_DIRECTORY)addr.ToPointer())[(int)index]);
		}
		~DataDirectoriesWrapper()
		{
		}
		property DataDirectoryWrapper^ ExportEntry
		{
			DataDirectoryWrapper^ get()
			{
				if (IMAGE_DIRECTORY_ENTRY_EXPORT >= structSize)
				{
					return nullptr;
				}
				return gcnew DataDirectoryWrapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_EXPORT), base);
			}
		}
		property DataDirectoryWrapper^ ImportEntry
		{
			DataDirectoryWrapper^ get()
			{
				if (IMAGE_DIRECTORY_ENTRY_IMPORT >= structSize)
				{
					return nullptr;
				}
				return gcnew DataDirectoryWrapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_IMPORT), base);
			}
		}
		property DataDirectoryWrapper^ ResourceEntry
		{
			DataDirectoryWrapper^ get()
			{
				if (IMAGE_DIRECTORY_ENTRY_RESOURCE >= structSize)
				{
					return nullptr;
				}
				return gcnew DataDirectoryWrapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_RESOURCE), base);
			}
		}
		property DataDirectoryWrapper^ ExceptionEntry
		{
			DataDirectoryWrapper^ get()
			{
				if (IMAGE_DIRECTORY_ENTRY_EXCEPTION >= structSize)
				{
					return nullptr;
				}
				return gcnew DataDirectoryWrapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_EXCEPTION), base);
			}
		}
		property DataDirectoryWrapper^ SecurityEntry
		{
			DataDirectoryWrapper^ get()
			{
				if (IMAGE_DIRECTORY_ENTRY_SECURITY >= structSize)
				{
					return nullptr;
				}
				return gcnew DataDirectoryWrapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_SECURITY), base);
			}
		}
		property DataDirectoryWrapper^ BaserelocEntry
		{
			DataDirectoryWrapper^ get()
			{
				if (IMAGE_DIRECTORY_ENTRY_BASERELOC >= structSize)
				{
					return nullptr;
				}
				return gcnew DataDirectoryWrapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_BASERELOC), base);
			}
		}
		property DataDirectoryWrapper^ DebugEntry
		{
			DataDirectoryWrapper^ get()
			{
				if (IMAGE_DIRECTORY_ENTRY_DEBUG >= structSize)
				{
					return nullptr;
				}
				return gcnew DataDirectoryWrapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_DEBUG), base);
			}
		}
		property DataDirectoryWrapper^ ArchitectureEntry
		{
			DataDirectoryWrapper^ get()
			{
				if (IMAGE_DIRECTORY_ENTRY_ARCHITECTURE >= structSize)
				{
					return nullptr;
				}
				return gcnew DataDirectoryWrapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_ARCHITECTURE), base);
			}
		}
		property DataDirectoryWrapper^ GlobalptrEntry
		{
			DataDirectoryWrapper^ get()
			{
				if (IMAGE_DIRECTORY_ENTRY_GLOBALPTR >= structSize)
				{
					return nullptr;
				}
				return gcnew DataDirectoryWrapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_GLOBALPTR), base);
			}
		}
		property DataDirectoryWrapper^ TlsEntry
		{
			DataDirectoryWrapper^ get()
			{
				if (IMAGE_DIRECTORY_ENTRY_TLS >= structSize)
				{
					return nullptr;
				}
				return gcnew DataDirectoryWrapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_TLS), base);
			}
		}
		property DataDirectoryWrapper^ LoadConfigEntry
		{
			DataDirectoryWrapper^ get()
			{
				if (IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG >= structSize)
				{
					return nullptr;
				}
				return gcnew DataDirectoryWrapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG), base);
			}
		}
		property DataDirectoryWrapper^ BoundImportEntry
		{
			DataDirectoryWrapper^ get()
			{
				if (IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT >= structSize)
				{
					return nullptr;
				}
				return gcnew DataDirectoryWrapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT), base);
			}
		}
		property DataDirectoryWrapper^ IatEntry
		{
			DataDirectoryWrapper^ get()
			{
				if (IMAGE_DIRECTORY_ENTRY_IAT >= structSize)
				{
					return nullptr;
				}
				return gcnew DataDirectoryWrapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_IAT), base);
			}
		}
		property DataDirectoryWrapper^ DelayImportEntry
		{
			DataDirectoryWrapper^ get()
			{
				if (IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT >= structSize)
				{
					return nullptr;
				}
				return gcnew DataDirectoryWrapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT), base);
			}
		}
		property DataDirectoryWrapper^ ComDescriptorEntry
		{
			DataDirectoryWrapper^ get()
			{
				if (IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR >= structSize)
				{
					return nullptr;
				}
				return gcnew DataDirectoryWrapper(GetDirectoryPointer(IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR), base);
			}
		}

	};
}  // namespace PeImageClr
