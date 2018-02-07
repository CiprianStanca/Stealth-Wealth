#include "stdafx.h"
#include "ParticleBehavior.h"


CParticleBehavior::CParticleBehavior()
{
}


CParticleBehavior::~CParticleBehavior()
{
}

/*void
CParticleBehavior::Update(float dt_)
{
	//make is slightly smaller
	float size = m_pGameObject->GetTransform()->GetSize3().m_fX;
	size -= (dt_ * 2.0f);

	if (size < SIZETHRESHOLD)
	{
		//Tag for deletion
		m_pGameObject->TagForDeletion();

	}
	m_pGameObject->GetTransform()->SetSize(size, size, size);
	((CColourMaterial *)(m_pGameObject->GetMaterial()))->SetAlpha(size);

}*/