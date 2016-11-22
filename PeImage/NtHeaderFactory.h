#pragma once
#include <memory>
#include "IDosHeader.h"
#include "INtHeader.h"
namespace PeDecoder
{
	class NtHeaderFactory final
	{
	public:
		static _STD unique_ptr<INtHeader> CreateNtHeaderInstance(const IDosHeader& dosHeader);
	private:
		NtHeaderFactory() = delete;

		~NtHeaderFactory() = delete;
	};
}
