#include "StdAfx.h"
#include "PlayerBehavior.h"
#include "Input.h"

CPlayerBehavior::CPlayerBehavior(void)
{
}

CPlayerBehavior::~CPlayerBehavior(void)
{
}

void
CPlayerBehavior::Update(float dt_)
{

	if (CInput::Instance()->GetIfKeyDown(DIK_RIGHT))
	{
		m_pTransform->Translate(CVector3(0.1f,0,0));
	}
	else if (CInput::Instance()->GetIfKeyDown(DIK_LEFT))
	{
		m_pTransform->Translate(CVector3(-0.1f,0,0));
	}
}
