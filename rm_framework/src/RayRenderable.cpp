#include "stdafx.h"
#include "RayRenderable.h"


CRayRenderable::CRayRenderable(void)
{
	m_fRayLength = 10.0f;
}

CRayRenderable::CRayRenderable(  float length_)
{
	m_fRayLength=length_;
}

CRayRenderable::~CRayRenderable(void)
{
}

void 
CRayRenderable::Render()
{

	CVector3 mypos =m_pTransform->GetPosition();
	CVector3 mydirection;
	m_pTransform->GetForwardDirection(&mydirection);

	glPushMatrix();
	//glLoadIdentity();

	glDisable(GL_LIGHTING);
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glLineWidth(5.0f);

	glDisable(GL_TEXTURE_2D);

	glBegin(GL_LINES);
		glVertex3f(mypos.m_fX,mypos.m_fY,mypos.m_fZ);
		glVertex3f(mypos.m_fX+m_fRayLength*mydirection.m_fX,mypos.m_fY+m_fRayLength*mydirection.m_fY,mypos.m_fZ+m_fRayLength*mydirection.m_fZ);
	glEnd();

	glLineWidth(1.0f);
	glPopMatrix();


}
	
void 
CRayRenderable::CheckRayForCollision()
{

}