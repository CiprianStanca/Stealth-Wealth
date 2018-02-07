#include "stdafx.h"
#include "MouseManager.h"


CMouseManager::CMouseManager(void)
{
}


CMouseManager::~CMouseManager(void)
{
}


//add listener to vector of currently active listeners
void 
CMouseManager::addMouseMovedListener(IMouseListener * listener_)
{
	m_vMouseListeners.push_back(listener_);
}
	
void 
CMouseManager::mouseMoved(float x_, float y_)
{
	//iterate through list of listeners and call their mousemoved function
	std::vector<IMouseListener *>::iterator itr = m_vMouseListeners.begin();

	for (;itr<m_vMouseListeners.end(); itr++)
	{
		(*itr)->MouseMoved(x_,y_);
	}
}


	
	//singleton access function
CMouseManager *
CMouseManager::Instance()
{
	if (_instance ==0)
	{
		_instance = new CMouseManager();
	}
	return _instance;
}

CMouseManager * CMouseManager::_instance=0;