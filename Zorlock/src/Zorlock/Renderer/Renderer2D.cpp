#include "ZLpch.h"
#include "Zorlock/Renderer/Renderer2D.h"
#include "Zorlock/Renderer/VertexArray.h"
#include "Zorlock/Renderer/Shader.h"
#include "Zorlock/Renderer/RenderCommand.h"

//#include <glm/gtc/matrix_transform.hpp>

#define QUADVERTEXCOUNT 6

namespace Zorlock {


	struct QuadVertex
	{
	public:
		QuadVertex() = default;
		QuadVertex(float x, float y, float z, float r, float g, float b, float a, float u, float v, float ti, float tf) : Position(VECTOR3(x,y,z)), Color(COLOR4(r,g,b,a)), TexCoord(VECTOR2(u,v)), TexIndex(ti), TilingFactor(tf)
		{}
		QuadVertex(VECTOR3 pos, COLOR4 col, VECTOR2 uv, float ti, float tf) : Position(pos), Color(col), TexCoord(uv), TexIndex(ti), TilingFactor(tf)
		{}
		VECTOR3 Position;
		COLOR4 Color;
		VECTOR2 TexCoord;
		float TexIndex;
		float TilingFactor;

	};

	struct Renderer2DData
	{
		//this should be a global value.. 
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
		//std::vector<QuadVertex*> QuadVertexBufferList;
		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture

		VECTOR4 QuadVertexPositions[4];

		Renderer2D::Statistics Stats;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		ZL_PROFILE_FUNCTION();
		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
			samplers[i] = i;

		//s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data.TextureShader = Shader::Create("2dShader","assets/shaders/Texture.zlsl");
		s_Data.TextureShader->Bind();
		s_Data.QuadVertexArray = VertexArray::Create();
		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		printf("Size of quad vertex is %u ", (uint32_t)sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout(s_Data.TextureShader->GetLayout(),s_Data.TextureShader.get());

		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;


		s_Data.WhiteTexture = Texture2D::Create(1, 1, 0xffffffff);



		//OpenGL only, Directx combines all textures into a single array, doesn;t need to send an array of addresses

		//s_Data.TextureShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);
		
		// Set all texture slots to 0
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;

		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, -0.1f, 1.0f };
		s_Data.QuadVertexPositions[1] = {  0.5f, -0.5f, -0.1f, 1.0f };
		s_Data.QuadVertexPositions[2] = {  0.5f,  0.5f, -0.1f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, -0.1f, 1.0f };

		
	}

