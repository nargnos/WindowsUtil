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

		PIMAGE_THUNK_DATA32 CurrentThunk32();
		PIMAGE_THUNK_DATA32 CurrentOriginalThunk32();
		PIMAGE_THUNK_DATA64 CurrentThunk64();

		PIMAGE_THUNK_DATA64 CurrentOriginalThunk64();

		bool IsSnapByOrdinal(PIMAGE_THUNK_DATA32 thunk);
		bool IsSnapByOrdinal(PIMAGE_THUNK_DATA64 thunk);
		ULONGLONG GetOrdinal(PIMAGE_THUNK_DATA64 thunk);
		DWORD GetOrdinal(PIMAGE_THUNK_DATA32 thunk);
		PIMAGE_IMPORT_BY_NAME GetImportByNameStruct(PIMAGE_THUNK_DATA32 thunk);
		PIMAGE_IMPORT_BY_NAME GetImportByNameStruct(PIMAGE_THUNK_DATA64 thunk);
		bool Next();
		void Reset();
		~ImportThunkReader();

	private:
		PIMAGE_IMPORT_DESCRIPTOR importDescriptor;
		bool is32;
		PVOID currentThunk;
		PVOID currentOriginalThunk;
		PeDecoder& pe;
		PVOID originalThunk;
		PVOID thunk;

	};
}