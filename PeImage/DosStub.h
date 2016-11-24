#pragma once
#include <Windows.h>
namespace PeDecoder
{
	class PeImage;
	class DosStub
	{
	public:
		typedef unsigned char* iterator;
		explicit DosStub(const PeImage& pe);
		bool IsExist() const;
		explicit operator bool() const;
		DWORD GetSize() const;
		iterator begin() const;
		iterator end() const;
		virtual ~DosStub();
	protected:
		unsigned char* ptr_;
		DWORD size_;
	};
}  // namespace PeDecoder
