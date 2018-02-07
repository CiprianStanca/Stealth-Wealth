#include "stdafx.h"
#include "CollideDeleteBehavior.h"
#include "Input.h"


CCollideDeleteBehavior::CCollideDeleteBehavior(void)
{
	
}


CCollideDeleteBehavior::~CCollideDeleteBehavior(void)
{
}


int score = 0; //initial score
void
CCollideDeleteBehavior::Update(float dt_)
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
		//for debug purposes, printout what we bumped into
		CGameObject * thingWeHit = hit->GetGameObject();
		IRenderable * renWeHit = thingWeHit->GetRenderable();
		char txt[352];
		sprintf(txt, "camera hit a artiffact %s", renWeHit->GetType());
		DPrint(txt);

		if(CInput::Instance()->GetIfKeyDown(DIK_E))
		{
			m_pGameObject->TagForDeletion();
			char txt[32];
			sprintf(txt, "Item has been picked up");
			DPrint(txt);

			//adds the score to the GUI.
			score += 1;

			if (score == 3)
			{
				g_pGame->SetState(eGameStateWon);
			}

		}
		

	}
	

	
}

