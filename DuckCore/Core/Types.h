#pragma once
#include <cstdint>

using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

using uint = unsigned int;
using byte = uint8_t;

float FloatMax(); // 3.402823466e+38F
float FloatMin(); // 1.175494351e-38F
float FloatEpsilon(); // 1.192092896e-07F
float FloatInfinity();

double DoubleMax();
double DoubleMin();
double DoubleEpsilon();
double DoubleInfinity();

int8 Int8Max(); // 127
int8 Int8Min(); // -128
int16 Int16Max(); // 32767
int16 Int16Min(); // -32768
int32 Int32Max(); // 2147483647
int32 Int32Min(); // -2147483648
int64 Int64Max(); // 9223372036854775807
int64 Int64Min(); // -9223372036854775808

uint8 UInt8Max(); // 255
uint8 UInt8Min(); // 0
uint16 UInt16Max(); // 65535
uint16 UInt16Min(); // 0
uint32 UInt32Max(); // 4294967295
uint32 UInt32Min(); // 0
uint64 UInt64Max(); // 18446744073709551615
uint64 UInt64Min(); // 0

template <typename tCastType>
tCastType StaticCast(auto&& inItem)
{
	return static_cast<tCastType>(inItem);
}

template <typename tCastType>
tCastType SCast(auto&& inItem)
{
	return static_cast<tCastType>(inItem);
}

template <typename tCastType>
tCastType ReinterpretCast(auto&& inItem)
{
	return reinterpret_cast<tCastType>(inItem);
}

template <typename tCastType>
tCastType RCast(auto&& inItem)
{
	return reinterpret_cast<tCastType>(inItem);
}