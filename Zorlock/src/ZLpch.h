#pragma once
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>


#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Zorlock/Log.h"
#ifdef ZL_PLATFORM_WINDOWS 
	#include <Windows.h>
#endif

//Renderer
#ifdef RENDERER_DX11
#define DX11_API
#endif

#ifdef RENDERER_OPENGL
#define OPENGL_API
#endif

