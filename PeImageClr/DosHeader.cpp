#include "stdafx.h"
#include "DosHeader.h"
#include "Unmanaged.h"
#include "StructureDefineCommon.h"
namespace PeImageClr
{
	DosHeader::DosHeader(PeDecoder::PeImage* pe):
		pe_(pe),
		dosHeader_(pe->GetDosHeader().get())
	{
		data_ = Unmanaged::PtrToStructure<ImageDosHeader^>(IntPtr(dosHeader_->GetPtr()));
	}
}  // namespace PeImageClr
