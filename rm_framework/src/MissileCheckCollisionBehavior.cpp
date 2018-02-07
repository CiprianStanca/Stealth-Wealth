#include "stdafx.h"
#include "MissileCheckCollisionBehavior.h"


CMissileCheckCollisionBehavior::CMissileCheckCollisionBehavior(void)
{
}


CMissileCheckCollisionBehavior::~CMissileCheckCollisionBehavior(void)
{
}


void 
CMissileCheckCollisionBehavior::Update(float dt_)
{
//check for collision
	ICollider * hit = new CSphereCollider(); //to store information about hit object
	if (0==hit) return;

	ICollider * myCollider=m_pGameObject->GetCollider();//collider attached to missile
	if (0==myCollider) return;

	bool collision = CCollisionManager::Instance()->GetCollision(myCollider,hit);
	if (collision)
	{
		//find out about the thing we hit
		CGameObject * objWeHit = hit->GetGameObject();
		//get the renderable
		if (0==objWeHit) return;

		IRenderable * rendWeHit = objWeHit->GetRenderable();
		if (0==rendWeHit) return;

		char txt[32];
		sprintf(txt,"missile hit a %s",rendWeHit->GetType());
		DPrint(txt);

		if (strcmp(rendWeHit->GetType(),"CCameraRenderable")==0)
		{
			//we hit the camera

		}
		//else if (strcmp(rendWeHit->GetType(), "CSprite") == 0)
		//{
			//we hit the camera

		//}
		else
		{

		//add a short lived explosion billboard
		CGameObject * pExplosion=new CGameObject();
		pExplosion->GetTransform()->SetPosition(m_pTransform->GetPosition());
        pExplosion->GetTransform()->SetSize(1,1,1);
        pExplosion->SetRenderable(new CSprite());
        pExplosion->SetMaterial(new CColourMaterial(true));
        pExplosion->GetMaterial()->SetTexture(18);//set explosion texture
		pExplosion->GetMaterial()->EnableTransparentDepthSort();
		pExplosion->AddBehavior(new CFaceCameraBehavior());
		pExplosion->AddBehavior(new CSpriteSheetAnimationBehavior(5,4,15));
		pExplosion->AddBehavior(new CTimedDeletionBehavior(20));
		g_pGame->AddObject(pExplosion);

		//call CollisionResponder if there is one
		ICollisionResponder * colres =objWeHit->GetCollisionResponder();
		if (colres) 
			{
			colres->ReactToCollision();
			//remove the missile
			m_pGameObject->TagForDeletion();
			}
		if (objWeHit->m_bIsPlayer == true)
		{
			//player is spotted
			OutputDebugStringA("Player Has BEEEN HIT");
		}
		m_pGameObject->TagForDeletion();
		}



		
	}
}