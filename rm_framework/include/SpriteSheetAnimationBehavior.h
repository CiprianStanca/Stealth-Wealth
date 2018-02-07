#pragma once
#include "ibehavior.h"
class CSpriteSheetAnimationBehavior :
	public IBehavior
{
public:
	CSpriteSheetAnimationBehavior(int rows_ = 4, int cols_ = 4, float fps_ = 10.0f, int startframe_ = 0, int endFrame_ = -1);
	~CSpriteSheetAnimationBehavior(void);
	void Update(float dt_);
	void AddedToGameObject();

private:
	float m_fSecondsPerFrame;
	int m_iCols;
	int m_iRows;
	float m_tTimeSinceLastFrameChange;
	int m_iCurrentFrame;
	int m_iTotalFrames;
	void NextFrame();
	int m_iStartFrame;
	int m_iEndFrame;
};

