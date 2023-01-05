#pragma once
#include "UInt.h"
#include <array>
#include <string>
#include <cmath>
#include <sstream>


namespace Tomato
{
	template <typename T, size_t ROWS, size_t COLS>
	class Matrix
	{
	public:
		Matrix(const T& el = 0);
		Matrix(const Matrix<T, ROWS, COLS>& M);
		~Matrix();
		
		std::string ToString() const;

		bool operator==(const Matrix<T, ROWS, COLS>& other) const;
		bool operator!=(const Matrix<T, ROWS, COLS>& other) const;
		std::array<T, COLS>& operator[](unsigned int index);
		const std::array<T, COLS>& operator[](unsigned int index) const;
		Matrix<T, ROWS, COLS> operator+(const Matrix<T, ROWS, COLS>& other) const;
		Matrix<T, ROWS, COLS> operator-(const Matrix<T, ROWS, COLS>& other) const;
		
		T GetDeterminant() const;
		Matrix<T, ROWS - 1, COLS - 1> Minor(unsigned int row, unsigned int col) const;
		const std::array<std::array<T, COLS>, ROWS>& GetData() const;

		template <typename T, size_t M, size_t N, size_t P>
		friend Matrix<T, M, P> operator*(const Matrix<T, M, N>& A, const Matrix<T, N, P>& B);
		template <typename T, size_t ROWS, size_t COLS>
		friend Matrix<T, ROWS, COLS> operator*(const T scalar, const Matrix<T, ROWS, COLS>& mat);
		template <typename T, size_t ROWS, size_t COLS>
		friend Matrix<T, ROWS, COLS> operator*(const Matrix<T, ROWS, COLS>& mat, const T scalar);
	
		template <typename T, size_t ROWS, size_t COLS>
		friend std::ostream& operator<<(std::ostream& os, const Matrix<T, ROWS, COLS>& A);
	
		T* ToPtr();
		const T* ToPtr() const;
	private: 
		static void Diagonally(Matrix<T, ROWS, COLS>& A, unsigned int n = 0);
	protected:
		std::array<std::array<T, COLS>, ROWS> m_Data;
	};

