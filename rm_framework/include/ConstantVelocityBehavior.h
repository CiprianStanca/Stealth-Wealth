#pragma once
#include "ibehavior.h"

class CConstantVelocityBehavior :
	public IBehavior
{
public:
	CConstantVelocityBehavior(CVector3  vel_);
	~CConstantVelocityBehavior(void);
	void Update(float dt_);
	void SetVelocity(CVector3  vel_){m_Velocity=vel_;}

private:
	CVector3 m_Velocity;
};