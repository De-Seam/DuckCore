#include <DuckCore/Math/Transform.h>

namespace DC
{
Transform2D::Transform2D(const Vec2<TransformType>& inPosition, const Vec2<TransformType>& inHalfSize, const TransformType& inRotation) :
    mPosition(inPosition),
    mHalfSize(inHalfSize),
    mRotation(inRotation)
{}

Transform2D Transform2D::operator*(const Transform2D& inOther) const
{
	return
	{
		mPosition + inOther.mPosition,
		gMax2(mHalfSize, inOther.mHalfSize),
		mRotation + inOther.mRotation
	};
}

AABB<TransformType> Transform2D::GetBounds() const
{
	TransformType rotation = gToRadiansF(mRotation);
	TransformType sin_r = std::abs(std::sin(rotation));
	TransformType cos_r = std::abs(std::cos(rotation));

	// Compute the half-size of the rotated object
	TransformType half_width = mHalfSize.mX * cos_r + mHalfSize.mY * sin_r;
	TransformType half_height = mHalfSize.mX * sin_r + mHalfSize.mY * cos_r;
	Vec2<TransformType> half_size = {half_width, half_height};

	AABB<TransformType> aabb;
	aabb.mMin = mPosition - half_size;
	aabb.mMax = mPosition + half_size;

	return aabb;
}

void to_json(Json& outJson, const Transform2D& inVariable) 
{
	outJson["mPosition"] = inVariable.mPosition;
	outJson["mHalfSize"] = inVariable.mHalfSize;
	outJson["mRotation"] = inVariable.mRotation;
}

void from_json(const Json& inJson, Transform2D& outVariable) 
{
	outVariable.mPosition = inJson["mPosition"];
	outVariable.mHalfSize = inJson["mHalfSize"];
	outVariable.mRotation = inJson["mRotation"];
}

}