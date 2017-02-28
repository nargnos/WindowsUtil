#pragma once
#include <Windows.h>
#include <memory>
#include "ISectionHeaders.h"
#include "IDosHeader.h"
#include "INtHeader.h"
namespace PeDecoder
{
	class PeImage;
	class NtHeaderFactory
	{
	public:
		static _STD unique_ptr<INtHeader> Create(const IDosHeader & dosHeader);
	private:
		NtHeaderFactory() = delete;

		~NtHeaderFactory() = delete;

	};

}  // namespace PeDecoder