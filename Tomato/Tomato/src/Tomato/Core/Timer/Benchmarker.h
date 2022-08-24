#pragma once
#include "Timer.h"


namespace Tomato
{
	class Benchmarker
	{
	public:
		Benchmarker(std::string_view name);
		~Benchmarker();

		void Write();

		static void StartSession(std::string_view category, std::string_view outputPath);
		static void EndSession();
	private:
		bool isWritten;
		Timer m_Timer;
		std::string m_Name;
	};
}

#ifdef DEBUG 
#define TOMATO_BENCHMARKING
#endif
#ifdef TOMATO_BENCHMARKING

#define TOMATO_BENCHMARKING_START_SESSION(x, y) Tomato::Benchmarker::StartSession(x, y)
#define TOMATO_BENCHMARKING_END_SESSION() Tomato::Benchmarker::EndSession()
#define TOMATO_BENCHMARKING_NAME(name) Tomato::Benchmarker benchmarker = Tomato::Benchmarker(name)
#define TOMATO_BENCHMARKING_FUNCTION() TOMATO_BENCHMARKING_NAME(__FUNCSIG__)

#define BENCHMARKING_START_SESSION(x, y) Tomato::Benchmarker::StartSession(x, y)
#define BENCHMARKING_END_SESSION() Tomato::Benchmarker::EndSession()
#define BENCHMARKING_NAME(name) Tomato::Benchmarker benchmarker = Tomato::Benchmarker(name)
#define BENCHMARKING_FUNCTION() TOMATO_BENCHMARKING_NAME(__FUNCSIG__)

#else

#define TOMATO_BENCHMARKING_START_SESSION(x, y)
#define TOMATO_BENCHMARKING_END_SESSION()
#define TOMATO_BENCHMARKING_NAME(name) 
#define TOMATO_BENCHMARKING_FUNCTION()

#define BENCHMARKING_START_SESSION(x, y)
#define BENCHMARKING_END_SESSION()
#define BENCHMARKING_NAME(name)
#define BENCHMARKING_FUNCTION()

#endif

