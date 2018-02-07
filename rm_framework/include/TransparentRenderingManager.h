#pragma once

class CGameObject;

#include <vector>

class CTransparentRenderingManager
{
public:
	CTransparentRenderingManager(void);
	~CTransparentRenderingManager(void);
	static void RenderAllTransparentObjectsBackToFront();
	static void AddGameObject(CGameObject * obj);
	static void RemoveGameObject(CGameObject * obj);
	static std::vector<CGameObject *> m_vTransparentGameObject_list;
};

