#include "stdafx.h"
#include "GUITextureRenderable.h"


CGUITextureRenderable::CGUITextureRenderable()
{
	
}


CGUITextureRenderable::~CGUITextureRenderable(void)
{
}


void
CGUITextureRenderable::Render()
{
	//now do 2d rendering
	//setup orthographic projection
	CGraphics::OrthoGL(-0.5,0.5,-0.5,0.5);


	//render 2d stuff
	if (m_pGameObject)
	{
		glTranslatef(m_pGameObject->GetTransform()->GetPosition().m_fX, m_pGameObject->GetTransform()->GetPosition().m_fY,m_pGameObject->GetTransform()->GetPosition().m_fZ);		// move to proper position
		glScalef(m_pGameObject->GetTransform()->GetSize3().m_fX, m_pGameObject->GetTransform()->GetSize3().m_fY,m_pGameObject->GetTransform()->GetSize3().m_fZ);
	}

	// Display a quad size 1 by 1, centred at origin
	glBegin(GL_QUADS);
		glTexCoord3f(0.0f, 1.0f, 0.0f);
		glVertex2f(-0.5, 0.5);

		glTexCoord3f(0.0f, 0.0f ,0.0f);
		glVertex2f(-0.5, -0.5);

		glTexCoord3f(1.0f, 0.0f,0.0f);
		glVertex2f(0.5, -0.5);

		glTexCoord3f(1.0f, 1.0f, 0.0f);
		glVertex2f(0.5, 0.5);
	glEnd();

	//now set it back to normal 3d
	CGraphics::PerspectiveGL(45.0f,1.33,0.1f,1000.0f);


}