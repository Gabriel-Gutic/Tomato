#include "pchTomato.h"
#include "Matrix.h"


namespace Tomato
{
	Mat4::Mat4(float value)
	{
		for (int i = 0; i < 4; i++)
		{
			m_Data[i] = Float4(0.0f, 0.0f, 0.0f, 0.0f);
			m_Data[i][i] = value;
		}
	}

	std::string Mat4::ToString() const
	{
		std::stringstream ss;
		ss << "(";
		for (unsigned int i = 0; i < 4; i++)
		{
			if (i != 0)
				ss << ", ";
			ss << "(" << m_Data[i] << ")";
		}
		ss << ")";

		return ss.str();
	}

	bool Mat4::operator==(const Mat4& other) const
	{
		for (unsigned int i = 0; i < 4; i++)
			for (unsigned int j = 0; j < 4; j++)
				if (m_Data[i][j] != other[i][j])
					return false;
		return true;
	}

	bool Mat4::operator!=(const Mat4& other) const
	{
		return !(*this == other);
	}

	Float4& Mat4::operator[](unsigned int index)
	{
		return m_Data[index];
	}

	const Float4& Mat4::operator[](unsigned int index) const
	{
		return m_Data[index];
	}

	Mat4 Mat4::operator+(const Mat4& other) const
	{
		Mat4 result;
		for (int i = 0; i < 4; i++)
		{
			result[i] = (*this)[i] + other[i];
		}
		return result;
	}

	Mat4 Mat4::operator-(const Mat4& other) const
	{
		Mat4 result;
		for (int i = 0; i < 4; i++)
		{
			result[i] = (*this)[i] - other[i];
		}
		return result;
	}

	float Mat4::GetDeterminant() const
	{
		return 
			  m_Data[0][0] * m_Data[1][1] * m_Data[2][2] * m_Data[3][3]
			+ m_Data[0][0] * m_Data[1][1] * m_Data[2][3] * m_Data[3][2]
			+ m_Data[0][0] * m_Data[1][2] * m_Data[2][1] * m_Data[3][3]
			+ m_Data[0][0] * m_Data[1][2] * m_Data[2][3] * m_Data[3][1]
			+ m_Data[0][0] * m_Data[1][3] * m_Data[2][1] * m_Data[3][2]
			+ m_Data[0][0] * m_Data[1][3] * m_Data[2][2] * m_Data[3][1]

			+ m_Data[0][1] * m_Data[1][0] * m_Data[2][2] * m_Data[3][3]
			+ m_Data[0][1] * m_Data[1][0] * m_Data[2][3] * m_Data[3][2]
			+ m_Data[0][1] * m_Data[1][2] * m_Data[2][0] * m_Data[3][3]
			+ m_Data[0][1] * m_Data[1][2] * m_Data[2][3] * m_Data[3][0]
			+ m_Data[0][1] * m_Data[1][3] * m_Data[2][0] * m_Data[3][2]
			+ m_Data[0][1] * m_Data[1][3] * m_Data[2][2] * m_Data[3][0]

			+ m_Data[0][2] * m_Data[1][1] * m_Data[2][0] * m_Data[3][3]
			+ m_Data[0][2] * m_Data[1][1] * m_Data[2][3] * m_Data[3][0]
			+ m_Data[0][2] * m_Data[1][0] * m_Data[2][0] * m_Data[3][3]
			+ m_Data[0][2] * m_Data[1][0] * m_Data[2][3] * m_Data[3][0]
			+ m_Data[0][2] * m_Data[1][3] * m_Data[2][0] * m_Data[3][0]
			+ m_Data[0][2] * m_Data[1][3] * m_Data[2][0] * m_Data[3][0]

			+ m_Data[0][3] * m_Data[1][1] * m_Data[2][2] * m_Data[3][0]
			+ m_Data[0][3] * m_Data[1][1] * m_Data[2][0] * m_Data[3][2]
			+ m_Data[0][3] * m_Data[1][2] * m_Data[2][1] * m_Data[3][0]
			+ m_Data[0][3] * m_Data[1][2] * m_Data[2][0] * m_Data[3][1]
			+ m_Data[0][3] * m_Data[1][0] * m_Data[2][1] * m_Data[3][2]
			+ m_Data[0][3] * m_Data[1][0] * m_Data[2][2] * m_Data[3][1];
	}

	Matrix<float, 3, 3> Mat4::Minor(unsigned int row, unsigned int col) const
	{
		TOMATO_ASSERT(row < 4 && col < 4, "You're trying to remove a row or a column that is not in the matrix");

		Matrix<float, 3, 3> minor;
		unsigned int i0, j0;
		i0 = j0 = 0;
		for (unsigned int i = 0; i < 4; i++)
			for (unsigned int j = 0; j < 4; j++)
				if (i != row && j != col)
				{
					minor[i0][j0++] = m_Data[i][j];
					if (j0 == 3)
					{
						i0++;
						j0 = 0;
					}
				}
		return minor;
	}

	const std::array<Float4, 4>& Mat4::GetData() const
	{
		return m_Data;
	}

	float* Mat4::ToPtr()
	{
		return m_Data[0].ToPtr();
	}

	const float* Mat4::ToPtr() const
	{
		return m_Data[0].ToPtr();
	}

	Mat4 operator*(const Mat4& A, const Mat4& B)
	{
		Mat4 result;
		for (int i = 0; i < 4; i++)
		{
			result[i] = A[i][0] * B[0];
			for (int j = 1; j < 4; j++)
			{
				result[i] = result[i] + A[i][j] * B[j];
			}
		}
		return result;
	}

	Mat4 operator*(const float scalar, const Mat4& mat)
	{
		Mat4 result;
		for (int i = 0; i < 4; i++)
			result[i] = scalar * mat[i];
		return result;
	}

	Mat4 operator*(const Mat4& mat, const float scalar)
	{
		return scalar * mat;
	}

	std::ostream& operator<<(std::ostream& os, const Mat4& A)
	{
		os << A.ToString();
		return os;
	}

}