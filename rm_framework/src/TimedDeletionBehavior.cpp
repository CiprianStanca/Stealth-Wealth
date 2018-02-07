#include "stdafx.h"
#include "TimedDeletionBehavior.h"


CTimedDeletionBehavior::CTimedDeletionBehavior(int frames)
{
	m_iFramesToShow = frames;
	m_iUpdatesCompleted=0;
}


CTimedDeletionBehavior::~CTimedDeletionBehavior(void)
{
}


void
CTimedDeletionBehavior::Update(float dt_)
{
	m_iUpdatesCompleted++;

	if (m_iUpdatesCompleted >=m_iFramesToShow)
		{
		//delete self
		m_pGameObject->TagForDeletion();
		}
}