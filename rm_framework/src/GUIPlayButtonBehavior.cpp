#include "stdafx.h"
#include "GUIPlayButtonBehavior.h"

extern CGame * g_pGame;

CGUIPlayButtonBehavior::CGUIPlayButtonBehavior(void)
{
}


CGUIPlayButtonBehavior::~CGUIPlayButtonBehavior(void)
{
}

void
CGUIPlayButtonBehavior::OnClick()
{
	g_pGame->SetState(eGameStatePlay);
}