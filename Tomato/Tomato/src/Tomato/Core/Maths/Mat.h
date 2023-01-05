#pragma once


namespace Tomato
{
	using Mat2 = Matrix<float, 2, 2>;
	using Mat2x1 = Matrix<float, 2, 1>;
	using Mat1x2 = Matrix<float, 1, 2>;
	using Mat3 = Matrix<float, 3, 3>;
	using Mat3x1 = Matrix<float, 3, 1>;
	using Mat3x2 = Matrix<float, 3, 2>;
	using Mat1x3 = Matrix<float, 1, 3>;
	using Mat2x3 = Matrix<float, 2, 3>;
	using Mat4x1 = Matrix<float, 4, 1>;
	using Mat4x2 = Matrix<float, 4, 2>;
	using Mat4x3 = Matrix<float, 4, 3>;
	using Mat1x4 = Matrix<float, 1, 4>;
	using Mat2x4 = Matrix<float, 2, 4>;
	using Mat3x4 = Matrix<float, 3, 4>;

	template <typename T>
	Float2 operator*(const Matrix<T, 2, 2>& mat, const Float2& vec);
	template <typename T>
	Double2 operator*(const Matrix<T, 2, 2>& mat, const Double2& vec);
	template <typename T>
	Float2 operator*(const Matrix<T, 2, 2>& mat, const Int2& vec);
	template <typename T>
	Float2 operator*(const Matrix<T, 2, 2>& mat, const UInt2& vec);
	
	template <typename T>
	Float3 operator*(const Matrix<T, 3, 3>& mat, const Float3& vec);
	template <typename T>
	Double3 operator*(const Matrix<T, 3, 3>& mat, const Double3& vec);
	template <typename T>
	Float3 operator*(const Matrix<T, 3, 3>& mat, const Int3& vec);
	template <typename T>
	Float3 operator*(const Matrix<T, 3, 3>& mat, const UInt3& vec);

	template <typename T>
	Float3 operator*(const Matrix<T, 4, 4>& mat, const Float3& vec);
	template <typename T>
	Double3 operator*(const Matrix<T, 4, 4>& mat, const Double3& vec);
	template <typename T>
	Float3 operator*(const Matrix<T, 4, 4>& mat, const Int3& vec);
	template <typename T>
	Float3 operator*(const Matrix<T, 4, 4>& mat, const UInt3& vec);

	Float3 operator*(const Mat4& mat, const Float3& vec);
	Double3 operator*(const Mat4& mat, const Double3& vec);
	Float3 operator*(const Mat4& mat, const Int3& vec);
	Float3 operator*(const Mat4& mat, const UInt3& vec);

	template <typename T>
	Float4 operator*(const Matrix<T, 4, 4>& mat, const Float4& vec);
	template <typename T>
	Double4 operator*(const Matrix<T, 4, 4>& mat, const Double4& vec);
	template <typename T>
	Float4 operator*(const Matrix<T, 4, 4>& mat, const Int4& vec);
	template <typename T>
	Float4 operator*(const Matrix<T, 4, 4>& mat, const UInt4& vec);

	Float4 operator*(const Mat4& mat, const Float4& vec);
	Double4 operator*(const Mat4& mat, const Double4& vec);
	Float4 operator*(const Mat4& mat, const Int4& vec);
	Float4 operator*(const Mat4& mat, const UInt4& vec);

	template<typename T>
	Float2 operator*(const Matrix<T, 2, 2>& mat, const Float2& vec)
	{
		Float2 result(0);
		for (unsigned int i = 0; i < 2; i++)
		{
			result[i] = mat[i][0] * vec.x + mat[i][1] * vec.y;
		}
		return result;
	}

	template<typename T>
	Double2 operator*(const Matrix<T, 2, 2>& mat, const Double2& vec)
	{
		Double2 result(0);
		for (unsigned int i = 0; i < 2; i++)
		{
			result[i] = mat[i][0] * vec.x + mat[i][1] * vec.y;
		}
		return result;
	}

	template<typename T>
	Float2 operator*(const Matrix<T, 2, 2>& mat, const Int2& vec)
	{
		Float2 result(0);
		for (unsigned int i = 0; i < 2; i++)
		{
			result[i] = mat[i][0] * vec.x + mat[i][1] * vec.y;
		}
		return result;
	}

	template<typename T>
	Float2 operator*(const Matrix<T, 2, 2>& mat, const UInt2& vec)
	{
		Float2 result(0);
		for (unsigned int i = 0; i < 2; i++)
		{
			result[i] = mat[i][0] * vec.x + mat[i][1] * vec.y;
		}
		return result;
	}

