#include "StdAfx.h"
#include "AgentBehavior.h"
#include "stdio.h"

CAgentBehavior::CAgentBehavior(void)
{
}

CAgentBehavior::~CAgentBehavior(void)
{
}

void
CAgentBehavior::Update(float dt_)
{
	//generate random number
	int dx=-5+rand()%10;
	int dz=-5+rand()%10;
	m_pTransform->Translate(CVector3(0.01*dx,0, 0.01*dz));
}