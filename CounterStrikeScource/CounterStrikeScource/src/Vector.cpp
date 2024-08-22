/*
	this is a simple class for assaultcube
	  AssaultCube Version 1.2.0.2
	created by: captain_x-X#2181
	https://github.com/Captain-X-X
*/
#include "pch.h"
#include "Vector.h"

m_Vector2::m_Vector2()
{
	x = y = 0.0f;
}
m_Vector2::m_Vector2(float init)
{
	this->x = init;
	this->y = init;
}
m_Vector2::m_Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

void m_Vector2::scaleFixedPoint(float scale, m_Vector2 fixedPoint)
{
	x = x * scale + fixedPoint.x * (1 - scale);
	y = y * scale + fixedPoint.y * (1 - scale);
}

m_Vector3 m_Vector3::m_Vector3Add(m_Vector3 src, m_Vector3 dst)
{
	m_Vector3 add;
	add.x = src.x + dst.x;
	add.y = src.y + dst.y;
	add.z = src.z + dst.z;
	return add;
}

m_Vector3 m_Vector3::m_Vector3Sub(m_Vector3 src, m_Vector3 dst)
{
	m_Vector3 sub;
	sub.x = src.x - dst.x;
	sub.y = src.y - dst.y;
	sub.z = src.z - dst.z;
	return sub;
}

m_Vector3 m_Vector3::m_Vector3Multiply(m_Vector3 src, m_Vector3 dst)
{
	m_Vector3 multiply;
	multiply.x = src.x * dst.x;
	multiply.y = src.y * dst.y;
	multiply.z = src.z * dst.z;
	return multiply;
}

m_Vector3 m_Vector3::m_Vector3Divide(m_Vector3 src, m_Vector3 dst)
{
	m_Vector3 divide;
	divide.x = src.x / dst.x;
	divide.y = src.y / dst.y;
	divide.z = src.z / dst.z;
	return divide;
}