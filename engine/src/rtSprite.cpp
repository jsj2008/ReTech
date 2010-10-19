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
#include "rtSprite.h"
#include "rtResourceManager.h"
#include "rtImage.h"
#include "rtWorldObject.h"

namespace rt
{
	Sprite::Sprite()
	{
	}

	Sprite::~Sprite()
	{

	}

	void Sprite::Draw( sf::RenderWindow* iRenderWindow )
	{
		mSprite.SetPosition(mOwner->GetPosition());
		mSprite.SetScale(mOwner->GetScale());
		mSprite.SetOrigin(mOwner->GetOrigin());
		mSprite.SetRotation(mOwner->GetRotation());

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