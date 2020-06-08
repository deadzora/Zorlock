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
#include <optional>
#include <unordered_set>
#include <typeindex>
#include "Zorlock/Core/Log.h"

#include "Zorlock/Debug/Instrumentor.h"

#ifdef ZL_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#define ZL_DEPRECATED(x) [[deprecated(x)]]
#define ZL_GETFILEEXTENSION(f) f.substr(f.find_last_of(".") + 1)
#define ZL_FILEEXISTS(f) std::filesystem::exists(f)

using TypeInfoRef = std::reference_wrapper<const std::type_info>;
struct Hasher {
	std::size_t operator()(TypeInfoRef code) const
	{
		return code.get().hash_code();
	}
};
struct EqualTo {
	bool operator()(TypeInfoRef lhs, TypeInfoRef rhs) const
	{
		return lhs.get() == rhs.get();
	}
};

//See description below about the usage.
template <typename T>
struct TypeName
{
	static const char* Get()
	{
		return typeid(T).name();
	}
};


static std::unordered_map<TypeInfoRef, std::string, Hasher, EqualTo> AssetTypes;
//So this cool define let's me generate a string from the typename, then i can pass that to the asset manager
//this way i know what kind of asset i'm saving and loading.
//USAGE:
//put ZL_ENABLE_TYPENAME(MyClass) after your class declare in your header.

#define ZL_ENABLE_TYPENAME(A) template <> struct TypeName<A> { static const char *Get() {  AssetTypes[typeid(A)] = #A; return #A; }};
#define ZL_GETTYPENAME(A) TypeName<A>::Get();
#define ZL_GETTYPEID(S) Assettype_names[S]->hash_code()

