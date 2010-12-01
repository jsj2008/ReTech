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
#include "rtParticleEditor.h"
#include "rtGuiManager.h"
#include "rtParticleEditorScreen.h"

namespace rt
{
	ParticleEditor::ParticleEditor()
	{
		rt::GuiManager::Get()->AddScreen("ParticleEditor", new ParticleEditorScreen(this));
	}

	ParticleEditor::~ParticleEditor()
	{

	}

	void ParticleEditor::Update(float iTimeElapsed)
	{

	}

	void ParticleEditor::Render()
	{

	}

	bool ParticleEditor::HandleEvent(const sf::Event& iEvent)
	{
		return true;
	}

	void ParticleEditor::OnEnabled()
	{
		rt::GuiManager::Get()->ChangeScreen("ParticleEditor");
	}

	void ParticleEditor::OnDisabled()
	{
		rt::GuiManager::Get()->PopScreen();
	}
}