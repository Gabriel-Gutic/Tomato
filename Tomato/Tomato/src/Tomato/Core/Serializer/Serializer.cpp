#include "pchTomato.h"
#include "Serializer.h"


namespace Tomato
{
	Serializer::Serializer(std::string_view filePath)
		:m_FilePath(filePath)
	{
		TOMATO_ASSERT(File::Exist(m_FilePath), "File {0} doesn't exist!", m_FilePath);
		m_Data = YAML::Load(m_FilePath);
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