#pragma once
#include "ShowPropertiesConverter.h"
#include "IDescription.h"
#include "IPropertiesFilter.h"
#include "ImageDosHeader.h"
#include "IGetData.h"
namespace PeImageClr
{
	[TypeConverter(ShowPropertiesConverter::typeid)]
	public ref class DosHeader :
		public IGetData<ImageDosHeader^>
	{
	public:
		DosHeader(PeDecoder::PeImage* pe);
		virtual property ImageDosHeader^ Data
		{
			ImageDosHeader^ get()
			{
				return data_;
			}
		}
	private:
		PeDecoder::PeImage* pe_;
		PeDecoder::DosHeader* dosHeader_;
		ImageDosHeader^ data_;
	};
}  // namespace PeImageClr
