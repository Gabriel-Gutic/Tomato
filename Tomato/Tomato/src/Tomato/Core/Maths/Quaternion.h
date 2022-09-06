#pragma once


namespace Tomato
{
	class Quaternion
	{
	public:
		Quaternion(float scalar = 0.0f, Float3 vector = Float3());
		Quaternion(float a, float b, float c, float d);
		~Quaternion() = default;

		Quaternion Conjugate() const;
		float Norm() const;
		Quaternion Reciprocal() const;
		Quaternion Normalize() const;

		std::string ToString() const;

		Quaternion operator+(const Quaternion& other) const;
		Quaternion operator-(const Quaternion& other) const;
		Quaternion operator*(const Quaternion& other) const;
		Quaternion operator/(const Quaternion& other) const;
		friend Quaternion operator*(float scalar, const Quaternion& q);
		friend Quaternion operator*(const Quaternion& q, float scalar);
	
		static Quaternion Rotation(float angle, const Float3& axis);
		static Quaternion Rotation(float pitch, float yaw, float roll);
		static Quaternion Rotation(const Float3& angles);
	
		Float4  ToFloat4() const;
		Mat4 ToMat4() const;

		friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);
	private:
		float m_Scalar;
		Float3 m_Vector;
	};
}
