#pragma once
#include "irenderable.h"
class CCamera :
	public IRenderable
{
public:
	CCamera(void);
	~CCamera(void);
	void Render();
	void AddedToGameObject();
	void ToggleBirdsEyeView();
	float GetBoundingSphereRadius();
	char * GetType(){return "CCameraRenderable";}

private:
	bool m_bBirdsEyeView;
	
};

