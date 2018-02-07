#pragma once
class CGuardBehavior:
	public IBehavior
{
public:
	CGuardBehavior(int level);
	~CGuardBehavior();
	void Update(float dt_);
	void SetLevel(int level);

private:
	CVector3 m_v3PlayerPosition;
	int m_iGuardCurrentLevel;
	bool m_bIgnoreOrders;
};

