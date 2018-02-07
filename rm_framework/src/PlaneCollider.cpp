#include "stdafx.h"
#include "PlaneCollider.h"


CPlaneCollider::CPlaneCollider(void)
{
	m_bUseXAxis = true; // if false then use z axis
	m_fMinX = -0.5f;
	m_fMaxX = 0.5f;
	m_fMinY = -0.5f;
	m_fMaxY = 0.5f;
	m_fMinZ = -0.5f;
	m_fMaxZ = 0.5f;
}


CPlaneCollider::~CPlaneCollider(void)
{
}


void
CPlaneCollider::AddedToGameObject()
{
	m_bUseXAxis = (0 == ((int)m_pTransform->GetYaw())%180);
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

	if (m_bUseZAxis) {
		m_fMinX = m_pTransform->GetPosition().m_fX - 0.5 * m_pTransform->GetSize3().m_fX;
		m_fMaxX = m_pTransform->GetPosition().m_fX + 0.5 * m_pTransform->GetSize3().m_fX;
		m_fMinY = m_fMaxY = m_pTransform->GetPosition().m_fY;
		m_fMinZ = m_pTransform->GetPosition().m_fZ - 0.5 * m_pTransform->GetSize3().m_fZ;
		m_fMaxZ = m_pTransform->GetPosition().m_fZ + 0.5 * m_pTransform->GetSize3().m_fZ;

		char txt[128];
		sprintf_s(txt, "minX = %f ; maxX = %f ; minY = %f ; minZ = %f ; maxZ = %f ; ", m_fMinX, m_fMaxX, m_fMinY, m_fMinZ, m_fMaxZ);
		DPrint(txt);
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
CPlaneCollider::CheckForCollision(ICollider * in_)
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
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
		if (!m_bUseXAxis && !m_bUseZAxis)
		{
			if (abs(m_fMinX - pSphere->GetTransform()->GetPosition().m_fX)<pSphere->GetScaledRadius())
			{

				if ((pSphere->GetTransform()->GetPosition().m_fY - pSphere->GetScaledRadius() < m_fMaxY) &&
					(pSphere->GetTransform()->GetPosition().m_fY + pSphere->GetScaledRadius() > m_fMinY) &&
					(pSphere->GetTransform()->GetPosition().m_fZ + pSphere->GetScaledRadius() > m_fMinZ) &&
					(pSphere->GetTransform()->GetPosition().m_fZ - pSphere->GetScaledRadius() < m_fMaxZ))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	else
	if(m_bUseZAxis){
		//check for distance sphere centre-Y and wall-Y

		if (abs(m_fMinY - pSphere->GetTransform()->GetPosition().m_fY)<pSphere->GetScaledRadius())
		{
			if ( (pSphere->GetTransform()->GetPosition().m_fZ - pSphere->GetScaledRadius() < m_fMaxZ) && 
				(pSphere->GetTransform()->GetPosition().m_fZ + pSphere->GetScaledRadius() > m_fMinZ) && 
				(pSphere->GetTransform()->GetPosition().m_fX - pSphere->GetScaledRadius() < m_fMaxX) &&
				(pSphere->GetTransform()->GetPosition().m_fX + pSphere->GetScaledRadius() > m_fMinX) )
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	return false;
}

bool CPlaneCollider::CheckForCollisionWithRay(CVector3 raystart_, CVector3 raydirection_, float raylength_, CVector3 * hitPoint_)
{
	IRenderable * ren = m_pGameObject->GetRenderable();
	char * type = ren->GetType();
	if (type[1] == 'C' && type[2] == 'a')
	{
		return false;
	}
	//does ray intersect bounding sphere?

	//compute vector from beginning of ray to centre of sphere
	CVector3 vRayStartToSphereCentre = m_vPosition - raystart_;
	//get dot product of this vector with ray direction
	float dotp = vRayStartToSphereCentre.DotProduct(&raydirection_);

	if (dotp < 0)
	{
		// no collision
		return false;
	}
	else
	{
		// we might have collision
		char txt[32];
		sprintf(txt, "RAY HIT A PLANE");
		DPrint(txt);
		CVector3 vCentreProjOnLine = raystart_ + raydirection_ * dotp;
		char txxt[62];
		sprintf(txxt, "%.2f %.2f %.2f - centreprojline", vCentreProjOnLine.m_fX, vCentreProjOnLine.m_fY, vCentreProjOnLine.m_fZ);
		DPrint(txxt);
		char txxxxt[92];
		sprintf(txxxxt, "%.2f %.2f %.2f %.2f %.2f %.2f  - object tested against", m_fMinX, m_fMaxX, m_fMinY, m_fMaxY, m_fMinZ, m_fMaxZ);
		DPrint(txxxxt);
		//calc distance from centre to projected point
		//CVector3 vCentreToProjectedPoint = vCentreProjOnLine - m_vPosition;
		//float dist = vCentreToProjectedPoint.GetLength();
		
		if (m_fMinX == m_fMaxX)
		{
			if (vCentreProjOnLine.m_fY >= m_fMinY && vCentreProjOnLine.m_fY <= m_fMaxY &&
				vCentreProjOnLine.m_fZ >= m_fMinZ && vCentreProjOnLine.m_fZ <= m_fMaxZ)
			{
				//return data about hit point
				if (hitPoint_)
				{
					hitPoint_->m_fX = vCentreProjOnLine.m_fX;
					hitPoint_->m_fY = vCentreProjOnLine.m_fY;
					hitPoint_->m_fZ = vCentreProjOnLine.m_fZ;
				}
				return true;
			}
		}
		if (m_fMinY == m_fMaxY)
		{
			if (vCentreProjOnLine.m_fX >= m_fMinX && vCentreProjOnLine.m_fX <= m_fMaxX &&
				vCentreProjOnLine.m_fZ >= m_fMinZ && vCentreProjOnLine.m_fZ <= m_fMaxZ)
			{
				//return data about hit point
				if (hitPoint_)
				{
					hitPoint_->m_fX = vCentreProjOnLine.m_fX;
					hitPoint_->m_fY = vCentreProjOnLine.m_fY;
					hitPoint_->m_fZ = vCentreProjOnLine.m_fZ;
				}
				return true;
			}
		}
		if (m_fMinZ == m_fMaxZ)
		{
			if (vCentreProjOnLine.m_fX >= m_fMinX && vCentreProjOnLine.m_fX <= m_fMaxX &&
				vCentreProjOnLine.m_fY >= m_fMinY && vCentreProjOnLine.m_fY <= m_fMaxY)
			{
				//return data about hit point
				if (hitPoint_)
				{
					hitPoint_->m_fX = vCentreProjOnLine.m_fX;
					hitPoint_->m_fY = vCentreProjOnLine.m_fY;
					hitPoint_->m_fZ = vCentreProjOnLine.m_fZ;
				}
				return true;
			}
		}
	}
	
	
	return false;
}




bool
CPlaneCollider::RespondToCollision()
{
	return !m_bIsTrigger; //if we are a trigger then we return false to mean no blocking behavior
	//return true;
}

void
CPlaneCollider::Render()
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
			glVertex3f(m_fMinX, m_fMinY, m_fMaxZ);
			glVertex3f(m_fMaxX, m_fMinY, m_fMaxZ);
			glVertex3f(m_fMaxX, m_fMinY, m_fMinZ);
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