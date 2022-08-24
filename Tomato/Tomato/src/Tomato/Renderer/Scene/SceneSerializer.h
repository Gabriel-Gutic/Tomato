#pragma once
#include "Scene.h"


namespace Tomato
{
	class SceneSerializer : public Serializer
	{
	public:
		SceneSerializer(std::string_view sceneName, std::string_view filePath);
		virtual ~SceneSerializer() override = default;

		static void SerializeEntity(YAML::Emitter& out, const std::shared_ptr<Entity>& entity);

		virtual void Serialize() override;
		virtual void Deserialize() override;
	private:
		std::string m_SceneName;
	};
}
