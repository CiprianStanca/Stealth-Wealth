#include "stdafx.h"
#include "SpaceGame.h"



CSpaceGame::CSpaceGame(void)
{
	Initialize();
}


CSpaceGame::~CSpaceGame(void)
{
}

void
CSpaceGame::Initialize()
{
 //load the textures
 
        CTextureLoader::getInstance().CreateTexture("assets/menu.bmp", MENU);
        CTextureLoader::getInstance().CreateTexture("assets/skybox.bmp", SKYBOX);
        CTextureLoader::getInstance().CreateTexture("assets/crate.bmp", CRATE);
        CTextureLoader::getInstance().CreateTexture("assets/fence.png", FENCE);
        CTextureLoader::getInstance().CreateTexture("assets/enemy.png", ENEMY);
		CTextureLoader::getInstance().CreateTexture("assets/grass.png", GRASS);
        //add some objects
 
        m_pRootNode= new CGameObject();
		m_pRootNode->GetTransform()->SetPosition(0,2,15);
		m_pRootNode->SetRenderable(new CCamera());
		m_pRootNode->SetBehavior(new FPSCameraBehavior());
 
		CGameObject * pCube = new CGameObject();
		pCube->GetTransform()->SetPosition(1.0f,0.0f,0.0f);
		pCube->GetTransform()->SetSize(50,50,50);
		pCube->SetRenderable(new CSkyBoxRenderable());
		pCube->SetMaterial(new CSkyBoxMaterial());
		pCube->GetMaterial()->SetTexture(SKYBOX);
		m_pRootNode->Attach(pCube);

		for (int i=0; i<5; i++)
		{
        CGameObject * pFencePanel=new CGameObject();
        pFencePanel->GetTransform()->SetPosition(2*(float)i,1,-5);
        pFencePanel->GetTransform()->SetSize(2,2,1);
        pFencePanel->SetRenderable(new CSprite());
        pFencePanel->SetMaterial(new CColourMaterial());
        pFencePanel->GetMaterial()->SetTexture(FENCE);
        m_pRootNode->Attach(pFencePanel);
		}
 

        CGameObject * pPlayer=new CGameObject();
		pPlayer->GetTransform()->SetPosition(0,0.5,0);
        pPlayer->GetMaterial()->SetTexture(CRATE);
		pPlayer->SetBehavior(new CSpinBehavior());
        m_pRootNode->Attach(pPlayer);
 
         CGameObject * pGround=new CGameObject();
		pGround->GetTransform()->SetSize(20,0.01,20);
        pGround->GetMaterial()->SetTexture(GRASS);
        m_pRootNode->Attach(pGround);

        CGameObject * pLMissile=new CGameObject();
        pLMissile->GetTransform()->SetPosition(-0.75,0,0);
        pLMissile->GetTransform()->SetSize(0.1,0.4,1);
        pLMissile->GetMaterial()->SetTexture(CRATE);
        m_pRootNode->Attach(pLMissile);
 
        //pPlayer->Attach(pLMissile);
 

 
        if (1)
 
        {
 
                for (int i=0; i< 12; i++)
 
                {
 
                        CGameObject * pRMissile=new CGameObject();
						pRMissile->GetTransform()->SetSize(0.1,0.1,1);
                        pRMissile->GetMaterial()->SetTexture(NO_TEXTURE);
                        CMissileBehavior * pMissBh = new CMissileBehavior();
                        pMissBh->SetAngleOffset((float)i* 6.284/12.0f );
                        pRMissile->SetBehavior(pMissBh);

                        pPlayer->Attach(pRMissile);

                }
 
        }
 
        CGameObject * pAlien=new CGameObject();
		pAlien->GetTransform()->SetPosition(-2,0.5,0);
        pAlien->SetBehavior(new CAgentBehavior());
		pAlien->GetMaterial()->SetTexture(CRATE);
		m_pRootNode->Attach(pAlien);
 
		CGameObject * pBillBoard=new CGameObject();
        pBillBoard->GetTransform()->SetPosition(2,0.5,0);
        pBillBoard->GetTransform()->SetSize(1,1,1);
        pBillBoard->SetRenderable(new CSprite());
        pBillBoard->SetMaterial(new CColourMaterial());
        pBillBoard->GetMaterial()->SetTexture(ENEMY);
		pBillBoard->SetBehavior(new CFaceCameraBehavior());
        m_pRootNode->Attach(pBillBoard);
}