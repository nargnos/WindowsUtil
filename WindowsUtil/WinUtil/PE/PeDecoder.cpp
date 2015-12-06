#include "PeDecoder.h"
#include "PeDecoder.h"
namespace PE
{
	bool PeDecoder::IsMapped()
	{
		return isMapped;
	}
	
	


	
	
	


	bool PeDecoder::LoadPEImage(PVOID base, bool isMapped)
	{
		isPE = false;
		
		if (!base)
		{
			return false;
		}
		
		this->base = reinterpret_cast<PBYTE>(base);
		this->isMapped = isMapped;
		// 载入头
		dosHeader = _STD make_shared<DosHeader<PeDecoder>>(*this);
		ntHeader = _STD make_shared<NtHeader<PeDecoder>>(*this);

		// 检查pe格式
		if (!dosHeader->VerifyDosSignature() ||!ntHeader->VerifyNtSignature())
		{
			return false;
		}
		// 初始化nt头
		if (!ntHeader->Init())
		{
			return false;
		}
		this->hasNtHeader32 = ntHeader->HasNtHeader32();
		section= _STD make_shared<SectionHeaders<PeDecoder>>(*this);
		if (!section->Init())
		{
			return false;
		}

		isPE = true;
		return true;
	}

	inline PVOID PeDecoder::GetBase()
	{
		return this->base;
	}

}