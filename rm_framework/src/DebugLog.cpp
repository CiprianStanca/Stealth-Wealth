#include "StdAfx.h"
#include "DebugLog.h"

CDebugLog::CDebugLog(void)
{
}

CDebugLog::~CDebugLog(void)
{
}

void
CDebugLog::Print(char *txt_)
{
	OutputDebugString("\n+++++");
	OutputDebugString(txt_);
	OutputDebugString("+++++\n");
}

CDebugLog * 
CDebugLog::Instance()
{
	if (NULL==pInstance)
	{
		pInstance=new CDebugLog();
	}
	return pInstance;
}

CDebugLog * CDebugLog::pInstance=NULL;