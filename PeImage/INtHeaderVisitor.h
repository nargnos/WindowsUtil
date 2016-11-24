#pragma once
#include "VisitorBase.h"
namespace PeDecoder
{
	template<typename>
	class NtHeaderImpl;
	using NtHeader32 = NtHeaderImpl<PIMAGE_NT_HEADERS32>;
	using NtHeader64 = NtHeaderImpl<PIMAGE_NT_HEADERS64>;

	__interface INtHeaderVisitor
	{
		void Visit(const NtHeader32& nt) const;
		void Visit(const NtHeader64& nt) const;
	};

	template<typename TFunc32, typename TFunc64>
	auto MakeNtHeaderVisitor(TFunc32&& func32, TFunc64&& func64)
	{
		return VisitorBase<INtHeaderVisitor, NtHeader32, TFunc32, NtHeader64, TFunc64>(_STD forward<TFunc32>(func32), _STD forward<TFunc64>(func64));
	}
}  // namespace PeDecoder
