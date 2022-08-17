#pragma once

#define Vec2h(Type) class Type##2									\
{																	\
public:																\
	union {															\
		struct {													\
			std::pair<Type, Type> data;								\
		};															\
		struct {													\
			std::array<Type, 2> list;								\
		};															\
		struct {													\
			Type x, y;												\
		};															\
		struct {													\
			Type a, b;												\
		};															\
	};																\
																	\
	Type##2(Type x = 0.0f, Type y = 0.0f);							\
	Type##2(const Type##2& f);										\
	std::string ToString() const;									\
																	\
	static Type DotProduct(const Type##2& f1, const Type##2& f2);	\
																	\
	Type##2& operator=(const Type##2& other);						\
	bool operator==(const Type##2& other) const;					\
	bool operator!=(const Type##2& other) const;					\
	Type##2 operator+(const Type##2& other) const;					\
	Type##2 operator-(const Type##2& other) const;					\
	Type operator*(const Type##2& other) const;						\
	Type& operator[](size_t index); 								\
	const Type& operator[](size_t index) const;						\
	friend Type##2 operator*(const Type##2& f2, Type dot);			\
	friend Type##2 operator*(Type dot, const Type##2& f2);			\
																			\
	friend std::ostream& operator<<(std::ostream& os, const Type##2 & f2);	\
};


#define Vec2cpp(Type) Type##2::Type##2(Type x, Type y)					\
:x(x), y(y)																\
{																		\
}																		\
																		\
Type##2::Type##2(const Type##2& f)											\
	: x(f.x), y(f.y)													\
{																		\
}																		\
																		\
std::string Type##2::ToString() const									\
{																		\
	std::stringstream ss;												\
	ss << "(" << x << ", " << y << ")";									\
	return ss.str();													\
}																		\
																		\
Type Type##2::DotProduct(const Type##2& f1, const Type##2& f2)			\
{																		\
	return f1.x * f2.x + f1.y * f2.y;									\
}																		\
																		\
Type##2& Type##2::operator=(const Type##2& other)						\
{																		\
	if (this == &other)													\
		return *this; 													\
																		\
	data = other.data;													\
	return *this;														\
}																		\
																		\
bool Type##2::operator==(const Type##2& other) const					\
{																		\
	return x == other.x && y == other.y;								\
}																		\
																		\
bool Type##2::operator!=(const Type##2& other) const							\
{																		\
	return !(x == other.x && y == other.y);							\
}																		\
																		\
Type##2 Type##2::operator+(const Type##2& other) const							\
{																		\
	return Type##2(x + other.x, y + other.y);							\
}																		\
																		\
Type##2 Type##2::operator-(const Type##2& other) const							\
{																		\
	return Type##2(x - other.x, y - other.y);							\
}																		\
																		\
Type Type##2::operator*(const Type##2& other) const							\
{																		\
	return DotProduct(*this, other);									\
}																		\
																		\
Type& Type##2::operator[](size_t index)											\
{																		\
	return list[index];													\
}																		\
																		\
const Type& Type##2::operator[](size_t index) const								\
{																		\
	return list[index];													\
}																		\
																		\
Type##2 operator*(const Type##2& f2, Type dot)							\
{																		\
	return Type##2(dot * f2.x, dot * f2.y);								\
}																		\
																		\
Type##2 operator*(Type dot, const Type##2& f2)							\
{																		\
	return f2 * dot;													\
}																		\
																		\
std::ostream& operator<<(std::ostream& os, const Type##2 & f2)			\
{																		\
	os << f2.ToString();												\
	return os;															\
}
					

#define Vec3h(Type) class Type##3												\
	{																		\
	public:																	\
		union {																\
			struct {														\
				std::tuple<Type, Type, Type> data;						\
			};																\
			struct {													\
				std::array<Type, 3> list;							\
			};															\
			struct {														\
				Type##2 xy;													\
			};																\
			struct {														\
				Type##2 ab;													\
			};																\
			struct {														\
				Type x, y, z;												\
			};																\
			struct {														\
				Type a, b, c;												\
			};																\
		};																	\
																			\
		Type##3(Type x = 0.0f, Type y = 0.0f, Type z = 0.0f);				\
		Type##3(const Type##2 & f, Type z = 0.0f);							\
		Type##3(Type x, const Type##2 & f);									\
		Type##3(const Type##3 & f);											\
		std::string ToString() const;										\
																			\
		static Type DotProduct(const Type##3 & f1, const Type##3 & f2);		\
		static Type##3 CrossProduct(const Type##3 & f1, const Type##3 & f2);\
																			\
		Type##3& operator=(const Type##3& other);							\
		bool operator==(const Type##3& other) const;						\
		bool operator!=(const Type##3& other) const;						\
		Type##3 operator+(const Type##3 & other) const;						\
		Type##3 operator-(const Type##3 & other) const;						\
		Type operator*(const Type##3 & other) const;						\
		Type& operator[](size_t index); 									\
		const Type& operator[](size_t index) const;							\
		friend Type##3 operator*(const Type##3 & f3, Type dot);				\
		friend Type##3 operator*(Type dot, const Type##3 & f3);				\
																			\
		friend std::ostream& operator<<(std::ostream& os, const Type##3& f3);	\
	};


#define Vec3cpp(Type) Type##3::Type##3(Type x, Type y, Type z)					\
:x(x), y(y), z(z)																\
{																				\
																				\
}																				\
																				\
Type##3::Type##3(const Type##2& f, Type z)										\
	: x(f.x), y(f.y), z(z)														\
{																				\
}																				\
																				\
Type##3::Type##3(Type x, const Type##2& f)										\
	: x(x), y(f.x), z(f.y)														\
{																				\
}																				\
																				\
Type##3::Type##3(const Type##3& f)													\
	: a(f.a), b(f.b), c(f.c)													\
{																				\
}																				\
																				\
std::string Type##3::ToString() const											\
{																				\
	std::stringstream ss;														\
	ss << "(" << x << ", " << y << ", " << z << ")";							\
	return ss.str();															\
}																				\
																				\
Type Type##3::DotProduct(const Type##3& f1, const Type##3& f2)					\
{																				\
	return f1.x * f2.x + f1.y * f2.y + f1.z * f2.z;								\
}																				\
																				\
Type##3 Type##3::CrossProduct(const Type##3& f1, const Type##3& f2)					\
{																				\
	return Type##3																\
	(																			\
		f1.y * f2.z - f1.z * f2.y,												\
		f1.z * f2.x - f1.x * f2.z,												\
		f1.x * f2.y - f1.y * f2.x												\
	);																			\
}																				\
																				\
Type##3& Type##3::operator=(const Type##3& other)						\
{																		\
	if (this == &other)													\
		return *this; 													\
																		\
	data = other.data;													\
	return *this;														\
}																		\
																		\
bool Type##3::operator==(const Type##3& other) const							\
{																				\
	return x == other.x && y == other.y && z == other.z;						\
}																				\
																				\
bool Type##3::operator!=(const Type##3& other) const									\
{																				\
	return !(x == other.x && y == other.y && z == other.z);						\
}																				\
																				\
Type##3 Type##3::operator+(const Type##3& other) const								\
{																				\
	return Type##3(x + other.x, y + other.y, z + other.z);						\
}																				\
																				\
Type##3 Type##3::operator-(const Type##3& other) const									\
{																				\
	return Type##3(x - other.x, y - other.y, z - other.z);						\
}																				\
																				\
Type Type##3::operator*(const Type##3& other) const									\
{																				\
	return DotProduct(*this, other);											\
}																				\
																				\
Type& Type##3::operator[](size_t index)											\
{																		\
	return list[index];													\
}																		\
																		\
const Type& Type##3::operator[](size_t index) const								\
{																		\
	return list[index];													\
}																		\
																				\
Type##3 operator*(const Type##3& f3, Type dot)									\
{																				\
	return Type##3(dot * f3.x, dot * f3.y, dot * f3.z);							\
}																				\
																				\
Type##3 operator*(Type dot, const Type##3& f3)									\
{																				\
	return f3 * dot;															\
}																				\
																				\
std::ostream& operator<<(std::ostream& os, const Type##3& f3)					\
{																				\
	os << f3.ToString();														\
	return os;																	\
}


#define Vec4h(Type) class Type##4													\
	{																			\
	public:																		\
		union {																	\
			struct {															\
				std::tuple<Type, Type, Type, Type> data;					\
			};																	\
			struct {													\
				std::array<Type, 4> list;							\
			};															\
			struct {															\
				Type##3 xyz;														\
			};																	\
			struct {															\
				Type##2 xy, zw;													\
			};																	\
			struct {															\
				Type##3 abc;														\
			};																	\
			struct {															\
				Type##2 ab, cd;													\
			};																	\
			struct {															\
				Type x, y, z, w;												\
			};																	\
			struct {															\
				Type a, b, c, d;												\
			};																	\
		};																		\
																				\
		Type##4(Type x = 0.0f, Type y = 0.0f, Type z = 0.0f, Type w = 0.0f);	\
		Type##4(Type x, const Type##2 & f, Type w = 0.0f);						\
		Type##4(const Type##2 & f1, const Type##2 & f2);							\
		Type##4(const Type##3 & f, Type w = 0.0f);								\
		Type##4(Type x, const Type##3 & f);										\
		Type##4(const Type##4 & f);												\
		std::string ToString() const;											\
																				\
		static Type DotProduct(const Type##4 & f1, const Type##4 & f2);			\
																				\
		Type##4& operator=(const Type##4& other);								\
		bool operator==(const Type##4& other) const;							\
		bool operator!=(const Type##4& other) const;							\
		Type##4 operator+(const Type##4 & other) const;							\
		Type##4 operator-(const Type##4 & other) const;							\
		Type operator*(const Type##4 & other) const;							\
		Type& operator[](size_t index); 										\
		const Type& operator[](size_t index) const;								\
		friend Type##4 operator*(const Type##4 & f3, Type dot);					\
		friend Type##4 operator*(Type dot, const Type##4 & f3);					\
																				\
		friend std::ostream& operator<<(std::ostream& os, const Type##4& f4);	\
	};


#define Vec4cpp(Type) Type##4::Type##4(Type x, Type y, Type z, Type w)			\
:x(x), y(y), z(z), w(w)																\
{																					\
}																					\
																					\
Type##4::Type##4(Type x, const Type##2& f, Type w)									\
	: x(x), y(f.x), z(f.y), w(w)													\
{																					\
}																					\
																					\
Type##4::Type##4(const Type##2& f1, const Type##2& f2)									\
	: xy(f1), zw(f2)																\
{																					\
}																					\
																					\
Type##4::Type##4(const Type##3& f, Type w)											\
	: x(f.x), y(f.y), z(f.z), w(w)													\
{																					\
}																					\
																					\
Type##4::Type##4(Type x, const Type##3& f)											\
	: x(x), y(f.x), z(f.y), w(f.z)													\
{																					\
}																					\
																					\
Type##4::Type##4(const Type##4& f)														\
	: xy(f.xy), zw(f.zw)															\
{																					\
}																					\
																					\
std::string Type##4::ToString() const												\
{																					\
	std::stringstream ss;															\
	ss << "(" << x << ", " << y << ", " << z << ", " << w << ")";					\
	return ss.str();																\
}																					\
																					\
Type Type##4::DotProduct(const Type##4& f1, const Type##4& f2)						\
{																					\
	return f1.x * f2.x + f1.y * f2.y + f1.z * f2.z + f1.w * f2.w;					\
}																					\
																				\
Type##4& Type##4::operator=(const Type##4& other)						\
{																		\
	if (this == &other)													\
		return *this; 													\
																		\
	data = other.data;													\
	return *this;														\
}																		\
																		\
bool Type##4::operator==(const Type##4& other) const									\
{																				\
	return x == other.x && y == other.y && z == other.z && w == other.w;						\
}																				\
																				\
bool Type##4::operator!=(const Type##4& other) const									\
{																				\
	return !(x == other.x && y == other.y && z == other.z && w == other.w);						\
}																				\
																					\
Type##4 Type##4::operator+(const Type##4& other) const										\
{																					\
	return Type##4(x + other.x, y + other.y, z + other.z, w + other.w);				\
}																					\
																					\
Type##4 Type##4::operator-(const Type##4& other) const										\
{																					\
	return Type##4(x - other.x, y - other.y, z - other.z, w - other.w);				\
}																					\
																					\
Type Type##4::operator*(const Type##4& other) const										\
{																					\
	return DotProduct(*this, other);												\
}																					\
																					\
Type& Type##4::operator[](size_t index)														\
{																					\
	return list[index];																\
}																					\
																					\
const Type& Type##4::operator[](size_t index) const											\
{																					\
	return list[index];																\
}																					\
																					\
Type##4 operator*(const Type##4& f4, Type dot)										\
{																					\
	return Type##4(f4.x * dot, f4.y * dot, f4.z * dot, f4.w * dot);					\
}																					\
																					\
Type##4 operator*(Type dot, const Type##4& f4)										\
{																					\
	return f4 * dot;																\
}																				\
																				\
std::ostream& operator<<(std::ostream& os, const Type##4& f4)					\
{																				\
	os << f4.ToString();														\
	return os;																	\
}
