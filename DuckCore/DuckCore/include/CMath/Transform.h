#pragma once
#include <CMath/Quaternion.h>
#include <CMath/Vector.h>

struct Transform2D
{
	Vec2 mPosition;
	Vec2 mHalfSize;
	float mRotation;

	Transform2D() :
		mPosition(0.f),
		mHalfSize(32.f),
		mRotation(0.f) {}

	Transform2D(const Vec2& position, const Vec2& size, float rotation) :
		mPosition(position),
		mHalfSize(size),
		mRotation(rotation) {}

	Transform2D(const Transform2D& i) = default;
	Transform2D& operator=(const Transform2D& i) = default;

	Transform2D operator+(const Transform2D& i) const
	{
		return
		{
			mPosition + i.mPosition,
			mHalfSize + i.mHalfSize,
			mRotation + i.mRotation
		};
	}

	Transform2D operator-(const Transform2D& i) const
	{
		return
		{
			mPosition - i.mPosition,
			mHalfSize - i.mHalfSize,
			mRotation - i.mRotation
		};
	}
};

struct Transform3D
{
	Vec3 mPosition;
	Vec3 mScale;
	Quat mRotation;
};
