#include "StdAfx.h"
#include "Transform.h"

CTransform::CTransform(void)
{
	m_fX=0.0f;
	m_fY=0.0f;
	m_fZ=0.0f;

	m_fW=1.0f;
	m_fH=1.0f;
	m_fD=1.0f;

	m_fYaw=0.0f;
	m_fPitch=0.0f;

	m_bClampToTerrain=false;
	m_fClampOffset=0.0f;

	
}

CTransform::CTransform(CVector3 * pos_)
{
	m_fX=pos_->m_fX;
	m_fY=pos_->m_fY;
	m_fZ=pos_->m_fZ;

	m_fW=1.0f;
	m_fH=1.0f;
	m_fD=1.0f;

	m_fYaw=0.0f;
	m_fPitch=0.0f;

	m_bClampToTerrain=false;
	m_fClampOffset=0.0f;

}


CTransform::CTransform(float x_, float y_, float z_)
{
	m_fX=x_;
	m_fY=y_;
	m_fZ=z_;

	m_fW=1.0f;
	m_fH=1.0f;
	m_fD=1.0f;

	m_fYaw=0.0f;
	m_fPitch=0.0f;

	m_bClampToTerrain=false;
	m_fClampOffset=0.0f;

}

CTransform::~CTransform(void)
{
}

void 
CTransform::SetPosition(CVector3 pos)
{
	m_fX=pos.m_fX;
	m_fY=pos.m_fY;
	m_fZ=pos.m_fZ;

}

void 
CTransform::SetPosition(float x_, float y_, float z_)
{
	m_fX=x_;
	m_fY=y_;
	m_fZ=z_;
}

void 
CTransform::SetSize(CVector3 scale)
{
	m_fW=scale.m_fX;
	m_fH=scale.m_fY;
	m_fD=scale.m_fZ;

}

void
CTransform::SetSize(float w_, float h_, float d_)
{
	m_fW=w_;
	m_fH=h_;
	m_fD=d_;
}

CVector3 
CTransform::GetPosition()
{
	CVector3 out;
 	out.m_fX=m_fX;
	out.m_fY=m_fY;
	out.m_fZ=m_fZ;
	return out;
}

CVector3 
CTransform::GetSize3()
{
	CVector3 out;
	out.m_fX=m_fW;
	out.m_fY=m_fH;
	out.m_fZ=m_fD;
	return out;
}


void
CTransform::Translate(CVector3 offset_)
{
	m_fX+=offset_.m_fX;
	m_fY+=offset_.m_fY;
	m_fZ+=offset_.m_fZ;
}

void
CTransform::Translate(CVector3 * pOffset_)
{
	if (pOffset_ !=0)
	{
		m_fX+=pOffset_->m_fX;
		m_fY+=pOffset_->m_fY;
		m_fZ+=pOffset_->m_fZ;
	}
}

void 
CTransform::Translate(float x_, float y_, float z_)
{
	m_fX+=x_;
	m_fY+=y_;
	m_fZ+=z_;
}

void	 
CTransform::IncrementYaw(float yaw_)
{
	m_fYaw +=yaw_;
	if (m_fYaw > 360) m_fYaw-=360;
}

	
void 
CTransform::incrementPitch(float pitch_)
{
	char txt[32];
	sprintf_s(txt, "PITCH OF FENCE IS  %f", pitch_);
	DPrint(txt);
	m_fPitch +=pitch_;
	if(m_fPitch > 360) m_fPitch -=360;
}

void
CTransform::ApplyClampToTerrain()
{
	if (!m_bClampToTerrain) return;
	

	float y = GetTerrainHeight(m_fX,m_fZ);
	if(m_fY < y + m_fClampOffset)m_fY =y + m_fClampOffset;
	
}

bool
CTransform::isOnTerrain()
{
	float y = GetTerrainHeight(m_fX, m_fZ);
	if (m_fY == y + m_fClampOffset) return true;
	return false;
}

float 
CTransform::GetTerrainHeight(float x_, float z_)
{
	//get Terrain
	CGameObject * obj =CTagManager::Instance()->GetObjectWithTag("Terrain");

	if (obj)
	{
		CTerrainRenderable * tern = (CTerrainRenderable *) obj->GetRenderable();
		float y = tern ->GetHeightAtPoint(x_,z_);
		return y;
	}

	return 0;
}

float 
CTransform::GetTerrainHeight(CVector3 pos)
{
	//get Terrain
	CGameObject * obj =CTagManager::Instance()->GetObjectWithTag("Terrain");

	if (obj)
	{
		CTerrainRenderable * tern = (CTerrainRenderable *) obj->GetRenderable();
		float y = tern ->GetHeightAtPoint(pos.m_fX, pos.m_fZ);
		return y;
	}

	return 0;
}



void
CTransform::AddedToGameObject()
{
//apply terrain clamping
	ApplyClampToTerrain();
}


void
CTransform::GetForwardDirection(CVector3 * pVec_)
{
	float cosYaw,sinYaw,sinPitch;
	cosYaw=(float)cos(DEG2RAD(m_fYaw));
	sinYaw=(float)sin(DEG2RAD(m_fYaw));
	sinPitch=(float)sin(DEG2RAD(m_fPitch));

	pVec_->m_fX =sinYaw;
	pVec_->m_fY=sinPitch;
	pVec_->m_fZ=-cosYaw;
	pVec_->Normalise();

	return;

}

void
CTransform::GetRightDirection(CVector3 * pVec_)
{
	float cosYaw,sinYaw,sinPitch;
	cosYaw=(float)cos(DEG2RAD(m_fYaw));
	sinYaw=(float)sin(DEG2RAD(m_fYaw));
	sinPitch=(float)sin(DEG2RAD(m_fPitch));

	pVec_->m_fX =cosYaw;
	pVec_->m_fY=sinPitch;
	pVec_->m_fZ=sinYaw;
	pVec_->Normalise();
}

void
CTransform::GetUpDirection(CVector3 * pVec_)
{
	CVector3 vfwd;
	GetForwardDirection(&vfwd);
	CVector3 vright;
	GetRightDirection(&vright);
	//calc fwd from cross product
	CVector3 vUp;
	vright.CrossProduct(&vfwd,&vUp);
	pVec_->m_fX = vUp.m_fX;
	pVec_->m_fY = vUp.m_fY;
	pVec_->m_fZ = vUp.m_fZ;
	
}