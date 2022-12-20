#include "pchTomato.h"
#include "Random.h"


namespace Tomato
{
	RandomEngine* RandomEngine::s_Instance = nullptr;

	RandomEngine::RandomEngine()
		:m_Device(nullptr), m_MT(nullptr)
	{
		m_Device = std::make_unique<std::random_device>();
		m_MT = std::make_unique<std::mt19937>((*m_Device)());
	}

	RandomEngine::~RandomEngine()
	{
	}

	void RandomEngine::Initialize()
	{
		TOMATO_ASSERT(!s_Instance, "RandomEngine already initialized!");
		s_Instance = new RandomEngine();
	}

	void RandomEngine::Terminate()
	{
		delete s_Instance;
	}

	RandomEngine& RandomEngine::Get()
	{
		return *s_Instance;
	}

	int RandomEngine::RandomInt(int a, int b) const
	{
		std::uniform_int_distribution<int> distribution(a, b);
		int random_int = distribution(*m_MT);
		return random_int;
	}

	float RandomEngine::RandomFloat(float a, float b) const
	{
		std::uniform_real_distribution<float> distribution(a, b);
		float random_float = distribution(*m_MT);
		return random_float;
	}

}