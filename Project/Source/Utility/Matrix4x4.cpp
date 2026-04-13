#include "Matrix4x4.h"
#include <cmath>

Matrix4x4::Matrix4x4() : 
	m00(0.0f),m01(0.0f),m02(0.0f),m03(0.0f),
	m10(0.0f),m11(0.0f),m12(0.0f),m13(0.0f),
	m20(0.0f),m21(0.0f),m22(0.0f),m23(0.0f),
	m30(0.0f),m31(0.0f),m32(0.0f),m33(0.0f)
{
}

Matrix4x4::Matrix4x4(float m00, float m01, float m02, float m03,
					 float m10, float m11, float m12, float m13,
					 float m20, float m21, float m22, float m23,
					 float m30, float m31, float m32, float m33) :
	m00(m00),m01(m01),m02(m02),m03(m03),
	m10(m10),m11(m11),m12(m12),m13(m13),
	m20(m20),m21(m21),m22(m22),m23(m23),
	m30(m30),m31(m31),m32(m32),m33(m33)
{
}

Matrix4x4 Matrix4x4::Identity()
{
	return Matrix4x4(1.0f,0.0f,0.0f,0.0f,
					 0.0f,1.0f,0.0f,0.0f,
					 0.0f,0.0f,1.0f,0.0f,
					 0.0f,0.0f,0.0f,1.0f);
}

Matrix4x4 Matrix4x4::Zero()
{
	return Matrix4x4(0.0f, 0.0f, 0.0f, 0.0f,
					 0.0f, 0.0f, 0.0f, 0.0f,
					 0.0f, 0.0f, 0.0f, 0.0f,
					 0.0f, 0.0f, 0.0f, 0.0f);
}

Matrix4x4 Matrix4x4::GetRotXMatrix(float angle)
{
	float cos = cosf(angle);
	float sin = sinf(angle);
	return Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
					 0.0f, cos, -sin, 0.0f,
					 0.0f, sin, cos, 0.0f,
					 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 Matrix4x4::GetRotYMatrix(float angle)
{
	float cos = cosf(angle);
	float sin = sinf(angle);
	return Matrix4x4(cos, 0.0f, sin, 0.0f,
					 0.0f, 1.0f, 0.0f, 0.0f,
					 -sin, 0.0f, cos, 0.0f,
					 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 Matrix4x4::GetRotZMatrix(float angle)
{
	float cos = cosf(angle);
	float sin = sinf(angle);
	return Matrix4x4(cos, -sin, 0.0f, 0.0f,
					 sin, cos, 0.0f, 0.0f,
					 0.0f, 0.0f, 1.0f, 0.0f,
					 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 Matrix4x4::GetTranslateMatrix(Vector3 v)
{
	Matrix4x4 ans = Identity();
	ans.m03 = v.x;
	ans.m13 = v.y;
	ans.m23 = v.z;
	return ans;
}

Matrix4x4 Matrix4x4::GetScaleMatrix(Vector3 v)
{
	Matrix4x4 ans = Identity();
	ans.m00 = v.x;
	ans.m11 = v.y;
	ans.m22 = v.z;
	return ans;
}

MATRIX Matrix4x4::ToDxLib() const
{
	return {m00,m10,m20,m30,
			m01,m11,m21,m31,
			m02,m12,m22,m32,
			m03,m13,m23,m33 };
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 m) const
{
	return Matrix4x4(
		m00 * m.m00 + m01 * m.m10 + m02 * m.m20 + m03 * m.m30,
		m00 * m.m01 + m01 * m.m11 + m02 * m.m21 + m03 * m.m31,
		m00 * m.m02 + m01 * m.m12 + m02 * m.m22 + m03 * m.m32,
		m00 * m.m03 + m01 * m.m13 + m02 * m.m23 + m03 * m.m33,
		m10 * m.m00 + m11 * m.m10 + m12 * m.m20 + m13 * m.m30,
		m10 * m.m01 + m11 * m.m11 + m12 * m.m21 + m13 * m.m31,
		m10 * m.m02 + m11 * m.m12 + m12 * m.m22 + m13 * m.m32,
		m10 * m.m03 + m11 * m.m13 + m12 * m.m23 + m13 * m.m33,
		m20 * m.m00 + m21 * m.m10 + m22 * m.m20 + m23 * m.m30,
		m20 * m.m01 + m21 * m.m11 + m22 * m.m21 + m23 * m.m31,
		m20 * m.m02 + m21 * m.m12 + m22 * m.m22 + m23 * m.m32,
		m20 * m.m03 + m21 * m.m13 + m22 * m.m23 + m23 * m.m33,
		m30 * m.m00 + m31 * m.m10 + m32 * m.m20 + m33 * m.m30,
		m30 * m.m01 + m31 * m.m11 + m32 * m.m21 + m33 * m.m31,
		m30 * m.m02 + m31 * m.m12 + m32 * m.m22 + m33 * m.m32,
		m30 * m.m03 + m31 * m.m13 + m32 * m.m23 + m33 * m.m33
	);
}

void Matrix4x4::operator*=(Matrix4x4 m)
{
	*this = *this * m;
}

Vector3 Matrix4x4::operator*(Vector3 v) const
{
	return Vector3(v.x * m00 + v.y * m01 + v.z * m02 + m03,
				   v.x * m10 + v.y * m11 + v.z * m12 + m13,
				   v.x * m20 + v.y * m21 + v.z * m22 + m23);
}

void Matrix4x4::operator*=(Vector3 v)
{
	v = *this * v;
}