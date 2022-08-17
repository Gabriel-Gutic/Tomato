#include "pchTomato.h"
#include "Quaternion.h"


namespace Tomato
{
	Quaternion::Quaternion(Float scalar, Float3 vector)
		:m_Scalar(scalar), m_Vector(vector)
	{
	}

	Quaternion::Quaternion(Float a, Float b, Float c, Float d)
		:m_Scalar(a), m_Vector(Float3(b, c, d))
	{
	}

	Quaternion Quaternion::Conjugate() const
	{
		return Quaternion(m_Scalar, -1 * m_Vector);
	}

	Float Quaternion::Norm() const
	{
		return sqrtf(m_Scalar * m_Scalar + m_Vector[0] * m_Vector[0] + 
			m_Vector[1] * m_Vector[1] + m_Vector[2] * m_Vector[2]
		);
	}

	Quaternion Quaternion::Reciprocal() const
	{
		Float norm = Norm();
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

	Float3 Quaternion::Rotate(const Float3& p, const Float3& angles)
	{
		return Rotate(p, angles.x, angles.y, angles.z);
	}

	Float3 Quaternion::Rotate(const Float3& p, Float angle, const Float3& axis)
	{
		Float cosine = cosf(Math::Radians(angle) / 2.0f);
		Float sine = sinf(Math::Radians(angle) / 2.0f);
		Quaternion q(cosine, sine * Math::Normalize(axis));

		Quaternion _p(0.0f, p);

		return (q * _p * q.Reciprocal()).m_Vector;
	}

	Float3 Quaternion::Rotate(const Float3& p, Float roll, Float pitch, Float yaw)
	{
		Float cr = cosf(Math::Radians(roll) / 2.0f);
		Float sr = sinf(Math::Radians(roll) / 2.0f);
		Float cp = cosf(Math::Radians(pitch) / 2.0f);
		Float sp = sinf(Math::Radians(pitch) / 2.0f);
		Float cy = cosf(Math::Radians(yaw) / 2.0f);
		Float sy = sinf(Math::Radians(yaw) / 2.0f);

		Quaternion q(
			cr * cp * cy + sr * sp * sy,
			sr * cp * cy - cr * sp * sy,
			cr * sp * cy + sr * cp * sy,
			cr * cp * sy - sr * sp * cy
		);

		Quaternion _p(0.0f, p);

		return (q * _p * q.Reciprocal()).m_Vector;
	}

	Quaternion operator*(Float scalar, const Quaternion& q)
	{
		return Quaternion(scalar * q.m_Scalar, scalar * q.m_Vector);
	}

	Quaternion operator*(const Quaternion& q, Float scalar)
	{
		return scalar * q;
	}

	std::ostream& operator<<(std::ostream& os, const Quaternion& q)
	{
		os << q.ToString();
		return os;
	}


}