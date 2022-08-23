#pragma once


namespace Tomato
{
	class Quaternion
	{
	public:
		Quaternion(Float scalar = 0.0f, Float3 vector = Float3());
		Quaternion(Float a, Float b, Float c, Float d);
		~Quaternion() = default;

		Quaternion Conjugate() const;
		Float Norm() const;
		Quaternion Reciprocal() const;
		Quaternion Normalize() const;

		std::string ToString() const;

		Quaternion operator+(const Quaternion& other) const;
		Quaternion operator-(const Quaternion& other) const;
		Quaternion operator*(const Quaternion& other) const;
		Quaternion operator/(const Quaternion& other) const;
		friend Quaternion operator*(Float scalar, const Quaternion& q);
		friend Quaternion operator*(const Quaternion& q, Float scalar);
	
		static Quaternion Rotation(Float angle, const Float3& axis);
		static Quaternion Rotation(Float pitch, Float yaw, Float roll);
		static Quaternion Rotation(const Float3& angles);
	
		Float4  ToFloat4() const;
		Mat4 ToMat4() const;

		friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);
	private:
		Float m_Scalar;
		Float3 m_Vector;
	};
}
