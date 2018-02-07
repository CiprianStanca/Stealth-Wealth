#include "StdAfx.h"
#include "Sprite.h"

CSprite::CSprite()
{
	m_fU0=0.0f;
	m_fU1=1.0f;
	m_fV0=0.0f;
	m_fV1=1.0f;
}

CSprite::~CSprite(void)
{
}

void
CSprite::SetUV(float u0_, float u1_,float v0_, float v1_)
{
	m_fU0=u0_;
	m_fU1=u1_;
	m_fV0=v0_;
	m_fV1=v1_;
}

void 
CSprite::Render()
{
	
	//glLoadIdentity();

	//transform to position specified by GameObject
	if (m_pGameObject)
	{
		glTranslatef(m_pGameObject->GetTransform()->GetPosition().m_fX, m_pGameObject->GetTransform()->GetPosition().m_fY,m_pGameObject->GetTransform()->GetPosition().m_fZ);		// move to proper position
		glRotatef(m_pGameObject->GetTransform()->GetYaw(),0.0f,1.0f,0.0f);
		glRotatef(m_pGameObject->GetTransform()->GetPitch(), 1.0f, 0.0f, 0.0f);
		glScalef(m_pGameObject->GetTransform()->GetSize3().m_fX, m_pGameObject->GetTransform()->GetSize3().m_fY,m_pGameObject->GetTransform()->GetSize3().m_fZ);
	}

	// Display a quad size 1 by 1, centred at origin
	glBegin(GL_QUADS);
		glTexCoord3f(m_fU0, m_fV1,0.0f);
		glVertex2f(-0.5, 0.5);

		glTexCoord3f(m_fU0, m_fV0,0.0f);
		glVertex2f(-0.5, -0.5);

		glTexCoord3f(m_fU1, m_fV0,0.0f);
		glVertex2f(0.5, -0.5);

		glTexCoord3f(m_fU1, m_fV1,0.0f);
		glVertex2f(0.5, 0.5);
	glEnd();

}


float
CSprite::GetBoundingSphereRadius()
{
	return 0.5f;
}