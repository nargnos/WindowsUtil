#include "..\..\stdafx.h"
#include "..\PeImage.h"
#include "OptionalHeaderWapper.h"

namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		OptionalHeaderWapper32::PeStructWapperType & OptionalHeaderWapper32::GetUnmanagedStruct()
		{
			return pe->UnmanagedObject()->GetNtHeader->GetNtHeader32()->OptionalHeader;
		}
		OptionalHeaderWapper64::PeStructWapperType & OptionalHeaderWapper64::GetUnmanagedStruct()
		{
			return pe->UnmanagedObject()->GetNtHeader->GetNtHeader64()->OptionalHeader;
		}
	}
}