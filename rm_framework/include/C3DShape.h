#pragma once
#include "irenderable.h"

class C3DShape :
	public IRenderable
{
public:
	C3DShape(void);
	~C3DShape(void);
	void Render();
	float GetBoundingSphereRadius();
};

