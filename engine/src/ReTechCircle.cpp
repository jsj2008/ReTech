#include "ReTechCommonIncludes.h"
#include "ReTechCircle.h"

namespace rt
{
	Circle::Circle()
		: mRadius(1), mOutlineThikness(0)
	{
		mClassName = "Circle";

		CreateVarProperty("center_point", mCenterPoint);
		CreateVarProperty("radius", mRadius);
		CreateVarProperty("brush_color", mBrushColor);
		CreateVarProperty("outline_thikness", mOutlineThikness);
		CreateVarProperty("outline_color", mOutlineColor);
	}

	Circle::~Circle()
	{

	}

	void Circle::UnSerialize( const YAML::Node& iNode )
	{
		WorldObject::UnSerialize(iNode);

		updateShape();
	}

	void Circle::Draw( sf::RenderWindow* iRenderWindow )
	{
		mShape.SetPosition(GetPosition());
		mShape.SetScale(GetScale());
		mShape.SetOrigin(GetOrigin());
		mShape.SetRotation(GetRotation());

		iRenderWindow->Draw(mShape);
	}

	void Circle::SetCenter( const sf::Vector2f& iCenter, float iRadius )
	{
		mCenterPoint = iCenter;
		mRadius = iRadius;

		updateShape();
	}

	void Circle::SetBrush( const sf::Color& iColor )
	{
		mBrushColor = iColor;

		updateShape();
	}

	void Circle::SetOutline( float iThikness, const sf::Color& iColor )
	{
		mOutlineThikness = iThikness;
		mOutlineColor = iColor;

		updateShape();
	}

	void Circle::updateShape()
	{
		mShape = sf::Shape::Circle(mCenterPoint, mRadius, mBrushColor, mOutlineThikness, mOutlineColor);
	}
}