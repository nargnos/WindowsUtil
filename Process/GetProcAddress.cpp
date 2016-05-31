#include "stdafx.h"
#include "GetProcAddress.h"
#include <PeImage\PeDecoder.h>
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

		void * GetProcAddress(HMODULE module, std::function<bool(LPCSTR)> comp)
		{
			assert(module != NULL);
			assert(comp);
			PeDecoder::PeImage pe(module, true);
			if (!pe.IsPe())
			{
				return nullptr;
			}
			auto& exportDir = pe.GetExportDirectory();
			auto end = exportDir->end();

			auto result = _STD find_if(exportDir->begin(), end, [&comp]
			(PeDecoder::ExportIteratorNode& node)
			{
				return comp(node.NamePtr());
			});

			if (end == result)
			{
				return nullptr;
			}
			return result->FuncPtr();
		}

		void * GetProcAddress(HMODULE module, const void * lpProcName, std::function<int(LPCSTR, const void*)> comp)
		{
			assert(module != NULL);
			PeDecoder::PeImage pe(module, true);
			if (!pe.IsPe())
			{
				return nullptr;
			}
			auto& exportDir = pe.GetExportDirectory();
			auto end = exportDir->end();

			auto result = _STD lower_bound(exportDir->begin(), end, lpProcName, [&comp]
			(PeDecoder::ExportIteratorNode& node, const void* val)
			{
				return comp(node.NamePtr(), val) < 0;
			});

			if (result == end || comp(result->NamePtr(), lpProcName) != 0)
			{
				return nullptr;
			}
			return result->FuncPtr();
		}
	}  // namespace Overwrite
}  // namespace Process
