#pragma once

class CDebugLog
{
public:
	
	~CDebugLog(void);
	void Print(char * txt_);
	static CDebugLog * Instance();
private:
	CDebugLog(void);
	static CDebugLog * pInstance;
};
