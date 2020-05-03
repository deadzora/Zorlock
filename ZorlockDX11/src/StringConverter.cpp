#include "StringConverter.h"
#include <algorithm>
#include <string>
#include <filesystem>

std::string StringConverter::WidetoString(const wchar_t * str)
{
	std::wstring ws(str);
	std::string strng(ws.begin(), ws.end());
	return strng;
}

std::wstring StringConverter::StringtoWide(std::string str)
{
	std::wstring wide_string(str.begin(), str.end());
	return wide_string;
}

std::string StringConverter::GetDirectory(const std::string & filepath)
{
	size_t off1 = filepath.find_last_of('\\');
	size_t off2 = filepath.find_last_of('/');
	if (off1 == std::string::npos && off2 == std::string::npos)
	{
		return "";
	}
	if (off1 == std::string::npos)
	{
		return filepath.substr(0, off2);
	}
	if (off2 == std::string::npos)
	{
		return filepath.substr(0, off1);
	}

	return filepath.substr(0, std::max(off1, off2));
}

std::string StringConverter::GetFileExtension(const std::string & filename)
{
	size_t off = filename.find_last_of('.');
	if (off == std::string::npos)
	{
		return {};
	}

	return std::string(filename.substr(off + 1));
}




bool StringConverter::FileExists(const std::string& name) {
	
	return std::filesystem::exists(name);
	//std::filesystem::exists("helloworld.txt");
}





