#include "stdafx.h"
#include "MovingForwardBehavior.h"


CMovingForwardBehavior::CMovingForwardBehavior(float Fvel_)
{
	m_FVelocity = Fvel_;
}


CMovingForwardBehavior::~CMovingForwardBehavior()
{

}

void
CMovingForwardBehavior::Update(float dt_)
{
	CVector3 direction = CVector3();
	m_pTransform->GetForwardDirection(&direction);
	
	float dx = direction.m_fX* 5 *dt_;
	float dy = direction.m_fY* 5 *dt_;
	float dz = direction.m_fZ* 5 *dt_;

	m_pTransform->Translate(dx, dy, dz);
}