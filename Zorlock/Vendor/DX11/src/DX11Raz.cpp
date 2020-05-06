#include "ZLpch.h"
#include "DX11Raz.h"

namespace DX11Raz
{
	static DX11GraphicsEngine engine;
	static bool enabled = false;

	DX11GraphicsEngine::~DX11GraphicsEngine()
	{
		//release stuff
	}

	DX11GraphicsEngine* DX11GraphicsEngine::get()
	{
		enabled = true;
		return &engine;
	}

}
