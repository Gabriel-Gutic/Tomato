#include "pchTomato.h"
#include "Quaternion.h"


namespace Tomato
{
	Quaternion::Quaternion(float scalar, Float3 vector)
		:m_Scalar(scalar), m_Vector(vector)
	{
	}

	Quaternion::Quaternion(float a, float b, float c, float d)
		:m_Scalar(a), m_Vector(Float3(b, c, d))
	{
	}

	Quaternion Quaternion::Conjugate() const
	{
		return Quaternion(m_Scalar, -1 * m_Vector);
	}

	float Quaternion::Norm() const
	{
		return sqrtf(m_Scalar * m_Scalar + m_Vector[0] * m_Vector[0] + 
			m_Vector[1] * m_Vector[1] + m_Vector[2] * m_Vector[2]
		);
	}

	Quaternion Quaternion::Reciprocal() const
	{
		float norm = Norm();
		return 1.0f / (norm * norm) * Conjugate();
	}

	Quaternion Quaternion::Normalize() const
	{
		return 1.0f / Norm() * *this;
	}

	std::string Quaternion::ToString() const
	{
		std::stringstream ss;
		ss << "(" << m_Scalar << ", " << m_Vector.ToString() << ")";
		return ss.str();
	}

	Quaternion Quaternion::operator+(const Quaternion& other) const
	{
		return Quaternion(this->m_Scalar + other.m_Scalar, this->m_Vector + other.m_Vector);
	}

	Quaternion Quaternion::operator-(const Quaternion& other) const
	{
		return Quaternion(this->m_Scalar - other.m_Scalar, this->m_Vector - other.m_Vector);
	}

	Quaternion Quaternion::operator*(const Quaternion& other) const
	{
		return Quaternion(this->m_Scalar * other.m_Scalar - Float3::DotProduct(this->m_Vector, other.m_Vector),
			this->m_Scalar * other.m_Vector + other.m_Scalar * this->m_Vector + Float3::CrossProduct(this->m_Vector, other.m_Vector)
		);
	}

	Quaternion Quaternion::operator/(const Quaternion& other) const
	{
		return *this * other.Reciprocal();
	}

	Quaternion Quaternion::Rotation(const Float3& angles)
	{
		return Rotation(angles.x, angles.y, angles.z);
	}

	Float4 Quaternion::ToFloat4() const
	{
		return Float4(m_Scalar, m_Vector);
	}

	Mat4 Quaternion::ToMat4() const
	{
		Mat4 m(1.0f);

		float x, y, z, s;
		x = m_Vector.x;
		y = m_Vector.y;
		z = m_Vector.z;
		s = m_Scalar;

		m[0][0] = 1 - 2 * y * y - 2 * z * z;
		m[0][1] = 2 * x * y - 2 * s * z;
		m[0][2] = 2 * x * z + 2 * s * y;
		m[1][0] = 2 * x * y + 2 * s * z;
		m[1][1] = 1 - 2 * x * x - 2 * z * z;
		m[1][2] = 2 * y * z - 2 * s * x;
		m[2][0] = 2 * x * z - 2 * s * y;
		m[2][1] = 2 * y * z + 2 * s * x;
		m[2][2] = 1 - 2 * x * x - 2 * y * y;

		return m;
	}

	Quaternion Quaternion::Rotation(float angle, const Float3& axis)
	{
		float cosine = cosf(Math::Radians(angle) / 2.0f);
		float sine = sinf(Math::Radians(angle) / 2.0f);
		Quaternion q(cosine, sine * Math::Normalize(axis));

		return q;
	}

	Quaternion Quaternion::Rotation(float roll, float pitch, float yaw)
	{
		float cr = cosf(Math::Radians(roll) / 2.0f);
		float sr = sinf(Math::Radians(roll) / 2.0f);
		float cp = cosf(Math::Radians(pitch) / 2.0f);
		float sp = sinf(Math::Radians(pitch) / 2.0f);
		float cy = cosf(Math::Radians(yaw) / 2.0f);
		float sy = sinf(Math::Radians(yaw) / 2.0f);

		Quaternion q(
			cr * cp * cy + sr * sp * sy,
			sr * cp * cy - cr * sp * sy,
			cr * sp * cy + sr * cp * sy,
			cr * cp * sy - sr * sp * cy
		);

		return q;
	}

	Quaternion operator*(float scalar, const Quaternion& q)
	{
		return Quaternion(scalar * q.m_Scalar, scalar * q.m_Vector);
	}

	Quaternion operator*(const Quaternion& q, float scalar)
	{
		return scalar * q;
	}

	std::ostream& operator<<(std::ostream& os, const Quaternion& q)
	{
		os << q.ToString();
		return os;
	}
}