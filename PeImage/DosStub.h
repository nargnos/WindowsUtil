#pragma once
#include <Windows.h>
#include <memory>
#include "IPeImage.h"
namespace PeDecoder
{
	class DosStub
	{
	public:
		typedef unsigned char* iterator;
		explicit DosStub(const _STD shared_ptr<IPeImage>& pe);
		bool IsExist() const;
		explicit operator bool() const;
		DWORD GetSize() const;
		iterator begin() const;
		iterator end() const;
		virtual ~DosStub();
	protected:
		_STD shared_ptr<IPeImage> pe_;
		unsigned char* ptr_;
		DWORD size_;
	};
}  // namespace PeDecoder
