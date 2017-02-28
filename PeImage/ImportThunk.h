#pragma once
#include "IImportThunk.h"
#include "GetOriginal.h"
#include "IteratorBase.h"
#include "IPeImage.h"
namespace PeDecoder
{
	class ImportThunkIterator;
	template<typename TThunkType>
	class ImportThunk:
		public IImportThunk
	{
	public:
		static_assert(_STD is_same<PIMAGE_THUNK_DATA32, TThunkType>::value ||
			_STD is_same<PIMAGE_THUNK_DATA64, TThunkType>::value, "PIMAGE_THUNK_DATA32 PIMAGE_THUNK_DATA64");
		friend ImportThunkIterator;
		ImportThunk(const IPeImage& util, TThunkType thunk, TThunkType originalThunk) :
			originalThunk_(originalThunk),
			thunk_(thunk),
			util_(&util)
		{

		}
		// 判断是否是用ID导入的
		// false表示这个结构可用GetImportByName取得名字
		virtual bool IsSnapByOrdinal() const override
		{
			assert(GetNameThunk());
			return GetThunkOrdinal<TThunkType>::IsSnapByOrdinal(GetNameThunk());
		}
		// 需先进行IsSnapByOrdinal()判断
		// 取当前导入函数名的存储结构
		virtual PIMAGE_IMPORT_BY_NAME GetImportByName() const override
		{
			assert(GetNameThunk());
			assert(GetNameThunk()->u1.AddressOfData != 0);
			assert(!IsSnapByOrdinal());
			return reinterpret_cast<PIMAGE_IMPORT_BY_NAME>(util_->RvaToDataPtr(GetNameThunk()->u1.AddressOfData));
		}
		
		virtual PVOID GetFuncAddress() const override
		{
			assert(GetAddressThunk());
			assert(GetAddressThunk()->u1.Function != 0);
			return util_->IsMapped()? (PVOID)GetAddressThunk()->u1.Function : util_->RvaToDataPtr(GetAddressThunk()->u1.Function);
		}
		virtual void Accept(IReadThunkDetail& visitor) const override
		{
			visitor.Visit(*this);
		}
		// AddressThunk
		virtual void* GetThunkPtr() const override
		{
			return GetAddressThunk();
		}
		// NameThunk
		virtual void* GetOriginalThunkPtr() const override
		{
			return GetNameThunk();
		}
		TThunkType GetAddressThunk() const
		{
			return thunk_;
		}
		TThunkType GetNameThunk() const
		{
			return originalThunk_;
		}
		// 需先进行IsSnapByOrdinal()判断
		// 取当前导入函数的ID
		typename GetThunkOrdinal<TThunkType>::TResult GetOrdinal() const
		{
			return GetThunkOrdinal<TThunkType>::GetOrdinal(originalThunk_);
		}
		virtual ~ImportThunk()
		{
			util_ = nullptr;
			thunk_ = nullptr;
			originalThunk_ = nullptr;
		}

	protected:
		const IPeImage* util_;
		TThunkType thunk_;
		TThunkType originalThunk_;

	};

	// 辅助查找iat的函数
	template<typename TThunkIterator>
	TThunkIterator FindThunk(TThunkIterator begin, TThunkIterator end, LPCSTR procName)
	{
		return _STD find_if(begin, end, [procName](auto& node)
		{
			if (!node->IsSnapByOrdinal())
			{
				return strcmp(reinterpret_cast<PCHAR>(node->GetImportByName()->Name), procName) == 0;
			}
			return false;
		});
	}
}  // namespace PeDecoder
