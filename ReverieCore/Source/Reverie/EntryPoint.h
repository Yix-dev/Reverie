#pragma once
#include <iostream>

#include "Application/Application.h"

extern std::unique_ptr<Reverie::Application> Reverie::CreateApplication(HINSTANCE Instance);

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
#ifdef REVERIE_DEBUG

    if (AllocConsole())
    {
        FILE* fp;

        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONOUT$", "w", stderr);
        freopen_s(&fp, "CONIN$", "r", stdin);

        std::cout.clear();
        std::cerr.clear();
        std::cin.clear();

        SetConsoleTitleA("Reverie Debug Console");
    }
#endif
	std::unique_ptr<Reverie::Application> application = Reverie::CreateApplication(instance);
	application->Run();

}	