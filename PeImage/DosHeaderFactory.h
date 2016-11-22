#pragma once
#include <memory>
#include "IDosHeader.h"
namespace PeDecoder
{

	class DosHeaderFactory final
	{
	public:
		static _STD unique_ptr<IDosHeader> CreateDosHeaderInstance(const PIMAGE_DOS_HEADER rawptr);
	private:
		DosHeaderFactory() = delete;

		~DosHeaderFactory() = delete;

	};

}