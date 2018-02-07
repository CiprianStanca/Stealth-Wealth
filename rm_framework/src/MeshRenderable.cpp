#include "stdafx.h"
#include "MeshRenderable.h"


CMeshRenderable::CMeshRenderable(char * filepath_)
{

	float maxx,maxy,maxz,minx,miny,minz;
	maxx=maxy=maxz=minx=miny=minz=0;

	//try to load data
   using namespace std;
   fstream file;

   // Open and close with a basic_filebuf
   file.open(filepath_,ios::in);
	//read number of verts

   file>>m_iNumVerts;
	m_iNumVerts/=3; //convert number of positions to number of 3d coordinate sets

	//now resize data structure to make room
	vertlist.resize(m_iNumVerts);
   for (int i=0;i<m_iNumVerts;i++)
	{
		file>>(vertlist[i].x);
		file>>(vertlist[i].y);
		file>>(vertlist[i].z);
		//update max sizes for bounding sphere
		if ((vertlist[i].x)>maxx){maxx=(vertlist[i].x);}
		if ((vertlist[i].y)>maxy){maxy=(vertlist[i].y);}
		if ((vertlist[i].z)>maxz){maxz=(vertlist[i].z);}
		if ((vertlist[i].x)<minx){minx=(vertlist[i].x);}
		if ((vertlist[i].y)<miny){miny=(vertlist[i].y);}
		if ((vertlist[i].z)<minz){minz=(vertlist[i].z);}
	} 

   //now we have max and minx etc we can calculate the radius of the bounding sphere
   float rangex = maxx - minx;
   float rangey = maxy - miny;
   float rangez = maxz - minz;

   float xcentre = minx + 0.5 * rangex;
   float ycentre = miny + 0.5 * rangey;
   float zcentre = minz + 0.5 * rangez;

   float halfxSquared =(0.5* rangex)*(0.5*rangex);
   float halfySquared =(0.5* rangey)*(0.5*rangey);
   float halfzSquared =(0.5* rangez)*(0.5*rangez);
   double radSquared = halfxSquared + halfySquared+halfzSquared;
   m_fRadius = (float)sqrt(radSquared);

   m_vBoundingSphereOffset.m_fX=xcentre;
   m_vBoundingSphereOffset.m_fY=ycentre;
   m_vBoundingSphereOffset.m_fZ=zcentre;

	//read number of normals

	file>>m_iNumNormals;
	m_iNumNormals/=3; //convert num positions into num 3d position coordinates
	
	//now resize data structure to make room
	normlist.resize(m_iNumNormals);
	
	for (int i=0;i<m_iNumNormals;i++)
	{
	file>>(normlist[i].x);
	file>>(normlist[i].y);
	file>>(normlist[i].z);
	} 

	//read number texture coordinates

	file>>m_iNumTexcoords;
	m_iNumTexcoords/=3; //convert num floats loaded to num (x,y) pairs

	//now resize data structure to make room
	texcoordlist.resize(m_iNumTexcoords);
	float dummy; //used to extract null information if texcoords are 3d

	for (int i=0;i<m_iNumTexcoords;i++)
	{
	file>>(texcoordlist[i].x);
	file>>(texcoordlist[i].y);
	file>> dummy;
	} 

	//read number of polygons
	//each triangle consists of index for coordinate, normal, texcoord for each of three vertices
	file>>m_iNumTriangleData;
	//m_iNumTriangleData/=9; //convert num integers loaded to num triangle data sets

	//now resize data structure to make room
	trilist.resize(m_iNumTriangleData);

	for (int i=0;i<m_iNumTriangleData;i++)
	{
		file>>(trilist[i].pointindex[0]);
		file>>(trilist[i].normalindex[0]);
		file>>(trilist[i].texcoordindex[0]);
	
		file>>(trilist[i].pointindex[1]);
		file>>(trilist[i].normalindex[1]);
		file>>(trilist[i].texcoordindex[1]);
	
		file>>(trilist[i].pointindex[2]);
		file>>(trilist[i].normalindex[2]);
		file>>(trilist[i].texcoordindex[2]);
	} 
	file.close(); //.rdbuf( )->close( );

	//debug text for loaded model
	char txt[128];
	sprintf(txt,"model %s loaded, x from %2.2f to %2.2f, y from %2.2f to %2.2f and z from %2.2f to %2.2f", filepath_, minx, maxx, miny, maxy, minz, maxz);
	DPrint(txt);

}


