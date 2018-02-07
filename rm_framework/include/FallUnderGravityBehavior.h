#pragma once
#include "ibehavior.h"
class CFallUnderGravityBehavior :
	public IBehavior
{
public:
	CFallUnderGravityBehavior(void);
	~CFallUnderGravityBehavior(void);
	void Update(float dt_);

private:
	CVector3 m_Velocity;
};

