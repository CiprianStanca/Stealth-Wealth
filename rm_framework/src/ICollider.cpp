#include "StdAfx.h"
#include "ICollider.h"

ICollider::ICollider(void)
{
	
	//m_bIsTrigger=false;

}

ICollider::~ICollider(void)
{
	//remove self from collision manager
	CCollisionManager::Instance()->RemoveCollider(this);
}

void
ICollider::AddedToGameObject()
{
	//m_bIsTrigger = false;
	CCollisionManager::Instance()->AddCollider(this);
}



void 
ICollider::SetPosition(CVector3 * pos_)
{
	m_vPosition.m_fX = pos_->m_fX;
	m_vPosition.m_fY = pos_->m_fY;
	m_vPosition.m_fZ = pos_->m_fZ;
}

void 
ICollider::SetScale(CVector3 * scale_)
{
	m_vScale.m_fX = scale_->m_fX;
	m_vScale.m_fY = scale_->m_fY;
	m_vScale.m_fZ = scale_->m_fZ;
}

void ICollider::SetTrigger()
{
	m_bIsTrigger = true;
}

