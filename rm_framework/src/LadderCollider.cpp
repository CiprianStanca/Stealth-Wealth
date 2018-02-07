#include "stdafx.h"
#include "LadderCollider.h"


CLadderCollider::CLadderCollider(void)
{
	m_bUseXAxis = true; // if false then use z axis
	m_fMinX = -0.5f;
	m_fMaxX = 0.5f;
	m_fMinY = -0.5f;
	m_fMaxY = 0.5f;
	m_fMinZ = 0.0f;
	m_fMaxZ = 0.0f;
}


CLadderCollider::~CLadderCollider(void)
{
}


void
CLadderCollider::AddedToGameObject()
{
	m_bUseXAxis = (0 == m_pTransform->GetYaw());
	m_bUseZAxis = (0 != m_pTransform->GetPitch());
	if (m_bUseXAxis && !m_bUseZAxis)
	{
		m_fMinX = m_pTransform->GetPosition().m_fX - 0.5 * m_pTransform->GetSize3().m_fX;
		m_fMaxX = m_pTransform->GetPosition().m_fX + 0.5 * m_pTransform->GetSize3().m_fX;
		m_fMinY = m_pTransform->GetPosition().m_fY - 0.5 * m_pTransform->GetSize3().m_fY;
		m_fMaxY = m_pTransform->GetPosition().m_fY + 0.5 * m_pTransform->GetSize3().m_fY;
		m_fMinZ = m_fMaxZ = m_pTransform->GetPosition().m_fZ;
	}
	
	if (!m_bUseXAxis && !m_bUseZAxis) {
		m_fMinX = m_fMaxX = m_pTransform->GetPosition().m_fX;
		m_fMinY = m_pTransform->GetPosition().m_fY - 0.5 * m_pTransform->GetSize3().m_fY;
		m_fMaxY = m_pTransform->GetPosition().m_fY + 0.5 * m_pTransform->GetSize3().m_fY;
		m_fMinZ = m_pTransform->GetPosition().m_fZ - 0.5 * m_pTransform->GetSize3().m_fZ;
		m_fMaxZ = m_pTransform->GetPosition().m_fZ + 0.5 * m_pTransform->GetSize3().m_fZ;

	}
	
	if ( m_bUseZAxis) {
		m_fMinX = m_pTransform->GetPosition().m_fX - 0.5 * m_pTransform->GetSize3().m_fX;
		m_fMaxX = m_pTransform->GetPosition().m_fX + 0.5 * m_pTransform->GetSize3().m_fX;
		m_fMinY = m_fMaxY = m_pTransform->GetPosition().m_fY;
		m_fMinZ = m_pTransform->GetPosition().m_fZ - 0.5 * m_pTransform->GetSize3().m_fZ;
		m_fMaxZ = m_pTransform->GetPosition().m_fZ + 0.5 * m_pTransform->GetSize3().m_fZ;
	}

	ICollider::AddedToGameObject();
}

/*void CPlaneCollider::SetAxisUsed(char axis)
{
if (axis == 'X' || axis )
{

}
}*/

bool
CLadderCollider::CheckForCollision(ICollider * in_)
{
	CSphereCollider * pSphere = (CSphereCollider *)in_;

	if (m_bUseXAxis && !m_bUseZAxis)
	{
		//check for distance between sphere centre-z and wall-z
		if (abs(m_fMinZ - pSphere->GetTransform()->GetPosition().m_fZ)<pSphere->GetScaledRadius())
		{

			if ((pSphere->GetTransform()->GetPosition().m_fX - pSphere->GetScaledRadius() < m_fMaxX) &&
				(pSphere->GetTransform()->GetPosition().m_fX + pSphere->GetScaledRadius() > m_fMinX) &&
				(pSphere->GetTransform()->GetPosition().m_fY + pSphere->GetScaledRadius() > m_fMinY) &&
				(pSphere->GetTransform()->GetPosition().m_fY - pSphere->GetScaledRadius() < m_fMaxY))
			{
				g_pGame->isClimbing = true;
				return true;
			}
			else
			{
				g_pGame->isClimbing = true;
				return false;
			}
		}
	}

	return false;
}




bool
CLadderCollider::RespondToCollision()
{
	return !m_bIsTrigger; //if we are a trigger then we return false to mean no blocking behavior
	//return true;
}

void
CLadderCollider::Render()
{
	if (m_pGameObject)
	{
		glPushMatrix();

		//draw collider as quad, centred at transform position
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
		glDisable(GL_CULL_FACE); //don't cull faces
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glLineWidth(2.0f);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

		if (m_bUseXAxis && !m_bUseZAxis)
		{
			//plane aligned with x axis
			glBegin(GL_QUADS);
			glVertex3f(m_fMinX, m_fMinY, m_fMinZ);
			glVertex3f(m_fMinX, m_fMaxY, m_fMinZ);
			glVertex3f(m_fMaxX, m_fMaxY, m_fMinZ);
			glVertex3f(m_fMaxX, m_fMinY, m_fMinZ);
			glEnd();
		}
		if (!m_bUseXAxis && !m_bUseZAxis)
		{
			//plane aligned with y axis
			glBegin(GL_QUADS);
			glVertex3f(m_fMinX, m_fMinY, m_fMinZ);
			glVertex3f(m_fMinX, m_fMaxY, m_fMinZ);
			glVertex3f(m_fMinX, m_fMaxY, m_fMaxZ);
			glVertex3f(m_fMinX, m_fMinY, m_fMaxZ);
			glEnd();
		}
		if (m_bUseZAxis)
		{
			//plane aligned with z axis
			glBegin(GL_QUADS);
			glVertex3f(m_fMinX, m_fMinY, m_fMinZ);
			glVertex3f(m_fMaxX, m_fMinY, m_fMinZ);
			glVertex3f(m_fMinX, m_fMinY, m_fMaxZ);
			glVertex3f(m_fMaxX, m_fMinY, m_fMaxZ);
			glEnd();
		}

		//put things back to normal
		glLineWidth(1.0f);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //wireframe mode
		glEnable(GL_CULL_FACE); //don't cull faces
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);

		glPopMatrix();


	}//end if gameobject
}//end function