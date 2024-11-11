#pragma once
// Std includes
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

float gFloatMax(); // 3.402823466e+38F
float gFloatMin(); // 1.175494351e-38F
float gFloatEpsilon(); // 1.192092896e-07F
float gFloatInfinity();

double gDoubleMax();
double gDoubleMin();
double gDoubleEpsilon();
double gDoubleInfinity();

int8 gInt8Max(); // 127
int8 gInt8Min(); // -128
int16 gInt16Max(); // 32767
int16 gInt16Min(); // 32768
int32 gInt32Max(); // 2147483647
int32 gInt32Min(); // 2147483648
int64 gInt64Max(); // 9223372036854775807
int64 gInt64Min(); // 9223372036854775808

uint8 gUInt8Max(); // 255
uint8 gUInt8Min(); // 0
uint16 gUInt16Max(); // 65535
uint16 gUInt16Min(); // 0
uint32 gUInt32Max(); // 4294967295
uint32 gUInt32Min(); // 0
uint64 gUInt64Max(); // 18446744073709551615
uint64 gUInt64Min(); // 0

template<typename taCastType>
taCastType gStaticCast(auto& inItem)
{
	return static_cast<taCastType>(inItem);
}