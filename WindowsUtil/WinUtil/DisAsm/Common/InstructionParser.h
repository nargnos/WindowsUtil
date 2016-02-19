#pragma once
#include "Common.h"
#include "Interface\IParseEngine.h"
#include "Interface\IInstruction.h"

class InstructionParser
{
public:
	/*/// <summary>
	/// 机器码解析器
	/// </summary>
	/// <param name="parseEngine">反汇编引擎</param>
	InstructionParser(const shared_ptr<IParseEngine>& parseEngine);*/

	/// <summary>
	/// 将指定位置的机器码转换成指令标识
	/// </summary>
	/// <param name="pos">机器码起始位置</param>
	/// <param name="result">当转换时，读取的中间数据会覆盖并存储在内，即使转换失败中间数据也不做清空处理</param>
	/// <returns>指示是否转换成功</returns>
	bool TryParse(void* pos, _Out_ shared_ptr<IInstruction>& result);


private:
	shared_ptr<IParseEngine> engine;
};
//
//class InstructionParser
//{
//public:
//
//	InstructionParser()
//	{
//	}
//	// 返回读取长度, 读取信息保存在inst参数里
//	int Read(const shared_ptr<Instruction>& inst) const
//	{
//		auto current = inst->GetFactory()->GetBeginStateInstance();
//		while (current != NULL && current->IsEnd())
//		{
//			current = current->Next(inst);
//			assert(current);  // TODO: grp/esc类指令代码未写，读到这类指令会有NULL
//		}
//		return inst->ReadCount();
//	}
//	~InstructionParser()
//	{
//	}
//};

