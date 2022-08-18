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
				//m_Data[name] = *triangle;
			}
			else if (auto quad = Object::Cast<Quad>(obj))
			{
				m_Data[name] = *quad;
			}
			else if (auto poly = Object::Cast<Polygon>(obj))
			{
				//m_Data[name] = *poly;
			}
			else if (auto circle = Object::Cast<Circle>(obj))
			{
				//m_Data[name] = *circle;
			}
		}
	}

	void SceneSerializer::Deserialize()
	{
		TOMATO_PRINT("Deserialize Scene '{0}'", m_SceneName);
	}
}