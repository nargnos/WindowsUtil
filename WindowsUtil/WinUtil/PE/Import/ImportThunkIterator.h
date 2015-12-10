#pragma once
#include "../Common/Common.h"
namespace PE
{
	// 导入表Thunk结构读取器
	class ImportDescriptorIterator;
	class ImportThunkIterator
	{
		ImportDescriptorIterator& importDescriptorIterator;
		bool is32;
		PVOID currentThunk;
		PVOID currentOriginalThunk;

		PVOID originalThunk;
		PVOID thunk;
		void Init(PIMAGE_IMPORT_DESCRIPTOR importDescriptor);
	public:
		ImportThunkIterator(ImportDescriptorIterator& importDescriptorIterator);


		PIMAGE_THUNK_DATA32 CurrentThunk32();
		PIMAGE_THUNK_DATA32 CurrentOriginalThunk32();
		PIMAGE_THUNK_DATA64 CurrentThunk64();

		PIMAGE_THUNK_DATA64 CurrentOriginalThunk64();




		bool Next();
		void Reset();
		~ImportThunkIterator();

	};

}