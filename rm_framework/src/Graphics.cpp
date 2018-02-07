#include "StdAfx.h"
#include "Graphics.h"




CGraphics::CGraphics(void)
{
	
}

CGraphics::~CGraphics(void)
{
}

void
CGraphics::InitializeGraphics(HWND hWnd)
{
	DPrint("Graphics: InitializeGraphics");

	s_hDC= GetDC(hWnd);
	bSetupPixelFormat(); // call our pixel format setup function
	s_hRC = wglCreateContext(s_hDC); // create rendering context 
	wglMakeCurrent(s_hDC, s_hRC); //and make it current
}


void
CGraphics::PrepareToRender()
{
	

	//DPrint("Graphics: Prepare To Render");
	//clear frame buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
CGraphics::FinishRenderingFrame()
{
	//check whether to show bounding spheres
	if (CInput::Instance()->GetIfKeyDownEvent(DIK_C))
	{
		bShowColliders=!bShowColliders;
	}
	//render bounding spheres
	if (bShowColliders)
	{
	CCollisionManager::Instance()->RenderAllColliders();
	}
	//DPrint("Graphics: FinishRenderingFrame");
	// bring backbuffer to foreground
	SwapBuffers(s_hDC);
}

void 
CGraphics::PrepareChangeProjection()
{
	glMatrixMode(GL_PROJECTION);//set projection as //current matrix
	glLoadIdentity(); 
}


void 
CGraphics::FinishedChangeProjection()
{
	glMatrixMode(GL_MODELVIEW);	// set modelview matrix
	glLoadIdentity();		// reset modelview matrix
}


void 
CGraphics::PerspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	PrepareChangeProjection();
	//From http://nehe.gamedev.net/article/replacement_for_gluperspective/21002/

	const GLdouble pi = 3.1415926535897932384626433832795;
	GLdouble fW, fH;
	
	fH = tan(fovY / 360 * pi) * zNear;
	fW = fH * aspect;

	glFrustum(-fW, fW, -fH, fH, zNear, zFar);
	FinishedChangeProjection();
}


void
CGraphics::OrthoGL(float left_, float right_, float bottom_, float top_ )
{
	PrepareChangeProjection();
	glOrtho(left_, right_, bottom_, top_, -1, 1);
	FinishedChangeProjection();
}


void
CGraphics::SetWindowSize(int width_, int height_)
{
	char txt[64];
	sprintf(txt,"Graphics: SetWindowSize(%d,%d)",width_,height_);
	DPrint(txt);
	int width, height;
	m_iWinWidth=width_;
	m_iWinHeight=height_;

		if (m_iWinHeight==0)		// don't want a divide by zero
		{
		m_iWinHeight=1;					
		}
		glViewport(0, 0, m_iWinWidth, m_iWinHeight);	// reset the viewport to new dimensions
		//glMatrixMode(GL_PROJECTION);//set projection as //current matrix

		{
			//glLoadIdentity(); 
			float aspect=(float)m_iWinWidth/(float)m_iWinHeight;
			float halfheight=5.0f; //set screen to display 10 units high
			float heightwidth=aspect*halfheight; //width depends on screen aspect
			if (b2DMode)
			{
				//25/02/2014 change
				//gluOrtho2D should be the same as glOrtho; you just need the clipping planes included too
				OrthoGL(-heightwidth, heightwidth, -halfheight, halfheight);
				//gluOrtho2D(-heightwidth, heightwidth, -halfheight, halfheight);
			}
			else
			{

				//25/02/2014 Change - Oliver
				//Replacement for glu function for perspective.
				//Stolen from NeHe because it was concise; but we now call
				//glfrustum directly
				//gluPerspective(45.0f,aspect,0.1f,1000.0f);
				PerspectiveGL(45.0f, aspect, 0.1f, 1000.0f);
			}

		}

		//glMatrixMode(GL_MODELVIEW);	// set modelview matrix
		//glLoadIdentity();		// reset modelview matrix
}

void
CGraphics::DestroyGraphicsWindow(HWND &hWnd)
{
	DPrint("Graphics: DestroyGraphicsWindow");

	wglMakeCurrent(NULL, NULL); //This frees our rendering memory and sets 
									//everything back to normal
	wglDeleteContext(s_hRC);	// Delete our OpenGL Rendering Context	
	s_hRC=NULL; 

	if (s_hDC) 
	{
		ReleaseDC(hWnd, s_hDC);
		s_hDC=NULL;
	}



}


void
CGraphics::DrawTestObject()
{
	//DPrint("Graphics: DrawTestObject");

	float fX,fY;
	float fW,fH;
	fX=0.0f;
	fY=0.0f;
	fW=1.0f;
	fH=1.0f;
	int iTextureID=0;

	glLoadIdentity();

	glEnable(GL_BLEND);// Turn Blending On
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glTranslatef(fX,fY,0);		// move to proper position
	glScalef(fW,fH,1);
	glColor4f(1,1,1,1);		// set color

	if (iTextureID)
	{
		//use texture
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, iTextureID); 
	}
	else
	{
		//zero for texture ID means don't use texture
		glDisable(GL_TEXTURE_2D);
	}

// Display a quad size 1 by 1, centred at origin
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-0.5, 0.5);

		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-0.5, -0.5);

		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(0.5, -0.5);

		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(0.5, 0.5);
	glEnd();

}


bool
CGraphics::bSetupPixelFormat()
{
	DPrint("Graphics: bSetupPixelFormat");


	PIXELFORMATDESCRIPTOR pfd; 
	int pixelformat; 
 
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);// Set the size of the structure
	pfd.nVersion = 1;					// Always set this to 1
													// Pass in the appropriate OpenGL flags
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; 
	pfd.dwLayerMask = PFD_MAIN_PLANE;	
	// We want the standard mask (this is ignored anyway)
	pfd.iPixelType = PFD_TYPE_RGBA;	// We want RGB and Alpha pixel type
	pfd.cColorBits = 16;						
	pfd.cDepthBits = 0;// Depthbits is ignored for RGBA, but do it anyway
	pfd.cAccumBits = 0;	// No special bitplanes needed
	pfd.cStencilBits = 0;	// We desire no stencil bits
 
// get a pixel format that best matches one passed in from the device
    if ( (pixelformat = ChoosePixelFormat(s_hDC, &pfd)) == FALSE ) 
    { 
        MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK); 
        return FALSE; 
    } 
 
// This sets the pixel format that we extracted from above
    if (SetPixelFormat(s_hDC, pixelformat, &pfd) == FALSE) 
    { 
        MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK); 
        return FALSE; 
    } 
 
    return TRUE;
}

HDC CGraphics::s_hDC=0; // General HDC - (handle to device context)
HGLRC CGraphics::s_hRC=0; // General OpenGL_DC - Our Rendering Context for OpenGL
bool CGraphics::b2DMode=false;
int CGraphics::m_iWinWidth=0;
int CGraphics::m_iWinHeight=0;
bool CGraphics::bShowColliders=true;