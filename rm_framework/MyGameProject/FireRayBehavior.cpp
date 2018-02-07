#include "stdafx.h"
#include "FireRayBehavior.h"


CFireRayBehavior::CFireRayBehavior(void)
{
}


CFireRayBehavior::~CFireRayBehavior(void)
{
}


void 
CFireRayBehavior::Update(float dt_)
{


	//check for spacebar press or left clicking
	if (CInput::Instance()->GetIfKeyDownEvent(DIK_SPACE) || ((GetKeyState(VK_LBUTTON)) & 0x100) != 0)
	{
		DPrint ("fire ray");

		CVector3 mypos =m_pTransform->GetPosition();
		CVector3 fwd;
		m_pTransform->GetForwardDirection(&fwd);
		CVector3 rightOffset;
		CVector3 upOffset;
		m_pTransform->GetRightDirection(&rightOffset);
		m_pTransform->GetUpDirection(&upOffset);
		float Xoffset = 0.025f; //how far is gun to right of camera?
		float Yoffset = -0.02f; //how much lower is gun than middle of screen?
		rightOffset *= Xoffset;
		upOffset *= Yoffset;
		CVector3 gunPos = mypos + rightOffset + upOffset;


		//now create ray
		CGameObject * ray= new CGameObject();
		ray->GetTransform()->SetPosition(gunPos);
		ray->GetTransform()->SetYaw(m_pTransform->GetYaw());
		ray->GetTransform()->SetPitch(m_pTransform->GetPitch());
		ray->SetRenderable(new CRayRenderable(10.0f));
		ray->AddBehavior(new CRayBehavior());
		ray->AddBehavior(new CTimedDeletionBehavior(2));
		g_pGame->AddObject(ray);



		
	}
}