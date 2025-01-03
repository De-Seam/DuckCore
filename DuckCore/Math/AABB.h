#pragma once
#include <DuckCore/Config.h>
#include <DuckCore/Math/Vector.h>

namespace DC
{
template<typename taType>
struct AABB
{
	Vec2<taType> mMin;
	Vec2<taType> mMax;

	bool Intersects(const Vec2<taType>& inPoint) const
	{
		return	inPoint.mX >= mMin.mX && inPoint.mX <= mMax.mX &&
			inPoint.mY >= mMin.mY && inPoint.mY <= mMax.mY;
	}

	bool Intersects(const AABB& inOther) const
	{
		return	mMin.mX < inOther.mMax.mX && mMax.mX > inOther.mMin.mX &&
			mMin.mY < inOther.mMax.mY && mMax.mY > inOther.mMin.mY;
	}

	Vec2<taType> GetSidesLength() const
	{
		return mMax - mMin;
	}

	taType Area() const
	{
		Vec2 length = GetSidesLength();
		return length.mX * length.mY;
	}

	Vec2<taType> GetCenter() const
	{
		Vec2 length = GetSidesLength();
		return mMax - (length * 0.5f);
	}
};

extern template struct AABB<float>;
extern template struct AABB<double>;
}