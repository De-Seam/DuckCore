#pragma once
// Core includes
#include <DuckCore/Utilities/NoCopy.h>
#include <DuckCore/Utilities/Utilities.h>

// Std includes
#include <utility>

namespace DC
{

template<typename taType>
class UniquePtr : public NoCopy
{
public:
	UniquePtr() = default;
	~UniquePtr();

	// Move operators
	template<typename taParentType>
	UniquePtr(UniquePtr<taParentType>&& inOther) noexcept;
	template<typename taParentType>
	UniquePtr& operator=(UniquePtr<taParentType>&& inOther) noexcept;

	template<typename taChildType>
	UniquePtr<taChildType> StaticCast() noexcept;

	template<typename... taArgs>
	static UniquePtr<taType> sMakeUnique(taArgs&&... inArgs);

	void Delete() { delete mPtr; mPtr = nullptr; }

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

	template<typename taOtherType, typename... taArgs>
	friend UniquePtr<taOtherType> MakeUnique(taArgs&&... inArgs); // MakeUnique
};

template<typename taType, typename... taArgs>
UniquePtr<taType> MakeUnique(taArgs&&... inArgs)
{
	return UniquePtr<taType>(new taType(std::forward<taArgs>(inArgs)...));
}

template<typename taType>
inline UniquePtr<taType>::~UniquePtr()
{
	delete mPtr;
	mPtr = nullptr;
}

// Move constructor
template<typename taType>
template<typename taParentType>
inline UniquePtr<taType>::UniquePtr(UniquePtr<taParentType>&& inOther) noexcept
{
	mPtr = inOther.Get();
	inOther.Internal_SetDataPtr(nullptr);
}

// Move assignment
template<typename taType>
template<typename taParentType>
inline UniquePtr<taType>& UniquePtr<taType>::operator=(UniquePtr<taParentType>&& inOther) noexcept
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
template<typename taChildType>
UniquePtr<taChildType> UniquePtr<taType>::StaticCast() noexcept
{
	UniquePtr<taChildType> new_unique_ptr;
	new_unique_ptr.Internal_SetDataPtr(static_cast<taChildType*>(mPtr));
	mPtr = nullptr;
	return Move(new_unique_ptr);
}

template<typename taType>
template<typename... taArgs>
inline UniquePtr<taType> UniquePtr<taType>::sMakeUnique(taArgs&&... inArgs)
{
	return UniquePtr<taType>(new taType(std::forward<taArgs>(inArgs)...));
}
}
