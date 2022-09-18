#include "pch.h"

class Layer3D : public Tomato::Layer
{
public:
	Layer3D()
	{
		Tomato::App::GetWindow()->SetTitle("Tomato3D");
		Tomato::GUI::ShowDockspace();
	}

	void OnUpdate(float dt)
	{
		float angle = m_Timer.GetMilliseconds() / 10.0f;
		Tomato::Mat4 rot = Tomato::Quaternion::Rotation(angle, angle, angle).ToMat4();
		Tomato::Renderer3D::Get()->Draw(Tomato::Mesh::Cube(), rot);

		auto& camera = Tomato::App::GetCurrentCamera()->GetComponent<Tomato::CameraComponent>();
		auto& tran = Tomato::App::GetCurrentCamera()->GetComponent<Tomato::TransformComponent>();

		const auto& window = Tomato::App::GetWindow();

		if (m_CurrentCameraProjection == 0)
			camera.SetOrthographicProjection(-window->GetAspectRatio() * m_CameraOrthoSize, window->GetAspectRatio() * m_CameraOrthoSize, -m_CameraOrthoSize, m_CameraOrthoSize, 0.1f, 100.0f);
		else
			camera.SetPerspectiveProjection(45.0f, window->GetAspectRatio(), 0.1f, 100.0f);

		float cameraSpeed = m_CameraSpeed * dt;
		if (Tomato::Input::Keyboard(TOMATO_KEY_LEFT))
		{
			tran.Position.x -= cameraSpeed;
			camera.Target.x -= 2 * cameraSpeed;
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_RIGHT))
		{
			tran.Position.x += cameraSpeed;
			camera.Target.x += 2 * cameraSpeed;
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_UP))
		{
			tran.Position.y += cameraSpeed;
			camera.Target.y += 2 * cameraSpeed;
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_DOWN))
		{
			tran.Position.y -= cameraSpeed;
			camera.Target.y -= 2 * cameraSpeed;
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_NUMPAD_8))
		{
			tran.Position.z -= cameraSpeed;
			camera.Target.z -= 2 * cameraSpeed;
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_NUMPAD_2))
		{
			tran.Position.z += cameraSpeed;
			camera.Target.z += 2 * cameraSpeed;
		}

		if (Tomato::Input::Keyboard(TOMATO_KEY_MINUS))
		{
			window->SetFullscreen(true);
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_EQUAL))
		{
			window->SetFullscreen(false);
		}
	}

	virtual void OnGUI() override
	{
		bool show_demo_window = true;
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
	}
private:
	int m_CurrentCameraProjection = 1;

	float m_CameraSpeed = 3.0f;
	float m_CameraOrthoSize = 1.0f;
	float m_CameraFOV = 45.0f;

	Tomato::Timer m_Timer;
};


class Tomato3D : public Tomato::App
{
public:
	Tomato3D(const std::unordered_map<std::string, std::any>& args)
		:App(args)
	{
		auto& scene = this->CreateScene("3D Scene");
		scene->PushLayer(new Layer3D());
	}
	virtual ~Tomato3D() override = default;
};

Tomato::App* Tomato::App::Create(const std::unordered_map<std::string, std::any>& args)
{
	return new Tomato3D(args);
}