#include "stdafx.h"
#include "Node.h"

CNode::CNode(void) //setup new node, not attached to anything
{
	pParent=0;
	pChild=0;
	pPrev=this;
	pNext=this;
}

CNode::CNode(CNode * node_) //setup new node and attach it as a child of specified node
{
	pParent=0;
	pChild=0;
	pPrev=this;
	pNext=this;
	//AttachTo(node_);
}

CNode::~CNode(void)
{
	Detach();

	while (pChild) //delete all children
	{
		delete pChild;
	}
}

bool 
CNode::HasParent()
{
	return (pParent!=0);
}

bool 
CNode::HasChild()
{
	return (pChild !=0);
}

bool 
CNode::IsFirstChild()
{
	if (pParent)
	{
		return (pParent->pChild==this);
	}
	else
	{
		return false;
	}
}
	
bool 
CNode::IsLastChild()
{
	if (pParent)
	{
		return (pParent->pChild->pPrev == this);
	}
	else
	{
		return false;
	}
}

void 
CNode::AttachTo(CNode * newParent_)
{
//if this node already attached to another node then detach it
	if (pParent)
	{
		Detach();
	}

	pParent=newParent_;

	if (pParent->pChild) //child already exists, this is not the first child
	{
		pPrev=pParent->pChild->pPrev;
		pNext=pParent->pChild;
		pParent->pChild->pPrev->pNext=this;
		pParent->pChild->pPrev=this;
	}
	else
	{
		pParent->pChild=this; //this is the first child
	}
}

void
CNode::AddChild(CNode * newChild_)
{
	//if child node is already attached then detach it
	if (newChild_->HasParent())
	{
		newChild_->Detach();
	}
	newChild_->pParent=this;

	if (pChild)
	{
		newChild_->pPrev=pChild->pPrev;
		newChild_->pNext=pChild;
		pChild->pPrev->pNext=newChild_;
		pChild->pPrev=newChild_;
	}
	else
	{
		pChild=newChild_;
	}
	
}


void
CNode::Detach()
{
//if this node is the first child of the parent (first in list)
	//then the parent points to the next child in the list
	if (pParent && pParent->pChild ==this)
	{
		if (pNext != this)
		{
			pParent->pChild=pNext;
		}
		else
		{
			pParent->pChild=0;
		}
	}
	//get rid of links
	pPrev->pNext=pNext;
	pNext->pPrev=pPrev;

	//now this node is not in the list
	pPrev=this;
	pNext=this;
}

int
CNode::CountNodes()
{
	if (pChild)
	{
		return pChild->CountNodes() +1 ;
	}
	else
	{ 
		return 1;
	}
}


