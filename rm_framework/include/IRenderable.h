#pragma once
#include "IComponent.h"
class CGameObject;

class IRenderable: public IComponent
{
public:
	IRenderable(void);
	~IRenderable(void);

	virtual void Render()=0;
	virtual float GetBoundingSphereRadius();
	virtual void GetBoundingSphereOffset(CVector3 * result_);
	char * GetType(){return "IRenderable";}

};
