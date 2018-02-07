#pragma once
#include "ColourMaterial.h"
class LitMaterial :
	public CColourMaterial
{
public:
	LitMaterial(void);
	~LitMaterial(void);
	void SetupRendering();
};

