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

#pragma once
#include "rtComponent.h"

namespace rt
{
	class Line : public Component
	{
	public:
		Line();
		virtual ~Line();

		virtual void Draw(sf::RenderWindow* iRenderWindow);

		void SetPoints(const Vector2f& iFirst, const Vector2f& iSecond);
		void SetBrush(float iThikness, const Color& iColor);
		void SetOutline(float iThikness, const Color& iColor);

		UDeclareUserObject

		static void RegisterMetaClass()
		{
			camp::Class::declare<Line>("Line")
				.base<Component>()
				.constructor0()
				.property("StartPoint", &Line::mFirstPoint)
				.property("EndPoint", &Line::mSecondPoint)
				.property("BrushThikness", &Line::mBrushThikness)
				.property("OutlineThikness", &Line::mOutlineThikness)
				.property("BrushColor", &Line::mBrushColor)
				.property("OutlineColor", &Line::mOutlineColor)
				;
		}

	protected:
		void updateShape();

		sf::Shape	mShape;

		Vector2f	mFirstPoint;
		Vector2f	mSecondPoint;

		float		mBrushThikness;
		float		mOutlineThikness;

		Color		mBrushColor;
		Color		mOutlineColor;
	};
}

CAMP_AUTO_TYPE(rt::Line, &rt::Line::RegisterMetaClass)