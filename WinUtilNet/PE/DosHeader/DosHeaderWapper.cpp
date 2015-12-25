#include "DosHeaderWapper.h"
#include "..\PeImage.h"
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		void DosHeaderWapper::Reset()
		{
			e_res = nullptr;
			e_res2 = nullptr;
		}
		DosHeaderWapper::PeStructWapperType & DosHeaderWapper::GetUnmanagedStruct()
		{
			return pe->UnmanagedObject()->GetDosHeader;
		}
	}
}