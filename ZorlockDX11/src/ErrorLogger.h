#pragma once
#include "StringConverter.h"
#include <Windows.h>

class ErrorLogger
{
public:
	static void Log(std::string message);
	static void log(HRESULT hr, std::string message);
};

