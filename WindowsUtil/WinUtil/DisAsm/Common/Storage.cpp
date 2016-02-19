#include "Storage.h"
namespace Disassembler
{
	StorageBase::StorageBase()
	{
		currentPos = beginPos = NULL;
	}
	StorageBase::StorageBase(const StorageBase & val)
	{
		this->currentPos = val.currentPos;
		this->beginPos = val.beginPos;
	}
	void StorageBase::SetInitialPosition(const void* pos)
	{
		currentPos = NULL;
		isSuccess = false;
		beginPos = reinterpret_cast<const unsigned char*>(pos);
	}

	const unsigned char* StorageBase::GetCurrentPosition()
	{
		return currentPos;
	}

	void StorageBase::NextByte()
	{
		if (currentPos == NULL)
		{
			currentPos = beginPos;
			return;
		}
		++currentPos;
	}

	bool StorageBase::IsSuccess()
	{
		return isSuccess;
	}

	void StorageBase::SetSuccess()
	{
		isSuccess = true;
	}

}  // namespace Disassembler
