#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Zorlock/Core/Log.h"

#include "Zorlock/Debug/Instrumentor.h"

#ifdef ZL_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#define ZL_DEPRECATED(x) [[deprecated(x)]]
#define ZL_GETFILEEXTENSION(f) f.substr(f.find_last_of(".") + 1)
#define ZL_FILEEXISTS(f) std::filesystem::exists(f)