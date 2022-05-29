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

		std::array<T, COLS>& operator[](UInt index);
		const std::array<T, COLS>& operator[](UInt index) const;
		Matrix<T, ROWS, COLS> operator+(const Matrix<T, ROWS, COLS>& other);
		Matrix<T, ROWS, COLS> operator-(const Matrix<T, ROWS, COLS>& other);
		
		T GetDeterminant() const;
		T GetDeterminant1() const;
		// TODO: More efficient

		template <typename T, size_t M, size_t N, size_t P>
		friend Matrix<T, M, P> operator*(const Matrix<T, M, N>& A, const Matrix<T, N, P>& B);
	private: 
		static T Determinant(const Matrix<T, ROWS, COLS>& A, UInt n = 0);
		static T GetMinor(const Matrix<T, ROWS, COLS>& A, UInt n);
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
	inline Matrix<T, ROWS, COLS> Matrix<T, ROWS, COLS>::operator+(const Matrix<T, ROWS, COLS>& other)
	{
		Matrix<T, ROWS, COLS> M;
		for (UInt i = 0; i < ROWS; i++)
			for (UInt j = 0; j < COLS; j++)
				M[i][j] = m_Data[i][j] + other[i][j];
		return M;
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline Matrix<T, ROWS, COLS> Matrix<T, ROWS, COLS>::operator-(const Matrix<T, ROWS, COLS>& other)
	{
		Matrix<T, ROWS, COLS> M;
		for (UInt i = 0; i < ROWS; i++)
			for (UInt j = 0; j < COLS; j++)
				M[i][j] = m_Data[i][j] - other[i][j];
		return M;
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline T Matrix<T, ROWS, COLS>::GetDeterminant() const
	{
		auto M = *this;

		return T();
	}

	template<typename T, size_t ROWS, size_t COLS>
	inline T Matrix<T, ROWS, COLS>::GetDeterminant1() const
	{
		return GetMinor(*this, ROWS);
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
	inline T Matrix<T, ROWS, COLS>::Determinant(const Matrix<T, ROWS, COLS>& A, UInt n)
	{
		if (ROWS != COLS)
			return NAN;
		UInt line = n;
		while (line < ROWS)
			if (A[line][n] == 0)
				line++;
			else break;

		if (line == ROWS)
			return 0;

		if (line != n)
			for (UInt j = n; j < ROWS; j++)
				std::swap(A[n][j], A[line][j]);

		for (UInt i = n + 1; i < ROWS; i++)
			if (A[i][n] != 0)
			{
				for (UInt j = n; j < ROWS; j++)
				{
					//A[i][n]
				}
			}
	}

	template<typename T, size_t ROWS, size_t COLS>
	T Matrix<T, ROWS, COLS>::GetMinor(const Matrix<T, ROWS, COLS>& A, UInt n)
	{
		if (ROWS != COLS || n > ROWS)
			return NAN;
		if (n == 1)
			return A[0][0];
		T minor = 0;
		for (UInt k = 0; k < n; k++)
		{
			Matrix<T, ROWS, COLS> B;
			for (UInt i = 1; i < n; i++)
			{
				UInt p = 0;
				for (UInt j = 0; j < n; j++)
					if (j != k)
						B[i - 1][p++] = A[i][j];
			}

			if (A[0][k] != 0)
				minor += A[0][k] * pow(-1.0, k) * GetMinor(B, n - 1);
		}
		return minor;
	}

}
