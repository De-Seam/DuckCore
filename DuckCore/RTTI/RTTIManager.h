#pragma once
#include <DuckCore/Containers/Array.h>
#include <DuckCore/Managers/Manager.h>

namespace DC
{
class RTTIManager final : public Manager
{
	MANAGER_BASE_CLASS(RTTIManager)
public:
	RTTIManager();

	template <typename tType>
	void Register() { Register(tType::sGetRTTI()); }
	void Register(const RTTI& aRTTI);

private:
	Array<const RTTI*> mRTTIs;

	struct RTTINode
	{
		RTTINode(const RTTI& aSelf, const RTTI* aParent) : mSelf(aSelf), mParent(aParent) { }

		const RTTI& mSelf;
		const RTTI* mParent = nullptr;
		Array<RTTINode> mChildren;
	};
	RTTINode mRootRTTINode;
};
}
