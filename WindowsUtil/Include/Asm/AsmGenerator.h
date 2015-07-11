#pragma once
#include <cassert>
#include "..\Process\LazyLoad\LazyLoadSystemApi.h"
namespace Asm
{

#ifndef _WIN64
#endif
	enum class Registers
	{
		// 半字节
		al,
		bl,
		cl,
		dl,
		ah,
		bh,
		ch,
		dh,
		// 64
		r8b,
		r9b,
		r10b,
		r11b,
		r12b,
		r13b,
		r14b,
		r15b,

		// 字节
		ax,
		bx,
		cx,
		dx,
		si,
		di,
		bp,
		sp,
		// 64
		r8w,
		r9w,
		r10w,
		r11w,
		r12w,
		r13w,
		r14w,
		r15w,

		// 双字节
		eax,
		ebx,
		ecx,
		edx,
		esi,
		edi,
		ebp,
		esp,
		// 64
		r8d,
		r9d,
		r10d,
		r11d,
		r12d,
		r13d,
		r14d,
		r15d,

		// 四字节 64
		rax,
		rbx,
		rcx,
		rdx,
		rsi,
		rdi,
		rbp,
		rsp,
		r8,
		r9,
		r10,
		r11,
		r12,
		r13,
		r14,
		r15
	};


	class AsmGenerator
	{
		PUINT8 binBuff;
		bool isGenerated;
		DWORD buffSize;
		PUINT8 oldCur;
		PUINT8 writeCur; // bin写入游标
		PUINT8 endBuff;

		template<typename T>
		void Write(T val);

		void SaveCur(OUT PVOID* save);
		//AsmGenerator& __stdcall OneByteCmd(UINT8 cmdCode, OUT PVOID* currentCodeAddr);
	public:
		AsmGenerator(PVOID buff,DWORD size); // 可以设置一段任意区域写入代码
		~AsmGenerator();
		bool IsGeneratedSuccess();// 表示是否成功创建
		template<typename T>
		T GetCode();
		DWORD CodeSize();
		bool SetWriteCur(PVOID addr); // 设置游标位置, 越界返回false, 并将游标至于边界值
		bool MoveWriteCur(DWORD addr);// 移动游标位置, 越界返回false, 并将游标至于边界值
		const PUINT8 CurrCur();
		const PUINT8 PrevCur();

		// 这样做要实现的就太多了
		//// 跳转到立即数
		//AsmGenerator& __stdcall Jmp_Address(DWORD address, OUT PVOID* currentCodeAddr = NULL);
		//AsmGenerator& __stdcall Jmp_Short_Address(INT8 pos, OUT PVOID* currentCodeAddr = NULL);

		//// push 立即数
		//AsmGenerator& __stdcall Push_Value(DWORD value, OUT PVOID* currentCodeAddr = NULL);
		//// value小于0为ret,否则为ret value
		//AsmGenerator& __stdcall Retn(SHORT value = -1, OUT PVOID* currentCodeAddr = NULL);
		//
		//AsmGenerator& __stdcall Pushad(OUT PVOID* currentCodeAddr = NULL);

		//AsmGenerator& __stdcall Cld(OUT PVOID* currentCodeAddr = NULL);
		//// mov 寄存器,立即数
		//AsmGenerator& __stdcall Mov_Reg_Value(OUT PVOID* currentCodeAddr = NULL);

		//AsmGenerator& __stdcall Nop(OUT PVOID* currentCodeAddr = NULL);

		template<typename T>
		AsmGenerator& __stdcall Emit(T val, OUT PVOID* currentCodeAddr = NULL);

		template<typename T>
		AsmGenerator& __stdcall operator<<(T val);
	};
}
