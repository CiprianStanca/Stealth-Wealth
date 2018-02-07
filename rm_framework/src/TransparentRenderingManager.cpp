#include "stdafx.h"
#include "TransparentRenderingManager.h"


CTransparentRenderingManager::CTransparentRenderingManager(void)
{
}


CTransparentRenderingManager::~CTransparentRenderingManager(void)
{
}

void 
CTransparentRenderingManager::AddGameObject(CGameObject * obj)
{
	m_vTransparentGameObject_list.push_back(obj);
	DPrint("transparent object added");

}


void 
CTransparentRenderingManager::RemoveGameObject(CGameObject * obj)
{
	//find the specified game object in the list
	vector<CGameObject *>::iterator itr =find (m_vTransparentGameObject_list.begin(), m_vTransparentGameObject_list.end(), obj);
	if (itr == m_vTransparentGameObject_list.end()) return; //item not found

    m_vTransparentGameObject_list.erase(itr);
}


bool SortGameObjects( CGameObject * b1,  CGameObject * b2)
{
  return b1->GetDistanceFromCamera() > b2->GetDistanceFromCamera();
	
}

void 
CTransparentRenderingManager::RenderAllTransparentObjectsBackToFront()
{
	std::sort(m_vTransparentGameObject_list.begin(), m_vTransparentGameObject_list.end(), SortGameObjects);

	

	std::vector<CGameObject *>::iterator itr = m_vTransparentGameObject_list.begin();

	glPushMatrix();
	glLoadIdentity();
	//find the camera game object
	CGameObject * cam = CTagManager::Instance()->GetObjectWithTag("Camera");
	CCamera * pCamera=(CCamera *)(cam->GetRenderable());
	pCamera->Render();

	for ( ; itr< m_vTransparentGameObject_list.end(); itr++)
	{
		glPushMatrix();
		//render game object
		(*itr)->GetMaterial()->SetupRendering();
		(*itr)->GetRenderable()->Render();
		glPopMatrix();
	}
	glPopMatrix();
}




std::vector<CGameObject *> CTransparentRenderingManager::m_vTransparentGameObject_list;

