#pragma once
#include "irenderable.h"
class CSkyBoxRenderable :
	public IRenderable
{
public:
	CSkyBoxRenderable(void);
	~CSkyBoxRenderable(void);
	void Render();
};

