#include "stdafx.h"
#include "TagManager.h"


CTagManager::CTagManager(void)
{
}


CTagManager::~CTagManager(void)
{
}

void 
CTagManager::AddTag(CGameObject * gameObject_, char * strtag)
{
	std::string tag(strtag);
	tagMap[tag]=gameObject_;
	m_iNumTags=tagMap.size();
}

CTagManager *
CTagManager::Destroy()
{
	if (_instance)
	{
	delete _instance;
	_instance=0;
	}


	return _instance;
}

CGameObject * 
CTagManager::GetObjectWithTag(char * strTag)
{
	std::string tag(strTag);

	if (tagMap.count(tag))
	{
		CGameObject *obj =tagMap[tag];
		return obj;
	}
	else
	{
		return 0;
	}
}


CTagManager *
CTagManager::Instance()
{
	if (_instance ==0)
	{
		_instance = new CTagManager();
	}
	return _instance;
}

CTagManager * CTagManager::_instance =0;