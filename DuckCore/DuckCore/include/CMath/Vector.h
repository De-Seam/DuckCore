#pragma once
#include <CCore/Types.h>

#include <cassert>
#include <cmath>
#include <string>

#pragma warning (push)
#pragma warning (disable : 4201) //to avoid nameless struct / union warning.

template<typename taType>
inline taType gMin(taType a, taType b)
{
	return ((a) < (b) ? (a) : (b));
}

template<typename taType>
inline taType gMax(taType a, taType b)
{
	return ((a) > (b) ? (a) : (b));
}

template<typename taType>
inline taType gClamp(taType x, taType a, taType b)
{
	return gMax(gMin(x, b), a);
}

template<typename taType>
void Swap(taType& a, taType& b)
{
	taType temp = a;
	a = b;
	b = temp;
}

struct IVec2
{
	int32 x, y;

	IVec2(int32 x, int32 y)
		: x(x), y(y) {}

	IVec2(const int i)
		: IVec2(i, i) {}

	IVec2()
		: IVec2(0) {}

	IVec2(const IVec2& i)
		: IVec2(i.x, i.y) {}

	IVec2& operator=(const IVec2& inOther)
	{
		x = inOther.x;
		y = inOther.y;
		return *this;
	}

	int32& operator[](size_t i)
	{
		assert(i < 2);
		return *(&x + i);
	}

	IVec2 operator -() const { return {-x, -y}; }
	IVec2 operator +(const IVec2& i) const { return {x + i.x, y + i.y}; }
	IVec2 operator -(const IVec2& i) const { return {x - i.x, y - i.y}; }
	IVec2 operator *(const IVec2& i) const { return {x * i.x, y * i.y}; }
	IVec2 operator *(const int i) const { return {x * i, y * i}; }
	IVec2 operator /(const IVec2& i) const { return {x / i.x, y / i.y}; }
	IVec2 operator /(const int i) const { return {x / i, y / i}; }
	const IVec2& operator +=(const IVec2& i) { return *this = *this + i; }
	const IVec2& operator -=(const IVec2& i) { return *this = *this - i; }
	const IVec2& operator *=(const IVec2& i) { return *this = *this * i; }
	const IVec2& operator *=(const int i) { return *this = *this * i; }
	const IVec2& operator /=(const IVec2& i) { return *this = *this / i; }
	const IVec2& operator /=(const int i) { return *this = *this / i; }
};

struct Vec2
{
	float x, y;

	Vec2(float x, float y)
		: x(x), y(y) {}

	Vec2(const float i)
		: Vec2(i, i) {}

	Vec2()
		: Vec2(0) {}

	Vec2(const Vec2& i)
		: Vec2(i.x, i.y) {}

	Vec2& operator=(const Vec2& inOther)
	{
		x = inOther.x;
		y = inOther.y;
		return *this;
	}

	Vec2(const IVec2& i)
		: x(static_cast<float>(i.x)), y(static_cast<float>(i.y)) {}

	Vec2& operator=(const IVec2& inOther)
	{
		x = static_cast<float>(inOther.x);
		y = static_cast<float>(inOther.y);
		return *this;
	}

	float& operator[](size_t i)
	{
		assert(i < 2);
		return *(&x + i);
	}

	const float& operator[](size_t i) const
	{
		assert(i < 2);
		return *(&x + i);
	}

	IVec2 to_ivec2() const
	{
		return {static_cast<int>(x), static_cast<int>(y)};
	}

	Vec2 operator -() const { return {-x, -y}; }
	Vec2 operator +(const Vec2& i) const { return {x + i.x, y + i.y}; }
	Vec2 operator -(const Vec2& i) const { return {x - i.x, y - i.y}; }
	Vec2 operator *(const Vec2& i) const { return {x * i.x, y * i.y}; }
	Vec2 operator *(const float i) const { return {x * i, y * i}; }
	Vec2 operator /(const Vec2& i) const { return {x / i.x, y / i.y}; }
	Vec2 operator /(const float i) const { return {x / i, y / i}; }
	const Vec2& operator +=(const Vec2& i) { return *this = *this + i; }
	const Vec2& operator -=(const Vec2& i) { return *this = *this - i; }
	const Vec2& operator *=(const Vec2& i) { return *this = *this * i; }
	const Vec2& operator *=(const float i) { return *this = *this * i; }
	const Vec2& operator /=(const Vec2& i) { return *this = *this / i; }
	const Vec2& operator /=(const float i) { return *this = *this / i; }

