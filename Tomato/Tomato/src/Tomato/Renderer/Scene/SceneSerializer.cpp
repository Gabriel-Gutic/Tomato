#include "pchTomato.h"
#include "SceneSerializer.h"

#include "Core/App/App.h"
#include "Object/2D/Object2D.h"


namespace Tomato
{
	SceneSerializer::SceneSerializer(std::string_view sceneName, std::string_view filePath)
		:Serializer(filePath), m_SceneName(sceneName)
	{
	}

	void SceneSerializer::Serialize()
	{
		for (const auto& [name, obj] : App::GetScenes()[m_SceneName]->GetObjects())
		{
			if (auto triangle = Object::Cast<Triangle>(obj))
			{
				m_Data["Objects"][name]["Type"] = "Triangle";
				m_Data["Objects"][name]["Data"] = *triangle;
			}
			else if (auto quad = Object::Cast<Quad>(obj))
			{
				m_Data["Objects"][name]["Type"] = "Quad";
				m_Data["Objects"][name]["Data"] = *quad;
			}
			else if (auto poly = Object::Cast<Polygon>(obj))
			{
				m_Data["Objects"][name]["Type"] = "Polygon";
				m_Data["Objects"][name]["Data"] = *poly;
			}
			//else if (auto circle = Object::Cast<Circle>(obj))
			//{
			//	m_Data["Objects"][name]["Type"] = "Circle";
			//	m_Data["Objects"][name]["Data"] = *circle;
			//}
		}
	}

	void SceneSerializer::Deserialize()
	{
		TOMATO_PRINT("Deserialization for scene '{0}'", m_SceneName);

		for (YAML::const_iterator it = m_Data["Objects"].begin(); it != m_Data["Objects"].end(); ++it)
		{
			std::string name = it->first.as<std::string>();
			std::string type = it->second["Type"].as<std::string>();

			if (type == "Quad")
			{
				Quad quad = it->second["Data"].as<Quad>();
				App::GetScenes()[m_SceneName]->PushObject(name, std::make_shared<Quad>(quad));
			}
			else if (type == "Triangle")
			{
				Triangle triangle = it->second["Data"].as<Triangle>();
				App::GetScenes()[m_SceneName]->PushObject(name, std::make_shared<Triangle>(triangle));
			}
			else if (type == "Polygon")
			{
				Polygon poly = it->second["Data"].as<Polygon>();
				App::GetScenes()[m_SceneName]->PushObject(name, std::make_shared<Polygon>(poly));
			}
			//else if (type == "Circle")
			//{
			//	Circle circle = it->second["Data"].as<Circle>();
			//	App::GetScenes()[m_SceneName]->PushObject(name, std::make_shared<Circle>(circle));
			//}
		}
	}
}