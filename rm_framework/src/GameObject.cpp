#include "StdAfx.h"
#include "GameObject.h"


CGameObject::CGameObject(void)
{
	m_pRenderable=0;
	m_pMaterial=0;
	m_pCollider=0;
	m_pCollisionResponder=0;

	//add default components
	SetMaterial(new LitMaterial());
	SetTransform(new CTransform());
	SetRenderable(new C3DShape());
	//by default only certain types of renderable generate a collider
	//they have a function GetBoundingSphereRadius - if this returns 0 no collider is created
	m_bTaggedForDeletion=false;
	m_bActive=true;

}

CGameObject::~CGameObject(void)
{

	//destroy components
	if (m_pRenderable)
		{
			delete m_pRenderable;
		}
	
	if (m_pMaterial)
		{
		if(m_pMaterial->GetIfUsesTransparencyDepthSort())
			{
				//remove self from transparentRenderingManager
				CTransparentRenderingManager::RemoveGameObject(this);
			}
			delete m_pMaterial;
		}
	if (m_pCollider)
		{
				delete m_pCollider;
		}
	if (m_pCollisionResponder)
		{
				delete m_pCollisionResponder;
		}
	if (m_vBehaviors.size() >0)
	{
		//iterate through behaviors and delete each one
		//loop through all behaviors
		std::vector<IBehavior *>::iterator itr = m_vBehaviors.begin();
		for (; itr<m_vBehaviors.end(); itr++)
		{
			delete (*itr);
			(*itr) = 0;

		}
		m_vBehaviors.resize(0);
	}
}




void
CGameObject::Render()
{
	if (!m_bActive) return;

	if (m_pMaterial)
	{
		m_pMaterial->SetupRendering();
		if (m_pMaterial->GetIfUsesTransparencyDepthSort())
		{
			return;
		}
	}

	if (m_pRenderable)
	{
		m_pRenderable->Render();
	}

	/*if (m_pCollider)
	{
		m_pCollider->Render();
	}*/
}

void
CGameObject::Update(float dt_)
{
		if (!m_bActive) return;

		//loop through all behaviors
		std::vector<IBehavior *>::iterator itr = m_vBehaviors.begin();
		for (; itr<m_vBehaviors.end(); itr++)
		{
		(*itr)->Update(dt_);
		}
		
}

void
CGameObject::RenderRecursive()
{
	//render self then render children

	glPushMatrix();
	Render();

	if (HasChild())
	{
		((CGameObject *)pChild)->RenderRecursive();
	}

	glPopMatrix();
	
	//then render siblings

	if (HasParent() && !IsLastChild())
	{
	((CGameObject *)pNext)->RenderRecursive();
	}
}

void
CGameObject::UpdateRecursive(float dt_)
{

	//update self then update children


	Update(dt_);

	if (HasChild())
	{
		CGameObject * pChildGO =(CGameObject *)pChild;
		if (pChildGO->bGetTaggedForDeletion())
		{
			//delete child and remove
			pChildGO->Detach();
			delete pChildGO;
			//DPrint("GameObject::deleteing game object");
		}
		else
		{
			pChildGO->UpdateRecursive(dt_);
		}
	}

	
	//then update siblings

	if (HasParent() && !IsLastChild())
	{
		CGameObject * pNextGO =(CGameObject *)pNext;
		if (pNextGO->bGetTaggedForDeletion())
		{
			//DPrint("GameObject::deleteing game object");
			//DPrint(pNextGO->GetRenderable()->GetType());
			pNextGO->Detach();
			delete pNextGO;

		}
		else
		{
			pNextGO->UpdateRecursive(dt_);
		}
	}
}

void 
CGameObject::SetMaterial(IMaterial * pMaterial_)
{
	m_pMaterial=pMaterial_;
	m_pMaterial->SetGameObject(this);
}

void 
CGameObject::SetRenderable(IRenderable * pRenderable_)
{
	m_pRenderable=pRenderable_;
	m_pRenderable->SetGameObject(this);


}

void
CGameObject::GenerateColliderForRenderable(ICollider::eColliderType type)
{
	if (0==m_pRenderable) return;


	if (type ==ICollider::eColliderTypePlane)
	{
		SetCollider (new CPlaneCollider());
		return;
	}

	if (type == ICollider::eColliderTypeSphere)
	{
		//attempt to make sphere collider if required
		float rad = m_pRenderable->GetBoundingSphereRadius();
		if (rad>0)
		{
			SetCollider (new CSphereCollider(rad));
		}
		else
		{
			m_pCollider=0;
		}
	}
	if (type == ICollider::eColliderTypeCube)
	{
		SetCollider(new CCubeCollider());
		return;
	}
	if (type == ICollider::eColliderTypeLadder)
	{
		SetCollider(new CLadderCollider());
		return;
	}
}

void 
CGameObject::SetCollider(ICollider * pCollider_)
{
	m_pCollider=pCollider_;
	m_pCollider->SetGameObject(this);
	AddBehavior(new CUpdateBoundingSphereBehavior());
}

void
CGameObject::AddBehavior(IBehavior * pBehavior_)
{
	m_vBehaviors.push_back(pBehavior_);
	pBehavior_->SetGameObject(this);
}

void
CGameObject::SetTransform(CTransform * pTransform_)
{
	m_pTransform=pTransform_;
	m_pTransform->SetGameObject(this);

}

void 
CGameObject::SetCollisionResponder(ICollisionResponder * pResToCol_)
{
	m_pCollisionResponder=pResToCol_;
	m_pCollisionResponder->SetGameObject(this);
}

ICollisionResponder * 
CGameObject::GetCollisionResponder()
{
	return m_pCollisionResponder;
}

IRenderable * 
CGameObject::GetRenderable()
{
	return m_pRenderable;
}

IMaterial * 
CGameObject::GetMaterial()
{
	return m_pMaterial;
}

/*IBehavior * 
CGameObject::GetBehavior()
{
	return m_pBehavior;
}*/

CTransform * 
CGameObject::GetTransform()
{
	return m_pTransform;
}

ICollider*
CGameObject::GetCollider()
{
	return m_pCollider;
}

void
CGameObject::CalcDistanceFromCamera()
{
	CGameObject * cam = CTagManager::Instance()->GetObjectWithTag("Camera");
	
	if (cam)
	{
	CVector3 myPos = m_pTransform->GetPosition();
	CVector3 camPos = cam->GetTransform()->GetPosition();
	CVector3 relativePos= myPos - camPos;
	m_fDistanceFromCamera = abs( relativePos.GetLength());
	}

	//if renderable type is GUITexture then return 0
	if (strcmp(m_pRenderable->GetType(),"GUITextureRenderable")==0)
	{
		m_fDistanceFromCamera=0;
	}
}

float
CGameObject::GetDistanceFromCamera()
{
	CalcDistanceFromCamera();
	return m_fDistanceFromCamera;
}