	void Renderer2D::Shutdown()
	{
		ZL_PROFILE_FUNCTION();
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		
		ZL_PROFILE_FUNCTION();
		camera.UpdateViewMatrix();
		s_Data.TextureShader->Bind();
		if (RendererAPI::GetAPI() == RendererAPI::API::DX11)
		{
			s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewMatrix() * camera.GetProjectionMatrix());
		}
		else {
			s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetProjectionMatrix() * camera.GetViewMatrix());
		}
		s_Data.QuadIndexCount = 0;
		s_Data.Stats.QuadCount = 0;
		s_Data.Stats.DrawCalls = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::EndScene()
	{
		ZL_PROFILE_FUNCTION();

		s_Data.TextureShader->Bind();
		uint32_t dataSize = sizeof(QuadVertex)* QUADVERTEXCOUNT;

		s_Data.Stats.DrawCalls = 0;
		uint32_t lasttexture = -1;
		for (size_t i = 0; i < s_Data.Stats.QuadCount; i++)
		{
			uint32_t index = s_Data.QuadVertexBufferBase[i*4].TexIndex;
			uint32_t bound = 0;
			//DX11 will retain the shader texture assigned between each draw call but openGL doesn't
			//However OpenGL keeps texture in memory so its ok to assign it per pass where as DX11 must reupload it each time it changes.
			if (ZLRENDERAPI == RendererAPI::API::OpenGL)
			{
				s_Data.TextureSlots[index]->Bind(bound);
				s_Data.TextureShader->SetInt("u_Textures", 0);
				s_Data.Stats.DrawCalls++;
			}
			else {
				if (index != lasttexture)
				{
					s_Data.TextureSlots[index]->Bind(bound);
					s_Data.TextureShader->SetInt("u_Textures", 0);
					lasttexture = index;
					s_Data.Stats.DrawCalls++;
				}
			}

			QuadVertex* quad = new QuadVertex[4];
			std::copy(s_Data.QuadVertexBufferBase + (i * 4), s_Data.QuadVertexBufferBase + ((i+1) * 4), quad);
			s_Data.QuadVertexBuffer->SetData(quad, dataSize);
			delete[] quad;
			RenderCommand::DrawIndexed(s_Data.QuadVertexArray, QUADVERTEXCOUNT+2);
			
		}

	
		//uint32_t dataSize = sizeof(QuadVertex) * s_Data.QuadIndexCount;
		
		
		//Flush();
	}

	void Renderer2D::Flush()
	{
		// Bind textures
		/*
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.TextureSlots[i]->Bind(i);

		//s_Data.WhiteTexture->Bind("u_Textures");
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
		s_Data.Stats.DrawCalls++;
		*/
	}

	void Renderer2D::FlushAndReset()
	{
		EndScene();

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::DrawQuad(const VECTOR2& position, const VECTOR2& size, const COLOR4& color)
	{
		DrawQuad(VECTOR3( position.x, position.y, -0.01f ), size, color);
	}

	void Renderer2D::DrawQuad(const VECTOR3& position, const VECTOR2& size, const COLOR4& color)
	{
		ZL_PROFILE_FUNCTION();

		constexpr size_t quadVertexCount = 4;
		const float textureIndex = 0.0f; // White Texture
		constexpr VECTOR2ARRAY textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float tilingFactor = 1.0f;

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		MATRIX4 transform = MATRIX4::TRS(position, QUATERNION::EulerAngles(VECTOR3(0,0,0)), VECTOR3(size.x, size.y, 1.0f));// = MATRIX4::IDENTITY().translation(position) * MATRIX4::IDENTITY().scaling(VECTOR3(size.x,size.y,1.0f));  //glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			
			VECTOR3 pos = transform.multiply(s_Data.QuadVertexPositions[i].ToVector3());

			
			s_Data.QuadVertexBufferPtr->Position = pos;
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = { textureCoords[i][0],textureCoords[i][1] };
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
			
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}





	void Renderer2D::DrawQuad(const VECTOR2& position, const VECTOR2& size, const Ref<Texture2D>& texture, float tilingFactor, const COLOR4& tintColor)
	{
		DrawQuad(VECTOR3( position.x, position.y, -0.01f ), size, texture, tilingFactor, tintColor);
	}



	void Renderer2D::DrawQuad(const VECTOR3& position, const VECTOR2& size, const Ref<Texture2D>& texture, float tilingFactor, const COLOR4& tintColor)
	{
		ZL_PROFILE_FUNCTION();

		constexpr size_t quadVertexCount = 4;
		constexpr COLOR4ARRAY color = { 1.0f, 1.0f, 1.0f, 1.0f };
		constexpr VECTOR2ARRAY textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
				FlushAndReset();

			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		MATRIX4 transform = MATRIX4::TRS(position, QUATERNION::EulerAngles(VECTOR3(0,0,0)), VECTOR3(size.x, size.y, 1.0f));// = MATRIX4::IDENTITY().translation(position) * MATRIX4::IDENTITY().scaling(VECTOR3(size.x,size.y,1.0f));  //glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		transform.inverse();
		for (size_t i = 0; i < quadVertexCount; i++)
		{
			
			VECTOR3 pos = transform.multiply(s_Data.QuadVertexPositions[i].ToVector3());

			
			s_Data.QuadVertexBufferPtr->Position = pos;
			s_Data.QuadVertexBufferPtr->Color = { color[0],color[1],color[2],color[3] };
			s_Data.QuadVertexBufferPtr->TexCoord = { textureCoords[i][0],textureCoords[i][1] };
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
			
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const VECTOR2& position, const VECTOR2& size, float rotation, const COLOR4& color)
	{
		DrawRotatedQuad(VECTOR3( position.x, position.y, 0.0f ), size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const VECTOR3& position, const VECTOR2& size, float rotation, const COLOR4& color)
	{
		ZL_PROFILE_FUNCTION();

		constexpr size_t quadVertexCount = 4;
		const float textureIndex = 0.0f; // White Texture
		constexpr VECTOR2ARRAY textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float tilingFactor = 1.0f;

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();


		MATRIX4 transform = MATRIX4::TRS(position, QUATERNION::EulerAngles(VECTOR3(0.0f, 0.0f, rotation)), VECTOR3(size.x, size.y, 1.0f)); 


		for (size_t i = 0; i < quadVertexCount; i++)
		{
			VECTOR3 pos = transform.multiply(s_Data.QuadVertexPositions[i].ToVector3());

			
			s_Data.QuadVertexBufferPtr->Position = pos;
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = { textureCoords[i][0],textureCoords[i][1] };
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
			
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}



	void Renderer2D::DrawRotatedQuad(const VECTOR2& position, const VECTOR2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const COLOR4& tintColor)
	{
		DrawRotatedQuad(VECTOR3( position.x, position.y, 0.0f ), size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const VECTOR3& position, const VECTOR2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const COLOR4& tintColor)
	{
		ZL_PROFILE_FUNCTION();

		constexpr size_t quadVertexCount = 4;
		constexpr COLOR4ARRAY color = { 1.0f, 1.0f, 1.0f, 1.0f };
		constexpr VECTOR2ARRAY textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
				FlushAndReset();

			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		MATRIX4 transform = MATRIX4::TRS(position, QUATERNION::EulerAngles(VECTOR3(0.0f, 0.0f, rotation)), VECTOR3(size.x, size.y, 1.0f));
		

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			VECTOR3 pos = transform.multiply(s_Data.QuadVertexPositions[i].ToVector3());

			
			s_Data.QuadVertexBufferPtr->Position = pos;
			s_Data.QuadVertexBufferPtr->Color = { color[0],color[1],color[2],color[3] };
			s_Data.QuadVertexBufferPtr->TexCoord = { textureCoords[i][0],textureCoords[i][1] };
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
			
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.Stats;
	}

}