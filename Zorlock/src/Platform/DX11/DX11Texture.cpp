#include "ZLpch.h"
#include "DX11Texture.h"


namespace Zorlock
{
	DX11Texture2D::DX11Texture2D(uint32_t width, uint32_t height) : m_Width(width), m_Height(height)
	{
		ZL_PROFILE_FUNCTION();
	}

	DX11Texture2D::DX11Texture2D(const std::string& path) : m_Path(path)
	{
		ZL_PROFILE_FUNCTION();
	}

	DX11Texture2D::~DX11Texture2D()
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11Texture2D::SetData(void* data, uint32_t size)
	{
		ZL_PROFILE_FUNCTION();

	}

	void DX11Texture2D::Bind(uint32_t slot) const
	{
		ZL_PROFILE_FUNCTION();
	}

}
