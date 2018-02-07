#pragma once
#include "ColourMaterial.h"
class CSkyBoxMaterial :
	public CColourMaterial
{
public:
	CSkyBoxMaterial(void);
	~CSkyBoxMaterial(void);
	void SetupRendering();
};

