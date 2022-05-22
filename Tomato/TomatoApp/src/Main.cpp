#include "Tomato.h"


class TomatoApp : public Tomato::App
{
public:
	TomatoApp()
	{

	}

	~TomatoApp()
	{

	}
private:
};


Tomato::App* Tomato::App::Create()
{
	return new TomatoApp();
}