#include "pchTomato.h"
#include "SceneSerializer.h"

#include "Core/App/App.h"

#include "Component/Component.h"


namespace Tomato
{
	SceneSerializer::SceneSerializer(std::string_view sceneName, std::string_view filePath)
		:Serializer(filePath), m_SceneName(sceneName)
	{
	}

	void SceneSerializer::SerializeEntity(YAML::Emitter& out, const std::shared_ptr<Entity>& entity)
	{
		out << YAML::BeginMap;
		
		if (entity->HasComponent<Component::Transform>())
		{
			auto& tran = entity->GetComponent<Component::Transform>();
			out << YAML::Key << "Transform"
				<< YAML::Value << YAML::BeginMap
				<< YAML::Key << "Position" << YAML::Value;
			EncodeFloat3(out, tran.Position);
			out << YAML::Key << "Scale" << YAML::Value;
			EncodeFloat3(out, tran.Scale);
			out << YAML::Key << "Rotation" << YAML::Value;
			EncodeFloat3(out, tran.Rotation);
			out	<< YAML::EndMap;
		}
		if (entity->HasComponent<Component::Renderer>())
		{
			auto& render = entity->GetComponent<Component::Renderer>();
			out << YAML::Key << "Renderer" << YAML::Value << YAML::BeginMap
				<< YAML::Key << "Sprite" << YAML::Value << render.Sprite
				<< YAML::Key << "Color" << YAML::Value;
			EncodeFloat4(out, render.Color);
			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}

	void SceneSerializer::Serialize()
	{
		YAML::Emitter out;

		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << m_SceneName;
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginMap;
		for (const auto& [name, entity] : App::GetScenes()[m_SceneName]->GetEntities())
		{
			if (!entity)
				continue;
			out << YAML::Key << name << YAML::Value;
			SerializeEntity(out, entity);
		}
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream output(m_FilePath.c_str());
		output << out.c_str();
		output.close();
	}

	void SceneSerializer::Deserialize()
	{
		TOMATO_PRINT("Deserialization for scene '{0}'", m_SceneName);

		YAML::Node data = YAML::LoadFile(m_FilePath);

		if (!data["Scene"])
		{
			TOMATO_PRINT("Failed to deserialize scene '{0}'", m_SceneName);
			return;
		}

		std::string new_name = data["Scene"].as<std::string>();
		if (m_SceneName != new_name)
		{
			App::SetSceneName(m_SceneName, new_name);
			m_SceneName = new_name;
		}

		auto entities = data["Entities"];

		if (entities)
		{
			for (const auto& entity : entities)
			{
				std::string name = entity.first.as<std::string>();
				auto& ent = App::GetScenes()[m_SceneName]->PushEntity(name, std::make_shared<Entity>());
				auto entity_data = entity.second;
				
				if (entity_data)
				{
					for (const auto& comp : entity_data)
					{
						std::string name_c = comp.first.as<std::string>();
						if (name_c == "Transform")
						{
							auto tran = DecodeTransform(comp.second);
							TOMATO_PRINT(tran.Position.ToString());
							ent->AddComponent<Component::Transform>(tran.Position, tran.Scale, tran.Rotation);
						}
						else if (name_c == "Renderer")
						{
							auto rend = DecodeRenderer(comp.second);
							ent->AddComponent<Component::Renderer>(rend.Sprite, rend.Color);
						}
					}
				}
			}
		}
	}
}