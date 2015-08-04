#pragma once
#include <Windows.h>
#include <WinBase.h>
namespace Common
{
	template<class T>
	class SimpleQueue
	{
		
	public:
		SimpleQueue(UINT size = 8);
		SimpleQueue();
		~SimpleQueue();
		bool Enqueue(T val);
		bool Dequeue();
		T Front();
	private:
		UINT size;
		T queueBuff;
		void Resize();
		UINT count;
		
	};

}