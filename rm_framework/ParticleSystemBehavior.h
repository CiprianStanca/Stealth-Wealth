#pragma once
#include "ibehavior.h"
class CParticleSystemBehavior :
	public IBehavior
{
public:
	CParticleSystemBehavior();
	~CParticleSystemBehavior();
	void Update(float dt_);
	void CreateParticle(CVector3 pos, CVector3 velocity_, float size_);
};

