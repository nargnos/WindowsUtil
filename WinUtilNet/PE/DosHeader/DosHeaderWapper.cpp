#include "DosHeaderWapper.h"
#include "..\PeImage.h"
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		DosHeaderWapper::PeStructWapperType & DosHeaderWapper::GetUnmanagedStruct()
		{
			return pe->GetPeDecoder()->GetDosHeader;
		}
		DosHeaderWapper::DosHeaderWapper(PeImage ^ pe) :PeStructWapperBase(pe)
		{
			SetDescription(GetPeBase(), GetPeBase(), sizeof(IMAGE_DOS_HEADER));
			e_res = nullptr;
			e_res2 = nullptr;
		}
	}
}