#include "Tomato.h"
#include "TrianglesLayer.h"
#include "TDLayer.h"
#include "GUILayer.h"
#include "MainLayer.h"


class TomatoApp : public Tomato::App
{
public:
	TomatoApp()
	{
		auto& main_scene = CreateScene("Main Scene");
		main_scene->PushLayer(new MainLayer());

		auto& triangles_scene = CreateScene("Triangles Scene");
		triangles_scene->PushLayer(new TrianglesLayer());

		auto& td_scene = CreateScene("3D Scene");
		td_scene->PushLayer(new TDLayer());
		
		PushImGuiLayer("Main GUI Layer", new GUILayer());
	}

	~TomatoApp()
	{

	}
private:
};


Tomato::App* Tomato::App::Create()
{
	TOMATO_BENCHMARKING_FUNCTION();
	return new TomatoApp();
}
