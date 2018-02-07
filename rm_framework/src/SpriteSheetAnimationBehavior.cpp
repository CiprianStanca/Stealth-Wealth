#include "stdafx.h"
#include "SpriteSheetAnimationBehavior.h"


CSpriteSheetAnimationBehavior::CSpriteSheetAnimationBehavior(int rows_, int cols_, float fps_, int startFrame_, int endFrame_)
{
	m_fSecondsPerFrame = 1.0f / (float)fps_;
	m_iCols = cols_;
	m_iRows = rows_;
	m_tTimeSinceLastFrameChange = 0.0f;

	m_iTotalFrames = m_iCols *m_iRows;

	m_iStartFrame = startFrame_;
	m_iEndFrame = endFrame_ == -1 ? (m_iTotalFrames - 1) : endFrame_;
	m_iCurrentFrame = m_iStartFrame - 1;

	NextFrame();
}


CSpriteSheetAnimationBehavior::~CSpriteSheetAnimationBehavior(void)
{
}

void
CSpriteSheetAnimationBehavior::Update(float dt_)
{
	m_tTimeSinceLastFrameChange +=dt_;

	if ((m_tTimeSinceLastFrameChange) >m_fSecondsPerFrame)
	{
		m_tTimeSinceLastFrameChange=0.0f;
		NextFrame();
	}
}


void
CSpriteSheetAnimationBehavior::NextFrame()
{
	m_iCurrentFrame++;
	if (m_iCurrentFrame >= m_iEndFrame)
	{
		m_iCurrentFrame = m_iStartFrame;
	}

	//calc row
	int col = (m_iCurrentFrame / m_iCols);
	int row = (m_iCurrentFrame % m_iCols);

	float rowWidth = 1.0f / (float)m_iCols;
	float colHeight = 1.0f / (float)m_iRows;

	float m_fULeft = row * rowWidth;// + 0.01;
	float m_fURight = (row + 1)* rowWidth;// -0.01;
	float m_fVTop = ((m_iCols - 1 - col) + 1) * colHeight;// -0.01;
	float m_fVBottom = (m_iCols - 1 - col) * colHeight;// + 0.01;

	//now set u,v coordinates on the sprite renderable
	if (m_pGameObject)
	{
		IRenderable * ren = m_pGameObject->GetRenderable();
		CSprite * spr = (CSprite *)ren;

		if (spr)
		{
			spr->SetUV(m_fULeft, m_fURight, m_fVBottom, m_fVTop);
		}
	}
	char text[128];
	sprintf(text, "animation frame %d, row:%d, col:%d, uvs are %2.2f,%2.2f,%2.2f,%2.2f", m_iCurrentFrame, row, col, m_fULeft, m_fURight, m_fVBottom, m_fVTop);
	//DPrint(text);
}

void
CSpriteSheetAnimationBehavior::AddedToGameObject()
{
	NextFrame();
}