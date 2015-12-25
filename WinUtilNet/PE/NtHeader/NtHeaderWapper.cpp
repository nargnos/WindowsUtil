
#include "NtHeaderWapper.h"
#include "..\PeImage.h"
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		inline bool NtHeaderWapper::Is32PE()
		{
			return pe->HasNtHeader32;
		}
		NtHeaderWapper::PeStructWapperType & NtHeaderWapper::GetUnmanagedStruct()
		{
			return pe->UnmanagedObject()->GetNtHeader;
		}
	}
}