#include "stdafx.h"
#include "PlayerSpotted.h"


CPlayerSpotted::CPlayerSpotted()
{
}


CPlayerSpotted::~CPlayerSpotted()
{
}
void
CPlayerSpotted::Update(float dt_)
{
	//checks for collision with object

	//update position of collider
	//ICollider * col = m_pGameObject->GetCollider();
	//CVector3 pos = m_pTransform->GetPosition();
	//if (col) col->SetPosition(&pos);
	
	


		//check for collision
		ICollider * hit = new CSphereCollider();
		ICollider * myCollider = m_pGameObject->GetCollider();
		bool collision = CCollisionManager::Instance()->GetCollision(myCollider, hit);

		if (collision)
		{
			CGameObject * objWeHit = hit->GetGameObject();
			if (0 == objWeHit) return;
			IRenderable * rendWeHit = objWeHit->GetRenderable();
			if (0 == rendWeHit) return;
			if (strcmp(rendWeHit->GetType(), "C3DShape") == 0)
			{
				//we hit the camera
				//g_pGame->m_bPlayerSpotted = false;
			}
			else
			{
				g_pGame->m_fDelay = g_pGame->m_fDelay + 1;
				//for debug purposes, printout what we bumped into
				CGameObject * thingWeHit = hit->GetGameObject();
				IRenderable * renWeHit = thingWeHit->GetRenderable();

				g_pGame->m_bPlayerSpotted = true;
				char txt[332];
				sprintf(txt, "I sense the player around me %d", g_pGame->m_bPlayerSpotted);
				DPrint(txt);
			}
		}
		else
		{
			g_pGame->m_bPlayerSpotted = false;

		}

}
