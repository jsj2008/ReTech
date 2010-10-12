/*
Copyright (c) 2010 Alexander Novitsky                                             

Permission is hereby granted, free of charge, to any person obtaining a copy  
of this software and associated documentation files (the "Software"), to deal 
in the Software without restriction, including without limitation the rights  
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell     
copies of the Software, and to permit persons to whom the Software is         
furnished to do so, subject to the following conditions:                      

The above copyright notice and this permission notice shall be included in    
all copies or substantial portions of the Software.                           

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN     
THE SOFTWARE.
*/

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