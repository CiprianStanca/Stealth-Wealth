#include "StdAfx.h"
#include "IRenderable.h"

IRenderable::IRenderable(void)
{
	
}

IRenderable::~IRenderable(void)
{
}

float 
IRenderable::GetBoundingSphereRadius()
{
	return 0.0f;
}

void
IRenderable::GetBoundingSphereOffset(CVector3 * result_)
{
	result_->m_fX=0.0f;
	result_->m_fY=0.0f;
	result_->m_fZ=0.0f;
}