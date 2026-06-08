#pragma once
#include <DirectXMath.h>
#define INLINE __forceinline
namespace Reverie::Math
{
	using namespace DirectX;

    enum ZeroTag { kZero, kOrigin };
    enum IdentityTag { kOne, kIdentity };
    enum XUnitVector { kXUnitVector };
    enum YUnitVector { kYUnitVector };
    enum ZUnitVector { kZUnitVector };
    enum WUnitVector { kWUnitVector };
}