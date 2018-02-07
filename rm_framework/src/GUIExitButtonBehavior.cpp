#include "stdafx.h"
#include "GUIExitButtonBehavior.h"

extern CGame * g_pGame;

CGUIExitButtonBehavior::CGUIExitButtonBehavior(void)
{
}


CGUIExitButtonBehavior::~CGUIExitButtonBehavior(void)
{
}

void
CGUIExitButtonBehavior::OnClick()
{
	exit(0);
}