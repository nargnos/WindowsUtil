#include "ImportThunkIterator.h"

namespace PE
{
//	
//		// 导入表Thunk结构读取器
//
//		ImportThunkIterator::ImportThunkIterator(PeDecoder& pe, PIMAGE_IMPORT_DESCRIPTOR importDescriptor)
//		{
//			Init(pe, importDescriptor);
//		}
//		ImportThunkIterator::ImportThunkIterator()
//		{
//			currentThunk = NULL;
//			currentOriginalThunk = NULL;
//		}
//		void ImportThunkIterator::Init(PeDecoder& pe, PIMAGE_IMPORT_DESCRIPTOR importDescriptor)
//		{
//			assert(importDescriptor);
//			is32 = pe.HasNtHeader32();
//			originalThunk = pe.GetRvaData(importDescriptor->OriginalFirstThunk);
//			thunk = pe.GetRvaData(importDescriptor->FirstThunk);
//			Reset();
//		}
//
//		PIMAGE_THUNK_DATA32 ImportThunkIterator::CurrentThunk32()
//		{
//			return is32?CONVERT_THUNK_POINTER(currentThunk, 32): NULL;
//		}
//		PIMAGE_THUNK_DATA32 ImportThunkIterator::CurrentOriginalThunk32()
//		{
//			return is32?CONVERT_THUNK_POINTER(currentOriginalThunk, 32): NULL;
//		}
//		PIMAGE_THUNK_DATA64 ImportThunkIterator::CurrentThunk64()
//		{
//			return is32?NULL: CONVERT_THUNK_POINTER(currentThunk, 64);
//		}
//
//		PIMAGE_THUNK_DATA64 ImportThunkIterator::CurrentOriginalThunk64()
//		{
//			return is32?NULL: CONVERT_THUNK_POINTER(currentOriginalThunk, 64);
//		}
//
//
//#define CHECK_THUNK(x) \
//			auto tmpThunk = CONVERT_THUNK_POINTER(currentOriginalThunk, x) + 1;\
//			if (CONVERT_THUNK_POINTER(tmpThunk,x)->u1.AddressOfData == NULL)	   \
//			{																   \
//				return false;												   \
//			}																   \
//			currentThunk =  CONVERT_THUNK_POINTER(currentThunk, x) + 1;		   \
//			currentOriginalThunk = tmpThunk;
//		bool ImportThunkIterator::Next()
//		{
//			if (currentThunk == NULL && currentOriginalThunk == NULL)
//			{
//				currentThunk = thunk;
//				currentOriginalThunk = originalThunk;
//				return true;
//			}
//			if (is32)
//			{
//				CHECK_THUNK(32);
//			}
//			else
//			{
//				CHECK_THUNK(64);
//			}
//
//			return true;
//		}
//		void ImportThunkIterator::Reset()
//		{
//			currentThunk = NULL;
//			currentOriginalThunk = NULL;
//		}
//		ImportThunkIterator::~ImportThunkIterator() {}
	
}