#include "stdafx.h"
#include "FPSCameraBehavior.h"
#include "Input.h"

FPSCameraBehavior::FPSCameraBehavior(void)
{

	//register self as Mouse Listener
	CMouseManager::Instance()->addMouseMovedListener(this);
}


FPSCameraBehavior::~FPSCameraBehavior(void)
{
}

void
FPSCameraBehavior::Update(float dt_)
{
	//record position before movement
	CVector3 oldpos = m_pTransform->GetPosition(); //store position prior to movement
	

	
	if (CInput::Instance()->GetIfKeyDown(DIK_D))
	{
		m_fStrafeSpeed=10;
	}
	else if (CInput::Instance()->GetIfKeyDown(DIK_A))
	{
		m_fStrafeSpeed=-10;
	
	}
	else m_fStrafeSpeed=0.0f;

	if (CInput::Instance()->GetIfKeyDown(DIK_W))
	{
		m_fSpeed=10;

		if (g_pGame->isClimbing == true)
		{
			m_fJumpSpeed = 10;
		}
		if (g_pGame->isClimbing == false)
		{
			m_fJumpSpeed = 0;
		}

		
	}
	else if (CInput::Instance()->GetIfKeyDown(DIK_S))
	{
		m_fSpeed=-10;
		
		
	}
	
	else m_fSpeed=0.0f;

	if (CInput::Instance()->GetIfKeyDown(DIK_F))
	{
		m_fJumpSpeed = 10;

	}
	else
	{
		m_fJumpSpeed = 0.0f;
	}
	
	if (CInput::Instance()->GetIfKeyDownEvent(DIK_B))
	{
		//toggle birds eye view
		CCamera * pCamera = (CCamera *)(m_pGameObject->GetRenderable());
		pCamera->ToggleBirdsEyeView();
	}
	if (CInput::Instance()->GetIfKeyDownEvent(DIK_N))
	{
		g_pGame->SetState(eGameStateMenu);
	}

	float cosYaw,sinYaw,sinPitch;
	cosYaw=(float)cos(DEG2RAD(m_pTransform->GetYaw()));
	sinYaw=(float)sin(DEG2RAD(m_pTransform->GetYaw()));
	//sinPitch=(float)sin(DEG2RAD(m_pTransform->GetPitch()));

	//update position based on speed
	float dx=sinYaw*m_fSpeed*dt_ +cosYaw*m_fStrafeSpeed*dt_;
	float dz=-cosYaw*m_fSpeed*dt_ + sinYaw*m_fStrafeSpeed*dt_;
	float dy = m_fJumpSpeed*dt_;
	m_pTransform->Translate(dx,dy,dz);
	m_pTransform->ApplyClampToTerrain();

	//update position of collider
	ICollider * col =m_pGameObject->GetCollider();
	CVector3 pos=m_pTransform->GetPosition();
	if (col) col->SetPosition(&pos);

	//check for collision
	ICollider * hit = new CSphereCollider();
	ICollider * myCollider=m_pGameObject->GetCollider();
	bool collision = CCollisionManager::Instance()->GetCollision(myCollider,hit);
	if (collision && hit->RespondToCollision())
	{
		//for debug purposes, printout what we bumped into
		CGameObject * thingWeHit = hit->GetGameObject();
		IRenderable * renWeHit = thingWeHit->GetRenderable();
		char txt[32];
		sprintf(txt,"camera hit a %s %d",renWeHit->GetType(), hit->RespondToCollision());
		DPrint(txt);
		
		//revert to old pos and old lookat
		m_pTransform->SetPosition(oldpos); //restore back to old saved position

		if (g_pGame->isClimbing == true) 
		{
			// if climbing on ladder do this
			dx = 0;
			dz = 0;

			dy = 10 * dt_;
			g_pGame->isClimbing = false;
		}
		else
		{
			// if not climbing on ladder do this
			// allows the player to slide across flat surfaces
			m_pTransform->Translate(dx, 0, 0); //moves only in the x direction
			m_pTransform->ApplyClampToTerrain();
			pos = m_pTransform->GetPosition();
			if (col) col->SetPosition(&pos);
			bool xBlocked = CCollisionManager::Instance()->GetCollision(myCollider, hit);
			m_pTransform->SetPosition(oldpos);

			m_pTransform->Translate(0, 0, dz); //moves only in the z direction
			m_pTransform->ApplyClampToTerrain();
			pos = m_pTransform->GetPosition();
			if (col) col->SetPosition(&pos);
			bool zBlocked = CCollisionManager::Instance()->GetCollision(myCollider, hit);
			m_pTransform->SetPosition(oldpos);

			m_pTransform->Translate(0, dy, 0); //moves only in the y direction
			m_pTransform->ApplyClampToTerrain();
			pos = m_pTransform->GetPosition();
			if (col) col->SetPosition(&pos);
			bool yBlocked = CCollisionManager::Instance()->GetCollision(myCollider, hit);
			m_pTransform->SetPosition(oldpos);

			if (xBlocked)
			{
				dx = 0;
			}

			if (zBlocked)
			{
				dz = 0;
			}

			if (yBlocked)
			{
				dy = 0;
			}
		}
		m_pTransform->Translate(dx, dy, dz);
		m_pTransform->ApplyClampToTerrain();
	}
}


void 
FPSCameraBehavior::MouseMoved(float x_, float y_)
{
	m_pTransform->IncrementYaw(x_ *15);
	m_pTransform->incrementPitch(y_ *-15);
}