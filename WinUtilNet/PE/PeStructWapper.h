#pragma once
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		ref class PeImage;

		[TypeConverter(ShowPropertiesConverter::typeid)]
		public ref class PeStructDescription:
			public IDescription,
			public StructOffset
		{

		protected:
			int structSize;
			void SetDescription(IntPtr ptr, IntPtr basePtr, int size)
			{
				addr = ptr;
				base = basePtr;
				structSize = size;
			}
		public:
			
			PeStructDescription():StructOffset(IntPtr::Zero, IntPtr::Zero)
			{
				structSize = 0;
			}
			[BrowsableAttribute(false)]
			property IntPtr Offset
			{
				IntPtr get()
				{
					return StructOffset::Offset;
				}
			}
			virtual String ^ GetDescription() override
			{
				if (addr == IntPtr::Zero)
				{
					return String::Empty;
				}
				auto offset = Offset.ToString("X" + 2 * IntPtr::Size);
				if (structSize == 0)
				{
					return String::Format("[{0}]", offset);
				}
				return String::Format("[{0} ({1} Bytes)]", offset, structSize);
			}
			virtual array<String^>^ GetSortList()=0;
		};
		template<typename T>
		public ref class PeStructWapper :public PeStructDescription
		{
		protected:
			typedef PeStructWapper<T> PeStructWapperBase;
			typedef T PeStructWapperType;
			PeImage^ pe;

		internal:
			virtual PeStructWapperType& GetUnmanagedStruct() = 0;

		public:
			PeStructWapper(PeImage^ pe)
			{
				this->pe = pe;
				base = pe->BaseAddress;
			}
			IntPtr GetPeBase()
			{
				return pe->BaseAddress;
			}
		};

		

	}
}
