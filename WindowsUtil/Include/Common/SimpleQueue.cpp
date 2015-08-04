#include "SimpleQueue.h"

namespace Common
{
	template<class T>
	SimpleQueue<T>::SimpleQueue(UINT size)
	{
		if (size<8)
		{
			size = 8;
		}
		this->size = size;
		this->queueBuff = new T[size];
	}
	
	template<class T>
	SimpleQueue<T>::~SimpleQueue()
	{
		delete[] queueBuff;
	}

	template<class T>
	bool SimpleQueue<T>::Enqueue(T val)
	{
		
		queueBuff[end] = val;
		
	}

	template<class T>
	void SimpleQueue<T>::Resize()
	{

	}


	template<class T>
	bool SimpleQueue<T>::Dequeue()
	{
		
		return 0;
	}	

	template<class T>
	T SimpleQueue<T>::Front()
	{
		return queueBuff[start];
	}
}