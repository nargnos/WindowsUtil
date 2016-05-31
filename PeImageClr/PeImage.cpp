
#include "stdafx.h"

#include "PeImage.h"
#include "ImageDosHeader.h"
namespace PeImageClr
{
	PeImage::PeImage(IntPtr ^ pe, bool isMapped) :
		PeImage(pe->ToPointer(), isMapped)
	{
		ImageDosHeader k;
		cli::array<int>^ kl;
		kl[0];
	}
}  // namespace PeImageClr
