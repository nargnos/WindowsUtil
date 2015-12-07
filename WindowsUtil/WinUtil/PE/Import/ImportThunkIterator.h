#pragma once
#include <Windows.h>
#include <cassert>
namespace PE
{
	// 导入表Thunk结构读取器

	template<typename _ImportDescriptorIterator>
	class ImportThunkIterator
	{
		_ImportDescriptorIterator& importDescriptorIterator;
		bool is32;
		PVOID currentThunk;
		PVOID currentOriginalThunk;

		PVOID originalThunk;
		PVOID thunk;
		void Init(PIMAGE_IMPORT_DESCRIPTOR importDescriptor)
		{
			originalThunk = importDescriptorIterator.importDirectory.GetPeDecoder().GetRvaData(importDescriptor->OriginalFirstThunk);
			thunk = importDescriptorIterator.importDirectory.GetPeDecoder().GetRvaData(importDescriptor->FirstThunk);
			Reset();
		}
	public:
		ImportThunkIterator(_ImportDescriptorIterator& importDescriptorIterator) :importDescriptorIterator(importDescriptorIterator)
		{
			is32 = importDescriptorIterator.importDirectory.GetPeDecoder().HasNtHeader32();
			Init(importDescriptorIterator.Current());
		}

#define CONVERT_THUNK_POINTER(thunkPointer, x) ((PIMAGE_THUNK_DATA##x)thunkPointer)
		PIMAGE_THUNK_DATA32 CurrentThunk32()
		{
			return is32 ? CONVERT_THUNK_POINTER(currentThunk, 32) : NULL;
		}
		PIMAGE_THUNK_DATA32 CurrentOriginalThunk32()
		{
			return is32 ? CONVERT_THUNK_POINTER(currentOriginalThunk, 32) : NULL;
		}
		PIMAGE_THUNK_DATA64 CurrentThunk64()
		{
			return is32 ? NULL : CONVERT_THUNK_POINTER(currentThunk, 64);
		}

		PIMAGE_THUNK_DATA64 CurrentOriginalThunk64()
		{
			return is32 ? NULL : CONVERT_THUNK_POINTER(currentOriginalThunk, 64);
		}



#define CHECK_THUNK(x) \
			auto tmpThunk = CONVERT_THUNK_POINTER(currentOriginalThunk, x) + 1;\
			if (CONVERT_THUNK_POINTER(tmpThunk,x)->u1.AddressOfData == NULL)   \
			{																   \
				return false;												   \
			}																   \
			currentThunk =  CONVERT_THUNK_POINTER(currentThunk, x) + 1;		   \
			currentOriginalThunk = tmpThunk;
		bool Next()
		{
			if (currentThunk == NULL && currentOriginalThunk == NULL)
			{
				currentThunk = thunk;
				currentOriginalThunk = originalThunk;
				return true;
			}
			if (is32)
			{
				CHECK_THUNK(32);
			}
			else
			{
				CHECK_THUNK(64);
			}

			return true;
		}
		void Reset()
		{
			currentThunk = NULL;
			currentOriginalThunk = NULL;
		}
		~ImportThunkIterator() {}

	};

}