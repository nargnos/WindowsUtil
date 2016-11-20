#pragma once

namespace PeDecoder
{
	class TypeOffset
	{
	public:
		friend class TypeOffsetIterator;
		TypeOffset(PIMAGE_BASE_RELOCATION baseReloc, PWORD ptr);
		PWORD GetPtr() const;
		WORD CurrentType();

		DWORD CurrentRelocRva();

		// 下面函数会修改pe, 未完成, 不要用
		void ApplyCurrentReloc(PVOID oldBase, PVOID currentBase);
		
	protected:
		static void RelocHighLow(PVOID oldBase, PVOID currentBase, DWORD relocRva);

		static void RelocLow(PVOID oldBase, PVOID currentBase, DWORD relocRva);

		static void RelocHigh(PVOID oldBase, PVOID currentBase, DWORD relocRva);

		static void RelocDir64(PVOID oldBase, PVOID currentBase, DWORD relocRva);

		PIMAGE_BASE_RELOCATION baseReloc_;
		PWORD ptr_;
	};
}  // namespace PeDecoder
