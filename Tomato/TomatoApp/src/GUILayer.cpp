#include "GUILayer.h"

GUILayer::GUILayer()
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

	camera->SetPerspectiveProjection(m_FOV, window->GetAspectRatio(), 0.1f, 100.0f);
	//camera->SetOrthographicProjection(-window->GetAspectRatio(), window->GetAspectRatio(), -1.0f, 1.0f, 0.1f, 100.0f);

	if (Tomato::Input::Keyboard(TOMATO_KEY_LEFT))
		camera->MoveX(-m_Speed);
	if (Tomato::Input::Keyboard(TOMATO_KEY_RIGHT))
		camera->MoveX(m_Speed);
	if (Tomato::Input::Keyboard(TOMATO_KEY_UP))
		camera->MoveY(m_Speed);
	if (Tomato::Input::Keyboard(TOMATO_KEY_DOWN))
		camera->MoveY(-m_Speed);
	if (Tomato::Input::Keyboard(TOMATO_KEY_KP_8))
		camera->MoveZ(-m_Speed);
	if (Tomato::Input::Keyboard(TOMATO_KEY_KP_2))
		camera->MoveZ(m_Speed);
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

	if (ImGui::ListBox("Scene", &m_CurrentSceneIndex, scenes.data(), scenes.size()));
	{
		Tomato::App::SetCurrentScene(scenes[m_CurrentSceneIndex]);
	}
	ImGui::SliderFloat3("Camera Rotation", &m_CameraRotation[0], -90.0f, 90.0f);
	ImGui::ColorPicker4("Background Color", &m_BackgroundColor[0]);

	ImGui::End();
}

void GUILayer::OnEvent(const Tomato::Event& e)
{
	if (e.GetType() == Tomato::EventType::Wheel)
	{
		auto ev = Tomato::Event::Cast<Tomato::WheelEvent>(e);

		m_FOV += (Tomato::Float)ev.GetValue();
	}
}
