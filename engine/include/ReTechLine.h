#ifndef __rtLine_H__
#define __rtLine_H__

#include "ReTechWorldObject.h"

namespace rt
{
	class Line : public WorldObject
	{
	public:
		Line();
		virtual ~Line();

		virtual void UnSerialize(const YAML::Node& iNode);

		virtual void Draw(sf::RenderWindow* iRenderWindow);

		void SetPoints(const sf::Vector2f& iFirst, const sf::Vector2f& iSecond);
		void SetBrush(float iThikness, const sf::Color& iColor);
		void SetOutline(float iThikness, const sf::Color& iColor);

	protected:
		void updateShape();

		sf::Shape		mShape;

		sf::Vector2f	mFirstPoint;
		sf::Vector2f	mSecondPoint;

		float			mBrushThikness;
		float			mOutlineThikness;

		sf::Color		mBrushColor;
		sf::Color		mOutlineColor;
	};
}

#endif