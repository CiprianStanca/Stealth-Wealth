#pragma once
#include "icomponent.h"

class ICollider :
	public IComponent
{
public:

	enum eColliderType{
		eColliderTypeSphere,
		eColliderTypePlane,
		eColliderTypeCube,
		eColliderTypeLadder,
	};

	ICollider(void);
	~ICollider(void);
	virtual void Render()=0;
	virtual bool CheckForCollision(ICollider * in_)=0;
	virtual bool CheckForCollisionWithRay(CVector3 raystart_,CVector3 raydirection_, float raylength_, CVector3 * hitPoint_){return 0;}
	void SetPosition(CVector3 * pos_);
	void SetScale(CVector3 *scal_);
	void SetTrigger();
	virtual bool RespondToCollision()=0;//return true to mean block passage of objects
	void AddedToGameObject();
	char * GetType(){return "ICollider";}

	CVector3 m_vPosition;
	CVector3 m_vScale;
	bool m_bIsTrigger = false; //like in Unity, objects set to be a trigger allow objects to pass through


};