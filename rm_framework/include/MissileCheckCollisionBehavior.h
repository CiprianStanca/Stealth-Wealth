#pragma once
#include "ibehavior.h"
class CMissileCheckCollisionBehavior :
	public IBehavior
{
public:
	CMissileCheckCollisionBehavior(void);
	~CMissileCheckCollisionBehavior(void);
	void Update(float dt_);
};

