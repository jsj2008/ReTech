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

#include "rtCommonIncludes.h"
#include "rtCircle.h"
#include "rtWorldObject.h"

namespace rt
{
	Circle::Circle()
		: mRadius(1), mOutlineThikness(0)
	{
	}

	Circle::~Circle()
	{

	}

	void Circle::Draw( sf::RenderWindow* iRenderWindow )
	{
		mShape.SetPosition(mOwner->GetPosition());
		mShape.SetScale(mOwner->GetScale());
		mShape.SetOrigin(mOwner->GetOrigin());
		mShape.SetRotation(mOwner->GetRotation());

		iRenderWindow->Draw(mShape);
	}

	void Circle::SetCenter( const Vector2f& iCenter, float iRadius )
	{
		mCenterPoint = iCenter;
		mRadius = iRadius;

		updateShape();
	}

	void Circle::SetBrush( const Color& iColor )
	{
		mBrushColor = iColor;

		updateShape();
	}

	void Circle::SetOutline( float iThikness, const Color& iColor )
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