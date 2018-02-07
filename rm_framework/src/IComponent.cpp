#include "StdAfx.h"
#include "IComponent.h"

IComponent::IComponent(void)
{
	m_pGameObject=0;
}

IComponent::~IComponent(void)
{
}

void 
IComponent::SetGameObject(CGameObject * pGameObject_)
{
	m_pGameObject=pGameObject_;
	m_pTransform=(CTransform *)(m_pGameObject->GetTransform());
	AddedToGameObject();
}
