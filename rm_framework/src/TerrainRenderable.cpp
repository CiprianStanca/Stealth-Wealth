#include "stdafx.h"
#include "TerrainRenderable.h"


CTerrainRenderable::CTerrainRenderable(char * filename_)
{
	imgFormat = FreeImage_GetFileType(filename_, 0);	
	pBitmap = FreeImage_Load(imgFormat, filename_);

	int imgBPP = FreeImage_GetBPP(pBitmap);
	m_iMapVerticesx = FreeImage_GetWidth(pBitmap);
	m_iMapVerticesz = FreeImage_GetHeight(pBitmap);

	char outputDebug[64];
	sprintf(outputDebug,"\n***loading heightfield with size: %d * %d**\n",m_iMapVerticesx,m_iMapVerticesz);
	OutputDebugString(outputDebug);

	m_pImageData = FreeImage_GetBits(pBitmap);

	
	m_bDisplayListCreated=0;
	//resize data structures to match size of image loaded
	m_vHeights.resize(m_iMapVerticesx*m_iMapVerticesz);
	m_vNormals.resize(m_iMapVerticesx*m_iMapVerticesz);
	//calculate how much u,v coordinates change by in each step
	m_fTerrainStepWidth=1.0f/m_iMapVerticesx;
	m_fTerrainStepHeight=1.0f/m_iMapVerticesz;

	ComputeVertexHeights();
	ComputeNormals();

	//for debugging, printout a few of the normals

}

void
CTerrainRenderable::AddedToGameObject()
{
	//tag this object with 'Terrain'
	CTagManager::Instance()->AddTag(m_pGameObject,"Terrain");

	//switch off terrain following
	m_pGameObject->GetTransform()->m_bClampToTerrain=false;
}


void
CTerrainRenderable::Load()
{

}

void
CTerrainRenderable::Unload()
{
	if( m_pImageData )
    {
        free( m_pImageData );
    }

	glCallList(m_iDisplayList);
}

CTerrainRenderable::~CTerrainRenderable(void)
{
}


void
CTerrainRenderable::Render()
{
	if (!m_bDisplayListCreated)
	{
		m_bDisplayListCreated=true;
		CreateDisplayList();
	}

		//transform to position specified by GameObject
	if (m_pGameObject)
	{
		glTranslatef(m_pGameObject->GetTransform()->GetPosition().m_fX, m_pGameObject->GetTransform()->GetPosition().m_fY,m_pGameObject->GetTransform()->GetPosition().m_fZ);		// move to proper position
		glRotatef(m_pGameObject->GetTransform()->GetYaw(),0.0f,1.0f,0.0f);
		glScalef(m_pGameObject->GetTransform()->GetSize3().m_fX, m_pGameObject->GetTransform()->GetSize3().m_fY,m_pGameObject->GetTransform()->GetSize3().m_fZ);
	}

	glCallList(m_iDisplayList);
}



