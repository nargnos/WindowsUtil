
#include "NtHeaderWapper.h"
#include "..\PeImage.h"
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		inline bool NtHeaderWapper::Is32PE()
		{
			return pe->HasNtHeader32;
		}
		NtHeaderWapper::NtHeaderWapper(PeImage ^ pe) :PeStructWapperBase(pe)
		{
			fileHeader = nullptr;
			optionalHeader = nullptr;
			SetDescription(IntPtr(pe->GetPeDecoder()->GetNtHeader->GetNtHeader32()),pe->BaseAddress, 0);
		}
		NtHeaderWapper::PeStructWapperType & NtHeaderWapper::GetUnmanagedStruct()
		{
			return pe->GetPeDecoder()->GetNtHeader;
		}
		
	}
}