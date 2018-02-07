#include "stdafx.h"	
#include "FireMissileBehavior.h"

CFireMissileBehavior::CFireMissileBehavior(void)
{

}

CFireMissileBehavior::~CFireMissileBehavior(void)
{

}

void 
CFireMissileBehavior::Update(float dt_)
{
	float speed =20.0f;

	if (CInput::Instance()->GetIfKeyDownEvent(DIK_R))
	{
		g_pGame->ammo = 30;
	}

	//check for spacebar press
	if (g_pGame->ammo > 0)
	if (CInput::Instance()->GetIfKeyDownEvent(DIK_SPACE) || ((GetKeyState(VK_LBUTTON)) & 0x100) != 0)
	{
		if (g_pGame->ammo > 0)
		{
			float randPitch = rand() % 3;
			float randYaw = rand() % 3;
			m_pTransform->incrementPitch(randPitch - 1);
			m_pTransform->IncrementYaw(randYaw - 1);
			g_pGame->ammo = g_pGame->ammo - 1;

		}
		DPrint ("fire bullet");
		//create a new game object
		CGameObject * missile = new CGameObject();
		
		//work out position which is right a bit from camera position
		CVector3 mypos =m_pTransform->GetPosition();
		CVector3 rightDirection;
		m_pTransform->GetRightDirection(&rightDirection);
		float offset = 0.1; //how far is gun to right of camera?
		rightDirection *=offset;
		CVector3 gunPos = mypos + rightDirection;
		

		missile->GetTransform()->SetPosition(gunPos);
		missile->GetTransform()->SetSize(0.1,0.1,0.1);
		missile->SetRenderable(new C3DShape());
		missile->GenerateColliderForRenderable();
		g_pGame->AddObject(missile);
		
		//calculate fire direction
		CVector3  vdir; //declare a vector in which to store the current direction we are facing
		m_pTransform->GetForwardDirection(&vdir);

		//create the missile
		vdir*=speed; //multiply the (normalized) vector by the desired speed
		missile->AddBehavior(new CConstantVelocityBehavior(vdir));
		missile->AddBehavior(new CMissileCheckCollisionBehavior());
		missile->AddBehavior(new CTimedDeletionBehavior(300));
		//missile->AddBehavior(new CFallUnderGravityBehavior());


		
	}
}