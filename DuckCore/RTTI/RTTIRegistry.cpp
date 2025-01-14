#include <DuckCore/RTTI/RTTI.h>
#include <DuckCore/RTTI/RTTIRegistry.h>

namespace DC
{
RTTIRegistry gRTTIRegistry = {};

void RTTIRegistry::GetChildClassesOf(const RTTI& inRTTI, Array<RTTI*>& outChildClasses)
{
	gAssert(outChildClasses.IsEmpty());

	UpdateRTTITree();

	RTTIContainer* container = FindRTTIContainer(inRTTI);
	gAssert(container != nullptr);

	sGatherChildClassesRecursive(*container, outChildClasses);
}

void RTTIRegistry::RegisterRTTI(RTTI& inRTTI)
{
	gAssert(mRTTIContainerRoots.IsEmpty(), "Shouldn't be registering new RTTIs after the tree has been generated.");
	mRTTIArray.Add(&inRTTI);
	mRTTIContainerRoots.Clear();
}

void RTTIRegistry::UpdateRTTITree()
{
	if (!mRTTIContainerRoots.IsEmpty())
		return;

	BuildRTTITreeRecursive("NONE", mRTTIContainerRoots);
}

void RTTIRegistry::BuildRTTITreeRecursive(const char* inCurrentClassName, Array<RTTIContainer>& ioCurrentRTTIContainer)
{
	for (RTTI* rtti : mRTTIArray)
	{
		if (rtti->GetBaseClassName() == inCurrentClassName)
		{
			RTTIContainer container;
			container.mRTTI = rtti;
			ioCurrentRTTIContainer.Add(container);
			BuildRTTITreeRecursive(rtti->GetClassName(), ioCurrentRTTIContainer.Back().mChildRTTIContainers);
		}
	}
}

RTTIRegistry::RTTIContainer* RTTIRegistry::FindRTTIContainer(const RTTI& inRTTI)
{
	for (RTTIContainer& rtti_container : mRTTIContainerRoots)
	{
		if (RTTIContainer* found_container = sFindRTTIContainerRecursive(inRTTI, rtti_container))
			return found_container;
	}
	return nullptr;
}

RTTIRegistry::RTTIContainer* RTTIRegistry::sFindRTTIContainerRecursive(const RTTI& inRTTI, RTTIContainer& inCurrentRTTIContainer)
{
	if (inCurrentRTTIContainer.mRTTI == &inRTTI)
		return &inCurrentRTTIContainer;

	for (RTTIContainer& rtti_container : inCurrentRTTIContainer.mChildRTTIContainers)
	{
		if (RTTIContainer* found_container = sFindRTTIContainerRecursive(inRTTI, rtti_container))
			return found_container;
	}

	return nullptr;
}

void RTTIRegistry::sGatherChildClassesRecursive(RTTIContainer& inCurrentRTTIContainer, Array<RTTI*>& outChildClasses)
{
	outChildClasses.Add(inCurrentRTTIContainer.mRTTI);

	for (RTTIContainer& container : inCurrentRTTIContainer.mChildRTTIContainers)
		sGatherChildClassesRecursive(container, outChildClasses);
}
}
