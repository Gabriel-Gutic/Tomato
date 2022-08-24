#pragma once
#include "Renderer/Scene/Component/Component.h"


namespace Tomato
{
	class Serializer
	{
	public:
		Serializer(std::string_view filePath);
		virtual ~Serializer() = default;

		virtual void Serialize() = 0;
		virtual void Deserialize() = 0;

		static void EncodeFloat2(YAML::Emitter& out, const Float2& f2);
		static void EncodeFloat3(YAML::Emitter& out, const Float3& f3);
		static void EncodeFloat4(YAML::Emitter& out, const Float4& f4);
		static Float2 DecodeFloat2(const YAML::Node& node);
		static Float3 DecodeFloat3(const YAML::Node& node);
		static Float4 DecodeFloat4(const YAML::Node& node);

		static void EncodeTransform(YAML::Emitter& out, const Component::Transform& tran);
		static void EncodeRenderer(YAML::Emitter& out, const Component::Renderer& rend);
		static Component::Transform DecodeTransform(const YAML::Node& node);
		static Component::Renderer DecodeRenderer(const YAML::Node& node);
	protected:
		std::string m_FilePath;
	};
}
