#include <CMath/Matrix.h>
#include <CMath/Quaternion.h>

Mat4 gTranslate(Mat4 matrix, Vec3 vector)
{
	matrix.w = matrix.x * vector.x + matrix.y * vector.y + matrix.z * vector.z + matrix.w;
	return matrix;
}

Mat4 gScale(Mat4 matrix, Vec3 vector)
{
	matrix[0] = matrix[0] * vector[0];
	matrix[1] = matrix[1] * vector[1];
	matrix[2] = matrix[2] * vector[2];
	return matrix;
}

Mat4 gRotate(Mat4 m, float angle, Vec3 v)
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

Mat4 GetPerspective(float fovy, float aspect, float znear, float zfar)
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

Mat4 gLookAt(const Vec3& eye, const Vec3& target, const Vec3& up)
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

Mat3 gToMat3(const Quat& q)
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

Mat4 gToMat4(const Quat& q)
{
	Mat3 matrix3 = gToMat3(q);
	Mat4 matrix4 = Mat4(matrix3);
	return matrix4;
}
