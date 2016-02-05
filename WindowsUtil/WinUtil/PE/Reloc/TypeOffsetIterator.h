#pragma once
#include "../Common/Common.h"
namespace PE
{
	class BaseRelocationIterator;
	class TypeOffsetIterator :
		public IIterator<PWORD>
	{
	public:
		explicit TypeOffsetIterator(BaseRelocationIterator& baseRelocationIterator);
		~TypeOffsetIterator();

		PWORD Current();
		bool Next();
		void Reset();
		WORD CurrentType();
		DWORD CurrentRelocRva();

		// 应用重定位使用的函数（读取时不需要）
		void ApplyCurrentReloc(PVOID oldBase, PVOID currentBase);

		static void RelocHighLow(PVOID oldBase, PVOID currentBase, DWORD relocRva);
		static void RelocLow(PVOID oldBase, PVOID currentBase, DWORD relocRva);
		static void RelocHigh(PVOID oldBase, PVOID currentBase, DWORD relocRva);
		static void RelocDir64(PVOID oldBase, PVOID currentBase, DWORD relocRva);
	private:
		DWORD virtualAddress;
		PWORD endTypeOffset;
		PWORD typeOffset;
		PWORD currentTypeOffset;

		PIMAGE_BASE_RELOCATION currentReloc;
		void Init(PIMAGE_BASE_RELOCATION reloc);

	};



}  // namespace PE
