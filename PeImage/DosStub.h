#pragma once
#include <Windows.h>
namespace PeDecoder
{
	class DosHeader;
	class NtHeader;
	class DosStub
	{
	public:
		typedef unsigned char* iterator;
		DosStub(const DosHeader& dos, const NtHeader& nt);
		DWORD GetSize() const;
		iterator begin() const;
		iterator end() const;
	protected:
		unsigned char* ptr_;
		DWORD size_;
	};
}  // namespace PeDecoder
