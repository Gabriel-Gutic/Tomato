#pragma once


namespace Tomato::Math
{
	UInt NumberOfDigits(Int number);
	UInt NumberOfDigits(UInt number);
	UInt NumberOfDigits(Long number);
	UInt NumberOfDigits(ULong number);
	std::string ToString(Int number);
	std::string ToString(UInt number);
	std::string ToString(Long number);
	std::string ToString(ULong number);
	std::string ToString(Float number, UInt precision = 2);
	std::string ToString(Double number, UInt precision = 2);
	std::string ToString(Bool value);
}
