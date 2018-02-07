#pragma once
#include "IBehavior.h"
class CTurnAfterTimeBehavior:
	public IBehavior

{
public:
	CTurnAfterTimeBehavior(float timer_, float limit_, float degree_);
	~CTurnAfterTimeBehavior();
	void Update(float dt_);

private:

	float m_fTimer;
	float m_fTimeLimit;
	float m_fNumDegrees;

};

