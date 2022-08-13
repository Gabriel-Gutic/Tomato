#include "pchTomato.h"
#include "File.h"


namespace Tomato
{
	File::File(std::string_view path, FileType type)
		:m_Path(path), m_Type(type), isClosed(true)
	{
		Open();
	}

	File::~File()
	{
		Close();
	}

	void File::Open()
	{
		if (isClosed)
		{
			TOMATO_ASSERT(Exist(m_Path) || m_Type != FileType::Read, "File {0} doesn't exist!", m_Path);
			m_Buffer = std::make_unique<std::fstream>(m_Path.c_str(), (int)m_Type | std::ios::binary);
			isClosed = false;
		}
	}

	void File::Close()
	{
		if (!isClosed)
		{
			m_Buffer->close();
			isClosed = true;
		}
	}

	void File::Seek(UInt pos) const
	{
		m_Buffer->seekg(pos);
	}

	Bool File::EndOfFile() const
	{
		return m_Buffer->eof();
	}

	std::string File::Read()
	{
		TOMATO_ASSERT(!isClosed, "The file {0} is closed", m_Path);
		bool valid = (m_Type == FileType::Read || m_Type == FileType::WriteRead);
		TOMATO_ASSERT(valid, "You can't read from file {0}", m_Path);
		
		std::string result;
		m_Buffer->seekg(0, std::ios::end);
		Long size = m_Buffer->tellg();
		if (size != -1)
		{
			result.resize(size);
			m_Buffer->seekg(0, std::ios::beg);
			m_Buffer->read(&result[0], size);

			//Remove Carriage Return On Windows
			result.erase(remove(result.begin(), result.end(), '\r'), result.end());

			return result;
		}
		return "";
	}

	std::string File::ReadLine()
	{
		TOMATO_ASSERT(!isClosed, "The file {0} is closed", m_Path);
		bool valid = (m_Type == FileType::Read || m_Type == FileType::WriteRead);
		TOMATO_ASSERT(valid, "You can't read from file {0}", m_Path);
		std::string line;
		getline(*m_Buffer, line);

		//Remove Carriage Return On Windows
		line.erase(remove(line.begin(), line.end(), '\r'), line.end());

		return line;
	}

	std::vector<std::string> File::ReadLines()
	{
		TOMATO_ASSERT(!isClosed, "The file {0} is closed", m_Path);
		bool valid = (m_Type == FileType::Read || m_Type == FileType::WriteRead);
		TOMATO_ASSERT(valid, "You can't read from file {0}", m_Path);

		std::vector<std::string> lines;
		Seek(0);
		while (!EndOfFile())
		{
			std::string line;
			getline(*m_Buffer, line);

			//Remove Carriage Return On Windows
			line.erase(remove(line.begin(), line.end(), '\r'), line.end());
			
			lines.push_back(line);
		}
		return lines;
	}

	void File::Write(std::string_view data)
	{
		TOMATO_ASSERT(!isClosed, "The file {0} is closed", m_Path);
		bool valid = (m_Type == FileType::Write || m_Type == FileType::WriteRead);
		TOMATO_ASSERT(valid, "You can't write to file {0}", m_Path);
	
		*m_Buffer << data;
	}

	void File::WriteLine(std::string_view line)
	{
		TOMATO_ASSERT(!isClosed, "The file {0} is closed", m_Path);
		bool valid = (m_Type == FileType::Write || m_Type == FileType::WriteRead);
		TOMATO_ASSERT(valid, "You can't write to file {0}", m_Path);

		*m_Buffer << line << '\n';
	}

	void File::Append(std::string_view data)
	{
		TOMATO_ASSERT(!isClosed, "The file {0} is closed", m_Path);
		bool valid = (m_Type == FileType::Append);
		TOMATO_ASSERT(valid, "You can't append to file {0}", m_Path);

		*m_Buffer << data;
	}

	void File::AppendLine(std::string_view line)
	{
		TOMATO_ASSERT(!isClosed, "The file {0} is closed", m_Path);
		bool valid = (m_Type == FileType::Append);
		TOMATO_ASSERT(valid, "You can't append to file {0}", m_Path);

		*m_Buffer << line << '\n';
	}

	File File::Create(std::string_view path, FileType type)
	{
		return File(path, type);
	}

	bool File::Exist(std::string_view path)
	{
		return std::filesystem::exists(path.data());
	}

	std::optional<std::string> File::Read(std::string_view source)
	{
		std::ifstream file(source.data());

		if (!file)
		{
			return {};
		}

		std::stringstream ss;
		ss << file.rdbuf();
		file.close();

		return ss.str();
	}
}