	[[nodiscard]] float dot(const Vec2& i) const
	{
		return (x * i.x + y * i.y);
	}

	[[nodiscard]] Vec2 cross(const Vec2& i) const
	{
		return Vec2(
			y * i.x - x * i.y,
			x * i.y - y * i.x);
	}

	[[nodiscard]] float length2() const
	{
		return x * x + y * y;
	}

	[[nodiscard]] float length() const
	{
		return std::sqrt(length2());
	}

	[[nodiscard]] Vec2 normalize() const
	{
		float l = length();
		return {x / l, y / l};
	}
};

struct Vec3
{
	float x, y, z;

	Vec3(float x, float y, float z)
		: x(x), y(y), z(z) {}

	Vec3(const float i)
		: Vec3(i, i, i) {}

	Vec3()
		: Vec3(0) {}

	Vec3(const Vec3& i)
		: Vec3(i.x, i.y, i.z) {}

	Vec3& operator=(const Vec3& inOther)
	{
		x = inOther.x;
		y = inOther.y;
		z = inOther.z;
		return *this;
	}

	float& operator[](size_t i)
	{
		assert(i < 3);
		return *(&x + i);
	}

	Vec3 operator -() const { return {-x, -y, -z}; }
	Vec3 operator +(const Vec3& i) const { return {x + i.x, y + i.y, z + i.z}; }
	Vec3 operator -(const Vec3& i) const { return {x - i.x, y - i.y, z - i.z}; }
	Vec3 operator *(const Vec3& i) const { return {x * i.x, y * i.y, z * i.z}; }
	Vec3 operator *(const float i) const { return {x * i, y * i, z * i}; }
	Vec3 operator /(const Vec3& i) const { return {x / i.x, y / i.y, z / i.z}; }
	Vec3 operator /(const float i) const { return {x / i, y / i, z / i}; }
	const Vec3& operator +=(const Vec3& i) { return *this = *this + i; }
	const Vec3& operator -=(const Vec3& i) { return *this = *this - i; }
	const Vec3& operator *=(const Vec3& i) { return *this = *this * i; }
	const Vec3& operator *=(const float i) { return *this = *this * i; }
	const Vec3& operator /=(const Vec3& i) { return *this = *this / i; }
	const Vec3& operator /=(const float i) { return *this = *this / i; }

	bool operator==(const Vec3& i) { return x == i.x && y == i.y && z == i.z; }

	[[nodiscard]] uint32 get_argb() const
	{
		const float t_r = gClamp<float>(x, 0, 1);
		const float t_g = gClamp<float>(y, 0, 1);
		const float t_b = gClamp<float>(z, 0, 1);
		return (uint32)255 | (static_cast<uint8_t>(t_r * 255) << 16) | (static_cast<uint8_t>(t_g * 255) << 8) | (static_cast<
			uint8_t>(t_b * 255));
	}

	[[nodiscard]] uint32_t get_rgba() const
	{
		const float t_r = gClamp<float>(x, 0, 1);
		const float t_g = gClamp<float>(y, 0, 1);
		const float t_b = gClamp<float>(z, 0, 1);
		return static_cast<uint32_t>((static_cast<uint8_t>(t_r * 255) << 24) | (static_cast<uint8_t>(t_g * 255) << 16) |
			(static_cast<uint8_t>(t_b * 255) << 8) | 255);
	}

	[[nodiscard]] float dot(const Vec3& i) const
	{
		return (x * i.x + y * i.y + z * i.z);
	}

	[[nodiscard]] Vec3 cross(const Vec3& i) const
	{
		return Vec3(
			y * i.z - z * i.y,
			z * i.x - x * i.z,
			x * i.y - y * i.x);
	}
};

struct alignas(4 * sizeof(float)) Vec4
{
	float x, y, z, w;

