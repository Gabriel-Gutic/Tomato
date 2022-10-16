#include "pch.h"

class Tomato3DMenuBar : public Tomato::MenuBar
{
public:
	Tomato3DMenuBar()
	{

	}

	~Tomato3DMenuBar()
	{

	}
private:
};

class Layer3D : public Tomato::Layer
{
public:
	Layer3D()
	{
		Tomato::App::GetWindow()->SetTitle("Tomato3D");
		Tomato::GUI::ShowDockspace();
		Tomato::GUI::HideMainMenu();
		Tomato::GUI::HideSecondMenu();

		m_Cube = Tomato::Mesh::Cube();

		m_Cube.Textures.push_back(Tomato::Texture::CreateShared("assets/Images/grass_bottom.png"));
		m_Cube.Textures.push_back(Tomato::Texture::CreateShared("assets/Images/grass_side.png"));
		m_Cube.Textures.push_back(Tomato::Texture::CreateShared("assets/Images/grass_top.jpg"));

		uint32_t i;
		for (i = 0; i < 4; i++)
			m_Cube.Vertices[i].TexIndex = 0.0f;
		for (; i < 20; i++)
			m_Cube.Vertices[i].TexIndex = 1.0f;
		for (; i < 24; i++)
			m_Cube.Vertices[i].TexIndex = 2.0f;
	}

	void OnUpdate(float dt)
	{
		// Show FPS
		if (Tomato::Input::Keyboard(TOMATO_KEY_F))
		{
			PRINT(Tomato::App::GetFPS());
		}

		float angle = m_Timer.GetMilliseconds() / 10.0f;
		Tomato::Mat4 rot = Tomato::Quaternion::Rotation(m_Rotation).ToMat4();
		Tomato::Renderer3D::Get()->Draw(m_Cube, rot);


		auto& camera = Tomato::App::GetCurrentCamera()->GetComponent<Tomato::CameraComponent>();
		auto& tran = Tomato::App::GetCurrentCamera()->GetComponent<Tomato::TransformComponent>();

		const auto& window = Tomato::App::GetWindow();

		if (m_CurrentCameraProjection == 0)
			camera.SetOrthographicProjection(-window->GetAspectRatio() * m_CameraOrthoSize, window->GetAspectRatio() * m_CameraOrthoSize, -m_CameraOrthoSize, m_CameraOrthoSize, 0.1f, 100.0f);
		else
			camera.SetPerspectiveProjection(45.0f, window->GetAspectRatio(), 0.1f, 100.0f);

		float rotationSpeed = 30.0f * dt;

		float cameraSpeed = m_CameraSpeed * dt;
		if (Tomato::Input::Keyboard(TOMATO_KEY_LEFT))
		{
			m_Rotation.y += rotationSpeed;
			//tran.Position.x -= cameraSpeed;
			//camera.Target.x -= 2 * cameraSpeed;
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_RIGHT))
		{
			m_Rotation.y -= rotationSpeed;
			//tran.Position.x += cameraSpeed;
			//camera.Target.x += 2 * cameraSpeed;
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_UP))
		{
			m_Rotation.x -= rotationSpeed;
			//tran.Position.y += cameraSpeed;
			//camera.Target.y += 2 * cameraSpeed;
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_DOWN))
		{
			m_Rotation.x += rotationSpeed;
			//tran.Position.y -= cameraSpeed;
			//camera.Target.y -= 2 * cameraSpeed;
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_NUMPAD_8))
		{
			//tran.Position.z -= cameraSpeed;
			//camera.Target.z -= 2 * cameraSpeed;
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_NUMPAD_2))
		{
			//tran.Position.z += cameraSpeed;
			//camera.Target.z += 2 * cameraSpeed;
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_NUMPAD_4))
		{
			m_Rotation.z += rotationSpeed;
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_NUMPAD_6))
		{
			m_Rotation.z -= rotationSpeed;
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

	virtual void OnEvent(const Tomato::Event& e)
	{
		if (e.GetType() == Tomato::EventType::KeyPress)
		{
			auto& camera = Tomato::App::GetCurrentCamera()->GetComponent<Tomato::CameraComponent>();
			auto& tran = Tomato::App::GetCurrentCamera()->GetComponent<Tomato::TransformComponent>();

			float cameraSpeed = m_CameraSpeed * 0.1f;
			auto ev = Tomato::Event::Cast<Tomato::KeyPressEvent>(e);
			if (ev.GetKey() == TOMATO_KEY_LEFT)
			{
				//m_Rotation.y += rotationSpeed;
				//tran.Position.x -= cameraSpeed;
				//camera.Target.x -= 2 * cameraSpeed;
			}
			if (ev.GetKey() == TOMATO_KEY_RIGHT)
			{
				//m_Rotation.y -= rotationSpeed;
				//tran.Position.x += cameraSpeed;
				//camera.Target.x += 2 * cameraSpeed;
			}
			if (ev.GetKey() == TOMATO_KEY_UP)
			{
				//m_Rotation.x -= rotationSpeed;
				//tran.Position.y += cameraSpeed;
				//camera.Target.y += 2 * cameraSpeed;
			}
			if (ev.GetKey() == TOMATO_KEY_DOWN)
			{
				//m_Rotation.x += rotationSpeed;
				//tran.Position.y -= cameraSpeed;
				//camera.Target.y -= 2 * cameraSpeed;
			}
			if (ev.GetKey() == TOMATO_KEY_NUMPAD_8)
			{
				//tran.Position.z -= cameraSpeed;
				//camera.Target.z -= 2 * cameraSpeed;
			}
			if (ev.GetKey() == TOMATO_KEY_NUMPAD_2)
			{
				//tran.Position.z += cameraSpeed;
				//camera.Target.z += 2 * cameraSpeed;
			}
		}
	}

	virtual void OnGUI() override
	{
		bool show_demo_window = true;
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		
		ImGui::Begin("Menu");
		ImGui::Text("Menu");
		ImGui::End();
	}
private:
	int m_CurrentCameraProjection = 1;

	float m_CameraSpeed = 3.0f;
	float m_CameraOrthoSize = 1.0f;
	float m_CameraFOV = 45.0f;

	Tomato::Timer m_Timer;

	Tomato::Mesh m_Cube;
	Tomato::Float3 m_Rotation;
};


class Tomato3D : public Tomato::App
{
public:
	Tomato3D(const std::unordered_map<std::string, std::any>& args)
		:App(args)
	{
		auto& scene = this->CreateScene("3D Scene");
		scene->PushLayer(new Layer3D());

		App::SetMenuBar(new Tomato3DMenuBar());
	}
	virtual ~Tomato3D() override = default;
};

Tomato::App* Tomato::App::Create(const std::unordered_map<std::string, std::any>& args)
{
	return new Tomato3D(args);
}