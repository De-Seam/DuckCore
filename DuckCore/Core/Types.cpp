#include <DuckCore/Core/Types.h>

#include <cfloat>
#include <corecrt_math.h>

float gFloatMax()
{
	return FLT_MAX;
}

float gFloatMin()
{
	return FLT_MIN;
}

float gFloatEpsilon()
{
	return FLT_EPSILON;
}

float gFloatInfinity()
{
	return INFINITY;
}

double gDoubleMax()
{
	return DBL_MAX;
}

double gDoubleMin()
{
	return DBL_MIN;
}

double gDoubleEpsilon()
{
	return DBL_EPSILON;
}

double gDoubleInfinity()
{
	return HUGE_VAL;
}

int8 gInt8Max()
{
	return INT8_MAX;
}

int8 gInt8Min()
{
    return INT8_MIN;
}

int16 gInt16Max()
{
	return INT16_MAX;
}

int16 gInt16Min()
{
	return	INT16_MIN;
}

int32 gInt32Max()
{
	return INT32_MAX;
}

int32 gInt32Min()
{
	return INT32_MIN;
}

int64 gInt64Max()
{
	return INT64_MAX;
}

int64 gInt64Min()
{
	return INT64_MIN;
}

uint8 gUInt8Max()
{
	return UINT8_MAX;
}

uint8 gUInt8Min()
{
	return 0;
}

uint16 gUInt16Max()
{
	return UINT16_MAX;
}

uint16 gUInt16Min()
{
	return 0;
}

uint32 gUInt32Max()
{
	return UINT32_MAX;
}

uint32 gUInt32Min()
{
	return 0;
}

uint64 gUInt64Max()
{
	return UINT64_MAX;
}

uint64 gUInt64Min()
{
	return 0;
}