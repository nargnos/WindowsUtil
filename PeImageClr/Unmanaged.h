#pragma once


namespace PeImageClr
{
	using namespace System;
	using namespace System::Runtime::InteropServices;
	using namespace cli;
	using namespace System::Diagnostics;
	ref class Unmanaged
	{
	public:
		generic<typename T>
		static T PtrToStructure(IntPtr ptr)
		{
			return Marshal::PtrToStructure<T>(ptr);
		}

	private:
		Unmanaged()
		{
		}
	};
}  // namespace PeImageClr
