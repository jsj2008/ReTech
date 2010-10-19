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
	class Text : public Component
	{
	public:
		Text();
		virtual ~Text();

		virtual void Draw(sf::RenderWindow* iRenderWindow);

		void SetFont(const std::string& iResourceName);
		std::string GetFont();

		void SetString(const std::string& iString);
		std::string GetString();

		void SetCharacterSize(unsigned int iSize);
		unsigned int GetCharacterSize();

		UDeclareUserObject

		static void RegisterMetaClass()
		{
			camp::Class::declare<Text>("Text")
				.base<Component>()
				.constructor0()
				.property("Font", &Text::GetFont, &Text::SetFont)
				.property("String", &Text::GetString, &Text::SetString)
				.property("CharacterSize", &Text::GetCharacterSize, &Text::SetCharacterSize);
		}

	protected:
		sf::Text mText;

		std::string mResourceName;
	};
}

CAMP_AUTO_TYPE(rt::Text, &rt::Text::RegisterMetaClass)