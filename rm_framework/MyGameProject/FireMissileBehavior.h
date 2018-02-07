#pragma once
#include "ibehavior.h"


class CRay;

class CFireMissileBehavior :
	public IBehavior
{
public:
	CFireMissileBehavior(void);
	~CFireMissileBehavior(void);
	void Update(float dt_);


};
