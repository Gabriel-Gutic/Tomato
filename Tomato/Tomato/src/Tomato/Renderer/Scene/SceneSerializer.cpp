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

	void SceneSerializer::SerializeObject(YAML::Emitter& out, const std::shared_ptr<Object>& object)
	{
		out << YAML::BeginMap;
		
		//if (object->HasComponent<Transform>())
		//{
		//
		//}

		out << YAML::EndMap;
	}

	void SceneSerializer::Serialize()
	{
		YAML::Emitter out;

		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << m_SceneName;
		out << YAML::Key << "Objects" << YAML::Value << YAML::BeginSeq;
		//for (const auto& [name, obj] : App::GetScenes()[m_SceneName]->GetObjects())
		//{
		//	if (!obj)
		//		continue;
		//	SerializeObject(out, obj);
		//}
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream output(m_FilePath.c_str());
		output << out.c_str();
	}

	void SceneSerializer::Deserialize()
	{
		TOMATO_PRINT("Deserialization for scene '{0}'", m_SceneName);

		for (YAML::const_iterator it = m_Data["Objects"].begin(); it != m_Data["Objects"].end(); ++it)
		{
			std::string name = it->first.as<std::string>();
			std::string type = it->second["Type"].as<std::string>();

			//if (type == "Quad")
			//{
			//	Quad quad = it->second["Data"].as<Quad>();
			//	App::GetScenes()[m_SceneName]->PushObject(name, std::make_shared<Quad>(quad));
			//}
			//else if (type == "Triangle")
			//{
			//	Triangle triangle = it->second["Data"].as<Triangle>();
			//	App::GetScenes()[m_SceneName]->PushObject(name, std::make_shared<Triangle>(triangle));
			//}
			//else if (type == "Polygon")
			//{
			//	Polygon poly = it->second["Data"].as<Polygon>();
			//	App::GetScenes()[m_SceneName]->PushObject(name, std::make_shared<Polygon>(poly));
			//}
			//else if (type == "Circle")
			//{
			//	Circle circle = it->second["Data"].as<Circle>();
			//	App::GetScenes()[m_SceneName]->PushObject(name, std::make_shared<Circle>(circle));
			//}
		}
	}
}