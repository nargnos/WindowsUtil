#pragma once
#include "..\stdafx.h"
#include "DosHeader\DosHeaderWapper.h"
#include "NtHeader\NtHeaderWapper.h"
#include "Section\SectionWapper.h"
#include "Export\ExportWapper.h"
#include "Import\ImportWapper.h"
namespace NAMESPACE {
	namespace PeDecoderWapper
	{


		[TypeConverter(ShowPropertiesConverter::typeid)]
		public ref class PeImage :
			public IDescription,
			public IPropertiesFilter
		{
			::PE::PeDecoder* pe;

			static array<String^>^ sortList;

			DosHeaderWapper^ dosHeader;
			NtHeaderWapper^ ntHeader;
			UnmanagedByteArray^ dosStub;
			SectionHeaderArrayWapper^ sectionHeaders;
			ExportWapper^ exportWapper;
			ImportDescriptorArrayWapper^ import;
			void OnPeAttached();
			void OnReset()
			{
				dosHeader = nullptr;
				ntHeader = nullptr;
				dosStub = nullptr;
				sectionHeaders = nullptr;
				exportWapper = nullptr;
				import = nullptr;
			}
		protected:

			/*void AddResetEvent(IReset^ obj)
			{
				Reset += gcnew Action(obj, &IReset::Reset);
			}*/
			//event Action^ Reset;
		public:
			event Action^ PeAttached;
			bool Attach(IntPtr pe, bool isMapped);
			bool Attach(PVOID pe, bool isMapped);
			void Dettach()
			{
				OnReset();
				pe->Dettach();
			}
			PeImage()
			{
				pe = new ::PE::PeDecoder();
			}
			~PeImage()
			{
				this->!PeImage();
			}
			!PeImage()
			{
				if (pe)
				{
					delete pe;
					pe = NULL;
				}
			}
			virtual String ^ GetDescription();
			virtual array<String^>^ GetSortList();
			::PE::PeDecoder* GetPeDecoder()
			{
				return pe;
			}
			[BrowsableAttribute(false)]
			property bool IsAttached
			{
				bool get()
				{
					return pe->IsAttached();
				}
			}
			[BrowsableAttribute(false)]
			property IntPtr BaseAddress
			{
				IntPtr get()
				{
					return IntPtr(pe->GetBase());
				}
			}
			[BrowsableAttribute(false)]
			property bool IsMapped
			{
				bool get()
				{
					return pe->IsMapped();
				}
			}
			[DisplayNameAttribute("Is32PE")]
			property bool HasNtHeader32
			{
				bool get()
				{
					return pe->HasNtHeader32();
				}
			}
			[BrowsableAttribute(false)]
			property bool IsPE
			{
				bool get()
				{
					return pe->IsPE();
				}
			}
			
			[DisplayNameAttribute("Dos Header")]
			property DosHeaderWapper^ DosHeader
			{
				DosHeaderWapper^ get()
				{
					if (dosHeader == nullptr)
					{
						dosHeader = gcnew DosHeaderWapper(this);
					}
					return dosHeader;
				}
			}
			[DisplayNameAttribute("Dos Stub")]
			property UnmanagedByteArray^ DosStub //
			{
				UnmanagedByteArray^ get()
				{
					if (dosStub == nullptr)
					{
						auto lfanew = &(pe->GetDosHeader->GetValue()->e_lfanew);
						auto ptr = IntPtr(lfanew);
						ptr += sizeof(*lfanew);
						auto dosStubSize = *lfanew - sizeof(IMAGE_DOS_HEADER);
						dosStub = gcnew UnmanagedByteArray(ptr,BaseAddress, dosStubSize);
					}
					return dosStub;
				}
			};
			[DisplayNameAttribute("Nt Headers")]
			property NtHeaderWapper^ NtHeader
			{
				NtHeaderWapper^ get()
				{
					if (ntHeader == nullptr)
					{
						ntHeader = gcnew NtHeaderWapper(this);
					}
					return ntHeader;
				}
			}
			[DisplayNameAttribute("Section Headers")]
			property SectionHeaderArrayWapper^ SectionHeaders
			{
				SectionHeaderArrayWapper^ get()
				{
					if (sectionHeaders == nullptr)
					{
						sectionHeaders = gcnew SectionHeaderArrayWapper(this);
					}
					return sectionHeaders;
				}
			}
			
			[DisplayNameAttribute("Export Directory")]
			property ExportWapper^ Export
			{
				ExportWapper^ get()
				{
					if (exportWapper == nullptr)
					{
						if (pe->GetExport->IsExist())
						{
							exportWapper = gcnew ExportWapper(this);
						}
					}
					return exportWapper;
				}
			}

			[DisplayNameAttribute("Import Directory")]
				property ImportDescriptorArrayWapper^ Import
			{
				ImportDescriptorArrayWapper^ get()
				{
					if (import == nullptr)
					{
						if (pe->GetImport->IsExist())
						{
							import = gcnew ImportDescriptorArrayWapper(this);
						}
					}
					return import;
				}
			}

			// Í¨¹ý IPropertiesFilter ¼Ì³Ð
			virtual List<String^>^ GetHidePropList();
			/*

			void GetSection();
			void GetReloc();
			void GetExport();
			void GetImport();
			void GetResource();
			void GetException();
			void GetSecurity();
			void GetDebug();
			void GetArchitecture();
			void GetGlobalptr();
			void GetTls();
			void GetLoadConfig();
			void GetBoundImport();
			void GetIat();
			void GetDelayImport();
			void GetComDescriptor();
			*/
		};
	}
}