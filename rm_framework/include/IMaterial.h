#pragma once
#include "IComponent.h"

class IMaterial: public IComponent
{
public:
	IMaterial(void);
	~IMaterial(void);
	virtual void SetupRendering()=0;
	virtual void SetColour(float r_, float g_, float b_, float a_=1.0f)=0;
	virtual void SetTexture(int textureID_)=0;
	void EnableTransparentDepthSort();
	bool GetIfUsesTransparencyDepthSort(){return m_bTransparent;}
	virtual int GetTexture() = 0;

private:
	bool m_bTransparent;
};
