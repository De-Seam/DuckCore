#pragma once
#include "DuckCore/Math/AABB.h"
#include "DuckCore/Math/Vector.h"

namespace DC
{

template<typename taType>
struct Rect2D
{
	Vec2<taType> mBottomLeft;
	Vec2<taType> mWidthHeight;

	Rect2D() = default;
	Rect2D(const Vec2<taType>& inBottomLeft, const Vec2<taType>& inWidthHeight) :
		mBottomLeft(inBottomLeft),
		mWidthHeight(inWidthHeight)
	{}
	Rect2D(taType inX, taType inY, taType inWidth, taType inHeight) :
		mBottomLeft(inX, inY),
		mWidthHeight(inWidth, inHeight)
	{}
	Rect2D(const Rect2D& inOther) = default;

	template<typename taOtherType>
	Rect2D<taOtherType> As()
	{
		return Rect2D(mBottomLeft.As<taOtherType>(), mWidthHeight.As<taOtherType>());
	}

	AABB<taType> ToAABB() const
	{
		return
		{
			mBottomLeft,
			mBottomLeft + mWidthHeight
		};
	}
};

extern template struct Rect2D<float>;
extern template struct Rect2D<double>;
extern template struct Rect2D<int>;
extern template struct Rect2D<uint32>;
}
