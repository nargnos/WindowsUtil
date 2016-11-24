#pragma once
#include <Windows.h>
#include <memory>
#include "ISectionHeaders.h"
#include "IDosHeader.h"
#include "INtHeader.h"
namespace PeDecoder
{
	class PeImage;
	class HeaderFactory
	{
	public:
		static _STD unique_ptr<ISectionHeaders> CreateSectionHeadersInstance(const PeImage& pe);
		static _STD unique_ptr<INtHeader> CreateNtHeaderInstance(const IDosHeader& dosHeader);
		static _STD unique_ptr<IDosHeader> CreateDosHeaderInstance(const PIMAGE_DOS_HEADER rawptr);
	private:
		HeaderFactory() = delete;

		~HeaderFactory() = delete;

	};

}  // namespace PeDecoder