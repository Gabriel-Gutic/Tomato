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

		static void EncodeTransform(YAML::Emitter& out, const TransformComponent& tran);
		static void EncodeMeshRenderer(YAML::Emitter& out, const MeshRendererComponent& rend);
		static void EncodeCamera(YAML::Emitter& out, const CameraComponent& cam);
		static TransformComponent DecodeTransform(const YAML::Node& node);
		static MeshRendererComponent DecodeMeshRenderer(const YAML::Node& node);
		static CameraComponent DecodeCamera(const YAML::Node& node);
	protected:
		std::string m_FilePath;
	};
}
