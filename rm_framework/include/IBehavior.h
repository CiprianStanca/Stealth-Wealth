#pragma once
#include "icomponent.h"

class IBehavior :
	public IComponent
{
public:
	IBehavior(void);
	~IBehavior(void);

	virtual void Update(float dt_)=0;
};
