#pragma once
#include "ibehavior.h"
class CParticleBehavior :
	public IBehavior
{
public:
	CParticleBehavior();
	~CParticleBehavior();
	void Update(float dt_);
};

