#pragma once
#include "ibehavior.h"

class CPlayerBehavior :
	public IBehavior
{
public:
	CPlayerBehavior(void);
	~CPlayerBehavior(void);
	void Update(float dt_);
};
