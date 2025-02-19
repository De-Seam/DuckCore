#pragma once
// Core includes
#include <DuckCore/Config.h>
#include <DuckCore/Core/Assert.h>
#include <DuckCore/Core/Types.h>
#include <DuckCore/Math/HelperFunctions.h>
#include <DuckCore/Math/RGBA.h>
#include <DuckCore/Utilities/Json.h>

// Std includes
#include <cmath>

namespace DC
{
#pragma warning (push)
#pragma warning (disable : 4201) //to avoid nameless struct / union warning.

template<typename taType>
struct Vec2
{
	taType mX, mY;

	Vec2() : Vec2(0) {}
	Vec2(const taType& inX, const taType& inY) : mX(inX), mY(inY) {}
	explicit Vec2(const taType& inValue) : Vec2(inValue, inValue) {}

	Vec2(const Vec2& inOther) : Vec2(inOther.mX, inOther.mY) {}
	Vec2& operator=(const Vec2& inOther) = default;

	Vec2(Vec2&&) = default;
	Vec2& operator=(Vec2&& inOther) = default;

	~Vec2() = default;

	taType& operator[](int inIndex)
	{
		gAssert(inIndex < 2);
		return *(&mX + inIndex);
	}

	const taType& operator[](int inIndex) const
	{
		gAssert(inIndex < 2);
		return *(&mX + inIndex);
	}

	template<typename taOtherType>
	Vec2<taOtherType> As() const
	{
		return
		{
			static_cast<taOtherType>(mX),
			static_cast<taOtherType>(mY)
		};
	}

	template <typename taSameType = taType, std::enable_if_t<std::is_signed_v<taSameType>>>
	Vec2 operator -() const { return {-mX, -mY}; }

	Vec2 operator +(const Vec2& inOther) const { return {mX + inOther.mX, mY + inOther.mY}; }
	Vec2 operator -(const Vec2& inOther) const { return {mX - inOther.mX, mY - inOther.mY}; }
	Vec2 operator *(const Vec2& inOther) const { return {mX * inOther.mX, mY * inOther.mY}; }
	Vec2 operator *(const taType inMultiplier) const { return {mX * inMultiplier, mY * inMultiplier}; }
	Vec2 operator /(const Vec2& inOther) const { return {mX / inOther.mX, mY / inOther.mY}; }
	Vec2 operator /(const taType inDivider) const { return {mX / inDivider, mY / inDivider}; }
	const Vec2& operator +=(const Vec2& inOther) { return *this = *this + inOther; }
	const Vec2& operator -=(const Vec2& inOther) { return *this = *this - inOther; }
	const Vec2& operator *=(const Vec2& inOther) { return *this = *this * inOther; }
	const Vec2& operator *=(const taType inMultiplier) { return *this = *this * inMultiplier; }
	const Vec2& operator /=(const Vec2& inOther) { return *this = *this / inOther; }
	const Vec2& operator /=(const taType inDivider) { return *this = *this / inDivider; }

	bool operator==(const Vec2& inOther) const { return mX == inOther.mX && mY == inOther.mY; }
	bool operator!=(const Vec2& inOther) const { return !(*this == inOther); }

	[[nodiscard]] taType Dot(const Vec2& inOther) const
	{
		return (mX * inOther.mX + mY * inOther.mY);
	}

	[[nodiscard]] Vec2 Cross(const Vec2& inOther) const
	{
		return Vec2(
			mY * inOther.mX - mX * inOther.mY,
			mX * inOther.mY - mY * inOther.mX);
	}

	[[nodiscard]] taType Length2() const
	{
		return Dot(*this);
	}

	template <typename taSameType = float, typename = std::enable_if_t<std::is_same_v<taSameType, float>>>
	[[nodiscard]] float Length() const
	{
		return std::sqrtf(Length2());
	}

	template <typename taSameType = double, typename = std::enable_if_t<std::is_same_v<taSameType, double>>>
	[[nodiscard]] double Length() const
	{
		return std::sqrt(Length2());
	}

	template <typename taSameType = taType, std::enable_if_t<std::is_floating_point_v<taSameType>>>
	[[nodiscard]] Vec2 Normalize() const
	{
		taType l = Length<taType>();
		return {mX / l, mY / l};
	}
};

template<typename taType>
void to_json(Json& outJson, const Vec2<taType>& inVariable)
{
    outJson = { inVariable.mX, inVariable.mY };
}

template<typename taType>
void from_json(const Json& inJson, Vec2<taType>& outVariable)
{
    outVariable.mX = inJson[0];
	outVariable.mY = inJson[1];
}

template<typename taType>
struct Vec3
{
	taType mX, mY, mZ;

	Vec3() : Vec3(0) {}
	Vec3(const taType& inX, const taType& inY, const taType& inZ) : mX(inX), mY(inY), mZ(inZ) {}
	explicit Vec3(const taType& inValue) : Vec3(inValue, inValue, inValue) {}

