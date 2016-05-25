#pragma once

namespace PeDecoder
{
	template<typename TDataPtr>
	class DataPtr
	{
	public:
		static_assert(_STD is_pointer<TDataPtr>::value, "TDataPtr not a pointer");
		typedef TDataPtr TDataPtr;
		typedef _STD remove_pointer_t<TDataPtr> TDataType;
		DataPtr(TDataPtr dataPtr) :
			dataPtr_(dataPtr)
		{
			assert(dataPtr);
		}

		virtual ~DataPtr() = default;
		TDataPtr GetPtr() const
		{
			return dataPtr_;
		}

	protected:
		TDataPtr dataPtr_;
	};
}  // namespace PeDecoder
