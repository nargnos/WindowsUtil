#include "..\..\stdafx.h"
#include "ExportWapper.h"
#include "..\PeImage.h"
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		inline ExportWapper::PeStructWapperType & ExportWapper::GetUnmanagedStruct()
		{
			return pe->GetPeDecoder()->GetExport;
		}
	}
}