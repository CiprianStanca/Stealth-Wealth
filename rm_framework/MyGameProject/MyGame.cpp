#include "stdafx.h"
#include "MyGame.h"
#include "FireMissileBehavior.h"
#include "FireRayBehavior.h"

MyGame::MyGame(void)
{
	LoadMenu();
	m_eState = eGameStateMenu;

}


MyGame::~MyGame(void)
{
}

void
MyGame::LoadTextures()
{
	//load the textures

	CTextureLoader::getInstance().CreateTexture("assets/skybox.bmp", SKYBOX);
	CTextureLoader::getInstance().CreateTexture("assets/crate.bmp", CRATE);
	CTextureLoader::getInstance().CreateTexture("assets/museumwall.jpg", FENCE);
	CTextureLoader::getInstance().CreateTexture("assets/enemy.png", ENEMY);
	CTextureLoader::getInstance().CreateTexture("assets/hut.bmp", HUT);
	CTextureLoader::getInstance().CreateTexture("assets/grass.jpg", GRASS);
	CTextureLoader::getInstance().CreateTexture("assets/explosion.bmp", EXPLOSION);
	CTextureLoader::getInstance().CreateTexture("assets/artifactgui.png", GUI);
	CTextureLoader::getInstance().CreateTexture("assets/fpsgun.png", GUN);
	CTextureLoader::getInstance().CreateTexture("assets/stonewall.jpg", OUTWALL);
	CTextureLoader::getInstance().CreateTexture("assets/floor.jpg", FLOOR);
	CTextureLoader::getInstance().CreateTexture("assets/tree.png", TREE);
	CTextureLoader::getInstance().CreateTexture("assets/diamond.png", DIAMOND);
	CTextureLoader::getInstance().CreateTexture("assets/artifact.png", ARTIFACT);
	CTextureLoader::getInstance().CreateTexture("assets/number0.png", ZERO);
	CTextureLoader::getInstance().CreateTexture("assets/number1.png", ONE);
	CTextureLoader::getInstance().CreateTexture("assets/number2.png", TWO);
	CTextureLoader::getInstance().CreateTexture("assets/benchuv.png", BENCH);
	CTextureLoader::getInstance().CreateTexture("assets/poleuv.png", POLE);
	CTextureLoader::getInstance().CreateTexture("assets/binuv.png", BIN);
	CTextureLoader::getInstance().CreateTexture("assets/secondfloor.png", METAL);
	CTextureLoader::getInstance().CreateTexture("assets/ladder.png", LADDER);
	CTextureLoader::getInstance().CreateTexture("assets/egyptianhawk.png", EGYPT);
	CTextureLoader::getInstance().CreateTexture("assets/scarab.png", SCARAB);
	CTextureLoader::getInstance().CreateTexture("assets/congrat.png", GAMEWON);
	CTextureLoader::getInstance().CreateTexture("assets/youloss.png", GAMELOST);

}

void
MyGame::LoadMenu()
{


	CTextureLoader::getInstance().CreateTexture("assets/bg.png", MENU);
	CTextureLoader::getInstance().CreateTexture("assets/playnormal.png", PLAYBUTTON);
	CTextureLoader::getInstance().CreateTexture("assets/playhigh.png", PLAYBUTTONHI);
	CTextureLoader::getInstance().CreateTexture("assets/playclicked.png", PLAYBUTTONCLICK);
	CTextureLoader::getInstance().CreateTexture("assets/insnormal.png", SETTINGSBUTTON);
	CTextureLoader::getInstance().CreateTexture("assets/inshigh.png", SETTINGSBUTTONHI);
	CTextureLoader::getInstance().CreateTexture("assets/insclicked.png", SETTINGSBUTTONCLICK);
	CTextureLoader::getInstance().CreateTexture("assets/quitnormal.png", SCOREBUTTON);
	CTextureLoader::getInstance().CreateTexture("assets/quithigh.png", SCOREBUTTONHI);
	CTextureLoader::getInstance().CreateTexture("assets/quitclicked.png", SCOREBUTTONCLICK);
	CTextureLoader::getInstance().CreateTexture("assets/exitframe.png", EXITWINDOW);


	pMenu = new CGameObject();
	pMenu->SetRenderable(new CGUITextureRenderable());
	pMenu->SetMaterial(new CColourMaterial());
	pMenu->GetMaterial()->SetTexture(MENU);

	pPlayButton = new CGameObject();
	pPlayButton->SetRenderable(new CGUITextureRenderable());
	pPlayButton->SetMaterial(new CColourMaterial());
	pPlayButton->GetMaterial()->SetTexture(PLAYBUTTON);
	pPlayButton->GetTransform()->SetSize(0.1, 0.1, 1);
	pPlayButton->GetTransform()->SetPosition(-0.3, 0.2, 0.01);
	pPlayButton->AddBehavior(new CGUIPlayButtonBehavior());

	pOptionsButton = new CGameObject();
	pOptionsButton->SetRenderable(new CGUITextureRenderable());
	pOptionsButton->SetMaterial(new CColourMaterial());
	pOptionsButton->GetMaterial()->SetTexture(SETTINGSBUTTON);
	pOptionsButton->GetTransform()->SetSize(0.3, 0.1, 1);
	pOptionsButton->GetTransform()->SetPosition(-0.2, 0.05, 0.01);
	pOptionsButton->AddBehavior(new CGUIInstructionButtonBehavior());

	pScoreButton = new CGameObject();
	pScoreButton->SetRenderable(new CGUITextureRenderable());
	pScoreButton->SetMaterial(new CColourMaterial());
	pScoreButton->GetMaterial()->SetTexture(SCOREBUTTON);
	pScoreButton->GetTransform()->SetSize(0.1, 0.1, 1);
	pScoreButton->GetTransform()->SetPosition(-0.30, -0.1, 0.01);
	//pScoreButton->AddBehavior(new CGUIButtonBehavior());
	pScoreButton->AddBehavior(new CGUIExitButtonBehavior());
}

void
MyGame::LoadInstructions()
{


	CTextureLoader::getInstance().CreateTexture("assets/instructions.png", INSTRUCTIONS);

	pInstructions = new CGameObject();
	pInstructions->SetRenderable(new CGUITextureRenderable());
	pInstructions->SetMaterial(new CColourMaterial());
	pInstructions->GetMaterial()->SetTexture(INSTRUCTIONS);

}

