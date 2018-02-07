#pragma once
#include "IBehavior.h"
#include "IMouseListener.h"


class CGUIButtonBehavior :
	public IBehavior,
	public IMouseListener
{
public:
	CGUIButtonBehavior();
	~CGUIButtonBehavior();
	void MouseMoved(float x_, float y_);
	void Update(float dt_);

private:
	float m_fMouseXRel;
	float m_fMouseYRel;
	bool m_bMouseIsOver;
	bool m_bButtonStateLastFrame;

	virtual void OnMouseEnter(); //to be overridden by sub classes
	virtual void OnMouseLeave(); //to be overridden by sub classes
	virtual void OnClick(); //to be overridden by sub classes

	int m_iNormalTexture;
};

