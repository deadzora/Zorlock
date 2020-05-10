#pragma once
#include <memory>
#define GLFW_EXPOSE_NATIVE_WIN32
// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64  */
		#define ZL_PLATFORM_WINDOWS
		/* Direct X only Macro letting Shaders include other shader files from the same directory */
		#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define ZL_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define ZL_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define ZL_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define ZL_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection

#ifdef ZL_DEBUG
	#if defined(ZL_PLATFORM_WINDOWS)
		#define ZL_DEBUGBREAK() __debugbreak()
	#elif defined(ZL_PLATFORM_LINUX)
		#include <signal.h>
		#define ZL_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define ZL_ENABLE_ASSERTS
#else
	#define ZL_DEBUGBREAK()
#endif

#ifdef ZL_ENABLE_ASSERTS
	#define ZL_ASSERT(x, ...) { if(!(x)) { ZL_ERROR("Assertion Failed: {0}", __VA_ARGS__); ZL_DEBUGBREAK(); } }
	#define ZL_CORE_ASSERT(x, ...) { if(!(x)) { ZL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); ZL_DEBUGBREAK(); } }
#else
	#define ZL_ASSERT(x, ...)
	#define ZL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define ZL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define ZL_SCRIPT_EXPORT(...) _attribute__((annotate("se," #__VA_ARGS__)))

namespace Zorlock {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}
