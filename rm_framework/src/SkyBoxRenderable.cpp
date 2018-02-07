#include "stdafx.h"
#include "SkyBoxRenderable.h"


CSkyBoxRenderable::CSkyBoxRenderable(void)
{
}


CSkyBoxRenderable::~CSkyBoxRenderable(void)
{
}


void
CSkyBoxRenderable::Render()
{
	if (m_pGameObject)
	{
		glTranslatef(m_pTransform->GetPosition().m_fX, m_pTransform->GetPosition().m_fY,m_pTransform->GetPosition().m_fZ);		// move to proper position
		glScalef(m_pTransform->GetSize3().m_fX, m_pTransform->GetSize3().m_fY,m_pTransform->GetSize3().m_fZ);
	}


	glPushMatrix();

	glEnable(GL_NORMALIZE);

	float pointA[]={0.0f,1.0f};
	float pointB[]={0.25,1.0};
	float pointC[]={0.5,1.0};
	float pointD[]={0.75f,1.0f};
	float pointE[]={1.0,1.0};
	float pointF[]={0.0,0.5};
	float pointG[]={0.25f,0.5f};
	float pointH[]={0.5,0.5};
	float pointI[]={0.75,0.5};
	float pointJ[]={1.0,0.5};
	float pointK[]={0.0,0.0};
	float pointL[]={0.25,0.0};
	float pointM[]={0.5,0.0};
	float pointN[]={0.75,0.0};
	float pointO[]={1.0,0.0};

	// Display a quad size 1 by 1, centred at origin
	glBegin(GL_POLYGON);
				glNormal3f(0.0f, 1.0f, 0.0f);	// top face
				glTexCoord2f(pointC[0],pointC[1]);
				glVertex3f(0.5f, 0.5f, 0.5f);	
				glTexCoord2f(pointH[0],pointH[1]);
				glVertex3f(0.5f, 0.5f, -0.5f);
				glTexCoord2f(pointG[0],pointG[1]);
				glVertex3f(-0.5f, 0.5f, -0.5f);
				glTexCoord2f(pointB[0],pointB[1]);
				glVertex3f(-0.5f, 0.5f, 0.5f);
			glEnd();
			glBegin(GL_POLYGON);
				glNormal3f(0.0f, 0.0f, 1.0f);	// front face
				glTexCoord2f(pointI[0],pointI[1]);
				glVertex3f(0.5f, 0.5f, 0.5f);	
				glTexCoord2f(pointJ[0],pointJ[1]);
				glVertex3f(-0.5f, 0.5f, 0.5f);
				glTexCoord2f(pointO[0],pointO[1]);
				glVertex3f(-0.5f, -0.5f, 0.5f);
				glTexCoord2f(pointN[0],pointN[1]);
				glVertex3f(0.5f, -0.5f, 0.5f);
			glEnd();
			glBegin(GL_POLYGON);
				glNormal3f(1.0f, 0.0f, 0.0f);	// right face
				glTexCoord2f(pointI[0],pointI[1]);
				glVertex3f(0.5f, 0.5f, 0.5f);	
				glTexCoord2f(pointN[0],pointN[1]);
				glVertex3f(0.5f, -0.5f, 0.5f);
				glTexCoord2f(pointM[0],pointM[1]);
				glVertex3f(0.5f, -0.5f, -0.5f);
				glTexCoord2f(pointH[0],pointH[1]);
				glVertex3f(0.5f, 0.5f, -0.5f);
			glEnd();
			glBegin(GL_POLYGON);
				glNormal3f(-1.0f, 0.0f, 0.0f);	// left face
				glTexCoord2f(pointF[0],pointF[1]);
				glVertex3f(-0.5f, 0.5f, 0.5f);	
				glTexCoord2f(pointG[0],pointG[1]);
				glVertex3f(-0.5f, 0.5f, -0.5f);
				glTexCoord2f(pointL[0],pointL[1]);
				glVertex3f(-0.5f, -0.5f, -0.5f);
				glTexCoord2f(pointK[0],pointK[1]);
				glVertex3f(-0.5f, -0.5f, 0.5f);
			glEnd();
			glBegin(GL_POLYGON);
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
			glBegin(GL_POLYGON);
				glNormal3f(0.0f, 0.0f, -1.0f);	// back face
				glTexCoord2f(pointM[0],pointM[1]);
				glVertex3f(0.5f, -0.5f, -0.5f);
				glTexCoord2f(pointL[0],pointL[1]);
				glVertex3f(-0.5f, -0.5f, -0.5f);
				glTexCoord2f(pointG[0],pointG[1]);
				glVertex3f(-0.5f, 0.5f, -0.5f);
				glTexCoord2f(pointH[0],pointH[1]);
				glVertex3f(0.5f, 0.5f, -0.5f);	
			glEnd();

		glPopMatrix();
}