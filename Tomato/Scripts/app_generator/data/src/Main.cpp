#include "pch{ProjectName}.h"
#include "{ProjectName}MenuBar.h"
#include "{ProjectName}Layer.h"
#include "GUILayer.h"


class {ProjectName} : public Tomato::App
{
public:
{ProjectName}()
	{
		auto& main_scene = CreateScene("Main Scene");
		main_scene->PushLayer(new {ProjectName}Layer());
		
		PushImGuiLayer("Main GUI Layer", new GUILayer());

		SetMenuBar(new {ProjectName}MenuBar());
	}

	~{ProjectName}()
	{

	}
private:
};


Tomato::App* Tomato::App::Create()
{
	TOMATO_BENCHMARKING_FUNCTION();
	return new {ProjectName}();
}
