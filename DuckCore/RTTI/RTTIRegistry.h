#pragma once
#include <DuckCore/Containers/Array.h>

namespace DC
{
class RTTI;

class RTTIRegistry
{
public:
	template<typename taType>
	void GetChildClassesOf(Array<RTTI*>& outChildClasses);
	void GetChildClassesOf(const RTTI& inRTTI, Array<RTTI*>& outChildClasses);

private:
	void RegisterRTTI(RTTI& inRTTI);
	void UpdateRTTITree();
	struct RTTIContainer;
	void BuildRTTITreeRecursive(const char* inCurrentClassName, Array<RTTIContainer>& ioCurrentRTTIContainer);
	RTTIContainer* FindRTTIContainer(const RTTI& inRTTI);
	static RTTIContainer* sFindRTTIContainerRecursive(const RTTI& inRTTI, RTTIContainer& inCurrentRTTIContainer);

	static void sGatherChildClassesRecursive(RTTIContainer& inCurrentRTTIContainer, Array<RTTI*>& outChildClasses);

	Array<RTTI*> mRTTIArray;

	struct RTTIContainer
	{
		RTTI* mRTTI = nullptr;
		Array<RTTIContainer> mChildRTTIContainers;
	};
	Array<RTTIContainer> mRTTIContainerRoots;

	friend class RTTI;
};

template <typename taType>
void RTTIRegistry::GetChildClassesOf(Array<RTTI*>& outChildClasses)
{
	GetChildClassesOf(taType::sGetRTTI(), outChildClasses);
}

extern RTTIRegistry gRTTIRegistry;
}
