#include "PrefixQueue.h"
namespace Asm
{

	int PrefixQueue::Push(OpcodePrefix prefix)
	{
		auto group = prefix.PrefixGroup;
		if (!Exist[group -1])
		{
			ConflictQueues.swap(std::queue<OpcodePrefix>());
			Exist[group -1] = true;
			prefixQueues.push(prefix);
			return true;
		}
		else
		{
			// 存在，出队到队首组号等于冲突组号
			OpcodePrefix tmpPrefixQueue;
			do
			{
				tmpPrefixQueue = prefixQueues.front();
				Pop();
				ConflictQueues.push(tmpPrefixQueue);// 入队
			} while (tmpPrefixQueue.PrefixGroup != group);

		}
		return false;
	}

	BYTE PrefixQueue::Pop()
	{
		Exist[prefixQueues.front().PrefixGroup - 1] = false;
		prefixQueues.pop();
		return 0;
	}


	PrefixQueue::PrefixQueue()
	{
	}

	//	bool PrefixQueue::PushPrefixQueue(BYTE PrefixQueue)
//	{
		//auto group = PrefixQueueRecord.Record(PrefixQueue);
		//if (group)
		//{
		//	// 冲突
		//	BYTE tmpPrefixQueue;
		//	do
		//	{
		//		tmpPrefixQueue = PrefixQueues.front();
		//		PrefixQueues.pop();
		//		// TODO: 输出tmpPrefixQueue
		//	} while (PrefixByteToGroup(tmpPrefixQueue) != group);
		//	// TODO: 剩余队列中数据为起效前缀,这段do代码要单独分出来
		//	return false;
		//}
		//PrefixQueues.push(PrefixQueue);
	//	return true;
//	}
	PrefixQueue::~PrefixQueue()
	{
	}
	void PrefixQueue::Reset()
	{
		for (int i = 0; i < 4; i++)
		{
			Exist[i] = false;
		}
		prefixQueues.swap(std::queue<OpcodePrefix>());
	}
}