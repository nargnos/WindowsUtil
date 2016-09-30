#pragma once
struct IteratorFriendAccess
{
	template<typename T>
	static bool Equal(const T& it, const T & val)
	{
		return it.Equal(val);
	}

	template<typename T>
	static void Increment(T& it)
	{
		it.Increment();
	}

	template<typename T>
	static void Decrement(T& it)
	{
		it.Decrement();
	}

	template<typename T>
	static void Advance(T& it, int n)
	{
		it.Advance(n);
	}
	template<typename T>
	static typename T::difference_type DistanceTo(const T& it, const T & val)
	{
		return it.DistanceTo(val);
	}

	template<typename T>
	static typename T::reference Dereference(T& it)
	{
		return it.Dereference();
	}

	template<typename T>
	static const typename T::reference Dereference(const T& it)
	{
		return it.Dereference();
	}
};