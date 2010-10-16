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

namespace rt
{
	class Vector2f : public sf::Vector2f
	{
		float& GetX(){ return x; }
		float& GetY(){ return y; }

	public:
		static void RegisterMetaClass()
		{
			camp::Class::declare<Vector2f>("Vector2f")
				.property("X", &Vector2f::GetX)
				.property("Y", &Vector2f::GetY);
		}
	};

	class FloatRect : public sf::FloatRect
	{
		float& GetLeft(){ return Left; }
		float& GetTop(){ return Top; }
		float& GetWidth(){ return Width; }
		float& GetHeight(){ return Height; }

	public:
		static void RegisterMetaClass()
		{
			camp::Class::declare<FloatRect>("Vector2f")
				.property("Left", &FloatRect::GetLeft)
				.property("Top", &FloatRect::GetTop)
				.property("Width", &FloatRect::GetWidth)
				.property("Height", &FloatRect::GetHeight);
		}
	};

	class Color : public sf::Color
	{
		sf::Uint8& GetR(){ return r; }
		sf::Uint8& GetG(){ return g; }
		sf::Uint8& GetB(){ return b; }
		sf::Uint8& GetA(){ return a; }

	public:
		static void RegisterMetaClass()
		{
			camp::Class::declare<Color>("Color")
				.property("R", &Color::GetR)
				.property("G", &Color::GetG)
				.property("B", &Color::GetB)
				.property("A", &Color::GetA);
		}
	};
}

CAMP_AUTO_TYPE(rt::Vector2f, &rt::Vector2f::RegisterMetaClass)
CAMP_AUTO_TYPE(rt::FloatRect, &rt::FloatRect::RegisterMetaClass)
CAMP_AUTO_TYPE(rt::Color, &rt::Color::RegisterMetaClass)