#include "stdafx.h"
#include "SkyBoxMaterial.h"


CSkyBoxMaterial::CSkyBoxMaterial(void)
{
}


CSkyBoxMaterial::~CSkyBoxMaterial(void)
{
}

void
CSkyBoxMaterial::SetupRendering()
{
	CColourMaterial::SetupRendering();
	glDisable(GL_BLEND);// Turn Blending Off


	glDisable(GL_LIGHTING); 


	GLfloat white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat grey[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);


	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glEnable (GL_DEPTH_TEST);

	//glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
		 // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    //glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE );
   // glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_EXT_CLAMP_TO_EDGE );
}