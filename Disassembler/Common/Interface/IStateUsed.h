#pragma once
#include "InterfaceDefine.h"
namespace Disassembler
{
	template<typename TTrait>
	interface IStateUsed :public Interface
	{
		virtual typename TTrait::TOpcodeDataWapper* GetOpcodeDataWapper() PURE;
		virtual typename TTrait::TStorage* GetStorage() PURE;
	};
}  // namespace Disassembler