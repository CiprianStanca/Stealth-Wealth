#pragma once
class CRayRenderable : public IRenderable
{
public:
	CRayRenderable(void);
	CRayRenderable(float length_);
	~CRayRenderable(void);
	void Render();
	void CheckRayForCollision();

protected:
	float m_fRayLength;
};

