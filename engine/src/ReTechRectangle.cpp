#include "ReTechCommonIncludes.h"
#include "ReTechRectangle.h"

namespace rt
{
	Rectangle::Rectangle()
		: mOutlineThikness(0)
	{
		mClassName = "Rectangle";

		CreateVarProperty("rect", mRect);
		CreateVarProperty("brush_color", mBrushColor);
		CreateVarProperty("outline_thikness", mOutlineThikness);
		CreateVarProperty("outline_color", mOutlineColor);
	}

	Rectangle::~Rectangle()
	{

	}

	void Rectangle::UnSerialize( const YAML::Node& iNode )
	{
		WorldObject::UnSerialize(iNode);

		updateShape();
	}

	void Rectangle::Draw( sf::RenderWindow* iRenderWindow )
	{
		mShape.SetPosition(GetPosition());
		mShape.SetScale(GetScale());
		mShape.SetOrigin(GetOrigin());
		mShape.SetRotation(GetRotation());

		iRenderWindow->Draw(mShape);
	}

	void Rectangle::SetRect( const sf::FloatRect& iRect)
	{
		mRect = iRect;

		updateShape();
	}

	void Rectangle::SetBrush(const sf::Color& iColor )
	{
		mBrushColor = iColor;

		updateShape();
	}

	void Rectangle::SetOutline( float iThikness, const sf::Color& iColor )
	{
		mOutlineThikness = iThikness;
		mOutlineColor = iColor;

		updateShape();
	}

	void Rectangle::updateShape()
	{
		mShape = sf::Shape::Rectangle(mRect, mBrushColor, mOutlineThikness, mOutlineColor);
	}
}