#pragma once
#include "DataPtr.h"
#include "GetOriginal.h"
namespace PeDecoder
{
	template<typename TThunkType>
	class ImportThunkIteratorNode
	{
	public:
		friend class ImportThunkIterator<TThunkType>;
		static_assert(_STD is_same<PIMAGE_THUNK_DATA32, TThunkType>::value ||
			_STD is_same<PIMAGE_THUNK_DATA64, TThunkType>::value, "type error");

		ImportThunkIteratorNode(PeImage& pe, TThunkType thunk, TThunkType originalThunk) :
			originalThunk_(originalThunk),
			thunk_(thunk),
			pe_(&pe)
		{

		}
		TThunkType GetAddressThunk() const
		{
			return thunk_;
		}
		TThunkType GetNameThunk() const
		{
			return originalThunk_;
		}
		// 判断是否是用ID导入的
		// false表示这个结构可用GetImportByName取得名字
		bool IsSnapByOrdinal() const
		{
			return GetThunkOrdinal<TThunkType>::IsSnapByOrdinal(originalThunk_);
		}
		// 需先进行IsSnapByOrdinal()判断
		// 取当前导入函数名的存储结构
		PIMAGE_IMPORT_BY_NAME GetImportByName() const
		{
			assert(originalThunk_->u1.AddressOfData != 0);
			assert(!IsSnapByOrdinal());
			return reinterpret_cast<PIMAGE_IMPORT_BY_NAME>(pe_->RvaToDataPtr(originalThunk_->u1.AddressOfData));
		}
		
		// 需先进行IsSnapByOrdinal()判断
		// 取当前导入函数的ID
		typename GetThunkOrdinal<TThunkType>::TResult GetOrdinal() const
		{
			return GetThunkOrdinal<TThunkType>::GetOrdinal(originalThunk_);
		}
		

		PVOID GetFuncAddress() const
		{
			assert(thunk_->u1.Function != 0);
			return pe_->IsMapped()? (PVOID)thunk_->u1.Function:pe_->RvaToDataPtr(thunk_->u1.Function);
		}
	protected:
		
		PeImage* pe_;
		TThunkType thunk_;
		TThunkType originalThunk_;
	};

	using ImportThunkIteratorNode32 = ImportThunkIteratorNode<PIMAGE_THUNK_DATA32>;
	using ImportThunkIteratorNode64 = ImportThunkIteratorNode<PIMAGE_THUNK_DATA64>;

	// node类型为ImportThunkIteratorNode<TThunkType>
	// 类型有PIMAGE_THUNK_DATA32 PIMAGE_THUNK_DATA64
	template<typename TThunkType>
	class ImportThunkIterator :
		public iterator_facade<
		ImportThunkIterator<TThunkType>,
		ImportThunkIteratorNode<TThunkType>,
		forward_traversal_tag>
	{
	public:
		friend class iterator_core_access;

		ImportThunkIterator(PeImage& pe, TThunkType thunk, TThunkType originalThunk) :
			store_(pe, thunk, originalThunk)
		{
		}
	protected:
		bool equal(const ImportThunkIterator & val) const
		{
			return GetStore().originalThunk_ == val.GetStore().originalThunk_ &&
				GetStore().thunk_ == val.GetStore().thunk_;
		}
		void increment()
		{
			++GetStore().originalThunk_;
			++GetStore().thunk_;
			if (GetStore().originalThunk_->u1.AddressOfData == 0)
			{
				// 到末尾了
				GetStore().originalThunk_ = nullptr;
				GetStore().thunk_ = nullptr;
			}
		}


		ImportThunkIteratorNode<TThunkType>& dereference() const
		{
			return const_cast<ImportThunkIteratorNode<TThunkType>&>(GetStore());
		}
		ImportThunkIteratorNode<TThunkType>& GetStore()
		{
			return store_;
		}
		const ImportThunkIteratorNode<TThunkType>& GetStore() const
		{
			return store_;
		}
		ImportThunkIteratorNode<TThunkType> store_;
	};

	using ImportThunkIterator32 = ImportThunkIterator<PIMAGE_THUNK_DATA32>;
	using ImportThunkIterator64 = ImportThunkIterator<PIMAGE_THUNK_DATA64>;

	template<typename TThunkType>
	class ImportThunk
	{
	public:
		typedef ImportThunkIterator<TThunkType> iterator;
		// @firstThunk: address table
		// @firstOriginalThunk: name table 有可能是 Original
		ImportThunk(PeImage& pe, TThunkType firstThunk, TThunkType firstOriginalThunk) :
			firstOriginalThunk_(firstOriginalThunk),
			firstThunk_(firstThunk),
			pe_(pe)
		{
		}

		ImportThunkIterator<TThunkType> begin() const
		{
			return ImportThunkIterator<TThunkType>(pe_, firstThunk_, firstOriginalThunk_);
		}
		ImportThunkIterator<TThunkType> end() const
		{
			return ImportThunkIterator<TThunkType>(pe_, nullptr, nullptr);
		}
	protected:
		PeImage& pe_;
		TThunkType firstOriginalThunk_;
		TThunkType firstThunk_;
	};
	using ImportThunk32 = ImportThunk<PIMAGE_THUNK_DATA32>;
	using ImportThunk64 = ImportThunk<PIMAGE_THUNK_DATA64>;

	// 辅助查找iat的函数
	template<typename TThunkIterator, typename TThunkIteratorNode>
	TThunkIterator FindThunk(TThunkIterator begin, TThunkIterator end, LPCSTR procName)
	{
		return _STD find_if(begin, end, [procName](TThunkIteratorNode& node)
		{
			if (!node.IsSnapByOrdinal())
			{
				return strcmp(reinterpret_cast<PCHAR>(node.GetImportByName()->Name), procName) == 0;
			}
			return false;
		});
	}
}  // namespace PeDecoder
