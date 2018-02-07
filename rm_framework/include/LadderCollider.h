#pragma once
class CLadderCollider:
	public ICollider 
{
public:
	CLadderCollider();
	~CLadderCollider();

	bool CheckForCollision(ICollider * in_);
	bool RespondToCollision();
	char * GetType() { return "CPlaneCollider"; }
	void Render();
	void AddedToGameObject();

private:
	bool m_bUseXAxis; // if false then use z axis
	float m_fMinX;
	float m_fMaxX;
	float m_fMinY;
	float m_fMaxY;
	float m_fMinZ;
	float m_fMaxZ;
	bool m_bUseZAxis;
};

