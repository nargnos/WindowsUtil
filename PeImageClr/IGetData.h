#pragma once
namespace PeImageClr
{
	generic<typename TData>
		interface class IGetData
		{
			property TData Data
			{
				TData get();
			}
		};
}  // namespace PeImageClr
