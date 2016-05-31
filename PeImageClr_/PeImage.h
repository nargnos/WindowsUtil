// PeImageClr.h
#pragma once
#include "ShowPropertiesConverter.h"
#include "IPropertiesFilter.h"
#include "IDescription.h"
namespace PeImageClr
{
	using namespace System::Collections;
	using namespace System::ComponentModel;
	using namespace System;
	[TypeConverter(ShowPropertiesConverter::typeid)]
	ref class PeImage :
		public IDescription,
		public IPropertiesFilter
	{
	public:

		PeImage(IntPtr^ ptr, bool isMapped);
		~PeImage();
		!PeImage();
		PeDecoder::PeImage& GetPeDecoder();
		virtual String ^ GetDescription();
		virtual array<String^>^ GetSortList();
		virtual List<String^>^ GetHidePropList();
		[BrowsableAttribute(false)]
		property IntPtr BaseAddress
		{
			IntPtr get()
			{
				return IntPtr(pe_->GetBase());
			}
		}
		/*[DisplayNameAttribute("Export Directory")]
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
	}*/
	protected:
		static array<String^>^ sortList;
		PeDecoder::PeImage* pe_;
	};

}

