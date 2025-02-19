#pragma once
// Core includes
#include "DuckCore/Config.h"
#include "DuckCore/Math/AABB.h"
#include "DuckCore/Math/Vector.h"
#include "DuckCore/Utilities/Json.h"

namespace DC
{

// 2D transform
struct Transform2D
{
	Vec2<TransformType> mPosition = {0.0, 0.0};
	Vec2<TransformType> mHalfSize = {32.0, 32.0};
	TransformType mRotation = 0.0;

	Transform2D() = default;
	Transform2D(const Vec2<TransformType>& inPosition, const Vec2<TransformType>& inHalfSize, const TransformType& inRotation);
	Transform2D(const Transform2D& inOther) = default;

	Transform2D& operator=(const Transform2D& inOther) = default;
	Transform2D operator*(const Transform2D& inOther) const;

	AABB<TransformType> GetBounds() const;
};

void ToJson(Json& outJson, const Transform2D& inVariable);
void FromJson(const Json& inJson, Transform2D& outVariable);

}
