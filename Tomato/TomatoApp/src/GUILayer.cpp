#include "GUILayer.h"

GUILayer::GUILayer()
	:m_BackgroundColor(Tomato::Float4(1.0f, 0.0f, 0.0f, 1.0f))
{
	Tomato::App::GetCurrentCamera()->MoveZ(1.0f);
	Tomato::GUI::ShowDockspace();
	Tomato::GUI::ShowRenderWindow();
}

void GUILayer::OnUpdate()
{
	Tomato::Renderer::SetBackgroundColor(m_BackgroundColor);

	const auto& camera = Tomato::App::GetCurrentCamera();
	camera->SetRotation(m_CameraRotation);

	const auto& window = Tomato::App::GetWindow();

	if (m_CurrentCameraProjection == 0)
		camera->SetOrthographicProjection(-window->GetAspectRatio() * m_CameraOrthoSize, window->GetAspectRatio() * m_CameraOrthoSize, -m_CameraOrthoSize, m_CameraOrthoSize, 0.1f, 100.0f);
	else 
		camera->SetPerspectiveProjection(m_CameraFOV, window->GetAspectRatio(), 0.1f, 100.0f);

	if (Tomato::Input::Keyboard(TOMATO_KEY_LEFT))
		camera->MoveX(-m_CameraSpeed);
	if (Tomato::Input::Keyboard(TOMATO_KEY_RIGHT))
		camera->MoveX(m_CameraSpeed);
	if (Tomato::Input::Keyboard(TOMATO_KEY_UP))
		camera->MoveY(m_CameraSpeed);
	if (Tomato::Input::Keyboard(TOMATO_KEY_DOWN))
		camera->MoveY(-m_CameraSpeed);
	if (Tomato::Input::Keyboard(TOMATO_KEY_KP_8))
		camera->MoveZ(-m_CameraSpeed);
	if (Tomato::Input::Keyboard(TOMATO_KEY_KP_2))
		camera->MoveZ(m_CameraSpeed);
}

void GUILayer::OnGUI()
{
	ImGui::Begin("ImGui Window");

	const auto& scene_map = Tomato::App::GetScenes();
	std::vector<const char*> scenes;
	scenes.reserve(scene_map.size());
	auto& current_scene = Tomato::App::GetCurrentSceneName();
	PRINT(current_scene);

	for (const auto& [name, scene] : scene_map)
		scenes.push_back(name.c_str());
	if (ImGui::Combo("Scene", &m_CurrentSceneIndex, scenes.data(), scenes.size()));
	{
		Tomato::App::SetCurrentScene(scenes[m_CurrentSceneIndex]);
	}

	std::array<const char*, 2> projs = { "Orthographic", "Perspective" };
	ImGui::Combo("Camera Projection", &m_CurrentCameraProjection, projs.data(), projs.size());

	ImGui::SliderFloat3("Camera Rotation", &m_CameraRotation[0], -90.0f, 90.0f);
	ImGui::ColorPicker4("Background Color", &m_BackgroundColor[0]);

	ImGui::End();
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
