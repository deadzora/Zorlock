#pragma once
#include <string>
#include <filesystem>


class StringConverter
{
public:
	static std::string WidetoString(const wchar_t * str);
	static std::wstring StringtoWide(std::string str);
	static std::string GetDirectory(const std::string & filepath);
	static std::string GetFileExtension(const std::string & filename);
	static bool FileExists(const std::string & name);
};


