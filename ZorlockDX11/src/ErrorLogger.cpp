#include "ErrorLogger.h"
#include "StringConverter.h"
#include <comdef.h>

void ErrorLogger::Log(std::string message)
{
	std::string error_message = "Error: " + message;
	MessageBoxA(NULL, error_message.c_str(), "Error", MB_ICONERROR);
}

void ErrorLogger::log(HRESULT hr, std::string message)
{
	_com_error error(hr);
	std::wstring error_message = L"Error: " + StringConverter::StringtoWide(message) + L"\n" + StringConverter::StringtoWide(std::string("yo mama"));
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}
