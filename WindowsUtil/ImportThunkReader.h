#pragma once
#include "PeDecoder.h"
namespace PE
{
	// 导入表Thunk结构读取器
#define CONVERT_THUNK_POINTER(thunkPointer, x) ((PIMAGE_THUNK_DATA##x)thunkPointer)
	class ImportThunkReader
	{
	public:
		ImportThunkReader(PeDecoder& pe, PIMAGE_IMPORT_DESCRIPTOR importDescriptor);
		ImportThunkReader();
		void Init(PeDecoder& pe, PIMAGE_IMPORT_DESCRIPTOR importDescriptor);

		PIMAGE_THUNK_DATA32 CurrentThunk32();
		PIMAGE_THUNK_DATA32 CurrentOriginalThunk32();
		PIMAGE_THUNK_DATA64 CurrentThunk64();
		PIMAGE_THUNK_DATA64 CurrentOriginalThunk64();

	
		
		bool Next();
		void Reset();
		~ImportThunkReader();

		static PIMAGE_IMPORT_BY_NAME GetNameStruct(PeDecoder& pe, PIMAGE_THUNK_DATA32 thunk);
		static PIMAGE_IMPORT_BY_NAME GetNameStruct(PeDecoder& pe, PIMAGE_THUNK_DATA64 thunk);
		static bool IsSnapByOrdinal(PIMAGE_THUNK_DATA32 thunk);
		static bool IsSnapByOrdinal(PIMAGE_THUNK_DATA64 thunk);
		static ULONGLONG GetOrdinal(PIMAGE_THUNK_DATA64 thunk);
		static DWORD GetOrdinal(PIMAGE_THUNK_DATA32 thunk);
	private:
		bool is32;
		PVOID currentThunk;
		PVOID currentOriginalThunk;
		
		PVOID originalThunk;
		PVOID thunk;

	};
}