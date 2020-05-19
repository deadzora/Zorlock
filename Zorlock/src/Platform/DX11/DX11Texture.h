#pragma once

#include "Zorlock/Renderer/Texture.h"
#include <DX11Textures.h>
#include <d3d11.h>

namespace Zorlock {

	class DX11Texture2D : public Texture2D
	{
	public:
		DX11Texture2D(uint32_t width, uint32_t height);
		DX11Texture2D(uint32_t width, uint32_t height, uint32_t color);
		DX11Texture2D(const std::string& path);
		virtual ~DX11Texture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((DX11Texture2D&)other).m_RendererID;
		}
	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		DX11Raz::RazTexture * m_RendererID;
		DXGI_FORMAT m_InternalFormat, m_DataFormat;
	};

}
