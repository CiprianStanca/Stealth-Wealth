#include "stdafx.h"
#include "GuardBehavior.h"


CGuardBehavior::CGuardBehavior(int level)
{
	SetLevel(level);
}


CGuardBehavior::~CGuardBehavior()
{
}

void CGuardBehavior::Update(float dt_)
{
	if (CGuardCaptain::Instance()->CaptainOrder())
	{
		// unit has got orders from captain
		m_v3PlayerPosition = CGuardCaptain::Instance()->GetPlayerPosition();

		// translate player position to map coordinates
		int playerX_ = int(m_v3PlayerPosition.m_fX);
		int playerZ_ = int(m_v3PlayerPosition.m_fZ);
		int playerLevel_;

		if (m_v3PlayerPosition.m_fY < 3)
		{
			playerLevel_ = 1;
		}
		else
			playerLevel_ = 2;

		// check if guard is on same level

		if (m_iGuardCurrentLevel == playerLevel_)
		{
			// proceed on following the player;

			// get guard position relative to map coordinate system
			CVector3 guardPosition = m_pTransform->GetPosition();
			guardPosition.m_fX = floor(guardPosition.m_fX) + CMapStorage::Instance()->GetMapOffset();
			guardPosition.m_fZ = floor(guardPosition.m_fZ) + CMapStorage::Instance()->GetMapOffset();

			// get shortest path to the playerposition and find out next tile to move into

			CVector3 targetPosition = CMapStorage::Instance()->getNextTileInPath(guardPosition.m_fX, guardPosition.m_fZ, m_v3PlayerPosition.m_fX, m_v3PlayerPosition.m_fZ, m_iGuardCurrentLevel);

			//CVector3 myPos = m_pTransform->GetPosition();
			//CVector3 camPos = cam->GetTransform()->GetPosition();

			guardPosition = m_pTransform->GetPosition();
			float dx = (targetPosition.m_fX  - CMapStorage::Instance()->GetMapOffset()) - (guardPosition.m_fX );
			float dz = (targetPosition.m_fZ  - CMapStorage::Instance()->GetMapOffset()) - (guardPosition.m_fZ  );

			double thetaradians = atan2(dx, dz);
			double thetadegrees = 180 * thetaradians / 3.142;
			m_pTransform->SetYaw(thetadegrees);

			CVector3 direction = CVector3();
			m_pTransform->GetForwardDirection(&direction);

			dx = direction.m_fX* 1 *dt_;
			float dy = direction.m_fY* 1 *dt_;
			dz = direction.m_fZ* 1 *dt_;

			m_pTransform->Translate(dx, dy, dz);

		}
		else
		{
			// ignore captain orders, they are not for you haha, good luck doing that to your manager
			m_bIgnoreOrders = true;
		}

	}

	if(!CGuardCaptain::Instance()->CaptainOrder() || m_bIgnoreOrders)
	{
		// unit can move freely
		// reset the ignore order bool in case it was used to enter the if
		m_bIgnoreOrders = false;

		// randomly select next tile the guard will move towards.
		
		CVector3 guardPosition = m_pTransform->GetPosition();
		guardPosition.m_fX = floor(guardPosition.m_fX ) + CMapStorage::Instance()->GetMapOffset();
		guardPosition.m_fZ = floor(guardPosition.m_fZ ) + CMapStorage::Instance()->GetMapOffset();

		CVector3 targetPosition = CMapStorage::Instance()->getRandomPoint(guardPosition.m_fX, guardPosition.m_fZ, m_iGuardCurrentLevel);

		float dx = (targetPosition.m_fX  - CMapStorage::Instance()->GetMapOffset()) - (guardPosition.m_fX  - CMapStorage::Instance()->GetMapOffset());
		float dz = (targetPosition.m_fZ  - CMapStorage::Instance()->GetMapOffset()) - (guardPosition.m_fZ  - CMapStorage::Instance()->GetMapOffset());

		double thetaradians = atan2(dx, dz);
		double thetadegrees = 180 * thetaradians / 3.142;
		m_pTransform->SetYaw(thetadegrees);

		CVector3 direction = CVector3();
		m_pTransform->GetForwardDirection(&direction);

		dx = direction.m_fX * 1 * dt_;
		float dy = direction.m_fY * 1 * dt_;
		dz = direction.m_fZ * 1 * dt_;

		char txt[32];
		sprintf_s(txt, "GUARD MOVED RANDOM");
		DPrint(txt);

		m_pTransform->Translate(dx, dy, dz);


	}

}

void CGuardBehavior::SetLevel(int level)
{
	m_iGuardCurrentLevel = level;

}


