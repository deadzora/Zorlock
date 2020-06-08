#include "ZLpch.h"
#include "DX11Raz.h"
#include "DX11Texture.h"
#include "DX11Shaders.h"


namespace Zorlock
{
	DX11Texture2D::DX11Texture2D(uint32_t width, uint32_t height) : m_Width(width), m_Height(height)
	{
		ZL_PROFILE_FUNCTION();
		Ref<DX11Raz::DX11Color> white = Ref<DX11Raz::DX11Color>(new DX11Raz::DX11Color(255,255,255));

		m_RendererID = Ref<DX11Raz::RazTexture>(DX11Raz::RazCreateTexture(white, (UINT)width, (UINT)height, aiTextureType::aiTextureType_DIFFUSE));
	}

	DX11Texture2D::DX11Texture2D(uint32_t width, uint32_t height, uint32_t color)
	{
		Ref<DX11Raz::DX11Color> newcolor = Ref<DX11Raz::DX11Color>(new DX11Raz::DX11Color(color));
		m_RendererID = Ref<DX11Raz::RazTexture>(DX11Raz::RazCreateTexture(newcolor, (UINT)width, (UINT)height, aiTextureType::aiTextureType_DIFFUSE));
	}

	DX11Texture2D::DX11Texture2D(uint32_t width, uint32_t height, uint32_t color, uint32_t size)
	{
		Ref<DX11Raz::DX11Color> newcolor = Ref<DX11Raz::DX11Color>(new DX11Raz::DX11Color(color));
		m_RendererID = Ref<DX11Raz::RazTexture>(DX11Raz::RazCreateTexture(newcolor, (UINT)width, (UINT)height, (UINT)size, aiTextureType::aiTextureType_DIFFUSE));
	}

	DX11Texture2D::DX11Texture2D(const std::string& path) : m_Path(path)
	{
		ZL_PROFILE_FUNCTION();
		m_RendererID = DX11Raz::RazCreateTexture(path, aiTextureType::aiTextureType_DIFFUSE);
	}



	void DX11Texture2D::SetData(void* data, uint32_t size)
	{
		ZL_PROFILE_FUNCTION();

	}

	void DX11Texture2D::Bind(uint32_t slot) const
	{
		ZL_PROFILE_FUNCTION();
		DX11Raz::RazSetCurrentTexture(m_RendererID);
		RAZPTR<DX11Raz::RazShader> rs = nullptr;
		rs = DX11Raz::RazGetCurrentShader();
		if (rs != nullptr)
		{
			if (!rs->GetTextureBufferUploaded(slot))
			{
				printf("APPLY SHADER \n");
				rs->SetTextureBufferUploaded(slot,true);
				DX11Raz::RazApplyShaderTexture(m_RendererID, slot);
			}
		}

	}

	void DX11Texture2D::Bind(std::string varname)
	{
		ZL_PROFILE_FUNCTION();
		DX11Raz::RazGetCurrentShader()->UpdateTextureBuffer(varname, m_RendererID);
		DX11Raz::RazGetCurrentShader()->ApplyTexture(varname);
	}

}
