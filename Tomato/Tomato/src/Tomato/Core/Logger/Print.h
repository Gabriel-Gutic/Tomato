#pragma once
#include "Logger.h"


#ifdef DEBUG

#define PRINT(...)			Tomato::Logger::GetCore()->info(__VA_ARGS__)
#define ERROR(...)			Tomato::Logger::GetCore()->error(__VA_ARGS__)
#define WARNING(...)	    Tomato::Logger::GetCore()->warn(__VA_ARGS__)
#define TRACE(...)			Tomato::Logger::GetCore()->trace(__VA_ARGS__)
#define ASSERT(x, ...)	    if (!(x)) { ERROR(__VA_ARGS__); __debugbreak(); }


#define TOMATO_PRINT(...)			Tomato::Logger::GetCore()->info(__VA_ARGS__)
#define TOMATO_ERROR(...)			Tomato::Logger::GetCore()->error(__VA_ARGS__)
#define TOMATO_WARNING(...)			Tomato::Logger::GetCore()->warn(__VA_ARGS__)
#define TOMATO_TRACE(...)			Tomato::Logger::GetCore()->trace(__VA_ARGS__)
#define TOMATO_ASSERT(x, ...)	    if (!(x)) { ERROR(__VA_ARGS__); __debugbreak(); }

#else

#define PRINT(...)	
#define ERROR(...)	
#define WARNING(...)
#define TRACE(...)	
#define ASSERT(x, ...)


#define TOMATO_PRINT(...)	
#define TOMATO_ERROR(...)	
#define TOMATO_WARNING(...)	
#define TOMATO_TRACE(...)	
#define TOMATO_ASSERT(x, ...)


#endif // DEBUG