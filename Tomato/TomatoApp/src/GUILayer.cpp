#include "GUILayer.h"

GUILayer::GUILayer()
	:m_BackgroundColor(Tomato::Float4(1.0f, 0.0f, 0.0f, 1.0f))
{
	Tomato::GUI::ShowDockspace();
	Tomato::GUI::ShowRenderWindow();
}

void GUILayer::OnUpdate(Tomato::Float dt)
{
	Tomato::Renderer::SetBackgroundColor(m_BackgroundColor);

	auto& camera = Tomato::App::GetCurrentCamera()->GetComponent<Tomato::CameraComponent>();
	auto& tran = Tomato::App::GetCurrentCamera()->GetComponent<Tomato::TransformComponent>();
	tran.Rotation = m_CameraRotation;

	const auto& window = Tomato::App::GetWindow();

	if (m_CurrentCameraProjection == 0)
		camera.SetOrthographicProjection(-window->GetAspectRatio() * m_CameraOrthoSize, window->GetAspectRatio() * m_CameraOrthoSize, -m_CameraOrthoSize, m_CameraOrthoSize, 0.1f, 100.0f);
	else 
		camera.SetPerspectiveProjection(m_CameraFOV, window->GetAspectRatio(), 0.1f, 100.0f);

	Tomato::Float cameraSpeed = m_CameraSpeed * dt;
	if (Tomato::Input::Keyboard(TOMATO_KEY_LEFT))
		tran.Position.x -= cameraSpeed;
	if (Tomato::Input::Keyboard(TOMATO_KEY_RIGHT))
		tran.Position.x += cameraSpeed;
	if (Tomato::Input::Keyboard(TOMATO_KEY_UP))
		tran.Position.y += cameraSpeed;
	if (Tomato::Input::Keyboard(TOMATO_KEY_DOWN))
		tran.Position.y -= cameraSpeed;
	if (Tomato::Input::Keyboard(TOMATO_KEY_KP_8))
		tran.Position.z += cameraSpeed;
	if (Tomato::Input::Keyboard(TOMATO_KEY_KP_2))
		tran.Position.z -= cameraSpeed;
}

void GUILayer::OnGUI()
{
	ImGui::Begin("Status");
	std::string fps = "FPS: " + Tomato::Math::ToString(Tomato::App::GetFPS());
	ImGui::Text(fps.c_str());
	std::string vertices = "Vertices: " + Tomato::Math::ToString(Tomato::Renderer::GetNumberOfVertices());
	ImGui::Text(vertices.c_str());
	ImGui::End();

	ImGui::Begin("ImGui Window");
	const auto& scene_map = Tomato::App::GetScenes();
	std::vector<const char*> scenes;
	scenes.reserve(scene_map.size());

	for (const auto& [name, scene] : scene_map)
		scenes.push_back(name.c_str());
	if (ImGui::Combo("Scene", &m_CurrentSceneIndex, scenes.data(), scenes.size()))
	{
		Tomato::App::SetCurrentScene(scenes[m_CurrentSceneIndex]);
	}

	std::array<const char*, 2> projs = { "Orthographic", "Perspective" };
	ImGui::Combo("Camera Projection", &m_CurrentCameraProjection, projs.data(), projs.size());

	ImGui::SliderFloat3("Camera Rotation", &m_CameraRotation[0], -90.0f, 90.0f);
	ImGui::ColorPicker4("Background Color", &m_BackgroundColor[0]);

	ImGui::End();

	auto& entities = Tomato::App::GetCurrentScene()->GetEntities();
	if (entities.size() > 0)
	{
		ImGui::Begin("Scene Hierarchy");

		static Tomato::UInt currentEntity = 0;
		if (currentEntity >= entities.size())
			currentEntity = 0;

		std::vector<std::string> entity_names;
		entity_names.resize(entities.size());

		Tomato::UInt i = 0;
		for (const auto& [name, entity] : entities)
		{
			entity_names[i++] = name;
		}

		if (ImGui::BeginCombo("##", entity_names[currentEntity].c_str()))
		{
			for (Tomato::UInt i = 0; i < entity_names.size(); i++)
			{
				bool is_selected = (entity_names[currentEntity] == entity_names[i]);
				if (ImGui::Selectable(entity_names[i].c_str(), is_selected))
					currentEntity = i;
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		ImGui::End();

		ImGui::Begin("Entity");
		ImGui::Text(entity_names[currentEntity].c_str());
		if (Tomato::App::GetCurrentScene()->GetEntity(entity_names[currentEntity])->HasComponent<Tomato::TransformComponent>())
		{
			Tomato::App::GetCurrentScene()->GetEntity(entity_names[currentEntity])->GetComponent<Tomato::TransformComponent>().ToImGui();
		}
		ImGui::End();
	}
}

void GUILayer::OnEvent(const Tomato::Event& e)
{
	if (e.GetType() == Tomato::EventType::Wheel)
	{
		auto ev = Tomato::Event::Cast<Tomato::WheelEvent>(e);

		if (m_CurrentCameraProjection == 1)
			m_CameraFOV += (Tomato::Float)ev.GetValue();
		else
			m_CameraOrthoSize += m_CameraSpeed * (Tomato::Float)ev.GetValue();
	}
}
