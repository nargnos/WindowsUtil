#pragma once
#include "InterfaceDefine.h"
namespace Disassembler
{
	interface IStorage :public Interface
	{
		virtual void SetInitialPosition(const void* pos) PURE;
		virtual const unsigned char* GetCurrentPosition() PURE;
		/// <summary>
		/// 将读取位置移动到下一个字节
		/// </summary>
		virtual void NextByte() PURE;
		virtual void Seek(int offset) PURE;
		virtual void Clear() PURE;
		virtual bool IsSuccess() PURE;
	};
}  // namespace Disassembler