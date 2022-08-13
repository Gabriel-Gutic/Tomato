#pragma once
#include "Timer.h"


namespace Tomato
{
	class Benchmarker
	{
	public:
		Benchmarker();
		~Benchmarker();

		void Write() const;

		static void StartSession(std::string_view category, std::string_view outputPath);
		static void EndSession();
	private:
		bool isWritten;
		Timer m_Timer;
	};
}


