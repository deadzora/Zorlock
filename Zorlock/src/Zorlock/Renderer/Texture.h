#pragma once

#include <string>

#include "Zorlock/Core/Core.h"

namespace Zorlock {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;
		virtual void Bind(std::string varname) = 0;
		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual bool operator==(const Texture& other) const = 0;
		
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static Ref<Texture2D> Create(uint32_t width, uint32_t height, uint32_t color);
		static Ref<Texture2D> Create(uint32_t width, uint32_t height, uint32_t color, uint32_t size);
		static Ref<Texture2D> Create(const std::string& path);
	};
	ZL_ENABLE_TYPENAME(Texture)
	ZL_ENABLE_TYPENAME(Texture2D)
}

#define ZLTEXTURE2D Zorlock::Texture2D