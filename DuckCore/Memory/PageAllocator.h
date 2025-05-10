#pragma once
#include <DuckCore/Containers/Array.h>
#include <DuckCore/Threads/Mutex.h>
#include <DuckCore/Threads/ScopedMutex.h>
#include <DuckCore/Utilities/NoCopy.h>

namespace DC
{
// Allocator that allocates in pages.
template <typename tType>
class PageAllocator
{
public:
	template <typename... tArgs>
	static tType* sNew(tArgs&&... aArgs);
	static void sDelete(tType* aPtr);

	static void sSetMemoryPageCountMultiplier(float aMultiplier);
	
private:
	class MemoryPage
	{
	public:
		explicit MemoryPage(int aCount)
		{
			mData = gReinterpretCast<Element*>(malloc(aCount * sizeof(Element)));
			for (int i = 0; i < aCount; i++)
			{
				int next_element = i + 1;
				mData[i].mNextFreeElement = next_element != aCount ? &mData[next_element] : nullptr;
			}
			mFirstFreeElement = &mData[0];
		}
		~MemoryPage()
		{
			free(mData);
		}

		bool HasFreeSpace() const { return mFirstFreeElement != nullptr; }
		
		template <typename... tArgs>
		tType* New(tArgs&&... aArgs)
		{
			gAssert(mFirstFreeElement != nullptr);

			Element* free_element = mFirstFreeElement;
			mFirstFreeElement = free_element->mNextFreeElement;

			new (&free_element->mElement) tType(std::forward<tArgs>(aArgs)...);
			return &free_element->mElement;
		}

		bool TryDelete(tType* aPtr, int aCount)
		{
			tType* min = GetMin();
			tType* max = GetMax();

			// Test if aPtr is inside this memory page.
			if (aPtr > max && aPtr < min)
				return false;

			aPtr->~tType();
			
			// We can reinterpret cast because Element::mElement is the first variable in the Element struct.
			Element* element = gReinterpretCast<Element*>(aPtr);

			// aPtr will be the new first free element, and the old first free element will be aPtr their next free element.
			element->mNextFreeElement = mFirstFreeElement;
			mFirstFreeElement = element;

			return true;
		}

		tType* GetMin() { return &mData[0].mElement; }
		tType* GetMax(int aCount) { return &mData[aCount - 1].mElement; }
		
	private:
		struct Element
		{
			tType mElement; // The actual element. It's important that this is the first variable in the struct.
			Element* mNextFreeElement; // Points to the next Element that's free. Or nullptr if none, or nullptr if this element itself is not free.
		};
		
		Element* mData; // Data of count aCount in our constructor.
		Element* mFirstFreeElement = nullptr; // Points to the first Element in mData that's free, or nullptr if none.
	};

	static int sGetCountForIndex(int aIndex) { const int count = gStaticCast<int>(gStaticCast<float>(aIndex) * sMemoryPageCountMultiplier); return count > 0 ? count : 1; }

	inline static Array<MemoryPage> sMemoryPages;
	inline static Mutex sMutex;

	inline static float sMemoryPageCountMultiplier = 2.0f; // By default, the first page is 1 large, the 2nd 2, the 3rd 4, the 4th 8, the 5th 16, etc. But this can be changed for specific classes.
};

template<typename tType>
template <typename... tArgs>
tType* PageAllocator<tType>::sNew(tArgs&&... aArgs)
{
	ScopedMutexLock lock(sMutex);
	
	for (MemoryPage& memory_page : sMemoryPages)
	{
		if (!memory_page.HasFreeSpace())
			continue;
		
		return memory_page.New(std::forward<tArgs>(aArgs)...);
	}

	const int index = sMemoryPages.Emplace(sGetCountForIndex(sMemoryPages.Length()));
	tType* ptr = sMemoryPages[index].New(std::forward<tArgs>(aArgs)...);
	return ptr;
}

template<typename tType>
void PageAllocator<tType>::sDelete(tType* aPtr)
{
	ScopedMutexLock lock(sMutex);

	for (int i = sMemoryPages.Length() - 1; i >= 0; i--)
	{
		MemoryPage& memory_page = sMemoryPages[i];
		const int count = sGetCountForIndex(i);
		
		if (memory_page.TryDelete(aPtr, count))
			return;
	}
}

template<typename tType>
void PageAllocator<tType>::sSetMemoryPageCountMultiplier(float aMultiplier)
{
	gAssert(sMemoryPages.IsEmpty(), "Can't increase the multiplier after we have already started allocating. Set the multipler during application startup.");
	sMemoryPageCountMultiplier = aMultiplier;
}
}
