#include "stdafx.h"
#include <string>
#include "CppUnitTest.h"
#include <PeImage\PeDecoder.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace PeDecoder;
using std::ostringstream;
using std::endl;
namespace PeImageLibTest
{
	TEST_CLASS(PeImageTest)
	{
	public:
		PeImageTest() :
			pe_(GetModuleHandle(L"user32.dll"), true)
		{
			wchar_t str[MAX_PATH];
			GetModuleFileName(GetModuleHandle(L"user32.dll"), str, sizeof(str));
			Logger::WriteMessage(str);
			Assert::IsTrue(pe_.IsPe());

		}
		TEST_METHOD(ReadDosHeader)
		{
			auto& dosHeader = pe_.GetDosHeader();
			auto ptr = dosHeader->GetPtr();
			ostringstream out;
			out << "e_lfanew:" << std::hex << ptr->e_lfanew << endl;

			auto& dosStub = dosHeader->GetDosStub();
			DWORD size = 0;
			if (dosStub)
			{
				size = dosStub->GetSize();
			}
			out << std::dec << "stub size:" << size;
			Logger::WriteMessage(out.str().c_str());
		}
		TEST_METHOD(ReadNtHeader)
		{
			auto& nt = pe_.GetNtHeader();
			auto& de = nt->GetDataDirectoryEntries();
			ostringstream out;
			for each (auto& var in *de)
			{
				out << std::hex << "ADDR:" << var.VirtualAddress << " SIZE:" << var.Size << endl;
			}
			Logger::WriteMessage(out.str().c_str());
		}
		TEST_METHOD(ReadSections)
		{
			auto& sections = pe_.GetSections();
			ostringstream out;
			for each (auto& var in *sections)
			{
				out << "SECTION: " << std::string((char*)&var.Name) << endl;
			}
			Logger::WriteMessage(out.str().c_str());

		}
		TEST_METHOD(ReadExportDirectory)
		{
			PeDecoder::ExportDirectory exportDir(pe_);

			if (exportDir)
			{
				ostringstream out;
				out << "Export:" << endl << "----------" << endl;
				for each (auto& var in exportDir)
				{
					auto name = (char*)pe_.RvaToDataPtr(*var.NameRva());
					out << name << endl;
				}
				Logger::WriteMessage(out.str().c_str());
			}
			else
			{
				Logger::WriteMessage("Export Not Exist");
			}
		}
		TEST_METHOD(ReadImportDirectory)
		{
			PeDecoder::ImportDirectory importDir(pe_);
			if (!importDir)
			{
				Logger::WriteMessage("Export Not Exist");
				return;
			}
			auto type = pe_.GetImageType();

			ostringstream out;
			for each (auto& var in importDir)
			{
				out << endl << "# " << var.GetName() << endl;
				out << "----------" << endl;
				if (type == ImageType::PE32)
				{
					for each (auto& val in var.GetThunk32())
					{
						if (!val.IsSnapByOrdinal())
						{
							auto name = val.GetImportByName();
							out << (PCHAR)name->Name << " - "
								<< val.GetFuncAddress() << endl;
						}
						else
						{
							out << val.GetOrdinal() << " - " << val.GetFuncAddress() << endl;
						}

					}
				}
				else
				{
					for each (auto& val in var.GetThunk64())
					{
						if (!val.IsSnapByOrdinal())
						{
							auto name = val.GetImportByName();
							out << (PCHAR)name->Name << " - "
								<< val.GetFuncAddress() << endl;
						}
						else
						{
							out << val.GetOrdinal() << " - " << val.GetFuncAddress() << endl;
						}
					}
				}
				out << "----------" << endl;
			}

			Logger::WriteMessage(out.str().c_str());
		}

		TEST_METHOD(ReadRelocDirectory)
		{
			PeDecoder::RelocDirectory reloc(pe_);
			if (reloc)
			{
				ostringstream out;
				for each (auto& var in reloc)
				{
					out << "Rva: " << (void*)var.GetPtr()->VirtualAddress <<
						" Size of Block:" << std::hex << var.GetPtr()->SizeOfBlock << "h" <<
						" Count: " << std::dec << var.GetCount() << endl;
					for each (auto& node in var)
					{
						out << (void*)node.CurrentRelocRva() << " : " << node.CurrentType() << endl;
					}
				}
				Logger::WriteMessage(out.str().c_str());

			}

		}
		TEST_METHOD(ReadResourceDirectory)
		{
			PeDecoder::ResourceDirectory res(pe_);
			if (res)
			{
				for each (auto& var in res)
				{
					if (var.NameIsString())
					{
					}
				}
			}
		}
	private:
		PeImage pe_;

	};
}