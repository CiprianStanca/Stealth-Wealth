#include "stdafx.h"
#include "CubeCollider.h"


CCubeCollider::CCubeCollider()
{
	m_fMinX = -0.5f;
	m_fMaxX = 0.5f;
	m_fMinY = -0.5f;
	m_fMaxY = 0.5f;
	m_fMinZ = -0.5f;
	m_fMaxZ = 0.5f;
}


CCubeCollider::~CCubeCollider()
{
}

void CCubeCollider::AddedToGameObject()
{
	m_bUseXAxis = (0 == m_pTransform->GetYaw());

	m_fMinX = m_pTransform->GetPosition().m_fX - 0.5 * m_pTransform->GetSize3().m_fX;
	m_fMaxX = m_pTransform->GetPosition().m_fX + 0.5 * m_pTransform->GetSize3().m_fX;
	m_fMinY = m_pTransform->GetPosition().m_fY - 0.5 * m_pTransform->GetSize3().m_fY;
	m_fMaxY = m_pTransform->GetPosition().m_fY + 0.5 * m_pTransform->GetSize3().m_fY;
	m_fMinZ = m_pTransform->GetPosition().m_fZ - 0.5 * m_pTransform->GetSize3().m_fZ;
	m_fMaxZ = m_pTransform->GetPosition().m_fZ + 0.5 * m_pTransform->GetSize3().m_fZ;

	ICollider::AddedToGameObject();
}

/*void CPlaneCollider::SetAxisUsed(char axis)
{
if (axis == 'X' || axis )
{

}
}*/

bool
CCubeCollider::CheckForCollision(ICollider * in_)
{
	CSphereCollider * pSphere = (CSphereCollider *)in_;

	if (abs(m_fMinZ - pSphere->GetTransform()->GetPosition().m_fZ)<pSphere->GetScaledRadius())
	{

		if ((pSphere->GetTransform()->GetPosition().m_fX - pSphere->GetScaledRadius() < m_fMaxX) && 
			(pSphere->GetTransform()->GetPosition().m_fX + pSphere->GetScaledRadius() > m_fMinX) &&
			(pSphere->GetTransform()->GetPosition().m_fY + pSphere->GetScaledRadius() > m_fMinY) &&
			(pSphere->GetTransform()->GetPosition().m_fY - pSphere->GetScaledRadius() < m_fMaxY) )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if (abs(m_fMinX - pSphere->GetTransform()->GetPosition().m_fX) < pSphere->GetScaledRadius())
	{

		if ((pSphere->GetTransform()->GetPosition().m_fZ - pSphere->GetScaledRadius() < m_fMaxZ) && 
			(pSphere->GetTransform()->GetPosition().m_fZ + pSphere->GetScaledRadius() > m_fMinZ) &&
			(pSphere->GetTransform()->GetPosition().m_fY + pSphere->GetScaledRadius() > m_fMinY) &&
			(pSphere->GetTransform()->GetPosition().m_fY - pSphere->GetScaledRadius() < m_fMaxY) )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if (abs(m_fMinX - pSphere->GetTransform()->GetPosition().m_fX) < pSphere->GetScaledRadius())
	{

		if ((pSphere->GetTransform()->GetPosition().m_fY - pSphere->GetScaledRadius() < m_fMaxY) && 
			(pSphere->GetTransform()->GetPosition().m_fY + pSphere->GetScaledRadius() > m_fMinY) &&
			(pSphere->GetTransform()->GetPosition().m_fZ - pSphere->GetScaledRadius() < m_fMaxZ) &&
			(pSphere->GetTransform()->GetPosition().m_fZ + pSphere->GetScaledRadius() > m_fMinZ))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}




bool
CCubeCollider::RespondToCollision()
{
	return !m_bIsTrigger; //if we are a trigger then we return false to mean no blocking behavior
	//return true;
}

void
CCubeCollider::Render()
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


			//plane aligned with x axis
			glBegin(GL_QUADS);
			glColor3f(0.0f, 1.0f, 0.0f);    // Color Blue
			glVertex3f(m_fMinX, m_fMaxY, m_fMaxZ);    // Top Right Of The Quad (Top) A
			glVertex3f(m_fMaxX, m_fMaxY, m_fMaxZ);    // Top Left Of The Quad (Top) B
			glVertex3f(m_fMinX, m_fMinY, m_fMaxZ);    // Bottom Left Of The Quad (Top) C
			glVertex3f(m_fMaxX, m_fMinY, m_fMaxZ);    // Bottom Right Of The Quad (Top) D
			glColor3f(1.0f, 0.5f, 0.0f);    // Color Orange
			glVertex3f(m_fMinX, m_fMaxY, m_fMinZ);    // Top Right Of The Quad (Bottom) E
			glVertex3f(m_fMaxX, m_fMaxY, m_fMinZ);    // Top Left Of The Quad (Bottom) F
			glVertex3f(m_fMinX, m_fMinY, m_fMinZ);    // Bottom Left Of The Quad (Bottom) G
			glVertex3f(m_fMaxX, m_fMinY, m_fMinZ);    // Bottom Right Of The Quad (Bottom) H
			glColor3f(1.0f, 0.0f, 0.0f);    // Color Red    
			glVertex3f(m_fMinX, m_fMinY, m_fMaxZ);    // Top Right Of The Quad (Front) C
			glVertex3f(m_fMaxX, m_fMinY, m_fMaxZ);    // Top Left Of The Quad (Front) D
			glVertex3f(m_fMinX, m_fMinY, m_fMinZ);    // Bottom Left Of The Quad (Front) G
			glVertex3f(m_fMaxX, m_fMinY, m_fMinZ);    // Bottom Right Of The Quad (Front) H
			glColor3f(1.0f, 1.0f, 0.0f);    // Color Yellow
			glVertex3f(m_fMinX, m_fMaxY, m_fMaxZ);    // Top Right Of The Quad (Back) A
			glVertex3f(m_fMaxX, m_fMaxY, m_fMaxZ);    // Top Left Of The Quad (Back) B
			glVertex3f(m_fMinX, m_fMaxY, m_fMinZ);    // Bottom Left Of The Quad (Back) E
			glVertex3f(m_fMaxX, m_fMaxY, m_fMinZ);    // Bottom Right Of The Quad (Back) F
			glColor3f(0.0f, 0.0f, 1.0f);    // Color Blue
			glVertex3f(m_fMinX, m_fMaxY, m_fMaxZ);    // Top Right Of The Quad (Left) A
			glVertex3f(m_fMinX, m_fMinY, m_fMaxZ);    // Top Left Of The Quad (Left) C
			glVertex3f(m_fMinX, m_fMaxY, m_fMinZ);    // Bottom Left Of The Quad (Left) E
			glVertex3f(m_fMinX, m_fMinY, m_fMinZ);    // Bottom Right Of The Quad (Left) G
			glColor3f(1.0f, 0.0f, 1.0f);    // Color Violet
			glVertex3f(m_fMaxX, m_fMinY, m_fMaxZ);    // Top Right Of The Quad (Right) D
			glVertex3f(m_fMaxX, m_fMaxY, m_fMaxZ);    // Top Left Of The Quad (Right) B
			glVertex3f(m_fMaxX, m_fMinY, m_fMinZ);    // Bottom Left Of The Quad (Right) H
			glVertex3f(m_fMaxX, m_fMaxY, m_fMinZ);    // Bottom Right Of The Quad (Right) F
			glEnd();
		
		

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