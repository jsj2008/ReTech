#ifndef __rtRectangle_H__
#define __rtRectangle_H__

#include "ReTechWorldObject.h"

namespace rt
{
	class Rectangle : public WorldObject
	{
	public:
		Rectangle();
		virtual ~Rectangle();

		virtual void UnSerialize(const YAML::Node& iNode);

		virtual void Draw(sf::RenderWindow* iRenderWindow);

		void SetRect(const sf::FloatRect& iRect);
		void SetBrush(const sf::Color& iColor);
		void SetOutline(float iThikness, const sf::Color& iColor);

	protected:
		void updateShape();

		sf::Shape		mShape;

		sf::FloatRect	mRect;

		float			mOutlineThikness;

		sf::Color		mBrushColor;
		sf::Color		mOutlineColor;
	};
}

#endif