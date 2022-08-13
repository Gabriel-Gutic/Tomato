#include "Tomato.h"
#include "FileTests.h"


namespace Tomato::Tests
{
	void FileTests::Read()
	{
		//File  f = File("unexisting.txt", FileType::Read);

		File file = File("files/read.txt", FileType::Read);

		std::string text = file.Read();
		std::string result = R"(Hello World
Line 2
Line 3)";
		TOMATO_ASSERT(text.compare(result) == 0, "File::Read Test Failed!\nExpected result: {0}\nResult: {1}", result, text);
	
		TOMATO_PRINT("File::Read Test Passed!");
	}

	void FileTests::ReadLine()
	{
		File file = File("files/read.txt", FileType::Read);
		
		std::vector<std::string> lines;
		lines.reserve(3);
		while (!file.EndOfFile())
			lines.push_back(file.ReadLine());
		std::vector<std::string> expected_lines = { "Hello World", "Line 2", "Line 3" };
		bool equal = true;
		for (UInt i = 0; i < lines.size() && equal; i++)
			if (lines[i].compare(expected_lines[i]) != 0)
				equal = false;
		TOMATO_ASSERT(equal, "File::ReadLine Test Failed!\nExpected result: \n{0}\n{1}\n{2}\nResult: \n{3}\n{4}\n{5}", expected_lines[0], expected_lines[1], expected_lines[2], lines[0], lines[1], lines[2]);
		
		TOMATO_PRINT("File::ReadLine Test Passed!");
	}

	void FileTests::ReadLines()
	{
		File file = File("files/read.txt", FileType::Read);

		std::vector<std::string> lines = file.ReadLines();
		std::vector<std::string> expected_lines = { "Hello World", "Line 2", "Line 3" };
		bool equal = true;
		for (UInt i = 0; i < lines.size() && equal; i++)
			if (lines[i].compare(expected_lines[i]) != 0)
				equal = false;
		TOMATO_ASSERT(equal, "File::ReadLines Test Failed!\nExpected result: \n{0}\n{1}\n{2}\nResult: \n{3}\n{4}\n{5}", expected_lines[0], expected_lines[1], expected_lines[2], lines[0], lines[1], lines[2]);

		TOMATO_PRINT("File::ReadLines Test Passed!");
	}

	void FileTests::Write()
	{
		File file = File("files/write.txt", FileType::Write);

		file.Write(R"(
Hello World
Welcome Here
)");
		file.Write("Hello Again");

		TOMATO_PRINT("File::Write Test Passed!");
	}

	void FileTests::WriteLine()
	{
		File file = File("files/writeline.txt", FileType::Write);

		file.WriteLine("Line 1");
		file.WriteLine("Line 2");

		TOMATO_PRINT("File::WriteLine Test Passed!");
	}

	void FileTests::Append()
	{
		File file = File("files/append.txt", FileType::Append);

		file.Append(R"(
Hello World
Welcome Here
)");
		file.Append("Hello Again");

		TOMATO_PRINT("File::Append Test Passed!");
	}

	void FileTests::AppendLine()
	{
		File file = File("files/appendline.txt", FileType::Append);

		file.AppendLine("Line 1");
		file.AppendLine("Line 2");

		TOMATO_PRINT("File::AppendLine Test Passed!");
	}

}