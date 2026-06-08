#pragma once
#include "Common.h"
#include "Vector.h"

namespace Reverie::Math
{
	__declspec(align(16)) class Matrix3
	{
	public:
		INLINE Matrix3() {}
		INLINE Matrix3(Vector3 x, Vector3 y, Vector3 z) : m_Matrix{ x, y, z } {}
		INLINE Matrix3(const Matrix3& m) : m_Matrix{ m.m_Matrix[0], m.m_Matrix[1], m.m_Matrix[2] } {}

	private:
		Vector3 m_Matrix[3];
	};
}
