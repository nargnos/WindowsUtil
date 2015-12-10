#include "ImportDirectory.h"
#define CONVERT_THUNK_POINTER(thunkPointer, x) ((PIMAGE_THUNK_DATA##x)thunkPointer)
#define CHECK_THUNK(x) \
			auto tmpThunk = CONVERT_THUNK_POINTER(currentOriginalThunk, x) + 1;\
			if (CONVERT_THUNK_POINTER(tmpThunk,x)->u1.AddressOfData == NULL)   \
			{																   \
				return false;												   \
			}																   \
			currentThunk =  CONVERT_THUNK_POINTER(currentThunk, x) + 1;		   \
			currentOriginalThunk = tmpThunk;
void PE::ImportThunkIterator::Init(PIMAGE_IMPORT_DESCRIPTOR importDescriptor)
{
	originalThunk = importDescriptorIterator.importDirectory.GetPeDecoder().GetRvaData(importDescriptor->OriginalFirstThunk);
	thunk = importDescriptorIterator.importDirectory.GetPeDecoder().GetRvaData(importDescriptor->FirstThunk);
	Reset();
}

PE::ImportThunkIterator::ImportThunkIterator(ImportDescriptorIterator & importDescriptorIterator) :importDescriptorIterator(importDescriptorIterator)
{
	is32 = importDescriptorIterator.importDirectory.GetPeDecoder().HasNtHeader32();
	Init(importDescriptorIterator.Current());
}

PIMAGE_THUNK_DATA32 PE::ImportThunkIterator::CurrentThunk32()
{
	return is32 ? CONVERT_THUNK_POINTER(currentThunk, 32) : NULL;
}

PIMAGE_THUNK_DATA32 PE::ImportThunkIterator::CurrentOriginalThunk32()
{
	return is32 ? CONVERT_THUNK_POINTER(currentOriginalThunk, 32) : NULL;
}

PIMAGE_THUNK_DATA64 PE::ImportThunkIterator::CurrentThunk64()
{
	return is32 ? NULL : CONVERT_THUNK_POINTER(currentThunk, 64);
}

PIMAGE_THUNK_DATA64 PE::ImportThunkIterator::CurrentOriginalThunk64()
{
	return is32 ? NULL : CONVERT_THUNK_POINTER(currentOriginalThunk, 64);
}

bool PE::ImportThunkIterator::Next()
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

void PE::ImportThunkIterator::Reset()
{
	currentThunk = NULL;
	currentOriginalThunk = NULL;
}

PE::ImportThunkIterator::~ImportThunkIterator() {}
