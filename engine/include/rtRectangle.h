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

#include "rtWorldObject.h"

namespace rt
{
	class Rectangle : public WorldObject
	{
	public:
		Rectangle();
		virtual ~Rectangle();

		virtual void UnSerialize(const YAML::Node& iNode);

		virtual void Draw(sf::RenderWindow* iRenderWindow);

		void SetRect(const FloatRect& iRect);
		void SetBrush(const Color& iColor);
		void SetOutline(float iThikness, const Color& iColor);

		static void RegisterMetaClass()
		{
			camp::Class::declare<Rectangle>("Rectangle")
				.base<WorldObject>()
				.constructor0()
				.property("Rect", &Rectangle::mRect)
				.property("BrushColor", &Rectangle::mBrushColor)
				.property("OutlineThikness", &Rectangle::mOutlineThikness)
				.property("OutlineColor", &Rectangle::mOutlineColor);
		}

	protected:
		void updateShape();

		sf::Shape	mShape;

		FloatRect	mRect;

		float		mOutlineThikness;

		Color		mBrushColor;
		Color		mOutlineColor;
	};
}

CAMP_AUTO_TYPE(rt::Rectangle, &rt::Rectangle::RegisterMetaClass)