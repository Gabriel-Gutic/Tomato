#include "Tomato.h"

#include "MathTests/MathTestsLayer.h"


class TomatoTests : public Tomato::App
{
public:
	TomatoTests()
	{
		PushLayer(new Tomato::Tests::MathTestsLayer());

		SLEEP(10000);
		Exit();
	}

	~TomatoTests()
	{

	}
private:
};


Tomato::App* Tomato::App::Create()
{
	return new TomatoTests();
}