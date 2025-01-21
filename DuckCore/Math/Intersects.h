#pragma once
#include <DuckCore/Math/Rect.h>
#include <DuckCore/Math/Vector.h>

namespace DC
{
	// Point-Rectangle intersection
	bool gIntersects(const FVec2& inPoint, const FRect2D& inRectangle);
	inline bool gIntersects(const IVec2& inPoint, const FRect2D& inRectangle) { return gIntersects(inPoint.As<float>(), inRectangle); }
}
