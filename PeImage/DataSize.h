#pragma once
namespace PeDecoder
{
	namespace Detail
	{
		template<typename TSizePtr>
		class DataSize
		{
		public:
			static_assert(_STD is_pointer<TSizePtr>::value, "TSizePtr not a pointer");
			typedef TSizePtr TSizePtr;
			typedef _STD remove_pointer_t<TSizePtr> TSizeType;
			DataSize(TSizePtr sizePtr) :
				sizePtr_(sizePtr)
			{
				assert(sizePtr);
			}
			virtual ~DataSize() = default;
			TSizePtr GetSizePtr() const
			{
				return sizePtr_;
			}
			TSizeType GetSize() const
			{
				return *GetSizePtr();
			}
		protected:
			// 需要保存大小来源指针
			TSizePtr sizePtr_;
		};
	}  // namespace Detail


}  // namespace PeDecoder
