#pragma once
#include "ibehavior.h"

class CUpdateBoundingSphereBehavior :
	public IBehavior
{
public:
	CUpdateBoundingSphereBehavior(void);
	~CUpdateBoundingSphereBehavior(void);
	void Update(float dt_);


};