#pragma once
#include "DirectoryBase.h"
namespace PeDecoder
{
	class ExportDirectory :
		public DirectoryBase<DataDirectoryEntryType::Export>
	{
	public:
		class iterator;

		ExportDirectory(PeImage& pe, TDataPtr ptr, TSizePtr sizePtr);
		~ExportDirectory() = default;
		const PDWORD GetFunctionsPtr() const;
		const PDWORD GetNamesPtr() const;
		const PWORD GetNameOrdinalsPtr() const;
		const PDWORD GetNumberOfFunctionsPtr() const;
		const PDWORD GetNumberOfNamesPtr() const;
		iterator begin() const;
		iterator end() const;
	protected:
		PDWORD numberOfFunctions_;
		PDWORD numberOfNames_;
		PDWORD funcTable_;
		PDWORD nameTable_;
		PWORD nameOrdinalTable_;
	};

	class ExportIteratorNode
	{
	public:
		friend class ExportDirectory::iterator;
		ExportIteratorNode(const ExportDirectory& directory, DWORD index);
		PDWORD FuncRva() const;
		PDWORD NameRva() const;
		PWORD NameOrdinals() const;
	private:
		bool Equal(const ExportIteratorNode & val) const;
		void Increment();
		void Decrement();
		void Advance(int n);
		int DistanceTo(const ExportIteratorNode & val);
		bool InRange() const;

		const ExportDirectory& directory_;
		DWORD index_;
	};
	class ExportDirectory::iterator :
		public iterator_facade<ExportDirectory::iterator, ExportIteratorNode, random_access_traversal_tag>
	{
	public:
		friend class iterator_core_access;
		iterator(const ExportDirectory& directory, DWORD index);

		~iterator() = default;
	private:
		bool equal(const iterator & val) const;
		void increment();
		void decrement();
		void advance(int n);
		difference_type distance_to(const iterator & val);
		reference dereference();
		ExportIteratorNode& GetStore();
		const ExportIteratorNode& GetStore() const;
		ExportIteratorNode node_;
	};

}  // namespace PeDecoder
