	

#include "StdAfx.h"
#include "UpdateBoundingSphereBehavior.h"


CUpdateBoundingSphereBehavior::CUpdateBoundingSphereBehavior(void)
{

}

CUpdateBoundingSphereBehavior::~CUpdateBoundingSphereBehavior(void)
{

}
	

void 
CUpdateBoundingSphereBehavior::Update(float dt_)
{
	ICollider * col = m_pGameObject->GetCollider();

	//update position of bsphere based on latest transform
	if (col)
	{
		col->SetPosition(&(m_pTransform->GetPosition()));
		col->SetScale(&(m_pTransform->GetSize3()));
	}
}