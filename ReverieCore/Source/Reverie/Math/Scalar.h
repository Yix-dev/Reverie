#pragma once
#include "Common.h"
namespace Reverie::Math
{
	class Scalar
	{
	public:
		INLINE Scalar():m_Vector() {}
		INLINE Scalar(const Scalar& s): m_Vector(s) {}
		INLINE Scalar(float s) : m_Vector(XMVectorReplicate(s)) {}

		INLINE explicit Scalar(FXMVECTOR s): m_Vector(s){}
		INLINE explicit Scalar(ZeroTag) : m_Vector(XMVectorZero()) {}
		INLINE explicit Scalar(IdentityTag) : m_Vector(XMVectorSplatOne()) {}

		INLINE operator float() const
		{
			return XMVectorGetX(m_Vector);
		}
		INLINE operator XMVECTOR() const
		{
			return m_Vector;
		}

		INLINE Scalar operator- () { return Scalar(XMVectorNegate(m_Vector)); }
		INLINE Scalar operator+ (Scalar s) { return Scalar(XMVectorAdd(m_Vector, s)); }
		INLINE Scalar operator- (Scalar s) { return Scalar(XMVectorSubtract(m_Vector, s)); }
		INLINE Scalar operator* (Scalar s) { return Scalar(XMVectorMultiply(m_Vector, s)); }
		INLINE Scalar operator/ (Scalar s) { return Scalar(XMVectorDivide(m_Vector, s)); }
		INLINE Scalar operator+ (float s) { return *this + Scalar(s); }
		INLINE Scalar operator- (float s) { return *this - Scalar(s); }
		INLINE Scalar operator* (float s) { return *this * Scalar(s); }
		INLINE Scalar operator/ (float s) { return *this / Scalar(s); }
		friend INLINE Scalar operator+ (float s1, Scalar s2) { return Scalar(s1) + s2; }
		friend INLINE Scalar operator- (float s1, Scalar s2) { return Scalar(s1) - s2; }
		friend INLINE Scalar operator* (float s1, Scalar s2) { return Scalar(s1) * s2; }
		friend INLINE Scalar operator/ (float s1, Scalar s2) { return Scalar(s1) / s2; }

	private:
		XMVECTOR m_Vector;
	};
}