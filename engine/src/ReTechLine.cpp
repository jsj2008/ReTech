#include "ReTechCommonIncludes.h"
#include "ReTechLine.h"

namespace rt
{
	Line::Line()
		: mBrushThikness(1), mOutlineThikness(0)
	{
		mClassName = "Line";

		CreateVarProperty("start_point", mFirstPoint);
		CreateVarProperty("end_point", mSecondPoint);
		CreateVarProperty("brush_thikness", mBrushThikness);
		CreateVarProperty("brush_color", mBrushColor);
		CreateVarProperty("outline_thikness", mOutlineThikness);
		CreateVarProperty("outline_color", mOutlineColor);
	}

	Line::~Line()
	{

	}

	void Line::UnSerialize( const YAML::Node& iNode )
	{
		WorldObject::UnSerialize(iNode);

		updateShape();
	}

	void Line::Draw( sf::RenderWindow* iRenderWindow )
	{
		mShape.SetPosition(GetPosition());
		mShape.SetScale(GetScale());
		mShape.SetOrigin(GetOrigin());
		mShape.SetRotation(GetRotation());

		iRenderWindow->Draw(mShape);
	}

	void Line::SetPoints( const sf::Vector2f& iFirst, const sf::Vector2f& iSecond )
	{
		mFirstPoint = iFirst;
		mSecondPoint = iSecond;

		updateShape();
	}

	void Line::SetBrush( float iThikness, const sf::Color& iColor )
	{
		mBrushThikness = iThikness;
		mBrushColor = iColor;

		updateShape();
	}

	void Line::SetOutline( float iThikness, const sf::Color& iColor )
	{
		mOutlineThikness = iThikness;
		mOutlineColor = iColor;

		updateShape();
	}

	void Line::updateShape()
	{
		mShape = sf::Shape::Line(mFirstPoint, mSecondPoint, mBrushThikness, mBrushColor, mOutlineThikness, mOutlineColor);
	}
}