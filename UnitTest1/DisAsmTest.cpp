
#include "CppUnitTest.h"
#include <iostream>
#include <string>
#include <strstream>
#include <DisAsm\Asm\Asm.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTest1
{

	// ≤‚ ‘32Œª≤ø∑÷
	TEST_CLASS(TestDisAsm)
	{

	public:
		TEST_METHOD(DA_Test)
		{
			BYTE code[] = { 0x66, 0x55,0x8B,0xEC,0x6A,0xFF,0x68,0xE8,0x65,0x99,0x00,0x64,0xA1,0x00,0x00,0x00,0x00,
				0x50,0x81,0xEC,0x18,0x01,0x00,0x00,0x53,0x56,0x57,0x8D,0xBD,0xDC,0xFE,0xFF,0xFF,
				0xB9,0x46,0x00,0x00,0x00,0xB8,0xCC,0xCC,0xCC,0xCC,0xF3,0xAB,0xA1,0x08,0x11,0x9A,
				0x00,0x33,0xC5,0x89,0x45,0xF0,0x50,0x8D,0x45,0xF4,0x64,0xA3,0x00,0x00,0x00,0x00,
				0xC7,0x45,0xE8,0x01,0x00,0x00,0x00,0x6A,0x34,0x8D,0x4D,0xAC,0xE8,0x1B,0x48,0xFE,
				0xFF,0x6A,0x01,0x8D,0x4D,0xAC,0xE8,0x6B,0x48,0xFE,0xFF,0xC7,0x45,0xFC,0x00,0x00,
				0x00,0x00
			};
			auto fac = make_shared<StateFactory>();

			auto ai = make_shared<AsmInstruction>(fac, true, true);
			ai->Init(code);
			OpcodeReader opReader;
			opReader.Read(ai);
		}
		TEST_METHOD(GetReg_Test)
		{
			AsmOpcodeDataWapper wapper;
			LPCSTR str = NULL;
			// reg
			str = wapper.GetRegisterName(REG_AL);
			Assert::AreEqual(str, "al");
			str = wapper.GetRegisterName(REG_AX);
			Assert::AreEqual(str, "ax");
			str = wapper.GetRegisterName(REG_EAX);
			Assert::AreEqual(str, "eax");
			str = wapper.GetRegisterName(REG_RAX);
			Assert::AreEqual(str, "rax");
			str = wapper.GetRegisterName(REG_MM0);
			Assert::AreEqual(str, "mm0");
			str = wapper.GetRegisterName(REG_XMM0);
			Assert::AreEqual(str, "xmm0");
			str = wapper.GetRegisterName(REG_CL);
			Assert::AreEqual(str, "cl");
			str = wapper.GetRegisterName(REG_CX);
			Assert::AreEqual(str, "cx");
			str = wapper.GetRegisterName(REG_ECX);
			Assert::AreEqual(str, "ecx");
			str = wapper.GetRegisterName(REG_RCX);
			Assert::AreEqual(str, "rcx");
			str = wapper.GetRegisterName(REG_MM1);
			Assert::AreEqual(str, "mm1");
			str = wapper.GetRegisterName(REG_XMM1);
			Assert::AreEqual(str, "xmm1");
			str = wapper.GetRegisterName(REG_DL);
			Assert::AreEqual(str, "dl");
			str = wapper.GetRegisterName(REG_DX);
			Assert::AreEqual(str, "dx");
			str = wapper.GetRegisterName(REG_EDX);
			Assert::AreEqual(str, "edx");
			str = wapper.GetRegisterName(REG_RDX);
			Assert::AreEqual(str, "rdx");
			str = wapper.GetRegisterName(REG_MM2);
			Assert::AreEqual(str, "mm2");
			str = wapper.GetRegisterName(REG_XMM2);
			Assert::AreEqual(str, "xmm2");
			str = wapper.GetRegisterName(REG_BL);
			Assert::AreEqual(str, "bl");
			str = wapper.GetRegisterName(REG_BX);
			Assert::AreEqual(str, "bx");
			str = wapper.GetRegisterName(REG_EBX);
			Assert::AreEqual(str, "ebx");
			str = wapper.GetRegisterName(REG_RBX);
			Assert::AreEqual(str, "rbx");
			str = wapper.GetRegisterName(REG_MM3);
			Assert::AreEqual(str, "mm3");
			str = wapper.GetRegisterName(REG_XMM3);
			Assert::AreEqual(str, "xmm3");
			str = wapper.GetRegisterName(REG_AH);
			Assert::AreEqual(str, "ah");
			str = wapper.GetRegisterName(REG_SP);
			Assert::AreEqual(str, "sp");
			str = wapper.GetRegisterName(REG_ESP);
			Assert::AreEqual(str, "esp");
			str = wapper.GetRegisterName(REG_RSP);
			Assert::AreEqual(str, "rsp");
			str = wapper.GetRegisterName(REG_MM4);
			Assert::AreEqual(str, "mm4");
			str = wapper.GetRegisterName(REG_XMM4);
			Assert::AreEqual(str, "xmm4");
			str = wapper.GetRegisterName(REG_CH);
			Assert::AreEqual(str, "ch");
			str = wapper.GetRegisterName(REG_BP);
			Assert::AreEqual(str, "bp");
			str = wapper.GetRegisterName(REG_EBP);
			Assert::AreEqual(str, "ebp");
			str = wapper.GetRegisterName(REG_RBP);
			Assert::AreEqual(str, "rbp");
			str = wapper.GetRegisterName(REG_MM5);
			Assert::AreEqual(str, "mm5");
			str = wapper.GetRegisterName(REG_XMM5);
			Assert::AreEqual(str, "xmm5");
			str = wapper.GetRegisterName(REG_DH);
			Assert::AreEqual(str, "dh");
			str = wapper.GetRegisterName(REG_SI);
			Assert::AreEqual(str, "si");
			str = wapper.GetRegisterName(REG_ESI);
			Assert::AreEqual(str, "esi");
			str = wapper.GetRegisterName(REG_RSI);
			Assert::AreEqual(str, "rsi");
			str = wapper.GetRegisterName(REG_MM6);
			Assert::AreEqual(str, "mm6");
			str = wapper.GetRegisterName(REG_XMM6);
			Assert::AreEqual(str, "xmm6");
			str = wapper.GetRegisterName(REG_BH);
			Assert::AreEqual(str, "bh");
			str = wapper.GetRegisterName(REG_DI);
			Assert::AreEqual(str, "di");
			str = wapper.GetRegisterName(REG_EDI);
			Assert::AreEqual(str, "edi");
			str = wapper.GetRegisterName(REG_RDI);
			Assert::AreEqual(str, "rdi");
			str = wapper.GetRegisterName(REG_MM7);
			Assert::AreEqual(str, "mm7");
			str = wapper.GetRegisterName(REG_XMM7);
			Assert::AreEqual(str, "xmm7");


			str = wapper.GetRegisterName(REG_R8L);
			Assert::AreEqual(str, "r8l");
			str = wapper.GetRegisterName(REG_R8W);
			Assert::AreEqual(str, "r8w");
			str = wapper.GetRegisterName(REG_R8D);
			Assert::AreEqual(str, "r8d");
			str = wapper.GetRegisterName(REG_R8);
			Assert::AreEqual(str, "r8");
			str = wapper.GetRegisterName(REG_XMM8);
			Assert::AreEqual(str, "xmm8");
			str = wapper.GetRegisterName(REG_R9L);
			Assert::AreEqual(str, "r9l");
			str = wapper.GetRegisterName(REG_R9W);
			Assert::AreEqual(str, "r9w");
			str = wapper.GetRegisterName(REG_R9D);
			Assert::AreEqual(str, "r9d");
			str = wapper.GetRegisterName(REG_R9);
			Assert::AreEqual(str, "r9");
			str = wapper.GetRegisterName(REG_XMM9);
			Assert::AreEqual(str, "xmm9");
			str = wapper.GetRegisterName(REG_R10L);
			Assert::AreEqual(str, "r10l");
			str = wapper.GetRegisterName(REG_R10W);
			Assert::AreEqual(str, "r10w");
			str = wapper.GetRegisterName(REG_R10D);
			Assert::AreEqual(str, "r10d");
			str = wapper.GetRegisterName(REG_R10);
			Assert::AreEqual(str, "r10");
			str = wapper.GetRegisterName(REG_XMM10);
			Assert::AreEqual(str, "xmm10");
			str = wapper.GetRegisterName(REG_R11L);
			Assert::AreEqual(str, "r11l");
			str = wapper.GetRegisterName(REG_R11W);
			Assert::AreEqual(str, "r11w");
			str = wapper.GetRegisterName(REG_R11D);
			Assert::AreEqual(str, "r11d");
			str = wapper.GetRegisterName(REG_R11);
			Assert::AreEqual(str, "r11");
			str = wapper.GetRegisterName(REG_XMM11);
			Assert::AreEqual(str, "xmm11");
			str = wapper.GetRegisterName(REG_R12L);
			Assert::AreEqual(str, "r12l");
			str = wapper.GetRegisterName(REG_R12W);
			Assert::AreEqual(str, "r12w");
			str = wapper.GetRegisterName(REG_R12D);
			Assert::AreEqual(str, "r12d");
			str = wapper.GetRegisterName(REG_R12);
			Assert::AreEqual(str, "r12");
			str = wapper.GetRegisterName(REG_XMM12);
			Assert::AreEqual(str, "xmm12");
			str = wapper.GetRegisterName(REG_R13L);
			Assert::AreEqual(str, "r13l");
			str = wapper.GetRegisterName(REG_R13W);
			Assert::AreEqual(str, "r13w");
			str = wapper.GetRegisterName(REG_R13D);
			Assert::AreEqual(str, "r13d");
			str = wapper.GetRegisterName(REG_R13);
			Assert::AreEqual(str, "r13");
			str = wapper.GetRegisterName(REG_XMM13);
			Assert::AreEqual(str, "xmm13");
			str = wapper.GetRegisterName(REG_R14L);
			Assert::AreEqual(str, "r14l");
			str = wapper.GetRegisterName(REG_R14W);
			Assert::AreEqual(str, "r14w");
			str = wapper.GetRegisterName(REG_R14D);
			Assert::AreEqual(str, "r14d");
			str = wapper.GetRegisterName(REG_R14);
			Assert::AreEqual(str, "r14");
			str = wapper.GetRegisterName(REG_XMM14);
			Assert::AreEqual(str, "xmm14");
			str = wapper.GetRegisterName(REG_R15L);
			Assert::AreEqual(str, "r15l");
			str = wapper.GetRegisterName(REG_R15W);
			Assert::AreEqual(str, "r15w");
			str = wapper.GetRegisterName(REG_R15D);
			Assert::AreEqual(str, "r15d");
			str = wapper.GetRegisterName(REG_R15);
			Assert::AreEqual(str, "r15");
			str = wapper.GetRegisterName(REG_XMM15);
			Assert::AreEqual(str, "xmm15");

			str = wapper.GetRegisterName(REG_SPL);
			Assert::AreEqual(str, "spl");
			str = wapper.GetRegisterName(REG_BPL);
			Assert::AreEqual(str, "bpl");
			str = wapper.GetRegisterName(REG_SIL);
			Assert::AreEqual(str, "sil");
			str = wapper.GetRegisterName(REG_DIL);
			Assert::AreEqual(str, "dil");

			// seg
			str = wapper.GetSegName(SEG_CS);
			Assert::AreEqual(str, "cs");
			str = wapper.GetSegName(SEG_DS);
			Assert::AreEqual(str, "ds");
			str = wapper.GetSegName(SEG_ES);
			Assert::AreEqual(str, "es");
			str = wapper.GetSegName(SEG_FS);
			Assert::AreEqual(str, "fs");
			str = wapper.GetSegName(SEG_GS);
			Assert::AreEqual(str, "gs");
			str = wapper.GetSegName(SEG_SS);
			Assert::AreEqual(str, "ss");


		}

	private:

	};
}