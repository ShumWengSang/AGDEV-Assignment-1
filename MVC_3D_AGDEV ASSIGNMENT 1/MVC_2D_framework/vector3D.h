#ifndef __VECTOR_3D__
#define __VECTOR_3D__

#ifndef __MATH_H__
#include <math.h>
#define __MATH_H__
#endif

#ifndef __MATRIX4X4_H__
#include "SceneGraph\Matrix4x4.h"
#endif

#define PI 3.14156

class Vector3D
{
public:
	float m_x, m_y, m_z;

	//default constructor
	Vector3D(float X = 0, float Y = 0, float Z = 0)
	{
		m_x = X;
		m_y = Y;
		m_z = Z;
	}
	~Vector3D(){};

	void Set(float X = 0.0, float Y = 0.0, float Z = 0.0)
	{
		m_x = X;
		m_y = Y;
		m_z = Z;
	}

	void Set(Vector3D thePos)
	{
		m_x = thePos.m_x;
		m_y = thePos.m_y;
		m_z = thePos.m_z;
	}


	//calculate and return the magnitude of this vector
	float GetMagnitude()
	{
		return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
	}

	float GetMagnitudeSquare()
	{
		return (m_x * m_x + m_y * m_y + m_z * m_z);
	}

	//multiply this vector by a scalar
	Vector3D operator*(float num) const
	{
		return Vector3D(m_x * num, m_y * num, m_z * num);
	}

	Vector3D operator*=(float num)
	{
		Set(m_x * num, m_y * num, m_z * num);
		return *this;
	}

	//pass in a vector, pass in a scalar, return the product
	friend Vector3D operator*(float num, Vector3D const &vec)
	{
		return Vector3D(vec.m_x * num, vec.m_y * num, vec.m_z * num);
	}

	//add two vectors
	Vector3D operator+(const Vector3D &vec) const
	{
		return Vector3D(m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z);
	}

	Vector3D operator+=(const Vector3D &vec)
	{
		Set(m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z);
		return *this;
	}

	//subtract two vectors
	Vector3D operator-(const Vector3D &vec) const
	{
		return Vector3D(m_x - vec.m_x, m_y - vec.m_y, m_z - vec.m_z);
	}

	Vector3D operator-=(const Vector3D &vec)
	{
		Set(m_x - vec.m_x, m_y - vec.m_y, m_z - vec.m_z);
		return *this;
	}

	bool operator !=(const Vector3D &vec) const
	{
		if (this->m_x != vec.m_x)
		{
			return true;
		}
		if (this->m_y != vec.m_y)
		{
			return true;
		}				
		if (this->m_z != vec.m_z)
		{
			return true;
		}
		else
			return false;

	}

	bool operator ==(const Vector3D &vec) const
	{
		if (this->m_x == vec.m_x)
		{
			if (this->m_y == vec.m_y)
			{
				if (this->m_z == vec.m_z)
				{
					return true;
				}
			}
		}
		else
			return false;
	}
	//normalize this vector
	void NormalizeVector3D()
	{
		float magnitude = sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
		m_x /= magnitude;
		m_y /= magnitude;
		m_z /= magnitude;
	}
	
	Vector3D NormalizedVector3D()
	{
		float magnitude = sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
		float x = m_x / magnitude;
		float y = m_y / magnitude;
		float z = m_z / magnitude;
		return Vector3D(x,y,z);
	}

	//calculate and return dot product
	float DotVector3D(const Vector3D &vec) const
	{
		return m_x * vec.m_x + m_y * vec.m_y + m_z * vec.m_z;
	}

	//calculate and return cross product
	Vector3D CrossVector3D(const Vector3D &vec) const
	{
		return Vector3D(m_y * vec.m_z - m_z * vec.m_y,
				m_z * vec.m_x - m_x * vec.m_z,
				m_x * vec.m_y - m_y * vec.m_x);
	}

	Vector3D operator*(const Matrix4x4 &m) const
	{
		return Vector3D(m_x*m.matrix[0] + m_y*m.matrix[4] + m_z*m.matrix[8] + 1 * m.matrix[12],
			m_x*m.matrix[1] + m_y*m.matrix[5] + m_z*m.matrix[9] + 1 * m.matrix[13],
			m_x*m.matrix[2] + m_y*m.matrix[6] + m_z*m.matrix[10] + 1 * m.matrix[14]);
	}
};

#endif