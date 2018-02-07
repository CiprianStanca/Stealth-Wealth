#include "stdafx.h"
#include "Vector.h"
#include <math.h>

CVector3::CVector3(float x_,float y_, float z_)
{
	m_fX=x_;
	m_fY=y_;
	m_fZ=z_;
}

CVector3::CVector3()
{
	m_fX=0.0f;
	m_fY=0.0f;
	m_fZ=0.0f;
}

CVector3::~CVector3()
{
}

void CVector3::Normalise()
{
	float length = this->GetLength();

	if (length != 0.0f)
	{
		m_fX /= length;
		m_fY /= length;
		m_fZ /= length;
	}
}

float CVector3::DotProduct(CVector3 * invector)
{
	return 
		this->m_fX * invector->m_fX + 
		this->m_fY * invector->m_fY + 
		this->m_fZ * invector->m_fZ; 
}

void 
CVector3::CrossProduct(CVector3 * invector, CVector3 * out_)
{

	float dx1 = (this->m_fY * invector->m_fZ);
	float dx2 = (invector->m_fY * this->m_fZ);
	float dy1 = (this->m_fZ * invector->m_fX);
	float dy2 = (invector->m_fZ * this->m_fX);
	float dz1 = (this->m_fX * invector->m_fY);
	float dz2 = (invector->m_fX * this->m_fY);

	out_->m_fX = dx1 - dx2;
	out_->m_fY = dy1 - dy2;
	out_->m_fZ = dz1 - dz2;
	return;
}

CVector3 CVector3::operator-(CVector3 op2) 
{ 
	CVector3 temp; 
 
	temp.m_fX = m_fX - op2.m_fX; 
	temp.m_fY = m_fY - op2.m_fY; 
	temp.m_fZ = m_fZ - op2.m_fZ; 
	return temp; 
}

CVector3 CVector3::operator+(CVector3 op2) 
{ 
	CVector3 temp; 
 
	temp.m_fX = m_fX + op2.m_fX; 
	temp.m_fY = m_fY + op2.m_fY; 
	temp.m_fZ = m_fZ + op2.m_fZ; 
	return temp; 
}

CVector3 CVector3::operator*(float mult) 
{ 
	CVector3 temp; 
 
	temp.m_fX = m_fX * mult;
	temp.m_fY = m_fY * mult;
	temp.m_fZ = m_fZ * mult;
	return temp; 
}

void CVector3::operator*=(float mult) 
{ 
	CVector3 temp; 
 
	m_fX *= mult;
	m_fY *= mult;
	m_fZ *= mult;
}

float CVector3::GetLength()
{
	return sqrt(m_fX*m_fX + m_fY*m_fY + m_fZ*m_fZ);
}

void CVector3::AddVector(CVector3 * vec_)
{
	m_fX += vec_->m_fX;
	m_fY += vec_->m_fY;
	m_fZ += vec_->m_fZ;
}

CVector2::CVector2(float x_,float y_)
{
	m_fX=x_;
	m_fY=y_;
}

CVector2::CVector2()
{

}

CVector2::~CVector2(void)
{
}


void CVector2::Normalise()
{
	float length = this->GetLength();
	m_fX /= length;
	m_fY /= length;
}

float CVector2::DotProduct(CVector2 * invector)
{
	return 
		this->m_fX * invector->m_fX + 
		this->m_fY*invector->m_fY;
}

CVector2 CVector2::operator-(CVector2 op2) 
{ 
	CVector2 temp; 
 
	temp.m_fX = m_fX - op2.m_fX; 
	temp.m_fY = m_fY - op2.m_fY; 

	return temp; 
}

CVector2 CVector2::operator+(CVector2 op2) 
{ 
	CVector2 temp; 
 
	temp.m_fX = m_fX + op2.m_fX; 
	temp.m_fY = m_fY + op2.m_fY; 

	return temp; 
}

CVector2 CVector2::operator*(float mult) 
{ 
	CVector2 temp; 
 
	temp.m_fX = m_fX *mult;
	temp.m_fY = m_fY *mult;

	return temp; 
}

float CVector2::GetLength()
{
	return sqrt(m_fX*m_fX + m_fY*m_fY);
}

