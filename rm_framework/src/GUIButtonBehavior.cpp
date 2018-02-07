#include "stdafx.h"
#include "GUIButtonBehavior.h"


CGUIButtonBehavior::CGUIButtonBehavior()
{
	//register self as Mouse Listener
	CMouseManager::Instance()->addMouseMovedListener(this);
	m_bButtonStateLastFrame = false;
}


CGUIButtonBehavior::~CGUIButtonBehavior()
{
}

void 
CGUIButtonBehavior::MouseMoved(float x_, float y_)
{
	m_fMouseXRel = x_;
	m_fMouseYRel = y_;

	char txt[64];
	sprintf(txt, "mouse at: %2.2f,%2.2f", m_fMouseXRel, m_fMouseYRel);
	DPrint(txt);
}

void
CGUIButtonBehavior::Update(float dt_)
{
	float width = m_pTransform->GetSize3().m_fX;
	float height = m_pTransform->GetSize3().m_fY;
	float thisx = m_pTransform->GetPosition().m_fX;
	float thisy = m_pTransform->GetPosition().m_fY;

	float xmin = 0.5*(1 - width) + thisx;
	float xmax = 0.5*(1 + width) + thisx;

	float ymin = 0.5*(1 - height) - thisy;
	float ymax = 0.5*(1 + height) - thisy;

	m_bMouseIsOver = false;
	//compare with mouse
	if (m_fMouseXRel > xmin   && m_fMouseXRel < xmax)
	{
		if (m_fMouseYRel > ymin   && m_fMouseYRel < ymax)
		{
			m_bMouseIsOver = true;
		}
	}


	if (m_bMouseIsOver && !m_bButtonStateLastFrame)
	{
		//increment texture
		m_iNormalTexture = m_pGameObject->GetMaterial()->GetTexture();
		m_pGameObject->GetMaterial()->SetTexture(m_iNormalTexture + 1);
		
		OnMouseEnter();
	}
	if (!m_bMouseIsOver && m_bButtonStateLastFrame)
	{
		//decrement texture
		m_pGameObject->GetMaterial()->SetTexture(m_iNormalTexture);

		OnMouseLeave();
	}

	if (m_bMouseIsOver && ((GetKeyState(VK_LBUTTON)) & 0x100) != 0)
	{
		m_pGameObject->GetMaterial()->SetTexture(m_iNormalTexture+2);

		OnClick();
	}
	m_bButtonStateLastFrame = m_bMouseIsOver;
	
}

void 
CGUIButtonBehavior::OnMouseEnter()
{

}


void 
CGUIButtonBehavior::OnMouseLeave()
{
	
}


void
CGUIButtonBehavior::OnClick()
{

}