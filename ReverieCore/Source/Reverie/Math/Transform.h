#pragma once
#include "Common.h"
#include "Vector.h"
#include "Quaternion.h"
#include "Matrix3.h"

namespace Reverie::Math
{
	class OrthogonalTransform
	{
	public:
		INLINE OrthogonalTransform() :m_Rotation(kIdentity), m_Translation(kZero){}
		INLINE OrthogonalTransform(Quaternion rotate, Vector3 translation) : m_Rotation(rotate), m_Translation(translation) {}
		INLINE OrthogonalTransform(const Matrix3& rotation, Vector3 translation) : m_Rotation(XMQuaternionRotationMatrix(rotation)), m_Translation(translation){}

		INLINE explicit OrthogonalTransform(Quaternion rotate) : m_Rotation(rotate), m_Translation(kZero) {}
		INLINE explicit OrthogonalTransform(Vector3 translation) : m_Rotation(kIdentity), m_Translation(translation) {}
		INLINE explicit OrthogonalTransform(const Matrix3& rotation) : m_Rotation(XMQuaternionRotationMatrix(rotation)), m_Translation(kZero) {}
		INLINE explicit OrthogonalTransform(IdentityTag) : m_Rotation(kIdentity), m_Translation(kZero){}
		INLINE explicit OrthogonalTransform(FXMMATRIX mat): OrthogonalTransform(Matrix3(mat), Vector3(mat.r[3])){}

		INLINE void SetRotation(Quaternion q) { m_Rotation = q; }
		INLINE void SetTranslation(Vector3 t) { m_Translation = t; }

		INLINE Quaternion GetRotation() const { return m_Rotation; }
		INLINE Vector3 GetTranslation() const { return m_Translation; }

		static INLINE OrthogonalTransform MakeXRotation(float angle) { return OrthogonalTransform(Quaternion(Vector3(kXUnitVector), angle)); }
		static INLINE OrthogonalTransform MakeYRotation(float angle) { return OrthogonalTransform(Quaternion(Vector3(kYUnitVector), angle));}
		static INLINE OrthogonalTransform MakeZRotation(float angle) { return OrthogonalTransform(Quaternion(Vector3(kZUnitVector), angle)); }
		static INLINE OrthogonalTransform MakeTranslation(Vector3 t) { return OrthogonalTransform(t); }

		INLINE OrthogonalTransform operator*(const OrthogonalTransform& t) const
		{
			return OrthogonalTransform(m_Rotation * t.GetRotation(), m_Translation * t.GetRotation() + t.GetTranslation());
		}
		INLINE OrthogonalTransform operator~() const
		{
			return OrthogonalTransform(~m_Rotation, -m_Translation * ~m_Rotation);
		}
		INLINE OrthogonalTransform operator*=(const OrthogonalTransform& t)
		{
			*this = OrthogonalTransform(m_Rotation * t.GetRotation(), m_Translation * t.GetRotation() + t.GetTranslation());
			return *this;
		}
		
	private:
		Quaternion m_Rotation;
		Vector3 m_Translation;
	};

	class ScaleAndTranslation
	{
	public:
		INLINE ScaleAndTranslation() {}
		INLINE ScaleAndTranslation(float tx, float ty, float tz, float scale) : m_Repr(tx, ty, tz, scale) {}
		INLINE ScaleAndTranslation(Vector3 translation, Scalar scale) : m_Repr(translation, scale) {}

		INLINE explicit ScaleAndTranslation(IdentityTag) : m_Repr(kWUnitVector) {}
		INLINE explicit ScaleAndTranslation(FXMVECTOR t) : m_Repr(t) {}

		INLINE void SetScale(Scalar scale) { m_Repr.SetW(scale); }
		INLINE void SetTranslation(Vector3 translation) { m_Repr.SetXYZ(translation); }

		INLINE Scalar GetScale() const { return m_Repr.GetW(); }
		INLINE Vector3 GetTranslation() const { return Vector3(m_Repr); }
	private:
		Vector4 m_Repr;
	};

	class UniformTransform
	{
	public:
		INLINE UniformTransform(){}
		INLINE UniformTransform(Quaternion rotation, const ScaleAndTranslation& scaleTranslation): m_Rotation(rotation), m_ScaleTranslation(scaleTranslation){}
		INLINE UniformTransform(Quaternion rotation, Scalar scale, Vector3 translation) : m_Rotation(rotation), m_ScaleTranslation(translation, scale) {}

		INLINE explicit UniformTransform(IdentityTag):m_Rotation(kIdentity), m_ScaleTranslation(kIdentity){}
		

		INLINE void SetRotation(Quaternion rotation) { m_Rotation = rotation; }
		INLINE void SetScale(Scalar scale) { m_ScaleTranslation.SetScale(scale); }
		INLINE void SetTranslation(Vector3 translation) { m_ScaleTranslation.SetTranslation(translation); }
		
		INLINE Quaternion GetRotation() const { return m_Rotation; }
		INLINE Scalar GetScale() const { return m_ScaleTranslation.GetScale(); }
		INLINE Vector3 GetTranslation() const { return m_ScaleTranslation.GetTranslation(); }

