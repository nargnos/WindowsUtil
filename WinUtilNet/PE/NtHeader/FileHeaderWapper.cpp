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

		FileHeaderWapper::FileHeaderWapper(PeImage ^ pe) :PeStructWapperBase(pe)
		{
			SetDescription(IntPtr(&pe->GetPeDecoder()->GetNtHeader->GetNtHeader32()->FileHeader), GetPeBase(),sizeof(IMAGE_FILE_HEADER));
		}

	}
}