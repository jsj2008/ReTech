#ifndef __rtCircle_H__
#define __rtCircle_H__

#include "ReTechWorldObject.h"

namespace rt
{
	class Circle : public WorldObject
	{
	public:
		Circle();
		virtual ~Circle();

		virtual void UnSerialize(const YAML::Node& iNode);

		virtual void Draw(sf::RenderWindow* iRenderWindow);

		void SetCenter(const sf::Vector2f& iCenter, float iRadius);
		void SetBrush(const sf::Color& iColor);
		void SetOutline(float iThikness, const sf::Color& iColor);

	protected:
		void updateShape();

		sf::Shape		mShape;

		sf::Vector2f	mCenterPoint;
		float			mRadius;

		float			mOutlineThikness;

		sf::Color		mBrushColor;
		sf::Color		mOutlineColor;
	};
}

#endif