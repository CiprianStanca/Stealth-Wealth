#pragma once

/* static functions to manage OpenGL rendering */

class CGraphics
{
public:
	CGraphics(void);
	~CGraphics(void);

	static void PrepareToRender();
	static void FinishRenderingFrame();
	static void InitializeGraphics(HWND hWnd);
	static void SetWindowSize(int width, int height);
	static void DestroyGraphicsWindow(HWND &hWnd);
	static void DrawTestObject(); 

	static void PerspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);
	static void OrthoGL(float left_, float right_, float bottom_, float top_ );

	static int GetWidth(){return m_iWinWidth;}
	static int GetHeight(){return m_iWinHeight;}

private:

	static bool bSetupPixelFormat();
	static bool b2DMode;
	static HDC   s_hDC; // General HDC - (handle to device context)
	static HGLRC s_hRC; // General OpenGL_DC - Our Rendering Context for OpenGL
	static int m_iWinWidth;
	static int m_iWinHeight;

	static void PrepareChangeProjection();
	static void FinishedChangeProjection();

	static bool bShowColliders;

};
