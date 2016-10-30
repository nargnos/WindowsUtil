#include "stdafx.h"
#include "ExportIteratorNode.h"
#include "ExportDirectory.h"
#include "IPeImage.h"
namespace PeDecoder
{
	ExportIteratorNode::ExportIteratorNode(ExportDirectory & directory, DWORD index) :
		directory_(&directory),
		index_(index)
	{
	}

	PDWORD ExportIteratorNode::FuncRva()
	{
		return &directory_->GetFunctionsPtr()[*NameOrdinals()];
	}

	PDWORD ExportIteratorNode::NameRva()
	{
		return &directory_->GetNamesPtr()[index_];
	}

	PWORD ExportIteratorNode::NameOrdinals()
	{
		return &directory_->GetNameOrdinalsPtr()[index_];
	}

	void * ExportIteratorNode::FuncPtr()
	{
		return directory_->GetPe().RvaToDataPtr(*FuncRva());
	}

	char * ExportIteratorNode::NamePtr()
	{
		return reinterpret_cast<char*>(directory_->GetPe().RvaToDataPtr(*NameRva()));
	}

}  // namespace PeDecoder
