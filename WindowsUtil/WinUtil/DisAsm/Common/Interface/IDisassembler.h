#pragma once
#include "InterfaceDefine.h"
#include "IInstruction.h"
namespace Disassembler
{
	/// <summary>
	/// 反汇编引擎接口
	/// </summary>
	interface IDisassembler :public Interface
	{
		/// <summary>
		/// 将指定位置的机器码转换成指令,转换完成后需要用
		/// </summary>
		/// <param name="pos">机器码起始位置</param>
		/// <returns>返回读取的指令长度，0表示转换失败</returns>
		virtual unsigned int Parse(void* pos) PURE;

		/// <summary>
		/// 获取返回结果
		/// </summary>
		virtual unique_ptr<IInstruction> GetResult() const PURE;

	};
}  // namespace Disassembler
