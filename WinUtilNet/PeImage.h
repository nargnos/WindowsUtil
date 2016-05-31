#pragma once
#include "DosHeaderWrapper.h"
#include "NtHeaderWrapper.h"
#include "SectionWrapper.h"
#include "ExportWrapper.h"
#include "ImportWrapper.h"
namespace NAMESPACE {
	namespace PeDecoderWrapper
	{
		[TypeConverter(ShowPropertiesConverter::typeid)]
		public ref class PeImage :
			public IDescription,
			public IPropertiesFilter
		{
			::::PeDecoder* pe;

			

			DosHeaderWrapper^ dosHeader;
			NtHeaderWrapper^ ntHeader;
			UnmanagedByteArray^ dosStub;
			SectionHeaderArrayWrapper^ sectionHeaders;
			ExportWrapper^ exportWrapper;
			ImportDescriptorArrayWrapper^ import;
			void OnPeAttached()
			{
				PeAttached();
			}
			void OnReset()
			{
				dosHeader = nullptr;
				ntHeader = nullptr;
				dosStub = nullptr;
				sectionHeaders = nullptr;
				exportWrapper = nullptr;
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
			bool Attach(IntPtr pe, bool isMapped)
			{
				return Attach(pePtr.ToPointer(), isMapped);
			}
			bool Attach(PVOID pe, bool isMapped)
			{
				auto result = pe->Attach(pePtr, isMapped);
				if (result)
				{
					OnReset();
					OnPeAttached();
				}
				return result;
			}
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
			
			
			
			[BrowsableAttribute(false)]
			property bool IsAttached
			{
				bool get()
				{
					return pe->IsAttached();
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
			property DosHeaderWrapper^ DosHeader
			{
				DosHeaderWrapper^ get()
				{
					if (dosHeader == nullptr)
					{
						dosHeader = gcnew DosHeaderWrapper(this);
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
			property NtHeaderWrapper^ NtHeader
			{
				NtHeaderWrapper^ get()
				{
					if (ntHeader == nullptr)
					{
						ntHeader = gcnew NtHeaderWrapper(this);
					}
					return ntHeader;
				}
			}
			[DisplayNameAttribute("Section Headers")]
			property SectionHeaderArrayWrapper^ SectionHeaders
			{
				SectionHeaderArrayWrapper^ get()
				{
					if (sectionHeaders == nullptr)
					{
						sectionHeaders = gcnew SectionHeaderArrayWrapper(this);
					}
					return sectionHeaders;
				}
			}
			
			

			// Í¨¹ý IPropertiesFilter ¼Ì³Ð
			
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