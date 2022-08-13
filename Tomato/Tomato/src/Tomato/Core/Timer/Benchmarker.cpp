#include "pchTomato.h"
#include "Benchmarker.h"


namespace Tomato
{
	struct BenchmarkerData
	{
		static ULong Counter;
		static std::unique_ptr<std::fstream> File;
		static ULong Start;
		static std::string Category;
	};

	std::unique_ptr<std::fstream> BenchmarkerData::File = nullptr;
	ULong BenchmarkerData::Counter = 0;
	ULong BenchmarkerData::Start = 0;
	std::string BenchmarkerData::Category = "";

	Benchmarker::Benchmarker()
		:isWritten(false), m_Timer(Timer())
	{
	}

	Benchmarker::~Benchmarker()
	{
		if (!isWritten)
			Write();
	}

	void Benchmarker::Write() const
	{
		const ULong duration = m_Timer.GetMicroseconds();

		//*BenchmarkerData::File << "";

		BenchmarkerData::Start += duration;
		BenchmarkerData::Counter++;
	}

	void Benchmarker::StartSession(std::string_view category, std::string_view outputPath)
	{
		BenchmarkerData::Category = category;

		TOMATO_ASSERT(File::Exist(outputPath), "File {0} doesn't exist!", outputPath.data());
	
		
	}

	void Benchmarker::EndSession()
	{
	}
}