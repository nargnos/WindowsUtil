#include "InitStruct.h"
namespace PE
{
	InitStruct::InitStruct()
	{
		isInitialized = false;
	}


	// ≥ı ºªØ ß∞‹∑µªÿfalse

	bool InitStruct::Init()
	{
		if (isInitialized)
		{
			return isInitialized;
		}
		isInitialized = InitFunc();
		return isInitialized;
	}

	bool InitStruct::IsInit()
	{
		return isInitialized;
	}

	InitStruct::~InitStruct()
	{
	}
}