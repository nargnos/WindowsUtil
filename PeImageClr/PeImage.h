// PeImageClr.h

#pragma once
#include "ShowPropertiesConverter.h"
#include "IDescription.h"
#include "IPropertiesFilter.h"
#include "DosHeader.h"
#include "StructureDefineCommon.h"
using namespace System;

namespace PeImageClr
{
	//[TypeConverter(ShowPropertiesConverter::typeid)]
	public ref class PeImage
	{
	public:
		PeImage(IntPtr^ pe, bool isMapped);
		PeImage(void* pe, bool isMapped) :
			pe_(new PeDecoder::PeImage(pe, isMapped))
		{
			dosHeader_ = gcnew Lazy<PeImageClr::DosHeader^>(
				gcnew Func<PeImageClr::DosHeader^>(this,&PeImage::CreatePeStructure<PeImageClr::DosHeader>),
				true);

		}
		~PeImage()
		{
			pe_->~PeImage();
		}
		!PeImage()
		{
			delete pe_;
		}
		property PeDecoder::ImageType ImageType
		{
			PeDecoder::ImageType get()
			{
				return pe_->GetImageType();
			}
		}
		property DosHeader^ DosHeader
		{
			PeImageClr::DosHeader^ get()
			{
				return dosHeader_->Value;
			}
		}

	

	protected:
		template<typename T>
		T^ CreatePeStructure()
		{
			return gcnew T(pe_);
		}

		PeDecoder::PeImage* pe_;
		Lazy<PeImageClr::DosHeader^>^ dosHeader_;

	};
}  // namespace PeImageClr
