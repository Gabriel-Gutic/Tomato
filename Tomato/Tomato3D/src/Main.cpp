#include "pch.h"

class Layer3D : public Tomato::Layer
{
public:
	Layer3D()
	{
		Tomato::App::GetWindow()->SetTitle("Tomato3D");
		//Tomato::GUI::ShowDockspace();
	}

	void OnUpdate(float dt)
	{
		Tomato::Renderer3D::Get()->Draw(Tomato::Mesh::Cube());

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
		if (Tomato::Input::Keyboard(TOMATO_KEY_KP_8))
		{
			tran.Position.z -= cameraSpeed;
			camera.Target.z -= 2 * cameraSpeed;
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_KP_2))
		{
			tran.Position.z += cameraSpeed;
			camera.Target.z += 2 * cameraSpeed;
		}

		if (Tomato::Input::Keyboard(TOMATO_KEY_Q))
		{
			window->SetFullscreen(true);
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_W))
		{
			window->SetFullscreen(false);
		}
	}
private:
	int m_CurrentCameraProjection = 1;

	float m_CameraSpeed = 3.0f;
	float m_CameraOrthoSize = 1.0f;
	float m_CameraFOV = 45.0f;
};


class Tomato3D : public Tomato::App
{
public:
	Tomato3D()
	{
		auto& scene = this->CreateScene("3D Scene");
		scene->PushLayer(new Layer3D());
	}
	virtual ~Tomato3D() override = default;
};

Tomato::App* Tomato::App::Create()
{
	return new Tomato3D();
}