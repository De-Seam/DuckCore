#include <DuckCore/AccelerationStructures/BVH.h>

#include <DuckCore/Core/Log.h>
#include <DuckCore/Threads/Thread.h>

using namespace DC;

BVH::~BVH()
{
#ifdef __linux
	if (mIndices != nullptr)
		free(mIndices);
#elif _WIN32
	if (mIndices != nullptr)
		_aligned_free(mIndices);
#endif
}

void BVH::Build()
{
#ifdef __linux
	if (mIndices != nullptr)
		free(mIndices);
#elif _WIN32
	if (mIndices != nullptr)
		_aligned_free(mIndices);
#endif

	mNodes.Clear();

	mIndexCount = StaticCast<uint32>(mObjects.Length());

#ifdef __linux
	posix_memalign((void**)&mIndices, (StaticCast<size_t>(mIndexCount) + 1) * sizeof(uint32), 64);
#elif _WIN32
	mIndices = StaticCast<uint32*>(_aligned_malloc((StaticCast<size_t>(mIndexCount) + 1) * sizeof(uint32), 64));
#endif

	for (size_t i = 0; i < mObjects.Length(); i++)
		mIndices[i] = StaticCast<uint32>(i);

	mNodes.Reserve(mObjects.Length() * 2 + 1);
	mNodes.Add(BVHNode()); //Root Node
	mNodes.Add(BVHNode()); //Empty Node for cache alignment

	mNodes[0].mAABB = CreateAABBFromObjects(0, mObjects.Length());
	Subdivide(&mNodes[0], 0, mObjects.Length(), 0);

	Log(String::sFormatted("BVH Created with %i nodes from %i objects\n", mNodes.Length(), mObjects.Length()));
}

// Add an object to the BVH. The object is owned by the caller. The BVH does not assume ownership.
void BVH::AddObject(BVHObject& aObject)
{
	mIsDirty = true;
	mObjects.Add(&aObject);
}

AABB<float> BVH::CreateAABBFromObjects(uint64 inFirst, uint64 inCount)
{
	FVec2 min = FVec2(INFINITY);
	FVec2 max = FVec2(-INFINITY);

	for (uint32 i = 0; i < inCount; i++)
	{
		const AABB<float>& mObjectAABB = mObjects[StaticCast<int>(mIndices[inFirst + i])]->GetAABB();
		min.mX = Min(mObjectAABB.mMin.mX, min.mX);
		min.mY = Min(mObjectAABB.mMin.mY, min.mY);

		max.mX = Max(mObjectAABB.mMax.mX, max.mX);
		max.mY = Max(mObjectAABB.mMax.mY, max.mY);
	}

	return {min, max};
}

void BVH::Subdivide(BVHNode* inNode, uint64 inFirst, uint64 inCount, uint64 inDepth)
{
	inNode->mAABB = CreateAABBFromObjects(inFirst, inCount);
	Partition(inNode, inFirst, inCount, inDepth);
}

void BVH::Partition(BVHNode* inNode, uint64 inFirst, uint64 inCount, uint64 inDepth)
{
	Vec2 sides_length = inNode->mAABB.mMax - inNode->mAABB.mMin;
	float best_split_location = 0;
	float best_split_cost = INFINITY;
	size_t best_split_axis = 0;

	int split_amount = 20;
	if (inCount - 1 < split_amount)
		split_amount = inCount - 1;
	float split_amount_flt = static_cast<float>(split_amount);
	float split_amount_inv_flt = 1.f / split_amount_flt;

	for (int axis = 0; axis < 2; axis++)
	{
		float next_val = 0;
		for (int i = 0; i < split_amount; i++)
		{
			next_val += sides_length[axis] * split_amount_inv_flt;
			float split_cost = ComputeSplitCost(inFirst, inCount, inNode->mAABB.mMin[axis] + next_val, axis);
			if (split_cost < best_split_cost)
			{
				best_split_cost = split_cost;
				best_split_location = inNode->mAABB.mMin[axis] + next_val;
				best_split_axis = axis;
			}
		}
	}

	//Leaf node
	if (best_split_cost >= inNode->mAABB.Area() * StaticCast<float>(inCount))
	{
		inNode->mLeafNode.mFirstIndex = StaticCast<uint32>(inFirst);
		inNode->mLeafNode.mCount = StaticCast<uint32>(inCount);
		return;
	}

	// Branch node
	uint64 index = SplitIndices(inFirst, inCount, best_split_location, best_split_axis);
	uint64 left_count = index - inFirst;

	int left_node_index = mNodes.Length();
	inNode->mBranchNode.mLeftIndex = StaticCast<uint32>(left_node_index);

	//Children
	mNodes.Add(BVHNode());
	mNodes.Add(BVHNode());

	Subdivide(&mNodes[left_node_index], inFirst, left_count, inDepth + 1);
	Subdivide(&mNodes[left_node_index + 1], index, inCount - left_count, inDepth + 1);
}

float BVH::ComputeSplitCost(uint64 inFirst, uint64 inCount, float inSplitLocation, uint64 inSplitAxis)
{
	uint64 index = SplitIndices(inFirst, inCount, inSplitLocation, inSplitAxis);

	uint64 count_left = index - inFirst;
	uint64 count_right = inCount - count_left;

	AABB aabb_left = CreateAABBFromObjects(inFirst, count_left);
	AABB aabb_right = CreateAABBFromObjects(index, count_right);

	return aabb_left.Area() * count_left + aabb_right.Area() + count_right;
}

uint64 BVH::SplitIndices(uint64 inFirst, uint64 inCount, float inSplitLocation, uint64 inSplitAxis)
{
	uint64 index = inFirst;
	for (uint64 i = inFirst; i < inFirst + inCount; i++)
	{
		const FVec2& position = mObjects[mIndices[i]]->GetAABB().GetCenter();
		if (position[inSplitAxis] <= inSplitLocation)
		{
			//std::swap(m_indices[index], m_indices[i]);
			uint32 t = mIndices[index];
			mIndices[index] = mIndices[i];
			mIndices[i] = t;
			index++;
		}
	}
	return index;
}