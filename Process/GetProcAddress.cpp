#include "stdafx.h"
#include "GetProcAddress.h"
#include <PeImage\PeDecoder.h>
#include <PeImage\ExportDirectory.h>
namespace Process
{
	namespace Overwrite
	{
		_Ret_maybenull_ void* GetProcAddress(_In_ _Notnull_ HMODULE module,
			_In_ _Notnull_ LPCSTR lpProcName)
		{
			return GetProcAddress(module, lpProcName, [](LPCSTR node, const void* val)
			{
				return strcmp(node, reinterpret_cast<LPCSTR>(val));
			});
		}

		_Ret_maybenull_ void* GetProcAddress(_In_ _Notnull_ HMODULE module,
			const _STD function<bool(LPCSTR)>& comp)
		{
			assert(module != NULL);
			assert(comp);
			auto pe = PeDecoder::PeImage::Create(module, true);
			if (!pe)
			{
				return nullptr;
			}
			auto exportDir = PeDecoder::ExportDirectory::Create(pe);

			if (!exportDir)
			{
				return nullptr;
			}
			auto end = exportDir->end();

			auto result = _STD find_if(exportDir->begin(), end, [&comp]
			(auto& node)
			{
				return comp(node->NamePtr());
			});

			if (end == result)
			{
				return nullptr;
			}
			return result->FuncPtr();
		}

		_Ret_maybenull_ void* GetProcAddress(_In_ _Notnull_ HMODULE module,
			_In_ _Notnull_ const void* lpProcName,
			const _STD function<int(LPCSTR, const void*)>& comp)
		{
			assert(module != NULL);
			assert(lpProcName != nullptr);
			auto pe = PeDecoder::PeImage::Create(module, true);
			if (!pe)
			{
				return nullptr;
			}
			auto exportDir = PeDecoder::ExportDirectory::Create(pe);

			if (!exportDir)
			{
				return nullptr;
			}
			auto end = exportDir->end();

			auto result = _STD lower_bound(exportDir->begin(), end, lpProcName, [&comp]
			(auto& node, const void* val)
			{
				return comp(node->NamePtr(), val) < 0;
			});

			if (result == end || comp(result->NamePtr(), lpProcName) != FALSE)
			{
				return nullptr;
			}
			return result->FuncPtr();
		}

	}  // namespace Overwrite
}  // namespace Process
