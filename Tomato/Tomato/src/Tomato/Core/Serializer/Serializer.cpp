#include "pchTomato.h"
#include "Serializer.h"

#include "Renderer/Scene/Component/Component.h"


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

	void Serializer::EncodeFloat2(YAML::Emitter& out, const Float2& f2)
	{
		out << YAML::BeginSeq << f2.x << f2.y << YAML::EndSeq;
	}

	void Serializer::EncodeFloat3(YAML::Emitter& out, const Float3& f3)
	{
		out << YAML::BeginSeq << f3.x << f3.y << f3.z << YAML::EndSeq;
	}

	void Serializer::EncodeFloat4(YAML::Emitter& out, const Float4& f4)
	{
		out << YAML::BeginSeq << f4.x << f4.y << f4.z << f4.w << YAML::EndSeq;
	}

	Float2 Serializer::DecodeFloat2(const YAML::Node& node)
	{
		if (!node.IsSequence() or node.size() != 2)
		{
			TOMATO_ERROR("Invalid Node");
			return Float2();
		}

		return Float2(node[0].as<Float>(), node[1].as<Float>());
	}

	Float3 Serializer::DecodeFloat3(const YAML::Node& node)
	{
		if (!node.IsSequence() or node.size() != 3)
		{
			TOMATO_ERROR("Invalid Node");
			return Float3();
		}

		return Float3(node[0].as<Float>(), node[1].as<Float>(), node[2].as<Float>());
	}

	Float4 Serializer::DecodeFloat4(const YAML::Node& node)
	{
		if (!node.IsSequence() or node.size() != 4)
		{
			TOMATO_ERROR("Invalid Node");
			return Float4();
		}

		return Float4(node[0].as<Float>(), node[1].as<Float>(), node[2].as<Float>(), node[3].as<Float>());
	}

	void Serializer::EncodeTransform(YAML::Emitter& out, const Component::Transform& tran)
	{
		out << YAML::Key << "Transform" << YAML::Value << YAML::BeginMap;
		out << YAML::Key << "Position" << YAML::Value;
		EncodeFloat3(out, tran.Position);
		out << YAML::Key << "Scale" << YAML::Value;
		EncodeFloat3(out, tran.Scale);
		out << YAML::Key << "Rotation" << YAML::Value;
		EncodeFloat3(out, tran.Rotation);
	}

	void Serializer::EncodeRenderer(YAML::Emitter& out, const Component::Renderer& rend)
	{
		out << YAML::Key << "Renderer" << YAML::Value << YAML::BeginMap;
		out << YAML::Key << "Sprite" << YAML::Value << rend.Sprite;
		out << YAML::Key << "Color" << YAML::Value;
		EncodeFloat4(out, rend.Color);
	}

	Component::Transform Serializer::DecodeTransform(const YAML::Node& node)
	{
		if (!node.IsMap())
		{
			TOMATO_ERROR("Invalid Node");
		}
		Component::Transform tran;
		auto pos = node["Position"];
		if (pos)
			tran.Position = DecodeFloat3(pos);
		auto scale = node["Scale"];
		if (scale)
			tran.Scale = DecodeFloat3(scale);
		auto rot = node["Rotation"];
		if (rot)
			tran.Rotation = DecodeFloat3(rot);
		
		return tran;
	}

	Component::Renderer Serializer::DecodeRenderer(const YAML::Node& node)
	{
		if (!node.IsMap())
		{
			TOMATO_ERROR("Invalid Node");
		}
		Component::Renderer rend;

		auto sprite = node["Sprite"];
		if (sprite)
			rend.Sprite = sprite.as<std::string>();
		auto color = node["Color"];
		if (color)
			rend.Color = DecodeFloat4(color);

		return rend;
	}
}