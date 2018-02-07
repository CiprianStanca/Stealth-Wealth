#pragma once
#include "ibehavior.h"
class CFaceCameraBehavior :
	public IBehavior
{
public:
	CFaceCameraBehavior(void);
	~CFaceCameraBehavior(void);
	void Update(float dt_);
};

