#pragma once


namespace Tomato
{
	struct RawImageData
	{
		Int Width;
		Int Height;
		Int NrChannels;
		UChar* Data;
		UInt Size;
	};

	class Image
	{
	public:
		Image(std::string_view path);
		~Image();

		const UChar* GetData() const;
		UInt GetBufferSize() const;
		Int GetWidth() const;
		Int GetHeight() const;
		Int GetNrChannels() const;
		Int GetFormat() const;
	private:
		RawImageData m_RawData;
	};
}
