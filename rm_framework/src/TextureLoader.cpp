#include "stdafx.h"
#include "TextureLoader.h"

#pragma comment(lib, "FreeImage.lib")

static UINT texturecount = 0;
CTextureLoader * CTextureLoader::m_instance = 0;

UINT g_Texture[200];

bool
CTextureLoader::CreateTexture(LPSTR _fileName, int _texID)
{
	imgFormat = FreeImage_GetFileType(_fileName, 0);	
	pBitmap = FreeImage_Load(imgFormat, _fileName);
	
	if (!CreateGLTexture(_texID))
		{
			return false;
		};

	FreeImage_Unload(pBitmap);
	return true;
}

bool CTextureLoader::CreateGLTexture(int textureID)
{
	int imgBPP = FreeImage_GetBPP(pBitmap);
	int imgWidth = FreeImage_GetWidth(pBitmap);
	int imgHeight = FreeImage_GetHeight(pBitmap);
	GLubyte * imgBits = FreeImage_GetBits(pBitmap);

	glGenTextures(1, &g_Texture[textureID]);
	glBindTexture(GL_TEXTURE_2D, g_Texture[textureID]);	

	if (imgBPP ==32) //image usess alpha channel
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,  imgWidth, imgHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, imgBits);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,  imgWidth, imgHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, imgBits);
	}
	//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, imgWidth, imgHeight, GL_BGR_EXT , GL_UNSIGNED_BYTE, imgBits);//pBitmap->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (glGetError())
	{
		int x = glGetError();
		return false;
	}
	return true;
}

CTextureLoader& CTextureLoader::getInstance()
{
	if (!m_instance)
	{
		m_instance = new CTextureLoader();
	}

	return * m_instance;
}