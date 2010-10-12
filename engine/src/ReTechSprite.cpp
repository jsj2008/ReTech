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
#include "ReTechSprite.h"
#include "ReTechResourceManager.h"
#include "ReTechImage.h"

namespace rt
{
	Sprite::Sprite()
	{
		mClassName = "Sprite";

		CreateFuncProperty("sprite", fastdelegate::MakeDelegate(this, &Sprite::SetResource), fastdelegate::MakeDelegate(this, &Sprite::GetResource));
	}

	Sprite::~Sprite()
	{

	}

	void Sprite::Draw( sf::RenderWindow* iRenderWindow )
	{
		mSprite.SetPosition(GetPosition());
		mSprite.SetScale(GetScale());
		mSprite.SetOrigin(GetOrigin());
		mSprite.SetRotation(GetRotation());

		iRenderWindow->Draw(mSprite);
	}

	void Sprite::SetResource( const std::string& iResourceName )
	{
		mResourceName = iResourceName;

		Image* image = UResource(Image, iResourceName);

		if(image)
		{
			image->Load();
			mSprite.SetImage(*image);
		}
	}

	const std::string& Sprite::GetResource()
	{
		return  mResourceName;
	}
}