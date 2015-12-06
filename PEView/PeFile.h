#pragma once
#include <PE\PeDecoder.h>
#include <memory>
#include <list>
#include <msclr\marshal_cppstd.h>  
#include "PeDataReader.h"
#include "PeDataCommon.h"
namespace PEView
{
	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::Collections::Generic;
	using namespace msclr::interop;

	extern std::shared_ptr<PE::PeDecoder> peDecoder;

	ref class PeFile
	{
	
		System::IO::FileInfo^ fileInfo;
		long long mapSize;
		bool isReadOnly;

		IntPtr^ pePtr = IntPtr::Zero;
		String^ exePath;
		PeDataReader<_ExeInfo>^ exeInfoReader;
		List<_ExeInfo^>^ GetExeInfoData();


		PeDataReader<_PeData>^ dosHeaderReader;
		List<_PeData^>^ GetDosHeaderData();

		PeDataReader<_PeData>^ ntHeaderReader;
		List<_PeData^>^ GetNtHeaderData();

		PeDataReader<_PeData>^ fileHeaderReader;
		List<_PeData^>^ GetFileHeaderData();

		PeDataReader<_PeData>^ optionalHeaderReader;
		List<_PeData^>^ GetOptionalHeaderData();

		String ^ GetDataDirectoriesFieldName(int index, bool isRvaAddress);

		PeDataReader<_PeData>^ dataDirectoriesReader;
		List<_PeData^>^ GetDataDirectoriesData();

		SectionDataReader^ sectionReader;
		List<_SectionData^>^ GetSectionData();
	public:
		PeFile();
		~PeFile();
		event Action^ Opened;
		event Action^ Closed;

		void OpenFile(System::String^ filePath, bool isReadOnly);
		void CloseFile();
		void Reset() 
		{
			exeInfoReader = nullptr;
			dosHeaderReader = nullptr;
			ntHeaderReader = nullptr;
			fileHeaderReader = nullptr;
			optionalHeaderReader = nullptr;
			dataDirectoriesReader = nullptr;
			sectionReader = nullptr;
		}
		property IntPtr ExePtr
		{
			IntPtr get()
			{
				return IntPtr(peDecoder->GetBase());
			}
		};
		property long long MapSize
		{
			long long get()
			{
				return mapSize;
			}
		};

		property String^ ExePath 
		{			
			String^ get()
			{
				return exePath;
			}
		};

		property PeDataReader<_ExeInfo>^ ExeInfo
		{
			PeDataReader<_ExeInfo>^ get()
			{
				if (!exeInfoReader)
				{
					exeInfoReader = gcnew PeDataReader<_ExeInfo>(GetExeInfoData());
				}
				return exeInfoReader;
			}
		};

		property PeDataReader<_PeData>^ DosHeader
		{
			PeDataReader<_PeData>^ get()
			{
				if (!dosHeaderReader)
				{
					dosHeaderReader = gcnew PeDataReader<_PeData>(GetDosHeaderData());
				}
				return dosHeaderReader;
			}
		};

		property PeDataReader<_PeData>^ NtHeader
		{
			PeDataReader<_PeData>^ get()
			{
				if (!ntHeaderReader)
				{
					ntHeaderReader = gcnew PeDataReader<_PeData>(GetNtHeaderData());
				}
				return ntHeaderReader;
			}
		};

		property PeDataReader<_PeData>^ FileHeader
		{
			PeDataReader<_PeData>^ get()
			{
				if (!fileHeaderReader)
				{
					fileHeaderReader = gcnew PeDataReader<_PeData>(GetFileHeaderData());
				}
				return fileHeaderReader;
			}
		}; 
		property PeDataReader<_PeData>^ OptionalHeader
		{
			PeDataReader<_PeData>^ get()
			{
				if (!optionalHeaderReader)
				{
					optionalHeaderReader = gcnew PeDataReader<_PeData>(GetOptionalHeaderData());
				}
				return optionalHeaderReader;
			}
		};
		property PeDataReader<_PeData>^ DataDirectories
		{
			PeDataReader<_PeData>^ get()
			{
				if (!dataDirectoriesReader)
				{
					dataDirectoriesReader = gcnew PeDataReader<_PeData>(GetDataDirectoriesData());
				}
				return dataDirectoriesReader;
			}
		};
		

		property SectionDataReader^ Section
		{
			SectionDataReader^ get()
			{
				if (!sectionReader)
				{
					sectionReader = gcnew SectionDataReader(GetSectionData());
				}
				return sectionReader;
			}
		};
	};

}