#pragma once
#include "../Common/Common.h"
namespace PE
{

	class DosHeader :public IGetValue<PIMAGE_DOS_HEADER>, public PeStruct
	{
		PIMAGE_DOS_HEADER  dosHeader;
	public:
		friend class PeDecoder;
		explicit DosHeader(PeDecoder* pe);
		~DosHeader();
		bool VerifyDosSignature();
		virtual PIMAGE_DOS_HEADER GetValue() override;

	};


}  // namespace PE
