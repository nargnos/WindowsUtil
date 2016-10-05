#include "stdafx.h"
#include "IPeImage.h"

PeDecoder::IPeImage::operator bool() const
{
	return IsPe();
}
