#pragma once
#include <Windows.h>
#include "VisitorBase.h"
namespace PeDecoder
{
	template<typename>
	class ImportThunk;
	using ImportThunk32 = ImportThunk<PIMAGE_THUNK_DATA32>;
	using ImportThunk64 = ImportThunk<PIMAGE_THUNK_DATA64>;

	__interface IReadThunkDetail
	{
		void Visit(const ImportThunk32& t32) const;
		void Visit(const ImportThunk64& t64) const;
	};

	template<typename TFunc32, typename TFunc64>
	auto MakeThunkVisitor(TFunc32&& func32, TFunc64&& func64)
	{
		return VisitorBase<IReadThunkDetail, ImportThunk32, TFunc32, ImportThunk64, TFunc64>(_STD forward<TFunc32>(func32), _STD forward<TFunc64>(func64));
	}
}  // namespace PeDecoder