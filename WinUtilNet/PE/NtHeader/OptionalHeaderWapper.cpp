#include "..\..\stdafx.h"
#include "..\PeImage.h"
#include "OptionalHeaderWapper.h"

namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		
		OptionalHeaderWapper32::PeStructWapperType & OptionalHeaderWapper32::GetUnmanagedStruct()
		{
			return pe->GetPeDecoder()->GetNtHeader->GetNtHeader32()->OptionalHeader;
		}
		OptionalHeaderWapper32::OptionalHeaderWapper32(PeImage ^ pe) :PeStructWapperBase(pe)
		{
			SetDescription(IntPtr(&pe->GetPeDecoder()->GetNtHeader->GetNtHeader32()->OptionalHeader), GetPeBase(),sizeof(IMAGE_OPTIONAL_HEADER32));
		}
		OptionalHeaderWapper64::PeStructWapperType & OptionalHeaderWapper64::GetUnmanagedStruct()
		{
			return pe->GetPeDecoder()->GetNtHeader->GetNtHeader64()->OptionalHeader;
		}
		OptionalHeaderWapper64::OptionalHeaderWapper64(PeImage ^ pe) :PeStructWapperBase(pe)
		{
			SetDescription(IntPtr(&pe->GetPeDecoder()->GetNtHeader->GetNtHeader64()->OptionalHeader), GetPeBase(), sizeof(IMAGE_OPTIONAL_HEADER64));
		}
		
	}
}