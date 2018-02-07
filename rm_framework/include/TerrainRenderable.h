#pragma once
#include <FreeImage.h>
#include "irenderable.h"
//#include <gl/gl.h> //for RGB image

class CVector3;

class CTerrainRenderable :
	public IRenderable
{
public:
	CTerrainRenderable(char * filename_);
	~CTerrainRenderable(void);
	float GetHeightAtPoint(float x_, float z_);
	void Load();
	void Unload();
	void Render();
	


private:
	int m_iMapVerticesx;
	int m_iMapVerticesz;
	float m_fTerrainStepWidth;
	float m_fTerrainStepHeight;
	GLuint m_iDisplayList;
			
	FREE_IMAGE_FORMAT imgFormat;
	FIBITMAP * pBitmap;
	BYTE * m_pImageData;

	bool m_bDisplayListCreated;

	std::vector <float> m_vHeights;
	std::vector <CVector3 *> m_vNormals;

	void ComputeNormals();
	void ComputeVertexHeights();
	void CreateDisplayList();
	void AddedToGameObject();
	CVector3 * ComputeCrossProduct(int x1,int z1,int x2,int z2,int x3,int z3) ;

};

