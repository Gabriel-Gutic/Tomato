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
			file.Close();
		}
	}
}