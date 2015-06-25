#pragma once
#include "PeDecoder.h"
namespace PE
{
	class BaseRelocationReader
	{
	public:
		BaseRelocationReader(PIMAGE_BASE_RELOCATION reloc, DWORD relocSize);
		~BaseRelocationReader();
		bool Next();
		PIMAGE_BASE_RELOCATION Current();
		void Reset();
	private:
		PIMAGE_BASE_RELOCATION reloc;
		PIMAGE_BASE_RELOCATION currentReloc;
		PIMAGE_BASE_RELOCATION endReloc;
	};

	

	
}