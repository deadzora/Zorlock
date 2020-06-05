#include "ZLpch.h"
#include "Math.h"
#include "Zorlock/Renderer/Color.h"
namespace Zorlock
{




	Vector3::Vector3(ColorRGB& c) : x(c.x), y(c.y), z(c.z)
	{
	}

	Vector3 Vector3::lerp(float t, const Vector3& a, const Vector3& b)
	{
		t = MathF::clamp(t, 0, 1);
		return (1.0f - t) * a + t * b;
	}

	Vector4::Vector4(ColorRGB& c) : x(c.x), y(c.y), z(c.z), w(1.0f)
	{
	}

	Vector4::Vector4(ColorRGBA& c) : x(c.x), y(c.y), z(c.z), w(c.w)
	{

	}

	void Quaternion::fromRotationMatrix(const Matrix& mata)
	{
		// Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
		// article "Quaternion Calculus and Fast Animation".
		MATRIX3ARRAY& mat = Matrix(mata).ToArray();
		float trace = mat[0][0] + mat[1][1] + mat[2][2];
		float root;

		if (trace > 0.0f)
		{
			// |w| > 1/2, may as well choose w > 1/2
			root = sqrt(trace + 1.0f);  // 2w
			w = 0.5f * root;
			root = 0.5f / root;  // 1/(4w)
			x = (mat[2][1] - mat[1][2]) * root;
			y = (mat[0][2] - mat[2][0]) * root;
			z = (mat[1][0] - mat[0][1]) * root;
		}
		else
		{
			// |w| <= 1/2
			static UINT32 nextLookup[3] = { 1, 2, 0 };
			UINT32 i = 0;

			if (mat[1][1] > mat[0][0])
				i = 1;

			if (mat[2][2] > mat[i][i])
				i = 2;

			UINT32 j = nextLookup[i];
			UINT32 k = nextLookup[j];

			root = sqrt(mat[i][i] - mat[j][j] - mat[k][k] + 1.0f);

			float* cmpntLookup[3] = { &x, &y, &z };
			*cmpntLookup[i] = 0.5f * root;
			root = 0.5f / root;

			w = (mat[k][j] - mat[j][k]) * root;
			*cmpntLookup[j] = (mat[j][i] + mat[i][j]) * root;
			*cmpntLookup[k] = (mat[k][i] + mat[i][k]) * root;
		}

		normalize();
	}

	Quaternion Quaternion::normalize(const Quaternion& q, float tolerance)
	{
		float sqrdLen = dot(q, q);
		if (sqrdLen > tolerance)
			return q * MathF::invSqrt(sqrdLen);

		return q;
	}

	Quaternion Quaternion::slerp(float t, const Quaternion& p, const Quaternion& q, bool shortestPath)
	{
		float cos = p.dot(q);
		Quaternion quat;

		if (cos < 0.0f && shortestPath)
		{
			cos = -cos;
			quat = -q;
		}
		else
		{
			quat = q;
		}

		if (abs(cos) < 1 - EPSILON)
		{
			// Standard case (slerp)
			float sin = sqrtf(1 - MathF::sqr(cos));
			float angle = MathF::RadiansFromDegrees(atan2(sin, cos));
			float invSin = 1.0f / sin;
			float coeff0 = sinf((1.0f - t) * angle) * invSin;
			float coeff1 = sinf(t * angle) * invSin;
			return coeff0 * p + coeff1 * quat;
		}
		else
		{
			// There are two situations:
			// 1. "p" and "q" are very close (fCos ~= +1), so we can do a linear
			//    interpolation safely.
			// 2. "p" and "q" are almost inverse of each other (fCos ~= -1), there
			//    are an infinite number of possibilities interpolation. but we haven't
			//    have method to fix this case, so just use linear interpolation here.
			Quaternion ret = (1.0f - t) * p + t * quat;

			// Taking the complement requires renormalization
			ret.normalize();
			return ret;
		}
	}

	void Matrix::QDUDecomposition(Matrix& matQ, Vector3& vecD, Vector3& vecU) const
	{
		// Build orthogonal matrix Q
		float invLength = MathF::invSqrt(i.x * i.x + j.x * j.x + k.x * k.x);
		matQ.i.x = i.x * invLength;
		matQ.j.x = j.x * invLength;
		matQ.k.x = k.x * invLength;

		float dot = matQ.i.x * i.y + matQ.j.x * j.y + matQ.k.x * k.y;
		matQ.i.y = i.y - dot * matQ.i.x;
		matQ.j.y = j.y - dot * matQ.j.x;
		matQ.k.y = k.y - dot * matQ.k.x;

		invLength = MathF::invSqrt(matQ.i.y * matQ.i.y + matQ.j.y * matQ.j.y + matQ.k.y * matQ.k.y);
		matQ.i.y *= invLength;
		matQ.j.y *= invLength;
		matQ.k.y *= invLength;

		dot = matQ.i.x * i.z + matQ.j.x * j.z + matQ.k.x * k.z;
		matQ.i.z = i.z - dot * matQ.i.x;
		matQ.j.z = j.z - dot * matQ.j.x;
		matQ.k.z = k.z - dot * matQ.k.x;

		dot = matQ.i.y * i.z + matQ.j.y * j.z + matQ.k.y * k.z;
		matQ.i.z -= dot * matQ.i.y;
		matQ.j.z -= dot * matQ.j.y;
		matQ.k.z -= dot * matQ.k.y;

		invLength = MathF::invSqrt(matQ.i.z * matQ.i.z + matQ.j.z * matQ.j.z + matQ.k.z * matQ.k.z);
		matQ.i.z *= invLength;
		matQ.j.z *= invLength;
		matQ.k.z *= invLength;

		// Guarantee that orthogonal matrix has determinant 1 (no reflections)
		float fDet = matQ.i.x * matQ.j.y * matQ.k.z + matQ.i.y * matQ.j.z * matQ.k.x +
			matQ.i.z * matQ.j.x * matQ.k.y - matQ.i.z * matQ.j.y * matQ.k.x -
			matQ.i.y * matQ.j.x * matQ.k.z - matQ.i.x * matQ.j.z * matQ.k.y;

		if (fDet < 0.0f)
		{
			matQ.inverse();
		}

		// Build "right" matrix R
		Matrix matRight;
		matRight.i.x = matQ.i.x * i.x + matQ.j.x * j.x +
			matQ.k.x * k.x;
		matRight.i.y = matQ.i.x * i.y + matQ.j.x * j.y +
			matQ.k.x * k.y;
		matRight.j.y = matQ.i.y * i.y + matQ.j.y * j.y +
			matQ.k.y * k.y;
		matRight.i.z = matQ.i.x * i.z + matQ.j.x * j.z +
			matQ.k.x * k.z;
		matRight.j.z = matQ.i.y * i.z + matQ.j.y * j.z +
			matQ.k.y * k.z;
		matRight.k.z = matQ.i.z * i.z + matQ.j.z * j.z +
			matQ.k.z * k.z;

		// The scaling component
		vecD.x = matRight.i.x;
		vecD.y = matRight.j.y;
		vecD.z = matRight.k.z;

		// The shear component
		float invD0 = 1.0f / vecD.x;
		vecU.x = matRight.i.y * invD0;
		vecU.y = matRight.i.z * invD0;
		vecU.z = matRight.j.z / vecD.y;
	}

}
