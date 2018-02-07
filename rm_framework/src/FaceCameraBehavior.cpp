#include "stdafx.h"
#include "FaceCameraBehavior.h"


CFaceCameraBehavior::CFaceCameraBehavior(void)
{
}


CFaceCameraBehavior::~CFaceCameraBehavior(void)
{
}

void 
CFaceCameraBehavior::Update(float dt_)
{
	CGameObject * cam = CTagManager::Instance()->GetObjectWithTag("Camera");
	
	assert (cam);

	CVector3 myPos = m_pTransform->GetPosition();
	CVector3 camPos = cam->GetTransform()->GetPosition();

	float dx=camPos.m_fX - myPos.m_fX;
	float dz=camPos.m_fZ - myPos.m_fZ;

	double thetaradians=atan2(dx,dz);
	double thetadegrees=180*thetaradians/3.142;
	m_pTransform->SetYaw(thetadegrees);

}