#pragma once
#include "icomponent.h"

class ICollisionResponder :
	public IComponent
{
public:
	ICollisionResponder(void);
	~ICollisionResponder(void);
	virtual bool ReactToCollision()=0;
};

