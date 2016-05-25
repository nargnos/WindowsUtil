#pragma once
#include "DataPtr.h"
namespace PeDecoder
{
	class DosStub:
		public DataPtr<unsigned char*>
	{
	public:
		typedef TDataPtr iterator;
		DosStub(void* ptr, DWORD size);
		~DosStub() = default;
		DWORD GetSize();
		iterator begin() const;
		iterator end() const;
	protected:
		unsigned char* dosStub_;
		DWORD size_;
	};
}  // namespace PeDecoder
