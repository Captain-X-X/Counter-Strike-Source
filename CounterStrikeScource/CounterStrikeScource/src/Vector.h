#pragma once
/*
	this is a simple class for assaultcube
	  AssaultCube Version 1.2.0.2
	created by: captain_x-X#2181
	https://github.com/Captain-X-X
*/

#define PI         3.14159265358979323846
#include <math.h>
#include <corecrt_math.h>
#include <cfloat>
#include <vector>

struct m_Vector2 // for source engine games
{
	m_Vector2();
	m_Vector2(float init);
	m_Vector2(float x, float y);
	float x{ 0 };
	float y{ 0 };
	void scaleFixedPoint(float scale, m_Vector2 fixedPoint);
};

class m_Vector3 // for source engine games
{
public:
	float x = 0.f;
	float z = 0.f;
	float y = 0.f;
	m_Vector3() {};
	m_Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
	m_Vector3 operator + (const m_Vector3& rhs) const { return m_Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	m_Vector3 operator - (const m_Vector3& rhs) const { return m_Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
	m_Vector3 operator * (const float& rhs) const { return m_Vector3(x * rhs, y * rhs, z * rhs); }
	m_Vector3 operator / (const float& rhs) const { return m_Vector3(x / rhs, y / rhs, z / rhs); }
	m_Vector3& operator += (const m_Vector3& rhs) { return *this = *this + rhs; }
	m_Vector3& operator -= (const m_Vector3& rhs) { return *this = *this - rhs; }
	m_Vector3& operator *= (const float& rhs) { return *this = *this * rhs; }
	m_Vector3& operator /= (const float& rhs) { return *this = *this / rhs; }
	float Length() const { return sqrtf(x * x + y * y + z * z); }
	m_Vector3 Normalize() const { return *this * (1 / Length()); }
	float Distance(const m_Vector3& rhs) const { return (*this - rhs).Length(); }
	m_Vector3 m_Vector3Add(m_Vector3 src, m_Vector3 dst);
	m_Vector3 m_Vector3Sub(m_Vector3 src, m_Vector3 dst);
	m_Vector3 m_Vector3Multiply(m_Vector3 src, m_Vector3 dst);
	m_Vector3 m_Vector3Divide(m_Vector3 src, m_Vector3 dst);
};

struct m_Vector4
{
	m_Vector4()
	{
		x = y = z = w = 0.0f;
	}
	m_Vector4(float _x, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	float x, z, y, w;
};