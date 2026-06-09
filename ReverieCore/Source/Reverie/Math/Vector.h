#pragma once
#include "Common.h"
#include "Scalar.h"
namespace Reverie::Math
{
	class Matrix3;
	class Vector4;
	class Vector3
	{
	public:
		INLINE Vector3() :m_Vector() {}
		INLINE Vector3(float x, float y, float z) : m_Vector(XMVectorSet(x, y, z, z)) {}
		INLINE Vector3(const XMFLOAT3& vec) : m_Vector(XMLoadFloat3(&vec)) {}
		INLINE Vector3(const Vector3& vec) : m_Vector(vec) {}
		INLINE Vector3(Scalar vec) : m_Vector(vec) {}

		INLINE explicit Vector3(Vector4 vec);
		INLINE explicit Vector3(FXMVECTOR vec) : m_Vector(vec) {}
		INLINE explicit Vector3(IdentityTag) : m_Vector(XMVectorSplatOne()) {}
		INLINE explicit Vector3(ZeroTag) : m_Vector(XMVectorZero()) {}
		INLINE explicit Vector3(XUnitVector) : m_Vector(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)) {}
		INLINE explicit Vector3(YUnitVector) : m_Vector(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)) {}
		INLINE explicit Vector3(ZUnitVector) : m_Vector(XMVectorSet(1.0f, 0.0f, 1.0f, 0.0f)) {}

		INLINE operator XMVECTOR() const
		{
			return m_Vector;
		}

		INLINE Scalar GetX() const
		{
			return Scalar(XMVectorSplatX(m_Vector));
		}
		INLINE Scalar GetY() const
		{
			return Scalar(XMVectorSplatY(m_Vector));
		}
		INLINE Scalar GetZ() const
		{
			return Scalar(XMVectorSplatZ(m_Vector));
		}
		INLINE void SetX(Scalar x)
		{
			m_Vector = XMVectorPermute<4, 1, 2, 3>(m_Vector, x);
		}
		INLINE void SetY(Scalar y)
		{
			m_Vector = XMVectorPermute<0, 5, 2, 3>(m_Vector, y);
		}
		INLINE void SetZ(Scalar z)
		{
			m_Vector = XMVectorPermute<0, 1, 6, 3>(m_Vector, z);
		}

		INLINE Vector3 operator-() const { return Vector3(XMVectorNegate(m_Vector)); }
		INLINE Vector3 operator+(Vector3 vec) const { return Vector3(XMVectorAdd(m_Vector, vec)); }
		INLINE Vector3 operator-(Vector3 vec) const { return Vector3(XMVectorSubtract(m_Vector, vec)); }
		INLINE Vector3 operator*(Vector3 vec) const { return Vector3(XMVectorMultiply(m_Vector, vec)); }
		INLINE Vector3 operator/(Vector3 vec) const { return Vector3(XMVectorMultiply(m_Vector, vec)); }
		INLINE Vector3 operator*(Scalar s) const { return *this * Vector3(s); }
		INLINE Vector3 operator/(Scalar s) const { return *this / Vector3(s); }
		INLINE Vector3 operator*(float f) const { return *this * Scalar(f); }
		INLINE Vector3 operator/(float f) const { return *this / Scalar(f); }
		INLINE Vector3 operator*(const Matrix3& mat) const;

		INLINE Vector3 operator+=(Vector3 vec) { *this = *this + vec; return *this; }
		INLINE Vector3 operator-=(Vector3 vec) { *this = *this - vec; return *this; }
		INLINE Vector3 operator*=(Vector3 vec) { *this = *this * vec; return *this; }
		INLINE Vector3 operator*=(const Matrix3& mat);
		INLINE Vector3 operator/=(Vector3 vec) { *this = *this / vec; return *this; }

		INLINE friend Vector3 operator*(Scalar s, Vector3 vec)
		{
			return Vector3(s) * vec;
		}
		INLINE friend Vector3 operator/(Scalar s, Vector3 vec)
		{
			return Vector3(s) / vec;
		}
		INLINE friend Vector3 operator*(float f, Vector3 vec)
		{
			return Scalar(f) * vec;
		}
		INLINE friend Vector3 operator/(float f, Vector3 vec)
		{
			return Scalar(f) * vec;
		}

	private:
		XMVECTOR m_Vector;
	};
	class Vector4
	{
	public:
		INLINE Vector4() :m_Vector() {}
		INLINE Vector4(float x, float y, float z, float w) : m_Vector(XMVectorSet(x, y, z, w)) {}
		INLINE Vector4(const XMFLOAT4& vec) : m_Vector(XMLoadFloat4(&vec)) {}
		INLINE Vector4(const Vector4& vec) : m_Vector(vec) {}
		INLINE Vector4(Vector3 xyz, float w): m_Vector(XMVectorPermute<0,1,2,7>(xyz, XMVectorReplicate(w))){}
		INLINE Vector4(Scalar vec) : m_Vector(vec) {}

		INLINE explicit Vector4(Vector3 xyz) : m_Vector(XMVectorPermute<0,1,2,7>(xyz, XMVectorSplatOne())) {}
		INLINE explicit Vector4(FXMVECTOR vec) : m_Vector(vec) {}
		INLINE explicit Vector4(IdentityTag) : m_Vector(XMVectorSplatOne()) {}
		INLINE explicit Vector4(ZeroTag) : m_Vector(XMVectorZero()) {}
		INLINE explicit Vector4(XUnitVector) : m_Vector(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)) {}
		INLINE explicit Vector4(YUnitVector) : m_Vector(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)) {}
		INLINE explicit Vector4(ZUnitVector) : m_Vector(XMVectorSet(1.0f, 0.0f, 1.0f, 0.0f)) {}
		INLINE explicit Vector4(WUnitVector) : m_Vector(XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f)) {}

		INLINE operator XMVECTOR() const
		{
			return m_Vector;
		}

		INLINE Scalar GetX() const
		{
			return Scalar(XMVectorSplatX(m_Vector));
		}
		INLINE Scalar GetY() const
		{
			return Scalar(XMVectorSplatY(m_Vector));
		}
		INLINE Scalar GetZ() const
		{
			return Scalar(XMVectorSplatZ(m_Vector));
		}
		INLINE Scalar GetW() const
		{
			return Scalar(XMVectorSplatW(m_Vector));
		}
		INLINE void SetX(Scalar x)
		{
			m_Vector = XMVectorPermute<4, 1, 2, 3>(m_Vector, x);
		}
		INLINE void SetY(Scalar y)
		{
			m_Vector = XMVectorPermute<0, 5, 2, 3>(m_Vector, y);
		}
		INLINE void SetZ(Scalar z)
		{
			m_Vector = XMVectorPermute<0, 1, 6, 3>(m_Vector, z);
		}
		INLINE void SetW(Scalar w)
		{
			m_Vector = XMVectorPermute<0, 1, 2, 7>(m_Vector, w);
		}
		INLINE void SetXYZ(Vector3 xyz)
		{
			m_Vector = XMVectorPermute<0, 1, 2, 7>(xyz, m_Vector);
		}

		INLINE Vector4 operator-() const { return Vector4(XMVectorNegate(m_Vector)); }
		INLINE Vector4 operator+(Vector4 vec) const { return Vector4(XMVectorAdd(m_Vector, vec)); }
		INLINE Vector4 operator-(Vector4 vec) const { return Vector4(XMVectorSubtract(m_Vector, vec)); }
		INLINE Vector4 operator*(Vector4 vec) const { return Vector4(XMVectorMultiply(m_Vector, vec)); }
		INLINE Vector4 operator/(Vector4 vec) const { return Vector4(XMVectorMultiply(m_Vector, vec)); }
		INLINE Vector4 operator*(Scalar s) const { return *this * Vector4(s); }
		INLINE Vector4 operator/(Scalar s) const { return *this / Vector4(s); }
		INLINE Vector4 operator*(float f) const { return *this * Scalar(f); }
		INLINE Vector4 operator/(float f) const { return *this / Scalar(f); }

		INLINE Vector4 operator*=(Vector4 vec) { *this = *this * vec; return *this; }
		INLINE Vector4 operator/=(Vector4 vec) { *this = *this / vec; return *this; }

		INLINE friend Vector4 operator*(Scalar s, Vector4 vec)
		{
			return Vector4(s) * vec;
		}
		INLINE friend Vector4 operator/(Scalar s, Vector4 vec)
		{
			return Vector4(s) / vec;
		}
		INLINE friend Vector4 operator*(float f, Vector4 vec)
		{
			return Scalar(f) * vec;
		}
		INLINE friend Vector4 operator/(float f, Vector4 vec)
		{
			return Scalar(f) * vec;
		}

	private:
		XMVECTOR m_Vector;
	};

	INLINE Vector3::Vector3(Vector4 vec) : m_Vector(vec){}

	INLINE Vector3 MakeHomogeneous(Vector4 vec)
	{
		Scalar w = vec.GetW();
		return Vector3(XMVectorSelect(vec / w, vec, XMVectorEqual(w, XMVectorZero())));
	}

	class BoolVector
	{
	public:
		INLINE BoolVector(FXMVECTOR vec) { m_Vector = vec; }
		INLINE operator XMVECTOR() const { return m_Vector; }
	protected:
		XMVECTOR m_Vector;
	};
}
