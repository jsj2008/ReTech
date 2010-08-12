#ifndef __rtText_H__
#define __rtText_H__

#include "ReTechWorldObject.h"

namespace rt
{
	class Text : public WorldObject
	{
	public:
		Text();
		virtual ~Text();

		virtual void Draw(sf::RenderWindow* iRenderWindow);

		void SetFont(const std::string& iResourceName);
		const std::string& GetFont();

	protected:
		sf::Text mText;

		std::string mResourceName;
	};
}

#endif