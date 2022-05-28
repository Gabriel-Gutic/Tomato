#pragma once
#include "UInt.h"
#include <array>
#include <string>
#include <sstream>


namespace Tomato
{
	template <typename T, size_t ROWS, size_t COLS>
	class Matrix
	{
	public:
		Matrix(const T& el = 0);
		~Matrix();
		
		std::string ToString() const;

		std::array<T, COLS>& operator[](UInt index);
		const std::array<T, COLS>& operator[](UInt index) const;
		Matrix<T, ROWS, COLS> operator+(const Matrix<T, ROWS, COLS>& other);
		Matrix<T, ROWS, COLS> operator-(const Matrix<T, ROWS, COLS>& other);
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
}
