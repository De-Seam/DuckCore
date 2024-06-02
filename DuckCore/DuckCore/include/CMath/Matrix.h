#pragma once
#include <CMath/Vector.h>

struct Mat3
{
	Vec3 x, y, z;

	Mat3() {}

	Mat3(float i) :
		x(i, 0, 0),
		y(0, i, 0),
		z(0, 0, i) {}

	Mat3(Vec3 x, Vec3 y, Vec3 z)
		: x(x), y(y), z(z) {}

	Mat3(const Mat3& i)
		: x(i.x), y(i.y), z(i.z) {}

	Mat3& operator=(const Mat3& inOther)
	{
		x = inOther.x;
		y = inOther.y;
		z = inOther.z;
		return *this;
	}

	Vec3& operator[](size_t i)
	{
		assert(i < 3);
		return *(&x + i);
	}

	Mat3 operator*(Mat3& i)
	{
		return
		{
			{x[0] * i.x[0] + x[1] * i.y[0] + x[2] * i.z[0]},
			{y[0] * i.x[1] + y[1] * i.y[1] + y[2] * i.z[1]},
			{z[0] * i.x[2] + z[1] * i.y[2] + z[2] * i.z[2]}
		};
	}
};

struct Mat4
{
	Vec4 x, y, z, w;

	Mat4() {}

	Mat4(float i) :
		x(i, 0, 0, 0),
		y(0, i, 0, 0),
		z(0, 0, i, 0),
		w(0, 0, 0, i) {}

	Mat4(Vec4 x, Vec4 y, Vec4 z, Vec4 w)
		: x(x), y(y), z(z), w(w) {}

	Mat4(const Mat4& i)
		: x(i.x), y(i.y), z(i.z), w(i.w) {}

	Mat4& operator=(const Mat4& inOther)
	{
		x = inOther.x;
		y = inOther.y;
		z = inOther.z;
		w = inOther.w;
		return *this;
	}

	Mat4(const Mat3& i)
		: x(i.x), y(i.y), z(i.z), w(0.f, 0.f, 0.f, 1.f) {}

	Vec4& operator[](size_t i)
	{
		assert(i < 4);
		return *(&x + i);
	}

	const Vec4& operator[](size_t i) const
	{
		assert(i < 4);
		return *(&x + i);
	}

	Mat4 operator*(const Mat4& i) const
	{
		Mat4 result;
#ifdef USE_SIMD

		__m256d row1 = _mm256_loadu_pd(&x.x);
		__m256d row2 = _mm256_loadu_pd(&y.x);
		__m256d row3 = _mm256_loadu_pd(&z.x);
		__m256d row4 = _mm256_loadu_pd(&w.x);

		for (int j = 0; j < 4; ++j) {
			__m256d col = _mm256_set_pd(i.w[j], i.z[j], i.y[j], i.x[j]);

			__m256d r1 = _mm256_mul_pd(row1, col);
			__m256d r2 = _mm256_mul_pd(row2, col);
			__m256d r3 = _mm256_mul_pd(row3, col);
			__m256d r4 = _mm256_mul_pd(row4, col);

			r1 = _mm256_hadd_pd(r1, r1);
			r2 = _mm256_hadd_pd(r2, r2);
			r3 = _mm256_hadd_pd(r3, r3);
			r4 = _mm256_hadd_pd(r4, r4);

			float res1[4], res2[4], res3[4], res4[4];
			_mm256_storeu_pd(res1, r1);
			_mm256_storeu_pd(res2, r2);
			_mm256_storeu_pd(res3, r3);
			_mm256_storeu_pd(res4, r4);

			result.x[j] = res1[0] + res1[2];
			result.y[j] = res2[0] + res2[2];
			result.z[j] = res3[0] + res3[2];
			result.w[j] = res4[0] + res4[2];
		}

#else
		result.x.x = x.x * i.x.x + x.y * i.y.x + x.z * i.z.x + x.w * i.w.x;
		result.x.y = x.x * i.x.y + x.y * i.y.y + x.z * i.z.y + x.w * i.w.y;
		result.x.z = x.x * i.x.z + x.y * i.y.z + x.z * i.z.z + x.w * i.w.z;
		result.x.w = x.x * i.x.w + x.y * i.y.w + x.z * i.z.w + x.w * i.w.w;

		result.y.x = y.x * i.x.x + y.y * i.y.x + y.z * i.z.x + y.w * i.w.x;
		result.y.y = y.x * i.x.y + y.y * i.y.y + y.z * i.z.y + y.w * i.w.y;
		result.y.z = y.x * i.x.z + y.y * i.y.z + y.z * i.z.z + y.w * i.w.z;
		result.y.w = y.x * i.x.w + y.y * i.y.w + y.z * i.z.w + y.w * i.w.w;

		result.z.x = z.x * i.x.x + z.y * i.y.x + z.z * i.z.x + z.w * i.w.x;
		result.z.y = z.x * i.x.y + z.y * i.y.y + z.z * i.z.y + z.w * i.w.y;
		result.z.z = z.x * i.x.z + z.y * i.y.z + z.z * i.z.z + z.w * i.w.z;
		result.z.w = z.x * i.x.w + z.y * i.y.w + z.z * i.z.w + z.w * i.w.w;

		result.w.x = w.x * i.x.x + w.y * i.y.x + w.z * i.z.x + w.w * i.w.x;
		result.w.y = w.x * i.x.y + w.y * i.y.y + w.z * i.z.y + w.w * i.w.y;
		result.w.z = w.x * i.x.z + w.y * i.y.z + w.z * i.z.z + w.w * i.w.z;
		result.w.w = w.x * i.x.w + w.y * i.y.w + w.z * i.z.w + w.w * i.w.w;
#endif
		return result;
	}

