#include "stdafx.h"
#include "FallUnderGravityBehavior.h"


CFallUnderGravityBehavior::CFallUnderGravityBehavior(void)
{
	
}


CFallUnderGravityBehavior::~CFallUnderGravityBehavior(void)
{
}


void
CFallUnderGravityBehavior::Update(float dt_)
{
	float gravity =10.0f;

	//update velocity due to gravity
	
	m_Velocity.m_fY -= dt_ * gravity;
	//apply velocity
	//m_pTransform->Translate(0, m_Velocity.m_fY * dt_, 0);

	if (!(m_pTransform->isOnTerrain()))
	{
		m_pTransform->Translate(0, m_Velocity.m_fY * dt_, 0);
		char debugTxt[200];
		sprintf(debugTxt, "velocity of gravity on Y is ----- %2.2f", m_Velocity.m_fY);
		DPrint(debugTxt);


		ICollider * hit = new CSphereCollider();
		ICollider * myCollider = m_pGameObject->GetCollider();
		bool collision = CCollisionManager::Instance()->GetCollision(myCollider, hit);
		if (collision)
		{
			CGameObject * thingWeHit = hit->GetGameObject();
			IRenderable * renWeHit = thingWeHit->GetRenderable();
			char txt[32];
			sprintf(txt, "camera hit a %s", renWeHit->GetType());
			DPrint(txt);
			
			//revert to old pos and old lookat
			m_pTransform->Translate(0, -m_Velocity.m_fY * dt_, 0);; //restore back to old saved position
			m_Velocity.m_fY = 0;
			m_pTransform->ApplyClampToTerrain();
		}
	}
	else
	{
		m_Velocity.m_fY = 0;
	}
}