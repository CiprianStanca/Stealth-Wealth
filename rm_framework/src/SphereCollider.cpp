
#include "stdafx.h"
#include "SphereCollider.h"

CSphereCollider::CSphereCollider(float rad_)
{
	m_fRadius= rad_;
	m_bIsTrigger = false;
}


CSphereCollider::~CSphereCollider(void)
{

}
	
void 
CSphereCollider::Render()
{
	//calculate updated radius
	//depends on original radius * scale factor
	GetScaledRadius();

	if (m_pGameObject)
	{
		glPushMatrix();
		
		//draw collider as sphere, centred at transform position
		glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE ); //wireframe mode
		glDisable(GL_CULL_FACE); //don't cull faces
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
	

		glTranslatef(m_vPosition.m_fX,m_vPosition.m_fY,m_vPosition.m_fZ );

		GLUquadric* newQuad= gluNewQuadric(); 
		gluQuadricTexture(newQuad,1);
		gluSphere ( newQuad , m_fScaledRadius , 32, 32) ;//temp remove * rad

		//put things back to normal
		glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL ); //wireframe mode
		glEnable(GL_CULL_FACE); //don't cull faces
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);

		glPopMatrix();


	}
}

float 
CSphereCollider::GetScaledRadius()
{
	m_fScaledRadius=m_fRadius * m_vScale.m_fX;
	return m_fScaledRadius;
}

 bool  
CSphereCollider::CheckForCollision(ICollider * in_)
 {
	GetScaledRadius();

	float dx,dy,dz;
	CSphereCollider * insphere = (CSphereCollider *)in_;
	dx=m_vPosition.m_fX-insphere->m_vPosition.m_fX;
	dy=m_vPosition.m_fY-insphere->m_vPosition.m_fY;
	dz=m_vPosition.m_fZ-insphere->m_vPosition.m_fZ;

	//use pythag
	double separation;
	separation=sqrt(dx*dx+dy*dy+dz*dz);
	//sum of radii
	double sumradii=m_fScaledRadius+insphere->GetScaledRadius();

	return (separation<sumradii);
 }

 bool
 CSphereCollider::CheckForCollisionWithRay(CVector3 raystart_,CVector3 raydirection_, float raylength_,CVector3 * hitPoint_)
 {
		
	 //if I am attached to camera then return a false
	IRenderable * ren= m_pGameObject ->GetRenderable();
	char * type=ren->GetType();
	if (type[1]=='C' && type[2]=='a')
	{
		return false;
	}
	 //does ray intersect bounding sphere?

		//compute vector from beginning of ray to centre of sphere
		CVector3 vRayStartToSphereCentre = m_vPosition-raystart_;
		//get dot product of this vector with ray direction
		float dotp=vRayStartToSphereCentre.DotProduct(&raydirection_);

		char debugtxt[256];
	

		if (dotp<0)
		{
			//no collision, sphere behind ray
			//sprintf(debugtxt,"%d,no collision with %s. dotprod:%2.2f\n",i,typeid(*obj).name(),dotp);
		}
		else
		{
			//sphere centre projects onto line
			//calc projected point of centre of sphere on line
			CVector3 vCentreProjOnLine = raystart_ + raydirection_ * dotp;
			//calc distance from centre to projected point
			CVector3 vCentreToProjectedPoint=vCentreProjOnLine-m_vPosition;
			float dist=vCentreToProjectedPoint.GetLength();
			if (dist > m_fScaledRadius)
			{
				//no collision
				//sprintf(debugtxt,"%d,no collision with %s. distance to centre:%2.2f, radius:2.2f\n",i,typeid(*obj).name(),dist,sphrad);
				
			}
			else
			{
				//there is a collision with obj
				sprintf(debugtxt," collision with %s. distance to centre:%2.2f, radius:2.2f\n",m_pGameObject->GetRenderable()->GetType(),dist,m_fScaledRadius);
				//calc intersection point
				float dCentreToProjectedCentre =(vCentreProjOnLine-m_vPosition).GetLength();
				float dist=sqrt(m_fScaledRadius*m_fScaledRadius  - dCentreToProjectedCentre*dCentreToProjectedCentre);//pythagoras
				float distInt1=(vCentreProjOnLine-m_vPosition).GetLength()-dist;
				
				CVector3 vIntsec=m_vPosition + raydirection_ * distInt1;
				DPrint("collision between ray and ");
				DPrint(m_pGameObject->GetRenderable()->GetType());


				//return data about hit point
				if (hitPoint_)
				{
					hitPoint_->m_fX = vIntsec.m_fX;
					hitPoint_->m_fY = vIntsec.m_fY;
					hitPoint_->m_fZ = vIntsec.m_fZ;
				}
				return true;
			}
	 }
		return false;
 }

bool 
CSphereCollider::RespondToCollision()
 {
	 return !m_bIsTrigger; //if we are a trigger then we return false to mean no blocking behavior
 }