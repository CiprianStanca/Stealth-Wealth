#include "StdAfx.h"
#include "ColourMaterial.h"
//#include <gl\gl.h>

CColourMaterial::CColourMaterial(bool bAdditive_)
{

	m_fRed=1.0f;
	m_fGreen=1.0f;
	m_fBlue=1.0f;
	m_fAlpha=1.0f;
	m_iTextureID=0;
	m_bAdditiveBlending=bAdditive_;
}

CColourMaterial::~CColourMaterial(void)
{
}

void
CColourMaterial::SetColour(float r_, float g_, float b_, float a_)
{
	m_fRed=r_;
	m_fGreen=g_;
	m_fBlue=b_;
	m_fAlpha=a_;
}


void 
CColourMaterial::SetTexture(int textureID_)
{
	m_iTextureID=textureID_;
}


void
CColourMaterial::SetupRendering()
{
	if (m_iTextureID)
	{
		//texture specified
		glBindTexture(GL_TEXTURE_2D, m_iTextureID); //use the one and only texture
		glEnable(GL_TEXTURE_2D);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}

	glEnable(GL_BLEND);// Turn Blending On
	if (m_bAdditiveBlending)
	{
		glBlendFunc(GL_ONE, GL_ONE);
	}
	else
	{
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	}

	//glLoadIdentity();
	glColor4f(m_fRed,m_fGreen,m_fBlue,m_fAlpha);		// set color to red
	glDisable(GL_LIGHTING); 

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable (GL_DEPTH_TEST);
}

