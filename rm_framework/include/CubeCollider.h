#pragma once
#include "icollider.h"

class CCubeCollider:
	public ICollider
{
public:
	CCubeCollider(void);
	~CCubeCollider(void);


	bool CheckForCollision(ICollider * in_);
	bool RespondToCollision();
	char * GetType() { return "CCubeCollider"; }
	void Render();
	void AddedToGameObject();
	void SetAxisUsed(char axis);

private:
	bool m_bUseXAxis; // if false then use z axis
	float m_fMinX;
	float m_fMaxX;
	float m_fMinY;
	float m_fMaxY;
	float m_fMinZ;
	float m_fMaxZ;
};

