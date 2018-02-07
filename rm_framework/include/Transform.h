#pragma once
#include "Vector.h"
#include "icomponent.h"

class CTransform: public IComponent
{
public:
	CTransform(void);
	CTransform(float x_, float y_, float z_);
	CTransform(CVector3 * pos_);
	~CTransform(void);

	void AddedToGameObject();
	void SetPosition(CVector3 pos); //absolute
	void SetPosition(float x_, float y_, float z_);
	void Translate(CVector3 offset_); //relative
	void Translate(CVector3 * pOffset_); //relative
	void Translate(float x_, float y_, float z_);
	void SetSize(CVector3 size); //absolute
	void SetSize(float w_, float h_, float d_);
	bool isOnTerrain();
	CVector3 GetPosition();
	CVector3 GetSize3();
	float GetYaw(){return m_fYaw;}
	void SetYaw(float yaw_){m_fYaw = yaw_;}
	float GetPitch(){return m_fPitch;}
	void SetPitch(float pitch_){m_fPitch = pitch_;}
	void IncrementYaw(float yaw_);
	void incrementPitch(float pitch_);
	bool m_bClampToTerrain;
	float m_fClampOffset;
	void ApplyClampToTerrain();
	void GetForwardDirection(CVector3 * pVec_);
	void GetRightDirection(CVector3 * pVec_);
	void GetUpDirection(CVector3 * pVec_);
	float GetTerrainHeight(float x_, float z_);
	float GetTerrainHeight(CVector3 pos);

private:
	float m_fX;
	float m_fY;
	float m_fZ;

	float m_fW;
	float m_fH;
	float m_fD;

	float m_fYaw;
	float m_fPitch;
	int m_iTextureID;
	

	

};
