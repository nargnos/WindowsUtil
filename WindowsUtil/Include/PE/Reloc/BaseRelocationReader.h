#pragma once
#include "..\PeDecoder.h"
namespace PE
{
	namespace Reloc
	{
		class BaseRelocationReader
		{
		public:
			BaseRelocationReader(PIMAGE_BASE_RELOCATION reloc, DWORD relocSize);
			BaseRelocationReader(PeDecoder& pe);
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
}