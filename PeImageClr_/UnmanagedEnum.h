#pragma once
#include "ShowPropertiesConverter.h"
#include "StructOffset.h"
#include "IDescription.h"
#include "UnmanagedEnumSort.h"
namespace PeImageClr
{
	generic<typename T> where T:Enum
		[TypeConverter(ShowPropertiesConverter::typeid)]
	public ref class UnmanagedEnum :
		public StructOffset,
		public IDescription
	{

		Type^ type;
		typedef UnmanagedEnum<T> UnmanagedEnumType;
	public:
		UnmanagedEnum(IntPtr addr, IntPtr base) :StructOffset(addr, base)
		{
		}

		~UnmanagedEnum()
		{
		}

		property T Value
		{
			T get()
			{
				if (type == nullptr)
				{
					switch (sizeof(T))
					{
					case sizeof(BYTE) :
						type = BYTE::typeid;
						break;
					case sizeof(WORD) :
						type = WORD::typeid;
						break;
					case sizeof(DWORD) :
						type = DWORD::typeid;
						break;
					default:
						throw gcnew System::InvalidCastException();
					}
				}
				return safe_cast<T>(UnmanagedMemory::PtrToStructure(addr, type));
			}
			void set(T value)
			{
				// TODO:
			}
		};


		virtual String ^ GetDescription()
		{
			return String::Format(GetValueSizeStr(sizeof(T)) + "\t{0}", Value);
		}

		virtual array<String^>^ GetSortList()
		{
			return UnmanagedEnumSort::GetSortList();
		}

	};
}  // namespace PeImageClr
