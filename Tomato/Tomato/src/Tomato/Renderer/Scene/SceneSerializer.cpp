#include "pchTomato.h"
#include "SceneSerializer.h"

#include "Core/App/App.h"
#include "Object/2D/Object2D.h"

#include "Component/Transform.h"
#include "Component/Color.h"


namespace Tomato
{
	SceneSerializer::SceneSerializer(std::string_view sceneName, std::string_view filePath)
		:Serializer(filePath), m_SceneName(sceneName)
	{
	}

	void SceneSerializer::SerializeEntity(YAML::Emitter& out, const std::shared_ptr<Entity>& entity)
	{
		out << YAML::BeginMap;
		
		if (entity->HasComponent<Transform>())
		{
			auto& tran = entity->GetComponent<Transform>();
			out << YAML::Key << "Transform"
				<< YAML::Value << YAML::BeginMap
				<< YAML::Key << "Position" << YAML::Value << YAML::BeginSeq
				<< tran.Position.x << tran.Position.y << tran.Position.z
				<< YAML::EndSeq
				<< YAML::Key << "Scale" << YAML::Value << YAML::BeginSeq
				<< tran.Scale.x << tran.Scale.y << tran.Scale.z
				<< YAML::EndSeq
				<< YAML::Key << "Rotation" << YAML::Value << YAML::BeginSeq
				<< tran.Rotation.x << tran.Rotation.y << tran.Rotation.z
				<< YAML::EndSeq
				<< YAML::EndMap;
		}
		if (entity->HasComponent<Color>())
		{
			auto& color = entity->GetComponent<Color>();
			out << YAML::Key << "Color" << YAML::Value << YAML::BeginMap
				<< YAML::Key << "Red" << YAML::Value << color.Red
				<< YAML::Key << "Green" << YAML::Value << color.Green
				<< YAML::Key << "Blue" << YAML::Value << color.Blue
				<< YAML::Key << "Alpha" << YAML::Value << color.Alpha
				<< YAML::EndMap;
		}

		out << YAML::EndMap;
	}

	void SceneSerializer::Serialize()
	{
		YAML::Emitter out;

		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << m_SceneName;
		out << YAML::Key << "Objects" << YAML::Value << YAML::BeginMap;
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

		//for (YAML::const_iterator it = m_Data["Objects"].begin(); it != m_Data["Objects"].end(); ++it)
		//{
		//	std::string name = it->first.as<std::string>();
		//	std::string type = it->second["Type"].as<std::string>();

		//	//if (type == "Quad")
		//	//{
		//	//	Quad quad = it->second["Data"].as<Quad>();
		//	//	App::GetScenes()[m_SceneName]->PushObject(name, std::make_shared<Quad>(quad));
		//	//}
		//	//else if (type == "Triangle")
		//	//{
		//	//	Triangle triangle = it->second["Data"].as<Triangle>();
		//	//	App::GetScenes()[m_SceneName]->PushObject(name, std::make_shared<Triangle>(triangle));
		//	//}
		//	//else if (type == "Polygon")
		//	//{
		//	//	Polygon poly = it->second["Data"].as<Polygon>();
		//	//	App::GetScenes()[m_SceneName]->PushObject(name, std::make_shared<Polygon>(poly));
		//	//}
		//	//else if (type == "Circle")
		//	//{
		//	//	Circle circle = it->second["Data"].as<Circle>();
		//	//	App::GetScenes()[m_SceneName]->PushObject(name, std::make_shared<Circle>(circle));
		//	//}
		//}
	}
}