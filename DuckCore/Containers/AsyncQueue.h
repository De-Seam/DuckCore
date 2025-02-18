#pragma once
#include <DuckCore/Containers/Pair.h>
#include <DuckCore/Core/Types.h>

#include <condition_variable>
#include <mutex>
#include <queue>

namespace DC
{

enum class DequeueResult
{
	Success,
	Empty,
	Locked
};

// A thread-safe queue.
template<class T>
class AsyncQueue
{
public:
	// Add an element to the queue.
	void Enqueue(T t)
	{
		std::lock_guard<std::mutex> lock(mMutex);
		mQueue.push(t);
		mConditionVariable.notify_one();
	}

	bool TryEnqueue(T t)
	{
		if (mMutex.try_lock())
		{
			mQueue.push(t);
			mConditionVariable.notify_one();
			mMutex.unlock();
			return true;
		}
		return false;
	}

	// Get the "front"-element.
	// If the queue is empty, wait till a element is available.
	T Dequeue(void)
	{
		std::unique_lock<std::mutex> lock(mMutex);
		while (mQueue.empty())
		{
			// release lock as long as the wait and reacquire it afterward.
			mConditionVariable.wait(lock);
		}
		T val = mQueue.front();
		mQueue.pop();
		return val;
	}

	Pair<DequeueResult, T> TryDequeue()
	{
		if (mMutex.try_lock())
		{
			if (mQueue.empty())
			{
				mMutex.unlock();
				return {DequeueResult::Empty, T()};
			}
			T val = mQueue.front();
			mQueue.pop();
			mMutex.unlock();
			return {DequeueResult::Success, val};
		}
		return { DequeueResult::Locked, T()};
	}

	void Clear()
	{
		std::lock_guard<std::mutex> lock(mMutex);
		while (!mQueue.empty())
		{
			mQueue.pop();
		}
	}

	uint64 Size() const
	{
		return mQueue.size();
	}

	bool IsEmpty() const
	{
		return mQueue.empty();
	}

	void Lock()
	{
		mMutex.lock();
	}

	void Unlock()
	{
		mMutex.unlock();
	}

private:
	std::queue<T> mQueue;
	mutable std::mutex mMutex;
	std::condition_variable mConditionVariable;
};
}