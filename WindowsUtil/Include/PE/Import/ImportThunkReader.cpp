#include "ImportThunkReader.h"

namespace PE
{
	namespace Import{
		// 导入表Thunk结构读取器

		ImportThunkReader::ImportThunkReader(PeDecoder& pe, PIMAGE_IMPORT_DESCRIPTOR importDescriptor)
		{
			Init(pe, importDescriptor);
		}
		ImportThunkReader::ImportThunkReader()
		{
			currentThunk = NULL;
			currentOriginalThunk = NULL;
		}
		void ImportThunkReader::Init(PeDecoder& pe, PIMAGE_IMPORT_DESCRIPTOR importDescriptor)
		{
			assert(importDescriptor);
			is32 = pe.HasNtHeader32();
			originalThunk = pe.GetRvaData(importDescriptor->OriginalFirstThunk);
			thunk = pe.GetRvaData(importDescriptor->FirstThunk);
			Reset();
		}

		PIMAGE_THUNK_DATA32 ImportThunkReader::CurrentThunk32()
		{
			if (is32)
			{
				return CONVERT_THUNK_POINTER(currentThunk, 32);
			}
			return NULL;
		}
		PIMAGE_THUNK_DATA32 ImportThunkReader::CurrentOriginalThunk32()
		{
			if (is32)
			{
				return CONVERT_THUNK_POINTER(currentOriginalThunk, 32);
			}
			return NULL;
		}
		PIMAGE_THUNK_DATA64 ImportThunkReader::CurrentThunk64()
		{
			if (is32)
			{
				return NULL;
			}
			return CONVERT_THUNK_POINTER(currentThunk, 64);
		}

		PIMAGE_THUNK_DATA64 ImportThunkReader::CurrentOriginalThunk64()
		{
			if (is32)
			{
				return NULL;
			}
			return CONVERT_THUNK_POINTER(currentOriginalThunk, 64);
		}



		bool ImportThunkReader::Next()
		{
#define CHECK_THUNK(x) auto tmpThunk = CONVERT_THUNK_POINTER(currentOriginalThunk, x) + 1;\
			if (CONVERT_THUNK_POINTER(tmpThunk,x)->u1.AddressOfData == NULL)\
						{\
				return false;\
						}\
			currentThunk =  CONVERT_THUNK_POINTER(currentThunk, x) + 1;\
			currentOriginalThunk = tmpThunk;

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
		void ImportThunkReader::Reset()
		{
			currentThunk = NULL;
			currentOriginalThunk = NULL;
		}
		ImportThunkReader::~ImportThunkReader(){}

	}
}