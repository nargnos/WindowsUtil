#include "stdafx.h"
#include "DosStub.h"


namespace PeDecoder
{

	DosStub::DosStub(void* ptr, DWORD size):
		DataPtr(reinterpret_cast<unsigned char*>(ptr)),
		size_(size)
	{
		assert(ptr);
	}
	DWORD DosStub::GetSize() const
	{
		return size_;
	}

	DosStub::iterator DosStub::begin() const
	{
		return GetPtr();
	}

	DosStub::iterator DosStub::end() const
	{
		return GetPtr() + GetSize();
	}

}  // namespace PeDecoder
