#pragma once
// Core includes
#include "DuckCore/Utilities/NoCopy.h"

namespace DC
{

template<typename taType>
class UniquePtr : public NoCopy
{
public:
	UniquePtr() = default;
	~UniquePtr();

	// Move operators
	template<typename taChildType>
	UniquePtr(UniquePtr<taChildType>&& inOther) noexcept;
	template<typename taChildType>
	UniquePtr& operator=(UniquePtr<taChildType>&& inOther) noexcept;

	template<typename... taArgs>
	static UniquePtr<taType> sMakeUnique(taArgs&&... inArgs);

	taType* Get() { return mPtr; }
	const taType* Get() const { return mPtr; }

	operator taType*() { return mPtr; }
	operator const taType*()  const { return mPtr; }

	taType* operator->() { return mPtr; }
	const taType* operator->() const { return mPtr; }

	void Internal_SetDataPtr(taType* inPtr) { mPtr = inPtr; }
	
private:
	UniquePtr(taType* inPtr) : mPtr(inPtr) {}

	taType* mPtr = nullptr;
};

template<typename taType>
inline UniquePtr<taType>::~UniquePtr()
{
    delete mPtr;
}

// Move constructor
template<typename taType>
template<typename taChildType>
inline UniquePtr<taType>::UniquePtr(UniquePtr<taChildType>&& inOther) noexcept
{
	mPtr = inOther.Get();
	inOther.Internal_SetDataPtr(nullptr);
}

// Move assignment
template<typename taType>
template<typename taChildType>
inline UniquePtr<taType>& UniquePtr<taType>::operator=(UniquePtr<taChildType>&& inOther) noexcept
{
	if (this->Get() != inOther.Get())
	{
		delete mPtr; // Delete the current object
		mPtr = inOther.Get(); // Transfer ownership
		inOther.Internal_SetDataPtr(nullptr);
	}
	return *this;
}

template<typename taType>
template<typename... taArgs>
inline UniquePtr<taType> UniquePtr<taType>::sMakeUnique(taArgs&&... inArgs)
{
	return UniquePtr<taType>(new taType(std::forward<taArgs>(inArgs)...));
}

}
