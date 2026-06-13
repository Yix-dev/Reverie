#pragma once
#include "Common.h"
#include "Quaternion.h"
#include "Vector.h"

namespace Reverie::Math
{
	__declspec(align(16)) class Matrix3
	{
	public:
		INLINE Matrix3() {}
		INLINE Matrix3(Vector3 x, Vector3 y, Vector3 z) : m_Matrix{ x, y, z } {}
		INLINE Matrix3(const Matrix3& mat) : m_Matrix{ mat.m_Matrix[0], mat.m_Matrix[1], mat.m_Matrix[2] } {}

		INLINE explicit Matrix3(Quaternion q):Matrix3(XMMatrixRotationQuaternion(q)){}
		INLINE explicit Matrix3(FXMMATRIX mat) : m_Matrix{Vector3(mat.r[0]), Vector3(mat.r[1]), Vector3(mat.r[2])} {}
		INLINE explicit Matrix3(IdentityTag) : m_Matrix{Vector3(kXUnitVector), Vector3(kYUnitVector), Vector3(kZUnitVector) }{}
		INLINE explicit Matrix3(ZeroTag) : m_Matrix{Vector3(kZero), Vector3(kZero), Vector3(kZero) }{}

		INLINE void SetX(Vector3 x)
		{
			m_Matrix[0] = x;
		}
		INLINE void SetY(Vector3 y)
		{
			m_Matrix[1] = y;
		}
		INLINE void SetZ(Vector3 z)
		{
			m_Matrix[2] = z;
		}

		INLINE Vector3 GetX() const
		{
			return m_Matrix[0];
		}
		INLINE Vector3 GetY() const
		{
			return m_Matrix[1];
		}
		INLINE Vector3 GetZ() const
		{
			return m_Matrix[2];
		}

		static Matrix3 MakeXRotation(float angle)
		{
			return Matrix3(XMMatrixRotationX(angle));
		}
		static Matrix3 MakeYRotation(float angle)
		{
			return Matrix3(XMMatrixRotationY(angle));
		}
		static Matrix3 MakeZRotation(float angle)
		{
			return Matrix3(XMMatrixRotationZ(angle));
		}
		static Matrix3 MakeScale(float scale)
		{
			return Matrix3(XMMatrixScaling(scale, scale, scale));
		}
		static Matrix3 MakeScale(float sx, float sy, float sz)
		{
			return Matrix3(XMMatrixScaling(sx, sy, sz));
		}
		static Matrix3 MakeScale(XMFLOAT3 scale)
		{
			return Matrix3(XMMatrixScaling(scale.x, scale.y, scale.z));
		}
		static Matrix3 MakeScale(Vector3 scale)
		{
			return Matrix3(XMMatrixScalingFromVector(scale));
		}

		INLINE operator XMMATRIX() const
		{
			return XMMATRIX(m_Matrix[0], m_Matrix[1], m_Matrix[2], XMVectorZero());
		}
		INLINE Matrix3 operator*(Scalar s) const
		{
			return Matrix3(m_Matrix[0] * s, m_Matrix[1] * s, m_Matrix[2] * s);
		}
		INLINE Matrix3 operator*(const Matrix3& mat) const
		{
			return Matrix3(m_Matrix[0] * mat, m_Matrix[1] * mat, m_Matrix[2] * mat);
		}
		INLINE Matrix3 operator*=(const Matrix3& mat)
		{
			*this = *this * mat;
			return *this;
		}
		friend INLINE Matrix3 operator*(Scalar s, const Matrix3& mat)
		{
			return mat * s;
		}

	private:
		Vector3 m_Matrix[3];
	};

	//Implementation of Vector functions that require the full definition of Matrix3
	INLINE Vector3 Vector3::operator*(const Matrix3& mat) const { return Vector3(XMVector3TransformNormal(m_Vector, mat)); }
	INLINE Vector3 Vector3::operator*=(const Matrix3& mat) { *this = *this * mat; return *this; }

}
