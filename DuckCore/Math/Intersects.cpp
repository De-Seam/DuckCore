#include <DuckCore/Math/Intersects.h>

namespace DC
{
bool gIntersects(const FVec2& inPoint, const FRect2D& inRectangle) 
{
	return inPoint.mX >= inRectangle.mX && inPoint.mX <= inRectangle.mX + inRectangle.mWidth &&
		inPoint.mY >= inRectangle.mY && inPoint.mY <= inRectangle.mY + inRectangle.mHeight;
}
}
