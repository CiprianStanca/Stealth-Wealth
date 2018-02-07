#pragma once

class CNode
{
public:
	CNode(void);
	CNode(CNode * node_);
	~CNode(void);
	CNode * pParent;
	CNode * pChild;
	CNode * pPrev;
	CNode * pNext;

	bool HasParent();
	bool HasChild();
	bool IsFirstChild();
	bool IsLastChild();

	void AttachTo(CNode * newParent_);
	void AddChild(CNode * newChild_);
	void Detach();
	int CountNodes();

	

	
};
