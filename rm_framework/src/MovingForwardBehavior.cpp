#include "stdafx.h"
#include "MovingForwardBehavior.h"


CMovingForwardBehavior::CMovingForwardBehavior(float Fvel_)
{
	m_FVelocity = fVel_;
}


CMovingForwardBehavior::~CMovingForwardBehavior()
{

}

void
CMovingForwardBehavior::Update(float dt_)
{
	CVector3 direction = CVector3();
	m_pTransform->GetForwardDirection(&direction);
	
	float dx = direction.m_fX*m_FVelocity*dt_;
	float dy = direction.m_fY*m_FVelocity*dt_;
	float dz = direction.m_fZ*m_FVelocity*dt_;

	m_pTransform->Translate(dx, dy, dz);
}