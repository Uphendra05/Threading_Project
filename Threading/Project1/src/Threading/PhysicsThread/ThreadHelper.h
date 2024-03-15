#pragma once

#include <iostream>
#include <functional>
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN

namespace InterLock
{
	template <typename T>
	T Exchange(volatile T* target, T value)
	{
		return InterlockedExchange(target, value);
	}

	template <typename T>
	T Add(volatile T* addend, T value)
	{
		return InterlockedAdd(addend, value);
	}

	template <typename T>
	T Add64(volatile T* addend, T value)
	{
		return InterlockedAdd64(addend, value);
	}

	template <typename T>
	T Increment(volatile T* addend)
	{
		return InterlockedIncrement(addend);
	}

	template <typename T>
	T Decrement(volatile T* addend)
	{
		return InterlockedDecrement(addend);
	}

	template <typename T>
	T CompareExchange(volatile T* destination, T exchange, T comparand)
	{
		return InterlockedCompareExchange(destination, exchange, comparand);
	}


}