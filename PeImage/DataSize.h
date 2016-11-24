#pragma once
namespace PeDecoder
{
	namespace Detail
	{
		template<typename TSizePtr>
		class DataSize
		{
		public:
			static_assert(_STD is_pointer<TSizePtr>::value, "TSizePtr is not a pointer");
			typedef TSizePtr TSizePtr;
			typedef _STD remove_pointer_t<TSizePtr> TSizeType;
			DataSize(TSizePtr sizePtr) :
				sizePtr_(sizePtr)
			{

			}
			virtual ~DataSize()
			{
				sizePtr_ = nullptr;
			}
			TSizePtr GetSizePtr() const
			{
				assert(sizePtr_);
				return sizePtr_;
			}
			TSizeType size() const
			{
				return GetSize();
			}
			TSizeType GetSize() const
			{
				return *GetSizePtr();
			}
		protected:
			void SetSizePtr(TSizePtr ptr)
			{
				sizePtr_ = ptr;
			}
			// 需要保存大小来源指针
			TSizePtr sizePtr_;
		};
	}  // namespace Detail


}  // namespace PeDecoder
