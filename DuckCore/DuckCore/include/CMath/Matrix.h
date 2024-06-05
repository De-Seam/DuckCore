#pragma once
#include <CMath/Vector.h>

struct Quat;

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

Mat4 gTranslate(Mat4 matrix, Vec3 vector);

Mat4 gScale(Mat4 matrix, Vec3 vector);

Mat4 gRotate(Mat4 m, float angle, Vec3 v);

Mat4 GetPerspective(float fovy, float aspect, float znear, float zfar);

Mat4 gLookAt(const Vec3& eye, const Vec3& target, const Vec3& up);

Mat3 gToMat3(const Quat& q);

Mat4 gToMat4(const Quat& q);
