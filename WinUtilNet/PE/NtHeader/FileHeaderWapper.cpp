#include "..\..\stdafx.h"
#include "..\PeImage.h"
#include "FileHeaderWapper.h"
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		FileHeaderWapper::PeStructWapperType & FileHeaderWapper::GetUnmanagedStruct()
		{
			return pe->NtHeader->GetUnmanagedStruct()->GetNtHeader32()->FileHeader;
		}

	}
}