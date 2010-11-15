#pragma once

#include "rtTool.h"

namespace rt
{
	class ParticleEditor : public Tool
	{
	public:
		ParticleEditor();
		virtual ~ParticleEditor();

		virtual void Update(float iTimeElapsed);
		virtual void Render();
		virtual bool HandleEvent(const sf::Event& iEvent);

	protected:
	};
}