#pragma once
#include "PeDecoder.h"
namespace PE{
	// 导出表读取器 TODO: 添加一个c++函数名称翻译器,或找一下系统里面有没有现成函数
	class ExportReader
	{
	public:
		ExportReader(PeDecoder& pe);
		ExportReader(PeDecoder& pe, PIMAGE_EXPORT_DIRECTORY exportDirectory);
		~ExportReader();
		PIMAGE_EXPORT_DIRECTORY GetExportDirectory();
		PDWORD CurrentFuncRva();
		PDWORD CurrentNameRva();
		PWORD CurrentNameOrdinals();
		bool Next();
		void Reset();
	private:
		PIMAGE_EXPORT_DIRECTORY exportDirectory;
		PDWORD numberOfFunctions;
		PDWORD funcs;
		PDWORD names;
		PWORD nameOrdinals;
		DWORD currentIndex;
	};
}