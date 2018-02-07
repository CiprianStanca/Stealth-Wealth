#pragma once
#include "IBehavior.h"

class CAgentBehavior :
	public IBehavior
{
public:
	CAgentBehavior(void);
	~CAgentBehavior(void);
	void Update(float dt_);
};
