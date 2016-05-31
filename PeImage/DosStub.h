#pragma once
#include "DataPtr.h"
namespace PeDecoder
{
	class DosStub:
		public Detail::DataPtr<unsigned char*>
	{
	public:
		typedef TDataPtr iterator;
		DosStub(void* ptr, DWORD size);
		~DosStub() = default;
		DWORD GetSize() const;
		iterator begin() const;
		iterator end() const;
	protected:
		DWORD size_;
	};
}  // namespace PeDecoder
