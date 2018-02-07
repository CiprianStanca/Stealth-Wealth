#include "stdafx.h"
#include "FireEnemyMissileBehavior.h"


CFireEnemyMissileBehavior::CFireEnemyMissileBehavior()
{
}


CFireEnemyMissileBehavior::~CFireEnemyMissileBehavior()
{
}

void
CFireEnemyMissileBehavior::Update(float dt_)
{
	float speed = 20.0f;
	char txt[332];
	sprintf_s(txt, "I as a guard should fire right now %d", g_pGame->m_bPlayerSpotted);
	DPrint(txt);

	//check for spacebar press
	if (g_pGame->m_fDelay == 50)
	{
		
		if (g_pGame->m_bPlayerSpotted == true)
		{
			//CInput::Instance()->GetIfKeyDownEvent(DIK_SPACE)
			//g_pGame->m_bPlayerSpotted == true
			DPrint("fire bullet");
			//create a new game object
			CGameObject * missile = new CGameObject();

			//work out position which is right a bit from camera position
			CVector3 mypos = m_pTransform->GetPosition();
			CVector3 rightDirection;
			m_pTransform->GetRightDirection(&rightDirection);
			float offset = 0.1; //how far is gun to right of camera?
			rightDirection *= offset;
			CVector3 gunPos = mypos + rightDirection;

			missile->SetRenderable(new C3DShape());
			missile->GetTransform()->SetPosition(gunPos);
			missile->GetTransform()->SetSize(0.1, 0.1, 0.1);
			missile->GenerateColliderForRenderable();
			g_pGame->AddObject(missile);

			//calculate fire direction
			CVector3  vdir; //declare a vector in which to store the current direction we are facing
			m_pTransform->GetForwardDirection(&vdir);

			//create the missile
			vdir *= speed; //multiply the (normalized) vector by the desired speed
			missile->AddBehavior(new CConstantVelocityBehavior(vdir));
			missile->AddBehavior(new CMissileCheckPlayerCollisionBehavior());
			missile->AddBehavior(new CTimedDeletionBehavior(400));
			g_pGame->m_bPlayerSpotted = false;
			//missile->AddBehavior(new CFallUnderGravityBehavior());


			g_pGame->m_fDelay = 0;
		}
	}
}