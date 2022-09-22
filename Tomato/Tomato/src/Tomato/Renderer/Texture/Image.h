#pragma once


namespace Tomato
{
	struct RawImageData
	{
		int Width;
		int Height;
		int NrChannels;
		unsigned char* Data;
		unsigned int Size;
	};

	class Image
	{
	public:
		enum class Format
		{
			None = 0,
			Red = 1,
			RG = 2,
			RGB = 3,
			RGBA = 4,
		};
	public:
		Image(std::string_view path);
		~Image();

		const unsigned char* GetData() const;
		unsigned int GetBufferSize() const;
		int GetWidth() const;
		int GetHeight() const;
		int GetNrChannels() const;
		Format GetFormat() const;
	private:
		RawImageData m_RawData;
	};
}
