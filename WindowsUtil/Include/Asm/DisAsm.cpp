#include "DisAsm.h"
namespace Asm
{
	DisAsm::_PrefixRecord::_PrefixRecord()
	{
		Reset();
	}
	void DisAsm::_PrefixRecord::Reset()
	{
		Exist[0] = Exist[1] = Exist[2] = Exist[3] = false;
	}

	BYTE DisAsm::_PrefixRecord::Record(BYTE prefix)
	{
		auto group = PrefixByteToGroup(prefix);
		assert(group > 0);
		if (Exist[group - 1])
		{
			// 存在
			return group;
		}
		Exist[group - 1] = true;
		return 0;
	}

	// 初始化结构
	DisAsm::DisAsm()
	{
	}

	bool DisAsm::PushPrefix(BYTE prefix)
	{
		auto group = prefixRecord.Record(prefix);
		if (group)
		{
			// 冲突
			BYTE tmpPrefix;
			do
			{
				tmpPrefix = prefixs.front();
				prefixs.pop();
				// TODO: 输出tmpPrefix
			} while (PrefixByteToGroup(tmpPrefix) != group);
			// TODO: 剩余队列中数据为起效前缀,这段do代码要单独分出来
			return false;
		}
		prefixs.push(prefix);
		return true;
	}
	DisAsm::~DisAsm()
	{
	}
}