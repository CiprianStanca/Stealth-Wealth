#include "StdAfx.h"
#include "Game.h"

CGame::CGame(void)
{
	m_pRootNode=0;
	
}

CGame::~CGame(void)
{
}


void
CGame::SetState(eGameState state)
{
	m_eState = state;
}

void
CGame::AddObject(CGameObject * pGameObject_)
{
m_pRootNode->AddChild(pGameObject_);
}

float
CGame::PrepareForDoFrame()
{
	//refresh input
	CInput::Instance()->GetInput();
	float dt=CTimer::Instance()->Getdt();
	return dt;
}

void
CGame::DoFrame()
{
	float dt=PrepareForDoFrame();


	//update all objects
	if (m_pRootNode)
	{
	m_pRootNode->UpdateRecursive(dt);
	
	//render all objects
	m_pRootNode->RenderRecursive();

	//render transparent stuff last
	//CTransparentRenderingManager::RenderAllTransparentObjectsBackToFront();
	
	}
	CTransparentRenderingManager::RenderAllTransparentObjectsBackToFront();
}