	Vec4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w) {}

	Vec4(const float i)
		: Vec4(i, i, i, i) {}

	Vec4()
		: Vec4(0) {}

	Vec4(const Vec4& i)
		: Vec4(i.x, i.y, i.z, i.w) {}

	Vec4& operator=(const Vec4& inOther)
	{
		x = inOther.x;
		y = inOther.y;
		z = inOther.z;
		w = inOther.w;
		return *this;
	}

	Vec4(const Vec3& i)
		: Vec4(i.x, i.y, i.z, 0.f) {}

	float& operator[](size_t i)
	{
		assert(i < 4);
		return *(&x + i);
	}

	const float& operator[](size_t i) const
	{
		assert(i < 4);
		return *(&x + i);
	}

	Vec4 operator -() const { return {-x, -y, -z, -w}; }
	Vec4 operator +(const Vec4& i) const { return {x + i.x, y + i.y, z + i.z, w + i.w}; }
	Vec4 operator -(const Vec4& i) const { return {x - i.x, y - i.y, z - i.z, w - i.w}; }
	Vec4 operator *(const Vec4& i) const { return {x * i.x, y * i.y, z * i.z, w * i.w}; }
	Vec4 operator *(const float i) const { return {x * i, y * i, z * i, w * i}; }
	Vec4 operator /(const Vec4& i) const { return {x / i.x, y / i.y, z / i.z, w / i.w}; }
	Vec4 operator /(const float i) const { return {x / i, y / i, z / i, w / i}; }
	const Vec4& operator +=(const Vec4& i) { return *this = *this + i; }
	const Vec4& operator -=(const Vec4& i) { return *this = *this - i; }
	const Vec4& operator *=(const Vec4& i) { return *this = *this * i; }
	const Vec4& operator *=(const float i) { return *this = *this * i; }
	const Vec4& operator /=(const Vec4& i) { return *this = *this / i; }
	const Vec4& operator /=(const float i) { return *this = *this / i; }

	[[nodiscard]] uint32_t get_argb() const
	{
		const float t_a = gClamp<float>(w, 0, 1);
		const float t_r = gClamp<float>(x, 0, 1);
		const float t_g = gClamp<float>(y, 0, 1);
		const float t_b = gClamp<float>(z, 0, 1);
		return static_cast<uint32_t>((static_cast<uint8_t>(t_a * 255) << 24) | (static_cast<uint8_t>(t_r * 255) << 16) |
			(static_cast<uint8_t>(t_g * 255) << 8) | (static_cast<uint8_t>(t_b * 255)));
	}

	[[nodiscard]] uint32_t get_rgba() const
	{
		const float t_a = gClamp<float>(w, 0, 1);
		const float t_r = gClamp<float>(x, 0, 1);
		const float t_g = gClamp<float>(y, 0, 1);
		const float t_b = gClamp<float>(z, 0, 1);
		return static_cast<uint32_t>((static_cast<uint8_t>(t_r * 255) << 24) | (static_cast<uint8_t>(t_g * 255) << 16) |
			(static_cast<uint8_t>(t_b * 255) << 8) | (static_cast<uint8_t>(t_a * 255)));
	}
};

struct alignas(4 * sizeof(float)) IVec4
{
	int32 x, y, z, w;

	IVec4(int32 x, int32 y, int32 z, int32 w)
		: x(x), y(y), z(z), w(w) {}

	IVec4(const int32 i)
		: IVec4(i, i, i, i) {}

	IVec4()
		: IVec4(0) {}

	IVec4(const IVec4& i)
		: IVec4(i.x, i.y, i.z, i.w) {}

	IVec4& operator=(const IVec4& inOther)
	{
		x = inOther.x;
		y = inOther.y;
		z = inOther.z;
		w = inOther.w;
		return *this;
	}

	IVec4(const IVec2& xy, const IVec2& zw)
		: IVec4(xy.x, xy.y, zw.x, zw.y) {}

	int32& operator[](size_t i)
	{
		assert(i < 4);
		return *(&x + i);
	}

	const int32& operator[](size_t i) const
	{
		assert(i < 4);
		return *(&x + i);
	}

