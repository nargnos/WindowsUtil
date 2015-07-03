#pragma once
#include "..\PeDecoder.h"
namespace PE{
	namespace Export{

		// 导出表读取器 TODO: 添加一个c++函数名称翻译器,或找一下系统里面有没有现成函数
		// 只对名字遍历, 因为结构关系, 没有名字的函数会被漏掉
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
			PDWORD FuncTable();
			PDWORD NameTable();
			PWORD OrdinalTable();
			PDWORD NumberOfFunctions();
			PDWORD NumberOfNames();
		private:
			PIMAGE_EXPORT_DIRECTORY exportDirectory;
			PDWORD numberOfFunctions;
			PDWORD numberOfNames;
			PDWORD funcs;
			PDWORD names;
			PWORD nameOrdinals;
			int currentIndex;
		};
		FARPROC GetProcAddress(PeDecoder& pe, LPCSTR lpProcName); // 二分查找
		FARPROC GetProcAddress(HMODULE module, LPCSTR lpProcName);
		FARPROC GetProcAddress(HMODULE module, PVOID compareName, bool compareCallback(PVOID compare, LPCSTR procName)); // 顺序查找, 带比较器, 返回true表示值相同
		FARPROC GetProcAddress(PeDecoder& pe, PVOID compareName, bool compareCallback(PVOID compare, LPCSTR procName));
	}
}