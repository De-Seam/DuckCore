#pragma once
#include <DuckCore/Math/AABB.h>

namespace DC
{
struct BVHNode
{
#pragma pack(push, 1)
	struct BranchNode
	{
		uint32 mLeftIndex = 0; // The index of the first child node.
		bool mIsLeaf = false; // If this is a leaf node. If not, it is a branch node.
		byte mPadding[3] = { 0 }; // Padding to make the size of BranchNode and LeafNode the same.
	};
	struct LeafNode
	{
		uint32 mFirstIndex = 0; // The index of the first object in the mIndices array.
		uint32 mCount = 0; // The count of objects in the leaf. (If this is 0, it is a branch node. See BranchNode::mIsLeaf).
	};
#pragma pack(pop)

	static_assert(sizeof(BranchNode) == sizeof(LeafNode), "BranchNode and LeafNode must have the same size");
	static_assert(alignof(BranchNode) == alignof(LeafNode), "BranchNode and LeafNode must have the same alignment");

	BVHNode() :
		mAABB(AABB<float>()),
		mBranchNode(BranchNode())
	{}

	bool IsLeafNode() const { return mBranchNode.mIsLeaf; }
	bool IsBranchNode() const { return !IsLeafNode(); }

	AABB<float> mAABB;
	union
	{
		BranchNode mBranchNode;
		LeafNode mLeafNode;
	};
};
}