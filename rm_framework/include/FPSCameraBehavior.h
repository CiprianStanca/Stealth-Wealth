#pragma once
#include "ibehavior.h"
#include "IMouseListener.h"

//inherits from both IBhehavior and IMouseListener to get mouse move events
class FPSCameraBehavior :
	public IBehavior,
	public IMouseListener
{
public:
	FPSCameraBehavior(void);
	~FPSCameraBehavior(void);
	void Update(float dt_);
	void MouseMoved(float x_, float y_);

private:
	float m_fSpeed;
	float m_fStrafeSpeed;
	float m_fJumpSpeed;
	float m_fClimbingLadder;

	CGameObject * pExitMenu;
	CGameObject * pExitButton;
};

