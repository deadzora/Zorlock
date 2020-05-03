#define USING_MAIN_TESTMODE
#include "AppWindow.h"
#include "EditorWindow.h"



#ifndef ZL_BUILD_DLL
int main()
{
#ifdef USING_MAIN_TESTMODE
	AppWindow app;
	if (app.init())
	{
		while (app.isRunning())
		{
			app.broadcast();
		}
	}
#else
	EditorWindow app;
	app.WindowName = "Editor";
	if (app.init())
	{
		while (app.isRunning())
		{
			app.broadcast();
		}
	}
#endif
	return 0;
}
#endif
