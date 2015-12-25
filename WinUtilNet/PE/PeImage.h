#pragma once
#include "..\stdafx.h"
#include "DosHeader\DosHeaderWapper.h"
#include "NtHeader\NtHeaderWapper.h"
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		[TypeConverter(PeImageConverter::typeid)]
		public ref class PeImage :public UnmanagedWapper<::PE::PeDecoder>
		{
			DosHeaderWapper^ dosHeader; 
			NtHeaderWapper^ ntHeader;
			void OnPeLoaded();
		protected:
			virtual ::PE::PeDecoder * GetData() override;
			
			void AddResetEvent(IReset^ obj)
			{
				PeLoaded += gcnew Action(obj, &IReset::Reset);
			}
		public:
			PeImage();
			event Action^ PeLoaded;
			bool LoadPEImage(IntPtr pe, bool isMapped);

			[TypeConverter(ValueConverter::typeid)]
			property IntPtr BaseAddress
			{
				IntPtr get()
				{
					return IntPtr(UnmanagedObject()->GetBase());
				}
			}
			property bool IsMapped
			{
				bool get()
				{
					return UnmanagedObject()->IsMapped();
				}
			}
			[DisplayNameAttribute("Is32PE")]
			property bool HasNtHeader32
			{
				bool get()
				{
					return UnmanagedObject()->HasNtHeader32();
				}
			}
			[BrowsableAttribute(false)]
			property bool IsPE
			{
				bool get()
				{
					return UnmanagedObject()->IsPE();
				}
			}
			//[BrowsableAttribute(false)]
			property DosHeaderWapper^ DosHeader
			{
				DosHeaderWapper^ get()
				{
					if (dosHeader==nullptr)
					{
						dosHeader = gcnew DosHeaderWapper(this);
						AddResetEvent(dosHeader);
					}
					return dosHeader;
				}
			}
			
			property NtHeaderWapper^ NtHeader
			{
				NtHeaderWapper^ get()
				{
					if (ntHeader == nullptr)
					{
						ntHeader = gcnew NtHeaderWapper(this);
						AddResetEvent(ntHeader);
					}
					return ntHeader;
				}
			}
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