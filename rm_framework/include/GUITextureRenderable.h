#pragma once
#include "irenderable.h"
class CGUITextureRenderable :
	public IRenderable
{
public:
	CGUITextureRenderable();
	~CGUITextureRenderable(void);
	void Render();
	float GetRadius(){return 0.0f;}
	char * GetType(){return "GUITextureRenderable";}
};

