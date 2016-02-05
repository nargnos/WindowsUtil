#pragma once
namespace PE
{
	class InitStruct
	{
	protected:
		bool isInitialized;
		virtual bool InitFunc() = 0;
	public:

		InitStruct();
		// ≥ı ºªØ ß∞‹∑µªÿfalse
		bool Init();
		bool IsInit();
		virtual ~InitStruct();
	};

}  // namespace PE