CMeshRenderable::~CMeshRenderable(void)
{
}

void 
CMeshRenderable::Render()
{
		//transform to position specified by GameObject
	if (m_pGameObject)
	{
		glTranslatef(m_pGameObject->GetTransform()->GetPosition().m_fX, m_pGameObject->GetTransform()->GetPosition().m_fY,m_pGameObject->GetTransform()->GetPosition().m_fZ);		// move to proper position
		
		//pitch is rotation about x axis
		glRotatef(m_pGameObject->GetTransform()->GetPitch(),1.0f,0.0f,0.0f);

		//yaw or heading is rotation about y axis
		glRotatef(m_pGameObject->GetTransform()->GetYaw(),0.0f,1.0f,0.0f);

		glScalef(m_pGameObject->GetTransform()->GetSize3().m_fX, m_pGameObject->GetTransform()->GetSize3().m_fY,m_pGameObject->GetTransform()->GetSize3().m_fZ);
	}



	glBegin(GL_TRIANGLES);
			int offset=0; //offset is relative to beginning of trilist
			for (int trianglenumber=0;trianglenumber<m_iNumTriangleData;trianglenumber++)
			{
				glTexCoord2f(texcoordlist[trilist[trianglenumber].texcoordindex[0]].x, texcoordlist[trilist[trianglenumber].texcoordindex[0]].y);
				glNormal3f(normlist[trilist[trianglenumber].normalindex[0]].x,normlist[trilist[trianglenumber].normalindex[0]].y,normlist[trilist[trianglenumber].normalindex[0]].z);
				glVertex3f(vertlist[trilist[trianglenumber].pointindex[0]].x,vertlist[trilist[trianglenumber].pointindex[0]].y,vertlist[trilist[trianglenumber].pointindex[0]].z);

				glTexCoord2f(texcoordlist[trilist[trianglenumber].texcoordindex[1]].x, texcoordlist[trilist[trianglenumber].texcoordindex[1]].y);
				glNormal3f(normlist[trilist[trianglenumber].normalindex[1]].x,normlist[trilist[trianglenumber].normalindex[1]].y,normlist[trilist[trianglenumber].normalindex[1]].z);
				glVertex3f(vertlist[trilist[trianglenumber].pointindex[1]].x,vertlist[trilist[trianglenumber].pointindex[1]].y,vertlist[trilist[trianglenumber].pointindex[1]].z);

				glTexCoord2f(texcoordlist[trilist[trianglenumber].texcoordindex[2]].x, texcoordlist[trilist[trianglenumber].texcoordindex[2]].y);
				glNormal3f(normlist[trilist[trianglenumber].normalindex[2]].x,normlist[trilist[trianglenumber].normalindex[2]].y,normlist[trilist[trianglenumber].normalindex[2]].z);
				glVertex3f(vertlist[trilist[trianglenumber].pointindex[2]].x,vertlist[trilist[trianglenumber].pointindex[2]].y,vertlist[trilist[trianglenumber].pointindex[2]].z);	
			}//end loop for each triangle
	glEnd();



}


float
CMeshRenderable::GetBoundingSphereRadius()
{
	return m_fRadius;
}

void
CMeshRenderable::GetBoundingSphereOffset(CVector3 * result_)
{
	(*result_) = m_vBoundingSphereOffset;
}