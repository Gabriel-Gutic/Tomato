#pragma once


namespace Tomato
{
	class RandomEngine
	{
	private:
		RandomEngine();
	public:
		RandomEngine(const RandomEngine&) = delete;
		~RandomEngine();

		static void Initialize();
		static void Terminate();

		static RandomEngine& Get();

		int RandomInt(int a, int b) const;
		float RandomFloat(float a, float b) const;
	private:
		std::unique_ptr<std::random_device> m_Device;
		std::unique_ptr<std::mt19937> m_MT;

		static RandomEngine* s_Instance;
	};
}
