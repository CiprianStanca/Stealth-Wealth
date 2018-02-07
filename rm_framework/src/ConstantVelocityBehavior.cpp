#include "stdafx.h"
#include "ConstantVelocityBehavior.h"


CConstantVelocityBehavior::CConstantVelocityBehavior(CVector3  vel_)
{
	m_Velocity =  vel_;
}


CConstantVelocityBehavior::~CConstantVelocityBehavior(void)
{


}


void 
CConstantVelocityBehavior::Update(float dt_)
{
	m_pTransform->Translate(m_Velocity.m_fX * dt_, m_Velocity.m_fY * dt_,m_Velocity.m_fZ * dt_);
}