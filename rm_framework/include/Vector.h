#pragma once



class CVector3
{
public:
	CVector3(float x_, float y_, float z_);
	CVector3();
	~CVector3(void);
	void Normalise();
	float DotProduct(CVector3 * invector);
	void CrossProduct(CVector3 * invector, CVector3 *out_);
	CVector3 operator-(CVector3 op2);
	CVector3 operator+(CVector3 op2);
	CVector3 operator*(float mult);
	void operator*=(float mult);
	float GetLength();
	void AddVector(CVector3 * vec_);

	float m_fX;
	float m_fY;
	float m_fZ;
};

class CVector2
{
public:
	CVector2(float x_, float y_);
	CVector2();
	~CVector2(void);
	void Normalise();
	float DotProduct(CVector2 * invector);
	CVector2 operator-(CVector2 op2);
	CVector2 operator+(CVector2 op2);
	CVector2 operator*(float mult);
	float GetLength();

	float m_fX;
	float m_fY;

};
