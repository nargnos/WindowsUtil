#pragma once
#include "IDescription.h"
#include "StructOffset.h"
#include "ShowPropertiesConverter.h"
namespace PeImageClr
{
	[TypeConverter(ShowPropertiesConverter::typeid)]
	public ref class PeStructDescription :
		public IDescription,
		public StructOffset
	{

	protected:
		int structSize;
		void SetDescription(IntPtr ptr, IntPtr basePtr, int size);
	public:

		PeStructDescription();
		[BrowsableAttribute(false)]
		property IntPtr Offset
		{
			IntPtr get()
			{
				return StructOffset::Offset;
			}
		}
		virtual String ^ GetDescription() override;
		virtual array<String^>^ GetSortList() = 0;
	};
}  // namespace PeImageClr
