#pragma once
#include "ibehavior.h"
class CSpinBehavior :
	public IBehavior
{
public:
	CSpinBehavior(void);
	~CSpinBehavior(void);
	void Update(float dt_);
};

