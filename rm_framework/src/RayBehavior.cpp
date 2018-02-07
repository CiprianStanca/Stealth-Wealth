#include "stdafx.h"
#include "RayBehavior.h"




CRayBehavior::CRayBehavior(void)
{

}


CRayBehavior::~CRayBehavior(void)
{
}

void
CRayBehavior::Update(float dt_)
{

	CVector3 fwd;
	CVector3 pos;
	pos =m_pTransform->GetPosition();
	m_pTransform->GetForwardDirection(&fwd);

	CSphereCollider thingWehit;
	//check for collision
	CVector3 hitPoint;
	bool collision = CCollisionManager::Instance()->GetCollisionWithRay(pos, fwd,10.0f,&thingWehit,&hitPoint);
	if (collision)
	{
		//call CollisionResponder if there is one
		CGameObject * objWeHit = thingWehit.GetGameObject();
		IRenderable * renWehit =objWeHit->GetRenderable();
		if (renWehit)
			{
				DPrint("ray hit a...");
				DPrint(renWehit->GetType());
			}
		if (objWeHit)
		{
		ICollisionResponder * colres =objWeHit->GetCollisionResponder();
		if (colres) colres->ReactToCollision();
		//create a temporary explosion at the point of impact


			CGameObject * pExplosion=new CGameObject();
			pExplosion->GetTransform()->SetPosition(hitPoint);
			pExplosion->GetTransform()->SetSize(1,1,1);
			pExplosion->SetRenderable(new CSprite());
			pExplosion->SetMaterial(new CColourMaterial(true));
			pExplosion->GetMaterial()->SetTexture(17); //explosion graphic
			pExplosion->AddBehavior(new CSpriteSheetAnimationBehavior(5,4,15));
			pExplosion->AddBehavior(new CFaceCameraBehavior());
			pExplosion->AddBehavior(new CTimedDeletionBehavior(50));
			g_pGame->AddObject(pExplosion);
			pExplosion->GetMaterial()->EnableTransparentDepthSort();
		}
	}

}