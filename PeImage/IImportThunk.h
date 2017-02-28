#pragma once
#include <Windows.h>
#include "IReadThunkDetail.h"
namespace PeDecoder
{
	__interface IImportThunk
	{
		bool IsSnapByOrdinal() const;
		PIMAGE_IMPORT_BY_NAME GetImportByName() const;
		PVOID GetFuncAddress() const;
		void Accept(IReadThunkDetail& visitor) const;
		// AddressThunk
		void* GetThunkPtr() const;
		// NameThunk
		void* GetOriginalThunkPtr() const;
	};
}  // namespace PeDecoder