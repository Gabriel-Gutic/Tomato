#include "pchTomato.h"
#include "App.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GUI/GUI.h"
#include "Renderer/Shader/ShaderProgram.h"

#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Texture/Texture.h"
#include "Renderer/Camera.h"


namespace Tomato
{
	App* App::s_Instance = nullptr;
	App::App()
		:isRunning(true)
	{
		TOMATO_ASSERT(!s_Instance, "App already instantiated!");
		s_Instance = this;

		m_Window = std::make_unique<Window>("Tomato Window", 800, 800);

		GUI::Init();

		m_Camera = std::make_unique<Camera>(Float3(2.0f, -2.0f, 7.0f));
	}

	App::~App()
	{
		GUI::Destroy();
	}

	Int App::Run()
	{
		std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>(std::initializer_list<Vertex>{
			{ { -0.5f, -0.5f, 0.0f}, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }},
			{ { -0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, { 0.0f, 1.0f } },
			{ {  0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}, { 1.0f, 0.0f } },
			{ {  0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f}, { 1.0f, 1.0f } },
			//{ {  1.0f,  0.0f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f}},
		});
		std::shared_ptr<VertexArray> va = std::make_shared<VertexArray>();
	
		std::shared_ptr<IndexBuffer> ib = std::make_shared<IndexBuffer>(std::initializer_list<UInt>{
			0, 1, 2,
			2, 3, 1,
			//3, 4, 2,
		});

		std::shared_ptr<ShaderProgram> shaderProgram = std::make_shared<ShaderProgram>("assets/Shaders/VertexShader.glsl", "assets/Shaders/FragmentShader.glsl");

		std::shared_ptr<Texture> texture = std::make_shared<Texture>("assets/images/plain.png");

		while (isRunning)
		{
			while (!m_EventQueue.empty())
			{
				auto& e = *m_EventQueue.front();

				if (e.GetType() == EventType::WindowClose)
				{
					Exit();
				}

				TOMATO_PRINT(e.ToString());

				for (auto& layer : m_LayerStack)
				{
					layer->OnEvent(e);
				}

				delete m_EventQueue.front();
				m_EventQueue.pop();
			}

			m_Window->Clear(1.0f, 0.0f, 0.0f);

			shaderProgram->Use();

			texture->Bind();
			va->Bind();
			ib->Bind();

			auto view = m_Camera->Update();
			TOMATO_PRINT(view.ToString());

			Int location = glGetUniformLocation(shaderProgram->GetID(), "View");
			glUniformMatrix4fv(location, 1, GL_FALSE, &view[0][0]);

			//glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawElements(GL_TRIANGLES, ib->GetSize(), GL_UNSIGNED_INT, (void*)0);

			for (auto& layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			VertexArray::Unbind();
			shaderProgram->Use(false);

			GUI::Begin();
			
			for (auto& layer : m_LayerStack)
			{
				layer->OnGUI();
			}
			
			GUI::End();

			m_Window->Swap();
		}

		return 0;
	}

	void App::PushEvent(Event* event)
	{
		s_Instance->m_EventQueue.push(event);
	}

	void App::PushLayer(Layer* layer)
	{
		s_Instance->m_LayerStack.push_back(layer);
	}

	void App::PopLayer()
	{
		s_Instance->m_LayerStack.pop_back();
	}

	std::unique_ptr<Window>& App::GetWindow()
	{
		return s_Instance->m_Window;
	}

	void App::Exit()
	{
		s_Instance->isRunning = false;
	}
}