#pragma once
namespace DX11Raz
{
#define RAZPTR std::shared_ptr
	template<typename T, typename ... Args>
	constexpr RAZPTR<T> CreateZRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}