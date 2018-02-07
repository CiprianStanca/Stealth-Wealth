#pragma once
class CGameObject;
class CTransform;

extern CGame * g_pGame; //the global game object

class IComponent
{
public:
	IComponent(void);
	~IComponent(void);
	virtual void SetGameObject(CGameObject * pGameObject_);
	CGameObject * GetGameObject(){return m_pGameObject;}
	CTransform * GetTransform(){return m_pTransform;}
	virtual void AddedToGameObject(){;}
	virtual char * GetType(){return "IComponent";}
	friend class CCollisionManager;
protected:

	CGameObject * m_pGameObject;
	CTransform * m_pTransform;
};
