#pragma once
#include "ShowPropertiesConverter.h"
#include "StructOffset.h"
#include "IDescription.h"
#include "ValueArrayConverter.h"
#include "WinSize.h"
#include "UnmanagedArraySort.h"
#include "UnmanagedMemory.h"
namespace PeImageClr
{
	using namespace System::Diagnostics;
	generic<typename T> where T:ValueType
		[TypeConverter(ShowPropertiesConverter::typeid)]
	public ref class UnmanagedArray :
		public StructOffset,
		public IDescription
	{
		static array<String^>^ sortList;
	protected:
		int length;
		typedef UnmanagedArray<T> UnmanagedArrayBase;
	public:
		UnmanagedArray(IntPtr ptr, IntPtr base, int length) :StructOffset(ptr, base)
		{
			Debug::Assert(ptr != IntPtr::Zero && length > 0);
			this->length = length;
			this->addr = ptr;
		}
		T Read(int index)
		{
			return default[index];
		}
		property T default[int]
		{
			T get(int index)
		{
			Debug::Assert(index >= 0 && index <= length);
			return safe_cast<T>(UnmanagedMemory::PtrToStructure(addr + index * sizeof(T), T::typeid));
		};
		void set(int index, T value)
		{
			Debug::Assert(index >= 0 && index <= length);
			UnmanagedMemory::StructureToPtr(value, addr + index * sizeof(T), false);
		};
		};
		[TypeConverter(ValueConverter::typeid)]
		property int Length
		{
			int get()
			{
				return length;
			}
		};
		[TypeConverter(ValueArrayConverter::typeid)]
		property array<T>^ Array
		{
			// FIX: 性能低
			array<T>^ get()
			{
				array<T>^ result = gcnew array<T>(length);
				for (int i = 0; i < result->Length; i++)
				{
					result[i] = default[i];
				}
				return result;
			}
			void set(array<T>^ value)
			{
				if (value != nullptr)
				{
					// 截断多余的
					auto loopTimes = value->Length < length ? value->Length : length;
					for (int i = 0; i < loopTimes; i++)
					{
						default[i] = value[i];
					}
				}
			}
		};
		virtual String ^ GetDescription() override
		{
			return String::Format(GetValueSizeStr(sizeof(T)) + "\t* {0}(D)", length);
		}

		virtual array<String^>^ GetSortList()
		{
			return UnmanagedArraySort::GetSortList();
		}
	};

}  // namespace PeImageClr
