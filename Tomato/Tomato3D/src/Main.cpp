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
		:m_Font("assets/Fonts/Roboto/Roboto-Regular.ttf")
	{
		m_FrameBuffer = Tomato::FrameBuffer::CreateShared();
		Tomato::Renderer3D::SetFrameBuffer(m_FrameBuffer);

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

		Tomato::App::GetCurrentCamera()->GetComponent<Tomato::TransformComponent>().Position.y = -1.0f;
	
		Tomato::Renderer3D::SetBackgroundColor({ 0.8f, 0.8f, 0.8f });

		Tomato::Renderer3D::SetLight(Tomato::Float3(2.0f, 2.0f, 0.0f));
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
		//Tomato::Renderer3D::Get()->Draw(m_Cube, rot);

		DrawLines();

		auto& camera = Tomato::App::GetCurrentCamera()->GetComponent<Tomato::CameraComponent>();
		auto& tran = Tomato::App::GetCurrentCamera()->GetComponent<Tomato::TransformComponent>();

		const auto& window = Tomato::App::GetWindow();

		if (m_CurrentCameraProjection == 0)
			camera.SetOrthographicProjection(-window->GetAspectRatio() * m_CameraOrthoSize, window->GetAspectRatio() * m_CameraOrthoSize, -m_CameraOrthoSize, m_CameraOrthoSize, 0.1f, 100.0f);
		else
			camera.SetPerspectiveProjection(45.0f, window->GetAspectRatio(), 0.1f, 100.0f);

		float rotationSpeed = 30.0f * dt;

		float cameraSpeed = m_CameraSpeed * dt;

		float squareSpeed = m_SquareSpeed * dt;

		if (Tomato::Input::Keyboard(TOMATO_KEY_A))
		{
			m_SquarePos.x -= squareSpeed;
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_D))
		{
			m_SquarePos.x += squareSpeed;
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_W))
		{
			m_SquarePos.y += squareSpeed;
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_S))
		{
			m_SquarePos.y -= squareSpeed;
		}
		
		if (Tomato::Input::Keyboard(TOMATO_KEY_MINUS))
		{
			window->SetFullscreen(true);
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_EQUAL))
		{
			window->SetFullscreen(false);
		}

		auto& pos = Tomato::App::GetCurrentCamera()->GetComponent<Tomato::TransformComponent>().Position;
		auto& target = Tomato::App::GetCurrentCamera()->GetComponent<Tomato::CameraComponent>().Target;
		if (Tomato::Input::Keyboard(TOMATO_KEY_LEFT))
		{
			m_CameraTheta -= m_CameraSpeed * dt;
		}
		if (Tomato::Input::Keyboard(TOMATO_KEY_RIGHT))
		{
			m_CameraTheta += m_CameraSpeed * dt;
		}
		CameraRepositioning();
	}

	virtual void OnEvent(const Tomato::Event& e)
	{

	}

	virtual void OnGUI() override
	{
		Tomato::GUI::RenderWindow(m_FrameBuffer, true);
		
		bool show_demo_window = true;
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		
		ImGui::Begin("Menu");
		
		ImGui::Text(("FPS: " + Tomato::Math::ToString(Tomato::App::GetFPS())).c_str());

		const char* const cameraTypes[] = { "Orthographic", "Perspective" };
		ImGui::Combo("Camera Type", &m_CurrentCameraProjection, cameraTypes, 2);
		
		ImGui::SliderFloat("Smoothness", &m_Smoothness, 0.3f, 1.0f);
		
		ImGui::End();
	}
private:
	void DrawLines()
	{
		TOMATO_BENCHMARKING_FUNCTION();

		m_Font.RenderText("Text", { 1.0f, 0.5f, 1.0f },
			Tomato::Color::Red, 12.0f, Tomato::Float3(0.0f, 90.0f, 90.0f)
		);

		float maxPoint = m_CameraRadius / 3.0f;

		Tomato::Renderer3D::Get()->DrawLine({ -maxPoint,  0.0f,  0.0f }, { maxPoint, 0.0f, 0.0f }, Tomato::Color::Red);
		m_Font.RenderText("x", { maxPoint, maxPoint / 20.0f, 0.0f },
			Tomato::Color::Red, maxPoint
		);
		Tomato::Renderer3D::Get()->DrawLine({ 0.0f, -maxPoint,  0.0f }, { 0.0f, maxPoint, 0.0f }, Tomato::Color::Green);
		m_Font.RenderText("y", { maxPoint / 20.0f, maxPoint, 0.0f },
			Tomato::Color::Green, maxPoint
		);
		Tomato::Renderer3D::Get()->DrawLine({ 0.0f,  0.0f, -maxPoint }, { 0.0f, 0.0f, maxPoint }, Tomato::Color::Blue);
		m_Font.RenderText("z", { 0.0f, maxPoint / 20.0f , maxPoint },
			Tomato::Color::Blue, maxPoint
		);

		DrawExplicitGraph([](float x, float z) {
			return Tomato::Math::Sqrt(1.0f - x * x - z * z);
		}, Tomato::Float3(0.5f, 0.4f, 0.3f));
	}

	void CameraRepositioning()
	{
		auto& tran = Tomato::App::GetCurrentCamera()->GetComponent<Tomato::TransformComponent>();

		tran.Position.x = 3 * Tomato::Math::Cos(m_CameraTheta);
		tran.Position.z = 3 * Tomato::Math::Sin(m_CameraTheta);
	}

	void DrawExplicitGraph(const std::function<float(float, float)>& f, const Tomato::Float3& color, const float alpha = 1.0f) const
	{
		TOMATO_BENCHMARKING_FUNCTION();

		float dx, dz;
		dx = dz = m_CameraRadius / (100.0f * m_Smoothness);

		float limit = m_CameraRadius / 3.0f;

		for (float x = -limit; x <= limit - dx; x += dx)
		{
			for (float z = -limit; z <= limit - dz; z += dz)
			{
				Tomato::Renderer3D::Get()->DrawQuad
				(
					Tomato::Float3(x, f(x, z), z),
					Tomato::Float3(x, f(x, z + dz), z + dz),
					Tomato::Float3(x + dx, f(x + dx, z + dz), z + dz),
					Tomato::Float3(x + dx, f(x + dx, z), z),
					color,
					alpha
				);
			}
		}
	}
private:
	float m_CameraSpeed = 0.5f;
	float m_CameraOrthoSize = 1.0f;
	float m_CameraFOV = 45.0f;
	float m_CameraTheta = Tomato::Math::pi / 2.0f;
	float m_CameraRadius = 4.0f;
	float m_Smoothness = 0.7f;

	Tomato::Timer m_Timer;

	Tomato::Float2 m_SquarePos = { -0.5, 0.5 };
	float m_SquareSpeed = 0.4f;

	Tomato::Mesh m_Cube;
	Tomato::Float3 m_Rotation;
	std::shared_ptr<Tomato::FrameBuffer> m_FrameBuffer;

	Tomato::Font m_Font;

	// GUI
	int m_CurrentCameraProjection = 1;
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