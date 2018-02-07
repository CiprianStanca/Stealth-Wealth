#pragma once
#include "icollisionresponder.h"

class CDestroyedByMissileCollisionResponder :
	public ICollisionResponder
{
public:
	CDestroyedByMissileCollisionResponder(void);
	~CDestroyedByMissileCollisionResponder(void);
	bool ReactToCollision();
};