//function analyzes each vertex in terrain
//looks at adjacent triangles, determines the normal for each adjacent triangle
//then calculates the average normal vector of all the triangles that meet at the vertex
void
CTerrainRenderable::ComputeNormals()
{
float xfactor=1.0f/(m_iMapVerticesx-1);
float zfactor=1.0f/(m_iMapVerticesz-1);

for (int z=0;z<(m_iMapVerticesz);z++)
{
		for (int x=0;x<(m_iMapVerticesx);x++)
        {	
			CVector3 * norm1=new CVector3();
			CVector3 * norm2=new CVector3();
			
			//for the four corners
			if (x == 0 && z == 0) {
				norm1 = ComputeCrossProduct(0,0, 0,1, 1,0);	
				norm1->Normalise();			
			}
			else if (x == m_iMapVerticesx-1 && z == m_iMapVerticesz-1) {
				norm1 = ComputeCrossProduct(x,z, x,z-1, x-1,z);	
				norm1->Normalise();				
			}
			else if (x == 0 && z == m_iMapVerticesz-1) {
				norm1 = ComputeCrossProduct(x,z, x+1,z,x,z-1 );	
				norm1->Normalise();			
			}
			else if (x == m_iMapVerticesx-1 && z == 0) {
				norm1 = ComputeCrossProduct(x,z, x-1,z, x,z+1);	
				norm1->Normalise();					
			}


			//for the edges
			/* normals for the borders -> calc average of two triangles */
			else if (z == 0) {
				norm1 = ComputeCrossProduct(x,0, x-1,0, x,1);
				norm1->Normalise();	
				
				norm2 = ComputeCrossProduct(x,0,x,1,x+1,0);
				norm2->Normalise();	
				norm1->AddVector(norm2);
				norm1->Normalise();	
			}
			else if (x == 0) {
				norm1 = ComputeCrossProduct(0,z,1,z, 0,z-1 );
				norm1->Normalise();	
				
				norm2 = ComputeCrossProduct(0,z,0,z+1,1,z);
				norm2->Normalise();	
				norm1->AddVector(norm2);
				norm1->Normalise();	
			}
			else if (x == m_iMapVerticesx-1) {
				norm1 = ComputeCrossProduct(x,z, x,z-1, x-1,z);
				norm1->Normalise();	
				
				norm2 = ComputeCrossProduct(x,z,x-1,z,x,z+1);
				norm2->Normalise();	
				norm1->AddVector(norm2);
				norm1->Normalise();	
			}
			else if (z == m_iMapVerticesz-1) {
				norm1 = ComputeCrossProduct(x,z, x+1,z, x,z-1);
				norm1->Normalise();	
				
				norm2 = ComputeCrossProduct(x,z,x,z-1,x-1,z);
				norm2->Normalise();	
				norm1->AddVector(norm2);
				norm1->Normalise();	
			}

			//for inner vertices, compute
			else 
			{
			norm1 = ComputeCrossProduct(x,z, x-1,z, x-1,z+1);
			norm1->Normalise();	
				
			norm2 = ComputeCrossProduct(x,z, x-1,z+1, x,z+1);
			norm2->Normalise();	
			norm1->AddVector(norm2);
				
			norm2 = ComputeCrossProduct(x,z, x,z+1, x+1,z+1);
			norm2->Normalise();	
			norm1->AddVector(norm2);
				
			norm2 = ComputeCrossProduct(x,z, x+1,z+1, x+1,z);
			norm2->Normalise();	
			norm1->AddVector(norm2);
				
			norm2 = ComputeCrossProduct(x,z, x+1,z, x+1,z-1);
			norm2->Normalise();	
			norm1->AddVector(norm2);
				
			norm2 = ComputeCrossProduct(x,z, x+1,z-1, x,z-1);
			norm2->Normalise();	
			norm1->AddVector(norm2);
				
			norm2 = ComputeCrossProduct(x,z, x,z-1, x-1,z-1);
			norm2->Normalise();	
			norm1->AddVector(norm2);
				
			norm2 = ComputeCrossProduct(x,z, x-1,z-1, x-1,z);
			norm2->Normalise();	
			norm1->AddVector(norm2);
			norm1->Normalise();	
			}
			
			int index=x+m_iMapVerticesx * z;
			m_vNormals[index]=norm1;
		}
}
}


//compute the normal of a face using the indices of its three vertices
CVector3 *
CTerrainRenderable::ComputeCrossProduct(int x1,int z1,int x2,int z2,int x3,int z3) 
{

	float v1[3],v2[3];
		
	v1[0] = (x2-x1) * m_fTerrainStepWidth; 
	v1[1] = -m_vHeights[z1 * m_iMapVerticesx + x1] 
			+ m_vHeights[z2 * m_iMapVerticesx + x2];
	v1[2] = (z2-z1) * m_fTerrainStepHeight; 


	v2[0] = (x3-x1) * m_fTerrainStepWidth; 
	v2[1] = -m_vHeights[z1 * m_iMapVerticesx + x1] 
			+ m_vHeights[z3 * m_iMapVerticesx + x3];
	v2[2] = (z3-z1) * m_fTerrainStepHeight; 

	CVector3 * pAuxNormal=new CVector3();

	pAuxNormal->m_fX = v1[1] * v2[2] - v1[2] * v2[1];
	pAuxNormal->m_fY = v1[2] * v2[0] - v1[0] * v2[2];
	pAuxNormal->m_fZ = v1[0] * v2[1] - v1[1] * v2[0];

	return(pAuxNormal);
}