	const Mat4& operator *=(const Mat4& i) { return *this = *this * i; }

	std::string to_string()
	{
		return std::to_string(x.x) + " : " + std::to_string(x.y) + " : " + std::to_string(x.z) + " : " +
			std::to_string(x.w) + "\n" +
			std::to_string(y.x) + " : " + std::to_string(y.y) + " : " + std::to_string(y.z) + " : " +
			std::to_string(y.w) + "\n" +
			std::to_string(z.x) + " : " + std::to_string(z.y) + " : " + std::to_string(z.z) + " : " +
			std::to_string(z.w) + "\n" +
			std::to_string(w.x) + " : " + std::to_string(w.y) + " : " + std::to_string(w.z) + " : " +
			std::to_string(w.w) + "\n";
	}
};

Mat4 translate(Mat4 matrix, Vec3 vector)
{
	matrix.w = matrix.x * vector.x + matrix.y * vector.y + matrix.z * vector.z + matrix.w;
	return matrix;
}

Mat4 scale(Mat4 matrix, Vec3 vector)
{
	matrix[0] = matrix[0] * vector[0];
	matrix[1] = matrix[1] * vector[1];
	matrix[2] = matrix[2] * vector[2];
	return matrix;
}

Mat4 rotate(Mat4 m, float angle, Vec3 v)
{
	const float a = angle;
	const float c = cos(a);
	const float s = sin(a);

	Vec3 axis(gNormalize(v));
	Vec3 temp(axis * (1.f - c));

	Mat4 temp_matrix;
	temp_matrix[0][0] = c + temp[0] * axis[0];
	temp_matrix[0][1] = temp[0] * axis[1] + s * axis[2];
	temp_matrix[0][2] = temp[0] * axis[2] - s * axis[1];

	temp_matrix[1][0] = temp[1] * axis[0] - s * axis[2];
	temp_matrix[1][1] = c + temp[1] * axis[1];
	temp_matrix[1][2] = temp[1] * axis[2] + s * axis[0];

	temp_matrix[2][0] = temp[2] * axis[0] + s * axis[1];
	temp_matrix[2][1] = temp[2] * axis[1] - s * axis[0];
	temp_matrix[2][2] = c + temp[2] * axis[2];

	Mat4 result;
	result[0] = m[0] * temp_matrix[0][0] + m[1] * temp_matrix[0][1] + m[2] * temp_matrix[0][2];
	result[1] = m[0] * temp_matrix[1][0] + m[1] * temp_matrix[1][1] + m[2] * temp_matrix[1][2];
	result[2] = m[0] * temp_matrix[2][0] + m[1] * temp_matrix[2][1] + m[2] * temp_matrix[2][2];
	result[3] = m[3];
	return result;
}

Mat4 get_perspective(float fovy, float aspect, float znear, float zfar)
{
	assert(abs(aspect - std::numeric_limits<float>::epsilon()) > 0.f);

	const float tanHalfFovy = tan(fovy / 2.f);

	Mat4 result(1.f);
	result[0][0] = 1.f / (aspect * tanHalfFovy);
	result[1][1] = 1.f / (tanHalfFovy);
	result[2][2] = -(zfar + znear) / (zfar - znear);
	result[2][3] = -1.f;
	result[3][2] = -2.f * zfar * znear / (zfar - znear);
	return result;
}

Mat4 look_at(const Vec3& eye, const Vec3& target, const Vec3& up)
{
	Vec3 zaxis = gNormalize(eye - target);
	Vec3 xaxis = gNormalize(up.cross(zaxis));
	Vec3 yaxis = zaxis.cross(xaxis);

	Mat4 view;
	view[0][0] = xaxis.x;
	view[1][0] = xaxis.y;
	view[2][0] = xaxis.z;
	view[3][0] = -xaxis.dot(eye);

	view[0][1] = yaxis.x;
	view[1][1] = yaxis.y;
	view[2][1] = yaxis.z;
	view[3][1] = -yaxis.dot(eye);

	view[0][2] = zaxis.x;
	view[1][2] = zaxis.y;
	view[2][2] = zaxis.z;
	view[3][2] = -zaxis.dot(eye);

	return view;
}

Mat3 to_mat3(const Quat& q)
{
	Mat3 result(1.f);
	float qxx(q.x * q.x);
	float qyy(q.y * q.y);
	float qzz(q.z * q.z);
	float qxz(q.x * q.z);
	float qxy(q.x * q.y);
	float qyz(q.y * q.z);
	float qwx(q.w * q.x);
	float qwy(q.w * q.y);
	float qwz(q.w * q.z);

	result[0][0] = 1.f - 2.f * (qyy + qzz);
	result[0][1] = 2.f * (qxy + qwz);
	result[0][2] = 2.f * (qxz - qwy);

	result[1][0] = 2.f * (qxy - qwz);
	result[1][1] = 1.f - 2.f * (qxx + qzz);
	result[1][2] = 2.f * (qyz + qwx);

	result[2][0] = 2.f * (qxz + qwy);
	result[2][1] = 2.f * (qyz - qwx);
	result[2][2] = 1.f - 2.f * (qxx + qyy);
	return result;
}

Mat4 to_mat4(const Quat& q)
{
	Mat3 matrix3 = to_mat3(q);
	Mat4 matrix4 = Mat4(matrix3);
	return matrix4;
}
