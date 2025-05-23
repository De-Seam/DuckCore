#include <DuckCore/RTTI/RTTIManager.h>

#include <DuckCore/Threads/Thread.h>

namespace DC
{
RTTIManager::RTTIManager() : mRootRTTINode(RTTIClass::sGetRTTI(), nullptr)
{
	mRTTIs.Add(&RTTIClass::sGetRTTI());
}

void RTTIManager::Register(const RTTI& aRTTI)
{
	gAssert(IsMainThread());
	
	const RTTI* base_class = aRTTI.GetBaseClassRTTI();

	const int index = mRootRTTINode.mChildren.FindIf([base_class](const RTTINode& aItem) { return &aItem.mSelf == base_class; });
	if (index != -1)
	{
		RTTINode& parent_node = mRootRTTINode.mChildren[index];
		parent_node.mChildren.Add(RTTINode(aRTTI, &parent_node.mSelf));
	}
	else if (&mRootRTTINode.mSelf == base_class)
	{
		mRootRTTINode.mChildren.Add(RTTINode(aRTTI, &mRootRTTINode.mSelf));
	}
	else
	{
		// Register parent and try again.
		Register(*base_class);
		Register(aRTTI);
		return;
	}

	mRTTIs.Add(&aRTTI);
}
}
