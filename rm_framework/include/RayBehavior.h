#pragma once
#include "ibehavior.h"

class CRayBehavior :public IBehavior
{
public:
	CRayBehavior();
	~CRayBehavior(void);
	void Update(float dt_);

};

