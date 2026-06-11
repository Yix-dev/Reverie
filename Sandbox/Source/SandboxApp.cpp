#include "Core.h"

class SandboxApp : public Reverie::Application
{
public:
	SandboxApp(HINSTANCE Instance)
		:Application(Instance)
	{
		
	}
	~SandboxApp() override
	{

	}
};

std::unique_ptr<Reverie::Application> Reverie::CreateApplication(HINSTANCE Instance)
{
	return std::make_unique<SandboxApp>(Instance);
}