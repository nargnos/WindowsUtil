#pragma once
namespace NAMESPACE {
	template<typename T>
	public ref class UnmanagedWapper
	{
		T* data;
	protected:
		virtual T* GetData() = 0;
	internal:
		T* UnmanagedObject()
		{
			if (!data)
			{
				data = GetData();
			}
			return data;
		}
	public:
		UnmanagedWapper()
		{
			data = NULL;
		}
		~UnmanagedWapper()
		{
			this->!UnmanagedWapper();
		}
		!UnmanagedWapper()
		{
			if (data)
			{
				delete data;
				data = NULL;
			}
		}
		
	};
}
