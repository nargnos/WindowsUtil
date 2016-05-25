#include "stdafx.h"
#include "ExportDirectory.h"
#include "PeImage.h"

namespace PeDecoder
{
	ExportDirectory::ExportDirectory(PeImage & pe, TDataPtr ptr, TSizePtr sizePtr) :
		DirectoryBase(pe, ptr, sizePtr)
	{
		numberOfNames_ = &GetPtr()->NumberOfNames;
		numberOfFunctions_ = &GetPtr()->NumberOfFunctions;
		funcTable_ = reinterpret_cast<PDWORD>(pe.RvaToDataPtr(GetPtr()->AddressOfFunctions));
		nameTable_ = reinterpret_cast<PDWORD>(pe.RvaToDataPtr(GetPtr()->AddressOfNames));
		nameOrdinalTable_ = reinterpret_cast<PWORD>(pe.RvaToDataPtr(GetPtr()->AddressOfNameOrdinals));
	}
	const PDWORD ExportDirectory::GetFunctionsPtr() const
	{

		return funcTable_;
	}
	const PDWORD ExportDirectory::GetNamesPtr() const
	{
		return nameTable_;
	}
	const PWORD ExportDirectory::GetNameOrdinalsPtr() const
	{
		return nameOrdinalTable_;
	}
	const PDWORD ExportDirectory::GetNumberOfFunctionsPtr() const
	{
		return numberOfFunctions_;
	}
	const PDWORD ExportDirectory::GetNumberOfNamesPtr() const
	{
		return numberOfNames_;
	}

	ExportDirectory::iterator ExportDirectory::begin() const
	{
		return ExportDirectory::iterator(*this, 0);
	}

	ExportDirectory::iterator ExportDirectory::end() const
	{
		return ExportDirectory::iterator(*this, *GetNumberOfNamesPtr());
	}


	ExportDirectory::iterator::iterator(const ExportDirectory & directory, DWORD index) :
		node_(directory, index)
	{

	}

	bool ExportDirectory::iterator::equal(const ExportDirectory::iterator & val) const
	{
		return GetStore().Equal(val.GetStore());
	}
	void ExportDirectory::iterator::increment()
	{
		GetStore().Increment();
	}
	void ExportDirectory::iterator::decrement()
	{
		GetStore().Decrement();
	}
	void ExportDirectory::iterator::advance(int n)
	{
		GetStore().Advance(n);
	}
	ExportDirectory::iterator::difference_type ExportDirectory::iterator::distance_to(const iterator & val)
	{
		return GetStore().DistanceTo(val.GetStore());
	}
	ExportDirectory::iterator::reference ExportDirectory::iterator::dereference()
	{
		return GetStore();
	}
	ExportIteratorNode & ExportDirectory::iterator::GetStore()
	{
		return node_;
	}
	const ExportIteratorNode & ExportDirectory::iterator::GetStore() const
	{
		return node_;
	}
	ExportIteratorNode::ExportIteratorNode(const ExportDirectory & directory, DWORD index) :
		directory_(directory),
		index_(index)
	{

	}
	PDWORD ExportIteratorNode::FuncRva() const
	{
		return &directory_.GetFunctionsPtr()[*NameOrdinals()];
	}
	PDWORD ExportIteratorNode::NameRva() const
	{
		return &directory_.GetNamesPtr()[index_];
	}
	PWORD ExportIteratorNode::NameOrdinals() const
	{
		return &directory_.GetNameOrdinalsPtr()[index_];
	}
	bool ExportIteratorNode::Equal(const ExportIteratorNode & val) const
	{
		return &val.directory_ == &directory_ && val.index_ == index_;
	}
	void ExportIteratorNode::Increment()
	{
		++index_;
		assert(InRange());
	}
	void ExportIteratorNode::Decrement()
	{
		--index_;
		assert(InRange());
	}
	void ExportIteratorNode::Advance(int n)
	{
		index_ += n;
		assert(InRange());
	}
	int ExportIteratorNode::DistanceTo(const ExportIteratorNode & val)
	{
		assert(Equal(val));
		return val.index_ - index_;
	}
	bool ExportIteratorNode::InRange() const
	{
		return index_ >= 0 && index_ <= *directory_.GetNumberOfNamesPtr();
	}
}  // namespace PeDecoder
