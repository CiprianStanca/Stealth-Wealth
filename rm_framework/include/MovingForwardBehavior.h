#pragma once
#include "ibehavior.h"

class CMovingForwardBehavior :
	public IBehavior
{

public:
	CMovingForwardBehavior(float Fvel_);
	~CMovingForwardBehavior();
	void Update(float dt_);

private:
	float m_FVelocity;
};

