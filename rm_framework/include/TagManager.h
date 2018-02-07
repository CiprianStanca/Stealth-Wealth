#pragma once
#include <map>
#include <string>

class CTagManager
{
public:
	CTagManager(void);
	~CTagManager(void);
	void AddTag(CGameObject * gameObject_, char * strTag);
	CGameObject * GetObjectWithTag(char * strTag);
	static CTagManager * Instance();
	static CTagManager * Destroy();

	int GetNumTags(){return (int)m_iNumTags;}

private:
	static CTagManager * _instance;
	std::map<std::string, CGameObject *> tagMap;
	unsigned int m_iNumTags;
};

