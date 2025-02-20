#pragma once
#include <DuckCore/Math/AABB.h>

namespace DC
{
// BVHObject can be inherited to create custom objects in the BVH. These are owned in memory by the owner of the BVH.
class BVHObject
{
public:
	void SetAABB(const AABB<float>& aAABB) { mAABB = aAABB; }
	const AABB<float>& GetAABB() const { return mAABB; }

private:
	AABB<float> mAABB;
};
}