	template<typename T, size_t ROWS, size_t COLS>
	inline Matrix<T, ROWS, COLS>::Matrix(const T& el)
	{
		for (unsigned int i = 0; i < ROWS; i++)
			for (unsigned int j = 0; j < COLS; j++)
				if (i != j)
					m_Data[i][j] = 0;
				else
					m_Data[i][j] = el;
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline Matrix<T, ROWS, COLS>::Matrix(const Matrix<T, ROWS, COLS>& M)
	{
		m_Data = M.m_Data;
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline Matrix<T, ROWS, COLS>::~Matrix()
	{
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline std::string Matrix<T, ROWS, COLS>::ToString() const
	{
		std::stringstream ss;
		ss << "(";
		for (unsigned int i = 0; i < ROWS; i++)
		{
			ss << "(" << m_Data[i][0];
			for (unsigned int j = 1; j < COLS; j++)
				ss << ", " << m_Data[i][j];
			ss << ")";
			if (i < ROWS - 1)
				ss << ", ";
		}
		ss << ")";
		
		return ss.str();
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline bool Matrix<T, ROWS, COLS>::operator==(const Matrix<T, ROWS, COLS>& other) const
	{
		for (unsigned int i = 0; i < ROWS; i++)
			for (unsigned int j = 0; j < COLS; j++)
				if (m_Data[i][j] != other[i][j])
					return false;
		return true;
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline bool Matrix<T, ROWS, COLS>::operator!=(const Matrix<T, ROWS, COLS>& other) const
	{
		return !(*this == other);
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline std::array<T, COLS>& Matrix<T, ROWS, COLS>::operator[](unsigned int index)
	{
		return m_Data[index];
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline const std::array<T, COLS>& Matrix<T, ROWS, COLS>::operator[](unsigned int index) const
	{
		return m_Data[index];
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline Matrix<T, ROWS, COLS> Matrix<T, ROWS, COLS>::operator+(const Matrix<T, ROWS, COLS>& other) const
	{
		Matrix<T, ROWS, COLS> M;
		for (unsigned int i = 0; i < ROWS; i++)
			for (unsigned int j = 0; j < COLS; j++)
				M[i][j] = m_Data[i][j] + other[i][j];
		return M;
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline Matrix<T, ROWS, COLS> Matrix<T, ROWS, COLS>::operator-(const Matrix<T, ROWS, COLS>& other) const
	{
		Matrix<T, ROWS, COLS> M;
		for (unsigned int i = 0; i < ROWS; i++)
			for (unsigned int j = 0; j < COLS; j++)
				M[i][j] = m_Data[i][j] - other[i][j];
		return M;
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline T Matrix<T, ROWS, COLS>::GetDeterminant() const
	{
		if (ROWS != COLS)
			return NAN;

		if (ROWS == 2)
			return m_Data[0][0] * m_Data[1][1] - m_Data[0][1] * m_Data[1][0];

		auto M = *this;

		T det = 1;

		Diagonally(M);
		for (unsigned int i = 0; i < ROWS; i++)
			det *= M[i][i];
		return det;
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline Matrix<T, ROWS - 1, COLS - 1> Matrix<T, ROWS, COLS>::Minor(unsigned int row, unsigned int col) const
	{
		TOMATO_ASSERT(row < ROWS && col < COLS, "You're trying to remove a row or a column that is not in the matrix");

		Matrix<T, ROWS - 1, COLS - 1> minor;
		unsigned int i0, j0;
		i0 = j0 = 0;
		for (unsigned int i = 0; i < ROWS; i++)
			for (unsigned int j = 0; j < COLS; j++)
				if (i != row && j != col)
				{
					minor[i0][j0++] = m_Data[i][j];
					if (j0 == COLS - 1)
					{
						i0++;
						j0 = 0;
					}
				}
		return minor;
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline const std::array<std::array<T, COLS>, ROWS>& Matrix<T, ROWS, COLS>::GetData() const
	{
		return m_Data;
	}

	template<typename T, size_t M, size_t N, size_t P>
	inline Matrix<T, M, P> operator*(const Matrix<T, M, N>& A, const Matrix<T, N, P>& B)
	{
		Matrix<T, M, P> C;
		for (unsigned int i = 0; i < M; i++)
		{
			for (unsigned int k = 0; k < N; k++)
			{
				for (unsigned int j = 0; j < P; j++)
				{
					C[i][j] += (A[i][k] * B[k][j]);
				}
			}
		}
		return C;
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline Matrix<T, ROWS, COLS> operator*(const T scalar, const Matrix<T, ROWS, COLS>& mat)
	{
		Matrix<T, ROWS, COLS> result;

		for (unsigned int i = 0; i < ROWS; i++)
			for (unsigned int j = 0; j < ROWS; j++)
				result[i][j] = scalar * mat[i][j];
		return result;
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline Matrix<T, ROWS, COLS> operator*(const Matrix<T, ROWS, COLS>& mat, const T scalar)
	{
		return scalar * mat;
	}

	template<typename T, size_t ROWS, size_t COLS>
	std::ostream& operator<<(std::ostream& os, const Matrix<T, ROWS, COLS>& A)
	{
		os << A.ToString();
		return os;
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline T* Matrix<T, ROWS, COLS>::ToPtr()
	{
		return &m_Data[0][0];
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline const T* Matrix<T, ROWS, COLS>::ToPtr() const
	{
		return &m_Data[0][0];
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline void Matrix<T, ROWS, COLS>::Diagonally(Matrix<T, ROWS, COLS>& A, unsigned int n)
	{
		unsigned int line = n;
		while (line < ROWS)
			if (A[line][n] == 0)
				line++;
			else break;

		if (line == ROWS)
			return;

		if (line != n)
			for (unsigned int j = n; j < ROWS; j++)
				std::swap(A[n][j], A[line][j]);

		for (unsigned int i = n + 1; i < ROWS; i++)
			if (A[i][n] != 0)
			{
				T el = -A[i][n] / A[n][n];
				A[i][n] = 0;
				for (unsigned int j = n + 1; j < ROWS; j++)
				{
					A[i][j] += el * A[n][j];
				}
			}

		if (n < ROWS - 1)
			Diagonally(A, n + 1);
	}

	class Mat4
	{
	public:
		Mat4(float value = 0.0f);
		Mat4(const Mat4&) = default;
		~Mat4() = default;

		std::string ToString() const;

		bool operator==(const Mat4& other) const;
		bool operator!=(const Mat4& other) const;
		Float4& operator[](unsigned int index);
		const Float4& operator[](unsigned int index) const;
		Mat4 operator+(const Mat4& other) const;
		Mat4 operator-(const Mat4& other) const;

		float GetDeterminant() const;
		Matrix<float, 3, 3> Minor(unsigned int row, unsigned int col) const;
		const std::array<Float4, 4>& GetData() const;

		friend Mat4 operator*(const Mat4& A, const Mat4& B);
		friend Mat4 operator*(const float scalar, const Mat4& mat);
		friend Mat4 operator*(const Mat4& mat, const float scalar);

		friend std::ostream& operator<<(std::ostream& os, const Mat4& A);

		float* ToPtr();
		const float* ToPtr() const;
	private:
		std::array<Float4, 4> m_Data;
	};
}
