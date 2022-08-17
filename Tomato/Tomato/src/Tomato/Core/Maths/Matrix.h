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
		std::array<T, COLS>& operator[](UInt index);
		const std::array<T, COLS>& operator[](UInt index) const;
		Matrix<T, ROWS, COLS> operator+(const Matrix<T, ROWS, COLS>& other) const;
		Matrix<T, ROWS, COLS> operator-(const Matrix<T, ROWS, COLS>& other) const;
		
		Float GetDeterminant() const;
		Matrix<T, ROWS - 1, COLS - 1> Minor(UInt row, UInt col) const;
		const std::array<std::array<T, COLS>, ROWS>& GetData() const;

		template <typename T, size_t M, size_t N, size_t P>
		friend Matrix<T, M, P> operator*(const Matrix<T, M, N>& A, const Matrix<T, N, P>& B);
		template <typename T, size_t ROWS, size_t COLS>
		friend Matrix<T, ROWS, COLS> operator*(const T scalar, const Matrix<T, ROWS, COLS>& mat);
		template <typename T, size_t ROWS, size_t COLS>
		friend Matrix<T, ROWS, COLS> operator*(const Matrix<T, ROWS, COLS>& mat, const T scalar);
	
		template <typename T, size_t ROWS, size_t COLS>
		friend std::ostream& operator<<(std::ostream& os, const Matrix<T, ROWS, COLS>& A);
	private: 
		static void Diagonally(Matrix<T, ROWS, COLS>& A, UInt n = 0);
	protected:
		std::array<std::array<T, COLS>, ROWS> m_Data;
	};

	template<typename T, size_t ROWS, size_t COLS>
	inline Matrix<T, ROWS, COLS>::Matrix(const T& el)
	{
		for (UInt i = 0; i < ROWS; i++)
			for (UInt j = 0; j < COLS; j++)
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
		for (UInt i = 0; i < ROWS; i++)
		{
			ss << "(" << m_Data[i][0];
			for (UInt j = 1; j < COLS; j++)
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
		for (UInt i = 0; i < ROWS; i++)
			for (UInt j = 0; j < COLS; j++)
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
	inline std::array<T, COLS>& Matrix<T, ROWS, COLS>::operator[](UInt index)
	{
		return m_Data[index];
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline const std::array<T, COLS>& Matrix<T, ROWS, COLS>::operator[](UInt index) const
	{
		return m_Data[index];
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline Matrix<T, ROWS, COLS> Matrix<T, ROWS, COLS>::operator+(const Matrix<T, ROWS, COLS>& other) const
	{
		Matrix<T, ROWS, COLS> M;
		for (UInt i = 0; i < ROWS; i++)
			for (UInt j = 0; j < COLS; j++)
				M[i][j] = m_Data[i][j] + other[i][j];
		return M;
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline Matrix<T, ROWS, COLS> Matrix<T, ROWS, COLS>::operator-(const Matrix<T, ROWS, COLS>& other) const
	{
		Matrix<T, ROWS, COLS> M;
		for (UInt i = 0; i < ROWS; i++)
			for (UInt j = 0; j < COLS; j++)
				M[i][j] = m_Data[i][j] - other[i][j];
		return M;
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline Float Matrix<T, ROWS, COLS>::GetDeterminant() const
	{
		if (ROWS != COLS)
			return NAN;

		if (ROWS == 2)
			return m_Data[0][0] * m_Data[1][1] - m_Data[0][1] * m_Data[1][0];

		auto M = *this;

		Float det = 1;

		Diagonally(M);
		for (UInt i = 0; i < ROWS; i++)
			det *= M[i][i];
		return det;
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline Matrix<T, ROWS - 1, COLS - 1> Matrix<T, ROWS, COLS>::Minor(UInt row, UInt col) const
	{
		TOMATO_ASSERT(row < ROWS && col < COLS, "You're trying to remove a row or a column that is not in the matrix");

		Matrix<T, ROWS - 1, COLS - 1> minor;
		UInt i0, j0;
		i0 = j0 = 0;
		for (UInt i = 0; i < ROWS; i++)
			for (UInt j = 0; j < COLS; j++)
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
	Matrix<T, M, P> operator*(const Matrix<T, M, N>& A, const Matrix<T, N, P>& B)
	{
		Matrix<T, M, P> C;
		for (UInt i = 0; i < M; i++)
		{
			for (UInt j = 0; j < P; j++)
			{
				C[i][j] = 0;
				for (UInt k = 0; k < N; k++)
				{
					C[i][j] += (A[i][k] * B[k][j]);
				}
			}
		}
		return C;
	}

	template<typename T, size_t ROWS, size_t COLS>
	Matrix<T, ROWS, COLS> operator*(const T scalar, const Matrix<T, ROWS, COLS>& mat)
	{
		Matrix<T, ROWS, COLS> result;

		for (UInt i = 0; i < ROWS; i++)
			for (UInt j = 0; j < ROWS; j++)
				result[i][j] = scalar * mat[i][j];
		return result;
	}

	template<typename T, size_t ROWS, size_t COLS>
	Matrix<T, ROWS, COLS> operator*(const Matrix<T, ROWS, COLS>& mat, const T scalar)
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
	inline void Matrix<T, ROWS, COLS>::Diagonally(Matrix<T, ROWS, COLS>& A, UInt n)
	{
		UInt line = n;
		while (line < ROWS)
			if (A[line][n] == 0)
				line++;
			else break;

		if (line == ROWS)
			return;

		if (line != n)
			for (UInt j = n; j < ROWS; j++)
				std::swap(A[n][j], A[line][j]);

		for (UInt i = n + 1; i < ROWS; i++)
			if (A[i][n] != 0)
			{
				T el = -A[i][n] / A[n][n];
				A[i][n] = 0;
				for (UInt j = n + 1; j < ROWS; j++)
				{
					A[i][j] += el * A[n][j];
				}
			}

		if (n < ROWS - 1)
			Diagonally(A, n + 1);
	}

}
