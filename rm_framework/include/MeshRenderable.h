#pragma once
#include <vector>
using namespace std;
#include "irenderable.h"


struct point3d{
	float x;
	float y;
	float z;
};

struct point2d{
	float x;
	float y;
};

struct vertexdata{
	int pointindex[3];
	int normalindex[3];
	int texcoordindex[3];
};

class CMeshRenderable :
	public IRenderable
{
public:
	CMeshRenderable(char * filepath_);
	~CMeshRenderable(void);
	void Render();
	float GetBoundingSphereRadius();
	void GetBoundingSphereOffset(CVector3 * result_);
	char * GetType(){return "IMeshRenderable";}

private:
	vector <point3d> vertlist; //point3d vertlist[485];//vertex list
	vector <point3d> normlist; //point3d normlist[507];//normals list
	vector <point2d> texcoordlist; //point2d texcoordlist[1608];//tex coord list
	vector <vertexdata> trilist; //int trilist[943];//triangle list  943/6

	int m_iNumVerts;
	int m_iNumNormals;
	int m_iNumTexcoords;
	int m_iNumTriangleData;

	float m_fRadius;
	CVector3 m_vBoundingSphereOffset;
};

