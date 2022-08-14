#include "pchTomato.h"
#include "Benchmarker.h"


namespace Tomato
{
	struct BenchmarkerData
	{
		static ULong Counter;
		static std::unique_ptr<File> ResultFile;
		static ULong Start;
		static std::string Category;
	};

	std::unique_ptr<File> BenchmarkerData::ResultFile = nullptr;
	ULong BenchmarkerData::Counter = 0;
	ULong BenchmarkerData::Start = 0;
	std::string BenchmarkerData::Category = "";

	Benchmarker::Benchmarker(std::string_view name)
		:isWritten(false), m_Timer(Timer()), m_Name(name)
	{
	}

	Benchmarker::~Benchmarker()
	{
		if (!isWritten)
			Write();
	}

	void Benchmarker::Write()
	{
		const ULong duration = m_Timer.GetMicroseconds();

		if (BenchmarkerData::Counter != 0)
			BenchmarkerData::ResultFile->WriteLine("    ,");
		BenchmarkerData::ResultFile->WriteLine("    {");
		BenchmarkerData::ResultFile->WriteLine("      \"cat\": \"" + BenchmarkerData::Category + "\",");
		BenchmarkerData::ResultFile->WriteLine("      \"name\": \"" + m_Name + "\",");
		BenchmarkerData::ResultFile->WriteLine("      \"dur\": " + std::to_string(duration) + ",");
		BenchmarkerData::ResultFile->WriteLine("      \"pid\": 0,");
		BenchmarkerData::ResultFile->WriteLine("      \"tid\": " + std::to_string(0) + ",");
		BenchmarkerData::ResultFile->WriteLine("      \"ts\": " + std::to_string(BenchmarkerData::Start) + ",");
		BenchmarkerData::ResultFile->WriteLine("      \"ph\": \"X\"");
		BenchmarkerData::ResultFile->WriteLine("    }");

		BenchmarkerData::Start += duration;
		BenchmarkerData::Counter++;

		isWritten = true;
	}

	void Benchmarker::StartSession(std::string_view category, std::string_view outputPath)
	{
		BenchmarkerData::Category = category;
		BenchmarkerData::Counter = 0;

		BenchmarkerData::ResultFile = std::make_unique<File>(outputPath, FileType::Write);
		BenchmarkerData::ResultFile->WriteLine("{");
		BenchmarkerData::ResultFile->WriteLine("  \"otherData\": {},");
		BenchmarkerData::ResultFile->WriteLine("  \"traceEvents\": ");
		BenchmarkerData::ResultFile->WriteLine("  [");
	}

	void Benchmarker::EndSession()
	{
		BenchmarkerData::ResultFile->WriteLine("  ]");
		BenchmarkerData::ResultFile->WriteLine("}");

		BenchmarkerData::ResultFile->Close();
		BenchmarkerData::ResultFile = nullptr;
	}
}