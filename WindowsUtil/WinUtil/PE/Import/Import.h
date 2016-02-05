#pragma once
#include <cassert>
#include "..\PeImage.h"
namespace PE
{
		LPSTR GetDescriptorName(PeDecoder & pe, PIMAGE_IMPORT_DESCRIPTOR descriptor);
		PIMAGE_IMPORT_BY_NAME GetNameStruct(PeDecoder & pe, PIMAGE_THUNK_DATA32 thunk);
		PIMAGE_IMPORT_BY_NAME GetNameStruct(PeDecoder & pe, PIMAGE_THUNK_DATA64 thunk);
		bool IsSnapByOrdinal(PIMAGE_THUNK_DATA32 thunk);
		bool IsSnapByOrdinal(PIMAGE_THUNK_DATA64 thunk);
		ULONGLONG GetOrdinal(PIMAGE_THUNK_DATA64 thunk);
		DWORD GetOrdinal(PIMAGE_THUNK_DATA32 thunk);
		PVOID GetProcImportThunkAddress(PeDecoder & pe, LPCSTR dllName, LPCSTR procName);  // 如果没有dllName则匹配第一个遇到的函数名

}  // namespace PE
