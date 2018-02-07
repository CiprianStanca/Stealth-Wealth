#pragma once
class CGuardCaptain
{
public:
	CGuardCaptain();
	~CGuardCaptain();
	static CGuardCaptain * Instance();

	void Destroy();
	void Update();
	bool CaptainOrder();
	CVector3 GetPlayerPosition();
	
private:
	static CGuardCaptain * instance_;
	bool m_bCaptainResponse;
	CVector3 m_v3PlayerPosition;
};

