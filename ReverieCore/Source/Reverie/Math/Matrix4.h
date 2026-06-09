#pragma once
#include "Common.h"
#include "Vector.h"
#include "Matrix3.h"

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

		INLINE explicit Matrix4(const XMMATRIX& mat) : m_Matrix(mat) {}
		INLINE explicit Matrix4(IdentityTag) : m_Matrix(XMMatrixIdentity()) {}
		INLINE explicit Matrix4(ZeroTag)
		{
			m_Matrix.r[0] = m_Matrix.r[1] = m_Matrix.r[2] = m_Matrix.r[3] = XMVectorZero();
		}
	private:
		XMMATRIX m_Matrix;
	};
}
