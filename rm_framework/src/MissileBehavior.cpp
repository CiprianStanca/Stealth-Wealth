#include "stdafx.h"
#include "MissileBehavior.h"


CMissileBehavior::CMissileBehavior(void)
{
	m_fTime=0.0f;
}


CMissileBehavior::~CMissileBehavior(void)
{
}

void
CMissileBehavior::Update(float dt_)
{
	m_fTime+=dt_;

	//move upwards
	//m_pGameObject->GetTransform()->Translate(CVector3(0,5*dt_,0));
	//rotate in a circle?
	float radius = 1.0f;
	float angle = m_fTime + m_fAngleOffset ;

	float x=radius * sin(angle);
	float y=radius * cos (angle);

	m_pGameObject->GetTransform()->SetPosition(CVector3(x,y,0));

}