	template<typename T>
	Float3 operator*(const Matrix<T, 3, 3>& mat, const Float3& vec)
	{
		Float3 result(0);
		for (unsigned int i = 0; i < 3; i++)
		{
			result[i] = mat[i][0] * vec.x + mat[i][1] * vec.y + mat[i][2] * vec.z;
		}
		return result;
	}

	template<typename T>
	Double3 operator*(const Matrix<T, 3, 3>& mat, const Double3& vec)
	{
		Double3 result(0);
		for (unsigned int i = 0; i < 3; i++)
		{
			result[i] = mat[i][0] * vec.x + mat[i][1] * vec.y + mat[i][2] * vec.z;
		}
		return result;
	}

	template<typename T>
	Float3 operator*(const Matrix<T, 3, 3>& mat, const Int3& vec)
	{
		Float3 result(0);
		for (unsigned int i = 0; i < 3; i++)
		{
			result[i] = mat[i][0] * vec.x + mat[i][1] * vec.y + mat[i][2] * vec.z;
		}
		return result;
	}

	template<typename T>
	Float3 operator*(const Matrix<T, 3, 3>& mat, const UInt3& vec)
	{
		Float3 result(0);
		for (unsigned int i = 0; i < 3; i++)
		{
			result[i] = mat[i][0] * vec.x + mat[i][1] * vec.y + mat[i][2] * vec.z;
		}
		return result;
	}

	template<typename T>
	Float3 operator*(const Matrix<T, 4, 4>& mat, const Float3& vec)
	{
		Float3 result(0);
		for (unsigned int i = 0; i < 3; i++)
		{
			result[i] = mat[i][0] * vec.x + mat[i][1] * vec.y + mat[i][2] * vec.z + mat[i][3];
		}
		return result;
	}

	template<typename T>
	Double3 operator*(const Matrix<T, 4, 4>& mat, const Double3& vec)
	{
		Double3 result(0);
		for (unsigned int i = 0; i < 3; i++)
		{
			result[i] = mat[i][0] * vec.x + mat[i][1] * vec.y + mat[i][2] * vec.z + mat[i][3];
		}
		return result;
	}

	template<typename T>
	Float3 operator*(const Matrix<T, 4, 4>& mat, const Int3& vec)
	{
		Float3 result(0);
		for (unsigned int i = 0; i < 3; i++)
		{
			result[i] = mat[i][0] * vec.x + mat[i][1] * vec.y + mat[i][2] * vec.z + mat[i][3];
		}
		return result;
	}

	template<typename T>
	Float3 operator*(const Matrix<T, 4, 4>& mat, const UInt3& vec)
	{
		Float3 result(0);
		for (unsigned int i = 0; i < 3; i++)
		{
			result[i] = mat[i][0] * vec.x + mat[i][1] * vec.y + mat[i][2] * vec.z + mat[i][3];
		}
		return result;
	}

	template<typename T>
	Float4 operator*(const Matrix<T, 4, 4>& mat, const Float4& vec)
	{
		Float4 result(0);
		for (unsigned int i = 0; i < 4; i++)
		{
			result[i] = mat[i][0] * vec.x + mat[i][1] * vec.y + mat[i][2] * vec.z + mat[i][3] * vec.w;
		}
		return result;
	}

	template<typename T>
	Double4 operator*(const Matrix<T, 4, 4>& mat, const Double4& vec)
	{
		Double4 result(0);
		for (unsigned int i = 0; i < 4; i++)
		{
			result[i] = mat[i][0] * vec.x + mat[i][1] * vec.y + mat[i][2] * vec.z + mat[i][3] * vec.w;
		}
		return result;
	}

	template<typename T>
	Float4 operator*(const Matrix<T, 4, 4>& mat, const Int4& vec)
	{
		Float4 result(0);
		for (unsigned int i = 0; i < 4; i++)
		{
			result[i] = mat[i][0] * vec.x + mat[i][1] * vec.y + mat[i][2] * vec.z + mat[i][3] * vec.w;
		}
		return result;
	}

	template<typename T>
	Float4 operator*(const Matrix<T, 4, 4>& mat, const UInt4& vec)
	{
		Float4 result(0);
		for (unsigned int i = 0; i < 4; i++)
		{
			result[i] = mat[i][0] * vec.x + mat[i][1] * vec.y + mat[i][2] * vec.z + mat[i][3] * vec.w;
		}
		return result;
	}
}
