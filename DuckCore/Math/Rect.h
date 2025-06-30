#pragma once
#include "DuckCore/Math/AABB.h"
#include "DuckCore/Math/Vector.h"

#ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable : 4201) //to avoid nameless struct / union warning.
#elif defined(__GNUC__) || defined(__clang__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wpedantic"
#else
    #error "Unsupported compiler"
#endif

namespace DC
{

template<typename tType>
struct Rect2D
{
	union
	{
		struct
		{
			tType mX, mY, mWidth, mHeight;
		};
		struct
		{
			Vec2<tType> mBottomLeft;
			Vec2<tType> mWidthHeight;
		};
	};

	Rect2D() : mX(gStaticCast<tType>(0)), mY(gStaticCast<tType>(0)), mWidth(gStaticCast<tType>(0)), mHeight(gStaticCast<tType>(0)) {}
	Rect2D(const Vec2<tType>& inBottomLeft, const Vec2<tType>& inWidthHeight) :
		mBottomLeft(inBottomLeft),
		mWidthHeight(inWidthHeight)
	{}
	Rect2D(tType inX, tType inY, tType inWidth, tType inHeight) :
		mBottomLeft(inX, inY),
		mWidthHeight(inWidth, inHeight)
	{}
	Rect2D(const Rect2D<tType>& inOther) : mBottomLeft(inOther.mBottomLeft), mWidthHeight(inOther.mWidthHeight) {}

	template<typename taOtherType>
	Rect2D<taOtherType> As()
	{
		return Rect2D(mBottomLeft.template As<taOtherType>(), mWidthHeight.template As<taOtherType>());
	}

	AABB<tType> ToAABB() const
	{
		return
		{
			mBottomLeft,
			mBottomLeft + mWidthHeight
		};
	}
};

using DRect2D = Rect2D<double>;
using FRect2D = Rect2D<float>;
using IRect2D = Rect2D<int32>;
using URect2D = Rect2D<uint32>;
extern template struct Rect2D<float>;
extern template struct Rect2D<double>;
extern template struct Rect2D<int>;
extern template struct Rect2D<uint32>;
}

#ifdef _MSC_VER
    #pragma warning(pop)
#elif defined(__GNUC__) || defined(__clang__)
    #pragma GCC diagnostic pop
#else
    #error "Unsupported compiler"
#endif