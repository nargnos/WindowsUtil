#pragma once

namespace Disassembler
{
	// 对应使用的状态工厂关系、数据wapper类型等
	template<typename TDisassembler>
	struct Disassembler_Trait;
	// typedef 状态选择类（把之前的工厂改成了这个，继续这个命名吧） TStateFactory;
	// typedef 状态中用的opcode查找函数包装 TOpcodeDataWapper;
	// typedef 状态中用的存储结构 TStorage;
	// typedef IStateUsed<Disassembler_Trait<反汇编引擎>> TStateUsed; // 在不同状态中用来传递数据的类型
	
	// 状态使用以下的声明方式，使用特化在工厂中使用
	// template<int stateID>
	// class XXXState;
}  // namespace Disassembler