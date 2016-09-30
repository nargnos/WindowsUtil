#pragma once

namespace PeDecoder
{
	namespace Detail
	{
		template<typename TDataPtr>
		class DataPtr
		{
		public:
			static_assert(_STD is_pointer<TDataPtr>::value, "TDataPtr is not a pointer");
			typedef TDataPtr TDataPtr;
			typedef _STD remove_pointer_t<TDataPtr> TDataType;
			explicit DataPtr(TDataPtr dataPtr) :
				dataPtr_(dataPtr)
			{

			}

			virtual ~DataPtr() = default;
			TDataPtr GetPtr() const
			{
				assert(dataPtr_);
				return dataPtr_;
			}
			explicit operator bool()
			{
				return dataPtr_ != nullptr;
			}
		protected:
			void SetPtr(TDataPtr ptr)
			{
				dataPtr_ = ptr;
			}
			TDataPtr dataPtr_;
		};
	}  // namespace Detail

}  // namespace PeDecoder
