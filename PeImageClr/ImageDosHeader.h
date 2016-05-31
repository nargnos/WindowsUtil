#pragma once
#include "StructureDefineCommon.h"
#include "ShowPropertiesConverter.h"
namespace PeImageClr
{
	//[TypeConverter(ShowPropertiesConverter::typeid)]
	[StructLayout(LayoutKind::Sequential, Size = sizeof(IMAGE_FILE_HEADER))]
	public ref struct ImageDosHeader
	{
		WORD   e_magic;                     // Magic number
		WORD   e_cblp;                      // Bytes on last page of file
		WORD   e_cp;                        // Pages in file
		WORD   e_crlc;                      // Relocations
		WORD   e_cparhdr;                   // Size of header in paragraphs
		WORD   e_minalloc;                  // Minimum extra paragraphs needed
		WORD   e_maxalloc;                  // Maximum extra paragraphs needed
		WORD   e_ss;                        // Initial (relative) SS value
		WORD   e_sp;                        // Initial SP value
		WORD   e_csum;                      // Checksum
		WORD   e_ip;                        // Initial IP value
		WORD   e_cs;                        // Initial (relative) CS value
		WORD   e_lfarlc;                    // File address of relocation table
		WORD   e_ovno;                      // Overlay number
		[MarshalAs(UnmanagedType::ByValArray, SizeConst = 4)]
		array<WORD>^   e_res;                    // Reserved words
		WORD   e_oemid;                     // OEM identifier (for e_oeminfo)
		WORD   e_oeminfo;                   // OEM information; e_oemid specific
		[MarshalAs(UnmanagedType::ByValArray, SizeConst = 10)]
		array<WORD>^   e_res2;                  // Reserved words
		LONG   e_lfanew;                    // File address of new exe header
	};
}  // namespace PeImageClr
