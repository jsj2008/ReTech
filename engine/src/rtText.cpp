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
#include "rtText.h"
#include "rtFont.h"
#include "rtWorldObject.h"

namespace rt
{
	Text::Text()
	{
	}

	Text::~Text()
	{

	}

	void Text::Draw( sf::RenderWindow* iRenderWindow )
	{
		mText.SetPosition(mOwner->GetPosition());
		mText.SetScale(mOwner->GetScale());
		mText.SetOrigin(mOwner->GetOrigin());
		mText.SetRotation(mOwner->GetRotation());


		iRenderWindow->Draw(mText);
	}

	void Text::SetFont( const std::string& iResourceName )
	{
		mResourceName = iResourceName;

		Font* font = UResource(Font, iResourceName);
		font->Load();

		mText.SetFont(*font);
	}

	std::string Text::GetFont()
	{
		return mResourceName;
	}

	void Text::SetString( const std::string& iString )
	{
		mText.SetString(iString);
	}

	std::string Text::GetString()
	{
		return mText.GetString();
	}

	void Text::SetCharacterSize( unsigned int iSize )
	{
		mText.SetCharacterSize(iSize);
	}

	unsigned int Text::GetCharacterSize()
	{
		return mText.GetCharacterSize();
	}
}