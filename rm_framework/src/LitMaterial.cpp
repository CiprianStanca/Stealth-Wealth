#include "stdafx.h"
#include "LitMaterial.h"


LitMaterial::LitMaterial(void)
{
}


LitMaterial::~LitMaterial(void)
{
}


void
LitMaterial::SetupRendering()
{
	CColourMaterial::SetupRendering();
	glDisable(GL_BLEND);// Turn Blending On
	//add a light source - directional light
	GLfloat  position[4]={0,5,10,0};
	GLfloat color[4]={1,1,1,1};
	GLfloat ambient[4]={0.4f,0.4f,0.4f,1};
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glEnable(GL_LIGHT0); 
	glEnable(GL_LIGHTING); 
	//glDisable(GL_LIGHTING); 


	GLfloat white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat grey[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);


	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable (GL_DEPTH_TEST);
}