#pragma once


namespace Tomato
{
	class Serializer
	{
	public:
		Serializer(std::string_view filePath);
		virtual ~Serializer() = default;

		virtual void Serialize() = 0;
		virtual void Deserialize() = 0;
	protected:
		std::string m_FilePath;
	};
}
