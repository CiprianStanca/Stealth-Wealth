#pragma once
#include "ibehavior.h"
class CMissileBehavior :
	public IBehavior
{
public:
	CMissileBehavior(void);
	~CMissileBehavior(void);
	void Update(float dt_);
	void SetAngleOffset(float ang_){m_fAngleOffset = ang_;}
private:
	float m_fTime;
	float m_fAngleOffset;
};

