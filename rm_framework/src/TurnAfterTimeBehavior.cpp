#include "stdafx.h"
#include "TurnAfterTimeBehavior.h"



CTurnAfterTimeBehavior::CTurnAfterTimeBehavior(float timer_, float limit_, float degree_)
{
	m_fTimer = timer_;
	m_fTimeLimit = limit_;
	m_fNumDegrees = degree_;
}

CTurnAfterTimeBehavior::~CTurnAfterTimeBehavior()
{
}

void CTurnAfterTimeBehavior::Update(float dt_)
{
	m_fTimer += dt_;

	if (m_fTimer >= m_fTimeLimit)
	{
		m_fTimer = 0;
		m_pTransform->IncrementYaw(m_fNumDegrees);
	}
}
