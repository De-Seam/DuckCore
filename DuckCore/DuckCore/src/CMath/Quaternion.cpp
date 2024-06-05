#include <CMath/Quaternion.h>
#include <CMath/HelperFunctions.h>

Vec3 Quat::rotate(const Vec3& v) const
{
	Quat p(v.x, v.y, v.z, 0);
	Quat q_inv(-x, -y, -z, w);
	Quat result = (*this) * p * q_inv;

	return Vec3(result.x, result.y, result.z);
}

Vec3 Quat::get_euler() const
{
	Vec3 angles;

	// yaw (z-axis rotation)
	{
		float siny_cosp = 2.f * (y * z + w * x);
		float cosy_cosp = w * w - x * x - y * y + z * z;

		angles.x = std::atan2(siny_cosp, cosy_cosp);
	}

	// pitch (y-axis rotation)
	{
		float sinp = 2.f * (w * y - z * x);
		if (std::abs(sinp) >= 1.f)
			angles.y = std::copysign(Pi() / 2.f, sinp); // use 90 degrees if out of range
		else
			angles.y = std::asin(sinp);
	}

	// roll (x-axis rotation)
	{
		float t_y = 2.f * (x * y + w * z);
		float t_x = w * w + x * x - y * y - z * z;

		angles.z = std::atan2(t_y, t_x);
	}

	return angles;
}
