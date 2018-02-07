#pragma once

#include <vector>
class IMouseListener;

class CMouseManager
{
public:
	static CMouseManager * Instance(); //singleton access function
	CMouseManager(void);
	~CMouseManager(void);
	void addMouseMovedListener(IMouseListener * listener_);
	void mouseMoved(float xrel_, float yrel_);

	void setMouseAnchoredToCentreScreen(bool trueFalse_){ bMouseAnchoredToCentreScreen = trueFalse_; }
	bool GetMouseAnchoredToCentreScreen(){ return bMouseAnchoredToCentreScreen; }

private:
	std::vector <IMouseListener * > m_vMouseListeners;
	static CMouseManager * _instance;
	bool bMouseAnchoredToCentreScreen;
};

