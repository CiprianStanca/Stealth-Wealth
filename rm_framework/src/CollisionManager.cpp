#include "stdafx.h"
#include "CollisionManager.h"


CCollisionManager::CCollisionManager(void)
{
}


CCollisionManager::~CCollisionManager(void)
{
}

void  
CCollisionManager::AddCollider(ICollider * col)
{
	DPrint("adding collider");
	DPrint(col->GetType());
	m_vCollidersList.push_back(col);
	ShowDebugInfo();
}

void 
CCollisionManager::RemoveCollider(ICollider * col)
{
	DPrint("removing collider");
	//find the specified collider in the list
	vector<ICollider *>::iterator itr =find (m_vCollidersList.begin(), m_vCollidersList.end(), col);
	if (itr == m_vCollidersList.end()) return; //item not found

    m_vCollidersList.erase(itr);
	ShowDebugInfo();
}

bool
CCollisionManager::GetCollision(ICollider * in_, ICollider * out_)
{
	//iterate through all colliders
	vector<ICollider *>::iterator itr=m_vCollidersList.begin();

	for (; itr< m_vCollidersList.end(); itr++)
	{
		ICollider * colToTest = (*itr);
		if (colToTest==0) continue;

		if (colToTest==in_) continue; //no point checking against self

		if (colToTest->CheckForCollision(in_))
		{
		
				//collision occur
				//send output data about colliding object
				if (out_)
				{
					out_->SetPosition(&(colToTest->m_vPosition));
					out_->m_pGameObject =colToTest->GetGameObject();
					out_->m_bIsTrigger = colToTest->m_bIsTrigger;				
				}
				return true;
			
		}
	}
	return false;
}


bool
CCollisionManager::GetCollisionWithRay(CVector3 raystart_, CVector3 direction_, float length_, ICollider *out_, CVector3 * hitPoint_)
{

	//iterate through all colliders
	vector<ICollider *>::iterator itr=m_vCollidersList.begin();

	for (; itr< m_vCollidersList.end(); itr++)
	{

		ICollider * colToTest = *itr;

			if (colToTest->CheckForCollisionWithRay(raystart_, direction_,length_,hitPoint_))
			{
				//we have a collision with collider
				//send output data about colliding object
				if (out_)
				{
					out_->SetPosition(&(colToTest->m_vPosition));
					out_->m_pGameObject =colToTest->GetGameObject();
				
				}
				return true;
			}

	

	}//end loop
	return false;	

}//end funct


void 
CCollisionManager::ShowDebugInfo()
{
	char txt[32];
	sprintf(txt,"there are now %d colliders",m_vCollidersList.size());
	DPrint(txt);

}

void  
CCollisionManager::RenderAllColliders()
{
	glPushMatrix();
	glLoadIdentity();
	//find the camera game object
	CGameObject * cam = CTagManager::Instance()->GetObjectWithTag("Camera");
	CCamera * pCamera=(CCamera *)(cam->GetRenderable());
	pCamera->Render();

	vector<ICollider *>::iterator itr=m_vCollidersList.begin();

	for (; itr< m_vCollidersList.end(); itr++)
	{
		(*itr)->Render();
	}
	glPopMatrix();
}


void
CCollisionManager::Destroy()
{
	if (_instance)
	{
	delete _instance;
	_instance=0;
	}

}




CCollisionManager *
CCollisionManager::Instance()
{
	if (_instance ==0)
	{
		_instance = new CCollisionManager();
	}
	return _instance;
}

CCollisionManager * CCollisionManager::_instance =0;