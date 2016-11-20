#pragma once
#include <Windows.h>
namespace PeDecoder
{
	template<typename> class ImportThunk;
	class ImportDirectory;
	// 根据pe类型选择PIMAGE_THUNK_DATA32 PIMAGE_THUNK_DATA64类型的thunk
	class ImportDescriptor
	{
	public:
		using Thunk32 = ImportThunk<PIMAGE_THUNK_DATA32>;
		using Thunk64 = ImportThunk<PIMAGE_THUNK_DATA64>;
		friend class ImportDirectoryIterator;
		ImportDescriptor(ImportDirectory& importDirectory, PIMAGE_IMPORT_DESCRIPTOR ptr);

		Thunk32 GetThunk32() const;
		Thunk64 GetThunk64() const;
		PCHAR GetName() const;
		PIMAGE_IMPORT_DESCRIPTOR GetPtr() const;

	protected:
		PIMAGE_IMPORT_DESCRIPTOR dataPtr_;
		ImportDirectory* importDirectory_;
	};


}  // namespace PeDecoder
