#pragma once
class InitStruct
{
protected:
	bool isInitialized;
	virtual bool InitFunc() = 0;
public:

	InitStruct()
	{
		isInitialized = false;
	}
	// ≥ı ºªØ ß∞‹∑µªÿfalse
	bool Init() 
	{
		if (isInitialized)
		{
			return isInitialized;
		}
		isInitialized = InitFunc();
		return isInitialized;
	}
	virtual ~InitStruct()
	{
	}
};

