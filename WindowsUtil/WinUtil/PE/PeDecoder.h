#pragma once
#include <cassert>
#include <Windows.h>
#include <WinBase.h>
#include <WinTrust.h>
#include <memory>
namespace PE
{

	class DosHeader;
	class NtHeader;
	class SectionHeaders;
	class RelocDirectory;
	class ExportDirectory;
	class ImportDirectory;
	class ResourceDirectory;
	class EntryExceptionDirectory;
	class SecurityDirectory;
	class DebugDirectory;
	class ArchitectureDirectory;
	class GlobalptrDirectory;
	class TlsDirectory;
	class LoadConfigDirectory;
	class BoundImportDirectory;
	class IatDirectory;
	class DelayImportDirectory;
	class ComDescriptorDirectory;

	// PE解析器, 这个用来读本地程序或文件
	// TODO: 数据目录解析只完成了导入导出表\资源\重定位\节的读取器
	class PeDecoder
	{


		PBYTE base;

		bool isMapped;
		bool isPE;
		bool hasNtHeader32;
		bool isBinded;
		bool isAttached;
		void BindPtr();
		
	public:
		template<typename T>
		class PeStructInstance
		{
			_STD shared_ptr<T> data;
			PeDecoder* peDecoder;
			void Bind(PeDecoder* const peDecoder)
			{
				this->peDecoder = peDecoder;
			}
			void Reset()
			{
				data = NULL;
				/*if (data)
				{
					data->Reset();
				}*/
			}
			PeStructInstance() = default;
			PeStructInstance(PeStructInstance&) = delete;
			void operator =(PeStructInstance&) = delete;
		public:
			friend PeDecoder;

			_STD shared_ptr<T> operator->()
			{
				if (!data)
				{
					if (peDecoder->isAttached)
					{
						data = _STD make_shared<T>(*peDecoder);
					}

				}
				return data;
			}
			_STD shared_ptr<T> operator()()
			{
				return this->operator->();
			}

		};
		PeDecoder();
		~PeDecoder() = default;
		void Clear();
		PeDecoder(PeDecoder& pe) = delete;
		bool Attach(PVOID base, bool isMapped);
		void Dettach();
		PVOID GetBase();
		PeStructInstance<DosHeader> GetDosHeader;
		PeStructInstance<NtHeader> GetNtHeader;
		PeStructInstance<SectionHeaders> GetSection;
		PeStructInstance<RelocDirectory> GetReloc;
		PeStructInstance<ExportDirectory> GetExport;
		PeStructInstance<ImportDirectory> GetImport;
		PeStructInstance<ResourceDirectory> GetResource;
		PeStructInstance<EntryExceptionDirectory> GetException;
		PeStructInstance<SecurityDirectory> GetSecurity;
		PeStructInstance<DebugDirectory> GetDebug;
		PeStructInstance<ArchitectureDirectory> GetArchitecture;
		PeStructInstance<GlobalptrDirectory> GetGlobalptr;
		PeStructInstance<TlsDirectory> GetTls;
		PeStructInstance<LoadConfigDirectory> GetLoadConfig;
		PeStructInstance<BoundImportDirectory> GetBoundImport;
		PeStructInstance<IatDirectory> GetIat;
		PeStructInstance<DelayImportDirectory> GetDelayImport;
		PeStructInstance<ComDescriptorDirectory> GetComDescriptor;

		bool IsMapped();
		bool HasNtHeader32();
		bool IsPE();
		bool IsAttached();
		PIMAGE_SECTION_HEADER RvaToSection(DWORD rva);
		PIMAGE_SECTION_HEADER OffsetToSection(DWORD fileOffset);
		DWORD RvaToOffset(DWORD rva);
		DWORD OffsetToRva(DWORD fileOffset);
		PVOID GetRvaData(DWORD rva);
		PIMAGE_DATA_DIRECTORY GetDataDirectory(DWORD index);
		PVOID DirectoryEntryToData(DWORD index, PDWORD* size);

		// TODO: 需要添加的内容（想到了再补充
		// 将文件载入到内存运行（可从其它文件载入用作代码（载入其它代码块）（需要重定位等
		// 编辑各个子结构（在各个分支类型里写，包括文件（F）中和内存（M）中
		// 统计结构间隙（可找pe头中不需要的部分（FM
		// 移动入口点（加代码，需要找间隙或添加节（FM
		// 移动入口点（复制代码，需要找间隙添加节和读代码长度（hook部分已写读长度（若复制到涉及重定位的地方需要处理一下（FM
		// 代码添加（FM
		// 修改特征
		// 保存修改

		// 以下每个结构自带 改查（查已写
		// 凡是有增自带删

		// DosHeader
		// 删除dos stub （需要重定位和移动节（F

		// NtHeader
		// 移动（这个移动会带动后面的结构一起移动（F

		// Section
		// 移动节的位置（需要重定位（FM
		// 增加（F
		// 删除部分需要能把原先内容合并到其它地方去
		// 简单加解密（需要添加解密代码作为入口点（重定位部分需要保存并删除，使用解密代码重定位（F

		// Reloc
		// 从文件映射到内存用的重定位
		// 将节移动后需要的重定位（FM
		// 增加（F
		// 只能直接删，不管之后能不能运行

		// Export
		// 修改导出名（F
		// 添加导出（文件隐含函数导出（F
		// 删导出（F

		// Import
		// 添加导入（F
		// 删除导入（如果是删已有的导入会比较复杂（遍历重定位表找对应位置？）（F

		// Resource
		// 定位修改设置（F


	};

}