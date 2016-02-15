#pragma once
#include "../Common/Common.h"
namespace PE
{
	// 导出表读取器
	// 只对名字遍历, 因为结构关系, 没有名字的函数会被漏掉

	class ExportDirectory;
	class ExportIterator
	{
		ExportDirectory* exportDir;
		int currentIndex;
	public:
		explicit ExportIterator(ExportDirectory* exportDir);
		~ExportIterator();

		PDWORD CurrentFuncRva();
		PDWORD CurrentNameRva();
		PWORD CurrentNameOrdinals();
		bool Next();
		void Reset();
	};

}  // namespace PE
