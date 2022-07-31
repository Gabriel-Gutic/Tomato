#pragma once


namespace Tomato
{
	struct RawImageData
	{
		Int Width;
		Int Height;
		Int NrChannels;
		UChar* Data;
	};

	class Image
	{
	public:
		Image(std::string_view path);
		~Image();

		Int GetWidth() const;
		Int GetHeight() const;
		Int GetNrChannels() const;
	private:
		RawImageData m_RawData;
	};
}