void
CTerrainRenderable::ComputeVertexHeights()
{
	
	float xfactor=1.0f/(m_iMapVerticesx-1);
	float zfactor=1.0f/(m_iMapVerticesz-1);

	for (int z=0;z<(m_iMapVerticesz-1);z++)
	{
			for (int x=0;x<(m_iMapVerticesx-1);x++)
			{	
				
					int vertxindex=x;
					int vertzindex=z;				
					float xprop=xfactor*vertxindex;
					float zprop=zfactor*vertzindex;
					float y=(m_pImageData[(vertzindex*m_iMapVerticesz+vertxindex)*3])/255.0f;
					m_vHeights[vertxindex + m_iMapVerticesx * vertzindex]=y;

					vertxindex=x;
					vertzindex=z+1;				
					xprop=xfactor*vertxindex;
					zprop=zfactor*vertzindex;
					glTexCoord2f(xprop,zprop);
					y=(m_pImageData[(vertzindex*m_iMapVerticesz+vertxindex)*3])/255.0f;
					m_vHeights[vertxindex + m_iMapVerticesx * vertzindex]=y;	

					vertxindex=x+1;
					vertzindex=z;				
					xprop=xfactor*vertxindex;
					zprop=zfactor*vertzindex;
					y=(m_pImageData[(vertzindex*m_iMapVerticesz+vertxindex)*3])/255.0f;
					m_vHeights[vertxindex + m_iMapVerticesx * vertzindex]=y;


					vertxindex=x+1;
					vertzindex=z+1;				
					xprop=xfactor*vertxindex;
					zprop=zfactor*vertzindex;
					y=(m_pImageData[(vertzindex*m_iMapVerticesz+vertxindex)*3])/255.0f;
					m_vHeights[vertxindex + m_iMapVerticesx * vertzindex]=y;

				}
			
			}
}


void
CTerrainRenderable::CreateDisplayList()
{
	m_iDisplayList= glGenLists(1);
	glNewList(m_iDisplayList,GL_COMPILE);

	float xfactor=1.0f/(m_iMapVerticesx-1);
	float zfactor=1.0f/(m_iMapVerticesz-1);

	float xTile=10; //how may times texture repeats in x
	float zTile=10; //how many times texture repeats in z

	for (int z=0;z<(m_iMapVerticesz-1);z++)
	{
			for (int x=0;x<(m_iMapVerticesx-1);x++)
			{	
				glBegin(GL_TRIANGLES);
				{	
				

					int vertxindex=x;
					int vertzindex=z;				
					float xprop=xfactor*vertxindex;
					float zprop=zfactor*vertzindex;
					float y = (m_pImageData[(vertzindex*m_iMapVerticesz + vertxindex) * 3]) / 255.0f;
					CVector3 * norm=m_vNormals[vertxindex+m_iMapVerticesx * vertzindex];
					glNormal3f(norm->m_fX,norm->m_fY,norm->m_fZ);
					glTexCoord2f(xprop*xTile,zprop*zTile);
					glVertex3f(-0.5f+xprop,y,-0.5f+zprop);		//v0	

					vertxindex=x;
					vertzindex=z+1;				
					xprop=xfactor*vertxindex;
					zprop=zfactor*vertzindex;
					norm=m_vNormals[vertxindex+m_iMapVerticesx * vertzindex];
					glNormal3f(norm->m_fX,norm->m_fY,norm->m_fZ);
					glTexCoord2f(xprop*xTile,zprop*zTile);
					y = (m_pImageData[(vertzindex*m_iMapVerticesz + vertxindex) * 3]) / 255.0f;
					glVertex3f(-0.5f+xprop,y,-0.5f+zprop);	//v1	

					vertxindex=x+1;
					vertzindex=z;				
					xprop=xfactor*vertxindex;
					zprop=zfactor*vertzindex;
					norm=m_vNormals[vertxindex+m_iMapVerticesx * vertzindex];
					glNormal3f(norm->m_fX,norm->m_fY,norm->m_fZ);
					glTexCoord2f(xprop*xTile,zprop*zTile);
					y = (m_pImageData[(vertzindex*m_iMapVerticesz + vertxindex) * 3]) / 255.0f;
					glVertex3f(-0.5f+xprop,y,-0.5f+zprop);     //v2
				
				
					vertxindex=x+1;
					vertzindex=z;				
					xprop=xfactor*vertxindex;
					zprop=zfactor*vertzindex;
					norm=m_vNormals[vertxindex+m_iMapVerticesx * vertzindex];
					glNormal3f(norm->m_fX,norm->m_fY,norm->m_fZ);
					glTexCoord2f(xprop*xTile,zprop*zTile);
					y = (m_pImageData[(vertzindex*m_iMapVerticesz + vertxindex) * 3]) / 255.0f;
					glVertex3f(-0.5f+xprop,y,-0.5f+zprop);    //v2	

					vertxindex=x;
					vertzindex=z+1;				
					xprop=xfactor*vertxindex;
					zprop=zfactor*vertzindex;
					norm=m_vNormals[vertxindex+m_iMapVerticesx * vertzindex];
					glNormal3f(norm->m_fX,norm->m_fY,norm->m_fZ);
					glTexCoord2f(xprop*xTile,zprop*zTile);
					y = (m_pImageData[(vertzindex*m_iMapVerticesz + vertxindex) * 3]) / 255.0f;
					glVertex3f(-0.5f+xprop,y,-0.5f+zprop);    //v1	

					vertxindex=x+1;
					vertzindex=z+1;				
					xprop=xfactor*vertxindex;
					zprop=zfactor*vertzindex;
					norm=m_vNormals[vertxindex+m_iMapVerticesx * vertzindex];
					glNormal3f(norm->m_fX,norm->m_fY,norm->m_fZ);
					glTexCoord2f(xprop*xTile,zprop*zTile);
					y = (m_pImageData[(vertzindex*m_iMapVerticesz + vertxindex) * 3]) / 255.0f;
					glVertex3f(-0.5f+xprop,y,-0.5f+zprop);  //v3
				}
				glEnd();
			}
	}

	glEndList();

	GLenum error=glGetError();
	int x=1;


}

