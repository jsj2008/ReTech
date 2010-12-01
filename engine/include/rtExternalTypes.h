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

#include "rtDefines.h"

namespace rt
{
	class Vector2f : public sf::Vector2f
	{
		UWriteableProperyOverride(X, float, x)
		UWriteableProperyOverride(Y, float, y)

 		UDesc_Begin(Vector2f)
		UDesc_Constructor
 		UDesc_WriteableProperty(X)
 		UDesc_WriteableProperty(Y)
 		UDesc_End
	};

	class FloatRect : public sf::FloatRect
	{
		UWriteableProperyOverride(Left, float, Left)
		UWriteableProperyOverride(Top, float, Top)
		UWriteableProperyOverride(Width, float, Width)
		UWriteableProperyOverride(Height, float, Height)

		UDesc_Begin(FloatRect)
		UDesc_Constructor
		UDesc_WriteableProperty(Left)
		UDesc_WriteableProperty(Top)
		UDesc_WriteableProperty(Width)
		UDesc_WriteableProperty(Height)
		UDesc_End
	};

	class Color : public sf::Color
	{
		UWriteableProperyOverride(R, sf::Uint8, r)
		UWriteableProperyOverride(G, sf::Uint8, g)
		UWriteableProperyOverride(B, sf::Uint8, b)
		UWriteableProperyOverride(A, sf::Uint8, a)

		UDesc_Begin(Color)
		UDesc_Constructor
		UDesc_WriteableProperty(R)
		UDesc_WriteableProperty(G)
		UDesc_WriteableProperty(B)
		UDesc_WriteableProperty(A)
		UDesc_End
	};
}

UDesc_AutoType(Vector2f)
UDesc_AutoType(FloatRect)
UDesc_AutoType(Color)