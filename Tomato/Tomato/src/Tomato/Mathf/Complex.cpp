#include "Complex.h"

#include "Mathf.h"

#include <sstream>


namespace Tomato
{

    const Complex Complex::Nan = Complex(NAN, NAN);
    const Complex Complex::Inf = Complex(INFINITY, INFINITY);

    Complex::Complex(float real, float imaginary)
        :m_Real(real), m_Imaginary(imaginary)
    {
    }

    Complex::Complex(const Complex& other)
        :Complex()
    {
        if (this != &other)
        {
            m_Real = other.m_Real;
            m_Imaginary = other.m_Imaginary;
        }
    }

    Complex& Complex::operator=(const Complex& other)
    {
        if (this != &other)
        {
            m_Real = other.m_Real;
            m_Imaginary = other.m_Imaginary;
        }
        return *this;
    }

    float Complex::GetReal() const
    {
        return m_Real;
    }

    float Complex::GetImaginary() const
    {
        return m_Imaginary;
    }

    void Complex::SetReal(float real)
    {
        m_Real = real;
    }

    void Complex::SetImaginary(float imag)
    {
        m_Imaginary = imag;
    }

    float Complex::GetArgument() const
    {
        return atan2f(m_Imaginary, m_Real);
    }

    float Complex::GetModulus() const
    {
        return sqrtf(GetModulusSquared());
    }

    float Complex::GetModulusSquared() const
    {
        return m_Real * m_Real + m_Imaginary * m_Imaginary;
    }

    void Complex::SetArgument(float theta)
    {
        float ro = GetModulus();
        m_Real = ro * cosf(theta);
        m_Imaginary = ro * sinf(theta);
    }

    void Complex::SetModulus(float ro)
    {
        float theta = GetArgument();
        m_Real = ro * cosf(theta);
        m_Imaginary = ro * sinf(theta);
    }

    Complex Complex::GetReverse() const
    {
        return 1.0f / *this;
    }

    Complex Complex::GetConjugate() const
    {
        return Complex(m_Real, -m_Imaginary);
    }

    bool Complex::IsInf() const
    {
        return isinf(m_Real) || isinf(m_Imaginary);
    }

    bool Complex::IsNan() const
    {
        return isnan(m_Real) || isnan(m_Imaginary);
    }

    std::string Complex::ToString() const
    {
        std::stringstream ss;

        if (IsNan())
            return "nan";
        if (IsInf())
            return "inf";

        if (abs(m_Imaginary) < Mathf::Epsilon)
        {
            if (abs(m_Real) >= Mathf::Epsilon)
                ss << m_Real;
            else
                ss << "0";
        }
        else
        {
            if (abs(m_Real) >= Mathf::Epsilon)
            {
                ss << m_Real;
                if (m_Imaginary > 0.0f)
                    ss << "+";
            }
            if (m_Imaginary != 1.0f && m_Imaginary != -1.0f)
                ss << m_Imaginary;
            ss << "i";
        }

        return ss.str();
    }

    Complex::operator float() const
    {
        return m_Real;
    }

    Complex Complex::CreateFromPolar(float theta, float ro)
    {
        return Complex(
            ro * cosf(theta),
            ro * sinf(theta)
        );
    }

    std::ostream& operator<<(std::ostream& os, const Complex& z)
    {
        os << z.ToString();
        return os;
    }

    Complex Complex::operator-()
    {
        return Complex(-m_Real, -m_Imaginary);
    }

    Complex operator+(const Complex& z1, const Complex& z2)
    {
        if (z1.IsInf() && z2.IsInf() || z1.IsNan() || z2.IsNan())
            return Complex::Nan;
        if (z1.IsInf() || z2.IsInf())
            return Complex::Inf;
        return Complex(z1.m_Real + z2.m_Real, z1.m_Imaginary + z2.m_Imaginary);
    }

    Complex operator-(const Complex& z1, const Complex& z2)
    {
        if (z1.IsInf() && z2.IsInf() || z1.IsNan() || z2.IsNan())
            return Complex::Nan;
        if (z1.IsInf() || z2.IsInf())
            return Complex::Inf;
        return Complex(z1.m_Real - z2.m_Real, z1.m_Imaginary - z2.m_Imaginary);
    }

    Complex operator*(const Complex& z1, const Complex& z2)
    {
        if (z1.IsInf() && z2 == 0.0f || z1 == 0.0f && z2.IsInf() || z1.IsNan() || z2.IsNan())
            return Complex::Nan;
        if (z1.IsInf() || z2.IsInf())
            return Complex::Inf;
        return Complex(z1.m_Real * z2.m_Real - z1.m_Imaginary * z2.m_Imaginary, z1.m_Real * z2.m_Imaginary + z1.m_Imaginary * z2.m_Real);
    }

    Complex operator/(const Complex& z1, const Complex& z2)
    {
        if (z2 == 0.0f)
        {
            if (z1 == 0.0f)
                return Complex::Nan;
            return Complex::Inf;
        }
        if (z1.IsInf() && z2.IsInf())
            return Complex::Nan;
        if (z1.IsInf())
            return Complex::Inf;
        if (z2.IsInf())
            return 0.0f;

        float denominator = z2.m_Real * z2.m_Real + z2.m_Imaginary * z2.m_Imaginary;

        return Complex(
            (z1.m_Real * z2.m_Real + z1.m_Imaginary * z2.m_Imaginary) / denominator,
            (z1.m_Imaginary * z2.m_Real - z1.m_Real * z2.m_Imaginary) / denominator);
    }

    bool operator==(const Complex& z1, const Complex& z2)
    {
        return z1.IsInf() && z2.IsInf() || z1.IsNan() && z2.IsNan() || 
            abs(z1.m_Real - z2.m_Real) < Mathf::Epsilon && abs(z1.m_Imaginary - z2.m_Imaginary) < Mathf::Epsilon;
    }

    bool operator!=(const Complex& z1, const Complex& z2)
    {
        return !(z1 == z2);
    }
}