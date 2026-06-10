#pragma once
#include "Application/Application.h"

extern std::unique_ptr<Reverie::Application> Hazel::CreateApplication(HINSTANCE Instance);

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	Reverie::Application* application = CreateApplication(instance);
	application->Run();

}