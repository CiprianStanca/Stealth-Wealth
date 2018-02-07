#pragma once
#include "imaterial.h"
class CGUITextureMaterial :
	public IMaterial
{
public:
	CGUITextureMaterial(void);
	~CGUITextureMaterial(void);
	void SetupRendering();
};

