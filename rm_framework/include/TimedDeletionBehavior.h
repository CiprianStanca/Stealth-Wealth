#pragma once

#include "ibehavior.h"

class CTimedDeletionBehavior :
	public IBehavior
{
public:
	CTimedDeletionBehavior(int frames=1);
	~CTimedDeletionBehavior(void);
	void Update(float dt_);

private:
	int m_iFramesToShow;
	int m_iUpdatesCompleted;
};

