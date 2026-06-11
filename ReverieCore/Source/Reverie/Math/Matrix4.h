#pragma once
#include "Common.h"
#include "Vector.h"
#include "Matrix3.h"
#include "Transform.h"

namespace Reverie::Math
{
	__declspec(align(16)) class Matrix4
	{
	public:
		INLINE Matrix4() :m_Matrix() {}
		INLINE Matrix4(Vector3 x, Vector3 y, Vector3 z, Vector3 w)
		{
			m_Matrix.r[0] = XMVectorPermute<0, 1, 2, 7>(x, XMVectorZero());
			m_Matrix.r[1] = XMVectorPermute<0, 1, 2, 7>(y, XMVectorZero());
			m_Matrix.r[2] = XMVectorPermute<0, 1, 2, 7>(z, XMVectorZero());
			m_Matrix.r[3] = XMVectorPermute<0, 1, 2, 7>(w, XMVectorSplatOne());
		}
		INLINE Matrix4(Vector4 x, Vector4 y, Vector4 z, Vector4 w)
		{
			m_Matrix.r[0] = x;
			m_Matrix.r[1] = y;
			m_Matrix.r[2] = z;
			m_Matrix.r[3] = w;
		}
		INLINE Matrix4(const float* data)
		{
			m_Matrix = XMLoadFloat4x4((XMFLOAT4X4*)data);
		}
		INLINE Matrix4(const Matrix4& mat) : m_Matrix(mat.m_Matrix) {}
		INLINE Matrix4(const Matrix3& mat)
		{
			m_Matrix.r[0] = XMVectorPermute<0, 1, 2, 7>(mat.GetX(), XMVectorZero());
			m_Matrix.r[1] = XMVectorPermute<0, 1, 2, 7>(mat.GetY(), XMVectorZero());
			m_Matrix.r[2] = XMVectorPermute<0, 1, 2, 7>(mat.GetZ(), XMVectorZero());
			m_Matrix.r[3] = XMVectorPermute<0, 1, 2, 7>(XMVectorZero(), XMVectorSplatOne());
		}
		INLINE Matrix4(const Matrix3& xyz, Vector3 w)
		{
			m_Matrix.r[0] = XMVectorPermute<0, 1, 2, 7>(xyz.GetX(), XMVectorZero());
			m_Matrix.r[1] = XMVectorPermute<0, 1, 2, 7>(xyz.GetY(), XMVectorZero());
			m_Matrix.r[2] = XMVectorPermute<0, 1, 2, 7>(xyz.GetZ(), XMVectorZero());
			m_Matrix.r[3] = XMVectorPermute<0, 1, 2, 7>(w, XMVectorSplatOne());
		}

		INLINE explicit Matrix4(const AffineTransform& t) : Matrix4(t.GetBasis(), t.GetTranslation()){}
		INLINE explicit Matrix4(const OrthogonalTransform& t) : Matrix4(Matrix3(t.GetRotation()), t.GetTranslation()){}
		INLINE explicit Matrix4(const XMMATRIX& mat) : m_Matrix(mat) {}
		INLINE explicit Matrix4(IdentityTag) : m_Matrix(XMMatrixIdentity()) {}
		INLINE explicit Matrix4(ZeroTag)
		{
			m_Matrix.r[0] = m_Matrix.r[1] = m_Matrix.r[2] = m_Matrix.r[3] = XMVectorZero();
		}

		INLINE const Matrix3& Get3x3() const { return (const Matrix3&)*this; }
		INLINE void Set3x3(const Matrix3& xyz)
		{
			m_Matrix.r[0] = XMVectorPermute<0, 1, 2, 7>(xyz.GetX(), XMVectorZero());
			m_Matrix.r[1] = XMVectorPermute<0, 1, 2, 7>(xyz.GetY(), XMVectorZero());
			m_Matrix.r[2] = XMVectorPermute<0, 1, 2, 7>(xyz.GetZ(), XMVectorZero());
		}

		INLINE Vector4 GetX() const { return Vector4(m_Matrix.r[0]); }
		INLINE Vector4 GetY() const { return Vector4(m_Matrix.r[1]); }
		INLINE Vector4 GetZ() const { return Vector4(m_Matrix.r[2]); }
		INLINE Vector4 GetW() const { return Vector4(m_Matrix.r[3]); }

		INLINE void SetX(Vector4 x) { m_Matrix.r[0] = x; }
		INLINE void SetY(Vector4 y) { m_Matrix.r[1] = y; }
		INLINE void SetZ(Vector4 z) { m_Matrix.r[2] = z; }
		INLINE void SetW(Vector4 w) { m_Matrix.r[3] = w; }

		INLINE operator XMMATRIX() const { return m_Matrix; }
		INLINE Matrix4 operator*(const Matrix4& rhs) const { return Matrix4(XMMatrixMultiply(m_Matrix, rhs)); }
		INLINE Matrix4 operator*=(const Matrix4& rhs) { *this = Matrix4(XMMatrixMultiply(m_Matrix, rhs)); return *this; }

		static INLINE Matrix4 MakeScale(float scale) { return Matrix4(XMMatrixScaling(scale, scale, scale)); }
		static INLINE Matrix4 MakeScale(Vector3 scale) { return Matrix4(XMMatrixScaling(scale.GetX(), scale.GetY(), scale.GetZ())); }
	private:
		XMMATRIX m_Matrix;
	};

	INLINE Vector4 Vector3::operator* (const Matrix4& mat) const
	{
		return Vector4(XMVector4Transform(*this, mat));
	}
	INLINE Vector3 Vector3::operator*=(const Matrix4& mat)
	{
		*this = Vector3(XMVector4Transform(*this, mat));
		return *this;
	}
	INLINE Vector4 Vector4::operator* (const Matrix4& mat) const
	{
		return Vector4(XMVector4Transform(*this, mat));
	}
	INLINE Vector4 Vector4::operator*=(const Matrix4& mat)
	{
		*this = Vector4(XMVector4Transform(*this, mat));
		return *this;
	}
}
