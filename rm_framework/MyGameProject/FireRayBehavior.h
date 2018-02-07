#pragma once
#include "ibehavior.h"
class CFireRayBehavior :
	public IBehavior
{
public:
	CFireRayBehavior(void);
	~CFireRayBehavior(void);
	void Update(float dt_);
};

