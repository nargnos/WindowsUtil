#include "stdafx.h"
#include "ExportIteratorNode.h"
#include "ExportDirectory.h"
namespace PeDecoder
{
	ExportIteratorNode::ExportIteratorNode(const ExportDirectory & directory, DWORD index) :
		directory_(&directory),
		index_(index)
	{
	}

	PDWORD ExportIteratorNode::FuncRva()
	{
		assert(directory_);
		return &directory_->GetFunctionsPtr()[*NameOrdinals()];
	}

	PDWORD ExportIteratorNode::NameRva()
	{
		assert(directory_);
		return &directory_->GetNamesPtr()[index_];
	}

	PWORD ExportIteratorNode::NameOrdinals()
	{
		assert(directory_);
		return &directory_->GetNameOrdinalsPtr()[index_];
	}

	void * ExportIteratorNode::FuncPtr()
	{
		assert(directory_);
		return directory_->GetUtil().RvaToDataPtr(*FuncRva());
	}

	char * ExportIteratorNode::NamePtr()
	{
		assert(directory_);
		return reinterpret_cast<char*>(directory_->GetUtil().RvaToDataPtr(*NameRva()));
	}

	ExportIteratorNode::~ExportIteratorNode()
	{
		directory_ = nullptr;
	}

	ExportIteratorNode * ExportIteratorNode::operator->()
	{
		return this;
	}

	const ExportIteratorNode * ExportIteratorNode::operator->() const
	{
		return this;
	}

}  // namespace PeDecoder
