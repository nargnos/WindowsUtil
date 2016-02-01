#pragma once
#include "../Common/Common.h"
namespace PE
{
	
	class NtHeader :
		public PeStruct,
		public InitStruct
	{
		PVOID ntHeader;
		PIMAGE_DATA_DIRECTORY imageDataDirectoryEntry;
		PDWORD imageDataDirectorySize;
		bool hasNtHeader32;
	public:
		friend class PeDecoder;
		explicit NtHeader(PeDecoder& pe);
		~NtHeader();
		 bool VerifyNtSignature();
		 const PIMAGE_NT_HEADERS32 GetNtHeader32();
		 const PIMAGE_NT_HEADERS64 GetNtHeader64();

		// IMAGE_ROM_OPTIONAL_HDR_MAGIC类型返回false（没写解析代码）
		virtual bool InitFunc() override;
		 bool HasNtHeader32();
		 const PIMAGE_DATA_DIRECTORY GetImageDataDirectoryEntry();
		 const PDWORD GetImageDataDirectorySize();
	};

}