	Vec3(const Vec3& inOther) : Vec3(inOther.mX, inOther.mY, inOther.mZ) {}
	Vec3& operator=(const Vec3& inOther) = default;

    Vec3(Vec3&&) = default;
    Vec3& operator=(Vec3&& inOther) = default;

	~Vec3() = default;

	taType& operator[](int inIndex)
	{
		gAssert(inIndex < 3);
		return *(&mX + inIndex);
	}

	const taType& operator[](int inIndex) const
	{
		gAssert(inIndex < 3);
		return *(&mX + inIndex);
	}

	template<typename taOtherType>
    Vec2<taOtherType> As() const
	{
	    return
	    {
	        static_cast<taOtherType>(mX),
	        static_cast<taOtherType>(mY),
	        static_cast<taOtherType>(mZ)
	    };
	}

	template <typename taSameType = taType, std::enable_if_t<std::is_signed_v<taSameType>>>
	Vec3 operator -() const { return {-mX, -mY, -mZ}; }

	Vec3 operator +(const Vec3& i) const { return {mX + i.mX, mY + i.mY, mZ + i.mZ}; }
	Vec3 operator -(const Vec3& i) const { return {mX - i.mX, mY - i.mY, mZ - i.mZ}; }
	Vec3 operator *(const Vec3& i) const { return {mX * i.mX, mY * i.mY, mZ * i.mZ}; }
	Vec3 operator *(const taType i) const { return {mX * i, mY * i, mZ * i}; }
	Vec3 operator /(const Vec3& i) const { return {mX / i.mX, mY / i.mY, mZ / i.mZ}; }
	Vec3 operator /(const taType i) const { return {mX / i, mY / i, mZ / i}; }
	const Vec3& operator +=(const Vec3& i) { return *this = *this + i; }
	const Vec3& operator -=(const Vec3& i) { return *this = *this - i; }
	const Vec3& operator *=(const Vec3& i) { return *this = *this * i; }
	const Vec3& operator *=(const taType i) { return *this = *this * i; }
	const Vec3& operator /=(const Vec3& i) { return *this = *this / i; }
	const Vec3& operator /=(const taType i) { return *this = *this / i; }

	bool operator==(const Vec3& inOther) { return mX == inOther.mX && mY == inOther.mY && mZ == inOther.mZ; }

	template <typename taSameType = float, typename = std::enable_if_t<std::is_same_v<taSameType, float>>>
	[[nodiscard]] uint32 GetARGB() const
	{
        static_assert(std::is_floating_point_v<taType>);

		const taType t_r = gClamp<taType>(mX, 0, 1);
		const taType t_g = gClamp<taType>(mY, 0, 1);
		const taType t_b = gClamp<taType>(mZ, 0, 1);
		return static_cast<uint32>(255) | (static_cast<uint8_t>(t_r * 255) << 16) | (static_cast<uint8_t>(t_g * 255) << 8) | (static_cast<
			uint8_t>(t_b * 255));
	}

	template <typename taSameType = float, typename = std::enable_if_t<std::is_same_v<taSameType, float>>>
	[[nodiscard]] RGBA GetRGBA() const
	{
		return RGBA(gClamp(mX, 0.0f, 1.0f), gClamp(mY, 0.0f, 1.0f), gClamp(mZ, 0.0f, 1.0f), 1.0f);
	}

	[[nodiscard]] taType Dot(const Vec3& inOther) const
	{
		return (mX * inOther.mX + mY * inOther.mY + mZ * inOther.mZ);
	}

	[[nodiscard]] Vec3 Cross(const Vec3& inOther) const
	{
		return Vec3(
			mY * inOther.mZ - mZ * inOther.mY,
			mZ * inOther.mX - mX * inOther.mZ,
			mX * inOther.mY - mY * inOther.mX);
	}

	[[nodiscard]] taType Length2() const
	{
		return Dot(*this);
	}

	template <typename taSameType = float, typename = std::enable_if_t<std::is_same_v<taSameType, float>>>
	[[nodiscard]] float Length() const
	{
		return std::sqrtf(Length2());
	}

	template <typename taSameType = double, typename = std::enable_if_t<std::is_same_v<taSameType, double>>>
	[[nodiscard]] double Length() const
	{
		return std::sqrt(Length2());
	}

	template <typename taSameType = taType, std::enable_if_t<std::is_floating_point_v<taSameType>>>
	[[nodiscard]] Vec3 Normalize() const
	{
		taType l = Length<taType>();
		return { mX / l, mY / l };
	}
};

template<typename taType>
struct alignas(4 * sizeof(taType)) Vec4
{
	taType mX, mY, mZ, mW;

