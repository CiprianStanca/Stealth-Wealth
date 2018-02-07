#include <FreeImage.h>
//#include <gl/GL.h>

#pragma once



class CTextureLoader
{
	public:
		bool CreateTexture(LPSTR strFileName, int textureID);
		void CheckBitDepth();
		static CTextureLoader& getInstance();
		GLuint g_Texture[200];

	private:		

		CTextureLoader (const CTextureLoader &){};
		CTextureLoader & operator=(const CTextureLoader &){};
		CTextureLoader(){};
		~CTextureLoader();
		
		bool CreateGLTexture(int _texID); //Creates a new OpenGL texture
		void CreateGLESTexture(){};
		void CreateDX9Texture(){};
		void CreateDX11Texture(){};
				
		FREE_IMAGE_FORMAT imgFormat;
		FIBITMAP * pBitmap;
		static UINT textureCount;
		static CTextureLoader * m_instance;
};
