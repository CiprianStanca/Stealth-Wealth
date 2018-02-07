#pragma once
#include "node.h"
#include <vector>
#include <ICollider.h>

class IRenderable;
class IMaterial;
class IBehavior;
class CTransform;
class ICollider;
class ICollisionResponder;


extern CGame * g_pGame; //the global game object

class CGameObject :
	public CNode
{
public:
	CGameObject(void);
	~CGameObject(void);

	void Render();
	void Update(float dt_);
	void RenderRecursive();
	void UpdateRecursive(float dt_);
	void SetActive(bool onoff){m_bActive=onoff;}

	void SetRenderable(IRenderable * pRenderable_);
	void SetMaterial(IMaterial * pMaterial_);
	void AddBehavior(IBehavior * pBehavior_);
	void SetTransform(CTransform * pTransform_);
	void SetCollider(ICollider * pCollider_);
	void SetCollisionResponder(ICollisionResponder * pResToCol_);

	void GenerateColliderForRenderable(ICollider::eColliderType type=ICollider::eColliderTypeSphere);

	IRenderable * GetRenderable();
	IMaterial * GetMaterial();
	//IBehavior * GetBehavior();
	CTransform * GetTransform();
	ICollider * GetCollider();
	ICollisionResponder * GetCollisionResponder();

	void TagForDeletion(){m_bTaggedForDeletion=true;}
	bool bGetTaggedForDeletion(){return m_bTaggedForDeletion;}
	bool m_bIsPlayer = false;
	float GetDistanceFromCamera();
	void CalcDistanceFromCamera();

private:

	IRenderable * m_pRenderable;
	IMaterial * m_pMaterial;
	vector <IBehavior *> m_vBehaviors;
	CTransform * m_pTransform;
	ICollider * m_pCollider;
	ICollisionResponder * m_pCollisionResponder;
	
	bool m_bActive;
	bool m_bTaggedForDeletion;
	float m_fDistanceFromCamera;
};
