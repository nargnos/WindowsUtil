#pragma once
namespace PeDecoder
{
	// 不要修改这里的顺序
	enum class NtHeaderType :
		unsigned char
	{
		UnKnown,
		Rom,
		NtHeader32,
		NtHeader64
	};
}  // namespace PeDecoder
