#pragma once
#include <map>
#include <string>

class ICollider;
class CVector3;

class CCollisionManager
{
public:
	CCollisionManager(void);
	~CCollisionManager(void);
	static CCollisionManager * Instance();
	void Destroy();
	void  AddCollider(ICollider * col);
	void RemoveCollider(ICollider * col);
	void RenderAllColliders();
	bool GetCollision(ICollider * in_,ICollider *out_=0);
	bool GetCollisionWithRay(CVector3 raystart, CVector3 direction, float length, ICollider *out_=0, CVector3 * hitPoint_=0);

private:
	static CCollisionManager * _instance;
	vector<ICollider *> m_vCollidersList;
	void ShowDebugInfo();

};