#pragma once
#include "Vector.h"

namespace Reverie::Math
{
	class BoundingSphere
	{
	public:
		BoundingSphere(){}
		BoundingSphere(float x, float y, float z, float radius) : m_Repr(x, y, z, radius){}
		BoundingSphere(Vector3 center, Scalar radius) : m_Repr(center, radius) {}
		BoundingSphere(const XMFLOAT4* unaligned_array) : m_Repr(*unaligned_array){}

		explicit BoundingSphere(ZeroTag) : m_Repr(kZero){}
		explicit BoundingSphere(FXMVECTOR vec) : m_Repr(vec){}
		explicit BoundingSphere(const XMFLOAT4& f4) : m_Repr(f4){}
		explicit BoundingSphere(Vector4 vec) : m_Repr(vec){}

		explicit operator Vector3() const { return Vector3(m_Repr); }

		Vector3 GetCenter() const { return Vector3(m_Repr); }
		Scalar GetRadius() const { return m_Repr.GetW(); }
		
		BoundingSphere Union(const BoundingSphere& rhs)
		{
			float radA = GetRadius();
			if (radA == 0.0f)
				return rhs;
			float radB = rhs.GetRadius();
			if (radB == 0.0f)
				return *this;

			Vector3 diff =  GetCenter() - rhs.GetCenter();
			
		}

	private:
		Vector4 m_Repr;
	};

}
