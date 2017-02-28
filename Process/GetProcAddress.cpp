#include "stdafx.h"
#include "GetProcAddress.h"
#include <PeImage\PeDecoder.h>
#include <PeImage\ExportDirectory.h>
namespace Process
{
	namespace Overwrite
	{
		void * GetProcAddress(HMODULE module, LPCSTR lpProcName)
		{
			return GetProcAddress(module, lpProcName, [](LPCSTR node, const void* val)
			{
				return strcmp(node, reinterpret_cast<LPCSTR>(val));
			});
		}

		void * GetProcAddress(HMODULE module, const std::function<bool(LPCSTR)>& comp)
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

		void * GetProcAddress(HMODULE module, const void * lpProcName, const std::function<int(LPCSTR, const void*)>& comp)
		{
			assert(module != NULL);
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
