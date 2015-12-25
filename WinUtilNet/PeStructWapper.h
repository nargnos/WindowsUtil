#pragma once
namespace NAMESPACE {
	namespace PeDecoderWapper
	{
		ref class PeImage;
		public interface class IReset
		{
			void Reset()=0;
		};

		template<typename T>
		public ref class PeStructWapper
		{
		protected:
			typedef PeStructWapper<T> PeStructWapperBase;
			typedef T PeStructWapperType;
			PeImage^ pe;
		internal:
			virtual PeStructWapperType& GetUnmanagedStruct()=0;
			
		public:
			PeStructWapper(PeImage^ pe)
			{
				this->pe = pe;
			}
			
		};
	}
}
