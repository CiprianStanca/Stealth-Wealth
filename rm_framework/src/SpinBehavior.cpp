#include "stdafx.h"
#include "SpinBehavior.h"


CSpinBehavior::CSpinBehavior(void)
{
}


CSpinBehavior::~CSpinBehavior(void)
{
}

void 
CSpinBehavior::Update(float dt_)
{
	float spinspeed = 90;
	m_pTransform->IncrementYaw(dt_ * spinspeed);
}
