#ifndef __rtSprite_H__
#define __rtSprite_H__

#include "ReTechWorldObject.h"

namespace rt
{
	class Sprite : public WorldObject
	{
	public:
		Sprite();
		virtual ~Sprite();

		virtual void Draw(sf::RenderWindow* iRenderWindow);

		void SetResource(const std::string& iResourceName);
		const std::string& GetResource(); 

		protected:
			sf::Sprite mSprite;

			std::string mResourceName;
	};
}

#endif