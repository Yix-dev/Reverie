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
		INLINE OrthogonalTransform(Quaternion rotate): m_Rotation(rotate), m_Translation(kZero){}
		INLINE OrthogonalTransform(Vector3 translation) : m_Rotation(kIdentity), m_Translation(translation) {}
		INLINE OrthogonalTransform(Quaternion rotate, Vector3 translation) : m_Rotation(rotate), m_Translation(translation) {}
		INLINE OrthogonalTransform(const Matrix3& rotation) : m_Rotation(XMQuaternionRotationMatrix(rotation)), m_Translation(kZero) {}
		INLINE OrthogonalTransform(const Matrix3& rotation, Vector3 translation) : m_Rotation(XMQuaternionRotationMatrix(rotation)), m_Translation(translation){}

		INLINE explicit OrthogonalTransform(IdentityTag) : m_Rotation(kIdentity), m_Translation(kZero){}
		INLINE explicit OrthogonalTransform(const XMMATRIX& mat): OrthogonalTransform(Matrix3(mat), Vector3(mat.r[3])){}
	private:
		Quaternion m_Rotation;
		Vector3 m_Translation;
	};
	class AffineTransform;
	class ScaleAndTranslation;
	class UniformTransform;

}
