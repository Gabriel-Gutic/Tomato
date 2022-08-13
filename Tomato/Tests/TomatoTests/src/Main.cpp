#include "Tomato.h"

#include "MathTests/MathTestsLayer.h"
#include "FileTests/FileTestsLayer.h"


class TomatoTests : public Tomato::App
{
public:
	TomatoTests()
	{
		PushLayer(new Tomato::Tests::MathTestsLayer());
		PushLayer(new Tomato::Tests::FileTestsLayer());

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