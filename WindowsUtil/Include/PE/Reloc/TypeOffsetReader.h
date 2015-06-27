#pragma once
#include "BaseRelocationReader.h"
namespace PE
{
	namespace Reloc
	{
		class TypeOffsetReader
		{
		public:
			TypeOffsetReader();
			TypeOffsetReader(PIMAGE_BASE_RELOCATION reloc);
			~TypeOffsetReader();
			void Init(PIMAGE_BASE_RELOCATION reloc);
			PWORD Current();
			bool Next();
			void Reset();
			WORD CurrentType();
			DWORD CurrentRelocRva();
			void ApplyCurrentReloc(PVOID oldBase, PVOID currentBase);// 当程序已经映射完毕后不要使用

		private:
			DWORD virtualAddress;
			PWORD endTypeOffset;
			PWORD typeOffset;
			PWORD currentTypeOffset;
		};
		void RelocHighLow(PVOID oldBase, PVOID currentBase, DWORD relocRva);
		void RelocLow(PVOID oldBase, PVOID currentBase, DWORD relocRva);
		void RelocHigh(PVOID oldBase, PVOID currentBase, DWORD relocRva);
		void RelocDir64(PVOID oldBase, PVOID currentBase, DWORD relocRva);
	}

}