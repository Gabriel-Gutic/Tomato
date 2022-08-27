#include "pchTomato.h"
#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "App.h"
#include "Event/KeyboardEvent.h"
#include "Event/MouseEvent.h"
#include "Event/WindowEvent.h"

#include <stb_image/stb_image.h>


namespace Tomato
{
	Window::Window(std::string_view title, int width, int height)
		:m_Data({
				title.data(),
				200,
				100,
				width,
				height,
				false
			}), m_Window(nullptr)
	{
		TOMATO_BENCHMARKING_FUNCTION();

		/* Initialize the library */
		TOMATO_ASSERT(glfwInit(), "Failed to initialize GLFW!");

		/* Create a windowed mode window and its OpenGL context */
		auto window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			TOMATO_ASSERT(0, "Failed to create GLFW Window!");
		}

		glfwSetWindowPos(window, m_Data.X, m_Data.Y);

		m_Window = window;

		/* Make the window's context current */
		glfwMakeContextCurrent(window);
		glfwSwapInterval(m_Data.VSync);
		glfwSetWindowUserPointer(window, &m_Data);

		TOMATO_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD");
	
		//glViewport(0, 0, m_Data.Width, m_Data.Height);

		SetIcon("assets/Logo/logo.png");

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			switch (action)
			{
			case GLFW_PRESS:
				App::PushEvent(new KeyPressEvent(key));
				break;
			case GLFW_RELEASE:
				App::PushEvent(new KeyReleaseEvent(key));
				break;
			case GLFW_REPEAT:
				App::PushEvent(new KeyRepeatEvent(key));
				break;
			}
		});

		glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int codepoint) {
			App::PushEvent(new CharEvent(codepoint));
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			switch (action)
			{
			case GLFW_PRESS:
				App::PushEvent(new MouseButtonPressEvent(button));
				break;
			case GLFW_RELEASE:
				App::PushEvent(new MouseButtonReleaseEvent(button));
				break;
			}
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
			App::PushEvent(new MouseMoveEvent(xpos, ypos));
		});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
			App::PushEvent(new WheelEvent(yoffset));
		});

		glfwSetWindowPosCallback(window, [](GLFWwindow* window, int xpos, int ypos) {
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		
			data.X = xpos;
			data.Y = ypos;
		});

		glfwSetWindowMaximizeCallback(window, [](GLFWwindow* window, int maximized) {
			App::PushEvent(new WindowMaximizeEvent(maximized));
		});

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			
			auto& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			data.Width = width;
			data.Height = height;

			glViewport(0, 0, data.Width, data.Height); 

			if (data.Width == 0 || data.Height == 0)
				App::PushEvent(new WindowMinimizeEvent(true));
			else App::PushEvent(new WindowMinimizeEvent(false));

			App::PushEvent(new WindowResizeEvent(width, height));
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			App::PushEvent(new WindowCloseEvent());
		});
	}

	Window::~Window()
	{
		glfwDestroyWindow((GLFWwindow*)m_Window);
		glfwTerminate();
	}

	void Window::Clear(float r, float g, float b, float a) const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(r, g, b, a);
	}

	void Window::Clear(const Float4& color) const
	{
		Clear(color.a, color.b, color.c, color.w);
	}

	void Window::Swap()
	{
		/* Swap front and back buffers */
		glfwSwapBuffers((GLFWwindow*)m_Window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	void* Window::Get()
	{
		return m_Window;
	}

	int Window::GetWidth() const
	{
		return m_Data.Width;
	}

	int Window::GetHeight() const
	{
		return m_Data.Height;
	}

	std::pair<int, int> Window::GetSize() const
	{
		return { m_Data.Width, m_Data.Height };
	}

	void Window::SetSize(int width, int height)
	{
		glfwSetWindowSize((GLFWwindow*)m_Window, width, height);
		m_Data.Width = width;
		m_Data.Height = height;
	}

	void Window::SetWidth(int width)
	{
		glfwSetWindowSize((GLFWwindow*)m_Window, width, m_Data.Height);
		m_Data.Width = width;
	}

	void Window::SetHeight(int height)
	{
		glfwSetWindowSize((GLFWwindow*)m_Window, m_Data.Width, height);
		m_Data.Height = height;
	}

	Float Window::GetAspectRatio() const
	{
		return (Float)m_Data.Width / (Float)m_Data.Height;
	}

	int Window::GetX() const
	{
		return m_Data.X;
	}

	int Window::GetY() const
	{
		return m_Data.Y;
	}

	std::pair<int, int> Window::GetPos() const
	{
		return { m_Data.X, m_Data.Y };
	}

	void Window::SetPos(int x, int y)
	{
		m_Data.X = x;
		m_Data.Y = y;
		glfwSetWindowPos(static_cast<GLFWwindow*>(m_Window), x, y);
	}

	void Window::SetX(int x)
	{
		SetPos(x, m_Data.Y);
	}

	void Window::SetY(int y)
	{
		SetPos(m_Data.X, y);
	}

	void Window::SetTitle(std::string_view title)
	{
		glfwSetWindowTitle((GLFWwindow*)m_Window, title.data());
		m_Data.Title = title;
	}

	const std::string& Window::GetTitle() const
	{
		return m_Data.Title;
	}

	void Window::SetIcon(std::string_view iconPath)
	{
		TOMATO_ASSERT(File::Exist(iconPath), "Icon '{0}' not found!", iconPath.data());

		GLFWimage images[1];
		images[0].pixels = stbi_load(iconPath.data(), &images[0].width, &images[0].height, 0, 4); //rgba channels 
		glfwSetWindowIcon((GLFWwindow*)m_Window, 1, images);
		stbi_image_free(images[0].pixels);
	}

	void Window::SetVSync(bool vsync)
	{
		glfwSwapInterval(vsync);
		m_Data.VSync = vsync;
	}

	bool Window::GetVSync() const
	{
		return m_Data.VSync;
	}

}