#include "pchTomato.h"
#include "Serializer.h"


namespace Tomato
{
	Serializer::Serializer(std::string_view filePath)
		:m_FilePath(filePath)
	{
		if (!File::Exist(m_FilePath))
		{
			File file = File(m_FilePath, FileType::Write);
		}
		m_Data = YAML::LoadFile(m_FilePath);
	}

	Serializer::~Serializer()
	{
		std::fstream output(m_FilePath, std::ios::out);
		if (output)
		{
			output << m_Data;
			output.close();
		}
	}

}