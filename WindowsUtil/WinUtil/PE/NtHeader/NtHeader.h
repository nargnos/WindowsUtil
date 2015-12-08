#pragma once
#include "../Common/Common.h"
namespace PE
{
	template<typename _PeDecoder>
	class NtHeader :
		public PeStruct<_PeDecoder>,
		public InitStruct
	{
		PVOID ntHeader;
		PIMAGE_DATA_DIRECTORY imageDataDirectoryEntry;
		PDWORD imageDataDirectorySize;
		bool hasNtHeader32;
	public:
		friend _PeDecoder;
		NtHeader(_PeDecoder& pe) :PeStructBase(pe)
		{
			ntHeader = reinterpret_cast<PBYTE>(peDecoder.GetBase()) + peDecoder.GetDosHeader()->GetValue()->e_lfanew;
			hasNtHeader32 = false;
		}
		~NtHeader() {}
		inline bool VerifyNtSignature()
		{
			return GetNtHeader32()->Signature == IMAGE_NT_SIGNATURE;
		}
		inline const PIMAGE_NT_HEADERS32 GetNtHeader32()
		{
			return reinterpret_cast<PIMAGE_NT_HEADERS32>(ntHeader);
		}
		inline const PIMAGE_NT_HEADERS64 GetNtHeader64()
		{
			return reinterpret_cast<PIMAGE_NT_HEADERS64>(ntHeader);
		}

		// IMAGE_ROM_OPTIONAL_HDR_MAGIC类型返回false（没写解析代码）
		virtual bool InitFunc() override
		{
			switch (GetNtHeader32()->OptionalHeader.Magic)
			{
			case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
				hasNtHeader32 = false;
				imageDataDirectoryEntry = GetNtHeader64()->OptionalHeader.DataDirectory;
				imageDataDirectorySize = &GetNtHeader64()->OptionalHeader.NumberOfRvaAndSizes;
				return true;
			case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
				hasNtHeader32 = true;
				imageDataDirectoryEntry = GetNtHeader32()->OptionalHeader.DataDirectory;
				imageDataDirectorySize = &GetNtHeader32()->OptionalHeader.NumberOfRvaAndSizes;
				return true;
			
			default:
				break;
			}
			return false;
		}
		inline bool HasNtHeader32()
		{
			return hasNtHeader32;
		}
		inline const PIMAGE_DATA_DIRECTORY GetImageDataDirectoryEntry()
		{
			return	imageDataDirectoryEntry;
		}
		inline const PDWORD GetImageDataDirectorySize()
		{
			return imageDataDirectorySize;
		}
	};

}