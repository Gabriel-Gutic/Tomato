#pragma once


namespace Tomato
{
	class Serializer
	{
	public:
		Serializer(std::string_view filePath);
		virtual ~Serializer();

		virtual void Serialize(){};
		virtual void Deserialize(){};
	protected:
		std::string m_FilePath;
		YAML::Node m_Data;
	};
}
