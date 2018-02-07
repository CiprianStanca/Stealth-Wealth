#pragma once
#include "IMaterial.h"

class CColourMaterial :
	public IMaterial
{
public:
	CColourMaterial(bool bAdditive_=false);
	
	~CColourMaterial(void);
	void SetupRendering();
	void SetColour(float r_, float g_, float b_, float a_=1.0f);
	void SetTexture(int textureID_);
	int GetTexture(){ return m_iTextureID; }

private:
	float m_fRed;
	float m_fGreen;
	float m_fBlue;
	float m_fAlpha;
	int m_iTextureID;
	bool m_bAdditiveBlending;
};
