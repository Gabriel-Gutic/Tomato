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
		
		if (entity->HasComponent<TransformComponent>())
		{
			auto& tran = entity->GetComponent<TransformComponent>();
			EncodeTransform(out, tran);
		}

		if (entity->HasComponent<MeshRendererComponent>())
		{
			auto& render = entity->GetComponent<MeshRendererComponent>();
			EncodeMeshRenderer(out, render);
		}

		out << YAML::EndMap;
	}

	void SceneSerializer::Serialize()
	{
		YAML::Emitter out;

		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << m_SceneName;
		out << YAML::Key << "MainCamera" << YAML::Value << YAML::BeginMap;
		EncodeCamera(out, App::GetScene(m_SceneName)->GetCamera()->GetComponent<CameraComponent>());
		EncodeTransform(out, App::GetScene(m_SceneName)->GetCamera()->GetComponent<TransformComponent>());
		out << YAML::EndMap;

		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginMap;
		for (const auto& [name, entity] : App::GetScene(m_SceneName)->GetEntities())
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

		const auto& mainCamera = data["MainCamera"];
		if (mainCamera)
		{
			auto& cam = App::GetScene(m_SceneName)->GetCamera();

			auto& camera = cam->GetComponent<CameraComponent>();
			auto& tran = cam->GetComponent<TransformComponent>();

			if (mainCamera["Camera"])
				camera = DecodeCamera(mainCamera["Camera"]);

			if (mainCamera["Transform"])
				tran = DecodeTransform(mainCamera["Transform"]);
		}

		const auto& entities = data["Entities"];

		if (entities)
		{
			for (const auto& entity : entities)
			{
				std::string name = entity.first.as<std::string>();
				TOMATO_PRINT(name);
				auto& ent = App::GetScenes()[m_SceneName]->PushEntity(name, std::make_shared<Entity>());
				auto& entity_data = entity.second;
				
				if (entity_data)
				{
					for (const auto& comp : entity_data)
					{
						std::string name_c = comp.first.as<std::string>();
						if (name_c == "Transform")
						{
							auto tran = DecodeTransform(comp.second);
							ent->ReplaceComponent<TransformComponent>(tran.Position, tran.Scale, tran.Rotation);
						}
						else if (name_c == "MeshRenderer")
						{
							auto rend = DecodeMeshRenderer(comp.second);
							ent->ReplaceComponent<MeshRendererComponent>(rend.Sprite, rend.Color, rend.mesh);
						}
					}
				}
			}
		}
	}
}