#include "stdafx.h"
#include "C3DShape.h"


C3DShape::C3DShape(void)
{
}


C3DShape::~C3DShape(void)
{
}



void 
C3DShape::Render()
{

	//transform to position specified by GameObject
	if (m_pGameObject)
	{
		glTranslatef(m_pGameObject->GetTransform()->GetPosition().m_fX, m_pGameObject->GetTransform()->GetPosition().m_fY,m_pGameObject->GetTransform()->GetPosition().m_fZ);		// move to proper position
		glRotatef(m_pGameObject->GetTransform()->GetYaw(),0.0f,1.0f,0.0f);
		glScalef(m_pGameObject->GetTransform()->GetSize3().m_fX, m_pGameObject->GetTransform()->GetSize3().m_fY,m_pGameObject->GetTransform()->GetSize3().m_fZ);
	}




	glPushMatrix();


	// Display a quad size 1 by 1, centred at origin
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);	// top face
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.5f, 0.5f, 0.5f);	
			glTexCoord2f(0.5f, 0.0f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			glTexCoord2f(0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glTexCoord2f(0.0f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
		glEnd();
		
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);	// front face
			glTexCoord2f(0.5f, 0.5f);
			glVertex3f(0.5f, 0.5f, 0.5f);	
			glTexCoord2f(0.0f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glTexCoord2f(0.5f, 0.0f);
			glVertex3f(0.5f, -0.5f, 0.5f);
		glEnd();
		
		glBegin(GL_QUADS);
			glNormal3f(1.0f, 0.0f, 0.0f);	// right face
			glTexCoord2f(0.5f, 1.0f);
			glVertex3f(0.5f, 0.5f, 0.5f);	
			glTexCoord2f(0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glTexCoord2f(1.0f, 0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();
		
		glBegin(GL_QUADS);
			glNormal3f(-1.0f, 0.0f, 0.0f);	// left face
			glTexCoord2f(0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);	
			glTexCoord2f(0.0f, 0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glTexCoord2f(0.5f, 0.0f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
		glEnd();
		
		glBegin(GL_QUADS);
			glNormal3f(0.0f, -1.0f, 0.0f);	// bottom face
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0.5f, -0.5f, 0.5f);	
		glEnd();
		
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, -1.0f);	// back face
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glTexCoord2f(0.5f, 0.0f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glTexCoord2f(0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glTexCoord2f(0.0f, 0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);	
		glEnd();

	glPopMatrix();

}

float
C3DShape::GetBoundingSphereRadius()
{
	return 0.707f;
}