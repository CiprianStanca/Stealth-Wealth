#pragma once
#include "icollider.h"

class CSphereCollider :
	public ICollider
{
public:
	CSphereCollider(float rad_=0.0f);
	~CSphereCollider(void);
	void SetTrigger();
	void Render();
	 bool  CheckForCollision(ICollider * insphere_);
	 bool CheckForCollisionWithRay(CVector3 raystart_,CVector3 raydirection_, float raylength_,CVector3 * hitPoint_);
	 float GetScaledRadius(); //takes into account current transform
	 bool RespondToCollision();
	 char * GetType(){return "SphereCollider";}

private:
	float m_fRadius;//original game object without any scaling
	float m_fScaledRadius; //scaled according to current transform
	bool m_bTrigger;
	//void SetTrigger();

};