	Vec4() : Vec4(0) {}
	Vec4(const taType& inX, const taType& inY, const taType& inZ, const taType& inW) : mX(inX), mY(inY), mZ(inZ), mW(inW) {}
	explicit Vec4(const taType& inValue) : Vec4(inValue, inValue, inValue, inValue) {}

	Vec4(const Vec4& inOther) : Vec4(inOther.mX, inOther.mY, inOther.mZ, inOther.mW) {}
	Vec4& operator=(const Vec4& inOther) = default;

    Vec4(Vec4&&) = default;
    Vec4& operator=(Vec4&& inOther) = default;

	~Vec4() = default;

	taType& operator[](int inIndex)
	{
		gAssert(inIndex < 4);
		return *(&mX + inIndex);
	}

	const taType& operator[](int inIndex) const
	{
		gAssert(inIndex < 4);
		return *(&mX + inIndex);
	}

	template<typename taOtherType>
    Vec2<taOtherType> As() const
	{
	    return
	    {
	        static_cast<taOtherType>(mX),
	        static_cast<taOtherType>(mY),
	        static_cast<taOtherType>(mZ),
			static_cast<taOtherType>(mW)
	    };
	}

	template <typename taSameType = taType, std::enable_if_t<std::is_signed_v<taSameType>>>
	Vec4 operator -() const { return {-mX, -mY, -mZ, -mW}; }

	Vec4 operator +(const Vec4& i) const { return {mX + i.mX, mY + i.mY, mZ + i.mZ, mW + i.mW}; }
	Vec4 operator -(const Vec4& i) const { return {mX - i.mX, mY - i.mY, mZ - i.mZ, mW - i.mW}; }
	Vec4 operator *(const Vec4& i) const { return {mX * i.mX, mY * i.mY, mZ * i.mZ, mW * i.mW}; }
	Vec4 operator *(const taType i) const { return {mX * i, mY * i, mZ * i, mW * i}; }
	Vec4 operator /(const Vec4& i) const { return {mX / i.mX, mY / i.mY, mZ / i.mZ, mW / i.mW}; }
	Vec4 operator /(const taType i) const { return {mX / i, mY / i, mZ / i, mW / i}; }
	const Vec4& operator +=(const Vec4& i) { return *this = *this + i; }
	const Vec4& operator -=(const Vec4& i) { return *this = *this - i; }
	const Vec4& operator *=(const Vec4& i) { return *this = *this * i; }
	const Vec4& operator *=(const taType i) { return *this = *this * i; }
	const Vec4& operator /=(const Vec4& i) { return *this = *this / i; }
	const Vec4& operator /=(const taType i) { return *this = *this / i; }

	template <typename taSameType = float, typename = std::enable_if_t<std::is_same_v<taSameType, float>>>
	[[nodiscard]] uint32 GetARGB() const
	{
		const taType t_a = gClamp<taType>(mW, 0, 1);
		const taType t_r = gClamp<taType>(mX, 0, 1);
		const taType t_g = gClamp<taType>(mY, 0, 1);
		const taType t_b = gClamp<taType>(mZ, 0, 1);
		return static_cast<uint32>((static_cast<uint8_t>(t_a * 255) << 24) | (static_cast<uint8_t>(t_r * 255) << 16) |
			(static_cast<uint8_t>(t_g * 255) << 8) | (static_cast<uint8_t>(t_b * 255)));
	}

	template <typename taSameType = float, typename = std::enable_if_t<std::is_same_v<taSameType, float>>>
	[[nodiscard]] RGBA GetRGBA() const
	{
		return RGBA(gClamp(mX, 0.0f, 1.0f), gClamp(mY, 0.0f, 1.0f), gClamp(mZ, 0.0f, 1.0f), gClamp(mW, 0.0f, 1.0f));
	}

	[[nodiscard]] taType Dot(const Vec4& inOther) const
	{
		return (mX * inOther.mX + mY * inOther.mY + mZ * inOther.mZ + mW * mW);
	}

	[[nodiscard]] taType Length2() const
	{
		return Dot(*this);
	}

	template <typename taSameType = float, typename = std::enable_if_t<std::is_same_v<taSameType, float>>>
	[[nodiscard]] float Length() const
	{
		return std::sqrtf(Length2());
	}

	template <typename taSameType = double, typename = std::enable_if_t<std::is_same_v<taSameType, double>>>
	[[nodiscard]] double Length() const
	{
		return std::sqrt(Length2());
	}

