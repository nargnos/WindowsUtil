#pragma once
#include "../Common/Common.h"
#include "ExportIterator.h"

namespace PE
{

	// TODO: 添加一个c++函数名称翻译器, 或找一下系统里面有没有现成函数
	template<typename _PeDecoder>
	class ExportDirectory :
		public DataDirectory<_PeDecoder, PIMAGE_EXPORT_DIRECTORY, IMAGE_DIRECTORY_ENTRY_EXPORT>,
		public GetIterator<ExportIterator<ExportDirectory<_PeDecoder>>, ExportDirectory<_PeDecoder>>,
		public IGetValue<PIMAGE_EXPORT_DIRECTORY>
	{
		PDWORD numberOfFunctions;
		PDWORD numberOfNames;
		PDWORD funcsTable;
		PDWORD namesTable;
		PWORD nameOrdinalsTable;
	public:
		friend ExportIterator<ExportDirectory<_PeDecoder>>;
		ExportDirectory(_PeDecoder& pe) :DataDirectory<_PeDecoder, PIMAGE_EXPORT_DIRECTORY, IMAGE_DIRECTORY_ENTRY_EXPORT>(pe)
		{
			auto exportDirectory = GetValue();
			if (exportDirectory)
			{
				numberOfNames = &exportDirectory->NumberOfNames;
				numberOfFunctions = &exportDirectory->NumberOfFunctions;
				funcsTable = reinterpret_cast<PDWORD>(peDecoder.GetRvaData(exportDirectory->AddressOfFunctions));
				namesTable = reinterpret_cast<PDWORD>(peDecoder.GetRvaData(exportDirectory->AddressOfNames));
				nameOrdinalsTable = reinterpret_cast<PWORD>(peDecoder.GetRvaData(exportDirectory->AddressOfNameOrdinals));
			}
			else
			{
				numberOfNames = NULL;
				numberOfFunctions = NULL;
				funcsTable = NULL;
				namesTable = NULL;
				nameOrdinalsTable = NULL;
			}
		}
		~ExportDirectory() {}

		virtual PIMAGE_EXPORT_DIRECTORY GetValue() override
		{
			return data;
		}
		inline const PDWORD FuncTable()
		{
			return funcsTable;
		}
		inline const PDWORD NameTable()
		{
			return namesTable;
		}
		inline const PWORD OrdinalTable()
		{
			return nameOrdinalsTable;
		}
		inline const PDWORD NumberOfFunctions()
		{
			return numberOfFunctions;
		}
		inline const PDWORD NumberOfNames()
		{
			return numberOfNames;
		}
	};
}