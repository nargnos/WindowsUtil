#pragma once
namespace PeDecoder
{

	template<typename T>
	struct GetThunkOrdinal;

	template<>
	struct GetThunkOrdinal<PIMAGE_THUNK_DATA32>
	{
		typedef DWORD TResult;
		static bool IsSnapByOrdinal(PIMAGE_THUNK_DATA32 thunk)
		{
			return IMAGE_SNAP_BY_ORDINAL32(thunk->u1.Ordinal);
		}
		static TResult GetOrdinal(PIMAGE_THUNK_DATA32 ptr)
		{
			return IMAGE_ORDINAL32(ptr->u1.Ordinal);
		}
	};

	template<>
	struct GetThunkOrdinal<PIMAGE_THUNK_DATA64>
	{
		typedef ULONGLONG TResult;
		static bool IsSnapByOrdinal(PIMAGE_THUNK_DATA64 thunk)
		{
			return IMAGE_SNAP_BY_ORDINAL64(thunk->u1.Ordinal);
		}
		static TResult GetOrdinal(PIMAGE_THUNK_DATA64 ptr)
		{
			return IMAGE_ORDINAL64(ptr->u1.Ordinal);
		}
	};
}  // namespace PeDecoder
