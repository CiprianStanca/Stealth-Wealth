#pragma once
#include "icollider.h"


class CPlaneCollider :
	public ICollider
{
public:
	CPlaneCollider(void);
	~CPlaneCollider(void);


	bool CheckForCollision(ICollider * in_);
	bool CheckForCollisionWithRay(CVector3 raystart_, CVector3 raydirection_, float raylength_, CVector3 * hitPoint_);
	bool RespondToCollision();
	char * GetType(){return "CPlaneCollider";}
	void Render();
	void AddedToGameObject();
	void SetAxisUsed(char axis);

private:
	bool m_bUseXAxis; // if false then use z axis
	bool m_bUseZAxis;
	float m_fMinX;
	float m_fMaxX;
	float m_fMinY;
	float m_fMaxY;
	float m_fMinZ;
	float m_fMaxZ;
};