	private:
		Quaternion m_Rotation;
		ScaleAndTranslation m_ScaleTranslation;
	};

	class AffineTransform
	{
	public:
		INLINE AffineTransform() {}
		INLINE AffineTransform(Vector3 x, Vector3 y, Vector3 z, Vector3 w) :m_Basis(x, y, z), m_Translation(w) {}
		INLINE AffineTransform(const Matrix3& mat, Vector3 translation = Vector3(kZero)) : m_Basis(mat), m_Translation(translation) {}
		INLINE AffineTransform(Quaternion rotation, Vector3 translation = Vector3(kZero)) : m_Basis(rotation), m_Translation(translation) {}

		INLINE explicit AffineTransform(const OrthogonalTransform& t) : m_Basis(t.GetRotation()), m_Translation(t.GetTranslation()) {}
		INLINE explicit AffineTransform(const UniformTransform& t)
		{
			m_Translation = t.GetTranslation();
			m_Basis = t.GetScale() * Matrix3(t.GetRotation());
		}
		INLINE explicit AffineTransform(IdentityTag): m_Translation(kZero), m_Basis(kIdentity){}
		INLINE explicit AffineTransform(FXMMATRIX mat): m_Basis(mat), m_Translation(mat.r[3]){}

		INLINE operator XMMATRIX() { return (XMMATRIX&)*this; }

		INLINE void SetX(Vector3 x) { m_Basis.SetX(x); }
		INLINE void SetY(Vector3 y) { m_Basis.SetY(y); }
		INLINE void SetZ(Vector3 z) { m_Basis.SetZ(z); }
		INLINE void SetTranslation(Vector3 translation) { m_Translation = translation; }
		INLINE void SetBasis(const Matrix3& basis) { m_Basis = basis; }

		INLINE Vector3 GetX() const { return m_Basis.GetX(); }
		INLINE Vector3 GetY() const { return m_Basis.GetY(); }
		INLINE Vector3 GetZ() const { return m_Basis.GetZ(); }
		INLINE Vector3 GetTranslation() const { return m_Translation; }
		INLINE const Matrix3& GetBasis() const { return (const Matrix3&)*this; }

		static INLINE AffineTransform MakeXRotation(float angle) { return { Matrix3::MakeXRotation(angle) }; }
		static INLINE AffineTransform MakeYRotation(float angle) { return { Matrix3::MakeYRotation(angle) }; }
		static INLINE AffineTransform MakeZRotation(float angle) { return {Matrix3::MakeZRotation(angle)}; }
		static INLINE AffineTransform MakeScale(float scale) { return { Matrix3::MakeScale(scale) }; }
		static INLINE AffineTransform MakeScale(Vector3 scale) { return { Matrix3::MakeScale(scale) }; }
		static INLINE AffineTransform MakeTranslation(Vector3 translate) { return { Quaternion(kIdentity), translate }; }

		INLINE AffineTransform operator*(const AffineTransform& t) const
		{
			return {m_Basis * t.GetBasis(), m_Translation * t};
		}
		INLINE AffineTransform operator*=(const AffineTransform& t)
		{
			*this = AffineTransform(m_Basis * t.GetBasis(), m_Translation * t);
			return *this;
		}


	private:
		Matrix3 m_Basis;
		Vector3 m_Translation;
	};

	

	//Implementation of Vector function that require the full definition of Transform
	INLINE Vector3 Vector3::operator*(const OrthogonalTransform& t) const
	{
		return *this * t.GetRotation() + t.GetTranslation();
	}
	INLINE Vector3 Vector3::operator*=(const OrthogonalTransform& t)
	{
		*this = *this * t.GetRotation() + t.GetTranslation();
		return *this;
	}
	INLINE Vector3 Vector3::operator*(const UniformTransform& t) const
	{
		return *this * t.GetScale() * t.GetRotation() + t.GetTranslation();
	}
	INLINE Vector3 Vector3::operator*=(const UniformTransform& t)
	{
		*this = *this * t.GetScale() * t.GetRotation() + t.GetTranslation();
		return *this;
	}
	INLINE Vector3 Vector3::operator*(const AffineTransform& t) const
	{
		return *this * t.GetBasis() + t.GetTranslation();
	}
	INLINE Vector3 Vector3::operator*=(const AffineTransform& t)
	{
		*this = *this * t.GetBasis() + t.GetTranslation();
		return *this;
	}
	INLINE Vector4 Vector4::operator*(const OrthogonalTransform& t) const
	{
		return Vector4(XMVectorPermute<0, 1, 2, 7>(Vector3(*this) * t.GetRotation(), XMVectorZero())) 
		+ Vector4(XMVectorPermute<0, 1, 2, 7>(t.GetTranslation(), XMVectorSplatOne()) * this->GetW());
	}
	INLINE Vector4 Vector4::operator*=(const OrthogonalTransform& t)
	{
		*this = Vector4(XMVectorPermute<0, 1, 2, 7>(Vector3(*this) * t.GetRotation(), XMVectorZero()))
			+ Vector4(XMVectorPermute<0, 1, 2, 7>(t.GetTranslation(), XMVectorSplatOne()) * (float)this->GetW());
		return *this;
	}
}
