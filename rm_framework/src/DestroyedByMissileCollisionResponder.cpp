#include "stdafx.h"
#include "DestroyedByMissileCollisionResponder.h"


CDestroyedByMissileCollisionResponder::CDestroyedByMissileCollisionResponder(void)
{
}


CDestroyedByMissileCollisionResponder::~CDestroyedByMissileCollisionResponder(void)
{
}

bool
CDestroyedByMissileCollisionResponder::ReactToCollision()
{
	DPrint ("object destroyed");

	m_pGameObject->TagForDeletion();
	return false;
}