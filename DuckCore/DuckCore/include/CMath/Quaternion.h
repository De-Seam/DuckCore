#pragma once
#include <CMath/Vector.h>

struct Quat
{
	float x, y, z, w;

	Quat() = default;

	Quat(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w) {}

	Quat(float a_x, float a_y, float a_z)
	{
		float cy = std::cos(a_z * 0.5f);
		float sy = std::sin(a_z * 0.5f);
		float cp = std::cos(a_y * 0.5f);
		float sp = std::sin(a_y * 0.5f);
		float cr = std::cos(a_x * 0.5f);
		float sr = std::sin(a_x * 0.5f);

		w = cr * cp * cy + sr * sp * sy;
		x = sr * cp * cy - cr * sp * sy;
		y = cr * sp * cy + sr * cp * sy;
		z = cr * cp * sy - sr * sp * cy;
	}

	Quat(const Vec3& i)
		: Quat(i.x, i.y, i.z) {}

	Quat(const Quat& inOther)
		: x(inOther.x), y(inOther.y), z(inOther.z), w(inOther.w) {}

	Quat& operator=(const Quat& inOther)
	{
		x = inOther.x;
		y = inOther.y;
		z = inOther.z;
		w = inOther.w;
		return *this;
	}

	Quat operator -() const { return {-x, -y, -z, -w}; }
	Quat operator +(const Quat& i) const { return {x + i.x, y + i.y, z + i.z, w + i.w}; }
	Quat operator -(const Quat& i) const { return {x - i.x, y - i.y, z - i.z, w - i.w}; }
	Quat operator *(const float i) const { return {x * i, y * i, z * i, w * i}; }

	Quat operator *(const Quat& i) const
	{
		return
		{
			w * i.x + x * i.w + y * i.z - z * i.y,
			w * i.y - x * i.z + y * i.w + z * i.x,
			w * i.z + x * i.y - y * i.x + z * i.w,
			w * i.w - x * i.x - y * i.y - z * i.z
		};
	}

	const Quat& operator +=(const Quat& i) { return *this = *this + i; }
	const Quat& operator -=(const Quat& i) { return *this = *this - i; }
	const Quat& operator *=(const Quat& i) { return *this = *this * i; }
	const Quat& operator *=(const float i) { return *this = *this * i; }

	Vec3 rotate(const Vec3& v) const;

	Vec3 get_euler() const;
};

inline Quat gNormalize(const Quat& q)
{
	float n = sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	if (n <= 0.f)
		return {0, 0, 0, 0};
	n = 1.f / n;
	return
	{
		q.x * n,
		q.y * n,
		q.z * n,
		q.w * n
	};
}

inline Quat gAngleAxis(float angle, const Vec3& i)
{
	float a(angle);
	float s = std::sin(a * 0.5f);

	Vec3 xyz = i * s;
	return {xyz.x, xyz.y, xyz.z, std::cos(a * 0.5f)};
}
