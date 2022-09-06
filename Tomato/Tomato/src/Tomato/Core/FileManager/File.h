#pragma once


namespace Tomato
{
	enum class FileType
	{
		Read = 0x01,
		Write = 0x02,
		WriteRead = Write | Read,
		Append = 0x08,
	};

	class File
	{
	public:
		File(std::string_view path, FileType type);
		~File();


		void Open();
		void Close();

		void Seek(unsigned int pos) const;
		bool EndOfFile() const;
		std::string Read();
		std::string ReadLine();
		std::vector<std::string> ReadLines();
		void Write(std::string_view data);
		void WriteLine(std::string_view line);
		void Append(std::string_view data);
		void AppendLine(std::string_view line);

		static File Create(std::string_view path, FileType type);
		static bool Exist(std::string_view path);
		static std::optional<std::string> Read(std::string_view source);
	private:
		std::string m_Path;
		FileType m_Type;
		bool isClosed;
		std::unique_ptr<std::fstream> m_Buffer;
	};
}
