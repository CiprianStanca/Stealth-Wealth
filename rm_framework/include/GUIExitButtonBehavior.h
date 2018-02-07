#pragma once
#include "guibuttonbehavior.h"
class CGUIExitButtonBehavior :
	public CGUIButtonBehavior
{
public:
	CGUIExitButtonBehavior(void);
	~CGUIExitButtonBehavior(void);
	void OnClick();
};
