#pragma once
#include "Common.h"
#include "Vector.h"

namespace Reverie::Math
{
	class Quaternion
	{
	public:
		INLINE Quaternion(): m_Vector(){}
		INLINE Quaternion(Vector3 axis, Scalar angle) : m_Vector(XMQuaternionRotationAxis(axis, angle)){}
		INLINE Quaternion(float pitch, float yaw, float roll) :m_Vector(XMQuaternionRotationRollPitchYaw(pitch, yaw, roll)){}
		
		INLINE explicit Quaternion(const XMMATRIX& mat) : m_Vector(XMQuaternionRotationMatrix(mat)){}
		INLINE explicit Quaternion(FXMVECTOR vec): m_Vector(vec){}
		INLINE explicit Quaternion(IdentityTag): m_Vector(XMQuaternionIdentity()){}

		INLINE operator XMVECTOR() const { return m_Vector; }

		INLINE Quaternion operator~() const { return Quaternion(XMQuaternionConjugate(m_Vector)); }
		INLINE Quaternion operator-() const { return Quaternion(XMVectorNegate(m_Vector)); }

		INLINE Quaternion operator*(Quaternion rhs) const { return Quaternion(XMQuaternionMultiply(m_Vector, rhs)); }
		INLINE Vector3 operator*(Vector3 rhs) const { return Vector3(XMVector3Rotate(rhs, m_Vector)); }

		INLINE Quaternion& operator=(Quaternion rhs) { m_Vector = rhs; return *this; }
		INLINE Quaternion& operator*=(Quaternion rhs) { *this = *this * rhs; return *this; }

	private:
		XMVECTOR m_Vector;

	};

	INLINE Quaternion Normalize(Quaternion q) { return Quaternion(XMQuaternionNormalize(q)); }
	INLINE Quaternion Slerp(Quaternion a, Quaternion b, float t) { return Normalize(Quaternion(XMQuaternionSlerp(a, b, t))); }
	INLINE Quaternion Lerp(Quaternion a, Quaternion b, float t) { return Normalize(Quaternion(XMVectorLerp(a, b, t))); }
}