	template <typename taSameType = taType, std::enable_if_t<std::is_floating_point_v<taSameType>>>
	[[nodiscard]] Vec4 Normalize() const
	{
		taType l = Length<taType>();
		return { mX / l, mY / l };
	}
};

template<typename taType>
inline Vec2<taType> gNormalize(const Vec2<taType>& inVector)
{
    static_assert(std::is_floating_point_v<taType>);

	taType mag = std::sqrt(inVector.mX * inVector.mX + inVector.mY * inVector.mY);
	gAssert(mag != 0.f, "Try using normalize_safe instead");
	taType inv = 1.f / mag;
	return {inVector.mX * inv, inVector.mY * inv};
}

template<typename taType>
inline Vec2<taType> gNormalizeSafe(const Vec2<taType>& inVector)
{
    static_assert(std::is_floating_point_v<taType>);

	taType mag = std::sqrt(inVector.mX * inVector.mX + inVector.mY * inVector.mY);
	if (mag == 0.f)
		mag = 1.f;
	taType inv = 1.f / mag;
	return {inVector.mX * inv, inVector.mY * inv};
}

template<typename taType>
inline Vec3<taType> gNormalize(const Vec3<taType>& i)
{
    static_assert(std::is_floating_point_v<taType>);

	taType mag = std::sqrt(i.mX * i.mX + i.mY * i.mY + i.mZ * i.mZ);
	gAssert(mag != 0.f && "Try using normalize_safe instead");
	taType inv = 1.f / mag;
	return {i.mX * inv, i.mY * inv, i.mZ * inv};
}

template<typename taType>
inline Vec3<taType> gNormalizeSafe(const Vec3<taType>& i)
{
    static_assert(std::is_floating_point_v<taType>);

	taType mag = std::sqrt(i.mX * i.mX + i.mY * i.mY + i.mZ * i.mZ);
	if (mag == 0.f)
		mag = 1.f;
	taType inv = 1.f / mag;
	return {i.mX * inv, i.mY * inv, i.mZ * inv};
}

template<typename taType>
inline Vec4<taType> gNormalize(const Vec4<taType>& i)
{
    static_assert(std::is_floating_point_v<taType>);

	taType mag = std::sqrt(i.mX * i.mX + i.mY * i.mY + i.mZ * i.mZ);
	assert(mag != 0.f && "Try using normalize_safe instead");
	taType inv = 1.f / mag;
	return {i.mX * inv, i.mY * inv, i.mZ * inv, i.mW * inv};
}

template<typename taType>
inline Vec4<taType> gNormalizeSafe(const Vec4<taType>& inVector)
{
    static_assert(std::is_floating_point_v<taType>);

	taType mag = std::sqrt(inVector.mX * inVector.mX + inVector.mY * inVector.mY + inVector.mZ * inVector.mZ);
	if (mag == 0.f)
		mag = 1.f;
	taType inv = 1.f / mag;
	return {inVector.mX * inv, inVector.mY * inv, inVector.mZ * inv, inVector.mW * inv};
}

template<typename taType>
inline Vec2<taType> gClamp2(const Vec2<taType>& inValue, const Vec2<taType>& inMin, const Vec2<taType>& inMax)
{
	return
	{
		gClamp(inValue.mX, inMin.mX, inMax.mX),
		gClamp(inValue.mY, inMin.mY, inMax.mY)
	};
}

template<typename taType>
inline Vec2<taType> gMax2(const Vec2<taType>& inA, const Vec2<taType>& inB)
{
	return
	{
		gMax(inA.mX, inB.mX),
		gMax(inA.mY, inB.mY)
	};
}

template<typename taType>
inline Vec2<taType> gMin2(const Vec2<taType>& inA, const Vec2<taType>& inB)
{
	return
	{
		gMin(inA.mX, inB.mX),
		gMin(inA.mY, inB.mY)
	};
}

template<typename taType>
inline Vec2<taType> gLerp2(const Vec2<taType>& inA, const Vec2<taType>& inB, taType inT)
{
	return inA + (inB - inA) * inT;
}

template<typename taType>
inline Vec3<taType> gLerp3(const Vec3<taType>& inA, const Vec3<taType>& inB, taType inT)
{
	return inA + (inB - inA) * inT;
}

// Vec2
using DVec2 = Vec2<double>;
using FVec2 = Vec2<float>;
using IVec2 = Vec2<int32>;
using UVec2 = Vec2<uint32>;
extern template struct Vec2<double>;
extern template struct Vec2<float>;
extern template struct Vec2<int32>;
extern template struct Vec2<uint32>;

// Vec3
using DVec3 = Vec3<double>;
using FVec3 = Vec3<float>;
using IVec3 = Vec3<int32>;
using UVec3 = Vec3<uint32>;
extern template struct Vec3<double>;
extern template struct Vec3<float>;
extern template struct Vec3<int32>;
extern template struct Vec3<uint32>;

// Vec4
using DVec4 = Vec4<double>;
using FVec4 = Vec4<float>;
using IVec4 = Vec4<int32>;
using UVec4 = Vec4<uint32>;
extern template struct Vec4<double>;
extern template struct Vec4<float>;
extern template struct Vec4<int32>;
extern template struct Vec4<uint32>;

#pragma warning (pop)

}
