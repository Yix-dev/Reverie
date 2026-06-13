#pragma once
#include "Reverie/System.h"

namespace Reverie::Audio
{
	class AudioSystem : public System
	{
	public:
		AudioSystem() : System() {}
		~AudioSystem() override {}

		void Initialize(Eventbus* eventbus) override;
		void OnUpdate() override;
		void Shutdown() override;
	};
}
