#include "StdAfx.h"
#include "IMaterial.h"

IMaterial::IMaterial(void)
{
	m_bTransparent = false;
}

IMaterial::~IMaterial(void)
{
}


void
IMaterial::EnableTransparentDepthSort()
{
	m_bTransparent=true;
	CTransparentRenderingManager::AddGameObject(m_pGameObject);
}