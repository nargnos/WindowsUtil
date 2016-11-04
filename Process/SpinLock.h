#pragma once
#include "Common.h"
// 函数名按照stl的以兼容lock_guard
class SpinLock
{
public:
	SpinLock() = default;
	bool try_lock();
	void lock();
	void unlock();
private:
	static void ThreadYield(unsigned int k);
	_STD atomic_flag lock_ = ATOMIC_VAR_INIT(false);

	SpinLock(const SpinLock&) = delete;
	SpinLock& operator=(const SpinLock&) = delete;
};