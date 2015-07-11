#pragma once
#include <cassert>
#include "..\PeDecoder.h"
namespace PE
{
	namespace Import{
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

			
		private:
			bool is32;
			PVOID currentThunk;
			PVOID currentOriginalThunk;

			PVOID originalThunk;
			PVOID thunk;

		};
	}
}