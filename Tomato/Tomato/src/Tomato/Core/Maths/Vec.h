#pragma once

#define Vec2h(Name, Type) class Name##2												\
{																				\
public:																			\
	union {																		\
		struct {																\
			std::pair<Type, Type> data;											\
		};																		\
		struct {																\
			std::array<Type, 2> list;											\
		};																		\
		struct {																\
			Type x, y;															\
		};																		\
		struct {																\
			Type a, b;															\
		};																		\
	};																			\
																				\
	Name##2(Type x = 0.0f, Type y = 0.0f);										\
	Name##2(const Name##2& f);													\
	std::string ToString() const;												\
																				\
	static Type DotProduct(const Name##2& f1, const Name##2& f2);				\
																				\
	Name##2& operator=(const Name##2& other);									\
	bool operator==(const Name##2& other) const;								\
	bool operator!=(const Name##2& other) const;								\
	Name##2 operator+(const Name##2& other) const;								\
	Name##2 operator-(const Name##2& other) const;								\
	Type operator*(const Name##2& other) const;									\
	Type& operator[](size_t index); 											\
	const Type& operator[](size_t index) const;									\
	friend Name##2 operator*(const Name##2& f2, Type dot);						\
	friend Name##2 operator*(Type dot, const Name##2& f2);						\
																				\
	friend std::ostream& operator<<(std::ostream& os, const Name##2 & f2);		\
																				\
	Type* ToPtr();																\
	const Type* ToPtr() const;													\
};


#define Vec2cpp(Name, Type) Name##2::Name##2(Type x, Type y)							\
:x(x), y(y)																		\
{																				\
}																				\
																				\
Name##2::Name##2(const Name##2& f)												\
	: x(f.x), y(f.y)															\
{																				\
}																				\
																				\
std::string Name##2::ToString() const											\
{																				\
	std::stringstream ss;														\
	ss << "(" << x << ", " << y << ")";											\
	return ss.str();															\
}																				\
																				\
Type Name##2::DotProduct(const Name##2& f1, const Name##2& f2)					\
{																				\
	return f1.x * f2.x + f1.y * f2.y;											\
}																				\
																				\
Name##2& Name##2::operator=(const Name##2& other)								\
{																				\
	if (this == &other)															\
		return *this; 															\
																				\
	data = other.data;															\
	return *this;																\
}																				\
																				\
bool Name##2::operator==(const Name##2& other) const							\
{																				\
	return x == other.x && y == other.y;										\
}																				\
																				\
bool Name##2::operator!=(const Name##2& other) const							\
{																				\
	return !(x == other.x && y == other.y);										\
}																				\
																				\
Name##2 Name##2::operator+(const Name##2& other) const							\
{																				\
	return Name##2(x + other.x, y + other.y);									\
}																				\
																				\
Name##2 Name##2::operator-(const Name##2& other) const							\
{																				\
	return Name##2(x - other.x, y - other.y);									\
}																				\
																				\
Type Name##2::operator*(const Name##2& other) const								\
{																				\
	return DotProduct(*this, other);											\
}																				\
																				\
Type& Name##2::operator[](size_t index)											\
{																				\
	return list[index];															\
}																				\
																				\
const Type& Name##2::operator[](size_t index) const								\
{																				\
	return list[index];															\
}																				\
																				\
Name##2 operator*(const Name##2& f2, Type dot)									\
{																				\
	return Name##2(dot * f2.x, dot * f2.y);										\
}																				\
																				\
Name##2 operator*(Type dot, const Name##2& f2)									\
{																				\
	return f2 * dot;															\
}																				\
																				\
std::ostream& operator<<(std::ostream& os, const Name##2 & f2)					\
{																				\
	os << f2.ToString();														\
	return os;																	\
}																				\
																				\
Type* Name##2::ToPtr()															\
{																				\
	return &x;																	\
}																				\
																				\
const Type* Name##2::ToPtr() const												\
{																				\
	return &x;																	\
}
					

#define Vec3h(Name, Type) class Name##3												\
	{																			\
	public:																		\
		union {																	\
			struct {															\
				std::tuple<Type, Type, Type> data;								\
			};																	\
			struct {															\
				std::array<Type, 3> list;										\
			};																	\
			struct {															\
				Name##2 xy;														\
			};																	\
			struct {															\
				Name##2 ab;														\
			};																	\
			struct {															\
				Type x, y, z;													\
			};																	\
			struct {															\
				Type a, b, c;													\
			};																	\
		};																		\
																				\
		Name##3(Type x = 0.0f, Type y = 0.0f, Type z = 0.0f);					\
		Name##3(const Name##2 & f, Type z = 0.0f);								\
		Name##3(Type x, const Name##2 & f);										\
		Name##3(const Name##3 & f);												\
		std::string ToString() const;											\
																				\
		static Type DotProduct(const Name##3 & f1, const Name##3 & f2);			\
		static Name##3 CrossProduct(const Name##3 & f1, const Name##3 & f2);	\
																				\
		Name##3& operator=(const Name##3& other);								\
		bool operator==(const Name##3& other) const;							\
		bool operator!=(const Name##3& other) const;							\
		Name##3 operator+(const Name##3 & other) const;							\
		Name##3 operator-(const Name##3 & other) const;							\
		Type operator*(const Name##3 & other) const;							\
		Type& operator[](size_t index); 										\
		const Type& operator[](size_t index) const;								\
		friend Name##3 operator*(const Name##3 & f3, Type dot);					\
		friend Name##3 operator*(Type dot, const Name##3 & f3);					\
																				\
		friend std::ostream& operator<<(std::ostream& os, const Name##3& f3);	\
																				\
		Type* ToPtr();															\
		const Type* ToPtr() const;												\
	};


#define Vec3cpp(Name, Type) Name##3::Name##3(Type x, Type y, Type z)			\
:x(x), y(y), z(z)																\
{																				\
																				\
}																				\
																				\
Name##3::Name##3(const Name##2& f, Type z)										\
	: x(f.x), y(f.y), z(z)														\
{																				\
}																				\
																				\
Name##3::Name##3(Type x, const Name##2& f)										\
	: x(x), y(f.x), z(f.y)														\
{																				\
}																				\
																				\
Name##3::Name##3(const Name##3& f)												\
	: a(f.a), b(f.b), c(f.c)													\
{																				\
}																				\
																				\
std::string Name##3::ToString() const											\
{																				\
	std::stringstream ss;														\
	ss << "(" << x << ", " << y << ", " << z << ")";							\
	return ss.str();															\
}																				\
																				\
Type Name##3::DotProduct(const Name##3& f1, const Name##3& f2)					\
{																				\
	return f1.x * f2.x + f1.y * f2.y + f1.z * f2.z;								\
}																				\
																				\
Name##3 Name##3::CrossProduct(const Name##3& f1, const Name##3& f2)				\
{																				\
	return Name##3																\
	(																			\
		f1.y * f2.z - f1.z * f2.y,												\
		f1.z * f2.x - f1.x * f2.z,												\
		f1.x * f2.y - f1.y * f2.x												\
	);																			\
}																				\
																				\
Name##3& Name##3::operator=(const Name##3& other)								\
{																				\
	if (this == &other)															\
		return *this; 															\
																				\
	data = other.data;															\
	return *this;																\
}																				\
																				\
bool Name##3::operator==(const Name##3& other) const							\
{																				\
	return x == other.x && y == other.y && z == other.z;						\
}																				\
																				\
bool Name##3::operator!=(const Name##3& other) const							\
{																				\
	return !(x == other.x && y == other.y && z == other.z);						\
}																				\
																				\
Name##3 Name##3::operator+(const Name##3& other) const							\
{																				\
	return Name##3(x + other.x, y + other.y, z + other.z);						\
}																				\
																				\
Name##3 Name##3::operator-(const Name##3& other) const							\
{																				\
	return Name##3(x - other.x, y - other.y, z - other.z);						\
}																				\
																				\
Type Name##3::operator*(const Name##3& other) const								\
{																				\
	return DotProduct(*this, other);											\
}																				\
																				\
Type& Name##3::operator[](size_t index)											\
{																				\
	return list[index];															\
}																				\
																				\
const Type& Name##3::operator[](size_t index) const								\
{																				\
	return list[index];															\
}																				\
																				\
Name##3 operator*(const Name##3& f3, Type dot)									\
{																				\
	return Name##3(dot * f3.x, dot * f3.y, dot * f3.z);							\
}																				\
																				\
Name##3 operator*(Type dot, const Name##3& f3)									\
{																				\
	return f3 * dot;															\
}																				\
																				\
std::ostream& operator<<(std::ostream& os, const Name##3& f3)					\
{																				\
	os << f3.ToString();														\
	return os;																	\
}																				\
																				\
Type* Name##3::ToPtr()															\
{																				\
	return &x;																	\
}																				\
																				\
const Type* Name##3::ToPtr() const												\
{																				\
	return &x;																	\
}


#define Vec4h(Name, Type) class Name##4											\
	{																			\
	public:																		\
		union {																	\
			struct {															\
				std::tuple<Type, Type, Type, Type> data;						\
			};																	\
			struct {															\
				std::array<Type, 4> list;										\
			};																	\
			struct {															\
				Name##3 xyz;													\
			};																	\
			struct {															\
				Name##2 xy, zw;													\
			};																	\
			struct {															\
				Name##3 abc;													\
			};																	\
			struct {															\
				Name##2 ab, cd;													\
			};																	\
			struct {															\
				Type x, y, z, w;												\
			};																	\
			struct {															\
				Type a, b, c, d;												\
			};																	\
		};																		\
																				\
		Name##4(Type x = 0.0f, Type y = 0.0f, Type z = 0.0f, Type w = 0.0f);	\
		Name##4(Type x, const Name##2 & f, Type w = 0.0f);						\
		Name##4(const Name##2 & f1, const Name##2 & f2);						\
		Name##4(const Name##3 & f, Type w = 0.0f);								\
		Name##4(Type x, const Name##3 & f);										\
		Name##4(const Name##4 & f);												\
		std::string ToString() const;											\
																				\
		static Type DotProduct(const Name##4 & f1, const Name##4 & f2);			\
																				\
		Name##4& operator=(const Name##4& other);								\
		bool operator==(const Name##4& other) const;							\
		bool operator!=(const Name##4& other) const;							\
		Name##4 operator+(const Name##4 & other) const;							\
		Name##4 operator-(const Name##4 & other) const;							\
		Type operator*(const Name##4 & other) const;							\
		Type& operator[](size_t index); 										\
		const Type& operator[](size_t index) const;								\
		friend Name##4 operator*(const Name##4 & f3, Type dot);					\
		friend Name##4 operator*(Type dot, const Name##4 & f3);					\
																				\
		friend std::ostream& operator<<(std::ostream& os, const Name##4& f4);	\
																				\
		Type* ToPtr();															\
		const Type* ToPtr() const;												\
	};


#define Vec4cpp(Name, Type) Name##4::Name##4(Type x, Type y, Type z, Type w)	\
:x(x), y(y), z(z), w(w)															\
{																				\
}																				\
																				\
Name##4::Name##4(Type x, const Name##2& f, Type w)								\
	: x(x), y(f.x), z(f.y), w(w)												\
{																				\
}																				\
																				\
Name##4::Name##4(const Name##2& f1, const Name##2& f2)							\
	: xy(f1), zw(f2)															\
{																				\
}																				\
																				\
Name##4::Name##4(const Name##3& f, Type w)										\
	: x(f.x), y(f.y), z(f.z), w(w)												\
{																				\
}																				\
																				\
Name##4::Name##4(Type x, const Name##3& f)										\
	: x(x), y(f.x), z(f.y), w(f.z)												\
{																				\
}																				\
																				\
Name##4::Name##4(const Name##4& f)												\
	: xy(f.xy), zw(f.zw)														\
{																				\
}																				\
																				\
std::string Name##4::ToString() const											\
{																				\
	std::stringstream ss;														\
	ss << "(" << x << ", " << y << ", " << z << ", " << w << ")";				\
	return ss.str();															\
}																				\
																				\
Type Name##4::DotProduct(const Name##4& f1, const Name##4& f2)					\
{																				\
	return f1.x * f2.x + f1.y * f2.y + f1.z * f2.z + f1.w * f2.w;				\
}																				\
																				\
Name##4& Name##4::operator=(const Name##4& other)								\
{																				\
	if (this == &other)															\
		return *this; 															\
																				\
	data = other.data;															\
	return *this;																\
}																				\
																				\
bool Name##4::operator==(const Name##4& other) const							\
{																				\
	return x == other.x && y == other.y && z == other.z && w == other.w;		\
}																				\
																				\
bool Name##4::operator!=(const Name##4& other) const							\
{																				\
	return !(x == other.x && y == other.y && z == other.z && w == other.w);		\
}																				\
																				\
Name##4 Name##4::operator+(const Name##4& other) const							\
{																				\
	return Name##4(x + other.x, y + other.y, z + other.z, w + other.w);			\
}																				\
																				\
Name##4 Name##4::operator-(const Name##4& other) const							\
{																				\
	return Name##4(x - other.x, y - other.y, z - other.z, w - other.w);			\
}																				\
																				\
Type Name##4::operator*(const Name##4& other) const								\
{																				\
	return DotProduct(*this, other);											\
}																				\
																				\
Type& Name##4::operator[](size_t index)											\
{																				\
	return list[index];															\
}																				\
																				\
const Type& Name##4::operator[](size_t index) const								\
{																				\
	return list[index];															\
}																				\
																				\
Name##4 operator*(const Name##4& f4, Type dot)									\
{																				\
	return Name##4(f4.x * dot, f4.y * dot, f4.z * dot, f4.w * dot);				\
}																				\
																				\
Name##4 operator*(Type dot, const Name##4& f4)									\
{																				\
	return f4 * dot;															\
}																				\
																				\
std::ostream& operator<<(std::ostream& os, const Name##4& f4)					\
{																				\
	os << f4.ToString();														\
	return os;																	\
}																				\
																				\
Type* Name##4::ToPtr()															\
{																				\
	return &x;																	\
}																				\
																				\
const Type* Name##4::ToPtr() const															\
{																				\
	return &x;																		\
}