float 
CTerrainRenderable::GetHeightAtPoint(float x_,float z_)
{
	//original terrain has been scaled and translated
	//so undo translation
	if (m_pGameObject==0)
		{
			return 0.0f;
		}

	float x_relative=x_ - m_pGameObject->GetTransform()->GetPosition().m_fX;
	float z_relative=z_ - m_pGameObject->GetTransform()->GetPosition().m_fZ;
	//now undo scale
	x_relative/=m_pGameObject->GetTransform()->GetSize3().m_fX;
	z_relative/=m_pGameObject->GetTransform()->GetSize3().m_fZ;

	//add 0.5 to convert range back to 0->1
	x_relative+=0.5f;
	z_relative+=0.5f;
	//calculate xmin,max and zmin max
	//float xmin,xmax,zmin,zmax;

	if (x_relative<0.0f || x_relative>1.0f) return 0;
	if (z_relative<0.0f || z_relative>1.0f) return 0;

	//position of ith vertex in x direction
	//=xmin+i* m_fw/m_iMapVerticesx
	//z=zmin+ j* m_fd/m_iMapVerticesz
	int whichvertexx,whichvertexz;
	whichvertexx=(int)(x_relative*(m_iMapVerticesx-1));
	whichvertexz=(int)(z_relative*(m_iMapVerticesz-1));

	// compute the height field coordinates (Col0, Row0)
	// and (Col1, Row1) that identify the height field cell 
	// directly below the camera.
	int col0 = whichvertexx;
	int row0 = whichvertexz;
	int col1 = col0 + 1;
	int row1 = row0 + 1;

	// make sure that the cell coordinates don't fall
	// outside the height field.
	if (col1 > m_iMapVerticesx)
		col1 = 0;
	if (row1 > m_iMapVerticesz)
		row1 = 0;

	// get the four corner heights of the cell from the height field
	int h00 = m_pImageData[3*(col0 +row0*m_iMapVerticesz)];
	int h01 = m_pImageData[3*(col1 + row0*m_iMapVerticesz)];
	int h11 = m_pImageData[3*(col1 + row1*m_iMapVerticesz)];
	int h10 = m_pImageData[3*(col0 + row1*m_iMapVerticesz)];

	// calculate the position of the point relative to the cell.
	// note, that 0 <= tx, ty <= 1.
	float tx = (x_relative - float(col0)/m_iMapVerticesx)*64;
	float tz = (z_relative - float(row0)/m_iMapVerticesz)*64;

	// the next step is to perform a bilinear interpolation
	// to compute the height of the terrain directly below
	// the object.
	float txtz = tx * tz;

	float final_height = (float)h00 * (1.0f - tz - tx + txtz)
						+ (float)h01 * (tx - txtz)
						+ (float)h11 * txtz
						+ (float)h10 * (tz - txtz);

	
	
	 final_height*=(m_pGameObject->GetTransform()->GetSize3().m_fY)/255.0f;
	 return final_height;
}