	IVec4 operator -() const { return {-x, -y, -z, -w}; }
	IVec4 operator +(const IVec4& i) const { return {x + i.x, y + i.y, z + i.z, w + i.w}; }
	IVec4 operator -(const IVec4& i) const { return {x - i.x, y - i.y, z - i.z, w - i.w}; }
	IVec4 operator *(const IVec4& i) const { return {x * i.x, y * i.y, z * i.z, w * i.w}; }
	IVec4 operator *(const int32 i) const { return {x * i, y * i, z * i, w * i}; }
	IVec4 operator /(const IVec4& i) const { return {x / i.x, y / i.y, z / i.z, w / i.w}; }
	IVec4 operator /(const int32 i) const { return {x / i, y / i, z / i, w / i}; }
	const IVec4& operator +=(const IVec4& i) { return *this = *this + i; }
	const IVec4& operator -=(const IVec4& i) { return *this = *this - i; }
	const IVec4& operator *=(const IVec4& i) { return *this = *this * i; }
	const IVec4& operator *=(const int32 i) { return *this = *this * i; }
	const IVec4& operator /=(const IVec4& i) { return *this = *this / i; }
	const IVec4& operator /=(const int32 i) { return *this = *this / i; }
};

inline Vec2 gNormalize(const Vec2& i)
{
	float mag = std::sqrt(i.x * i.x + i.y * i.y);
	assert(mag != 0.f && "Try using normalize_safe instead");
	float inv = 1.f / mag;
	return {i.x * inv, i.y * inv};
}

inline Vec2 gNormalizeSafe(const Vec2& i)
{
	float mag = std::sqrt(i.x * i.x + i.y * i.y);
	if (mag == 0.f)
		mag = 1.f;
	float inv = 1.f / mag;
	return {i.x * inv, i.y * inv};
}

inline Vec3 gNormalize(const Vec3& i)
{
	float mag = std::sqrt(i.x * i.x + i.y * i.y + i.z * i.z);
	assert(mag != 0.f && "Try using normalize_safe instead");
	float inv = 1.f / mag;
	return {i.x * inv, i.y * inv, i.z * inv};
}

inline Vec3 gNormalizeSafe(const Vec3& i)
{
	float mag = std::sqrt(i.x * i.x + i.y * i.y + i.z * i.z);
	if (mag == 0.f)
		mag = 1.f;
	float inv = 1.f / mag;
	return {i.x * inv, i.y * inv, i.z * inv};
}

inline Vec4 gNormalize(const Vec4& i)
{
	float mag = std::sqrt(i.x * i.x + i.y * i.y + i.z * i.z);
	assert(mag != 0.f && "Try using normalize_safe instead");
	float inv = 1.f / mag;
	return {i.x * inv, i.y * inv, i.z * inv, i.w * inv};
}

inline Vec4 gNormalizeSafe(const Vec4& i)
{
	float mag = std::sqrt(i.x * i.x + i.y * i.y + i.z * i.z);
	if (mag == 0.f)
		mag = 1.f;
	float inv = 1.f / mag;
	return {i.x * inv, i.y * inv, i.z * inv, i.w * inv};
}

inline Vec2 gClamp2(Vec2 x, Vec2 a, Vec2 b)
{
	return
	{
		gClamp(x.x, a.x, b.x),
		gClamp(x.y, a.y, b.y)
	};
}

inline IVec2 gClamp2(IVec2 x, IVec2 a, IVec2 b)
{
	return
	{
		gClamp(x.x, a.x, b.x),
		gClamp(x.y, a.y, b.y)
	};
}

inline Vec2 gMax2(Vec2 a, Vec2 b)
{
	return
	{
		gMax(a.x, b.x),
		gMax(a.y, b.y)
	};
}

inline Vec2 gMin2(Vec2 a, Vec2 b)
{
	return
	{
		gMin(a.x, b.x),
		gMin(a.y, b.y)
	};
}

inline Vec2 gLerp2(Vec2 a, Vec2 b, float t)
{
	return a + (b - a) * t;
}

inline Vec3 gLerp3(Vec3 a, Vec3 b, float t)
{
	return a + (b - a) * t;
}

#pragma warning (pop)
