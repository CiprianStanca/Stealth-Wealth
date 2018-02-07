#pragma once
class CGameObject;

static enum eGameState
{
	eGameStateMenu,
	eGameStatePlay,
	eGameStateInstructions,
	eGameStateWon,
	eGameStateLost
};

class CGame
{
public:
	CGame();
	~CGame(void);

	virtual void DoFrame();
	void AddObject(CGameObject * pGameObject_);
	float PrepareForDoFrame();
	virtual void SetState(eGameState state);
	bool isClimbing = false; //Variable responsbile for ladder climbing
	bool m_bPlayerSpotted = false;
	float m_fDelay;
	CGameObject * m_pRootNode;
	int ammo = 30;

protected:
	eGameState m_eState;
};
