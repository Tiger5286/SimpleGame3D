#include "Vector3.h"
#include <cmath>

Vector3::Vector3():
	x(0.0f),
	y(0.0f),
	z(0.0f)
{
}

Vector3::Vector3(float x, float y, float z) :
	x(x),
	y(y),
	z(z)
{
}

Vector3::~Vector3()
{
}

VECTOR Vector3::ToDxLib() const
{
	return { x,y,z };
}

Vector3 Vector3::FromDxLib(VECTOR vec)
{
	return Vector3(vec.x, vec.y, vec.z);
}

void Vector3::Draw(int x, int y) const
{
	DrawFormatString(x, y, 0xffffff, L"x:%.2f,y:%.2f,z:%.2f", this->x, this->y, this->z);
}

float Vector3::SquaredLength() const
{
	return x * x + y * y + z * z;
}

float Vector3::Length() const
{
	return sqrtf(SquaredLength());
}

void Vector3::Normalize()
{
	float length = Length();
	if (length > 0.0f)
	{
		x /= length;
		y /= length;
		z /= length;
	}
}

Vector3 Vector3::Normalized() const
{
	Vector3 ans;
	float length = Length();
	if (length > 0.0f)
	{
		ans.x = x / length;
		ans.y = y / length;
		ans.z = z / length;
	}
	return ans;
}

float Vector3::Dot(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::Cross(const Vector3& v) const
{
	return Vector3(y * v.z - z * v.y,
				   z * v.x - x * v.z,
				   x * v.y - y * v.x);
}

void Vector3::Lerp(const Vector3& v, float t)
{
	x = std::lerp(x, v.x, t);
	y = std::lerp(y, v.y, t);
	z = std::lerp(z, v.z, t);
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator+(const Vector3& v) const
{
	return Vector3(x + v.x,
				   y + v.y,
				   z + v.z);
}

void Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

Vector3 Vector3::operator-(const Vector3& v) const
{
	return Vector3(x - v.x,
				   y - v.y,
				   z - v.z);
}

void Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

Vector3 Vector3::operator*(float s) const
{
	return Vector3(x * s,
				   y * s,
				   z * s);
}

void Vector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
}

bool Vector3::operator==(const Vector3& v) const
{
	if (x == v.x && y == v.y && z == v.z) return true;
	return false;
}

bool Vector3::operator!=(const Vector3& v) const
{
	if (x != v.x || y != v.y || z != v.z) return true;
	return false;
}
