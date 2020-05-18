#pragma once

#include "Zorlock/Renderer/OrthographicCamera.h"
#include "Color.h"
#include "Zorlock/Renderer/Texture.h"

namespace Zorlock {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		// Primitives
		static void DrawQuad(const VECTOR2& position, const VECTOR2& size, const COLOR4& color);
		static void DrawQuad(const VECTOR3& position, const VECTOR2& size, const COLOR4& color);
		static void DrawQuad(const VECTOR2& position, const VECTOR2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const COLOR4& tintColor = COLOR4::WHITE());
		static void DrawQuad(const VECTOR3& position, const VECTOR2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const COLOR4& tintColor = COLOR4::WHITE());

		static void DrawRotatedQuad(const VECTOR2& position, const VECTOR2& size, float rotation, const COLOR4& color);
		static void DrawRotatedQuad(const VECTOR3& position, const VECTOR2& size, float rotation, const COLOR4& color);
		static void DrawRotatedQuad(const VECTOR2& position, const VECTOR2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const COLOR4& tintColor = COLOR4::WHITE());
		static void DrawRotatedQuad(const VECTOR3& position, const VECTOR2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const COLOR4& tintColor = COLOR4::WHITE());

		// Stats
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};
		static void ResetStats();
		static Statistics GetStats();
	private:
		static void FlushAndReset();
	};

}