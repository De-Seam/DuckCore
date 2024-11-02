#pragma once
// DuckCore includes
#include <DuckCore/Utilities/Utilities.h>

// Std includes
#include <memory>

template<typename taType>
class SharedPtr
{
public:
	SharedPtr();
	SharedPtr(const SharedPtr& inOther);
	SharedPtr(SharedPtr&& inOther) noexcept;
	explicit SharedPtr(std::shared_ptr<taType> inPtr);

	SharedPtr& operator=(const SharedPtr& inOther) { mPtr = inOther.mPtr; return *this; }

	operator taType*() { return mPtr.get(); }
	operator const taType*() const { return mPtr.get(); }

	taType* operator->() { return mPtr.get(); }
	const taType* operator->() const { return mPtr.get(); }

	template<typename... taArgs>
	static SharedPtr<taType> sMakeUnique(taArgs&&... inArgs);

private:
	std::shared_ptr<taType> mPtr;
};

template<typename taType>
SharedPtr<taType>::SharedPtr() :
	mPtr(nullptr) 
{}

template<typename taType>
SharedPtr<taType>::SharedPtr(const SharedPtr& inOther) :
	mPtr(inOther.mPtr)
{}

template<typename taType>
SharedPtr<taType>::SharedPtr(SharedPtr&& inOther) noexcept :
	mPtr(gMove(inOther.mPtr))
{}

template<typename taType>
SharedPtr<taType>::SharedPtr(std::shared_ptr<taType> inPtr) :
	mPtr(inPtr)
{}

template<typename taType>
template<typename ... taArgs>
SharedPtr<taType> SharedPtr<taType>::sMakeUnique(taArgs&&... inArgs)
{
	return SharedPtr<taType>{ std::make_shared<taType>(std::forward<taArgs>(inArgs)...) };
}
