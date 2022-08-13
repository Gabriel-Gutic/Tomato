#include "FileTestsLayer.h"

#include "FileTests.h"


namespace Tomato::Tests
{
	FileTestsLayer::FileTestsLayer()
	{
		FileTests::Read();
		FileTests::ReadLine();
		FileTests::ReadLines();
		FileTests::Write();
		FileTests::WriteLine();
		FileTests::Append();
		FileTests::AppendLine();
	}

}