void
MyGame::LoadWon()
{


	//CTextureLoader::getInstance().CreateTexture("assets/instructions.png", INSTRUCTIONS);

	pWon = new CGameObject();
	pWon->SetRenderable(new CGUITextureRenderable());
	pWon->SetMaterial(new CColourMaterial());
	pWon->GetMaterial()->SetTexture(GAMEWON);

}

void
MyGame::LoadLost()
{


	//CTextureLoader::getInstance().CreateTexture("assets/instructions.png", INSTRUCTIONS);

	pLost = new CGameObject();
	pLost->SetRenderable(new CGUITextureRenderable());
	pLost->SetMaterial(new CColourMaterial());
	pLost->GetMaterial()->SetTexture(GAMELOST);

}

void
MyGame::LoadWorld()
{
	//add some objects

	m_pRootNode = new CGameObject();
	m_pRootNode->GetTransform()->SetPosition(0, 1, 5);
	m_pRootNode->SetRenderable(new CCamera());
	m_pRootNode->AddBehavior(new FPSCameraBehavior());
	m_pRootNode->GenerateColliderForRenderable();
	m_pRootNode->AddBehavior(new CFallUnderGravityBehavior());
	m_pRootNode->AddBehavior(new CFireMissileBehavior());
	//m_pRootNode->AddBehavior(new CFireRayBehavior());


	/*CGameObject * pTree = new CGameObject();
	pTree->GetTransform()->SetSize(2, 10, 1);
	pTree->SetRenderable(new CSprite());
	pTree->SetMaterial(new CColourMaterial());
	pTree->GetTransform()->SetPosition(0, 1, 5);
	pTree->SetMaterial(new LitMaterial());
	pTree->AddBehavior(new CFaceCameraBehavior());
	pTree->GetMaterial()->EnableTransparentDepthSort();
	pTree->GetMaterial()->SetTexture(TREE);
	m_pRootNode->AddChild(pTree);*/

	{
		// skybox section + world boundaries colliders
		CGameObject * pSkyBox = new CGameObject();
		pSkyBox->GetTransform()->SetPosition(0.0f, 0.0f, 0.0f);
		pSkyBox->GetTransform()->SetSize(50, 50, 50);
		pSkyBox->SetMaterial(new CSkyBoxMaterial());
		pSkyBox->GetMaterial()->SetTexture(SKYBOX);
		pSkyBox->SetRenderable(new CSkyBoxRenderable());
		pSkyBox->GenerateColliderForRenderable(ICollider::eColliderTypeCube);
		m_pRootNode->AddChild(pSkyBox);

		CGameObject * pSkyBoxPanel1 = new CGameObject();
		pSkyBoxPanel1->GetTransform()->SetPosition(0.0f, 25.0f, -25.1f);
		pSkyBoxPanel1->GetTransform()->SetSize(50, 50, 0);
		pSkyBoxPanel1->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pSkyBoxPanel1);

		CGameObject * pSkyBoxPanel2 = new CGameObject();
		pSkyBoxPanel2->GetTransform()->SetPosition(0.0f, 25.0f, 25.1f);
		pSkyBoxPanel2->GetTransform()->SetSize(50, 50, 0);
		pSkyBoxPanel2->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pSkyBoxPanel2);

		CGameObject * pSkyBoxPanel3 = new CGameObject();
		pSkyBoxPanel3->GetTransform()->SetPosition(25.1f, 25.0f, 0.0f);
		pSkyBoxPanel3->GetTransform()->SetSize(0, 50, 50);
		pSkyBoxPanel3->GetTransform()->IncrementYaw(180);
		pSkyBoxPanel3->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pSkyBoxPanel3);

		CGameObject * pSkyBoxPanel4 = new CGameObject();
		pSkyBoxPanel4->GetTransform()->SetPosition(-25.1f, 25.0f, 0.0f);
		pSkyBoxPanel4->GetTransform()->SetSize(0, 50, 50);
		pSkyBoxPanel4->GetTransform()->IncrementYaw(180);
		pSkyBoxPanel4->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pSkyBoxPanel4);
	}
	// skyBox + boundaries section end
	for (int i = 0; i < 8; i++)//trees
	{
		CGameObject * pWalker = new CGameObject();
		pWalker->GetTransform()->SetSize(2, 4, 2);
		pWalker->GetTransform()->SetPosition(16 - 4 * (float)i, 2, -16);
		pWalker->SetRenderable(new CSprite());
		pWalker->SetMaterial(new CColourMaterial());
		pWalker->GetMaterial()->EnableTransparentDepthSort();
		pWalker->GetMaterial()->SetTexture(TREE);
		pWalker->AddBehavior(new CFaceCameraBehavior());
		pWalker->GetTransform()->m_bClampToTerrain = true;
		pWalker->GetTransform()->m_fClampOffset = 1.0f;
		pWalker->GetTransform()->ApplyClampToTerrain();
		pWalker->GenerateColliderForRenderable();
		//pWalker->SetCollisionResponder(new CDestroyedByMissileCollisionResponder());
		//pWalker->AddBehavior(new CCollideDeleteBehavior());
		m_pRootNode->AddChild(pWalker);

	}


	//Artifacts of the game
	CGameObject * pArtifact = new CGameObject();
	pArtifact->GetTransform()->SetSize(1, 1, 1);
	pArtifact->GetTransform()->SetPosition(20, -2.5, -5);
	pArtifact->SetRenderable(new CSprite());
	pArtifact->SetMaterial(new CColourMaterial());
	pArtifact->GetMaterial()->EnableTransparentDepthSort();
	pArtifact->GetMaterial()->SetTexture(DIAMOND);
	pArtifact->AddBehavior(new CFaceCameraBehavior());
	pArtifact->GetTransform()->m_bClampToTerrain = true;
	pArtifact->GetTransform()->m_fClampOffset = 1.0f;
	pArtifact->GetTransform()->ApplyClampToTerrain();
	pArtifact->GenerateColliderForRenderable(ICollider::eColliderTypeSphere);
	pArtifact->AddBehavior(new CCollideDeleteBehavior()); //adds the collision deletion behavior to the artifact.
	pArtifact->GetCollider()->SetTrigger();
	m_pRootNode->AddChild(pArtifact);

	//Artifacts of the game


	//Artifacts of the game
	CGameObject * pArtifact4 = new CGameObject();
	pArtifact4->GetTransform()->SetSize(1, 1, 1);
	pArtifact4->GetTransform()->SetPosition(-1, 4, 4);
	pArtifact4->SetRenderable(new CSprite());
	pArtifact4->SetMaterial(new CColourMaterial());
	pArtifact4->GetMaterial()->EnableTransparentDepthSort();
	pArtifact4->GetMaterial()->SetTexture(EGYPT);
	pArtifact4->AddBehavior(new CFaceCameraBehavior());
	pArtifact4->GetTransform()->m_bClampToTerrain = true;
	pArtifact4->GetTransform()->m_fClampOffset = 1.0f;
	pArtifact4->GetTransform()->ApplyClampToTerrain();
	pArtifact4->GenerateColliderForRenderable(ICollider::eColliderTypeSphere);
	pArtifact4->AddBehavior(new CCollideDeleteBehavior()); //adds the collision deletion behavior to the artifact.
	pArtifact4->GetCollider()->SetTrigger();
	m_pRootNode->AddChild(pArtifact4);

	CGameObject * pArtifact2 = new CGameObject();
	pArtifact2->GetTransform()->SetSize(1, 1, 1);
	pArtifact2->GetTransform()->SetPosition(0, -2.5, -5);
	pArtifact2->SetRenderable(new CSprite());
	pArtifact2->SetMaterial(new CColourMaterial());
	pArtifact2->GetMaterial()->EnableTransparentDepthSort();
	pArtifact2->GetMaterial()->SetTexture(ARTIFACT);
	pArtifact2->AddBehavior(new CFaceCameraBehavior());
	pArtifact2->GetTransform()->m_bClampToTerrain = true;
	pArtifact2->GetTransform()->m_fClampOffset = 1.0f;
	pArtifact2->GetTransform()->ApplyClampToTerrain();
	pArtifact2->GenerateColliderForRenderable(ICollider::eColliderTypeSphere);
	pArtifact2->AddBehavior(new CCollideDeleteBehavior()); //adds the collision deletion behavior to the artifact.
	pArtifact2->GetCollider()->SetTrigger();
	m_pRootNode->AddChild(pArtifact2);

	CGameObject * pBench = new CGameObject();
	pBench->GetTransform()->SetPosition(-1, -5, 1);
	pBench->SetMaterial(new LitMaterial());
	pBench->SetRenderable(new CMeshRenderable("assets/bench.dat"));
	pBench->GetTransform()->SetSize(0.5, 0.5, 0.5);
	pBench->GetMaterial()->SetTexture(BENCH);
	pBench->GetTransform()->m_bClampToTerrain = true;
	pBench->GetTransform()->m_fClampOffset = 0.3f;
	pBench->GetTransform()->ApplyClampToTerrain();
	pBench->GenerateColliderForRenderable(ICollider::eColliderTypeCube);
	pBench->SetCollisionResponder(new CDestroyedByMissileCollisionResponder());
	m_pRootNode->AddChild(pBench);


	CGameObject * pBench2 = new CGameObject();
	pBench2->GetTransform()->SetPosition(15, -5, 1);
	pBench2->SetMaterial(new LitMaterial());
	pBench2->SetRenderable(new CMeshRenderable("assets/bench.dat"));
	pBench2->GetTransform()->SetSize(0.5, 0.5, 0.5);
	pBench2->GetMaterial()->SetTexture(BENCH);
	pBench2->GetTransform()->m_bClampToTerrain = true;
	pBench2->GetTransform()->m_fClampOffset = 0.3f;
	pBench2->GetTransform()->ApplyClampToTerrain();
	pBench2->GenerateColliderForRenderable(ICollider::eColliderTypeCube);
	pBench2->SetCollisionResponder(new CDestroyedByMissileCollisionResponder());
	m_pRootNode->AddChild(pBench2);



	for (int i = 0; i < 12; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		CMapStorage::Instance()->AddPoint(-3, 23 - 2 * (float)i, 1, 0);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-3, 0.11, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 12; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-1, 23 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-1, 0.11, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 12; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(1, 23 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(1, 0.11, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	CGameObject * pTerrain = new CGameObject();
	pTerrain->GetTransform()->SetSize(50, 0.1, 50);
	pTerrain->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
	pTerrain->SetMaterial(new LitMaterial());
	pTerrain->GetMaterial()->SetTexture(GRASS);
	m_pRootNode->AddChild(pTerrain);

	for (int i = 0; i<3; i++)//first left wall 
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-4, 23 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(-4, 1, 23 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<3; i++)//first left wall 
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-4, 23 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(-90);
		pFencePanel->GetTransform()->SetPosition(-4, 1, 23 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<7; i++)//second left wall
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-4, 13 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(-4, 1, 13 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);

	}

	for (int i = 0; i<3; i++)//far end wall
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(1 - 2 * (float)i, 0, 1, 0);
		//pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(1 - 2 * (float)i, 1, 0);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);

	}


	for (int i = 0; i<3; i++)//far end wall
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(1 - 2 * (float)i, -0.001, 1, 180);
		pFencePanel->GetTransform()->IncrementYaw(180);
		pFencePanel->GetTransform()->SetPosition(1 - 2 * (float)i, 1, -0.001);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(OUTWALL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);

	}

	for (int i = 0; i<2; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-4.01, 13 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(-90);
		pFencePanel->GetTransform()->SetPosition(-4.01, 1, 13 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}
	for (int i = 0; i<5; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-4.01, 9 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(-90);
		pFencePanel->GetTransform()->SetPosition(-4.01, 1, 9 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(OUTWALL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<5; i++)//first right wall
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(2, 23 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->SetPosition(2, 1, 23 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->GetTransform()->IncrementYaw(-90);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);

		CGameObject * pFencePanelBACK = new CGameObject();
		CMapStorage::Instance()->AddPoint(-2.01, 23 - 2 * (float)i, 1, 90);
		pFencePanelBACK->GetTransform()->IncrementYaw(90);
		pFencePanelBACK->GetTransform()->SetPosition(2.01, 1, 23 - 2 * (float)i);
		pFencePanelBACK->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanelBACK->SetRenderable(new CSprite());
		pFencePanelBACK->SetMaterial(new CColourMaterial());
		pFencePanelBACK->GetMaterial()->SetTexture(FENCE);
		pFencePanelBACK->GetTransform()->m_bClampToTerrain = true;
		pFencePanelBACK->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanelBACK->GetTransform()->ApplyClampToTerrain();
		pFencePanelBACK->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanelBACK);
	}


	for (int i = 0; i<5; i++)//second right wall
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(2, 9 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(-90);
		pFencePanel->GetTransform()->SetPosition(2, 1, 9 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);

		for (int i = 0; i<5; i++)
		{
			CGameObject * pFencePanel = new CGameObject();
			CMapStorage::Instance()->AddPoint(-2.01, 9 - 2 * (float)i, 1, 90);
			pFencePanel->GetTransform()->IncrementYaw(90);
			pFencePanel->GetTransform()->SetPosition(2.01, 1, 9 - 2 * (float)i);
			pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
			pFencePanel->SetRenderable(new CSprite());
			pFencePanel->SetMaterial(new CColourMaterial());
			pFencePanel->GetMaterial()->SetTexture(FENCE);
			pFencePanel->GetTransform()->m_bClampToTerrain = true;
			pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
			pFencePanel->GetTransform()->ApplyClampToTerrain();
			pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
			m_pRootNode->AddChild(pFencePanel);
		}
	}
	//start of left room
	for (int i = 0; i<2; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-5 - 2 * (float)i, 10, 1, 0);
		//pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(-5 - 2 * (float)i, 1, 10);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);

		for (int i = 0; i<2; i++)
		{
			CGameObject * pFencePanel = new CGameObject();
			CMapStorage::Instance()->AddPoint(-5.01 - 2 * (float)i, 9.99, 1, 0);
			pFencePanel->GetTransform()->IncrementYaw(-180);
			pFencePanel->GetTransform()->SetPosition(-5.01 - 2 * (float)i, 1, 9.99);
			pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
			pFencePanel->SetRenderable(new CSprite());
			pFencePanel->SetMaterial(new CColourMaterial());
			pFencePanel->GetMaterial()->SetTexture(OUTWALL);
			pFencePanel->GetTransform()->m_bClampToTerrain = true;
			pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
			pFencePanel->GetTransform()->ApplyClampToTerrain();
			pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
			m_pRootNode->AddChild(pFencePanel);
		}
	}

	for (int i = 0; i<1; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		//pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(-13 - 2 * (float)i, 1, 10);
		CMapStorage::Instance()->AddPoint(-13 - 2 * (float)i, 10, 1, 0);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);

		for (int i = 0; i<1; i++)
		{
			CGameObject * pFencePanel = new CGameObject();
			CMapStorage::Instance()->AddPoint(-13 - 2 * (float)i, 9.99, 1, 0);
			pFencePanel->GetTransform()->IncrementYaw(-180);
			pFencePanel->GetTransform()->SetPosition(-13 - 2 * (float)i, 1, 9.99);
			pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
			pFencePanel->SetRenderable(new CSprite());
			pFencePanel->SetMaterial(new CColourMaterial());
			pFencePanel->GetMaterial()->SetTexture(OUTWALL);
			pFencePanel->GetTransform()->m_bClampToTerrain = true;
			pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
			pFencePanel->GetTransform()->ApplyClampToTerrain();
			pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
			m_pRootNode->AddChild(pFencePanel);
		}
	}

	for (int i = 0; i<1; i++)//ladder
	{
		CGameObject * pFencePanel = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-13 - 2 * (float)i, 9.99, 1, 0);
		pFencePanel->GetTransform()->IncrementYaw(-180);
		pFencePanel->GetTransform()->SetPosition(-13 - 2 * (float)i, 1, 9.8);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(LADDER);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypeLadder);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i < 7; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-5, 23 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-5, 0.11, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 7; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-7, 23 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-7, 0.11, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 7; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-9, 23 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-9, 0.11, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 7; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-11, 23 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-11, 0.11, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 7; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-13, 23 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-13, 0.11, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i<5; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-5 - 2 * (float)i, 24, 1, 0);
		pFencePanel->GetTransform()->IncrementYaw(-180);
		pFencePanel->GetTransform()->SetPosition(-5 - 2 * (float)i, 1, 24);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}
	for (int i = 0; i<3; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-14, 24 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(-14, 1, 24 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);

	}

	for (int i = 0; i<3; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-14, 15 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(-14, 1, 15 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);

		for (int i = 0; i<3; i++)
		{
			CGameObject * pFencePanel = new CGameObject();
			CMapStorage::Instance()->AddPoint(-14, 15 - 2 * (float)i, 1, 90);
			pFencePanel->GetTransform()->IncrementYaw(-90);
			pFencePanel->GetTransform()->SetPosition(-14, 1, 15 - 2 * (float)i);
			pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
			pFencePanel->SetRenderable(new CSprite());
			pFencePanel->SetMaterial(new CColourMaterial());
			pFencePanel->GetMaterial()->SetTexture(FENCE);
			pFencePanel->GetTransform()->m_bClampToTerrain = true;
			pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
			pFencePanel->GetTransform()->ApplyClampToTerrain();
			pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
			m_pRootNode->AddChild(pFencePanel);
		}
	}

	//start left corridor

	for (int i = 0; i < 19; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-15, 18 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-15, 0.11, 18 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 20; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-17, 18 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-17, 0.11, 18 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i<20; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-18, 18 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(-18, 1, 18 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<5; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-13.9, 9 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(-13.9, 1, 9 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(OUTWALL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<5; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-14, 9 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(-90);
		pFencePanel->GetTransform()->SetPosition(-14, 1, 9 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<6; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-13.9, -6 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(-13.9, 1, -6 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(OUTWALL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}
	for (int i = 0; i<6; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-14, 6 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(-90);
		pFencePanel->GetTransform()->SetPosition(-14, 1, -6 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<2; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-15 - 2 * (float)i, 19, 1, 0);
		pFencePanel->GetTransform()->IncrementYaw(-180);
		pFencePanel->GetTransform()->SetPosition(-15 - 2 * (float)i, 1, 19);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}
	for (int i = 0; i<20; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(21 - 2 * (float)i, -21, 1, 0);
		//pFencePanel->GetTransform()->IncrementYaw(180);
		pFencePanel->GetTransform()->SetPosition(21 - 2 * (float)i, 1, -21);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<16; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(17 - 2 * (float)i, -17, 1, 0);
		pFencePanel->GetTransform()->IncrementYaw(-180);
		pFencePanel->GetTransform()->SetPosition(17 - 2 * (float)i, 1, -17);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}
	for (int i = 0; i<16; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(17 - 2 * (float)i, -16.9, 1, 0);
		//pFencePanel->GetTransform()->IncrementYaw(-180);
		pFencePanel->GetTransform()->SetPosition(17 - 2 * (float)i, 1, -16.9);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(OUTWALL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i < 16; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17 - 2 * (float)i, -18, 1, 0);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(17 - 2 * (float)i, 0.11, -18);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}
	for (int i = 0; i < 18; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17 - 2 * (float)i, -20, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(17 - 2 * (float)i, 0.11, -20);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	//start of right room 

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(3, 23 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(3, 0.11, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(5, 23 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(5, 0.11, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(7, 23 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(7, 0.11, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(9, 23 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(9, 0.11, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(11, 23 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(11, 0.11, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(13, 23 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(13, 0.11, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(15, 23 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(15, 0.11, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17, 23 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(17, 0.11, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i<8; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(17 - 2 * (float)i, 24, 1, 0);
		pFencePanel->GetTransform()->IncrementYaw(-180);
		pFencePanel->GetTransform()->SetPosition(17 - 2 * (float)i, 1, 24);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<8; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(17 - 2 * (float)i, 2, 1, 0);
		//pFencePanel->GetTransform()->IncrementYaw(180);
		pFencePanel->GetTransform()->SetPosition(17 - 2 * (float)i, 1, 2);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<8; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(17 - 2 * (float)i, 24, 1.9, 0);
		pFencePanel->GetTransform()->IncrementYaw(180);
		pFencePanel->GetTransform()->SetPosition(17 - 2 * (float)i, 1, 1.9);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(OUTWALL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<5; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(18, 23 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(-90);
		pFencePanel->GetTransform()->SetPosition(18, 1, 23 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<4; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(18, 9 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(-90);
		pFencePanel->GetTransform()->SetPosition(18, 1, 9 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}


	//start of right corridor

	for (int i = 0; i<4; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(18.01, 9 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(18.01, 1, 9 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<2; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(21 - 2 * (float)i, 14, 1, 0);
		pFencePanel->GetTransform()->IncrementYaw(180);
		pFencePanel->GetTransform()->SetPosition(21 - 2 * (float)i, 1, 14);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i < 18; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(19, 13 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(19, 0.11, 13 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}
	for (int i = 0; i < 18; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(21, 13 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(21, 0.11, 13 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i<18; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(22, 13 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(-90);
		pFencePanel->GetTransform()->SetPosition(22, 1, 13 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<3; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(18, -12 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(18, 1, -12 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<3; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(17.9, -12 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(-90);
		pFencePanel->GetTransform()->SetPosition(17.9, 1, -12 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(OUTWALL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<4; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(18.01, 1 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(18.01, 1, 1 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<4; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(17.9, 1 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(-90);
		pFencePanel->GetTransform()->SetPosition(17.9, 1, 1 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(OUTWALL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	//start of second floor


	for (int i = 0; i < 16; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17 - 2 * (float)i, -18, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(17 - 2 * (float)i, 3, -18);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 16; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17 - 2 * (float)i, -20, 2);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(17 - 2 * (float)i, 3, -20);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 20; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-17, 18 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-17, 3, 18 - 2 * (float)i);
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}


	for (int i = 0; i < 20; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-15, 18 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-15, 3, 18 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 18; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(19, 14 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(19, 3, 14 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}


	for (int i = 0; i < 18; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-21, 14 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(21, 3, 14 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(17, 3, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(15, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(15, 3, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(13, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(13, 3, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(11, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(11, 3, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(9, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(9, 3, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(7, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(7, 3, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(5, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(5, 3, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(3, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(3, 3, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 7; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-5, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-5, 3, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 7; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-7, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-7, 3, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 7; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-9, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-9, 3, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 7; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-11, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-11, 3, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 7; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-13, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-13, 3, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	//second floor fences

	for (int i = 0; i<16; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(17 - 2 * (float)i, -17, 2, 0);
		pFencePanel->GetTransform()->IncrementYaw(-180);
		pFencePanel->GetTransform()->SetPosition(17 - 2 * (float)i, 3.7, -17);
		pFencePanel->GetTransform()->SetSize(2, 1.5, 0.5);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(METAL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<16; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(17 - 2 * (float)i, -17, 2, 0);
		//pFencePanel->GetTransform()->IncrementYaw(-180);
		pFencePanel->GetTransform()->SetPosition(17 - 2 * (float)i, 3.7, -17);
		pFencePanel->GetTransform()->SetSize(2, 1.5, 0.5);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(METAL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<20; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(21 - 2 * (float)i, -21, 2, 0);
		pFencePanel->GetTransform()->IncrementYaw(-180);
		pFencePanel->GetTransform()->SetPosition(21 - 2 * (float)i, 3.7, -21);
		pFencePanel->GetTransform()->SetSize(2, 1.5, 0.5);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(METAL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<20; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(21 - 2 * (float)i, -21, 2, 0);
		//pFencePanel->GetTransform()->IncrementYaw(-180);
		pFencePanel->GetTransform()->SetPosition(21 - 2 * (float)i, 3.7, -21);
		pFencePanel->GetTransform()->SetSize(2, 1.5, 0.5);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(METAL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<18; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(22, 14 - 2 * (float)i, 2, 90);
		pFencePanel->GetTransform()->IncrementYaw(-90);
		pFencePanel->GetTransform()->SetPosition(22, 3.7, 14 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 1.5, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(METAL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<10; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(18, 2 - 2 * (float)i, 2, 90);
		pFencePanel->GetTransform()->IncrementYaw(-90);
		pFencePanel->GetTransform()->SetPosition(18, 3.7, 2 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 1.5, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(METAL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<10; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(18, 2 - 2 * (float)i, 2, 90);
		pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(18, 3.7, 2 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 1.5, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(METAL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<20; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-18, 18 - 2 * (float)i, 2, 90);
		pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(-18, 3.7, 18 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 1.5, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(METAL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<14; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-14, 10 - 2 * (float)i, 2, 90);
		pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(-14, 3.7, 10 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 1.5, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(METAL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<14; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-14, 10 - 2 * (float)i, 2, 90);
		pFencePanel->GetTransform()->IncrementYaw(-90);
		pFencePanel->GetTransform()->SetPosition(-14, 3.7, 10 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 1.5, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(METAL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<2; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-15 - 2 * (float)i, 19, 2, 0);
		pFencePanel->GetTransform()->IncrementYaw(-180);
		pFencePanel->GetTransform()->SetPosition(-15 - 2 * (float)i, 3.7, 19);
		pFencePanel->GetTransform()->SetSize(2, 1.5, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(METAL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<2; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(21 - 2 * (float)i, 15, 2, 0);
		pFencePanel->GetTransform()->IncrementYaw(180);
		pFencePanel->GetTransform()->SetPosition(21 - 2 * (float)i, 3.7, 15);
		pFencePanel->GetTransform()->SetSize(2, 1.5, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(METAL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<5; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(18, 24 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(-90);
		pFencePanel->GetTransform()->SetPosition(18, 4.8, 24 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<5; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(18, 24 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(18.01, 4.8, 24 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<8; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(17 - 2 * (float)i, 2, 1, 0);
		//pFencePanel->GetTransform()->IncrementYaw(180);
		pFencePanel->GetTransform()->SetPosition(17 - 2 * (float)i, 4.8, 2);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<8; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(17 - 2 * (float)i, 2, 1, 0);
		pFencePanel->GetTransform()->IncrementYaw(180);
		pFencePanel->GetTransform()->SetPosition(17 - 2 * (float)i, 4.8, 2);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(OUTWALL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<16; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(17 - 2 * (float)i, 24, 1, 0);
		pFencePanel->GetTransform()->IncrementYaw(-180);
		pFencePanel->GetTransform()->SetPosition(17 - 2 * (float)i, 4.8, 24);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<3; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-5 - 2 * (float)i, 10.01, 1, 0);
		pFencePanel->GetTransform()->IncrementYaw(-180);
		pFencePanel->GetTransform()->SetPosition(-5 - 2 * (float)i, 4.95, 10.01);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(OUTWALL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<3; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-5 - 2 * (float)i, 10, 1, 0);
		//pFencePanel->GetTransform()->IncrementYaw(-180);
		pFencePanel->GetTransform()->SetPosition(-5 - 2 * (float)i, 4.95, 10);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);
	}

	for (int i = 0; i<3; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-14, 24 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(-14, 4.95, 24 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);

	}

	for (int i = 0; i<3; i++)//far end wall
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(1 - 2 * (float)i, 0, 1, 0);
		//pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(1 - 2 * (float)i, 4.95, 0);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);

	}

	for (int i = 0; i<3; i++)//far end wall
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(1 - 2 * (float)i, 0.01, 1, 0);
		pFencePanel->GetTransform()->IncrementYaw(180);
		pFencePanel->GetTransform()->SetPosition(1 - 2 * (float)i, 4.95, 0.01);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(OUTWALL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);

	}


	for (int i = 0; i<5; i++)//second top left wall
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-4, 9 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(-4, 4.95, 9 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);

	}

	for (int i = 0; i<5; i++)//second top left wall
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(-3.99, 9 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(-90);
		pFencePanel->GetTransform()->SetPosition(-3.99, 4.95, 9 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(OUTWALL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);

	}

	for (int i = 0; i<1; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(2, 1 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(-90);
		pFencePanel->GetTransform()->SetPosition(2, 4.85, 1 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(FENCE);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);

	}

	for (int i = 0; i<1; i++)
	{
		CGameObject * pFencePanel = new CGameObject();
		CMapStorage::Instance()->AddPoint(2, 1 - 2 * (float)i, 1, 90);
		pFencePanel->GetTransform()->IncrementYaw(90);
		pFencePanel->GetTransform()->SetPosition(2, 4.85, 1 - 2 * (float)i);
		pFencePanel->GetTransform()->SetSize(2, 3.8, 2);
		pFencePanel->SetRenderable(new CSprite());
		pFencePanel->SetMaterial(new CColourMaterial());
		pFencePanel->GetMaterial()->SetTexture(OUTWALL);
		pFencePanel->GetTransform()->m_bClampToTerrain = true;
		pFencePanel->GetTransform()->m_fClampOffset = 1.0f;
		pFencePanel->GetTransform()->ApplyClampToTerrain();
		pFencePanel->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pFencePanel);

	}

	for (int i = 0; i < 12; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-3, 23 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-3, 3, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 12; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(-1, 23 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-1, 3, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}
	for (int i = 0; i < 12; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(1, 23 - 2 * (float)i, 1);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(1, 3, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	//second floor roof

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(17, 6.8, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(15, 6.8, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}
	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(13, 6.8, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(11, 6.8, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(9, 6.8, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(7, 6.8, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(5, 6.8, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 11; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(3, 6.8, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 12; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(1, 6.8, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}
	for (int i = 0; i < 12; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-1, 6.8, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}
	for (int i = 0; i < 12; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-3, 6.8, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 7; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-5, 6.8, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 7; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-7, 6.8, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 7; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-9, 6.8, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 7; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-11, 6.8, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	for (int i = 0; i < 7; i++)//floor tiles
	{
		CGameObject * pFloor = new CGameObject();
		//CMapStorage::Instance()->AddPoint(17, 23 - 2 * (float)i, 2);
		pFloor->GetTransform()->IncrementYaw(-90);
		pFloor->GetTransform()->SetSize(2, 0.11, 2);
		pFloor->GetTransform()->SetPosition(-13, 6.8, 23 - 2 * (float)i);
		//pFloor->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
		pFloor->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		pFloor->SetMaterial(new LitMaterial());
		pFloor->GetMaterial()->SetTexture(FLOOR);
		m_pRootNode->AddChild(pFloor);
	}

	// guards
	CGameObject * pArtifact3 = new CGameObject();
	pArtifact3->GetTransform()->SetSize(1, 1, 1);
	pArtifact3->GetTransform()->SetPosition(-2, 1.2, -20);
	//pArtifact3->AddBehavior(new CFallUnderGravityBehavior());
	pArtifact3->SetRenderable(new CSprite());
	pArtifact3->SetMaterial(new CColourMaterial());
	pArtifact3->GetMaterial()->EnableTransparentDepthSort();
	pArtifact3->GetMaterial()->SetTexture(EGYPT);
	pArtifact3->AddBehavior(new CFaceCameraBehavior());
	pArtifact3->GetTransform()->m_bClampToTerrain = true;
	pArtifact3->GetTransform()->m_fClampOffset = 1.0f;
	pArtifact3->GetTransform()->ApplyClampToTerrain();
	pArtifact3->GenerateColliderForRenderable(ICollider::eColliderTypeSphere);
	pArtifact3->AddBehavior(new CFaceCameraBehavior());
	pArtifact3->AddBehavior(new CCollideDeleteBehavior()); //adds the collision deletion behavior to the artifact.
	pArtifact3->GetCollider()->SetTrigger();
	m_pRootNode->AddChild(pArtifact3);

	CGameObject * pGuard1 = new CGameObject();
	pGuard1->GetTransform()->SetSize(2, 2, 2);
	pGuard1->GetTransform()->SetPosition(-4, 1.2, -20);
	pGuard1->SetRenderable(new CSprite());
	pGuard1->SetMaterial(new CColourMaterial());
	pGuard1->GetMaterial()->EnableTransparentDepthSort();
	pGuard1->GetMaterial()->SetTexture(ENEMY);
	pGuard1->AddBehavior(new CFaceCameraBehavior());
	pGuard1->GetTransform()->m_bClampToTerrain = true;
	pGuard1->GetTransform()->m_fClampOffset = 1.0f;
	pGuard1->GetTransform()->ApplyClampToTerrain();
	pGuard1->GenerateColliderForRenderable(ICollider::eColliderTypeSphere);
	pGuard1->AddBehavior(new CGuardBehavior(2));
	pGuard1->AddBehavior(new CPlayerSpotted());
	pGuard1->GetCollider()->SetTrigger();
	m_pRootNode->AddChild(pGuard1);

	CGameObject * pGuard2 = new CGameObject();
	pGuard2->GetTransform()->SetSize(2, 2, 2);
	pGuard2->GetTransform()->SetPosition(-4, 1.2, -20);
	pGuard2->SetRenderable(new CSprite());
	pGuard2->SetMaterial(new CColourMaterial());
	pGuard2->GetMaterial()->EnableTransparentDepthSort();
	pGuard2->GetMaterial()->SetTexture(ENEMY);
	pGuard2->AddBehavior(new CFaceCameraBehavior());
	pGuard2->GetTransform()->m_bClampToTerrain = true;
	pGuard2->GetTransform()->m_fClampOffset = 1.0f;
	pGuard2->GetTransform()->ApplyClampToTerrain();
	pGuard2->GenerateColliderForRenderable(ICollider::eColliderTypeSphere);
	pGuard2->AddBehavior(new CGuardBehavior(2));
	pGuard2->AddBehavior(new CPlayerSpotted()); 
	pGuard2->GetCollider()->SetTrigger();
	m_pRootNode->AddChild(pGuard2);

	CGameObject * pGuard3 = new CGameObject();
	pGuard3->GetTransform()->SetSize(2, 2, 2);
	pGuard3->GetTransform()->SetPosition(-4, 1.2, -15);
	pGuard3->SetRenderable(new CSprite());
	pGuard3->SetMaterial(new CColourMaterial());
	pGuard3->GetMaterial()->EnableTransparentDepthSort();
	pGuard3->GetMaterial()->SetTexture(ENEMY);
	pGuard3->AddBehavior(new CFaceCameraBehavior());
	pGuard3->GetTransform()->m_bClampToTerrain = true;
	pGuard3->GetTransform()->m_fClampOffset = 1.0f;
	pGuard3->GetTransform()->ApplyClampToTerrain();
	pGuard3->GenerateColliderForRenderable(ICollider::eColliderTypeSphere);
	pGuard3->AddBehavior(new CGuardBehavior(2));
	pGuard3->AddBehavior(new CPlayerSpotted()); 
	pGuard3->GetCollider()->SetTrigger();
	m_pRootNode->AddChild(pGuard3);

	CGameObject * pGuard4 = new CGameObject();
	pGuard4->GetTransform()->SetSize(2, 2, 2);
	pGuard4->GetTransform()->SetPosition(-3, 1.2, -11);
	pGuard4->SetRenderable(new CSprite());
	pGuard4->SetMaterial(new CColourMaterial());
	pGuard4->GetMaterial()->EnableTransparentDepthSort();
	pGuard4->GetMaterial()->SetTexture(ENEMY);
	pGuard4->AddBehavior(new CFaceCameraBehavior());
	pGuard4->GetTransform()->m_bClampToTerrain = true;
	pGuard4->GetTransform()->m_fClampOffset = 1.0f;
	pGuard4->GetTransform()->ApplyClampToTerrain();
	pGuard4->GenerateColliderForRenderable(ICollider::eColliderTypeSphere);
	pGuard4->AddBehavior(new CGuardBehavior(2));
	pGuard4->AddBehavior(new CPlayerSpotted());
	pGuard4->GetCollider()->SetTrigger();
	m_pRootNode->AddChild(pGuard4);
	

	//creates the GUI for the game.
	CGameObject * pGun = new CGameObject();
	pGun->GetTransform()->SetPosition(0.25f, -0.35f, 0.0f);
	pGun->GetTransform()->SetSize(0.5f, 0.3f, 1.0f);
	pGun->SetMaterial(new CColourMaterial());
	pGun->SetRenderable(new CGUITextureRenderable());
	pGun->GetMaterial()->SetTexture(GUN);
	pGun->GetMaterial()->EnableTransparentDepthSort();
	m_pRootNode->AddChild(pGun);

	CGameObject * pNumber = new CGameObject();
	pNumber->GetTransform()->SetPosition(0.425, 0.280, 0);
	pNumber->GetTransform()->SetSize(0.03, 0.03, 1);
	pNumber->SetRenderable(new CGUITextureRenderable());
	pNumber->SetMaterial(new CColourMaterial());
	pNumber->GetMaterial()->SetTexture(ZERO);
	pNumber->GetMaterial()->EnableTransparentDepthSort();
	m_pRootNode->AddChild(pNumber);

	CGameObject * pHUD = new CGameObject();
	pHUD->GetTransform()->SetPosition(0.425, 0.375, 0);
	pHUD->GetTransform()->SetSize(0.15, 0.25, 1);
	pHUD->SetRenderable(new CGUITextureRenderable());
	pHUD->SetMaterial(new CColourMaterial());
	pHUD->GetMaterial()->SetTexture(GUI);
	pHUD->GetMaterial()->EnableTransparentDepthSort();
	m_pRootNode->AddChild(pHUD);

	CMapStorage::Instance()->PrintMap();
}

void
MyGame::LoadWorld2()
{
	//add some objects

	m_pRootNode = new CGameObject();
	m_pRootNode->GetTransform()->SetPosition(0, 2, 5);
	m_pRootNode->SetRenderable(new CCamera());
	m_pRootNode->AddBehavior(new FPSCameraBehavior());
	m_pRootNode->GenerateColliderForRenderable();
	m_pRootNode->AddBehavior(new CFallUnderGravityBehavior());
	//m_pRootNode->AddBehavior(new CFireMissileBehavior());
	m_pRootNode->AddBehavior(new CFireRayBehavior());

	{
		// skybox section + world boundaries colliders
		CGameObject * pSkyBox = new CGameObject();
		pSkyBox->GetTransform()->SetPosition(0.0f, 0.0f, 0.0f);
		pSkyBox->GetTransform()->SetSize(50, 50, 50);
		pSkyBox->SetMaterial(new CSkyBoxMaterial());
		pSkyBox->GetMaterial()->SetTexture(SKYBOX);
		pSkyBox->SetRenderable(new CSkyBoxRenderable());
		pSkyBox->GenerateColliderForRenderable(ICollider::eColliderTypeCube);
		m_pRootNode->AddChild(pSkyBox);

		CGameObject * pSkyBoxPanel1 = new CGameObject();
		pSkyBoxPanel1->GetTransform()->SetPosition(0.0f, 25.0f, -25.1f);
		pSkyBoxPanel1->GetTransform()->SetSize(50, 50, 0);
		pSkyBoxPanel1->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pSkyBoxPanel1);

		CGameObject * pSkyBoxPanel2 = new CGameObject();
		pSkyBoxPanel2->GetTransform()->SetPosition(0.0f, 25.0f, 25.1f);
		pSkyBoxPanel2->GetTransform()->SetSize(50, 50, 0);
		pSkyBoxPanel2->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pSkyBoxPanel2);

		CGameObject * pSkyBoxPanel3 = new CGameObject();
		pSkyBoxPanel3->GetTransform()->SetPosition(25.1f, 25.0f, 0.0f);
		pSkyBoxPanel3->GetTransform()->SetSize(0, 50, 50);
		pSkyBoxPanel3->GetTransform()->IncrementYaw(180);
		pSkyBoxPanel3->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pSkyBoxPanel3);

		CGameObject * pSkyBoxPanel4 = new CGameObject();
		pSkyBoxPanel4->GetTransform()->SetPosition(-25.1f, 25.0f, 0.0f);
		pSkyBoxPanel4->GetTransform()->SetSize(0, 50, 50);
		pSkyBoxPanel4->GetTransform()->IncrementYaw(180);
		pSkyBoxPanel4->GenerateColliderForRenderable(ICollider::eColliderTypePlane);
		m_pRootNode->AddChild(pSkyBoxPanel4);
	}
	// skyBox + boundaries section end

	CGameObject * pTerrain = new CGameObject();
	pTerrain->GetTransform()->SetSize(50, 0.1, 50);
	pTerrain->SetRenderable(new CTerrainRenderable("assets/heightfield256.bmp"));
	pTerrain->SetMaterial(new LitMaterial());
	pTerrain->GetMaterial()->SetTexture(GRASS);
	m_pRootNode->AddChild(pTerrain);

	CGameObject * pAlien = new CGameObject();
	pAlien->GetTransform()->SetPosition(-2, 1.0, 0);
	pAlien->SetMaterial(new LitMaterial());
	//pAlien->AddBehavior(new CSpinBehavior());
	//pAlien->AddBehavior(new CAgentBehavior());
	pAlien->AddBehavior(new CMovingForwardBehavior(1));
	pAlien->AddBehavior(new CTurnAfterTimeBehavior(0, 1, 180));
	pAlien->GetMaterial()->SetTexture(CRATE);
	m_pRootNode->AddChild(pAlien);


	CGameObject * pGun = new CGameObject();
	pGun->GetTransform()->SetPosition(0.25f, -0.35f, 0.0f);
	pGun->GetTransform()->SetSize(0.5f, 0.3f, 1.0f);
	pGun->SetMaterial(new CColourMaterial());
	pGun->SetRenderable(new CGUITextureRenderable());
	pGun->GetMaterial()->SetTexture(GUN);
	pGun->GetMaterial()->EnableTransparentDepthSort();
	m_pRootNode->AddChild(pGun);

	CGameObject * pHUD = new CGameObject();
	pHUD->GetTransform()->SetPosition(0.425, 0.375, 0);
	pHUD->GetTransform()->SetSize(0.15, 0.25, 1);
	pHUD->SetRenderable(new CGUITextureRenderable());
	pHUD->SetMaterial(new CColourMaterial());
	pHUD->GetMaterial()->SetTexture(GUI);
	pHUD->GetMaterial()->EnableTransparentDepthSort();
	m_pRootNode->AddChild(pHUD);

}



void MyGame::DoFrame()
{
	//while we are in menu mode, we provide 
	if (m_eState == eGameStateMenu)
	{
		CMouseManager::Instance()->setMouseAnchoredToCentreScreen(false);

		//initialisation to refresh Input and get dt
		PrepareForDoFrame();
		//draw the menu gameobject
		pPlayButton->Update(0);
		pOptionsButton->Update(0);
		pScoreButton->Update(0);

		pMenu->Render();
		pPlayButton->Render();
		pOptionsButton->Render();
		pScoreButton->Render();

		//check for condition to change state
		if (CInput::Instance()->GetIfKeyDown(DIK_SPACE))
		{
			m_eState = eGameStatePlay;
		}
	}


	if (m_eState == eGameStatePlay)
	{
		CMouseManager::Instance()->setMouseAnchoredToCentreScreen(true);
		//use DoFrame method from base class which is CGame
		CGame::DoFrame();
	}

	if (!m_bWorldLoaded)
	{
		//call loading of the textures
		LoadTextures();

		//call loading of the world
		LoadWorld();

		m_bWorldLoaded = true;
	}

	if (m_eState == eGameStateInstructions)
	{
		CMouseManager::Instance()->setMouseAnchoredToCentreScreen(false);

		LoadInstructions();
		//initialisation to refresh Input and get dt
		PrepareForDoFrame();
		//draw the menu gameobject

		pInstructions->Render();

		if (CInput::Instance()->GetIfKeyDownEvent(DIK_ESCAPE))
		{
			m_eState = eGameStateMenu;
		}
	}

	if (m_eState == eGameStateWon)
	{
		CMouseManager::Instance()->setMouseAnchoredToCentreScreen(false);

		LoadWon();
		//initialisation to refresh Input and get dt
		PrepareForDoFrame();
		//draw the menu gameobject

		pWon->Render();

		if (CInput::Instance()->GetIfKeyDownEvent(DIK_ESCAPE))
		{
			m_eState = eGameStateMenu;
		}
	}
	if (m_eState == eGameStateLost)
	{
		CMouseManager::Instance()->setMouseAnchoredToCentreScreen(false);

		LoadLost();
		//initialisation to refresh Input and get dt
		PrepareForDoFrame();
		//draw the menu gameobject

		pLost->Render();

		if (CInput::Instance()->GetIfKeyDownEvent(DIK_ESCAPE))
		{
			m_eState = eGameStateMenu;
		}
	}


}