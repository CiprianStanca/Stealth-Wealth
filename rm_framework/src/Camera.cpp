#include "stdafx.h"
#include "Camera.h"
#define DEG2RAD(x) 3.142*x/180

CCamera::CCamera(void)
{
	m_bBirdsEyeView=false;
}


CCamera::~CCamera(void)
{
}

void
CCamera::AddedToGameObject()
{
	//tag this object with 'Camera'
	CTagManager::Instance()->AddTag(m_pGameObject,"Camera");

	assert (m_pGameObject);
	//switch on terrain following
	m_pGameObject->GetTransform()->m_bClampToTerrain=true;
	m_pGameObject->GetTransform()->m_fClampOffset=1.0f;
}

void 
CCamera::Render()
{
	//update lookat based on current forward direction (Which is now available via Transform::GetForwardDirection() )

	float x=m_pTransform->GetPosition().m_fX;
	float y=m_pTransform->GetPosition().m_fY;
	float z=m_pTransform->GetPosition().m_fZ;

	//get forward direction
	CVector3 fwd;
	m_pTransform->GetForwardDirection(&fwd);
		
	float lookAtx=x+fwd.m_fX;
	float lookAty=y+fwd.m_fY;
	float lookAtz=z+fwd.m_fZ;

	if (m_bBirdsEyeView)
	{
		gluLookAt(0,20,0,0, 0, 0,0,0,-1);
	}
	else
	{
		gluLookAt(x,y,z,lookAtx, lookAty, lookAtz,0,1,0);
	}


}

void
CCamera::ToggleBirdsEyeView()
{
	m_bBirdsEyeView = !m_bBirdsEyeView;
}

float
CCamera::GetBoundingSphereRadius()
{
	return 1.0f;
}