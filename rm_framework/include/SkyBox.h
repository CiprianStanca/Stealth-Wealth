#pragma once
#include "irenderable.h"
class CSkyBox :
	public IRenderable
{
public:
	CSkyBox(void);
	~CSkyBox(void);
	void Render();
};

