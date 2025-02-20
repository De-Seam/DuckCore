#pragma once
#include <DuckCore/AccelerationStructures/BVHNode.h>
#include <DuckCore/AccelerationStructures/BVHObject.h>
#include <DuckCore/Containers/Array.h>
#include <DuckCore/Containers/Pair.h>
#include <DuckCore/Math/Rect.h>
#include <DuckCore/Utilities/NoCopy.h>

namespace DC
{

// BVH is a private class from the CollisionWorld, so public functions should be called from the CollisionWorld
class BVH : public NoCopy, NoMove
{
public:
	BVH() = default;
	~BVH();

	void AddObject(BVHObject& aObject); // Add an object to the BVH. The object is owned by the caller. The BVH does not assume ownership.

	void Build(); // (Re)build the BVH. Expensive operation.

	bool IsGenerated() const { return mIndices != nullptr; }
	bool IsDirty() const { return mIsDirty; } // Is dirty means that objects have been added or removed, so the BVH should be re-built.

private:
	// Creates AABB from objects. Uses mIndices.
	AABB<float> CreateAABBFromObjects(uint64 inFirst, uint64 inCount);

	void Subdivide(BVHNode* inNode, uint64 inFirst, uint64 inCount, uint64 inDepth);
	void Partition(BVHNode* inNode, uint64 inFirst, uint64 inCount, uint64 inDepth);
	float ComputeSplitCost(uint64 inFirst, uint64 inCount, float inSplitLocation, uint64 inSplitAxis);
	uint64 SplitIndices(uint64 inFirst, uint64 inCount, float inSplitLocation, uint64 inSplitAxis);

	Array<BVHObject*> mObjects;
	bool mIsDirty = false;

	Array<BVHNode> mNodes;

	uint32* mIndices = nullptr; ///< Indices of the objects in the mObjects array, uses int32 for space efficiency
	uint32 mIndexCount = 0; ///< Count of mIndices. Saved because mObjects can change before the mIndices is reconstructed

	FVec2 mDynamicAABBModifier = {0.25f, 0.25f}; ///< The AABB of dynamic objects is expanded by this amount
};
}
