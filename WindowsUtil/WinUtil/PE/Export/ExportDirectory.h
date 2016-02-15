#pragma once
#include "ExportIterator.h"

namespace PE
{

	// TODO: 添加一个c++函数名称翻译器, 或找一下系统里面有没有现成函数

	class ExportDirectory :
		public DataDirectory<ExportDirectory, PIMAGE_EXPORT_DIRECTORY, IMAGE_DIRECTORY_ENTRY_EXPORT>,
		public GetIterator<ExportIterator, ExportDirectory>,
		public IGetValue<PIMAGE_EXPORT_DIRECTORY>
	{
		PDWORD numberOfFunctions;
		PDWORD numberOfNames;
		PDWORD funcTable;
		PDWORD nameTable;
		PWORD nameOrdinalTable;
	public:
		friend GetIteratorBase::Iterator;
		explicit ExportDirectory(PeDecoder* pe);
		~ExportDirectory();

		virtual PIMAGE_EXPORT_DIRECTORY GetValue() override;
		const PDWORD FuncTable();
		const PDWORD NameTable();
		const PWORD OrdinalTable();
		const PDWORD NumberOfFunctions();
		const PDWORD NumberOfNames();
	};
}  // namespace PE
