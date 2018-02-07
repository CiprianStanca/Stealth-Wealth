#pragma once
#include "IBehavior.h"

class CCollideDeleteBehavior :
	public IBehavior
{
public:
	CCollideDeleteBehavior(void);
	~CCollideDeleteBehavior(void);
	void Update(float dt_);
};
