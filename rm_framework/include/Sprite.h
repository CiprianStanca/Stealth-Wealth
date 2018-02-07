#pragma once
#include "irenderable.h"

class CSprite :
	public IRenderable
{
public:
	CSprite();
	~CSprite(void);
	void Render();
	void SetUV(float u0_, float u1_,float v0_, float v1_);
	float GetBoundingSphereRadius();
	char * GetType(){return "CSprite";}
private:
	float m_fU0;
	float m_fU1;
	float m_fV0;
	float m_fV1;
	
};
