#include "stdafx.h"
#include "GuardCaptain.h"


CGuardCaptain::CGuardCaptain()
{
}

CGuardCaptain::~CGuardCaptain()
{
}

void
CGuardCaptain::Destroy()
{
	if (instance_)
	{
		delete instance_;
		instance_ = 0;
	}
}

void CGuardCaptain::Update()
{

	// check if player is spotted

	if (g_pGame->m_bPlayerSpotted)
	{
		// if spotted send guards around;
		m_bCaptainResponse = true;
		
		// store player coordinates;
		m_v3PlayerPosition = g_pGame->m_pRootNode->GetTransform()->GetPosition();
		m_v3PlayerPosition.m_fX = floor(m_v3PlayerPosition.m_fX);
		//m_v3PlayerPosition.m_fY = floor(m_v3PlayerPosition.m_fZ);
		m_v3PlayerPosition.m_fZ = floor(m_v3PlayerPosition.m_fZ);
	}
	else
	{
		// set the response of guard captain to null
		m_bCaptainResponse = false;
	}

}

bool CGuardCaptain::CaptainOrder()
{
	return m_bCaptainResponse;
}

CVector3 CGuardCaptain::GetPlayerPosition()
{
	return m_v3PlayerPosition;
}



CGuardCaptain * CGuardCaptain::Instance()
{
	if (instance_ == 0)
	{
		instance_ = new CGuardCaptain();
	}
	return instance_;
}

CGuardCaptain * CGuardCaptain::instance_ = 0;
