#pragma once
#include <Windows.h>
#include <array>
namespace PeDecoder
{
	namespace Detail
	{
		#define ALIGN_UP(value, alignment) (((UINT)value + (UINT)alignment - 1)& ~((UINT)alignment - 1))
		enum class SectionCharacteristics :unsigned long
		{
			Align1024Bytes = IMAGE_SCN_ALIGN_1024BYTES,
			Align128Bytes = IMAGE_SCN_ALIGN_128BYTES,
			Align16Bytes = IMAGE_SCN_ALIGN_16BYTES,
			Align1Bytes = IMAGE_SCN_ALIGN_1BYTES,
			Align2048Bytes = IMAGE_SCN_ALIGN_2048BYTES,
			Align256Bytes = IMAGE_SCN_ALIGN_256BYTES,
			Align2Bytes = IMAGE_SCN_ALIGN_2BYTES,
			Align32Bytes = IMAGE_SCN_ALIGN_32BYTES,
			Align4096Bytes = IMAGE_SCN_ALIGN_4096BYTES,
			Align4Bytes = IMAGE_SCN_ALIGN_4BYTES,
			Align512Bytes = IMAGE_SCN_ALIGN_512BYTES,
			Align64Bytes = IMAGE_SCN_ALIGN_64BYTES,
			Align8192Bytes = IMAGE_SCN_ALIGN_8192BYTES,
			Align8Bytes = IMAGE_SCN_ALIGN_8BYTES,
			AlignMask = IMAGE_SCN_ALIGN_MASK,
			CntCode = IMAGE_SCN_CNT_CODE,
			CntInitializedData = IMAGE_SCN_CNT_INITIALIZED_DATA,
			CntUninitializedData = IMAGE_SCN_CNT_UNINITIALIZED_DATA,
			Gprel = IMAGE_SCN_GPREL,
			LnkComdat = IMAGE_SCN_LNK_COMDAT,
			LnkInfo = IMAGE_SCN_LNK_INFO,
			LnkNrelocOvfl = IMAGE_SCN_LNK_NRELOC_OVFL,
			LnkOther = IMAGE_SCN_LNK_OTHER,
			LnkRemove = IMAGE_SCN_LNK_REMOVE,
			Mem16bit = IMAGE_SCN_MEM_16BIT,
			MemDiscardable = IMAGE_SCN_MEM_DISCARDABLE,
			MemExecute = IMAGE_SCN_MEM_EXECUTE,
			MemFardata = IMAGE_SCN_MEM_FARDATA,
			MemLocked = IMAGE_SCN_MEM_LOCKED,
			MemNotCached = IMAGE_SCN_MEM_NOT_CACHED,
			MemNotPaged = IMAGE_SCN_MEM_NOT_PAGED,
			MemPreload = IMAGE_SCN_MEM_PRELOAD,
			MemPurgeable = IMAGE_SCN_MEM_PURGEABLE,
			MemRead = IMAGE_SCN_MEM_READ,
			MemShared = IMAGE_SCN_MEM_SHARED,
			MemWrite = IMAGE_SCN_MEM_WRITE,
			NoDeferSpecExc = IMAGE_SCN_NO_DEFER_SPEC_EXC,
			TypeNoPad = IMAGE_SCN_TYPE_NO_PAD,
		};
		struct Section :
			public IMAGE_SECTION_HEADER
		{
			constexpr static int Size = IMAGE_SIZEOF_SECTION_HEADER;
			constexpr static int NameSize = IMAGE_SIZEOF_SHORT_NAME;

			_STD array<BYTE, Size>& GetNameArray() const;
			SectionCharacteristics GetCharacteristics() const;
			bool RvaInRange(DWORD rva, DWORD sectionAlignment) const;
			bool OffsetInRange(DWORD fileOffset, DWORD sectionAlignment) const;
		};
	}  // namespace Detail

}  // namespace PeDecoder
